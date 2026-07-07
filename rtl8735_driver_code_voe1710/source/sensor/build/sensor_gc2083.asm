
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	d9 07 00 70 89 02 00 70                             ...p...p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

70000060 <g_gc2083_i2c_init_regs_asic>:
70000060:	fe 03 f0 00 fe 03 f0 00 fe 03 f0 00 fe 03 00 00     ................
70000070:	f2 03 00 00 f3 03 00 00 f4 03 36 00 f5 03 c0 00     ..........6.....
70000080:	f6 03 24 00 f7 03 01 00 f8 03 32 00 f9 03 43 00     ..$.......2...C.
70000090:	fc 03 8e 00 81 03 07 00 d7 00 29 00 6d 0d 18 00     ..........).m...
700000a0:	d5 00 03 00 82 00 01 00 b3 0d d4 00 b0 0d 0d 00     ................
700000b0:	b5 0d 96 00 03 0d 02 00 04 0d 02 00 05 0d 05 00     ................
700000c0:	06 0d c9 00 07 0d 00 00 08 0d 11 00 09 0d 00 00     ................
700000d0:	0a 0d 02 00 0b 00 00 00 0c 00 02 00 0d 0d 04 00     ................
700000e0:	0e 0d 40 00 0f 00 07 00 10 00 90 00 17 00 0c 00     ..@.............
700000f0:	73 0d 92 00 76 00 00 00 76 0d 00 00 41 0d 04 00     s...v...v...A...
70000100:	42 0d 65 00 7a 0d 10 00 19 0d 31 00 25 0d cb 00     B.e.z.....1.%...
70000110:	20 0d 60 00 27 0d 03 00 29 0d 60 00 43 0d 10 00      .`.'...).`.C...
70000120:	49 0d 10 00 55 0d 18 00 c2 0d 44 00 58 00 3c 00     I...U.....D.X.<.
70000130:	d8 00 68 00 d9 00 14 00 da 00 c1 00 50 00 18 00     ..h.........P...
70000140:	b6 0d 3d 00 d2 00 bc 00 66 0d 42 00 8c 00 07 00     ..=.....f.B.....
70000150:	8d 00 ff 00 7a 00 50 00 d0 00 00 00 c1 0d 00 00     ....z.P.........
70000160:	02 01 a9 00 58 01 00 00 07 01 a6 00 08 01 a9 00     ....X...........
70000170:	09 01 a8 00 0a 01 a7 00 0b 01 ff 00 0c 01 ff 00     ................
70000180:	28 04 86 00 29 04 86 00 2a 04 86 00 2b 04 68 00     (...)...*...+.h.
70000190:	2c 04 68 00 2d 04 68 00 2e 04 68 00 2f 04 68 00     ,.h.-.h...h./.h.
700001a0:	30 04 4f 00 31 04 68 00 32 04 67 00 33 04 66 00     0.O.1.h.2.g.3.f.
700001b0:	34 04 66 00 35 04 66 00 36 04 66 00 37 04 66 00     4.f.5.f.6.f.7.f.
700001c0:	38 04 62 00 39 04 62 00 3a 04 62 00 3b 04 62 00     8.b.9.b.:.b.;.b.
700001d0:	3c 04 62 00 3d 04 62 00 3e 04 62 00 3f 04 62 00     <.b.=.b.>.b.?.b.
700001e0:	77 00 01 00 78 00 65 00 79 00 04 00 67 00 a0 00     w...x.e.y...g...
700001f0:	54 00 ff 00 55 00 02 00 56 00 00 00 57 00 04 00     T...U...V...W...
70000200:	5a 00 ff 00 5b 00 07 00 26 00 01 00 52 01 02 00     Z...[...&...R...
70000210:	53 01 50 00 55 01 93 00 10 04 16 00 11 04 16 00     S.P.U...........
70000220:	12 04 16 00 13 04 16 00 14 04 6f 00 15 04 6f 00     ..........o...o.
70000230:	16 04 6f 00 17 04 6f 00 e0 04 18 00 92 01 04 00     ..o...o.........
70000240:	94 01 03 00 95 01 04 00 96 01 38 00 97 01 07 00     ..........8.....
70000250:	98 01 80 00 01 02 27 00 02 02 53 00 03 02 ce 00     ......'...S.....
70000260:	04 02 40 00 12 02 07 00 13 02 80 00 15 02 12 00     ..@.............
70000270:	29 02 05 00 37 02 03 00 3e 02 99 00                 )...7...>...

7000027c <real_slave_addr>:
7000027c:	37 00 00 00                                         7...

70000280 <slave_addr_list>:
70000280:	37 00 00 00 3f 00 00 00                             7...?...

70000288 <rts_isp_set_voe_ops>:
70000288:	4b01      	ldr	r3, [pc, #4]	; (70000290 <rts_isp_set_voe_ops+0x8>)
7000028a:	6018      	str	r0, [r3, #0]
7000028c:	4770      	bx	lr
7000028e:	bf00      	nop
70000290:	70000048 	.word	0x70000048

70000294 <isp_driver_is_fpga>:
70000294:	2000      	movs	r0, #0
70000296:	4770      	bx	lr

70000298 <gc2083_get_info>:
70000298:	b530      	push	{r4, r5, lr}
7000029a:	2800      	cmp	r0, #0
7000029c:	d15e      	bne.n	7000035c <gc2083_get_info+0xc4>
7000029e:	2900      	cmp	r1, #0
700002a0:	d05c      	beq.n	7000035c <gc2083_get_info+0xc4>
700002a2:	4b30      	ldr	r3, [pc, #192]	; (70000364 <gc2083_get_info+0xcc>)
700002a4:	f44f 62f0 	mov.w	r2, #1920	; 0x780
700002a8:	f241 3488 	movw	r4, #5000	; 0x1388
700002ac:	f8df c0b8 	ldr.w	ip, [pc, #184]	; 70000368 <gc2083_get_info+0xd0>
700002b0:	610b      	str	r3, [r1, #16]
700002b2:	f44f 6387 	mov.w	r3, #1080	; 0x438
700002b6:	f8c1 40b8 	str.w	r4, [r1, #184]	; 0xb8
700002ba:	2464      	movs	r4, #100	; 0x64
700002bc:	2502      	movs	r5, #2
700002be:	7108      	strb	r0, [r1, #4]
700002c0:	f8c1 40c4 	str.w	r4, [r1, #196]	; 0xc4
700002c4:	f44f 747a 	mov.w	r4, #1000	; 0x3e8
700002c8:	f881 00a4 	strb.w	r0, [r1, #164]	; 0xa4
700002cc:	f8c1 00b4 	str.w	r0, [r1, #180]	; 0xb4
700002d0:	f881 50bc 	strb.w	r5, [r1, #188]	; 0xbc
700002d4:	f881 00e0 	strb.w	r0, [r1, #224]	; 0xe0
700002d8:	e9c1 2302 	strd	r2, r3, [r1, #8]
700002dc:	4a23      	ldr	r2, [pc, #140]	; (7000036c <gc2083_get_info+0xd4>)
700002de:	2301      	movs	r3, #1
700002e0:	6812      	ldr	r2, [r2, #0]
700002e2:	600b      	str	r3, [r1, #0]
700002e4:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
700002e8:	4a21      	ldr	r2, [pc, #132]	; (70000370 <gc2083_get_info+0xd8>)
700002ea:	f881 30b0 	strb.w	r3, [r1, #176]	; 0xb0
700002ee:	7812      	ldrb	r2, [r2, #0]
700002f0:	f8c1 30c0 	str.w	r3, [r1, #192]	; 0xc0
700002f4:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
700002f8:	2203      	movs	r2, #3
700002fa:	f881 30d4 	strb.w	r3, [r1, #212]	; 0xd4
700002fe:	f881 2098 	strb.w	r2, [r1, #152]	; 0x98
70000302:	f881 20c8 	strb.w	r2, [r1, #200]	; 0xc8
70000306:	e9c1 3436 	strd	r3, r4, [r1, #216]	; 0xd8
7000030a:	e9c1 3439 	strd	r3, r4, [r1, #228]	; 0xe4
7000030e:	e9c1 c433 	strd	ip, r4, [r1, #204]	; 0xcc
70000312:	f44f 7481 	mov.w	r4, #258	; 0x102
70000316:	e9c1 0024 	strd	r0, r0, [r1, #144]	; 0x90
7000031a:	e9c1 0027 	strd	r0, r0, [r1, #156]	; 0x9c
7000031e:	e9c1 002a 	strd	r0, r0, [r1, #168]	; 0xa8
70000322:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
70000326:	2408      	movs	r4, #8
70000328:	f881 32e4 	strb.w	r3, [r1, #740]	; 0x2e4
7000032c:	f8c1 4088 	str.w	r4, [r1, #136]	; 0x88
70000330:	f242 7410 	movw	r4, #10000	; 0x2710
70000334:	4b0f      	ldr	r3, [pc, #60]	; (70000374 <gc2083_get_info+0xdc>)
70000336:	f881 508c 	strb.w	r5, [r1, #140]	; 0x8c
7000033a:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
7000033e:	f8c1 02dc 	str.w	r0, [r1, #732]	; 0x2dc
70000342:	f8c1 42e0 	str.w	r4, [r1, #736]	; 0x2e0
70000346:	f8c1 02e8 	str.w	r0, [r1, #744]	; 0x2e8
7000034a:	f8c1 32ec 	str.w	r3, [r1, #748]	; 0x2ec
7000034e:	f881 22f0 	strb.w	r2, [r1, #752]	; 0x2f0
70000352:	f8c1 22d4 	str.w	r2, [r1, #724]	; 0x2d4
70000356:	e9c1 04bd 	strd	r0, r4, [r1, #756]	; 0x2f4
7000035a:	bd30      	pop	{r4, r5, pc}
7000035c:	f06f 0015 	mvn.w	r0, #21
70000360:	e7fb      	b.n	7000035a <gc2083_get_info+0xc2>
70000362:	bf00      	nop
70000364:	41f00000 	.word	0x41f00000
70000368:	016e3600 	.word	0x016e3600
7000036c:	7000027c 	.word	0x7000027c
70000370:	7000004c 	.word	0x7000004c
70000374:	000186a0 	.word	0x000186a0

70000378 <gc2083_get_init_info>:
70000378:	b570      	push	{r4, r5, r6, lr}
7000037a:	4614      	mov	r4, r2
7000037c:	4605      	mov	r5, r0
7000037e:	b110      	cbz	r0, 70000386 <gc2083_get_init_info+0xe>
70000380:	f06f 0015 	mvn.w	r0, #21
70000384:	bd70      	pop	{r4, r5, r6, pc}
70000386:	2a00      	cmp	r2, #0
70000388:	d0fa      	beq.n	70000380 <gc2083_get_init_info+0x8>
7000038a:	780b      	ldrb	r3, [r1, #0]
7000038c:	4e1c      	ldr	r6, [pc, #112]	; (70000400 <gc2083_get_init_info+0x88>)
7000038e:	68c8      	ldr	r0, [r1, #12]
70000390:	7033      	strb	r3, [r6, #0]
70000392:	f000 feb7 	bl	70001104 <__aeabi_f2uiz>
70000396:	b280      	uxth	r0, r0
70000398:	f000 fc9a 	bl	70000cd0 <__aeabi_i2f>
7000039c:	4919      	ldr	r1, [pc, #100]	; (70000404 <gc2083_get_init_info+0x8c>)
7000039e:	f000 fe7f 	bl	700010a0 <__aeabi_fcmpeq>
700003a2:	2800      	cmp	r0, #0
700003a4:	d0ec      	beq.n	70000380 <gc2083_get_init_info+0x8>
700003a6:	4b18      	ldr	r3, [pc, #96]	; (70000408 <gc2083_get_init_info+0x90>)
700003a8:	f44f 62f0 	mov.w	r2, #1920	; 0x780
700003ac:	f44f 6148 	mov.w	r1, #3200	; 0xc80
700003b0:	60a5      	str	r5, [r4, #8]
700003b2:	6063      	str	r3, [r4, #4]
700003b4:	2387      	movs	r3, #135	; 0x87
700003b6:	4628      	mov	r0, r5
700003b8:	6023      	str	r3, [r4, #0]
700003ba:	2302      	movs	r3, #2
700003bc:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
700003c0:	f240 5303 	movw	r3, #1283	; 0x503
700003c4:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
700003c8:	230a      	movs	r3, #10
700003ca:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
700003ce:	2304      	movs	r3, #4
700003d0:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
700003d4:	f44f 6387 	mov.w	r3, #1080	; 0x438
700003d8:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
700003dc:	4b0b      	ldr	r3, [pc, #44]	; (7000040c <gc2083_get_init_info+0x94>)
700003de:	e9c4 3124 	strd	r3, r1, [r4, #144]	; 0x90
700003e2:	f240 4365 	movw	r3, #1125	; 0x465
700003e6:	81f3      	strh	r3, [r6, #14]
700003e8:	f8c4 3098 	str.w	r3, [r4, #152]	; 0x98
700003ec:	f641 235e 	movw	r3, #6750	; 0x1a5e
700003f0:	f8c4 309c 	str.w	r3, [r4, #156]	; 0x9c
700003f4:	4b06      	ldr	r3, [pc, #24]	; (70000410 <gc2083_get_init_info+0x98>)
700003f6:	e9c4 5522 	strd	r5, r5, [r4, #136]	; 0x88
700003fa:	6073      	str	r3, [r6, #4]
700003fc:	e7c2      	b.n	70000384 <gc2083_get_init_info+0xc>
700003fe:	bf00      	nop
70000400:	7000004c 	.word	0x7000004c
70000404:	41f00000 	.word	0x41f00000
70000408:	70000060 	.word	0x70000060
7000040c:	066ff300 	.word	0x066ff300
70000410:	41ed097b 	.word	0x41ed097b

70000414 <gc2083_start>:
70000414:	b918      	cbnz	r0, 7000041e <gc2083_start+0xa>
70000416:	4b03      	ldr	r3, [pc, #12]	; (70000424 <gc2083_start+0x10>)
70000418:	2200      	movs	r2, #0
7000041a:	609a      	str	r2, [r3, #8]
7000041c:	4770      	bx	lr
7000041e:	f06f 0015 	mvn.w	r0, #21
70000422:	4770      	bx	lr
70000424:	7000004c 	.word	0x7000004c

70000428 <gc2083_get_exposure_range>:
70000428:	b538      	push	{r3, r4, r5, lr}
7000042a:	460a      	mov	r2, r1
7000042c:	4604      	mov	r4, r0
7000042e:	b968      	cbnz	r0, 7000044c <gc2083_get_exposure_range+0x24>
70000430:	4908      	ldr	r1, [pc, #32]	; (70000454 <gc2083_get_exposure_range+0x2c>)
70000432:	f1a2 0010 	sub.w	r0, r2, #16
70000436:	684d      	ldr	r5, [r1, #4]
70000438:	601d      	str	r5, [r3, #0]
7000043a:	f000 fc45 	bl	70000cc8 <__aeabi_ui2f>
7000043e:	4629      	mov	r1, r5
70000440:	f000 fc9a 	bl	70000d78 <__aeabi_fmul>
70000444:	9b04      	ldr	r3, [sp, #16]
70000446:	6018      	str	r0, [r3, #0]
70000448:	4620      	mov	r0, r4
7000044a:	bd38      	pop	{r3, r4, r5, pc}
7000044c:	f06f 0015 	mvn.w	r0, #21
70000450:	e7fb      	b.n	7000044a <gc2083_get_exposure_range+0x22>
70000452:	bf00      	nop
70000454:	7000004c 	.word	0x7000004c

70000458 <gc2083_get_tuned_dgain>:
70000458:	b920      	cbnz	r0, 70000464 <gc2083_get_tuned_dgain+0xc>
7000045a:	b119      	cbz	r1, 70000464 <gc2083_get_tuned_dgain+0xc>
7000045c:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
70000460:	600b      	str	r3, [r1, #0]
70000462:	4770      	bx	lr
70000464:	f06f 0015 	mvn.w	r0, #21
70000468:	4770      	bx	lr
	...

7000046c <gc2083_get_exposure_gain_info>:
7000046c:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
70000470:	4688      	mov	r8, r1
70000472:	4616      	mov	r6, r2
70000474:	2800      	cmp	r0, #0
70000476:	f040 80f6 	bne.w	70000666 <gc2083_get_exposure_gain_info+0x1fa>
7000047a:	2900      	cmp	r1, #0
7000047c:	f000 80f3 	beq.w	70000666 <gc2083_get_exposure_gain_info+0x1fa>
70000480:	2a00      	cmp	r2, #0
70000482:	f000 80f0 	beq.w	70000666 <gc2083_get_exposure_gain_info+0x1fa>
70000486:	f8d1 9000 	ldr.w	r9, [r1]
7000048a:	1d15      	adds	r5, r2, #4
7000048c:	4f77      	ldr	r7, [pc, #476]	; (7000066c <gc2083_get_exposure_gain_info+0x200>)
7000048e:	4649      	mov	r1, r9
70000490:	68b8      	ldr	r0, [r7, #8]
70000492:	f000 fb67 	bl	70000b64 <__aeabi_fsub>
70000496:	2100      	movs	r1, #0
70000498:	4604      	mov	r4, r0
7000049a:	f000 fe1f 	bl	700010dc <__aeabi_fcmpge>
7000049e:	2800      	cmp	r0, #0
700004a0:	f000 80c3 	beq.w	7000062a <gc2083_get_exposure_gain_info+0x1be>
700004a4:	4972      	ldr	r1, [pc, #456]	; (70000670 <gc2083_get_exposure_gain_info+0x204>)
700004a6:	4620      	mov	r0, r4
700004a8:	f000 fe22 	bl	700010f0 <__aeabi_fcmpgt>
700004ac:	1e04      	subs	r4, r0, #0
700004ae:	f8d8 8018 	ldr.w	r8, [r8, #24]
700004b2:	bf18      	it	ne
700004b4:	2401      	movne	r4, #1
700004b6:	2c00      	cmp	r4, #0
700004b8:	f040 80bc 	bne.w	70000634 <gc2083_get_exposure_gain_info+0x1c8>
700004bc:	89bb      	ldrh	r3, [r7, #12]
700004be:	fa1f f288 	uxth.w	r2, r8
700004c2:	1a98      	subs	r0, r3, r2
700004c4:	bf48      	it	mi
700004c6:	1ad0      	submi	r0, r2, r3
700004c8:	f000 fc02 	bl	70000cd0 <__aeabi_i2f>
700004cc:	4968      	ldr	r1, [pc, #416]	; (70000670 <gc2083_get_exposure_gain_info+0x204>)
700004ce:	f000 fe0f 	bl	700010f0 <__aeabi_fcmpgt>
700004d2:	b198      	cbz	r0, 700004fc <gc2083_get_exposure_gain_info+0x90>
700004d4:	2314      	movs	r3, #20
700004d6:	f640 5141 	movw	r1, #3393	; 0xd41
700004da:	4363      	muls	r3, r4
700004dc:	3402      	adds	r4, #2
700004de:	18ea      	adds	r2, r5, r3
700004e0:	3314      	adds	r3, #20
700004e2:	8111      	strh	r1, [r2, #8]
700004e4:	f3c8 2107 	ubfx	r1, r8, #8, #8
700004e8:	442b      	add	r3, r5
700004ea:	8151      	strh	r1, [r2, #10]
700004ec:	f640 5242 	movw	r2, #3394	; 0xd42
700004f0:	811a      	strh	r2, [r3, #8]
700004f2:	fa5f f288 	uxtb.w	r2, r8
700004f6:	815a      	strh	r2, [r3, #10]
700004f8:	f8a7 800c 	strh.w	r8, [r7, #12]
700004fc:	7c7b      	ldrb	r3, [r7, #17]
700004fe:	f897 8010 	ldrb.w	r8, [r7, #16]
70000502:	ebb3 0008 	subs.w	r0, r3, r8
70000506:	bf48      	it	mi
70000508:	eba8 0003 	submi.w	r0, r8, r3
7000050c:	f000 fbe0 	bl	70000cd0 <__aeabi_i2f>
70000510:	4957      	ldr	r1, [pc, #348]	; (70000670 <gc2083_get_exposure_gain_info+0x204>)
70000512:	f000 fded 	bl	700010f0 <__aeabi_fcmpgt>
70000516:	2800      	cmp	r0, #0
70000518:	f000 8083 	beq.w	70000622 <gc2083_get_exposure_gain_info+0x1b6>
7000051c:	2314      	movs	r3, #20
7000051e:	4855      	ldr	r0, [pc, #340]	; (70000674 <gc2083_get_exposure_gain_info+0x208>)
70000520:	ea4f 1c08 	mov.w	ip, r8, lsl #4
70000524:	f640 5ec1 	movw	lr, #3521	; 0xdc1
70000528:	4363      	muls	r3, r4
7000052a:	eb00 1108 	add.w	r1, r0, r8, lsl #4
7000052e:	f810 000c 	ldrb.w	r0, [r0, ip]
70000532:	f04f 0cd0 	mov.w	ip, #208	; 0xd0
70000536:	18ea      	adds	r2, r5, r3
70000538:	340f      	adds	r4, #15
7000053a:	8150      	strh	r0, [r2, #10]
7000053c:	484e      	ldr	r0, [pc, #312]	; (70000678 <gc2083_get_exposure_gain_info+0x20c>)
7000053e:	f8a2 c008 	strh.w	ip, [r2, #8]
70000542:	61d0      	str	r0, [r2, #28]
70000544:	f103 0028 	add.w	r0, r3, #40	; 0x28
70000548:	f891 c001 	ldrb.w	ip, [r1, #1]
7000054c:	4428      	add	r0, r5
7000054e:	f8a0 c00a 	strh.w	ip, [r0, #10]
70000552:	f04f 0cb8 	mov.w	ip, #184	; 0xb8
70000556:	f8a0 e008 	strh.w	lr, [r0, #8]
7000055a:	4848      	ldr	r0, [pc, #288]	; (7000067c <gc2083_get_exposure_gain_info+0x210>)
7000055c:	6450      	str	r0, [r2, #68]	; 0x44
7000055e:	f103 0250 	add.w	r2, r3, #80	; 0x50
70000562:	7888      	ldrb	r0, [r1, #2]
70000564:	442a      	add	r2, r5
70000566:	f8a2 c008 	strh.w	ip, [r2, #8]
7000056a:	f04f 0cb9 	mov.w	ip, #185	; 0xb9
7000056e:	8150      	strh	r0, [r2, #10]
70000570:	f103 0264 	add.w	r2, r3, #100	; 0x64
70000574:	78c8      	ldrb	r0, [r1, #3]
70000576:	442a      	add	r2, r5
70000578:	f8a2 c008 	strh.w	ip, [r2, #8]
7000057c:	f240 1c55 	movw	ip, #341	; 0x155
70000580:	8150      	strh	r0, [r2, #10]
70000582:	f103 0278 	add.w	r2, r3, #120	; 0x78
70000586:	7908      	ldrb	r0, [r1, #4]
70000588:	442a      	add	r2, r5
7000058a:	f8a2 c008 	strh.w	ip, [r2, #8]
7000058e:	f44f 6c82 	mov.w	ip, #1040	; 0x410
70000592:	8150      	strh	r0, [r2, #10]
70000594:	f103 028c 	add.w	r2, r3, #140	; 0x8c
70000598:	7948      	ldrb	r0, [r1, #5]
7000059a:	442a      	add	r2, r5
7000059c:	f8a2 c008 	strh.w	ip, [r2, #8]
700005a0:	f240 4c11 	movw	ip, #1041	; 0x411
700005a4:	8150      	strh	r0, [r2, #10]
700005a6:	f103 02a0 	add.w	r2, r3, #160	; 0xa0
700005aa:	7988      	ldrb	r0, [r1, #6]
700005ac:	442a      	add	r2, r5
700005ae:	f8a2 c008 	strh.w	ip, [r2, #8]
700005b2:	f240 4c12 	movw	ip, #1042	; 0x412
700005b6:	8150      	strh	r0, [r2, #10]
700005b8:	f103 02b4 	add.w	r2, r3, #180	; 0xb4
700005bc:	79c8      	ldrb	r0, [r1, #7]
700005be:	442a      	add	r2, r5
700005c0:	f8a2 c008 	strh.w	ip, [r2, #8]
700005c4:	f240 4c13 	movw	ip, #1043	; 0x413
700005c8:	8150      	strh	r0, [r2, #10]
700005ca:	f103 02c8 	add.w	r2, r3, #200	; 0xc8
700005ce:	7a08      	ldrb	r0, [r1, #8]
700005d0:	442a      	add	r2, r5
700005d2:	f8a2 c008 	strh.w	ip, [r2, #8]
700005d6:	f240 4c14 	movw	ip, #1044	; 0x414
700005da:	8150      	strh	r0, [r2, #10]
700005dc:	f103 02dc 	add.w	r2, r3, #220	; 0xdc
700005e0:	7a48      	ldrb	r0, [r1, #9]
700005e2:	442a      	add	r2, r5
700005e4:	f8a2 c008 	strh.w	ip, [r2, #8]
700005e8:	f240 4c15 	movw	ip, #1045	; 0x415
700005ec:	8150      	strh	r0, [r2, #10]
700005ee:	f103 02f0 	add.w	r2, r3, #240	; 0xf0
700005f2:	7a88      	ldrb	r0, [r1, #10]
700005f4:	442a      	add	r2, r5
700005f6:	f8a2 c008 	strh.w	ip, [r2, #8]
700005fa:	f240 4c16 	movw	ip, #1046	; 0x416
700005fe:	8150      	strh	r0, [r2, #10]
70000600:	f503 7282 	add.w	r2, r3, #260	; 0x104
70000604:	7ac8      	ldrb	r0, [r1, #11]
70000606:	f503 738c 	add.w	r3, r3, #280	; 0x118
7000060a:	442a      	add	r2, r5
7000060c:	442b      	add	r3, r5
7000060e:	f8a2 c008 	strh.w	ip, [r2, #8]
70000612:	8150      	strh	r0, [r2, #10]
70000614:	7b0a      	ldrb	r2, [r1, #12]
70000616:	f240 4117 	movw	r1, #1047	; 0x417
7000061a:	815a      	strh	r2, [r3, #10]
7000061c:	8119      	strh	r1, [r3, #8]
7000061e:	f887 8011 	strb.w	r8, [r7, #17]
70000622:	2000      	movs	r0, #0
70000624:	6034      	str	r4, [r6, #0]
70000626:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
7000062a:	4915      	ldr	r1, [pc, #84]	; (70000680 <gc2083_get_exposure_gain_info+0x214>)
7000062c:	4620      	mov	r0, r4
7000062e:	f000 fd41 	bl	700010b4 <__aeabi_fcmplt>
70000632:	e73b      	b.n	700004ac <gc2083_get_exposure_gain_info+0x40>
70000634:	6879      	ldr	r1, [r7, #4]
70000636:	4648      	mov	r0, r9
70000638:	f000 fc52 	bl	70000ee0 <__aeabi_fdiv>
7000063c:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
70000640:	f000 fa92 	bl	70000b68 <__addsf3>
70000644:	2402      	movs	r4, #2
70000646:	f000 fd5d 	bl	70001104 <__aeabi_f2uiz>
7000064a:	f640 5303 	movw	r3, #3331	; 0xd03
7000064e:	f8c7 9008 	str.w	r9, [r7, #8]
70000652:	81b3      	strh	r3, [r6, #12]
70000654:	f3c0 2307 	ubfx	r3, r0, #8, #8
70000658:	b2c0      	uxtb	r0, r0
7000065a:	81f3      	strh	r3, [r6, #14]
7000065c:	f640 5304 	movw	r3, #3332	; 0xd04
70000660:	8470      	strh	r0, [r6, #34]	; 0x22
70000662:	8433      	strh	r3, [r6, #32]
70000664:	e72a      	b.n	700004bc <gc2083_get_exposure_gain_info+0x50>
70000666:	f06f 0015 	mvn.w	r0, #21
7000066a:	e7dc      	b.n	70000626 <gc2083_get_exposure_gain_info+0x1ba>
7000066c:	7000004c 	.word	0x7000004c
70000670:	3a83126f 	.word	0x3a83126f
70000674:	700007e0 	.word	0x700007e0
70000678:	002e031d 	.word	0x002e031d
7000067c:	0028031d 	.word	0x0028031d
70000680:	ba83126f 	.word	0xba83126f

70000684 <gc2083_set_mirror_flip>:
70000684:	784b      	ldrb	r3, [r1, #1]
70000686:	780a      	ldrb	r2, [r1, #0]
70000688:	2b00      	cmp	r3, #0
7000068a:	bf14      	ite	ne
7000068c:	2302      	movne	r3, #2
7000068e:	2300      	moveq	r3, #0
70000690:	2a00      	cmp	r2, #0
70000692:	bf18      	it	ne
70000694:	f043 0301 	orrne.w	r3, r3, #1
70000698:	2201      	movs	r2, #1
7000069a:	2b02      	cmp	r3, #2
7000069c:	708a      	strb	r2, [r1, #2]
7000069e:	d011      	beq.n	700006c4 <gc2083_set_mirror_flip+0x40>
700006a0:	2b03      	cmp	r3, #3
700006a2:	d011      	beq.n	700006c8 <gc2083_set_mirror_flip+0x44>
700006a4:	4293      	cmp	r3, r2
700006a6:	d008      	beq.n	700006ba <gc2083_set_mirror_flip+0x36>
700006a8:	2315      	movs	r3, #21
700006aa:	610b      	str	r3, [r1, #16]
700006ac:	f640 5315 	movw	r3, #3349	; 0xd15
700006b0:	624b      	str	r3, [r1, #36]	; 0x24
700006b2:	2302      	movs	r3, #2
700006b4:	2000      	movs	r0, #0
700006b6:	604b      	str	r3, [r1, #4]
700006b8:	4770      	bx	lr
700006ba:	4b04      	ldr	r3, [pc, #16]	; (700006cc <gc2083_set_mirror_flip+0x48>)
700006bc:	610b      	str	r3, [r1, #16]
700006be:	f503 6350 	add.w	r3, r3, #3328	; 0xd00
700006c2:	e7f5      	b.n	700006b0 <gc2083_set_mirror_flip+0x2c>
700006c4:	4b02      	ldr	r3, [pc, #8]	; (700006d0 <gc2083_set_mirror_flip+0x4c>)
700006c6:	e7f9      	b.n	700006bc <gc2083_set_mirror_flip+0x38>
700006c8:	4b02      	ldr	r3, [pc, #8]	; (700006d4 <gc2083_set_mirror_flip+0x50>)
700006ca:	e7f7      	b.n	700006bc <gc2083_set_mirror_flip+0x38>
700006cc:	00010015 	.word	0x00010015
700006d0:	00020015 	.word	0x00020015
700006d4:	00030015 	.word	0x00030015

700006d8 <gc2083_check>:
700006d8:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
700006da:	4d1e      	ldr	r5, [pc, #120]	; (70000754 <gc2083_check+0x7c>)
700006dc:	4606      	mov	r6, r0
700006de:	682b      	ldr	r3, [r5, #0]
700006e0:	6c1b      	ldr	r3, [r3, #64]	; 0x40
700006e2:	4798      	blx	r3
700006e4:	2801      	cmp	r0, #1
700006e6:	dc31      	bgt.n	7000074c <gc2083_check+0x74>
700006e8:	4b1b      	ldr	r3, [pc, #108]	; (70000758 <gc2083_check+0x80>)
700006ea:	f853 2020 	ldr.w	r2, [r3, r0, lsl #2]
700006ee:	4b1b      	ldr	r3, [pc, #108]	; (7000075c <gc2083_check+0x84>)
700006f0:	601a      	str	r2, [r3, #0]
700006f2:	682b      	ldr	r3, [r5, #0]
700006f4:	685b      	ldr	r3, [r3, #4]
700006f6:	4798      	blx	r3
700006f8:	f44f 737c 	mov.w	r3, #1008	; 0x3f0
700006fc:	a901      	add	r1, sp, #4
700006fe:	4630      	mov	r0, r6
70000700:	f8ad 3004 	strh.w	r3, [sp, #4]
70000704:	682b      	ldr	r3, [r5, #0]
70000706:	68db      	ldr	r3, [r3, #12]
70000708:	4798      	blx	r3
7000070a:	4604      	mov	r4, r0
7000070c:	b128      	cbz	r0, 7000071a <gc2083_check+0x42>
7000070e:	682b      	ldr	r3, [r5, #0]
70000710:	689b      	ldr	r3, [r3, #8]
70000712:	4798      	blx	r3
70000714:	4620      	mov	r0, r4
70000716:	b003      	add	sp, #12
70000718:	bdf0      	pop	{r4, r5, r6, r7, pc}
7000071a:	f240 33f1 	movw	r3, #1009	; 0x3f1
7000071e:	a901      	add	r1, sp, #4
70000720:	4630      	mov	r0, r6
70000722:	f8bd 7006 	ldrh.w	r7, [sp, #6]
70000726:	f8ad 3004 	strh.w	r3, [sp, #4]
7000072a:	682b      	ldr	r3, [r5, #0]
7000072c:	68db      	ldr	r3, [r3, #12]
7000072e:	4798      	blx	r3
70000730:	682b      	ldr	r3, [r5, #0]
70000732:	4604      	mov	r4, r0
70000734:	689b      	ldr	r3, [r3, #8]
70000736:	4798      	blx	r3
70000738:	2c00      	cmp	r4, #0
7000073a:	d1eb      	bne.n	70000714 <gc2083_check+0x3c>
7000073c:	f8bd 3006 	ldrh.w	r3, [sp, #6]
70000740:	f242 0283 	movw	r2, #8323	; 0x2083
70000744:	ea43 2307 	orr.w	r3, r3, r7, lsl #8
70000748:	4293      	cmp	r3, r2
7000074a:	d0e3      	beq.n	70000714 <gc2083_check+0x3c>
7000074c:	f06f 0415 	mvn.w	r4, #21
70000750:	e7e0      	b.n	70000714 <gc2083_check+0x3c>
70000752:	bf00      	nop
70000754:	70000048 	.word	0x70000048
70000758:	70000280 	.word	0x70000280
7000075c:	7000027c 	.word	0x7000027c

70000760 <gc2083_get_slave_addr_num>:
70000760:	2002      	movs	r0, #2
70000762:	4770      	bx	lr

70000764 <gc2083_get_tuned_again>:
70000764:	b570      	push	{r4, r5, r6, lr}
70000766:	460d      	mov	r5, r1
70000768:	4604      	mov	r4, r0
7000076a:	bb68      	cbnz	r0, 700007c8 <gc2083_get_tuned_again+0x64>
7000076c:	b361      	cbz	r1, 700007c8 <gc2083_get_tuned_again+0x64>
7000076e:	f04f 4185 	mov.w	r1, #1115684864	; 0x42800000
70000772:	6828      	ldr	r0, [r5, #0]
70000774:	f000 fb00 	bl	70000d78 <__aeabi_fmul>
70000778:	f000 fcc4 	bl	70001104 <__aeabi_f2uiz>
7000077c:	f640 63b3 	movw	r3, #3763	; 0xeb3
70000780:	b280      	uxth	r0, r0
70000782:	4298      	cmp	r0, r3
70000784:	d90d      	bls.n	700007a2 <gc2083_get_tuned_again+0x3e>
70000786:	4b12      	ldr	r3, [pc, #72]	; (700007d0 <gc2083_get_tuned_again+0x6c>)
70000788:	2217      	movs	r2, #23
7000078a:	f640 60b4 	movw	r0, #3764	; 0xeb4
7000078e:	741a      	strb	r2, [r3, #16]
70000790:	f000 fa9e 	bl	70000cd0 <__aeabi_i2f>
70000794:	f04f 5172 	mov.w	r1, #1015021568	; 0x3c800000
70000798:	f000 faee 	bl	70000d78 <__aeabi_fmul>
7000079c:	6028      	str	r0, [r5, #0]
7000079e:	2000      	movs	r0, #0
700007a0:	bd70      	pop	{r4, r5, r6, pc}
700007a2:	4a0c      	ldr	r2, [pc, #48]	; (700007d4 <gc2083_get_tuned_again+0x70>)
700007a4:	4623      	mov	r3, r4
700007a6:	89d1      	ldrh	r1, [r2, #14]
700007a8:	461c      	mov	r4, r3
700007aa:	3301      	adds	r3, #1
700007ac:	4288      	cmp	r0, r1
700007ae:	d306      	bcc.n	700007be <gc2083_get_tuned_again+0x5a>
700007b0:	8bd6      	ldrh	r6, [r2, #30]
700007b2:	4286      	cmp	r6, r0
700007b4:	d903      	bls.n	700007be <gc2083_get_tuned_again+0x5a>
700007b6:	4b06      	ldr	r3, [pc, #24]	; (700007d0 <gc2083_get_tuned_again+0x6c>)
700007b8:	4608      	mov	r0, r1
700007ba:	741c      	strb	r4, [r3, #16]
700007bc:	e7e8      	b.n	70000790 <gc2083_get_tuned_again+0x2c>
700007be:	2b17      	cmp	r3, #23
700007c0:	f102 0210 	add.w	r2, r2, #16
700007c4:	d1ef      	bne.n	700007a6 <gc2083_get_tuned_again+0x42>
700007c6:	e7e3      	b.n	70000790 <gc2083_get_tuned_again+0x2c>
700007c8:	f06f 0015 	mvn.w	r0, #21
700007cc:	e7e8      	b.n	700007a0 <gc2083_get_tuned_again+0x3c>
700007ce:	bf00      	nop
700007d0:	7000004c 	.word	0x7000004c
700007d4:	700007e0 	.word	0x700007e0

700007d8 <rts_isp_get_sensor_ops>:
700007d8:	4800      	ldr	r0, [pc, #0]	; (700007dc <rts_isp_get_sensor_ops+0x4>)
700007da:	4770      	bx	lr
700007dc:	70000960 	.word	0x70000960

700007e0 <g_gc2083_gain_config>:
700007e0:	00010000 11111103 6f6f6f11 0040006f     .........oooo.@.
700007f0:	0c010010 11111103 6f6f6f11 004d006f     .........oooo.M.
70000800:	1a010001 11111103 6f6f6f11 005c006f     .........oooo.\.
70000810:	2b010011 11111103 6f6f6f11 006e006f     ...+.....oooo.n.
70000820:	00020002 11111103 6f6f6f11 0080006f     .........oooo...
70000830:	18020012 11111103 6f6f6f11 009a006f     .........oooo...
70000840:	33020003 11111103 6f6f6f11 00ba006f     ...3.....oooo...
70000850:	15030013 11111103 6f6f6f11 00df006f     .........oooo...
70000860:	00040004 11111103 6f6f6f11 010d006f     .........oooo...
70000870:	e0040014 11111103 6f6f6f11 0143006f     .........oooo.C.
70000880:	26050005 11111103 6f6f6f11 017d006f     ...&.....oooo.}.
70000890:	2b060015 11111103 6f6f6f11 01c9006f     ...+.....oooo...
700008a0:	00080044 11111103 6f6f6f11 0220006f     D........oooo. .
700008b0:	22090054 11111103 6f6f6f11 028d006f     T..".....oooo...
700008c0:	0d0b0045 11111103 6f6f6f11 02fa006f     E........oooo...
700008d0:	160d0055 11111103 6f6f6f11 0392006f     U........oooo...
700008e0:	00100104 16161619 6f6f6f16 0436006f     .........oooo.6.
700008f0:	04130114 16161619 6f6f6f16 050d006f     .........oooo...
70000900:	1a160124 16161619 6f6f6f16 0605006f     $........oooo...
70000910:	2b1a0134 16161619 6f6f6f16 0739006f     4..+.....oooo.9.
70000920:	00200144 18181836 6f6f6f18 0881006f     D. .6....oooo...
70000930:	07260154 18181836 6f6f6f18 0a34006f     T.&.6....oooo.4.
70000940:	332c0164 18181836 6f6f6f18 0c40006f     d.,36....oooo.@.
70000950:	17350174 18181836 6f6f6f18 0eb4006f     t.5.6....oooo...

70000960 <gc2083_ops>:
70000960:	73000005 30326367 00003338 00000000     ...sgc2083......
	...
70000984:	70000299 70000379 70000429 70000765     ...py..p)..pe..p
70000994:	70000459 7000046d 00000000 00000000     Y..pm..p........
700009a4:	70000415 00000000 00000000 00000000     ...p............
700009b4:	70000685 00000000 00000000 00000000     ...p............
700009c4:	700006d9 00000000 00000000 00000000     ...p............
700009d4:	70000761 00000000 00000000 00000000     a..p............
	...
700009f4:	0cfff04f 52d0ea1c ea1cbf1e ea9253d1     O......R.....S..
70000a04:	ea930f0c d06f0f0c ea80441a 02400c01     ......o..D....@.
70000a14:	ea5fbf18 d01e2141 6300f04f 1050ea43     .._.A!..O..cC.P.
70000a24:	1151ea43 3101fba0 4000f00c 0f00f5b1     C.Q....1...@....
70000a34:	0049bf3e 71d3ea41 ea40005b f1620001     >.I.A..q[.@...b.
70000a44:	2afd027f f1b3d81d eb404f00 bf0850c2     ...*.....O@..P..
70000a54:	0001f020 f0904770 f00c0f00 bf084c00      ...pG.......L..
70000a64:	ea4c0249 ea402050 3a7f2051 f1d2bfc2     I.L.P @.Q .:....
70000a74:	ea4003ff 477050c2 0000f440 0300f04f     ..@..PpG@...O...
70000a84:	dc5d3a01 0f19f112 f000bfdc 47704000     .:]..........@pG
70000a94:	0200f1c2 fa210041 f1c2f102 fa000220     ....A.!..... ...
70000aa4:	ea5ffc02 f1400031 ea530000 bf08034c     .._.1.@...S.L...
70000ab4:	70dcea20 f0924770 f0000f00 bf024c00      ..ppG.......L..
70000ac4:	f4100040 3a010f00 ea40d0f9 f093000c     @......:..@.....
70000ad4:	f0010f00 bf024c00 f4110049 3b010f00     .....L..I......;
70000ae4:	ea41d0f9 e78f010c 53d1ea0c 0f0cea92     ..A........S....
70000af4:	ea93bf18 d00a0f0c 4c00f030 f031bf18     ........0..L..1.
70000b04:	d1d84c00 0001ea80 4000f000 f0904770     .L.........@pG..
70000b14:	bf170f00 4f00f090 f0914608 f0910f00     .......O.F......
70000b24:	d0144f00 0f0cea92 0242d101 ea93d10f     .O........B.....
70000b34:	d1030f0c bf18024b d1084608 0001ea80     ....K....F......
70000b44:	4000f000 40fef040 0000f440 f0404770     ...@@..@@...pG@.
70000b54:	f44040fe 47700040                       .@@.@.pG

70000b5c <__aeabi_frsub>:
70000b5c:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70000b60:	e002      	b.n	70000b68 <__addsf3>
70000b62:	bf00      	nop

70000b64 <__aeabi_fsub>:
70000b64:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

70000b68 <__addsf3>:
70000b68:	0042      	lsls	r2, r0, #1
70000b6a:	bf1f      	itttt	ne
70000b6c:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70000b70:	ea92 0f03 	teqne	r2, r3
70000b74:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
70000b78:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000b7c:	d06a      	beq.n	70000c54 <__addsf3+0xec>
70000b7e:	ea4f 6212 	mov.w	r2, r2, lsr #24
70000b82:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
70000b86:	bfc1      	itttt	gt
70000b88:	18d2      	addgt	r2, r2, r3
70000b8a:	4041      	eorgt	r1, r0
70000b8c:	4048      	eorgt	r0, r1
70000b8e:	4041      	eorgt	r1, r0
70000b90:	bfb8      	it	lt
70000b92:	425b      	neglt	r3, r3
70000b94:	2b19      	cmp	r3, #25
70000b96:	bf88      	it	hi
70000b98:	4770      	bxhi	lr
70000b9a:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
70000b9e:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000ba2:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
70000ba6:	bf18      	it	ne
70000ba8:	4240      	negne	r0, r0
70000baa:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000bae:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
70000bb2:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
70000bb6:	bf18      	it	ne
70000bb8:	4249      	negne	r1, r1
70000bba:	ea92 0f03 	teq	r2, r3
70000bbe:	d03f      	beq.n	70000c40 <__addsf3+0xd8>
70000bc0:	f1a2 0201 	sub.w	r2, r2, #1
70000bc4:	fa41 fc03 	asr.w	ip, r1, r3
70000bc8:	eb10 000c 	adds.w	r0, r0, ip
70000bcc:	f1c3 0320 	rsb	r3, r3, #32
70000bd0:	fa01 f103 	lsl.w	r1, r1, r3
70000bd4:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000bd8:	d502      	bpl.n	70000be0 <__addsf3+0x78>
70000bda:	4249      	negs	r1, r1
70000bdc:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70000be0:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70000be4:	d313      	bcc.n	70000c0e <__addsf3+0xa6>
70000be6:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
70000bea:	d306      	bcc.n	70000bfa <__addsf3+0x92>
70000bec:	0840      	lsrs	r0, r0, #1
70000bee:	ea4f 0131 	mov.w	r1, r1, rrx
70000bf2:	f102 0201 	add.w	r2, r2, #1
70000bf6:	2afe      	cmp	r2, #254	; 0xfe
70000bf8:	d251      	bcs.n	70000c9e <__addsf3+0x136>
70000bfa:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
70000bfe:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000c02:	bf08      	it	eq
70000c04:	f020 0001 	biceq.w	r0, r0, #1
70000c08:	ea40 0003 	orr.w	r0, r0, r3
70000c0c:	4770      	bx	lr
70000c0e:	0049      	lsls	r1, r1, #1
70000c10:	eb40 0000 	adc.w	r0, r0, r0
70000c14:	3a01      	subs	r2, #1
70000c16:	bf28      	it	cs
70000c18:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70000c1c:	d2ed      	bcs.n	70000bfa <__addsf3+0x92>
70000c1e:	fab0 fc80 	clz	ip, r0
70000c22:	f1ac 0c08 	sub.w	ip, ip, #8
70000c26:	ebb2 020c 	subs.w	r2, r2, ip
70000c2a:	fa00 f00c 	lsl.w	r0, r0, ip
70000c2e:	bfaa      	itet	ge
70000c30:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
70000c34:	4252      	neglt	r2, r2
70000c36:	4318      	orrge	r0, r3
70000c38:	bfbc      	itt	lt
70000c3a:	40d0      	lsrlt	r0, r2
70000c3c:	4318      	orrlt	r0, r3
70000c3e:	4770      	bx	lr
70000c40:	f092 0f00 	teq	r2, #0
70000c44:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
70000c48:	bf06      	itte	eq
70000c4a:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
70000c4e:	3201      	addeq	r2, #1
70000c50:	3b01      	subne	r3, #1
70000c52:	e7b5      	b.n	70000bc0 <__addsf3+0x58>
70000c54:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000c58:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000c5c:	bf18      	it	ne
70000c5e:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000c62:	d021      	beq.n	70000ca8 <__addsf3+0x140>
70000c64:	ea92 0f03 	teq	r2, r3
70000c68:	d004      	beq.n	70000c74 <__addsf3+0x10c>
70000c6a:	f092 0f00 	teq	r2, #0
70000c6e:	bf08      	it	eq
70000c70:	4608      	moveq	r0, r1
70000c72:	4770      	bx	lr
70000c74:	ea90 0f01 	teq	r0, r1
70000c78:	bf1c      	itt	ne
70000c7a:	2000      	movne	r0, #0
70000c7c:	4770      	bxne	lr
70000c7e:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
70000c82:	d104      	bne.n	70000c8e <__addsf3+0x126>
70000c84:	0040      	lsls	r0, r0, #1
70000c86:	bf28      	it	cs
70000c88:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
70000c8c:	4770      	bx	lr
70000c8e:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
70000c92:	bf3c      	itt	cc
70000c94:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
70000c98:	4770      	bxcc	lr
70000c9a:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000c9e:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
70000ca2:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000ca6:	4770      	bx	lr
70000ca8:	ea7f 6222 	mvns.w	r2, r2, asr #24
70000cac:	bf16      	itet	ne
70000cae:	4608      	movne	r0, r1
70000cb0:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70000cb4:	4601      	movne	r1, r0
70000cb6:	0242      	lsls	r2, r0, #9
70000cb8:	bf06      	itte	eq
70000cba:	ea5f 2341 	movseq.w	r3, r1, lsl #9
70000cbe:	ea90 0f01 	teqeq	r0, r1
70000cc2:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
70000cc6:	4770      	bx	lr

70000cc8 <__aeabi_ui2f>:
70000cc8:	f04f 0300 	mov.w	r3, #0
70000ccc:	e004      	b.n	70000cd8 <__aeabi_i2f+0x8>
70000cce:	bf00      	nop

70000cd0 <__aeabi_i2f>:
70000cd0:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70000cd4:	bf48      	it	mi
70000cd6:	4240      	negmi	r0, r0
70000cd8:	ea5f 0c00 	movs.w	ip, r0
70000cdc:	bf08      	it	eq
70000cde:	4770      	bxeq	lr
70000ce0:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70000ce4:	4601      	mov	r1, r0
70000ce6:	f04f 0000 	mov.w	r0, #0
70000cea:	e01c      	b.n	70000d26 <__aeabi_l2f+0x2a>

70000cec <__aeabi_ul2f>:
70000cec:	ea50 0201 	orrs.w	r2, r0, r1
70000cf0:	bf08      	it	eq
70000cf2:	4770      	bxeq	lr
70000cf4:	f04f 0300 	mov.w	r3, #0
70000cf8:	e00a      	b.n	70000d10 <__aeabi_l2f+0x14>
70000cfa:	bf00      	nop

70000cfc <__aeabi_l2f>:
70000cfc:	ea50 0201 	orrs.w	r2, r0, r1
70000d00:	bf08      	it	eq
70000d02:	4770      	bxeq	lr
70000d04:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70000d08:	d502      	bpl.n	70000d10 <__aeabi_l2f+0x14>
70000d0a:	4240      	negs	r0, r0
70000d0c:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000d10:	ea5f 0c01 	movs.w	ip, r1
70000d14:	bf02      	ittt	eq
70000d16:	4684      	moveq	ip, r0
70000d18:	4601      	moveq	r1, r0
70000d1a:	2000      	moveq	r0, #0
70000d1c:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70000d20:	bf08      	it	eq
70000d22:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70000d26:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
70000d2a:	fabc f28c 	clz	r2, ip
70000d2e:	3a08      	subs	r2, #8
70000d30:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
70000d34:	db10      	blt.n	70000d58 <__aeabi_l2f+0x5c>
70000d36:	fa01 fc02 	lsl.w	ip, r1, r2
70000d3a:	4463      	add	r3, ip
70000d3c:	fa00 fc02 	lsl.w	ip, r0, r2
70000d40:	f1c2 0220 	rsb	r2, r2, #32
70000d44:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000d48:	fa20 f202 	lsr.w	r2, r0, r2
70000d4c:	eb43 0002 	adc.w	r0, r3, r2
70000d50:	bf08      	it	eq
70000d52:	f020 0001 	biceq.w	r0, r0, #1
70000d56:	4770      	bx	lr
70000d58:	f102 0220 	add.w	r2, r2, #32
70000d5c:	fa01 fc02 	lsl.w	ip, r1, r2
70000d60:	f1c2 0220 	rsb	r2, r2, #32
70000d64:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
70000d68:	fa21 f202 	lsr.w	r2, r1, r2
70000d6c:	eb43 0002 	adc.w	r0, r3, r2
70000d70:	bf08      	it	eq
70000d72:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000d76:	4770      	bx	lr

70000d78 <__aeabi_fmul>:
70000d78:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000d7c:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000d80:	bf1e      	ittt	ne
70000d82:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000d86:	ea92 0f0c 	teqne	r2, ip
70000d8a:	ea93 0f0c 	teqne	r3, ip
70000d8e:	d06f      	beq.n	70000e70 <__aeabi_fmul+0xf8>
70000d90:	441a      	add	r2, r3
70000d92:	ea80 0c01 	eor.w	ip, r0, r1
70000d96:	0240      	lsls	r0, r0, #9
70000d98:	bf18      	it	ne
70000d9a:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000d9e:	d01e      	beq.n	70000dde <__aeabi_fmul+0x66>
70000da0:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000da4:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000da8:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000dac:	fba0 3101 	umull	r3, r1, r0, r1
70000db0:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000db4:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000db8:	bf3e      	ittt	cc
70000dba:	0049      	lslcc	r1, r1, #1
70000dbc:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000dc0:	005b      	lslcc	r3, r3, #1
70000dc2:	ea40 0001 	orr.w	r0, r0, r1
70000dc6:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000dca:	2afd      	cmp	r2, #253	; 0xfd
70000dcc:	d81d      	bhi.n	70000e0a <__aeabi_fmul+0x92>
70000dce:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000dd2:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000dd6:	bf08      	it	eq
70000dd8:	f020 0001 	biceq.w	r0, r0, #1
70000ddc:	4770      	bx	lr
70000dde:	f090 0f00 	teq	r0, #0
70000de2:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000de6:	bf08      	it	eq
70000de8:	0249      	lsleq	r1, r1, #9
70000dea:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000dee:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000df2:	3a7f      	subs	r2, #127	; 0x7f
70000df4:	bfc2      	ittt	gt
70000df6:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000dfa:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000dfe:	4770      	bxgt	lr
70000e00:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000e04:	f04f 0300 	mov.w	r3, #0
70000e08:	3a01      	subs	r2, #1
70000e0a:	dc5d      	bgt.n	70000ec8 <__aeabi_fmul+0x150>
70000e0c:	f112 0f19 	cmn.w	r2, #25
70000e10:	bfdc      	itt	le
70000e12:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000e16:	4770      	bxle	lr
70000e18:	f1c2 0200 	rsb	r2, r2, #0
70000e1c:	0041      	lsls	r1, r0, #1
70000e1e:	fa21 f102 	lsr.w	r1, r1, r2
70000e22:	f1c2 0220 	rsb	r2, r2, #32
70000e26:	fa00 fc02 	lsl.w	ip, r0, r2
70000e2a:	ea5f 0031 	movs.w	r0, r1, rrx
70000e2e:	f140 0000 	adc.w	r0, r0, #0
70000e32:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000e36:	bf08      	it	eq
70000e38:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000e3c:	4770      	bx	lr
70000e3e:	f092 0f00 	teq	r2, #0
70000e42:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000e46:	bf02      	ittt	eq
70000e48:	0040      	lsleq	r0, r0, #1
70000e4a:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000e4e:	3a01      	subeq	r2, #1
70000e50:	d0f9      	beq.n	70000e46 <__aeabi_fmul+0xce>
70000e52:	ea40 000c 	orr.w	r0, r0, ip
70000e56:	f093 0f00 	teq	r3, #0
70000e5a:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000e5e:	bf02      	ittt	eq
70000e60:	0049      	lsleq	r1, r1, #1
70000e62:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000e66:	3b01      	subeq	r3, #1
70000e68:	d0f9      	beq.n	70000e5e <__aeabi_fmul+0xe6>
70000e6a:	ea41 010c 	orr.w	r1, r1, ip
70000e6e:	e78f      	b.n	70000d90 <__aeabi_fmul+0x18>
70000e70:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000e74:	ea92 0f0c 	teq	r2, ip
70000e78:	bf18      	it	ne
70000e7a:	ea93 0f0c 	teqne	r3, ip
70000e7e:	d00a      	beq.n	70000e96 <__aeabi_fmul+0x11e>
70000e80:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000e84:	bf18      	it	ne
70000e86:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000e8a:	d1d8      	bne.n	70000e3e <__aeabi_fmul+0xc6>
70000e8c:	ea80 0001 	eor.w	r0, r0, r1
70000e90:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000e94:	4770      	bx	lr
70000e96:	f090 0f00 	teq	r0, #0
70000e9a:	bf17      	itett	ne
70000e9c:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000ea0:	4608      	moveq	r0, r1
70000ea2:	f091 0f00 	teqne	r1, #0
70000ea6:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000eaa:	d014      	beq.n	70000ed6 <__aeabi_fmul+0x15e>
70000eac:	ea92 0f0c 	teq	r2, ip
70000eb0:	d101      	bne.n	70000eb6 <__aeabi_fmul+0x13e>
70000eb2:	0242      	lsls	r2, r0, #9
70000eb4:	d10f      	bne.n	70000ed6 <__aeabi_fmul+0x15e>
70000eb6:	ea93 0f0c 	teq	r3, ip
70000eba:	d103      	bne.n	70000ec4 <__aeabi_fmul+0x14c>
70000ebc:	024b      	lsls	r3, r1, #9
70000ebe:	bf18      	it	ne
70000ec0:	4608      	movne	r0, r1
70000ec2:	d108      	bne.n	70000ed6 <__aeabi_fmul+0x15e>
70000ec4:	ea80 0001 	eor.w	r0, r0, r1
70000ec8:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000ecc:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000ed0:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000ed4:	4770      	bx	lr
70000ed6:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000eda:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000ede:	4770      	bx	lr

70000ee0 <__aeabi_fdiv>:
70000ee0:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000ee4:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000ee8:	bf1e      	ittt	ne
70000eea:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000eee:	ea92 0f0c 	teqne	r2, ip
70000ef2:	ea93 0f0c 	teqne	r3, ip
70000ef6:	d069      	beq.n	70000fcc <__aeabi_fdiv+0xec>
70000ef8:	eba2 0203 	sub.w	r2, r2, r3
70000efc:	ea80 0c01 	eor.w	ip, r0, r1
70000f00:	0249      	lsls	r1, r1, #9
70000f02:	ea4f 2040 	mov.w	r0, r0, lsl #9
70000f06:	d037      	beq.n	70000f78 <__aeabi_fdiv+0x98>
70000f08:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70000f0c:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70000f10:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70000f14:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000f18:	428b      	cmp	r3, r1
70000f1a:	bf38      	it	cc
70000f1c:	005b      	lslcc	r3, r3, #1
70000f1e:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70000f22:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70000f26:	428b      	cmp	r3, r1
70000f28:	bf24      	itt	cs
70000f2a:	1a5b      	subcs	r3, r3, r1
70000f2c:	ea40 000c 	orrcs.w	r0, r0, ip
70000f30:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70000f34:	bf24      	itt	cs
70000f36:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
70000f3a:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70000f3e:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70000f42:	bf24      	itt	cs
70000f44:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
70000f48:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
70000f4c:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
70000f50:	bf24      	itt	cs
70000f52:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
70000f56:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
70000f5a:	011b      	lsls	r3, r3, #4
70000f5c:	bf18      	it	ne
70000f5e:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70000f62:	d1e0      	bne.n	70000f26 <__aeabi_fdiv+0x46>
70000f64:	2afd      	cmp	r2, #253	; 0xfd
70000f66:	f63f af50 	bhi.w	70000e0a <__aeabi_fmul+0x92>
70000f6a:	428b      	cmp	r3, r1
70000f6c:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000f70:	bf08      	it	eq
70000f72:	f020 0001 	biceq.w	r0, r0, #1
70000f76:	4770      	bx	lr
70000f78:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000f7c:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000f80:	327f      	adds	r2, #127	; 0x7f
70000f82:	bfc2      	ittt	gt
70000f84:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000f88:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000f8c:	4770      	bxgt	lr
70000f8e:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000f92:	f04f 0300 	mov.w	r3, #0
70000f96:	3a01      	subs	r2, #1
70000f98:	e737      	b.n	70000e0a <__aeabi_fmul+0x92>
70000f9a:	f092 0f00 	teq	r2, #0
70000f9e:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000fa2:	bf02      	ittt	eq
70000fa4:	0040      	lsleq	r0, r0, #1
70000fa6:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000faa:	3a01      	subeq	r2, #1
70000fac:	d0f9      	beq.n	70000fa2 <__aeabi_fdiv+0xc2>
70000fae:	ea40 000c 	orr.w	r0, r0, ip
70000fb2:	f093 0f00 	teq	r3, #0
70000fb6:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000fba:	bf02      	ittt	eq
70000fbc:	0049      	lsleq	r1, r1, #1
70000fbe:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000fc2:	3b01      	subeq	r3, #1
70000fc4:	d0f9      	beq.n	70000fba <__aeabi_fdiv+0xda>
70000fc6:	ea41 010c 	orr.w	r1, r1, ip
70000fca:	e795      	b.n	70000ef8 <__aeabi_fdiv+0x18>
70000fcc:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000fd0:	ea92 0f0c 	teq	r2, ip
70000fd4:	d108      	bne.n	70000fe8 <__aeabi_fdiv+0x108>
70000fd6:	0242      	lsls	r2, r0, #9
70000fd8:	f47f af7d 	bne.w	70000ed6 <__aeabi_fmul+0x15e>
70000fdc:	ea93 0f0c 	teq	r3, ip
70000fe0:	f47f af70 	bne.w	70000ec4 <__aeabi_fmul+0x14c>
70000fe4:	4608      	mov	r0, r1
70000fe6:	e776      	b.n	70000ed6 <__aeabi_fmul+0x15e>
70000fe8:	ea93 0f0c 	teq	r3, ip
70000fec:	d104      	bne.n	70000ff8 <__aeabi_fdiv+0x118>
70000fee:	024b      	lsls	r3, r1, #9
70000ff0:	f43f af4c 	beq.w	70000e8c <__aeabi_fmul+0x114>
70000ff4:	4608      	mov	r0, r1
70000ff6:	e76e      	b.n	70000ed6 <__aeabi_fmul+0x15e>
70000ff8:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000ffc:	bf18      	it	ne
70000ffe:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70001002:	d1ca      	bne.n	70000f9a <__aeabi_fdiv+0xba>
70001004:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70001008:	f47f af5c 	bne.w	70000ec4 <__aeabi_fmul+0x14c>
7000100c:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70001010:	f47f af3c 	bne.w	70000e8c <__aeabi_fmul+0x114>
70001014:	e75f      	b.n	70000ed6 <__aeabi_fmul+0x15e>
70001016:	bf00      	nop

70001018 <__gesf2>:
70001018:	f04f 3cff 	mov.w	ip, #4294967295
7000101c:	e006      	b.n	7000102c <__cmpsf2+0x4>
7000101e:	bf00      	nop

70001020 <__lesf2>:
70001020:	f04f 0c01 	mov.w	ip, #1
70001024:	e002      	b.n	7000102c <__cmpsf2+0x4>
70001026:	bf00      	nop

70001028 <__cmpsf2>:
70001028:	f04f 0c01 	mov.w	ip, #1
7000102c:	f84d cd04 	str.w	ip, [sp, #-4]!
70001030:	ea4f 0240 	mov.w	r2, r0, lsl #1
70001034:	ea4f 0341 	mov.w	r3, r1, lsl #1
70001038:	ea7f 6c22 	mvns.w	ip, r2, asr #24
7000103c:	bf18      	it	ne
7000103e:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70001042:	d011      	beq.n	70001068 <__cmpsf2+0x40>
70001044:	b001      	add	sp, #4
70001046:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
7000104a:	bf18      	it	ne
7000104c:	ea90 0f01 	teqne	r0, r1
70001050:	bf58      	it	pl
70001052:	ebb2 0003 	subspl.w	r0, r2, r3
70001056:	bf88      	it	hi
70001058:	17c8      	asrhi	r0, r1, #31
7000105a:	bf38      	it	cc
7000105c:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70001060:	bf18      	it	ne
70001062:	f040 0001 	orrne.w	r0, r0, #1
70001066:	4770      	bx	lr
70001068:	ea7f 6c22 	mvns.w	ip, r2, asr #24
7000106c:	d102      	bne.n	70001074 <__cmpsf2+0x4c>
7000106e:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70001072:	d105      	bne.n	70001080 <__cmpsf2+0x58>
70001074:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70001078:	d1e4      	bne.n	70001044 <__cmpsf2+0x1c>
7000107a:	ea5f 2c41 	movs.w	ip, r1, lsl #9
7000107e:	d0e1      	beq.n	70001044 <__cmpsf2+0x1c>
70001080:	f85d 0b04 	ldr.w	r0, [sp], #4
70001084:	4770      	bx	lr
70001086:	bf00      	nop

70001088 <__aeabi_cfrcmple>:
70001088:	4684      	mov	ip, r0
7000108a:	4608      	mov	r0, r1
7000108c:	4661      	mov	r1, ip
7000108e:	e7ff      	b.n	70001090 <__aeabi_cfcmpeq>

70001090 <__aeabi_cfcmpeq>:
70001090:	b50f      	push	{r0, r1, r2, r3, lr}
70001092:	f7ff ffc9 	bl	70001028 <__cmpsf2>
70001096:	2800      	cmp	r0, #0
70001098:	bf48      	it	mi
7000109a:	f110 0f00 	cmnmi.w	r0, #0
7000109e:	bd0f      	pop	{r0, r1, r2, r3, pc}

700010a0 <__aeabi_fcmpeq>:
700010a0:	f84d ed08 	str.w	lr, [sp, #-8]!
700010a4:	f7ff fff4 	bl	70001090 <__aeabi_cfcmpeq>
700010a8:	bf0c      	ite	eq
700010aa:	2001      	moveq	r0, #1
700010ac:	2000      	movne	r0, #0
700010ae:	f85d fb08 	ldr.w	pc, [sp], #8
700010b2:	bf00      	nop

700010b4 <__aeabi_fcmplt>:
700010b4:	f84d ed08 	str.w	lr, [sp, #-8]!
700010b8:	f7ff ffea 	bl	70001090 <__aeabi_cfcmpeq>
700010bc:	bf34      	ite	cc
700010be:	2001      	movcc	r0, #1
700010c0:	2000      	movcs	r0, #0
700010c2:	f85d fb08 	ldr.w	pc, [sp], #8
700010c6:	bf00      	nop

700010c8 <__aeabi_fcmple>:
700010c8:	f84d ed08 	str.w	lr, [sp, #-8]!
700010cc:	f7ff ffe0 	bl	70001090 <__aeabi_cfcmpeq>
700010d0:	bf94      	ite	ls
700010d2:	2001      	movls	r0, #1
700010d4:	2000      	movhi	r0, #0
700010d6:	f85d fb08 	ldr.w	pc, [sp], #8
700010da:	bf00      	nop

700010dc <__aeabi_fcmpge>:
700010dc:	f84d ed08 	str.w	lr, [sp, #-8]!
700010e0:	f7ff ffd2 	bl	70001088 <__aeabi_cfrcmple>
700010e4:	bf94      	ite	ls
700010e6:	2001      	movls	r0, #1
700010e8:	2000      	movhi	r0, #0
700010ea:	f85d fb08 	ldr.w	pc, [sp], #8
700010ee:	bf00      	nop

700010f0 <__aeabi_fcmpgt>:
700010f0:	f84d ed08 	str.w	lr, [sp, #-8]!
700010f4:	f7ff ffc8 	bl	70001088 <__aeabi_cfrcmple>
700010f8:	bf34      	ite	cc
700010fa:	2001      	movcc	r0, #1
700010fc:	2000      	movcs	r0, #0
700010fe:	f85d fb08 	ldr.w	pc, [sp], #8
70001102:	bf00      	nop

70001104 <__aeabi_f2uiz>:
70001104:	0042      	lsls	r2, r0, #1
70001106:	d20e      	bcs.n	70001126 <__aeabi_f2uiz+0x22>
70001108:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
7000110c:	d30b      	bcc.n	70001126 <__aeabi_f2uiz+0x22>
7000110e:	f04f 039e 	mov.w	r3, #158	; 0x9e
70001112:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70001116:	d409      	bmi.n	7000112c <__aeabi_f2uiz+0x28>
70001118:	ea4f 2300 	mov.w	r3, r0, lsl #8
7000111c:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70001120:	fa23 f002 	lsr.w	r0, r3, r2
70001124:	4770      	bx	lr
70001126:	f04f 0000 	mov.w	r0, #0
7000112a:	4770      	bx	lr
7000112c:	f112 0f61 	cmn.w	r2, #97	; 0x61
70001130:	d101      	bne.n	70001136 <__aeabi_f2uiz+0x32>
70001132:	0242      	lsls	r2, r0, #9
70001134:	d102      	bne.n	7000113c <__aeabi_f2uiz+0x38>
70001136:	f04f 30ff 	mov.w	r0, #4294967295
7000113a:	4770      	bx	lr
7000113c:	f04f 0000 	mov.w	r0, #0
70001140:	4770      	bx	lr
70001142:	bf00      	nop
