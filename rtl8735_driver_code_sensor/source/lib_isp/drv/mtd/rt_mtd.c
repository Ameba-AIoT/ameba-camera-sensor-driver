#include "rt_mtd.h"
#include "rt_util.h"

//#include "rlxboard.h"  // Frank: MUST before part.h
#include "rlx_mman.h"

#include "spi_flash.h"
#include "sf_internal.h"

enum {
	RT_SF_OPCODE_READ = 0,
	RT_SF_OPCODE_WRITE,
	RT_SF_OPCODE_UPDATE,
	RT_SF_OPCODE_DUMP,
	RT_SF_OPCODE_ERASE,
	RT_SF_OPCODE_NUM,
};

struct spi_flash *flash = NULL;

void rt_sf_print(void)
{
	if (!flash)
	{
		rt_printf("error! not opened (probe).\n");
		return;
	}
	char str[32];
	rt_printf("SF Detected %s, ", flash->name);
	rt_printf("page %s, ", size_to_str(flash->page_size, str));
	rt_printf("sector %s, ", size_to_str(flash->sector_size, str));
	rt_printf("erase %s, ", size_to_str(flash->erase_size, str));
	rt_printf("total %s", size_to_str(flash->size, str));
	rt_printf("\n");
}

int rt_sf_probe(unsigned int bus, unsigned int cs, unsigned int speed, unsigned int mode)
{
	struct spi_flash *new;

#ifdef CONFIG_SPI_NOR_PRM_MODE
	spi_flash_exit_prm_mode(flash->spi);
	spi_flash_disable_prm(flash->spi);
#endif
	new = spi_flash_probe(bus, cs, speed, mode);
	if (!new)
	{
		rt_printf("fail to probe SPI flash at %u:%u\n", bus, cs);
		return RT_E_INIT_FAIL;
	}
#ifdef CONFIG_SPI_NOR_PRM_MODE
	spi_flash_enable_prm(flash->spi);
#endif
	if (flash)
		spi_flash_free(flash);
	flash = new;

	return RT_OK;
}

/**
 * This function takes a byte length and a delta unit of time to compute the
 * approximate bytes per second
 *
 * @param len       amount of bytes currently processed
 * @param start_ms  start time of processing in ms
 * @return bytes per second if OK, 0 on error
 */
// static ulong bytes_per_second(unsigned int len, ulong start_ms)
// {
//     // less accurate but avoids overflow
//     if (len >= ((unsigned int) -1) / 1024)
//         return len / (max(get_timer(start_ms) / 1024, 1));
//     else
//         return 1024 * len / max(get_timer(start_ms), 1);
// }

/**
 * Write a block of data to SPI flash, first checking if it is different from
 * what is already there.
 *
 * If the data being written is the same, then *skipped is incremented by len.
 *
 * @param flash     flash context pointer
 * @param offset    flash offset to write
 * @param len       number of bytes to write
 * @param buf       buffer to write from
 * @param cmp_buf   read buffer to use to compare data
 * @param skipped   Count of skipped data (incremented by this function)
 * @return NULL if OK, else a string containing the stage which failed
 */
// Frank, change return type.
// return: RT_OK, RT_E_MTD_READ, RT_E_MTD_WRITE, RT_E_MTD_ERASE
static int spi_flash_update_block(struct spi_flash *flash, unsigned int offset,
		size_t len, const char *buf, char *cmp_buf, size_t *skipped)
{
	//debug("offset=%#x, sector_size=%#x, len=%#zx\n", offset, flash->sector_size, len);

	// Read the entire sector so to allow for rewriting
	if (spi_flash_read(flash, offset, flash->sector_size, cmp_buf))
		return RT_E_MTD_READ;
	// Compare only what is meaningful (len)
	if (memcmp(cmp_buf, buf, len) == 0)
	{
		//debug("Skip region %x size %zx: no change\n", offset, len);
		*skipped += len;
		return RT_OK;
	}
	// Erase the entire sector
	if (spi_flash_erase(flash, offset, flash->sector_size))
		return RT_E_MTD_ERASE;
	// Write the initial part of the block from the source
	if (spi_flash_write(flash, offset, len, buf))
		return RT_E_MTD_WRITE;
	// If it's a partial sector, rewrite the existing part
	if (len != flash->sector_size)
	{
		// Rewrite the original data to the end of the sector
		if (spi_flash_write(flash, offset + len, flash->sector_size - len, &cmp_buf[len]))
			return RT_E_MTD_WRITE;
	}

	return RT_OK;
}

typedef struct {
	size_t  bytes_written;
	size_t  bytes_skipped;
	// ----- log if error occurs -----
	unsigned int  err_offset;
	size_t  err_todo;
	int     err_code;
} sf_update_log_st;

static const char *s_mtd_err_code_str[] = { "MALLOC", "READ", "WRITE", "ERASE" };

/**
 * Update an area of SPI flash by erasing and writing any blocks which need
 * to change. Existing blocks with the correct data are left unchanged.
 *
 * @param flash     flash context pointer
 * @param offset    flash offset to write
 * @param len       number of bytes to write
 * @param buf       buffer to write from
 * @return 0 if ok, 1 on error
 */
// note: comment get_timer() related print msg for now.
static int spi_flash_update(struct spi_flash *flash, unsigned int offset, size_t len, const char *buf, sf_update_log_st *log)
{
	char *cmp_buf = NULL;

	const char *end = buf + len;
	int code = RT_OK;
	size_t todo;        // number of bytes to do in this pass
	size_t skipped = 0; // statistics
	//const ulong start_time = get_timer(0);
	//size_t scale = 1;
	//const char *start_buf = buf;
	//ulong delta;

	// if (end - buf >= 200)
	//     scale = (end - buf) / 100;
	//
	if (!(cmp_buf = rt_malloc(flash->sector_size)))
	{
		log->err_code   = RT_E_MTD_MALLOC;
		log->err_offset = offset;
		log->err_todo   = min((unsigned int)(end - buf), flash->sector_size);
		return RT_E_OPERATE_FAIL;
	}
	//my_printf("cmp_buf = 0x%08x\n", (uint)cmp_buf);

	// ulong last_update = get_timer(0);
	for (; buf < end && (code == RT_OK); buf += todo, offset += todo)
	{
		todo = min((unsigned int)(end - buf), flash->sector_size);
		// if (get_timer(last_update) > 100)
		// {
		//     rt_printf("   \rUpdating, %zu%% %lu B/s",
		//             100 - (end-buf)/scale,
		//             bytes_per_second(buf - start_buf, start_time));
		//     last_update = get_timer(0);
		// }
		code = spi_flash_update_block(flash, offset, todo, buf, cmp_buf, &skipped);
		// update log.
		log->err_code   = (code - RT_CODE_BASE_MTD);
		log->err_offset = offset;
		log->err_todo   = todo;
		if (code != RT_OK)
		{
			//my_debug("0x%08x, %d, %d\n", offset, todo, code);
			break;
		}
	}
	rt_free(cmp_buf);
	//putc(stdout, '\r');
	if (code != RT_OK)
	{
		return RT_E_OPERATE_FAIL;
	}
	//
	log->bytes_written = len - skipped;
	log->bytes_skipped = skipped;
	// delta = get_timer(start_time);
	// rt_printf("%u bytes written, %u bytes skipped\n", len - skipped, skipped);
	// rt_printf(" in %ld.%lds, speed %ld B/s\n", delta / 1000, delta % 1000, bytes_per_second(len, start_time));

	spi_flash_set_auto_mode(flash->spi);
#ifdef CONFIG_SPI_NOR_PRM_MODE
	spi_flash_set_prm_mode(flash->spi);
#endif

	return RT_OK;
}

// return
//  RT_E_NOT_OPEN       : maybe 'sf probe' not run before.
//  RT_E_INVALID_ARG    : maybe opcode is invalid
//  RT_E_OUT_OF_RANGE   : (sf_addr + len > flash->size)
//  RT_E_MMAP_FAIL      : fail to map physical memory
//  RT_E_INVALID_LENGTH : @len is invalid
//
int rt_sf_do_ops(int opcode, u32 mem_addr, u32 sf_addr, u32 len)
{
	const char *opcode_str[] = {"READ", "WRITE", "UPDATE", "DUMP", "ERASE"};
	sf_update_log_st    update_log = {0};
	rt_dump_opt_st  opt = {0};
	void *buf;
	int ret = RT_OK;

	if (flash == NULL)
	{
		rt_printf("error! sf not opened (probe).\n");
		return RT_E_NOT_OPEN;
	}
	if (opcode < RT_SF_OPCODE_READ || opcode >= RT_SF_OPCODE_NUM)
	{
		rt_fatal("invalid opcode.\n");
		return RT_E_INVALID_ARG;
	}
	// Consistency checking
	if (sf_addr + len > flash->size)
	{
		rt_printf("error! access exceed flash size\n");
		return RT_E_OUT_OF_RANGE;
	}
	if (len == 0)
	{
		rt_printf("error! len = 0\n");
		return RT_E_INVALID_LENGTH;
	}
	buf = NULL;
	// ERASE
	if (opcode == RT_SF_OPCODE_ERASE)
	{
		ret = spi_flash_erase(flash, sf_addr, len);
		goto post;
	}
	// READ, WRITE, DUMP
	buf = rlx_map_physmem(mem_addr, len, MAP_WRBACK);
	if (!buf)
	{
		rt_printf("error! map_physmem fail\n");
		return RT_E_MMAP_FAIL;
	}
	//
	if (opcode == RT_SF_OPCODE_READ)
	{
		if (len % RT_SF_READ_UNIT_SZ)
		{
			rt_printf("error! len (%d), invalid readsize, not multiple of %d-bytes\n", (int)len, RT_SF_READ_UNIT_SZ);
			return RT_E_INVALID_LENGTH;
		}
		ret = spi_flash_read(flash, sf_addr, len, buf);
	}
	if (opcode == RT_SF_OPCODE_DUMP)
	{
		ret = spi_flash_read(flash, sf_addr, len, buf);
	}
	else if (opcode == RT_SF_OPCODE_WRITE)
	{
		ret = spi_flash_write(flash, sf_addr, len, buf);
	}
	else if (opcode == RT_SF_OPCODE_UPDATE)
	{
		if (sf_addr % flash->erase_size)
		{
			rt_printf("error! sf_addr (0x%08X) is not aligned to flash erase_size.\n", (UINT)sf_addr);
			return RT_E_INVALID_ARG;
		}
		ret = spi_flash_update(flash, sf_addr, len, buf, &update_log);
	}
	// fall through
post:
	ret = (ret == 0 ? RT_OK : RT_E_OPERATE_FAIL);
	rt_printf("{SF} %lu bytes @ %#x %s: %s\n", (ULONG)len, (UINT)sf_addr, opcode_str[opcode], (ret == RT_OK ? "OK" : "ERROR"));
	if ((opcode == RT_SF_OPCODE_DUMP) && (ret == RT_OK))
	{
		rt_printf("by using, mem_addr = 0x%08X, mmap buf = 0x%08X\n", (UINT)mem_addr, (UINT)buf);
		opt.flag.addr_show = 1;
		opt.flag.note_show = 1;
		opt.addr_start = sf_addr;
		rt_printf("\n");
		rt_dump_mem_ex((uint32_t)buf, len, &opt);
		rt_printf("\n");
	}
	if (opcode == RT_SF_OPCODE_UPDATE)
	{
		if (ret == RT_OK)
		{
			rt_printf("%u bytes written, %u bytes skipped\n", update_log.bytes_written, update_log.bytes_skipped);
		}
		else
		{
			rt_printf("error! -> code = %d (%s), ", update_log.err_code, s_mtd_err_code_str[update_log.err_code]);
			if (update_log.err_code == RT_E_MTD_MALLOC)
			{
				rt_printf("(log) sf_addr = 0x%08X, todo = %d bytes", update_log.err_offset, update_log.err_todo);
			}
			rt_printf("\n");
		}
	}
	//
	if (buf)
	{
		//rlx_unmap_physmem(buf, len);
	}
	return ret;
}

int rt_sf_dump(u32 mem_addr, u32 sf_addr, u32 len)
{
	return rt_sf_do_ops(RT_SF_OPCODE_DUMP, mem_addr, sf_addr, len);
}

int rt_sf_erase(u32 sf_addr, u32 len)
{
	return rt_sf_do_ops(RT_SF_OPCODE_ERASE, 0, sf_addr, len);
}

int rt_sf_read(u32 mem_addr, u32 sf_addr, u32 len)
{
	return rt_sf_do_ops(RT_SF_OPCODE_READ, mem_addr, sf_addr, len);
}

int rt_sf_write(u32 mem_addr, u32 sf_addr, u32 len)
{
	return rt_sf_do_ops(RT_SF_OPCODE_WRITE, mem_addr, sf_addr, len);
}

int rt_sf_update(u32 mem_addr, u32 sf_addr, u32 len)
{
	void *mem_ptr;
	int ncopy, ret;

	if (flash == NULL)
	{
		rt_printf("error! sf not opened (probe).\n");
		return RT_E_NOT_OPEN;
	}
	if (len == 0)
	{
		rt_warning("len = 0\n");
		return RT_OK;
	}
	if (sf_addr + len > flash->size)
	{
		rt_printf("error! access exceed flash size\n");
		return RT_E_OUT_OF_RANGE;
	}

	int idx = 0;
	u32 sf_ptr = sf_addr;
	int size = flash->erase_size;

	if (sf_addr % flash->erase_size == 0)
		goto has_aligned;
	// if block#0 is non-aligned.
	if (!(mem_ptr = rt_malloc(size)))
	{
		rt_err("read buf oom!\n");
		return RT_E_NO_MEMORY;
	}
	sf_ptr = ROUND(sf_addr, size) - size;
	ret = rt_sf_read((u32)mem_ptr, sf_ptr, size);
	if (ret != RT_OK)
	{
		rt_printf("{SF} blk#%d, sf_read(0x%08x, 0x%08x, %d) = %s\n", idx, (UINT)mem_ptr, sf_ptr, size, rt_code_str(ret));
		goto free_exit;
	}
	ncopy = (sf_ptr + size) - sf_addr;
	if (ncopy > (int)len)
		ncopy = len;
	memcpy((void *)((u32)mem_ptr + (sf_addr-sf_ptr)), (void *)mem_addr, ncopy);
	//
	// my_printf("{SF} ncopy = %d, 0x%08x\n", ncopy, (UINT)(mem_ptr + (sf_addr-sf_ptr)));
	// my_printf("{SF} blk#%d, sf_update(0x%08x, 0x%08x, %d)\n", idx, (UINT)mem_ptr, sf_ptr, size);
	ret = rt_sf_do_ops(RT_SF_OPCODE_UPDATE, (u32)mem_ptr, sf_ptr, size);
	if (ret != RT_OK)
	{
		rt_printf("{SF} blk#%d, sf_update(0x%08x, 0x%08x, %d) = %s\n", idx, (UINT)mem_ptr, sf_ptr, size, rt_code_str(ret));
		goto free_exit;
	}
	rt_safe_free(mem_ptr);
	sf_addr += ncopy;
	mem_addr += ncopy;
	len -= ncopy;

has_aligned:
	while (len > 0)
	{
		idx++;
		if (len > (u32)size)
		{
			len -= size;
		}
		else
		{
			size = len;
			len = 0;
		}
		//my_printf("{SF} blk#%d, sf_update(0x%08x, 0x%08x, %d)\n", idx, (UINT)mem_addr, sf_addr, size);
		ret = rt_sf_do_ops(RT_SF_OPCODE_UPDATE, mem_addr, sf_addr, size);
		if (ret != RT_OK)
		{
			rt_printf("{SF} block#%d, sf_update(0x%08x, 0x%08x, %d) = %s\n", idx, (UINT)mem_ptr, sf_ptr, size, rt_code_str(ret));
			break;
		}
		sf_addr += size;
		mem_addr += size;
	}
	return ret;

free_exit:
	rt_safe_free(mem_ptr);
	return ret;
}

int rt_sf_rdsr(u8 code, u8 *out)
{
	int ret;

	if (flash == NULL)
	{
		rt_printf("error! sf not opened (probe).\n");
		return RT_E_NOT_OPEN;
	}
	ret = spi_flash_cmd_read_status(flash, out, code);
	return ret;
}

// ----------------------------------------------------------------------------
//  MTD partition info.
// ----------------------------------------------------------------------------
extern pair_uint_cstr_st   g_mtd_part[];

int g_mtd_part_size(void)
{
	pair_uint_cstr_st *p = g_mtd_part;
	int n = 0;
	do
	{
		if (n++ > 16)
		{
			RT_ASSERT(1);
		}
		p++;
	} while (p->first);
	return n;
}

void rt_mtd_dump(void)
{
	if (!flash)
	{
		rt_printf("error! sf not opened (probe).\n");
		return;
	}
	rt_printf("dev : %-8s %-8s %-12s%s\n", "sf_addr", "size", "erasesize", "name");
	for (int i = 0; i < g_mtd_part_size(); i++)
	{
		rt_printf("mtd%d: %08X %08x %08x    \"%s\"\n", i,
				rt_mtd_calc_sf_addr(i, 0),
				g_mtd_part[i].first,
				flash->erase_size,
				g_mtd_part[i].second);
	}
	rt_printf("\n");
	return;
}

u32 rt_mtd_calc_sf_addr(u8 mtd_idx, u32 mtd_ofs)
{
	RT_ASSERT(mtd_idx < g_mtd_part_size());

	u32 adr = mtd_ofs;
	if (mtd_idx <= 1)
		return adr;

	for (int i = 1; i < mtd_idx; i++)
		adr += g_mtd_part[i].first;

	return adr;
}
