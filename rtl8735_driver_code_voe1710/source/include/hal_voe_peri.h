#ifndef _HAL_VOE_PERI_H_
#define _HAL_VOE_PERI_H_

void voe_wdt_enable(int mode, int sec);
void voe_wdt_refresh(void);
uint8_t hal_sys_get_rom_ver(void);


#endif // _HAL_VOE_PERI_H_
