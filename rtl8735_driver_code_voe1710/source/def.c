
#include "cmsis_voe.h"
#include "hal_video.h"
#include "voe_def.h"

#if 0
SECTION_VIDEO_ADP volatile __attribute__ ((aligned (32))) hal_video_adapter_t video_adaptor
={
		.cmd[0] = (commandLine_s *)(0x70000000 + 0x3A000 + 0x080),
		.cmd[1] = (commandLine_s *)(0x70000000 + 0x3A000 + 0x580),
		.cmd[2] = (commandLine_s *)(0x70000000 + 0x3A000 + 0xa80),
		.cmd[3] = (commandLine_s *)(0x70000000 + 0x3A000 + 0xf80),
		.cmd[4] = (commandLine_s *)(0x70000000 + 0x3A000 + 0x1480),
};
#endif

