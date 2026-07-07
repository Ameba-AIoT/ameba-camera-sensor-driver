
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	71 04 00 70 69 00 00 70                             q..pi..p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

70000064 <g_imx775_i2c_init_regs_linear>:
70000064:	e1 00 01 00                                         ....

70000068 <rts_isp_set_voe_ops>:
70000068:	4b01      	ldr	r3, [pc, #4]	; (70000070 <rts_isp_set_voe_ops+0x8>)
7000006a:	6018      	str	r0, [r3, #0]
7000006c:	4770      	bx	lr
7000006e:	bf00      	nop
70000070:	70000048 	.word	0x70000048

70000074 <isp_driver_is_fpga>:
70000074:	2000      	movs	r0, #0
70000076:	4770      	bx	lr

70000078 <imx775_get_info>:
70000078:	b530      	push	{r4, r5, lr}
7000007a:	2800      	cmp	r0, #0
7000007c:	d157      	bne.n	7000012e <imx775_get_info+0xb6>
7000007e:	2900      	cmp	r1, #0
70000080:	d055      	beq.n	7000012e <imx775_get_info+0xb6>
70000082:	f44f 6522 	mov.w	r5, #2592	; 0xa20
70000086:	f44f 64f3 	mov.w	r4, #1944	; 0x798
7000008a:	4a2a      	ldr	r2, [pc, #168]	; (70000134 <imx775_get_info+0xbc>)
7000008c:	2301      	movs	r3, #1
7000008e:	f8df c0a8 	ldr.w	ip, [pc, #168]	; 70000138 <imx775_get_info+0xc0>
70000092:	610a      	str	r2, [r1, #16]
70000094:	620a      	str	r2, [r1, #32]
70000096:	4a29      	ldr	r2, [pc, #164]	; (7000013c <imx775_get_info+0xc4>)
70000098:	7108      	strb	r0, [r1, #4]
7000009a:	7812      	ldrb	r2, [r2, #0]
7000009c:	750b      	strb	r3, [r1, #20]
7000009e:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
700000a2:	220a      	movs	r2, #10
700000a4:	f8c1 0090 	str.w	r0, [r1, #144]	; 0x90
700000a8:	f8c1 20a0 	str.w	r2, [r1, #160]	; 0xa0
700000ac:	f881 0098 	strb.w	r0, [r1, #152]	; 0x98
700000b0:	f8c1 309c 	str.w	r3, [r1, #156]	; 0x9c
700000b4:	f881 30a4 	strb.w	r3, [r1, #164]	; 0xa4
700000b8:	f881 00b0 	strb.w	r0, [r1, #176]	; 0xb0
700000bc:	f881 30c8 	strb.w	r3, [r1, #200]	; 0xc8
700000c0:	f8c1 30cc 	str.w	r3, [r1, #204]	; 0xcc
700000c4:	f881 00d4 	strb.w	r0, [r1, #212]	; 0xd4
700000c8:	f8c1 30d8 	str.w	r3, [r1, #216]	; 0xd8
700000cc:	e9c1 5402 	strd	r5, r4, [r1, #8]
700000d0:	e9c1 5406 	strd	r5, r4, [r1, #24]
700000d4:	2532      	movs	r5, #50	; 0x32
700000d6:	2402      	movs	r4, #2
700000d8:	f8c1 5094 	str.w	r5, [r1, #148]	; 0x94
700000dc:	600c      	str	r4, [r1, #0]
700000de:	e9c1 052a 	strd	r0, r5, [r1, #168]	; 0xa8
700000e2:	2564      	movs	r5, #100	; 0x64
700000e4:	e9c1 c530 	strd	ip, r5, [r1, #192]	; 0xc0
700000e8:	25c8      	movs	r5, #200	; 0xc8
700000ea:	f8c1 50d0 	str.w	r5, [r1, #208]	; 0xd0
700000ee:	f44f 75fa 	mov.w	r5, #500	; 0x1f4
700000f2:	f8c1 50dc 	str.w	r5, [r1, #220]	; 0xdc
700000f6:	251b      	movs	r5, #27
700000f8:	e9c1 022d 	strd	r0, r2, [r1, #180]	; 0xb4
700000fc:	f881 5085 	strb.w	r5, [r1, #133]	; 0x85
70000100:	2203      	movs	r2, #3
70000102:	f44f 7581 	mov.w	r5, #258	; 0x102
70000106:	f881 20bc 	strb.w	r2, [r1, #188]	; 0xbc
7000010a:	f8a1 5086 	strh.w	r5, [r1, #134]	; 0x86
7000010e:	2507      	movs	r5, #7
70000110:	f881 208c 	strb.w	r2, [r1, #140]	; 0x8c
70000114:	f8c1 5088 	str.w	r5, [r1, #136]	; 0x88
70000118:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
7000011c:	f881 22e4 	strb.w	r2, [r1, #740]	; 0x2e4
70000120:	f8c1 42d4 	str.w	r4, [r1, #724]	; 0x2d4
70000124:	e9c1 03b7 	strd	r0, r3, [r1, #732]	; 0x2dc
70000128:	e9c1 03ba 	strd	r0, r3, [r1, #744]	; 0x2e8
7000012c:	bd30      	pop	{r4, r5, pc}
7000012e:	f06f 0015 	mvn.w	r0, #21
70000132:	e7fb      	b.n	7000012c <imx775_get_info+0xb4>
70000134:	41f00000 	.word	0x41f00000
70000138:	016e3600 	.word	0x016e3600
7000013c:	7000004c 	.word	0x7000004c

70000140 <imx775_start>:
70000140:	b918      	cbnz	r0, 7000014a <imx775_start+0xa>
70000142:	4b03      	ldr	r3, [pc, #12]	; (70000150 <imx775_start+0x10>)
70000144:	2200      	movs	r2, #0
70000146:	609a      	str	r2, [r3, #8]
70000148:	4770      	bx	lr
7000014a:	f06f 0015 	mvn.w	r0, #21
7000014e:	4770      	bx	lr
70000150:	7000004c 	.word	0x7000004c

70000154 <imx775_get_tuned_dgain>:
70000154:	b948      	cbnz	r0, 7000016a <imx775_get_tuned_dgain+0x16>
70000156:	b141      	cbz	r1, 7000016a <imx775_get_tuned_dgain+0x16>
70000158:	4a05      	ldr	r2, [pc, #20]	; (70000170 <imx775_get_tuned_dgain+0x1c>)
7000015a:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
7000015e:	7812      	ldrb	r2, [r2, #0]
70000160:	600b      	str	r3, [r1, #0]
70000162:	2a01      	cmp	r2, #1
70000164:	d103      	bne.n	7000016e <imx775_get_tuned_dgain+0x1a>
70000166:	604b      	str	r3, [r1, #4]
70000168:	4770      	bx	lr
7000016a:	f06f 0015 	mvn.w	r0, #21
7000016e:	4770      	bx	lr
70000170:	7000004c 	.word	0x7000004c

70000174 <imx775_get_exposure_gain_info>:
70000174:	2000      	movs	r0, #0
70000176:	4770      	bx	lr

70000178 <imx775_set_mirror_flip>:
70000178:	780b      	ldrb	r3, [r1, #0]
7000017a:	784a      	ldrb	r2, [r1, #1]
7000017c:	2b00      	cmp	r3, #0
7000017e:	bf14      	ite	ne
70000180:	2302      	movne	r3, #2
70000182:	2300      	moveq	r3, #0
70000184:	2a00      	cmp	r2, #0
70000186:	bf18      	it	ne
70000188:	f043 0301 	orrne.w	r3, r3, #1
7000018c:	2201      	movs	r2, #1
7000018e:	2b02      	cmp	r3, #2
70000190:	708a      	strb	r2, [r1, #2]
70000192:	d00d      	beq.n	700001b0 <imx775_set_mirror_flip+0x38>
70000194:	2b03      	cmp	r3, #3
70000196:	d00e      	beq.n	700001b6 <imx775_set_mirror_flip+0x3e>
70000198:	4293      	cmp	r3, r2
7000019a:	f642 03b2 	movw	r3, #10418	; 0x28b2
7000019e:	610b      	str	r3, [r1, #16]
700001a0:	d00b      	beq.n	700001ba <imx775_set_mirror_flip+0x42>
700001a2:	f247 634e 	movw	r3, #30286	; 0x764e
700001a6:	624b      	str	r3, [r1, #36]	; 0x24
700001a8:	2302      	movs	r3, #2
700001aa:	2000      	movs	r0, #0
700001ac:	604b      	str	r3, [r1, #4]
700001ae:	4770      	bx	lr
700001b0:	4b03      	ldr	r3, [pc, #12]	; (700001c0 <imx775_set_mirror_flip+0x48>)
700001b2:	610b      	str	r3, [r1, #16]
700001b4:	e7f5      	b.n	700001a2 <imx775_set_mirror_flip+0x2a>
700001b6:	4b02      	ldr	r3, [pc, #8]	; (700001c0 <imx775_set_mirror_flip+0x48>)
700001b8:	610b      	str	r3, [r1, #16]
700001ba:	4b02      	ldr	r3, [pc, #8]	; (700001c4 <imx775_set_mirror_flip+0x4c>)
700001bc:	e7f3      	b.n	700001a6 <imx775_set_mirror_flip+0x2e>
700001be:	bf00      	nop
700001c0:	000128b2 	.word	0x000128b2
700001c4:	0001764e 	.word	0x0001764e

700001c8 <imx775_check>:
700001c8:	e92d 41f3 	stmdb	sp!, {r0, r1, r4, r5, r6, r7, r8, lr}
700001cc:	4d1b      	ldr	r5, [pc, #108]	; (7000023c <imx775_check+0x74>)
700001ce:	4607      	mov	r7, r0
700001d0:	682b      	ldr	r3, [r5, #0]
700001d2:	685b      	ldr	r3, [r3, #4]
700001d4:	4798      	blx	r3
700001d6:	f242 5309 	movw	r3, #9481	; 0x2509
700001da:	a901      	add	r1, sp, #4
700001dc:	4638      	mov	r0, r7
700001de:	f8ad 3004 	strh.w	r3, [sp, #4]
700001e2:	682b      	ldr	r3, [r5, #0]
700001e4:	68db      	ldr	r3, [r3, #12]
700001e6:	4798      	blx	r3
700001e8:	4604      	mov	r4, r0
700001ea:	b130      	cbz	r0, 700001fa <imx775_check+0x32>
700001ec:	682b      	ldr	r3, [r5, #0]
700001ee:	689b      	ldr	r3, [r3, #8]
700001f0:	4798      	blx	r3
700001f2:	4620      	mov	r0, r4
700001f4:	b002      	add	sp, #8
700001f6:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
700001fa:	f242 53b1 	movw	r3, #9649	; 0x25b1
700001fe:	a901      	add	r1, sp, #4
70000200:	4638      	mov	r0, r7
70000202:	f8bd 8006 	ldrh.w	r8, [sp, #6]
70000206:	f8ad 3004 	strh.w	r3, [sp, #4]
7000020a:	682b      	ldr	r3, [r5, #0]
7000020c:	68db      	ldr	r3, [r3, #12]
7000020e:	4798      	blx	r3
70000210:	682b      	ldr	r3, [r5, #0]
70000212:	4604      	mov	r4, r0
70000214:	689b      	ldr	r3, [r3, #8]
70000216:	4798      	blx	r3
70000218:	2c00      	cmp	r4, #0
7000021a:	d1ea      	bne.n	700001f2 <imx775_check+0x2a>
7000021c:	f8bd 6006 	ldrh.w	r6, [sp, #6]
70000220:	682b      	ldr	r3, [r5, #0]
70000222:	ea46 2608 	orr.w	r6, r6, r8, lsl #8
70000226:	4806      	ldr	r0, [pc, #24]	; (70000240 <imx775_check+0x78>)
70000228:	681b      	ldr	r3, [r3, #0]
7000022a:	4631      	mov	r1, r6
7000022c:	4798      	blx	r3
7000022e:	f24a 3328 	movw	r3, #41768	; 0xa328
70000232:	429e      	cmp	r6, r3
70000234:	bf18      	it	ne
70000236:	f06f 0415 	mvnne.w	r4, #21
7000023a:	e7da      	b.n	700001f2 <imx775_check+0x2a>
7000023c:	70000048 	.word	0x70000048
70000240:	70000478 	.word	0x70000478

70000244 <imx775_get_init_info>:
70000244:	b510      	push	{r4, lr}
70000246:	bb90      	cbnz	r0, 700002ae <imx775_get_init_info+0x6a>
70000248:	b38a      	cbz	r2, 700002ae <imx775_get_init_info+0x6a>
7000024a:	7809      	ldrb	r1, [r1, #0]
7000024c:	4b19      	ldr	r3, [pc, #100]	; (700002b4 <imx775_get_init_info+0x70>)
7000024e:	2901      	cmp	r1, #1
70000250:	7019      	strb	r1, [r3, #0]
70000252:	d02b      	beq.n	700002ac <imx775_get_init_info+0x68>
70000254:	4918      	ldr	r1, [pc, #96]	; (700002b8 <imx775_get_init_info+0x74>)
70000256:	f44f 64f4 	mov.w	r4, #1952	; 0x7a0
7000025a:	f640 2c28 	movw	ip, #2600	; 0xa28
7000025e:	6051      	str	r1, [r2, #4]
70000260:	2101      	movs	r1, #1
70000262:	6011      	str	r1, [r2, #0]
70000264:	f645 51c0 	movw	r1, #24000	; 0x5dc0
70000268:	6091      	str	r1, [r2, #8]
7000026a:	2102      	movs	r1, #2
7000026c:	f882 1064 	strb.w	r1, [r2, #100]	; 0x64
70000270:	f240 310f 	movw	r1, #783	; 0x30f
70000274:	f8a2 1068 	strh.w	r1, [r2, #104]	; 0x68
70000278:	210c      	movs	r1, #12
7000027a:	f8a2 1074 	strh.w	r1, [r2, #116]	; 0x74
7000027e:	2104      	movs	r1, #4
70000280:	e9c2 c420 	strd	ip, r4, [r2, #128]	; 0x80
70000284:	f882 1060 	strb.w	r1, [r2, #96]	; 0x60
70000288:	f44f 54a5 	mov.w	r4, #5280	; 0x14a0
7000028c:	e9c2 1122 	strd	r1, r1, [r2, #136]	; 0x88
70000290:	490a      	ldr	r1, [pc, #40]	; (700002bc <imx775_get_init_info+0x78>)
70000292:	e9c2 1424 	strd	r1, r4, [r2, #144]	; 0x90
70000296:	f240 41e2 	movw	r1, #1250	; 0x4e2
7000029a:	f8c2 1098 	str.w	r1, [r2, #152]	; 0x98
7000029e:	8299      	strh	r1, [r3, #20]
700002a0:	f64f 311d 	movw	r1, #64285	; 0xfb1d
700002a4:	f8c2 109c 	str.w	r1, [r2, #156]	; 0x9c
700002a8:	4a05      	ldr	r2, [pc, #20]	; (700002c0 <imx775_get_init_info+0x7c>)
700002aa:	605a      	str	r2, [r3, #4]
700002ac:	bd10      	pop	{r4, pc}
700002ae:	f06f 0015 	mvn.w	r0, #21
700002b2:	e7fb      	b.n	700002ac <imx775_get_init_info+0x68>
700002b4:	7000004c 	.word	0x7000004c
700002b8:	70000064 	.word	0x70000064
700002bc:	0bcd3d80 	.word	0x0bcd3d80
700002c0:	41d55555 	.word	0x41d55555

700002c4 <imx775_get_exposure_range>:
700002c4:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
700002c8:	f8dd 8020 	ldr.w	r8, [sp, #32]
700002cc:	460c      	mov	r4, r1
700002ce:	4617      	mov	r7, r2
700002d0:	461e      	mov	r6, r3
700002d2:	4605      	mov	r5, r0
700002d4:	2800      	cmp	r0, #0
700002d6:	d14f      	bne.n	70000378 <imx775_get_exposure_range+0xb4>
700002d8:	4b29      	ldr	r3, [pc, #164]	; (70000380 <imx775_get_exposure_range+0xbc>)
700002da:	f893 a000 	ldrb.w	sl, [r3]
700002de:	f8d3 9004 	ldr.w	r9, [r3, #4]
700002e2:	f1ba 0f00 	cmp.w	sl, #0
700002e6:	d110      	bne.n	7000030a <imx775_get_exposure_range+0x46>
700002e8:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
700002ec:	4648      	mov	r0, r9
700002ee:	f002 f9d3 	bl	70002698 <__aeabi_fmul>
700002f2:	6030      	str	r0, [r6, #0]
700002f4:	1e60      	subs	r0, r4, #1
700002f6:	f002 f977 	bl	700025e8 <__aeabi_ui2f>
700002fa:	4649      	mov	r1, r9
700002fc:	f002 f9cc 	bl	70002698 <__aeabi_fmul>
70000300:	f8c8 0000 	str.w	r0, [r8]
70000304:	4650      	mov	r0, sl
70000306:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
7000030a:	f101 4100 	add.w	r1, r1, #2147483648	; 0x80000000
7000030e:	3906      	subs	r1, #6
70000310:	004c      	lsls	r4, r1, #1
70000312:	4620      	mov	r0, r4
70000314:	f6a4 04b5 	subw	r4, r4, #2229	; 0x8b5
70000318:	f002 f966 	bl	700025e8 <__aeabi_ui2f>
7000031c:	4682      	mov	sl, r0
7000031e:	f04f 517e 	mov.w	r1, #1065353216	; 0x3f800000
70000322:	6838      	ldr	r0, [r7, #0]
70000324:	f002 f8b0 	bl	70002488 <__addsf3>
70000328:	4601      	mov	r1, r0
7000032a:	4650      	mov	r0, sl
7000032c:	f002 fa68 	bl	70002800 <__aeabi_fdiv>
70000330:	f002 fb8e 	bl	70002a50 <__aeabi_f2uiz>
70000334:	f640 03ba 	movw	r3, #2234	; 0x8ba
70000338:	429c      	cmp	r4, r3
7000033a:	bf28      	it	cs
7000033c:	461c      	movcs	r4, r3
7000033e:	42a0      	cmp	r0, r4
70000340:	bf28      	it	cs
70000342:	4620      	movcs	r0, r4
70000344:	f002 f950 	bl	700025e8 <__aeabi_ui2f>
70000348:	4649      	mov	r1, r9
7000034a:	f002 f9a5 	bl	70002698 <__aeabi_fmul>
7000034e:	4649      	mov	r1, r9
70000350:	f8c8 0004 	str.w	r0, [r8, #4]
70000354:	4648      	mov	r0, r9
70000356:	f002 f897 	bl	70002488 <__addsf3>
7000035a:	6070      	str	r0, [r6, #4]
7000035c:	6839      	ldr	r1, [r7, #0]
7000035e:	f8d8 0004 	ldr.w	r0, [r8, #4]
70000362:	f002 f999 	bl	70002698 <__aeabi_fmul>
70000366:	f8c8 0000 	str.w	r0, [r8]
7000036a:	6839      	ldr	r1, [r7, #0]
7000036c:	6870      	ldr	r0, [r6, #4]
7000036e:	f002 f993 	bl	70002698 <__aeabi_fmul>
70000372:	6030      	str	r0, [r6, #0]
70000374:	4628      	mov	r0, r5
70000376:	e7c6      	b.n	70000306 <imx775_get_exposure_range+0x42>
70000378:	f06f 0015 	mvn.w	r0, #21
7000037c:	e7c3      	b.n	70000306 <imx775_get_exposure_range+0x42>
7000037e:	bf00      	nop
70000380:	7000004c 	.word	0x7000004c
70000384:	00000000 	.word	0x00000000

70000388 <imx775_get_tuned_again>:
70000388:	b538      	push	{r3, r4, r5, lr}
7000038a:	460c      	mov	r4, r1
7000038c:	2800      	cmp	r0, #0
7000038e:	d158      	bne.n	70000442 <imx775_get_tuned_again+0xba>
70000390:	2900      	cmp	r1, #0
70000392:	d056      	beq.n	70000442 <imx775_get_tuned_again+0xba>
70000394:	680d      	ldr	r5, [r1, #0]
70000396:	4628      	mov	r0, r5
70000398:	f000 f8c6 	bl	70000528 <log10f>
7000039c:	492c      	ldr	r1, [pc, #176]	; (70000450 <imx775_get_tuned_again+0xc8>)
7000039e:	4628      	mov	r0, r5
700003a0:	f002 fb2c 	bl	700029fc <__aeabi_fcmpge>
700003a4:	2800      	cmp	r0, #0
700003a6:	d148      	bne.n	7000043a <imx775_get_tuned_again+0xb2>
700003a8:	4628      	mov	r0, r5
700003aa:	f000 f8bd 	bl	70000528 <log10f>
700003ae:	f001 fced 	bl	70001d8c <__aeabi_f2d>
700003b2:	a325      	add	r3, pc, #148	; (adr r3, 70000448 <imx775_get_tuned_again+0xc0>)
700003b4:	e9d3 2300 	ldrd	r2, r3, [r3]
700003b8:	f001 fd40 	bl	70001e3c <__aeabi_dmul>
700003bc:	f001 ffee 	bl	7000239c <__aeabi_d2uiz>
700003c0:	b280      	uxth	r0, r0
700003c2:	f001 fcc1 	bl	70001d48 <__aeabi_ui2d>
700003c6:	a320      	add	r3, pc, #128	; (adr r3, 70000448 <imx775_get_tuned_again+0xc0>)
700003c8:	e9d3 2300 	ldrd	r2, r3, [r3]
700003cc:	f001 fe60 	bl	70002090 <__aeabi_ddiv>
700003d0:	460b      	mov	r3, r1
700003d2:	4602      	mov	r2, r0
700003d4:	491f      	ldr	r1, [pc, #124]	; (70000454 <imx775_get_tuned_again+0xcc>)
700003d6:	2000      	movs	r0, #0
700003d8:	f000 f8ce 	bl	70000578 <pow>
700003dc:	f001 fffe 	bl	700023dc <__aeabi_d2f>
700003e0:	4b1d      	ldr	r3, [pc, #116]	; (70000458 <imx775_get_tuned_again+0xd0>)
700003e2:	6020      	str	r0, [r4, #0]
700003e4:	781b      	ldrb	r3, [r3, #0]
700003e6:	2b01      	cmp	r3, #1
700003e8:	d125      	bne.n	70000436 <imx775_get_tuned_again+0xae>
700003ea:	6865      	ldr	r5, [r4, #4]
700003ec:	4628      	mov	r0, r5
700003ee:	f000 f89b 	bl	70000528 <log10f>
700003f2:	4917      	ldr	r1, [pc, #92]	; (70000450 <imx775_get_tuned_again+0xc8>)
700003f4:	4628      	mov	r0, r5
700003f6:	f002 fb01 	bl	700029fc <__aeabi_fcmpge>
700003fa:	bb00      	cbnz	r0, 7000043e <imx775_get_tuned_again+0xb6>
700003fc:	4628      	mov	r0, r5
700003fe:	f000 f893 	bl	70000528 <log10f>
70000402:	f001 fcc3 	bl	70001d8c <__aeabi_f2d>
70000406:	a310      	add	r3, pc, #64	; (adr r3, 70000448 <imx775_get_tuned_again+0xc0>)
70000408:	e9d3 2300 	ldrd	r2, r3, [r3]
7000040c:	f001 fd16 	bl	70001e3c <__aeabi_dmul>
70000410:	f001 ffc4 	bl	7000239c <__aeabi_d2uiz>
70000414:	b280      	uxth	r0, r0
70000416:	f001 fc97 	bl	70001d48 <__aeabi_ui2d>
7000041a:	a30b      	add	r3, pc, #44	; (adr r3, 70000448 <imx775_get_tuned_again+0xc0>)
7000041c:	e9d3 2300 	ldrd	r2, r3, [r3]
70000420:	f001 fe36 	bl	70002090 <__aeabi_ddiv>
70000424:	4602      	mov	r2, r0
70000426:	460b      	mov	r3, r1
70000428:	2000      	movs	r0, #0
7000042a:	490a      	ldr	r1, [pc, #40]	; (70000454 <imx775_get_tuned_again+0xcc>)
7000042c:	f000 f8a4 	bl	70000578 <pow>
70000430:	f001 ffd4 	bl	700023dc <__aeabi_d2f>
70000434:	6060      	str	r0, [r4, #4]
70000436:	2000      	movs	r0, #0
70000438:	e005      	b.n	70000446 <imx775_get_tuned_again+0xbe>
7000043a:	2064      	movs	r0, #100	; 0x64
7000043c:	e7c1      	b.n	700003c2 <imx775_get_tuned_again+0x3a>
7000043e:	2064      	movs	r0, #100	; 0x64
70000440:	e7e9      	b.n	70000416 <imx775_get_tuned_again+0x8e>
70000442:	f06f 0015 	mvn.w	r0, #21
70000446:	bd38      	pop	{r3, r4, r5, pc}
70000448:	930be0df 	.word	0x930be0df
7000044c:	4050aaa9 	.word	0x4050aaa9
70000450:	41fcfb4a 	.word	0x41fcfb4a
70000454:	40240000 	.word	0x40240000
70000458:	7000004c 	.word	0x7000004c

7000045c <clip_d_word>:
7000045c:	4603      	mov	r3, r0
7000045e:	4610      	mov	r0, r2
70000460:	4293      	cmp	r3, r2
70000462:	d803      	bhi.n	7000046c <clip_d_word+0x10>
70000464:	428b      	cmp	r3, r1
70000466:	bf38      	it	cc
70000468:	460b      	movcc	r3, r1
7000046a:	4618      	mov	r0, r3
7000046c:	4770      	bx	lr
	...

70000470 <rts_isp_get_sensor_ops>:
70000470:	4800      	ldr	r0, [pc, #0]	; (70000474 <rts_isp_get_sensor_ops+0x4>)
70000472:	4770      	bx	lr
70000474:	70000494 	.word	0x70000494
70000478:	786d6920 	.word	0x786d6920
7000047c:	5f353737 	.word	0x5f353737
70000480:	69676572 	.word	0x69676572
70000484:	72657473 	.word	0x72657473
70000488:	6469203a 	.word	0x6469203a
7000048c:	0a64253d 	.word	0x0a64253d
70000490:	00000000 	.word	0x00000000

70000494 <imx775_ops>:
70000494:	73000005 37786d69 00003537 00000000     ...simx775......
	...
700004b8:	70000079 70000245 700002c5 70000389     y..pE..p...p...p
700004c8:	70000155 70000175 00000000 00000000     U..pu..p........
700004d8:	70000141 00000000 00000000 00000000     A..p............
700004e8:	70000179 00000000 00000000 00000000     y..p............
700004f8:	700001c9 00000000 00000000 00000000     ...p............
	...

70000528 <log10f>:
70000528:	b538      	push	{r3, r4, r5, lr}
7000052a:	4604      	mov	r4, r0
7000052c:	f000 f88c 	bl	70000648 <__ieee754_log10f>
70000530:	4605      	mov	r5, r0
70000532:	4621      	mov	r1, r4
70000534:	4620      	mov	r0, r4
70000536:	f002 fa75 	bl	70002a24 <__aeabi_fcmpun>
7000053a:	b970      	cbnz	r0, 7000055a <log10f+0x32>
7000053c:	2100      	movs	r1, #0
7000053e:	4620      	mov	r0, r4
70000540:	f002 fa52 	bl	700029e8 <__aeabi_fcmple>
70000544:	b148      	cbz	r0, 7000055a <log10f+0x32>
70000546:	2100      	movs	r1, #0
70000548:	4620      	mov	r0, r4
7000054a:	f002 fa39 	bl	700029c0 <__aeabi_fcmpeq>
7000054e:	b130      	cbz	r0, 7000055e <log10f+0x36>
70000550:	f001 f8d4 	bl	700016fc <__errno>
70000554:	4d06      	ldr	r5, [pc, #24]	; (70000570 <log10f+0x48>)
70000556:	2322      	movs	r3, #34	; 0x22
70000558:	6003      	str	r3, [r0, #0]
7000055a:	4628      	mov	r0, r5
7000055c:	bd38      	pop	{r3, r4, r5, pc}
7000055e:	f001 f8cd 	bl	700016fc <__errno>
70000562:	2321      	movs	r3, #33	; 0x21
70000564:	6003      	str	r3, [r0, #0]
70000566:	4803      	ldr	r0, [pc, #12]	; (70000574 <log10f+0x4c>)
70000568:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
7000056c:	f001 b844 	b.w	700015f8 <nanf>
70000570:	ff800000 	.word	0xff800000
70000574:	70002ef8 	.word	0x70002ef8

70000578 <pow>:
70000578:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
7000057c:	4614      	mov	r4, r2
7000057e:	461d      	mov	r5, r3
70000580:	4680      	mov	r8, r0
70000582:	4689      	mov	r9, r1
70000584:	f000 f9d8 	bl	70000938 <__ieee754_pow>
70000588:	4622      	mov	r2, r4
7000058a:	4606      	mov	r6, r0
7000058c:	460f      	mov	r7, r1
7000058e:	462b      	mov	r3, r5
70000590:	4620      	mov	r0, r4
70000592:	4629      	mov	r1, r5
70000594:	f001 feec 	bl	70002370 <__aeabi_dcmpun>
70000598:	bbc8      	cbnz	r0, 7000060e <pow+0x96>
7000059a:	2200      	movs	r2, #0
7000059c:	2300      	movs	r3, #0
7000059e:	4640      	mov	r0, r8
700005a0:	4649      	mov	r1, r9
700005a2:	f001 feb3 	bl	7000230c <__aeabi_dcmpeq>
700005a6:	b1b8      	cbz	r0, 700005d8 <pow+0x60>
700005a8:	2200      	movs	r2, #0
700005aa:	2300      	movs	r3, #0
700005ac:	4620      	mov	r0, r4
700005ae:	4629      	mov	r1, r5
700005b0:	f001 feac 	bl	7000230c <__aeabi_dcmpeq>
700005b4:	2800      	cmp	r0, #0
700005b6:	d141      	bne.n	7000063c <pow+0xc4>
700005b8:	4620      	mov	r0, r4
700005ba:	4629      	mov	r1, r5
700005bc:	f001 f815 	bl	700015ea <finite>
700005c0:	b328      	cbz	r0, 7000060e <pow+0x96>
700005c2:	2200      	movs	r2, #0
700005c4:	2300      	movs	r3, #0
700005c6:	4620      	mov	r0, r4
700005c8:	4629      	mov	r1, r5
700005ca:	f001 fea9 	bl	70002320 <__aeabi_dcmplt>
700005ce:	b1f0      	cbz	r0, 7000060e <pow+0x96>
700005d0:	f001 f894 	bl	700016fc <__errno>
700005d4:	2322      	movs	r3, #34	; 0x22
700005d6:	e019      	b.n	7000060c <pow+0x94>
700005d8:	4630      	mov	r0, r6
700005da:	4639      	mov	r1, r7
700005dc:	f001 f805 	bl	700015ea <finite>
700005e0:	b9c8      	cbnz	r0, 70000616 <pow+0x9e>
700005e2:	4640      	mov	r0, r8
700005e4:	4649      	mov	r1, r9
700005e6:	f001 f800 	bl	700015ea <finite>
700005ea:	b1a0      	cbz	r0, 70000616 <pow+0x9e>
700005ec:	4620      	mov	r0, r4
700005ee:	4629      	mov	r1, r5
700005f0:	f000 fffb 	bl	700015ea <finite>
700005f4:	b178      	cbz	r0, 70000616 <pow+0x9e>
700005f6:	4632      	mov	r2, r6
700005f8:	463b      	mov	r3, r7
700005fa:	4630      	mov	r0, r6
700005fc:	4639      	mov	r1, r7
700005fe:	f001 feb7 	bl	70002370 <__aeabi_dcmpun>
70000602:	2800      	cmp	r0, #0
70000604:	d0e4      	beq.n	700005d0 <pow+0x58>
70000606:	f001 f879 	bl	700016fc <__errno>
7000060a:	2321      	movs	r3, #33	; 0x21
7000060c:	6003      	str	r3, [r0, #0]
7000060e:	4630      	mov	r0, r6
70000610:	4639      	mov	r1, r7
70000612:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
70000616:	2200      	movs	r2, #0
70000618:	2300      	movs	r3, #0
7000061a:	4630      	mov	r0, r6
7000061c:	4639      	mov	r1, r7
7000061e:	f001 fe75 	bl	7000230c <__aeabi_dcmpeq>
70000622:	2800      	cmp	r0, #0
70000624:	d0f3      	beq.n	7000060e <pow+0x96>
70000626:	4640      	mov	r0, r8
70000628:	4649      	mov	r1, r9
7000062a:	f000 ffde 	bl	700015ea <finite>
7000062e:	2800      	cmp	r0, #0
70000630:	d0ed      	beq.n	7000060e <pow+0x96>
70000632:	4620      	mov	r0, r4
70000634:	4629      	mov	r1, r5
70000636:	f000 ffd8 	bl	700015ea <finite>
7000063a:	e7c8      	b.n	700005ce <pow+0x56>
7000063c:	2600      	movs	r6, #0
7000063e:	4f01      	ldr	r7, [pc, #4]	; (70000644 <pow+0xcc>)
70000640:	e7e5      	b.n	7000060e <pow+0x96>
70000642:	bf00      	nop
70000644:	3ff00000 	.word	0x3ff00000

70000648 <__ieee754_log10f>:
70000648:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
7000064c:	4601      	mov	r1, r0
7000064e:	4603      	mov	r3, r0
70000650:	b570      	push	{r4, r5, r6, lr}
70000652:	d105      	bne.n	70000660 <__ieee754_log10f+0x18>
70000654:	2100      	movs	r1, #0
70000656:	f04f 404c 	mov.w	r0, #3422552064	; 0xcc000000
7000065a:	f002 f8d1 	bl	70002800 <__aeabi_fdiv>
7000065e:	bd70      	pop	{r4, r5, r6, pc}
70000660:	2800      	cmp	r0, #0
70000662:	da03      	bge.n	7000066c <__ieee754_log10f+0x24>
70000664:	f001 ff0e 	bl	70002484 <__aeabi_fsub>
70000668:	2100      	movs	r1, #0
7000066a:	e7f6      	b.n	7000065a <__ieee754_log10f+0x12>
7000066c:	f1b0 4fff 	cmp.w	r0, #2139095040	; 0x7f800000
70000670:	db02      	blt.n	70000678 <__ieee754_log10f+0x30>
70000672:	f001 ff09 	bl	70002488 <__addsf3>
70000676:	e7f2      	b.n	7000065e <__ieee754_log10f+0x16>
70000678:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
7000067c:	da2d      	bge.n	700006da <__ieee754_log10f+0x92>
7000067e:	f04f 4198 	mov.w	r1, #1275068416	; 0x4c000000
70000682:	f002 f809 	bl	70002698 <__aeabi_fmul>
70000686:	f06f 0218 	mvn.w	r2, #24
7000068a:	4603      	mov	r3, r0
7000068c:	15d8      	asrs	r0, r3, #23
7000068e:	f3c3 0416 	ubfx	r4, r3, #0, #23
70000692:	387f      	subs	r0, #127	; 0x7f
70000694:	4410      	add	r0, r2
70000696:	0fc6      	lsrs	r6, r0, #31
70000698:	eb00 70d0 	add.w	r0, r0, r0, lsr #31
7000069c:	f001 ffa8 	bl	700025f0 <__aeabi_i2f>
700006a0:	4605      	mov	r5, r0
700006a2:	f1c6 007f 	rsb	r0, r6, #127	; 0x7f
700006a6:	ea44 50c0 	orr.w	r0, r4, r0, lsl #23
700006aa:	f000 f81f 	bl	700006ec <__ieee754_logf>
700006ae:	490c      	ldr	r1, [pc, #48]	; (700006e0 <__ieee754_log10f+0x98>)
700006b0:	4606      	mov	r6, r0
700006b2:	4628      	mov	r0, r5
700006b4:	f001 fff0 	bl	70002698 <__aeabi_fmul>
700006b8:	4604      	mov	r4, r0
700006ba:	490a      	ldr	r1, [pc, #40]	; (700006e4 <__ieee754_log10f+0x9c>)
700006bc:	4630      	mov	r0, r6
700006be:	f001 ffeb 	bl	70002698 <__aeabi_fmul>
700006c2:	4601      	mov	r1, r0
700006c4:	4620      	mov	r0, r4
700006c6:	f001 fedf 	bl	70002488 <__addsf3>
700006ca:	4604      	mov	r4, r0
700006cc:	4906      	ldr	r1, [pc, #24]	; (700006e8 <__ieee754_log10f+0xa0>)
700006ce:	4628      	mov	r0, r5
700006d0:	f001 ffe2 	bl	70002698 <__aeabi_fmul>
700006d4:	4601      	mov	r1, r0
700006d6:	4620      	mov	r0, r4
700006d8:	e7cb      	b.n	70000672 <__ieee754_log10f+0x2a>
700006da:	2200      	movs	r2, #0
700006dc:	e7d6      	b.n	7000068c <__ieee754_log10f+0x44>
700006de:	bf00      	nop
700006e0:	355427db 	.word	0x355427db
700006e4:	3ede5bd9 	.word	0x3ede5bd9
700006e8:	3e9a2080 	.word	0x3e9a2080

700006ec <__ieee754_logf>:
700006ec:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
700006f0:	4601      	mov	r1, r0
700006f2:	e92d 4ff8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr}
700006f6:	4603      	mov	r3, r0
700006f8:	d106      	bne.n	70000708 <__ieee754_logf+0x1c>
700006fa:	2100      	movs	r1, #0
700006fc:	f04f 404c 	mov.w	r0, #3422552064	; 0xcc000000
70000700:	f002 f87e 	bl	70002800 <__aeabi_fdiv>
70000704:	e8bd 8ff8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc}
70000708:	2800      	cmp	r0, #0
7000070a:	da03      	bge.n	70000714 <__ieee754_logf+0x28>
7000070c:	f001 feba 	bl	70002484 <__aeabi_fsub>
70000710:	2100      	movs	r1, #0
70000712:	e7f5      	b.n	70000700 <__ieee754_logf+0x14>
70000714:	f1b0 4fff 	cmp.w	r0, #2139095040	; 0x7f800000
70000718:	db02      	blt.n	70000720 <__ieee754_logf+0x34>
7000071a:	f001 feb5 	bl	70002488 <__addsf3>
7000071e:	e7f1      	b.n	70000704 <__ieee754_logf+0x18>
70000720:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70000724:	da35      	bge.n	70000792 <__ieee754_logf+0xa6>
70000726:	f04f 4198 	mov.w	r1, #1275068416	; 0x4c000000
7000072a:	f001 ffb5 	bl	70002698 <__aeabi_fmul>
7000072e:	f06f 0218 	mvn.w	r2, #24
70000732:	4603      	mov	r3, r0
70000734:	f3c3 0416 	ubfx	r4, r3, #0, #23
70000738:	15de      	asrs	r6, r3, #23
7000073a:	4b71      	ldr	r3, [pc, #452]	; (70000900 <__ieee754_logf+0x214>)
7000073c:	f04f 517e 	mov.w	r1, #1065353216	; 0x3f800000
70000740:	3e7f      	subs	r6, #127	; 0x7f
70000742:	4423      	add	r3, r4
70000744:	4416      	add	r6, r2
70000746:	f403 0000 	and.w	r0, r3, #8388608	; 0x800000
7000074a:	eb06 56d3 	add.w	r6, r6, r3, lsr #23
7000074e:	f080 507e 	eor.w	r0, r0, #1065353216	; 0x3f800000
70000752:	4320      	orrs	r0, r4
70000754:	f001 fe96 	bl	70002484 <__aeabi_fsub>
70000758:	f104 020f 	add.w	r2, r4, #15
7000075c:	4b69      	ldr	r3, [pc, #420]	; (70000904 <__ieee754_logf+0x218>)
7000075e:	4605      	mov	r5, r0
70000760:	4013      	ands	r3, r2
70000762:	2b00      	cmp	r3, #0
70000764:	d13a      	bne.n	700007dc <__ieee754_logf+0xf0>
70000766:	2100      	movs	r1, #0
70000768:	f002 f92a 	bl	700029c0 <__aeabi_fcmpeq>
7000076c:	b198      	cbz	r0, 70000796 <__ieee754_logf+0xaa>
7000076e:	2e00      	cmp	r6, #0
70000770:	f000 80c4 	beq.w	700008fc <__ieee754_logf+0x210>
70000774:	4630      	mov	r0, r6
70000776:	f001 ff3b 	bl	700025f0 <__aeabi_i2f>
7000077a:	4963      	ldr	r1, [pc, #396]	; (70000908 <__ieee754_logf+0x21c>)
7000077c:	4605      	mov	r5, r0
7000077e:	f001 ff8b 	bl	70002698 <__aeabi_fmul>
70000782:	4604      	mov	r4, r0
70000784:	4961      	ldr	r1, [pc, #388]	; (7000090c <__ieee754_logf+0x220>)
70000786:	4628      	mov	r0, r5
70000788:	f001 ff86 	bl	70002698 <__aeabi_fmul>
7000078c:	4601      	mov	r1, r0
7000078e:	4620      	mov	r0, r4
70000790:	e7c3      	b.n	7000071a <__ieee754_logf+0x2e>
70000792:	2200      	movs	r2, #0
70000794:	e7ce      	b.n	70000734 <__ieee754_logf+0x48>
70000796:	495e      	ldr	r1, [pc, #376]	; (70000910 <__ieee754_logf+0x224>)
70000798:	4628      	mov	r0, r5
7000079a:	f001 ff7d 	bl	70002698 <__aeabi_fmul>
7000079e:	4601      	mov	r1, r0
700007a0:	f04f 507c 	mov.w	r0, #1056964608	; 0x3f000000
700007a4:	f001 fe6e 	bl	70002484 <__aeabi_fsub>
700007a8:	4604      	mov	r4, r0
700007aa:	4629      	mov	r1, r5
700007ac:	4628      	mov	r0, r5
700007ae:	f001 ff73 	bl	70002698 <__aeabi_fmul>
700007b2:	4601      	mov	r1, r0
700007b4:	4620      	mov	r0, r4
700007b6:	f001 ff6f 	bl	70002698 <__aeabi_fmul>
700007ba:	4604      	mov	r4, r0
700007bc:	b90e      	cbnz	r6, 700007c2 <__ieee754_logf+0xd6>
700007be:	4621      	mov	r1, r4
700007c0:	e06f      	b.n	700008a2 <__ieee754_logf+0x1b6>
700007c2:	4630      	mov	r0, r6
700007c4:	f001 ff14 	bl	700025f0 <__aeabi_i2f>
700007c8:	4607      	mov	r7, r0
700007ca:	494f      	ldr	r1, [pc, #316]	; (70000908 <__ieee754_logf+0x21c>)
700007cc:	f001 ff64 	bl	70002698 <__aeabi_fmul>
700007d0:	494e      	ldr	r1, [pc, #312]	; (7000090c <__ieee754_logf+0x220>)
700007d2:	4606      	mov	r6, r0
700007d4:	4638      	mov	r0, r7
700007d6:	f001 ff5f 	bl	70002698 <__aeabi_fmul>
700007da:	e072      	b.n	700008c2 <__ieee754_logf+0x1d6>
700007dc:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
700007e0:	f8df a130 	ldr.w	sl, [pc, #304]	; 70000914 <__ieee754_logf+0x228>
700007e4:	f001 fe50 	bl	70002488 <__addsf3>
700007e8:	4601      	mov	r1, r0
700007ea:	4628      	mov	r0, r5
700007ec:	44a2      	add	sl, r4
700007ee:	f002 f807 	bl	70002800 <__aeabi_fdiv>
700007f2:	4681      	mov	r9, r0
700007f4:	4630      	mov	r0, r6
700007f6:	f001 fefb 	bl	700025f0 <__aeabi_i2f>
700007fa:	4649      	mov	r1, r9
700007fc:	4680      	mov	r8, r0
700007fe:	4648      	mov	r0, r9
70000800:	f001 ff4a 	bl	70002698 <__aeabi_fmul>
70000804:	4601      	mov	r1, r0
70000806:	4683      	mov	fp, r0
70000808:	f001 ff46 	bl	70002698 <__aeabi_fmul>
7000080c:	4942      	ldr	r1, [pc, #264]	; (70000918 <__ieee754_logf+0x22c>)
7000080e:	4607      	mov	r7, r0
70000810:	f001 ff42 	bl	70002698 <__aeabi_fmul>
70000814:	4941      	ldr	r1, [pc, #260]	; (7000091c <__ieee754_logf+0x230>)
70000816:	f001 fe37 	bl	70002488 <__addsf3>
7000081a:	4639      	mov	r1, r7
7000081c:	f001 ff3c 	bl	70002698 <__aeabi_fmul>
70000820:	493f      	ldr	r1, [pc, #252]	; (70000920 <__ieee754_logf+0x234>)
70000822:	f001 fe31 	bl	70002488 <__addsf3>
70000826:	4639      	mov	r1, r7
70000828:	f001 ff36 	bl	70002698 <__aeabi_fmul>
7000082c:	493d      	ldr	r1, [pc, #244]	; (70000924 <__ieee754_logf+0x238>)
7000082e:	f001 fe2b 	bl	70002488 <__addsf3>
70000832:	4659      	mov	r1, fp
70000834:	f001 ff30 	bl	70002698 <__aeabi_fmul>
70000838:	493b      	ldr	r1, [pc, #236]	; (70000928 <__ieee754_logf+0x23c>)
7000083a:	4683      	mov	fp, r0
7000083c:	4638      	mov	r0, r7
7000083e:	f001 ff2b 	bl	70002698 <__aeabi_fmul>
70000842:	493a      	ldr	r1, [pc, #232]	; (7000092c <__ieee754_logf+0x240>)
70000844:	f001 fe20 	bl	70002488 <__addsf3>
70000848:	4639      	mov	r1, r7
7000084a:	f001 ff25 	bl	70002698 <__aeabi_fmul>
7000084e:	4938      	ldr	r1, [pc, #224]	; (70000930 <__ieee754_logf+0x244>)
70000850:	f001 fe1a 	bl	70002488 <__addsf3>
70000854:	4639      	mov	r1, r7
70000856:	f001 ff1f 	bl	70002698 <__aeabi_fmul>
7000085a:	4601      	mov	r1, r0
7000085c:	4658      	mov	r0, fp
7000085e:	f001 fe13 	bl	70002488 <__addsf3>
70000862:	f5c4 1357 	rsb	r3, r4, #3522560	; 0x35c000
70000866:	4607      	mov	r7, r0
70000868:	f503 7322 	add.w	r3, r3, #648	; 0x288
7000086c:	ea43 030a 	orr.w	r3, r3, sl
70000870:	2b00      	cmp	r3, #0
70000872:	dd30      	ble.n	700008d6 <__ieee754_logf+0x1ea>
70000874:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
70000878:	4628      	mov	r0, r5
7000087a:	f001 ff0d 	bl	70002698 <__aeabi_fmul>
7000087e:	4629      	mov	r1, r5
70000880:	f001 ff0a 	bl	70002698 <__aeabi_fmul>
70000884:	4601      	mov	r1, r0
70000886:	4604      	mov	r4, r0
70000888:	4638      	mov	r0, r7
7000088a:	f001 fdfd 	bl	70002488 <__addsf3>
7000088e:	4649      	mov	r1, r9
70000890:	f001 ff02 	bl	70002698 <__aeabi_fmul>
70000894:	4607      	mov	r7, r0
70000896:	b946      	cbnz	r6, 700008aa <__ieee754_logf+0x1be>
70000898:	4601      	mov	r1, r0
7000089a:	4620      	mov	r0, r4
7000089c:	f001 fdf2 	bl	70002484 <__aeabi_fsub>
700008a0:	4601      	mov	r1, r0
700008a2:	4628      	mov	r0, r5
700008a4:	f001 fdee 	bl	70002484 <__aeabi_fsub>
700008a8:	e72c      	b.n	70000704 <__ieee754_logf+0x18>
700008aa:	4917      	ldr	r1, [pc, #92]	; (70000908 <__ieee754_logf+0x21c>)
700008ac:	4640      	mov	r0, r8
700008ae:	f001 fef3 	bl	70002698 <__aeabi_fmul>
700008b2:	4916      	ldr	r1, [pc, #88]	; (7000090c <__ieee754_logf+0x220>)
700008b4:	4606      	mov	r6, r0
700008b6:	4640      	mov	r0, r8
700008b8:	f001 feee 	bl	70002698 <__aeabi_fmul>
700008bc:	4639      	mov	r1, r7
700008be:	f001 fde3 	bl	70002488 <__addsf3>
700008c2:	4601      	mov	r1, r0
700008c4:	4620      	mov	r0, r4
700008c6:	f001 fddd 	bl	70002484 <__aeabi_fsub>
700008ca:	4629      	mov	r1, r5
700008cc:	f001 fdda 	bl	70002484 <__aeabi_fsub>
700008d0:	4601      	mov	r1, r0
700008d2:	4630      	mov	r0, r6
700008d4:	e7e6      	b.n	700008a4 <__ieee754_logf+0x1b8>
700008d6:	4601      	mov	r1, r0
700008d8:	4628      	mov	r0, r5
700008da:	f001 fdd3 	bl	70002484 <__aeabi_fsub>
700008de:	4649      	mov	r1, r9
700008e0:	f001 feda 	bl	70002698 <__aeabi_fmul>
700008e4:	4604      	mov	r4, r0
700008e6:	2e00      	cmp	r6, #0
700008e8:	f43f af69 	beq.w	700007be <__ieee754_logf+0xd2>
700008ec:	4906      	ldr	r1, [pc, #24]	; (70000908 <__ieee754_logf+0x21c>)
700008ee:	4640      	mov	r0, r8
700008f0:	f001 fed2 	bl	70002698 <__aeabi_fmul>
700008f4:	4905      	ldr	r1, [pc, #20]	; (7000090c <__ieee754_logf+0x220>)
700008f6:	4606      	mov	r6, r0
700008f8:	4640      	mov	r0, r8
700008fa:	e76c      	b.n	700007d6 <__ieee754_logf+0xea>
700008fc:	2000      	movs	r0, #0
700008fe:	e701      	b.n	70000704 <__ieee754_logf+0x18>
70000900:	004afb20 	.word	0x004afb20
70000904:	007ffff0 	.word	0x007ffff0
70000908:	3f317180 	.word	0x3f317180
7000090c:	3717f7d1 	.word	0x3717f7d1
70000910:	3eaaaaab 	.word	0x3eaaaaab
70000914:	ffcf5c30 	.word	0xffcf5c30
70000918:	3e178897 	.word	0x3e178897
7000091c:	3e3a3325 	.word	0x3e3a3325
70000920:	3e924925 	.word	0x3e924925
70000924:	3f2aaaab 	.word	0x3f2aaaab
70000928:	3e1cd04f 	.word	0x3e1cd04f
7000092c:	3e638e29 	.word	0x3e638e29
70000930:	3ecccccd 	.word	0x3ecccccd
70000934:	00000000 	.word	0x00000000

70000938 <__ieee754_pow>:
70000938:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
7000093c:	b093      	sub	sp, #76	; 0x4c
7000093e:	4689      	mov	r9, r1
70000940:	4680      	mov	r8, r0
70000942:	e9cd 2302 	strd	r2, r3, [sp, #8]
70000946:	e9dd 2702 	ldrd	r2, r7, [sp, #8]
7000094a:	f027 4600 	bic.w	r6, r7, #2147483648	; 0x80000000
7000094e:	ea56 0102 	orrs.w	r1, r6, r2
70000952:	d111      	bne.n	70000978 <__ieee754_pow+0x40>
70000954:	1803      	adds	r3, r0, r0
70000956:	f489 2200 	eor.w	r2, r9, #524288	; 0x80000
7000095a:	4152      	adcs	r2, r2
7000095c:	4299      	cmp	r1, r3
7000095e:	4b82      	ldr	r3, [pc, #520]	; (70000b68 <__ieee754_pow+0x230>)
70000960:	4193      	sbcs	r3, r2
70000962:	f080 84b3 	bcs.w	700012cc <__ieee754_pow+0x994>
70000966:	4640      	mov	r0, r8
70000968:	4649      	mov	r1, r9
7000096a:	e9dd 2302 	ldrd	r2, r3, [sp, #8]
7000096e:	f001 f8af 	bl	70001ad0 <__adddf3>
70000972:	4683      	mov	fp, r0
70000974:	468c      	mov	ip, r1
70000976:	e06f      	b.n	70000a58 <__ieee754_pow+0x120>
70000978:	f029 4400 	bic.w	r4, r9, #2147483648	; 0x80000000
7000097c:	4b7b      	ldr	r3, [pc, #492]	; (70000b6c <__ieee754_pow+0x234>)
7000097e:	464d      	mov	r5, r9
70000980:	4682      	mov	sl, r0
70000982:	429c      	cmp	r4, r3
70000984:	dc06      	bgt.n	70000994 <__ieee754_pow+0x5c>
70000986:	d101      	bne.n	7000098c <__ieee754_pow+0x54>
70000988:	2800      	cmp	r0, #0
7000098a:	d1ec      	bne.n	70000966 <__ieee754_pow+0x2e>
7000098c:	429e      	cmp	r6, r3
7000098e:	dc01      	bgt.n	70000994 <__ieee754_pow+0x5c>
70000990:	d10f      	bne.n	700009b2 <__ieee754_pow+0x7a>
70000992:	b172      	cbz	r2, 700009b2 <__ieee754_pow+0x7a>
70000994:	f105 4540 	add.w	r5, r5, #3221225472	; 0xc0000000
70000998:	f505 1580 	add.w	r5, r5, #1048576	; 0x100000
7000099c:	ea55 050a 	orrs.w	r5, r5, sl
700009a0:	d1e1      	bne.n	70000966 <__ieee754_pow+0x2e>
700009a2:	e9dd 3202 	ldrd	r3, r2, [sp, #8]
700009a6:	18db      	adds	r3, r3, r3
700009a8:	f482 2200 	eor.w	r2, r2, #524288	; 0x80000
700009ac:	4152      	adcs	r2, r2
700009ae:	429d      	cmp	r5, r3
700009b0:	e7d5      	b.n	7000095e <__ieee754_pow+0x26>
700009b2:	2d00      	cmp	r5, #0
700009b4:	da39      	bge.n	70000a2a <__ieee754_pow+0xf2>
700009b6:	4b6e      	ldr	r3, [pc, #440]	; (70000b70 <__ieee754_pow+0x238>)
700009b8:	429e      	cmp	r6, r3
700009ba:	dc52      	bgt.n	70000a62 <__ieee754_pow+0x12a>
700009bc:	f1a3 7354 	sub.w	r3, r3, #55574528	; 0x3500000
700009c0:	429e      	cmp	r6, r3
700009c2:	f340 8496 	ble.w	700012f2 <__ieee754_pow+0x9ba>
700009c6:	1533      	asrs	r3, r6, #20
700009c8:	f2a3 33ff 	subw	r3, r3, #1023	; 0x3ff
700009cc:	2b14      	cmp	r3, #20
700009ce:	dd0f      	ble.n	700009f0 <__ieee754_pow+0xb8>
700009d0:	f1c3 0334 	rsb	r3, r3, #52	; 0x34
700009d4:	fa22 f103 	lsr.w	r1, r2, r3
700009d8:	fa01 f303 	lsl.w	r3, r1, r3
700009dc:	4293      	cmp	r3, r2
700009de:	f040 8488 	bne.w	700012f2 <__ieee754_pow+0x9ba>
700009e2:	f001 0101 	and.w	r1, r1, #1
700009e6:	f1c1 0302 	rsb	r3, r1, #2
700009ea:	9300      	str	r3, [sp, #0]
700009ec:	b182      	cbz	r2, 70000a10 <__ieee754_pow+0xd8>
700009ee:	e05d      	b.n	70000aac <__ieee754_pow+0x174>
700009f0:	2a00      	cmp	r2, #0
700009f2:	d159      	bne.n	70000aa8 <__ieee754_pow+0x170>
700009f4:	f1c3 0314 	rsb	r3, r3, #20
700009f8:	fa46 f103 	asr.w	r1, r6, r3
700009fc:	fa01 f303 	lsl.w	r3, r1, r3
70000a00:	42b3      	cmp	r3, r6
70000a02:	f040 8473 	bne.w	700012ec <__ieee754_pow+0x9b4>
70000a06:	f001 0101 	and.w	r1, r1, #1
70000a0a:	f1c1 0302 	rsb	r3, r1, #2
70000a0e:	9300      	str	r3, [sp, #0]
70000a10:	4b58      	ldr	r3, [pc, #352]	; (70000b74 <__ieee754_pow+0x23c>)
70000a12:	429e      	cmp	r6, r3
70000a14:	d132      	bne.n	70000a7c <__ieee754_pow+0x144>
70000a16:	2f00      	cmp	r7, #0
70000a18:	f280 8464 	bge.w	700012e4 <__ieee754_pow+0x9ac>
70000a1c:	4642      	mov	r2, r8
70000a1e:	464b      	mov	r3, r9
70000a20:	2000      	movs	r0, #0
70000a22:	4954      	ldr	r1, [pc, #336]	; (70000b74 <__ieee754_pow+0x23c>)
70000a24:	f001 fb34 	bl	70002090 <__aeabi_ddiv>
70000a28:	e7a3      	b.n	70000972 <__ieee754_pow+0x3a>
70000a2a:	2300      	movs	r3, #0
70000a2c:	9300      	str	r3, [sp, #0]
70000a2e:	2a00      	cmp	r2, #0
70000a30:	d13c      	bne.n	70000aac <__ieee754_pow+0x174>
70000a32:	4b4e      	ldr	r3, [pc, #312]	; (70000b6c <__ieee754_pow+0x234>)
70000a34:	429e      	cmp	r6, r3
70000a36:	d1eb      	bne.n	70000a10 <__ieee754_pow+0xd8>
70000a38:	f104 4340 	add.w	r3, r4, #3221225472	; 0xc0000000
70000a3c:	f503 1380 	add.w	r3, r3, #1048576	; 0x100000
70000a40:	ea53 030a 	orrs.w	r3, r3, sl
70000a44:	f000 8442 	beq.w	700012cc <__ieee754_pow+0x994>
70000a48:	4b4b      	ldr	r3, [pc, #300]	; (70000b78 <__ieee754_pow+0x240>)
70000a4a:	429c      	cmp	r4, r3
70000a4c:	dd0b      	ble.n	70000a66 <__ieee754_pow+0x12e>
70000a4e:	2f00      	cmp	r7, #0
70000a50:	f2c0 8442 	blt.w	700012d8 <__ieee754_pow+0x9a0>
70000a54:	e9dd bc02 	ldrd	fp, ip, [sp, #8]
70000a58:	4658      	mov	r0, fp
70000a5a:	4661      	mov	r1, ip
70000a5c:	b013      	add	sp, #76	; 0x4c
70000a5e:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
70000a62:	2302      	movs	r3, #2
70000a64:	e7e2      	b.n	70000a2c <__ieee754_pow+0xf4>
70000a66:	2f00      	cmp	r7, #0
70000a68:	f04f 0b00 	mov.w	fp, #0
70000a6c:	f04f 0c00 	mov.w	ip, #0
70000a70:	daf2      	bge.n	70000a58 <__ieee754_pow+0x120>
70000a72:	e9dd b302 	ldrd	fp, r3, [sp, #8]
70000a76:	f103 4c00 	add.w	ip, r3, #2147483648	; 0x80000000
70000a7a:	e7ed      	b.n	70000a58 <__ieee754_pow+0x120>
70000a7c:	f1b7 4f80 	cmp.w	r7, #1073741824	; 0x40000000
70000a80:	d106      	bne.n	70000a90 <__ieee754_pow+0x158>
70000a82:	4642      	mov	r2, r8
70000a84:	464b      	mov	r3, r9
70000a86:	4640      	mov	r0, r8
70000a88:	4649      	mov	r1, r9
70000a8a:	f001 f9d7 	bl	70001e3c <__aeabi_dmul>
70000a8e:	e770      	b.n	70000972 <__ieee754_pow+0x3a>
70000a90:	4b3a      	ldr	r3, [pc, #232]	; (70000b7c <__ieee754_pow+0x244>)
70000a92:	429f      	cmp	r7, r3
70000a94:	d10a      	bne.n	70000aac <__ieee754_pow+0x174>
70000a96:	2d00      	cmp	r5, #0
70000a98:	db08      	blt.n	70000aac <__ieee754_pow+0x174>
70000a9a:	4640      	mov	r0, r8
70000a9c:	4649      	mov	r1, r9
70000a9e:	b013      	add	sp, #76	; 0x4c
70000aa0:	e8bd 4ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
70000aa4:	f000 bc56 	b.w	70001354 <__ieee754_sqrt>
70000aa8:	2300      	movs	r3, #0
70000aaa:	9300      	str	r3, [sp, #0]
70000aac:	4640      	mov	r0, r8
70000aae:	4649      	mov	r1, r9
70000ab0:	f000 fd98 	bl	700015e4 <fabs>
70000ab4:	4683      	mov	fp, r0
70000ab6:	468c      	mov	ip, r1
70000ab8:	f1ba 0f00 	cmp.w	sl, #0
70000abc:	d128      	bne.n	70000b10 <__ieee754_pow+0x1d8>
70000abe:	b124      	cbz	r4, 70000aca <__ieee754_pow+0x192>
70000ac0:	f025 4240 	bic.w	r2, r5, #3221225472	; 0xc0000000
70000ac4:	4b2b      	ldr	r3, [pc, #172]	; (70000b74 <__ieee754_pow+0x23c>)
70000ac6:	429a      	cmp	r2, r3
70000ac8:	d122      	bne.n	70000b10 <__ieee754_pow+0x1d8>
70000aca:	2f00      	cmp	r7, #0
70000acc:	da07      	bge.n	70000ade <__ieee754_pow+0x1a6>
70000ace:	465a      	mov	r2, fp
70000ad0:	4663      	mov	r3, ip
70000ad2:	2000      	movs	r0, #0
70000ad4:	4927      	ldr	r1, [pc, #156]	; (70000b74 <__ieee754_pow+0x23c>)
70000ad6:	f001 fadb 	bl	70002090 <__aeabi_ddiv>
70000ada:	4683      	mov	fp, r0
70000adc:	468c      	mov	ip, r1
70000ade:	2d00      	cmp	r5, #0
70000ae0:	daba      	bge.n	70000a58 <__ieee754_pow+0x120>
70000ae2:	f104 4440 	add.w	r4, r4, #3221225472	; 0xc0000000
70000ae6:	9b00      	ldr	r3, [sp, #0]
70000ae8:	f504 1480 	add.w	r4, r4, #1048576	; 0x100000
70000aec:	4323      	orrs	r3, r4
70000aee:	d108      	bne.n	70000b02 <__ieee754_pow+0x1ca>
70000af0:	465a      	mov	r2, fp
70000af2:	4663      	mov	r3, ip
70000af4:	4658      	mov	r0, fp
70000af6:	4661      	mov	r1, ip
70000af8:	f000 ffe8 	bl	70001acc <__aeabi_dsub>
70000afc:	4602      	mov	r2, r0
70000afe:	460b      	mov	r3, r1
70000b00:	e790      	b.n	70000a24 <__ieee754_pow+0xec>
70000b02:	9b00      	ldr	r3, [sp, #0]
70000b04:	2b01      	cmp	r3, #1
70000b06:	d1a7      	bne.n	70000a58 <__ieee754_pow+0x120>
70000b08:	f10c 4300 	add.w	r3, ip, #2147483648	; 0x80000000
70000b0c:	469c      	mov	ip, r3
70000b0e:	e7a3      	b.n	70000a58 <__ieee754_pow+0x120>
70000b10:	0feb      	lsrs	r3, r5, #31
70000b12:	3b01      	subs	r3, #1
70000b14:	930d      	str	r3, [sp, #52]	; 0x34
70000b16:	9a0d      	ldr	r2, [sp, #52]	; 0x34
70000b18:	9b00      	ldr	r3, [sp, #0]
70000b1a:	4313      	orrs	r3, r2
70000b1c:	d104      	bne.n	70000b28 <__ieee754_pow+0x1f0>
70000b1e:	4642      	mov	r2, r8
70000b20:	464b      	mov	r3, r9
70000b22:	4640      	mov	r0, r8
70000b24:	4649      	mov	r1, r9
70000b26:	e7e7      	b.n	70000af8 <__ieee754_pow+0x1c0>
70000b28:	4b15      	ldr	r3, [pc, #84]	; (70000b80 <__ieee754_pow+0x248>)
70000b2a:	429e      	cmp	r6, r3
70000b2c:	f340 80f6 	ble.w	70000d1c <__ieee754_pow+0x3e4>
70000b30:	f103 7304 	add.w	r3, r3, #34603008	; 0x2100000
70000b34:	429e      	cmp	r6, r3
70000b36:	4b10      	ldr	r3, [pc, #64]	; (70000b78 <__ieee754_pow+0x240>)
70000b38:	dd09      	ble.n	70000b4e <__ieee754_pow+0x216>
70000b3a:	429c      	cmp	r4, r3
70000b3c:	dc0c      	bgt.n	70000b58 <__ieee754_pow+0x220>
70000b3e:	2f00      	cmp	r7, #0
70000b40:	da0c      	bge.n	70000b5c <__ieee754_pow+0x224>
70000b42:	2000      	movs	r0, #0
70000b44:	b013      	add	sp, #76	; 0x4c
70000b46:	e8bd 4ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
70000b4a:	f000 bce1 	b.w	70001510 <__math_oflow>
70000b4e:	429c      	cmp	r4, r3
70000b50:	dbf5      	blt.n	70000b3e <__ieee754_pow+0x206>
70000b52:	4b08      	ldr	r3, [pc, #32]	; (70000b74 <__ieee754_pow+0x23c>)
70000b54:	429c      	cmp	r4, r3
70000b56:	dd15      	ble.n	70000b84 <__ieee754_pow+0x24c>
70000b58:	2f00      	cmp	r7, #0
70000b5a:	dcf2      	bgt.n	70000b42 <__ieee754_pow+0x20a>
70000b5c:	2000      	movs	r0, #0
70000b5e:	b013      	add	sp, #76	; 0x4c
70000b60:	e8bd 4ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
70000b64:	f000 bccb 	b.w	700014fe <__math_uflow>
70000b68:	fff00000 	.word	0xfff00000
70000b6c:	7ff00000 	.word	0x7ff00000
70000b70:	433fffff 	.word	0x433fffff
70000b74:	3ff00000 	.word	0x3ff00000
70000b78:	3fefffff 	.word	0x3fefffff
70000b7c:	3fe00000 	.word	0x3fe00000
70000b80:	41e00000 	.word	0x41e00000
70000b84:	4661      	mov	r1, ip
70000b86:	2200      	movs	r2, #0
70000b88:	4b5f      	ldr	r3, [pc, #380]	; (70000d08 <__ieee754_pow+0x3d0>)
70000b8a:	4658      	mov	r0, fp
70000b8c:	f000 ff9e 	bl	70001acc <__aeabi_dsub>
70000b90:	4604      	mov	r4, r0
70000b92:	460d      	mov	r5, r1
70000b94:	a354      	add	r3, pc, #336	; (adr r3, 70000ce8 <__ieee754_pow+0x3b0>)
70000b96:	e9d3 2300 	ldrd	r2, r3, [r3]
70000b9a:	f001 f94f 	bl	70001e3c <__aeabi_dmul>
70000b9e:	4606      	mov	r6, r0
70000ba0:	460f      	mov	r7, r1
70000ba2:	4620      	mov	r0, r4
70000ba4:	4629      	mov	r1, r5
70000ba6:	a352      	add	r3, pc, #328	; (adr r3, 70000cf0 <__ieee754_pow+0x3b8>)
70000ba8:	e9d3 2300 	ldrd	r2, r3, [r3]
70000bac:	f001 f946 	bl	70001e3c <__aeabi_dmul>
70000bb0:	2200      	movs	r2, #0
70000bb2:	4682      	mov	sl, r0
70000bb4:	468b      	mov	fp, r1
70000bb6:	4b55      	ldr	r3, [pc, #340]	; (70000d0c <__ieee754_pow+0x3d4>)
70000bb8:	4620      	mov	r0, r4
70000bba:	4629      	mov	r1, r5
70000bbc:	f001 f93e 	bl	70001e3c <__aeabi_dmul>
70000bc0:	4602      	mov	r2, r0
70000bc2:	460b      	mov	r3, r1
70000bc4:	a14c      	add	r1, pc, #304	; (adr r1, 70000cf8 <__ieee754_pow+0x3c0>)
70000bc6:	e9d1 0100 	ldrd	r0, r1, [r1]
70000bca:	f000 ff7f 	bl	70001acc <__aeabi_dsub>
70000bce:	4622      	mov	r2, r4
70000bd0:	462b      	mov	r3, r5
70000bd2:	f001 f933 	bl	70001e3c <__aeabi_dmul>
70000bd6:	4602      	mov	r2, r0
70000bd8:	460b      	mov	r3, r1
70000bda:	2000      	movs	r0, #0
70000bdc:	494c      	ldr	r1, [pc, #304]	; (70000d10 <__ieee754_pow+0x3d8>)
70000bde:	f000 ff75 	bl	70001acc <__aeabi_dsub>
70000be2:	4680      	mov	r8, r0
70000be4:	4689      	mov	r9, r1
70000be6:	4622      	mov	r2, r4
70000be8:	462b      	mov	r3, r5
70000bea:	4620      	mov	r0, r4
70000bec:	4629      	mov	r1, r5
70000bee:	f001 f925 	bl	70001e3c <__aeabi_dmul>
70000bf2:	4602      	mov	r2, r0
70000bf4:	460b      	mov	r3, r1
70000bf6:	4640      	mov	r0, r8
70000bf8:	4649      	mov	r1, r9
70000bfa:	f001 f91f 	bl	70001e3c <__aeabi_dmul>
70000bfe:	a340      	add	r3, pc, #256	; (adr r3, 70000d00 <__ieee754_pow+0x3c8>)
70000c00:	e9d3 2300 	ldrd	r2, r3, [r3]
70000c04:	f001 f91a 	bl	70001e3c <__aeabi_dmul>
70000c08:	4602      	mov	r2, r0
70000c0a:	460b      	mov	r3, r1
70000c0c:	4650      	mov	r0, sl
70000c0e:	4659      	mov	r1, fp
70000c10:	f04f 0a00 	mov.w	sl, #0
70000c14:	f000 ff5a 	bl	70001acc <__aeabi_dsub>
70000c18:	4602      	mov	r2, r0
70000c1a:	460b      	mov	r3, r1
70000c1c:	4604      	mov	r4, r0
70000c1e:	460d      	mov	r5, r1
70000c20:	4630      	mov	r0, r6
70000c22:	4639      	mov	r1, r7
70000c24:	f000 ff54 	bl	70001ad0 <__adddf3>
70000c28:	4632      	mov	r2, r6
70000c2a:	463b      	mov	r3, r7
70000c2c:	4650      	mov	r0, sl
70000c2e:	468b      	mov	fp, r1
70000c30:	f000 ff4c 	bl	70001acc <__aeabi_dsub>
70000c34:	4602      	mov	r2, r0
70000c36:	460b      	mov	r3, r1
70000c38:	4620      	mov	r0, r4
70000c3a:	4629      	mov	r1, r5
70000c3c:	f000 ff46 	bl	70001acc <__aeabi_dsub>
70000c40:	9b00      	ldr	r3, [sp, #0]
70000c42:	9a0d      	ldr	r2, [sp, #52]	; 0x34
70000c44:	4604      	mov	r4, r0
70000c46:	3b01      	subs	r3, #1
70000c48:	460d      	mov	r5, r1
70000c4a:	4313      	orrs	r3, r2
70000c4c:	f04f 0200 	mov.w	r2, #0
70000c50:	bf0c      	ite	eq
70000c52:	4b30      	ldreq	r3, [pc, #192]	; (70000d14 <__ieee754_pow+0x3dc>)
70000c54:	4b2c      	ldrne	r3, [pc, #176]	; (70000d08 <__ieee754_pow+0x3d0>)
70000c56:	e9dd 6702 	ldrd	r6, r7, [sp, #8]
70000c5a:	2600      	movs	r6, #0
70000c5c:	e9cd 2300 	strd	r2, r3, [sp]
70000c60:	e9dd 0102 	ldrd	r0, r1, [sp, #8]
70000c64:	4632      	mov	r2, r6
70000c66:	463b      	mov	r3, r7
70000c68:	f000 ff30 	bl	70001acc <__aeabi_dsub>
70000c6c:	4652      	mov	r2, sl
70000c6e:	465b      	mov	r3, fp
70000c70:	f001 f8e4 	bl	70001e3c <__aeabi_dmul>
70000c74:	4680      	mov	r8, r0
70000c76:	4689      	mov	r9, r1
70000c78:	4620      	mov	r0, r4
70000c7a:	4629      	mov	r1, r5
70000c7c:	e9dd 2302 	ldrd	r2, r3, [sp, #8]
70000c80:	f001 f8dc 	bl	70001e3c <__aeabi_dmul>
70000c84:	4602      	mov	r2, r0
70000c86:	460b      	mov	r3, r1
70000c88:	4640      	mov	r0, r8
70000c8a:	4649      	mov	r1, r9
70000c8c:	f000 ff20 	bl	70001ad0 <__adddf3>
70000c90:	4632      	mov	r2, r6
70000c92:	463b      	mov	r3, r7
70000c94:	4680      	mov	r8, r0
70000c96:	4689      	mov	r9, r1
70000c98:	4650      	mov	r0, sl
70000c9a:	4659      	mov	r1, fp
70000c9c:	f001 f8ce 	bl	70001e3c <__aeabi_dmul>
70000ca0:	4604      	mov	r4, r0
70000ca2:	460d      	mov	r5, r1
70000ca4:	460b      	mov	r3, r1
70000ca6:	4602      	mov	r2, r0
70000ca8:	4649      	mov	r1, r9
70000caa:	4640      	mov	r0, r8
70000cac:	e9cd 4502 	strd	r4, r5, [sp, #8]
70000cb0:	f000 ff0e 	bl	70001ad0 <__adddf3>
70000cb4:	4b18      	ldr	r3, [pc, #96]	; (70000d18 <__ieee754_pow+0x3e0>)
70000cb6:	4682      	mov	sl, r0
70000cb8:	460f      	mov	r7, r1
70000cba:	4299      	cmp	r1, r3
70000cbc:	460e      	mov	r6, r1
70000cbe:	f340 82e0 	ble.w	70001282 <__ieee754_pow+0x94a>
70000cc2:	f101 433f 	add.w	r3, r1, #3204448256	; 0xbf000000
70000cc6:	f503 03e0 	add.w	r3, r3, #7340032	; 0x700000
70000cca:	4303      	orrs	r3, r0
70000ccc:	f000 81da 	beq.w	70001084 <__ieee754_pow+0x74c>
70000cd0:	2200      	movs	r2, #0
70000cd2:	2300      	movs	r3, #0
70000cd4:	e9dd 0100 	ldrd	r0, r1, [sp]
70000cd8:	f001 fb22 	bl	70002320 <__aeabi_dcmplt>
70000cdc:	3800      	subs	r0, #0
70000cde:	bf18      	it	ne
70000ce0:	2001      	movne	r0, #1
70000ce2:	e72f      	b.n	70000b44 <__ieee754_pow+0x20c>
70000ce4:	f3af 8000 	nop.w
70000ce8:	60000000 	.word	0x60000000
70000cec:	3ff71547 	.word	0x3ff71547
70000cf0:	f85ddf44 	.word	0xf85ddf44
70000cf4:	3e54ae0b 	.word	0x3e54ae0b
70000cf8:	55555555 	.word	0x55555555
70000cfc:	3fd55555 	.word	0x3fd55555
70000d00:	652b82fe 	.word	0x652b82fe
70000d04:	3ff71547 	.word	0x3ff71547
70000d08:	3ff00000 	.word	0x3ff00000
70000d0c:	3fd00000 	.word	0x3fd00000
70000d10:	3fe00000 	.word	0x3fe00000
70000d14:	bff00000 	.word	0xbff00000
70000d18:	408fffff 	.word	0x408fffff
70000d1c:	4bd2      	ldr	r3, [pc, #840]	; (70001068 <__ieee754_pow+0x730>)
70000d1e:	2200      	movs	r2, #0
70000d20:	402b      	ands	r3, r5
70000d22:	b943      	cbnz	r3, 70000d36 <__ieee754_pow+0x3fe>
70000d24:	4658      	mov	r0, fp
70000d26:	4bd1      	ldr	r3, [pc, #836]	; (7000106c <__ieee754_pow+0x734>)
70000d28:	4661      	mov	r1, ip
70000d2a:	f001 f887 	bl	70001e3c <__aeabi_dmul>
70000d2e:	f06f 0234 	mvn.w	r2, #52	; 0x34
70000d32:	4683      	mov	fp, r0
70000d34:	460c      	mov	r4, r1
70000d36:	1523      	asrs	r3, r4, #20
70000d38:	f3c4 0413 	ubfx	r4, r4, #0, #20
70000d3c:	f2a3 33ff 	subw	r3, r3, #1023	; 0x3ff
70000d40:	f044 557f 	orr.w	r5, r4, #1069547520	; 0x3fc00000
70000d44:	4413      	add	r3, r2
70000d46:	f445 1540 	orr.w	r5, r5, #3145728	; 0x300000
70000d4a:	930b      	str	r3, [sp, #44]	; 0x2c
70000d4c:	4bc8      	ldr	r3, [pc, #800]	; (70001070 <__ieee754_pow+0x738>)
70000d4e:	429c      	cmp	r4, r3
70000d50:	dd08      	ble.n	70000d64 <__ieee754_pow+0x42c>
70000d52:	4bc8      	ldr	r3, [pc, #800]	; (70001074 <__ieee754_pow+0x73c>)
70000d54:	429c      	cmp	r4, r3
70000d56:	f340 815e 	ble.w	70001016 <__ieee754_pow+0x6de>
70000d5a:	9b0b      	ldr	r3, [sp, #44]	; 0x2c
70000d5c:	f5a5 1580 	sub.w	r5, r5, #1048576	; 0x100000
70000d60:	3301      	adds	r3, #1
70000d62:	930b      	str	r3, [sp, #44]	; 0x2c
70000d64:	2600      	movs	r6, #0
70000d66:	4bc4      	ldr	r3, [pc, #784]	; (70001078 <__ieee754_pow+0x740>)
70000d68:	46da      	mov	sl, fp
70000d6a:	4658      	mov	r0, fp
70000d6c:	4629      	mov	r1, r5
70000d6e:	eb03 03c6 	add.w	r3, r3, r6, lsl #3
70000d72:	46ab      	mov	fp, r5
70000d74:	930c      	str	r3, [sp, #48]	; 0x30
70000d76:	e9d3 3400 	ldrd	r3, r4, [r3]
70000d7a:	461a      	mov	r2, r3
70000d7c:	e9cd 3408 	strd	r3, r4, [sp, #32]
70000d80:	4623      	mov	r3, r4
70000d82:	f000 fea3 	bl	70001acc <__aeabi_dsub>
70000d86:	4652      	mov	r2, sl
70000d88:	462b      	mov	r3, r5
70000d8a:	106d      	asrs	r5, r5, #1
70000d8c:	e9cd 010e 	strd	r0, r1, [sp, #56]	; 0x38
70000d90:	e9dd 0108 	ldrd	r0, r1, [sp, #32]
70000d94:	f000 fe9c 	bl	70001ad0 <__adddf3>
70000d98:	4602      	mov	r2, r0
70000d9a:	460b      	mov	r3, r1
70000d9c:	2000      	movs	r0, #0
70000d9e:	49b7      	ldr	r1, [pc, #732]	; (7000107c <__ieee754_pow+0x744>)
70000da0:	f045 5500 	orr.w	r5, r5, #536870912	; 0x20000000
70000da4:	f001 f974 	bl	70002090 <__aeabi_ddiv>
70000da8:	4602      	mov	r2, r0
70000daa:	460b      	mov	r3, r1
70000dac:	f505 2500 	add.w	r5, r5, #524288	; 0x80000
70000db0:	e9cd 0110 	strd	r0, r1, [sp, #64]	; 0x40
70000db4:	e9dd 010e 	ldrd	r0, r1, [sp, #56]	; 0x38
70000db8:	f001 f840 	bl	70001e3c <__aeabi_dmul>
70000dbc:	2200      	movs	r2, #0
70000dbe:	e9cd 0106 	strd	r0, r1, [sp, #24]
70000dc2:	e9dd 3406 	ldrd	r3, r4, [sp, #24]
70000dc6:	e9cd 3404 	strd	r3, r4, [sp, #16]
70000dca:	2300      	movs	r3, #0
70000dcc:	4614      	mov	r4, r2
70000dce:	9304      	str	r3, [sp, #16]
70000dd0:	eb05 4386 	add.w	r3, r5, r6, lsl #18
70000dd4:	e9dd 8904 	ldrd	r8, r9, [sp, #16]
70000dd8:	461d      	mov	r5, r3
70000dda:	4640      	mov	r0, r8
70000ddc:	4649      	mov	r1, r9
70000dde:	f001 f82d 	bl	70001e3c <__aeabi_dmul>
70000de2:	4602      	mov	r2, r0
70000de4:	460b      	mov	r3, r1
70000de6:	e9dd 010e 	ldrd	r0, r1, [sp, #56]	; 0x38
70000dea:	f000 fe6f 	bl	70001acc <__aeabi_dsub>
70000dee:	4606      	mov	r6, r0
70000df0:	460f      	mov	r7, r1
70000df2:	4620      	mov	r0, r4
70000df4:	4629      	mov	r1, r5
70000df6:	e9dd 2308 	ldrd	r2, r3, [sp, #32]
70000dfa:	f000 fe67 	bl	70001acc <__aeabi_dsub>
70000dfe:	4602      	mov	r2, r0
70000e00:	460b      	mov	r3, r1
70000e02:	4650      	mov	r0, sl
70000e04:	4659      	mov	r1, fp
70000e06:	f000 fe61 	bl	70001acc <__aeabi_dsub>
70000e0a:	4642      	mov	r2, r8
70000e0c:	464b      	mov	r3, r9
70000e0e:	f001 f815 	bl	70001e3c <__aeabi_dmul>
70000e12:	4602      	mov	r2, r0
70000e14:	460b      	mov	r3, r1
70000e16:	4630      	mov	r0, r6
70000e18:	4639      	mov	r1, r7
70000e1a:	f000 fe57 	bl	70001acc <__aeabi_dsub>
70000e1e:	e9dd 2310 	ldrd	r2, r3, [sp, #64]	; 0x40
70000e22:	f001 f80b 	bl	70001e3c <__aeabi_dmul>
70000e26:	e9dd 2306 	ldrd	r2, r3, [sp, #24]
70000e2a:	e9cd 0108 	strd	r0, r1, [sp, #32]
70000e2e:	4610      	mov	r0, r2
70000e30:	4619      	mov	r1, r3
70000e32:	f001 f803 	bl	70001e3c <__aeabi_dmul>
70000e36:	4604      	mov	r4, r0
70000e38:	460d      	mov	r5, r1
70000e3a:	a379      	add	r3, pc, #484	; (adr r3, 70001020 <__ieee754_pow+0x6e8>)
70000e3c:	e9d3 2300 	ldrd	r2, r3, [r3]
70000e40:	f000 fffc 	bl	70001e3c <__aeabi_dmul>
70000e44:	a378      	add	r3, pc, #480	; (adr r3, 70001028 <__ieee754_pow+0x6f0>)
70000e46:	e9d3 2300 	ldrd	r2, r3, [r3]
70000e4a:	f000 fe41 	bl	70001ad0 <__adddf3>
70000e4e:	4622      	mov	r2, r4
70000e50:	462b      	mov	r3, r5
70000e52:	f000 fff3 	bl	70001e3c <__aeabi_dmul>
70000e56:	a376      	add	r3, pc, #472	; (adr r3, 70001030 <__ieee754_pow+0x6f8>)
70000e58:	e9d3 2300 	ldrd	r2, r3, [r3]
70000e5c:	f000 fe38 	bl	70001ad0 <__adddf3>
70000e60:	4622      	mov	r2, r4
70000e62:	462b      	mov	r3, r5
70000e64:	f000 ffea 	bl	70001e3c <__aeabi_dmul>
70000e68:	a373      	add	r3, pc, #460	; (adr r3, 70001038 <__ieee754_pow+0x700>)
70000e6a:	e9d3 2300 	ldrd	r2, r3, [r3]
70000e6e:	f000 fe2f 	bl	70001ad0 <__adddf3>
70000e72:	4622      	mov	r2, r4
70000e74:	462b      	mov	r3, r5
70000e76:	f000 ffe1 	bl	70001e3c <__aeabi_dmul>
70000e7a:	a371      	add	r3, pc, #452	; (adr r3, 70001040 <__ieee754_pow+0x708>)
70000e7c:	e9d3 2300 	ldrd	r2, r3, [r3]
70000e80:	f000 fe26 	bl	70001ad0 <__adddf3>
70000e84:	4622      	mov	r2, r4
70000e86:	462b      	mov	r3, r5
70000e88:	f000 ffd8 	bl	70001e3c <__aeabi_dmul>
70000e8c:	a36e      	add	r3, pc, #440	; (adr r3, 70001048 <__ieee754_pow+0x710>)
70000e8e:	e9d3 2300 	ldrd	r2, r3, [r3]
70000e92:	f000 fe1d 	bl	70001ad0 <__adddf3>
70000e96:	4606      	mov	r6, r0
70000e98:	460f      	mov	r7, r1
70000e9a:	4622      	mov	r2, r4
70000e9c:	462b      	mov	r3, r5
70000e9e:	4620      	mov	r0, r4
70000ea0:	4629      	mov	r1, r5
70000ea2:	f000 ffcb 	bl	70001e3c <__aeabi_dmul>
70000ea6:	4602      	mov	r2, r0
70000ea8:	460b      	mov	r3, r1
70000eaa:	4630      	mov	r0, r6
70000eac:	4639      	mov	r1, r7
70000eae:	f000 ffc5 	bl	70001e3c <__aeabi_dmul>
70000eb2:	4642      	mov	r2, r8
70000eb4:	4604      	mov	r4, r0
70000eb6:	460d      	mov	r5, r1
70000eb8:	464b      	mov	r3, r9
70000eba:	e9dd 0106 	ldrd	r0, r1, [sp, #24]
70000ebe:	f000 fe07 	bl	70001ad0 <__adddf3>
70000ec2:	e9dd 2308 	ldrd	r2, r3, [sp, #32]
70000ec6:	f000 ffb9 	bl	70001e3c <__aeabi_dmul>
70000eca:	4622      	mov	r2, r4
70000ecc:	462b      	mov	r3, r5
70000ece:	2400      	movs	r4, #0
70000ed0:	f000 fdfe 	bl	70001ad0 <__adddf3>
70000ed4:	4642      	mov	r2, r8
70000ed6:	4606      	mov	r6, r0
70000ed8:	460f      	mov	r7, r1
70000eda:	464b      	mov	r3, r9
70000edc:	4640      	mov	r0, r8
70000ede:	4649      	mov	r1, r9
70000ee0:	f000 ffac 	bl	70001e3c <__aeabi_dmul>
70000ee4:	2200      	movs	r2, #0
70000ee6:	4b66      	ldr	r3, [pc, #408]	; (70001080 <__ieee754_pow+0x748>)
70000ee8:	4682      	mov	sl, r0
70000eea:	468b      	mov	fp, r1
70000eec:	f000 fdf0 	bl	70001ad0 <__adddf3>
70000ef0:	4632      	mov	r2, r6
70000ef2:	463b      	mov	r3, r7
70000ef4:	f000 fdec 	bl	70001ad0 <__adddf3>
70000ef8:	460d      	mov	r5, r1
70000efa:	4622      	mov	r2, r4
70000efc:	460b      	mov	r3, r1
70000efe:	4640      	mov	r0, r8
70000f00:	4649      	mov	r1, r9
70000f02:	f000 ff9b 	bl	70001e3c <__aeabi_dmul>
70000f06:	2200      	movs	r2, #0
70000f08:	4680      	mov	r8, r0
70000f0a:	4689      	mov	r9, r1
70000f0c:	4b5c      	ldr	r3, [pc, #368]	; (70001080 <__ieee754_pow+0x748>)
70000f0e:	4620      	mov	r0, r4
70000f10:	4629      	mov	r1, r5
70000f12:	f000 fddb 	bl	70001acc <__aeabi_dsub>
70000f16:	4652      	mov	r2, sl
70000f18:	465b      	mov	r3, fp
70000f1a:	f04f 0a00 	mov.w	sl, #0
70000f1e:	f000 fdd5 	bl	70001acc <__aeabi_dsub>
70000f22:	4602      	mov	r2, r0
70000f24:	460b      	mov	r3, r1
70000f26:	4630      	mov	r0, r6
70000f28:	4639      	mov	r1, r7
70000f2a:	f000 fdcf 	bl	70001acc <__aeabi_dsub>
70000f2e:	e9dd 2306 	ldrd	r2, r3, [sp, #24]
70000f32:	f000 ff83 	bl	70001e3c <__aeabi_dmul>
70000f36:	4606      	mov	r6, r0
70000f38:	460f      	mov	r7, r1
70000f3a:	4622      	mov	r2, r4
70000f3c:	462b      	mov	r3, r5
70000f3e:	2400      	movs	r4, #0
70000f40:	e9dd 0108 	ldrd	r0, r1, [sp, #32]
70000f44:	f000 ff7a 	bl	70001e3c <__aeabi_dmul>
70000f48:	4602      	mov	r2, r0
70000f4a:	460b      	mov	r3, r1
70000f4c:	4630      	mov	r0, r6
70000f4e:	4639      	mov	r1, r7
70000f50:	f000 fdbe 	bl	70001ad0 <__adddf3>
70000f54:	4606      	mov	r6, r0
70000f56:	460f      	mov	r7, r1
70000f58:	4602      	mov	r2, r0
70000f5a:	460b      	mov	r3, r1
70000f5c:	4640      	mov	r0, r8
70000f5e:	4649      	mov	r1, r9
70000f60:	f000 fdb6 	bl	70001ad0 <__adddf3>
70000f64:	460d      	mov	r5, r1
70000f66:	4620      	mov	r0, r4
70000f68:	a339      	add	r3, pc, #228	; (adr r3, 70001050 <__ieee754_pow+0x718>)
70000f6a:	e9d3 2300 	ldrd	r2, r3, [r3]
70000f6e:	f000 ff65 	bl	70001e3c <__aeabi_dmul>
70000f72:	4642      	mov	r2, r8
70000f74:	464b      	mov	r3, r9
70000f76:	e9cd 0106 	strd	r0, r1, [sp, #24]
70000f7a:	4620      	mov	r0, r4
70000f7c:	4629      	mov	r1, r5
70000f7e:	f000 fda5 	bl	70001acc <__aeabi_dsub>
70000f82:	4602      	mov	r2, r0
70000f84:	460b      	mov	r3, r1
70000f86:	4630      	mov	r0, r6
70000f88:	4639      	mov	r1, r7
70000f8a:	f000 fd9f 	bl	70001acc <__aeabi_dsub>
70000f8e:	a332      	add	r3, pc, #200	; (adr r3, 70001058 <__ieee754_pow+0x720>)
70000f90:	e9d3 2300 	ldrd	r2, r3, [r3]
70000f94:	f000 ff52 	bl	70001e3c <__aeabi_dmul>
70000f98:	4606      	mov	r6, r0
70000f9a:	460f      	mov	r7, r1
70000f9c:	4620      	mov	r0, r4
70000f9e:	4629      	mov	r1, r5
70000fa0:	a32f      	add	r3, pc, #188	; (adr r3, 70001060 <__ieee754_pow+0x728>)
70000fa2:	e9d3 2300 	ldrd	r2, r3, [r3]
70000fa6:	f000 ff49 	bl	70001e3c <__aeabi_dmul>
70000faa:	4602      	mov	r2, r0
70000fac:	460b      	mov	r3, r1
70000fae:	4630      	mov	r0, r6
70000fb0:	4639      	mov	r1, r7
70000fb2:	f000 fd8d 	bl	70001ad0 <__adddf3>
70000fb6:	9b0c      	ldr	r3, [sp, #48]	; 0x30
70000fb8:	e9d3 2304 	ldrd	r2, r3, [r3, #16]
70000fbc:	f000 fd88 	bl	70001ad0 <__adddf3>
70000fc0:	4680      	mov	r8, r0
70000fc2:	980b      	ldr	r0, [sp, #44]	; 0x2c
70000fc4:	4689      	mov	r9, r1
70000fc6:	f000 fecf 	bl	70001d68 <__aeabi_i2d>
70000fca:	9b0c      	ldr	r3, [sp, #48]	; 0x30
70000fcc:	4604      	mov	r4, r0
70000fce:	460d      	mov	r5, r1
70000fd0:	4642      	mov	r2, r8
70000fd2:	e9d3 6708 	ldrd	r6, r7, [r3, #32]
70000fd6:	464b      	mov	r3, r9
70000fd8:	e9dd 0106 	ldrd	r0, r1, [sp, #24]
70000fdc:	f000 fd78 	bl	70001ad0 <__adddf3>
70000fe0:	4632      	mov	r2, r6
70000fe2:	463b      	mov	r3, r7
70000fe4:	f000 fd74 	bl	70001ad0 <__adddf3>
70000fe8:	4622      	mov	r2, r4
70000fea:	462b      	mov	r3, r5
70000fec:	f000 fd70 	bl	70001ad0 <__adddf3>
70000ff0:	4622      	mov	r2, r4
70000ff2:	462b      	mov	r3, r5
70000ff4:	4650      	mov	r0, sl
70000ff6:	468b      	mov	fp, r1
70000ff8:	f000 fd68 	bl	70001acc <__aeabi_dsub>
70000ffc:	4632      	mov	r2, r6
70000ffe:	463b      	mov	r3, r7
70001000:	f000 fd64 	bl	70001acc <__aeabi_dsub>
70001004:	e9dd 2306 	ldrd	r2, r3, [sp, #24]
70001008:	f000 fd60 	bl	70001acc <__aeabi_dsub>
7000100c:	4602      	mov	r2, r0
7000100e:	460b      	mov	r3, r1
70001010:	4640      	mov	r0, r8
70001012:	4649      	mov	r1, r9
70001014:	e612      	b.n	70000c3c <__ieee754_pow+0x304>
70001016:	2601      	movs	r6, #1
70001018:	e6a5      	b.n	70000d66 <__ieee754_pow+0x42e>
7000101a:	bf00      	nop
7000101c:	f3af 8000 	nop.w
70001020:	4a454eef 	.word	0x4a454eef
70001024:	3fca7e28 	.word	0x3fca7e28
70001028:	93c9db65 	.word	0x93c9db65
7000102c:	3fcd864a 	.word	0x3fcd864a
70001030:	a91d4101 	.word	0xa91d4101
70001034:	3fd17460 	.word	0x3fd17460
70001038:	518f264d 	.word	0x518f264d
7000103c:	3fd55555 	.word	0x3fd55555
70001040:	db6fabff 	.word	0xdb6fabff
70001044:	3fdb6db6 	.word	0x3fdb6db6
70001048:	33333303 	.word	0x33333303
7000104c:	3fe33333 	.word	0x3fe33333
70001050:	e0000000 	.word	0xe0000000
70001054:	3feec709 	.word	0x3feec709
70001058:	dc3a03fd 	.word	0xdc3a03fd
7000105c:	3feec709 	.word	0x3feec709
70001060:	145b01f5 	.word	0x145b01f5
70001064:	be3e2fe0 	.word	0xbe3e2fe0
70001068:	7ff00000 	.word	0x7ff00000
7000106c:	43400000 	.word	0x43400000
70001070:	0003988e 	.word	0x0003988e
70001074:	000bb679 	.word	0x000bb679
70001078:	70002a90 	.word	0x70002a90
7000107c:	3ff00000 	.word	0x3ff00000
70001080:	40080000 	.word	0x40080000
70001084:	a39c      	add	r3, pc, #624	; (adr r3, 700012f8 <__ieee754_pow+0x9c0>)
70001086:	e9d3 2300 	ldrd	r2, r3, [r3]
7000108a:	4640      	mov	r0, r8
7000108c:	4649      	mov	r1, r9
7000108e:	f000 fd1f 	bl	70001ad0 <__adddf3>
70001092:	4622      	mov	r2, r4
70001094:	462b      	mov	r3, r5
70001096:	e9cd 0104 	strd	r0, r1, [sp, #16]
7000109a:	4650      	mov	r0, sl
7000109c:	4639      	mov	r1, r7
7000109e:	f000 fd15 	bl	70001acc <__aeabi_dsub>
700010a2:	4602      	mov	r2, r0
700010a4:	460b      	mov	r3, r1
700010a6:	e9dd 0104 	ldrd	r0, r1, [sp, #16]
700010aa:	f001 f957 	bl	7000235c <__aeabi_dcmpgt>
700010ae:	2800      	cmp	r0, #0
700010b0:	f47f ae0e 	bne.w	70000cd0 <__ieee754_pow+0x398>
700010b4:	f026 4300 	bic.w	r3, r6, #2147483648	; 0x80000000
700010b8:	4aa1      	ldr	r2, [pc, #644]	; (70001340 <__ieee754_pow+0xa08>)
700010ba:	4293      	cmp	r3, r2
700010bc:	f340 8101 	ble.w	700012c2 <__ieee754_pow+0x98a>
700010c0:	151b      	asrs	r3, r3, #20
700010c2:	f44f 1a80 	mov.w	sl, #1048576	; 0x100000
700010c6:	4f9f      	ldr	r7, [pc, #636]	; (70001344 <__ieee754_pow+0xa0c>)
700010c8:	2000      	movs	r0, #0
700010ca:	f2a3 33fe 	subw	r3, r3, #1022	; 0x3fe
700010ce:	2e00      	cmp	r6, #0
700010d0:	fa4a f303 	asr.w	r3, sl, r3
700010d4:	4433      	add	r3, r6
700010d6:	f3c3 520a 	ubfx	r2, r3, #20, #11
700010da:	f3c3 0a13 	ubfx	sl, r3, #0, #20
700010de:	f2a2 32ff 	subw	r2, r2, #1023	; 0x3ff
700010e2:	f44a 1a80 	orr.w	sl, sl, #1048576	; 0x100000
700010e6:	fa47 f702 	asr.w	r7, r7, r2
700010ea:	f1c2 0214 	rsb	r2, r2, #20
700010ee:	ea23 0107 	bic.w	r1, r3, r7
700010f2:	fa4a fa02 	asr.w	sl, sl, r2
700010f6:	4602      	mov	r2, r0
700010f8:	4620      	mov	r0, r4
700010fa:	460b      	mov	r3, r1
700010fc:	4629      	mov	r1, r5
700010fe:	bfb8      	it	lt
70001100:	f1ca 0a00 	rsblt	sl, sl, #0
70001104:	f000 fce2 	bl	70001acc <__aeabi_dsub>
70001108:	e9cd 0102 	strd	r0, r1, [sp, #8]
7000110c:	2400      	movs	r4, #0
7000110e:	4642      	mov	r2, r8
70001110:	464b      	mov	r3, r9
70001112:	e9dd 0102 	ldrd	r0, r1, [sp, #8]
70001116:	f000 fcdb 	bl	70001ad0 <__adddf3>
7000111a:	460d      	mov	r5, r1
7000111c:	4620      	mov	r0, r4
7000111e:	a378      	add	r3, pc, #480	; (adr r3, 70001300 <__ieee754_pow+0x9c8>)
70001120:	e9d3 2300 	ldrd	r2, r3, [r3]
70001124:	f000 fe8a 	bl	70001e3c <__aeabi_dmul>
70001128:	4606      	mov	r6, r0
7000112a:	460f      	mov	r7, r1
7000112c:	4620      	mov	r0, r4
7000112e:	4629      	mov	r1, r5
70001130:	e9dd 2302 	ldrd	r2, r3, [sp, #8]
70001134:	f000 fcca 	bl	70001acc <__aeabi_dsub>
70001138:	4602      	mov	r2, r0
7000113a:	460b      	mov	r3, r1
7000113c:	4640      	mov	r0, r8
7000113e:	4649      	mov	r1, r9
70001140:	f000 fcc4 	bl	70001acc <__aeabi_dsub>
70001144:	a370      	add	r3, pc, #448	; (adr r3, 70001308 <__ieee754_pow+0x9d0>)
70001146:	e9d3 2300 	ldrd	r2, r3, [r3]
7000114a:	f000 fe77 	bl	70001e3c <__aeabi_dmul>
7000114e:	4680      	mov	r8, r0
70001150:	4689      	mov	r9, r1
70001152:	4620      	mov	r0, r4
70001154:	4629      	mov	r1, r5
70001156:	a36e      	add	r3, pc, #440	; (adr r3, 70001310 <__ieee754_pow+0x9d8>)
70001158:	e9d3 2300 	ldrd	r2, r3, [r3]
7000115c:	f000 fe6e 	bl	70001e3c <__aeabi_dmul>
70001160:	4602      	mov	r2, r0
70001162:	460b      	mov	r3, r1
70001164:	4640      	mov	r0, r8
70001166:	4649      	mov	r1, r9
70001168:	f000 fcb2 	bl	70001ad0 <__adddf3>
7000116c:	4604      	mov	r4, r0
7000116e:	460d      	mov	r5, r1
70001170:	4602      	mov	r2, r0
70001172:	460b      	mov	r3, r1
70001174:	4630      	mov	r0, r6
70001176:	4639      	mov	r1, r7
70001178:	f000 fcaa 	bl	70001ad0 <__adddf3>
7000117c:	4632      	mov	r2, r6
7000117e:	4680      	mov	r8, r0
70001180:	4689      	mov	r9, r1
70001182:	463b      	mov	r3, r7
70001184:	f000 fca2 	bl	70001acc <__aeabi_dsub>
70001188:	4602      	mov	r2, r0
7000118a:	460b      	mov	r3, r1
7000118c:	4620      	mov	r0, r4
7000118e:	4629      	mov	r1, r5
70001190:	f000 fc9c 	bl	70001acc <__aeabi_dsub>
70001194:	4642      	mov	r2, r8
70001196:	4606      	mov	r6, r0
70001198:	460f      	mov	r7, r1
7000119a:	464b      	mov	r3, r9
7000119c:	4640      	mov	r0, r8
7000119e:	4649      	mov	r1, r9
700011a0:	f000 fe4c 	bl	70001e3c <__aeabi_dmul>
700011a4:	4604      	mov	r4, r0
700011a6:	460d      	mov	r5, r1
700011a8:	a35b      	add	r3, pc, #364	; (adr r3, 70001318 <__ieee754_pow+0x9e0>)
700011aa:	e9d3 2300 	ldrd	r2, r3, [r3]
700011ae:	f000 fe45 	bl	70001e3c <__aeabi_dmul>
700011b2:	a35b      	add	r3, pc, #364	; (adr r3, 70001320 <__ieee754_pow+0x9e8>)
700011b4:	e9d3 2300 	ldrd	r2, r3, [r3]
700011b8:	f000 fc88 	bl	70001acc <__aeabi_dsub>
700011bc:	4622      	mov	r2, r4
700011be:	462b      	mov	r3, r5
700011c0:	f000 fe3c 	bl	70001e3c <__aeabi_dmul>
700011c4:	a358      	add	r3, pc, #352	; (adr r3, 70001328 <__ieee754_pow+0x9f0>)
700011c6:	e9d3 2300 	ldrd	r2, r3, [r3]
700011ca:	f000 fc81 	bl	70001ad0 <__adddf3>
700011ce:	4622      	mov	r2, r4
700011d0:	462b      	mov	r3, r5
700011d2:	f000 fe33 	bl	70001e3c <__aeabi_dmul>
700011d6:	a356      	add	r3, pc, #344	; (adr r3, 70001330 <__ieee754_pow+0x9f8>)
700011d8:	e9d3 2300 	ldrd	r2, r3, [r3]
700011dc:	f000 fc76 	bl	70001acc <__aeabi_dsub>
700011e0:	4622      	mov	r2, r4
700011e2:	462b      	mov	r3, r5
700011e4:	f000 fe2a 	bl	70001e3c <__aeabi_dmul>
700011e8:	a353      	add	r3, pc, #332	; (adr r3, 70001338 <__ieee754_pow+0xa00>)
700011ea:	e9d3 2300 	ldrd	r2, r3, [r3]
700011ee:	f000 fc6f 	bl	70001ad0 <__adddf3>
700011f2:	4622      	mov	r2, r4
700011f4:	462b      	mov	r3, r5
700011f6:	f000 fe21 	bl	70001e3c <__aeabi_dmul>
700011fa:	4602      	mov	r2, r0
700011fc:	460b      	mov	r3, r1
700011fe:	4640      	mov	r0, r8
70001200:	4649      	mov	r1, r9
70001202:	f000 fc63 	bl	70001acc <__aeabi_dsub>
70001206:	4604      	mov	r4, r0
70001208:	460d      	mov	r5, r1
7000120a:	4602      	mov	r2, r0
7000120c:	460b      	mov	r3, r1
7000120e:	4640      	mov	r0, r8
70001210:	4649      	mov	r1, r9
70001212:	f000 fe13 	bl	70001e3c <__aeabi_dmul>
70001216:	2200      	movs	r2, #0
70001218:	f04f 4380 	mov.w	r3, #1073741824	; 0x40000000
7000121c:	e9cd 0102 	strd	r0, r1, [sp, #8]
70001220:	4620      	mov	r0, r4
70001222:	4629      	mov	r1, r5
70001224:	f000 fc52 	bl	70001acc <__aeabi_dsub>
70001228:	4602      	mov	r2, r0
7000122a:	460b      	mov	r3, r1
7000122c:	e9dd 0102 	ldrd	r0, r1, [sp, #8]
70001230:	f000 ff2e 	bl	70002090 <__aeabi_ddiv>
70001234:	4632      	mov	r2, r6
70001236:	4604      	mov	r4, r0
70001238:	460d      	mov	r5, r1
7000123a:	463b      	mov	r3, r7
7000123c:	4640      	mov	r0, r8
7000123e:	4649      	mov	r1, r9
70001240:	f000 fdfc 	bl	70001e3c <__aeabi_dmul>
70001244:	4632      	mov	r2, r6
70001246:	463b      	mov	r3, r7
70001248:	f000 fc42 	bl	70001ad0 <__adddf3>
7000124c:	4602      	mov	r2, r0
7000124e:	460b      	mov	r3, r1
70001250:	4620      	mov	r0, r4
70001252:	4629      	mov	r1, r5
70001254:	f000 fc3a 	bl	70001acc <__aeabi_dsub>
70001258:	4642      	mov	r2, r8
7000125a:	464b      	mov	r3, r9
7000125c:	f000 fc36 	bl	70001acc <__aeabi_dsub>
70001260:	4602      	mov	r2, r0
70001262:	460b      	mov	r3, r1
70001264:	2000      	movs	r0, #0
70001266:	4938      	ldr	r1, [pc, #224]	; (70001348 <__ieee754_pow+0xa10>)
70001268:	f000 fc30 	bl	70001acc <__aeabi_dsub>
7000126c:	eb01 540a 	add.w	r4, r1, sl, lsl #20
70001270:	f5b4 1f80 	cmp.w	r4, #1048576	; 0x100000
70001274:	da28      	bge.n	700012c8 <__ieee754_pow+0x990>
70001276:	4652      	mov	r2, sl
70001278:	f000 f9c2 	bl	70001600 <scalbn>
7000127c:	e9dd 2300 	ldrd	r2, r3, [sp]
70001280:	e403      	b.n	70000a8a <__ieee754_pow+0x152>
70001282:	f021 4700 	bic.w	r7, r1, #2147483648	; 0x80000000
70001286:	4b31      	ldr	r3, [pc, #196]	; (7000134c <__ieee754_pow+0xa14>)
70001288:	429f      	cmp	r7, r3
7000128a:	f77f af13 	ble.w	700010b4 <__ieee754_pow+0x77c>
7000128e:	4b30      	ldr	r3, [pc, #192]	; (70001350 <__ieee754_pow+0xa18>)
70001290:	440b      	add	r3, r1
70001292:	4303      	orrs	r3, r0
70001294:	d009      	beq.n	700012aa <__ieee754_pow+0x972>
70001296:	2200      	movs	r2, #0
70001298:	2300      	movs	r3, #0
7000129a:	e9dd 0100 	ldrd	r0, r1, [sp]
7000129e:	f001 f83f 	bl	70002320 <__aeabi_dcmplt>
700012a2:	3800      	subs	r0, #0
700012a4:	bf18      	it	ne
700012a6:	2001      	movne	r0, #1
700012a8:	e459      	b.n	70000b5e <__ieee754_pow+0x226>
700012aa:	4622      	mov	r2, r4
700012ac:	462b      	mov	r3, r5
700012ae:	f000 fc0d 	bl	70001acc <__aeabi_dsub>
700012b2:	4642      	mov	r2, r8
700012b4:	464b      	mov	r3, r9
700012b6:	f001 f847 	bl	70002348 <__aeabi_dcmpge>
700012ba:	2800      	cmp	r0, #0
700012bc:	f43f aefa 	beq.w	700010b4 <__ieee754_pow+0x77c>
700012c0:	e7e9      	b.n	70001296 <__ieee754_pow+0x95e>
700012c2:	f04f 0a00 	mov.w	sl, #0
700012c6:	e721      	b.n	7000110c <__ieee754_pow+0x7d4>
700012c8:	4621      	mov	r1, r4
700012ca:	e7d7      	b.n	7000127c <__ieee754_pow+0x944>
700012cc:	f04f 0b00 	mov.w	fp, #0
700012d0:	f8df c074 	ldr.w	ip, [pc, #116]	; 70001348 <__ieee754_pow+0xa10>
700012d4:	f7ff bbc0 	b.w	70000a58 <__ieee754_pow+0x120>
700012d8:	f04f 0b00 	mov.w	fp, #0
700012dc:	f04f 0c00 	mov.w	ip, #0
700012e0:	f7ff bbba 	b.w	70000a58 <__ieee754_pow+0x120>
700012e4:	4640      	mov	r0, r8
700012e6:	4649      	mov	r1, r9
700012e8:	f7ff bb43 	b.w	70000972 <__ieee754_pow+0x3a>
700012ec:	9200      	str	r2, [sp, #0]
700012ee:	f7ff bb8f 	b.w	70000a10 <__ieee754_pow+0xd8>
700012f2:	2300      	movs	r3, #0
700012f4:	f7ff bb79 	b.w	700009ea <__ieee754_pow+0xb2>
700012f8:	652b82fe 	.word	0x652b82fe
700012fc:	3c971547 	.word	0x3c971547
70001300:	00000000 	.word	0x00000000
70001304:	3fe62e43 	.word	0x3fe62e43
70001308:	fefa39ef 	.word	0xfefa39ef
7000130c:	3fe62e42 	.word	0x3fe62e42
70001310:	0ca86c39 	.word	0x0ca86c39
70001314:	be205c61 	.word	0xbe205c61
70001318:	72bea4d0 	.word	0x72bea4d0
7000131c:	3e663769 	.word	0x3e663769
70001320:	c5d26bf1 	.word	0xc5d26bf1
70001324:	3ebbbd41 	.word	0x3ebbbd41
70001328:	af25de2c 	.word	0xaf25de2c
7000132c:	3f11566a 	.word	0x3f11566a
70001330:	16bebd93 	.word	0x16bebd93
70001334:	3f66c16c 	.word	0x3f66c16c
70001338:	5555553e 	.word	0x5555553e
7000133c:	3fc55555 	.word	0x3fc55555
70001340:	3fe00000 	.word	0x3fe00000
70001344:	000fffff 	.word	0x000fffff
70001348:	3ff00000 	.word	0x3ff00000
7000134c:	4090cbff 	.word	0x4090cbff
70001350:	3f6f3400 	.word	0x3f6f3400

70001354 <__ieee754_sqrt>:
70001354:	f8df c160 	ldr.w	ip, [pc, #352]	; 700014b8 <__ieee754_sqrt+0x164>
70001358:	460a      	mov	r2, r1
7000135a:	4603      	mov	r3, r0
7000135c:	ea3c 0c01 	bics.w	ip, ip, r1
70001360:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
70001364:	4606      	mov	r6, r0
70001366:	460d      	mov	r5, r1
70001368:	460c      	mov	r4, r1
7000136a:	4607      	mov	r7, r0
7000136c:	d10f      	bne.n	7000138e <__ieee754_sqrt+0x3a>
7000136e:	4602      	mov	r2, r0
70001370:	460b      	mov	r3, r1
70001372:	f000 fd63 	bl	70001e3c <__aeabi_dmul>
70001376:	4602      	mov	r2, r0
70001378:	460b      	mov	r3, r1
7000137a:	4630      	mov	r0, r6
7000137c:	4629      	mov	r1, r5
7000137e:	f000 fba7 	bl	70001ad0 <__adddf3>
70001382:	4606      	mov	r6, r0
70001384:	460d      	mov	r5, r1
70001386:	4630      	mov	r0, r6
70001388:	4629      	mov	r1, r5
7000138a:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
7000138e:	2900      	cmp	r1, #0
70001390:	dc0e      	bgt.n	700013b0 <__ieee754_sqrt+0x5c>
70001392:	f021 4c00 	bic.w	ip, r1, #2147483648	; 0x80000000
70001396:	ea5c 0707 	orrs.w	r7, ip, r7
7000139a:	d0f4      	beq.n	70001386 <__ieee754_sqrt+0x32>
7000139c:	b141      	cbz	r1, 700013b0 <__ieee754_sqrt+0x5c>
7000139e:	4602      	mov	r2, r0
700013a0:	460b      	mov	r3, r1
700013a2:	f000 fb93 	bl	70001acc <__aeabi_dsub>
700013a6:	4602      	mov	r2, r0
700013a8:	460b      	mov	r3, r1
700013aa:	f000 fe71 	bl	70002090 <__aeabi_ddiv>
700013ae:	e7e8      	b.n	70001382 <__ieee754_sqrt+0x2e>
700013b0:	1521      	asrs	r1, r4, #20
700013b2:	d07a      	beq.n	700014aa <__ieee754_sqrt+0x156>
700013b4:	07cc      	lsls	r4, r1, #31
700013b6:	f3c2 0213 	ubfx	r2, r2, #0, #20
700013ba:	f2a1 37ff 	subw	r7, r1, #1023	; 0x3ff
700013be:	f04f 0400 	mov.w	r4, #0
700013c2:	bf58      	it	pl
700013c4:	0fd9      	lsrpl	r1, r3, #31
700013c6:	f442 1280 	orr.w	r2, r2, #1048576	; 0x100000
700013ca:	bf58      	it	pl
700013cc:	005b      	lslpl	r3, r3, #1
700013ce:	f04f 0516 	mov.w	r5, #22
700013d2:	bf58      	it	pl
700013d4:	eb01 0242 	addpl.w	r2, r1, r2, lsl #1
700013d8:	4620      	mov	r0, r4
700013da:	0fd9      	lsrs	r1, r3, #31
700013dc:	107f      	asrs	r7, r7, #1
700013de:	eb01 0242 	add.w	r2, r1, r2, lsl #1
700013e2:	f44f 1100 	mov.w	r1, #2097152	; 0x200000
700013e6:	005b      	lsls	r3, r3, #1
700013e8:	1846      	adds	r6, r0, r1
700013ea:	4296      	cmp	r6, r2
700013ec:	bfde      	ittt	le
700013ee:	1b92      	suble	r2, r2, r6
700013f0:	1870      	addle	r0, r6, r1
700013f2:	1864      	addle	r4, r4, r1
700013f4:	3d01      	subs	r5, #1
700013f6:	ea4f 0242 	mov.w	r2, r2, lsl #1
700013fa:	ea4f 0151 	mov.w	r1, r1, lsr #1
700013fe:	eb02 72d3 	add.w	r2, r2, r3, lsr #31
70001402:	ea4f 0343 	mov.w	r3, r3, lsl #1
70001406:	d1ef      	bne.n	700013e8 <__ieee754_sqrt+0x94>
70001408:	4629      	mov	r1, r5
7000140a:	f04f 0e20 	mov.w	lr, #32
7000140e:	f04f 4600 	mov.w	r6, #2147483648	; 0x80000000
70001412:	4282      	cmp	r2, r0
70001414:	eb06 0c05 	add.w	ip, r6, r5
70001418:	dc02      	bgt.n	70001420 <__ieee754_sqrt+0xcc>
7000141a:	d113      	bne.n	70001444 <__ieee754_sqrt+0xf0>
7000141c:	459c      	cmp	ip, r3
7000141e:	d811      	bhi.n	70001444 <__ieee754_sqrt+0xf0>
70001420:	f1bc 0f00 	cmp.w	ip, #0
70001424:	eb0c 0506 	add.w	r5, ip, r6
70001428:	da44      	bge.n	700014b4 <__ieee754_sqrt+0x160>
7000142a:	2d00      	cmp	r5, #0
7000142c:	db42      	blt.n	700014b4 <__ieee754_sqrt+0x160>
7000142e:	f100 0801 	add.w	r8, r0, #1
70001432:	1a12      	subs	r2, r2, r0
70001434:	459c      	cmp	ip, r3
70001436:	4431      	add	r1, r6
70001438:	eba3 030c 	sub.w	r3, r3, ip
7000143c:	bf88      	it	hi
7000143e:	f102 32ff 	addhi.w	r2, r2, #4294967295
70001442:	4640      	mov	r0, r8
70001444:	ea4f 7cd3 	mov.w	ip, r3, lsr #31
70001448:	f1be 0e01 	subs.w	lr, lr, #1
7000144c:	ea4f 0343 	mov.w	r3, r3, lsl #1
70001450:	eb0c 0242 	add.w	r2, ip, r2, lsl #1
70001454:	ea4f 0656 	mov.w	r6, r6, lsr #1
70001458:	d1db      	bne.n	70001412 <__ieee754_sqrt+0xbe>
7000145a:	4313      	orrs	r3, r2
7000145c:	d006      	beq.n	7000146c <__ieee754_sqrt+0x118>
7000145e:	1c48      	adds	r0, r1, #1
70001460:	bf13      	iteet	ne
70001462:	3101      	addne	r1, #1
70001464:	3401      	addeq	r4, #1
70001466:	4671      	moveq	r1, lr
70001468:	f021 0101 	bicne.w	r1, r1, #1
7000146c:	1063      	asrs	r3, r4, #1
7000146e:	07e2      	lsls	r2, r4, #31
70001470:	ea4f 0151 	mov.w	r1, r1, lsr #1
70001474:	f103 537f 	add.w	r3, r3, #1069547520	; 0x3fc00000
70001478:	bf48      	it	mi
7000147a:	f041 4100 	orrmi.w	r1, r1, #2147483648	; 0x80000000
7000147e:	f503 1300 	add.w	r3, r3, #2097152	; 0x200000
70001482:	460e      	mov	r6, r1
70001484:	eb03 5507 	add.w	r5, r3, r7, lsl #20
70001488:	e77d      	b.n	70001386 <__ieee754_sqrt+0x32>
7000148a:	0ada      	lsrs	r2, r3, #11
7000148c:	3815      	subs	r0, #21
7000148e:	055b      	lsls	r3, r3, #21
70001490:	2a00      	cmp	r2, #0
70001492:	d0fa      	beq.n	7000148a <__ieee754_sqrt+0x136>
70001494:	02d5      	lsls	r5, r2, #11
70001496:	d50a      	bpl.n	700014ae <__ieee754_sqrt+0x15a>
70001498:	f1c1 0420 	rsb	r4, r1, #32
7000149c:	1e4d      	subs	r5, r1, #1
7000149e:	fa23 f404 	lsr.w	r4, r3, r4
700014a2:	408b      	lsls	r3, r1
700014a4:	1b41      	subs	r1, r0, r5
700014a6:	4322      	orrs	r2, r4
700014a8:	e784      	b.n	700013b4 <__ieee754_sqrt+0x60>
700014aa:	4608      	mov	r0, r1
700014ac:	e7f0      	b.n	70001490 <__ieee754_sqrt+0x13c>
700014ae:	0052      	lsls	r2, r2, #1
700014b0:	3101      	adds	r1, #1
700014b2:	e7ef      	b.n	70001494 <__ieee754_sqrt+0x140>
700014b4:	4680      	mov	r8, r0
700014b6:	e7bc      	b.n	70001432 <__ieee754_sqrt+0xde>
700014b8:	7ff00000 	.word	0x7ff00000

700014bc <with_errno>:
700014bc:	b570      	push	{r4, r5, r6, lr}
700014be:	4604      	mov	r4, r0
700014c0:	460d      	mov	r5, r1
700014c2:	4616      	mov	r6, r2
700014c4:	f000 f91a 	bl	700016fc <__errno>
700014c8:	4629      	mov	r1, r5
700014ca:	6006      	str	r6, [r0, #0]
700014cc:	4620      	mov	r0, r4
700014ce:	bd70      	pop	{r4, r5, r6, pc}

700014d0 <xflow>:
700014d0:	b537      	push	{r0, r1, r2, r4, r5, lr}
700014d2:	4615      	mov	r5, r2
700014d4:	461c      	mov	r4, r3
700014d6:	b178      	cbz	r0, 700014f8 <xflow+0x28>
700014d8:	4610      	mov	r0, r2
700014da:	f103 4100 	add.w	r1, r3, #2147483648	; 0x80000000
700014de:	e9cd 0100 	strd	r0, r1, [sp]
700014e2:	e9dd 2300 	ldrd	r2, r3, [sp]
700014e6:	4628      	mov	r0, r5
700014e8:	4621      	mov	r1, r4
700014ea:	f000 fca7 	bl	70001e3c <__aeabi_dmul>
700014ee:	2222      	movs	r2, #34	; 0x22
700014f0:	b003      	add	sp, #12
700014f2:	e8bd 4030 	ldmia.w	sp!, {r4, r5, lr}
700014f6:	e7e1      	b.n	700014bc <with_errno>
700014f8:	4610      	mov	r0, r2
700014fa:	4619      	mov	r1, r3
700014fc:	e7ef      	b.n	700014de <xflow+0xe>

700014fe <__math_uflow>:
700014fe:	2200      	movs	r2, #0
70001500:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70001504:	e7e4      	b.n	700014d0 <xflow>

70001506 <__math_may_uflow>:
70001506:	2200      	movs	r2, #0
70001508:	4b00      	ldr	r3, [pc, #0]	; (7000150c <__math_may_uflow+0x6>)
7000150a:	e7e1      	b.n	700014d0 <xflow>
7000150c:	1e580000 	.word	0x1e580000

70001510 <__math_oflow>:
70001510:	2200      	movs	r2, #0
70001512:	f04f 43e0 	mov.w	r3, #1879048192	; 0x70000000
70001516:	e7db      	b.n	700014d0 <xflow>

70001518 <__math_divzero>:
70001518:	b507      	push	{r0, r1, r2, lr}
7000151a:	2200      	movs	r2, #0
7000151c:	b968      	cbnz	r0, 7000153a <__math_divzero+0x22>
7000151e:	4b08      	ldr	r3, [pc, #32]	; (70001540 <__math_divzero+0x28>)
70001520:	e9cd 2300 	strd	r2, r3, [sp]
70001524:	e9dd 0100 	ldrd	r0, r1, [sp]
70001528:	2200      	movs	r2, #0
7000152a:	2300      	movs	r3, #0
7000152c:	f000 fdb0 	bl	70002090 <__aeabi_ddiv>
70001530:	2222      	movs	r2, #34	; 0x22
70001532:	b003      	add	sp, #12
70001534:	f85d eb04 	ldr.w	lr, [sp], #4
70001538:	e7c0      	b.n	700014bc <with_errno>
7000153a:	4b02      	ldr	r3, [pc, #8]	; (70001544 <__math_divzero+0x2c>)
7000153c:	e7f0      	b.n	70001520 <__math_divzero+0x8>
7000153e:	bf00      	nop
70001540:	3ff00000 	.word	0x3ff00000
70001544:	bff00000 	.word	0xbff00000

70001548 <__math_invalid>:
70001548:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
7000154a:	4602      	mov	r2, r0
7000154c:	4606      	mov	r6, r0
7000154e:	460f      	mov	r7, r1
70001550:	460b      	mov	r3, r1
70001552:	f000 fabb 	bl	70001acc <__aeabi_dsub>
70001556:	4602      	mov	r2, r0
70001558:	460b      	mov	r3, r1
7000155a:	f000 fd99 	bl	70002090 <__aeabi_ddiv>
7000155e:	4632      	mov	r2, r6
70001560:	4604      	mov	r4, r0
70001562:	460d      	mov	r5, r1
70001564:	463b      	mov	r3, r7
70001566:	4630      	mov	r0, r6
70001568:	4639      	mov	r1, r7
7000156a:	f000 ff01 	bl	70002370 <__aeabi_dcmpun>
7000156e:	b928      	cbnz	r0, 7000157c <__math_invalid+0x34>
70001570:	4620      	mov	r0, r4
70001572:	4629      	mov	r1, r5
70001574:	2221      	movs	r2, #33	; 0x21
70001576:	e8bd 40f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, lr}
7000157a:	e79f      	b.n	700014bc <with_errno>
7000157c:	4620      	mov	r0, r4
7000157e:	4629      	mov	r1, r5
70001580:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}

70001582 <__math_check_uflow>:
70001582:	b538      	push	{r3, r4, r5, lr}
70001584:	2200      	movs	r2, #0
70001586:	2300      	movs	r3, #0
70001588:	4604      	mov	r4, r0
7000158a:	460d      	mov	r5, r1
7000158c:	f000 febe 	bl	7000230c <__aeabi_dcmpeq>
70001590:	b128      	cbz	r0, 7000159e <__math_check_uflow+0x1c>
70001592:	4620      	mov	r0, r4
70001594:	4629      	mov	r1, r5
70001596:	2222      	movs	r2, #34	; 0x22
70001598:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
7000159c:	e78e      	b.n	700014bc <with_errno>
7000159e:	4620      	mov	r0, r4
700015a0:	4629      	mov	r1, r5
700015a2:	bd38      	pop	{r3, r4, r5, pc}

700015a4 <__math_check_oflow>:
700015a4:	b570      	push	{r4, r5, r6, lr}
700015a6:	4604      	mov	r4, r0
700015a8:	f021 4600 	bic.w	r6, r1, #2147483648	; 0x80000000
700015ac:	460d      	mov	r5, r1
700015ae:	f04f 32ff 	mov.w	r2, #4294967295
700015b2:	4b0b      	ldr	r3, [pc, #44]	; (700015e0 <__math_check_oflow+0x3c>)
700015b4:	4620      	mov	r0, r4
700015b6:	4631      	mov	r1, r6
700015b8:	f000 feda 	bl	70002370 <__aeabi_dcmpun>
700015bc:	b968      	cbnz	r0, 700015da <__math_check_oflow+0x36>
700015be:	f04f 32ff 	mov.w	r2, #4294967295
700015c2:	4b07      	ldr	r3, [pc, #28]	; (700015e0 <__math_check_oflow+0x3c>)
700015c4:	4620      	mov	r0, r4
700015c6:	4631      	mov	r1, r6
700015c8:	f000 feb4 	bl	70002334 <__aeabi_dcmple>
700015cc:	b928      	cbnz	r0, 700015da <__math_check_oflow+0x36>
700015ce:	4620      	mov	r0, r4
700015d0:	4629      	mov	r1, r5
700015d2:	2222      	movs	r2, #34	; 0x22
700015d4:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
700015d8:	e770      	b.n	700014bc <with_errno>
700015da:	4620      	mov	r0, r4
700015dc:	4629      	mov	r1, r5
700015de:	bd70      	pop	{r4, r5, r6, pc}
700015e0:	7fefffff 	.word	0x7fefffff

700015e4 <fabs>:
700015e4:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
700015e8:	4770      	bx	lr

700015ea <finite>:
700015ea:	f041 4000 	orr.w	r0, r1, #2147483648	; 0x80000000
700015ee:	f500 1080 	add.w	r0, r0, #1048576	; 0x100000
700015f2:	0fc0      	lsrs	r0, r0, #31
700015f4:	4770      	bx	lr
	...

700015f8 <nanf>:
700015f8:	4800      	ldr	r0, [pc, #0]	; (700015fc <nanf+0x4>)
700015fa:	4770      	bx	lr
700015fc:	7fc00000 	.word	0x7fc00000

70001600 <scalbn>:
70001600:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
70001602:	f3c1 560a 	ubfx	r6, r1, #20, #11
70001606:	4604      	mov	r4, r0
70001608:	460d      	mov	r5, r1
7000160a:	4617      	mov	r7, r2
7000160c:	460b      	mov	r3, r1
7000160e:	b996      	cbnz	r6, 70001636 <scalbn+0x36>
70001610:	f021 4300 	bic.w	r3, r1, #2147483648	; 0x80000000
70001614:	4303      	orrs	r3, r0
70001616:	d039      	beq.n	7000168c <scalbn+0x8c>
70001618:	4b33      	ldr	r3, [pc, #204]	; (700016e8 <scalbn+0xe8>)
7000161a:	2200      	movs	r2, #0
7000161c:	f000 fc0e 	bl	70001e3c <__aeabi_dmul>
70001620:	4b32      	ldr	r3, [pc, #200]	; (700016ec <scalbn+0xec>)
70001622:	4604      	mov	r4, r0
70001624:	460d      	mov	r5, r1
70001626:	429f      	cmp	r7, r3
70001628:	da0f      	bge.n	7000164a <scalbn+0x4a>
7000162a:	a32b      	add	r3, pc, #172	; (adr r3, 700016d8 <scalbn+0xd8>)
7000162c:	e9d3 2300 	ldrd	r2, r3, [r3]
70001630:	f000 fc04 	bl	70001e3c <__aeabi_dmul>
70001634:	e006      	b.n	70001644 <scalbn+0x44>
70001636:	f240 72ff 	movw	r2, #2047	; 0x7ff
7000163a:	4296      	cmp	r6, r2
7000163c:	d10a      	bne.n	70001654 <scalbn+0x54>
7000163e:	4602      	mov	r2, r0
70001640:	f000 fa46 	bl	70001ad0 <__adddf3>
70001644:	4604      	mov	r4, r0
70001646:	460d      	mov	r5, r1
70001648:	e020      	b.n	7000168c <scalbn+0x8c>
7000164a:	460b      	mov	r3, r1
7000164c:	f3c1 510a 	ubfx	r1, r1, #20, #11
70001650:	f1a1 0636 	sub.w	r6, r1, #54	; 0x36
70001654:	19b9      	adds	r1, r7, r6
70001656:	f240 72fe 	movw	r2, #2046	; 0x7fe
7000165a:	4291      	cmp	r1, r2
7000165c:	dd0e      	ble.n	7000167c <scalbn+0x7c>
7000165e:	f005 4400 	and.w	r4, r5, #2147483648	; 0x80000000
70001662:	f044 41fc 	orr.w	r1, r4, #2113929216	; 0x7e000000
70001666:	4822      	ldr	r0, [pc, #136]	; (700016f0 <scalbn+0xf0>)
70001668:	f441 115f 	orr.w	r1, r1, #3653632	; 0x37c000
7000166c:	f441 5110 	orr.w	r1, r1, #9216	; 0x2400
70001670:	a31b      	add	r3, pc, #108	; (adr r3, 700016e0 <scalbn+0xe0>)
70001672:	e9d3 2300 	ldrd	r2, r3, [r3]
70001676:	f041 013c 	orr.w	r1, r1, #60	; 0x3c
7000167a:	e7d9      	b.n	70001630 <scalbn+0x30>
7000167c:	2900      	cmp	r1, #0
7000167e:	dd08      	ble.n	70001692 <scalbn+0x92>
70001680:	f023 43ff 	bic.w	r3, r3, #2139095040	; 0x7f800000
70001684:	f423 03e0 	bic.w	r3, r3, #7340032	; 0x700000
70001688:	ea43 5501 	orr.w	r5, r3, r1, lsl #20
7000168c:	4620      	mov	r0, r4
7000168e:	4629      	mov	r1, r5
70001690:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
70001692:	f111 0f35 	cmn.w	r1, #53	; 0x35
70001696:	da12      	bge.n	700016be <scalbn+0xbe>
70001698:	f24c 3350 	movw	r3, #50000	; 0xc350
7000169c:	429f      	cmp	r7, r3
7000169e:	ea4f 73d5 	mov.w	r3, r5, lsr #31
700016a2:	ea4f 74c3 	mov.w	r4, r3, lsl #31
700016a6:	dcdc      	bgt.n	70001662 <scalbn+0x62>
700016a8:	f044 71d2 	orr.w	r1, r4, #27525120	; 0x1a40000
700016ac:	4811      	ldr	r0, [pc, #68]	; (700016f4 <scalbn+0xf4>)
700016ae:	f441 31b7 	orr.w	r1, r1, #93696	; 0x16e00
700016b2:	a309      	add	r3, pc, #36	; (adr r3, 700016d8 <scalbn+0xd8>)
700016b4:	e9d3 2300 	ldrd	r2, r3, [r3]
700016b8:	f041 011f 	orr.w	r1, r1, #31
700016bc:	e7b8      	b.n	70001630 <scalbn+0x30>
700016be:	f023 43ff 	bic.w	r3, r3, #2139095040	; 0x7f800000
700016c2:	3136      	adds	r1, #54	; 0x36
700016c4:	4620      	mov	r0, r4
700016c6:	2200      	movs	r2, #0
700016c8:	f423 03e0 	bic.w	r3, r3, #7340032	; 0x700000
700016cc:	ea43 5501 	orr.w	r5, r3, r1, lsl #20
700016d0:	4b09      	ldr	r3, [pc, #36]	; (700016f8 <scalbn+0xf8>)
700016d2:	4629      	mov	r1, r5
700016d4:	e7ac      	b.n	70001630 <scalbn+0x30>
700016d6:	bf00      	nop
700016d8:	c2f8f359 	.word	0xc2f8f359
700016dc:	01a56e1f 	.word	0x01a56e1f
700016e0:	8800759c 	.word	0x8800759c
700016e4:	7e37e43c 	.word	0x7e37e43c
700016e8:	43500000 	.word	0x43500000
700016ec:	ffff3cb0 	.word	0xffff3cb0
700016f0:	8800759c 	.word	0x8800759c
700016f4:	c2f8f359 	.word	0xc2f8f359
700016f8:	3c900000 	.word	0x3c900000

700016fc <__errno>:
700016fc:	4b01      	ldr	r3, [pc, #4]	; (70001704 <__errno+0x8>)
700016fe:	6818      	ldr	r0, [r3, #0]
70001700:	4770      	bx	lr
70001702:	bf00      	nop
70001704:	70002ac8 	.word	0x70002ac8
70001708:	b570      	push	{r4, r5, r6, lr}
7000170a:	f04f 0cff 	mov.w	ip, #255	; 0xff
7000170e:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
70001712:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
70001716:	bf1d      	ittte	ne
70001718:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
7000171c:	ea94 0f0c 	teqne	r4, ip
70001720:	ea95 0f0c 	teqne	r5, ip
70001724:	f000 f8de 	bleq	700018e4 <__errno+0x1e8>
70001728:	442c      	add	r4, r5
7000172a:	ea81 0603 	eor.w	r6, r1, r3
7000172e:	ea21 514c 	bic.w	r1, r1, ip, lsl #21
70001732:	ea23 534c 	bic.w	r3, r3, ip, lsl #21
70001736:	ea50 3501 	orrs.w	r5, r0, r1, lsl #12
7000173a:	bf18      	it	ne
7000173c:	ea52 3503 	orrsne.w	r5, r2, r3, lsl #12
70001740:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70001744:	f443 1380 	orr.w	r3, r3, #1048576	; 0x100000
70001748:	d038      	beq.n	700017bc <__errno+0xc0>
7000174a:	fba0 ce02 	umull	ip, lr, r0, r2
7000174e:	f04f 0500 	mov.w	r5, #0
70001752:	fbe1 e502 	umlal	lr, r5, r1, r2
70001756:	f006 4200 	and.w	r2, r6, #2147483648	; 0x80000000
7000175a:	fbe0 e503 	umlal	lr, r5, r0, r3
7000175e:	f04f 0600 	mov.w	r6, #0
70001762:	fbe1 5603 	umlal	r5, r6, r1, r3
70001766:	f09c 0f00 	teq	ip, #0
7000176a:	bf18      	it	ne
7000176c:	f04e 0e01 	orrne.w	lr, lr, #1
70001770:	f1a4 04ff 	sub.w	r4, r4, #255	; 0xff
70001774:	f5b6 7f00 	cmp.w	r6, #512	; 0x200
70001778:	f564 7440 	sbc.w	r4, r4, #768	; 0x300
7000177c:	d204      	bcs.n	70001788 <__errno+0x8c>
7000177e:	ea5f 0e4e 	movs.w	lr, lr, lsl #1
70001782:	416d      	adcs	r5, r5
70001784:	eb46 0606 	adc.w	r6, r6, r6
70001788:	ea42 21c6 	orr.w	r1, r2, r6, lsl #11
7000178c:	ea41 5155 	orr.w	r1, r1, r5, lsr #21
70001790:	ea4f 20c5 	mov.w	r0, r5, lsl #11
70001794:	ea40 505e 	orr.w	r0, r0, lr, lsr #21
70001798:	ea4f 2ece 	mov.w	lr, lr, lsl #11
7000179c:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
700017a0:	bf88      	it	hi
700017a2:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
700017a6:	d81e      	bhi.n	700017e6 <__errno+0xea>
700017a8:	f1be 4f00 	cmp.w	lr, #2147483648	; 0x80000000
700017ac:	bf08      	it	eq
700017ae:	ea5f 0e50 	movseq.w	lr, r0, lsr #1
700017b2:	f150 0000 	adcs.w	r0, r0, #0
700017b6:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
700017ba:	bd70      	pop	{r4, r5, r6, pc}
700017bc:	f006 4600 	and.w	r6, r6, #2147483648	; 0x80000000
700017c0:	ea46 0101 	orr.w	r1, r6, r1
700017c4:	ea40 0002 	orr.w	r0, r0, r2
700017c8:	ea81 0103 	eor.w	r1, r1, r3
700017cc:	ebb4 045c 	subs.w	r4, r4, ip, lsr #1
700017d0:	bfc2      	ittt	gt
700017d2:	ebd4 050c 	rsbsgt	r5, r4, ip
700017d6:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
700017da:	bd70      	popgt	{r4, r5, r6, pc}
700017dc:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
700017e0:	f04f 0e00 	mov.w	lr, #0
700017e4:	3c01      	subs	r4, #1
700017e6:	f300 80ab 	bgt.w	70001940 <__errno+0x244>
700017ea:	f114 0f36 	cmn.w	r4, #54	; 0x36
700017ee:	bfde      	ittt	le
700017f0:	2000      	movle	r0, #0
700017f2:	f001 4100 	andle.w	r1, r1, #2147483648	; 0x80000000
700017f6:	bd70      	pople	{r4, r5, r6, pc}
700017f8:	f1c4 0400 	rsb	r4, r4, #0
700017fc:	3c20      	subs	r4, #32
700017fe:	da35      	bge.n	7000186c <__errno+0x170>
70001800:	340c      	adds	r4, #12
70001802:	dc1b      	bgt.n	7000183c <__errno+0x140>
70001804:	f104 0414 	add.w	r4, r4, #20
70001808:	f1c4 0520 	rsb	r5, r4, #32
7000180c:	fa00 f305 	lsl.w	r3, r0, r5
70001810:	fa20 f004 	lsr.w	r0, r0, r4
70001814:	fa01 f205 	lsl.w	r2, r1, r5
70001818:	ea40 0002 	orr.w	r0, r0, r2
7000181c:	f001 4200 	and.w	r2, r1, #2147483648	; 0x80000000
70001820:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
70001824:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
70001828:	fa21 f604 	lsr.w	r6, r1, r4
7000182c:	eb42 0106 	adc.w	r1, r2, r6
70001830:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70001834:	bf08      	it	eq
70001836:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
7000183a:	bd70      	pop	{r4, r5, r6, pc}
7000183c:	f1c4 040c 	rsb	r4, r4, #12
70001840:	f1c4 0520 	rsb	r5, r4, #32
70001844:	fa00 f304 	lsl.w	r3, r0, r4
70001848:	fa20 f005 	lsr.w	r0, r0, r5
7000184c:	fa01 f204 	lsl.w	r2, r1, r4
70001850:	ea40 0002 	orr.w	r0, r0, r2
70001854:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70001858:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
7000185c:	f141 0100 	adc.w	r1, r1, #0
70001860:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70001864:	bf08      	it	eq
70001866:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
7000186a:	bd70      	pop	{r4, r5, r6, pc}
7000186c:	f1c4 0520 	rsb	r5, r4, #32
70001870:	fa00 f205 	lsl.w	r2, r0, r5
70001874:	ea4e 0e02 	orr.w	lr, lr, r2
70001878:	fa20 f304 	lsr.w	r3, r0, r4
7000187c:	fa01 f205 	lsl.w	r2, r1, r5
70001880:	ea43 0302 	orr.w	r3, r3, r2
70001884:	fa21 f004 	lsr.w	r0, r1, r4
70001888:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
7000188c:	fa21 f204 	lsr.w	r2, r1, r4
70001890:	ea20 0002 	bic.w	r0, r0, r2
70001894:	eb00 70d3 	add.w	r0, r0, r3, lsr #31
70001898:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
7000189c:	bf08      	it	eq
7000189e:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
700018a2:	bd70      	pop	{r4, r5, r6, pc}
700018a4:	f094 0f00 	teq	r4, #0
700018a8:	d10f      	bne.n	700018ca <__errno+0x1ce>
700018aa:	f001 4600 	and.w	r6, r1, #2147483648	; 0x80000000
700018ae:	0040      	lsls	r0, r0, #1
700018b0:	eb41 0101 	adc.w	r1, r1, r1
700018b4:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
700018b8:	bf08      	it	eq
700018ba:	3c01      	subeq	r4, #1
700018bc:	d0f7      	beq.n	700018ae <__errno+0x1b2>
700018be:	ea41 0106 	orr.w	r1, r1, r6
700018c2:	f095 0f00 	teq	r5, #0
700018c6:	bf18      	it	ne
700018c8:	4770      	bxne	lr
700018ca:	f003 4600 	and.w	r6, r3, #2147483648	; 0x80000000
700018ce:	0052      	lsls	r2, r2, #1
700018d0:	eb43 0303 	adc.w	r3, r3, r3
700018d4:	f413 1f80 	tst.w	r3, #1048576	; 0x100000
700018d8:	bf08      	it	eq
700018da:	3d01      	subeq	r5, #1
700018dc:	d0f7      	beq.n	700018ce <__errno+0x1d2>
700018de:	ea43 0306 	orr.w	r3, r3, r6
700018e2:	4770      	bx	lr
700018e4:	ea94 0f0c 	teq	r4, ip
700018e8:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
700018ec:	bf18      	it	ne
700018ee:	ea95 0f0c 	teqne	r5, ip
700018f2:	d00c      	beq.n	7000190e <__errno+0x212>
700018f4:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
700018f8:	bf18      	it	ne
700018fa:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
700018fe:	d1d1      	bne.n	700018a4 <__errno+0x1a8>
70001900:	ea81 0103 	eor.w	r1, r1, r3
70001904:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70001908:	f04f 0000 	mov.w	r0, #0
7000190c:	bd70      	pop	{r4, r5, r6, pc}
7000190e:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
70001912:	bf06      	itte	eq
70001914:	4610      	moveq	r0, r2
70001916:	4619      	moveq	r1, r3
70001918:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
7000191c:	d019      	beq.n	70001952 <__errno+0x256>
7000191e:	ea94 0f0c 	teq	r4, ip
70001922:	d102      	bne.n	7000192a <__errno+0x22e>
70001924:	ea50 3601 	orrs.w	r6, r0, r1, lsl #12
70001928:	d113      	bne.n	70001952 <__errno+0x256>
7000192a:	ea95 0f0c 	teq	r5, ip
7000192e:	d105      	bne.n	7000193c <__errno+0x240>
70001930:	ea52 3603 	orrs.w	r6, r2, r3, lsl #12
70001934:	bf1c      	itt	ne
70001936:	4610      	movne	r0, r2
70001938:	4619      	movne	r1, r3
7000193a:	d10a      	bne.n	70001952 <__errno+0x256>
7000193c:	ea81 0103 	eor.w	r1, r1, r3
70001940:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70001944:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
70001948:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
7000194c:	f04f 0000 	mov.w	r0, #0
70001950:	bd70      	pop	{r4, r5, r6, pc}
70001952:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
70001956:	f441 0178 	orr.w	r1, r1, #16252928	; 0xf80000
7000195a:	bd70      	pop	{r4, r5, r6, pc}
7000195c:	f04f 0cff 	mov.w	ip, #255	; 0xff
70001960:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70001964:	bf1e      	ittt	ne
70001966:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
7000196a:	ea92 0f0c 	teqne	r2, ip
7000196e:	ea93 0f0c 	teqne	r3, ip
70001972:	d06f      	beq.n	70001a54 <__errno+0x358>
70001974:	441a      	add	r2, r3
70001976:	ea80 0c01 	eor.w	ip, r0, r1
7000197a:	0240      	lsls	r0, r0, #9
7000197c:	bf18      	it	ne
7000197e:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70001982:	d01e      	beq.n	700019c2 <__errno+0x2c6>
70001984:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70001988:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
7000198c:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70001990:	fba0 3101 	umull	r3, r1, r0, r1
70001994:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70001998:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
7000199c:	bf3e      	ittt	cc
7000199e:	0049      	lslcc	r1, r1, #1
700019a0:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
700019a4:	005b      	lslcc	r3, r3, #1
700019a6:	ea40 0001 	orr.w	r0, r0, r1
700019aa:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
700019ae:	2afd      	cmp	r2, #253	; 0xfd
700019b0:	d81d      	bhi.n	700019ee <__errno+0x2f2>
700019b2:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
700019b6:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
700019ba:	bf08      	it	eq
700019bc:	f020 0001 	biceq.w	r0, r0, #1
700019c0:	4770      	bx	lr
700019c2:	f090 0f00 	teq	r0, #0
700019c6:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
700019ca:	bf08      	it	eq
700019cc:	0249      	lsleq	r1, r1, #9
700019ce:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
700019d2:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
700019d6:	3a7f      	subs	r2, #127	; 0x7f
700019d8:	bfc2      	ittt	gt
700019da:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
700019de:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
700019e2:	4770      	bxgt	lr
700019e4:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700019e8:	f04f 0300 	mov.w	r3, #0
700019ec:	3a01      	subs	r2, #1
700019ee:	dc5d      	bgt.n	70001aac <__errno+0x3b0>
700019f0:	f112 0f19 	cmn.w	r2, #25
700019f4:	bfdc      	itt	le
700019f6:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
700019fa:	4770      	bxle	lr
700019fc:	f1c2 0200 	rsb	r2, r2, #0
70001a00:	0041      	lsls	r1, r0, #1
70001a02:	fa21 f102 	lsr.w	r1, r1, r2
70001a06:	f1c2 0220 	rsb	r2, r2, #32
70001a0a:	fa00 fc02 	lsl.w	ip, r0, r2
70001a0e:	ea5f 0031 	movs.w	r0, r1, rrx
70001a12:	f140 0000 	adc.w	r0, r0, #0
70001a16:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70001a1a:	bf08      	it	eq
70001a1c:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70001a20:	4770      	bx	lr
70001a22:	f092 0f00 	teq	r2, #0
70001a26:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70001a2a:	bf02      	ittt	eq
70001a2c:	0040      	lsleq	r0, r0, #1
70001a2e:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70001a32:	3a01      	subeq	r2, #1
70001a34:	d0f9      	beq.n	70001a2a <__errno+0x32e>
70001a36:	ea40 000c 	orr.w	r0, r0, ip
70001a3a:	f093 0f00 	teq	r3, #0
70001a3e:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70001a42:	bf02      	ittt	eq
70001a44:	0049      	lsleq	r1, r1, #1
70001a46:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70001a4a:	3b01      	subeq	r3, #1
70001a4c:	d0f9      	beq.n	70001a42 <__errno+0x346>
70001a4e:	ea41 010c 	orr.w	r1, r1, ip
70001a52:	e78f      	b.n	70001974 <__errno+0x278>
70001a54:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70001a58:	ea92 0f0c 	teq	r2, ip
70001a5c:	bf18      	it	ne
70001a5e:	ea93 0f0c 	teqne	r3, ip
70001a62:	d00a      	beq.n	70001a7a <__errno+0x37e>
70001a64:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70001a68:	bf18      	it	ne
70001a6a:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70001a6e:	d1d8      	bne.n	70001a22 <__errno+0x326>
70001a70:	ea80 0001 	eor.w	r0, r0, r1
70001a74:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70001a78:	4770      	bx	lr
70001a7a:	f090 0f00 	teq	r0, #0
70001a7e:	bf17      	itett	ne
70001a80:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70001a84:	4608      	moveq	r0, r1
70001a86:	f091 0f00 	teqne	r1, #0
70001a8a:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70001a8e:	d014      	beq.n	70001aba <__errno+0x3be>
70001a90:	ea92 0f0c 	teq	r2, ip
70001a94:	d101      	bne.n	70001a9a <__errno+0x39e>
70001a96:	0242      	lsls	r2, r0, #9
70001a98:	d10f      	bne.n	70001aba <__errno+0x3be>
70001a9a:	ea93 0f0c 	teq	r3, ip
70001a9e:	d103      	bne.n	70001aa8 <__errno+0x3ac>
70001aa0:	024b      	lsls	r3, r1, #9
70001aa2:	bf18      	it	ne
70001aa4:	4608      	movne	r0, r1
70001aa6:	d108      	bne.n	70001aba <__errno+0x3be>
70001aa8:	ea80 0001 	eor.w	r0, r0, r1
70001aac:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70001ab0:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70001ab4:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001ab8:	4770      	bx	lr
70001aba:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70001abe:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70001ac2:	4770      	bx	lr

70001ac4 <__aeabi_drsub>:
70001ac4:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000
70001ac8:	e002      	b.n	70001ad0 <__adddf3>
70001aca:	bf00      	nop

70001acc <__aeabi_dsub>:
70001acc:	f083 4300 	eor.w	r3, r3, #2147483648	; 0x80000000

70001ad0 <__adddf3>:
70001ad0:	b530      	push	{r4, r5, lr}
70001ad2:	ea4f 0441 	mov.w	r4, r1, lsl #1
70001ad6:	ea4f 0543 	mov.w	r5, r3, lsl #1
70001ada:	ea94 0f05 	teq	r4, r5
70001ade:	bf08      	it	eq
70001ae0:	ea90 0f02 	teqeq	r0, r2
70001ae4:	bf1f      	itttt	ne
70001ae6:	ea54 0c00 	orrsne.w	ip, r4, r0
70001aea:	ea55 0c02 	orrsne.w	ip, r5, r2
70001aee:	ea7f 5c64 	mvnsne.w	ip, r4, asr #21
70001af2:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70001af6:	f000 80e2 	beq.w	70001cbe <__adddf3+0x1ee>
70001afa:	ea4f 5454 	mov.w	r4, r4, lsr #21
70001afe:	ebd4 5555 	rsbs	r5, r4, r5, lsr #21
70001b02:	bfb8      	it	lt
70001b04:	426d      	neglt	r5, r5
70001b06:	dd0c      	ble.n	70001b22 <__adddf3+0x52>
70001b08:	442c      	add	r4, r5
70001b0a:	ea80 0202 	eor.w	r2, r0, r2
70001b0e:	ea81 0303 	eor.w	r3, r1, r3
70001b12:	ea82 0000 	eor.w	r0, r2, r0
70001b16:	ea83 0101 	eor.w	r1, r3, r1
70001b1a:	ea80 0202 	eor.w	r2, r0, r2
70001b1e:	ea81 0303 	eor.w	r3, r1, r3
70001b22:	2d36      	cmp	r5, #54	; 0x36
70001b24:	bf88      	it	hi
70001b26:	bd30      	pophi	{r4, r5, pc}
70001b28:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70001b2c:	ea4f 3101 	mov.w	r1, r1, lsl #12
70001b30:	f44f 1c80 	mov.w	ip, #1048576	; 0x100000
70001b34:	ea4c 3111 	orr.w	r1, ip, r1, lsr #12
70001b38:	d002      	beq.n	70001b40 <__adddf3+0x70>
70001b3a:	4240      	negs	r0, r0
70001b3c:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70001b40:	f013 4f00 	tst.w	r3, #2147483648	; 0x80000000
70001b44:	ea4f 3303 	mov.w	r3, r3, lsl #12
70001b48:	ea4c 3313 	orr.w	r3, ip, r3, lsr #12
70001b4c:	d002      	beq.n	70001b54 <__adddf3+0x84>
70001b4e:	4252      	negs	r2, r2
70001b50:	eb63 0343 	sbc.w	r3, r3, r3, lsl #1
70001b54:	ea94 0f05 	teq	r4, r5
70001b58:	f000 80a7 	beq.w	70001caa <__adddf3+0x1da>
70001b5c:	f1a4 0401 	sub.w	r4, r4, #1
70001b60:	f1d5 0e20 	rsbs	lr, r5, #32
70001b64:	db0d      	blt.n	70001b82 <__adddf3+0xb2>
70001b66:	fa02 fc0e 	lsl.w	ip, r2, lr
70001b6a:	fa22 f205 	lsr.w	r2, r2, r5
70001b6e:	1880      	adds	r0, r0, r2
70001b70:	f141 0100 	adc.w	r1, r1, #0
70001b74:	fa03 f20e 	lsl.w	r2, r3, lr
70001b78:	1880      	adds	r0, r0, r2
70001b7a:	fa43 f305 	asr.w	r3, r3, r5
70001b7e:	4159      	adcs	r1, r3
70001b80:	e00e      	b.n	70001ba0 <__adddf3+0xd0>
70001b82:	f1a5 0520 	sub.w	r5, r5, #32
70001b86:	f10e 0e20 	add.w	lr, lr, #32
70001b8a:	2a01      	cmp	r2, #1
70001b8c:	fa03 fc0e 	lsl.w	ip, r3, lr
70001b90:	bf28      	it	cs
70001b92:	f04c 0c02 	orrcs.w	ip, ip, #2
70001b96:	fa43 f305 	asr.w	r3, r3, r5
70001b9a:	18c0      	adds	r0, r0, r3
70001b9c:	eb51 71e3 	adcs.w	r1, r1, r3, asr #31
70001ba0:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70001ba4:	d507      	bpl.n	70001bb6 <__adddf3+0xe6>
70001ba6:	f04f 0e00 	mov.w	lr, #0
70001baa:	f1dc 0c00 	rsbs	ip, ip, #0
70001bae:	eb7e 0000 	sbcs.w	r0, lr, r0
70001bb2:	eb6e 0101 	sbc.w	r1, lr, r1
70001bb6:	f5b1 1f80 	cmp.w	r1, #1048576	; 0x100000
70001bba:	d31b      	bcc.n	70001bf4 <__adddf3+0x124>
70001bbc:	f5b1 1f00 	cmp.w	r1, #2097152	; 0x200000
70001bc0:	d30c      	bcc.n	70001bdc <__adddf3+0x10c>
70001bc2:	0849      	lsrs	r1, r1, #1
70001bc4:	ea5f 0030 	movs.w	r0, r0, rrx
70001bc8:	ea4f 0c3c 	mov.w	ip, ip, rrx
70001bcc:	f104 0401 	add.w	r4, r4, #1
70001bd0:	ea4f 5244 	mov.w	r2, r4, lsl #21
70001bd4:	f512 0f80 	cmn.w	r2, #4194304	; 0x400000
70001bd8:	f080 809a 	bcs.w	70001d10 <__adddf3+0x240>
70001bdc:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70001be0:	bf08      	it	eq
70001be2:	ea5f 0c50 	movseq.w	ip, r0, lsr #1
70001be6:	f150 0000 	adcs.w	r0, r0, #0
70001bea:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
70001bee:	ea41 0105 	orr.w	r1, r1, r5
70001bf2:	bd30      	pop	{r4, r5, pc}
70001bf4:	ea5f 0c4c 	movs.w	ip, ip, lsl #1
70001bf8:	4140      	adcs	r0, r0
70001bfa:	eb41 0101 	adc.w	r1, r1, r1
70001bfe:	3c01      	subs	r4, #1
70001c00:	bf28      	it	cs
70001c02:	f5b1 1f80 	cmpcs.w	r1, #1048576	; 0x100000
70001c06:	d2e9      	bcs.n	70001bdc <__adddf3+0x10c>
70001c08:	f091 0f00 	teq	r1, #0
70001c0c:	bf04      	itt	eq
70001c0e:	4601      	moveq	r1, r0
70001c10:	2000      	moveq	r0, #0
70001c12:	fab1 f381 	clz	r3, r1
70001c16:	bf08      	it	eq
70001c18:	3320      	addeq	r3, #32
70001c1a:	f1a3 030b 	sub.w	r3, r3, #11
70001c1e:	f1b3 0220 	subs.w	r2, r3, #32
70001c22:	da0c      	bge.n	70001c3e <__adddf3+0x16e>
70001c24:	320c      	adds	r2, #12
70001c26:	dd08      	ble.n	70001c3a <__adddf3+0x16a>
70001c28:	f102 0c14 	add.w	ip, r2, #20
70001c2c:	f1c2 020c 	rsb	r2, r2, #12
70001c30:	fa01 f00c 	lsl.w	r0, r1, ip
70001c34:	fa21 f102 	lsr.w	r1, r1, r2
70001c38:	e00c      	b.n	70001c54 <__adddf3+0x184>
70001c3a:	f102 0214 	add.w	r2, r2, #20
70001c3e:	bfd8      	it	le
70001c40:	f1c2 0c20 	rsble	ip, r2, #32
70001c44:	fa01 f102 	lsl.w	r1, r1, r2
70001c48:	fa20 fc0c 	lsr.w	ip, r0, ip
70001c4c:	bfdc      	itt	le
70001c4e:	ea41 010c 	orrle.w	r1, r1, ip
70001c52:	4090      	lslle	r0, r2
70001c54:	1ae4      	subs	r4, r4, r3
70001c56:	bfa2      	ittt	ge
70001c58:	eb01 5104 	addge.w	r1, r1, r4, lsl #20
70001c5c:	4329      	orrge	r1, r5
70001c5e:	bd30      	popge	{r4, r5, pc}
70001c60:	ea6f 0404 	mvn.w	r4, r4
70001c64:	3c1f      	subs	r4, #31
70001c66:	da1c      	bge.n	70001ca2 <__adddf3+0x1d2>
70001c68:	340c      	adds	r4, #12
70001c6a:	dc0e      	bgt.n	70001c8a <__adddf3+0x1ba>
70001c6c:	f104 0414 	add.w	r4, r4, #20
70001c70:	f1c4 0220 	rsb	r2, r4, #32
70001c74:	fa20 f004 	lsr.w	r0, r0, r4
70001c78:	fa01 f302 	lsl.w	r3, r1, r2
70001c7c:	ea40 0003 	orr.w	r0, r0, r3
70001c80:	fa21 f304 	lsr.w	r3, r1, r4
70001c84:	ea45 0103 	orr.w	r1, r5, r3
70001c88:	bd30      	pop	{r4, r5, pc}
70001c8a:	f1c4 040c 	rsb	r4, r4, #12
70001c8e:	f1c4 0220 	rsb	r2, r4, #32
70001c92:	fa20 f002 	lsr.w	r0, r0, r2
70001c96:	fa01 f304 	lsl.w	r3, r1, r4
70001c9a:	ea40 0003 	orr.w	r0, r0, r3
70001c9e:	4629      	mov	r1, r5
70001ca0:	bd30      	pop	{r4, r5, pc}
70001ca2:	fa21 f004 	lsr.w	r0, r1, r4
70001ca6:	4629      	mov	r1, r5
70001ca8:	bd30      	pop	{r4, r5, pc}
70001caa:	f094 0f00 	teq	r4, #0
70001cae:	f483 1380 	eor.w	r3, r3, #1048576	; 0x100000
70001cb2:	bf06      	itte	eq
70001cb4:	f481 1180 	eoreq.w	r1, r1, #1048576	; 0x100000
70001cb8:	3401      	addeq	r4, #1
70001cba:	3d01      	subne	r5, #1
70001cbc:	e74e      	b.n	70001b5c <__adddf3+0x8c>
70001cbe:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70001cc2:	bf18      	it	ne
70001cc4:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70001cc8:	d029      	beq.n	70001d1e <__adddf3+0x24e>
70001cca:	ea94 0f05 	teq	r4, r5
70001cce:	bf08      	it	eq
70001cd0:	ea90 0f02 	teqeq	r0, r2
70001cd4:	d005      	beq.n	70001ce2 <__adddf3+0x212>
70001cd6:	ea54 0c00 	orrs.w	ip, r4, r0
70001cda:	bf04      	itt	eq
70001cdc:	4619      	moveq	r1, r3
70001cde:	4610      	moveq	r0, r2
70001ce0:	bd30      	pop	{r4, r5, pc}
70001ce2:	ea91 0f03 	teq	r1, r3
70001ce6:	bf1e      	ittt	ne
70001ce8:	2100      	movne	r1, #0
70001cea:	2000      	movne	r0, #0
70001cec:	bd30      	popne	{r4, r5, pc}
70001cee:	ea5f 5c54 	movs.w	ip, r4, lsr #21
70001cf2:	d105      	bne.n	70001d00 <__adddf3+0x230>
70001cf4:	0040      	lsls	r0, r0, #1
70001cf6:	4149      	adcs	r1, r1
70001cf8:	bf28      	it	cs
70001cfa:	f041 4100 	orrcs.w	r1, r1, #2147483648	; 0x80000000
70001cfe:	bd30      	pop	{r4, r5, pc}
70001d00:	f514 0480 	adds.w	r4, r4, #4194304	; 0x400000
70001d04:	bf3c      	itt	cc
70001d06:	f501 1180 	addcc.w	r1, r1, #1048576	; 0x100000
70001d0a:	bd30      	popcc	{r4, r5, pc}
70001d0c:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70001d10:	f045 41fe 	orr.w	r1, r5, #2130706432	; 0x7f000000
70001d14:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
70001d18:	f04f 0000 	mov.w	r0, #0
70001d1c:	bd30      	pop	{r4, r5, pc}
70001d1e:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70001d22:	bf1a      	itte	ne
70001d24:	4619      	movne	r1, r3
70001d26:	4610      	movne	r0, r2
70001d28:	ea7f 5c65 	mvnseq.w	ip, r5, asr #21
70001d2c:	bf1c      	itt	ne
70001d2e:	460b      	movne	r3, r1
70001d30:	4602      	movne	r2, r0
70001d32:	ea50 3401 	orrs.w	r4, r0, r1, lsl #12
70001d36:	bf06      	itte	eq
70001d38:	ea52 3503 	orrseq.w	r5, r2, r3, lsl #12
70001d3c:	ea91 0f03 	teqeq	r1, r3
70001d40:	f441 2100 	orrne.w	r1, r1, #524288	; 0x80000
70001d44:	bd30      	pop	{r4, r5, pc}
70001d46:	bf00      	nop

70001d48 <__aeabi_ui2d>:
70001d48:	f090 0f00 	teq	r0, #0
70001d4c:	bf04      	itt	eq
70001d4e:	2100      	moveq	r1, #0
70001d50:	4770      	bxeq	lr
70001d52:	b530      	push	{r4, r5, lr}
70001d54:	f44f 6480 	mov.w	r4, #1024	; 0x400
70001d58:	f104 0432 	add.w	r4, r4, #50	; 0x32
70001d5c:	f04f 0500 	mov.w	r5, #0
70001d60:	f04f 0100 	mov.w	r1, #0
70001d64:	e750      	b.n	70001c08 <__adddf3+0x138>
70001d66:	bf00      	nop

70001d68 <__aeabi_i2d>:
70001d68:	f090 0f00 	teq	r0, #0
70001d6c:	bf04      	itt	eq
70001d6e:	2100      	moveq	r1, #0
70001d70:	4770      	bxeq	lr
70001d72:	b530      	push	{r4, r5, lr}
70001d74:	f44f 6480 	mov.w	r4, #1024	; 0x400
70001d78:	f104 0432 	add.w	r4, r4, #50	; 0x32
70001d7c:	f010 4500 	ands.w	r5, r0, #2147483648	; 0x80000000
70001d80:	bf48      	it	mi
70001d82:	4240      	negmi	r0, r0
70001d84:	f04f 0100 	mov.w	r1, #0
70001d88:	e73e      	b.n	70001c08 <__adddf3+0x138>
70001d8a:	bf00      	nop

70001d8c <__aeabi_f2d>:
70001d8c:	0042      	lsls	r2, r0, #1
70001d8e:	ea4f 01e2 	mov.w	r1, r2, asr #3
70001d92:	ea4f 0131 	mov.w	r1, r1, rrx
70001d96:	ea4f 7002 	mov.w	r0, r2, lsl #28
70001d9a:	bf1f      	itttt	ne
70001d9c:	f012 437f 	andsne.w	r3, r2, #4278190080	; 0xff000000
70001da0:	f093 4f7f 	teqne	r3, #4278190080	; 0xff000000
70001da4:	f081 5160 	eorne.w	r1, r1, #939524096	; 0x38000000
70001da8:	4770      	bxne	lr
70001daa:	f032 427f 	bics.w	r2, r2, #4278190080	; 0xff000000
70001dae:	bf08      	it	eq
70001db0:	4770      	bxeq	lr
70001db2:	f093 4f7f 	teq	r3, #4278190080	; 0xff000000
70001db6:	bf04      	itt	eq
70001db8:	f441 2100 	orreq.w	r1, r1, #524288	; 0x80000
70001dbc:	4770      	bxeq	lr
70001dbe:	b530      	push	{r4, r5, lr}
70001dc0:	f44f 7460 	mov.w	r4, #896	; 0x380
70001dc4:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70001dc8:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
70001dcc:	e71c      	b.n	70001c08 <__adddf3+0x138>
70001dce:	bf00      	nop

70001dd0 <__aeabi_ul2d>:
70001dd0:	ea50 0201 	orrs.w	r2, r0, r1
70001dd4:	bf08      	it	eq
70001dd6:	4770      	bxeq	lr
70001dd8:	b530      	push	{r4, r5, lr}
70001dda:	f04f 0500 	mov.w	r5, #0
70001dde:	e00a      	b.n	70001df6 <__aeabi_l2d+0x16>

70001de0 <__aeabi_l2d>:
70001de0:	ea50 0201 	orrs.w	r2, r0, r1
70001de4:	bf08      	it	eq
70001de6:	4770      	bxeq	lr
70001de8:	b530      	push	{r4, r5, lr}
70001dea:	f011 4500 	ands.w	r5, r1, #2147483648	; 0x80000000
70001dee:	d502      	bpl.n	70001df6 <__aeabi_l2d+0x16>
70001df0:	4240      	negs	r0, r0
70001df2:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70001df6:	f44f 6480 	mov.w	r4, #1024	; 0x400
70001dfa:	f104 0432 	add.w	r4, r4, #50	; 0x32
70001dfe:	ea5f 5c91 	movs.w	ip, r1, lsr #22
70001e02:	f43f aed8 	beq.w	70001bb6 <__adddf3+0xe6>
70001e06:	f04f 0203 	mov.w	r2, #3
70001e0a:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70001e0e:	bf18      	it	ne
70001e10:	3203      	addne	r2, #3
70001e12:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70001e16:	bf18      	it	ne
70001e18:	3203      	addne	r2, #3
70001e1a:	eb02 02dc 	add.w	r2, r2, ip, lsr #3
70001e1e:	f1c2 0320 	rsb	r3, r2, #32
70001e22:	fa00 fc03 	lsl.w	ip, r0, r3
70001e26:	fa20 f002 	lsr.w	r0, r0, r2
70001e2a:	fa01 fe03 	lsl.w	lr, r1, r3
70001e2e:	ea40 000e 	orr.w	r0, r0, lr
70001e32:	fa21 f102 	lsr.w	r1, r1, r2
70001e36:	4414      	add	r4, r2
70001e38:	e6bd      	b.n	70001bb6 <__adddf3+0xe6>
70001e3a:	bf00      	nop

70001e3c <__aeabi_dmul>:
70001e3c:	b570      	push	{r4, r5, r6, lr}
70001e3e:	f04f 0cff 	mov.w	ip, #255	; 0xff
70001e42:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
70001e46:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
70001e4a:	bf1d      	ittte	ne
70001e4c:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
70001e50:	ea94 0f0c 	teqne	r4, ip
70001e54:	ea95 0f0c 	teqne	r5, ip
70001e58:	f000 f8de 	bleq	70002018 <__aeabi_dmul+0x1dc>
70001e5c:	442c      	add	r4, r5
70001e5e:	ea81 0603 	eor.w	r6, r1, r3
70001e62:	ea21 514c 	bic.w	r1, r1, ip, lsl #21
70001e66:	ea23 534c 	bic.w	r3, r3, ip, lsl #21
70001e6a:	ea50 3501 	orrs.w	r5, r0, r1, lsl #12
70001e6e:	bf18      	it	ne
70001e70:	ea52 3503 	orrsne.w	r5, r2, r3, lsl #12
70001e74:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70001e78:	f443 1380 	orr.w	r3, r3, #1048576	; 0x100000
70001e7c:	d038      	beq.n	70001ef0 <__aeabi_dmul+0xb4>
70001e7e:	fba0 ce02 	umull	ip, lr, r0, r2
70001e82:	f04f 0500 	mov.w	r5, #0
70001e86:	fbe1 e502 	umlal	lr, r5, r1, r2
70001e8a:	f006 4200 	and.w	r2, r6, #2147483648	; 0x80000000
70001e8e:	fbe0 e503 	umlal	lr, r5, r0, r3
70001e92:	f04f 0600 	mov.w	r6, #0
70001e96:	fbe1 5603 	umlal	r5, r6, r1, r3
70001e9a:	f09c 0f00 	teq	ip, #0
70001e9e:	bf18      	it	ne
70001ea0:	f04e 0e01 	orrne.w	lr, lr, #1
70001ea4:	f1a4 04ff 	sub.w	r4, r4, #255	; 0xff
70001ea8:	f5b6 7f00 	cmp.w	r6, #512	; 0x200
70001eac:	f564 7440 	sbc.w	r4, r4, #768	; 0x300
70001eb0:	d204      	bcs.n	70001ebc <__aeabi_dmul+0x80>
70001eb2:	ea5f 0e4e 	movs.w	lr, lr, lsl #1
70001eb6:	416d      	adcs	r5, r5
70001eb8:	eb46 0606 	adc.w	r6, r6, r6
70001ebc:	ea42 21c6 	orr.w	r1, r2, r6, lsl #11
70001ec0:	ea41 5155 	orr.w	r1, r1, r5, lsr #21
70001ec4:	ea4f 20c5 	mov.w	r0, r5, lsl #11
70001ec8:	ea40 505e 	orr.w	r0, r0, lr, lsr #21
70001ecc:	ea4f 2ece 	mov.w	lr, lr, lsl #11
70001ed0:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
70001ed4:	bf88      	it	hi
70001ed6:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
70001eda:	d81e      	bhi.n	70001f1a <__aeabi_dmul+0xde>
70001edc:	f1be 4f00 	cmp.w	lr, #2147483648	; 0x80000000
70001ee0:	bf08      	it	eq
70001ee2:	ea5f 0e50 	movseq.w	lr, r0, lsr #1
70001ee6:	f150 0000 	adcs.w	r0, r0, #0
70001eea:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
70001eee:	bd70      	pop	{r4, r5, r6, pc}
70001ef0:	f006 4600 	and.w	r6, r6, #2147483648	; 0x80000000
70001ef4:	ea46 0101 	orr.w	r1, r6, r1
70001ef8:	ea40 0002 	orr.w	r0, r0, r2
70001efc:	ea81 0103 	eor.w	r1, r1, r3
70001f00:	ebb4 045c 	subs.w	r4, r4, ip, lsr #1
70001f04:	bfc2      	ittt	gt
70001f06:	ebd4 050c 	rsbsgt	r5, r4, ip
70001f0a:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
70001f0e:	bd70      	popgt	{r4, r5, r6, pc}
70001f10:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70001f14:	f04f 0e00 	mov.w	lr, #0
70001f18:	3c01      	subs	r4, #1
70001f1a:	f300 80ab 	bgt.w	70002074 <__aeabi_dmul+0x238>
70001f1e:	f114 0f36 	cmn.w	r4, #54	; 0x36
70001f22:	bfde      	ittt	le
70001f24:	2000      	movle	r0, #0
70001f26:	f001 4100 	andle.w	r1, r1, #2147483648	; 0x80000000
70001f2a:	bd70      	pople	{r4, r5, r6, pc}
70001f2c:	f1c4 0400 	rsb	r4, r4, #0
70001f30:	3c20      	subs	r4, #32
70001f32:	da35      	bge.n	70001fa0 <__aeabi_dmul+0x164>
70001f34:	340c      	adds	r4, #12
70001f36:	dc1b      	bgt.n	70001f70 <__aeabi_dmul+0x134>
70001f38:	f104 0414 	add.w	r4, r4, #20
70001f3c:	f1c4 0520 	rsb	r5, r4, #32
70001f40:	fa00 f305 	lsl.w	r3, r0, r5
70001f44:	fa20 f004 	lsr.w	r0, r0, r4
70001f48:	fa01 f205 	lsl.w	r2, r1, r5
70001f4c:	ea40 0002 	orr.w	r0, r0, r2
70001f50:	f001 4200 	and.w	r2, r1, #2147483648	; 0x80000000
70001f54:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
70001f58:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
70001f5c:	fa21 f604 	lsr.w	r6, r1, r4
70001f60:	eb42 0106 	adc.w	r1, r2, r6
70001f64:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70001f68:	bf08      	it	eq
70001f6a:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70001f6e:	bd70      	pop	{r4, r5, r6, pc}
70001f70:	f1c4 040c 	rsb	r4, r4, #12
70001f74:	f1c4 0520 	rsb	r5, r4, #32
70001f78:	fa00 f304 	lsl.w	r3, r0, r4
70001f7c:	fa20 f005 	lsr.w	r0, r0, r5
70001f80:	fa01 f204 	lsl.w	r2, r1, r4
70001f84:	ea40 0002 	orr.w	r0, r0, r2
70001f88:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70001f8c:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
70001f90:	f141 0100 	adc.w	r1, r1, #0
70001f94:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70001f98:	bf08      	it	eq
70001f9a:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70001f9e:	bd70      	pop	{r4, r5, r6, pc}
70001fa0:	f1c4 0520 	rsb	r5, r4, #32
70001fa4:	fa00 f205 	lsl.w	r2, r0, r5
70001fa8:	ea4e 0e02 	orr.w	lr, lr, r2
70001fac:	fa20 f304 	lsr.w	r3, r0, r4
70001fb0:	fa01 f205 	lsl.w	r2, r1, r5
70001fb4:	ea43 0302 	orr.w	r3, r3, r2
70001fb8:	fa21 f004 	lsr.w	r0, r1, r4
70001fbc:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70001fc0:	fa21 f204 	lsr.w	r2, r1, r4
70001fc4:	ea20 0002 	bic.w	r0, r0, r2
70001fc8:	eb00 70d3 	add.w	r0, r0, r3, lsr #31
70001fcc:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70001fd0:	bf08      	it	eq
70001fd2:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70001fd6:	bd70      	pop	{r4, r5, r6, pc}
70001fd8:	f094 0f00 	teq	r4, #0
70001fdc:	d10f      	bne.n	70001ffe <__aeabi_dmul+0x1c2>
70001fde:	f001 4600 	and.w	r6, r1, #2147483648	; 0x80000000
70001fe2:	0040      	lsls	r0, r0, #1
70001fe4:	eb41 0101 	adc.w	r1, r1, r1
70001fe8:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
70001fec:	bf08      	it	eq
70001fee:	3c01      	subeq	r4, #1
70001ff0:	d0f7      	beq.n	70001fe2 <__aeabi_dmul+0x1a6>
70001ff2:	ea41 0106 	orr.w	r1, r1, r6
70001ff6:	f095 0f00 	teq	r5, #0
70001ffa:	bf18      	it	ne
70001ffc:	4770      	bxne	lr
70001ffe:	f003 4600 	and.w	r6, r3, #2147483648	; 0x80000000
70002002:	0052      	lsls	r2, r2, #1
70002004:	eb43 0303 	adc.w	r3, r3, r3
70002008:	f413 1f80 	tst.w	r3, #1048576	; 0x100000
7000200c:	bf08      	it	eq
7000200e:	3d01      	subeq	r5, #1
70002010:	d0f7      	beq.n	70002002 <__aeabi_dmul+0x1c6>
70002012:	ea43 0306 	orr.w	r3, r3, r6
70002016:	4770      	bx	lr
70002018:	ea94 0f0c 	teq	r4, ip
7000201c:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
70002020:	bf18      	it	ne
70002022:	ea95 0f0c 	teqne	r5, ip
70002026:	d00c      	beq.n	70002042 <__aeabi_dmul+0x206>
70002028:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
7000202c:	bf18      	it	ne
7000202e:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
70002032:	d1d1      	bne.n	70001fd8 <__aeabi_dmul+0x19c>
70002034:	ea81 0103 	eor.w	r1, r1, r3
70002038:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
7000203c:	f04f 0000 	mov.w	r0, #0
70002040:	bd70      	pop	{r4, r5, r6, pc}
70002042:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
70002046:	bf06      	itte	eq
70002048:	4610      	moveq	r0, r2
7000204a:	4619      	moveq	r1, r3
7000204c:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
70002050:	d019      	beq.n	70002086 <__aeabi_dmul+0x24a>
70002052:	ea94 0f0c 	teq	r4, ip
70002056:	d102      	bne.n	7000205e <__aeabi_dmul+0x222>
70002058:	ea50 3601 	orrs.w	r6, r0, r1, lsl #12
7000205c:	d113      	bne.n	70002086 <__aeabi_dmul+0x24a>
7000205e:	ea95 0f0c 	teq	r5, ip
70002062:	d105      	bne.n	70002070 <__aeabi_dmul+0x234>
70002064:	ea52 3603 	orrs.w	r6, r2, r3, lsl #12
70002068:	bf1c      	itt	ne
7000206a:	4610      	movne	r0, r2
7000206c:	4619      	movne	r1, r3
7000206e:	d10a      	bne.n	70002086 <__aeabi_dmul+0x24a>
70002070:	ea81 0103 	eor.w	r1, r1, r3
70002074:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70002078:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
7000207c:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
70002080:	f04f 0000 	mov.w	r0, #0
70002084:	bd70      	pop	{r4, r5, r6, pc}
70002086:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
7000208a:	f441 0178 	orr.w	r1, r1, #16252928	; 0xf80000
7000208e:	bd70      	pop	{r4, r5, r6, pc}

70002090 <__aeabi_ddiv>:
70002090:	b570      	push	{r4, r5, r6, lr}
70002092:	f04f 0cff 	mov.w	ip, #255	; 0xff
70002096:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
7000209a:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
7000209e:	bf1d      	ittte	ne
700020a0:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
700020a4:	ea94 0f0c 	teqne	r4, ip
700020a8:	ea95 0f0c 	teqne	r5, ip
700020ac:	f000 f8a7 	bleq	700021fe <__aeabi_ddiv+0x16e>
700020b0:	eba4 0405 	sub.w	r4, r4, r5
700020b4:	ea81 0e03 	eor.w	lr, r1, r3
700020b8:	ea52 3503 	orrs.w	r5, r2, r3, lsl #12
700020bc:	ea4f 3101 	mov.w	r1, r1, lsl #12
700020c0:	f000 8088 	beq.w	700021d4 <__aeabi_ddiv+0x144>
700020c4:	ea4f 3303 	mov.w	r3, r3, lsl #12
700020c8:	f04f 5580 	mov.w	r5, #268435456	; 0x10000000
700020cc:	ea45 1313 	orr.w	r3, r5, r3, lsr #4
700020d0:	ea43 6312 	orr.w	r3, r3, r2, lsr #24
700020d4:	ea4f 2202 	mov.w	r2, r2, lsl #8
700020d8:	ea45 1511 	orr.w	r5, r5, r1, lsr #4
700020dc:	ea45 6510 	orr.w	r5, r5, r0, lsr #24
700020e0:	ea4f 2600 	mov.w	r6, r0, lsl #8
700020e4:	f00e 4100 	and.w	r1, lr, #2147483648	; 0x80000000
700020e8:	429d      	cmp	r5, r3
700020ea:	bf08      	it	eq
700020ec:	4296      	cmpeq	r6, r2
700020ee:	f144 04fd 	adc.w	r4, r4, #253	; 0xfd
700020f2:	f504 7440 	add.w	r4, r4, #768	; 0x300
700020f6:	d202      	bcs.n	700020fe <__aeabi_ddiv+0x6e>
700020f8:	085b      	lsrs	r3, r3, #1
700020fa:	ea4f 0232 	mov.w	r2, r2, rrx
700020fe:	1ab6      	subs	r6, r6, r2
70002100:	eb65 0503 	sbc.w	r5, r5, r3
70002104:	085b      	lsrs	r3, r3, #1
70002106:	ea4f 0232 	mov.w	r2, r2, rrx
7000210a:	f44f 1080 	mov.w	r0, #1048576	; 0x100000
7000210e:	f44f 2c00 	mov.w	ip, #524288	; 0x80000
70002112:	ebb6 0e02 	subs.w	lr, r6, r2
70002116:	eb75 0e03 	sbcs.w	lr, r5, r3
7000211a:	bf22      	ittt	cs
7000211c:	1ab6      	subcs	r6, r6, r2
7000211e:	4675      	movcs	r5, lr
70002120:	ea40 000c 	orrcs.w	r0, r0, ip
70002124:	085b      	lsrs	r3, r3, #1
70002126:	ea4f 0232 	mov.w	r2, r2, rrx
7000212a:	ebb6 0e02 	subs.w	lr, r6, r2
7000212e:	eb75 0e03 	sbcs.w	lr, r5, r3
70002132:	bf22      	ittt	cs
70002134:	1ab6      	subcs	r6, r6, r2
70002136:	4675      	movcs	r5, lr
70002138:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
7000213c:	085b      	lsrs	r3, r3, #1
7000213e:	ea4f 0232 	mov.w	r2, r2, rrx
70002142:	ebb6 0e02 	subs.w	lr, r6, r2
70002146:	eb75 0e03 	sbcs.w	lr, r5, r3
7000214a:	bf22      	ittt	cs
7000214c:	1ab6      	subcs	r6, r6, r2
7000214e:	4675      	movcs	r5, lr
70002150:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
70002154:	085b      	lsrs	r3, r3, #1
70002156:	ea4f 0232 	mov.w	r2, r2, rrx
7000215a:	ebb6 0e02 	subs.w	lr, r6, r2
7000215e:	eb75 0e03 	sbcs.w	lr, r5, r3
70002162:	bf22      	ittt	cs
70002164:	1ab6      	subcs	r6, r6, r2
70002166:	4675      	movcs	r5, lr
70002168:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
7000216c:	ea55 0e06 	orrs.w	lr, r5, r6
70002170:	d018      	beq.n	700021a4 <__aeabi_ddiv+0x114>
70002172:	ea4f 1505 	mov.w	r5, r5, lsl #4
70002176:	ea45 7516 	orr.w	r5, r5, r6, lsr #28
7000217a:	ea4f 1606 	mov.w	r6, r6, lsl #4
7000217e:	ea4f 03c3 	mov.w	r3, r3, lsl #3
70002182:	ea43 7352 	orr.w	r3, r3, r2, lsr #29
70002186:	ea4f 02c2 	mov.w	r2, r2, lsl #3
7000218a:	ea5f 1c1c 	movs.w	ip, ip, lsr #4
7000218e:	d1c0      	bne.n	70002112 <__aeabi_ddiv+0x82>
70002190:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
70002194:	d10b      	bne.n	700021ae <__aeabi_ddiv+0x11e>
70002196:	ea41 0100 	orr.w	r1, r1, r0
7000219a:	f04f 0000 	mov.w	r0, #0
7000219e:	f04f 4c00 	mov.w	ip, #2147483648	; 0x80000000
700021a2:	e7b6      	b.n	70002112 <__aeabi_ddiv+0x82>
700021a4:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
700021a8:	bf04      	itt	eq
700021aa:	4301      	orreq	r1, r0
700021ac:	2000      	moveq	r0, #0
700021ae:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
700021b2:	bf88      	it	hi
700021b4:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
700021b8:	f63f aeaf 	bhi.w	70001f1a <__aeabi_dmul+0xde>
700021bc:	ebb5 0c03 	subs.w	ip, r5, r3
700021c0:	bf04      	itt	eq
700021c2:	ebb6 0c02 	subseq.w	ip, r6, r2
700021c6:	ea5f 0c50 	movseq.w	ip, r0, lsr #1
700021ca:	f150 0000 	adcs.w	r0, r0, #0
700021ce:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
700021d2:	bd70      	pop	{r4, r5, r6, pc}
700021d4:	f00e 4e00 	and.w	lr, lr, #2147483648	; 0x80000000
700021d8:	ea4e 3111 	orr.w	r1, lr, r1, lsr #12
700021dc:	eb14 045c 	adds.w	r4, r4, ip, lsr #1
700021e0:	bfc2      	ittt	gt
700021e2:	ebd4 050c 	rsbsgt	r5, r4, ip
700021e6:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
700021ea:	bd70      	popgt	{r4, r5, r6, pc}
700021ec:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
700021f0:	f04f 0e00 	mov.w	lr, #0
700021f4:	3c01      	subs	r4, #1
700021f6:	e690      	b.n	70001f1a <__aeabi_dmul+0xde>
700021f8:	ea45 0e06 	orr.w	lr, r5, r6
700021fc:	e68d      	b.n	70001f1a <__aeabi_dmul+0xde>
700021fe:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
70002202:	ea94 0f0c 	teq	r4, ip
70002206:	bf08      	it	eq
70002208:	ea95 0f0c 	teqeq	r5, ip
7000220c:	f43f af3b 	beq.w	70002086 <__aeabi_dmul+0x24a>
70002210:	ea94 0f0c 	teq	r4, ip
70002214:	d10a      	bne.n	7000222c <__aeabi_ddiv+0x19c>
70002216:	ea50 3401 	orrs.w	r4, r0, r1, lsl #12
7000221a:	f47f af34 	bne.w	70002086 <__aeabi_dmul+0x24a>
7000221e:	ea95 0f0c 	teq	r5, ip
70002222:	f47f af25 	bne.w	70002070 <__aeabi_dmul+0x234>
70002226:	4610      	mov	r0, r2
70002228:	4619      	mov	r1, r3
7000222a:	e72c      	b.n	70002086 <__aeabi_dmul+0x24a>
7000222c:	ea95 0f0c 	teq	r5, ip
70002230:	d106      	bne.n	70002240 <__aeabi_ddiv+0x1b0>
70002232:	ea52 3503 	orrs.w	r5, r2, r3, lsl #12
70002236:	f43f aefd 	beq.w	70002034 <__aeabi_dmul+0x1f8>
7000223a:	4610      	mov	r0, r2
7000223c:	4619      	mov	r1, r3
7000223e:	e722      	b.n	70002086 <__aeabi_dmul+0x24a>
70002240:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
70002244:	bf18      	it	ne
70002246:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
7000224a:	f47f aec5 	bne.w	70001fd8 <__aeabi_dmul+0x19c>
7000224e:	ea50 0441 	orrs.w	r4, r0, r1, lsl #1
70002252:	f47f af0d 	bne.w	70002070 <__aeabi_dmul+0x234>
70002256:	ea52 0543 	orrs.w	r5, r2, r3, lsl #1
7000225a:	f47f aeeb 	bne.w	70002034 <__aeabi_dmul+0x1f8>
7000225e:	e712      	b.n	70002086 <__aeabi_dmul+0x24a>

70002260 <__gedf2>:
70002260:	f04f 3cff 	mov.w	ip, #4294967295
70002264:	e006      	b.n	70002274 <__cmpdf2+0x4>
70002266:	bf00      	nop

70002268 <__ledf2>:
70002268:	f04f 0c01 	mov.w	ip, #1
7000226c:	e002      	b.n	70002274 <__cmpdf2+0x4>
7000226e:	bf00      	nop

70002270 <__cmpdf2>:
70002270:	f04f 0c01 	mov.w	ip, #1
70002274:	f84d cd04 	str.w	ip, [sp, #-4]!
70002278:	ea4f 0c41 	mov.w	ip, r1, lsl #1
7000227c:	ea7f 5c6c 	mvns.w	ip, ip, asr #21
70002280:	ea4f 0c43 	mov.w	ip, r3, lsl #1
70002284:	bf18      	it	ne
70002286:	ea7f 5c6c 	mvnsne.w	ip, ip, asr #21
7000228a:	d01b      	beq.n	700022c4 <__cmpdf2+0x54>
7000228c:	b001      	add	sp, #4
7000228e:	ea50 0c41 	orrs.w	ip, r0, r1, lsl #1
70002292:	bf0c      	ite	eq
70002294:	ea52 0c43 	orrseq.w	ip, r2, r3, lsl #1
70002298:	ea91 0f03 	teqne	r1, r3
7000229c:	bf02      	ittt	eq
7000229e:	ea90 0f02 	teqeq	r0, r2
700022a2:	2000      	moveq	r0, #0
700022a4:	4770      	bxeq	lr
700022a6:	f110 0f00 	cmn.w	r0, #0
700022aa:	ea91 0f03 	teq	r1, r3
700022ae:	bf58      	it	pl
700022b0:	4299      	cmppl	r1, r3
700022b2:	bf08      	it	eq
700022b4:	4290      	cmpeq	r0, r2
700022b6:	bf2c      	ite	cs
700022b8:	17d8      	asrcs	r0, r3, #31
700022ba:	ea6f 70e3 	mvncc.w	r0, r3, asr #31
700022be:	f040 0001 	orr.w	r0, r0, #1
700022c2:	4770      	bx	lr
700022c4:	ea4f 0c41 	mov.w	ip, r1, lsl #1
700022c8:	ea7f 5c6c 	mvns.w	ip, ip, asr #21
700022cc:	d102      	bne.n	700022d4 <__cmpdf2+0x64>
700022ce:	ea50 3c01 	orrs.w	ip, r0, r1, lsl #12
700022d2:	d107      	bne.n	700022e4 <__cmpdf2+0x74>
700022d4:	ea4f 0c43 	mov.w	ip, r3, lsl #1
700022d8:	ea7f 5c6c 	mvns.w	ip, ip, asr #21
700022dc:	d1d6      	bne.n	7000228c <__cmpdf2+0x1c>
700022de:	ea52 3c03 	orrs.w	ip, r2, r3, lsl #12
700022e2:	d0d3      	beq.n	7000228c <__cmpdf2+0x1c>
700022e4:	f85d 0b04 	ldr.w	r0, [sp], #4
700022e8:	4770      	bx	lr
700022ea:	bf00      	nop

700022ec <__aeabi_cdrcmple>:
700022ec:	4684      	mov	ip, r0
700022ee:	4610      	mov	r0, r2
700022f0:	4662      	mov	r2, ip
700022f2:	468c      	mov	ip, r1
700022f4:	4619      	mov	r1, r3
700022f6:	4663      	mov	r3, ip
700022f8:	e000      	b.n	700022fc <__aeabi_cdcmpeq>
700022fa:	bf00      	nop

700022fc <__aeabi_cdcmpeq>:
700022fc:	b501      	push	{r0, lr}
700022fe:	f7ff ffb7 	bl	70002270 <__cmpdf2>
70002302:	2800      	cmp	r0, #0
70002304:	bf48      	it	mi
70002306:	f110 0f00 	cmnmi.w	r0, #0
7000230a:	bd01      	pop	{r0, pc}

7000230c <__aeabi_dcmpeq>:
7000230c:	f84d ed08 	str.w	lr, [sp, #-8]!
70002310:	f7ff fff4 	bl	700022fc <__aeabi_cdcmpeq>
70002314:	bf0c      	ite	eq
70002316:	2001      	moveq	r0, #1
70002318:	2000      	movne	r0, #0
7000231a:	f85d fb08 	ldr.w	pc, [sp], #8
7000231e:	bf00      	nop

70002320 <__aeabi_dcmplt>:
70002320:	f84d ed08 	str.w	lr, [sp, #-8]!
70002324:	f7ff ffea 	bl	700022fc <__aeabi_cdcmpeq>
70002328:	bf34      	ite	cc
7000232a:	2001      	movcc	r0, #1
7000232c:	2000      	movcs	r0, #0
7000232e:	f85d fb08 	ldr.w	pc, [sp], #8
70002332:	bf00      	nop

70002334 <__aeabi_dcmple>:
70002334:	f84d ed08 	str.w	lr, [sp, #-8]!
70002338:	f7ff ffe0 	bl	700022fc <__aeabi_cdcmpeq>
7000233c:	bf94      	ite	ls
7000233e:	2001      	movls	r0, #1
70002340:	2000      	movhi	r0, #0
70002342:	f85d fb08 	ldr.w	pc, [sp], #8
70002346:	bf00      	nop

70002348 <__aeabi_dcmpge>:
70002348:	f84d ed08 	str.w	lr, [sp, #-8]!
7000234c:	f7ff ffce 	bl	700022ec <__aeabi_cdrcmple>
70002350:	bf94      	ite	ls
70002352:	2001      	movls	r0, #1
70002354:	2000      	movhi	r0, #0
70002356:	f85d fb08 	ldr.w	pc, [sp], #8
7000235a:	bf00      	nop

7000235c <__aeabi_dcmpgt>:
7000235c:	f84d ed08 	str.w	lr, [sp, #-8]!
70002360:	f7ff ffc4 	bl	700022ec <__aeabi_cdrcmple>
70002364:	bf34      	ite	cc
70002366:	2001      	movcc	r0, #1
70002368:	2000      	movcs	r0, #0
7000236a:	f85d fb08 	ldr.w	pc, [sp], #8
7000236e:	bf00      	nop

70002370 <__aeabi_dcmpun>:
70002370:	ea4f 0c41 	mov.w	ip, r1, lsl #1
70002374:	ea7f 5c6c 	mvns.w	ip, ip, asr #21
70002378:	d102      	bne.n	70002380 <__aeabi_dcmpun+0x10>
7000237a:	ea50 3c01 	orrs.w	ip, r0, r1, lsl #12
7000237e:	d10a      	bne.n	70002396 <__aeabi_dcmpun+0x26>
70002380:	ea4f 0c43 	mov.w	ip, r3, lsl #1
70002384:	ea7f 5c6c 	mvns.w	ip, ip, asr #21
70002388:	d102      	bne.n	70002390 <__aeabi_dcmpun+0x20>
7000238a:	ea52 3c03 	orrs.w	ip, r2, r3, lsl #12
7000238e:	d102      	bne.n	70002396 <__aeabi_dcmpun+0x26>
70002390:	f04f 0000 	mov.w	r0, #0
70002394:	4770      	bx	lr
70002396:	f04f 0001 	mov.w	r0, #1
7000239a:	4770      	bx	lr

7000239c <__aeabi_d2uiz>:
7000239c:	004a      	lsls	r2, r1, #1
7000239e:	d211      	bcs.n	700023c4 <__aeabi_d2uiz+0x28>
700023a0:	f512 1200 	adds.w	r2, r2, #2097152	; 0x200000
700023a4:	d211      	bcs.n	700023ca <__aeabi_d2uiz+0x2e>
700023a6:	d50d      	bpl.n	700023c4 <__aeabi_d2uiz+0x28>
700023a8:	f46f 7378 	mvn.w	r3, #992	; 0x3e0
700023ac:	ebb3 5262 	subs.w	r2, r3, r2, asr #21
700023b0:	d40e      	bmi.n	700023d0 <__aeabi_d2uiz+0x34>
700023b2:	ea4f 23c1 	mov.w	r3, r1, lsl #11
700023b6:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
700023ba:	ea43 5350 	orr.w	r3, r3, r0, lsr #21
700023be:	fa23 f002 	lsr.w	r0, r3, r2
700023c2:	4770      	bx	lr
700023c4:	f04f 0000 	mov.w	r0, #0
700023c8:	4770      	bx	lr
700023ca:	ea50 3001 	orrs.w	r0, r0, r1, lsl #12
700023ce:	d102      	bne.n	700023d6 <__aeabi_d2uiz+0x3a>
700023d0:	f04f 30ff 	mov.w	r0, #4294967295
700023d4:	4770      	bx	lr
700023d6:	f04f 0000 	mov.w	r0, #0
700023da:	4770      	bx	lr

700023dc <__aeabi_d2f>:
700023dc:	ea4f 0241 	mov.w	r2, r1, lsl #1
700023e0:	f1b2 43e0 	subs.w	r3, r2, #1879048192	; 0x70000000
700023e4:	bf24      	itt	cs
700023e6:	f5b3 1c00 	subscs.w	ip, r3, #2097152	; 0x200000
700023ea:	f1dc 5cfe 	rsbscs	ip, ip, #532676608	; 0x1fc00000
700023ee:	d90d      	bls.n	7000240c <__aeabi_d2f+0x30>
700023f0:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
700023f4:	ea4f 02c0 	mov.w	r2, r0, lsl #3
700023f8:	ea4c 7050 	orr.w	r0, ip, r0, lsr #29
700023fc:	f1b2 4f00 	cmp.w	r2, #2147483648	; 0x80000000
70002400:	eb40 0083 	adc.w	r0, r0, r3, lsl #2
70002404:	bf08      	it	eq
70002406:	f020 0001 	biceq.w	r0, r0, #1
7000240a:	4770      	bx	lr
7000240c:	f011 4f80 	tst.w	r1, #1073741824	; 0x40000000
70002410:	d121      	bne.n	70002456 <__aeabi_d2f+0x7a>
70002412:	f113 7238 	adds.w	r2, r3, #48234496	; 0x2e00000
70002416:	bfbc      	itt	lt
70002418:	f001 4000 	andlt.w	r0, r1, #2147483648	; 0x80000000
7000241c:	4770      	bxlt	lr
7000241e:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70002422:	ea4f 5252 	mov.w	r2, r2, lsr #21
70002426:	f1c2 0218 	rsb	r2, r2, #24
7000242a:	f1c2 0c20 	rsb	ip, r2, #32
7000242e:	fa10 f30c 	lsls.w	r3, r0, ip
70002432:	fa20 f002 	lsr.w	r0, r0, r2
70002436:	bf18      	it	ne
70002438:	f040 0001 	orrne.w	r0, r0, #1
7000243c:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70002440:	ea4f 23d3 	mov.w	r3, r3, lsr #11
70002444:	fa03 fc0c 	lsl.w	ip, r3, ip
70002448:	ea40 000c 	orr.w	r0, r0, ip
7000244c:	fa23 f302 	lsr.w	r3, r3, r2
70002450:	ea4f 0343 	mov.w	r3, r3, lsl #1
70002454:	e7cc      	b.n	700023f0 <__aeabi_d2f+0x14>
70002456:	ea7f 5362 	mvns.w	r3, r2, asr #21
7000245a:	d107      	bne.n	7000246c <__aeabi_d2f+0x90>
7000245c:	ea50 3301 	orrs.w	r3, r0, r1, lsl #12
70002460:	bf1e      	ittt	ne
70002462:	f04f 40fe 	movne.w	r0, #2130706432	; 0x7f000000
70002466:	f440 0040 	orrne.w	r0, r0, #12582912	; 0xc00000
7000246a:	4770      	bxne	lr
7000246c:	f001 4000 	and.w	r0, r1, #2147483648	; 0x80000000
70002470:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70002474:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70002478:	4770      	bx	lr
7000247a:	bf00      	nop

7000247c <__aeabi_frsub>:
7000247c:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70002480:	e002      	b.n	70002488 <__addsf3>
70002482:	bf00      	nop

70002484 <__aeabi_fsub>:
70002484:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

70002488 <__addsf3>:
70002488:	0042      	lsls	r2, r0, #1
7000248a:	bf1f      	itttt	ne
7000248c:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70002490:	ea92 0f03 	teqne	r2, r3
70002494:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
70002498:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
7000249c:	d06a      	beq.n	70002574 <__addsf3+0xec>
7000249e:	ea4f 6212 	mov.w	r2, r2, lsr #24
700024a2:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
700024a6:	bfc1      	itttt	gt
700024a8:	18d2      	addgt	r2, r2, r3
700024aa:	4041      	eorgt	r1, r0
700024ac:	4048      	eorgt	r0, r1
700024ae:	4041      	eorgt	r1, r0
700024b0:	bfb8      	it	lt
700024b2:	425b      	neglt	r3, r3
700024b4:	2b19      	cmp	r3, #25
700024b6:	bf88      	it	hi
700024b8:	4770      	bxhi	lr
700024ba:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
700024be:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700024c2:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
700024c6:	bf18      	it	ne
700024c8:	4240      	negne	r0, r0
700024ca:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
700024ce:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
700024d2:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
700024d6:	bf18      	it	ne
700024d8:	4249      	negne	r1, r1
700024da:	ea92 0f03 	teq	r2, r3
700024de:	d03f      	beq.n	70002560 <__addsf3+0xd8>
700024e0:	f1a2 0201 	sub.w	r2, r2, #1
700024e4:	fa41 fc03 	asr.w	ip, r1, r3
700024e8:	eb10 000c 	adds.w	r0, r0, ip
700024ec:	f1c3 0320 	rsb	r3, r3, #32
700024f0:	fa01 f103 	lsl.w	r1, r1, r3
700024f4:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
700024f8:	d502      	bpl.n	70002500 <__addsf3+0x78>
700024fa:	4249      	negs	r1, r1
700024fc:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70002500:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70002504:	d313      	bcc.n	7000252e <__addsf3+0xa6>
70002506:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
7000250a:	d306      	bcc.n	7000251a <__addsf3+0x92>
7000250c:	0840      	lsrs	r0, r0, #1
7000250e:	ea4f 0131 	mov.w	r1, r1, rrx
70002512:	f102 0201 	add.w	r2, r2, #1
70002516:	2afe      	cmp	r2, #254	; 0xfe
70002518:	d251      	bcs.n	700025be <__addsf3+0x136>
7000251a:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
7000251e:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70002522:	bf08      	it	eq
70002524:	f020 0001 	biceq.w	r0, r0, #1
70002528:	ea40 0003 	orr.w	r0, r0, r3
7000252c:	4770      	bx	lr
7000252e:	0049      	lsls	r1, r1, #1
70002530:	eb40 0000 	adc.w	r0, r0, r0
70002534:	3a01      	subs	r2, #1
70002536:	bf28      	it	cs
70002538:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
7000253c:	d2ed      	bcs.n	7000251a <__addsf3+0x92>
7000253e:	fab0 fc80 	clz	ip, r0
70002542:	f1ac 0c08 	sub.w	ip, ip, #8
70002546:	ebb2 020c 	subs.w	r2, r2, ip
7000254a:	fa00 f00c 	lsl.w	r0, r0, ip
7000254e:	bfaa      	itet	ge
70002550:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
70002554:	4252      	neglt	r2, r2
70002556:	4318      	orrge	r0, r3
70002558:	bfbc      	itt	lt
7000255a:	40d0      	lsrlt	r0, r2
7000255c:	4318      	orrlt	r0, r3
7000255e:	4770      	bx	lr
70002560:	f092 0f00 	teq	r2, #0
70002564:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
70002568:	bf06      	itte	eq
7000256a:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
7000256e:	3201      	addeq	r2, #1
70002570:	3b01      	subne	r3, #1
70002572:	e7b5      	b.n	700024e0 <__addsf3+0x58>
70002574:	ea4f 0341 	mov.w	r3, r1, lsl #1
70002578:	ea7f 6c22 	mvns.w	ip, r2, asr #24
7000257c:	bf18      	it	ne
7000257e:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70002582:	d021      	beq.n	700025c8 <__addsf3+0x140>
70002584:	ea92 0f03 	teq	r2, r3
70002588:	d004      	beq.n	70002594 <__addsf3+0x10c>
7000258a:	f092 0f00 	teq	r2, #0
7000258e:	bf08      	it	eq
70002590:	4608      	moveq	r0, r1
70002592:	4770      	bx	lr
70002594:	ea90 0f01 	teq	r0, r1
70002598:	bf1c      	itt	ne
7000259a:	2000      	movne	r0, #0
7000259c:	4770      	bxne	lr
7000259e:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
700025a2:	d104      	bne.n	700025ae <__addsf3+0x126>
700025a4:	0040      	lsls	r0, r0, #1
700025a6:	bf28      	it	cs
700025a8:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
700025ac:	4770      	bx	lr
700025ae:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
700025b2:	bf3c      	itt	cc
700025b4:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
700025b8:	4770      	bxcc	lr
700025ba:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
700025be:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
700025c2:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700025c6:	4770      	bx	lr
700025c8:	ea7f 6222 	mvns.w	r2, r2, asr #24
700025cc:	bf16      	itet	ne
700025ce:	4608      	movne	r0, r1
700025d0:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
700025d4:	4601      	movne	r1, r0
700025d6:	0242      	lsls	r2, r0, #9
700025d8:	bf06      	itte	eq
700025da:	ea5f 2341 	movseq.w	r3, r1, lsl #9
700025de:	ea90 0f01 	teqeq	r0, r1
700025e2:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
700025e6:	4770      	bx	lr

700025e8 <__aeabi_ui2f>:
700025e8:	f04f 0300 	mov.w	r3, #0
700025ec:	e004      	b.n	700025f8 <__aeabi_i2f+0x8>
700025ee:	bf00      	nop

700025f0 <__aeabi_i2f>:
700025f0:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
700025f4:	bf48      	it	mi
700025f6:	4240      	negmi	r0, r0
700025f8:	ea5f 0c00 	movs.w	ip, r0
700025fc:	bf08      	it	eq
700025fe:	4770      	bxeq	lr
70002600:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70002604:	4601      	mov	r1, r0
70002606:	f04f 0000 	mov.w	r0, #0
7000260a:	e01c      	b.n	70002646 <__aeabi_l2f+0x2a>

7000260c <__aeabi_ul2f>:
7000260c:	ea50 0201 	orrs.w	r2, r0, r1
70002610:	bf08      	it	eq
70002612:	4770      	bxeq	lr
70002614:	f04f 0300 	mov.w	r3, #0
70002618:	e00a      	b.n	70002630 <__aeabi_l2f+0x14>
7000261a:	bf00      	nop

7000261c <__aeabi_l2f>:
7000261c:	ea50 0201 	orrs.w	r2, r0, r1
70002620:	bf08      	it	eq
70002622:	4770      	bxeq	lr
70002624:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70002628:	d502      	bpl.n	70002630 <__aeabi_l2f+0x14>
7000262a:	4240      	negs	r0, r0
7000262c:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70002630:	ea5f 0c01 	movs.w	ip, r1
70002634:	bf02      	ittt	eq
70002636:	4684      	moveq	ip, r0
70002638:	4601      	moveq	r1, r0
7000263a:	2000      	moveq	r0, #0
7000263c:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70002640:	bf08      	it	eq
70002642:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70002646:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
7000264a:	fabc f28c 	clz	r2, ip
7000264e:	3a08      	subs	r2, #8
70002650:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
70002654:	db10      	blt.n	70002678 <__aeabi_l2f+0x5c>
70002656:	fa01 fc02 	lsl.w	ip, r1, r2
7000265a:	4463      	add	r3, ip
7000265c:	fa00 fc02 	lsl.w	ip, r0, r2
70002660:	f1c2 0220 	rsb	r2, r2, #32
70002664:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70002668:	fa20 f202 	lsr.w	r2, r0, r2
7000266c:	eb43 0002 	adc.w	r0, r3, r2
70002670:	bf08      	it	eq
70002672:	f020 0001 	biceq.w	r0, r0, #1
70002676:	4770      	bx	lr
70002678:	f102 0220 	add.w	r2, r2, #32
7000267c:	fa01 fc02 	lsl.w	ip, r1, r2
70002680:	f1c2 0220 	rsb	r2, r2, #32
70002684:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
70002688:	fa21 f202 	lsr.w	r2, r1, r2
7000268c:	eb43 0002 	adc.w	r0, r3, r2
70002690:	bf08      	it	eq
70002692:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70002696:	4770      	bx	lr

70002698 <__aeabi_fmul>:
70002698:	f04f 0cff 	mov.w	ip, #255	; 0xff
7000269c:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
700026a0:	bf1e      	ittt	ne
700026a2:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
700026a6:	ea92 0f0c 	teqne	r2, ip
700026aa:	ea93 0f0c 	teqne	r3, ip
700026ae:	d06f      	beq.n	70002790 <__aeabi_fmul+0xf8>
700026b0:	441a      	add	r2, r3
700026b2:	ea80 0c01 	eor.w	ip, r0, r1
700026b6:	0240      	lsls	r0, r0, #9
700026b8:	bf18      	it	ne
700026ba:	ea5f 2141 	movsne.w	r1, r1, lsl #9
700026be:	d01e      	beq.n	700026fe <__aeabi_fmul+0x66>
700026c0:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
700026c4:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
700026c8:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
700026cc:	fba0 3101 	umull	r3, r1, r0, r1
700026d0:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
700026d4:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
700026d8:	bf3e      	ittt	cc
700026da:	0049      	lslcc	r1, r1, #1
700026dc:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
700026e0:	005b      	lslcc	r3, r3, #1
700026e2:	ea40 0001 	orr.w	r0, r0, r1
700026e6:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
700026ea:	2afd      	cmp	r2, #253	; 0xfd
700026ec:	d81d      	bhi.n	7000272a <__aeabi_fmul+0x92>
700026ee:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
700026f2:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
700026f6:	bf08      	it	eq
700026f8:	f020 0001 	biceq.w	r0, r0, #1
700026fc:	4770      	bx	lr
700026fe:	f090 0f00 	teq	r0, #0
70002702:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70002706:	bf08      	it	eq
70002708:	0249      	lsleq	r1, r1, #9
7000270a:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
7000270e:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70002712:	3a7f      	subs	r2, #127	; 0x7f
70002714:	bfc2      	ittt	gt
70002716:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
7000271a:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
7000271e:	4770      	bxgt	lr
70002720:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70002724:	f04f 0300 	mov.w	r3, #0
70002728:	3a01      	subs	r2, #1
7000272a:	dc5d      	bgt.n	700027e8 <__aeabi_fmul+0x150>
7000272c:	f112 0f19 	cmn.w	r2, #25
70002730:	bfdc      	itt	le
70002732:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70002736:	4770      	bxle	lr
70002738:	f1c2 0200 	rsb	r2, r2, #0
7000273c:	0041      	lsls	r1, r0, #1
7000273e:	fa21 f102 	lsr.w	r1, r1, r2
70002742:	f1c2 0220 	rsb	r2, r2, #32
70002746:	fa00 fc02 	lsl.w	ip, r0, r2
7000274a:	ea5f 0031 	movs.w	r0, r1, rrx
7000274e:	f140 0000 	adc.w	r0, r0, #0
70002752:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70002756:	bf08      	it	eq
70002758:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
7000275c:	4770      	bx	lr
7000275e:	f092 0f00 	teq	r2, #0
70002762:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70002766:	bf02      	ittt	eq
70002768:	0040      	lsleq	r0, r0, #1
7000276a:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
7000276e:	3a01      	subeq	r2, #1
70002770:	d0f9      	beq.n	70002766 <__aeabi_fmul+0xce>
70002772:	ea40 000c 	orr.w	r0, r0, ip
70002776:	f093 0f00 	teq	r3, #0
7000277a:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
7000277e:	bf02      	ittt	eq
70002780:	0049      	lsleq	r1, r1, #1
70002782:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70002786:	3b01      	subeq	r3, #1
70002788:	d0f9      	beq.n	7000277e <__aeabi_fmul+0xe6>
7000278a:	ea41 010c 	orr.w	r1, r1, ip
7000278e:	e78f      	b.n	700026b0 <__aeabi_fmul+0x18>
70002790:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70002794:	ea92 0f0c 	teq	r2, ip
70002798:	bf18      	it	ne
7000279a:	ea93 0f0c 	teqne	r3, ip
7000279e:	d00a      	beq.n	700027b6 <__aeabi_fmul+0x11e>
700027a0:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
700027a4:	bf18      	it	ne
700027a6:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
700027aa:	d1d8      	bne.n	7000275e <__aeabi_fmul+0xc6>
700027ac:	ea80 0001 	eor.w	r0, r0, r1
700027b0:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
700027b4:	4770      	bx	lr
700027b6:	f090 0f00 	teq	r0, #0
700027ba:	bf17      	itett	ne
700027bc:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
700027c0:	4608      	moveq	r0, r1
700027c2:	f091 0f00 	teqne	r1, #0
700027c6:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
700027ca:	d014      	beq.n	700027f6 <__aeabi_fmul+0x15e>
700027cc:	ea92 0f0c 	teq	r2, ip
700027d0:	d101      	bne.n	700027d6 <__aeabi_fmul+0x13e>
700027d2:	0242      	lsls	r2, r0, #9
700027d4:	d10f      	bne.n	700027f6 <__aeabi_fmul+0x15e>
700027d6:	ea93 0f0c 	teq	r3, ip
700027da:	d103      	bne.n	700027e4 <__aeabi_fmul+0x14c>
700027dc:	024b      	lsls	r3, r1, #9
700027de:	bf18      	it	ne
700027e0:	4608      	movne	r0, r1
700027e2:	d108      	bne.n	700027f6 <__aeabi_fmul+0x15e>
700027e4:	ea80 0001 	eor.w	r0, r0, r1
700027e8:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
700027ec:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
700027f0:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700027f4:	4770      	bx	lr
700027f6:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
700027fa:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
700027fe:	4770      	bx	lr

70002800 <__aeabi_fdiv>:
70002800:	f04f 0cff 	mov.w	ip, #255	; 0xff
70002804:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70002808:	bf1e      	ittt	ne
7000280a:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
7000280e:	ea92 0f0c 	teqne	r2, ip
70002812:	ea93 0f0c 	teqne	r3, ip
70002816:	d069      	beq.n	700028ec <__aeabi_fdiv+0xec>
70002818:	eba2 0203 	sub.w	r2, r2, r3
7000281c:	ea80 0c01 	eor.w	ip, r0, r1
70002820:	0249      	lsls	r1, r1, #9
70002822:	ea4f 2040 	mov.w	r0, r0, lsl #9
70002826:	d037      	beq.n	70002898 <__aeabi_fdiv+0x98>
70002828:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
7000282c:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70002830:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70002834:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70002838:	428b      	cmp	r3, r1
7000283a:	bf38      	it	cc
7000283c:	005b      	lslcc	r3, r3, #1
7000283e:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70002842:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70002846:	428b      	cmp	r3, r1
70002848:	bf24      	itt	cs
7000284a:	1a5b      	subcs	r3, r3, r1
7000284c:	ea40 000c 	orrcs.w	r0, r0, ip
70002850:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70002854:	bf24      	itt	cs
70002856:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
7000285a:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
7000285e:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70002862:	bf24      	itt	cs
70002864:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
70002868:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
7000286c:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
70002870:	bf24      	itt	cs
70002872:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
70002876:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
7000287a:	011b      	lsls	r3, r3, #4
7000287c:	bf18      	it	ne
7000287e:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70002882:	d1e0      	bne.n	70002846 <__aeabi_fdiv+0x46>
70002884:	2afd      	cmp	r2, #253	; 0xfd
70002886:	f63f af50 	bhi.w	7000272a <__aeabi_fmul+0x92>
7000288a:	428b      	cmp	r3, r1
7000288c:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70002890:	bf08      	it	eq
70002892:	f020 0001 	biceq.w	r0, r0, #1
70002896:	4770      	bx	lr
70002898:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
7000289c:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
700028a0:	327f      	adds	r2, #127	; 0x7f
700028a2:	bfc2      	ittt	gt
700028a4:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
700028a8:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
700028ac:	4770      	bxgt	lr
700028ae:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700028b2:	f04f 0300 	mov.w	r3, #0
700028b6:	3a01      	subs	r2, #1
700028b8:	e737      	b.n	7000272a <__aeabi_fmul+0x92>
700028ba:	f092 0f00 	teq	r2, #0
700028be:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
700028c2:	bf02      	ittt	eq
700028c4:	0040      	lsleq	r0, r0, #1
700028c6:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
700028ca:	3a01      	subeq	r2, #1
700028cc:	d0f9      	beq.n	700028c2 <__aeabi_fdiv+0xc2>
700028ce:	ea40 000c 	orr.w	r0, r0, ip
700028d2:	f093 0f00 	teq	r3, #0
700028d6:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
700028da:	bf02      	ittt	eq
700028dc:	0049      	lsleq	r1, r1, #1
700028de:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
700028e2:	3b01      	subeq	r3, #1
700028e4:	d0f9      	beq.n	700028da <__aeabi_fdiv+0xda>
700028e6:	ea41 010c 	orr.w	r1, r1, ip
700028ea:	e795      	b.n	70002818 <__aeabi_fdiv+0x18>
700028ec:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
700028f0:	ea92 0f0c 	teq	r2, ip
700028f4:	d108      	bne.n	70002908 <__aeabi_fdiv+0x108>
700028f6:	0242      	lsls	r2, r0, #9
700028f8:	f47f af7d 	bne.w	700027f6 <__aeabi_fmul+0x15e>
700028fc:	ea93 0f0c 	teq	r3, ip
70002900:	f47f af70 	bne.w	700027e4 <__aeabi_fmul+0x14c>
70002904:	4608      	mov	r0, r1
70002906:	e776      	b.n	700027f6 <__aeabi_fmul+0x15e>
70002908:	ea93 0f0c 	teq	r3, ip
7000290c:	d104      	bne.n	70002918 <__aeabi_fdiv+0x118>
7000290e:	024b      	lsls	r3, r1, #9
70002910:	f43f af4c 	beq.w	700027ac <__aeabi_fmul+0x114>
70002914:	4608      	mov	r0, r1
70002916:	e76e      	b.n	700027f6 <__aeabi_fmul+0x15e>
70002918:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
7000291c:	bf18      	it	ne
7000291e:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70002922:	d1ca      	bne.n	700028ba <__aeabi_fdiv+0xba>
70002924:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70002928:	f47f af5c 	bne.w	700027e4 <__aeabi_fmul+0x14c>
7000292c:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70002930:	f47f af3c 	bne.w	700027ac <__aeabi_fmul+0x114>
70002934:	e75f      	b.n	700027f6 <__aeabi_fmul+0x15e>
70002936:	bf00      	nop

70002938 <__gesf2>:
70002938:	f04f 3cff 	mov.w	ip, #4294967295
7000293c:	e006      	b.n	7000294c <__cmpsf2+0x4>
7000293e:	bf00      	nop

70002940 <__lesf2>:
70002940:	f04f 0c01 	mov.w	ip, #1
70002944:	e002      	b.n	7000294c <__cmpsf2+0x4>
70002946:	bf00      	nop

70002948 <__cmpsf2>:
70002948:	f04f 0c01 	mov.w	ip, #1
7000294c:	f84d cd04 	str.w	ip, [sp, #-4]!
70002950:	ea4f 0240 	mov.w	r2, r0, lsl #1
70002954:	ea4f 0341 	mov.w	r3, r1, lsl #1
70002958:	ea7f 6c22 	mvns.w	ip, r2, asr #24
7000295c:	bf18      	it	ne
7000295e:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70002962:	d011      	beq.n	70002988 <__cmpsf2+0x40>
70002964:	b001      	add	sp, #4
70002966:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
7000296a:	bf18      	it	ne
7000296c:	ea90 0f01 	teqne	r0, r1
70002970:	bf58      	it	pl
70002972:	ebb2 0003 	subspl.w	r0, r2, r3
70002976:	bf88      	it	hi
70002978:	17c8      	asrhi	r0, r1, #31
7000297a:	bf38      	it	cc
7000297c:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70002980:	bf18      	it	ne
70002982:	f040 0001 	orrne.w	r0, r0, #1
70002986:	4770      	bx	lr
70002988:	ea7f 6c22 	mvns.w	ip, r2, asr #24
7000298c:	d102      	bne.n	70002994 <__cmpsf2+0x4c>
7000298e:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70002992:	d105      	bne.n	700029a0 <__cmpsf2+0x58>
70002994:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70002998:	d1e4      	bne.n	70002964 <__cmpsf2+0x1c>
7000299a:	ea5f 2c41 	movs.w	ip, r1, lsl #9
7000299e:	d0e1      	beq.n	70002964 <__cmpsf2+0x1c>
700029a0:	f85d 0b04 	ldr.w	r0, [sp], #4
700029a4:	4770      	bx	lr
700029a6:	bf00      	nop

700029a8 <__aeabi_cfrcmple>:
700029a8:	4684      	mov	ip, r0
700029aa:	4608      	mov	r0, r1
700029ac:	4661      	mov	r1, ip
700029ae:	e7ff      	b.n	700029b0 <__aeabi_cfcmpeq>

700029b0 <__aeabi_cfcmpeq>:
700029b0:	b50f      	push	{r0, r1, r2, r3, lr}
700029b2:	f7ff ffc9 	bl	70002948 <__cmpsf2>
700029b6:	2800      	cmp	r0, #0
700029b8:	bf48      	it	mi
700029ba:	f110 0f00 	cmnmi.w	r0, #0
700029be:	bd0f      	pop	{r0, r1, r2, r3, pc}

700029c0 <__aeabi_fcmpeq>:
700029c0:	f84d ed08 	str.w	lr, [sp, #-8]!
700029c4:	f7ff fff4 	bl	700029b0 <__aeabi_cfcmpeq>
700029c8:	bf0c      	ite	eq
700029ca:	2001      	moveq	r0, #1
700029cc:	2000      	movne	r0, #0
700029ce:	f85d fb08 	ldr.w	pc, [sp], #8
700029d2:	bf00      	nop

700029d4 <__aeabi_fcmplt>:
700029d4:	f84d ed08 	str.w	lr, [sp, #-8]!
700029d8:	f7ff ffea 	bl	700029b0 <__aeabi_cfcmpeq>
700029dc:	bf34      	ite	cc
700029de:	2001      	movcc	r0, #1
700029e0:	2000      	movcs	r0, #0
700029e2:	f85d fb08 	ldr.w	pc, [sp], #8
700029e6:	bf00      	nop

700029e8 <__aeabi_fcmple>:
700029e8:	f84d ed08 	str.w	lr, [sp, #-8]!
700029ec:	f7ff ffe0 	bl	700029b0 <__aeabi_cfcmpeq>
700029f0:	bf94      	ite	ls
700029f2:	2001      	movls	r0, #1
700029f4:	2000      	movhi	r0, #0
700029f6:	f85d fb08 	ldr.w	pc, [sp], #8
700029fa:	bf00      	nop

700029fc <__aeabi_fcmpge>:
700029fc:	f84d ed08 	str.w	lr, [sp, #-8]!
70002a00:	f7ff ffd2 	bl	700029a8 <__aeabi_cfrcmple>
70002a04:	bf94      	ite	ls
70002a06:	2001      	movls	r0, #1
70002a08:	2000      	movhi	r0, #0
70002a0a:	f85d fb08 	ldr.w	pc, [sp], #8
70002a0e:	bf00      	nop

70002a10 <__aeabi_fcmpgt>:
70002a10:	f84d ed08 	str.w	lr, [sp, #-8]!
70002a14:	f7ff ffc8 	bl	700029a8 <__aeabi_cfrcmple>
70002a18:	bf34      	ite	cc
70002a1a:	2001      	movcc	r0, #1
70002a1c:	2000      	movcs	r0, #0
70002a1e:	f85d fb08 	ldr.w	pc, [sp], #8
70002a22:	bf00      	nop

70002a24 <__aeabi_fcmpun>:
70002a24:	ea4f 0240 	mov.w	r2, r0, lsl #1
70002a28:	ea4f 0341 	mov.w	r3, r1, lsl #1
70002a2c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70002a30:	d102      	bne.n	70002a38 <__aeabi_fcmpun+0x14>
70002a32:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70002a36:	d108      	bne.n	70002a4a <__aeabi_fcmpun+0x26>
70002a38:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70002a3c:	d102      	bne.n	70002a44 <__aeabi_fcmpun+0x20>
70002a3e:	ea5f 2c41 	movs.w	ip, r1, lsl #9
70002a42:	d102      	bne.n	70002a4a <__aeabi_fcmpun+0x26>
70002a44:	f04f 0000 	mov.w	r0, #0
70002a48:	4770      	bx	lr
70002a4a:	f04f 0001 	mov.w	r0, #1
70002a4e:	4770      	bx	lr

70002a50 <__aeabi_f2uiz>:
70002a50:	0042      	lsls	r2, r0, #1
70002a52:	d20e      	bcs.n	70002a72 <__aeabi_f2uiz+0x22>
70002a54:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70002a58:	d30b      	bcc.n	70002a72 <__aeabi_f2uiz+0x22>
70002a5a:	f04f 039e 	mov.w	r3, #158	; 0x9e
70002a5e:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70002a62:	d409      	bmi.n	70002a78 <__aeabi_f2uiz+0x28>
70002a64:	ea4f 2300 	mov.w	r3, r0, lsl #8
70002a68:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70002a6c:	fa23 f002 	lsr.w	r0, r3, r2
70002a70:	4770      	bx	lr
70002a72:	f04f 0000 	mov.w	r0, #0
70002a76:	4770      	bx	lr
70002a78:	f112 0f61 	cmn.w	r2, #97	; 0x61
70002a7c:	d101      	bne.n	70002a82 <__aeabi_f2uiz+0x32>
70002a7e:	0242      	lsls	r2, r0, #9
70002a80:	d102      	bne.n	70002a88 <__aeabi_f2uiz+0x38>
70002a82:	f04f 30ff 	mov.w	r0, #4294967295
70002a86:	4770      	bx	lr
70002a88:	f04f 0000 	mov.w	r0, #0
70002a8c:	4770      	bx	lr
70002a8e:	bf00      	nop

70002a90 <bp>:
70002a90:	0000 0000 0000 3ff0 0000 0000 0000 3ff8     .......?.......?

70002aa0 <dp_l>:
	...
70002aa8:	d006 43cf fdeb 3e4c                         ...C..L>

70002ab0 <dp_h>:
	...
70002ab8:	0000 4000 b803 3fe2                         ...@...?

70002ac0 <_global_impure_ptr>:
70002ac0:	2ad0 7000 0000 0000                         .*.p....

70002ac8 <_impure_ptr>:
70002ac8:	2ad0 7000 0000 0000                         .*.p....

70002ad0 <impure_data>:
70002ad0:	0000 0000 2dbc 7000 2e24 7000 2e8c 7000     .....-.p$..p...p
	...
70002b78:	0001 0000 0000 0000 330e abcd 1234 e66d     .........3..4.m.
70002b88:	deec 0005 000b 0000 0000 0000 0000 0000     ................
	...
