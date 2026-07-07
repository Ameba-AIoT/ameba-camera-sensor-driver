
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	35 08 00 70 49 02 00 70                             5..pI..p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

7000005c <g_imx327_i2c_init_regs_hdr>:
7000005c:	02 30 00 00 05 30 01 00 07 30 00 00 09 30 01 00     .0...0...0...0..
7000006c:	0a 30 f0 00 0c 30 11 00 11 30 02 00 18 30 e2 00     .0...0...0...0..
7000007c:	19 30 04 00 1c 30 98 00 1d 30 08 00 20 30 02 00     .0...0...0.. 0..
7000008c:	21 30 00 00 24 30 c9 00 25 30 07 00 30 30 11 00     !0..$0..%0..00..
7000009c:	31 30 00 00 45 30 05 00 46 30 01 00 4b 30 0a 00     10..E0..F0..K0..
700000ac:	5c 30 18 00 5d 30 03 00 5e 30 20 00 5f 30 01 00     \0..]0..^0 ._0..
700000bc:	9e 30 4a 00 9f 30 4a 00 d2 30 19 00 d7 30 03 00     .0J..0J..0...0..
700000cc:	06 31 11 00 29 31 00 00 3b 31 61 00 5e 31 1a 00     .1..)1..;1a.^1..
700000dc:	64 31 1a 00 7c 31 00 00 ec 31 0e 00 05 34 00 00     d1..|1...1...4..
700000ec:	07 34 01 00 14 34 0a 00 15 34 00 00 18 34 b4 00     .4...4...4...4..
700000fc:	19 34 08 00 41 34 0c 00 42 34 0c 00 43 34 01 00     .4..A4..B4..C4..
7000010c:	44 34 20 00 45 34 25 00 46 34 77 00 47 34 00 00     D4 .E4%.F4w.G4..
7000011c:	48 34 67 00 49 34 00 00 4a 34 47 00 4b 34 00 00     H4g.I4..J4G.K4..
7000012c:	4c 34 37 00 4d 34 00 00 4e 34 3f 00 4f 34 00 00     L47.M4..N4?.O4..
7000013c:	50 34 ff 00 51 34 00 00 52 34 3f 00 53 34 00 00     P4..Q4..R4?.S4..
7000014c:	54 34 37 00 55 34 00 00 72 34 a0 00 73 34 07 00     T47.U4..r4..s4..
7000015c:	7b 34 23 00 80 34 49 00 00 30 00 00                 {4#..4I..0..

70000168 <g_imx327_i2c_init_regs_linear>:
70000168:	02 30 00 00 05 30 00 00 07 30 00 00 09 30 02 00     .0...0...0...0..
70000178:	0a 30 3c 00 11 30 02 00 18 30 65 00 19 30 04 00     .0<..0...0e..0..
70000188:	1c 30 30 00 1d 30 11 00 46 30 00 00 4b 30 0a 00     .00..0..F0..K0..
70000198:	5c 30 18 00 5d 30 03 00 5e 30 20 00 5f 30 01 00     \0..]0..^0 ._0..
700001a8:	9e 30 4a 00 9f 30 4a 00 d2 30 19 00 d7 30 03 00     .0J..0J..0...0..
700001b8:	29 31 1d 00 3b 31 61 00 5e 31 1a 00 64 31 1a 00     )1..;1a.^1..d1..
700001c8:	7c 31 12 00 ec 31 37 00 05 34 10 00 07 34 01 00     |1...17..4...4..
700001d8:	14 34 0a 00 18 34 49 00 19 34 04 00 41 34 0c 00     .4...4I..4..A4..
700001e8:	42 34 0c 00 43 34 01 00 44 34 20 00 45 34 25 00     B4..C4..D4 .E4%.
700001f8:	46 34 57 00 47 34 00 00 48 34 37 00 49 34 00 00     F4W.G4..H47.I4..
70000208:	4a 34 1f 00 4b 34 00 00 4c 34 1f 00 4d 34 00 00     J4..K4..L4..M4..
70000218:	4e 34 1f 00 4f 34 00 00 50 34 77 00 51 34 00 00     N4..O4..P4w.Q4..
70000228:	52 34 1f 00 53 34 00 00 54 34 17 00 55 34 00 00     R4..S4..T4..U4..
70000238:	72 34 9c 00 73 34 07 00 80 34 49 00 00 30 00 00     r4..s4...4I..0..

70000248 <rts_isp_set_voe_ops>:
70000248:	4b01      	ldr	r3, [pc, #4]	; (70000250 <rts_isp_set_voe_ops+0x8>)
7000024a:	6018      	str	r0, [r3, #0]
7000024c:	4770      	bx	lr
7000024e:	bf00      	nop
70000250:	70000048 	.word	0x70000048

70000254 <isp_driver_is_fpga>:
70000254:	2000      	movs	r0, #0
70000256:	4770      	bx	lr

70000258 <imx327_get_info>:
70000258:	b510      	push	{r4, lr}
7000025a:	2800      	cmp	r0, #0
7000025c:	d14e      	bne.n	700002fc <imx327_get_info+0xa4>
7000025e:	2900      	cmp	r1, #0
70000260:	d04c      	beq.n	700002fc <imx327_get_info+0xa4>
70000262:	f44f 64f0 	mov.w	r4, #1920	; 0x780
70000266:	f44f 6287 	mov.w	r2, #1080	; 0x438
7000026a:	4b26      	ldr	r3, [pc, #152]	; (70000304 <imx327_get_info+0xac>)
7000026c:	f8df c098 	ldr.w	ip, [pc, #152]	; 70000308 <imx327_get_info+0xb0>
70000270:	610b      	str	r3, [r1, #16]
70000272:	2301      	movs	r3, #1
70000274:	7108      	strb	r0, [r1, #4]
70000276:	750b      	strb	r3, [r1, #20]
70000278:	f8c1 30a8 	str.w	r3, [r1, #168]	; 0xa8
7000027c:	f881 00a4 	strb.w	r0, [r1, #164]	; 0xa4
70000280:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
70000284:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
70000288:	e9c1 4202 	strd	r4, r2, [r1, #8]
7000028c:	e9c1 4206 	strd	r4, r2, [r1, #24]
70000290:	4a1e      	ldr	r2, [pc, #120]	; (7000030c <imx327_get_info+0xb4>)
70000292:	f44f 74fa 	mov.w	r4, #500	; 0x1f4
70000296:	620a      	str	r2, [r1, #32]
70000298:	2202      	movs	r2, #2
7000029a:	e9c1 c427 	strd	ip, r4, [r1, #156]	; 0x9c
7000029e:	600a      	str	r2, [r1, #0]
700002a0:	f44f 64fa 	mov.w	r4, #2000	; 0x7d0
700002a4:	4a1a      	ldr	r2, [pc, #104]	; (70000310 <imx327_get_info+0xb8>)
700002a6:	f8c1 40ac 	str.w	r4, [r1, #172]	; 0xac
700002aa:	241a      	movs	r4, #26
700002ac:	7812      	ldrb	r2, [r2, #0]
700002ae:	f881 4085 	strb.w	r4, [r1, #133]	; 0x85
700002b2:	f44f 7481 	mov.w	r4, #258	; 0x102
700002b6:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
700002ba:	2203      	movs	r2, #3
700002bc:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
700002c0:	f881 2098 	strb.w	r2, [r1, #152]	; 0x98
700002c4:	f8c1 2088 	str.w	r2, [r1, #136]	; 0x88
700002c8:	f881 22e4 	strb.w	r2, [r1, #740]	; 0x2e4
700002cc:	e9c1 03b7 	strd	r0, r3, [r1, #732]	; 0x2dc
700002d0:	e9c1 03ba 	strd	r0, r3, [r1, #744]	; 0x2e8
700002d4:	2304      	movs	r3, #4
700002d6:	f881 32f0 	strb.w	r3, [r1, #752]	; 0x2f0
700002da:	2306      	movs	r3, #6
700002dc:	e9c1 0024 	strd	r0, r0, [r1, #144]	; 0x90
700002e0:	e9c1 00bd 	strd	r0, r0, [r1, #756]	; 0x2f4
700002e4:	f881 32fc 	strb.w	r3, [r1, #764]	; 0x2fc
700002e8:	2305      	movs	r3, #5
700002ea:	e9c1 00c0 	strd	r0, r0, [r1, #768]	; 0x300
700002ee:	f881 3308 	strb.w	r3, [r1, #776]	; 0x308
700002f2:	f8c1 32d4 	str.w	r3, [r1, #724]	; 0x2d4
700002f6:	e9c1 00c3 	strd	r0, r0, [r1, #780]	; 0x30c
700002fa:	bd10      	pop	{r4, pc}
700002fc:	f06f 0015 	mvn.w	r0, #21
70000300:	e7fb      	b.n	700002fa <imx327_get_info+0xa2>
70000302:	bf00      	nop
70000304:	41f00000 	.word	0x41f00000
70000308:	02367b88 	.word	0x02367b88
7000030c:	41d80000 	.word	0x41d80000
70000310:	7000004c 	.word	0x7000004c

70000314 <imx327_get_init_info>:
70000314:	b510      	push	{r4, lr}
70000316:	2800      	cmp	r0, #0
70000318:	d15f      	bne.n	700003da <imx327_get_init_info+0xc6>
7000031a:	2a00      	cmp	r2, #0
7000031c:	d05d      	beq.n	700003da <imx327_get_init_info+0xc6>
7000031e:	7809      	ldrb	r1, [r1, #0]
70000320:	4b2f      	ldr	r3, [pc, #188]	; (700003e0 <imx327_get_init_info+0xcc>)
70000322:	2901      	cmp	r1, #1
70000324:	7019      	strb	r1, [r3, #0]
70000326:	d12d      	bne.n	70000384 <imx327_get_init_info+0x70>
70000328:	492e      	ldr	r1, [pc, #184]	; (700003e4 <imx327_get_init_info+0xd0>)
7000032a:	f240 7c9c 	movw	ip, #1948	; 0x79c
7000032e:	240d      	movs	r4, #13
70000330:	6090      	str	r0, [r2, #8]
70000332:	6051      	str	r1, [r2, #4]
70000334:	2143      	movs	r1, #67	; 0x43
70000336:	6011      	str	r1, [r2, #0]
70000338:	2102      	movs	r1, #2
7000033a:	f882 1064 	strb.w	r1, [r2, #100]	; 0x64
7000033e:	f240 3103 	movw	r1, #771	; 0x303
70000342:	f8a2 1068 	strh.w	r1, [r2, #104]	; 0x68
70000346:	210c      	movs	r1, #12
70000348:	f8a2 1074 	strh.w	r1, [r2, #116]	; 0x74
7000034c:	2103      	movs	r1, #3
7000034e:	6791      	str	r1, [r2, #120]	; 0x78
70000350:	f882 1060 	strb.w	r1, [r2, #96]	; 0x60
70000354:	f240 4149 	movw	r1, #1097	; 0x449
70000358:	e9c2 c120 	strd	ip, r1, [r2, #128]	; 0x80
7000035c:	2108      	movs	r1, #8
7000035e:	f241 1c30 	movw	ip, #4400	; 0x1130
70000362:	e9c2 4122 	strd	r4, r1, [r2, #136]	; 0x88
70000366:	4920      	ldr	r1, [pc, #128]	; (700003e8 <imx327_get_init_info+0xd4>)
70000368:	e9c2 1c24 	strd	r1, ip, [r2, #144]	; 0x90
7000036c:	f240 41e2 	movw	r1, #1250	; 0x4e2
70000370:	f8c2 1098 	str.w	r1, [r2, #152]	; 0x98
70000374:	8199      	strh	r1, [r3, #12]
70000376:	f640 11c4 	movw	r1, #2500	; 0x9c4
7000037a:	f8c2 109c 	str.w	r1, [r2, #156]	; 0x9c
7000037e:	4a1b      	ldr	r2, [pc, #108]	; (700003ec <imx327_get_init_info+0xd8>)
70000380:	605a      	str	r2, [r3, #4]
70000382:	bd10      	pop	{r4, pc}
70000384:	491a      	ldr	r1, [pc, #104]	; (700003f0 <imx327_get_init_info+0xdc>)
70000386:	f240 4449 	movw	r4, #1097	; 0x449
7000038a:	f240 7c9c 	movw	ip, #1948	; 0x79c
7000038e:	6090      	str	r0, [r2, #8]
70000390:	6051      	str	r1, [r2, #4]
70000392:	2138      	movs	r1, #56	; 0x38
70000394:	6011      	str	r1, [r2, #0]
70000396:	2102      	movs	r1, #2
70000398:	f882 1064 	strb.w	r1, [r2, #100]	; 0x64
7000039c:	f240 3103 	movw	r1, #771	; 0x303
700003a0:	f8a2 1068 	strh.w	r1, [r2, #104]	; 0x68
700003a4:	210c      	movs	r1, #12
700003a6:	e9c2 c420 	strd	ip, r4, [r2, #128]	; 0x80
700003aa:	f8a2 1074 	strh.w	r1, [r2, #116]	; 0x74
700003ae:	240d      	movs	r4, #13
700003b0:	2104      	movs	r1, #4
700003b2:	e9c2 4122 	strd	r4, r1, [r2, #136]	; 0x88
700003b6:	f882 1060 	strb.w	r1, [r2, #96]	; 0x60
700003ba:	f640 0498 	movw	r4, #2200	; 0x898
700003be:	490d      	ldr	r1, [pc, #52]	; (700003f4 <imx327_get_init_info+0xe0>)
700003c0:	e9c2 1424 	strd	r1, r4, [r2, #144]	; 0x90
700003c4:	f240 4165 	movw	r1, #1125	; 0x465
700003c8:	f8c2 1098 	str.w	r1, [r2, #152]	; 0x98
700003cc:	8199      	strh	r1, [r3, #12]
700003ce:	f248 31d6 	movw	r1, #33750	; 0x83d6
700003d2:	f8c2 109c 	str.w	r1, [r2, #156]	; 0x9c
700003d6:	4a08      	ldr	r2, [pc, #32]	; (700003f8 <imx327_get_init_info+0xe4>)
700003d8:	e7d2      	b.n	70000380 <imx327_get_init_info+0x6c>
700003da:	f06f 0015 	mvn.w	r0, #21
700003de:	e7d0      	b.n	70000382 <imx327_get_init_info+0x6e>
700003e0:	7000004c 	.word	0x7000004c
700003e4:	7000005c 	.word	0x7000005c
700003e8:	08d9ee20 	.word	0x08d9ee20
700003ec:	416d097b 	.word	0x416d097b
700003f0:	70000168 	.word	0x70000168
700003f4:	046cf710 	.word	0x046cf710
700003f8:	41ed097b 	.word	0x41ed097b

700003fc <imx327_start>:
700003fc:	b918      	cbnz	r0, 70000406 <imx327_start+0xa>
700003fe:	4b03      	ldr	r3, [pc, #12]	; (7000040c <imx327_start+0x10>)
70000400:	2200      	movs	r2, #0
70000402:	609a      	str	r2, [r3, #8]
70000404:	4770      	bx	lr
70000406:	f06f 0015 	mvn.w	r0, #21
7000040a:	4770      	bx	lr
7000040c:	7000004c 	.word	0x7000004c

70000410 <imx327_get_tuned_dgain>:
70000410:	b948      	cbnz	r0, 70000426 <imx327_get_tuned_dgain+0x16>
70000412:	b141      	cbz	r1, 70000426 <imx327_get_tuned_dgain+0x16>
70000414:	4a05      	ldr	r2, [pc, #20]	; (7000042c <imx327_get_tuned_dgain+0x1c>)
70000416:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
7000041a:	7812      	ldrb	r2, [r2, #0]
7000041c:	600b      	str	r3, [r1, #0]
7000041e:	2a01      	cmp	r2, #1
70000420:	d103      	bne.n	7000042a <imx327_get_tuned_dgain+0x1a>
70000422:	604b      	str	r3, [r1, #4]
70000424:	4770      	bx	lr
70000426:	f06f 0015 	mvn.w	r0, #21
7000042a:	4770      	bx	lr
7000042c:	7000004c 	.word	0x7000004c

70000430 <imx327_set_mirror_flip>:
70000430:	780b      	ldrb	r3, [r1, #0]
70000432:	2201      	movs	r2, #1
70000434:	7848      	ldrb	r0, [r1, #1]
70000436:	2b00      	cmp	r3, #0
70000438:	708a      	strb	r2, [r1, #2]
7000043a:	604a      	str	r2, [r1, #4]
7000043c:	bf14      	ite	ne
7000043e:	2302      	movne	r3, #2
70000440:	2300      	moveq	r3, #0
70000442:	b510      	push	{r4, lr}
70000444:	2800      	cmp	r0, #0
70000446:	bf18      	it	ne
70000448:	f043 0301 	orrne.w	r3, r3, #1
7000044c:	f243 0407 	movw	r4, #12295	; 0x3007
70000450:	2000      	movs	r0, #0
70000452:	820c      	strh	r4, [r1, #16]
70000454:	824b      	strh	r3, [r1, #18]
70000456:	bd10      	pop	{r4, pc}

70000458 <imx327_check>:
70000458:	e92d 41f3 	stmdb	sp!, {r0, r1, r4, r5, r6, r7, r8, lr}
7000045c:	4d1c      	ldr	r5, [pc, #112]	; (700004d0 <imx327_check+0x78>)
7000045e:	4607      	mov	r7, r0
70000460:	682b      	ldr	r3, [r5, #0]
70000462:	685b      	ldr	r3, [r3, #4]
70000464:	4798      	blx	r3
70000466:	f243 031e 	movw	r3, #12318	; 0x301e
7000046a:	a901      	add	r1, sp, #4
7000046c:	4638      	mov	r0, r7
7000046e:	f8ad 3004 	strh.w	r3, [sp, #4]
70000472:	682b      	ldr	r3, [r5, #0]
70000474:	68db      	ldr	r3, [r3, #12]
70000476:	4798      	blx	r3
70000478:	4604      	mov	r4, r0
7000047a:	b130      	cbz	r0, 7000048a <imx327_check+0x32>
7000047c:	682b      	ldr	r3, [r5, #0]
7000047e:	689b      	ldr	r3, [r3, #8]
70000480:	4798      	blx	r3
70000482:	4620      	mov	r0, r4
70000484:	b002      	add	sp, #8
70000486:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
7000048a:	f243 031f 	movw	r3, #12319	; 0x301f
7000048e:	a901      	add	r1, sp, #4
70000490:	4638      	mov	r0, r7
70000492:	f8bd 8006 	ldrh.w	r8, [sp, #6]
70000496:	f8ad 3004 	strh.w	r3, [sp, #4]
7000049a:	682b      	ldr	r3, [r5, #0]
7000049c:	68db      	ldr	r3, [r3, #12]
7000049e:	4798      	blx	r3
700004a0:	682b      	ldr	r3, [r5, #0]
700004a2:	4604      	mov	r4, r0
700004a4:	689b      	ldr	r3, [r3, #8]
700004a6:	4798      	blx	r3
700004a8:	2c00      	cmp	r4, #0
700004aa:	d1ea      	bne.n	70000482 <imx327_check+0x2a>
700004ac:	f8bd 6006 	ldrh.w	r6, [sp, #6]
700004b0:	682b      	ldr	r3, [r5, #0]
700004b2:	ea46 2608 	orr.w	r6, r6, r8, lsl #8
700004b6:	4907      	ldr	r1, [pc, #28]	; (700004d4 <imx327_check+0x7c>)
700004b8:	681b      	ldr	r3, [r3, #0]
700004ba:	4632      	mov	r2, r6
700004bc:	4806      	ldr	r0, [pc, #24]	; (700004d8 <imx327_check+0x80>)
700004be:	4798      	blx	r3
700004c0:	f24b 2301 	movw	r3, #45569	; 0xb201
700004c4:	429e      	cmp	r6, r3
700004c6:	bf18      	it	ne
700004c8:	f06f 0415 	mvnne.w	r4, #21
700004cc:	e7d9      	b.n	70000482 <imx327_check+0x2a>
700004ce:	bf00      	nop
700004d0:	70000048 	.word	0x70000048
700004d4:	7000083c 	.word	0x7000083c
700004d8:	70000855 	.word	0x70000855

700004dc <imx327_get_exposure_range>:
700004dc:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
700004e0:	f8dd 8020 	ldr.w	r8, [sp, #32]
700004e4:	4617      	mov	r7, r2
700004e6:	461e      	mov	r6, r3
700004e8:	4605      	mov	r5, r0
700004ea:	2800      	cmp	r0, #0
700004ec:	d145      	bne.n	7000057a <imx327_get_exposure_range+0x9e>
700004ee:	4b24      	ldr	r3, [pc, #144]	; (70000580 <imx327_get_exposure_range+0xa4>)
700004f0:	781c      	ldrb	r4, [r3, #0]
700004f2:	f8d3 9004 	ldr.w	r9, [r3, #4]
700004f6:	b964      	cbnz	r4, 70000512 <imx327_get_exposure_range+0x36>
700004f8:	1f08      	subs	r0, r1, #4
700004fa:	f8c6 9000 	str.w	r9, [r6]
700004fe:	f002 fa5f 	bl	700029c0 <__aeabi_ui2f>
70000502:	4649      	mov	r1, r9
70000504:	f002 fab4 	bl	70002a70 <__aeabi_fmul>
70000508:	f8c8 0000 	str.w	r0, [r8]
7000050c:	4620      	mov	r0, r4
7000050e:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
70000512:	f101 4100 	add.w	r1, r1, #2147483648	; 0x80000000
70000516:	3904      	subs	r1, #4
70000518:	004c      	lsls	r4, r1, #1
7000051a:	4620      	mov	r0, r4
7000051c:	f6a4 04ba 	subw	r4, r4, #2234	; 0x8ba
70000520:	f002 fa4e 	bl	700029c0 <__aeabi_ui2f>
70000524:	4682      	mov	sl, r0
70000526:	f04f 517e 	mov.w	r1, #1065353216	; 0x3f800000
7000052a:	6838      	ldr	r0, [r7, #0]
7000052c:	f002 f998 	bl	70002860 <__addsf3>
70000530:	4601      	mov	r1, r0
70000532:	4650      	mov	r0, sl
70000534:	f002 fb50 	bl	70002bd8 <__aeabi_fdiv>
70000538:	f002 fc76 	bl	70002e28 <__aeabi_f2uiz>
7000053c:	f240 1337 	movw	r3, #311	; 0x137
70000540:	429c      	cmp	r4, r3
70000542:	bf28      	it	cs
70000544:	461c      	movcs	r4, r3
70000546:	42a0      	cmp	r0, r4
70000548:	bf28      	it	cs
7000054a:	4620      	movcs	r0, r4
7000054c:	f002 fa38 	bl	700029c0 <__aeabi_ui2f>
70000550:	4649      	mov	r1, r9
70000552:	f002 fa8d 	bl	70002a70 <__aeabi_fmul>
70000556:	f8c8 0004 	str.w	r0, [r8, #4]
7000055a:	f8c6 9004 	str.w	r9, [r6, #4]
7000055e:	6839      	ldr	r1, [r7, #0]
70000560:	f8d8 0004 	ldr.w	r0, [r8, #4]
70000564:	f002 fa84 	bl	70002a70 <__aeabi_fmul>
70000568:	f8c8 0000 	str.w	r0, [r8]
7000056c:	6839      	ldr	r1, [r7, #0]
7000056e:	6870      	ldr	r0, [r6, #4]
70000570:	f002 fa7e 	bl	70002a70 <__aeabi_fmul>
70000574:	6030      	str	r0, [r6, #0]
70000576:	4628      	mov	r0, r5
70000578:	e7c9      	b.n	7000050e <imx327_get_exposure_range+0x32>
7000057a:	f06f 0015 	mvn.w	r0, #21
7000057e:	e7c6      	b.n	7000050e <imx327_get_exposure_range+0x32>
70000580:	7000004c 	.word	0x7000004c
70000584:	00000000 	.word	0x00000000

70000588 <get_sensor_gain_reg>:
70000588:	b510      	push	{r4, lr}
7000058a:	4604      	mov	r4, r0
7000058c:	f000 f9ba 	bl	70000904 <log10f>
70000590:	f04f 4183 	mov.w	r1, #1098907648	; 0x41800000
70000594:	4620      	mov	r0, r4
70000596:	f002 fc1d 	bl	70002dd4 <__aeabi_fcmpge>
7000059a:	b968      	cbnz	r0, 700005b8 <get_sensor_gain_reg+0x30>
7000059c:	4620      	mov	r0, r4
7000059e:	f000 f9b1 	bl	70000904 <log10f>
700005a2:	f001 fddf 	bl	70002164 <__aeabi_f2d>
700005a6:	a306      	add	r3, pc, #24	; (adr r3, 700005c0 <get_sensor_gain_reg+0x38>)
700005a8:	e9d3 2300 	ldrd	r2, r3, [r3]
700005ac:	f001 fe32 	bl	70002214 <__aeabi_dmul>
700005b0:	f002 f8e0 	bl	70002774 <__aeabi_d2uiz>
700005b4:	b280      	uxth	r0, r0
700005b6:	bd10      	pop	{r4, pc}
700005b8:	2050      	movs	r0, #80	; 0x50
700005ba:	e7fc      	b.n	700005b6 <get_sensor_gain_reg+0x2e>
700005bc:	f3af 8000 	nop.w
700005c0:	05bc01a3 	.word	0x05bc01a3
700005c4:	40509c12 	.word	0x40509c12

700005c8 <imx327_get_exposure_gain_info>:
700005c8:	e92d 4ff8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr}
700005cc:	460f      	mov	r7, r1
700005ce:	4614      	mov	r4, r2
700005d0:	2800      	cmp	r0, #0
700005d2:	f040 80e3 	bne.w	7000079c <imx327_get_exposure_gain_info+0x1d4>
700005d6:	2900      	cmp	r1, #0
700005d8:	f000 80e0 	beq.w	7000079c <imx327_get_exposure_gain_info+0x1d4>
700005dc:	2a00      	cmp	r2, #0
700005de:	f000 80dd 	beq.w	7000079c <imx327_get_exposure_gain_info+0x1d4>
700005e2:	4a70      	ldr	r2, [pc, #448]	; (700007a4 <imx327_get_exposure_gain_info+0x1dc>)
700005e4:	f892 8000 	ldrb.w	r8, [r2]
700005e8:	f1b8 0f00 	cmp.w	r8, #0
700005ec:	d136      	bne.n	7000065c <imx327_get_exposure_gain_info+0x94>
700005ee:	698b      	ldr	r3, [r1, #24]
700005f0:	6838      	ldr	r0, [r7, #0]
700005f2:	f1a3 0914 	sub.w	r9, r3, #20
700005f6:	6851      	ldr	r1, [r2, #4]
700005f8:	f002 faee 	bl	70002bd8 <__aeabi_fdiv>
700005fc:	fa1f f689 	uxth.w	r6, r9
70000600:	f002 fc12 	bl	70002e28 <__aeabi_f2uiz>
70000604:	6939      	ldr	r1, [r7, #16]
70000606:	1e75      	subs	r5, r6, #1
70000608:	b2f6      	uxtb	r6, r6
7000060a:	1a2d      	subs	r5, r5, r0
7000060c:	68b8      	ldr	r0, [r7, #8]
7000060e:	f002 fa2f 	bl	70002a70 <__aeabi_fmul>
70000612:	f7ff ffb9 	bl	70000588 <get_sensor_gain_reg>
70000616:	f243 0318 	movw	r3, #12312	; 0x3018
7000061a:	b2ad      	uxth	r5, r5
7000061c:	81e6      	strh	r6, [r4, #14]
7000061e:	81a3      	strh	r3, [r4, #12]
70000620:	f243 0319 	movw	r3, #12313	; 0x3019
70000624:	b2c0      	uxtb	r0, r0
70000626:	8423      	strh	r3, [r4, #32]
70000628:	ea4f 2319 	mov.w	r3, r9, lsr #8
7000062c:	f8a4 005e 	strh.w	r0, [r4, #94]	; 0x5e
70000630:	8463      	strh	r3, [r4, #34]	; 0x22
70000632:	f243 0320 	movw	r3, #12320	; 0x3020
70000636:	86a3      	strh	r3, [r4, #52]	; 0x34
70000638:	b2eb      	uxtb	r3, r5
7000063a:	0a2d      	lsrs	r5, r5, #8
7000063c:	86e3      	strh	r3, [r4, #54]	; 0x36
7000063e:	f243 0321 	movw	r3, #12321	; 0x3021
70000642:	f8a4 504a 	strh.w	r5, [r4, #74]	; 0x4a
70000646:	f8a4 3048 	strh.w	r3, [r4, #72]	; 0x48
7000064a:	f243 0314 	movw	r3, #12308	; 0x3014
7000064e:	f8a4 305c 	strh.w	r3, [r4, #92]	; 0x5c
70000652:	2305      	movs	r3, #5
70000654:	2000      	movs	r0, #0
70000656:	6023      	str	r3, [r4, #0]
70000658:	e8bd 8ff8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc}
7000065c:	f1b8 0f01 	cmp.w	r8, #1
70000660:	d1fa      	bne.n	70000658 <imx327_get_exposure_gain_info+0x90>
70000662:	6856      	ldr	r6, [r2, #4]
70000664:	6838      	ldr	r0, [r7, #0]
70000666:	4631      	mov	r1, r6
70000668:	f002 fab6 	bl	70002bd8 <__aeabi_fdiv>
7000066c:	f002 fbdc 	bl	70002e28 <__aeabi_f2uiz>
70000670:	4631      	mov	r1, r6
70000672:	fa1f f980 	uxth.w	r9, r0
70000676:	6878      	ldr	r0, [r7, #4]
70000678:	f002 faae 	bl	70002bd8 <__aeabi_fdiv>
7000067c:	f002 fbd4 	bl	70002e28 <__aeabi_f2uiz>
70000680:	f8d7 a018 	ldr.w	sl, [r7, #24]
70000684:	b281      	uxth	r1, r0
70000686:	f000 0001 	and.w	r0, r0, #1
7000068a:	ea4f 024a 	mov.w	r2, sl, lsl #1
7000068e:	1c86      	adds	r6, r0, #2
70000690:	1c4b      	adds	r3, r1, #1
70000692:	1e55      	subs	r5, r2, #1
70000694:	68b8      	ldr	r0, [r7, #8]
70000696:	4433      	add	r3, r6
70000698:	eba5 0509 	sub.w	r5, r5, r9
7000069c:	fa1f f883 	uxth.w	r8, r3
700006a0:	b2ad      	uxth	r5, r5
700006a2:	f1b8 0f10 	cmp.w	r8, #16
700006a6:	bf9c      	itt	ls
700006a8:	f04f 0811 	movls.w	r8, #17
700006ac:	f1c1 0110 	rsbls	r1, r1, #16
700006b0:	f108 0301 	add.w	r3, r8, #1
700006b4:	bf98      	it	ls
700006b6:	b28e      	uxthls	r6, r1
700006b8:	6939      	ldr	r1, [r7, #16]
700006ba:	f108 39ff 	add.w	r9, r8, #4294967295
700006be:	42ab      	cmp	r3, r5
700006c0:	f029 0901 	bic.w	r9, r9, #1
700006c4:	bfa8      	it	ge
700006c6:	f108 0502 	addge.w	r5, r8, #2
700006ca:	f609 09aa 	addw	r9, r9, #2218	; 0x8aa
700006ce:	bfa8      	it	ge
700006d0:	b2ad      	uxthge	r5, r5
700006d2:	f002 f9cd 	bl	70002a70 <__aeabi_fmul>
700006d6:	f7ff ff57 	bl	70000588 <get_sensor_gain_reg>
700006da:	6979      	ldr	r1, [r7, #20]
700006dc:	4683      	mov	fp, r0
700006de:	68f8      	ldr	r0, [r7, #12]
700006e0:	f002 f9c6 	bl	70002a70 <__aeabi_fmul>
700006e4:	f7ff ff50 	bl	70000588 <get_sensor_gain_reg>
700006e8:	f243 0314 	movw	r3, #12308	; 0x3014
700006ec:	fa1f f989 	uxth.w	r9, r9
700006f0:	81a3      	strh	r3, [r4, #12]
700006f2:	f243 03f2 	movw	r3, #12530	; 0x30f2
700006f6:	fa5f fb8b 	uxtb.w	fp, fp
700006fa:	8423      	strh	r3, [r4, #32]
700006fc:	f243 0320 	movw	r3, #12320	; 0x3020
70000700:	b2c0      	uxtb	r0, r0
70000702:	f8a4 b00e 	strh.w	fp, [r4, #14]
70000706:	86a3      	strh	r3, [r4, #52]	; 0x34
70000708:	b2f3      	uxtb	r3, r6
7000070a:	0a36      	lsrs	r6, r6, #8
7000070c:	8460      	strh	r0, [r4, #34]	; 0x22
7000070e:	86e3      	strh	r3, [r4, #54]	; 0x36
70000710:	f243 0321 	movw	r3, #12321	; 0x3021
70000714:	f8a4 604a 	strh.w	r6, [r4, #74]	; 0x4a
70000718:	f8a4 3048 	strh.w	r3, [r4, #72]	; 0x48
7000071c:	f243 0324 	movw	r3, #12324	; 0x3024
70000720:	f8a4 305c 	strh.w	r3, [r4, #92]	; 0x5c
70000724:	b2eb      	uxtb	r3, r5
70000726:	0a2d      	lsrs	r5, r5, #8
70000728:	f8a4 305e 	strh.w	r3, [r4, #94]	; 0x5e
7000072c:	f243 0325 	movw	r3, #12325	; 0x3025
70000730:	f8a4 5072 	strh.w	r5, [r4, #114]	; 0x72
70000734:	f8a4 3070 	strh.w	r3, [r4, #112]	; 0x70
70000738:	f243 0330 	movw	r3, #12336	; 0x3030
7000073c:	f8a4 3084 	strh.w	r3, [r4, #132]	; 0x84
70000740:	fa5f f388 	uxtb.w	r3, r8
70000744:	f8a4 3086 	strh.w	r3, [r4, #134]	; 0x86
70000748:	f243 0331 	movw	r3, #12337	; 0x3031
7000074c:	f8a4 3098 	strh.w	r3, [r4, #152]	; 0x98
70000750:	ea4f 2318 	mov.w	r3, r8, lsr #8
70000754:	f8a4 309a 	strh.w	r3, [r4, #154]	; 0x9a
70000758:	f243 4318 	movw	r3, #13336	; 0x3418
7000075c:	f8a4 30ac 	strh.w	r3, [r4, #172]	; 0xac
70000760:	fa5f f389 	uxtb.w	r3, r9
70000764:	ea4f 2919 	mov.w	r9, r9, lsr #8
70000768:	f8a4 30ae 	strh.w	r3, [r4, #174]	; 0xae
7000076c:	f243 4319 	movw	r3, #13337	; 0x3419
70000770:	f8a4 90c2 	strh.w	r9, [r4, #194]	; 0xc2
70000774:	f8a4 30c0 	strh.w	r3, [r4, #192]	; 0xc0
70000778:	f243 0318 	movw	r3, #12312	; 0x3018
7000077c:	f8a4 30d4 	strh.w	r3, [r4, #212]	; 0xd4
70000780:	fa5f f38a 	uxtb.w	r3, sl
70000784:	ea4f 2a1a 	mov.w	sl, sl, lsr #8
70000788:	f8a4 30d6 	strh.w	r3, [r4, #214]	; 0xd6
7000078c:	f243 0319 	movw	r3, #12313	; 0x3019
70000790:	f8a4 a0ea 	strh.w	sl, [r4, #234]	; 0xea
70000794:	f8a4 30e8 	strh.w	r3, [r4, #232]	; 0xe8
70000798:	230c      	movs	r3, #12
7000079a:	e75b      	b.n	70000654 <imx327_get_exposure_gain_info+0x8c>
7000079c:	f06f 0015 	mvn.w	r0, #21
700007a0:	e75a      	b.n	70000658 <imx327_get_exposure_gain_info+0x90>
700007a2:	bf00      	nop
700007a4:	7000004c 	.word	0x7000004c

700007a8 <imx327_get_tuned_again>:
700007a8:	b538      	push	{r3, r4, r5, lr}
700007aa:	460d      	mov	r5, r1
700007ac:	4604      	mov	r4, r0
700007ae:	bb60      	cbnz	r0, 7000080a <imx327_get_tuned_again+0x62>
700007b0:	b359      	cbz	r1, 7000080a <imx327_get_tuned_again+0x62>
700007b2:	6808      	ldr	r0, [r1, #0]
700007b4:	f7ff fee8 	bl	70000588 <get_sensor_gain_reg>
700007b8:	f001 fcb2 	bl	70002120 <__aeabi_ui2d>
700007bc:	a314      	add	r3, pc, #80	; (adr r3, 70000810 <imx327_get_tuned_again+0x68>)
700007be:	e9d3 2300 	ldrd	r2, r3, [r3]
700007c2:	f001 fe51 	bl	70002468 <__aeabi_ddiv>
700007c6:	460b      	mov	r3, r1
700007c8:	4602      	mov	r2, r0
700007ca:	4913      	ldr	r1, [pc, #76]	; (70000818 <imx327_get_tuned_again+0x70>)
700007cc:	2000      	movs	r0, #0
700007ce:	f000 f8c1 	bl	70000954 <pow>
700007d2:	f001 ffef 	bl	700027b4 <__aeabi_d2f>
700007d6:	4b11      	ldr	r3, [pc, #68]	; (7000081c <imx327_get_tuned_again+0x74>)
700007d8:	6028      	str	r0, [r5, #0]
700007da:	781b      	ldrb	r3, [r3, #0]
700007dc:	2b01      	cmp	r3, #1
700007de:	d112      	bne.n	70000806 <imx327_get_tuned_again+0x5e>
700007e0:	6868      	ldr	r0, [r5, #4]
700007e2:	f7ff fed1 	bl	70000588 <get_sensor_gain_reg>
700007e6:	f001 fc9b 	bl	70002120 <__aeabi_ui2d>
700007ea:	a309      	add	r3, pc, #36	; (adr r3, 70000810 <imx327_get_tuned_again+0x68>)
700007ec:	e9d3 2300 	ldrd	r2, r3, [r3]
700007f0:	f001 fe3a 	bl	70002468 <__aeabi_ddiv>
700007f4:	4602      	mov	r2, r0
700007f6:	460b      	mov	r3, r1
700007f8:	2000      	movs	r0, #0
700007fa:	4907      	ldr	r1, [pc, #28]	; (70000818 <imx327_get_tuned_again+0x70>)
700007fc:	f000 f8aa 	bl	70000954 <pow>
70000800:	f001 ffd8 	bl	700027b4 <__aeabi_d2f>
70000804:	6068      	str	r0, [r5, #4]
70000806:	4620      	mov	r0, r4
70000808:	e001      	b.n	7000080e <imx327_get_tuned_again+0x66>
7000080a:	f06f 0015 	mvn.w	r0, #21
7000080e:	bd38      	pop	{r3, r4, r5, pc}
70000810:	05bc01a3 	.word	0x05bc01a3
70000814:	40509c12 	.word	0x40509c12
70000818:	40240000 	.word	0x40240000
7000081c:	7000004c 	.word	0x7000004c

70000820 <clip_d_word>:
70000820:	4603      	mov	r3, r0
70000822:	4610      	mov	r0, r2
70000824:	4293      	cmp	r3, r2
70000826:	d803      	bhi.n	70000830 <clip_d_word+0x10>
70000828:	428b      	cmp	r3, r1
7000082a:	bf38      	it	cc
7000082c:	460b      	movcc	r3, r1
7000082e:	4618      	mov	r0, r3
70000830:	4770      	bx	lr
	...

70000834 <rts_isp_get_sensor_ops>:
70000834:	4800      	ldr	r0, [pc, #0]	; (70000838 <rts_isp_get_sensor_ops+0x4>)
70000836:	4770      	bx	lr
70000838:	70000870 	.word	0x70000870
7000083c:	206e6f4d 	.word	0x206e6f4d
70000840:	206e754a 	.word	0x206e754a
70000844:	31203531 	.word	0x31203531
70000848:	34303a31 	.word	0x34303a31
7000084c:	2030333a 	.word	0x2030333a
70000850:	36323032 	.word	0x36323032
70000854:	615a5b00 	.word	0x615a5b00
70000858:	205d6f6b 	.word	0x205d6f6b
7000085c:	74736554 	.word	0x74736554
70000860:	5f574620 	.word	0x5f574620
70000864:	305f7325 	.word	0x305f7325
70000868:	0a782578 	.word	0x0a782578
7000086c:	00000000 	.word	0x00000000

70000870 <imx327_ops>:
70000870:	73000005 33786d69 00003732 00000000     ...simx327......
	...
70000894:	70000259 70000315 700004dd 700007a9     Y..p...p...p...p
700008a4:	70000411 700005c9 00000000 00000000     ...p...p........
700008b4:	700003fd 00000000 00000000 00000000     ...p............
700008c4:	70000431 00000000 00000000 00000000     1..p............
700008d4:	70000459 00000000 00000000 00000000     Y..p............
	...

70000904 <log10f>:
70000904:	b538      	push	{r3, r4, r5, lr}
70000906:	4604      	mov	r4, r0
70000908:	f000 f88c 	bl	70000a24 <__ieee754_log10f>
7000090c:	4605      	mov	r5, r0
7000090e:	4621      	mov	r1, r4
70000910:	4620      	mov	r0, r4
70000912:	f002 fa73 	bl	70002dfc <__aeabi_fcmpun>
70000916:	b970      	cbnz	r0, 70000936 <log10f+0x32>
70000918:	2100      	movs	r1, #0
7000091a:	4620      	mov	r0, r4
7000091c:	f002 fa50 	bl	70002dc0 <__aeabi_fcmple>
70000920:	b148      	cbz	r0, 70000936 <log10f+0x32>
70000922:	2100      	movs	r1, #0
70000924:	4620      	mov	r0, r4
70000926:	f002 fa37 	bl	70002d98 <__aeabi_fcmpeq>
7000092a:	b130      	cbz	r0, 7000093a <log10f+0x36>
7000092c:	f001 f8d2 	bl	70001ad4 <__errno>
70000930:	4d06      	ldr	r5, [pc, #24]	; (7000094c <log10f+0x48>)
70000932:	2322      	movs	r3, #34	; 0x22
70000934:	6003      	str	r3, [r0, #0]
70000936:	4628      	mov	r0, r5
70000938:	bd38      	pop	{r3, r4, r5, pc}
7000093a:	f001 f8cb 	bl	70001ad4 <__errno>
7000093e:	2321      	movs	r3, #33	; 0x21
70000940:	6003      	str	r3, [r0, #0]
70000942:	4803      	ldr	r0, [pc, #12]	; (70000950 <log10f+0x4c>)
70000944:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
70000948:	f001 b842 	b.w	700019d0 <nanf>
7000094c:	ff800000 	.word	0xff800000
70000950:	700032d0 	.word	0x700032d0

70000954 <pow>:
70000954:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
70000958:	4614      	mov	r4, r2
7000095a:	461d      	mov	r5, r3
7000095c:	4680      	mov	r8, r0
7000095e:	4689      	mov	r9, r1
70000960:	f000 f9d6 	bl	70000d10 <__ieee754_pow>
70000964:	4622      	mov	r2, r4
70000966:	4606      	mov	r6, r0
70000968:	460f      	mov	r7, r1
7000096a:	462b      	mov	r3, r5
7000096c:	4620      	mov	r0, r4
7000096e:	4629      	mov	r1, r5
70000970:	f001 feea 	bl	70002748 <__aeabi_dcmpun>
70000974:	bbc8      	cbnz	r0, 700009ea <pow+0x96>
70000976:	2200      	movs	r2, #0
70000978:	2300      	movs	r3, #0
7000097a:	4640      	mov	r0, r8
7000097c:	4649      	mov	r1, r9
7000097e:	f001 feb1 	bl	700026e4 <__aeabi_dcmpeq>
70000982:	b1b8      	cbz	r0, 700009b4 <pow+0x60>
70000984:	2200      	movs	r2, #0
70000986:	2300      	movs	r3, #0
70000988:	4620      	mov	r0, r4
7000098a:	4629      	mov	r1, r5
7000098c:	f001 feaa 	bl	700026e4 <__aeabi_dcmpeq>
70000990:	2800      	cmp	r0, #0
70000992:	d141      	bne.n	70000a18 <pow+0xc4>
70000994:	4620      	mov	r0, r4
70000996:	4629      	mov	r1, r5
70000998:	f001 f813 	bl	700019c2 <finite>
7000099c:	b328      	cbz	r0, 700009ea <pow+0x96>
7000099e:	2200      	movs	r2, #0
700009a0:	2300      	movs	r3, #0
700009a2:	4620      	mov	r0, r4
700009a4:	4629      	mov	r1, r5
700009a6:	f001 fea7 	bl	700026f8 <__aeabi_dcmplt>
700009aa:	b1f0      	cbz	r0, 700009ea <pow+0x96>
700009ac:	f001 f892 	bl	70001ad4 <__errno>
700009b0:	2322      	movs	r3, #34	; 0x22
700009b2:	e019      	b.n	700009e8 <pow+0x94>
700009b4:	4630      	mov	r0, r6
700009b6:	4639      	mov	r1, r7
700009b8:	f001 f803 	bl	700019c2 <finite>
700009bc:	b9c8      	cbnz	r0, 700009f2 <pow+0x9e>
700009be:	4640      	mov	r0, r8
700009c0:	4649      	mov	r1, r9
700009c2:	f000 fffe 	bl	700019c2 <finite>
700009c6:	b1a0      	cbz	r0, 700009f2 <pow+0x9e>
700009c8:	4620      	mov	r0, r4
700009ca:	4629      	mov	r1, r5
700009cc:	f000 fff9 	bl	700019c2 <finite>
700009d0:	b178      	cbz	r0, 700009f2 <pow+0x9e>
700009d2:	4632      	mov	r2, r6
700009d4:	463b      	mov	r3, r7
700009d6:	4630      	mov	r0, r6
700009d8:	4639      	mov	r1, r7
700009da:	f001 feb5 	bl	70002748 <__aeabi_dcmpun>
700009de:	2800      	cmp	r0, #0
700009e0:	d0e4      	beq.n	700009ac <pow+0x58>
700009e2:	f001 f877 	bl	70001ad4 <__errno>
700009e6:	2321      	movs	r3, #33	; 0x21
700009e8:	6003      	str	r3, [r0, #0]
700009ea:	4630      	mov	r0, r6
700009ec:	4639      	mov	r1, r7
700009ee:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
700009f2:	2200      	movs	r2, #0
700009f4:	2300      	movs	r3, #0
700009f6:	4630      	mov	r0, r6
700009f8:	4639      	mov	r1, r7
700009fa:	f001 fe73 	bl	700026e4 <__aeabi_dcmpeq>
700009fe:	2800      	cmp	r0, #0
70000a00:	d0f3      	beq.n	700009ea <pow+0x96>
70000a02:	4640      	mov	r0, r8
70000a04:	4649      	mov	r1, r9
70000a06:	f000 ffdc 	bl	700019c2 <finite>
70000a0a:	2800      	cmp	r0, #0
70000a0c:	d0ed      	beq.n	700009ea <pow+0x96>
70000a0e:	4620      	mov	r0, r4
70000a10:	4629      	mov	r1, r5
70000a12:	f000 ffd6 	bl	700019c2 <finite>
70000a16:	e7c8      	b.n	700009aa <pow+0x56>
70000a18:	2600      	movs	r6, #0
70000a1a:	4f01      	ldr	r7, [pc, #4]	; (70000a20 <pow+0xcc>)
70000a1c:	e7e5      	b.n	700009ea <pow+0x96>
70000a1e:	bf00      	nop
70000a20:	3ff00000 	.word	0x3ff00000

70000a24 <__ieee754_log10f>:
70000a24:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70000a28:	4601      	mov	r1, r0
70000a2a:	4603      	mov	r3, r0
70000a2c:	b570      	push	{r4, r5, r6, lr}
70000a2e:	d105      	bne.n	70000a3c <__ieee754_log10f+0x18>
70000a30:	2100      	movs	r1, #0
70000a32:	f04f 404c 	mov.w	r0, #3422552064	; 0xcc000000
70000a36:	f002 f8cf 	bl	70002bd8 <__aeabi_fdiv>
70000a3a:	bd70      	pop	{r4, r5, r6, pc}
70000a3c:	2800      	cmp	r0, #0
70000a3e:	da03      	bge.n	70000a48 <__ieee754_log10f+0x24>
70000a40:	f001 ff0c 	bl	7000285c <__aeabi_fsub>
70000a44:	2100      	movs	r1, #0
70000a46:	e7f6      	b.n	70000a36 <__ieee754_log10f+0x12>
70000a48:	f1b0 4fff 	cmp.w	r0, #2139095040	; 0x7f800000
70000a4c:	db02      	blt.n	70000a54 <__ieee754_log10f+0x30>
70000a4e:	f001 ff07 	bl	70002860 <__addsf3>
70000a52:	e7f2      	b.n	70000a3a <__ieee754_log10f+0x16>
70000a54:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70000a58:	da2d      	bge.n	70000ab6 <__ieee754_log10f+0x92>
70000a5a:	f04f 4198 	mov.w	r1, #1275068416	; 0x4c000000
70000a5e:	f002 f807 	bl	70002a70 <__aeabi_fmul>
70000a62:	f06f 0218 	mvn.w	r2, #24
70000a66:	4603      	mov	r3, r0
70000a68:	15d8      	asrs	r0, r3, #23
70000a6a:	f3c3 0416 	ubfx	r4, r3, #0, #23
70000a6e:	387f      	subs	r0, #127	; 0x7f
70000a70:	4410      	add	r0, r2
70000a72:	0fc6      	lsrs	r6, r0, #31
70000a74:	eb00 70d0 	add.w	r0, r0, r0, lsr #31
70000a78:	f001 ffa6 	bl	700029c8 <__aeabi_i2f>
70000a7c:	4605      	mov	r5, r0
70000a7e:	f1c6 007f 	rsb	r0, r6, #127	; 0x7f
70000a82:	ea44 50c0 	orr.w	r0, r4, r0, lsl #23
70000a86:	f000 f81f 	bl	70000ac8 <__ieee754_logf>
70000a8a:	490c      	ldr	r1, [pc, #48]	; (70000abc <__ieee754_log10f+0x98>)
70000a8c:	4606      	mov	r6, r0
70000a8e:	4628      	mov	r0, r5
70000a90:	f001 ffee 	bl	70002a70 <__aeabi_fmul>
70000a94:	4604      	mov	r4, r0
70000a96:	490a      	ldr	r1, [pc, #40]	; (70000ac0 <__ieee754_log10f+0x9c>)
70000a98:	4630      	mov	r0, r6
70000a9a:	f001 ffe9 	bl	70002a70 <__aeabi_fmul>
70000a9e:	4601      	mov	r1, r0
70000aa0:	4620      	mov	r0, r4
70000aa2:	f001 fedd 	bl	70002860 <__addsf3>
70000aa6:	4604      	mov	r4, r0
70000aa8:	4906      	ldr	r1, [pc, #24]	; (70000ac4 <__ieee754_log10f+0xa0>)
70000aaa:	4628      	mov	r0, r5
70000aac:	f001 ffe0 	bl	70002a70 <__aeabi_fmul>
70000ab0:	4601      	mov	r1, r0
70000ab2:	4620      	mov	r0, r4
70000ab4:	e7cb      	b.n	70000a4e <__ieee754_log10f+0x2a>
70000ab6:	2200      	movs	r2, #0
70000ab8:	e7d6      	b.n	70000a68 <__ieee754_log10f+0x44>
70000aba:	bf00      	nop
70000abc:	355427db 	.word	0x355427db
70000ac0:	3ede5bd9 	.word	0x3ede5bd9
70000ac4:	3e9a2080 	.word	0x3e9a2080

70000ac8 <__ieee754_logf>:
70000ac8:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70000acc:	4601      	mov	r1, r0
70000ace:	e92d 4ff8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, lr}
70000ad2:	4603      	mov	r3, r0
70000ad4:	d106      	bne.n	70000ae4 <__ieee754_logf+0x1c>
70000ad6:	2100      	movs	r1, #0
70000ad8:	f04f 404c 	mov.w	r0, #3422552064	; 0xcc000000
70000adc:	f002 f87c 	bl	70002bd8 <__aeabi_fdiv>
70000ae0:	e8bd 8ff8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, sl, fp, pc}
70000ae4:	2800      	cmp	r0, #0
70000ae6:	da03      	bge.n	70000af0 <__ieee754_logf+0x28>
70000ae8:	f001 feb8 	bl	7000285c <__aeabi_fsub>
70000aec:	2100      	movs	r1, #0
70000aee:	e7f5      	b.n	70000adc <__ieee754_logf+0x14>
70000af0:	f1b0 4fff 	cmp.w	r0, #2139095040	; 0x7f800000
70000af4:	db02      	blt.n	70000afc <__ieee754_logf+0x34>
70000af6:	f001 feb3 	bl	70002860 <__addsf3>
70000afa:	e7f1      	b.n	70000ae0 <__ieee754_logf+0x18>
70000afc:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70000b00:	da35      	bge.n	70000b6e <__ieee754_logf+0xa6>
70000b02:	f04f 4198 	mov.w	r1, #1275068416	; 0x4c000000
70000b06:	f001 ffb3 	bl	70002a70 <__aeabi_fmul>
70000b0a:	f06f 0218 	mvn.w	r2, #24
70000b0e:	4603      	mov	r3, r0
70000b10:	f3c3 0416 	ubfx	r4, r3, #0, #23
70000b14:	15de      	asrs	r6, r3, #23
70000b16:	4b71      	ldr	r3, [pc, #452]	; (70000cdc <__ieee754_logf+0x214>)
70000b18:	f04f 517e 	mov.w	r1, #1065353216	; 0x3f800000
70000b1c:	3e7f      	subs	r6, #127	; 0x7f
70000b1e:	4423      	add	r3, r4
70000b20:	4416      	add	r6, r2
70000b22:	f403 0000 	and.w	r0, r3, #8388608	; 0x800000
70000b26:	eb06 56d3 	add.w	r6, r6, r3, lsr #23
70000b2a:	f080 507e 	eor.w	r0, r0, #1065353216	; 0x3f800000
70000b2e:	4320      	orrs	r0, r4
70000b30:	f001 fe94 	bl	7000285c <__aeabi_fsub>
70000b34:	f104 020f 	add.w	r2, r4, #15
70000b38:	4b69      	ldr	r3, [pc, #420]	; (70000ce0 <__ieee754_logf+0x218>)
70000b3a:	4605      	mov	r5, r0
70000b3c:	4013      	ands	r3, r2
70000b3e:	2b00      	cmp	r3, #0
70000b40:	d13a      	bne.n	70000bb8 <__ieee754_logf+0xf0>
70000b42:	2100      	movs	r1, #0
70000b44:	f002 f928 	bl	70002d98 <__aeabi_fcmpeq>
70000b48:	b198      	cbz	r0, 70000b72 <__ieee754_logf+0xaa>
70000b4a:	2e00      	cmp	r6, #0
70000b4c:	f000 80c4 	beq.w	70000cd8 <__ieee754_logf+0x210>
70000b50:	4630      	mov	r0, r6
70000b52:	f001 ff39 	bl	700029c8 <__aeabi_i2f>
70000b56:	4963      	ldr	r1, [pc, #396]	; (70000ce4 <__ieee754_logf+0x21c>)
70000b58:	4605      	mov	r5, r0
70000b5a:	f001 ff89 	bl	70002a70 <__aeabi_fmul>
70000b5e:	4604      	mov	r4, r0
70000b60:	4961      	ldr	r1, [pc, #388]	; (70000ce8 <__ieee754_logf+0x220>)
70000b62:	4628      	mov	r0, r5
70000b64:	f001 ff84 	bl	70002a70 <__aeabi_fmul>
70000b68:	4601      	mov	r1, r0
70000b6a:	4620      	mov	r0, r4
70000b6c:	e7c3      	b.n	70000af6 <__ieee754_logf+0x2e>
70000b6e:	2200      	movs	r2, #0
70000b70:	e7ce      	b.n	70000b10 <__ieee754_logf+0x48>
70000b72:	495e      	ldr	r1, [pc, #376]	; (70000cec <__ieee754_logf+0x224>)
70000b74:	4628      	mov	r0, r5
70000b76:	f001 ff7b 	bl	70002a70 <__aeabi_fmul>
70000b7a:	4601      	mov	r1, r0
70000b7c:	f04f 507c 	mov.w	r0, #1056964608	; 0x3f000000
70000b80:	f001 fe6c 	bl	7000285c <__aeabi_fsub>
70000b84:	4604      	mov	r4, r0
70000b86:	4629      	mov	r1, r5
70000b88:	4628      	mov	r0, r5
70000b8a:	f001 ff71 	bl	70002a70 <__aeabi_fmul>
70000b8e:	4601      	mov	r1, r0
70000b90:	4620      	mov	r0, r4
70000b92:	f001 ff6d 	bl	70002a70 <__aeabi_fmul>
70000b96:	4604      	mov	r4, r0
70000b98:	b90e      	cbnz	r6, 70000b9e <__ieee754_logf+0xd6>
70000b9a:	4621      	mov	r1, r4
70000b9c:	e06f      	b.n	70000c7e <__ieee754_logf+0x1b6>
70000b9e:	4630      	mov	r0, r6
70000ba0:	f001 ff12 	bl	700029c8 <__aeabi_i2f>
70000ba4:	4607      	mov	r7, r0
70000ba6:	494f      	ldr	r1, [pc, #316]	; (70000ce4 <__ieee754_logf+0x21c>)
70000ba8:	f001 ff62 	bl	70002a70 <__aeabi_fmul>
70000bac:	494e      	ldr	r1, [pc, #312]	; (70000ce8 <__ieee754_logf+0x220>)
70000bae:	4606      	mov	r6, r0
70000bb0:	4638      	mov	r0, r7
70000bb2:	f001 ff5d 	bl	70002a70 <__aeabi_fmul>
70000bb6:	e072      	b.n	70000c9e <__ieee754_logf+0x1d6>
70000bb8:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
70000bbc:	f8df a130 	ldr.w	sl, [pc, #304]	; 70000cf0 <__ieee754_logf+0x228>
70000bc0:	f001 fe4e 	bl	70002860 <__addsf3>
70000bc4:	4601      	mov	r1, r0
70000bc6:	4628      	mov	r0, r5
70000bc8:	44a2      	add	sl, r4
70000bca:	f002 f805 	bl	70002bd8 <__aeabi_fdiv>
70000bce:	4681      	mov	r9, r0
70000bd0:	4630      	mov	r0, r6
70000bd2:	f001 fef9 	bl	700029c8 <__aeabi_i2f>
70000bd6:	4649      	mov	r1, r9
70000bd8:	4680      	mov	r8, r0
70000bda:	4648      	mov	r0, r9
70000bdc:	f001 ff48 	bl	70002a70 <__aeabi_fmul>
70000be0:	4601      	mov	r1, r0
70000be2:	4683      	mov	fp, r0
70000be4:	f001 ff44 	bl	70002a70 <__aeabi_fmul>
70000be8:	4942      	ldr	r1, [pc, #264]	; (70000cf4 <__ieee754_logf+0x22c>)
70000bea:	4607      	mov	r7, r0
70000bec:	f001 ff40 	bl	70002a70 <__aeabi_fmul>
70000bf0:	4941      	ldr	r1, [pc, #260]	; (70000cf8 <__ieee754_logf+0x230>)
70000bf2:	f001 fe35 	bl	70002860 <__addsf3>
70000bf6:	4639      	mov	r1, r7
70000bf8:	f001 ff3a 	bl	70002a70 <__aeabi_fmul>
70000bfc:	493f      	ldr	r1, [pc, #252]	; (70000cfc <__ieee754_logf+0x234>)
70000bfe:	f001 fe2f 	bl	70002860 <__addsf3>
70000c02:	4639      	mov	r1, r7
70000c04:	f001 ff34 	bl	70002a70 <__aeabi_fmul>
70000c08:	493d      	ldr	r1, [pc, #244]	; (70000d00 <__ieee754_logf+0x238>)
70000c0a:	f001 fe29 	bl	70002860 <__addsf3>
70000c0e:	4659      	mov	r1, fp
70000c10:	f001 ff2e 	bl	70002a70 <__aeabi_fmul>
70000c14:	493b      	ldr	r1, [pc, #236]	; (70000d04 <__ieee754_logf+0x23c>)
70000c16:	4683      	mov	fp, r0
70000c18:	4638      	mov	r0, r7
70000c1a:	f001 ff29 	bl	70002a70 <__aeabi_fmul>
70000c1e:	493a      	ldr	r1, [pc, #232]	; (70000d08 <__ieee754_logf+0x240>)
70000c20:	f001 fe1e 	bl	70002860 <__addsf3>
70000c24:	4639      	mov	r1, r7
70000c26:	f001 ff23 	bl	70002a70 <__aeabi_fmul>
70000c2a:	4938      	ldr	r1, [pc, #224]	; (70000d0c <__ieee754_logf+0x244>)
70000c2c:	f001 fe18 	bl	70002860 <__addsf3>
70000c30:	4639      	mov	r1, r7
70000c32:	f001 ff1d 	bl	70002a70 <__aeabi_fmul>
70000c36:	4601      	mov	r1, r0
70000c38:	4658      	mov	r0, fp
70000c3a:	f001 fe11 	bl	70002860 <__addsf3>
70000c3e:	f5c4 1357 	rsb	r3, r4, #3522560	; 0x35c000
70000c42:	4607      	mov	r7, r0
70000c44:	f503 7322 	add.w	r3, r3, #648	; 0x288
70000c48:	ea43 030a 	orr.w	r3, r3, sl
70000c4c:	2b00      	cmp	r3, #0
70000c4e:	dd30      	ble.n	70000cb2 <__ieee754_logf+0x1ea>
70000c50:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
70000c54:	4628      	mov	r0, r5
70000c56:	f001 ff0b 	bl	70002a70 <__aeabi_fmul>
70000c5a:	4629      	mov	r1, r5
70000c5c:	f001 ff08 	bl	70002a70 <__aeabi_fmul>
70000c60:	4601      	mov	r1, r0
70000c62:	4604      	mov	r4, r0
70000c64:	4638      	mov	r0, r7
70000c66:	f001 fdfb 	bl	70002860 <__addsf3>
70000c6a:	4649      	mov	r1, r9
70000c6c:	f001 ff00 	bl	70002a70 <__aeabi_fmul>
70000c70:	4607      	mov	r7, r0
70000c72:	b946      	cbnz	r6, 70000c86 <__ieee754_logf+0x1be>
70000c74:	4601      	mov	r1, r0
70000c76:	4620      	mov	r0, r4
70000c78:	f001 fdf0 	bl	7000285c <__aeabi_fsub>
70000c7c:	4601      	mov	r1, r0
70000c7e:	4628      	mov	r0, r5
70000c80:	f001 fdec 	bl	7000285c <__aeabi_fsub>
70000c84:	e72c      	b.n	70000ae0 <__ieee754_logf+0x18>
70000c86:	4917      	ldr	r1, [pc, #92]	; (70000ce4 <__ieee754_logf+0x21c>)
70000c88:	4640      	mov	r0, r8
70000c8a:	f001 fef1 	bl	70002a70 <__aeabi_fmul>
70000c8e:	4916      	ldr	r1, [pc, #88]	; (70000ce8 <__ieee754_logf+0x220>)
70000c90:	4606      	mov	r6, r0
70000c92:	4640      	mov	r0, r8
70000c94:	f001 feec 	bl	70002a70 <__aeabi_fmul>
70000c98:	4639      	mov	r1, r7
70000c9a:	f001 fde1 	bl	70002860 <__addsf3>
70000c9e:	4601      	mov	r1, r0
70000ca0:	4620      	mov	r0, r4
70000ca2:	f001 fddb 	bl	7000285c <__aeabi_fsub>
70000ca6:	4629      	mov	r1, r5
70000ca8:	f001 fdd8 	bl	7000285c <__aeabi_fsub>
70000cac:	4601      	mov	r1, r0
70000cae:	4630      	mov	r0, r6
70000cb0:	e7e6      	b.n	70000c80 <__ieee754_logf+0x1b8>
70000cb2:	4601      	mov	r1, r0
70000cb4:	4628      	mov	r0, r5
70000cb6:	f001 fdd1 	bl	7000285c <__aeabi_fsub>
70000cba:	4649      	mov	r1, r9
70000cbc:	f001 fed8 	bl	70002a70 <__aeabi_fmul>
70000cc0:	4604      	mov	r4, r0
70000cc2:	2e00      	cmp	r6, #0
70000cc4:	f43f af69 	beq.w	70000b9a <__ieee754_logf+0xd2>
70000cc8:	4906      	ldr	r1, [pc, #24]	; (70000ce4 <__ieee754_logf+0x21c>)
70000cca:	4640      	mov	r0, r8
70000ccc:	f001 fed0 	bl	70002a70 <__aeabi_fmul>
70000cd0:	4905      	ldr	r1, [pc, #20]	; (70000ce8 <__ieee754_logf+0x220>)
70000cd2:	4606      	mov	r6, r0
70000cd4:	4640      	mov	r0, r8
70000cd6:	e76c      	b.n	70000bb2 <__ieee754_logf+0xea>
70000cd8:	2000      	movs	r0, #0
70000cda:	e701      	b.n	70000ae0 <__ieee754_logf+0x18>
70000cdc:	004afb20 	.word	0x004afb20
70000ce0:	007ffff0 	.word	0x007ffff0
70000ce4:	3f317180 	.word	0x3f317180
70000ce8:	3717f7d1 	.word	0x3717f7d1
70000cec:	3eaaaaab 	.word	0x3eaaaaab
70000cf0:	ffcf5c30 	.word	0xffcf5c30
70000cf4:	3e178897 	.word	0x3e178897
70000cf8:	3e3a3325 	.word	0x3e3a3325
70000cfc:	3e924925 	.word	0x3e924925
70000d00:	3f2aaaab 	.word	0x3f2aaaab
70000d04:	3e1cd04f 	.word	0x3e1cd04f
70000d08:	3e638e29 	.word	0x3e638e29
70000d0c:	3ecccccd 	.word	0x3ecccccd

70000d10 <__ieee754_pow>:
70000d10:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
70000d14:	b093      	sub	sp, #76	; 0x4c
70000d16:	4689      	mov	r9, r1
70000d18:	4680      	mov	r8, r0
70000d1a:	e9cd 2302 	strd	r2, r3, [sp, #8]
70000d1e:	e9dd 2702 	ldrd	r2, r7, [sp, #8]
70000d22:	f027 4600 	bic.w	r6, r7, #2147483648	; 0x80000000
70000d26:	ea56 0102 	orrs.w	r1, r6, r2
70000d2a:	d111      	bne.n	70000d50 <__ieee754_pow+0x40>
70000d2c:	1803      	adds	r3, r0, r0
70000d2e:	f489 2200 	eor.w	r2, r9, #524288	; 0x80000
70000d32:	4152      	adcs	r2, r2
70000d34:	4299      	cmp	r1, r3
70000d36:	4b82      	ldr	r3, [pc, #520]	; (70000f40 <__ieee754_pow+0x230>)
70000d38:	4193      	sbcs	r3, r2
70000d3a:	f080 84b3 	bcs.w	700016a4 <__ieee754_pow+0x994>
70000d3e:	4640      	mov	r0, r8
70000d40:	4649      	mov	r1, r9
70000d42:	e9dd 2302 	ldrd	r2, r3, [sp, #8]
70000d46:	f001 f8af 	bl	70001ea8 <__adddf3>
70000d4a:	4683      	mov	fp, r0
70000d4c:	468c      	mov	ip, r1
70000d4e:	e06f      	b.n	70000e30 <__ieee754_pow+0x120>
70000d50:	f029 4400 	bic.w	r4, r9, #2147483648	; 0x80000000
70000d54:	4b7b      	ldr	r3, [pc, #492]	; (70000f44 <__ieee754_pow+0x234>)
70000d56:	464d      	mov	r5, r9
70000d58:	4682      	mov	sl, r0
70000d5a:	429c      	cmp	r4, r3
70000d5c:	dc06      	bgt.n	70000d6c <__ieee754_pow+0x5c>
70000d5e:	d101      	bne.n	70000d64 <__ieee754_pow+0x54>
70000d60:	2800      	cmp	r0, #0
70000d62:	d1ec      	bne.n	70000d3e <__ieee754_pow+0x2e>
70000d64:	429e      	cmp	r6, r3
70000d66:	dc01      	bgt.n	70000d6c <__ieee754_pow+0x5c>
70000d68:	d10f      	bne.n	70000d8a <__ieee754_pow+0x7a>
70000d6a:	b172      	cbz	r2, 70000d8a <__ieee754_pow+0x7a>
70000d6c:	f105 4540 	add.w	r5, r5, #3221225472	; 0xc0000000
70000d70:	f505 1580 	add.w	r5, r5, #1048576	; 0x100000
70000d74:	ea55 050a 	orrs.w	r5, r5, sl
70000d78:	d1e1      	bne.n	70000d3e <__ieee754_pow+0x2e>
70000d7a:	e9dd 3202 	ldrd	r3, r2, [sp, #8]
70000d7e:	18db      	adds	r3, r3, r3
70000d80:	f482 2200 	eor.w	r2, r2, #524288	; 0x80000
70000d84:	4152      	adcs	r2, r2
70000d86:	429d      	cmp	r5, r3
70000d88:	e7d5      	b.n	70000d36 <__ieee754_pow+0x26>
70000d8a:	2d00      	cmp	r5, #0
70000d8c:	da39      	bge.n	70000e02 <__ieee754_pow+0xf2>
70000d8e:	4b6e      	ldr	r3, [pc, #440]	; (70000f48 <__ieee754_pow+0x238>)
70000d90:	429e      	cmp	r6, r3
70000d92:	dc52      	bgt.n	70000e3a <__ieee754_pow+0x12a>
70000d94:	f1a3 7354 	sub.w	r3, r3, #55574528	; 0x3500000
70000d98:	429e      	cmp	r6, r3
70000d9a:	f340 8496 	ble.w	700016ca <__ieee754_pow+0x9ba>
70000d9e:	1533      	asrs	r3, r6, #20
70000da0:	f2a3 33ff 	subw	r3, r3, #1023	; 0x3ff
70000da4:	2b14      	cmp	r3, #20
70000da6:	dd0f      	ble.n	70000dc8 <__ieee754_pow+0xb8>
70000da8:	f1c3 0334 	rsb	r3, r3, #52	; 0x34
70000dac:	fa22 f103 	lsr.w	r1, r2, r3
70000db0:	fa01 f303 	lsl.w	r3, r1, r3
70000db4:	4293      	cmp	r3, r2
70000db6:	f040 8488 	bne.w	700016ca <__ieee754_pow+0x9ba>
70000dba:	f001 0101 	and.w	r1, r1, #1
70000dbe:	f1c1 0302 	rsb	r3, r1, #2
70000dc2:	9300      	str	r3, [sp, #0]
70000dc4:	b182      	cbz	r2, 70000de8 <__ieee754_pow+0xd8>
70000dc6:	e05d      	b.n	70000e84 <__ieee754_pow+0x174>
70000dc8:	2a00      	cmp	r2, #0
70000dca:	d159      	bne.n	70000e80 <__ieee754_pow+0x170>
70000dcc:	f1c3 0314 	rsb	r3, r3, #20
70000dd0:	fa46 f103 	asr.w	r1, r6, r3
70000dd4:	fa01 f303 	lsl.w	r3, r1, r3
70000dd8:	42b3      	cmp	r3, r6
70000dda:	f040 8473 	bne.w	700016c4 <__ieee754_pow+0x9b4>
70000dde:	f001 0101 	and.w	r1, r1, #1
70000de2:	f1c1 0302 	rsb	r3, r1, #2
70000de6:	9300      	str	r3, [sp, #0]
70000de8:	4b58      	ldr	r3, [pc, #352]	; (70000f4c <__ieee754_pow+0x23c>)
70000dea:	429e      	cmp	r6, r3
70000dec:	d132      	bne.n	70000e54 <__ieee754_pow+0x144>
70000dee:	2f00      	cmp	r7, #0
70000df0:	f280 8464 	bge.w	700016bc <__ieee754_pow+0x9ac>
70000df4:	4642      	mov	r2, r8
70000df6:	464b      	mov	r3, r9
70000df8:	2000      	movs	r0, #0
70000dfa:	4954      	ldr	r1, [pc, #336]	; (70000f4c <__ieee754_pow+0x23c>)
70000dfc:	f001 fb34 	bl	70002468 <__aeabi_ddiv>
70000e00:	e7a3      	b.n	70000d4a <__ieee754_pow+0x3a>
70000e02:	2300      	movs	r3, #0
70000e04:	9300      	str	r3, [sp, #0]
70000e06:	2a00      	cmp	r2, #0
70000e08:	d13c      	bne.n	70000e84 <__ieee754_pow+0x174>
70000e0a:	4b4e      	ldr	r3, [pc, #312]	; (70000f44 <__ieee754_pow+0x234>)
70000e0c:	429e      	cmp	r6, r3
70000e0e:	d1eb      	bne.n	70000de8 <__ieee754_pow+0xd8>
70000e10:	f104 4340 	add.w	r3, r4, #3221225472	; 0xc0000000
70000e14:	f503 1380 	add.w	r3, r3, #1048576	; 0x100000
70000e18:	ea53 030a 	orrs.w	r3, r3, sl
70000e1c:	f000 8442 	beq.w	700016a4 <__ieee754_pow+0x994>
70000e20:	4b4b      	ldr	r3, [pc, #300]	; (70000f50 <__ieee754_pow+0x240>)
70000e22:	429c      	cmp	r4, r3
70000e24:	dd0b      	ble.n	70000e3e <__ieee754_pow+0x12e>
70000e26:	2f00      	cmp	r7, #0
70000e28:	f2c0 8442 	blt.w	700016b0 <__ieee754_pow+0x9a0>
70000e2c:	e9dd bc02 	ldrd	fp, ip, [sp, #8]
70000e30:	4658      	mov	r0, fp
70000e32:	4661      	mov	r1, ip
70000e34:	b013      	add	sp, #76	; 0x4c
70000e36:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
70000e3a:	2302      	movs	r3, #2
70000e3c:	e7e2      	b.n	70000e04 <__ieee754_pow+0xf4>
70000e3e:	2f00      	cmp	r7, #0
70000e40:	f04f 0b00 	mov.w	fp, #0
70000e44:	f04f 0c00 	mov.w	ip, #0
70000e48:	daf2      	bge.n	70000e30 <__ieee754_pow+0x120>
70000e4a:	e9dd b302 	ldrd	fp, r3, [sp, #8]
70000e4e:	f103 4c00 	add.w	ip, r3, #2147483648	; 0x80000000
70000e52:	e7ed      	b.n	70000e30 <__ieee754_pow+0x120>
70000e54:	f1b7 4f80 	cmp.w	r7, #1073741824	; 0x40000000
70000e58:	d106      	bne.n	70000e68 <__ieee754_pow+0x158>
70000e5a:	4642      	mov	r2, r8
70000e5c:	464b      	mov	r3, r9
70000e5e:	4640      	mov	r0, r8
70000e60:	4649      	mov	r1, r9
70000e62:	f001 f9d7 	bl	70002214 <__aeabi_dmul>
70000e66:	e770      	b.n	70000d4a <__ieee754_pow+0x3a>
70000e68:	4b3a      	ldr	r3, [pc, #232]	; (70000f54 <__ieee754_pow+0x244>)
70000e6a:	429f      	cmp	r7, r3
70000e6c:	d10a      	bne.n	70000e84 <__ieee754_pow+0x174>
70000e6e:	2d00      	cmp	r5, #0
70000e70:	db08      	blt.n	70000e84 <__ieee754_pow+0x174>
70000e72:	4640      	mov	r0, r8
70000e74:	4649      	mov	r1, r9
70000e76:	b013      	add	sp, #76	; 0x4c
70000e78:	e8bd 4ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
70000e7c:	f000 bc56 	b.w	7000172c <__ieee754_sqrt>
70000e80:	2300      	movs	r3, #0
70000e82:	9300      	str	r3, [sp, #0]
70000e84:	4640      	mov	r0, r8
70000e86:	4649      	mov	r1, r9
70000e88:	f000 fd98 	bl	700019bc <fabs>
70000e8c:	4683      	mov	fp, r0
70000e8e:	468c      	mov	ip, r1
70000e90:	f1ba 0f00 	cmp.w	sl, #0
70000e94:	d128      	bne.n	70000ee8 <__ieee754_pow+0x1d8>
70000e96:	b124      	cbz	r4, 70000ea2 <__ieee754_pow+0x192>
70000e98:	f025 4240 	bic.w	r2, r5, #3221225472	; 0xc0000000
70000e9c:	4b2b      	ldr	r3, [pc, #172]	; (70000f4c <__ieee754_pow+0x23c>)
70000e9e:	429a      	cmp	r2, r3
70000ea0:	d122      	bne.n	70000ee8 <__ieee754_pow+0x1d8>
70000ea2:	2f00      	cmp	r7, #0
70000ea4:	da07      	bge.n	70000eb6 <__ieee754_pow+0x1a6>
70000ea6:	465a      	mov	r2, fp
70000ea8:	4663      	mov	r3, ip
70000eaa:	2000      	movs	r0, #0
70000eac:	4927      	ldr	r1, [pc, #156]	; (70000f4c <__ieee754_pow+0x23c>)
70000eae:	f001 fadb 	bl	70002468 <__aeabi_ddiv>
70000eb2:	4683      	mov	fp, r0
70000eb4:	468c      	mov	ip, r1
70000eb6:	2d00      	cmp	r5, #0
70000eb8:	daba      	bge.n	70000e30 <__ieee754_pow+0x120>
70000eba:	f104 4440 	add.w	r4, r4, #3221225472	; 0xc0000000
70000ebe:	9b00      	ldr	r3, [sp, #0]
70000ec0:	f504 1480 	add.w	r4, r4, #1048576	; 0x100000
70000ec4:	4323      	orrs	r3, r4
70000ec6:	d108      	bne.n	70000eda <__ieee754_pow+0x1ca>
70000ec8:	465a      	mov	r2, fp
70000eca:	4663      	mov	r3, ip
70000ecc:	4658      	mov	r0, fp
70000ece:	4661      	mov	r1, ip
70000ed0:	f000 ffe8 	bl	70001ea4 <__aeabi_dsub>
70000ed4:	4602      	mov	r2, r0
70000ed6:	460b      	mov	r3, r1
70000ed8:	e790      	b.n	70000dfc <__ieee754_pow+0xec>
70000eda:	9b00      	ldr	r3, [sp, #0]
70000edc:	2b01      	cmp	r3, #1
70000ede:	d1a7      	bne.n	70000e30 <__ieee754_pow+0x120>
70000ee0:	f10c 4300 	add.w	r3, ip, #2147483648	; 0x80000000
70000ee4:	469c      	mov	ip, r3
70000ee6:	e7a3      	b.n	70000e30 <__ieee754_pow+0x120>
70000ee8:	0feb      	lsrs	r3, r5, #31
70000eea:	3b01      	subs	r3, #1
70000eec:	930d      	str	r3, [sp, #52]	; 0x34
70000eee:	9a0d      	ldr	r2, [sp, #52]	; 0x34
70000ef0:	9b00      	ldr	r3, [sp, #0]
70000ef2:	4313      	orrs	r3, r2
70000ef4:	d104      	bne.n	70000f00 <__ieee754_pow+0x1f0>
70000ef6:	4642      	mov	r2, r8
70000ef8:	464b      	mov	r3, r9
70000efa:	4640      	mov	r0, r8
70000efc:	4649      	mov	r1, r9
70000efe:	e7e7      	b.n	70000ed0 <__ieee754_pow+0x1c0>
70000f00:	4b15      	ldr	r3, [pc, #84]	; (70000f58 <__ieee754_pow+0x248>)
70000f02:	429e      	cmp	r6, r3
70000f04:	f340 80f6 	ble.w	700010f4 <__ieee754_pow+0x3e4>
70000f08:	f103 7304 	add.w	r3, r3, #34603008	; 0x2100000
70000f0c:	429e      	cmp	r6, r3
70000f0e:	4b10      	ldr	r3, [pc, #64]	; (70000f50 <__ieee754_pow+0x240>)
70000f10:	dd09      	ble.n	70000f26 <__ieee754_pow+0x216>
70000f12:	429c      	cmp	r4, r3
70000f14:	dc0c      	bgt.n	70000f30 <__ieee754_pow+0x220>
70000f16:	2f00      	cmp	r7, #0
70000f18:	da0c      	bge.n	70000f34 <__ieee754_pow+0x224>
70000f1a:	2000      	movs	r0, #0
70000f1c:	b013      	add	sp, #76	; 0x4c
70000f1e:	e8bd 4ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
70000f22:	f000 bce1 	b.w	700018e8 <__math_oflow>
70000f26:	429c      	cmp	r4, r3
70000f28:	dbf5      	blt.n	70000f16 <__ieee754_pow+0x206>
70000f2a:	4b08      	ldr	r3, [pc, #32]	; (70000f4c <__ieee754_pow+0x23c>)
70000f2c:	429c      	cmp	r4, r3
70000f2e:	dd15      	ble.n	70000f5c <__ieee754_pow+0x24c>
70000f30:	2f00      	cmp	r7, #0
70000f32:	dcf2      	bgt.n	70000f1a <__ieee754_pow+0x20a>
70000f34:	2000      	movs	r0, #0
70000f36:	b013      	add	sp, #76	; 0x4c
70000f38:	e8bd 4ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
70000f3c:	f000 bccb 	b.w	700018d6 <__math_uflow>
70000f40:	fff00000 	.word	0xfff00000
70000f44:	7ff00000 	.word	0x7ff00000
70000f48:	433fffff 	.word	0x433fffff
70000f4c:	3ff00000 	.word	0x3ff00000
70000f50:	3fefffff 	.word	0x3fefffff
70000f54:	3fe00000 	.word	0x3fe00000
70000f58:	41e00000 	.word	0x41e00000
70000f5c:	4661      	mov	r1, ip
70000f5e:	2200      	movs	r2, #0
70000f60:	4b5f      	ldr	r3, [pc, #380]	; (700010e0 <__ieee754_pow+0x3d0>)
70000f62:	4658      	mov	r0, fp
70000f64:	f000 ff9e 	bl	70001ea4 <__aeabi_dsub>
70000f68:	4604      	mov	r4, r0
70000f6a:	460d      	mov	r5, r1
70000f6c:	a354      	add	r3, pc, #336	; (adr r3, 700010c0 <__ieee754_pow+0x3b0>)
70000f6e:	e9d3 2300 	ldrd	r2, r3, [r3]
70000f72:	f001 f94f 	bl	70002214 <__aeabi_dmul>
70000f76:	4606      	mov	r6, r0
70000f78:	460f      	mov	r7, r1
70000f7a:	4620      	mov	r0, r4
70000f7c:	4629      	mov	r1, r5
70000f7e:	a352      	add	r3, pc, #328	; (adr r3, 700010c8 <__ieee754_pow+0x3b8>)
70000f80:	e9d3 2300 	ldrd	r2, r3, [r3]
70000f84:	f001 f946 	bl	70002214 <__aeabi_dmul>
70000f88:	2200      	movs	r2, #0
70000f8a:	4682      	mov	sl, r0
70000f8c:	468b      	mov	fp, r1
70000f8e:	4b55      	ldr	r3, [pc, #340]	; (700010e4 <__ieee754_pow+0x3d4>)
70000f90:	4620      	mov	r0, r4
70000f92:	4629      	mov	r1, r5
70000f94:	f001 f93e 	bl	70002214 <__aeabi_dmul>
70000f98:	4602      	mov	r2, r0
70000f9a:	460b      	mov	r3, r1
70000f9c:	a14c      	add	r1, pc, #304	; (adr r1, 700010d0 <__ieee754_pow+0x3c0>)
70000f9e:	e9d1 0100 	ldrd	r0, r1, [r1]
70000fa2:	f000 ff7f 	bl	70001ea4 <__aeabi_dsub>
70000fa6:	4622      	mov	r2, r4
70000fa8:	462b      	mov	r3, r5
70000faa:	f001 f933 	bl	70002214 <__aeabi_dmul>
70000fae:	4602      	mov	r2, r0
70000fb0:	460b      	mov	r3, r1
70000fb2:	2000      	movs	r0, #0
70000fb4:	494c      	ldr	r1, [pc, #304]	; (700010e8 <__ieee754_pow+0x3d8>)
70000fb6:	f000 ff75 	bl	70001ea4 <__aeabi_dsub>
70000fba:	4680      	mov	r8, r0
70000fbc:	4689      	mov	r9, r1
70000fbe:	4622      	mov	r2, r4
70000fc0:	462b      	mov	r3, r5
70000fc2:	4620      	mov	r0, r4
70000fc4:	4629      	mov	r1, r5
70000fc6:	f001 f925 	bl	70002214 <__aeabi_dmul>
70000fca:	4602      	mov	r2, r0
70000fcc:	460b      	mov	r3, r1
70000fce:	4640      	mov	r0, r8
70000fd0:	4649      	mov	r1, r9
70000fd2:	f001 f91f 	bl	70002214 <__aeabi_dmul>
70000fd6:	a340      	add	r3, pc, #256	; (adr r3, 700010d8 <__ieee754_pow+0x3c8>)
70000fd8:	e9d3 2300 	ldrd	r2, r3, [r3]
70000fdc:	f001 f91a 	bl	70002214 <__aeabi_dmul>
70000fe0:	4602      	mov	r2, r0
70000fe2:	460b      	mov	r3, r1
70000fe4:	4650      	mov	r0, sl
70000fe6:	4659      	mov	r1, fp
70000fe8:	f04f 0a00 	mov.w	sl, #0
70000fec:	f000 ff5a 	bl	70001ea4 <__aeabi_dsub>
70000ff0:	4602      	mov	r2, r0
70000ff2:	460b      	mov	r3, r1
70000ff4:	4604      	mov	r4, r0
70000ff6:	460d      	mov	r5, r1
70000ff8:	4630      	mov	r0, r6
70000ffa:	4639      	mov	r1, r7
70000ffc:	f000 ff54 	bl	70001ea8 <__adddf3>
70001000:	4632      	mov	r2, r6
70001002:	463b      	mov	r3, r7
70001004:	4650      	mov	r0, sl
70001006:	468b      	mov	fp, r1
70001008:	f000 ff4c 	bl	70001ea4 <__aeabi_dsub>
7000100c:	4602      	mov	r2, r0
7000100e:	460b      	mov	r3, r1
70001010:	4620      	mov	r0, r4
70001012:	4629      	mov	r1, r5
70001014:	f000 ff46 	bl	70001ea4 <__aeabi_dsub>
70001018:	9b00      	ldr	r3, [sp, #0]
7000101a:	9a0d      	ldr	r2, [sp, #52]	; 0x34
7000101c:	4604      	mov	r4, r0
7000101e:	3b01      	subs	r3, #1
70001020:	460d      	mov	r5, r1
70001022:	4313      	orrs	r3, r2
70001024:	f04f 0200 	mov.w	r2, #0
70001028:	bf0c      	ite	eq
7000102a:	4b30      	ldreq	r3, [pc, #192]	; (700010ec <__ieee754_pow+0x3dc>)
7000102c:	4b2c      	ldrne	r3, [pc, #176]	; (700010e0 <__ieee754_pow+0x3d0>)
7000102e:	e9dd 6702 	ldrd	r6, r7, [sp, #8]
70001032:	2600      	movs	r6, #0
70001034:	e9cd 2300 	strd	r2, r3, [sp]
70001038:	e9dd 0102 	ldrd	r0, r1, [sp, #8]
7000103c:	4632      	mov	r2, r6
7000103e:	463b      	mov	r3, r7
70001040:	f000 ff30 	bl	70001ea4 <__aeabi_dsub>
70001044:	4652      	mov	r2, sl
70001046:	465b      	mov	r3, fp
70001048:	f001 f8e4 	bl	70002214 <__aeabi_dmul>
7000104c:	4680      	mov	r8, r0
7000104e:	4689      	mov	r9, r1
70001050:	4620      	mov	r0, r4
70001052:	4629      	mov	r1, r5
70001054:	e9dd 2302 	ldrd	r2, r3, [sp, #8]
70001058:	f001 f8dc 	bl	70002214 <__aeabi_dmul>
7000105c:	4602      	mov	r2, r0
7000105e:	460b      	mov	r3, r1
70001060:	4640      	mov	r0, r8
70001062:	4649      	mov	r1, r9
70001064:	f000 ff20 	bl	70001ea8 <__adddf3>
70001068:	4632      	mov	r2, r6
7000106a:	463b      	mov	r3, r7
7000106c:	4680      	mov	r8, r0
7000106e:	4689      	mov	r9, r1
70001070:	4650      	mov	r0, sl
70001072:	4659      	mov	r1, fp
70001074:	f001 f8ce 	bl	70002214 <__aeabi_dmul>
70001078:	4604      	mov	r4, r0
7000107a:	460d      	mov	r5, r1
7000107c:	460b      	mov	r3, r1
7000107e:	4602      	mov	r2, r0
70001080:	4649      	mov	r1, r9
70001082:	4640      	mov	r0, r8
70001084:	e9cd 4502 	strd	r4, r5, [sp, #8]
70001088:	f000 ff0e 	bl	70001ea8 <__adddf3>
7000108c:	4b18      	ldr	r3, [pc, #96]	; (700010f0 <__ieee754_pow+0x3e0>)
7000108e:	4682      	mov	sl, r0
70001090:	460f      	mov	r7, r1
70001092:	4299      	cmp	r1, r3
70001094:	460e      	mov	r6, r1
70001096:	f340 82e0 	ble.w	7000165a <__ieee754_pow+0x94a>
7000109a:	f101 433f 	add.w	r3, r1, #3204448256	; 0xbf000000
7000109e:	f503 03e0 	add.w	r3, r3, #7340032	; 0x700000
700010a2:	4303      	orrs	r3, r0
700010a4:	f000 81da 	beq.w	7000145c <__ieee754_pow+0x74c>
700010a8:	2200      	movs	r2, #0
700010aa:	2300      	movs	r3, #0
700010ac:	e9dd 0100 	ldrd	r0, r1, [sp]
700010b0:	f001 fb22 	bl	700026f8 <__aeabi_dcmplt>
700010b4:	3800      	subs	r0, #0
700010b6:	bf18      	it	ne
700010b8:	2001      	movne	r0, #1
700010ba:	e72f      	b.n	70000f1c <__ieee754_pow+0x20c>
700010bc:	f3af 8000 	nop.w
700010c0:	60000000 	.word	0x60000000
700010c4:	3ff71547 	.word	0x3ff71547
700010c8:	f85ddf44 	.word	0xf85ddf44
700010cc:	3e54ae0b 	.word	0x3e54ae0b
700010d0:	55555555 	.word	0x55555555
700010d4:	3fd55555 	.word	0x3fd55555
700010d8:	652b82fe 	.word	0x652b82fe
700010dc:	3ff71547 	.word	0x3ff71547
700010e0:	3ff00000 	.word	0x3ff00000
700010e4:	3fd00000 	.word	0x3fd00000
700010e8:	3fe00000 	.word	0x3fe00000
700010ec:	bff00000 	.word	0xbff00000
700010f0:	408fffff 	.word	0x408fffff
700010f4:	4bd2      	ldr	r3, [pc, #840]	; (70001440 <__ieee754_pow+0x730>)
700010f6:	2200      	movs	r2, #0
700010f8:	402b      	ands	r3, r5
700010fa:	b943      	cbnz	r3, 7000110e <__ieee754_pow+0x3fe>
700010fc:	4658      	mov	r0, fp
700010fe:	4bd1      	ldr	r3, [pc, #836]	; (70001444 <__ieee754_pow+0x734>)
70001100:	4661      	mov	r1, ip
70001102:	f001 f887 	bl	70002214 <__aeabi_dmul>
70001106:	f06f 0234 	mvn.w	r2, #52	; 0x34
7000110a:	4683      	mov	fp, r0
7000110c:	460c      	mov	r4, r1
7000110e:	1523      	asrs	r3, r4, #20
70001110:	f3c4 0413 	ubfx	r4, r4, #0, #20
70001114:	f2a3 33ff 	subw	r3, r3, #1023	; 0x3ff
70001118:	f044 557f 	orr.w	r5, r4, #1069547520	; 0x3fc00000
7000111c:	4413      	add	r3, r2
7000111e:	f445 1540 	orr.w	r5, r5, #3145728	; 0x300000
70001122:	930b      	str	r3, [sp, #44]	; 0x2c
70001124:	4bc8      	ldr	r3, [pc, #800]	; (70001448 <__ieee754_pow+0x738>)
70001126:	429c      	cmp	r4, r3
70001128:	dd08      	ble.n	7000113c <__ieee754_pow+0x42c>
7000112a:	4bc8      	ldr	r3, [pc, #800]	; (7000144c <__ieee754_pow+0x73c>)
7000112c:	429c      	cmp	r4, r3
7000112e:	f340 815e 	ble.w	700013ee <__ieee754_pow+0x6de>
70001132:	9b0b      	ldr	r3, [sp, #44]	; 0x2c
70001134:	f5a5 1580 	sub.w	r5, r5, #1048576	; 0x100000
70001138:	3301      	adds	r3, #1
7000113a:	930b      	str	r3, [sp, #44]	; 0x2c
7000113c:	2600      	movs	r6, #0
7000113e:	4bc4      	ldr	r3, [pc, #784]	; (70001450 <__ieee754_pow+0x740>)
70001140:	46da      	mov	sl, fp
70001142:	4658      	mov	r0, fp
70001144:	4629      	mov	r1, r5
70001146:	eb03 03c6 	add.w	r3, r3, r6, lsl #3
7000114a:	46ab      	mov	fp, r5
7000114c:	930c      	str	r3, [sp, #48]	; 0x30
7000114e:	e9d3 3400 	ldrd	r3, r4, [r3]
70001152:	461a      	mov	r2, r3
70001154:	e9cd 3408 	strd	r3, r4, [sp, #32]
70001158:	4623      	mov	r3, r4
7000115a:	f000 fea3 	bl	70001ea4 <__aeabi_dsub>
7000115e:	4652      	mov	r2, sl
70001160:	462b      	mov	r3, r5
70001162:	106d      	asrs	r5, r5, #1
70001164:	e9cd 010e 	strd	r0, r1, [sp, #56]	; 0x38
70001168:	e9dd 0108 	ldrd	r0, r1, [sp, #32]
7000116c:	f000 fe9c 	bl	70001ea8 <__adddf3>
70001170:	4602      	mov	r2, r0
70001172:	460b      	mov	r3, r1
70001174:	2000      	movs	r0, #0
70001176:	49b7      	ldr	r1, [pc, #732]	; (70001454 <__ieee754_pow+0x744>)
70001178:	f045 5500 	orr.w	r5, r5, #536870912	; 0x20000000
7000117c:	f001 f974 	bl	70002468 <__aeabi_ddiv>
70001180:	4602      	mov	r2, r0
70001182:	460b      	mov	r3, r1
70001184:	f505 2500 	add.w	r5, r5, #524288	; 0x80000
70001188:	e9cd 0110 	strd	r0, r1, [sp, #64]	; 0x40
7000118c:	e9dd 010e 	ldrd	r0, r1, [sp, #56]	; 0x38
70001190:	f001 f840 	bl	70002214 <__aeabi_dmul>
70001194:	2200      	movs	r2, #0
70001196:	e9cd 0106 	strd	r0, r1, [sp, #24]
7000119a:	e9dd 3406 	ldrd	r3, r4, [sp, #24]
7000119e:	e9cd 3404 	strd	r3, r4, [sp, #16]
700011a2:	2300      	movs	r3, #0
700011a4:	4614      	mov	r4, r2
700011a6:	9304      	str	r3, [sp, #16]
700011a8:	eb05 4386 	add.w	r3, r5, r6, lsl #18
700011ac:	e9dd 8904 	ldrd	r8, r9, [sp, #16]
700011b0:	461d      	mov	r5, r3
700011b2:	4640      	mov	r0, r8
700011b4:	4649      	mov	r1, r9
700011b6:	f001 f82d 	bl	70002214 <__aeabi_dmul>
700011ba:	4602      	mov	r2, r0
700011bc:	460b      	mov	r3, r1
700011be:	e9dd 010e 	ldrd	r0, r1, [sp, #56]	; 0x38
700011c2:	f000 fe6f 	bl	70001ea4 <__aeabi_dsub>
700011c6:	4606      	mov	r6, r0
700011c8:	460f      	mov	r7, r1
700011ca:	4620      	mov	r0, r4
700011cc:	4629      	mov	r1, r5
700011ce:	e9dd 2308 	ldrd	r2, r3, [sp, #32]
700011d2:	f000 fe67 	bl	70001ea4 <__aeabi_dsub>
700011d6:	4602      	mov	r2, r0
700011d8:	460b      	mov	r3, r1
700011da:	4650      	mov	r0, sl
700011dc:	4659      	mov	r1, fp
700011de:	f000 fe61 	bl	70001ea4 <__aeabi_dsub>
700011e2:	4642      	mov	r2, r8
700011e4:	464b      	mov	r3, r9
700011e6:	f001 f815 	bl	70002214 <__aeabi_dmul>
700011ea:	4602      	mov	r2, r0
700011ec:	460b      	mov	r3, r1
700011ee:	4630      	mov	r0, r6
700011f0:	4639      	mov	r1, r7
700011f2:	f000 fe57 	bl	70001ea4 <__aeabi_dsub>
700011f6:	e9dd 2310 	ldrd	r2, r3, [sp, #64]	; 0x40
700011fa:	f001 f80b 	bl	70002214 <__aeabi_dmul>
700011fe:	e9dd 2306 	ldrd	r2, r3, [sp, #24]
70001202:	e9cd 0108 	strd	r0, r1, [sp, #32]
70001206:	4610      	mov	r0, r2
70001208:	4619      	mov	r1, r3
7000120a:	f001 f803 	bl	70002214 <__aeabi_dmul>
7000120e:	4604      	mov	r4, r0
70001210:	460d      	mov	r5, r1
70001212:	a379      	add	r3, pc, #484	; (adr r3, 700013f8 <__ieee754_pow+0x6e8>)
70001214:	e9d3 2300 	ldrd	r2, r3, [r3]
70001218:	f000 fffc 	bl	70002214 <__aeabi_dmul>
7000121c:	a378      	add	r3, pc, #480	; (adr r3, 70001400 <__ieee754_pow+0x6f0>)
7000121e:	e9d3 2300 	ldrd	r2, r3, [r3]
70001222:	f000 fe41 	bl	70001ea8 <__adddf3>
70001226:	4622      	mov	r2, r4
70001228:	462b      	mov	r3, r5
7000122a:	f000 fff3 	bl	70002214 <__aeabi_dmul>
7000122e:	a376      	add	r3, pc, #472	; (adr r3, 70001408 <__ieee754_pow+0x6f8>)
70001230:	e9d3 2300 	ldrd	r2, r3, [r3]
70001234:	f000 fe38 	bl	70001ea8 <__adddf3>
70001238:	4622      	mov	r2, r4
7000123a:	462b      	mov	r3, r5
7000123c:	f000 ffea 	bl	70002214 <__aeabi_dmul>
70001240:	a373      	add	r3, pc, #460	; (adr r3, 70001410 <__ieee754_pow+0x700>)
70001242:	e9d3 2300 	ldrd	r2, r3, [r3]
70001246:	f000 fe2f 	bl	70001ea8 <__adddf3>
7000124a:	4622      	mov	r2, r4
7000124c:	462b      	mov	r3, r5
7000124e:	f000 ffe1 	bl	70002214 <__aeabi_dmul>
70001252:	a371      	add	r3, pc, #452	; (adr r3, 70001418 <__ieee754_pow+0x708>)
70001254:	e9d3 2300 	ldrd	r2, r3, [r3]
70001258:	f000 fe26 	bl	70001ea8 <__adddf3>
7000125c:	4622      	mov	r2, r4
7000125e:	462b      	mov	r3, r5
70001260:	f000 ffd8 	bl	70002214 <__aeabi_dmul>
70001264:	a36e      	add	r3, pc, #440	; (adr r3, 70001420 <__ieee754_pow+0x710>)
70001266:	e9d3 2300 	ldrd	r2, r3, [r3]
7000126a:	f000 fe1d 	bl	70001ea8 <__adddf3>
7000126e:	4606      	mov	r6, r0
70001270:	460f      	mov	r7, r1
70001272:	4622      	mov	r2, r4
70001274:	462b      	mov	r3, r5
70001276:	4620      	mov	r0, r4
70001278:	4629      	mov	r1, r5
7000127a:	f000 ffcb 	bl	70002214 <__aeabi_dmul>
7000127e:	4602      	mov	r2, r0
70001280:	460b      	mov	r3, r1
70001282:	4630      	mov	r0, r6
70001284:	4639      	mov	r1, r7
70001286:	f000 ffc5 	bl	70002214 <__aeabi_dmul>
7000128a:	4642      	mov	r2, r8
7000128c:	4604      	mov	r4, r0
7000128e:	460d      	mov	r5, r1
70001290:	464b      	mov	r3, r9
70001292:	e9dd 0106 	ldrd	r0, r1, [sp, #24]
70001296:	f000 fe07 	bl	70001ea8 <__adddf3>
7000129a:	e9dd 2308 	ldrd	r2, r3, [sp, #32]
7000129e:	f000 ffb9 	bl	70002214 <__aeabi_dmul>
700012a2:	4622      	mov	r2, r4
700012a4:	462b      	mov	r3, r5
700012a6:	2400      	movs	r4, #0
700012a8:	f000 fdfe 	bl	70001ea8 <__adddf3>
700012ac:	4642      	mov	r2, r8
700012ae:	4606      	mov	r6, r0
700012b0:	460f      	mov	r7, r1
700012b2:	464b      	mov	r3, r9
700012b4:	4640      	mov	r0, r8
700012b6:	4649      	mov	r1, r9
700012b8:	f000 ffac 	bl	70002214 <__aeabi_dmul>
700012bc:	2200      	movs	r2, #0
700012be:	4b66      	ldr	r3, [pc, #408]	; (70001458 <__ieee754_pow+0x748>)
700012c0:	4682      	mov	sl, r0
700012c2:	468b      	mov	fp, r1
700012c4:	f000 fdf0 	bl	70001ea8 <__adddf3>
700012c8:	4632      	mov	r2, r6
700012ca:	463b      	mov	r3, r7
700012cc:	f000 fdec 	bl	70001ea8 <__adddf3>
700012d0:	460d      	mov	r5, r1
700012d2:	4622      	mov	r2, r4
700012d4:	460b      	mov	r3, r1
700012d6:	4640      	mov	r0, r8
700012d8:	4649      	mov	r1, r9
700012da:	f000 ff9b 	bl	70002214 <__aeabi_dmul>
700012de:	2200      	movs	r2, #0
700012e0:	4680      	mov	r8, r0
700012e2:	4689      	mov	r9, r1
700012e4:	4b5c      	ldr	r3, [pc, #368]	; (70001458 <__ieee754_pow+0x748>)
700012e6:	4620      	mov	r0, r4
700012e8:	4629      	mov	r1, r5
700012ea:	f000 fddb 	bl	70001ea4 <__aeabi_dsub>
700012ee:	4652      	mov	r2, sl
700012f0:	465b      	mov	r3, fp
700012f2:	f04f 0a00 	mov.w	sl, #0
700012f6:	f000 fdd5 	bl	70001ea4 <__aeabi_dsub>
700012fa:	4602      	mov	r2, r0
700012fc:	460b      	mov	r3, r1
700012fe:	4630      	mov	r0, r6
70001300:	4639      	mov	r1, r7
70001302:	f000 fdcf 	bl	70001ea4 <__aeabi_dsub>
70001306:	e9dd 2306 	ldrd	r2, r3, [sp, #24]
7000130a:	f000 ff83 	bl	70002214 <__aeabi_dmul>
7000130e:	4606      	mov	r6, r0
70001310:	460f      	mov	r7, r1
70001312:	4622      	mov	r2, r4
70001314:	462b      	mov	r3, r5
70001316:	2400      	movs	r4, #0
70001318:	e9dd 0108 	ldrd	r0, r1, [sp, #32]
7000131c:	f000 ff7a 	bl	70002214 <__aeabi_dmul>
70001320:	4602      	mov	r2, r0
70001322:	460b      	mov	r3, r1
70001324:	4630      	mov	r0, r6
70001326:	4639      	mov	r1, r7
70001328:	f000 fdbe 	bl	70001ea8 <__adddf3>
7000132c:	4606      	mov	r6, r0
7000132e:	460f      	mov	r7, r1
70001330:	4602      	mov	r2, r0
70001332:	460b      	mov	r3, r1
70001334:	4640      	mov	r0, r8
70001336:	4649      	mov	r1, r9
70001338:	f000 fdb6 	bl	70001ea8 <__adddf3>
7000133c:	460d      	mov	r5, r1
7000133e:	4620      	mov	r0, r4
70001340:	a339      	add	r3, pc, #228	; (adr r3, 70001428 <__ieee754_pow+0x718>)
70001342:	e9d3 2300 	ldrd	r2, r3, [r3]
70001346:	f000 ff65 	bl	70002214 <__aeabi_dmul>
7000134a:	4642      	mov	r2, r8
7000134c:	464b      	mov	r3, r9
7000134e:	e9cd 0106 	strd	r0, r1, [sp, #24]
70001352:	4620      	mov	r0, r4
70001354:	4629      	mov	r1, r5
70001356:	f000 fda5 	bl	70001ea4 <__aeabi_dsub>
7000135a:	4602      	mov	r2, r0
7000135c:	460b      	mov	r3, r1
7000135e:	4630      	mov	r0, r6
70001360:	4639      	mov	r1, r7
70001362:	f000 fd9f 	bl	70001ea4 <__aeabi_dsub>
70001366:	a332      	add	r3, pc, #200	; (adr r3, 70001430 <__ieee754_pow+0x720>)
70001368:	e9d3 2300 	ldrd	r2, r3, [r3]
7000136c:	f000 ff52 	bl	70002214 <__aeabi_dmul>
70001370:	4606      	mov	r6, r0
70001372:	460f      	mov	r7, r1
70001374:	4620      	mov	r0, r4
70001376:	4629      	mov	r1, r5
70001378:	a32f      	add	r3, pc, #188	; (adr r3, 70001438 <__ieee754_pow+0x728>)
7000137a:	e9d3 2300 	ldrd	r2, r3, [r3]
7000137e:	f000 ff49 	bl	70002214 <__aeabi_dmul>
70001382:	4602      	mov	r2, r0
70001384:	460b      	mov	r3, r1
70001386:	4630      	mov	r0, r6
70001388:	4639      	mov	r1, r7
7000138a:	f000 fd8d 	bl	70001ea8 <__adddf3>
7000138e:	9b0c      	ldr	r3, [sp, #48]	; 0x30
70001390:	e9d3 2304 	ldrd	r2, r3, [r3, #16]
70001394:	f000 fd88 	bl	70001ea8 <__adddf3>
70001398:	4680      	mov	r8, r0
7000139a:	980b      	ldr	r0, [sp, #44]	; 0x2c
7000139c:	4689      	mov	r9, r1
7000139e:	f000 fecf 	bl	70002140 <__aeabi_i2d>
700013a2:	9b0c      	ldr	r3, [sp, #48]	; 0x30
700013a4:	4604      	mov	r4, r0
700013a6:	460d      	mov	r5, r1
700013a8:	4642      	mov	r2, r8
700013aa:	e9d3 6708 	ldrd	r6, r7, [r3, #32]
700013ae:	464b      	mov	r3, r9
700013b0:	e9dd 0106 	ldrd	r0, r1, [sp, #24]
700013b4:	f000 fd78 	bl	70001ea8 <__adddf3>
700013b8:	4632      	mov	r2, r6
700013ba:	463b      	mov	r3, r7
700013bc:	f000 fd74 	bl	70001ea8 <__adddf3>
700013c0:	4622      	mov	r2, r4
700013c2:	462b      	mov	r3, r5
700013c4:	f000 fd70 	bl	70001ea8 <__adddf3>
700013c8:	4622      	mov	r2, r4
700013ca:	462b      	mov	r3, r5
700013cc:	4650      	mov	r0, sl
700013ce:	468b      	mov	fp, r1
700013d0:	f000 fd68 	bl	70001ea4 <__aeabi_dsub>
700013d4:	4632      	mov	r2, r6
700013d6:	463b      	mov	r3, r7
700013d8:	f000 fd64 	bl	70001ea4 <__aeabi_dsub>
700013dc:	e9dd 2306 	ldrd	r2, r3, [sp, #24]
700013e0:	f000 fd60 	bl	70001ea4 <__aeabi_dsub>
700013e4:	4602      	mov	r2, r0
700013e6:	460b      	mov	r3, r1
700013e8:	4640      	mov	r0, r8
700013ea:	4649      	mov	r1, r9
700013ec:	e612      	b.n	70001014 <__ieee754_pow+0x304>
700013ee:	2601      	movs	r6, #1
700013f0:	e6a5      	b.n	7000113e <__ieee754_pow+0x42e>
700013f2:	bf00      	nop
700013f4:	f3af 8000 	nop.w
700013f8:	4a454eef 	.word	0x4a454eef
700013fc:	3fca7e28 	.word	0x3fca7e28
70001400:	93c9db65 	.word	0x93c9db65
70001404:	3fcd864a 	.word	0x3fcd864a
70001408:	a91d4101 	.word	0xa91d4101
7000140c:	3fd17460 	.word	0x3fd17460
70001410:	518f264d 	.word	0x518f264d
70001414:	3fd55555 	.word	0x3fd55555
70001418:	db6fabff 	.word	0xdb6fabff
7000141c:	3fdb6db6 	.word	0x3fdb6db6
70001420:	33333303 	.word	0x33333303
70001424:	3fe33333 	.word	0x3fe33333
70001428:	e0000000 	.word	0xe0000000
7000142c:	3feec709 	.word	0x3feec709
70001430:	dc3a03fd 	.word	0xdc3a03fd
70001434:	3feec709 	.word	0x3feec709
70001438:	145b01f5 	.word	0x145b01f5
7000143c:	be3e2fe0 	.word	0xbe3e2fe0
70001440:	7ff00000 	.word	0x7ff00000
70001444:	43400000 	.word	0x43400000
70001448:	0003988e 	.word	0x0003988e
7000144c:	000bb679 	.word	0x000bb679
70001450:	70002e68 	.word	0x70002e68
70001454:	3ff00000 	.word	0x3ff00000
70001458:	40080000 	.word	0x40080000
7000145c:	a39c      	add	r3, pc, #624	; (adr r3, 700016d0 <__ieee754_pow+0x9c0>)
7000145e:	e9d3 2300 	ldrd	r2, r3, [r3]
70001462:	4640      	mov	r0, r8
70001464:	4649      	mov	r1, r9
70001466:	f000 fd1f 	bl	70001ea8 <__adddf3>
7000146a:	4622      	mov	r2, r4
7000146c:	462b      	mov	r3, r5
7000146e:	e9cd 0104 	strd	r0, r1, [sp, #16]
70001472:	4650      	mov	r0, sl
70001474:	4639      	mov	r1, r7
70001476:	f000 fd15 	bl	70001ea4 <__aeabi_dsub>
7000147a:	4602      	mov	r2, r0
7000147c:	460b      	mov	r3, r1
7000147e:	e9dd 0104 	ldrd	r0, r1, [sp, #16]
70001482:	f001 f957 	bl	70002734 <__aeabi_dcmpgt>
70001486:	2800      	cmp	r0, #0
70001488:	f47f ae0e 	bne.w	700010a8 <__ieee754_pow+0x398>
7000148c:	f026 4300 	bic.w	r3, r6, #2147483648	; 0x80000000
70001490:	4aa1      	ldr	r2, [pc, #644]	; (70001718 <__ieee754_pow+0xa08>)
70001492:	4293      	cmp	r3, r2
70001494:	f340 8101 	ble.w	7000169a <__ieee754_pow+0x98a>
70001498:	151b      	asrs	r3, r3, #20
7000149a:	f44f 1a80 	mov.w	sl, #1048576	; 0x100000
7000149e:	4f9f      	ldr	r7, [pc, #636]	; (7000171c <__ieee754_pow+0xa0c>)
700014a0:	2000      	movs	r0, #0
700014a2:	f2a3 33fe 	subw	r3, r3, #1022	; 0x3fe
700014a6:	2e00      	cmp	r6, #0
700014a8:	fa4a f303 	asr.w	r3, sl, r3
700014ac:	4433      	add	r3, r6
700014ae:	f3c3 520a 	ubfx	r2, r3, #20, #11
700014b2:	f3c3 0a13 	ubfx	sl, r3, #0, #20
700014b6:	f2a2 32ff 	subw	r2, r2, #1023	; 0x3ff
700014ba:	f44a 1a80 	orr.w	sl, sl, #1048576	; 0x100000
700014be:	fa47 f702 	asr.w	r7, r7, r2
700014c2:	f1c2 0214 	rsb	r2, r2, #20
700014c6:	ea23 0107 	bic.w	r1, r3, r7
700014ca:	fa4a fa02 	asr.w	sl, sl, r2
700014ce:	4602      	mov	r2, r0
700014d0:	4620      	mov	r0, r4
700014d2:	460b      	mov	r3, r1
700014d4:	4629      	mov	r1, r5
700014d6:	bfb8      	it	lt
700014d8:	f1ca 0a00 	rsblt	sl, sl, #0
700014dc:	f000 fce2 	bl	70001ea4 <__aeabi_dsub>
700014e0:	e9cd 0102 	strd	r0, r1, [sp, #8]
700014e4:	2400      	movs	r4, #0
700014e6:	4642      	mov	r2, r8
700014e8:	464b      	mov	r3, r9
700014ea:	e9dd 0102 	ldrd	r0, r1, [sp, #8]
700014ee:	f000 fcdb 	bl	70001ea8 <__adddf3>
700014f2:	460d      	mov	r5, r1
700014f4:	4620      	mov	r0, r4
700014f6:	a378      	add	r3, pc, #480	; (adr r3, 700016d8 <__ieee754_pow+0x9c8>)
700014f8:	e9d3 2300 	ldrd	r2, r3, [r3]
700014fc:	f000 fe8a 	bl	70002214 <__aeabi_dmul>
70001500:	4606      	mov	r6, r0
70001502:	460f      	mov	r7, r1
70001504:	4620      	mov	r0, r4
70001506:	4629      	mov	r1, r5
70001508:	e9dd 2302 	ldrd	r2, r3, [sp, #8]
7000150c:	f000 fcca 	bl	70001ea4 <__aeabi_dsub>
70001510:	4602      	mov	r2, r0
70001512:	460b      	mov	r3, r1
70001514:	4640      	mov	r0, r8
70001516:	4649      	mov	r1, r9
70001518:	f000 fcc4 	bl	70001ea4 <__aeabi_dsub>
7000151c:	a370      	add	r3, pc, #448	; (adr r3, 700016e0 <__ieee754_pow+0x9d0>)
7000151e:	e9d3 2300 	ldrd	r2, r3, [r3]
70001522:	f000 fe77 	bl	70002214 <__aeabi_dmul>
70001526:	4680      	mov	r8, r0
70001528:	4689      	mov	r9, r1
7000152a:	4620      	mov	r0, r4
7000152c:	4629      	mov	r1, r5
7000152e:	a36e      	add	r3, pc, #440	; (adr r3, 700016e8 <__ieee754_pow+0x9d8>)
70001530:	e9d3 2300 	ldrd	r2, r3, [r3]
70001534:	f000 fe6e 	bl	70002214 <__aeabi_dmul>
70001538:	4602      	mov	r2, r0
7000153a:	460b      	mov	r3, r1
7000153c:	4640      	mov	r0, r8
7000153e:	4649      	mov	r1, r9
70001540:	f000 fcb2 	bl	70001ea8 <__adddf3>
70001544:	4604      	mov	r4, r0
70001546:	460d      	mov	r5, r1
70001548:	4602      	mov	r2, r0
7000154a:	460b      	mov	r3, r1
7000154c:	4630      	mov	r0, r6
7000154e:	4639      	mov	r1, r7
70001550:	f000 fcaa 	bl	70001ea8 <__adddf3>
70001554:	4632      	mov	r2, r6
70001556:	4680      	mov	r8, r0
70001558:	4689      	mov	r9, r1
7000155a:	463b      	mov	r3, r7
7000155c:	f000 fca2 	bl	70001ea4 <__aeabi_dsub>
70001560:	4602      	mov	r2, r0
70001562:	460b      	mov	r3, r1
70001564:	4620      	mov	r0, r4
70001566:	4629      	mov	r1, r5
70001568:	f000 fc9c 	bl	70001ea4 <__aeabi_dsub>
7000156c:	4642      	mov	r2, r8
7000156e:	4606      	mov	r6, r0
70001570:	460f      	mov	r7, r1
70001572:	464b      	mov	r3, r9
70001574:	4640      	mov	r0, r8
70001576:	4649      	mov	r1, r9
70001578:	f000 fe4c 	bl	70002214 <__aeabi_dmul>
7000157c:	4604      	mov	r4, r0
7000157e:	460d      	mov	r5, r1
70001580:	a35b      	add	r3, pc, #364	; (adr r3, 700016f0 <__ieee754_pow+0x9e0>)
70001582:	e9d3 2300 	ldrd	r2, r3, [r3]
70001586:	f000 fe45 	bl	70002214 <__aeabi_dmul>
7000158a:	a35b      	add	r3, pc, #364	; (adr r3, 700016f8 <__ieee754_pow+0x9e8>)
7000158c:	e9d3 2300 	ldrd	r2, r3, [r3]
70001590:	f000 fc88 	bl	70001ea4 <__aeabi_dsub>
70001594:	4622      	mov	r2, r4
70001596:	462b      	mov	r3, r5
70001598:	f000 fe3c 	bl	70002214 <__aeabi_dmul>
7000159c:	a358      	add	r3, pc, #352	; (adr r3, 70001700 <__ieee754_pow+0x9f0>)
7000159e:	e9d3 2300 	ldrd	r2, r3, [r3]
700015a2:	f000 fc81 	bl	70001ea8 <__adddf3>
700015a6:	4622      	mov	r2, r4
700015a8:	462b      	mov	r3, r5
700015aa:	f000 fe33 	bl	70002214 <__aeabi_dmul>
700015ae:	a356      	add	r3, pc, #344	; (adr r3, 70001708 <__ieee754_pow+0x9f8>)
700015b0:	e9d3 2300 	ldrd	r2, r3, [r3]
700015b4:	f000 fc76 	bl	70001ea4 <__aeabi_dsub>
700015b8:	4622      	mov	r2, r4
700015ba:	462b      	mov	r3, r5
700015bc:	f000 fe2a 	bl	70002214 <__aeabi_dmul>
700015c0:	a353      	add	r3, pc, #332	; (adr r3, 70001710 <__ieee754_pow+0xa00>)
700015c2:	e9d3 2300 	ldrd	r2, r3, [r3]
700015c6:	f000 fc6f 	bl	70001ea8 <__adddf3>
700015ca:	4622      	mov	r2, r4
700015cc:	462b      	mov	r3, r5
700015ce:	f000 fe21 	bl	70002214 <__aeabi_dmul>
700015d2:	4602      	mov	r2, r0
700015d4:	460b      	mov	r3, r1
700015d6:	4640      	mov	r0, r8
700015d8:	4649      	mov	r1, r9
700015da:	f000 fc63 	bl	70001ea4 <__aeabi_dsub>
700015de:	4604      	mov	r4, r0
700015e0:	460d      	mov	r5, r1
700015e2:	4602      	mov	r2, r0
700015e4:	460b      	mov	r3, r1
700015e6:	4640      	mov	r0, r8
700015e8:	4649      	mov	r1, r9
700015ea:	f000 fe13 	bl	70002214 <__aeabi_dmul>
700015ee:	2200      	movs	r2, #0
700015f0:	f04f 4380 	mov.w	r3, #1073741824	; 0x40000000
700015f4:	e9cd 0102 	strd	r0, r1, [sp, #8]
700015f8:	4620      	mov	r0, r4
700015fa:	4629      	mov	r1, r5
700015fc:	f000 fc52 	bl	70001ea4 <__aeabi_dsub>
70001600:	4602      	mov	r2, r0
70001602:	460b      	mov	r3, r1
70001604:	e9dd 0102 	ldrd	r0, r1, [sp, #8]
70001608:	f000 ff2e 	bl	70002468 <__aeabi_ddiv>
7000160c:	4632      	mov	r2, r6
7000160e:	4604      	mov	r4, r0
70001610:	460d      	mov	r5, r1
70001612:	463b      	mov	r3, r7
70001614:	4640      	mov	r0, r8
70001616:	4649      	mov	r1, r9
70001618:	f000 fdfc 	bl	70002214 <__aeabi_dmul>
7000161c:	4632      	mov	r2, r6
7000161e:	463b      	mov	r3, r7
70001620:	f000 fc42 	bl	70001ea8 <__adddf3>
70001624:	4602      	mov	r2, r0
70001626:	460b      	mov	r3, r1
70001628:	4620      	mov	r0, r4
7000162a:	4629      	mov	r1, r5
7000162c:	f000 fc3a 	bl	70001ea4 <__aeabi_dsub>
70001630:	4642      	mov	r2, r8
70001632:	464b      	mov	r3, r9
70001634:	f000 fc36 	bl	70001ea4 <__aeabi_dsub>
70001638:	4602      	mov	r2, r0
7000163a:	460b      	mov	r3, r1
7000163c:	2000      	movs	r0, #0
7000163e:	4938      	ldr	r1, [pc, #224]	; (70001720 <__ieee754_pow+0xa10>)
70001640:	f000 fc30 	bl	70001ea4 <__aeabi_dsub>
70001644:	eb01 540a 	add.w	r4, r1, sl, lsl #20
70001648:	f5b4 1f80 	cmp.w	r4, #1048576	; 0x100000
7000164c:	da28      	bge.n	700016a0 <__ieee754_pow+0x990>
7000164e:	4652      	mov	r2, sl
70001650:	f000 f9c2 	bl	700019d8 <scalbn>
70001654:	e9dd 2300 	ldrd	r2, r3, [sp]
70001658:	e403      	b.n	70000e62 <__ieee754_pow+0x152>
7000165a:	f021 4700 	bic.w	r7, r1, #2147483648	; 0x80000000
7000165e:	4b31      	ldr	r3, [pc, #196]	; (70001724 <__ieee754_pow+0xa14>)
70001660:	429f      	cmp	r7, r3
70001662:	f77f af13 	ble.w	7000148c <__ieee754_pow+0x77c>
70001666:	4b30      	ldr	r3, [pc, #192]	; (70001728 <__ieee754_pow+0xa18>)
70001668:	440b      	add	r3, r1
7000166a:	4303      	orrs	r3, r0
7000166c:	d009      	beq.n	70001682 <__ieee754_pow+0x972>
7000166e:	2200      	movs	r2, #0
70001670:	2300      	movs	r3, #0
70001672:	e9dd 0100 	ldrd	r0, r1, [sp]
70001676:	f001 f83f 	bl	700026f8 <__aeabi_dcmplt>
7000167a:	3800      	subs	r0, #0
7000167c:	bf18      	it	ne
7000167e:	2001      	movne	r0, #1
70001680:	e459      	b.n	70000f36 <__ieee754_pow+0x226>
70001682:	4622      	mov	r2, r4
70001684:	462b      	mov	r3, r5
70001686:	f000 fc0d 	bl	70001ea4 <__aeabi_dsub>
7000168a:	4642      	mov	r2, r8
7000168c:	464b      	mov	r3, r9
7000168e:	f001 f847 	bl	70002720 <__aeabi_dcmpge>
70001692:	2800      	cmp	r0, #0
70001694:	f43f aefa 	beq.w	7000148c <__ieee754_pow+0x77c>
70001698:	e7e9      	b.n	7000166e <__ieee754_pow+0x95e>
7000169a:	f04f 0a00 	mov.w	sl, #0
7000169e:	e721      	b.n	700014e4 <__ieee754_pow+0x7d4>
700016a0:	4621      	mov	r1, r4
700016a2:	e7d7      	b.n	70001654 <__ieee754_pow+0x944>
700016a4:	f04f 0b00 	mov.w	fp, #0
700016a8:	f8df c074 	ldr.w	ip, [pc, #116]	; 70001720 <__ieee754_pow+0xa10>
700016ac:	f7ff bbc0 	b.w	70000e30 <__ieee754_pow+0x120>
700016b0:	f04f 0b00 	mov.w	fp, #0
700016b4:	f04f 0c00 	mov.w	ip, #0
700016b8:	f7ff bbba 	b.w	70000e30 <__ieee754_pow+0x120>
700016bc:	4640      	mov	r0, r8
700016be:	4649      	mov	r1, r9
700016c0:	f7ff bb43 	b.w	70000d4a <__ieee754_pow+0x3a>
700016c4:	9200      	str	r2, [sp, #0]
700016c6:	f7ff bb8f 	b.w	70000de8 <__ieee754_pow+0xd8>
700016ca:	2300      	movs	r3, #0
700016cc:	f7ff bb79 	b.w	70000dc2 <__ieee754_pow+0xb2>
700016d0:	652b82fe 	.word	0x652b82fe
700016d4:	3c971547 	.word	0x3c971547
700016d8:	00000000 	.word	0x00000000
700016dc:	3fe62e43 	.word	0x3fe62e43
700016e0:	fefa39ef 	.word	0xfefa39ef
700016e4:	3fe62e42 	.word	0x3fe62e42
700016e8:	0ca86c39 	.word	0x0ca86c39
700016ec:	be205c61 	.word	0xbe205c61
700016f0:	72bea4d0 	.word	0x72bea4d0
700016f4:	3e663769 	.word	0x3e663769
700016f8:	c5d26bf1 	.word	0xc5d26bf1
700016fc:	3ebbbd41 	.word	0x3ebbbd41
70001700:	af25de2c 	.word	0xaf25de2c
70001704:	3f11566a 	.word	0x3f11566a
70001708:	16bebd93 	.word	0x16bebd93
7000170c:	3f66c16c 	.word	0x3f66c16c
70001710:	5555553e 	.word	0x5555553e
70001714:	3fc55555 	.word	0x3fc55555
70001718:	3fe00000 	.word	0x3fe00000
7000171c:	000fffff 	.word	0x000fffff
70001720:	3ff00000 	.word	0x3ff00000
70001724:	4090cbff 	.word	0x4090cbff
70001728:	3f6f3400 	.word	0x3f6f3400

7000172c <__ieee754_sqrt>:
7000172c:	f8df c160 	ldr.w	ip, [pc, #352]	; 70001890 <__ieee754_sqrt+0x164>
70001730:	460a      	mov	r2, r1
70001732:	4603      	mov	r3, r0
70001734:	ea3c 0c01 	bics.w	ip, ip, r1
70001738:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
7000173c:	4606      	mov	r6, r0
7000173e:	460d      	mov	r5, r1
70001740:	460c      	mov	r4, r1
70001742:	4607      	mov	r7, r0
70001744:	d10f      	bne.n	70001766 <__ieee754_sqrt+0x3a>
70001746:	4602      	mov	r2, r0
70001748:	460b      	mov	r3, r1
7000174a:	f000 fd63 	bl	70002214 <__aeabi_dmul>
7000174e:	4602      	mov	r2, r0
70001750:	460b      	mov	r3, r1
70001752:	4630      	mov	r0, r6
70001754:	4629      	mov	r1, r5
70001756:	f000 fba7 	bl	70001ea8 <__adddf3>
7000175a:	4606      	mov	r6, r0
7000175c:	460d      	mov	r5, r1
7000175e:	4630      	mov	r0, r6
70001760:	4629      	mov	r1, r5
70001762:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
70001766:	2900      	cmp	r1, #0
70001768:	dc0e      	bgt.n	70001788 <__ieee754_sqrt+0x5c>
7000176a:	f021 4c00 	bic.w	ip, r1, #2147483648	; 0x80000000
7000176e:	ea5c 0707 	orrs.w	r7, ip, r7
70001772:	d0f4      	beq.n	7000175e <__ieee754_sqrt+0x32>
70001774:	b141      	cbz	r1, 70001788 <__ieee754_sqrt+0x5c>
70001776:	4602      	mov	r2, r0
70001778:	460b      	mov	r3, r1
7000177a:	f000 fb93 	bl	70001ea4 <__aeabi_dsub>
7000177e:	4602      	mov	r2, r0
70001780:	460b      	mov	r3, r1
70001782:	f000 fe71 	bl	70002468 <__aeabi_ddiv>
70001786:	e7e8      	b.n	7000175a <__ieee754_sqrt+0x2e>
70001788:	1521      	asrs	r1, r4, #20
7000178a:	d07a      	beq.n	70001882 <__ieee754_sqrt+0x156>
7000178c:	07cc      	lsls	r4, r1, #31
7000178e:	f3c2 0213 	ubfx	r2, r2, #0, #20
70001792:	f2a1 37ff 	subw	r7, r1, #1023	; 0x3ff
70001796:	f04f 0400 	mov.w	r4, #0
7000179a:	bf58      	it	pl
7000179c:	0fd9      	lsrpl	r1, r3, #31
7000179e:	f442 1280 	orr.w	r2, r2, #1048576	; 0x100000
700017a2:	bf58      	it	pl
700017a4:	005b      	lslpl	r3, r3, #1
700017a6:	f04f 0516 	mov.w	r5, #22
700017aa:	bf58      	it	pl
700017ac:	eb01 0242 	addpl.w	r2, r1, r2, lsl #1
700017b0:	4620      	mov	r0, r4
700017b2:	0fd9      	lsrs	r1, r3, #31
700017b4:	107f      	asrs	r7, r7, #1
700017b6:	eb01 0242 	add.w	r2, r1, r2, lsl #1
700017ba:	f44f 1100 	mov.w	r1, #2097152	; 0x200000
700017be:	005b      	lsls	r3, r3, #1
700017c0:	1846      	adds	r6, r0, r1
700017c2:	4296      	cmp	r6, r2
700017c4:	bfde      	ittt	le
700017c6:	1b92      	suble	r2, r2, r6
700017c8:	1870      	addle	r0, r6, r1
700017ca:	1864      	addle	r4, r4, r1
700017cc:	3d01      	subs	r5, #1
700017ce:	ea4f 0242 	mov.w	r2, r2, lsl #1
700017d2:	ea4f 0151 	mov.w	r1, r1, lsr #1
700017d6:	eb02 72d3 	add.w	r2, r2, r3, lsr #31
700017da:	ea4f 0343 	mov.w	r3, r3, lsl #1
700017de:	d1ef      	bne.n	700017c0 <__ieee754_sqrt+0x94>
700017e0:	4629      	mov	r1, r5
700017e2:	f04f 0e20 	mov.w	lr, #32
700017e6:	f04f 4600 	mov.w	r6, #2147483648	; 0x80000000
700017ea:	4282      	cmp	r2, r0
700017ec:	eb06 0c05 	add.w	ip, r6, r5
700017f0:	dc02      	bgt.n	700017f8 <__ieee754_sqrt+0xcc>
700017f2:	d113      	bne.n	7000181c <__ieee754_sqrt+0xf0>
700017f4:	459c      	cmp	ip, r3
700017f6:	d811      	bhi.n	7000181c <__ieee754_sqrt+0xf0>
700017f8:	f1bc 0f00 	cmp.w	ip, #0
700017fc:	eb0c 0506 	add.w	r5, ip, r6
70001800:	da44      	bge.n	7000188c <__ieee754_sqrt+0x160>
70001802:	2d00      	cmp	r5, #0
70001804:	db42      	blt.n	7000188c <__ieee754_sqrt+0x160>
70001806:	f100 0801 	add.w	r8, r0, #1
7000180a:	1a12      	subs	r2, r2, r0
7000180c:	459c      	cmp	ip, r3
7000180e:	4431      	add	r1, r6
70001810:	eba3 030c 	sub.w	r3, r3, ip
70001814:	bf88      	it	hi
70001816:	f102 32ff 	addhi.w	r2, r2, #4294967295
7000181a:	4640      	mov	r0, r8
7000181c:	ea4f 7cd3 	mov.w	ip, r3, lsr #31
70001820:	f1be 0e01 	subs.w	lr, lr, #1
70001824:	ea4f 0343 	mov.w	r3, r3, lsl #1
70001828:	eb0c 0242 	add.w	r2, ip, r2, lsl #1
7000182c:	ea4f 0656 	mov.w	r6, r6, lsr #1
70001830:	d1db      	bne.n	700017ea <__ieee754_sqrt+0xbe>
70001832:	4313      	orrs	r3, r2
70001834:	d006      	beq.n	70001844 <__ieee754_sqrt+0x118>
70001836:	1c48      	adds	r0, r1, #1
70001838:	bf13      	iteet	ne
7000183a:	3101      	addne	r1, #1
7000183c:	3401      	addeq	r4, #1
7000183e:	4671      	moveq	r1, lr
70001840:	f021 0101 	bicne.w	r1, r1, #1
70001844:	1063      	asrs	r3, r4, #1
70001846:	07e2      	lsls	r2, r4, #31
70001848:	ea4f 0151 	mov.w	r1, r1, lsr #1
7000184c:	f103 537f 	add.w	r3, r3, #1069547520	; 0x3fc00000
70001850:	bf48      	it	mi
70001852:	f041 4100 	orrmi.w	r1, r1, #2147483648	; 0x80000000
70001856:	f503 1300 	add.w	r3, r3, #2097152	; 0x200000
7000185a:	460e      	mov	r6, r1
7000185c:	eb03 5507 	add.w	r5, r3, r7, lsl #20
70001860:	e77d      	b.n	7000175e <__ieee754_sqrt+0x32>
70001862:	0ada      	lsrs	r2, r3, #11
70001864:	3815      	subs	r0, #21
70001866:	055b      	lsls	r3, r3, #21
70001868:	2a00      	cmp	r2, #0
7000186a:	d0fa      	beq.n	70001862 <__ieee754_sqrt+0x136>
7000186c:	02d5      	lsls	r5, r2, #11
7000186e:	d50a      	bpl.n	70001886 <__ieee754_sqrt+0x15a>
70001870:	f1c1 0420 	rsb	r4, r1, #32
70001874:	1e4d      	subs	r5, r1, #1
70001876:	fa23 f404 	lsr.w	r4, r3, r4
7000187a:	408b      	lsls	r3, r1
7000187c:	1b41      	subs	r1, r0, r5
7000187e:	4322      	orrs	r2, r4
70001880:	e784      	b.n	7000178c <__ieee754_sqrt+0x60>
70001882:	4608      	mov	r0, r1
70001884:	e7f0      	b.n	70001868 <__ieee754_sqrt+0x13c>
70001886:	0052      	lsls	r2, r2, #1
70001888:	3101      	adds	r1, #1
7000188a:	e7ef      	b.n	7000186c <__ieee754_sqrt+0x140>
7000188c:	4680      	mov	r8, r0
7000188e:	e7bc      	b.n	7000180a <__ieee754_sqrt+0xde>
70001890:	7ff00000 	.word	0x7ff00000

70001894 <with_errno>:
70001894:	b570      	push	{r4, r5, r6, lr}
70001896:	4604      	mov	r4, r0
70001898:	460d      	mov	r5, r1
7000189a:	4616      	mov	r6, r2
7000189c:	f000 f91a 	bl	70001ad4 <__errno>
700018a0:	4629      	mov	r1, r5
700018a2:	6006      	str	r6, [r0, #0]
700018a4:	4620      	mov	r0, r4
700018a6:	bd70      	pop	{r4, r5, r6, pc}

700018a8 <xflow>:
700018a8:	b537      	push	{r0, r1, r2, r4, r5, lr}
700018aa:	4615      	mov	r5, r2
700018ac:	461c      	mov	r4, r3
700018ae:	b178      	cbz	r0, 700018d0 <xflow+0x28>
700018b0:	4610      	mov	r0, r2
700018b2:	f103 4100 	add.w	r1, r3, #2147483648	; 0x80000000
700018b6:	e9cd 0100 	strd	r0, r1, [sp]
700018ba:	e9dd 2300 	ldrd	r2, r3, [sp]
700018be:	4628      	mov	r0, r5
700018c0:	4621      	mov	r1, r4
700018c2:	f000 fca7 	bl	70002214 <__aeabi_dmul>
700018c6:	2222      	movs	r2, #34	; 0x22
700018c8:	b003      	add	sp, #12
700018ca:	e8bd 4030 	ldmia.w	sp!, {r4, r5, lr}
700018ce:	e7e1      	b.n	70001894 <with_errno>
700018d0:	4610      	mov	r0, r2
700018d2:	4619      	mov	r1, r3
700018d4:	e7ef      	b.n	700018b6 <xflow+0xe>

700018d6 <__math_uflow>:
700018d6:	2200      	movs	r2, #0
700018d8:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
700018dc:	e7e4      	b.n	700018a8 <xflow>

700018de <__math_may_uflow>:
700018de:	2200      	movs	r2, #0
700018e0:	4b00      	ldr	r3, [pc, #0]	; (700018e4 <__math_may_uflow+0x6>)
700018e2:	e7e1      	b.n	700018a8 <xflow>
700018e4:	1e580000 	.word	0x1e580000

700018e8 <__math_oflow>:
700018e8:	2200      	movs	r2, #0
700018ea:	f04f 43e0 	mov.w	r3, #1879048192	; 0x70000000
700018ee:	e7db      	b.n	700018a8 <xflow>

700018f0 <__math_divzero>:
700018f0:	b507      	push	{r0, r1, r2, lr}
700018f2:	2200      	movs	r2, #0
700018f4:	b968      	cbnz	r0, 70001912 <__math_divzero+0x22>
700018f6:	4b08      	ldr	r3, [pc, #32]	; (70001918 <__math_divzero+0x28>)
700018f8:	e9cd 2300 	strd	r2, r3, [sp]
700018fc:	e9dd 0100 	ldrd	r0, r1, [sp]
70001900:	2200      	movs	r2, #0
70001902:	2300      	movs	r3, #0
70001904:	f000 fdb0 	bl	70002468 <__aeabi_ddiv>
70001908:	2222      	movs	r2, #34	; 0x22
7000190a:	b003      	add	sp, #12
7000190c:	f85d eb04 	ldr.w	lr, [sp], #4
70001910:	e7c0      	b.n	70001894 <with_errno>
70001912:	4b02      	ldr	r3, [pc, #8]	; (7000191c <__math_divzero+0x2c>)
70001914:	e7f0      	b.n	700018f8 <__math_divzero+0x8>
70001916:	bf00      	nop
70001918:	3ff00000 	.word	0x3ff00000
7000191c:	bff00000 	.word	0xbff00000

70001920 <__math_invalid>:
70001920:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
70001922:	4602      	mov	r2, r0
70001924:	4606      	mov	r6, r0
70001926:	460f      	mov	r7, r1
70001928:	460b      	mov	r3, r1
7000192a:	f000 fabb 	bl	70001ea4 <__aeabi_dsub>
7000192e:	4602      	mov	r2, r0
70001930:	460b      	mov	r3, r1
70001932:	f000 fd99 	bl	70002468 <__aeabi_ddiv>
70001936:	4632      	mov	r2, r6
70001938:	4604      	mov	r4, r0
7000193a:	460d      	mov	r5, r1
7000193c:	463b      	mov	r3, r7
7000193e:	4630      	mov	r0, r6
70001940:	4639      	mov	r1, r7
70001942:	f000 ff01 	bl	70002748 <__aeabi_dcmpun>
70001946:	b928      	cbnz	r0, 70001954 <__math_invalid+0x34>
70001948:	4620      	mov	r0, r4
7000194a:	4629      	mov	r1, r5
7000194c:	2221      	movs	r2, #33	; 0x21
7000194e:	e8bd 40f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, lr}
70001952:	e79f      	b.n	70001894 <with_errno>
70001954:	4620      	mov	r0, r4
70001956:	4629      	mov	r1, r5
70001958:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}

7000195a <__math_check_uflow>:
7000195a:	b538      	push	{r3, r4, r5, lr}
7000195c:	2200      	movs	r2, #0
7000195e:	2300      	movs	r3, #0
70001960:	4604      	mov	r4, r0
70001962:	460d      	mov	r5, r1
70001964:	f000 febe 	bl	700026e4 <__aeabi_dcmpeq>
70001968:	b128      	cbz	r0, 70001976 <__math_check_uflow+0x1c>
7000196a:	4620      	mov	r0, r4
7000196c:	4629      	mov	r1, r5
7000196e:	2222      	movs	r2, #34	; 0x22
70001970:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
70001974:	e78e      	b.n	70001894 <with_errno>
70001976:	4620      	mov	r0, r4
70001978:	4629      	mov	r1, r5
7000197a:	bd38      	pop	{r3, r4, r5, pc}

7000197c <__math_check_oflow>:
7000197c:	b570      	push	{r4, r5, r6, lr}
7000197e:	4604      	mov	r4, r0
70001980:	f021 4600 	bic.w	r6, r1, #2147483648	; 0x80000000
70001984:	460d      	mov	r5, r1
70001986:	f04f 32ff 	mov.w	r2, #4294967295
7000198a:	4b0b      	ldr	r3, [pc, #44]	; (700019b8 <__math_check_oflow+0x3c>)
7000198c:	4620      	mov	r0, r4
7000198e:	4631      	mov	r1, r6
70001990:	f000 feda 	bl	70002748 <__aeabi_dcmpun>
70001994:	b968      	cbnz	r0, 700019b2 <__math_check_oflow+0x36>
70001996:	f04f 32ff 	mov.w	r2, #4294967295
7000199a:	4b07      	ldr	r3, [pc, #28]	; (700019b8 <__math_check_oflow+0x3c>)
7000199c:	4620      	mov	r0, r4
7000199e:	4631      	mov	r1, r6
700019a0:	f000 feb4 	bl	7000270c <__aeabi_dcmple>
700019a4:	b928      	cbnz	r0, 700019b2 <__math_check_oflow+0x36>
700019a6:	4620      	mov	r0, r4
700019a8:	4629      	mov	r1, r5
700019aa:	2222      	movs	r2, #34	; 0x22
700019ac:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
700019b0:	e770      	b.n	70001894 <with_errno>
700019b2:	4620      	mov	r0, r4
700019b4:	4629      	mov	r1, r5
700019b6:	bd70      	pop	{r4, r5, r6, pc}
700019b8:	7fefffff 	.word	0x7fefffff

700019bc <fabs>:
700019bc:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
700019c0:	4770      	bx	lr

700019c2 <finite>:
700019c2:	f041 4000 	orr.w	r0, r1, #2147483648	; 0x80000000
700019c6:	f500 1080 	add.w	r0, r0, #1048576	; 0x100000
700019ca:	0fc0      	lsrs	r0, r0, #31
700019cc:	4770      	bx	lr
	...

700019d0 <nanf>:
700019d0:	4800      	ldr	r0, [pc, #0]	; (700019d4 <nanf+0x4>)
700019d2:	4770      	bx	lr
700019d4:	7fc00000 	.word	0x7fc00000

700019d8 <scalbn>:
700019d8:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
700019da:	f3c1 560a 	ubfx	r6, r1, #20, #11
700019de:	4604      	mov	r4, r0
700019e0:	460d      	mov	r5, r1
700019e2:	4617      	mov	r7, r2
700019e4:	460b      	mov	r3, r1
700019e6:	b996      	cbnz	r6, 70001a0e <scalbn+0x36>
700019e8:	f021 4300 	bic.w	r3, r1, #2147483648	; 0x80000000
700019ec:	4303      	orrs	r3, r0
700019ee:	d039      	beq.n	70001a64 <scalbn+0x8c>
700019f0:	4b33      	ldr	r3, [pc, #204]	; (70001ac0 <scalbn+0xe8>)
700019f2:	2200      	movs	r2, #0
700019f4:	f000 fc0e 	bl	70002214 <__aeabi_dmul>
700019f8:	4b32      	ldr	r3, [pc, #200]	; (70001ac4 <scalbn+0xec>)
700019fa:	4604      	mov	r4, r0
700019fc:	460d      	mov	r5, r1
700019fe:	429f      	cmp	r7, r3
70001a00:	da0f      	bge.n	70001a22 <scalbn+0x4a>
70001a02:	a32b      	add	r3, pc, #172	; (adr r3, 70001ab0 <scalbn+0xd8>)
70001a04:	e9d3 2300 	ldrd	r2, r3, [r3]
70001a08:	f000 fc04 	bl	70002214 <__aeabi_dmul>
70001a0c:	e006      	b.n	70001a1c <scalbn+0x44>
70001a0e:	f240 72ff 	movw	r2, #2047	; 0x7ff
70001a12:	4296      	cmp	r6, r2
70001a14:	d10a      	bne.n	70001a2c <scalbn+0x54>
70001a16:	4602      	mov	r2, r0
70001a18:	f000 fa46 	bl	70001ea8 <__adddf3>
70001a1c:	4604      	mov	r4, r0
70001a1e:	460d      	mov	r5, r1
70001a20:	e020      	b.n	70001a64 <scalbn+0x8c>
70001a22:	460b      	mov	r3, r1
70001a24:	f3c1 510a 	ubfx	r1, r1, #20, #11
70001a28:	f1a1 0636 	sub.w	r6, r1, #54	; 0x36
70001a2c:	19b9      	adds	r1, r7, r6
70001a2e:	f240 72fe 	movw	r2, #2046	; 0x7fe
70001a32:	4291      	cmp	r1, r2
70001a34:	dd0e      	ble.n	70001a54 <scalbn+0x7c>
70001a36:	f005 4400 	and.w	r4, r5, #2147483648	; 0x80000000
70001a3a:	f044 41fc 	orr.w	r1, r4, #2113929216	; 0x7e000000
70001a3e:	4822      	ldr	r0, [pc, #136]	; (70001ac8 <scalbn+0xf0>)
70001a40:	f441 115f 	orr.w	r1, r1, #3653632	; 0x37c000
70001a44:	f441 5110 	orr.w	r1, r1, #9216	; 0x2400
70001a48:	a31b      	add	r3, pc, #108	; (adr r3, 70001ab8 <scalbn+0xe0>)
70001a4a:	e9d3 2300 	ldrd	r2, r3, [r3]
70001a4e:	f041 013c 	orr.w	r1, r1, #60	; 0x3c
70001a52:	e7d9      	b.n	70001a08 <scalbn+0x30>
70001a54:	2900      	cmp	r1, #0
70001a56:	dd08      	ble.n	70001a6a <scalbn+0x92>
70001a58:	f023 43ff 	bic.w	r3, r3, #2139095040	; 0x7f800000
70001a5c:	f423 03e0 	bic.w	r3, r3, #7340032	; 0x700000
70001a60:	ea43 5501 	orr.w	r5, r3, r1, lsl #20
70001a64:	4620      	mov	r0, r4
70001a66:	4629      	mov	r1, r5
70001a68:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
70001a6a:	f111 0f35 	cmn.w	r1, #53	; 0x35
70001a6e:	da12      	bge.n	70001a96 <scalbn+0xbe>
70001a70:	f24c 3350 	movw	r3, #50000	; 0xc350
70001a74:	429f      	cmp	r7, r3
70001a76:	ea4f 73d5 	mov.w	r3, r5, lsr #31
70001a7a:	ea4f 74c3 	mov.w	r4, r3, lsl #31
70001a7e:	dcdc      	bgt.n	70001a3a <scalbn+0x62>
70001a80:	f044 71d2 	orr.w	r1, r4, #27525120	; 0x1a40000
70001a84:	4811      	ldr	r0, [pc, #68]	; (70001acc <scalbn+0xf4>)
70001a86:	f441 31b7 	orr.w	r1, r1, #93696	; 0x16e00
70001a8a:	a309      	add	r3, pc, #36	; (adr r3, 70001ab0 <scalbn+0xd8>)
70001a8c:	e9d3 2300 	ldrd	r2, r3, [r3]
70001a90:	f041 011f 	orr.w	r1, r1, #31
70001a94:	e7b8      	b.n	70001a08 <scalbn+0x30>
70001a96:	f023 43ff 	bic.w	r3, r3, #2139095040	; 0x7f800000
70001a9a:	3136      	adds	r1, #54	; 0x36
70001a9c:	4620      	mov	r0, r4
70001a9e:	2200      	movs	r2, #0
70001aa0:	f423 03e0 	bic.w	r3, r3, #7340032	; 0x700000
70001aa4:	ea43 5501 	orr.w	r5, r3, r1, lsl #20
70001aa8:	4b09      	ldr	r3, [pc, #36]	; (70001ad0 <scalbn+0xf8>)
70001aaa:	4629      	mov	r1, r5
70001aac:	e7ac      	b.n	70001a08 <scalbn+0x30>
70001aae:	bf00      	nop
70001ab0:	c2f8f359 	.word	0xc2f8f359
70001ab4:	01a56e1f 	.word	0x01a56e1f
70001ab8:	8800759c 	.word	0x8800759c
70001abc:	7e37e43c 	.word	0x7e37e43c
70001ac0:	43500000 	.word	0x43500000
70001ac4:	ffff3cb0 	.word	0xffff3cb0
70001ac8:	8800759c 	.word	0x8800759c
70001acc:	c2f8f359 	.word	0xc2f8f359
70001ad0:	3c900000 	.word	0x3c900000

70001ad4 <__errno>:
70001ad4:	4b01      	ldr	r3, [pc, #4]	; (70001adc <__errno+0x8>)
70001ad6:	6818      	ldr	r0, [r3, #0]
70001ad8:	4770      	bx	lr
70001ada:	bf00      	nop
70001adc:	70002ea0 	.word	0x70002ea0
70001ae0:	b570      	push	{r4, r5, r6, lr}
70001ae2:	f04f 0cff 	mov.w	ip, #255	; 0xff
70001ae6:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
70001aea:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
70001aee:	bf1d      	ittte	ne
70001af0:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
70001af4:	ea94 0f0c 	teqne	r4, ip
70001af8:	ea95 0f0c 	teqne	r5, ip
70001afc:	f000 f8de 	bleq	70001cbc <__errno+0x1e8>
70001b00:	442c      	add	r4, r5
70001b02:	ea81 0603 	eor.w	r6, r1, r3
70001b06:	ea21 514c 	bic.w	r1, r1, ip, lsl #21
70001b0a:	ea23 534c 	bic.w	r3, r3, ip, lsl #21
70001b0e:	ea50 3501 	orrs.w	r5, r0, r1, lsl #12
70001b12:	bf18      	it	ne
70001b14:	ea52 3503 	orrsne.w	r5, r2, r3, lsl #12
70001b18:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70001b1c:	f443 1380 	orr.w	r3, r3, #1048576	; 0x100000
70001b20:	d038      	beq.n	70001b94 <__errno+0xc0>
70001b22:	fba0 ce02 	umull	ip, lr, r0, r2
70001b26:	f04f 0500 	mov.w	r5, #0
70001b2a:	fbe1 e502 	umlal	lr, r5, r1, r2
70001b2e:	f006 4200 	and.w	r2, r6, #2147483648	; 0x80000000
70001b32:	fbe0 e503 	umlal	lr, r5, r0, r3
70001b36:	f04f 0600 	mov.w	r6, #0
70001b3a:	fbe1 5603 	umlal	r5, r6, r1, r3
70001b3e:	f09c 0f00 	teq	ip, #0
70001b42:	bf18      	it	ne
70001b44:	f04e 0e01 	orrne.w	lr, lr, #1
70001b48:	f1a4 04ff 	sub.w	r4, r4, #255	; 0xff
70001b4c:	f5b6 7f00 	cmp.w	r6, #512	; 0x200
70001b50:	f564 7440 	sbc.w	r4, r4, #768	; 0x300
70001b54:	d204      	bcs.n	70001b60 <__errno+0x8c>
70001b56:	ea5f 0e4e 	movs.w	lr, lr, lsl #1
70001b5a:	416d      	adcs	r5, r5
70001b5c:	eb46 0606 	adc.w	r6, r6, r6
70001b60:	ea42 21c6 	orr.w	r1, r2, r6, lsl #11
70001b64:	ea41 5155 	orr.w	r1, r1, r5, lsr #21
70001b68:	ea4f 20c5 	mov.w	r0, r5, lsl #11
70001b6c:	ea40 505e 	orr.w	r0, r0, lr, lsr #21
70001b70:	ea4f 2ece 	mov.w	lr, lr, lsl #11
70001b74:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
70001b78:	bf88      	it	hi
70001b7a:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
70001b7e:	d81e      	bhi.n	70001bbe <__errno+0xea>
70001b80:	f1be 4f00 	cmp.w	lr, #2147483648	; 0x80000000
70001b84:	bf08      	it	eq
70001b86:	ea5f 0e50 	movseq.w	lr, r0, lsr #1
70001b8a:	f150 0000 	adcs.w	r0, r0, #0
70001b8e:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
70001b92:	bd70      	pop	{r4, r5, r6, pc}
70001b94:	f006 4600 	and.w	r6, r6, #2147483648	; 0x80000000
70001b98:	ea46 0101 	orr.w	r1, r6, r1
70001b9c:	ea40 0002 	orr.w	r0, r0, r2
70001ba0:	ea81 0103 	eor.w	r1, r1, r3
70001ba4:	ebb4 045c 	subs.w	r4, r4, ip, lsr #1
70001ba8:	bfc2      	ittt	gt
70001baa:	ebd4 050c 	rsbsgt	r5, r4, ip
70001bae:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
70001bb2:	bd70      	popgt	{r4, r5, r6, pc}
70001bb4:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70001bb8:	f04f 0e00 	mov.w	lr, #0
70001bbc:	3c01      	subs	r4, #1
70001bbe:	f300 80ab 	bgt.w	70001d18 <__errno+0x244>
70001bc2:	f114 0f36 	cmn.w	r4, #54	; 0x36
70001bc6:	bfde      	ittt	le
70001bc8:	2000      	movle	r0, #0
70001bca:	f001 4100 	andle.w	r1, r1, #2147483648	; 0x80000000
70001bce:	bd70      	pople	{r4, r5, r6, pc}
70001bd0:	f1c4 0400 	rsb	r4, r4, #0
70001bd4:	3c20      	subs	r4, #32
70001bd6:	da35      	bge.n	70001c44 <__errno+0x170>
70001bd8:	340c      	adds	r4, #12
70001bda:	dc1b      	bgt.n	70001c14 <__errno+0x140>
70001bdc:	f104 0414 	add.w	r4, r4, #20
70001be0:	f1c4 0520 	rsb	r5, r4, #32
70001be4:	fa00 f305 	lsl.w	r3, r0, r5
70001be8:	fa20 f004 	lsr.w	r0, r0, r4
70001bec:	fa01 f205 	lsl.w	r2, r1, r5
70001bf0:	ea40 0002 	orr.w	r0, r0, r2
70001bf4:	f001 4200 	and.w	r2, r1, #2147483648	; 0x80000000
70001bf8:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
70001bfc:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
70001c00:	fa21 f604 	lsr.w	r6, r1, r4
70001c04:	eb42 0106 	adc.w	r1, r2, r6
70001c08:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70001c0c:	bf08      	it	eq
70001c0e:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70001c12:	bd70      	pop	{r4, r5, r6, pc}
70001c14:	f1c4 040c 	rsb	r4, r4, #12
70001c18:	f1c4 0520 	rsb	r5, r4, #32
70001c1c:	fa00 f304 	lsl.w	r3, r0, r4
70001c20:	fa20 f005 	lsr.w	r0, r0, r5
70001c24:	fa01 f204 	lsl.w	r2, r1, r4
70001c28:	ea40 0002 	orr.w	r0, r0, r2
70001c2c:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70001c30:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
70001c34:	f141 0100 	adc.w	r1, r1, #0
70001c38:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70001c3c:	bf08      	it	eq
70001c3e:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70001c42:	bd70      	pop	{r4, r5, r6, pc}
70001c44:	f1c4 0520 	rsb	r5, r4, #32
70001c48:	fa00 f205 	lsl.w	r2, r0, r5
70001c4c:	ea4e 0e02 	orr.w	lr, lr, r2
70001c50:	fa20 f304 	lsr.w	r3, r0, r4
70001c54:	fa01 f205 	lsl.w	r2, r1, r5
70001c58:	ea43 0302 	orr.w	r3, r3, r2
70001c5c:	fa21 f004 	lsr.w	r0, r1, r4
70001c60:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70001c64:	fa21 f204 	lsr.w	r2, r1, r4
70001c68:	ea20 0002 	bic.w	r0, r0, r2
70001c6c:	eb00 70d3 	add.w	r0, r0, r3, lsr #31
70001c70:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70001c74:	bf08      	it	eq
70001c76:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70001c7a:	bd70      	pop	{r4, r5, r6, pc}
70001c7c:	f094 0f00 	teq	r4, #0
70001c80:	d10f      	bne.n	70001ca2 <__errno+0x1ce>
70001c82:	f001 4600 	and.w	r6, r1, #2147483648	; 0x80000000
70001c86:	0040      	lsls	r0, r0, #1
70001c88:	eb41 0101 	adc.w	r1, r1, r1
70001c8c:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
70001c90:	bf08      	it	eq
70001c92:	3c01      	subeq	r4, #1
70001c94:	d0f7      	beq.n	70001c86 <__errno+0x1b2>
70001c96:	ea41 0106 	orr.w	r1, r1, r6
70001c9a:	f095 0f00 	teq	r5, #0
70001c9e:	bf18      	it	ne
70001ca0:	4770      	bxne	lr
70001ca2:	f003 4600 	and.w	r6, r3, #2147483648	; 0x80000000
70001ca6:	0052      	lsls	r2, r2, #1
70001ca8:	eb43 0303 	adc.w	r3, r3, r3
70001cac:	f413 1f80 	tst.w	r3, #1048576	; 0x100000
70001cb0:	bf08      	it	eq
70001cb2:	3d01      	subeq	r5, #1
70001cb4:	d0f7      	beq.n	70001ca6 <__errno+0x1d2>
70001cb6:	ea43 0306 	orr.w	r3, r3, r6
70001cba:	4770      	bx	lr
70001cbc:	ea94 0f0c 	teq	r4, ip
70001cc0:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
70001cc4:	bf18      	it	ne
70001cc6:	ea95 0f0c 	teqne	r5, ip
70001cca:	d00c      	beq.n	70001ce6 <__errno+0x212>
70001ccc:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
70001cd0:	bf18      	it	ne
70001cd2:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
70001cd6:	d1d1      	bne.n	70001c7c <__errno+0x1a8>
70001cd8:	ea81 0103 	eor.w	r1, r1, r3
70001cdc:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70001ce0:	f04f 0000 	mov.w	r0, #0
70001ce4:	bd70      	pop	{r4, r5, r6, pc}
70001ce6:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
70001cea:	bf06      	itte	eq
70001cec:	4610      	moveq	r0, r2
70001cee:	4619      	moveq	r1, r3
70001cf0:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
70001cf4:	d019      	beq.n	70001d2a <__errno+0x256>
70001cf6:	ea94 0f0c 	teq	r4, ip
70001cfa:	d102      	bne.n	70001d02 <__errno+0x22e>
70001cfc:	ea50 3601 	orrs.w	r6, r0, r1, lsl #12
70001d00:	d113      	bne.n	70001d2a <__errno+0x256>
70001d02:	ea95 0f0c 	teq	r5, ip
70001d06:	d105      	bne.n	70001d14 <__errno+0x240>
70001d08:	ea52 3603 	orrs.w	r6, r2, r3, lsl #12
70001d0c:	bf1c      	itt	ne
70001d0e:	4610      	movne	r0, r2
70001d10:	4619      	movne	r1, r3
70001d12:	d10a      	bne.n	70001d2a <__errno+0x256>
70001d14:	ea81 0103 	eor.w	r1, r1, r3
70001d18:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70001d1c:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
70001d20:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
70001d24:	f04f 0000 	mov.w	r0, #0
70001d28:	bd70      	pop	{r4, r5, r6, pc}
70001d2a:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
70001d2e:	f441 0178 	orr.w	r1, r1, #16252928	; 0xf80000
70001d32:	bd70      	pop	{r4, r5, r6, pc}
70001d34:	f04f 0cff 	mov.w	ip, #255	; 0xff
70001d38:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70001d3c:	bf1e      	ittt	ne
70001d3e:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70001d42:	ea92 0f0c 	teqne	r2, ip
70001d46:	ea93 0f0c 	teqne	r3, ip
70001d4a:	d06f      	beq.n	70001e2c <__errno+0x358>
70001d4c:	441a      	add	r2, r3
70001d4e:	ea80 0c01 	eor.w	ip, r0, r1
70001d52:	0240      	lsls	r0, r0, #9
70001d54:	bf18      	it	ne
70001d56:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70001d5a:	d01e      	beq.n	70001d9a <__errno+0x2c6>
70001d5c:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70001d60:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70001d64:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70001d68:	fba0 3101 	umull	r3, r1, r0, r1
70001d6c:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70001d70:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70001d74:	bf3e      	ittt	cc
70001d76:	0049      	lslcc	r1, r1, #1
70001d78:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70001d7c:	005b      	lslcc	r3, r3, #1
70001d7e:	ea40 0001 	orr.w	r0, r0, r1
70001d82:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70001d86:	2afd      	cmp	r2, #253	; 0xfd
70001d88:	d81d      	bhi.n	70001dc6 <__errno+0x2f2>
70001d8a:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70001d8e:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70001d92:	bf08      	it	eq
70001d94:	f020 0001 	biceq.w	r0, r0, #1
70001d98:	4770      	bx	lr
70001d9a:	f090 0f00 	teq	r0, #0
70001d9e:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70001da2:	bf08      	it	eq
70001da4:	0249      	lsleq	r1, r1, #9
70001da6:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70001daa:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70001dae:	3a7f      	subs	r2, #127	; 0x7f
70001db0:	bfc2      	ittt	gt
70001db2:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70001db6:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70001dba:	4770      	bxgt	lr
70001dbc:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001dc0:	f04f 0300 	mov.w	r3, #0
70001dc4:	3a01      	subs	r2, #1
70001dc6:	dc5d      	bgt.n	70001e84 <__errno+0x3b0>
70001dc8:	f112 0f19 	cmn.w	r2, #25
70001dcc:	bfdc      	itt	le
70001dce:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70001dd2:	4770      	bxle	lr
70001dd4:	f1c2 0200 	rsb	r2, r2, #0
70001dd8:	0041      	lsls	r1, r0, #1
70001dda:	fa21 f102 	lsr.w	r1, r1, r2
70001dde:	f1c2 0220 	rsb	r2, r2, #32
70001de2:	fa00 fc02 	lsl.w	ip, r0, r2
70001de6:	ea5f 0031 	movs.w	r0, r1, rrx
70001dea:	f140 0000 	adc.w	r0, r0, #0
70001dee:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70001df2:	bf08      	it	eq
70001df4:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70001df8:	4770      	bx	lr
70001dfa:	f092 0f00 	teq	r2, #0
70001dfe:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70001e02:	bf02      	ittt	eq
70001e04:	0040      	lsleq	r0, r0, #1
70001e06:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70001e0a:	3a01      	subeq	r2, #1
70001e0c:	d0f9      	beq.n	70001e02 <__errno+0x32e>
70001e0e:	ea40 000c 	orr.w	r0, r0, ip
70001e12:	f093 0f00 	teq	r3, #0
70001e16:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70001e1a:	bf02      	ittt	eq
70001e1c:	0049      	lsleq	r1, r1, #1
70001e1e:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70001e22:	3b01      	subeq	r3, #1
70001e24:	d0f9      	beq.n	70001e1a <__errno+0x346>
70001e26:	ea41 010c 	orr.w	r1, r1, ip
70001e2a:	e78f      	b.n	70001d4c <__errno+0x278>
70001e2c:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70001e30:	ea92 0f0c 	teq	r2, ip
70001e34:	bf18      	it	ne
70001e36:	ea93 0f0c 	teqne	r3, ip
70001e3a:	d00a      	beq.n	70001e52 <__errno+0x37e>
70001e3c:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70001e40:	bf18      	it	ne
70001e42:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70001e46:	d1d8      	bne.n	70001dfa <__errno+0x326>
70001e48:	ea80 0001 	eor.w	r0, r0, r1
70001e4c:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70001e50:	4770      	bx	lr
70001e52:	f090 0f00 	teq	r0, #0
70001e56:	bf17      	itett	ne
70001e58:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70001e5c:	4608      	moveq	r0, r1
70001e5e:	f091 0f00 	teqne	r1, #0
70001e62:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70001e66:	d014      	beq.n	70001e92 <__errno+0x3be>
70001e68:	ea92 0f0c 	teq	r2, ip
70001e6c:	d101      	bne.n	70001e72 <__errno+0x39e>
70001e6e:	0242      	lsls	r2, r0, #9
70001e70:	d10f      	bne.n	70001e92 <__errno+0x3be>
70001e72:	ea93 0f0c 	teq	r3, ip
70001e76:	d103      	bne.n	70001e80 <__errno+0x3ac>
70001e78:	024b      	lsls	r3, r1, #9
70001e7a:	bf18      	it	ne
70001e7c:	4608      	movne	r0, r1
70001e7e:	d108      	bne.n	70001e92 <__errno+0x3be>
70001e80:	ea80 0001 	eor.w	r0, r0, r1
70001e84:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70001e88:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70001e8c:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001e90:	4770      	bx	lr
70001e92:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70001e96:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70001e9a:	4770      	bx	lr

70001e9c <__aeabi_drsub>:
70001e9c:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000
70001ea0:	e002      	b.n	70001ea8 <__adddf3>
70001ea2:	bf00      	nop

70001ea4 <__aeabi_dsub>:
70001ea4:	f083 4300 	eor.w	r3, r3, #2147483648	; 0x80000000

70001ea8 <__adddf3>:
70001ea8:	b530      	push	{r4, r5, lr}
70001eaa:	ea4f 0441 	mov.w	r4, r1, lsl #1
70001eae:	ea4f 0543 	mov.w	r5, r3, lsl #1
70001eb2:	ea94 0f05 	teq	r4, r5
70001eb6:	bf08      	it	eq
70001eb8:	ea90 0f02 	teqeq	r0, r2
70001ebc:	bf1f      	itttt	ne
70001ebe:	ea54 0c00 	orrsne.w	ip, r4, r0
70001ec2:	ea55 0c02 	orrsne.w	ip, r5, r2
70001ec6:	ea7f 5c64 	mvnsne.w	ip, r4, asr #21
70001eca:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70001ece:	f000 80e2 	beq.w	70002096 <__adddf3+0x1ee>
70001ed2:	ea4f 5454 	mov.w	r4, r4, lsr #21
70001ed6:	ebd4 5555 	rsbs	r5, r4, r5, lsr #21
70001eda:	bfb8      	it	lt
70001edc:	426d      	neglt	r5, r5
70001ede:	dd0c      	ble.n	70001efa <__adddf3+0x52>
70001ee0:	442c      	add	r4, r5
70001ee2:	ea80 0202 	eor.w	r2, r0, r2
70001ee6:	ea81 0303 	eor.w	r3, r1, r3
70001eea:	ea82 0000 	eor.w	r0, r2, r0
70001eee:	ea83 0101 	eor.w	r1, r3, r1
70001ef2:	ea80 0202 	eor.w	r2, r0, r2
70001ef6:	ea81 0303 	eor.w	r3, r1, r3
70001efa:	2d36      	cmp	r5, #54	; 0x36
70001efc:	bf88      	it	hi
70001efe:	bd30      	pophi	{r4, r5, pc}
70001f00:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70001f04:	ea4f 3101 	mov.w	r1, r1, lsl #12
70001f08:	f44f 1c80 	mov.w	ip, #1048576	; 0x100000
70001f0c:	ea4c 3111 	orr.w	r1, ip, r1, lsr #12
70001f10:	d002      	beq.n	70001f18 <__adddf3+0x70>
70001f12:	4240      	negs	r0, r0
70001f14:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70001f18:	f013 4f00 	tst.w	r3, #2147483648	; 0x80000000
70001f1c:	ea4f 3303 	mov.w	r3, r3, lsl #12
70001f20:	ea4c 3313 	orr.w	r3, ip, r3, lsr #12
70001f24:	d002      	beq.n	70001f2c <__adddf3+0x84>
70001f26:	4252      	negs	r2, r2
70001f28:	eb63 0343 	sbc.w	r3, r3, r3, lsl #1
70001f2c:	ea94 0f05 	teq	r4, r5
70001f30:	f000 80a7 	beq.w	70002082 <__adddf3+0x1da>
70001f34:	f1a4 0401 	sub.w	r4, r4, #1
70001f38:	f1d5 0e20 	rsbs	lr, r5, #32
70001f3c:	db0d      	blt.n	70001f5a <__adddf3+0xb2>
70001f3e:	fa02 fc0e 	lsl.w	ip, r2, lr
70001f42:	fa22 f205 	lsr.w	r2, r2, r5
70001f46:	1880      	adds	r0, r0, r2
70001f48:	f141 0100 	adc.w	r1, r1, #0
70001f4c:	fa03 f20e 	lsl.w	r2, r3, lr
70001f50:	1880      	adds	r0, r0, r2
70001f52:	fa43 f305 	asr.w	r3, r3, r5
70001f56:	4159      	adcs	r1, r3
70001f58:	e00e      	b.n	70001f78 <__adddf3+0xd0>
70001f5a:	f1a5 0520 	sub.w	r5, r5, #32
70001f5e:	f10e 0e20 	add.w	lr, lr, #32
70001f62:	2a01      	cmp	r2, #1
70001f64:	fa03 fc0e 	lsl.w	ip, r3, lr
70001f68:	bf28      	it	cs
70001f6a:	f04c 0c02 	orrcs.w	ip, ip, #2
70001f6e:	fa43 f305 	asr.w	r3, r3, r5
70001f72:	18c0      	adds	r0, r0, r3
70001f74:	eb51 71e3 	adcs.w	r1, r1, r3, asr #31
70001f78:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70001f7c:	d507      	bpl.n	70001f8e <__adddf3+0xe6>
70001f7e:	f04f 0e00 	mov.w	lr, #0
70001f82:	f1dc 0c00 	rsbs	ip, ip, #0
70001f86:	eb7e 0000 	sbcs.w	r0, lr, r0
70001f8a:	eb6e 0101 	sbc.w	r1, lr, r1
70001f8e:	f5b1 1f80 	cmp.w	r1, #1048576	; 0x100000
70001f92:	d31b      	bcc.n	70001fcc <__adddf3+0x124>
70001f94:	f5b1 1f00 	cmp.w	r1, #2097152	; 0x200000
70001f98:	d30c      	bcc.n	70001fb4 <__adddf3+0x10c>
70001f9a:	0849      	lsrs	r1, r1, #1
70001f9c:	ea5f 0030 	movs.w	r0, r0, rrx
70001fa0:	ea4f 0c3c 	mov.w	ip, ip, rrx
70001fa4:	f104 0401 	add.w	r4, r4, #1
70001fa8:	ea4f 5244 	mov.w	r2, r4, lsl #21
70001fac:	f512 0f80 	cmn.w	r2, #4194304	; 0x400000
70001fb0:	f080 809a 	bcs.w	700020e8 <__adddf3+0x240>
70001fb4:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70001fb8:	bf08      	it	eq
70001fba:	ea5f 0c50 	movseq.w	ip, r0, lsr #1
70001fbe:	f150 0000 	adcs.w	r0, r0, #0
70001fc2:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
70001fc6:	ea41 0105 	orr.w	r1, r1, r5
70001fca:	bd30      	pop	{r4, r5, pc}
70001fcc:	ea5f 0c4c 	movs.w	ip, ip, lsl #1
70001fd0:	4140      	adcs	r0, r0
70001fd2:	eb41 0101 	adc.w	r1, r1, r1
70001fd6:	3c01      	subs	r4, #1
70001fd8:	bf28      	it	cs
70001fda:	f5b1 1f80 	cmpcs.w	r1, #1048576	; 0x100000
70001fde:	d2e9      	bcs.n	70001fb4 <__adddf3+0x10c>
70001fe0:	f091 0f00 	teq	r1, #0
70001fe4:	bf04      	itt	eq
70001fe6:	4601      	moveq	r1, r0
70001fe8:	2000      	moveq	r0, #0
70001fea:	fab1 f381 	clz	r3, r1
70001fee:	bf08      	it	eq
70001ff0:	3320      	addeq	r3, #32
70001ff2:	f1a3 030b 	sub.w	r3, r3, #11
70001ff6:	f1b3 0220 	subs.w	r2, r3, #32
70001ffa:	da0c      	bge.n	70002016 <__adddf3+0x16e>
70001ffc:	320c      	adds	r2, #12
70001ffe:	dd08      	ble.n	70002012 <__adddf3+0x16a>
70002000:	f102 0c14 	add.w	ip, r2, #20
70002004:	f1c2 020c 	rsb	r2, r2, #12
70002008:	fa01 f00c 	lsl.w	r0, r1, ip
7000200c:	fa21 f102 	lsr.w	r1, r1, r2
70002010:	e00c      	b.n	7000202c <__adddf3+0x184>
70002012:	f102 0214 	add.w	r2, r2, #20
70002016:	bfd8      	it	le
70002018:	f1c2 0c20 	rsble	ip, r2, #32
7000201c:	fa01 f102 	lsl.w	r1, r1, r2
70002020:	fa20 fc0c 	lsr.w	ip, r0, ip
70002024:	bfdc      	itt	le
70002026:	ea41 010c 	orrle.w	r1, r1, ip
7000202a:	4090      	lslle	r0, r2
7000202c:	1ae4      	subs	r4, r4, r3
7000202e:	bfa2      	ittt	ge
70002030:	eb01 5104 	addge.w	r1, r1, r4, lsl #20
70002034:	4329      	orrge	r1, r5
70002036:	bd30      	popge	{r4, r5, pc}
70002038:	ea6f 0404 	mvn.w	r4, r4
7000203c:	3c1f      	subs	r4, #31
7000203e:	da1c      	bge.n	7000207a <__adddf3+0x1d2>
70002040:	340c      	adds	r4, #12
70002042:	dc0e      	bgt.n	70002062 <__adddf3+0x1ba>
70002044:	f104 0414 	add.w	r4, r4, #20
70002048:	f1c4 0220 	rsb	r2, r4, #32
7000204c:	fa20 f004 	lsr.w	r0, r0, r4
70002050:	fa01 f302 	lsl.w	r3, r1, r2
70002054:	ea40 0003 	orr.w	r0, r0, r3
70002058:	fa21 f304 	lsr.w	r3, r1, r4
7000205c:	ea45 0103 	orr.w	r1, r5, r3
70002060:	bd30      	pop	{r4, r5, pc}
70002062:	f1c4 040c 	rsb	r4, r4, #12
70002066:	f1c4 0220 	rsb	r2, r4, #32
7000206a:	fa20 f002 	lsr.w	r0, r0, r2
7000206e:	fa01 f304 	lsl.w	r3, r1, r4
70002072:	ea40 0003 	orr.w	r0, r0, r3
70002076:	4629      	mov	r1, r5
70002078:	bd30      	pop	{r4, r5, pc}
7000207a:	fa21 f004 	lsr.w	r0, r1, r4
7000207e:	4629      	mov	r1, r5
70002080:	bd30      	pop	{r4, r5, pc}
70002082:	f094 0f00 	teq	r4, #0
70002086:	f483 1380 	eor.w	r3, r3, #1048576	; 0x100000
7000208a:	bf06      	itte	eq
7000208c:	f481 1180 	eoreq.w	r1, r1, #1048576	; 0x100000
70002090:	3401      	addeq	r4, #1
70002092:	3d01      	subne	r5, #1
70002094:	e74e      	b.n	70001f34 <__adddf3+0x8c>
70002096:	ea7f 5c64 	mvns.w	ip, r4, asr #21
7000209a:	bf18      	it	ne
7000209c:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
700020a0:	d029      	beq.n	700020f6 <__adddf3+0x24e>
700020a2:	ea94 0f05 	teq	r4, r5
700020a6:	bf08      	it	eq
700020a8:	ea90 0f02 	teqeq	r0, r2
700020ac:	d005      	beq.n	700020ba <__adddf3+0x212>
700020ae:	ea54 0c00 	orrs.w	ip, r4, r0
700020b2:	bf04      	itt	eq
700020b4:	4619      	moveq	r1, r3
700020b6:	4610      	moveq	r0, r2
700020b8:	bd30      	pop	{r4, r5, pc}
700020ba:	ea91 0f03 	teq	r1, r3
700020be:	bf1e      	ittt	ne
700020c0:	2100      	movne	r1, #0
700020c2:	2000      	movne	r0, #0
700020c4:	bd30      	popne	{r4, r5, pc}
700020c6:	ea5f 5c54 	movs.w	ip, r4, lsr #21
700020ca:	d105      	bne.n	700020d8 <__adddf3+0x230>
700020cc:	0040      	lsls	r0, r0, #1
700020ce:	4149      	adcs	r1, r1
700020d0:	bf28      	it	cs
700020d2:	f041 4100 	orrcs.w	r1, r1, #2147483648	; 0x80000000
700020d6:	bd30      	pop	{r4, r5, pc}
700020d8:	f514 0480 	adds.w	r4, r4, #4194304	; 0x400000
700020dc:	bf3c      	itt	cc
700020de:	f501 1180 	addcc.w	r1, r1, #1048576	; 0x100000
700020e2:	bd30      	popcc	{r4, r5, pc}
700020e4:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
700020e8:	f045 41fe 	orr.w	r1, r5, #2130706432	; 0x7f000000
700020ec:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
700020f0:	f04f 0000 	mov.w	r0, #0
700020f4:	bd30      	pop	{r4, r5, pc}
700020f6:	ea7f 5c64 	mvns.w	ip, r4, asr #21
700020fa:	bf1a      	itte	ne
700020fc:	4619      	movne	r1, r3
700020fe:	4610      	movne	r0, r2
70002100:	ea7f 5c65 	mvnseq.w	ip, r5, asr #21
70002104:	bf1c      	itt	ne
70002106:	460b      	movne	r3, r1
70002108:	4602      	movne	r2, r0
7000210a:	ea50 3401 	orrs.w	r4, r0, r1, lsl #12
7000210e:	bf06      	itte	eq
70002110:	ea52 3503 	orrseq.w	r5, r2, r3, lsl #12
70002114:	ea91 0f03 	teqeq	r1, r3
70002118:	f441 2100 	orrne.w	r1, r1, #524288	; 0x80000
7000211c:	bd30      	pop	{r4, r5, pc}
7000211e:	bf00      	nop

70002120 <__aeabi_ui2d>:
70002120:	f090 0f00 	teq	r0, #0
70002124:	bf04      	itt	eq
70002126:	2100      	moveq	r1, #0
70002128:	4770      	bxeq	lr
7000212a:	b530      	push	{r4, r5, lr}
7000212c:	f44f 6480 	mov.w	r4, #1024	; 0x400
70002130:	f104 0432 	add.w	r4, r4, #50	; 0x32
70002134:	f04f 0500 	mov.w	r5, #0
70002138:	f04f 0100 	mov.w	r1, #0
7000213c:	e750      	b.n	70001fe0 <__adddf3+0x138>
7000213e:	bf00      	nop

70002140 <__aeabi_i2d>:
70002140:	f090 0f00 	teq	r0, #0
70002144:	bf04      	itt	eq
70002146:	2100      	moveq	r1, #0
70002148:	4770      	bxeq	lr
7000214a:	b530      	push	{r4, r5, lr}
7000214c:	f44f 6480 	mov.w	r4, #1024	; 0x400
70002150:	f104 0432 	add.w	r4, r4, #50	; 0x32
70002154:	f010 4500 	ands.w	r5, r0, #2147483648	; 0x80000000
70002158:	bf48      	it	mi
7000215a:	4240      	negmi	r0, r0
7000215c:	f04f 0100 	mov.w	r1, #0
70002160:	e73e      	b.n	70001fe0 <__adddf3+0x138>
70002162:	bf00      	nop

70002164 <__aeabi_f2d>:
70002164:	0042      	lsls	r2, r0, #1
70002166:	ea4f 01e2 	mov.w	r1, r2, asr #3
7000216a:	ea4f 0131 	mov.w	r1, r1, rrx
7000216e:	ea4f 7002 	mov.w	r0, r2, lsl #28
70002172:	bf1f      	itttt	ne
70002174:	f012 437f 	andsne.w	r3, r2, #4278190080	; 0xff000000
70002178:	f093 4f7f 	teqne	r3, #4278190080	; 0xff000000
7000217c:	f081 5160 	eorne.w	r1, r1, #939524096	; 0x38000000
70002180:	4770      	bxne	lr
70002182:	f032 427f 	bics.w	r2, r2, #4278190080	; 0xff000000
70002186:	bf08      	it	eq
70002188:	4770      	bxeq	lr
7000218a:	f093 4f7f 	teq	r3, #4278190080	; 0xff000000
7000218e:	bf04      	itt	eq
70002190:	f441 2100 	orreq.w	r1, r1, #524288	; 0x80000
70002194:	4770      	bxeq	lr
70002196:	b530      	push	{r4, r5, lr}
70002198:	f44f 7460 	mov.w	r4, #896	; 0x380
7000219c:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
700021a0:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
700021a4:	e71c      	b.n	70001fe0 <__adddf3+0x138>
700021a6:	bf00      	nop

700021a8 <__aeabi_ul2d>:
700021a8:	ea50 0201 	orrs.w	r2, r0, r1
700021ac:	bf08      	it	eq
700021ae:	4770      	bxeq	lr
700021b0:	b530      	push	{r4, r5, lr}
700021b2:	f04f 0500 	mov.w	r5, #0
700021b6:	e00a      	b.n	700021ce <__aeabi_l2d+0x16>

700021b8 <__aeabi_l2d>:
700021b8:	ea50 0201 	orrs.w	r2, r0, r1
700021bc:	bf08      	it	eq
700021be:	4770      	bxeq	lr
700021c0:	b530      	push	{r4, r5, lr}
700021c2:	f011 4500 	ands.w	r5, r1, #2147483648	; 0x80000000
700021c6:	d502      	bpl.n	700021ce <__aeabi_l2d+0x16>
700021c8:	4240      	negs	r0, r0
700021ca:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
700021ce:	f44f 6480 	mov.w	r4, #1024	; 0x400
700021d2:	f104 0432 	add.w	r4, r4, #50	; 0x32
700021d6:	ea5f 5c91 	movs.w	ip, r1, lsr #22
700021da:	f43f aed8 	beq.w	70001f8e <__adddf3+0xe6>
700021de:	f04f 0203 	mov.w	r2, #3
700021e2:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
700021e6:	bf18      	it	ne
700021e8:	3203      	addne	r2, #3
700021ea:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
700021ee:	bf18      	it	ne
700021f0:	3203      	addne	r2, #3
700021f2:	eb02 02dc 	add.w	r2, r2, ip, lsr #3
700021f6:	f1c2 0320 	rsb	r3, r2, #32
700021fa:	fa00 fc03 	lsl.w	ip, r0, r3
700021fe:	fa20 f002 	lsr.w	r0, r0, r2
70002202:	fa01 fe03 	lsl.w	lr, r1, r3
70002206:	ea40 000e 	orr.w	r0, r0, lr
7000220a:	fa21 f102 	lsr.w	r1, r1, r2
7000220e:	4414      	add	r4, r2
70002210:	e6bd      	b.n	70001f8e <__adddf3+0xe6>
70002212:	bf00      	nop

70002214 <__aeabi_dmul>:
70002214:	b570      	push	{r4, r5, r6, lr}
70002216:	f04f 0cff 	mov.w	ip, #255	; 0xff
7000221a:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
7000221e:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
70002222:	bf1d      	ittte	ne
70002224:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
70002228:	ea94 0f0c 	teqne	r4, ip
7000222c:	ea95 0f0c 	teqne	r5, ip
70002230:	f000 f8de 	bleq	700023f0 <__aeabi_dmul+0x1dc>
70002234:	442c      	add	r4, r5
70002236:	ea81 0603 	eor.w	r6, r1, r3
7000223a:	ea21 514c 	bic.w	r1, r1, ip, lsl #21
7000223e:	ea23 534c 	bic.w	r3, r3, ip, lsl #21
70002242:	ea50 3501 	orrs.w	r5, r0, r1, lsl #12
70002246:	bf18      	it	ne
70002248:	ea52 3503 	orrsne.w	r5, r2, r3, lsl #12
7000224c:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70002250:	f443 1380 	orr.w	r3, r3, #1048576	; 0x100000
70002254:	d038      	beq.n	700022c8 <__aeabi_dmul+0xb4>
70002256:	fba0 ce02 	umull	ip, lr, r0, r2
7000225a:	f04f 0500 	mov.w	r5, #0
7000225e:	fbe1 e502 	umlal	lr, r5, r1, r2
70002262:	f006 4200 	and.w	r2, r6, #2147483648	; 0x80000000
70002266:	fbe0 e503 	umlal	lr, r5, r0, r3
7000226a:	f04f 0600 	mov.w	r6, #0
7000226e:	fbe1 5603 	umlal	r5, r6, r1, r3
70002272:	f09c 0f00 	teq	ip, #0
70002276:	bf18      	it	ne
70002278:	f04e 0e01 	orrne.w	lr, lr, #1
7000227c:	f1a4 04ff 	sub.w	r4, r4, #255	; 0xff
70002280:	f5b6 7f00 	cmp.w	r6, #512	; 0x200
70002284:	f564 7440 	sbc.w	r4, r4, #768	; 0x300
70002288:	d204      	bcs.n	70002294 <__aeabi_dmul+0x80>
7000228a:	ea5f 0e4e 	movs.w	lr, lr, lsl #1
7000228e:	416d      	adcs	r5, r5
70002290:	eb46 0606 	adc.w	r6, r6, r6
70002294:	ea42 21c6 	orr.w	r1, r2, r6, lsl #11
70002298:	ea41 5155 	orr.w	r1, r1, r5, lsr #21
7000229c:	ea4f 20c5 	mov.w	r0, r5, lsl #11
700022a0:	ea40 505e 	orr.w	r0, r0, lr, lsr #21
700022a4:	ea4f 2ece 	mov.w	lr, lr, lsl #11
700022a8:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
700022ac:	bf88      	it	hi
700022ae:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
700022b2:	d81e      	bhi.n	700022f2 <__aeabi_dmul+0xde>
700022b4:	f1be 4f00 	cmp.w	lr, #2147483648	; 0x80000000
700022b8:	bf08      	it	eq
700022ba:	ea5f 0e50 	movseq.w	lr, r0, lsr #1
700022be:	f150 0000 	adcs.w	r0, r0, #0
700022c2:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
700022c6:	bd70      	pop	{r4, r5, r6, pc}
700022c8:	f006 4600 	and.w	r6, r6, #2147483648	; 0x80000000
700022cc:	ea46 0101 	orr.w	r1, r6, r1
700022d0:	ea40 0002 	orr.w	r0, r0, r2
700022d4:	ea81 0103 	eor.w	r1, r1, r3
700022d8:	ebb4 045c 	subs.w	r4, r4, ip, lsr #1
700022dc:	bfc2      	ittt	gt
700022de:	ebd4 050c 	rsbsgt	r5, r4, ip
700022e2:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
700022e6:	bd70      	popgt	{r4, r5, r6, pc}
700022e8:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
700022ec:	f04f 0e00 	mov.w	lr, #0
700022f0:	3c01      	subs	r4, #1
700022f2:	f300 80ab 	bgt.w	7000244c <__aeabi_dmul+0x238>
700022f6:	f114 0f36 	cmn.w	r4, #54	; 0x36
700022fa:	bfde      	ittt	le
700022fc:	2000      	movle	r0, #0
700022fe:	f001 4100 	andle.w	r1, r1, #2147483648	; 0x80000000
70002302:	bd70      	pople	{r4, r5, r6, pc}
70002304:	f1c4 0400 	rsb	r4, r4, #0
70002308:	3c20      	subs	r4, #32
7000230a:	da35      	bge.n	70002378 <__aeabi_dmul+0x164>
7000230c:	340c      	adds	r4, #12
7000230e:	dc1b      	bgt.n	70002348 <__aeabi_dmul+0x134>
70002310:	f104 0414 	add.w	r4, r4, #20
70002314:	f1c4 0520 	rsb	r5, r4, #32
70002318:	fa00 f305 	lsl.w	r3, r0, r5
7000231c:	fa20 f004 	lsr.w	r0, r0, r4
70002320:	fa01 f205 	lsl.w	r2, r1, r5
70002324:	ea40 0002 	orr.w	r0, r0, r2
70002328:	f001 4200 	and.w	r2, r1, #2147483648	; 0x80000000
7000232c:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
70002330:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
70002334:	fa21 f604 	lsr.w	r6, r1, r4
70002338:	eb42 0106 	adc.w	r1, r2, r6
7000233c:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70002340:	bf08      	it	eq
70002342:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70002346:	bd70      	pop	{r4, r5, r6, pc}
70002348:	f1c4 040c 	rsb	r4, r4, #12
7000234c:	f1c4 0520 	rsb	r5, r4, #32
70002350:	fa00 f304 	lsl.w	r3, r0, r4
70002354:	fa20 f005 	lsr.w	r0, r0, r5
70002358:	fa01 f204 	lsl.w	r2, r1, r4
7000235c:	ea40 0002 	orr.w	r0, r0, r2
70002360:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70002364:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
70002368:	f141 0100 	adc.w	r1, r1, #0
7000236c:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70002370:	bf08      	it	eq
70002372:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70002376:	bd70      	pop	{r4, r5, r6, pc}
70002378:	f1c4 0520 	rsb	r5, r4, #32
7000237c:	fa00 f205 	lsl.w	r2, r0, r5
70002380:	ea4e 0e02 	orr.w	lr, lr, r2
70002384:	fa20 f304 	lsr.w	r3, r0, r4
70002388:	fa01 f205 	lsl.w	r2, r1, r5
7000238c:	ea43 0302 	orr.w	r3, r3, r2
70002390:	fa21 f004 	lsr.w	r0, r1, r4
70002394:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70002398:	fa21 f204 	lsr.w	r2, r1, r4
7000239c:	ea20 0002 	bic.w	r0, r0, r2
700023a0:	eb00 70d3 	add.w	r0, r0, r3, lsr #31
700023a4:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
700023a8:	bf08      	it	eq
700023aa:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
700023ae:	bd70      	pop	{r4, r5, r6, pc}
700023b0:	f094 0f00 	teq	r4, #0
700023b4:	d10f      	bne.n	700023d6 <__aeabi_dmul+0x1c2>
700023b6:	f001 4600 	and.w	r6, r1, #2147483648	; 0x80000000
700023ba:	0040      	lsls	r0, r0, #1
700023bc:	eb41 0101 	adc.w	r1, r1, r1
700023c0:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
700023c4:	bf08      	it	eq
700023c6:	3c01      	subeq	r4, #1
700023c8:	d0f7      	beq.n	700023ba <__aeabi_dmul+0x1a6>
700023ca:	ea41 0106 	orr.w	r1, r1, r6
700023ce:	f095 0f00 	teq	r5, #0
700023d2:	bf18      	it	ne
700023d4:	4770      	bxne	lr
700023d6:	f003 4600 	and.w	r6, r3, #2147483648	; 0x80000000
700023da:	0052      	lsls	r2, r2, #1
700023dc:	eb43 0303 	adc.w	r3, r3, r3
700023e0:	f413 1f80 	tst.w	r3, #1048576	; 0x100000
700023e4:	bf08      	it	eq
700023e6:	3d01      	subeq	r5, #1
700023e8:	d0f7      	beq.n	700023da <__aeabi_dmul+0x1c6>
700023ea:	ea43 0306 	orr.w	r3, r3, r6
700023ee:	4770      	bx	lr
700023f0:	ea94 0f0c 	teq	r4, ip
700023f4:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
700023f8:	bf18      	it	ne
700023fa:	ea95 0f0c 	teqne	r5, ip
700023fe:	d00c      	beq.n	7000241a <__aeabi_dmul+0x206>
70002400:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
70002404:	bf18      	it	ne
70002406:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
7000240a:	d1d1      	bne.n	700023b0 <__aeabi_dmul+0x19c>
7000240c:	ea81 0103 	eor.w	r1, r1, r3
70002410:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70002414:	f04f 0000 	mov.w	r0, #0
70002418:	bd70      	pop	{r4, r5, r6, pc}
7000241a:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
7000241e:	bf06      	itte	eq
70002420:	4610      	moveq	r0, r2
70002422:	4619      	moveq	r1, r3
70002424:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
70002428:	d019      	beq.n	7000245e <__aeabi_dmul+0x24a>
7000242a:	ea94 0f0c 	teq	r4, ip
7000242e:	d102      	bne.n	70002436 <__aeabi_dmul+0x222>
70002430:	ea50 3601 	orrs.w	r6, r0, r1, lsl #12
70002434:	d113      	bne.n	7000245e <__aeabi_dmul+0x24a>
70002436:	ea95 0f0c 	teq	r5, ip
7000243a:	d105      	bne.n	70002448 <__aeabi_dmul+0x234>
7000243c:	ea52 3603 	orrs.w	r6, r2, r3, lsl #12
70002440:	bf1c      	itt	ne
70002442:	4610      	movne	r0, r2
70002444:	4619      	movne	r1, r3
70002446:	d10a      	bne.n	7000245e <__aeabi_dmul+0x24a>
70002448:	ea81 0103 	eor.w	r1, r1, r3
7000244c:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70002450:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
70002454:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
70002458:	f04f 0000 	mov.w	r0, #0
7000245c:	bd70      	pop	{r4, r5, r6, pc}
7000245e:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
70002462:	f441 0178 	orr.w	r1, r1, #16252928	; 0xf80000
70002466:	bd70      	pop	{r4, r5, r6, pc}

70002468 <__aeabi_ddiv>:
70002468:	b570      	push	{r4, r5, r6, lr}
7000246a:	f04f 0cff 	mov.w	ip, #255	; 0xff
7000246e:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
70002472:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
70002476:	bf1d      	ittte	ne
70002478:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
7000247c:	ea94 0f0c 	teqne	r4, ip
70002480:	ea95 0f0c 	teqne	r5, ip
70002484:	f000 f8a7 	bleq	700025d6 <__aeabi_ddiv+0x16e>
70002488:	eba4 0405 	sub.w	r4, r4, r5
7000248c:	ea81 0e03 	eor.w	lr, r1, r3
70002490:	ea52 3503 	orrs.w	r5, r2, r3, lsl #12
70002494:	ea4f 3101 	mov.w	r1, r1, lsl #12
70002498:	f000 8088 	beq.w	700025ac <__aeabi_ddiv+0x144>
7000249c:	ea4f 3303 	mov.w	r3, r3, lsl #12
700024a0:	f04f 5580 	mov.w	r5, #268435456	; 0x10000000
700024a4:	ea45 1313 	orr.w	r3, r5, r3, lsr #4
700024a8:	ea43 6312 	orr.w	r3, r3, r2, lsr #24
700024ac:	ea4f 2202 	mov.w	r2, r2, lsl #8
700024b0:	ea45 1511 	orr.w	r5, r5, r1, lsr #4
700024b4:	ea45 6510 	orr.w	r5, r5, r0, lsr #24
700024b8:	ea4f 2600 	mov.w	r6, r0, lsl #8
700024bc:	f00e 4100 	and.w	r1, lr, #2147483648	; 0x80000000
700024c0:	429d      	cmp	r5, r3
700024c2:	bf08      	it	eq
700024c4:	4296      	cmpeq	r6, r2
700024c6:	f144 04fd 	adc.w	r4, r4, #253	; 0xfd
700024ca:	f504 7440 	add.w	r4, r4, #768	; 0x300
700024ce:	d202      	bcs.n	700024d6 <__aeabi_ddiv+0x6e>
700024d0:	085b      	lsrs	r3, r3, #1
700024d2:	ea4f 0232 	mov.w	r2, r2, rrx
700024d6:	1ab6      	subs	r6, r6, r2
700024d8:	eb65 0503 	sbc.w	r5, r5, r3
700024dc:	085b      	lsrs	r3, r3, #1
700024de:	ea4f 0232 	mov.w	r2, r2, rrx
700024e2:	f44f 1080 	mov.w	r0, #1048576	; 0x100000
700024e6:	f44f 2c00 	mov.w	ip, #524288	; 0x80000
700024ea:	ebb6 0e02 	subs.w	lr, r6, r2
700024ee:	eb75 0e03 	sbcs.w	lr, r5, r3
700024f2:	bf22      	ittt	cs
700024f4:	1ab6      	subcs	r6, r6, r2
700024f6:	4675      	movcs	r5, lr
700024f8:	ea40 000c 	orrcs.w	r0, r0, ip
700024fc:	085b      	lsrs	r3, r3, #1
700024fe:	ea4f 0232 	mov.w	r2, r2, rrx
70002502:	ebb6 0e02 	subs.w	lr, r6, r2
70002506:	eb75 0e03 	sbcs.w	lr, r5, r3
7000250a:	bf22      	ittt	cs
7000250c:	1ab6      	subcs	r6, r6, r2
7000250e:	4675      	movcs	r5, lr
70002510:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70002514:	085b      	lsrs	r3, r3, #1
70002516:	ea4f 0232 	mov.w	r2, r2, rrx
7000251a:	ebb6 0e02 	subs.w	lr, r6, r2
7000251e:	eb75 0e03 	sbcs.w	lr, r5, r3
70002522:	bf22      	ittt	cs
70002524:	1ab6      	subcs	r6, r6, r2
70002526:	4675      	movcs	r5, lr
70002528:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
7000252c:	085b      	lsrs	r3, r3, #1
7000252e:	ea4f 0232 	mov.w	r2, r2, rrx
70002532:	ebb6 0e02 	subs.w	lr, r6, r2
70002536:	eb75 0e03 	sbcs.w	lr, r5, r3
7000253a:	bf22      	ittt	cs
7000253c:	1ab6      	subcs	r6, r6, r2
7000253e:	4675      	movcs	r5, lr
70002540:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
70002544:	ea55 0e06 	orrs.w	lr, r5, r6
70002548:	d018      	beq.n	7000257c <__aeabi_ddiv+0x114>
7000254a:	ea4f 1505 	mov.w	r5, r5, lsl #4
7000254e:	ea45 7516 	orr.w	r5, r5, r6, lsr #28
70002552:	ea4f 1606 	mov.w	r6, r6, lsl #4
70002556:	ea4f 03c3 	mov.w	r3, r3, lsl #3
7000255a:	ea43 7352 	orr.w	r3, r3, r2, lsr #29
7000255e:	ea4f 02c2 	mov.w	r2, r2, lsl #3
70002562:	ea5f 1c1c 	movs.w	ip, ip, lsr #4
70002566:	d1c0      	bne.n	700024ea <__aeabi_ddiv+0x82>
70002568:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
7000256c:	d10b      	bne.n	70002586 <__aeabi_ddiv+0x11e>
7000256e:	ea41 0100 	orr.w	r1, r1, r0
70002572:	f04f 0000 	mov.w	r0, #0
70002576:	f04f 4c00 	mov.w	ip, #2147483648	; 0x80000000
7000257a:	e7b6      	b.n	700024ea <__aeabi_ddiv+0x82>
7000257c:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
70002580:	bf04      	itt	eq
70002582:	4301      	orreq	r1, r0
70002584:	2000      	moveq	r0, #0
70002586:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
7000258a:	bf88      	it	hi
7000258c:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
70002590:	f63f aeaf 	bhi.w	700022f2 <__aeabi_dmul+0xde>
70002594:	ebb5 0c03 	subs.w	ip, r5, r3
70002598:	bf04      	itt	eq
7000259a:	ebb6 0c02 	subseq.w	ip, r6, r2
7000259e:	ea5f 0c50 	movseq.w	ip, r0, lsr #1
700025a2:	f150 0000 	adcs.w	r0, r0, #0
700025a6:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
700025aa:	bd70      	pop	{r4, r5, r6, pc}
700025ac:	f00e 4e00 	and.w	lr, lr, #2147483648	; 0x80000000
700025b0:	ea4e 3111 	orr.w	r1, lr, r1, lsr #12
700025b4:	eb14 045c 	adds.w	r4, r4, ip, lsr #1
700025b8:	bfc2      	ittt	gt
700025ba:	ebd4 050c 	rsbsgt	r5, r4, ip
700025be:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
700025c2:	bd70      	popgt	{r4, r5, r6, pc}
700025c4:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
700025c8:	f04f 0e00 	mov.w	lr, #0
700025cc:	3c01      	subs	r4, #1
700025ce:	e690      	b.n	700022f2 <__aeabi_dmul+0xde>
700025d0:	ea45 0e06 	orr.w	lr, r5, r6
700025d4:	e68d      	b.n	700022f2 <__aeabi_dmul+0xde>
700025d6:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
700025da:	ea94 0f0c 	teq	r4, ip
700025de:	bf08      	it	eq
700025e0:	ea95 0f0c 	teqeq	r5, ip
700025e4:	f43f af3b 	beq.w	7000245e <__aeabi_dmul+0x24a>
700025e8:	ea94 0f0c 	teq	r4, ip
700025ec:	d10a      	bne.n	70002604 <__aeabi_ddiv+0x19c>
700025ee:	ea50 3401 	orrs.w	r4, r0, r1, lsl #12
700025f2:	f47f af34 	bne.w	7000245e <__aeabi_dmul+0x24a>
700025f6:	ea95 0f0c 	teq	r5, ip
700025fa:	f47f af25 	bne.w	70002448 <__aeabi_dmul+0x234>
700025fe:	4610      	mov	r0, r2
70002600:	4619      	mov	r1, r3
70002602:	e72c      	b.n	7000245e <__aeabi_dmul+0x24a>
70002604:	ea95 0f0c 	teq	r5, ip
70002608:	d106      	bne.n	70002618 <__aeabi_ddiv+0x1b0>
7000260a:	ea52 3503 	orrs.w	r5, r2, r3, lsl #12
7000260e:	f43f aefd 	beq.w	7000240c <__aeabi_dmul+0x1f8>
70002612:	4610      	mov	r0, r2
70002614:	4619      	mov	r1, r3
70002616:	e722      	b.n	7000245e <__aeabi_dmul+0x24a>
70002618:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
7000261c:	bf18      	it	ne
7000261e:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
70002622:	f47f aec5 	bne.w	700023b0 <__aeabi_dmul+0x19c>
70002626:	ea50 0441 	orrs.w	r4, r0, r1, lsl #1
7000262a:	f47f af0d 	bne.w	70002448 <__aeabi_dmul+0x234>
7000262e:	ea52 0543 	orrs.w	r5, r2, r3, lsl #1
70002632:	f47f aeeb 	bne.w	7000240c <__aeabi_dmul+0x1f8>
70002636:	e712      	b.n	7000245e <__aeabi_dmul+0x24a>

70002638 <__gedf2>:
70002638:	f04f 3cff 	mov.w	ip, #4294967295
7000263c:	e006      	b.n	7000264c <__cmpdf2+0x4>
7000263e:	bf00      	nop

70002640 <__ledf2>:
70002640:	f04f 0c01 	mov.w	ip, #1
70002644:	e002      	b.n	7000264c <__cmpdf2+0x4>
70002646:	bf00      	nop

70002648 <__cmpdf2>:
70002648:	f04f 0c01 	mov.w	ip, #1
7000264c:	f84d cd04 	str.w	ip, [sp, #-4]!
70002650:	ea4f 0c41 	mov.w	ip, r1, lsl #1
70002654:	ea7f 5c6c 	mvns.w	ip, ip, asr #21
70002658:	ea4f 0c43 	mov.w	ip, r3, lsl #1
7000265c:	bf18      	it	ne
7000265e:	ea7f 5c6c 	mvnsne.w	ip, ip, asr #21
70002662:	d01b      	beq.n	7000269c <__cmpdf2+0x54>
70002664:	b001      	add	sp, #4
70002666:	ea50 0c41 	orrs.w	ip, r0, r1, lsl #1
7000266a:	bf0c      	ite	eq
7000266c:	ea52 0c43 	orrseq.w	ip, r2, r3, lsl #1
70002670:	ea91 0f03 	teqne	r1, r3
70002674:	bf02      	ittt	eq
70002676:	ea90 0f02 	teqeq	r0, r2
7000267a:	2000      	moveq	r0, #0
7000267c:	4770      	bxeq	lr
7000267e:	f110 0f00 	cmn.w	r0, #0
70002682:	ea91 0f03 	teq	r1, r3
70002686:	bf58      	it	pl
70002688:	4299      	cmppl	r1, r3
7000268a:	bf08      	it	eq
7000268c:	4290      	cmpeq	r0, r2
7000268e:	bf2c      	ite	cs
70002690:	17d8      	asrcs	r0, r3, #31
70002692:	ea6f 70e3 	mvncc.w	r0, r3, asr #31
70002696:	f040 0001 	orr.w	r0, r0, #1
7000269a:	4770      	bx	lr
7000269c:	ea4f 0c41 	mov.w	ip, r1, lsl #1
700026a0:	ea7f 5c6c 	mvns.w	ip, ip, asr #21
700026a4:	d102      	bne.n	700026ac <__cmpdf2+0x64>
700026a6:	ea50 3c01 	orrs.w	ip, r0, r1, lsl #12
700026aa:	d107      	bne.n	700026bc <__cmpdf2+0x74>
700026ac:	ea4f 0c43 	mov.w	ip, r3, lsl #1
700026b0:	ea7f 5c6c 	mvns.w	ip, ip, asr #21
700026b4:	d1d6      	bne.n	70002664 <__cmpdf2+0x1c>
700026b6:	ea52 3c03 	orrs.w	ip, r2, r3, lsl #12
700026ba:	d0d3      	beq.n	70002664 <__cmpdf2+0x1c>
700026bc:	f85d 0b04 	ldr.w	r0, [sp], #4
700026c0:	4770      	bx	lr
700026c2:	bf00      	nop

700026c4 <__aeabi_cdrcmple>:
700026c4:	4684      	mov	ip, r0
700026c6:	4610      	mov	r0, r2
700026c8:	4662      	mov	r2, ip
700026ca:	468c      	mov	ip, r1
700026cc:	4619      	mov	r1, r3
700026ce:	4663      	mov	r3, ip
700026d0:	e000      	b.n	700026d4 <__aeabi_cdcmpeq>
700026d2:	bf00      	nop

700026d4 <__aeabi_cdcmpeq>:
700026d4:	b501      	push	{r0, lr}
700026d6:	f7ff ffb7 	bl	70002648 <__cmpdf2>
700026da:	2800      	cmp	r0, #0
700026dc:	bf48      	it	mi
700026de:	f110 0f00 	cmnmi.w	r0, #0
700026e2:	bd01      	pop	{r0, pc}

700026e4 <__aeabi_dcmpeq>:
700026e4:	f84d ed08 	str.w	lr, [sp, #-8]!
700026e8:	f7ff fff4 	bl	700026d4 <__aeabi_cdcmpeq>
700026ec:	bf0c      	ite	eq
700026ee:	2001      	moveq	r0, #1
700026f0:	2000      	movne	r0, #0
700026f2:	f85d fb08 	ldr.w	pc, [sp], #8
700026f6:	bf00      	nop

700026f8 <__aeabi_dcmplt>:
700026f8:	f84d ed08 	str.w	lr, [sp, #-8]!
700026fc:	f7ff ffea 	bl	700026d4 <__aeabi_cdcmpeq>
70002700:	bf34      	ite	cc
70002702:	2001      	movcc	r0, #1
70002704:	2000      	movcs	r0, #0
70002706:	f85d fb08 	ldr.w	pc, [sp], #8
7000270a:	bf00      	nop

7000270c <__aeabi_dcmple>:
7000270c:	f84d ed08 	str.w	lr, [sp, #-8]!
70002710:	f7ff ffe0 	bl	700026d4 <__aeabi_cdcmpeq>
70002714:	bf94      	ite	ls
70002716:	2001      	movls	r0, #1
70002718:	2000      	movhi	r0, #0
7000271a:	f85d fb08 	ldr.w	pc, [sp], #8
7000271e:	bf00      	nop

70002720 <__aeabi_dcmpge>:
70002720:	f84d ed08 	str.w	lr, [sp, #-8]!
70002724:	f7ff ffce 	bl	700026c4 <__aeabi_cdrcmple>
70002728:	bf94      	ite	ls
7000272a:	2001      	movls	r0, #1
7000272c:	2000      	movhi	r0, #0
7000272e:	f85d fb08 	ldr.w	pc, [sp], #8
70002732:	bf00      	nop

70002734 <__aeabi_dcmpgt>:
70002734:	f84d ed08 	str.w	lr, [sp, #-8]!
70002738:	f7ff ffc4 	bl	700026c4 <__aeabi_cdrcmple>
7000273c:	bf34      	ite	cc
7000273e:	2001      	movcc	r0, #1
70002740:	2000      	movcs	r0, #0
70002742:	f85d fb08 	ldr.w	pc, [sp], #8
70002746:	bf00      	nop

70002748 <__aeabi_dcmpun>:
70002748:	ea4f 0c41 	mov.w	ip, r1, lsl #1
7000274c:	ea7f 5c6c 	mvns.w	ip, ip, asr #21
70002750:	d102      	bne.n	70002758 <__aeabi_dcmpun+0x10>
70002752:	ea50 3c01 	orrs.w	ip, r0, r1, lsl #12
70002756:	d10a      	bne.n	7000276e <__aeabi_dcmpun+0x26>
70002758:	ea4f 0c43 	mov.w	ip, r3, lsl #1
7000275c:	ea7f 5c6c 	mvns.w	ip, ip, asr #21
70002760:	d102      	bne.n	70002768 <__aeabi_dcmpun+0x20>
70002762:	ea52 3c03 	orrs.w	ip, r2, r3, lsl #12
70002766:	d102      	bne.n	7000276e <__aeabi_dcmpun+0x26>
70002768:	f04f 0000 	mov.w	r0, #0
7000276c:	4770      	bx	lr
7000276e:	f04f 0001 	mov.w	r0, #1
70002772:	4770      	bx	lr

70002774 <__aeabi_d2uiz>:
70002774:	004a      	lsls	r2, r1, #1
70002776:	d211      	bcs.n	7000279c <__aeabi_d2uiz+0x28>
70002778:	f512 1200 	adds.w	r2, r2, #2097152	; 0x200000
7000277c:	d211      	bcs.n	700027a2 <__aeabi_d2uiz+0x2e>
7000277e:	d50d      	bpl.n	7000279c <__aeabi_d2uiz+0x28>
70002780:	f46f 7378 	mvn.w	r3, #992	; 0x3e0
70002784:	ebb3 5262 	subs.w	r2, r3, r2, asr #21
70002788:	d40e      	bmi.n	700027a8 <__aeabi_d2uiz+0x34>
7000278a:	ea4f 23c1 	mov.w	r3, r1, lsl #11
7000278e:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70002792:	ea43 5350 	orr.w	r3, r3, r0, lsr #21
70002796:	fa23 f002 	lsr.w	r0, r3, r2
7000279a:	4770      	bx	lr
7000279c:	f04f 0000 	mov.w	r0, #0
700027a0:	4770      	bx	lr
700027a2:	ea50 3001 	orrs.w	r0, r0, r1, lsl #12
700027a6:	d102      	bne.n	700027ae <__aeabi_d2uiz+0x3a>
700027a8:	f04f 30ff 	mov.w	r0, #4294967295
700027ac:	4770      	bx	lr
700027ae:	f04f 0000 	mov.w	r0, #0
700027b2:	4770      	bx	lr

700027b4 <__aeabi_d2f>:
700027b4:	ea4f 0241 	mov.w	r2, r1, lsl #1
700027b8:	f1b2 43e0 	subs.w	r3, r2, #1879048192	; 0x70000000
700027bc:	bf24      	itt	cs
700027be:	f5b3 1c00 	subscs.w	ip, r3, #2097152	; 0x200000
700027c2:	f1dc 5cfe 	rsbscs	ip, ip, #532676608	; 0x1fc00000
700027c6:	d90d      	bls.n	700027e4 <__aeabi_d2f+0x30>
700027c8:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
700027cc:	ea4f 02c0 	mov.w	r2, r0, lsl #3
700027d0:	ea4c 7050 	orr.w	r0, ip, r0, lsr #29
700027d4:	f1b2 4f00 	cmp.w	r2, #2147483648	; 0x80000000
700027d8:	eb40 0083 	adc.w	r0, r0, r3, lsl #2
700027dc:	bf08      	it	eq
700027de:	f020 0001 	biceq.w	r0, r0, #1
700027e2:	4770      	bx	lr
700027e4:	f011 4f80 	tst.w	r1, #1073741824	; 0x40000000
700027e8:	d121      	bne.n	7000282e <__aeabi_d2f+0x7a>
700027ea:	f113 7238 	adds.w	r2, r3, #48234496	; 0x2e00000
700027ee:	bfbc      	itt	lt
700027f0:	f001 4000 	andlt.w	r0, r1, #2147483648	; 0x80000000
700027f4:	4770      	bxlt	lr
700027f6:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
700027fa:	ea4f 5252 	mov.w	r2, r2, lsr #21
700027fe:	f1c2 0218 	rsb	r2, r2, #24
70002802:	f1c2 0c20 	rsb	ip, r2, #32
70002806:	fa10 f30c 	lsls.w	r3, r0, ip
7000280a:	fa20 f002 	lsr.w	r0, r0, r2
7000280e:	bf18      	it	ne
70002810:	f040 0001 	orrne.w	r0, r0, #1
70002814:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70002818:	ea4f 23d3 	mov.w	r3, r3, lsr #11
7000281c:	fa03 fc0c 	lsl.w	ip, r3, ip
70002820:	ea40 000c 	orr.w	r0, r0, ip
70002824:	fa23 f302 	lsr.w	r3, r3, r2
70002828:	ea4f 0343 	mov.w	r3, r3, lsl #1
7000282c:	e7cc      	b.n	700027c8 <__aeabi_d2f+0x14>
7000282e:	ea7f 5362 	mvns.w	r3, r2, asr #21
70002832:	d107      	bne.n	70002844 <__aeabi_d2f+0x90>
70002834:	ea50 3301 	orrs.w	r3, r0, r1, lsl #12
70002838:	bf1e      	ittt	ne
7000283a:	f04f 40fe 	movne.w	r0, #2130706432	; 0x7f000000
7000283e:	f440 0040 	orrne.w	r0, r0, #12582912	; 0xc00000
70002842:	4770      	bxne	lr
70002844:	f001 4000 	and.w	r0, r1, #2147483648	; 0x80000000
70002848:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
7000284c:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70002850:	4770      	bx	lr
70002852:	bf00      	nop

70002854 <__aeabi_frsub>:
70002854:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70002858:	e002      	b.n	70002860 <__addsf3>
7000285a:	bf00      	nop

7000285c <__aeabi_fsub>:
7000285c:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

70002860 <__addsf3>:
70002860:	0042      	lsls	r2, r0, #1
70002862:	bf1f      	itttt	ne
70002864:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70002868:	ea92 0f03 	teqne	r2, r3
7000286c:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
70002870:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70002874:	d06a      	beq.n	7000294c <__addsf3+0xec>
70002876:	ea4f 6212 	mov.w	r2, r2, lsr #24
7000287a:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
7000287e:	bfc1      	itttt	gt
70002880:	18d2      	addgt	r2, r2, r3
70002882:	4041      	eorgt	r1, r0
70002884:	4048      	eorgt	r0, r1
70002886:	4041      	eorgt	r1, r0
70002888:	bfb8      	it	lt
7000288a:	425b      	neglt	r3, r3
7000288c:	2b19      	cmp	r3, #25
7000288e:	bf88      	it	hi
70002890:	4770      	bxhi	lr
70002892:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
70002896:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
7000289a:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
7000289e:	bf18      	it	ne
700028a0:	4240      	negne	r0, r0
700028a2:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
700028a6:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
700028aa:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
700028ae:	bf18      	it	ne
700028b0:	4249      	negne	r1, r1
700028b2:	ea92 0f03 	teq	r2, r3
700028b6:	d03f      	beq.n	70002938 <__addsf3+0xd8>
700028b8:	f1a2 0201 	sub.w	r2, r2, #1
700028bc:	fa41 fc03 	asr.w	ip, r1, r3
700028c0:	eb10 000c 	adds.w	r0, r0, ip
700028c4:	f1c3 0320 	rsb	r3, r3, #32
700028c8:	fa01 f103 	lsl.w	r1, r1, r3
700028cc:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
700028d0:	d502      	bpl.n	700028d8 <__addsf3+0x78>
700028d2:	4249      	negs	r1, r1
700028d4:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
700028d8:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
700028dc:	d313      	bcc.n	70002906 <__addsf3+0xa6>
700028de:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
700028e2:	d306      	bcc.n	700028f2 <__addsf3+0x92>
700028e4:	0840      	lsrs	r0, r0, #1
700028e6:	ea4f 0131 	mov.w	r1, r1, rrx
700028ea:	f102 0201 	add.w	r2, r2, #1
700028ee:	2afe      	cmp	r2, #254	; 0xfe
700028f0:	d251      	bcs.n	70002996 <__addsf3+0x136>
700028f2:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
700028f6:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
700028fa:	bf08      	it	eq
700028fc:	f020 0001 	biceq.w	r0, r0, #1
70002900:	ea40 0003 	orr.w	r0, r0, r3
70002904:	4770      	bx	lr
70002906:	0049      	lsls	r1, r1, #1
70002908:	eb40 0000 	adc.w	r0, r0, r0
7000290c:	3a01      	subs	r2, #1
7000290e:	bf28      	it	cs
70002910:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70002914:	d2ed      	bcs.n	700028f2 <__addsf3+0x92>
70002916:	fab0 fc80 	clz	ip, r0
7000291a:	f1ac 0c08 	sub.w	ip, ip, #8
7000291e:	ebb2 020c 	subs.w	r2, r2, ip
70002922:	fa00 f00c 	lsl.w	r0, r0, ip
70002926:	bfaa      	itet	ge
70002928:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
7000292c:	4252      	neglt	r2, r2
7000292e:	4318      	orrge	r0, r3
70002930:	bfbc      	itt	lt
70002932:	40d0      	lsrlt	r0, r2
70002934:	4318      	orrlt	r0, r3
70002936:	4770      	bx	lr
70002938:	f092 0f00 	teq	r2, #0
7000293c:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
70002940:	bf06      	itte	eq
70002942:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
70002946:	3201      	addeq	r2, #1
70002948:	3b01      	subne	r3, #1
7000294a:	e7b5      	b.n	700028b8 <__addsf3+0x58>
7000294c:	ea4f 0341 	mov.w	r3, r1, lsl #1
70002950:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70002954:	bf18      	it	ne
70002956:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
7000295a:	d021      	beq.n	700029a0 <__addsf3+0x140>
7000295c:	ea92 0f03 	teq	r2, r3
70002960:	d004      	beq.n	7000296c <__addsf3+0x10c>
70002962:	f092 0f00 	teq	r2, #0
70002966:	bf08      	it	eq
70002968:	4608      	moveq	r0, r1
7000296a:	4770      	bx	lr
7000296c:	ea90 0f01 	teq	r0, r1
70002970:	bf1c      	itt	ne
70002972:	2000      	movne	r0, #0
70002974:	4770      	bxne	lr
70002976:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
7000297a:	d104      	bne.n	70002986 <__addsf3+0x126>
7000297c:	0040      	lsls	r0, r0, #1
7000297e:	bf28      	it	cs
70002980:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
70002984:	4770      	bx	lr
70002986:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
7000298a:	bf3c      	itt	cc
7000298c:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
70002990:	4770      	bxcc	lr
70002992:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70002996:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
7000299a:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
7000299e:	4770      	bx	lr
700029a0:	ea7f 6222 	mvns.w	r2, r2, asr #24
700029a4:	bf16      	itet	ne
700029a6:	4608      	movne	r0, r1
700029a8:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
700029ac:	4601      	movne	r1, r0
700029ae:	0242      	lsls	r2, r0, #9
700029b0:	bf06      	itte	eq
700029b2:	ea5f 2341 	movseq.w	r3, r1, lsl #9
700029b6:	ea90 0f01 	teqeq	r0, r1
700029ba:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
700029be:	4770      	bx	lr

700029c0 <__aeabi_ui2f>:
700029c0:	f04f 0300 	mov.w	r3, #0
700029c4:	e004      	b.n	700029d0 <__aeabi_i2f+0x8>
700029c6:	bf00      	nop

700029c8 <__aeabi_i2f>:
700029c8:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
700029cc:	bf48      	it	mi
700029ce:	4240      	negmi	r0, r0
700029d0:	ea5f 0c00 	movs.w	ip, r0
700029d4:	bf08      	it	eq
700029d6:	4770      	bxeq	lr
700029d8:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
700029dc:	4601      	mov	r1, r0
700029de:	f04f 0000 	mov.w	r0, #0
700029e2:	e01c      	b.n	70002a1e <__aeabi_l2f+0x2a>

700029e4 <__aeabi_ul2f>:
700029e4:	ea50 0201 	orrs.w	r2, r0, r1
700029e8:	bf08      	it	eq
700029ea:	4770      	bxeq	lr
700029ec:	f04f 0300 	mov.w	r3, #0
700029f0:	e00a      	b.n	70002a08 <__aeabi_l2f+0x14>
700029f2:	bf00      	nop

700029f4 <__aeabi_l2f>:
700029f4:	ea50 0201 	orrs.w	r2, r0, r1
700029f8:	bf08      	it	eq
700029fa:	4770      	bxeq	lr
700029fc:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70002a00:	d502      	bpl.n	70002a08 <__aeabi_l2f+0x14>
70002a02:	4240      	negs	r0, r0
70002a04:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70002a08:	ea5f 0c01 	movs.w	ip, r1
70002a0c:	bf02      	ittt	eq
70002a0e:	4684      	moveq	ip, r0
70002a10:	4601      	moveq	r1, r0
70002a12:	2000      	moveq	r0, #0
70002a14:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70002a18:	bf08      	it	eq
70002a1a:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70002a1e:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
70002a22:	fabc f28c 	clz	r2, ip
70002a26:	3a08      	subs	r2, #8
70002a28:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
70002a2c:	db10      	blt.n	70002a50 <__aeabi_l2f+0x5c>
70002a2e:	fa01 fc02 	lsl.w	ip, r1, r2
70002a32:	4463      	add	r3, ip
70002a34:	fa00 fc02 	lsl.w	ip, r0, r2
70002a38:	f1c2 0220 	rsb	r2, r2, #32
70002a3c:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70002a40:	fa20 f202 	lsr.w	r2, r0, r2
70002a44:	eb43 0002 	adc.w	r0, r3, r2
70002a48:	bf08      	it	eq
70002a4a:	f020 0001 	biceq.w	r0, r0, #1
70002a4e:	4770      	bx	lr
70002a50:	f102 0220 	add.w	r2, r2, #32
70002a54:	fa01 fc02 	lsl.w	ip, r1, r2
70002a58:	f1c2 0220 	rsb	r2, r2, #32
70002a5c:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
70002a60:	fa21 f202 	lsr.w	r2, r1, r2
70002a64:	eb43 0002 	adc.w	r0, r3, r2
70002a68:	bf08      	it	eq
70002a6a:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70002a6e:	4770      	bx	lr

70002a70 <__aeabi_fmul>:
70002a70:	f04f 0cff 	mov.w	ip, #255	; 0xff
70002a74:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70002a78:	bf1e      	ittt	ne
70002a7a:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70002a7e:	ea92 0f0c 	teqne	r2, ip
70002a82:	ea93 0f0c 	teqne	r3, ip
70002a86:	d06f      	beq.n	70002b68 <__aeabi_fmul+0xf8>
70002a88:	441a      	add	r2, r3
70002a8a:	ea80 0c01 	eor.w	ip, r0, r1
70002a8e:	0240      	lsls	r0, r0, #9
70002a90:	bf18      	it	ne
70002a92:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70002a96:	d01e      	beq.n	70002ad6 <__aeabi_fmul+0x66>
70002a98:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70002a9c:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70002aa0:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70002aa4:	fba0 3101 	umull	r3, r1, r0, r1
70002aa8:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70002aac:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70002ab0:	bf3e      	ittt	cc
70002ab2:	0049      	lslcc	r1, r1, #1
70002ab4:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70002ab8:	005b      	lslcc	r3, r3, #1
70002aba:	ea40 0001 	orr.w	r0, r0, r1
70002abe:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70002ac2:	2afd      	cmp	r2, #253	; 0xfd
70002ac4:	d81d      	bhi.n	70002b02 <__aeabi_fmul+0x92>
70002ac6:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70002aca:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70002ace:	bf08      	it	eq
70002ad0:	f020 0001 	biceq.w	r0, r0, #1
70002ad4:	4770      	bx	lr
70002ad6:	f090 0f00 	teq	r0, #0
70002ada:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70002ade:	bf08      	it	eq
70002ae0:	0249      	lsleq	r1, r1, #9
70002ae2:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70002ae6:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70002aea:	3a7f      	subs	r2, #127	; 0x7f
70002aec:	bfc2      	ittt	gt
70002aee:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70002af2:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70002af6:	4770      	bxgt	lr
70002af8:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70002afc:	f04f 0300 	mov.w	r3, #0
70002b00:	3a01      	subs	r2, #1
70002b02:	dc5d      	bgt.n	70002bc0 <__aeabi_fmul+0x150>
70002b04:	f112 0f19 	cmn.w	r2, #25
70002b08:	bfdc      	itt	le
70002b0a:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70002b0e:	4770      	bxle	lr
70002b10:	f1c2 0200 	rsb	r2, r2, #0
70002b14:	0041      	lsls	r1, r0, #1
70002b16:	fa21 f102 	lsr.w	r1, r1, r2
70002b1a:	f1c2 0220 	rsb	r2, r2, #32
70002b1e:	fa00 fc02 	lsl.w	ip, r0, r2
70002b22:	ea5f 0031 	movs.w	r0, r1, rrx
70002b26:	f140 0000 	adc.w	r0, r0, #0
70002b2a:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70002b2e:	bf08      	it	eq
70002b30:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70002b34:	4770      	bx	lr
70002b36:	f092 0f00 	teq	r2, #0
70002b3a:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70002b3e:	bf02      	ittt	eq
70002b40:	0040      	lsleq	r0, r0, #1
70002b42:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70002b46:	3a01      	subeq	r2, #1
70002b48:	d0f9      	beq.n	70002b3e <__aeabi_fmul+0xce>
70002b4a:	ea40 000c 	orr.w	r0, r0, ip
70002b4e:	f093 0f00 	teq	r3, #0
70002b52:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70002b56:	bf02      	ittt	eq
70002b58:	0049      	lsleq	r1, r1, #1
70002b5a:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70002b5e:	3b01      	subeq	r3, #1
70002b60:	d0f9      	beq.n	70002b56 <__aeabi_fmul+0xe6>
70002b62:	ea41 010c 	orr.w	r1, r1, ip
70002b66:	e78f      	b.n	70002a88 <__aeabi_fmul+0x18>
70002b68:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70002b6c:	ea92 0f0c 	teq	r2, ip
70002b70:	bf18      	it	ne
70002b72:	ea93 0f0c 	teqne	r3, ip
70002b76:	d00a      	beq.n	70002b8e <__aeabi_fmul+0x11e>
70002b78:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70002b7c:	bf18      	it	ne
70002b7e:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70002b82:	d1d8      	bne.n	70002b36 <__aeabi_fmul+0xc6>
70002b84:	ea80 0001 	eor.w	r0, r0, r1
70002b88:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70002b8c:	4770      	bx	lr
70002b8e:	f090 0f00 	teq	r0, #0
70002b92:	bf17      	itett	ne
70002b94:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70002b98:	4608      	moveq	r0, r1
70002b9a:	f091 0f00 	teqne	r1, #0
70002b9e:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70002ba2:	d014      	beq.n	70002bce <__aeabi_fmul+0x15e>
70002ba4:	ea92 0f0c 	teq	r2, ip
70002ba8:	d101      	bne.n	70002bae <__aeabi_fmul+0x13e>
70002baa:	0242      	lsls	r2, r0, #9
70002bac:	d10f      	bne.n	70002bce <__aeabi_fmul+0x15e>
70002bae:	ea93 0f0c 	teq	r3, ip
70002bb2:	d103      	bne.n	70002bbc <__aeabi_fmul+0x14c>
70002bb4:	024b      	lsls	r3, r1, #9
70002bb6:	bf18      	it	ne
70002bb8:	4608      	movne	r0, r1
70002bba:	d108      	bne.n	70002bce <__aeabi_fmul+0x15e>
70002bbc:	ea80 0001 	eor.w	r0, r0, r1
70002bc0:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70002bc4:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70002bc8:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70002bcc:	4770      	bx	lr
70002bce:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70002bd2:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70002bd6:	4770      	bx	lr

70002bd8 <__aeabi_fdiv>:
70002bd8:	f04f 0cff 	mov.w	ip, #255	; 0xff
70002bdc:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70002be0:	bf1e      	ittt	ne
70002be2:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70002be6:	ea92 0f0c 	teqne	r2, ip
70002bea:	ea93 0f0c 	teqne	r3, ip
70002bee:	d069      	beq.n	70002cc4 <__aeabi_fdiv+0xec>
70002bf0:	eba2 0203 	sub.w	r2, r2, r3
70002bf4:	ea80 0c01 	eor.w	ip, r0, r1
70002bf8:	0249      	lsls	r1, r1, #9
70002bfa:	ea4f 2040 	mov.w	r0, r0, lsl #9
70002bfe:	d037      	beq.n	70002c70 <__aeabi_fdiv+0x98>
70002c00:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70002c04:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70002c08:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70002c0c:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70002c10:	428b      	cmp	r3, r1
70002c12:	bf38      	it	cc
70002c14:	005b      	lslcc	r3, r3, #1
70002c16:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70002c1a:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70002c1e:	428b      	cmp	r3, r1
70002c20:	bf24      	itt	cs
70002c22:	1a5b      	subcs	r3, r3, r1
70002c24:	ea40 000c 	orrcs.w	r0, r0, ip
70002c28:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70002c2c:	bf24      	itt	cs
70002c2e:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
70002c32:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70002c36:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70002c3a:	bf24      	itt	cs
70002c3c:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
70002c40:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
70002c44:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
70002c48:	bf24      	itt	cs
70002c4a:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
70002c4e:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
70002c52:	011b      	lsls	r3, r3, #4
70002c54:	bf18      	it	ne
70002c56:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70002c5a:	d1e0      	bne.n	70002c1e <__aeabi_fdiv+0x46>
70002c5c:	2afd      	cmp	r2, #253	; 0xfd
70002c5e:	f63f af50 	bhi.w	70002b02 <__aeabi_fmul+0x92>
70002c62:	428b      	cmp	r3, r1
70002c64:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70002c68:	bf08      	it	eq
70002c6a:	f020 0001 	biceq.w	r0, r0, #1
70002c6e:	4770      	bx	lr
70002c70:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70002c74:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70002c78:	327f      	adds	r2, #127	; 0x7f
70002c7a:	bfc2      	ittt	gt
70002c7c:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70002c80:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70002c84:	4770      	bxgt	lr
70002c86:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70002c8a:	f04f 0300 	mov.w	r3, #0
70002c8e:	3a01      	subs	r2, #1
70002c90:	e737      	b.n	70002b02 <__aeabi_fmul+0x92>
70002c92:	f092 0f00 	teq	r2, #0
70002c96:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70002c9a:	bf02      	ittt	eq
70002c9c:	0040      	lsleq	r0, r0, #1
70002c9e:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70002ca2:	3a01      	subeq	r2, #1
70002ca4:	d0f9      	beq.n	70002c9a <__aeabi_fdiv+0xc2>
70002ca6:	ea40 000c 	orr.w	r0, r0, ip
70002caa:	f093 0f00 	teq	r3, #0
70002cae:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70002cb2:	bf02      	ittt	eq
70002cb4:	0049      	lsleq	r1, r1, #1
70002cb6:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70002cba:	3b01      	subeq	r3, #1
70002cbc:	d0f9      	beq.n	70002cb2 <__aeabi_fdiv+0xda>
70002cbe:	ea41 010c 	orr.w	r1, r1, ip
70002cc2:	e795      	b.n	70002bf0 <__aeabi_fdiv+0x18>
70002cc4:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70002cc8:	ea92 0f0c 	teq	r2, ip
70002ccc:	d108      	bne.n	70002ce0 <__aeabi_fdiv+0x108>
70002cce:	0242      	lsls	r2, r0, #9
70002cd0:	f47f af7d 	bne.w	70002bce <__aeabi_fmul+0x15e>
70002cd4:	ea93 0f0c 	teq	r3, ip
70002cd8:	f47f af70 	bne.w	70002bbc <__aeabi_fmul+0x14c>
70002cdc:	4608      	mov	r0, r1
70002cde:	e776      	b.n	70002bce <__aeabi_fmul+0x15e>
70002ce0:	ea93 0f0c 	teq	r3, ip
70002ce4:	d104      	bne.n	70002cf0 <__aeabi_fdiv+0x118>
70002ce6:	024b      	lsls	r3, r1, #9
70002ce8:	f43f af4c 	beq.w	70002b84 <__aeabi_fmul+0x114>
70002cec:	4608      	mov	r0, r1
70002cee:	e76e      	b.n	70002bce <__aeabi_fmul+0x15e>
70002cf0:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70002cf4:	bf18      	it	ne
70002cf6:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70002cfa:	d1ca      	bne.n	70002c92 <__aeabi_fdiv+0xba>
70002cfc:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70002d00:	f47f af5c 	bne.w	70002bbc <__aeabi_fmul+0x14c>
70002d04:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70002d08:	f47f af3c 	bne.w	70002b84 <__aeabi_fmul+0x114>
70002d0c:	e75f      	b.n	70002bce <__aeabi_fmul+0x15e>
70002d0e:	bf00      	nop

70002d10 <__gesf2>:
70002d10:	f04f 3cff 	mov.w	ip, #4294967295
70002d14:	e006      	b.n	70002d24 <__cmpsf2+0x4>
70002d16:	bf00      	nop

70002d18 <__lesf2>:
70002d18:	f04f 0c01 	mov.w	ip, #1
70002d1c:	e002      	b.n	70002d24 <__cmpsf2+0x4>
70002d1e:	bf00      	nop

70002d20 <__cmpsf2>:
70002d20:	f04f 0c01 	mov.w	ip, #1
70002d24:	f84d cd04 	str.w	ip, [sp, #-4]!
70002d28:	ea4f 0240 	mov.w	r2, r0, lsl #1
70002d2c:	ea4f 0341 	mov.w	r3, r1, lsl #1
70002d30:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70002d34:	bf18      	it	ne
70002d36:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70002d3a:	d011      	beq.n	70002d60 <__cmpsf2+0x40>
70002d3c:	b001      	add	sp, #4
70002d3e:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
70002d42:	bf18      	it	ne
70002d44:	ea90 0f01 	teqne	r0, r1
70002d48:	bf58      	it	pl
70002d4a:	ebb2 0003 	subspl.w	r0, r2, r3
70002d4e:	bf88      	it	hi
70002d50:	17c8      	asrhi	r0, r1, #31
70002d52:	bf38      	it	cc
70002d54:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70002d58:	bf18      	it	ne
70002d5a:	f040 0001 	orrne.w	r0, r0, #1
70002d5e:	4770      	bx	lr
70002d60:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70002d64:	d102      	bne.n	70002d6c <__cmpsf2+0x4c>
70002d66:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70002d6a:	d105      	bne.n	70002d78 <__cmpsf2+0x58>
70002d6c:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70002d70:	d1e4      	bne.n	70002d3c <__cmpsf2+0x1c>
70002d72:	ea5f 2c41 	movs.w	ip, r1, lsl #9
70002d76:	d0e1      	beq.n	70002d3c <__cmpsf2+0x1c>
70002d78:	f85d 0b04 	ldr.w	r0, [sp], #4
70002d7c:	4770      	bx	lr
70002d7e:	bf00      	nop

70002d80 <__aeabi_cfrcmple>:
70002d80:	4684      	mov	ip, r0
70002d82:	4608      	mov	r0, r1
70002d84:	4661      	mov	r1, ip
70002d86:	e7ff      	b.n	70002d88 <__aeabi_cfcmpeq>

70002d88 <__aeabi_cfcmpeq>:
70002d88:	b50f      	push	{r0, r1, r2, r3, lr}
70002d8a:	f7ff ffc9 	bl	70002d20 <__cmpsf2>
70002d8e:	2800      	cmp	r0, #0
70002d90:	bf48      	it	mi
70002d92:	f110 0f00 	cmnmi.w	r0, #0
70002d96:	bd0f      	pop	{r0, r1, r2, r3, pc}

70002d98 <__aeabi_fcmpeq>:
70002d98:	f84d ed08 	str.w	lr, [sp, #-8]!
70002d9c:	f7ff fff4 	bl	70002d88 <__aeabi_cfcmpeq>
70002da0:	bf0c      	ite	eq
70002da2:	2001      	moveq	r0, #1
70002da4:	2000      	movne	r0, #0
70002da6:	f85d fb08 	ldr.w	pc, [sp], #8
70002daa:	bf00      	nop

70002dac <__aeabi_fcmplt>:
70002dac:	f84d ed08 	str.w	lr, [sp, #-8]!
70002db0:	f7ff ffea 	bl	70002d88 <__aeabi_cfcmpeq>
70002db4:	bf34      	ite	cc
70002db6:	2001      	movcc	r0, #1
70002db8:	2000      	movcs	r0, #0
70002dba:	f85d fb08 	ldr.w	pc, [sp], #8
70002dbe:	bf00      	nop

70002dc0 <__aeabi_fcmple>:
70002dc0:	f84d ed08 	str.w	lr, [sp, #-8]!
70002dc4:	f7ff ffe0 	bl	70002d88 <__aeabi_cfcmpeq>
70002dc8:	bf94      	ite	ls
70002dca:	2001      	movls	r0, #1
70002dcc:	2000      	movhi	r0, #0
70002dce:	f85d fb08 	ldr.w	pc, [sp], #8
70002dd2:	bf00      	nop

70002dd4 <__aeabi_fcmpge>:
70002dd4:	f84d ed08 	str.w	lr, [sp, #-8]!
70002dd8:	f7ff ffd2 	bl	70002d80 <__aeabi_cfrcmple>
70002ddc:	bf94      	ite	ls
70002dde:	2001      	movls	r0, #1
70002de0:	2000      	movhi	r0, #0
70002de2:	f85d fb08 	ldr.w	pc, [sp], #8
70002de6:	bf00      	nop

70002de8 <__aeabi_fcmpgt>:
70002de8:	f84d ed08 	str.w	lr, [sp, #-8]!
70002dec:	f7ff ffc8 	bl	70002d80 <__aeabi_cfrcmple>
70002df0:	bf34      	ite	cc
70002df2:	2001      	movcc	r0, #1
70002df4:	2000      	movcs	r0, #0
70002df6:	f85d fb08 	ldr.w	pc, [sp], #8
70002dfa:	bf00      	nop

70002dfc <__aeabi_fcmpun>:
70002dfc:	ea4f 0240 	mov.w	r2, r0, lsl #1
70002e00:	ea4f 0341 	mov.w	r3, r1, lsl #1
70002e04:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70002e08:	d102      	bne.n	70002e10 <__aeabi_fcmpun+0x14>
70002e0a:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70002e0e:	d108      	bne.n	70002e22 <__aeabi_fcmpun+0x26>
70002e10:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70002e14:	d102      	bne.n	70002e1c <__aeabi_fcmpun+0x20>
70002e16:	ea5f 2c41 	movs.w	ip, r1, lsl #9
70002e1a:	d102      	bne.n	70002e22 <__aeabi_fcmpun+0x26>
70002e1c:	f04f 0000 	mov.w	r0, #0
70002e20:	4770      	bx	lr
70002e22:	f04f 0001 	mov.w	r0, #1
70002e26:	4770      	bx	lr

70002e28 <__aeabi_f2uiz>:
70002e28:	0042      	lsls	r2, r0, #1
70002e2a:	d20e      	bcs.n	70002e4a <__aeabi_f2uiz+0x22>
70002e2c:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70002e30:	d30b      	bcc.n	70002e4a <__aeabi_f2uiz+0x22>
70002e32:	f04f 039e 	mov.w	r3, #158	; 0x9e
70002e36:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70002e3a:	d409      	bmi.n	70002e50 <__aeabi_f2uiz+0x28>
70002e3c:	ea4f 2300 	mov.w	r3, r0, lsl #8
70002e40:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70002e44:	fa23 f002 	lsr.w	r0, r3, r2
70002e48:	4770      	bx	lr
70002e4a:	f04f 0000 	mov.w	r0, #0
70002e4e:	4770      	bx	lr
70002e50:	f112 0f61 	cmn.w	r2, #97	; 0x61
70002e54:	d101      	bne.n	70002e5a <__aeabi_f2uiz+0x32>
70002e56:	0242      	lsls	r2, r0, #9
70002e58:	d102      	bne.n	70002e60 <__aeabi_f2uiz+0x38>
70002e5a:	f04f 30ff 	mov.w	r0, #4294967295
70002e5e:	4770      	bx	lr
70002e60:	f04f 0000 	mov.w	r0, #0
70002e64:	4770      	bx	lr
70002e66:	bf00      	nop

70002e68 <bp>:
70002e68:	0000 0000 0000 3ff0 0000 0000 0000 3ff8     .......?.......?

70002e78 <dp_l>:
	...
70002e80:	d006 43cf fdeb 3e4c                         ...C..L>

70002e88 <dp_h>:
	...
70002e90:	0000 4000 b803 3fe2                         ...@...?

70002e98 <_global_impure_ptr>:
70002e98:	2ea8 7000 0000 0000                         ...p....

70002ea0 <_impure_ptr>:
70002ea0:	2ea8 7000 0000 0000                         ...p....

70002ea8 <impure_data>:
70002ea8:	0000 0000 3194 7000 31fc 7000 3264 7000     .....1.p.1.pd2.p
	...
70002f50:	0001 0000 0000 0000 330e abcd 1234 e66d     .........3..4.m.
70002f60:	deec 0005 000b 0000 0000 0000 0000 0000     ................
	...
