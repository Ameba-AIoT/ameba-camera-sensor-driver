
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	0d 07 00 70 5d 02 00 70                             ...p]..p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

7000006c <g_jxf53_i2c_init_regs_asic>:
7000006c:	12 00 40 00 48 00 8a 00 48 00 0a 00 0e 00 19 00     ..@.H...H.......
7000007c:	0f 00 04 00 10 00 20 00 11 00 80 00 46 00 09 00     ...... .....F...
7000008c:	47 00 66 00 0d 00 f2 00 57 00 6a 00 58 00 22 00     G.f.....W.j.X.".
7000009c:	5f 00 41 00 60 00 24 00 a5 00 c0 00 20 00 00 00     _.A.`.$..... ...
700000ac:	21 00 05 00 22 00 65 00 23 00 04 00 24 00 c2 00     !...".e.#...$...
700000bc:	25 00 3c 00 26 00 43 00 27 00 c8 00 28 00 13 00     %.<.&.C.'...(...
700000cc:	29 00 04 00 2a 00 bd 00 2b 00 14 00 2c 00 01 00     )...*...+...,...
700000dc:	2d 00 00 00 2e 00 14 00 2f 00 04 00 41 00 c7 00     -......./...A...
700000ec:	42 00 33 00 47 00 46 00 76 00 65 00 77 00 09 00     B.3.G.F.v.e.w...
700000fc:	80 00 01 00 af 00 22 00 ab 00 00 00 1d 00 00 00     ......".........
7000010c:	1e 00 04 00 6c 00 40 00 9e 00 f8 00 6e 00 2c 00     ....l.@.....n.,.
7000011c:	70 00 6c 00 71 00 6d 00 72 00 6a 00 73 00 56 00     p.l.q.m.r.j.s.V.
7000012c:	74 00 02 00 78 00 9d 00 89 00 01 00 6b 00 20 00     t...x.......k. .
7000013c:	86 00 40 00 31 00 10 00 32 00 18 00 33 00 e8 00     ..@.1...2...3...
7000014c:	34 00 5e 00 35 00 5e 00 3a 00 af 00 3b 00 00 00     4.^.5.^.:...;...
7000015c:	3c 00 ff 00 3d 00 ff 00 3e 00 ff 00 3f 00 bb 00     <...=...>...?...
7000016c:	40 00 ff 00 56 00 92 00 59 00 af 00 5a 00 47 00     @...V...Y...Z.G.
7000017c:	61 00 18 00 6f 00 04 00 85 00 5f 00 8a 00 44 00     a...o....._...D.
7000018c:	91 00 13 00 94 00 a0 00 9b 00 83 00 9c 00 e1 00     ................
7000019c:	a4 00 80 00 a6 00 22 00 a9 00 1c 00 5b 00 e7 00     ......".....[...
700001ac:	5c 00 28 00 5d 00 67 00 5e 00 11 00 62 00 21 00     \.(.].g.^...b.!.
700001bc:	63 00 0f 00 64 00 d0 00 65 00 02 00 67 00 49 00     c...d...e...g.I.
700001cc:	66 00 00 00 68 00 00 00 69 00 72 00 6a 00 12 00     f...h...i.r.j...
700001dc:	7a 00 00 00 82 00 20 00 8d 00 47 00 8f 00 90 00     z..... ...G.....
700001ec:	45 00 01 00 97 00 20 00 13 00 81 00 96 00 84 00     E..... .........
700001fc:	4a 00 01 00 b1 00 00 00 a1 00 0f 00 be 00 00 00     J...............
7000020c:	7e 00 48 00 b5 00 c0 00 50 00 02 00 49 00 10 00     ~.H.....P...I...
7000021c:	7f 00 57 00 90 00 00 00 7b 00 4a 00 7c 00 07 00     ..W.....{.J.|...
7000022c:	8c 00 ff 00 8e 00 00 00 8b 00 01 00 0c 00 00 00     ................
7000023c:	bc 00 11 00 19 00 20 00 1b 00 4f 00 12 00 30 00     ...... ...O...0.
7000024c:	00 00 10 00                                         ....

70000250 <real_slave_addr>:
70000250:	40 00 00 00                                         @...

70000254 <slave_addr_list>:
70000254:	40 00 00 00 46 00 00 00                             @...F...

7000025c <rts_isp_set_voe_ops>:
7000025c:	4b01      	ldr	r3, [pc, #4]	; (70000264 <rts_isp_set_voe_ops+0x8>)
7000025e:	6018      	str	r0, [r3, #0]
70000260:	4770      	bx	lr
70000262:	bf00      	nop
70000264:	70000048 	.word	0x70000048

70000268 <isp_driver_is_fpga>:
70000268:	2000      	movs	r0, #0
7000026a:	4770      	bx	lr

7000026c <jxf53_get_info>:
7000026c:	b530      	push	{r4, r5, lr}
7000026e:	2800      	cmp	r0, #0
70000270:	d14d      	bne.n	7000030e <jxf53_get_info+0xa2>
70000272:	2900      	cmp	r1, #0
70000274:	d04b      	beq.n	7000030e <jxf53_get_info+0xa2>
70000276:	f44f 62f0 	mov.w	r2, #1920	; 0x780
7000027a:	f44f 6387 	mov.w	r3, #1080	; 0x438
7000027e:	f44f 747a 	mov.w	r4, #1000	; 0x3e8
70000282:	4d24      	ldr	r5, [pc, #144]	; (70000314 <jxf53_get_info+0xa8>)
70000284:	7108      	strb	r0, [r1, #4]
70000286:	f881 00b0 	strb.w	r0, [r1, #176]	; 0xb0
7000028a:	f8c1 00b4 	str.w	r0, [r1, #180]	; 0xb4
7000028e:	f881 00bc 	strb.w	r0, [r1, #188]	; 0xbc
70000292:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
70000296:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
7000029a:	f8c1 02dc 	str.w	r0, [r1, #732]	; 0x2dc
7000029e:	e9c1 2302 	strd	r2, r3, [r1, #8]
700002a2:	4b1d      	ldr	r3, [pc, #116]	; (70000318 <jxf53_get_info+0xac>)
700002a4:	4a1d      	ldr	r2, [pc, #116]	; (7000031c <jxf53_get_info+0xb0>)
700002a6:	610b      	str	r3, [r1, #16]
700002a8:	2301      	movs	r3, #1
700002aa:	6812      	ldr	r2, [r2, #0]
700002ac:	600b      	str	r3, [r1, #0]
700002ae:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
700002b2:	4a1b      	ldr	r2, [pc, #108]	; (70000320 <jxf53_get_info+0xb4>)
700002b4:	f881 3098 	strb.w	r3, [r1, #152]	; 0x98
700002b8:	7812      	ldrb	r2, [r2, #0]
700002ba:	f881 30c8 	strb.w	r3, [r1, #200]	; 0xc8
700002be:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
700002c2:	2203      	movs	r2, #3
700002c4:	e9c1 542a 	strd	r5, r4, [r1, #168]	; 0xa8
700002c8:	e9c1 3430 	strd	r3, r4, [r1, #192]	; 0xc0
700002cc:	e9c1 0433 	strd	r0, r4, [r1, #204]	; 0xcc
700002d0:	f240 1401 	movw	r4, #257	; 0x101
700002d4:	f242 7510 	movw	r5, #10000	; 0x2710
700002d8:	f881 20a4 	strb.w	r2, [r1, #164]	; 0xa4
700002dc:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
700002e0:	2406      	movs	r4, #6
700002e2:	f8c1 50b8 	str.w	r5, [r1, #184]	; 0xb8
700002e6:	f8c1 4088 	str.w	r4, [r1, #136]	; 0x88
700002ea:	2464      	movs	r4, #100	; 0x64
700002ec:	e9c1 3324 	strd	r3, r3, [r1, #144]	; 0x90
700002f0:	e9c1 3327 	strd	r3, r3, [r1, #156]	; 0x9c
700002f4:	f8c1 42e0 	str.w	r4, [r1, #736]	; 0x2e0
700002f8:	f881 32e4 	strb.w	r3, [r1, #740]	; 0x2e4
700002fc:	f881 22f0 	strb.w	r2, [r1, #752]	; 0x2f0
70000300:	f8c1 22d4 	str.w	r2, [r1, #724]	; 0x2d4
70000304:	e9c1 34ba 	strd	r3, r4, [r1, #744]	; 0x2e8
70000308:	e9c1 04bd 	strd	r0, r4, [r1, #756]	; 0x2f4
7000030c:	bd30      	pop	{r4, r5, pc}
7000030e:	f06f 0015 	mvn.w	r0, #21
70000312:	e7fb      	b.n	7000030c <jxf53_get_info+0xa0>
70000314:	019bfcc0 	.word	0x019bfcc0
70000318:	41f00000 	.word	0x41f00000
7000031c:	70000250 	.word	0x70000250
70000320:	7000004c 	.word	0x7000004c

70000324 <jxf53_get_init_info>:
70000324:	b570      	push	{r4, r5, r6, lr}
70000326:	4614      	mov	r4, r2
70000328:	4605      	mov	r5, r0
7000032a:	b110      	cbz	r0, 70000332 <jxf53_get_init_info+0xe>
7000032c:	f06f 0015 	mvn.w	r0, #21
70000330:	bd70      	pop	{r4, r5, r6, pc}
70000332:	2a00      	cmp	r2, #0
70000334:	d0fa      	beq.n	7000032c <jxf53_get_init_info+0x8>
70000336:	780b      	ldrb	r3, [r1, #0]
70000338:	4e1b      	ldr	r6, [pc, #108]	; (700003a8 <jxf53_get_init_info+0x84>)
7000033a:	68c8      	ldr	r0, [r1, #12]
7000033c:	7033      	strb	r3, [r6, #0]
7000033e:	f001 f919 	bl	70001574 <__aeabi_f2uiz>
70000342:	b280      	uxth	r0, r0
70000344:	281e      	cmp	r0, #30
70000346:	d1f1      	bne.n	7000032c <jxf53_get_init_info+0x8>
70000348:	4b18      	ldr	r3, [pc, #96]	; (700003ac <jxf53_get_init_info+0x88>)
7000034a:	f44f 62f1 	mov.w	r2, #1928	; 0x788
7000034e:	f44f 6020 	mov.w	r0, #2560	; 0xa00
70000352:	60a5      	str	r5, [r4, #8]
70000354:	6063      	str	r3, [r4, #4]
70000356:	2379      	movs	r3, #121	; 0x79
70000358:	f8c4 5088 	str.w	r5, [r4, #136]	; 0x88
7000035c:	6023      	str	r3, [r4, #0]
7000035e:	2302      	movs	r3, #2
70000360:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
70000364:	f240 4303 	movw	r3, #1027	; 0x403
70000368:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
7000036c:	230a      	movs	r3, #10
7000036e:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
70000372:	2304      	movs	r3, #4
70000374:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
70000378:	f44f 6388 	mov.w	r3, #1088	; 0x440
7000037c:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
70000380:	2303      	movs	r3, #3
70000382:	f8c4 308c 	str.w	r3, [r4, #140]	; 0x8c
70000386:	4b0a      	ldr	r3, [pc, #40]	; (700003b0 <jxf53_get_init_info+0x8c>)
70000388:	e9c4 3024 	strd	r3, r0, [r4, #144]	; 0x90
7000038c:	f240 4365 	movw	r3, #1125	; 0x465
70000390:	4628      	mov	r0, r5
70000392:	6073      	str	r3, [r6, #4]
70000394:	f8c4 3098 	str.w	r3, [r4, #152]	; 0x98
70000398:	f248 33d6 	movw	r3, #33750	; 0x83d6
7000039c:	f8c4 309c 	str.w	r3, [r4, #156]	; 0x9c
700003a0:	4b04      	ldr	r3, [pc, #16]	; (700003b4 <jxf53_get_init_info+0x90>)
700003a2:	60b3      	str	r3, [r6, #8]
700003a4:	e7c4      	b.n	70000330 <jxf53_get_init_info+0xc>
700003a6:	bf00      	nop
700003a8:	7000004c 	.word	0x7000004c
700003ac:	7000006c 	.word	0x7000006c
700003b0:	05265c00 	.word	0x05265c00
700003b4:	41ed097b 	.word	0x41ed097b

700003b8 <jxf53_start>:
700003b8:	b918      	cbnz	r0, 700003c2 <jxf53_start+0xa>
700003ba:	4b03      	ldr	r3, [pc, #12]	; (700003c8 <jxf53_start+0x10>)
700003bc:	2200      	movs	r2, #0
700003be:	60da      	str	r2, [r3, #12]
700003c0:	4770      	bx	lr
700003c2:	f06f 0015 	mvn.w	r0, #21
700003c6:	4770      	bx	lr
700003c8:	7000004c 	.word	0x7000004c

700003cc <jxf53_get_tuned_dgain>:
700003cc:	b920      	cbnz	r0, 700003d8 <jxf53_get_tuned_dgain+0xc>
700003ce:	b119      	cbz	r1, 700003d8 <jxf53_get_tuned_dgain+0xc>
700003d0:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
700003d4:	600b      	str	r3, [r1, #0]
700003d6:	4770      	bx	lr
700003d8:	f06f 0015 	mvn.w	r0, #21
700003dc:	4770      	bx	lr
	...

700003e0 <jxf53_get_exposure_gain_info>:
700003e0:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
700003e4:	4614      	mov	r4, r2
700003e6:	2800      	cmp	r0, #0
700003e8:	d14b      	bne.n	70000482 <jxf53_get_exposure_gain_info+0xa2>
700003ea:	2900      	cmp	r1, #0
700003ec:	d049      	beq.n	70000482 <jxf53_get_exposure_gain_info+0xa2>
700003ee:	2a00      	cmp	r2, #0
700003f0:	d047      	beq.n	70000482 <jxf53_get_exposure_gain_info+0xa2>
700003f2:	f8d1 8000 	ldr.w	r8, [r1]
700003f6:	1d15      	adds	r5, r2, #4
700003f8:	4f23      	ldr	r7, [pc, #140]	; (70000488 <jxf53_get_exposure_gain_info+0xa8>)
700003fa:	698e      	ldr	r6, [r1, #24]
700003fc:	4641      	mov	r1, r8
700003fe:	68f8      	ldr	r0, [r7, #12]
70000400:	f000 fde8 	bl	70000fd4 <__aeabi_fsub>
70000404:	2100      	movs	r1, #0
70000406:	4681      	mov	r9, r0
70000408:	f001 f8a0 	bl	7000154c <__aeabi_fcmpge>
7000040c:	2800      	cmp	r0, #0
7000040e:	d033      	beq.n	70000478 <jxf53_get_exposure_gain_info+0x98>
70000410:	491e      	ldr	r1, [pc, #120]	; (7000048c <jxf53_get_exposure_gain_info+0xac>)
70000412:	4648      	mov	r0, r9
70000414:	f001 f8a4 	bl	70001560 <__aeabi_fcmpgt>
70000418:	b1a8      	cbz	r0, 70000446 <jxf53_get_exposure_gain_info+0x66>
7000041a:	68b9      	ldr	r1, [r7, #8]
7000041c:	4640      	mov	r0, r8
7000041e:	f000 ff97 	bl	70001350 <__aeabi_fdiv>
70000422:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
70000426:	f000 fdd7 	bl	70000fd8 <__addsf3>
7000042a:	f001 f8a3 	bl	70001574 <__aeabi_f2uiz>
7000042e:	f3c0 2307 	ubfx	r3, r0, #8, #8
70000432:	2202      	movs	r2, #2
70000434:	81e3      	strh	r3, [r4, #14]
70000436:	2301      	movs	r3, #1
70000438:	81a2      	strh	r2, [r4, #12]
7000043a:	8423      	strh	r3, [r4, #32]
7000043c:	b2c3      	uxtb	r3, r0
7000043e:	4610      	mov	r0, r2
70000440:	f8c7 800c 	str.w	r8, [r7, #12]
70000444:	8463      	strh	r3, [r4, #34]	; 0x22
70000446:	2114      	movs	r1, #20
70000448:	8a3f      	ldrh	r7, [r7, #16]
7000044a:	2300      	movs	r3, #0
7000044c:	4341      	muls	r1, r0
7000044e:	3003      	adds	r0, #3
70000450:	186a      	adds	r2, r5, r1
70000452:	8157      	strh	r7, [r2, #10]
70000454:	2723      	movs	r7, #35	; 0x23
70000456:	8113      	strh	r3, [r2, #8]
70000458:	f101 0214 	add.w	r2, r1, #20
7000045c:	3128      	adds	r1, #40	; 0x28
7000045e:	442a      	add	r2, r5
70000460:	4429      	add	r1, r5
70000462:	8117      	strh	r7, [r2, #8]
70000464:	0a37      	lsrs	r7, r6, #8
70000466:	b2f6      	uxtb	r6, r6
70000468:	8157      	strh	r7, [r2, #10]
7000046a:	2222      	movs	r2, #34	; 0x22
7000046c:	814e      	strh	r6, [r1, #10]
7000046e:	810a      	strh	r2, [r1, #8]
70000470:	6020      	str	r0, [r4, #0]
70000472:	4618      	mov	r0, r3
70000474:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
70000478:	4905      	ldr	r1, [pc, #20]	; (70000490 <jxf53_get_exposure_gain_info+0xb0>)
7000047a:	4648      	mov	r0, r9
7000047c:	f001 f852 	bl	70001524 <__aeabi_fcmplt>
70000480:	e7ca      	b.n	70000418 <jxf53_get_exposure_gain_info+0x38>
70000482:	f06f 0015 	mvn.w	r0, #21
70000486:	e7f5      	b.n	70000474 <jxf53_get_exposure_gain_info+0x94>
70000488:	7000004c 	.word	0x7000004c
7000048c:	3a83126f 	.word	0x3a83126f
70000490:	ba83126f 	.word	0xba83126f

70000494 <jxf53_set_mirror_flip>:
70000494:	784b      	ldrb	r3, [r1, #1]
70000496:	780a      	ldrb	r2, [r1, #0]
70000498:	2b00      	cmp	r3, #0
7000049a:	bf14      	ite	ne
7000049c:	2302      	movne	r3, #2
7000049e:	2300      	moveq	r3, #0
700004a0:	2a00      	cmp	r2, #0
700004a2:	bf18      	it	ne
700004a4:	f043 0301 	orrne.w	r3, r3, #1
700004a8:	2201      	movs	r2, #1
700004aa:	2b02      	cmp	r3, #2
700004ac:	708a      	strb	r2, [r1, #2]
700004ae:	d009      	beq.n	700004c4 <jxf53_set_mirror_flip+0x30>
700004b0:	2b03      	cmp	r3, #3
700004b2:	d00b      	beq.n	700004cc <jxf53_set_mirror_flip+0x38>
700004b4:	4293      	cmp	r3, r2
700004b6:	d007      	beq.n	700004c8 <jxf53_set_mirror_flip+0x34>
700004b8:	4b05      	ldr	r3, [pc, #20]	; (700004d0 <jxf53_set_mirror_flip+0x3c>)
700004ba:	610b      	str	r3, [r1, #16]
700004bc:	2301      	movs	r3, #1
700004be:	2000      	movs	r0, #0
700004c0:	604b      	str	r3, [r1, #4]
700004c2:	4770      	bx	lr
700004c4:	4b03      	ldr	r3, [pc, #12]	; (700004d4 <jxf53_set_mirror_flip+0x40>)
700004c6:	e7f8      	b.n	700004ba <jxf53_set_mirror_flip+0x26>
700004c8:	4b03      	ldr	r3, [pc, #12]	; (700004d8 <jxf53_set_mirror_flip+0x44>)
700004ca:	e7f6      	b.n	700004ba <jxf53_set_mirror_flip+0x26>
700004cc:	2312      	movs	r3, #18
700004ce:	e7f4      	b.n	700004ba <jxf53_set_mirror_flip+0x26>
700004d0:	00300012 	.word	0x00300012
700004d4:	00200012 	.word	0x00200012
700004d8:	00100012 	.word	0x00100012

700004dc <jxf53_check>:
700004dc:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
700004de:	4f1d      	ldr	r7, [pc, #116]	; (70000554 <jxf53_check+0x78>)
700004e0:	4605      	mov	r5, r0
700004e2:	683b      	ldr	r3, [r7, #0]
700004e4:	6c1b      	ldr	r3, [r3, #64]	; 0x40
700004e6:	4798      	blx	r3
700004e8:	2801      	cmp	r0, #1
700004ea:	dc2f      	bgt.n	7000054c <jxf53_check+0x70>
700004ec:	4b1a      	ldr	r3, [pc, #104]	; (70000558 <jxf53_check+0x7c>)
700004ee:	f853 2020 	ldr.w	r2, [r3, r0, lsl #2]
700004f2:	4b1a      	ldr	r3, [pc, #104]	; (7000055c <jxf53_check+0x80>)
700004f4:	601a      	str	r2, [r3, #0]
700004f6:	683b      	ldr	r3, [r7, #0]
700004f8:	685b      	ldr	r3, [r3, #4]
700004fa:	4798      	blx	r3
700004fc:	230a      	movs	r3, #10
700004fe:	a901      	add	r1, sp, #4
70000500:	4628      	mov	r0, r5
70000502:	f8ad 3004 	strh.w	r3, [sp, #4]
70000506:	683b      	ldr	r3, [r7, #0]
70000508:	68db      	ldr	r3, [r3, #12]
7000050a:	4798      	blx	r3
7000050c:	4604      	mov	r4, r0
7000050e:	b128      	cbz	r0, 7000051c <jxf53_check+0x40>
70000510:	683b      	ldr	r3, [r7, #0]
70000512:	689b      	ldr	r3, [r3, #8]
70000514:	4798      	blx	r3
70000516:	4620      	mov	r0, r4
70000518:	b003      	add	sp, #12
7000051a:	bdf0      	pop	{r4, r5, r6, r7, pc}
7000051c:	230b      	movs	r3, #11
7000051e:	a901      	add	r1, sp, #4
70000520:	4628      	mov	r0, r5
70000522:	f8bd 6006 	ldrh.w	r6, [sp, #6]
70000526:	f8ad 3004 	strh.w	r3, [sp, #4]
7000052a:	683b      	ldr	r3, [r7, #0]
7000052c:	68db      	ldr	r3, [r3, #12]
7000052e:	4798      	blx	r3
70000530:	4604      	mov	r4, r0
70000532:	2800      	cmp	r0, #0
70000534:	d1ec      	bne.n	70000510 <jxf53_check+0x34>
70000536:	683b      	ldr	r3, [r7, #0]
70000538:	f8bd 5006 	ldrh.w	r5, [sp, #6]
7000053c:	689b      	ldr	r3, [r3, #8]
7000053e:	4798      	blx	r3
70000540:	f640 0342 	movw	r3, #2114	; 0x842
70000544:	ea45 2506 	orr.w	r5, r5, r6, lsl #8
70000548:	429d      	cmp	r5, r3
7000054a:	d0e4      	beq.n	70000516 <jxf53_check+0x3a>
7000054c:	f06f 0415 	mvn.w	r4, #21
70000550:	e7e1      	b.n	70000516 <jxf53_check+0x3a>
70000552:	bf00      	nop
70000554:	70000048 	.word	0x70000048
70000558:	70000254 	.word	0x70000254
7000055c:	70000250 	.word	0x70000250

70000560 <jxf53_get_slave_addr_num>:
70000560:	2002      	movs	r0, #2
70000562:	4770      	bx	lr

70000564 <jxf53_get_tuned_again>:
70000564:	b570      	push	{r4, r5, r6, lr}
70000566:	460e      	mov	r6, r1
70000568:	2800      	cmp	r0, #0
7000056a:	f040 80ab 	bne.w	700006c4 <jxf53_get_tuned_again+0x160>
7000056e:	2900      	cmp	r1, #0
70000570:	f000 80a8 	beq.w	700006c4 <jxf53_get_tuned_again+0x160>
70000574:	680c      	ldr	r4, [r1, #0]
70000576:	f04f 517e 	mov.w	r1, #1065353216	; 0x3f800000
7000057a:	4620      	mov	r0, r4
7000057c:	f000 ffe6 	bl	7000154c <__aeabi_fcmpge>
70000580:	b338      	cbz	r0, 700005d2 <jxf53_get_tuned_again+0x6e>
70000582:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
70000586:	4620      	mov	r0, r4
70000588:	f000 ffcc 	bl	70001524 <__aeabi_fcmplt>
7000058c:	b308      	cbz	r0, 700005d2 <jxf53_get_tuned_again+0x6e>
7000058e:	4620      	mov	r0, r4
70000590:	f000 fc4c 	bl	70000e2c <__aeabi_f2d>
70000594:	2200      	movs	r2, #0
70000596:	4b4d      	ldr	r3, [pc, #308]	; (700006cc <jxf53_get_tuned_again+0x168>)
70000598:	f000 fae8 	bl	70000b6c <__aeabi_dsub>
7000059c:	2200      	movs	r2, #0
7000059e:	4b4c      	ldr	r3, [pc, #304]	; (700006d0 <jxf53_get_tuned_again+0x16c>)
700005a0:	f000 f902 	bl	700007a8 <__aeabi_dmul>
700005a4:	f000 fc9a 	bl	70000edc <__aeabi_d2iz>
700005a8:	4b4a      	ldr	r3, [pc, #296]	; (700006d4 <jxf53_get_tuned_again+0x170>)
700005aa:	b284      	uxth	r4, r0
700005ac:	6118      	str	r0, [r3, #16]
700005ae:	4620      	mov	r0, r4
700005b0:	f000 fdc2 	bl	70001138 <__aeabi_ui2f>
700005b4:	2c0f      	cmp	r4, #15
700005b6:	d85e      	bhi.n	70000676 <jxf53_get_tuned_again+0x112>
700005b8:	f000 fc38 	bl	70000e2c <__aeabi_f2d>
700005bc:	2200      	movs	r2, #0
700005be:	4b46      	ldr	r3, [pc, #280]	; (700006d8 <jxf53_get_tuned_again+0x174>)
700005c0:	f000 f8f2 	bl	700007a8 <__aeabi_dmul>
700005c4:	2200      	movs	r2, #0
700005c6:	4b41      	ldr	r3, [pc, #260]	; (700006cc <jxf53_get_tuned_again+0x168>)
700005c8:	f000 fad2 	bl	70000b70 <__adddf3>
700005cc:	f000 fcae 	bl	70000f2c <__aeabi_d2f>
700005d0:	e059      	b.n	70000686 <jxf53_get_tuned_again+0x122>
700005d2:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
700005d6:	4620      	mov	r0, r4
700005d8:	f000 ffb8 	bl	7000154c <__aeabi_fcmpge>
700005dc:	b1b0      	cbz	r0, 7000060c <jxf53_get_tuned_again+0xa8>
700005de:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
700005e2:	4620      	mov	r0, r4
700005e4:	f000 ff9e 	bl	70001524 <__aeabi_fcmplt>
700005e8:	b180      	cbz	r0, 7000060c <jxf53_get_tuned_again+0xa8>
700005ea:	4620      	mov	r0, r4
700005ec:	f000 fc1e 	bl	70000e2c <__aeabi_f2d>
700005f0:	2200      	movs	r2, #0
700005f2:	f04f 4380 	mov.w	r3, #1073741824	; 0x40000000
700005f6:	f000 fab9 	bl	70000b6c <__aeabi_dsub>
700005fa:	2200      	movs	r2, #0
700005fc:	4b37      	ldr	r3, [pc, #220]	; (700006dc <jxf53_get_tuned_again+0x178>)
700005fe:	f000 f8d3 	bl	700007a8 <__aeabi_dmul>
70000602:	2200      	movs	r2, #0
70000604:	4b32      	ldr	r3, [pc, #200]	; (700006d0 <jxf53_get_tuned_again+0x16c>)
70000606:	f000 fab3 	bl	70000b70 <__adddf3>
7000060a:	e7cb      	b.n	700005a4 <jxf53_get_tuned_again+0x40>
7000060c:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
70000610:	4620      	mov	r0, r4
70000612:	f000 ff9b 	bl	7000154c <__aeabi_fcmpge>
70000616:	b198      	cbz	r0, 70000640 <jxf53_get_tuned_again+0xdc>
70000618:	f04f 4182 	mov.w	r1, #1090519040	; 0x41000000
7000061c:	4620      	mov	r0, r4
7000061e:	f000 ff81 	bl	70001524 <__aeabi_fcmplt>
70000622:	b168      	cbz	r0, 70000640 <jxf53_get_tuned_again+0xdc>
70000624:	4620      	mov	r0, r4
70000626:	f000 fc01 	bl	70000e2c <__aeabi_f2d>
7000062a:	2200      	movs	r2, #0
7000062c:	4b2c      	ldr	r3, [pc, #176]	; (700006e0 <jxf53_get_tuned_again+0x17c>)
7000062e:	f000 fa9d 	bl	70000b6c <__aeabi_dsub>
70000632:	2200      	movs	r2, #0
70000634:	4b2a      	ldr	r3, [pc, #168]	; (700006e0 <jxf53_get_tuned_again+0x17c>)
70000636:	f000 f8b7 	bl	700007a8 <__aeabi_dmul>
7000063a:	2200      	movs	r2, #0
7000063c:	4b29      	ldr	r3, [pc, #164]	; (700006e4 <jxf53_get_tuned_again+0x180>)
7000063e:	e7e2      	b.n	70000606 <jxf53_get_tuned_again+0xa2>
70000640:	f04f 4182 	mov.w	r1, #1090519040	; 0x41000000
70000644:	4620      	mov	r0, r4
70000646:	f000 ff81 	bl	7000154c <__aeabi_fcmpge>
7000064a:	b190      	cbz	r0, 70000672 <jxf53_get_tuned_again+0x10e>
7000064c:	4926      	ldr	r1, [pc, #152]	; (700006e8 <jxf53_get_tuned_again+0x184>)
7000064e:	4620      	mov	r0, r4
70000650:	f000 ff72 	bl	70001538 <__aeabi_fcmple>
70000654:	b168      	cbz	r0, 70000672 <jxf53_get_tuned_again+0x10e>
70000656:	4620      	mov	r0, r4
70000658:	f000 fbe8 	bl	70000e2c <__aeabi_f2d>
7000065c:	2200      	movs	r2, #0
7000065e:	4b1f      	ldr	r3, [pc, #124]	; (700006dc <jxf53_get_tuned_again+0x178>)
70000660:	f000 fa84 	bl	70000b6c <__aeabi_dsub>
70000664:	4602      	mov	r2, r0
70000666:	460b      	mov	r3, r1
70000668:	f000 fa82 	bl	70000b70 <__adddf3>
7000066c:	2200      	movs	r2, #0
7000066e:	4b1f      	ldr	r3, [pc, #124]	; (700006ec <jxf53_get_tuned_again+0x188>)
70000670:	e7c9      	b.n	70000606 <jxf53_get_tuned_again+0xa2>
70000672:	203f      	movs	r0, #63	; 0x3f
70000674:	e798      	b.n	700005a8 <jxf53_get_tuned_again+0x44>
70000676:	f1a4 0310 	sub.w	r3, r4, #16
7000067a:	2b0f      	cmp	r3, #15
7000067c:	d807      	bhi.n	7000068e <jxf53_get_tuned_again+0x12a>
7000067e:	f04f 5178 	mov.w	r1, #1040187392	; 0x3e000000
70000682:	f000 fdb1 	bl	700011e8 <__aeabi_fmul>
70000686:	4605      	mov	r5, r0
70000688:	2000      	movs	r0, #0
7000068a:	6035      	str	r5, [r6, #0]
7000068c:	bd70      	pop	{r4, r5, r6, pc}
7000068e:	f1a4 0320 	sub.w	r3, r4, #32
70000692:	2b0f      	cmp	r3, #15
70000694:	d80a      	bhi.n	700006ac <jxf53_get_tuned_again+0x148>
70000696:	f000 fbc9 	bl	70000e2c <__aeabi_f2d>
7000069a:	2200      	movs	r2, #0
7000069c:	4b14      	ldr	r3, [pc, #80]	; (700006f0 <jxf53_get_tuned_again+0x18c>)
7000069e:	f000 f883 	bl	700007a8 <__aeabi_dmul>
700006a2:	2200      	movs	r2, #0
700006a4:	4b0e      	ldr	r3, [pc, #56]	; (700006e0 <jxf53_get_tuned_again+0x17c>)
700006a6:	f000 fa61 	bl	70000b6c <__aeabi_dsub>
700006aa:	e78f      	b.n	700005cc <jxf53_get_tuned_again+0x68>
700006ac:	3c30      	subs	r4, #48	; 0x30
700006ae:	2c0f      	cmp	r4, #15
700006b0:	d8ea      	bhi.n	70000688 <jxf53_get_tuned_again+0x124>
700006b2:	f000 fbbb 	bl	70000e2c <__aeabi_f2d>
700006b6:	2200      	movs	r2, #0
700006b8:	4b0e      	ldr	r3, [pc, #56]	; (700006f4 <jxf53_get_tuned_again+0x190>)
700006ba:	f000 f875 	bl	700007a8 <__aeabi_dmul>
700006be:	2200      	movs	r2, #0
700006c0:	4b03      	ldr	r3, [pc, #12]	; (700006d0 <jxf53_get_tuned_again+0x16c>)
700006c2:	e7f0      	b.n	700006a6 <jxf53_get_tuned_again+0x142>
700006c4:	f06f 0015 	mvn.w	r0, #21
700006c8:	e7e0      	b.n	7000068c <jxf53_get_tuned_again+0x128>
700006ca:	bf00      	nop
700006cc:	3ff00000 	.word	0x3ff00000
700006d0:	40300000 	.word	0x40300000
700006d4:	7000004c 	.word	0x7000004c
700006d8:	3fb00000 	.word	0x3fb00000
700006dc:	40200000 	.word	0x40200000
700006e0:	40100000 	.word	0x40100000
700006e4:	40400000 	.word	0x40400000
700006e8:	417c0000 	.word	0x417c0000
700006ec:	40480000 	.word	0x40480000
700006f0:	3fd00000 	.word	0x3fd00000
700006f4:	3fe00000 	.word	0x3fe00000

700006f8 <clip_d_word>:
700006f8:	4603      	mov	r3, r0
700006fa:	4610      	mov	r0, r2
700006fc:	4293      	cmp	r3, r2
700006fe:	d803      	bhi.n	70000708 <clip_d_word+0x10>
70000700:	428b      	cmp	r3, r1
70000702:	bf38      	it	cc
70000704:	460b      	movcc	r3, r1
70000706:	4618      	mov	r0, r3
70000708:	4770      	bx	lr
	...

7000070c <rts_isp_get_sensor_ops>:
7000070c:	4800      	ldr	r0, [pc, #0]	; (70000710 <rts_isp_get_sensor_ops+0x4>)
7000070e:	4770      	bx	lr
70000710:	70000714 	.word	0x70000714

70000714 <jxf53_ops>:
70000714:	73000005 3566786a 00000033 00000000     ...sjxf53.......
	...
70000738:	7000026d 70000325 00000000 70000565     m..p%..p....e..p
70000748:	700003cd 700003e1 00000000 00000000     ...p...p........
70000758:	700003b9 00000000 00000000 00000000     ...p............
70000768:	70000495 00000000 00000000 00000000     ...p............
70000778:	700004dd 00000000 00000000 00000000     ...p............
70000788:	70000561 00000000 00000000 00000000     a..p............
	...

700007a8 <__aeabi_dmul>:
700007a8:	b570      	push	{r4, r5, r6, lr}
700007aa:	f04f 0cff 	mov.w	ip, #255	; 0xff
700007ae:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
700007b2:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
700007b6:	bf1d      	ittte	ne
700007b8:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
700007bc:	ea94 0f0c 	teqne	r4, ip
700007c0:	ea95 0f0c 	teqne	r5, ip
700007c4:	f000 f8de 	bleq	70000984 <__aeabi_dmul+0x1dc>
700007c8:	442c      	add	r4, r5
700007ca:	ea81 0603 	eor.w	r6, r1, r3
700007ce:	ea21 514c 	bic.w	r1, r1, ip, lsl #21
700007d2:	ea23 534c 	bic.w	r3, r3, ip, lsl #21
700007d6:	ea50 3501 	orrs.w	r5, r0, r1, lsl #12
700007da:	bf18      	it	ne
700007dc:	ea52 3503 	orrsne.w	r5, r2, r3, lsl #12
700007e0:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
700007e4:	f443 1380 	orr.w	r3, r3, #1048576	; 0x100000
700007e8:	d038      	beq.n	7000085c <__aeabi_dmul+0xb4>
700007ea:	fba0 ce02 	umull	ip, lr, r0, r2
700007ee:	f04f 0500 	mov.w	r5, #0
700007f2:	fbe1 e502 	umlal	lr, r5, r1, r2
700007f6:	f006 4200 	and.w	r2, r6, #2147483648	; 0x80000000
700007fa:	fbe0 e503 	umlal	lr, r5, r0, r3
700007fe:	f04f 0600 	mov.w	r6, #0
70000802:	fbe1 5603 	umlal	r5, r6, r1, r3
70000806:	f09c 0f00 	teq	ip, #0
7000080a:	bf18      	it	ne
7000080c:	f04e 0e01 	orrne.w	lr, lr, #1
70000810:	f1a4 04ff 	sub.w	r4, r4, #255	; 0xff
70000814:	f5b6 7f00 	cmp.w	r6, #512	; 0x200
70000818:	f564 7440 	sbc.w	r4, r4, #768	; 0x300
7000081c:	d204      	bcs.n	70000828 <__aeabi_dmul+0x80>
7000081e:	ea5f 0e4e 	movs.w	lr, lr, lsl #1
70000822:	416d      	adcs	r5, r5
70000824:	eb46 0606 	adc.w	r6, r6, r6
70000828:	ea42 21c6 	orr.w	r1, r2, r6, lsl #11
7000082c:	ea41 5155 	orr.w	r1, r1, r5, lsr #21
70000830:	ea4f 20c5 	mov.w	r0, r5, lsl #11
70000834:	ea40 505e 	orr.w	r0, r0, lr, lsr #21
70000838:	ea4f 2ece 	mov.w	lr, lr, lsl #11
7000083c:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
70000840:	bf88      	it	hi
70000842:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
70000846:	d81e      	bhi.n	70000886 <__aeabi_dmul+0xde>
70000848:	f1be 4f00 	cmp.w	lr, #2147483648	; 0x80000000
7000084c:	bf08      	it	eq
7000084e:	ea5f 0e50 	movseq.w	lr, r0, lsr #1
70000852:	f150 0000 	adcs.w	r0, r0, #0
70000856:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
7000085a:	bd70      	pop	{r4, r5, r6, pc}
7000085c:	f006 4600 	and.w	r6, r6, #2147483648	; 0x80000000
70000860:	ea46 0101 	orr.w	r1, r6, r1
70000864:	ea40 0002 	orr.w	r0, r0, r2
70000868:	ea81 0103 	eor.w	r1, r1, r3
7000086c:	ebb4 045c 	subs.w	r4, r4, ip, lsr #1
70000870:	bfc2      	ittt	gt
70000872:	ebd4 050c 	rsbsgt	r5, r4, ip
70000876:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
7000087a:	bd70      	popgt	{r4, r5, r6, pc}
7000087c:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70000880:	f04f 0e00 	mov.w	lr, #0
70000884:	3c01      	subs	r4, #1
70000886:	f300 80ab 	bgt.w	700009e0 <__aeabi_dmul+0x238>
7000088a:	f114 0f36 	cmn.w	r4, #54	; 0x36
7000088e:	bfde      	ittt	le
70000890:	2000      	movle	r0, #0
70000892:	f001 4100 	andle.w	r1, r1, #2147483648	; 0x80000000
70000896:	bd70      	pople	{r4, r5, r6, pc}
70000898:	f1c4 0400 	rsb	r4, r4, #0
7000089c:	3c20      	subs	r4, #32
7000089e:	da35      	bge.n	7000090c <__aeabi_dmul+0x164>
700008a0:	340c      	adds	r4, #12
700008a2:	dc1b      	bgt.n	700008dc <__aeabi_dmul+0x134>
700008a4:	f104 0414 	add.w	r4, r4, #20
700008a8:	f1c4 0520 	rsb	r5, r4, #32
700008ac:	fa00 f305 	lsl.w	r3, r0, r5
700008b0:	fa20 f004 	lsr.w	r0, r0, r4
700008b4:	fa01 f205 	lsl.w	r2, r1, r5
700008b8:	ea40 0002 	orr.w	r0, r0, r2
700008bc:	f001 4200 	and.w	r2, r1, #2147483648	; 0x80000000
700008c0:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
700008c4:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
700008c8:	fa21 f604 	lsr.w	r6, r1, r4
700008cc:	eb42 0106 	adc.w	r1, r2, r6
700008d0:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
700008d4:	bf08      	it	eq
700008d6:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
700008da:	bd70      	pop	{r4, r5, r6, pc}
700008dc:	f1c4 040c 	rsb	r4, r4, #12
700008e0:	f1c4 0520 	rsb	r5, r4, #32
700008e4:	fa00 f304 	lsl.w	r3, r0, r4
700008e8:	fa20 f005 	lsr.w	r0, r0, r5
700008ec:	fa01 f204 	lsl.w	r2, r1, r4
700008f0:	ea40 0002 	orr.w	r0, r0, r2
700008f4:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700008f8:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
700008fc:	f141 0100 	adc.w	r1, r1, #0
70000900:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70000904:	bf08      	it	eq
70000906:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
7000090a:	bd70      	pop	{r4, r5, r6, pc}
7000090c:	f1c4 0520 	rsb	r5, r4, #32
70000910:	fa00 f205 	lsl.w	r2, r0, r5
70000914:	ea4e 0e02 	orr.w	lr, lr, r2
70000918:	fa20 f304 	lsr.w	r3, r0, r4
7000091c:	fa01 f205 	lsl.w	r2, r1, r5
70000920:	ea43 0302 	orr.w	r3, r3, r2
70000924:	fa21 f004 	lsr.w	r0, r1, r4
70000928:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
7000092c:	fa21 f204 	lsr.w	r2, r1, r4
70000930:	ea20 0002 	bic.w	r0, r0, r2
70000934:	eb00 70d3 	add.w	r0, r0, r3, lsr #31
70000938:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
7000093c:	bf08      	it	eq
7000093e:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70000942:	bd70      	pop	{r4, r5, r6, pc}
70000944:	f094 0f00 	teq	r4, #0
70000948:	d10f      	bne.n	7000096a <__aeabi_dmul+0x1c2>
7000094a:	f001 4600 	and.w	r6, r1, #2147483648	; 0x80000000
7000094e:	0040      	lsls	r0, r0, #1
70000950:	eb41 0101 	adc.w	r1, r1, r1
70000954:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
70000958:	bf08      	it	eq
7000095a:	3c01      	subeq	r4, #1
7000095c:	d0f7      	beq.n	7000094e <__aeabi_dmul+0x1a6>
7000095e:	ea41 0106 	orr.w	r1, r1, r6
70000962:	f095 0f00 	teq	r5, #0
70000966:	bf18      	it	ne
70000968:	4770      	bxne	lr
7000096a:	f003 4600 	and.w	r6, r3, #2147483648	; 0x80000000
7000096e:	0052      	lsls	r2, r2, #1
70000970:	eb43 0303 	adc.w	r3, r3, r3
70000974:	f413 1f80 	tst.w	r3, #1048576	; 0x100000
70000978:	bf08      	it	eq
7000097a:	3d01      	subeq	r5, #1
7000097c:	d0f7      	beq.n	7000096e <__aeabi_dmul+0x1c6>
7000097e:	ea43 0306 	orr.w	r3, r3, r6
70000982:	4770      	bx	lr
70000984:	ea94 0f0c 	teq	r4, ip
70000988:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
7000098c:	bf18      	it	ne
7000098e:	ea95 0f0c 	teqne	r5, ip
70000992:	d00c      	beq.n	700009ae <__aeabi_dmul+0x206>
70000994:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
70000998:	bf18      	it	ne
7000099a:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
7000099e:	d1d1      	bne.n	70000944 <__aeabi_dmul+0x19c>
700009a0:	ea81 0103 	eor.w	r1, r1, r3
700009a4:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700009a8:	f04f 0000 	mov.w	r0, #0
700009ac:	bd70      	pop	{r4, r5, r6, pc}
700009ae:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
700009b2:	bf06      	itte	eq
700009b4:	4610      	moveq	r0, r2
700009b6:	4619      	moveq	r1, r3
700009b8:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
700009bc:	d019      	beq.n	700009f2 <__aeabi_dmul+0x24a>
700009be:	ea94 0f0c 	teq	r4, ip
700009c2:	d102      	bne.n	700009ca <__aeabi_dmul+0x222>
700009c4:	ea50 3601 	orrs.w	r6, r0, r1, lsl #12
700009c8:	d113      	bne.n	700009f2 <__aeabi_dmul+0x24a>
700009ca:	ea95 0f0c 	teq	r5, ip
700009ce:	d105      	bne.n	700009dc <__aeabi_dmul+0x234>
700009d0:	ea52 3603 	orrs.w	r6, r2, r3, lsl #12
700009d4:	bf1c      	itt	ne
700009d6:	4610      	movne	r0, r2
700009d8:	4619      	movne	r1, r3
700009da:	d10a      	bne.n	700009f2 <__aeabi_dmul+0x24a>
700009dc:	ea81 0103 	eor.w	r1, r1, r3
700009e0:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700009e4:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
700009e8:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
700009ec:	f04f 0000 	mov.w	r0, #0
700009f0:	bd70      	pop	{r4, r5, r6, pc}
700009f2:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
700009f6:	f441 0178 	orr.w	r1, r1, #16252928	; 0xf80000
700009fa:	bd70      	pop	{r4, r5, r6, pc}
700009fc:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000a00:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000a04:	bf1e      	ittt	ne
70000a06:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000a0a:	ea92 0f0c 	teqne	r2, ip
70000a0e:	ea93 0f0c 	teqne	r3, ip
70000a12:	d06f      	beq.n	70000af4 <__aeabi_dmul+0x34c>
70000a14:	441a      	add	r2, r3
70000a16:	ea80 0c01 	eor.w	ip, r0, r1
70000a1a:	0240      	lsls	r0, r0, #9
70000a1c:	bf18      	it	ne
70000a1e:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000a22:	d01e      	beq.n	70000a62 <__aeabi_dmul+0x2ba>
70000a24:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000a28:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000a2c:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000a30:	fba0 3101 	umull	r3, r1, r0, r1
70000a34:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000a38:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000a3c:	bf3e      	ittt	cc
70000a3e:	0049      	lslcc	r1, r1, #1
70000a40:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000a44:	005b      	lslcc	r3, r3, #1
70000a46:	ea40 0001 	orr.w	r0, r0, r1
70000a4a:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000a4e:	2afd      	cmp	r2, #253	; 0xfd
70000a50:	d81d      	bhi.n	70000a8e <__aeabi_dmul+0x2e6>
70000a52:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000a56:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000a5a:	bf08      	it	eq
70000a5c:	f020 0001 	biceq.w	r0, r0, #1
70000a60:	4770      	bx	lr
70000a62:	f090 0f00 	teq	r0, #0
70000a66:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000a6a:	bf08      	it	eq
70000a6c:	0249      	lsleq	r1, r1, #9
70000a6e:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000a72:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000a76:	3a7f      	subs	r2, #127	; 0x7f
70000a78:	bfc2      	ittt	gt
70000a7a:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000a7e:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000a82:	4770      	bxgt	lr
70000a84:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000a88:	f04f 0300 	mov.w	r3, #0
70000a8c:	3a01      	subs	r2, #1
70000a8e:	dc5d      	bgt.n	70000b4c <__aeabi_dmul+0x3a4>
70000a90:	f112 0f19 	cmn.w	r2, #25
70000a94:	bfdc      	itt	le
70000a96:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000a9a:	4770      	bxle	lr
70000a9c:	f1c2 0200 	rsb	r2, r2, #0
70000aa0:	0041      	lsls	r1, r0, #1
70000aa2:	fa21 f102 	lsr.w	r1, r1, r2
70000aa6:	f1c2 0220 	rsb	r2, r2, #32
70000aaa:	fa00 fc02 	lsl.w	ip, r0, r2
70000aae:	ea5f 0031 	movs.w	r0, r1, rrx
70000ab2:	f140 0000 	adc.w	r0, r0, #0
70000ab6:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000aba:	bf08      	it	eq
70000abc:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000ac0:	4770      	bx	lr
70000ac2:	f092 0f00 	teq	r2, #0
70000ac6:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000aca:	bf02      	ittt	eq
70000acc:	0040      	lsleq	r0, r0, #1
70000ace:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000ad2:	3a01      	subeq	r2, #1
70000ad4:	d0f9      	beq.n	70000aca <__aeabi_dmul+0x322>
70000ad6:	ea40 000c 	orr.w	r0, r0, ip
70000ada:	f093 0f00 	teq	r3, #0
70000ade:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000ae2:	bf02      	ittt	eq
70000ae4:	0049      	lsleq	r1, r1, #1
70000ae6:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000aea:	3b01      	subeq	r3, #1
70000aec:	d0f9      	beq.n	70000ae2 <__aeabi_dmul+0x33a>
70000aee:	ea41 010c 	orr.w	r1, r1, ip
70000af2:	e78f      	b.n	70000a14 <__aeabi_dmul+0x26c>
70000af4:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000af8:	ea92 0f0c 	teq	r2, ip
70000afc:	bf18      	it	ne
70000afe:	ea93 0f0c 	teqne	r3, ip
70000b02:	d00a      	beq.n	70000b1a <__aeabi_dmul+0x372>
70000b04:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000b08:	bf18      	it	ne
70000b0a:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000b0e:	d1d8      	bne.n	70000ac2 <__aeabi_dmul+0x31a>
70000b10:	ea80 0001 	eor.w	r0, r0, r1
70000b14:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000b18:	4770      	bx	lr
70000b1a:	f090 0f00 	teq	r0, #0
70000b1e:	bf17      	itett	ne
70000b20:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000b24:	4608      	moveq	r0, r1
70000b26:	f091 0f00 	teqne	r1, #0
70000b2a:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000b2e:	d014      	beq.n	70000b5a <__aeabi_dmul+0x3b2>
70000b30:	ea92 0f0c 	teq	r2, ip
70000b34:	d101      	bne.n	70000b3a <__aeabi_dmul+0x392>
70000b36:	0242      	lsls	r2, r0, #9
70000b38:	d10f      	bne.n	70000b5a <__aeabi_dmul+0x3b2>
70000b3a:	ea93 0f0c 	teq	r3, ip
70000b3e:	d103      	bne.n	70000b48 <__aeabi_dmul+0x3a0>
70000b40:	024b      	lsls	r3, r1, #9
70000b42:	bf18      	it	ne
70000b44:	4608      	movne	r0, r1
70000b46:	d108      	bne.n	70000b5a <__aeabi_dmul+0x3b2>
70000b48:	ea80 0001 	eor.w	r0, r0, r1
70000b4c:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000b50:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000b54:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000b58:	4770      	bx	lr
70000b5a:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000b5e:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000b62:	4770      	bx	lr

70000b64 <__aeabi_drsub>:
70000b64:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000
70000b68:	e002      	b.n	70000b70 <__adddf3>
70000b6a:	bf00      	nop

70000b6c <__aeabi_dsub>:
70000b6c:	f083 4300 	eor.w	r3, r3, #2147483648	; 0x80000000

70000b70 <__adddf3>:
70000b70:	b530      	push	{r4, r5, lr}
70000b72:	ea4f 0441 	mov.w	r4, r1, lsl #1
70000b76:	ea4f 0543 	mov.w	r5, r3, lsl #1
70000b7a:	ea94 0f05 	teq	r4, r5
70000b7e:	bf08      	it	eq
70000b80:	ea90 0f02 	teqeq	r0, r2
70000b84:	bf1f      	itttt	ne
70000b86:	ea54 0c00 	orrsne.w	ip, r4, r0
70000b8a:	ea55 0c02 	orrsne.w	ip, r5, r2
70000b8e:	ea7f 5c64 	mvnsne.w	ip, r4, asr #21
70000b92:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70000b96:	f000 80e2 	beq.w	70000d5e <__adddf3+0x1ee>
70000b9a:	ea4f 5454 	mov.w	r4, r4, lsr #21
70000b9e:	ebd4 5555 	rsbs	r5, r4, r5, lsr #21
70000ba2:	bfb8      	it	lt
70000ba4:	426d      	neglt	r5, r5
70000ba6:	dd0c      	ble.n	70000bc2 <__adddf3+0x52>
70000ba8:	442c      	add	r4, r5
70000baa:	ea80 0202 	eor.w	r2, r0, r2
70000bae:	ea81 0303 	eor.w	r3, r1, r3
70000bb2:	ea82 0000 	eor.w	r0, r2, r0
70000bb6:	ea83 0101 	eor.w	r1, r3, r1
70000bba:	ea80 0202 	eor.w	r2, r0, r2
70000bbe:	ea81 0303 	eor.w	r3, r1, r3
70000bc2:	2d36      	cmp	r5, #54	; 0x36
70000bc4:	bf88      	it	hi
70000bc6:	bd30      	pophi	{r4, r5, pc}
70000bc8:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000bcc:	ea4f 3101 	mov.w	r1, r1, lsl #12
70000bd0:	f44f 1c80 	mov.w	ip, #1048576	; 0x100000
70000bd4:	ea4c 3111 	orr.w	r1, ip, r1, lsr #12
70000bd8:	d002      	beq.n	70000be0 <__adddf3+0x70>
70000bda:	4240      	negs	r0, r0
70000bdc:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000be0:	f013 4f00 	tst.w	r3, #2147483648	; 0x80000000
70000be4:	ea4f 3303 	mov.w	r3, r3, lsl #12
70000be8:	ea4c 3313 	orr.w	r3, ip, r3, lsr #12
70000bec:	d002      	beq.n	70000bf4 <__adddf3+0x84>
70000bee:	4252      	negs	r2, r2
70000bf0:	eb63 0343 	sbc.w	r3, r3, r3, lsl #1
70000bf4:	ea94 0f05 	teq	r4, r5
70000bf8:	f000 80a7 	beq.w	70000d4a <__adddf3+0x1da>
70000bfc:	f1a4 0401 	sub.w	r4, r4, #1
70000c00:	f1d5 0e20 	rsbs	lr, r5, #32
70000c04:	db0d      	blt.n	70000c22 <__adddf3+0xb2>
70000c06:	fa02 fc0e 	lsl.w	ip, r2, lr
70000c0a:	fa22 f205 	lsr.w	r2, r2, r5
70000c0e:	1880      	adds	r0, r0, r2
70000c10:	f141 0100 	adc.w	r1, r1, #0
70000c14:	fa03 f20e 	lsl.w	r2, r3, lr
70000c18:	1880      	adds	r0, r0, r2
70000c1a:	fa43 f305 	asr.w	r3, r3, r5
70000c1e:	4159      	adcs	r1, r3
70000c20:	e00e      	b.n	70000c40 <__adddf3+0xd0>
70000c22:	f1a5 0520 	sub.w	r5, r5, #32
70000c26:	f10e 0e20 	add.w	lr, lr, #32
70000c2a:	2a01      	cmp	r2, #1
70000c2c:	fa03 fc0e 	lsl.w	ip, r3, lr
70000c30:	bf28      	it	cs
70000c32:	f04c 0c02 	orrcs.w	ip, ip, #2
70000c36:	fa43 f305 	asr.w	r3, r3, r5
70000c3a:	18c0      	adds	r0, r0, r3
70000c3c:	eb51 71e3 	adcs.w	r1, r1, r3, asr #31
70000c40:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000c44:	d507      	bpl.n	70000c56 <__adddf3+0xe6>
70000c46:	f04f 0e00 	mov.w	lr, #0
70000c4a:	f1dc 0c00 	rsbs	ip, ip, #0
70000c4e:	eb7e 0000 	sbcs.w	r0, lr, r0
70000c52:	eb6e 0101 	sbc.w	r1, lr, r1
70000c56:	f5b1 1f80 	cmp.w	r1, #1048576	; 0x100000
70000c5a:	d31b      	bcc.n	70000c94 <__adddf3+0x124>
70000c5c:	f5b1 1f00 	cmp.w	r1, #2097152	; 0x200000
70000c60:	d30c      	bcc.n	70000c7c <__adddf3+0x10c>
70000c62:	0849      	lsrs	r1, r1, #1
70000c64:	ea5f 0030 	movs.w	r0, r0, rrx
70000c68:	ea4f 0c3c 	mov.w	ip, ip, rrx
70000c6c:	f104 0401 	add.w	r4, r4, #1
70000c70:	ea4f 5244 	mov.w	r2, r4, lsl #21
70000c74:	f512 0f80 	cmn.w	r2, #4194304	; 0x400000
70000c78:	f080 809a 	bcs.w	70000db0 <__adddf3+0x240>
70000c7c:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000c80:	bf08      	it	eq
70000c82:	ea5f 0c50 	movseq.w	ip, r0, lsr #1
70000c86:	f150 0000 	adcs.w	r0, r0, #0
70000c8a:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
70000c8e:	ea41 0105 	orr.w	r1, r1, r5
70000c92:	bd30      	pop	{r4, r5, pc}
70000c94:	ea5f 0c4c 	movs.w	ip, ip, lsl #1
70000c98:	4140      	adcs	r0, r0
70000c9a:	eb41 0101 	adc.w	r1, r1, r1
70000c9e:	3c01      	subs	r4, #1
70000ca0:	bf28      	it	cs
70000ca2:	f5b1 1f80 	cmpcs.w	r1, #1048576	; 0x100000
70000ca6:	d2e9      	bcs.n	70000c7c <__adddf3+0x10c>
70000ca8:	f091 0f00 	teq	r1, #0
70000cac:	bf04      	itt	eq
70000cae:	4601      	moveq	r1, r0
70000cb0:	2000      	moveq	r0, #0
70000cb2:	fab1 f381 	clz	r3, r1
70000cb6:	bf08      	it	eq
70000cb8:	3320      	addeq	r3, #32
70000cba:	f1a3 030b 	sub.w	r3, r3, #11
70000cbe:	f1b3 0220 	subs.w	r2, r3, #32
70000cc2:	da0c      	bge.n	70000cde <__adddf3+0x16e>
70000cc4:	320c      	adds	r2, #12
70000cc6:	dd08      	ble.n	70000cda <__adddf3+0x16a>
70000cc8:	f102 0c14 	add.w	ip, r2, #20
70000ccc:	f1c2 020c 	rsb	r2, r2, #12
70000cd0:	fa01 f00c 	lsl.w	r0, r1, ip
70000cd4:	fa21 f102 	lsr.w	r1, r1, r2
70000cd8:	e00c      	b.n	70000cf4 <__adddf3+0x184>
70000cda:	f102 0214 	add.w	r2, r2, #20
70000cde:	bfd8      	it	le
70000ce0:	f1c2 0c20 	rsble	ip, r2, #32
70000ce4:	fa01 f102 	lsl.w	r1, r1, r2
70000ce8:	fa20 fc0c 	lsr.w	ip, r0, ip
70000cec:	bfdc      	itt	le
70000cee:	ea41 010c 	orrle.w	r1, r1, ip
70000cf2:	4090      	lslle	r0, r2
70000cf4:	1ae4      	subs	r4, r4, r3
70000cf6:	bfa2      	ittt	ge
70000cf8:	eb01 5104 	addge.w	r1, r1, r4, lsl #20
70000cfc:	4329      	orrge	r1, r5
70000cfe:	bd30      	popge	{r4, r5, pc}
70000d00:	ea6f 0404 	mvn.w	r4, r4
70000d04:	3c1f      	subs	r4, #31
70000d06:	da1c      	bge.n	70000d42 <__adddf3+0x1d2>
70000d08:	340c      	adds	r4, #12
70000d0a:	dc0e      	bgt.n	70000d2a <__adddf3+0x1ba>
70000d0c:	f104 0414 	add.w	r4, r4, #20
70000d10:	f1c4 0220 	rsb	r2, r4, #32
70000d14:	fa20 f004 	lsr.w	r0, r0, r4
70000d18:	fa01 f302 	lsl.w	r3, r1, r2
70000d1c:	ea40 0003 	orr.w	r0, r0, r3
70000d20:	fa21 f304 	lsr.w	r3, r1, r4
70000d24:	ea45 0103 	orr.w	r1, r5, r3
70000d28:	bd30      	pop	{r4, r5, pc}
70000d2a:	f1c4 040c 	rsb	r4, r4, #12
70000d2e:	f1c4 0220 	rsb	r2, r4, #32
70000d32:	fa20 f002 	lsr.w	r0, r0, r2
70000d36:	fa01 f304 	lsl.w	r3, r1, r4
70000d3a:	ea40 0003 	orr.w	r0, r0, r3
70000d3e:	4629      	mov	r1, r5
70000d40:	bd30      	pop	{r4, r5, pc}
70000d42:	fa21 f004 	lsr.w	r0, r1, r4
70000d46:	4629      	mov	r1, r5
70000d48:	bd30      	pop	{r4, r5, pc}
70000d4a:	f094 0f00 	teq	r4, #0
70000d4e:	f483 1380 	eor.w	r3, r3, #1048576	; 0x100000
70000d52:	bf06      	itte	eq
70000d54:	f481 1180 	eoreq.w	r1, r1, #1048576	; 0x100000
70000d58:	3401      	addeq	r4, #1
70000d5a:	3d01      	subne	r5, #1
70000d5c:	e74e      	b.n	70000bfc <__adddf3+0x8c>
70000d5e:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70000d62:	bf18      	it	ne
70000d64:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70000d68:	d029      	beq.n	70000dbe <__adddf3+0x24e>
70000d6a:	ea94 0f05 	teq	r4, r5
70000d6e:	bf08      	it	eq
70000d70:	ea90 0f02 	teqeq	r0, r2
70000d74:	d005      	beq.n	70000d82 <__adddf3+0x212>
70000d76:	ea54 0c00 	orrs.w	ip, r4, r0
70000d7a:	bf04      	itt	eq
70000d7c:	4619      	moveq	r1, r3
70000d7e:	4610      	moveq	r0, r2
70000d80:	bd30      	pop	{r4, r5, pc}
70000d82:	ea91 0f03 	teq	r1, r3
70000d86:	bf1e      	ittt	ne
70000d88:	2100      	movne	r1, #0
70000d8a:	2000      	movne	r0, #0
70000d8c:	bd30      	popne	{r4, r5, pc}
70000d8e:	ea5f 5c54 	movs.w	ip, r4, lsr #21
70000d92:	d105      	bne.n	70000da0 <__adddf3+0x230>
70000d94:	0040      	lsls	r0, r0, #1
70000d96:	4149      	adcs	r1, r1
70000d98:	bf28      	it	cs
70000d9a:	f041 4100 	orrcs.w	r1, r1, #2147483648	; 0x80000000
70000d9e:	bd30      	pop	{r4, r5, pc}
70000da0:	f514 0480 	adds.w	r4, r4, #4194304	; 0x400000
70000da4:	bf3c      	itt	cc
70000da6:	f501 1180 	addcc.w	r1, r1, #1048576	; 0x100000
70000daa:	bd30      	popcc	{r4, r5, pc}
70000dac:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000db0:	f045 41fe 	orr.w	r1, r5, #2130706432	; 0x7f000000
70000db4:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
70000db8:	f04f 0000 	mov.w	r0, #0
70000dbc:	bd30      	pop	{r4, r5, pc}
70000dbe:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70000dc2:	bf1a      	itte	ne
70000dc4:	4619      	movne	r1, r3
70000dc6:	4610      	movne	r0, r2
70000dc8:	ea7f 5c65 	mvnseq.w	ip, r5, asr #21
70000dcc:	bf1c      	itt	ne
70000dce:	460b      	movne	r3, r1
70000dd0:	4602      	movne	r2, r0
70000dd2:	ea50 3401 	orrs.w	r4, r0, r1, lsl #12
70000dd6:	bf06      	itte	eq
70000dd8:	ea52 3503 	orrseq.w	r5, r2, r3, lsl #12
70000ddc:	ea91 0f03 	teqeq	r1, r3
70000de0:	f441 2100 	orrne.w	r1, r1, #524288	; 0x80000
70000de4:	bd30      	pop	{r4, r5, pc}
70000de6:	bf00      	nop

70000de8 <__aeabi_ui2d>:
70000de8:	f090 0f00 	teq	r0, #0
70000dec:	bf04      	itt	eq
70000dee:	2100      	moveq	r1, #0
70000df0:	4770      	bxeq	lr
70000df2:	b530      	push	{r4, r5, lr}
70000df4:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000df8:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000dfc:	f04f 0500 	mov.w	r5, #0
70000e00:	f04f 0100 	mov.w	r1, #0
70000e04:	e750      	b.n	70000ca8 <__adddf3+0x138>
70000e06:	bf00      	nop

70000e08 <__aeabi_i2d>:
70000e08:	f090 0f00 	teq	r0, #0
70000e0c:	bf04      	itt	eq
70000e0e:	2100      	moveq	r1, #0
70000e10:	4770      	bxeq	lr
70000e12:	b530      	push	{r4, r5, lr}
70000e14:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000e18:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000e1c:	f010 4500 	ands.w	r5, r0, #2147483648	; 0x80000000
70000e20:	bf48      	it	mi
70000e22:	4240      	negmi	r0, r0
70000e24:	f04f 0100 	mov.w	r1, #0
70000e28:	e73e      	b.n	70000ca8 <__adddf3+0x138>
70000e2a:	bf00      	nop

70000e2c <__aeabi_f2d>:
70000e2c:	0042      	lsls	r2, r0, #1
70000e2e:	ea4f 01e2 	mov.w	r1, r2, asr #3
70000e32:	ea4f 0131 	mov.w	r1, r1, rrx
70000e36:	ea4f 7002 	mov.w	r0, r2, lsl #28
70000e3a:	bf1f      	itttt	ne
70000e3c:	f012 437f 	andsne.w	r3, r2, #4278190080	; 0xff000000
70000e40:	f093 4f7f 	teqne	r3, #4278190080	; 0xff000000
70000e44:	f081 5160 	eorne.w	r1, r1, #939524096	; 0x38000000
70000e48:	4770      	bxne	lr
70000e4a:	f032 427f 	bics.w	r2, r2, #4278190080	; 0xff000000
70000e4e:	bf08      	it	eq
70000e50:	4770      	bxeq	lr
70000e52:	f093 4f7f 	teq	r3, #4278190080	; 0xff000000
70000e56:	bf04      	itt	eq
70000e58:	f441 2100 	orreq.w	r1, r1, #524288	; 0x80000
70000e5c:	4770      	bxeq	lr
70000e5e:	b530      	push	{r4, r5, lr}
70000e60:	f44f 7460 	mov.w	r4, #896	; 0x380
70000e64:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000e68:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
70000e6c:	e71c      	b.n	70000ca8 <__adddf3+0x138>
70000e6e:	bf00      	nop

70000e70 <__aeabi_ul2d>:
70000e70:	ea50 0201 	orrs.w	r2, r0, r1
70000e74:	bf08      	it	eq
70000e76:	4770      	bxeq	lr
70000e78:	b530      	push	{r4, r5, lr}
70000e7a:	f04f 0500 	mov.w	r5, #0
70000e7e:	e00a      	b.n	70000e96 <__aeabi_l2d+0x16>

70000e80 <__aeabi_l2d>:
70000e80:	ea50 0201 	orrs.w	r2, r0, r1
70000e84:	bf08      	it	eq
70000e86:	4770      	bxeq	lr
70000e88:	b530      	push	{r4, r5, lr}
70000e8a:	f011 4500 	ands.w	r5, r1, #2147483648	; 0x80000000
70000e8e:	d502      	bpl.n	70000e96 <__aeabi_l2d+0x16>
70000e90:	4240      	negs	r0, r0
70000e92:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000e96:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000e9a:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000e9e:	ea5f 5c91 	movs.w	ip, r1, lsr #22
70000ea2:	f43f aed8 	beq.w	70000c56 <__adddf3+0xe6>
70000ea6:	f04f 0203 	mov.w	r2, #3
70000eaa:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70000eae:	bf18      	it	ne
70000eb0:	3203      	addne	r2, #3
70000eb2:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70000eb6:	bf18      	it	ne
70000eb8:	3203      	addne	r2, #3
70000eba:	eb02 02dc 	add.w	r2, r2, ip, lsr #3
70000ebe:	f1c2 0320 	rsb	r3, r2, #32
70000ec2:	fa00 fc03 	lsl.w	ip, r0, r3
70000ec6:	fa20 f002 	lsr.w	r0, r0, r2
70000eca:	fa01 fe03 	lsl.w	lr, r1, r3
70000ece:	ea40 000e 	orr.w	r0, r0, lr
70000ed2:	fa21 f102 	lsr.w	r1, r1, r2
70000ed6:	4414      	add	r4, r2
70000ed8:	e6bd      	b.n	70000c56 <__adddf3+0xe6>
70000eda:	bf00      	nop

70000edc <__aeabi_d2iz>:
70000edc:	ea4f 0241 	mov.w	r2, r1, lsl #1
70000ee0:	f512 1200 	adds.w	r2, r2, #2097152	; 0x200000
70000ee4:	d215      	bcs.n	70000f12 <__aeabi_d2iz+0x36>
70000ee6:	d511      	bpl.n	70000f0c <__aeabi_d2iz+0x30>
70000ee8:	f46f 7378 	mvn.w	r3, #992	; 0x3e0
70000eec:	ebb3 5262 	subs.w	r2, r3, r2, asr #21
70000ef0:	d912      	bls.n	70000f18 <__aeabi_d2iz+0x3c>
70000ef2:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70000ef6:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000efa:	ea43 5350 	orr.w	r3, r3, r0, lsr #21
70000efe:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000f02:	fa23 f002 	lsr.w	r0, r3, r2
70000f06:	bf18      	it	ne
70000f08:	4240      	negne	r0, r0
70000f0a:	4770      	bx	lr
70000f0c:	f04f 0000 	mov.w	r0, #0
70000f10:	4770      	bx	lr
70000f12:	ea50 3001 	orrs.w	r0, r0, r1, lsl #12
70000f16:	d105      	bne.n	70000f24 <__aeabi_d2iz+0x48>
70000f18:	f011 4000 	ands.w	r0, r1, #2147483648	; 0x80000000
70000f1c:	bf08      	it	eq
70000f1e:	f06f 4000 	mvneq.w	r0, #2147483648	; 0x80000000
70000f22:	4770      	bx	lr
70000f24:	f04f 0000 	mov.w	r0, #0
70000f28:	4770      	bx	lr
70000f2a:	bf00      	nop

70000f2c <__aeabi_d2f>:
70000f2c:	ea4f 0241 	mov.w	r2, r1, lsl #1
70000f30:	f1b2 43e0 	subs.w	r3, r2, #1879048192	; 0x70000000
70000f34:	bf24      	itt	cs
70000f36:	f5b3 1c00 	subscs.w	ip, r3, #2097152	; 0x200000
70000f3a:	f1dc 5cfe 	rsbscs	ip, ip, #532676608	; 0x1fc00000
70000f3e:	d90d      	bls.n	70000f5c <__aeabi_d2f+0x30>
70000f40:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000f44:	ea4f 02c0 	mov.w	r2, r0, lsl #3
70000f48:	ea4c 7050 	orr.w	r0, ip, r0, lsr #29
70000f4c:	f1b2 4f00 	cmp.w	r2, #2147483648	; 0x80000000
70000f50:	eb40 0083 	adc.w	r0, r0, r3, lsl #2
70000f54:	bf08      	it	eq
70000f56:	f020 0001 	biceq.w	r0, r0, #1
70000f5a:	4770      	bx	lr
70000f5c:	f011 4f80 	tst.w	r1, #1073741824	; 0x40000000
70000f60:	d121      	bne.n	70000fa6 <__aeabi_d2f+0x7a>
70000f62:	f113 7238 	adds.w	r2, r3, #48234496	; 0x2e00000
70000f66:	bfbc      	itt	lt
70000f68:	f001 4000 	andlt.w	r0, r1, #2147483648	; 0x80000000
70000f6c:	4770      	bxlt	lr
70000f6e:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70000f72:	ea4f 5252 	mov.w	r2, r2, lsr #21
70000f76:	f1c2 0218 	rsb	r2, r2, #24
70000f7a:	f1c2 0c20 	rsb	ip, r2, #32
70000f7e:	fa10 f30c 	lsls.w	r3, r0, ip
70000f82:	fa20 f002 	lsr.w	r0, r0, r2
70000f86:	bf18      	it	ne
70000f88:	f040 0001 	orrne.w	r0, r0, #1
70000f8c:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70000f90:	ea4f 23d3 	mov.w	r3, r3, lsr #11
70000f94:	fa03 fc0c 	lsl.w	ip, r3, ip
70000f98:	ea40 000c 	orr.w	r0, r0, ip
70000f9c:	fa23 f302 	lsr.w	r3, r3, r2
70000fa0:	ea4f 0343 	mov.w	r3, r3, lsl #1
70000fa4:	e7cc      	b.n	70000f40 <__aeabi_d2f+0x14>
70000fa6:	ea7f 5362 	mvns.w	r3, r2, asr #21
70000faa:	d107      	bne.n	70000fbc <__aeabi_d2f+0x90>
70000fac:	ea50 3301 	orrs.w	r3, r0, r1, lsl #12
70000fb0:	bf1e      	ittt	ne
70000fb2:	f04f 40fe 	movne.w	r0, #2130706432	; 0x7f000000
70000fb6:	f440 0040 	orrne.w	r0, r0, #12582912	; 0xc00000
70000fba:	4770      	bxne	lr
70000fbc:	f001 4000 	and.w	r0, r1, #2147483648	; 0x80000000
70000fc0:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000fc4:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000fc8:	4770      	bx	lr
70000fca:	bf00      	nop

70000fcc <__aeabi_frsub>:
70000fcc:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70000fd0:	e002      	b.n	70000fd8 <__addsf3>
70000fd2:	bf00      	nop

70000fd4 <__aeabi_fsub>:
70000fd4:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

70000fd8 <__addsf3>:
70000fd8:	0042      	lsls	r2, r0, #1
70000fda:	bf1f      	itttt	ne
70000fdc:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70000fe0:	ea92 0f03 	teqne	r2, r3
70000fe4:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
70000fe8:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000fec:	d06a      	beq.n	700010c4 <__addsf3+0xec>
70000fee:	ea4f 6212 	mov.w	r2, r2, lsr #24
70000ff2:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
70000ff6:	bfc1      	itttt	gt
70000ff8:	18d2      	addgt	r2, r2, r3
70000ffa:	4041      	eorgt	r1, r0
70000ffc:	4048      	eorgt	r0, r1
70000ffe:	4041      	eorgt	r1, r0
70001000:	bfb8      	it	lt
70001002:	425b      	neglt	r3, r3
70001004:	2b19      	cmp	r3, #25
70001006:	bf88      	it	hi
70001008:	4770      	bxhi	lr
7000100a:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
7000100e:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001012:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
70001016:	bf18      	it	ne
70001018:	4240      	negne	r0, r0
7000101a:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
7000101e:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
70001022:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
70001026:	bf18      	it	ne
70001028:	4249      	negne	r1, r1
7000102a:	ea92 0f03 	teq	r2, r3
7000102e:	d03f      	beq.n	700010b0 <__addsf3+0xd8>
70001030:	f1a2 0201 	sub.w	r2, r2, #1
70001034:	fa41 fc03 	asr.w	ip, r1, r3
70001038:	eb10 000c 	adds.w	r0, r0, ip
7000103c:	f1c3 0320 	rsb	r3, r3, #32
70001040:	fa01 f103 	lsl.w	r1, r1, r3
70001044:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70001048:	d502      	bpl.n	70001050 <__addsf3+0x78>
7000104a:	4249      	negs	r1, r1
7000104c:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70001050:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70001054:	d313      	bcc.n	7000107e <__addsf3+0xa6>
70001056:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
7000105a:	d306      	bcc.n	7000106a <__addsf3+0x92>
7000105c:	0840      	lsrs	r0, r0, #1
7000105e:	ea4f 0131 	mov.w	r1, r1, rrx
70001062:	f102 0201 	add.w	r2, r2, #1
70001066:	2afe      	cmp	r2, #254	; 0xfe
70001068:	d251      	bcs.n	7000110e <__addsf3+0x136>
7000106a:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
7000106e:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70001072:	bf08      	it	eq
70001074:	f020 0001 	biceq.w	r0, r0, #1
70001078:	ea40 0003 	orr.w	r0, r0, r3
7000107c:	4770      	bx	lr
7000107e:	0049      	lsls	r1, r1, #1
70001080:	eb40 0000 	adc.w	r0, r0, r0
70001084:	3a01      	subs	r2, #1
70001086:	bf28      	it	cs
70001088:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
7000108c:	d2ed      	bcs.n	7000106a <__addsf3+0x92>
7000108e:	fab0 fc80 	clz	ip, r0
70001092:	f1ac 0c08 	sub.w	ip, ip, #8
70001096:	ebb2 020c 	subs.w	r2, r2, ip
7000109a:	fa00 f00c 	lsl.w	r0, r0, ip
7000109e:	bfaa      	itet	ge
700010a0:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
700010a4:	4252      	neglt	r2, r2
700010a6:	4318      	orrge	r0, r3
700010a8:	bfbc      	itt	lt
700010aa:	40d0      	lsrlt	r0, r2
700010ac:	4318      	orrlt	r0, r3
700010ae:	4770      	bx	lr
700010b0:	f092 0f00 	teq	r2, #0
700010b4:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
700010b8:	bf06      	itte	eq
700010ba:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
700010be:	3201      	addeq	r2, #1
700010c0:	3b01      	subne	r3, #1
700010c2:	e7b5      	b.n	70001030 <__addsf3+0x58>
700010c4:	ea4f 0341 	mov.w	r3, r1, lsl #1
700010c8:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700010cc:	bf18      	it	ne
700010ce:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700010d2:	d021      	beq.n	70001118 <__addsf3+0x140>
700010d4:	ea92 0f03 	teq	r2, r3
700010d8:	d004      	beq.n	700010e4 <__addsf3+0x10c>
700010da:	f092 0f00 	teq	r2, #0
700010de:	bf08      	it	eq
700010e0:	4608      	moveq	r0, r1
700010e2:	4770      	bx	lr
700010e4:	ea90 0f01 	teq	r0, r1
700010e8:	bf1c      	itt	ne
700010ea:	2000      	movne	r0, #0
700010ec:	4770      	bxne	lr
700010ee:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
700010f2:	d104      	bne.n	700010fe <__addsf3+0x126>
700010f4:	0040      	lsls	r0, r0, #1
700010f6:	bf28      	it	cs
700010f8:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
700010fc:	4770      	bx	lr
700010fe:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
70001102:	bf3c      	itt	cc
70001104:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
70001108:	4770      	bxcc	lr
7000110a:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
7000110e:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
70001112:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001116:	4770      	bx	lr
70001118:	ea7f 6222 	mvns.w	r2, r2, asr #24
7000111c:	bf16      	itet	ne
7000111e:	4608      	movne	r0, r1
70001120:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70001124:	4601      	movne	r1, r0
70001126:	0242      	lsls	r2, r0, #9
70001128:	bf06      	itte	eq
7000112a:	ea5f 2341 	movseq.w	r3, r1, lsl #9
7000112e:	ea90 0f01 	teqeq	r0, r1
70001132:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
70001136:	4770      	bx	lr

70001138 <__aeabi_ui2f>:
70001138:	f04f 0300 	mov.w	r3, #0
7000113c:	e004      	b.n	70001148 <__aeabi_i2f+0x8>
7000113e:	bf00      	nop

70001140 <__aeabi_i2f>:
70001140:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70001144:	bf48      	it	mi
70001146:	4240      	negmi	r0, r0
70001148:	ea5f 0c00 	movs.w	ip, r0
7000114c:	bf08      	it	eq
7000114e:	4770      	bxeq	lr
70001150:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70001154:	4601      	mov	r1, r0
70001156:	f04f 0000 	mov.w	r0, #0
7000115a:	e01c      	b.n	70001196 <__aeabi_l2f+0x2a>

7000115c <__aeabi_ul2f>:
7000115c:	ea50 0201 	orrs.w	r2, r0, r1
70001160:	bf08      	it	eq
70001162:	4770      	bxeq	lr
70001164:	f04f 0300 	mov.w	r3, #0
70001168:	e00a      	b.n	70001180 <__aeabi_l2f+0x14>
7000116a:	bf00      	nop

7000116c <__aeabi_l2f>:
7000116c:	ea50 0201 	orrs.w	r2, r0, r1
70001170:	bf08      	it	eq
70001172:	4770      	bxeq	lr
70001174:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70001178:	d502      	bpl.n	70001180 <__aeabi_l2f+0x14>
7000117a:	4240      	negs	r0, r0
7000117c:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70001180:	ea5f 0c01 	movs.w	ip, r1
70001184:	bf02      	ittt	eq
70001186:	4684      	moveq	ip, r0
70001188:	4601      	moveq	r1, r0
7000118a:	2000      	moveq	r0, #0
7000118c:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70001190:	bf08      	it	eq
70001192:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70001196:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
7000119a:	fabc f28c 	clz	r2, ip
7000119e:	3a08      	subs	r2, #8
700011a0:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
700011a4:	db10      	blt.n	700011c8 <__aeabi_l2f+0x5c>
700011a6:	fa01 fc02 	lsl.w	ip, r1, r2
700011aa:	4463      	add	r3, ip
700011ac:	fa00 fc02 	lsl.w	ip, r0, r2
700011b0:	f1c2 0220 	rsb	r2, r2, #32
700011b4:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
700011b8:	fa20 f202 	lsr.w	r2, r0, r2
700011bc:	eb43 0002 	adc.w	r0, r3, r2
700011c0:	bf08      	it	eq
700011c2:	f020 0001 	biceq.w	r0, r0, #1
700011c6:	4770      	bx	lr
700011c8:	f102 0220 	add.w	r2, r2, #32
700011cc:	fa01 fc02 	lsl.w	ip, r1, r2
700011d0:	f1c2 0220 	rsb	r2, r2, #32
700011d4:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
700011d8:	fa21 f202 	lsr.w	r2, r1, r2
700011dc:	eb43 0002 	adc.w	r0, r3, r2
700011e0:	bf08      	it	eq
700011e2:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
700011e6:	4770      	bx	lr

700011e8 <__aeabi_fmul>:
700011e8:	f04f 0cff 	mov.w	ip, #255	; 0xff
700011ec:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
700011f0:	bf1e      	ittt	ne
700011f2:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
700011f6:	ea92 0f0c 	teqne	r2, ip
700011fa:	ea93 0f0c 	teqne	r3, ip
700011fe:	d06f      	beq.n	700012e0 <__aeabi_fmul+0xf8>
70001200:	441a      	add	r2, r3
70001202:	ea80 0c01 	eor.w	ip, r0, r1
70001206:	0240      	lsls	r0, r0, #9
70001208:	bf18      	it	ne
7000120a:	ea5f 2141 	movsne.w	r1, r1, lsl #9
7000120e:	d01e      	beq.n	7000124e <__aeabi_fmul+0x66>
70001210:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70001214:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70001218:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
7000121c:	fba0 3101 	umull	r3, r1, r0, r1
70001220:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70001224:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70001228:	bf3e      	ittt	cc
7000122a:	0049      	lslcc	r1, r1, #1
7000122c:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70001230:	005b      	lslcc	r3, r3, #1
70001232:	ea40 0001 	orr.w	r0, r0, r1
70001236:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
7000123a:	2afd      	cmp	r2, #253	; 0xfd
7000123c:	d81d      	bhi.n	7000127a <__aeabi_fmul+0x92>
7000123e:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70001242:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70001246:	bf08      	it	eq
70001248:	f020 0001 	biceq.w	r0, r0, #1
7000124c:	4770      	bx	lr
7000124e:	f090 0f00 	teq	r0, #0
70001252:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70001256:	bf08      	it	eq
70001258:	0249      	lsleq	r1, r1, #9
7000125a:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
7000125e:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70001262:	3a7f      	subs	r2, #127	; 0x7f
70001264:	bfc2      	ittt	gt
70001266:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
7000126a:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
7000126e:	4770      	bxgt	lr
70001270:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001274:	f04f 0300 	mov.w	r3, #0
70001278:	3a01      	subs	r2, #1
7000127a:	dc5d      	bgt.n	70001338 <__aeabi_fmul+0x150>
7000127c:	f112 0f19 	cmn.w	r2, #25
70001280:	bfdc      	itt	le
70001282:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70001286:	4770      	bxle	lr
70001288:	f1c2 0200 	rsb	r2, r2, #0
7000128c:	0041      	lsls	r1, r0, #1
7000128e:	fa21 f102 	lsr.w	r1, r1, r2
70001292:	f1c2 0220 	rsb	r2, r2, #32
70001296:	fa00 fc02 	lsl.w	ip, r0, r2
7000129a:	ea5f 0031 	movs.w	r0, r1, rrx
7000129e:	f140 0000 	adc.w	r0, r0, #0
700012a2:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
700012a6:	bf08      	it	eq
700012a8:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
700012ac:	4770      	bx	lr
700012ae:	f092 0f00 	teq	r2, #0
700012b2:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
700012b6:	bf02      	ittt	eq
700012b8:	0040      	lsleq	r0, r0, #1
700012ba:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
700012be:	3a01      	subeq	r2, #1
700012c0:	d0f9      	beq.n	700012b6 <__aeabi_fmul+0xce>
700012c2:	ea40 000c 	orr.w	r0, r0, ip
700012c6:	f093 0f00 	teq	r3, #0
700012ca:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
700012ce:	bf02      	ittt	eq
700012d0:	0049      	lsleq	r1, r1, #1
700012d2:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
700012d6:	3b01      	subeq	r3, #1
700012d8:	d0f9      	beq.n	700012ce <__aeabi_fmul+0xe6>
700012da:	ea41 010c 	orr.w	r1, r1, ip
700012de:	e78f      	b.n	70001200 <__aeabi_fmul+0x18>
700012e0:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
700012e4:	ea92 0f0c 	teq	r2, ip
700012e8:	bf18      	it	ne
700012ea:	ea93 0f0c 	teqne	r3, ip
700012ee:	d00a      	beq.n	70001306 <__aeabi_fmul+0x11e>
700012f0:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
700012f4:	bf18      	it	ne
700012f6:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
700012fa:	d1d8      	bne.n	700012ae <__aeabi_fmul+0xc6>
700012fc:	ea80 0001 	eor.w	r0, r0, r1
70001300:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70001304:	4770      	bx	lr
70001306:	f090 0f00 	teq	r0, #0
7000130a:	bf17      	itett	ne
7000130c:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70001310:	4608      	moveq	r0, r1
70001312:	f091 0f00 	teqne	r1, #0
70001316:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
7000131a:	d014      	beq.n	70001346 <__aeabi_fmul+0x15e>
7000131c:	ea92 0f0c 	teq	r2, ip
70001320:	d101      	bne.n	70001326 <__aeabi_fmul+0x13e>
70001322:	0242      	lsls	r2, r0, #9
70001324:	d10f      	bne.n	70001346 <__aeabi_fmul+0x15e>
70001326:	ea93 0f0c 	teq	r3, ip
7000132a:	d103      	bne.n	70001334 <__aeabi_fmul+0x14c>
7000132c:	024b      	lsls	r3, r1, #9
7000132e:	bf18      	it	ne
70001330:	4608      	movne	r0, r1
70001332:	d108      	bne.n	70001346 <__aeabi_fmul+0x15e>
70001334:	ea80 0001 	eor.w	r0, r0, r1
70001338:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
7000133c:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70001340:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001344:	4770      	bx	lr
70001346:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
7000134a:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
7000134e:	4770      	bx	lr

70001350 <__aeabi_fdiv>:
70001350:	f04f 0cff 	mov.w	ip, #255	; 0xff
70001354:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70001358:	bf1e      	ittt	ne
7000135a:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
7000135e:	ea92 0f0c 	teqne	r2, ip
70001362:	ea93 0f0c 	teqne	r3, ip
70001366:	d069      	beq.n	7000143c <__aeabi_fdiv+0xec>
70001368:	eba2 0203 	sub.w	r2, r2, r3
7000136c:	ea80 0c01 	eor.w	ip, r0, r1
70001370:	0249      	lsls	r1, r1, #9
70001372:	ea4f 2040 	mov.w	r0, r0, lsl #9
70001376:	d037      	beq.n	700013e8 <__aeabi_fdiv+0x98>
70001378:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
7000137c:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70001380:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70001384:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70001388:	428b      	cmp	r3, r1
7000138a:	bf38      	it	cc
7000138c:	005b      	lslcc	r3, r3, #1
7000138e:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70001392:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70001396:	428b      	cmp	r3, r1
70001398:	bf24      	itt	cs
7000139a:	1a5b      	subcs	r3, r3, r1
7000139c:	ea40 000c 	orrcs.w	r0, r0, ip
700013a0:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
700013a4:	bf24      	itt	cs
700013a6:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
700013aa:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
700013ae:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
700013b2:	bf24      	itt	cs
700013b4:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
700013b8:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
700013bc:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
700013c0:	bf24      	itt	cs
700013c2:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
700013c6:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
700013ca:	011b      	lsls	r3, r3, #4
700013cc:	bf18      	it	ne
700013ce:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
700013d2:	d1e0      	bne.n	70001396 <__aeabi_fdiv+0x46>
700013d4:	2afd      	cmp	r2, #253	; 0xfd
700013d6:	f63f af50 	bhi.w	7000127a <__aeabi_fmul+0x92>
700013da:	428b      	cmp	r3, r1
700013dc:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
700013e0:	bf08      	it	eq
700013e2:	f020 0001 	biceq.w	r0, r0, #1
700013e6:	4770      	bx	lr
700013e8:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
700013ec:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
700013f0:	327f      	adds	r2, #127	; 0x7f
700013f2:	bfc2      	ittt	gt
700013f4:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
700013f8:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
700013fc:	4770      	bxgt	lr
700013fe:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001402:	f04f 0300 	mov.w	r3, #0
70001406:	3a01      	subs	r2, #1
70001408:	e737      	b.n	7000127a <__aeabi_fmul+0x92>
7000140a:	f092 0f00 	teq	r2, #0
7000140e:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70001412:	bf02      	ittt	eq
70001414:	0040      	lsleq	r0, r0, #1
70001416:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
7000141a:	3a01      	subeq	r2, #1
7000141c:	d0f9      	beq.n	70001412 <__aeabi_fdiv+0xc2>
7000141e:	ea40 000c 	orr.w	r0, r0, ip
70001422:	f093 0f00 	teq	r3, #0
70001426:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
7000142a:	bf02      	ittt	eq
7000142c:	0049      	lsleq	r1, r1, #1
7000142e:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70001432:	3b01      	subeq	r3, #1
70001434:	d0f9      	beq.n	7000142a <__aeabi_fdiv+0xda>
70001436:	ea41 010c 	orr.w	r1, r1, ip
7000143a:	e795      	b.n	70001368 <__aeabi_fdiv+0x18>
7000143c:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70001440:	ea92 0f0c 	teq	r2, ip
70001444:	d108      	bne.n	70001458 <__aeabi_fdiv+0x108>
70001446:	0242      	lsls	r2, r0, #9
70001448:	f47f af7d 	bne.w	70001346 <__aeabi_fmul+0x15e>
7000144c:	ea93 0f0c 	teq	r3, ip
70001450:	f47f af70 	bne.w	70001334 <__aeabi_fmul+0x14c>
70001454:	4608      	mov	r0, r1
70001456:	e776      	b.n	70001346 <__aeabi_fmul+0x15e>
70001458:	ea93 0f0c 	teq	r3, ip
7000145c:	d104      	bne.n	70001468 <__aeabi_fdiv+0x118>
7000145e:	024b      	lsls	r3, r1, #9
70001460:	f43f af4c 	beq.w	700012fc <__aeabi_fmul+0x114>
70001464:	4608      	mov	r0, r1
70001466:	e76e      	b.n	70001346 <__aeabi_fmul+0x15e>
70001468:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
7000146c:	bf18      	it	ne
7000146e:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70001472:	d1ca      	bne.n	7000140a <__aeabi_fdiv+0xba>
70001474:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70001478:	f47f af5c 	bne.w	70001334 <__aeabi_fmul+0x14c>
7000147c:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70001480:	f47f af3c 	bne.w	700012fc <__aeabi_fmul+0x114>
70001484:	e75f      	b.n	70001346 <__aeabi_fmul+0x15e>
70001486:	bf00      	nop

70001488 <__gesf2>:
70001488:	f04f 3cff 	mov.w	ip, #4294967295
7000148c:	e006      	b.n	7000149c <__cmpsf2+0x4>
7000148e:	bf00      	nop

70001490 <__lesf2>:
70001490:	f04f 0c01 	mov.w	ip, #1
70001494:	e002      	b.n	7000149c <__cmpsf2+0x4>
70001496:	bf00      	nop

70001498 <__cmpsf2>:
70001498:	f04f 0c01 	mov.w	ip, #1
7000149c:	f84d cd04 	str.w	ip, [sp, #-4]!
700014a0:	ea4f 0240 	mov.w	r2, r0, lsl #1
700014a4:	ea4f 0341 	mov.w	r3, r1, lsl #1
700014a8:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700014ac:	bf18      	it	ne
700014ae:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700014b2:	d011      	beq.n	700014d8 <__cmpsf2+0x40>
700014b4:	b001      	add	sp, #4
700014b6:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
700014ba:	bf18      	it	ne
700014bc:	ea90 0f01 	teqne	r0, r1
700014c0:	bf58      	it	pl
700014c2:	ebb2 0003 	subspl.w	r0, r2, r3
700014c6:	bf88      	it	hi
700014c8:	17c8      	asrhi	r0, r1, #31
700014ca:	bf38      	it	cc
700014cc:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
700014d0:	bf18      	it	ne
700014d2:	f040 0001 	orrne.w	r0, r0, #1
700014d6:	4770      	bx	lr
700014d8:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700014dc:	d102      	bne.n	700014e4 <__cmpsf2+0x4c>
700014de:	ea5f 2c40 	movs.w	ip, r0, lsl #9
700014e2:	d105      	bne.n	700014f0 <__cmpsf2+0x58>
700014e4:	ea7f 6c23 	mvns.w	ip, r3, asr #24
700014e8:	d1e4      	bne.n	700014b4 <__cmpsf2+0x1c>
700014ea:	ea5f 2c41 	movs.w	ip, r1, lsl #9
700014ee:	d0e1      	beq.n	700014b4 <__cmpsf2+0x1c>
700014f0:	f85d 0b04 	ldr.w	r0, [sp], #4
700014f4:	4770      	bx	lr
700014f6:	bf00      	nop

700014f8 <__aeabi_cfrcmple>:
700014f8:	4684      	mov	ip, r0
700014fa:	4608      	mov	r0, r1
700014fc:	4661      	mov	r1, ip
700014fe:	e7ff      	b.n	70001500 <__aeabi_cfcmpeq>

70001500 <__aeabi_cfcmpeq>:
70001500:	b50f      	push	{r0, r1, r2, r3, lr}
70001502:	f7ff ffc9 	bl	70001498 <__cmpsf2>
70001506:	2800      	cmp	r0, #0
70001508:	bf48      	it	mi
7000150a:	f110 0f00 	cmnmi.w	r0, #0
7000150e:	bd0f      	pop	{r0, r1, r2, r3, pc}

70001510 <__aeabi_fcmpeq>:
70001510:	f84d ed08 	str.w	lr, [sp, #-8]!
70001514:	f7ff fff4 	bl	70001500 <__aeabi_cfcmpeq>
70001518:	bf0c      	ite	eq
7000151a:	2001      	moveq	r0, #1
7000151c:	2000      	movne	r0, #0
7000151e:	f85d fb08 	ldr.w	pc, [sp], #8
70001522:	bf00      	nop

70001524 <__aeabi_fcmplt>:
70001524:	f84d ed08 	str.w	lr, [sp, #-8]!
70001528:	f7ff ffea 	bl	70001500 <__aeabi_cfcmpeq>
7000152c:	bf34      	ite	cc
7000152e:	2001      	movcc	r0, #1
70001530:	2000      	movcs	r0, #0
70001532:	f85d fb08 	ldr.w	pc, [sp], #8
70001536:	bf00      	nop

70001538 <__aeabi_fcmple>:
70001538:	f84d ed08 	str.w	lr, [sp, #-8]!
7000153c:	f7ff ffe0 	bl	70001500 <__aeabi_cfcmpeq>
70001540:	bf94      	ite	ls
70001542:	2001      	movls	r0, #1
70001544:	2000      	movhi	r0, #0
70001546:	f85d fb08 	ldr.w	pc, [sp], #8
7000154a:	bf00      	nop

7000154c <__aeabi_fcmpge>:
7000154c:	f84d ed08 	str.w	lr, [sp, #-8]!
70001550:	f7ff ffd2 	bl	700014f8 <__aeabi_cfrcmple>
70001554:	bf94      	ite	ls
70001556:	2001      	movls	r0, #1
70001558:	2000      	movhi	r0, #0
7000155a:	f85d fb08 	ldr.w	pc, [sp], #8
7000155e:	bf00      	nop

70001560 <__aeabi_fcmpgt>:
70001560:	f84d ed08 	str.w	lr, [sp, #-8]!
70001564:	f7ff ffc8 	bl	700014f8 <__aeabi_cfrcmple>
70001568:	bf34      	ite	cc
7000156a:	2001      	movcc	r0, #1
7000156c:	2000      	movcs	r0, #0
7000156e:	f85d fb08 	ldr.w	pc, [sp], #8
70001572:	bf00      	nop

70001574 <__aeabi_f2uiz>:
70001574:	0042      	lsls	r2, r0, #1
70001576:	d20e      	bcs.n	70001596 <__aeabi_f2uiz+0x22>
70001578:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
7000157c:	d30b      	bcc.n	70001596 <__aeabi_f2uiz+0x22>
7000157e:	f04f 039e 	mov.w	r3, #158	; 0x9e
70001582:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70001586:	d409      	bmi.n	7000159c <__aeabi_f2uiz+0x28>
70001588:	ea4f 2300 	mov.w	r3, r0, lsl #8
7000158c:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70001590:	fa23 f002 	lsr.w	r0, r3, r2
70001594:	4770      	bx	lr
70001596:	f04f 0000 	mov.w	r0, #0
7000159a:	4770      	bx	lr
7000159c:	f112 0f61 	cmn.w	r2, #97	; 0x61
700015a0:	d101      	bne.n	700015a6 <__aeabi_f2uiz+0x32>
700015a2:	0242      	lsls	r2, r0, #9
700015a4:	d102      	bne.n	700015ac <__aeabi_f2uiz+0x38>
700015a6:	f04f 30ff 	mov.w	r0, #4294967295
700015aa:	4770      	bx	lr
700015ac:	f04f 0000 	mov.w	r0, #0
700015b0:	4770      	bx	lr
700015b2:	bf00      	nop
