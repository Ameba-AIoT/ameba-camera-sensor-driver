
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	f1 06 00 70 41 02 00 70                             ...pA..p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

7000006c <g_jxf38p_i2c_init_regs_asic>:
7000006c:	12 00 40 00 48 00 8a 00 48 00 0a 00 0e 00 11 00     ..@.H...H.......
7000007c:	0f 00 04 00 10 00 24 00 11 00 80 00 46 00 00 00     ......$.....F...
7000008c:	0d 00 f0 00 57 00 67 00 58 00 1f 00 5f 00 41 00     ....W.g.X..._.A.
7000009c:	60 00 20 00 a5 00 4f 00 20 00 00 00 21 00 05 00     `. ...O. ...!...
700000ac:	22 00 65 00 23 00 04 00 24 00 c0 00 25 00 38 00     ".e.#...$...%.8.
700000bc:	26 00 43 00 27 00 fc 00 28 00 16 00 29 00 04 00     &.C.'...(...)...
700000cc:	2a 00 f0 00 2b 00 14 00 2c 00 02 00 2d 00 00 00     *...+...,...-...
700000dc:	2e 00 14 00 2f 00 44 00 41 00 c4 00 42 00 03 00     ..../.D.A...B...
700000ec:	47 00 42 00 76 00 60 00 77 00 09 00 80 00 01 00     G.B.v.`.w.......
700000fc:	af 00 22 00 ab 00 00 00 85 00 76 00 59 00 68 00     ..".......v.Y.h.
7000010c:	1d 00 00 00 1e 00 04 00 6c 00 40 00 6e 00 2c 00     ........l.@.n.,.
7000011c:	70 00 6c 00 71 00 6d 00 72 00 6a 00 73 00 36 00     p.l.q.m.r.j.s.6.
7000012c:	74 00 02 00 78 00 9c 00 89 00 01 00 6b 00 20 00     t...x.......k. .
7000013c:	86 00 40 00 30 00 8d 00 31 00 12 00 32 00 39 00     ..@.0...1...2.9.
7000014c:	33 00 60 00 34 00 29 00 35 00 25 00 3a 00 a0 00     3.`.4.).5.%.:...
7000015c:	56 00 90 00 59 00 68 00 5a 00 01 00 61 00 00 00     V...Y.h.Z...a...
7000016c:	64 00 d2 00 85 00 76 00 8a 00 00 00 91 00 08 00     d.....v.........
7000017c:	94 00 e0 00 9b 00 8f 00 a6 00 02 00 a7 00 80 00     ................
7000018c:	a9 00 4c 00 45 00 09 00 5b 00 a6 00 5c 00 64 00     ..L.E...[...\.d.
7000019c:	5d 00 86 00 5e 00 01 00 65 00 32 00 66 00 c0 00     ]...^...e.2.f...
700001ac:	67 00 48 00 68 00 00 00 69 00 72 00 6a 00 24 00     g.H.h...i.r.j.$.
700001bc:	7a 00 00 00 8d 00 67 00 8f 00 90 00 a4 00 c7 00     z.....g.........
700001cc:	b7 00 21 00 97 00 20 00 13 00 81 00 96 00 84 00     ..!... .........
700001dc:	4a 00 01 00 7e 00 4c 00 9e 00 f8 00 b5 00 0c 00     J...~.L.........
700001ec:	93 00 00 00 b1 00 00 00 a1 00 0f 00 a3 00 40 00     ..............@.
700001fc:	50 00 02 00 49 00 40 00 7f 00 56 00 8c 00 ff 00     P...I.@...V.....
7000020c:	8e 00 00 00 90 00 01 00 0c 00 00 00 bc 00 11 00     ................
7000021c:	82 00 00 00 19 00 20 00 1b 00 4f 00 12 00 00 00     ...... ...O.....
7000022c:	48 00 8a 00 48 00 0a 00                             H...H...

70000234 <real_slave_addr>:
70000234:	40 00 00 00                                         @...

70000238 <slave_addr_list>:
70000238:	40 00 00 00 46 00 00 00                             @...F...

70000240 <rts_isp_set_voe_ops>:
70000240:	4b01      	ldr	r3, [pc, #4]	; (70000248 <rts_isp_set_voe_ops+0x8>)
70000242:	6018      	str	r0, [r3, #0]
70000244:	4770      	bx	lr
70000246:	bf00      	nop
70000248:	70000048 	.word	0x70000048

7000024c <isp_driver_is_fpga>:
7000024c:	2000      	movs	r0, #0
7000024e:	4770      	bx	lr

70000250 <jxf38p_get_info>:
70000250:	b530      	push	{r4, r5, lr}
70000252:	2800      	cmp	r0, #0
70000254:	d151      	bne.n	700002fa <jxf38p_get_info+0xaa>
70000256:	2900      	cmp	r1, #0
70000258:	d04f      	beq.n	700002fa <jxf38p_get_info+0xaa>
7000025a:	f44f 62f0 	mov.w	r2, #1920	; 0x780
7000025e:	f44f 6387 	mov.w	r3, #1080	; 0x438
70000262:	f44f 747a 	mov.w	r4, #1000	; 0x3e8
70000266:	4d26      	ldr	r5, [pc, #152]	; (70000300 <jxf38p_get_info+0xb0>)
70000268:	7108      	strb	r0, [r1, #4]
7000026a:	f881 00b0 	strb.w	r0, [r1, #176]	; 0xb0
7000026e:	f8c1 00b4 	str.w	r0, [r1, #180]	; 0xb4
70000272:	f881 00bc 	strb.w	r0, [r1, #188]	; 0xbc
70000276:	f8c1 00cc 	str.w	r0, [r1, #204]	; 0xcc
7000027a:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
7000027e:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
70000282:	f8c1 02dc 	str.w	r0, [r1, #732]	; 0x2dc
70000286:	e9c1 2302 	strd	r2, r3, [r1, #8]
7000028a:	4b1e      	ldr	r3, [pc, #120]	; (70000304 <jxf38p_get_info+0xb4>)
7000028c:	4a1e      	ldr	r2, [pc, #120]	; (70000308 <jxf38p_get_info+0xb8>)
7000028e:	610b      	str	r3, [r1, #16]
70000290:	2301      	movs	r3, #1
70000292:	6812      	ldr	r2, [r2, #0]
70000294:	600b      	str	r3, [r1, #0]
70000296:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
7000029a:	4a1c      	ldr	r2, [pc, #112]	; (7000030c <jxf38p_get_info+0xbc>)
7000029c:	f881 3098 	strb.w	r3, [r1, #152]	; 0x98
700002a0:	7812      	ldrb	r2, [r2, #0]
700002a2:	f881 30c8 	strb.w	r3, [r1, #200]	; 0xc8
700002a6:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
700002aa:	2203      	movs	r2, #3
700002ac:	e9c1 542a 	strd	r5, r4, [r1, #168]	; 0xa8
700002b0:	e9c1 3430 	strd	r3, r4, [r1, #192]	; 0xc0
700002b4:	f640 34b8 	movw	r4, #3000	; 0xbb8
700002b8:	f242 7510 	movw	r5, #10000	; 0x2710
700002bc:	f881 20a4 	strb.w	r2, [r1, #164]	; 0xa4
700002c0:	f8c1 40d0 	str.w	r4, [r1, #208]	; 0xd0
700002c4:	f240 1401 	movw	r4, #257	; 0x101
700002c8:	f8c1 50b8 	str.w	r5, [r1, #184]	; 0xb8
700002cc:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
700002d0:	2406      	movs	r4, #6
700002d2:	f8c1 4088 	str.w	r4, [r1, #136]	; 0x88
700002d6:	2464      	movs	r4, #100	; 0x64
700002d8:	e9c1 3324 	strd	r3, r3, [r1, #144]	; 0x90
700002dc:	e9c1 3327 	strd	r3, r3, [r1, #156]	; 0x9c
700002e0:	f8c1 42e0 	str.w	r4, [r1, #736]	; 0x2e0
700002e4:	f881 32e4 	strb.w	r3, [r1, #740]	; 0x2e4
700002e8:	f881 22f0 	strb.w	r2, [r1, #752]	; 0x2f0
700002ec:	f8c1 22d4 	str.w	r2, [r1, #724]	; 0x2d4
700002f0:	e9c1 34ba 	strd	r3, r4, [r1, #744]	; 0x2e8
700002f4:	e9c1 04bd 	strd	r0, r4, [r1, #756]	; 0x2f4
700002f8:	bd30      	pop	{r4, r5, pc}
700002fa:	f06f 0015 	mvn.w	r0, #21
700002fe:	e7fb      	b.n	700002f8 <jxf38p_get_info+0xa8>
70000300:	016e3600 	.word	0x016e3600
70000304:	41f00000 	.word	0x41f00000
70000308:	70000234 	.word	0x70000234
7000030c:	7000004c 	.word	0x7000004c

70000310 <jxf38p_get_init_info>:
70000310:	b570      	push	{r4, r5, r6, lr}
70000312:	4614      	mov	r4, r2
70000314:	4605      	mov	r5, r0
70000316:	b110      	cbz	r0, 7000031e <jxf38p_get_init_info+0xe>
70000318:	f06f 0015 	mvn.w	r0, #21
7000031c:	bd70      	pop	{r4, r5, r6, pc}
7000031e:	2a00      	cmp	r2, #0
70000320:	d0fa      	beq.n	70000318 <jxf38p_get_init_info+0x8>
70000322:	780b      	ldrb	r3, [r1, #0]
70000324:	4e19      	ldr	r6, [pc, #100]	; (7000038c <jxf38p_get_init_info+0x7c>)
70000326:	68c8      	ldr	r0, [r1, #12]
70000328:	7033      	strb	r3, [r6, #0]
7000032a:	f001 f915 	bl	70001558 <__aeabi_f2uiz>
7000032e:	b280      	uxth	r0, r0
70000330:	281e      	cmp	r0, #30
70000332:	d1f1      	bne.n	70000318 <jxf38p_get_init_info+0x8>
70000334:	4b16      	ldr	r3, [pc, #88]	; (70000390 <jxf38p_get_init_info+0x80>)
70000336:	f44f 62f0 	mov.w	r2, #1920	; 0x780
7000033a:	f44f 6120 	mov.w	r1, #2560	; 0xa00
7000033e:	60a5      	str	r5, [r4, #8]
70000340:	6063      	str	r3, [r4, #4]
70000342:	2372      	movs	r3, #114	; 0x72
70000344:	4628      	mov	r0, r5
70000346:	6023      	str	r3, [r4, #0]
70000348:	2302      	movs	r3, #2
7000034a:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
7000034e:	f240 4303 	movw	r3, #1027	; 0x403
70000352:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
70000356:	230a      	movs	r3, #10
70000358:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
7000035c:	2304      	movs	r3, #4
7000035e:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
70000362:	f44f 6387 	mov.w	r3, #1080	; 0x438
70000366:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
7000036a:	4b0a      	ldr	r3, [pc, #40]	; (70000394 <jxf38p_get_init_info+0x84>)
7000036c:	e9c4 3124 	strd	r3, r1, [r4, #144]	; 0x90
70000370:	f240 4365 	movw	r3, #1125	; 0x465
70000374:	6073      	str	r3, [r6, #4]
70000376:	f8c4 3098 	str.w	r3, [r4, #152]	; 0x98
7000037a:	f248 33d6 	movw	r3, #33750	; 0x83d6
7000037e:	f8c4 309c 	str.w	r3, [r4, #156]	; 0x9c
70000382:	4b05      	ldr	r3, [pc, #20]	; (70000398 <jxf38p_get_init_info+0x88>)
70000384:	e9c4 5522 	strd	r5, r5, [r4, #136]	; 0x88
70000388:	60b3      	str	r3, [r6, #8]
7000038a:	e7c7      	b.n	7000031c <jxf38p_get_init_info+0xc>
7000038c:	7000004c 	.word	0x7000004c
70000390:	7000006c 	.word	0x7000006c
70000394:	05265c00 	.word	0x05265c00
70000398:	41ed097b 	.word	0x41ed097b

7000039c <jxf38p_start>:
7000039c:	b918      	cbnz	r0, 700003a6 <jxf38p_start+0xa>
7000039e:	4b03      	ldr	r3, [pc, #12]	; (700003ac <jxf38p_start+0x10>)
700003a0:	2200      	movs	r2, #0
700003a2:	60da      	str	r2, [r3, #12]
700003a4:	4770      	bx	lr
700003a6:	f06f 0015 	mvn.w	r0, #21
700003aa:	4770      	bx	lr
700003ac:	7000004c 	.word	0x7000004c

700003b0 <jxf38p_get_tuned_dgain>:
700003b0:	b920      	cbnz	r0, 700003bc <jxf38p_get_tuned_dgain+0xc>
700003b2:	b119      	cbz	r1, 700003bc <jxf38p_get_tuned_dgain+0xc>
700003b4:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
700003b8:	600b      	str	r3, [r1, #0]
700003ba:	4770      	bx	lr
700003bc:	f06f 0015 	mvn.w	r0, #21
700003c0:	4770      	bx	lr
	...

700003c4 <jxf38p_get_exposure_gain_info>:
700003c4:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
700003c8:	4614      	mov	r4, r2
700003ca:	2800      	cmp	r0, #0
700003cc:	d14b      	bne.n	70000466 <jxf38p_get_exposure_gain_info+0xa2>
700003ce:	2900      	cmp	r1, #0
700003d0:	d049      	beq.n	70000466 <jxf38p_get_exposure_gain_info+0xa2>
700003d2:	2a00      	cmp	r2, #0
700003d4:	d047      	beq.n	70000466 <jxf38p_get_exposure_gain_info+0xa2>
700003d6:	f8d1 8000 	ldr.w	r8, [r1]
700003da:	1d15      	adds	r5, r2, #4
700003dc:	4f23      	ldr	r7, [pc, #140]	; (7000046c <jxf38p_get_exposure_gain_info+0xa8>)
700003de:	698e      	ldr	r6, [r1, #24]
700003e0:	4641      	mov	r1, r8
700003e2:	68f8      	ldr	r0, [r7, #12]
700003e4:	f000 fde8 	bl	70000fb8 <__aeabi_fsub>
700003e8:	2100      	movs	r1, #0
700003ea:	4681      	mov	r9, r0
700003ec:	f001 f8a0 	bl	70001530 <__aeabi_fcmpge>
700003f0:	2800      	cmp	r0, #0
700003f2:	d033      	beq.n	7000045c <jxf38p_get_exposure_gain_info+0x98>
700003f4:	491e      	ldr	r1, [pc, #120]	; (70000470 <jxf38p_get_exposure_gain_info+0xac>)
700003f6:	4648      	mov	r0, r9
700003f8:	f001 f8a4 	bl	70001544 <__aeabi_fcmpgt>
700003fc:	b1a8      	cbz	r0, 7000042a <jxf38p_get_exposure_gain_info+0x66>
700003fe:	68b9      	ldr	r1, [r7, #8]
70000400:	4640      	mov	r0, r8
70000402:	f000 ff97 	bl	70001334 <__aeabi_fdiv>
70000406:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
7000040a:	f000 fdd7 	bl	70000fbc <__addsf3>
7000040e:	f001 f8a3 	bl	70001558 <__aeabi_f2uiz>
70000412:	f3c0 2307 	ubfx	r3, r0, #8, #8
70000416:	2202      	movs	r2, #2
70000418:	81e3      	strh	r3, [r4, #14]
7000041a:	2301      	movs	r3, #1
7000041c:	81a2      	strh	r2, [r4, #12]
7000041e:	8423      	strh	r3, [r4, #32]
70000420:	b2c3      	uxtb	r3, r0
70000422:	4610      	mov	r0, r2
70000424:	f8c7 800c 	str.w	r8, [r7, #12]
70000428:	8463      	strh	r3, [r4, #34]	; 0x22
7000042a:	2114      	movs	r1, #20
7000042c:	8a3f      	ldrh	r7, [r7, #16]
7000042e:	2300      	movs	r3, #0
70000430:	4341      	muls	r1, r0
70000432:	3003      	adds	r0, #3
70000434:	186a      	adds	r2, r5, r1
70000436:	8157      	strh	r7, [r2, #10]
70000438:	2723      	movs	r7, #35	; 0x23
7000043a:	8113      	strh	r3, [r2, #8]
7000043c:	f101 0214 	add.w	r2, r1, #20
70000440:	3128      	adds	r1, #40	; 0x28
70000442:	442a      	add	r2, r5
70000444:	4429      	add	r1, r5
70000446:	8117      	strh	r7, [r2, #8]
70000448:	0a37      	lsrs	r7, r6, #8
7000044a:	b2f6      	uxtb	r6, r6
7000044c:	8157      	strh	r7, [r2, #10]
7000044e:	2222      	movs	r2, #34	; 0x22
70000450:	814e      	strh	r6, [r1, #10]
70000452:	810a      	strh	r2, [r1, #8]
70000454:	6020      	str	r0, [r4, #0]
70000456:	4618      	mov	r0, r3
70000458:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
7000045c:	4905      	ldr	r1, [pc, #20]	; (70000474 <jxf38p_get_exposure_gain_info+0xb0>)
7000045e:	4648      	mov	r0, r9
70000460:	f001 f852 	bl	70001508 <__aeabi_fcmplt>
70000464:	e7ca      	b.n	700003fc <jxf38p_get_exposure_gain_info+0x38>
70000466:	f06f 0015 	mvn.w	r0, #21
7000046a:	e7f5      	b.n	70000458 <jxf38p_get_exposure_gain_info+0x94>
7000046c:	7000004c 	.word	0x7000004c
70000470:	3a83126f 	.word	0x3a83126f
70000474:	ba83126f 	.word	0xba83126f

70000478 <jxf38p_set_mirror_flip>:
70000478:	784b      	ldrb	r3, [r1, #1]
7000047a:	780a      	ldrb	r2, [r1, #0]
7000047c:	2b00      	cmp	r3, #0
7000047e:	bf14      	ite	ne
70000480:	2302      	movne	r3, #2
70000482:	2300      	moveq	r3, #0
70000484:	2a00      	cmp	r2, #0
70000486:	bf18      	it	ne
70000488:	f043 0301 	orrne.w	r3, r3, #1
7000048c:	2201      	movs	r2, #1
7000048e:	2b02      	cmp	r3, #2
70000490:	708a      	strb	r2, [r1, #2]
70000492:	d009      	beq.n	700004a8 <jxf38p_set_mirror_flip+0x30>
70000494:	2b03      	cmp	r3, #3
70000496:	d00b      	beq.n	700004b0 <jxf38p_set_mirror_flip+0x38>
70000498:	4293      	cmp	r3, r2
7000049a:	d007      	beq.n	700004ac <jxf38p_set_mirror_flip+0x34>
7000049c:	4b05      	ldr	r3, [pc, #20]	; (700004b4 <jxf38p_set_mirror_flip+0x3c>)
7000049e:	610b      	str	r3, [r1, #16]
700004a0:	2301      	movs	r3, #1
700004a2:	2000      	movs	r0, #0
700004a4:	604b      	str	r3, [r1, #4]
700004a6:	4770      	bx	lr
700004a8:	4b03      	ldr	r3, [pc, #12]	; (700004b8 <jxf38p_set_mirror_flip+0x40>)
700004aa:	e7f8      	b.n	7000049e <jxf38p_set_mirror_flip+0x26>
700004ac:	4b03      	ldr	r3, [pc, #12]	; (700004bc <jxf38p_set_mirror_flip+0x44>)
700004ae:	e7f6      	b.n	7000049e <jxf38p_set_mirror_flip+0x26>
700004b0:	2312      	movs	r3, #18
700004b2:	e7f4      	b.n	7000049e <jxf38p_set_mirror_flip+0x26>
700004b4:	00300012 	.word	0x00300012
700004b8:	00200012 	.word	0x00200012
700004bc:	00100012 	.word	0x00100012

700004c0 <jxf38p_check>:
700004c0:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
700004c2:	4d1d      	ldr	r5, [pc, #116]	; (70000538 <jxf38p_check+0x78>)
700004c4:	4606      	mov	r6, r0
700004c6:	682b      	ldr	r3, [r5, #0]
700004c8:	6c1b      	ldr	r3, [r3, #64]	; 0x40
700004ca:	4798      	blx	r3
700004cc:	2801      	cmp	r0, #1
700004ce:	dc2f      	bgt.n	70000530 <jxf38p_check+0x70>
700004d0:	4b1a      	ldr	r3, [pc, #104]	; (7000053c <jxf38p_check+0x7c>)
700004d2:	f853 2020 	ldr.w	r2, [r3, r0, lsl #2]
700004d6:	4b1a      	ldr	r3, [pc, #104]	; (70000540 <jxf38p_check+0x80>)
700004d8:	601a      	str	r2, [r3, #0]
700004da:	682b      	ldr	r3, [r5, #0]
700004dc:	685b      	ldr	r3, [r3, #4]
700004de:	4798      	blx	r3
700004e0:	230a      	movs	r3, #10
700004e2:	a901      	add	r1, sp, #4
700004e4:	4630      	mov	r0, r6
700004e6:	f8ad 3004 	strh.w	r3, [sp, #4]
700004ea:	682b      	ldr	r3, [r5, #0]
700004ec:	68db      	ldr	r3, [r3, #12]
700004ee:	4798      	blx	r3
700004f0:	4604      	mov	r4, r0
700004f2:	b128      	cbz	r0, 70000500 <jxf38p_check+0x40>
700004f4:	682b      	ldr	r3, [r5, #0]
700004f6:	689b      	ldr	r3, [r3, #8]
700004f8:	4798      	blx	r3
700004fa:	4620      	mov	r0, r4
700004fc:	b003      	add	sp, #12
700004fe:	bdf0      	pop	{r4, r5, r6, r7, pc}
70000500:	230b      	movs	r3, #11
70000502:	a901      	add	r1, sp, #4
70000504:	4630      	mov	r0, r6
70000506:	f8bd 7006 	ldrh.w	r7, [sp, #6]
7000050a:	f8ad 3004 	strh.w	r3, [sp, #4]
7000050e:	682b      	ldr	r3, [r5, #0]
70000510:	68db      	ldr	r3, [r3, #12]
70000512:	4798      	blx	r3
70000514:	682b      	ldr	r3, [r5, #0]
70000516:	4604      	mov	r4, r0
70000518:	689b      	ldr	r3, [r3, #8]
7000051a:	4798      	blx	r3
7000051c:	2c00      	cmp	r4, #0
7000051e:	d1ec      	bne.n	700004fa <jxf38p_check+0x3a>
70000520:	f8bd 3006 	ldrh.w	r3, [sp, #6]
70000524:	f640 0244 	movw	r2, #2116	; 0x844
70000528:	ea43 2307 	orr.w	r3, r3, r7, lsl #8
7000052c:	4293      	cmp	r3, r2
7000052e:	d0e4      	beq.n	700004fa <jxf38p_check+0x3a>
70000530:	f06f 0415 	mvn.w	r4, #21
70000534:	e7e1      	b.n	700004fa <jxf38p_check+0x3a>
70000536:	bf00      	nop
70000538:	70000048 	.word	0x70000048
7000053c:	70000238 	.word	0x70000238
70000540:	70000234 	.word	0x70000234

70000544 <jxf38_get_slave_addr_num>:
70000544:	2002      	movs	r0, #2
70000546:	4770      	bx	lr

70000548 <jxf38p_get_tuned_again>:
70000548:	b570      	push	{r4, r5, r6, lr}
7000054a:	460e      	mov	r6, r1
7000054c:	2800      	cmp	r0, #0
7000054e:	f040 80ab 	bne.w	700006a8 <jxf38p_get_tuned_again+0x160>
70000552:	2900      	cmp	r1, #0
70000554:	f000 80a8 	beq.w	700006a8 <jxf38p_get_tuned_again+0x160>
70000558:	680c      	ldr	r4, [r1, #0]
7000055a:	f04f 517e 	mov.w	r1, #1065353216	; 0x3f800000
7000055e:	4620      	mov	r0, r4
70000560:	f000 ffe6 	bl	70001530 <__aeabi_fcmpge>
70000564:	b338      	cbz	r0, 700005b6 <jxf38p_get_tuned_again+0x6e>
70000566:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
7000056a:	4620      	mov	r0, r4
7000056c:	f000 ffcc 	bl	70001508 <__aeabi_fcmplt>
70000570:	b308      	cbz	r0, 700005b6 <jxf38p_get_tuned_again+0x6e>
70000572:	4620      	mov	r0, r4
70000574:	f000 fc4c 	bl	70000e10 <__aeabi_f2d>
70000578:	2200      	movs	r2, #0
7000057a:	4b4d      	ldr	r3, [pc, #308]	; (700006b0 <jxf38p_get_tuned_again+0x168>)
7000057c:	f000 fae8 	bl	70000b50 <__aeabi_dsub>
70000580:	2200      	movs	r2, #0
70000582:	4b4c      	ldr	r3, [pc, #304]	; (700006b4 <jxf38p_get_tuned_again+0x16c>)
70000584:	f000 f902 	bl	7000078c <__aeabi_dmul>
70000588:	f000 fc9a 	bl	70000ec0 <__aeabi_d2iz>
7000058c:	4b4a      	ldr	r3, [pc, #296]	; (700006b8 <jxf38p_get_tuned_again+0x170>)
7000058e:	b284      	uxth	r4, r0
70000590:	6118      	str	r0, [r3, #16]
70000592:	4620      	mov	r0, r4
70000594:	f000 fdc2 	bl	7000111c <__aeabi_ui2f>
70000598:	2c0f      	cmp	r4, #15
7000059a:	d85e      	bhi.n	7000065a <jxf38p_get_tuned_again+0x112>
7000059c:	f000 fc38 	bl	70000e10 <__aeabi_f2d>
700005a0:	2200      	movs	r2, #0
700005a2:	4b46      	ldr	r3, [pc, #280]	; (700006bc <jxf38p_get_tuned_again+0x174>)
700005a4:	f000 f8f2 	bl	7000078c <__aeabi_dmul>
700005a8:	2200      	movs	r2, #0
700005aa:	4b41      	ldr	r3, [pc, #260]	; (700006b0 <jxf38p_get_tuned_again+0x168>)
700005ac:	f000 fad2 	bl	70000b54 <__adddf3>
700005b0:	f000 fcae 	bl	70000f10 <__aeabi_d2f>
700005b4:	e059      	b.n	7000066a <jxf38p_get_tuned_again+0x122>
700005b6:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
700005ba:	4620      	mov	r0, r4
700005bc:	f000 ffb8 	bl	70001530 <__aeabi_fcmpge>
700005c0:	b1b0      	cbz	r0, 700005f0 <jxf38p_get_tuned_again+0xa8>
700005c2:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
700005c6:	4620      	mov	r0, r4
700005c8:	f000 ff9e 	bl	70001508 <__aeabi_fcmplt>
700005cc:	b180      	cbz	r0, 700005f0 <jxf38p_get_tuned_again+0xa8>
700005ce:	4620      	mov	r0, r4
700005d0:	f000 fc1e 	bl	70000e10 <__aeabi_f2d>
700005d4:	2200      	movs	r2, #0
700005d6:	f04f 4380 	mov.w	r3, #1073741824	; 0x40000000
700005da:	f000 fab9 	bl	70000b50 <__aeabi_dsub>
700005de:	2200      	movs	r2, #0
700005e0:	4b37      	ldr	r3, [pc, #220]	; (700006c0 <jxf38p_get_tuned_again+0x178>)
700005e2:	f000 f8d3 	bl	7000078c <__aeabi_dmul>
700005e6:	2200      	movs	r2, #0
700005e8:	4b32      	ldr	r3, [pc, #200]	; (700006b4 <jxf38p_get_tuned_again+0x16c>)
700005ea:	f000 fab3 	bl	70000b54 <__adddf3>
700005ee:	e7cb      	b.n	70000588 <jxf38p_get_tuned_again+0x40>
700005f0:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
700005f4:	4620      	mov	r0, r4
700005f6:	f000 ff9b 	bl	70001530 <__aeabi_fcmpge>
700005fa:	b198      	cbz	r0, 70000624 <jxf38p_get_tuned_again+0xdc>
700005fc:	f04f 4182 	mov.w	r1, #1090519040	; 0x41000000
70000600:	4620      	mov	r0, r4
70000602:	f000 ff81 	bl	70001508 <__aeabi_fcmplt>
70000606:	b168      	cbz	r0, 70000624 <jxf38p_get_tuned_again+0xdc>
70000608:	4620      	mov	r0, r4
7000060a:	f000 fc01 	bl	70000e10 <__aeabi_f2d>
7000060e:	2200      	movs	r2, #0
70000610:	4b2c      	ldr	r3, [pc, #176]	; (700006c4 <jxf38p_get_tuned_again+0x17c>)
70000612:	f000 fa9d 	bl	70000b50 <__aeabi_dsub>
70000616:	2200      	movs	r2, #0
70000618:	4b2a      	ldr	r3, [pc, #168]	; (700006c4 <jxf38p_get_tuned_again+0x17c>)
7000061a:	f000 f8b7 	bl	7000078c <__aeabi_dmul>
7000061e:	2200      	movs	r2, #0
70000620:	4b29      	ldr	r3, [pc, #164]	; (700006c8 <jxf38p_get_tuned_again+0x180>)
70000622:	e7e2      	b.n	700005ea <jxf38p_get_tuned_again+0xa2>
70000624:	f04f 4182 	mov.w	r1, #1090519040	; 0x41000000
70000628:	4620      	mov	r0, r4
7000062a:	f000 ff81 	bl	70001530 <__aeabi_fcmpge>
7000062e:	b190      	cbz	r0, 70000656 <jxf38p_get_tuned_again+0x10e>
70000630:	4926      	ldr	r1, [pc, #152]	; (700006cc <jxf38p_get_tuned_again+0x184>)
70000632:	4620      	mov	r0, r4
70000634:	f000 ff72 	bl	7000151c <__aeabi_fcmple>
70000638:	b168      	cbz	r0, 70000656 <jxf38p_get_tuned_again+0x10e>
7000063a:	4620      	mov	r0, r4
7000063c:	f000 fbe8 	bl	70000e10 <__aeabi_f2d>
70000640:	2200      	movs	r2, #0
70000642:	4b1f      	ldr	r3, [pc, #124]	; (700006c0 <jxf38p_get_tuned_again+0x178>)
70000644:	f000 fa84 	bl	70000b50 <__aeabi_dsub>
70000648:	4602      	mov	r2, r0
7000064a:	460b      	mov	r3, r1
7000064c:	f000 fa82 	bl	70000b54 <__adddf3>
70000650:	2200      	movs	r2, #0
70000652:	4b1f      	ldr	r3, [pc, #124]	; (700006d0 <jxf38p_get_tuned_again+0x188>)
70000654:	e7c9      	b.n	700005ea <jxf38p_get_tuned_again+0xa2>
70000656:	203f      	movs	r0, #63	; 0x3f
70000658:	e798      	b.n	7000058c <jxf38p_get_tuned_again+0x44>
7000065a:	f1a4 0310 	sub.w	r3, r4, #16
7000065e:	2b0f      	cmp	r3, #15
70000660:	d807      	bhi.n	70000672 <jxf38p_get_tuned_again+0x12a>
70000662:	f04f 5178 	mov.w	r1, #1040187392	; 0x3e000000
70000666:	f000 fdb1 	bl	700011cc <__aeabi_fmul>
7000066a:	4605      	mov	r5, r0
7000066c:	2000      	movs	r0, #0
7000066e:	6035      	str	r5, [r6, #0]
70000670:	bd70      	pop	{r4, r5, r6, pc}
70000672:	f1a4 0320 	sub.w	r3, r4, #32
70000676:	2b0f      	cmp	r3, #15
70000678:	d80a      	bhi.n	70000690 <jxf38p_get_tuned_again+0x148>
7000067a:	f000 fbc9 	bl	70000e10 <__aeabi_f2d>
7000067e:	2200      	movs	r2, #0
70000680:	4b14      	ldr	r3, [pc, #80]	; (700006d4 <jxf38p_get_tuned_again+0x18c>)
70000682:	f000 f883 	bl	7000078c <__aeabi_dmul>
70000686:	2200      	movs	r2, #0
70000688:	4b0e      	ldr	r3, [pc, #56]	; (700006c4 <jxf38p_get_tuned_again+0x17c>)
7000068a:	f000 fa61 	bl	70000b50 <__aeabi_dsub>
7000068e:	e78f      	b.n	700005b0 <jxf38p_get_tuned_again+0x68>
70000690:	3c30      	subs	r4, #48	; 0x30
70000692:	2c0f      	cmp	r4, #15
70000694:	d8ea      	bhi.n	7000066c <jxf38p_get_tuned_again+0x124>
70000696:	f000 fbbb 	bl	70000e10 <__aeabi_f2d>
7000069a:	2200      	movs	r2, #0
7000069c:	4b0e      	ldr	r3, [pc, #56]	; (700006d8 <jxf38p_get_tuned_again+0x190>)
7000069e:	f000 f875 	bl	7000078c <__aeabi_dmul>
700006a2:	2200      	movs	r2, #0
700006a4:	4b03      	ldr	r3, [pc, #12]	; (700006b4 <jxf38p_get_tuned_again+0x16c>)
700006a6:	e7f0      	b.n	7000068a <jxf38p_get_tuned_again+0x142>
700006a8:	f06f 0015 	mvn.w	r0, #21
700006ac:	e7e0      	b.n	70000670 <jxf38p_get_tuned_again+0x128>
700006ae:	bf00      	nop
700006b0:	3ff00000 	.word	0x3ff00000
700006b4:	40300000 	.word	0x40300000
700006b8:	7000004c 	.word	0x7000004c
700006bc:	3fb00000 	.word	0x3fb00000
700006c0:	40200000 	.word	0x40200000
700006c4:	40100000 	.word	0x40100000
700006c8:	40400000 	.word	0x40400000
700006cc:	417c0000 	.word	0x417c0000
700006d0:	40480000 	.word	0x40480000
700006d4:	3fd00000 	.word	0x3fd00000
700006d8:	3fe00000 	.word	0x3fe00000

700006dc <clip_d_word>:
700006dc:	4603      	mov	r3, r0
700006de:	4610      	mov	r0, r2
700006e0:	4293      	cmp	r3, r2
700006e2:	d803      	bhi.n	700006ec <clip_d_word+0x10>
700006e4:	428b      	cmp	r3, r1
700006e6:	bf38      	it	cc
700006e8:	460b      	movcc	r3, r1
700006ea:	4618      	mov	r0, r3
700006ec:	4770      	bx	lr
	...

700006f0 <rts_isp_get_sensor_ops>:
700006f0:	4800      	ldr	r0, [pc, #0]	; (700006f4 <rts_isp_get_sensor_ops+0x4>)
700006f2:	4770      	bx	lr
700006f4:	700006f8 	.word	0x700006f8

700006f8 <jxf38p_ops>:
700006f8:	73000005 3366786a 00007038 00000000     ...sjxf38p......
	...
7000071c:	70000251 70000311 00000000 70000549     Q..p...p....I..p
7000072c:	700003b1 700003c5 00000000 00000000     ...p...p........
7000073c:	7000039d 00000000 00000000 00000000     ...p............
7000074c:	70000479 00000000 00000000 00000000     y..p............
7000075c:	700004c1 00000000 00000000 00000000     ...p............
7000076c:	70000545 00000000 00000000 00000000     E..p............
	...

7000078c <__aeabi_dmul>:
7000078c:	b570      	push	{r4, r5, r6, lr}
7000078e:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000792:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
70000796:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
7000079a:	bf1d      	ittte	ne
7000079c:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
700007a0:	ea94 0f0c 	teqne	r4, ip
700007a4:	ea95 0f0c 	teqne	r5, ip
700007a8:	f000 f8de 	bleq	70000968 <__aeabi_dmul+0x1dc>
700007ac:	442c      	add	r4, r5
700007ae:	ea81 0603 	eor.w	r6, r1, r3
700007b2:	ea21 514c 	bic.w	r1, r1, ip, lsl #21
700007b6:	ea23 534c 	bic.w	r3, r3, ip, lsl #21
700007ba:	ea50 3501 	orrs.w	r5, r0, r1, lsl #12
700007be:	bf18      	it	ne
700007c0:	ea52 3503 	orrsne.w	r5, r2, r3, lsl #12
700007c4:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
700007c8:	f443 1380 	orr.w	r3, r3, #1048576	; 0x100000
700007cc:	d038      	beq.n	70000840 <__aeabi_dmul+0xb4>
700007ce:	fba0 ce02 	umull	ip, lr, r0, r2
700007d2:	f04f 0500 	mov.w	r5, #0
700007d6:	fbe1 e502 	umlal	lr, r5, r1, r2
700007da:	f006 4200 	and.w	r2, r6, #2147483648	; 0x80000000
700007de:	fbe0 e503 	umlal	lr, r5, r0, r3
700007e2:	f04f 0600 	mov.w	r6, #0
700007e6:	fbe1 5603 	umlal	r5, r6, r1, r3
700007ea:	f09c 0f00 	teq	ip, #0
700007ee:	bf18      	it	ne
700007f0:	f04e 0e01 	orrne.w	lr, lr, #1
700007f4:	f1a4 04ff 	sub.w	r4, r4, #255	; 0xff
700007f8:	f5b6 7f00 	cmp.w	r6, #512	; 0x200
700007fc:	f564 7440 	sbc.w	r4, r4, #768	; 0x300
70000800:	d204      	bcs.n	7000080c <__aeabi_dmul+0x80>
70000802:	ea5f 0e4e 	movs.w	lr, lr, lsl #1
70000806:	416d      	adcs	r5, r5
70000808:	eb46 0606 	adc.w	r6, r6, r6
7000080c:	ea42 21c6 	orr.w	r1, r2, r6, lsl #11
70000810:	ea41 5155 	orr.w	r1, r1, r5, lsr #21
70000814:	ea4f 20c5 	mov.w	r0, r5, lsl #11
70000818:	ea40 505e 	orr.w	r0, r0, lr, lsr #21
7000081c:	ea4f 2ece 	mov.w	lr, lr, lsl #11
70000820:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
70000824:	bf88      	it	hi
70000826:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
7000082a:	d81e      	bhi.n	7000086a <__aeabi_dmul+0xde>
7000082c:	f1be 4f00 	cmp.w	lr, #2147483648	; 0x80000000
70000830:	bf08      	it	eq
70000832:	ea5f 0e50 	movseq.w	lr, r0, lsr #1
70000836:	f150 0000 	adcs.w	r0, r0, #0
7000083a:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
7000083e:	bd70      	pop	{r4, r5, r6, pc}
70000840:	f006 4600 	and.w	r6, r6, #2147483648	; 0x80000000
70000844:	ea46 0101 	orr.w	r1, r6, r1
70000848:	ea40 0002 	orr.w	r0, r0, r2
7000084c:	ea81 0103 	eor.w	r1, r1, r3
70000850:	ebb4 045c 	subs.w	r4, r4, ip, lsr #1
70000854:	bfc2      	ittt	gt
70000856:	ebd4 050c 	rsbsgt	r5, r4, ip
7000085a:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
7000085e:	bd70      	popgt	{r4, r5, r6, pc}
70000860:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70000864:	f04f 0e00 	mov.w	lr, #0
70000868:	3c01      	subs	r4, #1
7000086a:	f300 80ab 	bgt.w	700009c4 <__aeabi_dmul+0x238>
7000086e:	f114 0f36 	cmn.w	r4, #54	; 0x36
70000872:	bfde      	ittt	le
70000874:	2000      	movle	r0, #0
70000876:	f001 4100 	andle.w	r1, r1, #2147483648	; 0x80000000
7000087a:	bd70      	pople	{r4, r5, r6, pc}
7000087c:	f1c4 0400 	rsb	r4, r4, #0
70000880:	3c20      	subs	r4, #32
70000882:	da35      	bge.n	700008f0 <__aeabi_dmul+0x164>
70000884:	340c      	adds	r4, #12
70000886:	dc1b      	bgt.n	700008c0 <__aeabi_dmul+0x134>
70000888:	f104 0414 	add.w	r4, r4, #20
7000088c:	f1c4 0520 	rsb	r5, r4, #32
70000890:	fa00 f305 	lsl.w	r3, r0, r5
70000894:	fa20 f004 	lsr.w	r0, r0, r4
70000898:	fa01 f205 	lsl.w	r2, r1, r5
7000089c:	ea40 0002 	orr.w	r0, r0, r2
700008a0:	f001 4200 	and.w	r2, r1, #2147483648	; 0x80000000
700008a4:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
700008a8:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
700008ac:	fa21 f604 	lsr.w	r6, r1, r4
700008b0:	eb42 0106 	adc.w	r1, r2, r6
700008b4:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
700008b8:	bf08      	it	eq
700008ba:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
700008be:	bd70      	pop	{r4, r5, r6, pc}
700008c0:	f1c4 040c 	rsb	r4, r4, #12
700008c4:	f1c4 0520 	rsb	r5, r4, #32
700008c8:	fa00 f304 	lsl.w	r3, r0, r4
700008cc:	fa20 f005 	lsr.w	r0, r0, r5
700008d0:	fa01 f204 	lsl.w	r2, r1, r4
700008d4:	ea40 0002 	orr.w	r0, r0, r2
700008d8:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700008dc:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
700008e0:	f141 0100 	adc.w	r1, r1, #0
700008e4:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
700008e8:	bf08      	it	eq
700008ea:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
700008ee:	bd70      	pop	{r4, r5, r6, pc}
700008f0:	f1c4 0520 	rsb	r5, r4, #32
700008f4:	fa00 f205 	lsl.w	r2, r0, r5
700008f8:	ea4e 0e02 	orr.w	lr, lr, r2
700008fc:	fa20 f304 	lsr.w	r3, r0, r4
70000900:	fa01 f205 	lsl.w	r2, r1, r5
70000904:	ea43 0302 	orr.w	r3, r3, r2
70000908:	fa21 f004 	lsr.w	r0, r1, r4
7000090c:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70000910:	fa21 f204 	lsr.w	r2, r1, r4
70000914:	ea20 0002 	bic.w	r0, r0, r2
70000918:	eb00 70d3 	add.w	r0, r0, r3, lsr #31
7000091c:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70000920:	bf08      	it	eq
70000922:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70000926:	bd70      	pop	{r4, r5, r6, pc}
70000928:	f094 0f00 	teq	r4, #0
7000092c:	d10f      	bne.n	7000094e <__aeabi_dmul+0x1c2>
7000092e:	f001 4600 	and.w	r6, r1, #2147483648	; 0x80000000
70000932:	0040      	lsls	r0, r0, #1
70000934:	eb41 0101 	adc.w	r1, r1, r1
70000938:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
7000093c:	bf08      	it	eq
7000093e:	3c01      	subeq	r4, #1
70000940:	d0f7      	beq.n	70000932 <__aeabi_dmul+0x1a6>
70000942:	ea41 0106 	orr.w	r1, r1, r6
70000946:	f095 0f00 	teq	r5, #0
7000094a:	bf18      	it	ne
7000094c:	4770      	bxne	lr
7000094e:	f003 4600 	and.w	r6, r3, #2147483648	; 0x80000000
70000952:	0052      	lsls	r2, r2, #1
70000954:	eb43 0303 	adc.w	r3, r3, r3
70000958:	f413 1f80 	tst.w	r3, #1048576	; 0x100000
7000095c:	bf08      	it	eq
7000095e:	3d01      	subeq	r5, #1
70000960:	d0f7      	beq.n	70000952 <__aeabi_dmul+0x1c6>
70000962:	ea43 0306 	orr.w	r3, r3, r6
70000966:	4770      	bx	lr
70000968:	ea94 0f0c 	teq	r4, ip
7000096c:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
70000970:	bf18      	it	ne
70000972:	ea95 0f0c 	teqne	r5, ip
70000976:	d00c      	beq.n	70000992 <__aeabi_dmul+0x206>
70000978:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
7000097c:	bf18      	it	ne
7000097e:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
70000982:	d1d1      	bne.n	70000928 <__aeabi_dmul+0x19c>
70000984:	ea81 0103 	eor.w	r1, r1, r3
70000988:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
7000098c:	f04f 0000 	mov.w	r0, #0
70000990:	bd70      	pop	{r4, r5, r6, pc}
70000992:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
70000996:	bf06      	itte	eq
70000998:	4610      	moveq	r0, r2
7000099a:	4619      	moveq	r1, r3
7000099c:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
700009a0:	d019      	beq.n	700009d6 <__aeabi_dmul+0x24a>
700009a2:	ea94 0f0c 	teq	r4, ip
700009a6:	d102      	bne.n	700009ae <__aeabi_dmul+0x222>
700009a8:	ea50 3601 	orrs.w	r6, r0, r1, lsl #12
700009ac:	d113      	bne.n	700009d6 <__aeabi_dmul+0x24a>
700009ae:	ea95 0f0c 	teq	r5, ip
700009b2:	d105      	bne.n	700009c0 <__aeabi_dmul+0x234>
700009b4:	ea52 3603 	orrs.w	r6, r2, r3, lsl #12
700009b8:	bf1c      	itt	ne
700009ba:	4610      	movne	r0, r2
700009bc:	4619      	movne	r1, r3
700009be:	d10a      	bne.n	700009d6 <__aeabi_dmul+0x24a>
700009c0:	ea81 0103 	eor.w	r1, r1, r3
700009c4:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700009c8:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
700009cc:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
700009d0:	f04f 0000 	mov.w	r0, #0
700009d4:	bd70      	pop	{r4, r5, r6, pc}
700009d6:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
700009da:	f441 0178 	orr.w	r1, r1, #16252928	; 0xf80000
700009de:	bd70      	pop	{r4, r5, r6, pc}
700009e0:	f04f 0cff 	mov.w	ip, #255	; 0xff
700009e4:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
700009e8:	bf1e      	ittt	ne
700009ea:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
700009ee:	ea92 0f0c 	teqne	r2, ip
700009f2:	ea93 0f0c 	teqne	r3, ip
700009f6:	d06f      	beq.n	70000ad8 <__aeabi_dmul+0x34c>
700009f8:	441a      	add	r2, r3
700009fa:	ea80 0c01 	eor.w	ip, r0, r1
700009fe:	0240      	lsls	r0, r0, #9
70000a00:	bf18      	it	ne
70000a02:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000a06:	d01e      	beq.n	70000a46 <__aeabi_dmul+0x2ba>
70000a08:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000a0c:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000a10:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000a14:	fba0 3101 	umull	r3, r1, r0, r1
70000a18:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000a1c:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000a20:	bf3e      	ittt	cc
70000a22:	0049      	lslcc	r1, r1, #1
70000a24:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000a28:	005b      	lslcc	r3, r3, #1
70000a2a:	ea40 0001 	orr.w	r0, r0, r1
70000a2e:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000a32:	2afd      	cmp	r2, #253	; 0xfd
70000a34:	d81d      	bhi.n	70000a72 <__aeabi_dmul+0x2e6>
70000a36:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000a3a:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000a3e:	bf08      	it	eq
70000a40:	f020 0001 	biceq.w	r0, r0, #1
70000a44:	4770      	bx	lr
70000a46:	f090 0f00 	teq	r0, #0
70000a4a:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000a4e:	bf08      	it	eq
70000a50:	0249      	lsleq	r1, r1, #9
70000a52:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000a56:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000a5a:	3a7f      	subs	r2, #127	; 0x7f
70000a5c:	bfc2      	ittt	gt
70000a5e:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000a62:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000a66:	4770      	bxgt	lr
70000a68:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000a6c:	f04f 0300 	mov.w	r3, #0
70000a70:	3a01      	subs	r2, #1
70000a72:	dc5d      	bgt.n	70000b30 <__aeabi_dmul+0x3a4>
70000a74:	f112 0f19 	cmn.w	r2, #25
70000a78:	bfdc      	itt	le
70000a7a:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000a7e:	4770      	bxle	lr
70000a80:	f1c2 0200 	rsb	r2, r2, #0
70000a84:	0041      	lsls	r1, r0, #1
70000a86:	fa21 f102 	lsr.w	r1, r1, r2
70000a8a:	f1c2 0220 	rsb	r2, r2, #32
70000a8e:	fa00 fc02 	lsl.w	ip, r0, r2
70000a92:	ea5f 0031 	movs.w	r0, r1, rrx
70000a96:	f140 0000 	adc.w	r0, r0, #0
70000a9a:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000a9e:	bf08      	it	eq
70000aa0:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000aa4:	4770      	bx	lr
70000aa6:	f092 0f00 	teq	r2, #0
70000aaa:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000aae:	bf02      	ittt	eq
70000ab0:	0040      	lsleq	r0, r0, #1
70000ab2:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000ab6:	3a01      	subeq	r2, #1
70000ab8:	d0f9      	beq.n	70000aae <__aeabi_dmul+0x322>
70000aba:	ea40 000c 	orr.w	r0, r0, ip
70000abe:	f093 0f00 	teq	r3, #0
70000ac2:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000ac6:	bf02      	ittt	eq
70000ac8:	0049      	lsleq	r1, r1, #1
70000aca:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000ace:	3b01      	subeq	r3, #1
70000ad0:	d0f9      	beq.n	70000ac6 <__aeabi_dmul+0x33a>
70000ad2:	ea41 010c 	orr.w	r1, r1, ip
70000ad6:	e78f      	b.n	700009f8 <__aeabi_dmul+0x26c>
70000ad8:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000adc:	ea92 0f0c 	teq	r2, ip
70000ae0:	bf18      	it	ne
70000ae2:	ea93 0f0c 	teqne	r3, ip
70000ae6:	d00a      	beq.n	70000afe <__aeabi_dmul+0x372>
70000ae8:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000aec:	bf18      	it	ne
70000aee:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000af2:	d1d8      	bne.n	70000aa6 <__aeabi_dmul+0x31a>
70000af4:	ea80 0001 	eor.w	r0, r0, r1
70000af8:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000afc:	4770      	bx	lr
70000afe:	f090 0f00 	teq	r0, #0
70000b02:	bf17      	itett	ne
70000b04:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000b08:	4608      	moveq	r0, r1
70000b0a:	f091 0f00 	teqne	r1, #0
70000b0e:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000b12:	d014      	beq.n	70000b3e <__aeabi_dmul+0x3b2>
70000b14:	ea92 0f0c 	teq	r2, ip
70000b18:	d101      	bne.n	70000b1e <__aeabi_dmul+0x392>
70000b1a:	0242      	lsls	r2, r0, #9
70000b1c:	d10f      	bne.n	70000b3e <__aeabi_dmul+0x3b2>
70000b1e:	ea93 0f0c 	teq	r3, ip
70000b22:	d103      	bne.n	70000b2c <__aeabi_dmul+0x3a0>
70000b24:	024b      	lsls	r3, r1, #9
70000b26:	bf18      	it	ne
70000b28:	4608      	movne	r0, r1
70000b2a:	d108      	bne.n	70000b3e <__aeabi_dmul+0x3b2>
70000b2c:	ea80 0001 	eor.w	r0, r0, r1
70000b30:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000b34:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000b38:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000b3c:	4770      	bx	lr
70000b3e:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000b42:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000b46:	4770      	bx	lr

70000b48 <__aeabi_drsub>:
70000b48:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000
70000b4c:	e002      	b.n	70000b54 <__adddf3>
70000b4e:	bf00      	nop

70000b50 <__aeabi_dsub>:
70000b50:	f083 4300 	eor.w	r3, r3, #2147483648	; 0x80000000

70000b54 <__adddf3>:
70000b54:	b530      	push	{r4, r5, lr}
70000b56:	ea4f 0441 	mov.w	r4, r1, lsl #1
70000b5a:	ea4f 0543 	mov.w	r5, r3, lsl #1
70000b5e:	ea94 0f05 	teq	r4, r5
70000b62:	bf08      	it	eq
70000b64:	ea90 0f02 	teqeq	r0, r2
70000b68:	bf1f      	itttt	ne
70000b6a:	ea54 0c00 	orrsne.w	ip, r4, r0
70000b6e:	ea55 0c02 	orrsne.w	ip, r5, r2
70000b72:	ea7f 5c64 	mvnsne.w	ip, r4, asr #21
70000b76:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70000b7a:	f000 80e2 	beq.w	70000d42 <__adddf3+0x1ee>
70000b7e:	ea4f 5454 	mov.w	r4, r4, lsr #21
70000b82:	ebd4 5555 	rsbs	r5, r4, r5, lsr #21
70000b86:	bfb8      	it	lt
70000b88:	426d      	neglt	r5, r5
70000b8a:	dd0c      	ble.n	70000ba6 <__adddf3+0x52>
70000b8c:	442c      	add	r4, r5
70000b8e:	ea80 0202 	eor.w	r2, r0, r2
70000b92:	ea81 0303 	eor.w	r3, r1, r3
70000b96:	ea82 0000 	eor.w	r0, r2, r0
70000b9a:	ea83 0101 	eor.w	r1, r3, r1
70000b9e:	ea80 0202 	eor.w	r2, r0, r2
70000ba2:	ea81 0303 	eor.w	r3, r1, r3
70000ba6:	2d36      	cmp	r5, #54	; 0x36
70000ba8:	bf88      	it	hi
70000baa:	bd30      	pophi	{r4, r5, pc}
70000bac:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000bb0:	ea4f 3101 	mov.w	r1, r1, lsl #12
70000bb4:	f44f 1c80 	mov.w	ip, #1048576	; 0x100000
70000bb8:	ea4c 3111 	orr.w	r1, ip, r1, lsr #12
70000bbc:	d002      	beq.n	70000bc4 <__adddf3+0x70>
70000bbe:	4240      	negs	r0, r0
70000bc0:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000bc4:	f013 4f00 	tst.w	r3, #2147483648	; 0x80000000
70000bc8:	ea4f 3303 	mov.w	r3, r3, lsl #12
70000bcc:	ea4c 3313 	orr.w	r3, ip, r3, lsr #12
70000bd0:	d002      	beq.n	70000bd8 <__adddf3+0x84>
70000bd2:	4252      	negs	r2, r2
70000bd4:	eb63 0343 	sbc.w	r3, r3, r3, lsl #1
70000bd8:	ea94 0f05 	teq	r4, r5
70000bdc:	f000 80a7 	beq.w	70000d2e <__adddf3+0x1da>
70000be0:	f1a4 0401 	sub.w	r4, r4, #1
70000be4:	f1d5 0e20 	rsbs	lr, r5, #32
70000be8:	db0d      	blt.n	70000c06 <__adddf3+0xb2>
70000bea:	fa02 fc0e 	lsl.w	ip, r2, lr
70000bee:	fa22 f205 	lsr.w	r2, r2, r5
70000bf2:	1880      	adds	r0, r0, r2
70000bf4:	f141 0100 	adc.w	r1, r1, #0
70000bf8:	fa03 f20e 	lsl.w	r2, r3, lr
70000bfc:	1880      	adds	r0, r0, r2
70000bfe:	fa43 f305 	asr.w	r3, r3, r5
70000c02:	4159      	adcs	r1, r3
70000c04:	e00e      	b.n	70000c24 <__adddf3+0xd0>
70000c06:	f1a5 0520 	sub.w	r5, r5, #32
70000c0a:	f10e 0e20 	add.w	lr, lr, #32
70000c0e:	2a01      	cmp	r2, #1
70000c10:	fa03 fc0e 	lsl.w	ip, r3, lr
70000c14:	bf28      	it	cs
70000c16:	f04c 0c02 	orrcs.w	ip, ip, #2
70000c1a:	fa43 f305 	asr.w	r3, r3, r5
70000c1e:	18c0      	adds	r0, r0, r3
70000c20:	eb51 71e3 	adcs.w	r1, r1, r3, asr #31
70000c24:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000c28:	d507      	bpl.n	70000c3a <__adddf3+0xe6>
70000c2a:	f04f 0e00 	mov.w	lr, #0
70000c2e:	f1dc 0c00 	rsbs	ip, ip, #0
70000c32:	eb7e 0000 	sbcs.w	r0, lr, r0
70000c36:	eb6e 0101 	sbc.w	r1, lr, r1
70000c3a:	f5b1 1f80 	cmp.w	r1, #1048576	; 0x100000
70000c3e:	d31b      	bcc.n	70000c78 <__adddf3+0x124>
70000c40:	f5b1 1f00 	cmp.w	r1, #2097152	; 0x200000
70000c44:	d30c      	bcc.n	70000c60 <__adddf3+0x10c>
70000c46:	0849      	lsrs	r1, r1, #1
70000c48:	ea5f 0030 	movs.w	r0, r0, rrx
70000c4c:	ea4f 0c3c 	mov.w	ip, ip, rrx
70000c50:	f104 0401 	add.w	r4, r4, #1
70000c54:	ea4f 5244 	mov.w	r2, r4, lsl #21
70000c58:	f512 0f80 	cmn.w	r2, #4194304	; 0x400000
70000c5c:	f080 809a 	bcs.w	70000d94 <__adddf3+0x240>
70000c60:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000c64:	bf08      	it	eq
70000c66:	ea5f 0c50 	movseq.w	ip, r0, lsr #1
70000c6a:	f150 0000 	adcs.w	r0, r0, #0
70000c6e:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
70000c72:	ea41 0105 	orr.w	r1, r1, r5
70000c76:	bd30      	pop	{r4, r5, pc}
70000c78:	ea5f 0c4c 	movs.w	ip, ip, lsl #1
70000c7c:	4140      	adcs	r0, r0
70000c7e:	eb41 0101 	adc.w	r1, r1, r1
70000c82:	3c01      	subs	r4, #1
70000c84:	bf28      	it	cs
70000c86:	f5b1 1f80 	cmpcs.w	r1, #1048576	; 0x100000
70000c8a:	d2e9      	bcs.n	70000c60 <__adddf3+0x10c>
70000c8c:	f091 0f00 	teq	r1, #0
70000c90:	bf04      	itt	eq
70000c92:	4601      	moveq	r1, r0
70000c94:	2000      	moveq	r0, #0
70000c96:	fab1 f381 	clz	r3, r1
70000c9a:	bf08      	it	eq
70000c9c:	3320      	addeq	r3, #32
70000c9e:	f1a3 030b 	sub.w	r3, r3, #11
70000ca2:	f1b3 0220 	subs.w	r2, r3, #32
70000ca6:	da0c      	bge.n	70000cc2 <__adddf3+0x16e>
70000ca8:	320c      	adds	r2, #12
70000caa:	dd08      	ble.n	70000cbe <__adddf3+0x16a>
70000cac:	f102 0c14 	add.w	ip, r2, #20
70000cb0:	f1c2 020c 	rsb	r2, r2, #12
70000cb4:	fa01 f00c 	lsl.w	r0, r1, ip
70000cb8:	fa21 f102 	lsr.w	r1, r1, r2
70000cbc:	e00c      	b.n	70000cd8 <__adddf3+0x184>
70000cbe:	f102 0214 	add.w	r2, r2, #20
70000cc2:	bfd8      	it	le
70000cc4:	f1c2 0c20 	rsble	ip, r2, #32
70000cc8:	fa01 f102 	lsl.w	r1, r1, r2
70000ccc:	fa20 fc0c 	lsr.w	ip, r0, ip
70000cd0:	bfdc      	itt	le
70000cd2:	ea41 010c 	orrle.w	r1, r1, ip
70000cd6:	4090      	lslle	r0, r2
70000cd8:	1ae4      	subs	r4, r4, r3
70000cda:	bfa2      	ittt	ge
70000cdc:	eb01 5104 	addge.w	r1, r1, r4, lsl #20
70000ce0:	4329      	orrge	r1, r5
70000ce2:	bd30      	popge	{r4, r5, pc}
70000ce4:	ea6f 0404 	mvn.w	r4, r4
70000ce8:	3c1f      	subs	r4, #31
70000cea:	da1c      	bge.n	70000d26 <__adddf3+0x1d2>
70000cec:	340c      	adds	r4, #12
70000cee:	dc0e      	bgt.n	70000d0e <__adddf3+0x1ba>
70000cf0:	f104 0414 	add.w	r4, r4, #20
70000cf4:	f1c4 0220 	rsb	r2, r4, #32
70000cf8:	fa20 f004 	lsr.w	r0, r0, r4
70000cfc:	fa01 f302 	lsl.w	r3, r1, r2
70000d00:	ea40 0003 	orr.w	r0, r0, r3
70000d04:	fa21 f304 	lsr.w	r3, r1, r4
70000d08:	ea45 0103 	orr.w	r1, r5, r3
70000d0c:	bd30      	pop	{r4, r5, pc}
70000d0e:	f1c4 040c 	rsb	r4, r4, #12
70000d12:	f1c4 0220 	rsb	r2, r4, #32
70000d16:	fa20 f002 	lsr.w	r0, r0, r2
70000d1a:	fa01 f304 	lsl.w	r3, r1, r4
70000d1e:	ea40 0003 	orr.w	r0, r0, r3
70000d22:	4629      	mov	r1, r5
70000d24:	bd30      	pop	{r4, r5, pc}
70000d26:	fa21 f004 	lsr.w	r0, r1, r4
70000d2a:	4629      	mov	r1, r5
70000d2c:	bd30      	pop	{r4, r5, pc}
70000d2e:	f094 0f00 	teq	r4, #0
70000d32:	f483 1380 	eor.w	r3, r3, #1048576	; 0x100000
70000d36:	bf06      	itte	eq
70000d38:	f481 1180 	eoreq.w	r1, r1, #1048576	; 0x100000
70000d3c:	3401      	addeq	r4, #1
70000d3e:	3d01      	subne	r5, #1
70000d40:	e74e      	b.n	70000be0 <__adddf3+0x8c>
70000d42:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70000d46:	bf18      	it	ne
70000d48:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70000d4c:	d029      	beq.n	70000da2 <__adddf3+0x24e>
70000d4e:	ea94 0f05 	teq	r4, r5
70000d52:	bf08      	it	eq
70000d54:	ea90 0f02 	teqeq	r0, r2
70000d58:	d005      	beq.n	70000d66 <__adddf3+0x212>
70000d5a:	ea54 0c00 	orrs.w	ip, r4, r0
70000d5e:	bf04      	itt	eq
70000d60:	4619      	moveq	r1, r3
70000d62:	4610      	moveq	r0, r2
70000d64:	bd30      	pop	{r4, r5, pc}
70000d66:	ea91 0f03 	teq	r1, r3
70000d6a:	bf1e      	ittt	ne
70000d6c:	2100      	movne	r1, #0
70000d6e:	2000      	movne	r0, #0
70000d70:	bd30      	popne	{r4, r5, pc}
70000d72:	ea5f 5c54 	movs.w	ip, r4, lsr #21
70000d76:	d105      	bne.n	70000d84 <__adddf3+0x230>
70000d78:	0040      	lsls	r0, r0, #1
70000d7a:	4149      	adcs	r1, r1
70000d7c:	bf28      	it	cs
70000d7e:	f041 4100 	orrcs.w	r1, r1, #2147483648	; 0x80000000
70000d82:	bd30      	pop	{r4, r5, pc}
70000d84:	f514 0480 	adds.w	r4, r4, #4194304	; 0x400000
70000d88:	bf3c      	itt	cc
70000d8a:	f501 1180 	addcc.w	r1, r1, #1048576	; 0x100000
70000d8e:	bd30      	popcc	{r4, r5, pc}
70000d90:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000d94:	f045 41fe 	orr.w	r1, r5, #2130706432	; 0x7f000000
70000d98:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
70000d9c:	f04f 0000 	mov.w	r0, #0
70000da0:	bd30      	pop	{r4, r5, pc}
70000da2:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70000da6:	bf1a      	itte	ne
70000da8:	4619      	movne	r1, r3
70000daa:	4610      	movne	r0, r2
70000dac:	ea7f 5c65 	mvnseq.w	ip, r5, asr #21
70000db0:	bf1c      	itt	ne
70000db2:	460b      	movne	r3, r1
70000db4:	4602      	movne	r2, r0
70000db6:	ea50 3401 	orrs.w	r4, r0, r1, lsl #12
70000dba:	bf06      	itte	eq
70000dbc:	ea52 3503 	orrseq.w	r5, r2, r3, lsl #12
70000dc0:	ea91 0f03 	teqeq	r1, r3
70000dc4:	f441 2100 	orrne.w	r1, r1, #524288	; 0x80000
70000dc8:	bd30      	pop	{r4, r5, pc}
70000dca:	bf00      	nop

70000dcc <__aeabi_ui2d>:
70000dcc:	f090 0f00 	teq	r0, #0
70000dd0:	bf04      	itt	eq
70000dd2:	2100      	moveq	r1, #0
70000dd4:	4770      	bxeq	lr
70000dd6:	b530      	push	{r4, r5, lr}
70000dd8:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000ddc:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000de0:	f04f 0500 	mov.w	r5, #0
70000de4:	f04f 0100 	mov.w	r1, #0
70000de8:	e750      	b.n	70000c8c <__adddf3+0x138>
70000dea:	bf00      	nop

70000dec <__aeabi_i2d>:
70000dec:	f090 0f00 	teq	r0, #0
70000df0:	bf04      	itt	eq
70000df2:	2100      	moveq	r1, #0
70000df4:	4770      	bxeq	lr
70000df6:	b530      	push	{r4, r5, lr}
70000df8:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000dfc:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000e00:	f010 4500 	ands.w	r5, r0, #2147483648	; 0x80000000
70000e04:	bf48      	it	mi
70000e06:	4240      	negmi	r0, r0
70000e08:	f04f 0100 	mov.w	r1, #0
70000e0c:	e73e      	b.n	70000c8c <__adddf3+0x138>
70000e0e:	bf00      	nop

70000e10 <__aeabi_f2d>:
70000e10:	0042      	lsls	r2, r0, #1
70000e12:	ea4f 01e2 	mov.w	r1, r2, asr #3
70000e16:	ea4f 0131 	mov.w	r1, r1, rrx
70000e1a:	ea4f 7002 	mov.w	r0, r2, lsl #28
70000e1e:	bf1f      	itttt	ne
70000e20:	f012 437f 	andsne.w	r3, r2, #4278190080	; 0xff000000
70000e24:	f093 4f7f 	teqne	r3, #4278190080	; 0xff000000
70000e28:	f081 5160 	eorne.w	r1, r1, #939524096	; 0x38000000
70000e2c:	4770      	bxne	lr
70000e2e:	f032 427f 	bics.w	r2, r2, #4278190080	; 0xff000000
70000e32:	bf08      	it	eq
70000e34:	4770      	bxeq	lr
70000e36:	f093 4f7f 	teq	r3, #4278190080	; 0xff000000
70000e3a:	bf04      	itt	eq
70000e3c:	f441 2100 	orreq.w	r1, r1, #524288	; 0x80000
70000e40:	4770      	bxeq	lr
70000e42:	b530      	push	{r4, r5, lr}
70000e44:	f44f 7460 	mov.w	r4, #896	; 0x380
70000e48:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000e4c:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
70000e50:	e71c      	b.n	70000c8c <__adddf3+0x138>
70000e52:	bf00      	nop

70000e54 <__aeabi_ul2d>:
70000e54:	ea50 0201 	orrs.w	r2, r0, r1
70000e58:	bf08      	it	eq
70000e5a:	4770      	bxeq	lr
70000e5c:	b530      	push	{r4, r5, lr}
70000e5e:	f04f 0500 	mov.w	r5, #0
70000e62:	e00a      	b.n	70000e7a <__aeabi_l2d+0x16>

70000e64 <__aeabi_l2d>:
70000e64:	ea50 0201 	orrs.w	r2, r0, r1
70000e68:	bf08      	it	eq
70000e6a:	4770      	bxeq	lr
70000e6c:	b530      	push	{r4, r5, lr}
70000e6e:	f011 4500 	ands.w	r5, r1, #2147483648	; 0x80000000
70000e72:	d502      	bpl.n	70000e7a <__aeabi_l2d+0x16>
70000e74:	4240      	negs	r0, r0
70000e76:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000e7a:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000e7e:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000e82:	ea5f 5c91 	movs.w	ip, r1, lsr #22
70000e86:	f43f aed8 	beq.w	70000c3a <__adddf3+0xe6>
70000e8a:	f04f 0203 	mov.w	r2, #3
70000e8e:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70000e92:	bf18      	it	ne
70000e94:	3203      	addne	r2, #3
70000e96:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70000e9a:	bf18      	it	ne
70000e9c:	3203      	addne	r2, #3
70000e9e:	eb02 02dc 	add.w	r2, r2, ip, lsr #3
70000ea2:	f1c2 0320 	rsb	r3, r2, #32
70000ea6:	fa00 fc03 	lsl.w	ip, r0, r3
70000eaa:	fa20 f002 	lsr.w	r0, r0, r2
70000eae:	fa01 fe03 	lsl.w	lr, r1, r3
70000eb2:	ea40 000e 	orr.w	r0, r0, lr
70000eb6:	fa21 f102 	lsr.w	r1, r1, r2
70000eba:	4414      	add	r4, r2
70000ebc:	e6bd      	b.n	70000c3a <__adddf3+0xe6>
70000ebe:	bf00      	nop

70000ec0 <__aeabi_d2iz>:
70000ec0:	ea4f 0241 	mov.w	r2, r1, lsl #1
70000ec4:	f512 1200 	adds.w	r2, r2, #2097152	; 0x200000
70000ec8:	d215      	bcs.n	70000ef6 <__aeabi_d2iz+0x36>
70000eca:	d511      	bpl.n	70000ef0 <__aeabi_d2iz+0x30>
70000ecc:	f46f 7378 	mvn.w	r3, #992	; 0x3e0
70000ed0:	ebb3 5262 	subs.w	r2, r3, r2, asr #21
70000ed4:	d912      	bls.n	70000efc <__aeabi_d2iz+0x3c>
70000ed6:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70000eda:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000ede:	ea43 5350 	orr.w	r3, r3, r0, lsr #21
70000ee2:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000ee6:	fa23 f002 	lsr.w	r0, r3, r2
70000eea:	bf18      	it	ne
70000eec:	4240      	negne	r0, r0
70000eee:	4770      	bx	lr
70000ef0:	f04f 0000 	mov.w	r0, #0
70000ef4:	4770      	bx	lr
70000ef6:	ea50 3001 	orrs.w	r0, r0, r1, lsl #12
70000efa:	d105      	bne.n	70000f08 <__aeabi_d2iz+0x48>
70000efc:	f011 4000 	ands.w	r0, r1, #2147483648	; 0x80000000
70000f00:	bf08      	it	eq
70000f02:	f06f 4000 	mvneq.w	r0, #2147483648	; 0x80000000
70000f06:	4770      	bx	lr
70000f08:	f04f 0000 	mov.w	r0, #0
70000f0c:	4770      	bx	lr
70000f0e:	bf00      	nop

70000f10 <__aeabi_d2f>:
70000f10:	ea4f 0241 	mov.w	r2, r1, lsl #1
70000f14:	f1b2 43e0 	subs.w	r3, r2, #1879048192	; 0x70000000
70000f18:	bf24      	itt	cs
70000f1a:	f5b3 1c00 	subscs.w	ip, r3, #2097152	; 0x200000
70000f1e:	f1dc 5cfe 	rsbscs	ip, ip, #532676608	; 0x1fc00000
70000f22:	d90d      	bls.n	70000f40 <__aeabi_d2f+0x30>
70000f24:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000f28:	ea4f 02c0 	mov.w	r2, r0, lsl #3
70000f2c:	ea4c 7050 	orr.w	r0, ip, r0, lsr #29
70000f30:	f1b2 4f00 	cmp.w	r2, #2147483648	; 0x80000000
70000f34:	eb40 0083 	adc.w	r0, r0, r3, lsl #2
70000f38:	bf08      	it	eq
70000f3a:	f020 0001 	biceq.w	r0, r0, #1
70000f3e:	4770      	bx	lr
70000f40:	f011 4f80 	tst.w	r1, #1073741824	; 0x40000000
70000f44:	d121      	bne.n	70000f8a <__aeabi_d2f+0x7a>
70000f46:	f113 7238 	adds.w	r2, r3, #48234496	; 0x2e00000
70000f4a:	bfbc      	itt	lt
70000f4c:	f001 4000 	andlt.w	r0, r1, #2147483648	; 0x80000000
70000f50:	4770      	bxlt	lr
70000f52:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70000f56:	ea4f 5252 	mov.w	r2, r2, lsr #21
70000f5a:	f1c2 0218 	rsb	r2, r2, #24
70000f5e:	f1c2 0c20 	rsb	ip, r2, #32
70000f62:	fa10 f30c 	lsls.w	r3, r0, ip
70000f66:	fa20 f002 	lsr.w	r0, r0, r2
70000f6a:	bf18      	it	ne
70000f6c:	f040 0001 	orrne.w	r0, r0, #1
70000f70:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70000f74:	ea4f 23d3 	mov.w	r3, r3, lsr #11
70000f78:	fa03 fc0c 	lsl.w	ip, r3, ip
70000f7c:	ea40 000c 	orr.w	r0, r0, ip
70000f80:	fa23 f302 	lsr.w	r3, r3, r2
70000f84:	ea4f 0343 	mov.w	r3, r3, lsl #1
70000f88:	e7cc      	b.n	70000f24 <__aeabi_d2f+0x14>
70000f8a:	ea7f 5362 	mvns.w	r3, r2, asr #21
70000f8e:	d107      	bne.n	70000fa0 <__aeabi_d2f+0x90>
70000f90:	ea50 3301 	orrs.w	r3, r0, r1, lsl #12
70000f94:	bf1e      	ittt	ne
70000f96:	f04f 40fe 	movne.w	r0, #2130706432	; 0x7f000000
70000f9a:	f440 0040 	orrne.w	r0, r0, #12582912	; 0xc00000
70000f9e:	4770      	bxne	lr
70000fa0:	f001 4000 	and.w	r0, r1, #2147483648	; 0x80000000
70000fa4:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000fa8:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000fac:	4770      	bx	lr
70000fae:	bf00      	nop

70000fb0 <__aeabi_frsub>:
70000fb0:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70000fb4:	e002      	b.n	70000fbc <__addsf3>
70000fb6:	bf00      	nop

70000fb8 <__aeabi_fsub>:
70000fb8:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

70000fbc <__addsf3>:
70000fbc:	0042      	lsls	r2, r0, #1
70000fbe:	bf1f      	itttt	ne
70000fc0:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70000fc4:	ea92 0f03 	teqne	r2, r3
70000fc8:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
70000fcc:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000fd0:	d06a      	beq.n	700010a8 <__addsf3+0xec>
70000fd2:	ea4f 6212 	mov.w	r2, r2, lsr #24
70000fd6:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
70000fda:	bfc1      	itttt	gt
70000fdc:	18d2      	addgt	r2, r2, r3
70000fde:	4041      	eorgt	r1, r0
70000fe0:	4048      	eorgt	r0, r1
70000fe2:	4041      	eorgt	r1, r0
70000fe4:	bfb8      	it	lt
70000fe6:	425b      	neglt	r3, r3
70000fe8:	2b19      	cmp	r3, #25
70000fea:	bf88      	it	hi
70000fec:	4770      	bxhi	lr
70000fee:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
70000ff2:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000ff6:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
70000ffa:	bf18      	it	ne
70000ffc:	4240      	negne	r0, r0
70000ffe:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70001002:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
70001006:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
7000100a:	bf18      	it	ne
7000100c:	4249      	negne	r1, r1
7000100e:	ea92 0f03 	teq	r2, r3
70001012:	d03f      	beq.n	70001094 <__addsf3+0xd8>
70001014:	f1a2 0201 	sub.w	r2, r2, #1
70001018:	fa41 fc03 	asr.w	ip, r1, r3
7000101c:	eb10 000c 	adds.w	r0, r0, ip
70001020:	f1c3 0320 	rsb	r3, r3, #32
70001024:	fa01 f103 	lsl.w	r1, r1, r3
70001028:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
7000102c:	d502      	bpl.n	70001034 <__addsf3+0x78>
7000102e:	4249      	negs	r1, r1
70001030:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70001034:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70001038:	d313      	bcc.n	70001062 <__addsf3+0xa6>
7000103a:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
7000103e:	d306      	bcc.n	7000104e <__addsf3+0x92>
70001040:	0840      	lsrs	r0, r0, #1
70001042:	ea4f 0131 	mov.w	r1, r1, rrx
70001046:	f102 0201 	add.w	r2, r2, #1
7000104a:	2afe      	cmp	r2, #254	; 0xfe
7000104c:	d251      	bcs.n	700010f2 <__addsf3+0x136>
7000104e:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
70001052:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70001056:	bf08      	it	eq
70001058:	f020 0001 	biceq.w	r0, r0, #1
7000105c:	ea40 0003 	orr.w	r0, r0, r3
70001060:	4770      	bx	lr
70001062:	0049      	lsls	r1, r1, #1
70001064:	eb40 0000 	adc.w	r0, r0, r0
70001068:	3a01      	subs	r2, #1
7000106a:	bf28      	it	cs
7000106c:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70001070:	d2ed      	bcs.n	7000104e <__addsf3+0x92>
70001072:	fab0 fc80 	clz	ip, r0
70001076:	f1ac 0c08 	sub.w	ip, ip, #8
7000107a:	ebb2 020c 	subs.w	r2, r2, ip
7000107e:	fa00 f00c 	lsl.w	r0, r0, ip
70001082:	bfaa      	itet	ge
70001084:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
70001088:	4252      	neglt	r2, r2
7000108a:	4318      	orrge	r0, r3
7000108c:	bfbc      	itt	lt
7000108e:	40d0      	lsrlt	r0, r2
70001090:	4318      	orrlt	r0, r3
70001092:	4770      	bx	lr
70001094:	f092 0f00 	teq	r2, #0
70001098:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
7000109c:	bf06      	itte	eq
7000109e:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
700010a2:	3201      	addeq	r2, #1
700010a4:	3b01      	subne	r3, #1
700010a6:	e7b5      	b.n	70001014 <__addsf3+0x58>
700010a8:	ea4f 0341 	mov.w	r3, r1, lsl #1
700010ac:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700010b0:	bf18      	it	ne
700010b2:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700010b6:	d021      	beq.n	700010fc <__addsf3+0x140>
700010b8:	ea92 0f03 	teq	r2, r3
700010bc:	d004      	beq.n	700010c8 <__addsf3+0x10c>
700010be:	f092 0f00 	teq	r2, #0
700010c2:	bf08      	it	eq
700010c4:	4608      	moveq	r0, r1
700010c6:	4770      	bx	lr
700010c8:	ea90 0f01 	teq	r0, r1
700010cc:	bf1c      	itt	ne
700010ce:	2000      	movne	r0, #0
700010d0:	4770      	bxne	lr
700010d2:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
700010d6:	d104      	bne.n	700010e2 <__addsf3+0x126>
700010d8:	0040      	lsls	r0, r0, #1
700010da:	bf28      	it	cs
700010dc:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
700010e0:	4770      	bx	lr
700010e2:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
700010e6:	bf3c      	itt	cc
700010e8:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
700010ec:	4770      	bxcc	lr
700010ee:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
700010f2:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
700010f6:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700010fa:	4770      	bx	lr
700010fc:	ea7f 6222 	mvns.w	r2, r2, asr #24
70001100:	bf16      	itet	ne
70001102:	4608      	movne	r0, r1
70001104:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70001108:	4601      	movne	r1, r0
7000110a:	0242      	lsls	r2, r0, #9
7000110c:	bf06      	itte	eq
7000110e:	ea5f 2341 	movseq.w	r3, r1, lsl #9
70001112:	ea90 0f01 	teqeq	r0, r1
70001116:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
7000111a:	4770      	bx	lr

7000111c <__aeabi_ui2f>:
7000111c:	f04f 0300 	mov.w	r3, #0
70001120:	e004      	b.n	7000112c <__aeabi_i2f+0x8>
70001122:	bf00      	nop

70001124 <__aeabi_i2f>:
70001124:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70001128:	bf48      	it	mi
7000112a:	4240      	negmi	r0, r0
7000112c:	ea5f 0c00 	movs.w	ip, r0
70001130:	bf08      	it	eq
70001132:	4770      	bxeq	lr
70001134:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70001138:	4601      	mov	r1, r0
7000113a:	f04f 0000 	mov.w	r0, #0
7000113e:	e01c      	b.n	7000117a <__aeabi_l2f+0x2a>

70001140 <__aeabi_ul2f>:
70001140:	ea50 0201 	orrs.w	r2, r0, r1
70001144:	bf08      	it	eq
70001146:	4770      	bxeq	lr
70001148:	f04f 0300 	mov.w	r3, #0
7000114c:	e00a      	b.n	70001164 <__aeabi_l2f+0x14>
7000114e:	bf00      	nop

70001150 <__aeabi_l2f>:
70001150:	ea50 0201 	orrs.w	r2, r0, r1
70001154:	bf08      	it	eq
70001156:	4770      	bxeq	lr
70001158:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
7000115c:	d502      	bpl.n	70001164 <__aeabi_l2f+0x14>
7000115e:	4240      	negs	r0, r0
70001160:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70001164:	ea5f 0c01 	movs.w	ip, r1
70001168:	bf02      	ittt	eq
7000116a:	4684      	moveq	ip, r0
7000116c:	4601      	moveq	r1, r0
7000116e:	2000      	moveq	r0, #0
70001170:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70001174:	bf08      	it	eq
70001176:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
7000117a:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
7000117e:	fabc f28c 	clz	r2, ip
70001182:	3a08      	subs	r2, #8
70001184:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
70001188:	db10      	blt.n	700011ac <__aeabi_l2f+0x5c>
7000118a:	fa01 fc02 	lsl.w	ip, r1, r2
7000118e:	4463      	add	r3, ip
70001190:	fa00 fc02 	lsl.w	ip, r0, r2
70001194:	f1c2 0220 	rsb	r2, r2, #32
70001198:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
7000119c:	fa20 f202 	lsr.w	r2, r0, r2
700011a0:	eb43 0002 	adc.w	r0, r3, r2
700011a4:	bf08      	it	eq
700011a6:	f020 0001 	biceq.w	r0, r0, #1
700011aa:	4770      	bx	lr
700011ac:	f102 0220 	add.w	r2, r2, #32
700011b0:	fa01 fc02 	lsl.w	ip, r1, r2
700011b4:	f1c2 0220 	rsb	r2, r2, #32
700011b8:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
700011bc:	fa21 f202 	lsr.w	r2, r1, r2
700011c0:	eb43 0002 	adc.w	r0, r3, r2
700011c4:	bf08      	it	eq
700011c6:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
700011ca:	4770      	bx	lr

700011cc <__aeabi_fmul>:
700011cc:	f04f 0cff 	mov.w	ip, #255	; 0xff
700011d0:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
700011d4:	bf1e      	ittt	ne
700011d6:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
700011da:	ea92 0f0c 	teqne	r2, ip
700011de:	ea93 0f0c 	teqne	r3, ip
700011e2:	d06f      	beq.n	700012c4 <__aeabi_fmul+0xf8>
700011e4:	441a      	add	r2, r3
700011e6:	ea80 0c01 	eor.w	ip, r0, r1
700011ea:	0240      	lsls	r0, r0, #9
700011ec:	bf18      	it	ne
700011ee:	ea5f 2141 	movsne.w	r1, r1, lsl #9
700011f2:	d01e      	beq.n	70001232 <__aeabi_fmul+0x66>
700011f4:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
700011f8:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
700011fc:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70001200:	fba0 3101 	umull	r3, r1, r0, r1
70001204:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70001208:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
7000120c:	bf3e      	ittt	cc
7000120e:	0049      	lslcc	r1, r1, #1
70001210:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70001214:	005b      	lslcc	r3, r3, #1
70001216:	ea40 0001 	orr.w	r0, r0, r1
7000121a:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
7000121e:	2afd      	cmp	r2, #253	; 0xfd
70001220:	d81d      	bhi.n	7000125e <__aeabi_fmul+0x92>
70001222:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70001226:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
7000122a:	bf08      	it	eq
7000122c:	f020 0001 	biceq.w	r0, r0, #1
70001230:	4770      	bx	lr
70001232:	f090 0f00 	teq	r0, #0
70001236:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
7000123a:	bf08      	it	eq
7000123c:	0249      	lsleq	r1, r1, #9
7000123e:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70001242:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70001246:	3a7f      	subs	r2, #127	; 0x7f
70001248:	bfc2      	ittt	gt
7000124a:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
7000124e:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70001252:	4770      	bxgt	lr
70001254:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001258:	f04f 0300 	mov.w	r3, #0
7000125c:	3a01      	subs	r2, #1
7000125e:	dc5d      	bgt.n	7000131c <__aeabi_fmul+0x150>
70001260:	f112 0f19 	cmn.w	r2, #25
70001264:	bfdc      	itt	le
70001266:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
7000126a:	4770      	bxle	lr
7000126c:	f1c2 0200 	rsb	r2, r2, #0
70001270:	0041      	lsls	r1, r0, #1
70001272:	fa21 f102 	lsr.w	r1, r1, r2
70001276:	f1c2 0220 	rsb	r2, r2, #32
7000127a:	fa00 fc02 	lsl.w	ip, r0, r2
7000127e:	ea5f 0031 	movs.w	r0, r1, rrx
70001282:	f140 0000 	adc.w	r0, r0, #0
70001286:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
7000128a:	bf08      	it	eq
7000128c:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70001290:	4770      	bx	lr
70001292:	f092 0f00 	teq	r2, #0
70001296:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
7000129a:	bf02      	ittt	eq
7000129c:	0040      	lsleq	r0, r0, #1
7000129e:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
700012a2:	3a01      	subeq	r2, #1
700012a4:	d0f9      	beq.n	7000129a <__aeabi_fmul+0xce>
700012a6:	ea40 000c 	orr.w	r0, r0, ip
700012aa:	f093 0f00 	teq	r3, #0
700012ae:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
700012b2:	bf02      	ittt	eq
700012b4:	0049      	lsleq	r1, r1, #1
700012b6:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
700012ba:	3b01      	subeq	r3, #1
700012bc:	d0f9      	beq.n	700012b2 <__aeabi_fmul+0xe6>
700012be:	ea41 010c 	orr.w	r1, r1, ip
700012c2:	e78f      	b.n	700011e4 <__aeabi_fmul+0x18>
700012c4:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
700012c8:	ea92 0f0c 	teq	r2, ip
700012cc:	bf18      	it	ne
700012ce:	ea93 0f0c 	teqne	r3, ip
700012d2:	d00a      	beq.n	700012ea <__aeabi_fmul+0x11e>
700012d4:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
700012d8:	bf18      	it	ne
700012da:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
700012de:	d1d8      	bne.n	70001292 <__aeabi_fmul+0xc6>
700012e0:	ea80 0001 	eor.w	r0, r0, r1
700012e4:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
700012e8:	4770      	bx	lr
700012ea:	f090 0f00 	teq	r0, #0
700012ee:	bf17      	itett	ne
700012f0:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
700012f4:	4608      	moveq	r0, r1
700012f6:	f091 0f00 	teqne	r1, #0
700012fa:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
700012fe:	d014      	beq.n	7000132a <__aeabi_fmul+0x15e>
70001300:	ea92 0f0c 	teq	r2, ip
70001304:	d101      	bne.n	7000130a <__aeabi_fmul+0x13e>
70001306:	0242      	lsls	r2, r0, #9
70001308:	d10f      	bne.n	7000132a <__aeabi_fmul+0x15e>
7000130a:	ea93 0f0c 	teq	r3, ip
7000130e:	d103      	bne.n	70001318 <__aeabi_fmul+0x14c>
70001310:	024b      	lsls	r3, r1, #9
70001312:	bf18      	it	ne
70001314:	4608      	movne	r0, r1
70001316:	d108      	bne.n	7000132a <__aeabi_fmul+0x15e>
70001318:	ea80 0001 	eor.w	r0, r0, r1
7000131c:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70001320:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70001324:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001328:	4770      	bx	lr
7000132a:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
7000132e:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70001332:	4770      	bx	lr

70001334 <__aeabi_fdiv>:
70001334:	f04f 0cff 	mov.w	ip, #255	; 0xff
70001338:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
7000133c:	bf1e      	ittt	ne
7000133e:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70001342:	ea92 0f0c 	teqne	r2, ip
70001346:	ea93 0f0c 	teqne	r3, ip
7000134a:	d069      	beq.n	70001420 <__aeabi_fdiv+0xec>
7000134c:	eba2 0203 	sub.w	r2, r2, r3
70001350:	ea80 0c01 	eor.w	ip, r0, r1
70001354:	0249      	lsls	r1, r1, #9
70001356:	ea4f 2040 	mov.w	r0, r0, lsl #9
7000135a:	d037      	beq.n	700013cc <__aeabi_fdiv+0x98>
7000135c:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70001360:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70001364:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70001368:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
7000136c:	428b      	cmp	r3, r1
7000136e:	bf38      	it	cc
70001370:	005b      	lslcc	r3, r3, #1
70001372:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70001376:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
7000137a:	428b      	cmp	r3, r1
7000137c:	bf24      	itt	cs
7000137e:	1a5b      	subcs	r3, r3, r1
70001380:	ea40 000c 	orrcs.w	r0, r0, ip
70001384:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70001388:	bf24      	itt	cs
7000138a:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
7000138e:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70001392:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70001396:	bf24      	itt	cs
70001398:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
7000139c:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
700013a0:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
700013a4:	bf24      	itt	cs
700013a6:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
700013aa:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
700013ae:	011b      	lsls	r3, r3, #4
700013b0:	bf18      	it	ne
700013b2:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
700013b6:	d1e0      	bne.n	7000137a <__aeabi_fdiv+0x46>
700013b8:	2afd      	cmp	r2, #253	; 0xfd
700013ba:	f63f af50 	bhi.w	7000125e <__aeabi_fmul+0x92>
700013be:	428b      	cmp	r3, r1
700013c0:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
700013c4:	bf08      	it	eq
700013c6:	f020 0001 	biceq.w	r0, r0, #1
700013ca:	4770      	bx	lr
700013cc:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
700013d0:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
700013d4:	327f      	adds	r2, #127	; 0x7f
700013d6:	bfc2      	ittt	gt
700013d8:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
700013dc:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
700013e0:	4770      	bxgt	lr
700013e2:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700013e6:	f04f 0300 	mov.w	r3, #0
700013ea:	3a01      	subs	r2, #1
700013ec:	e737      	b.n	7000125e <__aeabi_fmul+0x92>
700013ee:	f092 0f00 	teq	r2, #0
700013f2:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
700013f6:	bf02      	ittt	eq
700013f8:	0040      	lsleq	r0, r0, #1
700013fa:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
700013fe:	3a01      	subeq	r2, #1
70001400:	d0f9      	beq.n	700013f6 <__aeabi_fdiv+0xc2>
70001402:	ea40 000c 	orr.w	r0, r0, ip
70001406:	f093 0f00 	teq	r3, #0
7000140a:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
7000140e:	bf02      	ittt	eq
70001410:	0049      	lsleq	r1, r1, #1
70001412:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70001416:	3b01      	subeq	r3, #1
70001418:	d0f9      	beq.n	7000140e <__aeabi_fdiv+0xda>
7000141a:	ea41 010c 	orr.w	r1, r1, ip
7000141e:	e795      	b.n	7000134c <__aeabi_fdiv+0x18>
70001420:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70001424:	ea92 0f0c 	teq	r2, ip
70001428:	d108      	bne.n	7000143c <__aeabi_fdiv+0x108>
7000142a:	0242      	lsls	r2, r0, #9
7000142c:	f47f af7d 	bne.w	7000132a <__aeabi_fmul+0x15e>
70001430:	ea93 0f0c 	teq	r3, ip
70001434:	f47f af70 	bne.w	70001318 <__aeabi_fmul+0x14c>
70001438:	4608      	mov	r0, r1
7000143a:	e776      	b.n	7000132a <__aeabi_fmul+0x15e>
7000143c:	ea93 0f0c 	teq	r3, ip
70001440:	d104      	bne.n	7000144c <__aeabi_fdiv+0x118>
70001442:	024b      	lsls	r3, r1, #9
70001444:	f43f af4c 	beq.w	700012e0 <__aeabi_fmul+0x114>
70001448:	4608      	mov	r0, r1
7000144a:	e76e      	b.n	7000132a <__aeabi_fmul+0x15e>
7000144c:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70001450:	bf18      	it	ne
70001452:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70001456:	d1ca      	bne.n	700013ee <__aeabi_fdiv+0xba>
70001458:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
7000145c:	f47f af5c 	bne.w	70001318 <__aeabi_fmul+0x14c>
70001460:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70001464:	f47f af3c 	bne.w	700012e0 <__aeabi_fmul+0x114>
70001468:	e75f      	b.n	7000132a <__aeabi_fmul+0x15e>
7000146a:	bf00      	nop

7000146c <__gesf2>:
7000146c:	f04f 3cff 	mov.w	ip, #4294967295
70001470:	e006      	b.n	70001480 <__cmpsf2+0x4>
70001472:	bf00      	nop

70001474 <__lesf2>:
70001474:	f04f 0c01 	mov.w	ip, #1
70001478:	e002      	b.n	70001480 <__cmpsf2+0x4>
7000147a:	bf00      	nop

7000147c <__cmpsf2>:
7000147c:	f04f 0c01 	mov.w	ip, #1
70001480:	f84d cd04 	str.w	ip, [sp, #-4]!
70001484:	ea4f 0240 	mov.w	r2, r0, lsl #1
70001488:	ea4f 0341 	mov.w	r3, r1, lsl #1
7000148c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70001490:	bf18      	it	ne
70001492:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70001496:	d011      	beq.n	700014bc <__cmpsf2+0x40>
70001498:	b001      	add	sp, #4
7000149a:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
7000149e:	bf18      	it	ne
700014a0:	ea90 0f01 	teqne	r0, r1
700014a4:	bf58      	it	pl
700014a6:	ebb2 0003 	subspl.w	r0, r2, r3
700014aa:	bf88      	it	hi
700014ac:	17c8      	asrhi	r0, r1, #31
700014ae:	bf38      	it	cc
700014b0:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
700014b4:	bf18      	it	ne
700014b6:	f040 0001 	orrne.w	r0, r0, #1
700014ba:	4770      	bx	lr
700014bc:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700014c0:	d102      	bne.n	700014c8 <__cmpsf2+0x4c>
700014c2:	ea5f 2c40 	movs.w	ip, r0, lsl #9
700014c6:	d105      	bne.n	700014d4 <__cmpsf2+0x58>
700014c8:	ea7f 6c23 	mvns.w	ip, r3, asr #24
700014cc:	d1e4      	bne.n	70001498 <__cmpsf2+0x1c>
700014ce:	ea5f 2c41 	movs.w	ip, r1, lsl #9
700014d2:	d0e1      	beq.n	70001498 <__cmpsf2+0x1c>
700014d4:	f85d 0b04 	ldr.w	r0, [sp], #4
700014d8:	4770      	bx	lr
700014da:	bf00      	nop

700014dc <__aeabi_cfrcmple>:
700014dc:	4684      	mov	ip, r0
700014de:	4608      	mov	r0, r1
700014e0:	4661      	mov	r1, ip
700014e2:	e7ff      	b.n	700014e4 <__aeabi_cfcmpeq>

700014e4 <__aeabi_cfcmpeq>:
700014e4:	b50f      	push	{r0, r1, r2, r3, lr}
700014e6:	f7ff ffc9 	bl	7000147c <__cmpsf2>
700014ea:	2800      	cmp	r0, #0
700014ec:	bf48      	it	mi
700014ee:	f110 0f00 	cmnmi.w	r0, #0
700014f2:	bd0f      	pop	{r0, r1, r2, r3, pc}

700014f4 <__aeabi_fcmpeq>:
700014f4:	f84d ed08 	str.w	lr, [sp, #-8]!
700014f8:	f7ff fff4 	bl	700014e4 <__aeabi_cfcmpeq>
700014fc:	bf0c      	ite	eq
700014fe:	2001      	moveq	r0, #1
70001500:	2000      	movne	r0, #0
70001502:	f85d fb08 	ldr.w	pc, [sp], #8
70001506:	bf00      	nop

70001508 <__aeabi_fcmplt>:
70001508:	f84d ed08 	str.w	lr, [sp, #-8]!
7000150c:	f7ff ffea 	bl	700014e4 <__aeabi_cfcmpeq>
70001510:	bf34      	ite	cc
70001512:	2001      	movcc	r0, #1
70001514:	2000      	movcs	r0, #0
70001516:	f85d fb08 	ldr.w	pc, [sp], #8
7000151a:	bf00      	nop

7000151c <__aeabi_fcmple>:
7000151c:	f84d ed08 	str.w	lr, [sp, #-8]!
70001520:	f7ff ffe0 	bl	700014e4 <__aeabi_cfcmpeq>
70001524:	bf94      	ite	ls
70001526:	2001      	movls	r0, #1
70001528:	2000      	movhi	r0, #0
7000152a:	f85d fb08 	ldr.w	pc, [sp], #8
7000152e:	bf00      	nop

70001530 <__aeabi_fcmpge>:
70001530:	f84d ed08 	str.w	lr, [sp, #-8]!
70001534:	f7ff ffd2 	bl	700014dc <__aeabi_cfrcmple>
70001538:	bf94      	ite	ls
7000153a:	2001      	movls	r0, #1
7000153c:	2000      	movhi	r0, #0
7000153e:	f85d fb08 	ldr.w	pc, [sp], #8
70001542:	bf00      	nop

70001544 <__aeabi_fcmpgt>:
70001544:	f84d ed08 	str.w	lr, [sp, #-8]!
70001548:	f7ff ffc8 	bl	700014dc <__aeabi_cfrcmple>
7000154c:	bf34      	ite	cc
7000154e:	2001      	movcc	r0, #1
70001550:	2000      	movcs	r0, #0
70001552:	f85d fb08 	ldr.w	pc, [sp], #8
70001556:	bf00      	nop

70001558 <__aeabi_f2uiz>:
70001558:	0042      	lsls	r2, r0, #1
7000155a:	d20e      	bcs.n	7000157a <__aeabi_f2uiz+0x22>
7000155c:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70001560:	d30b      	bcc.n	7000157a <__aeabi_f2uiz+0x22>
70001562:	f04f 039e 	mov.w	r3, #158	; 0x9e
70001566:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
7000156a:	d409      	bmi.n	70001580 <__aeabi_f2uiz+0x28>
7000156c:	ea4f 2300 	mov.w	r3, r0, lsl #8
70001570:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70001574:	fa23 f002 	lsr.w	r0, r3, r2
70001578:	4770      	bx	lr
7000157a:	f04f 0000 	mov.w	r0, #0
7000157e:	4770      	bx	lr
70001580:	f112 0f61 	cmn.w	r2, #97	; 0x61
70001584:	d101      	bne.n	7000158a <__aeabi_f2uiz+0x32>
70001586:	0242      	lsls	r2, r0, #9
70001588:	d102      	bne.n	70001590 <__aeabi_f2uiz+0x38>
7000158a:	f04f 30ff 	mov.w	r0, #4294967295
7000158e:	4770      	bx	lr
70001590:	f04f 0000 	mov.w	r0, #0
70001594:	4770      	bx	lr
70001596:	bf00      	nop
