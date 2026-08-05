#ifndef RLX_LDS_H
#define RLX_LDS_H

// Caution: remember to sync with sheipa.ld
#define TDNR_SIZE		(1928*1088)
#define VRAM_ALIGN		32
#define VRAM_SLOT		1
#define VRAM_CHN_0		((1920 * 1080 * 3 / 2 * VRAM_SLOT) + VRAM_ALIGN)
#define VRAM_CHN_1		((640  *  480 * 3 / 2 * VRAM_SLOT) + VRAM_ALIGN)
#define VRAM_CHN_2		((192  *  108 * 3 / 2 * VRAM_SLOT) + VRAM_ALIGN)
#define VRAM_SIZE		(VRAM_CHN_0 + VRAM_CHN_1 + VRAM_CHN_2)

extern unsigned char _tdnr_start_[];
extern unsigned char _vram_start_[];

#define TDNR_START		((const unsigned int)_tdnr_start_)
#define VRAM_START		((const unsigned int)_vram_start_)

// ----------------------------------------------------------------------------
#define VRAM_SIZE_YUV420(w, h)	(w*h*3/2)
#define VRAM_SIZE_YUV422(w, h)	(w*h*4/2)

#endif	// RLX_LDS_H
