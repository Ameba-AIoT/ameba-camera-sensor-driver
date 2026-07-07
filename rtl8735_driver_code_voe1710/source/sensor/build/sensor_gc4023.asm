
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	bd 06 00 70 c5 02 00 70                             ...p...p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

70000060 <g_gc4023_i2c_init_regs>:
70000060:	fe 03 f0 00 fe 03 00 00 fe 03 10 00 fe 03 00 00     ................
70000070:	38 0a 00 00 38 0a 01 00 20 0a 17 00 1c 06 50 00     8...8... .....P.
70000080:	1d 06 21 00 1e 06 6c 00 1f 06 06 00 21 0a 10 00     ..!...l.....!...
70000090:	34 0a 40 00 35 0a 01 00 36 0a 58 00 37 0a 06 00     4.@.5...6.X.7...
700000a0:	14 03 50 00 15 03 00 00 1c 03 ce 00 19 02 47 00     ..P...........G.
700000b0:	42 03 04 00 43 03 b0 00 59 02 05 00 5a 02 a0 00     B...C...Y...Z...
700000c0:	40 03 05 00 41 03 dc 00 47 03 02 00 48 03 0a 00     @...A...G...H...
700000d0:	49 03 08 00 4a 03 05 00 4b 03 a8 00 94 00 0a 00     I...J...K.......
700000e0:	95 00 08 00 96 00 05 00 97 00 a8 00 99 00 00 00     ................
700000f0:	9b 00 00 00 0c 06 01 00 0e 06 08 00 0f 06 05 00     ................
70000100:	0c 07 01 00 0e 07 08 00 0f 07 05 00 09 09 03 00     ................
70000110:	02 09 04 00 04 09 0b 00 07 09 54 00 08 09 06 00     ..........T.....
70000120:	03 09 9d 00 2a 07 18 00 24 07 0a 00 27 07 0a 00     ....*...$...'...
70000130:	2a 07 1c 00 2b 07 0a 00 66 14 10 00 68 14 15 00     *...+...f...h...
70000140:	67 14 0d 00 69 14 80 00 6a 14 e8 00 07 07 07 00     g...i...j.......
70000150:	37 07 0f 00 04 07 01 00 06 07 02 00 16 07 02 00     7...............
70000160:	08 07 c8 00 18 07 c8 00 1a 06 00 00 30 14 80 00     ............0...
70000170:	07 14 10 00 08 14 16 00 09 14 03 00 6d 14 0e 00     ............m...
70000180:	6e 14 42 00 6f 14 43 00 70 14 3c 00 71 14 3d 00     n.B.o.C.p.<.q.=.
70000190:	72 14 3a 00 73 14 3a 00 74 14 40 00 75 14 46 00     r.:.s.:.t.@.u.F.
700001a0:	20 14 14 00 64 14 15 00 6c 14 40 00 6d 14 40 00      ...d...l.@.m.@.
700001b0:	23 14 08 00 28 14 10 00 62 14 18 00 ce 02 04 00     #...(...b.......
700001c0:	3a 14 0f 00 2b 14 88 00 45 02 c9 00 3a 02 08 00     :...+...E...:...
700001d0:	cd 02 99 00 12 06 02 00 13 06 c7 00 43 02 03 00     ............C...
700001e0:	1b 02 09 00 89 00 03 00 40 00 a3 00 75 00 64 00     ........@...u.d.
700001f0:	04 00 0f 00 02 00 ab 00 53 00 0a 00 05 02 0c 00     ........S.......
70000200:	02 02 06 00 03 02 27 00 14 06 00 00 15 06 00 00     ......'.........
70000210:	81 01 0c 00 82 01 05 00 85 01 01 00 80 01 42 00     ..............B.
70000220:	00 01 08 00 06 01 38 00 0d 01 8a 00 0e 01 0c 00     ......8.........
70000230:	13 01 02 00 14 01 01 00 15 01 10 00 2c 02 03 00     ............,...
70000240:	00 01 09 00 52 00 02 00 76 00 01 00 1a 02 10 00     ....R...v.......
70000250:	34 04 75 00 35 04 75 00 36 04 75 00 37 04 75 00     4.u.5.u.6.u.7.u.
70000260:	30 04 0a 00 31 04 0a 00 32 04 0a 00 33 04 0a 00     0...1...2...3...
70000270:	58 04 00 00 59 04 00 00 5a 04 00 00 5b 04 00 00     X...Y...Z...[...
70000280:	67 0a 80 00 54 0a 0e 00 65 0a 10 00 98 0a 10 00     g...T...e.......
70000290:	be 05 00 00 a9 05 01 00 29 00 08 00 2b 00 a8 00     ........)...+...
700002a0:	83 0a e0 00 72 0a 02 00 73 0a 60 00 75 0a 41 00     ....r...s.`.u.A.
700002b0:	70 0a 03 00 5a 0a 80 00                             p...Z...

700002b8 <real_slave_addr>:
700002b8:	29 00 00 00                                         )...

700002bc <slave_addr_list>:
700002bc:	29 00 00 00 10 00 00 00                             ).......

700002c4 <rts_isp_set_voe_ops>:
700002c4:	4b01      	ldr	r3, [pc, #4]	; (700002cc <rts_isp_set_voe_ops+0x8>)
700002c6:	6018      	str	r0, [r3, #0]
700002c8:	4770      	bx	lr
700002ca:	bf00      	nop
700002cc:	70000048 	.word	0x70000048

700002d0 <isp_driver_is_fpga>:
700002d0:	2000      	movs	r0, #0
700002d2:	4770      	bx	lr

700002d4 <gc4023_get_info>:
700002d4:	b530      	push	{r4, r5, lr}
700002d6:	2800      	cmp	r0, #0
700002d8:	d14c      	bne.n	70000374 <gc4023_get_info+0xa0>
700002da:	2900      	cmp	r1, #0
700002dc:	d04a      	beq.n	70000374 <gc4023_get_info+0xa0>
700002de:	f44f 6220 	mov.w	r2, #2560	; 0xa00
700002e2:	f44f 63b4 	mov.w	r3, #1440	; 0x5a0
700002e6:	4d25      	ldr	r5, [pc, #148]	; (7000037c <gc4023_get_info+0xa8>)
700002e8:	2403      	movs	r4, #3
700002ea:	7108      	strb	r0, [r1, #4]
700002ec:	f881 40a4 	strb.w	r4, [r1, #164]	; 0xa4
700002f0:	f8c1 00a8 	str.w	r0, [r1, #168]	; 0xa8
700002f4:	f881 40b0 	strb.w	r4, [r1, #176]	; 0xb0
700002f8:	f881 00c8 	strb.w	r0, [r1, #200]	; 0xc8
700002fc:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
70000300:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
70000304:	e9c1 2302 	strd	r2, r3, [r1, #8]
70000308:	4b1d      	ldr	r3, [pc, #116]	; (70000380 <gc4023_get_info+0xac>)
7000030a:	2201      	movs	r2, #1
7000030c:	610b      	str	r3, [r1, #16]
7000030e:	4b1d      	ldr	r3, [pc, #116]	; (70000384 <gc4023_get_info+0xb0>)
70000310:	600a      	str	r2, [r1, #0]
70000312:	681b      	ldr	r3, [r3, #0]
70000314:	f881 2098 	strb.w	r2, [r1, #152]	; 0x98
70000318:	f881 3085 	strb.w	r3, [r1, #133]	; 0x85
7000031c:	4b1a      	ldr	r3, [pc, #104]	; (70000388 <gc4023_get_info+0xb4>)
7000031e:	f881 20bc 	strb.w	r2, [r1, #188]	; 0xbc
70000322:	781b      	ldrb	r3, [r3, #0]
70000324:	f881 3084 	strb.w	r3, [r1, #132]	; 0x84
70000328:	f44f 737a 	mov.w	r3, #1000	; 0x3e8
7000032c:	e9c1 532d 	strd	r5, r3, [r1, #180]	; 0xb4
70000330:	f44f 7581 	mov.w	r5, #258	; 0x102
70000334:	f8c1 30ac 	str.w	r3, [r1, #172]	; 0xac
70000338:	f8a1 5086 	strh.w	r5, [r1, #134]	; 0x86
7000033c:	2506      	movs	r5, #6
7000033e:	e9c1 2330 	strd	r2, r3, [r1, #192]	; 0xc0
70000342:	e9c1 2333 	strd	r2, r3, [r1, #204]	; 0xcc
70000346:	e9c1 03b7 	strd	r0, r3, [r1, #732]	; 0x2dc
7000034a:	e9c1 0024 	strd	r0, r0, [r1, #144]	; 0x90
7000034e:	e9c1 0027 	strd	r0, r0, [r1, #156]	; 0x9c
70000352:	f8c1 5088 	str.w	r5, [r1, #136]	; 0x88
70000356:	f881 22e4 	strb.w	r2, [r1, #740]	; 0x2e4
7000035a:	f881 42f0 	strb.w	r4, [r1, #752]	; 0x2f0
7000035e:	f8c1 02f4 	str.w	r0, [r1, #756]	; 0x2f4
70000362:	f8c1 42d4 	str.w	r4, [r1, #724]	; 0x2d4
70000366:	e9c1 03ba 	strd	r0, r3, [r1, #744]	; 0x2e8
7000036a:	f640 33b8 	movw	r3, #3000	; 0xbb8
7000036e:	f8c1 32f8 	str.w	r3, [r1, #760]	; 0x2f8
70000372:	bd30      	pop	{r4, r5, pc}
70000374:	f06f 0015 	mvn.w	r0, #21
70000378:	e7fb      	b.n	70000372 <gc4023_get_info+0x9e>
7000037a:	bf00      	nop
7000037c:	016e3600 	.word	0x016e3600
70000380:	41f00000 	.word	0x41f00000
70000384:	700002b8 	.word	0x700002b8
70000388:	7000004c 	.word	0x7000004c

7000038c <gc4023_get_init_info>:
7000038c:	b570      	push	{r4, r5, r6, lr}
7000038e:	4614      	mov	r4, r2
70000390:	4605      	mov	r5, r0
70000392:	b110      	cbz	r0, 7000039a <gc4023_get_init_info+0xe>
70000394:	f06f 0015 	mvn.w	r0, #21
70000398:	bd70      	pop	{r4, r5, r6, pc}
7000039a:	2a00      	cmp	r2, #0
7000039c:	d0fa      	beq.n	70000394 <gc4023_get_init_info+0x8>
7000039e:	780b      	ldrb	r3, [r1, #0]
700003a0:	4e1c      	ldr	r6, [pc, #112]	; (70000414 <gc4023_get_init_info+0x88>)
700003a2:	68c8      	ldr	r0, [r1, #12]
700003a4:	7033      	strb	r3, [r6, #0]
700003a6:	f000 fdb5 	bl	70000f14 <__aeabi_f2uiz>
700003aa:	b280      	uxth	r0, r0
700003ac:	f000 fb98 	bl	70000ae0 <__aeabi_i2f>
700003b0:	4919      	ldr	r1, [pc, #100]	; (70000418 <gc4023_get_init_info+0x8c>)
700003b2:	f000 fd7d 	bl	70000eb0 <__aeabi_fcmpeq>
700003b6:	2800      	cmp	r0, #0
700003b8:	d0ec      	beq.n	70000394 <gc4023_get_init_info+0x8>
700003ba:	4b18      	ldr	r3, [pc, #96]	; (7000041c <gc4023_get_init_info+0x90>)
700003bc:	f640 2208 	movw	r2, #2568	; 0xa08
700003c0:	f44f 5196 	mov.w	r1, #4800	; 0x12c0
700003c4:	60a5      	str	r5, [r4, #8]
700003c6:	6063      	str	r3, [r4, #4]
700003c8:	2396      	movs	r3, #150	; 0x96
700003ca:	4628      	mov	r0, r5
700003cc:	6023      	str	r3, [r4, #0]
700003ce:	2302      	movs	r3, #2
700003d0:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
700003d4:	f240 6303 	movw	r3, #1539	; 0x603
700003d8:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
700003dc:	230a      	movs	r3, #10
700003de:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
700003e2:	2304      	movs	r3, #4
700003e4:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
700003e8:	f44f 63b5 	mov.w	r3, #1448	; 0x5a8
700003ec:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
700003f0:	2301      	movs	r3, #1
700003f2:	f242 3228 	movw	r2, #9000	; 0x2328
700003f6:	e9c4 3522 	strd	r3, r5, [r4, #136]	; 0x88
700003fa:	4b09      	ldr	r3, [pc, #36]	; (70000420 <gc4023_get_init_info+0x94>)
700003fc:	e9c4 3124 	strd	r3, r1, [r4, #144]	; 0x90
70000400:	f240 53dc 	movw	r3, #1500	; 0x5dc
70000404:	e9c4 3226 	strd	r3, r2, [r4, #152]	; 0x98
70000408:	6073      	str	r3, [r6, #4]
7000040a:	2300      	movs	r3, #0
7000040c:	4a05      	ldr	r2, [pc, #20]	; (70000424 <gc4023_get_init_info+0x98>)
7000040e:	60f3      	str	r3, [r6, #12]
70000410:	60b2      	str	r2, [r6, #8]
70000412:	e7c1      	b.n	70000398 <gc4023_get_init_info+0xc>
70000414:	7000004c 	.word	0x7000004c
70000418:	41f00000 	.word	0x41f00000
7000041c:	70000060 	.word	0x70000060
70000420:	0cdfe600 	.word	0x0cdfe600
70000424:	41b1c71c 	.word	0x41b1c71c

70000428 <gc4023_start>:
70000428:	b918      	cbnz	r0, 70000432 <gc4023_start+0xa>
7000042a:	4b03      	ldr	r3, [pc, #12]	; (70000438 <gc4023_start+0x10>)
7000042c:	2200      	movs	r2, #0
7000042e:	60da      	str	r2, [r3, #12]
70000430:	4770      	bx	lr
70000432:	f06f 0015 	mvn.w	r0, #21
70000436:	4770      	bx	lr
70000438:	7000004c 	.word	0x7000004c

7000043c <gc4023_get_tuned_dgain>:
7000043c:	b920      	cbnz	r0, 70000448 <gc4023_get_tuned_dgain+0xc>
7000043e:	b119      	cbz	r1, 70000448 <gc4023_get_tuned_dgain+0xc>
70000440:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
70000444:	600b      	str	r3, [r1, #0]
70000446:	4770      	bx	lr
70000448:	f06f 0015 	mvn.w	r0, #21
7000044c:	4770      	bx	lr
	...

70000450 <gc4023_get_exposure_gain_info>:
70000450:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
70000454:	4615      	mov	r5, r2
70000456:	2800      	cmp	r0, #0
70000458:	f040 808f 	bne.w	7000057a <gc4023_get_exposure_gain_info+0x12a>
7000045c:	2900      	cmp	r1, #0
7000045e:	f000 808c 	beq.w	7000057a <gc4023_get_exposure_gain_info+0x12a>
70000462:	2a00      	cmp	r2, #0
70000464:	f000 8089 	beq.w	7000057a <gc4023_get_exposure_gain_info+0x12a>
70000468:	f8d1 8000 	ldr.w	r8, [r1]
7000046c:	1d14      	adds	r4, r2, #4
7000046e:	4f44      	ldr	r7, [pc, #272]	; (70000580 <gc4023_get_exposure_gain_info+0x130>)
70000470:	698e      	ldr	r6, [r1, #24]
70000472:	4641      	mov	r1, r8
70000474:	68f8      	ldr	r0, [r7, #12]
70000476:	f000 fa7d 	bl	70000974 <__aeabi_fsub>
7000047a:	2100      	movs	r1, #0
7000047c:	4681      	mov	r9, r0
7000047e:	f000 fd35 	bl	70000eec <__aeabi_fcmpge>
70000482:	2800      	cmp	r0, #0
70000484:	d074      	beq.n	70000570 <gc4023_get_exposure_gain_info+0x120>
70000486:	493f      	ldr	r1, [pc, #252]	; (70000584 <gc4023_get_exposure_gain_info+0x134>)
70000488:	4648      	mov	r0, r9
7000048a:	f000 fd39 	bl	70000f00 <__aeabi_fcmpgt>
7000048e:	b1b8      	cbz	r0, 700004c0 <gc4023_get_exposure_gain_info+0x70>
70000490:	68b9      	ldr	r1, [r7, #8]
70000492:	4640      	mov	r0, r8
70000494:	f000 fc2c 	bl	70000cf0 <__aeabi_fdiv>
70000498:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
7000049c:	f000 fa6c 	bl	70000978 <__addsf3>
700004a0:	f000 fd38 	bl	70000f14 <__aeabi_f2uiz>
700004a4:	f240 2302 	movw	r3, #514	; 0x202
700004a8:	81ab      	strh	r3, [r5, #12]
700004aa:	f3c0 2307 	ubfx	r3, r0, #8, #8
700004ae:	b2c0      	uxtb	r0, r0
700004b0:	81eb      	strh	r3, [r5, #14]
700004b2:	f240 2303 	movw	r3, #515	; 0x203
700004b6:	8468      	strh	r0, [r5, #34]	; 0x22
700004b8:	2002      	movs	r0, #2
700004ba:	842b      	strh	r3, [r5, #32]
700004bc:	f8c7 800c 	str.w	r8, [r7, #12]
700004c0:	6939      	ldr	r1, [r7, #16]
700004c2:	220a      	movs	r2, #10
700004c4:	2314      	movs	r3, #20
700004c6:	4f30      	ldr	r7, [pc, #192]	; (70000588 <gc4023_get_exposure_gain_info+0x138>)
700004c8:	4351      	muls	r1, r2
700004ca:	4343      	muls	r3, r0
700004cc:	3009      	adds	r0, #9
700004ce:	187a      	adds	r2, r7, r1
700004d0:	5c79      	ldrb	r1, [r7, r1]
700004d2:	eb04 0c03 	add.w	ip, r4, r3
700004d6:	f240 6714 	movw	r7, #1556	; 0x614
700004da:	f8ac 100a 	strh.w	r1, [ip, #10]
700004de:	f103 0114 	add.w	r1, r3, #20
700004e2:	f8ac 7008 	strh.w	r7, [ip, #8]
700004e6:	f240 6c15 	movw	ip, #1557	; 0x615
700004ea:	4421      	add	r1, r4
700004ec:	7857      	ldrb	r7, [r2, #1]
700004ee:	f8a1 c008 	strh.w	ip, [r1, #8]
700004f2:	f44f 7c06 	mov.w	ip, #536	; 0x218
700004f6:	814f      	strh	r7, [r1, #10]
700004f8:	f103 0128 	add.w	r1, r3, #40	; 0x28
700004fc:	7897      	ldrb	r7, [r2, #2]
700004fe:	4421      	add	r1, r4
70000500:	f8a1 c008 	strh.w	ip, [r1, #8]
70000504:	f241 4c67 	movw	ip, #5223	; 0x1467
70000508:	814f      	strh	r7, [r1, #10]
7000050a:	f103 013c 	add.w	r1, r3, #60	; 0x3c
7000050e:	78d7      	ldrb	r7, [r2, #3]
70000510:	4421      	add	r1, r4
70000512:	f8a1 c008 	strh.w	ip, [r1, #8]
70000516:	f241 4c68 	movw	ip, #5224	; 0x1468
7000051a:	814f      	strh	r7, [r1, #10]
7000051c:	f103 0150 	add.w	r1, r3, #80	; 0x50
70000520:	7917      	ldrb	r7, [r2, #4]
70000522:	4421      	add	r1, r4
70000524:	f8a1 c008 	strh.w	ip, [r1, #8]
70000528:	f04f 0cb8 	mov.w	ip, #184	; 0xb8
7000052c:	814f      	strh	r7, [r1, #10]
7000052e:	f103 0164 	add.w	r1, r3, #100	; 0x64
70000532:	7957      	ldrb	r7, [r2, #5]
70000534:	4421      	add	r1, r4
70000536:	7992      	ldrb	r2, [r2, #6]
70000538:	814f      	strh	r7, [r1, #10]
7000053a:	27b9      	movs	r7, #185	; 0xb9
7000053c:	f8a1 c008 	strh.w	ip, [r1, #8]
70000540:	f103 0178 	add.w	r1, r3, #120	; 0x78
70000544:	4421      	add	r1, r4
70000546:	814a      	strh	r2, [r1, #10]
70000548:	f103 028c 	add.w	r2, r3, #140	; 0x8c
7000054c:	810f      	strh	r7, [r1, #8]
7000054e:	f44f 7150 	mov.w	r1, #832	; 0x340
70000552:	4422      	add	r2, r4
70000554:	33a0      	adds	r3, #160	; 0xa0
70000556:	8111      	strh	r1, [r2, #8]
70000558:	0a31      	lsrs	r1, r6, #8
7000055a:	4423      	add	r3, r4
7000055c:	b2f6      	uxtb	r6, r6
7000055e:	8151      	strh	r1, [r2, #10]
70000560:	f240 3241 	movw	r2, #833	; 0x341
70000564:	815e      	strh	r6, [r3, #10]
70000566:	811a      	strh	r2, [r3, #8]
70000568:	6028      	str	r0, [r5, #0]
7000056a:	2000      	movs	r0, #0
7000056c:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
70000570:	4906      	ldr	r1, [pc, #24]	; (7000058c <gc4023_get_exposure_gain_info+0x13c>)
70000572:	4648      	mov	r0, r9
70000574:	f000 fca6 	bl	70000ec4 <__aeabi_fcmplt>
70000578:	e789      	b.n	7000048e <gc4023_get_exposure_gain_info+0x3e>
7000057a:	f06f 0015 	mvn.w	r0, #21
7000057e:	e7f5      	b.n	7000056c <gc4023_get_exposure_gain_info+0x11c>
70000580:	7000004c 	.word	0x7000004c
70000584:	3a83126f 	.word	0x3a83126f
70000588:	700006c4 	.word	0x700006c4
7000058c:	ba83126f 	.word	0xba83126f

70000590 <gc4023_set_mirror_flip>:
70000590:	784b      	ldrb	r3, [r1, #1]
70000592:	780a      	ldrb	r2, [r1, #0]
70000594:	2b00      	cmp	r3, #0
70000596:	bf14      	ite	ne
70000598:	2302      	movne	r3, #2
7000059a:	2300      	moveq	r3, #0
7000059c:	2a00      	cmp	r2, #0
7000059e:	bf18      	it	ne
700005a0:	f043 0301 	orrne.w	r3, r3, #1
700005a4:	2201      	movs	r2, #1
700005a6:	2b02      	cmp	r3, #2
700005a8:	708a      	strb	r2, [r1, #2]
700005aa:	d009      	beq.n	700005c0 <gc4023_set_mirror_flip+0x30>
700005ac:	2b03      	cmp	r3, #3
700005ae:	d00b      	beq.n	700005c8 <gc4023_set_mirror_flip+0x38>
700005b0:	4293      	cmp	r3, r2
700005b2:	d007      	beq.n	700005c4 <gc4023_set_mirror_flip+0x34>
700005b4:	4b06      	ldr	r3, [pc, #24]	; (700005d0 <gc4023_set_mirror_flip+0x40>)
700005b6:	610b      	str	r3, [r1, #16]
700005b8:	2301      	movs	r3, #1
700005ba:	2000      	movs	r0, #0
700005bc:	604b      	str	r3, [r1, #4]
700005be:	4770      	bx	lr
700005c0:	4b04      	ldr	r3, [pc, #16]	; (700005d4 <gc4023_set_mirror_flip+0x44>)
700005c2:	e7f8      	b.n	700005b6 <gc4023_set_mirror_flip+0x26>
700005c4:	4b04      	ldr	r3, [pc, #16]	; (700005d8 <gc4023_set_mirror_flip+0x48>)
700005c6:	e7f6      	b.n	700005b6 <gc4023_set_mirror_flip+0x26>
700005c8:	f44f 730b 	mov.w	r3, #556	; 0x22c
700005cc:	e7f3      	b.n	700005b6 <gc4023_set_mirror_flip+0x26>
700005ce:	bf00      	nop
700005d0:	0003022c 	.word	0x0003022c
700005d4:	0002022c 	.word	0x0002022c
700005d8:	0001022c 	.word	0x0001022c

700005dc <gc4023_check>:
700005dc:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
700005de:	4d19      	ldr	r5, [pc, #100]	; (70000644 <gc4023_check+0x68>)
700005e0:	4606      	mov	r6, r0
700005e2:	682b      	ldr	r3, [r5, #0]
700005e4:	685b      	ldr	r3, [r3, #4]
700005e6:	4798      	blx	r3
700005e8:	f44f 737c 	mov.w	r3, #1008	; 0x3f0
700005ec:	a901      	add	r1, sp, #4
700005ee:	4630      	mov	r0, r6
700005f0:	f8ad 3004 	strh.w	r3, [sp, #4]
700005f4:	682b      	ldr	r3, [r5, #0]
700005f6:	68db      	ldr	r3, [r3, #12]
700005f8:	4798      	blx	r3
700005fa:	4604      	mov	r4, r0
700005fc:	b128      	cbz	r0, 7000060a <gc4023_check+0x2e>
700005fe:	682b      	ldr	r3, [r5, #0]
70000600:	689b      	ldr	r3, [r3, #8]
70000602:	4798      	blx	r3
70000604:	4620      	mov	r0, r4
70000606:	b003      	add	sp, #12
70000608:	bdf0      	pop	{r4, r5, r6, r7, pc}
7000060a:	f240 33f1 	movw	r3, #1009	; 0x3f1
7000060e:	a901      	add	r1, sp, #4
70000610:	4630      	mov	r0, r6
70000612:	f8bd 7006 	ldrh.w	r7, [sp, #6]
70000616:	f8ad 3004 	strh.w	r3, [sp, #4]
7000061a:	682b      	ldr	r3, [r5, #0]
7000061c:	68db      	ldr	r3, [r3, #12]
7000061e:	4798      	blx	r3
70000620:	682b      	ldr	r3, [r5, #0]
70000622:	4604      	mov	r4, r0
70000624:	689b      	ldr	r3, [r3, #8]
70000626:	4798      	blx	r3
70000628:	2c00      	cmp	r4, #0
7000062a:	d1eb      	bne.n	70000604 <gc4023_check+0x28>
7000062c:	f8bd 3006 	ldrh.w	r3, [sp, #6]
70000630:	f244 0223 	movw	r2, #16419	; 0x4023
70000634:	ea43 2307 	orr.w	r3, r3, r7, lsl #8
70000638:	4293      	cmp	r3, r2
7000063a:	bf18      	it	ne
7000063c:	f06f 0415 	mvnne.w	r4, #21
70000640:	e7e0      	b.n	70000604 <gc4023_check+0x28>
70000642:	bf00      	nop
70000644:	70000048 	.word	0x70000048

70000648 <gc4023_get_slave_addr_num>:
70000648:	2002      	movs	r0, #2
7000064a:	4770      	bx	lr

7000064c <gc4023_get_tuned_again>:
7000064c:	b570      	push	{r4, r5, r6, lr}
7000064e:	460d      	mov	r5, r1
70000650:	4604      	mov	r4, r0
70000652:	bb60      	cbnz	r0, 700006ae <gc4023_get_tuned_again+0x62>
70000654:	b359      	cbz	r1, 700006ae <gc4023_get_tuned_again+0x62>
70000656:	f04f 4185 	mov.w	r1, #1115684864	; 0x42800000
7000065a:	6828      	ldr	r0, [r5, #0]
7000065c:	f000 fa94 	bl	70000b88 <__aeabi_fmul>
70000660:	f000 fc58 	bl	70000f14 <__aeabi_f2uiz>
70000664:	b280      	uxth	r0, r0
70000666:	f5b0 6f80 	cmp.w	r0, #1024	; 0x400
7000066a:	d30d      	bcc.n	70000688 <gc4023_get_tuned_again+0x3c>
7000066c:	4b11      	ldr	r3, [pc, #68]	; (700006b4 <gc4023_get_tuned_again+0x68>)
7000066e:	2210      	movs	r2, #16
70000670:	f44f 6080 	mov.w	r0, #1024	; 0x400
70000674:	611a      	str	r2, [r3, #16]
70000676:	f000 fa33 	bl	70000ae0 <__aeabi_i2f>
7000067a:	f04f 5172 	mov.w	r1, #1015021568	; 0x3c800000
7000067e:	f000 fa83 	bl	70000b88 <__aeabi_fmul>
70000682:	6028      	str	r0, [r5, #0]
70000684:	2000      	movs	r0, #0
70000686:	bd70      	pop	{r4, r5, r6, pc}
70000688:	4a0b      	ldr	r2, [pc, #44]	; (700006b8 <gc4023_get_tuned_again+0x6c>)
7000068a:	4623      	mov	r3, r4
7000068c:	8911      	ldrh	r1, [r2, #8]
7000068e:	461c      	mov	r4, r3
70000690:	3301      	adds	r3, #1
70000692:	4288      	cmp	r0, r1
70000694:	d306      	bcc.n	700006a4 <gc4023_get_tuned_again+0x58>
70000696:	8a56      	ldrh	r6, [r2, #18]
70000698:	4286      	cmp	r6, r0
7000069a:	d903      	bls.n	700006a4 <gc4023_get_tuned_again+0x58>
7000069c:	4b05      	ldr	r3, [pc, #20]	; (700006b4 <gc4023_get_tuned_again+0x68>)
7000069e:	4608      	mov	r0, r1
700006a0:	611c      	str	r4, [r3, #16]
700006a2:	e7e8      	b.n	70000676 <gc4023_get_tuned_again+0x2a>
700006a4:	2b10      	cmp	r3, #16
700006a6:	f102 020a 	add.w	r2, r2, #10
700006aa:	d1ef      	bne.n	7000068c <gc4023_get_tuned_again+0x40>
700006ac:	e7e3      	b.n	70000676 <gc4023_get_tuned_again+0x2a>
700006ae:	f06f 0015 	mvn.w	r0, #21
700006b2:	e7e8      	b.n	70000686 <gc4023_get_tuned_again+0x3a>
700006b4:	7000004c 	.word	0x7000004c
700006b8:	700006c4 	.word	0x700006c4

700006bc <rts_isp_get_sensor_ops>:
700006bc:	4800      	ldr	r0, [pc, #0]	; (700006c0 <rts_isp_get_sensor_ops+0x4>)
700006be:	4770      	bx	lr
700006c0:	70000770 	.word	0x70000770

700006c4 <g_gc4023_gain_config>:
700006c4:	0d000000 00000115 02800040 01150d00     ........@.......
700006d4:	004c000b 0d000001 00190115 0281005a     ..L.........Z...
700006e4:	01160e00 006a002a 0e000002 00000216     ....*.j.........
700006f4:	02820080 02170f00 00980017 10000003     ................
70000704:	00330218 028300b3 03191100 00d40014     ..3.............
70000714:	12000004 0000041a 02800100 041b1320     ............ ...
70000724:	012f002f 14200001 0026051c 02810166     /./... ...&.f...
70000734:	061d1520 01a90028 16200002 0000081e      ...(..... .....
70000744:	02820200 091e1620 025f001e 18200003     .... ....._... .
70000754:	000c0b20 028302cd 0d201820 03510011      ....... . ...Q.
70000764:	18200004 00001020 00000400              .. . .......

70000770 <gc4023_ops>:
70000770:	73000005 30346367 00003332 00000000     ...sgc4023......
	...
70000794:	700002d5 7000038d 00000000 7000064d     ...p...p....M..p
700007a4:	7000043d 70000451 00000000 00000000     =..pQ..p........
700007b4:	70000429 00000000 00000000 00000000     )..p............
700007c4:	70000591 00000000 00000000 00000000     ...p............
700007d4:	700005dd 00000000 00000000 00000000     ...p............
700007e4:	70000649 00000000 00000000 00000000     I..p............
	...
70000804:	0cfff04f 52d0ea1c ea1cbf1e ea9253d1     O......R.....S..
70000814:	ea930f0c d06f0f0c ea80441a 02400c01     ......o..D....@.
70000824:	ea5fbf18 d01e2141 6300f04f 1050ea43     .._.A!..O..cC.P.
70000834:	1151ea43 3101fba0 4000f00c 0f00f5b1     C.Q....1...@....
70000844:	0049bf3e 71d3ea41 ea40005b f1620001     >.I.A..q[.@...b.
70000854:	2afd027f f1b3d81d eb404f00 bf0850c2     ...*.....O@..P..
70000864:	0001f020 f0904770 f00c0f00 bf084c00      ...pG.......L..
70000874:	ea4c0249 ea402050 3a7f2051 f1d2bfc2     I.L.P @.Q .:....
70000884:	ea4003ff 477050c2 0000f440 0300f04f     ..@..PpG@...O...
70000894:	dc5d3a01 0f19f112 f000bfdc 47704000     .:]..........@pG
700008a4:	0200f1c2 fa210041 f1c2f102 fa000220     ....A.!..... ...
700008b4:	ea5ffc02 f1400031 ea530000 bf08034c     .._.1.@...S.L...
700008c4:	70dcea20 f0924770 f0000f00 bf024c00      ..ppG.......L..
700008d4:	f4100040 3a010f00 ea40d0f9 f093000c     @......:..@.....
700008e4:	f0010f00 bf024c00 f4110049 3b010f00     .....L..I......;
700008f4:	ea41d0f9 e78f010c 53d1ea0c 0f0cea92     ..A........S....
70000904:	ea93bf18 d00a0f0c 4c00f030 f031bf18     ........0..L..1.
70000914:	d1d84c00 0001ea80 4000f000 f0904770     .L.........@pG..
70000924:	bf170f00 4f00f090 f0914608 f0910f00     .......O.F......
70000934:	d0144f00 0f0cea92 0242d101 ea93d10f     .O........B.....
70000944:	d1030f0c bf18024b d1084608 0001ea80     ....K....F......
70000954:	4000f000 40fef040 0000f440 f0404770     ...@@..@@...pG@.
70000964:	f44040fe 47700040                       .@@.@.pG

7000096c <__aeabi_frsub>:
7000096c:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70000970:	e002      	b.n	70000978 <__addsf3>
70000972:	bf00      	nop

70000974 <__aeabi_fsub>:
70000974:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

70000978 <__addsf3>:
70000978:	0042      	lsls	r2, r0, #1
7000097a:	bf1f      	itttt	ne
7000097c:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70000980:	ea92 0f03 	teqne	r2, r3
70000984:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
70000988:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
7000098c:	d06a      	beq.n	70000a64 <__addsf3+0xec>
7000098e:	ea4f 6212 	mov.w	r2, r2, lsr #24
70000992:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
70000996:	bfc1      	itttt	gt
70000998:	18d2      	addgt	r2, r2, r3
7000099a:	4041      	eorgt	r1, r0
7000099c:	4048      	eorgt	r0, r1
7000099e:	4041      	eorgt	r1, r0
700009a0:	bfb8      	it	lt
700009a2:	425b      	neglt	r3, r3
700009a4:	2b19      	cmp	r3, #25
700009a6:	bf88      	it	hi
700009a8:	4770      	bxhi	lr
700009aa:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
700009ae:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700009b2:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
700009b6:	bf18      	it	ne
700009b8:	4240      	negne	r0, r0
700009ba:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
700009be:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
700009c2:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
700009c6:	bf18      	it	ne
700009c8:	4249      	negne	r1, r1
700009ca:	ea92 0f03 	teq	r2, r3
700009ce:	d03f      	beq.n	70000a50 <__addsf3+0xd8>
700009d0:	f1a2 0201 	sub.w	r2, r2, #1
700009d4:	fa41 fc03 	asr.w	ip, r1, r3
700009d8:	eb10 000c 	adds.w	r0, r0, ip
700009dc:	f1c3 0320 	rsb	r3, r3, #32
700009e0:	fa01 f103 	lsl.w	r1, r1, r3
700009e4:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
700009e8:	d502      	bpl.n	700009f0 <__addsf3+0x78>
700009ea:	4249      	negs	r1, r1
700009ec:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
700009f0:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
700009f4:	d313      	bcc.n	70000a1e <__addsf3+0xa6>
700009f6:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
700009fa:	d306      	bcc.n	70000a0a <__addsf3+0x92>
700009fc:	0840      	lsrs	r0, r0, #1
700009fe:	ea4f 0131 	mov.w	r1, r1, rrx
70000a02:	f102 0201 	add.w	r2, r2, #1
70000a06:	2afe      	cmp	r2, #254	; 0xfe
70000a08:	d251      	bcs.n	70000aae <__addsf3+0x136>
70000a0a:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
70000a0e:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000a12:	bf08      	it	eq
70000a14:	f020 0001 	biceq.w	r0, r0, #1
70000a18:	ea40 0003 	orr.w	r0, r0, r3
70000a1c:	4770      	bx	lr
70000a1e:	0049      	lsls	r1, r1, #1
70000a20:	eb40 0000 	adc.w	r0, r0, r0
70000a24:	3a01      	subs	r2, #1
70000a26:	bf28      	it	cs
70000a28:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70000a2c:	d2ed      	bcs.n	70000a0a <__addsf3+0x92>
70000a2e:	fab0 fc80 	clz	ip, r0
70000a32:	f1ac 0c08 	sub.w	ip, ip, #8
70000a36:	ebb2 020c 	subs.w	r2, r2, ip
70000a3a:	fa00 f00c 	lsl.w	r0, r0, ip
70000a3e:	bfaa      	itet	ge
70000a40:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
70000a44:	4252      	neglt	r2, r2
70000a46:	4318      	orrge	r0, r3
70000a48:	bfbc      	itt	lt
70000a4a:	40d0      	lsrlt	r0, r2
70000a4c:	4318      	orrlt	r0, r3
70000a4e:	4770      	bx	lr
70000a50:	f092 0f00 	teq	r2, #0
70000a54:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
70000a58:	bf06      	itte	eq
70000a5a:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
70000a5e:	3201      	addeq	r2, #1
70000a60:	3b01      	subne	r3, #1
70000a62:	e7b5      	b.n	700009d0 <__addsf3+0x58>
70000a64:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000a68:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000a6c:	bf18      	it	ne
70000a6e:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000a72:	d021      	beq.n	70000ab8 <__addsf3+0x140>
70000a74:	ea92 0f03 	teq	r2, r3
70000a78:	d004      	beq.n	70000a84 <__addsf3+0x10c>
70000a7a:	f092 0f00 	teq	r2, #0
70000a7e:	bf08      	it	eq
70000a80:	4608      	moveq	r0, r1
70000a82:	4770      	bx	lr
70000a84:	ea90 0f01 	teq	r0, r1
70000a88:	bf1c      	itt	ne
70000a8a:	2000      	movne	r0, #0
70000a8c:	4770      	bxne	lr
70000a8e:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
70000a92:	d104      	bne.n	70000a9e <__addsf3+0x126>
70000a94:	0040      	lsls	r0, r0, #1
70000a96:	bf28      	it	cs
70000a98:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
70000a9c:	4770      	bx	lr
70000a9e:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
70000aa2:	bf3c      	itt	cc
70000aa4:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
70000aa8:	4770      	bxcc	lr
70000aaa:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000aae:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
70000ab2:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000ab6:	4770      	bx	lr
70000ab8:	ea7f 6222 	mvns.w	r2, r2, asr #24
70000abc:	bf16      	itet	ne
70000abe:	4608      	movne	r0, r1
70000ac0:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70000ac4:	4601      	movne	r1, r0
70000ac6:	0242      	lsls	r2, r0, #9
70000ac8:	bf06      	itte	eq
70000aca:	ea5f 2341 	movseq.w	r3, r1, lsl #9
70000ace:	ea90 0f01 	teqeq	r0, r1
70000ad2:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
70000ad6:	4770      	bx	lr

70000ad8 <__aeabi_ui2f>:
70000ad8:	f04f 0300 	mov.w	r3, #0
70000adc:	e004      	b.n	70000ae8 <__aeabi_i2f+0x8>
70000ade:	bf00      	nop

70000ae0 <__aeabi_i2f>:
70000ae0:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70000ae4:	bf48      	it	mi
70000ae6:	4240      	negmi	r0, r0
70000ae8:	ea5f 0c00 	movs.w	ip, r0
70000aec:	bf08      	it	eq
70000aee:	4770      	bxeq	lr
70000af0:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70000af4:	4601      	mov	r1, r0
70000af6:	f04f 0000 	mov.w	r0, #0
70000afa:	e01c      	b.n	70000b36 <__aeabi_l2f+0x2a>

70000afc <__aeabi_ul2f>:
70000afc:	ea50 0201 	orrs.w	r2, r0, r1
70000b00:	bf08      	it	eq
70000b02:	4770      	bxeq	lr
70000b04:	f04f 0300 	mov.w	r3, #0
70000b08:	e00a      	b.n	70000b20 <__aeabi_l2f+0x14>
70000b0a:	bf00      	nop

70000b0c <__aeabi_l2f>:
70000b0c:	ea50 0201 	orrs.w	r2, r0, r1
70000b10:	bf08      	it	eq
70000b12:	4770      	bxeq	lr
70000b14:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70000b18:	d502      	bpl.n	70000b20 <__aeabi_l2f+0x14>
70000b1a:	4240      	negs	r0, r0
70000b1c:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000b20:	ea5f 0c01 	movs.w	ip, r1
70000b24:	bf02      	ittt	eq
70000b26:	4684      	moveq	ip, r0
70000b28:	4601      	moveq	r1, r0
70000b2a:	2000      	moveq	r0, #0
70000b2c:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70000b30:	bf08      	it	eq
70000b32:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70000b36:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
70000b3a:	fabc f28c 	clz	r2, ip
70000b3e:	3a08      	subs	r2, #8
70000b40:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
70000b44:	db10      	blt.n	70000b68 <__aeabi_l2f+0x5c>
70000b46:	fa01 fc02 	lsl.w	ip, r1, r2
70000b4a:	4463      	add	r3, ip
70000b4c:	fa00 fc02 	lsl.w	ip, r0, r2
70000b50:	f1c2 0220 	rsb	r2, r2, #32
70000b54:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000b58:	fa20 f202 	lsr.w	r2, r0, r2
70000b5c:	eb43 0002 	adc.w	r0, r3, r2
70000b60:	bf08      	it	eq
70000b62:	f020 0001 	biceq.w	r0, r0, #1
70000b66:	4770      	bx	lr
70000b68:	f102 0220 	add.w	r2, r2, #32
70000b6c:	fa01 fc02 	lsl.w	ip, r1, r2
70000b70:	f1c2 0220 	rsb	r2, r2, #32
70000b74:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
70000b78:	fa21 f202 	lsr.w	r2, r1, r2
70000b7c:	eb43 0002 	adc.w	r0, r3, r2
70000b80:	bf08      	it	eq
70000b82:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000b86:	4770      	bx	lr

70000b88 <__aeabi_fmul>:
70000b88:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000b8c:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000b90:	bf1e      	ittt	ne
70000b92:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000b96:	ea92 0f0c 	teqne	r2, ip
70000b9a:	ea93 0f0c 	teqne	r3, ip
70000b9e:	d06f      	beq.n	70000c80 <__aeabi_fmul+0xf8>
70000ba0:	441a      	add	r2, r3
70000ba2:	ea80 0c01 	eor.w	ip, r0, r1
70000ba6:	0240      	lsls	r0, r0, #9
70000ba8:	bf18      	it	ne
70000baa:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000bae:	d01e      	beq.n	70000bee <__aeabi_fmul+0x66>
70000bb0:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000bb4:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000bb8:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000bbc:	fba0 3101 	umull	r3, r1, r0, r1
70000bc0:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000bc4:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000bc8:	bf3e      	ittt	cc
70000bca:	0049      	lslcc	r1, r1, #1
70000bcc:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000bd0:	005b      	lslcc	r3, r3, #1
70000bd2:	ea40 0001 	orr.w	r0, r0, r1
70000bd6:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000bda:	2afd      	cmp	r2, #253	; 0xfd
70000bdc:	d81d      	bhi.n	70000c1a <__aeabi_fmul+0x92>
70000bde:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000be2:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000be6:	bf08      	it	eq
70000be8:	f020 0001 	biceq.w	r0, r0, #1
70000bec:	4770      	bx	lr
70000bee:	f090 0f00 	teq	r0, #0
70000bf2:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000bf6:	bf08      	it	eq
70000bf8:	0249      	lsleq	r1, r1, #9
70000bfa:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000bfe:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000c02:	3a7f      	subs	r2, #127	; 0x7f
70000c04:	bfc2      	ittt	gt
70000c06:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000c0a:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000c0e:	4770      	bxgt	lr
70000c10:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000c14:	f04f 0300 	mov.w	r3, #0
70000c18:	3a01      	subs	r2, #1
70000c1a:	dc5d      	bgt.n	70000cd8 <__aeabi_fmul+0x150>
70000c1c:	f112 0f19 	cmn.w	r2, #25
70000c20:	bfdc      	itt	le
70000c22:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000c26:	4770      	bxle	lr
70000c28:	f1c2 0200 	rsb	r2, r2, #0
70000c2c:	0041      	lsls	r1, r0, #1
70000c2e:	fa21 f102 	lsr.w	r1, r1, r2
70000c32:	f1c2 0220 	rsb	r2, r2, #32
70000c36:	fa00 fc02 	lsl.w	ip, r0, r2
70000c3a:	ea5f 0031 	movs.w	r0, r1, rrx
70000c3e:	f140 0000 	adc.w	r0, r0, #0
70000c42:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000c46:	bf08      	it	eq
70000c48:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000c4c:	4770      	bx	lr
70000c4e:	f092 0f00 	teq	r2, #0
70000c52:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000c56:	bf02      	ittt	eq
70000c58:	0040      	lsleq	r0, r0, #1
70000c5a:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000c5e:	3a01      	subeq	r2, #1
70000c60:	d0f9      	beq.n	70000c56 <__aeabi_fmul+0xce>
70000c62:	ea40 000c 	orr.w	r0, r0, ip
70000c66:	f093 0f00 	teq	r3, #0
70000c6a:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000c6e:	bf02      	ittt	eq
70000c70:	0049      	lsleq	r1, r1, #1
70000c72:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000c76:	3b01      	subeq	r3, #1
70000c78:	d0f9      	beq.n	70000c6e <__aeabi_fmul+0xe6>
70000c7a:	ea41 010c 	orr.w	r1, r1, ip
70000c7e:	e78f      	b.n	70000ba0 <__aeabi_fmul+0x18>
70000c80:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000c84:	ea92 0f0c 	teq	r2, ip
70000c88:	bf18      	it	ne
70000c8a:	ea93 0f0c 	teqne	r3, ip
70000c8e:	d00a      	beq.n	70000ca6 <__aeabi_fmul+0x11e>
70000c90:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000c94:	bf18      	it	ne
70000c96:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000c9a:	d1d8      	bne.n	70000c4e <__aeabi_fmul+0xc6>
70000c9c:	ea80 0001 	eor.w	r0, r0, r1
70000ca0:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000ca4:	4770      	bx	lr
70000ca6:	f090 0f00 	teq	r0, #0
70000caa:	bf17      	itett	ne
70000cac:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000cb0:	4608      	moveq	r0, r1
70000cb2:	f091 0f00 	teqne	r1, #0
70000cb6:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000cba:	d014      	beq.n	70000ce6 <__aeabi_fmul+0x15e>
70000cbc:	ea92 0f0c 	teq	r2, ip
70000cc0:	d101      	bne.n	70000cc6 <__aeabi_fmul+0x13e>
70000cc2:	0242      	lsls	r2, r0, #9
70000cc4:	d10f      	bne.n	70000ce6 <__aeabi_fmul+0x15e>
70000cc6:	ea93 0f0c 	teq	r3, ip
70000cca:	d103      	bne.n	70000cd4 <__aeabi_fmul+0x14c>
70000ccc:	024b      	lsls	r3, r1, #9
70000cce:	bf18      	it	ne
70000cd0:	4608      	movne	r0, r1
70000cd2:	d108      	bne.n	70000ce6 <__aeabi_fmul+0x15e>
70000cd4:	ea80 0001 	eor.w	r0, r0, r1
70000cd8:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000cdc:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000ce0:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000ce4:	4770      	bx	lr
70000ce6:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000cea:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000cee:	4770      	bx	lr

70000cf0 <__aeabi_fdiv>:
70000cf0:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000cf4:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000cf8:	bf1e      	ittt	ne
70000cfa:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000cfe:	ea92 0f0c 	teqne	r2, ip
70000d02:	ea93 0f0c 	teqne	r3, ip
70000d06:	d069      	beq.n	70000ddc <__aeabi_fdiv+0xec>
70000d08:	eba2 0203 	sub.w	r2, r2, r3
70000d0c:	ea80 0c01 	eor.w	ip, r0, r1
70000d10:	0249      	lsls	r1, r1, #9
70000d12:	ea4f 2040 	mov.w	r0, r0, lsl #9
70000d16:	d037      	beq.n	70000d88 <__aeabi_fdiv+0x98>
70000d18:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70000d1c:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70000d20:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70000d24:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000d28:	428b      	cmp	r3, r1
70000d2a:	bf38      	it	cc
70000d2c:	005b      	lslcc	r3, r3, #1
70000d2e:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70000d32:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70000d36:	428b      	cmp	r3, r1
70000d38:	bf24      	itt	cs
70000d3a:	1a5b      	subcs	r3, r3, r1
70000d3c:	ea40 000c 	orrcs.w	r0, r0, ip
70000d40:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70000d44:	bf24      	itt	cs
70000d46:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
70000d4a:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70000d4e:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70000d52:	bf24      	itt	cs
70000d54:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
70000d58:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
70000d5c:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
70000d60:	bf24      	itt	cs
70000d62:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
70000d66:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
70000d6a:	011b      	lsls	r3, r3, #4
70000d6c:	bf18      	it	ne
70000d6e:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70000d72:	d1e0      	bne.n	70000d36 <__aeabi_fdiv+0x46>
70000d74:	2afd      	cmp	r2, #253	; 0xfd
70000d76:	f63f af50 	bhi.w	70000c1a <__aeabi_fmul+0x92>
70000d7a:	428b      	cmp	r3, r1
70000d7c:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000d80:	bf08      	it	eq
70000d82:	f020 0001 	biceq.w	r0, r0, #1
70000d86:	4770      	bx	lr
70000d88:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000d8c:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000d90:	327f      	adds	r2, #127	; 0x7f
70000d92:	bfc2      	ittt	gt
70000d94:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000d98:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000d9c:	4770      	bxgt	lr
70000d9e:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000da2:	f04f 0300 	mov.w	r3, #0
70000da6:	3a01      	subs	r2, #1
70000da8:	e737      	b.n	70000c1a <__aeabi_fmul+0x92>
70000daa:	f092 0f00 	teq	r2, #0
70000dae:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000db2:	bf02      	ittt	eq
70000db4:	0040      	lsleq	r0, r0, #1
70000db6:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000dba:	3a01      	subeq	r2, #1
70000dbc:	d0f9      	beq.n	70000db2 <__aeabi_fdiv+0xc2>
70000dbe:	ea40 000c 	orr.w	r0, r0, ip
70000dc2:	f093 0f00 	teq	r3, #0
70000dc6:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000dca:	bf02      	ittt	eq
70000dcc:	0049      	lsleq	r1, r1, #1
70000dce:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000dd2:	3b01      	subeq	r3, #1
70000dd4:	d0f9      	beq.n	70000dca <__aeabi_fdiv+0xda>
70000dd6:	ea41 010c 	orr.w	r1, r1, ip
70000dda:	e795      	b.n	70000d08 <__aeabi_fdiv+0x18>
70000ddc:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000de0:	ea92 0f0c 	teq	r2, ip
70000de4:	d108      	bne.n	70000df8 <__aeabi_fdiv+0x108>
70000de6:	0242      	lsls	r2, r0, #9
70000de8:	f47f af7d 	bne.w	70000ce6 <__aeabi_fmul+0x15e>
70000dec:	ea93 0f0c 	teq	r3, ip
70000df0:	f47f af70 	bne.w	70000cd4 <__aeabi_fmul+0x14c>
70000df4:	4608      	mov	r0, r1
70000df6:	e776      	b.n	70000ce6 <__aeabi_fmul+0x15e>
70000df8:	ea93 0f0c 	teq	r3, ip
70000dfc:	d104      	bne.n	70000e08 <__aeabi_fdiv+0x118>
70000dfe:	024b      	lsls	r3, r1, #9
70000e00:	f43f af4c 	beq.w	70000c9c <__aeabi_fmul+0x114>
70000e04:	4608      	mov	r0, r1
70000e06:	e76e      	b.n	70000ce6 <__aeabi_fmul+0x15e>
70000e08:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000e0c:	bf18      	it	ne
70000e0e:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000e12:	d1ca      	bne.n	70000daa <__aeabi_fdiv+0xba>
70000e14:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70000e18:	f47f af5c 	bne.w	70000cd4 <__aeabi_fmul+0x14c>
70000e1c:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70000e20:	f47f af3c 	bne.w	70000c9c <__aeabi_fmul+0x114>
70000e24:	e75f      	b.n	70000ce6 <__aeabi_fmul+0x15e>
70000e26:	bf00      	nop

70000e28 <__gesf2>:
70000e28:	f04f 3cff 	mov.w	ip, #4294967295
70000e2c:	e006      	b.n	70000e3c <__cmpsf2+0x4>
70000e2e:	bf00      	nop

70000e30 <__lesf2>:
70000e30:	f04f 0c01 	mov.w	ip, #1
70000e34:	e002      	b.n	70000e3c <__cmpsf2+0x4>
70000e36:	bf00      	nop

70000e38 <__cmpsf2>:
70000e38:	f04f 0c01 	mov.w	ip, #1
70000e3c:	f84d cd04 	str.w	ip, [sp, #-4]!
70000e40:	ea4f 0240 	mov.w	r2, r0, lsl #1
70000e44:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000e48:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000e4c:	bf18      	it	ne
70000e4e:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000e52:	d011      	beq.n	70000e78 <__cmpsf2+0x40>
70000e54:	b001      	add	sp, #4
70000e56:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
70000e5a:	bf18      	it	ne
70000e5c:	ea90 0f01 	teqne	r0, r1
70000e60:	bf58      	it	pl
70000e62:	ebb2 0003 	subspl.w	r0, r2, r3
70000e66:	bf88      	it	hi
70000e68:	17c8      	asrhi	r0, r1, #31
70000e6a:	bf38      	it	cc
70000e6c:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70000e70:	bf18      	it	ne
70000e72:	f040 0001 	orrne.w	r0, r0, #1
70000e76:	4770      	bx	lr
70000e78:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000e7c:	d102      	bne.n	70000e84 <__cmpsf2+0x4c>
70000e7e:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70000e82:	d105      	bne.n	70000e90 <__cmpsf2+0x58>
70000e84:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70000e88:	d1e4      	bne.n	70000e54 <__cmpsf2+0x1c>
70000e8a:	ea5f 2c41 	movs.w	ip, r1, lsl #9
70000e8e:	d0e1      	beq.n	70000e54 <__cmpsf2+0x1c>
70000e90:	f85d 0b04 	ldr.w	r0, [sp], #4
70000e94:	4770      	bx	lr
70000e96:	bf00      	nop

70000e98 <__aeabi_cfrcmple>:
70000e98:	4684      	mov	ip, r0
70000e9a:	4608      	mov	r0, r1
70000e9c:	4661      	mov	r1, ip
70000e9e:	e7ff      	b.n	70000ea0 <__aeabi_cfcmpeq>

70000ea0 <__aeabi_cfcmpeq>:
70000ea0:	b50f      	push	{r0, r1, r2, r3, lr}
70000ea2:	f7ff ffc9 	bl	70000e38 <__cmpsf2>
70000ea6:	2800      	cmp	r0, #0
70000ea8:	bf48      	it	mi
70000eaa:	f110 0f00 	cmnmi.w	r0, #0
70000eae:	bd0f      	pop	{r0, r1, r2, r3, pc}

70000eb0 <__aeabi_fcmpeq>:
70000eb0:	f84d ed08 	str.w	lr, [sp, #-8]!
70000eb4:	f7ff fff4 	bl	70000ea0 <__aeabi_cfcmpeq>
70000eb8:	bf0c      	ite	eq
70000eba:	2001      	moveq	r0, #1
70000ebc:	2000      	movne	r0, #0
70000ebe:	f85d fb08 	ldr.w	pc, [sp], #8
70000ec2:	bf00      	nop

70000ec4 <__aeabi_fcmplt>:
70000ec4:	f84d ed08 	str.w	lr, [sp, #-8]!
70000ec8:	f7ff ffea 	bl	70000ea0 <__aeabi_cfcmpeq>
70000ecc:	bf34      	ite	cc
70000ece:	2001      	movcc	r0, #1
70000ed0:	2000      	movcs	r0, #0
70000ed2:	f85d fb08 	ldr.w	pc, [sp], #8
70000ed6:	bf00      	nop

70000ed8 <__aeabi_fcmple>:
70000ed8:	f84d ed08 	str.w	lr, [sp, #-8]!
70000edc:	f7ff ffe0 	bl	70000ea0 <__aeabi_cfcmpeq>
70000ee0:	bf94      	ite	ls
70000ee2:	2001      	movls	r0, #1
70000ee4:	2000      	movhi	r0, #0
70000ee6:	f85d fb08 	ldr.w	pc, [sp], #8
70000eea:	bf00      	nop

70000eec <__aeabi_fcmpge>:
70000eec:	f84d ed08 	str.w	lr, [sp, #-8]!
70000ef0:	f7ff ffd2 	bl	70000e98 <__aeabi_cfrcmple>
70000ef4:	bf94      	ite	ls
70000ef6:	2001      	movls	r0, #1
70000ef8:	2000      	movhi	r0, #0
70000efa:	f85d fb08 	ldr.w	pc, [sp], #8
70000efe:	bf00      	nop

70000f00 <__aeabi_fcmpgt>:
70000f00:	f84d ed08 	str.w	lr, [sp, #-8]!
70000f04:	f7ff ffc8 	bl	70000e98 <__aeabi_cfrcmple>
70000f08:	bf34      	ite	cc
70000f0a:	2001      	movcc	r0, #1
70000f0c:	2000      	movcs	r0, #0
70000f0e:	f85d fb08 	ldr.w	pc, [sp], #8
70000f12:	bf00      	nop

70000f14 <__aeabi_f2uiz>:
70000f14:	0042      	lsls	r2, r0, #1
70000f16:	d20e      	bcs.n	70000f36 <__aeabi_f2uiz+0x22>
70000f18:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70000f1c:	d30b      	bcc.n	70000f36 <__aeabi_f2uiz+0x22>
70000f1e:	f04f 039e 	mov.w	r3, #158	; 0x9e
70000f22:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70000f26:	d409      	bmi.n	70000f3c <__aeabi_f2uiz+0x28>
70000f28:	ea4f 2300 	mov.w	r3, r0, lsl #8
70000f2c:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000f30:	fa23 f002 	lsr.w	r0, r3, r2
70000f34:	4770      	bx	lr
70000f36:	f04f 0000 	mov.w	r0, #0
70000f3a:	4770      	bx	lr
70000f3c:	f112 0f61 	cmn.w	r2, #97	; 0x61
70000f40:	d101      	bne.n	70000f46 <__aeabi_f2uiz+0x32>
70000f42:	0242      	lsls	r2, r0, #9
70000f44:	d102      	bne.n	70000f4c <__aeabi_f2uiz+0x38>
70000f46:	f04f 30ff 	mov.w	r0, #4294967295
70000f4a:	4770      	bx	lr
70000f4c:	f04f 0000 	mov.w	r0, #0
70000f50:	4770      	bx	lr
70000f52:	bf00      	nop
