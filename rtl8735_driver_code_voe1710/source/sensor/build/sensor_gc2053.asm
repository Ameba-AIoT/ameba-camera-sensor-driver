
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	29 07 00 70 95 02 00 70                             )..p...p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

7000006c <g_gc2053_i2c_init_regs_asic>:
7000006c:	fe 00 80 00 fe 00 80 00 fe 00 80 00 fe 00 00 00     ................
7000007c:	f2 00 00 00 f3 00 00 00 f4 00 36 00 f5 00 c0 00     ..........6.....
7000008c:	f6 00 44 00 f7 00 01 00 f8 00 2c 00 f9 00 42 00     ..D.......,...B.
7000009c:	fc 00 8e 00 fe 00 00 00 87 00 18 00 ee 00 30 00     ..............0.
700000ac:	d0 00 b7 00 03 00 04 00 04 00 60 00 05 00 04 00     ..........`.....
700000bc:	06 00 4c 00 07 00 00 00 08 00 11 00 09 00 00 00     ..L.............
700000cc:	0a 00 02 00 0b 00 00 00 0c 00 02 00 0d 00 04 00     ................
700000dc:	0e 00 40 00 12 00 e2 00 13 00 16 00 19 00 0a 00     ..@.............
700000ec:	21 00 1c 00 28 00 0a 00 29 00 24 00 2b 00 04 00     !...(...).$.+...
700000fc:	32 00 f8 00 37 00 03 00 39 00 15 00 43 00 07 00     2...7...9...C...
7000010c:	44 00 40 00 46 00 0b 00 4b 00 20 00 4e 00 08 00     D.@.F...K. .N...
7000011c:	55 00 20 00 66 00 05 00 67 00 05 00 77 00 01 00     U. .f...g...w...
7000012c:	78 00 00 00 7c 00 93 00 8c 00 12 00 8d 00 92 00     x...|...........
7000013c:	90 00 00 00 9d 00 10 00 ce 00 7c 00 d2 00 41 00     ..........|...A.
7000014c:	d3 00 dc 00 e6 00 50 00 b6 00 c0 00 b0 00 70 00     ......P.......p.
7000015c:	b1 00 01 00 b2 00 00 00 b3 00 00 00 b4 00 00 00     ................
7000016c:	b8 00 01 00 b9 00 00 00 26 00 30 00 fe 00 01 00     ........&.0.....
7000017c:	40 00 23 00 55 00 07 00 60 00 40 00 fe 00 04 00     @.#.U...`.@.....
7000018c:	14 00 78 00 15 00 78 00 16 00 78 00 17 00 78 00     ..x...x...x...x.
7000019c:	fe 00 01 00 92 00 00 00 94 00 03 00 95 00 04 00     ................
700001ac:	96 00 40 00 97 00 07 00 98 00 88 00 fe 00 01 00     ..@.............
700001bc:	01 00 05 00 02 00 89 00 04 00 01 00 07 00 a6 00     ................
700001cc:	08 00 a9 00 09 00 a8 00 0a 00 a7 00 0b 00 ff 00     ................
700001dc:	0c 00 ff 00 0f 00 00 00 50 00 1c 00 89 00 03 00     ........P.......
700001ec:	fe 00 04 00 28 00 86 00 29 00 86 00 2a 00 86 00     ....(...)...*...
700001fc:	2b 00 68 00 2c 00 68 00 2d 00 68 00 2e 00 68 00     +.h.,.h.-.h...h.
7000020c:	2f 00 68 00 30 00 4f 00 31 00 68 00 32 00 67 00     /.h.0.O.1.h.2.g.
7000021c:	33 00 66 00 34 00 66 00 35 00 66 00 36 00 66 00     3.f.4.f.5.f.6.f.
7000022c:	37 00 66 00 38 00 62 00 39 00 62 00 3a 00 62 00     7.f.8.b.9.b.:.b.
7000023c:	3b 00 62 00 3c 00 62 00 3d 00 62 00 3e 00 62 00     ;.b.<.b.=.b.>.b.
7000024c:	3f 00 62 00 fe 00 01 00 9a 00 06 00 fe 00 00 00     ?.b.............
7000025c:	7b 00 2a 00 23 00 2d 00 fe 00 03 00 01 00 27 00     {.*.#.-.......'.
7000026c:	02 00 5f 00 03 00 b6 00 12 00 80 00 13 00 07 00     .._.............
7000027c:	15 00 12 00 fe 00 00 00 3e 00 91 00                 ........>...

70000288 <real_slave_addr>:
70000288:	37 00 00 00                                         7...

7000028c <slave_addr_list>:
7000028c:	37 00 00 00 3f 00 00 00                             7...?...

70000294 <rts_isp_set_voe_ops>:
70000294:	4b01      	ldr	r3, [pc, #4]	; (7000029c <rts_isp_set_voe_ops+0x8>)
70000296:	6018      	str	r0, [r3, #0]
70000298:	4770      	bx	lr
7000029a:	bf00      	nop
7000029c:	70000048 	.word	0x70000048

700002a0 <isp_driver_is_fpga>:
700002a0:	2000      	movs	r0, #0
700002a2:	4770      	bx	lr

700002a4 <gc2053_get_info>:
700002a4:	b5f0      	push	{r4, r5, r6, r7, lr}
700002a6:	2800      	cmp	r0, #0
700002a8:	f040 809d 	bne.w	700003e6 <gc2053_get_info+0x142>
700002ac:	2900      	cmp	r1, #0
700002ae:	f000 809a 	beq.w	700003e6 <gc2053_get_info+0x142>
700002b2:	f44f 62f0 	mov.w	r2, #1920	; 0x780
700002b6:	f44f 6387 	mov.w	r3, #1080	; 0x438
700002ba:	f44f 757a 	mov.w	r5, #1000	; 0x3e8
700002be:	f241 3488 	movw	r4, #5000	; 0x1388
700002c2:	2603      	movs	r6, #3
700002c4:	f04f 0c64 	mov.w	ip, #100	; 0x64
700002c8:	4f48      	ldr	r7, [pc, #288]	; (700003ec <gc2053_get_info+0x148>)
700002ca:	f04f 0e02 	mov.w	lr, #2
700002ce:	f8c1 c094 	str.w	ip, [r1, #148]	; 0x94
700002d2:	f881 e08c 	strb.w	lr, [r1, #140]	; 0x8c
700002d6:	f881 e150 	strb.w	lr, [r1, #336]	; 0x150
700002da:	7108      	strb	r0, [r1, #4]
700002dc:	f8df e110 	ldr.w	lr, [pc, #272]	; 700003f0 <gc2053_get_info+0x14c>
700002e0:	f881 0098 	strb.w	r0, [r1, #152]	; 0x98
700002e4:	f8c1 00a8 	str.w	r0, [r1, #168]	; 0xa8
700002e8:	f8c1 40ac 	str.w	r4, [r1, #172]	; 0xac
700002ec:	f881 60b0 	strb.w	r6, [r1, #176]	; 0xb0
700002f0:	f881 00c8 	strb.w	r0, [r1, #200]	; 0xc8
700002f4:	e9c1 2302 	strd	r2, r3, [r1, #8]
700002f8:	4a3e      	ldr	r2, [pc, #248]	; (700003f4 <gc2053_get_info+0x150>)
700002fa:	4b3f      	ldr	r3, [pc, #252]	; (700003f8 <gc2053_get_info+0x154>)
700002fc:	6812      	ldr	r2, [r2, #0]
700002fe:	610b      	str	r3, [r1, #16]
70000300:	2301      	movs	r3, #1
70000302:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
70000306:	4a3d      	ldr	r2, [pc, #244]	; (700003fc <gc2053_get_info+0x158>)
70000308:	600b      	str	r3, [r1, #0]
7000030a:	7812      	ldrb	r2, [r2, #0]
7000030c:	f8c1 3090 	str.w	r3, [r1, #144]	; 0x90
70000310:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
70000314:	f240 1201 	movw	r2, #257	; 0x101
70000318:	f881 30a4 	strb.w	r3, [r1, #164]	; 0xa4
7000031c:	f8a1 2086 	strh.w	r2, [r1, #134]	; 0x86
70000320:	2206      	movs	r2, #6
70000322:	f881 30bc 	strb.w	r3, [r1, #188]	; 0xbc
70000326:	f8c1 2088 	str.w	r2, [r1, #136]	; 0x88
7000032a:	e9c1 752d 	strd	r7, r5, [r1, #180]	; 0xb4
7000032e:	e9c1 3530 	strd	r3, r5, [r1, #192]	; 0xc0
70000332:	e9c1 3533 	strd	r3, r5, [r1, #204]	; 0xcc
70000336:	e9c1 3c55 	strd	r3, ip, [r1, #340]	; 0x154
7000033a:	e9c1 0027 	strd	r0, r0, [r1, #156]	; 0x9c
7000033e:	f04f 0c05 	mov.w	ip, #5
70000342:	f881 015c 	strb.w	r0, [r1, #348]	; 0x15c
70000346:	f881 3168 	strb.w	r3, [r1, #360]	; 0x168
7000034a:	f881 6174 	strb.w	r6, [r1, #372]	; 0x174
7000034e:	f881 3180 	strb.w	r3, [r1, #384]	; 0x180
70000352:	f881 018c 	strb.w	r0, [r1, #396]	; 0x18c
70000356:	f8c1 214c 	str.w	r2, [r1, #332]	; 0x14c
7000035a:	f881 0214 	strb.w	r0, [r1, #532]	; 0x214
7000035e:	f8c1 0218 	str.w	r0, [r1, #536]	; 0x218
70000362:	f881 3220 	strb.w	r3, [r1, #544]	; 0x220
70000366:	f8c1 0224 	str.w	r0, [r1, #548]	; 0x224
7000036a:	f8c1 e228 	str.w	lr, [r1, #552]	; 0x228
7000036e:	f881 622c 	strb.w	r6, [r1, #556]	; 0x22c
70000372:	f881 c238 	strb.w	ip, [r1, #568]	; 0x238
70000376:	f881 2244 	strb.w	r2, [r1, #580]	; 0x244
7000037a:	e9c1 755e 	strd	r7, r5, [r1, #376]	; 0x178
7000037e:	e9c1 3561 	strd	r3, r5, [r1, #388]	; 0x184
70000382:	2704      	movs	r7, #4
70000384:	e9c1 3564 	strd	r3, r5, [r1, #400]	; 0x190
70000388:	f242 7510 	movw	r5, #10000	; 0x2710
7000038c:	f881 7250 	strb.w	r7, [r1, #592]	; 0x250
70000390:	e9c1 0058 	strd	r0, r0, [r1, #352]	; 0x160
70000394:	e9c1 045b 	strd	r0, r4, [r1, #364]	; 0x16c
70000398:	f8c1 521c 	str.w	r5, [r1, #540]	; 0x21c
7000039c:	e9c1 058c 	strd	r0, r5, [r1, #560]	; 0x230
700003a0:	e9c1 048f 	strd	r0, r4, [r1, #572]	; 0x23c
700003a4:	e9c1 0492 	strd	r0, r4, [r1, #584]	; 0x248
700003a8:	e9c1 0095 	strd	r0, r0, [r1, #596]	; 0x254
700003ac:	f8c1 2210 	str.w	r2, [r1, #528]	; 0x210
700003b0:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
700003b4:	f881 32e4 	strb.w	r3, [r1, #740]	; 0x2e4
700003b8:	f881 62f0 	strb.w	r6, [r1, #752]	; 0x2f0
700003bc:	f881 c2fc 	strb.w	ip, [r1, #764]	; 0x2fc
700003c0:	f881 2308 	strb.w	r2, [r1, #776]	; 0x308
700003c4:	f881 7314 	strb.w	r7, [r1, #788]	; 0x314
700003c8:	f8c1 22d4 	str.w	r2, [r1, #724]	; 0x2d4
700003cc:	e9c1 05b7 	strd	r0, r5, [r1, #732]	; 0x2dc
700003d0:	e9c1 0eba 	strd	r0, lr, [r1, #744]	; 0x2e8
700003d4:	e9c1 05bd 	strd	r0, r5, [r1, #756]	; 0x2f4
700003d8:	e9c1 04c0 	strd	r0, r4, [r1, #768]	; 0x300
700003dc:	e9c1 04c3 	strd	r0, r4, [r1, #780]	; 0x30c
700003e0:	e9c1 00c6 	strd	r0, r0, [r1, #792]	; 0x318
700003e4:	bdf0      	pop	{r4, r5, r6, r7, pc}
700003e6:	f06f 0015 	mvn.w	r0, #21
700003ea:	e7fb      	b.n	700003e4 <gc2053_get_info+0x140>
700003ec:	019bfcc0 	.word	0x019bfcc0
700003f0:	000186a0 	.word	0x000186a0
700003f4:	70000288 	.word	0x70000288
700003f8:	41f00000 	.word	0x41f00000
700003fc:	7000004c 	.word	0x7000004c

70000400 <gc2053_get_init_info>:
70000400:	b570      	push	{r4, r5, r6, lr}
70000402:	4614      	mov	r4, r2
70000404:	4605      	mov	r5, r0
70000406:	b110      	cbz	r0, 7000040e <gc2053_get_init_info+0xe>
70000408:	f06f 0015 	mvn.w	r0, #21
7000040c:	bd70      	pop	{r4, r5, r6, pc}
7000040e:	2a00      	cmp	r2, #0
70000410:	d0fa      	beq.n	70000408 <gc2053_get_init_info+0x8>
70000412:	780b      	ldrb	r3, [r1, #0]
70000414:	4e1c      	ldr	r6, [pc, #112]	; (70000488 <gc2053_get_init_info+0x88>)
70000416:	68c8      	ldr	r0, [r1, #12]
70000418:	7033      	strb	r3, [r6, #0]
7000041a:	f000 fda7 	bl	70000f6c <__aeabi_f2uiz>
7000041e:	b280      	uxth	r0, r0
70000420:	f000 fb8a 	bl	70000b38 <__aeabi_i2f>
70000424:	4919      	ldr	r1, [pc, #100]	; (7000048c <gc2053_get_init_info+0x8c>)
70000426:	f000 fd6f 	bl	70000f08 <__aeabi_fcmpeq>
7000042a:	2800      	cmp	r0, #0
7000042c:	d0ec      	beq.n	70000408 <gc2053_get_init_info+0x8>
7000042e:	4b18      	ldr	r3, [pc, #96]	; (70000490 <gc2053_get_init_info+0x90>)
70000430:	f44f 62f1 	mov.w	r2, #1928	; 0x788
70000434:	f44f 615c 	mov.w	r1, #3520	; 0xdc0
70000438:	60a5      	str	r5, [r4, #8]
7000043a:	6063      	str	r3, [r4, #4]
7000043c:	2387      	movs	r3, #135	; 0x87
7000043e:	4628      	mov	r0, r5
70000440:	6023      	str	r3, [r4, #0]
70000442:	2302      	movs	r3, #2
70000444:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
70000448:	f240 5303 	movw	r3, #1283	; 0x503
7000044c:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
70000450:	230a      	movs	r3, #10
70000452:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
70000456:	2304      	movs	r3, #4
70000458:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
7000045c:	f44f 6388 	mov.w	r3, #1088	; 0x440
70000460:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
70000464:	2303      	movs	r3, #3
70000466:	e9c4 3522 	strd	r3, r5, [r4, #136]	; 0x88
7000046a:	4b0a      	ldr	r3, [pc, #40]	; (70000494 <gc2053_get_init_info+0x94>)
7000046c:	e9c4 3124 	strd	r3, r1, [r4, #144]	; 0x90
70000470:	f240 4365 	movw	r3, #1125	; 0x465
70000474:	6073      	str	r3, [r6, #4]
70000476:	f8c4 3098 	str.w	r3, [r4, #152]	; 0x98
7000047a:	f248 33d6 	movw	r3, #33750	; 0x83d6
7000047e:	f8c4 309c 	str.w	r3, [r4, #156]	; 0x9c
70000482:	4b05      	ldr	r3, [pc, #20]	; (70000498 <gc2053_get_init_info+0x98>)
70000484:	60b3      	str	r3, [r6, #8]
70000486:	e7c1      	b.n	7000040c <gc2053_get_init_info+0xc>
70000488:	7000004c 	.word	0x7000004c
7000048c:	41f00000 	.word	0x41f00000
70000490:	7000006c 	.word	0x7000006c
70000494:	0714be80 	.word	0x0714be80
70000498:	41ed097b 	.word	0x41ed097b

7000049c <gc2053_start>:
7000049c:	b918      	cbnz	r0, 700004a6 <gc2053_start+0xa>
7000049e:	4b03      	ldr	r3, [pc, #12]	; (700004ac <gc2053_start+0x10>)
700004a0:	2200      	movs	r2, #0
700004a2:	60da      	str	r2, [r3, #12]
700004a4:	4770      	bx	lr
700004a6:	f06f 0015 	mvn.w	r0, #21
700004aa:	4770      	bx	lr
700004ac:	7000004c 	.word	0x7000004c

700004b0 <gc2053_get_tuned_dgain>:
700004b0:	b920      	cbnz	r0, 700004bc <gc2053_get_tuned_dgain+0xc>
700004b2:	b119      	cbz	r1, 700004bc <gc2053_get_tuned_dgain+0xc>
700004b4:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
700004b8:	600b      	str	r3, [r1, #0]
700004ba:	4770      	bx	lr
700004bc:	f06f 0015 	mvn.w	r0, #21
700004c0:	4770      	bx	lr
	...

700004c4 <gc2053_get_exposure_gain_info>:
700004c4:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
700004c8:	4614      	mov	r4, r2
700004ca:	2800      	cmp	r0, #0
700004cc:	d179      	bne.n	700005c2 <gc2053_get_exposure_gain_info+0xfe>
700004ce:	2900      	cmp	r1, #0
700004d0:	d077      	beq.n	700005c2 <gc2053_get_exposure_gain_info+0xfe>
700004d2:	2a00      	cmp	r2, #0
700004d4:	d075      	beq.n	700005c2 <gc2053_get_exposure_gain_info+0xfe>
700004d6:	23fe      	movs	r3, #254	; 0xfe
700004d8:	f8d1 8000 	ldr.w	r8, [r1]
700004dc:	4e3a      	ldr	r6, [pc, #232]	; (700005c8 <gc2053_get_exposure_gain_info+0x104>)
700004de:	698d      	ldr	r5, [r1, #24]
700004e0:	4641      	mov	r1, r8
700004e2:	68f0      	ldr	r0, [r6, #12]
700004e4:	60d3      	str	r3, [r2, #12]
700004e6:	f000 fa71 	bl	700009cc <__aeabi_fsub>
700004ea:	2100      	movs	r1, #0
700004ec:	4607      	mov	r7, r0
700004ee:	f000 fd29 	bl	70000f44 <__aeabi_fcmpge>
700004f2:	2800      	cmp	r0, #0
700004f4:	d05e      	beq.n	700005b4 <gc2053_get_exposure_gain_info+0xf0>
700004f6:	4935      	ldr	r1, [pc, #212]	; (700005cc <gc2053_get_exposure_gain_info+0x108>)
700004f8:	4638      	mov	r0, r7
700004fa:	f000 fd2d 	bl	70000f58 <__aeabi_fcmpgt>
700004fe:	2800      	cmp	r0, #0
70000500:	d05d      	beq.n	700005be <gc2053_get_exposure_gain_info+0xfa>
70000502:	68b1      	ldr	r1, [r6, #8]
70000504:	4640      	mov	r0, r8
70000506:	f000 fc1f 	bl	70000d48 <__aeabi_fdiv>
7000050a:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
7000050e:	f000 fa5f 	bl	700009d0 <__addsf3>
70000512:	f000 fd2b 	bl	70000f6c <__aeabi_f2uiz>
70000516:	f3c0 2307 	ubfx	r3, r0, #8, #8
7000051a:	2103      	movs	r1, #3
7000051c:	b2c0      	uxtb	r0, r0
7000051e:	8463      	strh	r3, [r4, #34]	; 0x22
70000520:	2304      	movs	r3, #4
70000522:	8421      	strh	r1, [r4, #32]
70000524:	86a3      	strh	r3, [r4, #52]	; 0x34
70000526:	86e0      	strh	r0, [r4, #54]	; 0x36
70000528:	f8c6 800c 	str.w	r8, [r6, #12]
7000052c:	2314      	movs	r3, #20
7000052e:	1d22      	adds	r2, r4, #4
70000530:	27fe      	movs	r7, #254	; 0xfe
70000532:	6936      	ldr	r6, [r6, #16]
70000534:	434b      	muls	r3, r1
70000536:	f8df c098 	ldr.w	ip, [pc, #152]	; 700005d0 <gc2053_get_exposure_gain_info+0x10c>
7000053a:	f04f 08b3 	mov.w	r8, #179	; 0xb3
7000053e:	3107      	adds	r1, #7
70000540:	18d0      	adds	r0, r2, r3
70000542:	6087      	str	r7, [r0, #8]
70000544:	2706      	movs	r7, #6
70000546:	f103 0014 	add.w	r0, r3, #20
7000054a:	437e      	muls	r6, r7
7000054c:	4410      	add	r0, r2
7000054e:	eb0c 0706 	add.w	r7, ip, r6
70000552:	f81c 6006 	ldrb.w	r6, [ip, r6]
70000556:	f8a0 8008 	strh.w	r8, [r0, #8]
7000055a:	f04f 0cb4 	mov.w	ip, #180	; 0xb4
7000055e:	f897 e001 	ldrb.w	lr, [r7, #1]
70000562:	f8a0 e00a 	strh.w	lr, [r0, #10]
70000566:	f103 0028 	add.w	r0, r3, #40	; 0x28
7000056a:	4410      	add	r0, r2
7000056c:	f8a0 c008 	strh.w	ip, [r0, #8]
70000570:	f04f 0cb8 	mov.w	ip, #184	; 0xb8
70000574:	8146      	strh	r6, [r0, #10]
70000576:	f103 003c 	add.w	r0, r3, #60	; 0x3c
7000057a:	78be      	ldrb	r6, [r7, #2]
7000057c:	4410      	add	r0, r2
7000057e:	8146      	strh	r6, [r0, #10]
70000580:	f8a0 c008 	strh.w	ip, [r0, #8]
70000584:	f103 0050 	add.w	r0, r3, #80	; 0x50
70000588:	78fe      	ldrb	r6, [r7, #3]
7000058a:	27b9      	movs	r7, #185	; 0xb9
7000058c:	4410      	add	r0, r2
7000058e:	8146      	strh	r6, [r0, #10]
70000590:	2641      	movs	r6, #65	; 0x41
70000592:	8107      	strh	r7, [r0, #8]
70000594:	f103 0064 	add.w	r0, r3, #100	; 0x64
70000598:	3378      	adds	r3, #120	; 0x78
7000059a:	4410      	add	r0, r2
7000059c:	4413      	add	r3, r2
7000059e:	2242      	movs	r2, #66	; 0x42
700005a0:	8106      	strh	r6, [r0, #8]
700005a2:	0a2e      	lsrs	r6, r5, #8
700005a4:	b2ed      	uxtb	r5, r5
700005a6:	8146      	strh	r6, [r0, #10]
700005a8:	2000      	movs	r0, #0
700005aa:	811a      	strh	r2, [r3, #8]
700005ac:	815d      	strh	r5, [r3, #10]
700005ae:	6021      	str	r1, [r4, #0]
700005b0:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
700005b4:	4907      	ldr	r1, [pc, #28]	; (700005d4 <gc2053_get_exposure_gain_info+0x110>)
700005b6:	4638      	mov	r0, r7
700005b8:	f000 fcb0 	bl	70000f1c <__aeabi_fcmplt>
700005bc:	e79f      	b.n	700004fe <gc2053_get_exposure_gain_info+0x3a>
700005be:	2101      	movs	r1, #1
700005c0:	e7b4      	b.n	7000052c <gc2053_get_exposure_gain_info+0x68>
700005c2:	f06f 0015 	mvn.w	r0, #21
700005c6:	e7f3      	b.n	700005b0 <gc2053_get_exposure_gain_info+0xec>
700005c8:	7000004c 	.word	0x7000004c
700005cc:	3a83126f 	.word	0x3a83126f
700005d0:	70000730 	.word	0x70000730
700005d4:	ba83126f 	.word	0xba83126f

700005d8 <gc2053_set_mirror_flip>:
700005d8:	784b      	ldrb	r3, [r1, #1]
700005da:	780a      	ldrb	r2, [r1, #0]
700005dc:	2b00      	cmp	r3, #0
700005de:	bf14      	ite	ne
700005e0:	2302      	movne	r3, #2
700005e2:	2300      	moveq	r3, #0
700005e4:	2a00      	cmp	r2, #0
700005e6:	bf18      	it	ne
700005e8:	f043 0301 	orrne.w	r3, r3, #1
700005ec:	2201      	movs	r2, #1
700005ee:	2b02      	cmp	r3, #2
700005f0:	708a      	strb	r2, [r1, #2]
700005f2:	f04f 02fe 	mov.w	r2, #254	; 0xfe
700005f6:	610a      	str	r2, [r1, #16]
700005f8:	d00a      	beq.n	70000610 <gc2053_set_mirror_flip+0x38>
700005fa:	2b03      	cmp	r3, #3
700005fc:	d00a      	beq.n	70000614 <gc2053_set_mirror_flip+0x3c>
700005fe:	2b01      	cmp	r3, #1
70000600:	bf14      	ite	ne
70000602:	4b05      	ldrne	r3, [pc, #20]	; (70000618 <gc2053_set_mirror_flip+0x40>)
70000604:	4b05      	ldreq	r3, [pc, #20]	; (7000061c <gc2053_set_mirror_flip+0x44>)
70000606:	624b      	str	r3, [r1, #36]	; 0x24
70000608:	2302      	movs	r3, #2
7000060a:	2000      	movs	r0, #0
7000060c:	604b      	str	r3, [r1, #4]
7000060e:	4770      	bx	lr
70000610:	4b03      	ldr	r3, [pc, #12]	; (70000620 <gc2053_set_mirror_flip+0x48>)
70000612:	e7f8      	b.n	70000606 <gc2053_set_mirror_flip+0x2e>
70000614:	4b03      	ldr	r3, [pc, #12]	; (70000624 <gc2053_set_mirror_flip+0x4c>)
70000616:	e7f6      	b.n	70000606 <gc2053_set_mirror_flip+0x2e>
70000618:	00800017 	.word	0x00800017
7000061c:	00810017 	.word	0x00810017
70000620:	00820017 	.word	0x00820017
70000624:	00830017 	.word	0x00830017

70000628 <gc2053_check>:
70000628:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
7000062a:	4d1d      	ldr	r5, [pc, #116]	; (700006a0 <gc2053_check+0x78>)
7000062c:	4606      	mov	r6, r0
7000062e:	682b      	ldr	r3, [r5, #0]
70000630:	6c1b      	ldr	r3, [r3, #64]	; 0x40
70000632:	4798      	blx	r3
70000634:	2801      	cmp	r0, #1
70000636:	dc2f      	bgt.n	70000698 <gc2053_check+0x70>
70000638:	4b1a      	ldr	r3, [pc, #104]	; (700006a4 <gc2053_check+0x7c>)
7000063a:	f853 2020 	ldr.w	r2, [r3, r0, lsl #2]
7000063e:	4b1a      	ldr	r3, [pc, #104]	; (700006a8 <gc2053_check+0x80>)
70000640:	601a      	str	r2, [r3, #0]
70000642:	682b      	ldr	r3, [r5, #0]
70000644:	685b      	ldr	r3, [r3, #4]
70000646:	4798      	blx	r3
70000648:	23f0      	movs	r3, #240	; 0xf0
7000064a:	a901      	add	r1, sp, #4
7000064c:	4630      	mov	r0, r6
7000064e:	f8ad 3004 	strh.w	r3, [sp, #4]
70000652:	682b      	ldr	r3, [r5, #0]
70000654:	68db      	ldr	r3, [r3, #12]
70000656:	4798      	blx	r3
70000658:	4604      	mov	r4, r0
7000065a:	b128      	cbz	r0, 70000668 <gc2053_check+0x40>
7000065c:	682b      	ldr	r3, [r5, #0]
7000065e:	689b      	ldr	r3, [r3, #8]
70000660:	4798      	blx	r3
70000662:	4620      	mov	r0, r4
70000664:	b003      	add	sp, #12
70000666:	bdf0      	pop	{r4, r5, r6, r7, pc}
70000668:	23f1      	movs	r3, #241	; 0xf1
7000066a:	a901      	add	r1, sp, #4
7000066c:	4630      	mov	r0, r6
7000066e:	f8bd 7006 	ldrh.w	r7, [sp, #6]
70000672:	f8ad 3004 	strh.w	r3, [sp, #4]
70000676:	682b      	ldr	r3, [r5, #0]
70000678:	68db      	ldr	r3, [r3, #12]
7000067a:	4798      	blx	r3
7000067c:	682b      	ldr	r3, [r5, #0]
7000067e:	4604      	mov	r4, r0
70000680:	689b      	ldr	r3, [r3, #8]
70000682:	4798      	blx	r3
70000684:	2c00      	cmp	r4, #0
70000686:	d1ec      	bne.n	70000662 <gc2053_check+0x3a>
70000688:	f8bd 3006 	ldrh.w	r3, [sp, #6]
7000068c:	f242 0253 	movw	r2, #8275	; 0x2053
70000690:	ea43 2307 	orr.w	r3, r3, r7, lsl #8
70000694:	4293      	cmp	r3, r2
70000696:	d0e4      	beq.n	70000662 <gc2053_check+0x3a>
70000698:	f06f 0415 	mvn.w	r4, #21
7000069c:	e7e1      	b.n	70000662 <gc2053_check+0x3a>
7000069e:	bf00      	nop
700006a0:	70000048 	.word	0x70000048
700006a4:	7000028c 	.word	0x7000028c
700006a8:	70000288 	.word	0x70000288

700006ac <gc2053_pre_resume>:
700006ac:	2000      	movs	r0, #0
700006ae:	4770      	bx	lr

700006b0 <gc2053_get_slave_addr_num>:
700006b0:	2002      	movs	r0, #2
700006b2:	4770      	bx	lr

700006b4 <gc2053_get_tuned_again>:
700006b4:	b570      	push	{r4, r5, r6, lr}
700006b6:	460d      	mov	r5, r1
700006b8:	4604      	mov	r4, r0
700006ba:	bb60      	cbnz	r0, 70000716 <gc2053_get_tuned_again+0x62>
700006bc:	b359      	cbz	r1, 70000716 <gc2053_get_tuned_again+0x62>
700006be:	f04f 4185 	mov.w	r1, #1115684864	; 0x42800000
700006c2:	6828      	ldr	r0, [r5, #0]
700006c4:	f000 fa8c 	bl	70000be0 <__aeabi_fmul>
700006c8:	f000 fc50 	bl	70000f6c <__aeabi_f2uiz>
700006cc:	b280      	uxth	r0, r0
700006ce:	f5b0 6f7d 	cmp.w	r0, #4048	; 0xfd0
700006d2:	d30d      	bcc.n	700006f0 <gc2053_get_tuned_again+0x3c>
700006d4:	4b11      	ldr	r3, [pc, #68]	; (7000071c <gc2053_get_tuned_again+0x68>)
700006d6:	2218      	movs	r2, #24
700006d8:	f44f 607d 	mov.w	r0, #4048	; 0xfd0
700006dc:	611a      	str	r2, [r3, #16]
700006de:	f000 fa2b 	bl	70000b38 <__aeabi_i2f>
700006e2:	f04f 5172 	mov.w	r1, #1015021568	; 0x3c800000
700006e6:	f000 fa7b 	bl	70000be0 <__aeabi_fmul>
700006ea:	6028      	str	r0, [r5, #0]
700006ec:	2000      	movs	r0, #0
700006ee:	bd70      	pop	{r4, r5, r6, pc}
700006f0:	4a0b      	ldr	r2, [pc, #44]	; (70000720 <gc2053_get_tuned_again+0x6c>)
700006f2:	4623      	mov	r3, r4
700006f4:	8891      	ldrh	r1, [r2, #4]
700006f6:	461c      	mov	r4, r3
700006f8:	3301      	adds	r3, #1
700006fa:	4288      	cmp	r0, r1
700006fc:	d306      	bcc.n	7000070c <gc2053_get_tuned_again+0x58>
700006fe:	8956      	ldrh	r6, [r2, #10]
70000700:	4286      	cmp	r6, r0
70000702:	d903      	bls.n	7000070c <gc2053_get_tuned_again+0x58>
70000704:	4b05      	ldr	r3, [pc, #20]	; (7000071c <gc2053_get_tuned_again+0x68>)
70000706:	4608      	mov	r0, r1
70000708:	611c      	str	r4, [r3, #16]
7000070a:	e7e8      	b.n	700006de <gc2053_get_tuned_again+0x2a>
7000070c:	2b18      	cmp	r3, #24
7000070e:	f102 0206 	add.w	r2, r2, #6
70000712:	d1ef      	bne.n	700006f4 <gc2053_get_tuned_again+0x40>
70000714:	e7e3      	b.n	700006de <gc2053_get_tuned_again+0x2a>
70000716:	f06f 0015 	mvn.w	r0, #21
7000071a:	e7e8      	b.n	700006ee <gc2053_get_tuned_again+0x3a>
7000071c:	7000004c 	.word	0x7000004c
70000720:	70000730 	.word	0x70000730

70000724 <gc2053_stop>:
70000724:	2000      	movs	r0, #0
70000726:	4770      	bx	lr

70000728 <rts_isp_get_sensor_ops>:
70000728:	4800      	ldr	r0, [pc, #0]	; (7000072c <rts_isp_get_sensor_ops+0x4>)
7000072a:	4770      	bx	lr
7000072c:	700007c8 	.word	0x700007c8

70000730 <g_gc2053_gain_config>:
70000730:	00010000 10000040 004a0c01 1b012000     ....@.....J.. ..
70000740:	30000059 00662c01 3f014000 5000007f     Y..0.,f..@.?...P
70000750:	00931602 35026000 700000b1 00cb1603     .....`.5...p....
70000760:	02048000 90000104 012c3104 3205a000     .........1,....2
70000770:	b0000169 019f3506 0408c000 5a0001f8     i....5.........Z
70000780:	02451909 0f0b8300 930002d2 0340120d     ..E...........@.
70000790:	00108400 94000400 049e3a12 021a2c01     .........:...,..
700007a0:	3c010580 0655201b 0f208c00 9c0007c6     ...<. U... .....
700007b0:	08f30726 21366402 74020b22 0cd23a37     &....d6!"..t7:..
700007c0:	023dc600 00000fd0                       ..=.....

700007c8 <gc2053_ops>:
700007c8:	73000005 30326367 00003335 00000000     ...sgc2053......
	...
700007ec:	700002a5 70000401 00000000 700006b5     ...p...p.......p
700007fc:	700004b1 700004c5 00000000 00000000     ...p...p........
7000080c:	7000049d 70000725 00000000 00000000     ...p%..p........
7000081c:	700005d9 00000000 00000000 00000000     ...p............
7000082c:	70000629 700006ad 00000000 00000000     )..p...p........
7000083c:	700006b1 00000000 00000000 00000000     ...p............
	...
7000085c:	0cfff04f 52d0ea1c ea1cbf1e ea9253d1     O......R.....S..
7000086c:	ea930f0c d06f0f0c ea80441a 02400c01     ......o..D....@.
7000087c:	ea5fbf18 d01e2141 6300f04f 1050ea43     .._.A!..O..cC.P.
7000088c:	1151ea43 3101fba0 4000f00c 0f00f5b1     C.Q....1...@....
7000089c:	0049bf3e 71d3ea41 ea40005b f1620001     >.I.A..q[.@...b.
700008ac:	2afd027f f1b3d81d eb404f00 bf0850c2     ...*.....O@..P..
700008bc:	0001f020 f0904770 f00c0f00 bf084c00      ...pG.......L..
700008cc:	ea4c0249 ea402050 3a7f2051 f1d2bfc2     I.L.P @.Q .:....
700008dc:	ea4003ff 477050c2 0000f440 0300f04f     ..@..PpG@...O...
700008ec:	dc5d3a01 0f19f112 f000bfdc 47704000     .:]..........@pG
700008fc:	0200f1c2 fa210041 f1c2f102 fa000220     ....A.!..... ...
7000090c:	ea5ffc02 f1400031 ea530000 bf08034c     .._.1.@...S.L...
7000091c:	70dcea20 f0924770 f0000f00 bf024c00      ..ppG.......L..
7000092c:	f4100040 3a010f00 ea40d0f9 f093000c     @......:..@.....
7000093c:	f0010f00 bf024c00 f4110049 3b010f00     .....L..I......;
7000094c:	ea41d0f9 e78f010c 53d1ea0c 0f0cea92     ..A........S....
7000095c:	ea93bf18 d00a0f0c 4c00f030 f031bf18     ........0..L..1.
7000096c:	d1d84c00 0001ea80 4000f000 f0904770     .L.........@pG..
7000097c:	bf170f00 4f00f090 f0914608 f0910f00     .......O.F......
7000098c:	d0144f00 0f0cea92 0242d101 ea93d10f     .O........B.....
7000099c:	d1030f0c bf18024b d1084608 0001ea80     ....K....F......
700009ac:	4000f000 40fef040 0000f440 f0404770     ...@@..@@...pG@.
700009bc:	f44040fe 47700040                       .@@.@.pG

700009c4 <__aeabi_frsub>:
700009c4:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
700009c8:	e002      	b.n	700009d0 <__addsf3>
700009ca:	bf00      	nop

700009cc <__aeabi_fsub>:
700009cc:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

700009d0 <__addsf3>:
700009d0:	0042      	lsls	r2, r0, #1
700009d2:	bf1f      	itttt	ne
700009d4:	ea5f 0341 	movsne.w	r3, r1, lsl #1
700009d8:	ea92 0f03 	teqne	r2, r3
700009dc:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
700009e0:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700009e4:	d06a      	beq.n	70000abc <__addsf3+0xec>
700009e6:	ea4f 6212 	mov.w	r2, r2, lsr #24
700009ea:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
700009ee:	bfc1      	itttt	gt
700009f0:	18d2      	addgt	r2, r2, r3
700009f2:	4041      	eorgt	r1, r0
700009f4:	4048      	eorgt	r0, r1
700009f6:	4041      	eorgt	r1, r0
700009f8:	bfb8      	it	lt
700009fa:	425b      	neglt	r3, r3
700009fc:	2b19      	cmp	r3, #25
700009fe:	bf88      	it	hi
70000a00:	4770      	bxhi	lr
70000a02:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
70000a06:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000a0a:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
70000a0e:	bf18      	it	ne
70000a10:	4240      	negne	r0, r0
70000a12:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000a16:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
70000a1a:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
70000a1e:	bf18      	it	ne
70000a20:	4249      	negne	r1, r1
70000a22:	ea92 0f03 	teq	r2, r3
70000a26:	d03f      	beq.n	70000aa8 <__addsf3+0xd8>
70000a28:	f1a2 0201 	sub.w	r2, r2, #1
70000a2c:	fa41 fc03 	asr.w	ip, r1, r3
70000a30:	eb10 000c 	adds.w	r0, r0, ip
70000a34:	f1c3 0320 	rsb	r3, r3, #32
70000a38:	fa01 f103 	lsl.w	r1, r1, r3
70000a3c:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000a40:	d502      	bpl.n	70000a48 <__addsf3+0x78>
70000a42:	4249      	negs	r1, r1
70000a44:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70000a48:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70000a4c:	d313      	bcc.n	70000a76 <__addsf3+0xa6>
70000a4e:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
70000a52:	d306      	bcc.n	70000a62 <__addsf3+0x92>
70000a54:	0840      	lsrs	r0, r0, #1
70000a56:	ea4f 0131 	mov.w	r1, r1, rrx
70000a5a:	f102 0201 	add.w	r2, r2, #1
70000a5e:	2afe      	cmp	r2, #254	; 0xfe
70000a60:	d251      	bcs.n	70000b06 <__addsf3+0x136>
70000a62:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
70000a66:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000a6a:	bf08      	it	eq
70000a6c:	f020 0001 	biceq.w	r0, r0, #1
70000a70:	ea40 0003 	orr.w	r0, r0, r3
70000a74:	4770      	bx	lr
70000a76:	0049      	lsls	r1, r1, #1
70000a78:	eb40 0000 	adc.w	r0, r0, r0
70000a7c:	3a01      	subs	r2, #1
70000a7e:	bf28      	it	cs
70000a80:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70000a84:	d2ed      	bcs.n	70000a62 <__addsf3+0x92>
70000a86:	fab0 fc80 	clz	ip, r0
70000a8a:	f1ac 0c08 	sub.w	ip, ip, #8
70000a8e:	ebb2 020c 	subs.w	r2, r2, ip
70000a92:	fa00 f00c 	lsl.w	r0, r0, ip
70000a96:	bfaa      	itet	ge
70000a98:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
70000a9c:	4252      	neglt	r2, r2
70000a9e:	4318      	orrge	r0, r3
70000aa0:	bfbc      	itt	lt
70000aa2:	40d0      	lsrlt	r0, r2
70000aa4:	4318      	orrlt	r0, r3
70000aa6:	4770      	bx	lr
70000aa8:	f092 0f00 	teq	r2, #0
70000aac:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
70000ab0:	bf06      	itte	eq
70000ab2:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
70000ab6:	3201      	addeq	r2, #1
70000ab8:	3b01      	subne	r3, #1
70000aba:	e7b5      	b.n	70000a28 <__addsf3+0x58>
70000abc:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000ac0:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000ac4:	bf18      	it	ne
70000ac6:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000aca:	d021      	beq.n	70000b10 <__addsf3+0x140>
70000acc:	ea92 0f03 	teq	r2, r3
70000ad0:	d004      	beq.n	70000adc <__addsf3+0x10c>
70000ad2:	f092 0f00 	teq	r2, #0
70000ad6:	bf08      	it	eq
70000ad8:	4608      	moveq	r0, r1
70000ada:	4770      	bx	lr
70000adc:	ea90 0f01 	teq	r0, r1
70000ae0:	bf1c      	itt	ne
70000ae2:	2000      	movne	r0, #0
70000ae4:	4770      	bxne	lr
70000ae6:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
70000aea:	d104      	bne.n	70000af6 <__addsf3+0x126>
70000aec:	0040      	lsls	r0, r0, #1
70000aee:	bf28      	it	cs
70000af0:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
70000af4:	4770      	bx	lr
70000af6:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
70000afa:	bf3c      	itt	cc
70000afc:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
70000b00:	4770      	bxcc	lr
70000b02:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000b06:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
70000b0a:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000b0e:	4770      	bx	lr
70000b10:	ea7f 6222 	mvns.w	r2, r2, asr #24
70000b14:	bf16      	itet	ne
70000b16:	4608      	movne	r0, r1
70000b18:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70000b1c:	4601      	movne	r1, r0
70000b1e:	0242      	lsls	r2, r0, #9
70000b20:	bf06      	itte	eq
70000b22:	ea5f 2341 	movseq.w	r3, r1, lsl #9
70000b26:	ea90 0f01 	teqeq	r0, r1
70000b2a:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
70000b2e:	4770      	bx	lr

70000b30 <__aeabi_ui2f>:
70000b30:	f04f 0300 	mov.w	r3, #0
70000b34:	e004      	b.n	70000b40 <__aeabi_i2f+0x8>
70000b36:	bf00      	nop

70000b38 <__aeabi_i2f>:
70000b38:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70000b3c:	bf48      	it	mi
70000b3e:	4240      	negmi	r0, r0
70000b40:	ea5f 0c00 	movs.w	ip, r0
70000b44:	bf08      	it	eq
70000b46:	4770      	bxeq	lr
70000b48:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70000b4c:	4601      	mov	r1, r0
70000b4e:	f04f 0000 	mov.w	r0, #0
70000b52:	e01c      	b.n	70000b8e <__aeabi_l2f+0x2a>

70000b54 <__aeabi_ul2f>:
70000b54:	ea50 0201 	orrs.w	r2, r0, r1
70000b58:	bf08      	it	eq
70000b5a:	4770      	bxeq	lr
70000b5c:	f04f 0300 	mov.w	r3, #0
70000b60:	e00a      	b.n	70000b78 <__aeabi_l2f+0x14>
70000b62:	bf00      	nop

70000b64 <__aeabi_l2f>:
70000b64:	ea50 0201 	orrs.w	r2, r0, r1
70000b68:	bf08      	it	eq
70000b6a:	4770      	bxeq	lr
70000b6c:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70000b70:	d502      	bpl.n	70000b78 <__aeabi_l2f+0x14>
70000b72:	4240      	negs	r0, r0
70000b74:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000b78:	ea5f 0c01 	movs.w	ip, r1
70000b7c:	bf02      	ittt	eq
70000b7e:	4684      	moveq	ip, r0
70000b80:	4601      	moveq	r1, r0
70000b82:	2000      	moveq	r0, #0
70000b84:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70000b88:	bf08      	it	eq
70000b8a:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70000b8e:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
70000b92:	fabc f28c 	clz	r2, ip
70000b96:	3a08      	subs	r2, #8
70000b98:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
70000b9c:	db10      	blt.n	70000bc0 <__aeabi_l2f+0x5c>
70000b9e:	fa01 fc02 	lsl.w	ip, r1, r2
70000ba2:	4463      	add	r3, ip
70000ba4:	fa00 fc02 	lsl.w	ip, r0, r2
70000ba8:	f1c2 0220 	rsb	r2, r2, #32
70000bac:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000bb0:	fa20 f202 	lsr.w	r2, r0, r2
70000bb4:	eb43 0002 	adc.w	r0, r3, r2
70000bb8:	bf08      	it	eq
70000bba:	f020 0001 	biceq.w	r0, r0, #1
70000bbe:	4770      	bx	lr
70000bc0:	f102 0220 	add.w	r2, r2, #32
70000bc4:	fa01 fc02 	lsl.w	ip, r1, r2
70000bc8:	f1c2 0220 	rsb	r2, r2, #32
70000bcc:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
70000bd0:	fa21 f202 	lsr.w	r2, r1, r2
70000bd4:	eb43 0002 	adc.w	r0, r3, r2
70000bd8:	bf08      	it	eq
70000bda:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000bde:	4770      	bx	lr

70000be0 <__aeabi_fmul>:
70000be0:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000be4:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000be8:	bf1e      	ittt	ne
70000bea:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000bee:	ea92 0f0c 	teqne	r2, ip
70000bf2:	ea93 0f0c 	teqne	r3, ip
70000bf6:	d06f      	beq.n	70000cd8 <__aeabi_fmul+0xf8>
70000bf8:	441a      	add	r2, r3
70000bfa:	ea80 0c01 	eor.w	ip, r0, r1
70000bfe:	0240      	lsls	r0, r0, #9
70000c00:	bf18      	it	ne
70000c02:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000c06:	d01e      	beq.n	70000c46 <__aeabi_fmul+0x66>
70000c08:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000c0c:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000c10:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000c14:	fba0 3101 	umull	r3, r1, r0, r1
70000c18:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000c1c:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000c20:	bf3e      	ittt	cc
70000c22:	0049      	lslcc	r1, r1, #1
70000c24:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000c28:	005b      	lslcc	r3, r3, #1
70000c2a:	ea40 0001 	orr.w	r0, r0, r1
70000c2e:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000c32:	2afd      	cmp	r2, #253	; 0xfd
70000c34:	d81d      	bhi.n	70000c72 <__aeabi_fmul+0x92>
70000c36:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000c3a:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000c3e:	bf08      	it	eq
70000c40:	f020 0001 	biceq.w	r0, r0, #1
70000c44:	4770      	bx	lr
70000c46:	f090 0f00 	teq	r0, #0
70000c4a:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000c4e:	bf08      	it	eq
70000c50:	0249      	lsleq	r1, r1, #9
70000c52:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000c56:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000c5a:	3a7f      	subs	r2, #127	; 0x7f
70000c5c:	bfc2      	ittt	gt
70000c5e:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000c62:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000c66:	4770      	bxgt	lr
70000c68:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000c6c:	f04f 0300 	mov.w	r3, #0
70000c70:	3a01      	subs	r2, #1
70000c72:	dc5d      	bgt.n	70000d30 <__aeabi_fmul+0x150>
70000c74:	f112 0f19 	cmn.w	r2, #25
70000c78:	bfdc      	itt	le
70000c7a:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000c7e:	4770      	bxle	lr
70000c80:	f1c2 0200 	rsb	r2, r2, #0
70000c84:	0041      	lsls	r1, r0, #1
70000c86:	fa21 f102 	lsr.w	r1, r1, r2
70000c8a:	f1c2 0220 	rsb	r2, r2, #32
70000c8e:	fa00 fc02 	lsl.w	ip, r0, r2
70000c92:	ea5f 0031 	movs.w	r0, r1, rrx
70000c96:	f140 0000 	adc.w	r0, r0, #0
70000c9a:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000c9e:	bf08      	it	eq
70000ca0:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000ca4:	4770      	bx	lr
70000ca6:	f092 0f00 	teq	r2, #0
70000caa:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000cae:	bf02      	ittt	eq
70000cb0:	0040      	lsleq	r0, r0, #1
70000cb2:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000cb6:	3a01      	subeq	r2, #1
70000cb8:	d0f9      	beq.n	70000cae <__aeabi_fmul+0xce>
70000cba:	ea40 000c 	orr.w	r0, r0, ip
70000cbe:	f093 0f00 	teq	r3, #0
70000cc2:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000cc6:	bf02      	ittt	eq
70000cc8:	0049      	lsleq	r1, r1, #1
70000cca:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000cce:	3b01      	subeq	r3, #1
70000cd0:	d0f9      	beq.n	70000cc6 <__aeabi_fmul+0xe6>
70000cd2:	ea41 010c 	orr.w	r1, r1, ip
70000cd6:	e78f      	b.n	70000bf8 <__aeabi_fmul+0x18>
70000cd8:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000cdc:	ea92 0f0c 	teq	r2, ip
70000ce0:	bf18      	it	ne
70000ce2:	ea93 0f0c 	teqne	r3, ip
70000ce6:	d00a      	beq.n	70000cfe <__aeabi_fmul+0x11e>
70000ce8:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000cec:	bf18      	it	ne
70000cee:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000cf2:	d1d8      	bne.n	70000ca6 <__aeabi_fmul+0xc6>
70000cf4:	ea80 0001 	eor.w	r0, r0, r1
70000cf8:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000cfc:	4770      	bx	lr
70000cfe:	f090 0f00 	teq	r0, #0
70000d02:	bf17      	itett	ne
70000d04:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000d08:	4608      	moveq	r0, r1
70000d0a:	f091 0f00 	teqne	r1, #0
70000d0e:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000d12:	d014      	beq.n	70000d3e <__aeabi_fmul+0x15e>
70000d14:	ea92 0f0c 	teq	r2, ip
70000d18:	d101      	bne.n	70000d1e <__aeabi_fmul+0x13e>
70000d1a:	0242      	lsls	r2, r0, #9
70000d1c:	d10f      	bne.n	70000d3e <__aeabi_fmul+0x15e>
70000d1e:	ea93 0f0c 	teq	r3, ip
70000d22:	d103      	bne.n	70000d2c <__aeabi_fmul+0x14c>
70000d24:	024b      	lsls	r3, r1, #9
70000d26:	bf18      	it	ne
70000d28:	4608      	movne	r0, r1
70000d2a:	d108      	bne.n	70000d3e <__aeabi_fmul+0x15e>
70000d2c:	ea80 0001 	eor.w	r0, r0, r1
70000d30:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000d34:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000d38:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000d3c:	4770      	bx	lr
70000d3e:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000d42:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000d46:	4770      	bx	lr

70000d48 <__aeabi_fdiv>:
70000d48:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000d4c:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000d50:	bf1e      	ittt	ne
70000d52:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000d56:	ea92 0f0c 	teqne	r2, ip
70000d5a:	ea93 0f0c 	teqne	r3, ip
70000d5e:	d069      	beq.n	70000e34 <__aeabi_fdiv+0xec>
70000d60:	eba2 0203 	sub.w	r2, r2, r3
70000d64:	ea80 0c01 	eor.w	ip, r0, r1
70000d68:	0249      	lsls	r1, r1, #9
70000d6a:	ea4f 2040 	mov.w	r0, r0, lsl #9
70000d6e:	d037      	beq.n	70000de0 <__aeabi_fdiv+0x98>
70000d70:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70000d74:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70000d78:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70000d7c:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000d80:	428b      	cmp	r3, r1
70000d82:	bf38      	it	cc
70000d84:	005b      	lslcc	r3, r3, #1
70000d86:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70000d8a:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70000d8e:	428b      	cmp	r3, r1
70000d90:	bf24      	itt	cs
70000d92:	1a5b      	subcs	r3, r3, r1
70000d94:	ea40 000c 	orrcs.w	r0, r0, ip
70000d98:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70000d9c:	bf24      	itt	cs
70000d9e:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
70000da2:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70000da6:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70000daa:	bf24      	itt	cs
70000dac:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
70000db0:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
70000db4:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
70000db8:	bf24      	itt	cs
70000dba:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
70000dbe:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
70000dc2:	011b      	lsls	r3, r3, #4
70000dc4:	bf18      	it	ne
70000dc6:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70000dca:	d1e0      	bne.n	70000d8e <__aeabi_fdiv+0x46>
70000dcc:	2afd      	cmp	r2, #253	; 0xfd
70000dce:	f63f af50 	bhi.w	70000c72 <__aeabi_fmul+0x92>
70000dd2:	428b      	cmp	r3, r1
70000dd4:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000dd8:	bf08      	it	eq
70000dda:	f020 0001 	biceq.w	r0, r0, #1
70000dde:	4770      	bx	lr
70000de0:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000de4:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000de8:	327f      	adds	r2, #127	; 0x7f
70000dea:	bfc2      	ittt	gt
70000dec:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000df0:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000df4:	4770      	bxgt	lr
70000df6:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000dfa:	f04f 0300 	mov.w	r3, #0
70000dfe:	3a01      	subs	r2, #1
70000e00:	e737      	b.n	70000c72 <__aeabi_fmul+0x92>
70000e02:	f092 0f00 	teq	r2, #0
70000e06:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000e0a:	bf02      	ittt	eq
70000e0c:	0040      	lsleq	r0, r0, #1
70000e0e:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000e12:	3a01      	subeq	r2, #1
70000e14:	d0f9      	beq.n	70000e0a <__aeabi_fdiv+0xc2>
70000e16:	ea40 000c 	orr.w	r0, r0, ip
70000e1a:	f093 0f00 	teq	r3, #0
70000e1e:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000e22:	bf02      	ittt	eq
70000e24:	0049      	lsleq	r1, r1, #1
70000e26:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000e2a:	3b01      	subeq	r3, #1
70000e2c:	d0f9      	beq.n	70000e22 <__aeabi_fdiv+0xda>
70000e2e:	ea41 010c 	orr.w	r1, r1, ip
70000e32:	e795      	b.n	70000d60 <__aeabi_fdiv+0x18>
70000e34:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000e38:	ea92 0f0c 	teq	r2, ip
70000e3c:	d108      	bne.n	70000e50 <__aeabi_fdiv+0x108>
70000e3e:	0242      	lsls	r2, r0, #9
70000e40:	f47f af7d 	bne.w	70000d3e <__aeabi_fmul+0x15e>
70000e44:	ea93 0f0c 	teq	r3, ip
70000e48:	f47f af70 	bne.w	70000d2c <__aeabi_fmul+0x14c>
70000e4c:	4608      	mov	r0, r1
70000e4e:	e776      	b.n	70000d3e <__aeabi_fmul+0x15e>
70000e50:	ea93 0f0c 	teq	r3, ip
70000e54:	d104      	bne.n	70000e60 <__aeabi_fdiv+0x118>
70000e56:	024b      	lsls	r3, r1, #9
70000e58:	f43f af4c 	beq.w	70000cf4 <__aeabi_fmul+0x114>
70000e5c:	4608      	mov	r0, r1
70000e5e:	e76e      	b.n	70000d3e <__aeabi_fmul+0x15e>
70000e60:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000e64:	bf18      	it	ne
70000e66:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000e6a:	d1ca      	bne.n	70000e02 <__aeabi_fdiv+0xba>
70000e6c:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70000e70:	f47f af5c 	bne.w	70000d2c <__aeabi_fmul+0x14c>
70000e74:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70000e78:	f47f af3c 	bne.w	70000cf4 <__aeabi_fmul+0x114>
70000e7c:	e75f      	b.n	70000d3e <__aeabi_fmul+0x15e>
70000e7e:	bf00      	nop

70000e80 <__gesf2>:
70000e80:	f04f 3cff 	mov.w	ip, #4294967295
70000e84:	e006      	b.n	70000e94 <__cmpsf2+0x4>
70000e86:	bf00      	nop

70000e88 <__lesf2>:
70000e88:	f04f 0c01 	mov.w	ip, #1
70000e8c:	e002      	b.n	70000e94 <__cmpsf2+0x4>
70000e8e:	bf00      	nop

70000e90 <__cmpsf2>:
70000e90:	f04f 0c01 	mov.w	ip, #1
70000e94:	f84d cd04 	str.w	ip, [sp, #-4]!
70000e98:	ea4f 0240 	mov.w	r2, r0, lsl #1
70000e9c:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000ea0:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000ea4:	bf18      	it	ne
70000ea6:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000eaa:	d011      	beq.n	70000ed0 <__cmpsf2+0x40>
70000eac:	b001      	add	sp, #4
70000eae:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
70000eb2:	bf18      	it	ne
70000eb4:	ea90 0f01 	teqne	r0, r1
70000eb8:	bf58      	it	pl
70000eba:	ebb2 0003 	subspl.w	r0, r2, r3
70000ebe:	bf88      	it	hi
70000ec0:	17c8      	asrhi	r0, r1, #31
70000ec2:	bf38      	it	cc
70000ec4:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70000ec8:	bf18      	it	ne
70000eca:	f040 0001 	orrne.w	r0, r0, #1
70000ece:	4770      	bx	lr
70000ed0:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000ed4:	d102      	bne.n	70000edc <__cmpsf2+0x4c>
70000ed6:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70000eda:	d105      	bne.n	70000ee8 <__cmpsf2+0x58>
70000edc:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70000ee0:	d1e4      	bne.n	70000eac <__cmpsf2+0x1c>
70000ee2:	ea5f 2c41 	movs.w	ip, r1, lsl #9
70000ee6:	d0e1      	beq.n	70000eac <__cmpsf2+0x1c>
70000ee8:	f85d 0b04 	ldr.w	r0, [sp], #4
70000eec:	4770      	bx	lr
70000eee:	bf00      	nop

70000ef0 <__aeabi_cfrcmple>:
70000ef0:	4684      	mov	ip, r0
70000ef2:	4608      	mov	r0, r1
70000ef4:	4661      	mov	r1, ip
70000ef6:	e7ff      	b.n	70000ef8 <__aeabi_cfcmpeq>

70000ef8 <__aeabi_cfcmpeq>:
70000ef8:	b50f      	push	{r0, r1, r2, r3, lr}
70000efa:	f7ff ffc9 	bl	70000e90 <__cmpsf2>
70000efe:	2800      	cmp	r0, #0
70000f00:	bf48      	it	mi
70000f02:	f110 0f00 	cmnmi.w	r0, #0
70000f06:	bd0f      	pop	{r0, r1, r2, r3, pc}

70000f08 <__aeabi_fcmpeq>:
70000f08:	f84d ed08 	str.w	lr, [sp, #-8]!
70000f0c:	f7ff fff4 	bl	70000ef8 <__aeabi_cfcmpeq>
70000f10:	bf0c      	ite	eq
70000f12:	2001      	moveq	r0, #1
70000f14:	2000      	movne	r0, #0
70000f16:	f85d fb08 	ldr.w	pc, [sp], #8
70000f1a:	bf00      	nop

70000f1c <__aeabi_fcmplt>:
70000f1c:	f84d ed08 	str.w	lr, [sp, #-8]!
70000f20:	f7ff ffea 	bl	70000ef8 <__aeabi_cfcmpeq>
70000f24:	bf34      	ite	cc
70000f26:	2001      	movcc	r0, #1
70000f28:	2000      	movcs	r0, #0
70000f2a:	f85d fb08 	ldr.w	pc, [sp], #8
70000f2e:	bf00      	nop

70000f30 <__aeabi_fcmple>:
70000f30:	f84d ed08 	str.w	lr, [sp, #-8]!
70000f34:	f7ff ffe0 	bl	70000ef8 <__aeabi_cfcmpeq>
70000f38:	bf94      	ite	ls
70000f3a:	2001      	movls	r0, #1
70000f3c:	2000      	movhi	r0, #0
70000f3e:	f85d fb08 	ldr.w	pc, [sp], #8
70000f42:	bf00      	nop

70000f44 <__aeabi_fcmpge>:
70000f44:	f84d ed08 	str.w	lr, [sp, #-8]!
70000f48:	f7ff ffd2 	bl	70000ef0 <__aeabi_cfrcmple>
70000f4c:	bf94      	ite	ls
70000f4e:	2001      	movls	r0, #1
70000f50:	2000      	movhi	r0, #0
70000f52:	f85d fb08 	ldr.w	pc, [sp], #8
70000f56:	bf00      	nop

70000f58 <__aeabi_fcmpgt>:
70000f58:	f84d ed08 	str.w	lr, [sp, #-8]!
70000f5c:	f7ff ffc8 	bl	70000ef0 <__aeabi_cfrcmple>
70000f60:	bf34      	ite	cc
70000f62:	2001      	movcc	r0, #1
70000f64:	2000      	movcs	r0, #0
70000f66:	f85d fb08 	ldr.w	pc, [sp], #8
70000f6a:	bf00      	nop

70000f6c <__aeabi_f2uiz>:
70000f6c:	0042      	lsls	r2, r0, #1
70000f6e:	d20e      	bcs.n	70000f8e <__aeabi_f2uiz+0x22>
70000f70:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70000f74:	d30b      	bcc.n	70000f8e <__aeabi_f2uiz+0x22>
70000f76:	f04f 039e 	mov.w	r3, #158	; 0x9e
70000f7a:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70000f7e:	d409      	bmi.n	70000f94 <__aeabi_f2uiz+0x28>
70000f80:	ea4f 2300 	mov.w	r3, r0, lsl #8
70000f84:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000f88:	fa23 f002 	lsr.w	r0, r3, r2
70000f8c:	4770      	bx	lr
70000f8e:	f04f 0000 	mov.w	r0, #0
70000f92:	4770      	bx	lr
70000f94:	f112 0f61 	cmn.w	r2, #97	; 0x61
70000f98:	d101      	bne.n	70000f9e <__aeabi_f2uiz+0x32>
70000f9a:	0242      	lsls	r2, r0, #9
70000f9c:	d102      	bne.n	70000fa4 <__aeabi_f2uiz+0x38>
70000f9e:	f04f 30ff 	mov.w	r0, #4294967295
70000fa2:	4770      	bx	lr
70000fa4:	f04f 0000 	mov.w	r0, #0
70000fa8:	4770      	bx	lr
70000faa:	bf00      	nop
