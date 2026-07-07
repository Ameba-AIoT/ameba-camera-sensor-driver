


MEMORY
{
  ITCM_ROM   (rx)       : ORIGIN = 0x00000000, LENGTH = 0x400					/* 1KB	*/
  ITCM_RAM   (rwx)      : ORIGIN = 0x00040000, LENGTH = 0x10000  				/* 64KB */
  DTCM_ROM   (rx)       : ORIGIN = 0x20010000, LENGTH = 0x4000    				/* 16KB	*/
  DTCM_RAM   (rwx)      : ORIGIN = 0x20000000, LENGTH = 0xFF00					/* 63KB	*/
  ROM_RESV   (rwx)      : ORIGIN = 0x2000FF00, LENGTH = 0x100					/* 128B	*/   
  VOE_HEAD   (rwx)      : ORIGIN = 0x70000000, LENGTH = 0x70000040 - 0x70000000	/* 64B */  
  SENSOR     (rwx)      : ORIGIN = 0x70000040, LENGTH = 0x70008000 - 0x70000040	/* 32KB - 64B */  
  IQ         (rwx)      : ORIGIN = 0x70008000, LENGTH = 0x70035000 - 0x70008000	/* 180KB */
  IQ_CALI    (rwx)      : ORIGIN = 0x70035000, LENGTH = 0x7003A000 - 0x70035000	/* 20KB */    
  DDR_CMD    (rwx)      : ORIGIN = 0x7003A000, LENGTH = 0x7003C000 - 0x7003A000	/* 8KB   */
  DDR        (rwx)      : ORIGIN = 0x7003C000, LENGTH = 0x7009A000 - 0x7003C000	/* 376KB */
  DDR_2      (rwx)      : ORIGIN = 0x7009A000, LENGTH = 0x700E8000 - 0x7009A000	/* 312KB */
  BSS        (rwx)      : ORIGIN = 0x700E8000, LENGTH = 0x70100000 - 0x700E8000	/* 96KB  */
  
}


/* Library configurations */
/*GROUP(libgcc.a libc.a libm.a libnosys.a libsemihost.a)*/
GROUP(libgcc.a)

SECTIONS
{
	
  	.sensor :
	{
		__sensor_entry__ = .;
		KEEP(*sensor_*.o(.data.sensor_entry*))
		KEEP(*sensor_*.o(.bss*))
		KEEP(*sensor_*.o(.data*))
		KEEP(*sensor_*.o(.text*))
		KEEP(*sensor_*.o(.rodata*))		
		KEEP(*(.text))
		KEEP(*(.rodata))
		KEEP(*(.data))
		KEEP(*(.bss))
	} > SENSOR
	

    /* .stack section doesn't contains any symbols. It is only
     * used for linker to reserve space for the main stack section
     * WARNING: .stack should come immediately after the last secure memory
     * section.  This provides stack overflow detection. */

	 
    .stack (NOLOAD):
    {
	. = ALIGN(8);
	__StackLimit = .;
        *(.stack*);
     /*   . += 0x400 - (. - __StackLimit); */
        . += (ORIGIN(DTCM_RAM) + LENGTH(DTCM_RAM) - 8 - .); 
    } > DTCM_RAM
	
    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    __StackTop = ADDR(.stack) + SIZEOF(.stack);
    PROVIDE(__stack = __StackTop);
	
}
