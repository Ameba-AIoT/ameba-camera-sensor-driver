
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	89 06 00 70 a5 02 00 70                             ...p...p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

7000006c <g_sc231h_i2c_init_regs_asic>:
7000006c:	03 01 01 00 e9 36 80 00 f9 37 80 00 1f 30 14 00     .....6...7...0..
7000007c:	58 30 21 00 59 30 53 00 5a 30 40 00 0e 32 04 00     X0!.Y0S.Z0@..2..
7000008c:	0f 32 b0 00 10 32 00 00 11 32 04 00 12 32 00 00     .2...2...2...2..
7000009c:	13 32 03 00 50 32 00 00 01 33 0a 00 02 33 20 00     .2..P2...3...3 .
700000ac:	04 33 90 00 05 33 00 00 06 33 68 00 09 33 d0 00     .3...3...3h..3..
700000bc:	0b 33 d8 00 0d 33 08 00 1c 33 04 00 1e 33 81 00     .3...3...3...3..
700000cc:	1f 33 c1 00 23 33 06 00 33 33 10 00 34 33 40 00     .3..#3..33..43@.
700000dc:	64 33 5e 00 6c 33 8e 00 7f 33 13 00 8f 33 80 00     d3^.l3...3...3..
700000ec:	90 33 08 00 91 33 18 00 92 33 b8 00 93 33 0e 00     .3...3...3...3..
700000fc:	94 33 14 00 95 33 10 00 96 33 88 00 97 33 98 00     .3...3...3...3..
7000010c:	98 33 f8 00 99 33 0a 00 9a 33 0e 00 9b 33 10 00     .3...3...3...3..
7000011c:	9c 33 16 00 ae 33 80 00 af 33 c0 00 b1 33 80 00     .3...3...3...3..
7000012c:	b2 33 50 00 b3 33 14 00 f8 33 00 00 f9 33 68 00     .3P..3...3...3h.
7000013c:	fa 33 00 00 fb 33 68 00 fc 33 48 00 fd 33 78 00     .3...3h..3H..3x.
7000014c:	9f 34 03 00 a6 34 40 00 a7 34 58 00 a8 34 10 00     .4...4@..4X..4..
7000015c:	a9 34 10 00 f8 34 78 00 f9 34 10 00 19 36 20 00     .4...4x..4...6 .
7000016c:	1a 36 90 00 33 36 44 00 37 36 5c 00 3c 36 c0 00     .6..36D.76\.<6..
7000017c:	3d 36 02 00 60 36 80 00 61 36 81 00 62 36 8f 00     =6..`6..a6..b6..
7000018c:	63 36 81 00 64 36 81 00 65 36 82 00 66 36 8f 00     c6..d6..e6..f6..
7000019c:	67 36 08 00 68 36 80 00 69 36 88 00 6a 36 98 00     g6..h6..i6..j6..
700001ac:	6b 36 b8 00 6c 36 f8 00 70 36 b2 00 71 36 a2 00     k6..l6..p6..q6..
700001bc:	72 36 88 00 80 36 33 00 81 36 33 00 82 36 43 00     r6...63..63..6C.
700001cc:	c0 36 80 00 c1 36 88 00 c8 36 88 00 c9 36 b8 00     .6...6...6...6..
700001dc:	ea 36 0b 00 eb 36 0c 00 ec 36 5c 00 ed 36 04 00     .6...6...6\..6..
700001ec:	18 37 04 00 22 37 8b 00 24 37 d1 00 41 37 08 00     .7.."7..$7..A7..
700001fc:	70 37 17 00 71 37 9b 00 72 37 9b 00 c0 37 88 00     p7..q7..r7...7..
7000020c:	c1 37 b8 00 fa 37 0b 00 fc 37 10 00 fd 37 04 00     .7...7...7...7..
7000021c:	02 39 c0 00 03 39 40 00 09 39 00 00 1f 39 41 00     .9...9@..9...9A.
7000022c:	26 39 e0 00 33 39 80 00 34 39 02 00 37 39 6f 00     &9..39..49..79o.
7000023c:	00 3e 00 00 01 3e 95 00 02 3e 50 00 08 3e 00 00     .>...>...>P..>..
7000024c:	09 45 20 00 0d 45 07 00 37 48 33 00 80 57 76 00     .E ..E..7H3..Wv.
7000025c:	84 57 10 00 87 57 0a 00 88 57 0a 00 89 57 08 00     .W...W...W...W..
7000026c:	8a 57 0a 00 8b 57 0a 00 8c 57 08 00 8d 57 40 00     .W...W...W...W@.
7000027c:	92 57 04 00 95 57 04 00 ac 57 00 00 ad 57 00 00     .W...W...W...W..
7000028c:	e9 36 27 00 f9 37 27 00 00 01 01 00                 .6'..7'.....

70000298 <real_slave_addr>:
70000298:	30 00 00 00                                         0...

7000029c <slave_addr_list>:
7000029c:	30 00 00 00 32 00 00 00                             0...2...

700002a4 <rts_isp_set_voe_ops>:
700002a4:	4b01      	ldr	r3, [pc, #4]	; (700002ac <rts_isp_set_voe_ops+0x8>)
700002a6:	6018      	str	r0, [r3, #0]
700002a8:	4770      	bx	lr
700002aa:	bf00      	nop
700002ac:	70000048 	.word	0x70000048

700002b0 <isp_driver_is_fpga>:
700002b0:	2000      	movs	r0, #0
700002b2:	4770      	bx	lr

700002b4 <sc231h_get_info>:
700002b4:	b510      	push	{r4, lr}
700002b6:	2800      	cmp	r0, #0
700002b8:	d153      	bne.n	70000362 <sc231h_get_info+0xae>
700002ba:	2900      	cmp	r1, #0
700002bc:	d051      	beq.n	70000362 <sc231h_get_info+0xae>
700002be:	f44f 62f0 	mov.w	r2, #1920	; 0x780
700002c2:	f44f 6387 	mov.w	r3, #1080	; 0x438
700002c6:	f44f 747a 	mov.w	r4, #1000	; 0x3e8
700002ca:	f8df c09c 	ldr.w	ip, [pc, #156]	; 70000368 <sc231h_get_info+0xb4>
700002ce:	7108      	strb	r0, [r1, #4]
700002d0:	f8c1 40ac 	str.w	r4, [r1, #172]	; 0xac
700002d4:	f44f 74fa 	mov.w	r4, #500	; 0x1f4
700002d8:	f8c1 00a8 	str.w	r0, [r1, #168]	; 0xa8
700002dc:	f8c1 40b8 	str.w	r4, [r1, #184]	; 0xb8
700002e0:	f881 00b0 	strb.w	r0, [r1, #176]	; 0xb0
700002e4:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
700002e8:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
700002ec:	e9c1 2302 	strd	r2, r3, [r1, #8]
700002f0:	4b1e      	ldr	r3, [pc, #120]	; (7000036c <sc231h_get_info+0xb8>)
700002f2:	4a1f      	ldr	r2, [pc, #124]	; (70000370 <sc231h_get_info+0xbc>)
700002f4:	610b      	str	r3, [r1, #16]
700002f6:	2301      	movs	r3, #1
700002f8:	6812      	ldr	r2, [r2, #0]
700002fa:	600b      	str	r3, [r1, #0]
700002fc:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
70000300:	4a1c      	ldr	r2, [pc, #112]	; (70000374 <sc231h_get_info+0xc0>)
70000302:	f881 3098 	strb.w	r3, [r1, #152]	; 0x98
70000306:	7812      	ldrb	r2, [r2, #0]
70000308:	f8c1 30b4 	str.w	r3, [r1, #180]	; 0xb4
7000030c:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
70000310:	2203      	movs	r2, #3
70000312:	f881 30bc 	strb.w	r3, [r1, #188]	; 0xbc
70000316:	f881 20a4 	strb.w	r2, [r1, #164]	; 0xa4
7000031a:	f881 20c8 	strb.w	r2, [r1, #200]	; 0xc8
7000031e:	e9c1 3430 	strd	r3, r4, [r1, #192]	; 0xc0
70000322:	f44f 54fa 	mov.w	r4, #8000	; 0x1f40
70000326:	e9c1 c433 	strd	ip, r4, [r1, #204]	; 0xcc
7000032a:	f44f 7481 	mov.w	r4, #258	; 0x102
7000032e:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
70000332:	2406      	movs	r4, #6
70000334:	e9c1 0024 	strd	r0, r0, [r1, #144]	; 0x90
70000338:	e9c1 0027 	strd	r0, r0, [r1, #156]	; 0x9c
7000033c:	f8c1 4088 	str.w	r4, [r1, #136]	; 0x88
70000340:	e9c1 00b7 	strd	r0, r0, [r1, #732]	; 0x2dc
70000344:	f881 32e4 	strb.w	r3, [r1, #740]	; 0x2e4
70000348:	f241 3388 	movw	r3, #5000	; 0x1388
7000034c:	f881 22f0 	strb.w	r2, [r1, #752]	; 0x2f0
70000350:	f8c1 02f4 	str.w	r0, [r1, #756]	; 0x2f4
70000354:	f8c1 32f8 	str.w	r3, [r1, #760]	; 0x2f8
70000358:	f8c1 22d4 	str.w	r2, [r1, #724]	; 0x2d4
7000035c:	e9c1 00ba 	strd	r0, r0, [r1, #744]	; 0x2e8
70000360:	bd10      	pop	{r4, pc}
70000362:	f06f 0015 	mvn.w	r0, #21
70000366:	e7fb      	b.n	70000360 <sc231h_get_info+0xac>
70000368:	016e3600 	.word	0x016e3600
7000036c:	41f00000 	.word	0x41f00000
70000370:	70000298 	.word	0x70000298
70000374:	7000004c 	.word	0x7000004c

70000378 <sc231h_get_init_info>:
70000378:	b570      	push	{r4, r5, r6, lr}
7000037a:	4614      	mov	r4, r2
7000037c:	4605      	mov	r5, r0
7000037e:	b110      	cbz	r0, 70000386 <sc231h_get_init_info+0xe>
70000380:	f06f 0015 	mvn.w	r0, #21
70000384:	bd70      	pop	{r4, r5, r6, pc}
70000386:	2a00      	cmp	r2, #0
70000388:	d0fa      	beq.n	70000380 <sc231h_get_init_info+0x8>
7000038a:	780b      	ldrb	r3, [r1, #0]
7000038c:	4e1c      	ldr	r6, [pc, #112]	; (70000400 <sc231h_get_init_info+0x88>)
7000038e:	68c8      	ldr	r0, [r1, #12]
70000390:	7033      	strb	r3, [r6, #0]
70000392:	f000 fd5f 	bl	70000e54 <__aeabi_f2uiz>
70000396:	b280      	uxth	r0, r0
70000398:	f000 fb42 	bl	70000a20 <__aeabi_i2f>
7000039c:	4919      	ldr	r1, [pc, #100]	; (70000404 <sc231h_get_init_info+0x8c>)
7000039e:	f000 fd27 	bl	70000df0 <__aeabi_fcmpeq>
700003a2:	2800      	cmp	r0, #0
700003a4:	d0ec      	beq.n	70000380 <sc231h_get_init_info+0x8>
700003a6:	4b18      	ldr	r3, [pc, #96]	; (70000408 <sc231h_get_init_info+0x90>)
700003a8:	f44f 62f1 	mov.w	r2, #1928	; 0x788
700003ac:	f640 0198 	movw	r1, #2200	; 0x898
700003b0:	60a5      	str	r5, [r4, #8]
700003b2:	6063      	str	r3, [r4, #4]
700003b4:	238b      	movs	r3, #139	; 0x8b
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
700003d4:	f44f 6388 	mov.w	r3, #1088	; 0x440
700003d8:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
700003dc:	4b0b      	ldr	r3, [pc, #44]	; (7000040c <sc231h_get_init_info+0x94>)
700003de:	e9c4 3124 	strd	r3, r1, [r4, #144]	; 0x90
700003e2:	f44f 6396 	mov.w	r3, #1200	; 0x4b0
700003e6:	6073      	str	r3, [r6, #4]
700003e8:	f8c4 3098 	str.w	r3, [r4, #152]	; 0x98
700003ec:	f648 43a0 	movw	r3, #36000	; 0x8ca0
700003f0:	f8c4 309c 	str.w	r3, [r4, #156]	; 0x9c
700003f4:	4b06      	ldr	r3, [pc, #24]	; (70000410 <sc231h_get_init_info+0x98>)
700003f6:	e9c4 5522 	strd	r5, r5, [r4, #136]	; 0x88
700003fa:	60b3      	str	r3, [r6, #8]
700003fc:	e7c2      	b.n	70000384 <sc231h_get_init_info+0xc>
700003fe:	bf00      	nop
70000400:	7000004c 	.word	0x7000004c
70000404:	41f00000 	.word	0x41f00000
70000408:	7000006c 	.word	0x7000006c
7000040c:	04b87f00 	.word	0x04b87f00
70000410:	41de38e4 	.word	0x41de38e4

70000414 <sc231h_start>:
70000414:	b918      	cbnz	r0, 7000041e <sc231h_start+0xa>
70000416:	4b03      	ldr	r3, [pc, #12]	; (70000424 <sc231h_start+0x10>)
70000418:	2200      	movs	r2, #0
7000041a:	60da      	str	r2, [r3, #12]
7000041c:	4770      	bx	lr
7000041e:	f06f 0015 	mvn.w	r0, #21
70000422:	4770      	bx	lr
70000424:	7000004c 	.word	0x7000004c

70000428 <sc231h_get_tuned_dgain>:
70000428:	b920      	cbnz	r0, 70000434 <sc231h_get_tuned_dgain+0xc>
7000042a:	b119      	cbz	r1, 70000434 <sc231h_get_tuned_dgain+0xc>
7000042c:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
70000430:	600b      	str	r3, [r1, #0]
70000432:	4770      	bx	lr
70000434:	f06f 0015 	mvn.w	r0, #21
70000438:	4770      	bx	lr
	...

7000043c <sc231h_get_exposure_gain_info>:
7000043c:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
70000440:	4614      	mov	r4, r2
70000442:	2800      	cmp	r0, #0
70000444:	d166      	bne.n	70000514 <sc231h_get_exposure_gain_info+0xd8>
70000446:	2900      	cmp	r1, #0
70000448:	d064      	beq.n	70000514 <sc231h_get_exposure_gain_info+0xd8>
7000044a:	2a00      	cmp	r2, #0
7000044c:	d062      	beq.n	70000514 <sc231h_get_exposure_gain_info+0xd8>
7000044e:	f8d1 8000 	ldr.w	r8, [r1]
70000452:	1d15      	adds	r5, r2, #4
70000454:	4f31      	ldr	r7, [pc, #196]	; (7000051c <sc231h_get_exposure_gain_info+0xe0>)
70000456:	698e      	ldr	r6, [r1, #24]
70000458:	4641      	mov	r1, r8
7000045a:	68f8      	ldr	r0, [r7, #12]
7000045c:	f000 fa2a 	bl	700008b4 <__aeabi_fsub>
70000460:	2100      	movs	r1, #0
70000462:	4681      	mov	r9, r0
70000464:	f000 fce2 	bl	70000e2c <__aeabi_fcmpge>
70000468:	2800      	cmp	r0, #0
7000046a:	d04e      	beq.n	7000050a <sc231h_get_exposure_gain_info+0xce>
7000046c:	492c      	ldr	r1, [pc, #176]	; (70000520 <sc231h_get_exposure_gain_info+0xe4>)
7000046e:	4648      	mov	r0, r9
70000470:	f000 fce6 	bl	70000e40 <__aeabi_fcmpgt>
70000474:	b1f0      	cbz	r0, 700004b4 <sc231h_get_exposure_gain_info+0x78>
70000476:	68b9      	ldr	r1, [r7, #8]
70000478:	4640      	mov	r0, r8
7000047a:	f000 fbd9 	bl	70000c30 <__aeabi_fdiv>
7000047e:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
70000482:	f000 fa19 	bl	700008b8 <__addsf3>
70000486:	f000 fce5 	bl	70000e54 <__aeabi_f2uiz>
7000048a:	f44f 5278 	mov.w	r2, #15872	; 0x3e00
7000048e:	0103      	lsls	r3, r0, #4
70000490:	81a2      	strh	r2, [r4, #12]
70000492:	f3c0 3207 	ubfx	r2, r0, #12, #8
70000496:	f3c0 1007 	ubfx	r0, r0, #4, #8
7000049a:	b2db      	uxtb	r3, r3
7000049c:	81e2      	strh	r2, [r4, #14]
7000049e:	f643 6201 	movw	r2, #15873	; 0x3e01
700004a2:	8460      	strh	r0, [r4, #34]	; 0x22
700004a4:	2003      	movs	r0, #3
700004a6:	8422      	strh	r2, [r4, #32]
700004a8:	f643 6202 	movw	r2, #15874	; 0x3e02
700004ac:	86e3      	strh	r3, [r4, #54]	; 0x36
700004ae:	86a2      	strh	r2, [r4, #52]	; 0x34
700004b0:	f8c7 800c 	str.w	r8, [r7, #12]
700004b4:	2314      	movs	r3, #20
700004b6:	693f      	ldr	r7, [r7, #16]
700004b8:	491a      	ldr	r1, [pc, #104]	; (70000524 <sc231h_get_exposure_gain_info+0xe8>)
700004ba:	f643 6e08 	movw	lr, #15880	; 0x3e08
700004be:	4343      	muls	r3, r0
700004c0:	3004      	adds	r0, #4
700004c2:	f811 c027 	ldrb.w	ip, [r1, r7, lsl #2]
700004c6:	eb01 0187 	add.w	r1, r1, r7, lsl #2
700004ca:	18ea      	adds	r2, r5, r3
700004cc:	f643 6709 	movw	r7, #15881	; 0x3e09
700004d0:	7849      	ldrb	r1, [r1, #1]
700004d2:	f8a2 e008 	strh.w	lr, [r2, #8]
700004d6:	f8a2 c00a 	strh.w	ip, [r2, #10]
700004da:	f103 0214 	add.w	r2, r3, #20
700004de:	442a      	add	r2, r5
700004e0:	8151      	strh	r1, [r2, #10]
700004e2:	f243 210e 	movw	r1, #12814	; 0x320e
700004e6:	8117      	strh	r7, [r2, #8]
700004e8:	f103 0228 	add.w	r2, r3, #40	; 0x28
700004ec:	333c      	adds	r3, #60	; 0x3c
700004ee:	442a      	add	r2, r5
700004f0:	442b      	add	r3, r5
700004f2:	8111      	strh	r1, [r2, #8]
700004f4:	0a31      	lsrs	r1, r6, #8
700004f6:	b2f6      	uxtb	r6, r6
700004f8:	8151      	strh	r1, [r2, #10]
700004fa:	f243 220f 	movw	r2, #12815	; 0x320f
700004fe:	815e      	strh	r6, [r3, #10]
70000500:	811a      	strh	r2, [r3, #8]
70000502:	6020      	str	r0, [r4, #0]
70000504:	2000      	movs	r0, #0
70000506:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
7000050a:	4907      	ldr	r1, [pc, #28]	; (70000528 <sc231h_get_exposure_gain_info+0xec>)
7000050c:	4648      	mov	r0, r9
7000050e:	f000 fc79 	bl	70000e04 <__aeabi_fcmplt>
70000512:	e7af      	b.n	70000474 <sc231h_get_exposure_gain_info+0x38>
70000514:	f06f 0015 	mvn.w	r0, #21
70000518:	e7f5      	b.n	70000506 <sc231h_get_exposure_gain_info+0xca>
7000051a:	bf00      	nop
7000051c:	7000004c 	.word	0x7000004c
70000520:	3a83126f 	.word	0x3a83126f
70000524:	70000690 	.word	0x70000690
70000528:	ba83126f 	.word	0xba83126f

7000052c <sc231h_set_mirror_flip>:
7000052c:	784b      	ldrb	r3, [r1, #1]
7000052e:	780a      	ldrb	r2, [r1, #0]
70000530:	2b00      	cmp	r3, #0
70000532:	bf14      	ite	ne
70000534:	2302      	movne	r3, #2
70000536:	2300      	moveq	r3, #0
70000538:	2a00      	cmp	r2, #0
7000053a:	bf18      	it	ne
7000053c:	f043 0301 	orrne.w	r3, r3, #1
70000540:	2201      	movs	r2, #1
70000542:	2b02      	cmp	r3, #2
70000544:	708a      	strb	r2, [r1, #2]
70000546:	d009      	beq.n	7000055c <sc231h_set_mirror_flip+0x30>
70000548:	2b03      	cmp	r3, #3
7000054a:	d00b      	beq.n	70000564 <sc231h_set_mirror_flip+0x38>
7000054c:	4293      	cmp	r3, r2
7000054e:	d007      	beq.n	70000560 <sc231h_set_mirror_flip+0x34>
70000550:	4b06      	ldr	r3, [pc, #24]	; (7000056c <sc231h_set_mirror_flip+0x40>)
70000552:	610b      	str	r3, [r1, #16]
70000554:	2301      	movs	r3, #1
70000556:	2000      	movs	r0, #0
70000558:	604b      	str	r3, [r1, #4]
7000055a:	4770      	bx	lr
7000055c:	4b04      	ldr	r3, [pc, #16]	; (70000570 <sc231h_set_mirror_flip+0x44>)
7000055e:	e7f8      	b.n	70000552 <sc231h_set_mirror_flip+0x26>
70000560:	4b04      	ldr	r3, [pc, #16]	; (70000574 <sc231h_set_mirror_flip+0x48>)
70000562:	e7f6      	b.n	70000552 <sc231h_set_mirror_flip+0x26>
70000564:	f243 2321 	movw	r3, #12833	; 0x3221
70000568:	e7f3      	b.n	70000552 <sc231h_set_mirror_flip+0x26>
7000056a:	bf00      	nop
7000056c:	00663221 	.word	0x00663221
70000570:	00063221 	.word	0x00063221
70000574:	00603221 	.word	0x00603221

70000578 <sc231h_check>:
70000578:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
7000057a:	4d1e      	ldr	r5, [pc, #120]	; (700005f4 <sc231h_check+0x7c>)
7000057c:	4606      	mov	r6, r0
7000057e:	682b      	ldr	r3, [r5, #0]
70000580:	6c1b      	ldr	r3, [r3, #64]	; 0x40
70000582:	4798      	blx	r3
70000584:	2801      	cmp	r0, #1
70000586:	dc31      	bgt.n	700005ec <sc231h_check+0x74>
70000588:	4b1b      	ldr	r3, [pc, #108]	; (700005f8 <sc231h_check+0x80>)
7000058a:	f853 2020 	ldr.w	r2, [r3, r0, lsl #2]
7000058e:	4b1b      	ldr	r3, [pc, #108]	; (700005fc <sc231h_check+0x84>)
70000590:	601a      	str	r2, [r3, #0]
70000592:	682b      	ldr	r3, [r5, #0]
70000594:	685b      	ldr	r3, [r3, #4]
70000596:	4798      	blx	r3
70000598:	f243 1307 	movw	r3, #12551	; 0x3107
7000059c:	a901      	add	r1, sp, #4
7000059e:	4630      	mov	r0, r6
700005a0:	f8ad 3004 	strh.w	r3, [sp, #4]
700005a4:	682b      	ldr	r3, [r5, #0]
700005a6:	68db      	ldr	r3, [r3, #12]
700005a8:	4798      	blx	r3
700005aa:	4604      	mov	r4, r0
700005ac:	b128      	cbz	r0, 700005ba <sc231h_check+0x42>
700005ae:	682b      	ldr	r3, [r5, #0]
700005b0:	689b      	ldr	r3, [r3, #8]
700005b2:	4798      	blx	r3
700005b4:	4620      	mov	r0, r4
700005b6:	b003      	add	sp, #12
700005b8:	bdf0      	pop	{r4, r5, r6, r7, pc}
700005ba:	f243 1308 	movw	r3, #12552	; 0x3108
700005be:	a901      	add	r1, sp, #4
700005c0:	4630      	mov	r0, r6
700005c2:	f8bd 7006 	ldrh.w	r7, [sp, #6]
700005c6:	f8ad 3004 	strh.w	r3, [sp, #4]
700005ca:	682b      	ldr	r3, [r5, #0]
700005cc:	68db      	ldr	r3, [r3, #12]
700005ce:	4798      	blx	r3
700005d0:	682b      	ldr	r3, [r5, #0]
700005d2:	4604      	mov	r4, r0
700005d4:	689b      	ldr	r3, [r3, #8]
700005d6:	4798      	blx	r3
700005d8:	2c00      	cmp	r4, #0
700005da:	d1eb      	bne.n	700005b4 <sc231h_check+0x3c>
700005dc:	f8bd 3006 	ldrh.w	r3, [sp, #6]
700005e0:	f64c 326a 	movw	r2, #52074	; 0xcb6a
700005e4:	ea43 2307 	orr.w	r3, r3, r7, lsl #8
700005e8:	4293      	cmp	r3, r2
700005ea:	d0e3      	beq.n	700005b4 <sc231h_check+0x3c>
700005ec:	f06f 0415 	mvn.w	r4, #21
700005f0:	e7e0      	b.n	700005b4 <sc231h_check+0x3c>
700005f2:	bf00      	nop
700005f4:	70000048 	.word	0x70000048
700005f8:	7000029c 	.word	0x7000029c
700005fc:	70000298 	.word	0x70000298

70000600 <sc231h_get_slave_addr_num>:
70000600:	2002      	movs	r0, #2
70000602:	4770      	bx	lr

70000604 <sc231h_get_tuned_again>:
70000604:	b570      	push	{r4, r5, r6, lr}
70000606:	460d      	mov	r5, r1
70000608:	4604      	mov	r4, r0
7000060a:	bb60      	cbnz	r0, 70000666 <sc231h_get_tuned_again+0x62>
7000060c:	b359      	cbz	r1, 70000666 <sc231h_get_tuned_again+0x62>
7000060e:	f04f 4183 	mov.w	r1, #1098907648	; 0x41800000
70000612:	6828      	ldr	r0, [r5, #0]
70000614:	f000 fa58 	bl	70000ac8 <__aeabi_fmul>
70000618:	f000 fc1c 	bl	70000e54 <__aeabi_f2uiz>
7000061c:	b280      	uxth	r0, r0
7000061e:	f5b0 7f00 	cmp.w	r0, #512	; 0x200
70000622:	d30d      	bcc.n	70000640 <sc231h_get_tuned_again+0x3c>
70000624:	4b11      	ldr	r3, [pc, #68]	; (7000066c <sc231h_get_tuned_again+0x68>)
70000626:	2205      	movs	r2, #5
70000628:	f44f 7000 	mov.w	r0, #512	; 0x200
7000062c:	611a      	str	r2, [r3, #16]
7000062e:	f000 f9f7 	bl	70000a20 <__aeabi_i2f>
70000632:	f04f 5176 	mov.w	r1, #1031798784	; 0x3d800000
70000636:	f000 fa47 	bl	70000ac8 <__aeabi_fmul>
7000063a:	6028      	str	r0, [r5, #0]
7000063c:	2000      	movs	r0, #0
7000063e:	bd70      	pop	{r4, r5, r6, pc}
70000640:	4a0b      	ldr	r2, [pc, #44]	; (70000670 <sc231h_get_tuned_again+0x6c>)
70000642:	4623      	mov	r3, r4
70000644:	8851      	ldrh	r1, [r2, #2]
70000646:	461c      	mov	r4, r3
70000648:	3301      	adds	r3, #1
7000064a:	4288      	cmp	r0, r1
7000064c:	d306      	bcc.n	7000065c <sc231h_get_tuned_again+0x58>
7000064e:	88d6      	ldrh	r6, [r2, #6]
70000650:	4286      	cmp	r6, r0
70000652:	d903      	bls.n	7000065c <sc231h_get_tuned_again+0x58>
70000654:	4b05      	ldr	r3, [pc, #20]	; (7000066c <sc231h_get_tuned_again+0x68>)
70000656:	4608      	mov	r0, r1
70000658:	611c      	str	r4, [r3, #16]
7000065a:	e7e8      	b.n	7000062e <sc231h_get_tuned_again+0x2a>
7000065c:	2b07      	cmp	r3, #7
7000065e:	f102 0204 	add.w	r2, r2, #4
70000662:	d1ef      	bne.n	70000644 <sc231h_get_tuned_again+0x40>
70000664:	e7e3      	b.n	7000062e <sc231h_get_tuned_again+0x2a>
70000666:	f06f 0015 	mvn.w	r0, #21
7000066a:	e7e8      	b.n	7000063e <sc231h_get_tuned_again+0x3a>
7000066c:	7000004c 	.word	0x7000004c
70000670:	70000690 	.word	0x70000690

70000674 <clip_d_word>:
70000674:	4603      	mov	r3, r0
70000676:	4610      	mov	r0, r2
70000678:	4293      	cmp	r3, r2
7000067a:	d803      	bhi.n	70000684 <clip_d_word+0x10>
7000067c:	428b      	cmp	r3, r1
7000067e:	bf38      	it	cc
70000680:	460b      	movcc	r3, r1
70000682:	4618      	mov	r0, r3
70000684:	4770      	bx	lr
	...

70000688 <rts_isp_get_sensor_ops>:
70000688:	4800      	ldr	r0, [pc, #0]	; (7000068c <rts_isp_get_sensor_ops+0x4>)
7000068a:	4770      	bx	lr
7000068c:	700006b0 	.word	0x700006b0

70000690 <g_sc231h_gain_config>:
70000690:	00102000 00202001 00303001 00383801     . ...  ..00..88.
700006a0:	00603480 00802381 00c03481 010a2483     .4`..#...4...$..

700006b0 <sc231h_ops>:
700006b0:	73000005 33326373 00006831 00000000     ...ssc231h......
	...
700006d4:	700002b5 70000379 00000000 70000605     ...py..p.......p
700006e4:	70000429 7000043d 00000000 00000000     )..p=..p........
700006f4:	70000415 00000000 00000000 00000000     ...p............
70000704:	7000052d 00000000 00000000 00000000     -..p............
70000714:	70000579 00000000 00000000 00000000     y..p............
70000724:	70000601 00000000 00000000 00000000     ...p............
	...
70000744:	0cfff04f 52d0ea1c ea1cbf1e ea9253d1     O......R.....S..
70000754:	ea930f0c d06f0f0c ea80441a 02400c01     ......o..D....@.
70000764:	ea5fbf18 d01e2141 6300f04f 1050ea43     .._.A!..O..cC.P.
70000774:	1151ea43 3101fba0 4000f00c 0f00f5b1     C.Q....1...@....
70000784:	0049bf3e 71d3ea41 ea40005b f1620001     >.I.A..q[.@...b.
70000794:	2afd027f f1b3d81d eb404f00 bf0850c2     ...*.....O@..P..
700007a4:	0001f020 f0904770 f00c0f00 bf084c00      ...pG.......L..
700007b4:	ea4c0249 ea402050 3a7f2051 f1d2bfc2     I.L.P @.Q .:....
700007c4:	ea4003ff 477050c2 0000f440 0300f04f     ..@..PpG@...O...
700007d4:	dc5d3a01 0f19f112 f000bfdc 47704000     .:]..........@pG
700007e4:	0200f1c2 fa210041 f1c2f102 fa000220     ....A.!..... ...
700007f4:	ea5ffc02 f1400031 ea530000 bf08034c     .._.1.@...S.L...
70000804:	70dcea20 f0924770 f0000f00 bf024c00      ..ppG.......L..
70000814:	f4100040 3a010f00 ea40d0f9 f093000c     @......:..@.....
70000824:	f0010f00 bf024c00 f4110049 3b010f00     .....L..I......;
70000834:	ea41d0f9 e78f010c 53d1ea0c 0f0cea92     ..A........S....
70000844:	ea93bf18 d00a0f0c 4c00f030 f031bf18     ........0..L..1.
70000854:	d1d84c00 0001ea80 4000f000 f0904770     .L.........@pG..
70000864:	bf170f00 4f00f090 f0914608 f0910f00     .......O.F......
70000874:	d0144f00 0f0cea92 0242d101 ea93d10f     .O........B.....
70000884:	d1030f0c bf18024b d1084608 0001ea80     ....K....F......
70000894:	4000f000 40fef040 0000f440 f0404770     ...@@..@@...pG@.
700008a4:	f44040fe 47700040                       .@@.@.pG

700008ac <__aeabi_frsub>:
700008ac:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
700008b0:	e002      	b.n	700008b8 <__addsf3>
700008b2:	bf00      	nop

700008b4 <__aeabi_fsub>:
700008b4:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

700008b8 <__addsf3>:
700008b8:	0042      	lsls	r2, r0, #1
700008ba:	bf1f      	itttt	ne
700008bc:	ea5f 0341 	movsne.w	r3, r1, lsl #1
700008c0:	ea92 0f03 	teqne	r2, r3
700008c4:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
700008c8:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700008cc:	d06a      	beq.n	700009a4 <__addsf3+0xec>
700008ce:	ea4f 6212 	mov.w	r2, r2, lsr #24
700008d2:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
700008d6:	bfc1      	itttt	gt
700008d8:	18d2      	addgt	r2, r2, r3
700008da:	4041      	eorgt	r1, r0
700008dc:	4048      	eorgt	r0, r1
700008de:	4041      	eorgt	r1, r0
700008e0:	bfb8      	it	lt
700008e2:	425b      	neglt	r3, r3
700008e4:	2b19      	cmp	r3, #25
700008e6:	bf88      	it	hi
700008e8:	4770      	bxhi	lr
700008ea:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
700008ee:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700008f2:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
700008f6:	bf18      	it	ne
700008f8:	4240      	negne	r0, r0
700008fa:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
700008fe:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
70000902:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
70000906:	bf18      	it	ne
70000908:	4249      	negne	r1, r1
7000090a:	ea92 0f03 	teq	r2, r3
7000090e:	d03f      	beq.n	70000990 <__addsf3+0xd8>
70000910:	f1a2 0201 	sub.w	r2, r2, #1
70000914:	fa41 fc03 	asr.w	ip, r1, r3
70000918:	eb10 000c 	adds.w	r0, r0, ip
7000091c:	f1c3 0320 	rsb	r3, r3, #32
70000920:	fa01 f103 	lsl.w	r1, r1, r3
70000924:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000928:	d502      	bpl.n	70000930 <__addsf3+0x78>
7000092a:	4249      	negs	r1, r1
7000092c:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70000930:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70000934:	d313      	bcc.n	7000095e <__addsf3+0xa6>
70000936:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
7000093a:	d306      	bcc.n	7000094a <__addsf3+0x92>
7000093c:	0840      	lsrs	r0, r0, #1
7000093e:	ea4f 0131 	mov.w	r1, r1, rrx
70000942:	f102 0201 	add.w	r2, r2, #1
70000946:	2afe      	cmp	r2, #254	; 0xfe
70000948:	d251      	bcs.n	700009ee <__addsf3+0x136>
7000094a:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
7000094e:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000952:	bf08      	it	eq
70000954:	f020 0001 	biceq.w	r0, r0, #1
70000958:	ea40 0003 	orr.w	r0, r0, r3
7000095c:	4770      	bx	lr
7000095e:	0049      	lsls	r1, r1, #1
70000960:	eb40 0000 	adc.w	r0, r0, r0
70000964:	3a01      	subs	r2, #1
70000966:	bf28      	it	cs
70000968:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
7000096c:	d2ed      	bcs.n	7000094a <__addsf3+0x92>
7000096e:	fab0 fc80 	clz	ip, r0
70000972:	f1ac 0c08 	sub.w	ip, ip, #8
70000976:	ebb2 020c 	subs.w	r2, r2, ip
7000097a:	fa00 f00c 	lsl.w	r0, r0, ip
7000097e:	bfaa      	itet	ge
70000980:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
70000984:	4252      	neglt	r2, r2
70000986:	4318      	orrge	r0, r3
70000988:	bfbc      	itt	lt
7000098a:	40d0      	lsrlt	r0, r2
7000098c:	4318      	orrlt	r0, r3
7000098e:	4770      	bx	lr
70000990:	f092 0f00 	teq	r2, #0
70000994:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
70000998:	bf06      	itte	eq
7000099a:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
7000099e:	3201      	addeq	r2, #1
700009a0:	3b01      	subne	r3, #1
700009a2:	e7b5      	b.n	70000910 <__addsf3+0x58>
700009a4:	ea4f 0341 	mov.w	r3, r1, lsl #1
700009a8:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700009ac:	bf18      	it	ne
700009ae:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700009b2:	d021      	beq.n	700009f8 <__addsf3+0x140>
700009b4:	ea92 0f03 	teq	r2, r3
700009b8:	d004      	beq.n	700009c4 <__addsf3+0x10c>
700009ba:	f092 0f00 	teq	r2, #0
700009be:	bf08      	it	eq
700009c0:	4608      	moveq	r0, r1
700009c2:	4770      	bx	lr
700009c4:	ea90 0f01 	teq	r0, r1
700009c8:	bf1c      	itt	ne
700009ca:	2000      	movne	r0, #0
700009cc:	4770      	bxne	lr
700009ce:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
700009d2:	d104      	bne.n	700009de <__addsf3+0x126>
700009d4:	0040      	lsls	r0, r0, #1
700009d6:	bf28      	it	cs
700009d8:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
700009dc:	4770      	bx	lr
700009de:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
700009e2:	bf3c      	itt	cc
700009e4:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
700009e8:	4770      	bxcc	lr
700009ea:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
700009ee:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
700009f2:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700009f6:	4770      	bx	lr
700009f8:	ea7f 6222 	mvns.w	r2, r2, asr #24
700009fc:	bf16      	itet	ne
700009fe:	4608      	movne	r0, r1
70000a00:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70000a04:	4601      	movne	r1, r0
70000a06:	0242      	lsls	r2, r0, #9
70000a08:	bf06      	itte	eq
70000a0a:	ea5f 2341 	movseq.w	r3, r1, lsl #9
70000a0e:	ea90 0f01 	teqeq	r0, r1
70000a12:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
70000a16:	4770      	bx	lr

70000a18 <__aeabi_ui2f>:
70000a18:	f04f 0300 	mov.w	r3, #0
70000a1c:	e004      	b.n	70000a28 <__aeabi_i2f+0x8>
70000a1e:	bf00      	nop

70000a20 <__aeabi_i2f>:
70000a20:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70000a24:	bf48      	it	mi
70000a26:	4240      	negmi	r0, r0
70000a28:	ea5f 0c00 	movs.w	ip, r0
70000a2c:	bf08      	it	eq
70000a2e:	4770      	bxeq	lr
70000a30:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70000a34:	4601      	mov	r1, r0
70000a36:	f04f 0000 	mov.w	r0, #0
70000a3a:	e01c      	b.n	70000a76 <__aeabi_l2f+0x2a>

70000a3c <__aeabi_ul2f>:
70000a3c:	ea50 0201 	orrs.w	r2, r0, r1
70000a40:	bf08      	it	eq
70000a42:	4770      	bxeq	lr
70000a44:	f04f 0300 	mov.w	r3, #0
70000a48:	e00a      	b.n	70000a60 <__aeabi_l2f+0x14>
70000a4a:	bf00      	nop

70000a4c <__aeabi_l2f>:
70000a4c:	ea50 0201 	orrs.w	r2, r0, r1
70000a50:	bf08      	it	eq
70000a52:	4770      	bxeq	lr
70000a54:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70000a58:	d502      	bpl.n	70000a60 <__aeabi_l2f+0x14>
70000a5a:	4240      	negs	r0, r0
70000a5c:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000a60:	ea5f 0c01 	movs.w	ip, r1
70000a64:	bf02      	ittt	eq
70000a66:	4684      	moveq	ip, r0
70000a68:	4601      	moveq	r1, r0
70000a6a:	2000      	moveq	r0, #0
70000a6c:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70000a70:	bf08      	it	eq
70000a72:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70000a76:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
70000a7a:	fabc f28c 	clz	r2, ip
70000a7e:	3a08      	subs	r2, #8
70000a80:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
70000a84:	db10      	blt.n	70000aa8 <__aeabi_l2f+0x5c>
70000a86:	fa01 fc02 	lsl.w	ip, r1, r2
70000a8a:	4463      	add	r3, ip
70000a8c:	fa00 fc02 	lsl.w	ip, r0, r2
70000a90:	f1c2 0220 	rsb	r2, r2, #32
70000a94:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000a98:	fa20 f202 	lsr.w	r2, r0, r2
70000a9c:	eb43 0002 	adc.w	r0, r3, r2
70000aa0:	bf08      	it	eq
70000aa2:	f020 0001 	biceq.w	r0, r0, #1
70000aa6:	4770      	bx	lr
70000aa8:	f102 0220 	add.w	r2, r2, #32
70000aac:	fa01 fc02 	lsl.w	ip, r1, r2
70000ab0:	f1c2 0220 	rsb	r2, r2, #32
70000ab4:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
70000ab8:	fa21 f202 	lsr.w	r2, r1, r2
70000abc:	eb43 0002 	adc.w	r0, r3, r2
70000ac0:	bf08      	it	eq
70000ac2:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000ac6:	4770      	bx	lr

70000ac8 <__aeabi_fmul>:
70000ac8:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000acc:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000ad0:	bf1e      	ittt	ne
70000ad2:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000ad6:	ea92 0f0c 	teqne	r2, ip
70000ada:	ea93 0f0c 	teqne	r3, ip
70000ade:	d06f      	beq.n	70000bc0 <__aeabi_fmul+0xf8>
70000ae0:	441a      	add	r2, r3
70000ae2:	ea80 0c01 	eor.w	ip, r0, r1
70000ae6:	0240      	lsls	r0, r0, #9
70000ae8:	bf18      	it	ne
70000aea:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000aee:	d01e      	beq.n	70000b2e <__aeabi_fmul+0x66>
70000af0:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000af4:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000af8:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000afc:	fba0 3101 	umull	r3, r1, r0, r1
70000b00:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000b04:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000b08:	bf3e      	ittt	cc
70000b0a:	0049      	lslcc	r1, r1, #1
70000b0c:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000b10:	005b      	lslcc	r3, r3, #1
70000b12:	ea40 0001 	orr.w	r0, r0, r1
70000b16:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000b1a:	2afd      	cmp	r2, #253	; 0xfd
70000b1c:	d81d      	bhi.n	70000b5a <__aeabi_fmul+0x92>
70000b1e:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000b22:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000b26:	bf08      	it	eq
70000b28:	f020 0001 	biceq.w	r0, r0, #1
70000b2c:	4770      	bx	lr
70000b2e:	f090 0f00 	teq	r0, #0
70000b32:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000b36:	bf08      	it	eq
70000b38:	0249      	lsleq	r1, r1, #9
70000b3a:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000b3e:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000b42:	3a7f      	subs	r2, #127	; 0x7f
70000b44:	bfc2      	ittt	gt
70000b46:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000b4a:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000b4e:	4770      	bxgt	lr
70000b50:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000b54:	f04f 0300 	mov.w	r3, #0
70000b58:	3a01      	subs	r2, #1
70000b5a:	dc5d      	bgt.n	70000c18 <__aeabi_fmul+0x150>
70000b5c:	f112 0f19 	cmn.w	r2, #25
70000b60:	bfdc      	itt	le
70000b62:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000b66:	4770      	bxle	lr
70000b68:	f1c2 0200 	rsb	r2, r2, #0
70000b6c:	0041      	lsls	r1, r0, #1
70000b6e:	fa21 f102 	lsr.w	r1, r1, r2
70000b72:	f1c2 0220 	rsb	r2, r2, #32
70000b76:	fa00 fc02 	lsl.w	ip, r0, r2
70000b7a:	ea5f 0031 	movs.w	r0, r1, rrx
70000b7e:	f140 0000 	adc.w	r0, r0, #0
70000b82:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000b86:	bf08      	it	eq
70000b88:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000b8c:	4770      	bx	lr
70000b8e:	f092 0f00 	teq	r2, #0
70000b92:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000b96:	bf02      	ittt	eq
70000b98:	0040      	lsleq	r0, r0, #1
70000b9a:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000b9e:	3a01      	subeq	r2, #1
70000ba0:	d0f9      	beq.n	70000b96 <__aeabi_fmul+0xce>
70000ba2:	ea40 000c 	orr.w	r0, r0, ip
70000ba6:	f093 0f00 	teq	r3, #0
70000baa:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000bae:	bf02      	ittt	eq
70000bb0:	0049      	lsleq	r1, r1, #1
70000bb2:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000bb6:	3b01      	subeq	r3, #1
70000bb8:	d0f9      	beq.n	70000bae <__aeabi_fmul+0xe6>
70000bba:	ea41 010c 	orr.w	r1, r1, ip
70000bbe:	e78f      	b.n	70000ae0 <__aeabi_fmul+0x18>
70000bc0:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000bc4:	ea92 0f0c 	teq	r2, ip
70000bc8:	bf18      	it	ne
70000bca:	ea93 0f0c 	teqne	r3, ip
70000bce:	d00a      	beq.n	70000be6 <__aeabi_fmul+0x11e>
70000bd0:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000bd4:	bf18      	it	ne
70000bd6:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000bda:	d1d8      	bne.n	70000b8e <__aeabi_fmul+0xc6>
70000bdc:	ea80 0001 	eor.w	r0, r0, r1
70000be0:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000be4:	4770      	bx	lr
70000be6:	f090 0f00 	teq	r0, #0
70000bea:	bf17      	itett	ne
70000bec:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000bf0:	4608      	moveq	r0, r1
70000bf2:	f091 0f00 	teqne	r1, #0
70000bf6:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000bfa:	d014      	beq.n	70000c26 <__aeabi_fmul+0x15e>
70000bfc:	ea92 0f0c 	teq	r2, ip
70000c00:	d101      	bne.n	70000c06 <__aeabi_fmul+0x13e>
70000c02:	0242      	lsls	r2, r0, #9
70000c04:	d10f      	bne.n	70000c26 <__aeabi_fmul+0x15e>
70000c06:	ea93 0f0c 	teq	r3, ip
70000c0a:	d103      	bne.n	70000c14 <__aeabi_fmul+0x14c>
70000c0c:	024b      	lsls	r3, r1, #9
70000c0e:	bf18      	it	ne
70000c10:	4608      	movne	r0, r1
70000c12:	d108      	bne.n	70000c26 <__aeabi_fmul+0x15e>
70000c14:	ea80 0001 	eor.w	r0, r0, r1
70000c18:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000c1c:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000c20:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000c24:	4770      	bx	lr
70000c26:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000c2a:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000c2e:	4770      	bx	lr

70000c30 <__aeabi_fdiv>:
70000c30:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000c34:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000c38:	bf1e      	ittt	ne
70000c3a:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000c3e:	ea92 0f0c 	teqne	r2, ip
70000c42:	ea93 0f0c 	teqne	r3, ip
70000c46:	d069      	beq.n	70000d1c <__aeabi_fdiv+0xec>
70000c48:	eba2 0203 	sub.w	r2, r2, r3
70000c4c:	ea80 0c01 	eor.w	ip, r0, r1
70000c50:	0249      	lsls	r1, r1, #9
70000c52:	ea4f 2040 	mov.w	r0, r0, lsl #9
70000c56:	d037      	beq.n	70000cc8 <__aeabi_fdiv+0x98>
70000c58:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70000c5c:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70000c60:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70000c64:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000c68:	428b      	cmp	r3, r1
70000c6a:	bf38      	it	cc
70000c6c:	005b      	lslcc	r3, r3, #1
70000c6e:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70000c72:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70000c76:	428b      	cmp	r3, r1
70000c78:	bf24      	itt	cs
70000c7a:	1a5b      	subcs	r3, r3, r1
70000c7c:	ea40 000c 	orrcs.w	r0, r0, ip
70000c80:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70000c84:	bf24      	itt	cs
70000c86:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
70000c8a:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70000c8e:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70000c92:	bf24      	itt	cs
70000c94:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
70000c98:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
70000c9c:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
70000ca0:	bf24      	itt	cs
70000ca2:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
70000ca6:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
70000caa:	011b      	lsls	r3, r3, #4
70000cac:	bf18      	it	ne
70000cae:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70000cb2:	d1e0      	bne.n	70000c76 <__aeabi_fdiv+0x46>
70000cb4:	2afd      	cmp	r2, #253	; 0xfd
70000cb6:	f63f af50 	bhi.w	70000b5a <__aeabi_fmul+0x92>
70000cba:	428b      	cmp	r3, r1
70000cbc:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000cc0:	bf08      	it	eq
70000cc2:	f020 0001 	biceq.w	r0, r0, #1
70000cc6:	4770      	bx	lr
70000cc8:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000ccc:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000cd0:	327f      	adds	r2, #127	; 0x7f
70000cd2:	bfc2      	ittt	gt
70000cd4:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000cd8:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000cdc:	4770      	bxgt	lr
70000cde:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000ce2:	f04f 0300 	mov.w	r3, #0
70000ce6:	3a01      	subs	r2, #1
70000ce8:	e737      	b.n	70000b5a <__aeabi_fmul+0x92>
70000cea:	f092 0f00 	teq	r2, #0
70000cee:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000cf2:	bf02      	ittt	eq
70000cf4:	0040      	lsleq	r0, r0, #1
70000cf6:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000cfa:	3a01      	subeq	r2, #1
70000cfc:	d0f9      	beq.n	70000cf2 <__aeabi_fdiv+0xc2>
70000cfe:	ea40 000c 	orr.w	r0, r0, ip
70000d02:	f093 0f00 	teq	r3, #0
70000d06:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000d0a:	bf02      	ittt	eq
70000d0c:	0049      	lsleq	r1, r1, #1
70000d0e:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000d12:	3b01      	subeq	r3, #1
70000d14:	d0f9      	beq.n	70000d0a <__aeabi_fdiv+0xda>
70000d16:	ea41 010c 	orr.w	r1, r1, ip
70000d1a:	e795      	b.n	70000c48 <__aeabi_fdiv+0x18>
70000d1c:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000d20:	ea92 0f0c 	teq	r2, ip
70000d24:	d108      	bne.n	70000d38 <__aeabi_fdiv+0x108>
70000d26:	0242      	lsls	r2, r0, #9
70000d28:	f47f af7d 	bne.w	70000c26 <__aeabi_fmul+0x15e>
70000d2c:	ea93 0f0c 	teq	r3, ip
70000d30:	f47f af70 	bne.w	70000c14 <__aeabi_fmul+0x14c>
70000d34:	4608      	mov	r0, r1
70000d36:	e776      	b.n	70000c26 <__aeabi_fmul+0x15e>
70000d38:	ea93 0f0c 	teq	r3, ip
70000d3c:	d104      	bne.n	70000d48 <__aeabi_fdiv+0x118>
70000d3e:	024b      	lsls	r3, r1, #9
70000d40:	f43f af4c 	beq.w	70000bdc <__aeabi_fmul+0x114>
70000d44:	4608      	mov	r0, r1
70000d46:	e76e      	b.n	70000c26 <__aeabi_fmul+0x15e>
70000d48:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000d4c:	bf18      	it	ne
70000d4e:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000d52:	d1ca      	bne.n	70000cea <__aeabi_fdiv+0xba>
70000d54:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70000d58:	f47f af5c 	bne.w	70000c14 <__aeabi_fmul+0x14c>
70000d5c:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70000d60:	f47f af3c 	bne.w	70000bdc <__aeabi_fmul+0x114>
70000d64:	e75f      	b.n	70000c26 <__aeabi_fmul+0x15e>
70000d66:	bf00      	nop

70000d68 <__gesf2>:
70000d68:	f04f 3cff 	mov.w	ip, #4294967295
70000d6c:	e006      	b.n	70000d7c <__cmpsf2+0x4>
70000d6e:	bf00      	nop

70000d70 <__lesf2>:
70000d70:	f04f 0c01 	mov.w	ip, #1
70000d74:	e002      	b.n	70000d7c <__cmpsf2+0x4>
70000d76:	bf00      	nop

70000d78 <__cmpsf2>:
70000d78:	f04f 0c01 	mov.w	ip, #1
70000d7c:	f84d cd04 	str.w	ip, [sp, #-4]!
70000d80:	ea4f 0240 	mov.w	r2, r0, lsl #1
70000d84:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000d88:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000d8c:	bf18      	it	ne
70000d8e:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000d92:	d011      	beq.n	70000db8 <__cmpsf2+0x40>
70000d94:	b001      	add	sp, #4
70000d96:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
70000d9a:	bf18      	it	ne
70000d9c:	ea90 0f01 	teqne	r0, r1
70000da0:	bf58      	it	pl
70000da2:	ebb2 0003 	subspl.w	r0, r2, r3
70000da6:	bf88      	it	hi
70000da8:	17c8      	asrhi	r0, r1, #31
70000daa:	bf38      	it	cc
70000dac:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70000db0:	bf18      	it	ne
70000db2:	f040 0001 	orrne.w	r0, r0, #1
70000db6:	4770      	bx	lr
70000db8:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000dbc:	d102      	bne.n	70000dc4 <__cmpsf2+0x4c>
70000dbe:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70000dc2:	d105      	bne.n	70000dd0 <__cmpsf2+0x58>
70000dc4:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70000dc8:	d1e4      	bne.n	70000d94 <__cmpsf2+0x1c>
70000dca:	ea5f 2c41 	movs.w	ip, r1, lsl #9
70000dce:	d0e1      	beq.n	70000d94 <__cmpsf2+0x1c>
70000dd0:	f85d 0b04 	ldr.w	r0, [sp], #4
70000dd4:	4770      	bx	lr
70000dd6:	bf00      	nop

70000dd8 <__aeabi_cfrcmple>:
70000dd8:	4684      	mov	ip, r0
70000dda:	4608      	mov	r0, r1
70000ddc:	4661      	mov	r1, ip
70000dde:	e7ff      	b.n	70000de0 <__aeabi_cfcmpeq>

70000de0 <__aeabi_cfcmpeq>:
70000de0:	b50f      	push	{r0, r1, r2, r3, lr}
70000de2:	f7ff ffc9 	bl	70000d78 <__cmpsf2>
70000de6:	2800      	cmp	r0, #0
70000de8:	bf48      	it	mi
70000dea:	f110 0f00 	cmnmi.w	r0, #0
70000dee:	bd0f      	pop	{r0, r1, r2, r3, pc}

70000df0 <__aeabi_fcmpeq>:
70000df0:	f84d ed08 	str.w	lr, [sp, #-8]!
70000df4:	f7ff fff4 	bl	70000de0 <__aeabi_cfcmpeq>
70000df8:	bf0c      	ite	eq
70000dfa:	2001      	moveq	r0, #1
70000dfc:	2000      	movne	r0, #0
70000dfe:	f85d fb08 	ldr.w	pc, [sp], #8
70000e02:	bf00      	nop

70000e04 <__aeabi_fcmplt>:
70000e04:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e08:	f7ff ffea 	bl	70000de0 <__aeabi_cfcmpeq>
70000e0c:	bf34      	ite	cc
70000e0e:	2001      	movcc	r0, #1
70000e10:	2000      	movcs	r0, #0
70000e12:	f85d fb08 	ldr.w	pc, [sp], #8
70000e16:	bf00      	nop

70000e18 <__aeabi_fcmple>:
70000e18:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e1c:	f7ff ffe0 	bl	70000de0 <__aeabi_cfcmpeq>
70000e20:	bf94      	ite	ls
70000e22:	2001      	movls	r0, #1
70000e24:	2000      	movhi	r0, #0
70000e26:	f85d fb08 	ldr.w	pc, [sp], #8
70000e2a:	bf00      	nop

70000e2c <__aeabi_fcmpge>:
70000e2c:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e30:	f7ff ffd2 	bl	70000dd8 <__aeabi_cfrcmple>
70000e34:	bf94      	ite	ls
70000e36:	2001      	movls	r0, #1
70000e38:	2000      	movhi	r0, #0
70000e3a:	f85d fb08 	ldr.w	pc, [sp], #8
70000e3e:	bf00      	nop

70000e40 <__aeabi_fcmpgt>:
70000e40:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e44:	f7ff ffc8 	bl	70000dd8 <__aeabi_cfrcmple>
70000e48:	bf34      	ite	cc
70000e4a:	2001      	movcc	r0, #1
70000e4c:	2000      	movcs	r0, #0
70000e4e:	f85d fb08 	ldr.w	pc, [sp], #8
70000e52:	bf00      	nop

70000e54 <__aeabi_f2uiz>:
70000e54:	0042      	lsls	r2, r0, #1
70000e56:	d20e      	bcs.n	70000e76 <__aeabi_f2uiz+0x22>
70000e58:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70000e5c:	d30b      	bcc.n	70000e76 <__aeabi_f2uiz+0x22>
70000e5e:	f04f 039e 	mov.w	r3, #158	; 0x9e
70000e62:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70000e66:	d409      	bmi.n	70000e7c <__aeabi_f2uiz+0x28>
70000e68:	ea4f 2300 	mov.w	r3, r0, lsl #8
70000e6c:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000e70:	fa23 f002 	lsr.w	r0, r3, r2
70000e74:	4770      	bx	lr
70000e76:	f04f 0000 	mov.w	r0, #0
70000e7a:	4770      	bx	lr
70000e7c:	f112 0f61 	cmn.w	r2, #97	; 0x61
70000e80:	d101      	bne.n	70000e86 <__aeabi_f2uiz+0x32>
70000e82:	0242      	lsls	r2, r0, #9
70000e84:	d102      	bne.n	70000e8c <__aeabi_f2uiz+0x38>
70000e86:	f04f 30ff 	mov.w	r0, #4294967295
70000e8a:	4770      	bx	lr
70000e8c:	f04f 0000 	mov.w	r0, #0
70000e90:	4770      	bx	lr
70000e92:	bf00      	nop
