
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	11 07 00 70 61 02 00 70                             ...pa..p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

7000006c <g_jxf57_i2c_init_regs_asic>:
7000006c:	12 00 40 00 48 00 b3 00 48 00 33 00 0e 00 11 00     ..@.H...H.3.....
7000007c:	0f 00 0c 00 10 00 24 00 11 00 80 00 57 00 60 00     ......$.....W.`.
7000008c:	58 00 18 00 5f 00 01 00 46 00 18 00 b6 00 00 00     X..._...F.......
7000009c:	0d 00 d0 00 20 00 00 00 21 00 05 00 22 00 65 00     .... ...!...".e.
700000ac:	23 00 04 00 24 00 c4 00 25 00 40 00 26 00 43 00     #...$...%.@.&.C.
700000bc:	27 00 60 00 28 00 11 00 29 00 04 00 2a 00 51 00     '.`.(...)...*.Q.
700000cc:	2b 00 14 00 2c 00 00 00 2d 00 00 00 2e 00 14 00     +...,...-.......
700000dc:	2f 00 44 00 41 00 c8 00 42 00 03 00 47 00 42 00     /.D.A...B...G.B.
700000ec:	76 00 6a 00 77 00 09 00 80 00 01 00 af 00 22 00     v.j.w.........".
700000fc:	ab 00 00 00 1d 00 00 00 1e 00 04 00 6c 00 40 00     ............l.@.
7000010c:	08 00 00 00 70 00 8d 00 71 00 4d 00 72 00 6c 00     ....p...q.M.r.l.
7000011c:	73 00 56 00 74 00 02 00 78 00 9c 00 89 00 01 00     s.V.t...x.......
7000012c:	6b 00 00 00 86 00 00 00 30 00 8d 00 31 00 12 00     k.......0...1...
7000013c:	32 00 2f 00 33 00 20 00 34 00 3f 00 35 00 3f 00     2./.3. .4.?.5.?.
7000014c:	3a 00 a0 00 56 00 80 00 59 00 50 00 5a 00 88 00     :...V...Y.P.Z...
7000015c:	61 00 18 00 64 00 c2 00 85 00 50 00 8a 00 20 00     a...d.....P... .
7000016c:	90 00 08 00 91 00 01 00 94 00 e0 00 9b 00 8f 00     ................
7000017c:	a6 00 00 00 a7 00 80 00 a9 00 48 00 bf 00 01 00     ..........H.....
7000018c:	5a 00 19 00 5d 00 84 00 5e 00 90 00 5f 00 40 00     Z...]...^..._.@.
7000019c:	bf 00 00 00 45 00 09 00 5b 00 a0 00 5c 00 0c 00     ....E...[...\...
700001ac:	5d 00 41 00 5e 00 c3 00 65 00 32 00 66 00 10 00     ].A.^...e.2.f...
700001bc:	67 00 32 00 68 00 50 00 69 00 70 00 6a 00 23 00     g.2.h.P.i.p.j.#.
700001cc:	7a 00 88 00 8d 00 67 00 8f 00 90 00 9e 00 70 00     z.....g.......p.
700001dc:	a3 00 11 00 a4 00 87 00 a5 00 af 00 b8 00 21 00     ..............!.
700001ec:	b9 00 01 00 ba 00 f9 00 bb 00 05 00 bf 00 01 00     ................
700001fc:	4c 00 00 00 5f 00 c0 00 64 00 84 00 65 00 10 00     L..._...d...e...
7000020c:	66 00 40 00 67 00 70 00 6f 00 40 00 bf 00 00 00     f.@.g.p.o.@.....
7000021c:	13 00 81 00 4a 00 01 00 b1 00 04 00 50 00 02 00     ....J.......P...
7000022c:	49 00 10 00 bf 00 01 00 6f 00 52 00 5e 00 10 00     I.......o.R.^...
7000023c:	bf 00 00 00 bc 00 11 00 82 00 00 00 19 00 20 00     .............. .
7000024c:	ad 00 8a 00 12 00 00 00                             ........

70000254 <real_slave_addr>:
70000254:	40 00 00 00                                         @...

70000258 <slave_addr_list>:
70000258:	40 00 00 00 46 00 00 00                             @...F...

70000260 <rts_isp_set_voe_ops>:
70000260:	4b01      	ldr	r3, [pc, #4]	; (70000268 <rts_isp_set_voe_ops+0x8>)
70000262:	6018      	str	r0, [r3, #0]
70000264:	4770      	bx	lr
70000266:	bf00      	nop
70000268:	70000048 	.word	0x70000048

7000026c <isp_driver_is_fpga>:
7000026c:	2000      	movs	r0, #0
7000026e:	4770      	bx	lr

70000270 <jxf57_get_info>:
70000270:	b530      	push	{r4, r5, lr}
70000272:	2800      	cmp	r0, #0
70000274:	d14d      	bne.n	70000312 <jxf57_get_info+0xa2>
70000276:	2900      	cmp	r1, #0
70000278:	d04b      	beq.n	70000312 <jxf57_get_info+0xa2>
7000027a:	f44f 62f0 	mov.w	r2, #1920	; 0x780
7000027e:	f44f 6387 	mov.w	r3, #1080	; 0x438
70000282:	f44f 747a 	mov.w	r4, #1000	; 0x3e8
70000286:	4d24      	ldr	r5, [pc, #144]	; (70000318 <jxf57_get_info+0xa8>)
70000288:	7108      	strb	r0, [r1, #4]
7000028a:	f881 00b0 	strb.w	r0, [r1, #176]	; 0xb0
7000028e:	f8c1 00b4 	str.w	r0, [r1, #180]	; 0xb4
70000292:	f881 00bc 	strb.w	r0, [r1, #188]	; 0xbc
70000296:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
7000029a:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
7000029e:	f8c1 02dc 	str.w	r0, [r1, #732]	; 0x2dc
700002a2:	e9c1 2302 	strd	r2, r3, [r1, #8]
700002a6:	4b1d      	ldr	r3, [pc, #116]	; (7000031c <jxf57_get_info+0xac>)
700002a8:	4a1d      	ldr	r2, [pc, #116]	; (70000320 <jxf57_get_info+0xb0>)
700002aa:	610b      	str	r3, [r1, #16]
700002ac:	2301      	movs	r3, #1
700002ae:	6812      	ldr	r2, [r2, #0]
700002b0:	600b      	str	r3, [r1, #0]
700002b2:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
700002b6:	4a1b      	ldr	r2, [pc, #108]	; (70000324 <jxf57_get_info+0xb4>)
700002b8:	f881 3098 	strb.w	r3, [r1, #152]	; 0x98
700002bc:	7812      	ldrb	r2, [r2, #0]
700002be:	f881 30c8 	strb.w	r3, [r1, #200]	; 0xc8
700002c2:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
700002c6:	2203      	movs	r2, #3
700002c8:	e9c1 542a 	strd	r5, r4, [r1, #168]	; 0xa8
700002cc:	e9c1 3430 	strd	r3, r4, [r1, #192]	; 0xc0
700002d0:	e9c1 0433 	strd	r0, r4, [r1, #204]	; 0xcc
700002d4:	f240 1401 	movw	r4, #257	; 0x101
700002d8:	f242 7510 	movw	r5, #10000	; 0x2710
700002dc:	f881 20a4 	strb.w	r2, [r1, #164]	; 0xa4
700002e0:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
700002e4:	2406      	movs	r4, #6
700002e6:	f8c1 50b8 	str.w	r5, [r1, #184]	; 0xb8
700002ea:	f8c1 4088 	str.w	r4, [r1, #136]	; 0x88
700002ee:	2464      	movs	r4, #100	; 0x64
700002f0:	e9c1 3324 	strd	r3, r3, [r1, #144]	; 0x90
700002f4:	e9c1 3327 	strd	r3, r3, [r1, #156]	; 0x9c
700002f8:	f8c1 42e0 	str.w	r4, [r1, #736]	; 0x2e0
700002fc:	f881 32e4 	strb.w	r3, [r1, #740]	; 0x2e4
70000300:	f881 22f0 	strb.w	r2, [r1, #752]	; 0x2f0
70000304:	f8c1 22d4 	str.w	r2, [r1, #724]	; 0x2d4
70000308:	e9c1 34ba 	strd	r3, r4, [r1, #744]	; 0x2e8
7000030c:	e9c1 04bd 	strd	r0, r4, [r1, #756]	; 0x2f4
70000310:	bd30      	pop	{r4, r5, pc}
70000312:	f06f 0015 	mvn.w	r0, #21
70000316:	e7fb      	b.n	70000310 <jxf57_get_info+0xa0>
70000318:	016e3600 	.word	0x016e3600
7000031c:	41f00000 	.word	0x41f00000
70000320:	70000254 	.word	0x70000254
70000324:	7000004c 	.word	0x7000004c

70000328 <jxf57_get_init_info>:
70000328:	b570      	push	{r4, r5, r6, lr}
7000032a:	4614      	mov	r4, r2
7000032c:	4605      	mov	r5, r0
7000032e:	b110      	cbz	r0, 70000336 <jxf57_get_init_info+0xe>
70000330:	f06f 0015 	mvn.w	r0, #21
70000334:	bd70      	pop	{r4, r5, r6, pc}
70000336:	2a00      	cmp	r2, #0
70000338:	d0fa      	beq.n	70000330 <jxf57_get_init_info+0x8>
7000033a:	780b      	ldrb	r3, [r1, #0]
7000033c:	4e1b      	ldr	r6, [pc, #108]	; (700003ac <jxf57_get_init_info+0x84>)
7000033e:	68c8      	ldr	r0, [r1, #12]
70000340:	7033      	strb	r3, [r6, #0]
70000342:	f001 f919 	bl	70001578 <__aeabi_f2uiz>
70000346:	b280      	uxth	r0, r0
70000348:	281e      	cmp	r0, #30
7000034a:	d1f1      	bne.n	70000330 <jxf57_get_init_info+0x8>
7000034c:	4b18      	ldr	r3, [pc, #96]	; (700003b0 <jxf57_get_init_info+0x88>)
7000034e:	f44f 62f1 	mov.w	r2, #1928	; 0x788
70000352:	f44f 6020 	mov.w	r0, #2560	; 0xa00
70000356:	60a5      	str	r5, [r4, #8]
70000358:	6063      	str	r3, [r4, #4]
7000035a:	237a      	movs	r3, #122	; 0x7a
7000035c:	f8c4 5088 	str.w	r5, [r4, #136]	; 0x88
70000360:	6023      	str	r3, [r4, #0]
70000362:	2302      	movs	r3, #2
70000364:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
70000368:	f240 3303 	movw	r3, #771	; 0x303
7000036c:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
70000370:	230a      	movs	r3, #10
70000372:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
70000376:	2304      	movs	r3, #4
70000378:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
7000037c:	f44f 6388 	mov.w	r3, #1088	; 0x440
70000380:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
70000384:	2301      	movs	r3, #1
70000386:	f8c4 308c 	str.w	r3, [r4, #140]	; 0x8c
7000038a:	4b0a      	ldr	r3, [pc, #40]	; (700003b4 <jxf57_get_init_info+0x8c>)
7000038c:	e9c4 3024 	strd	r3, r0, [r4, #144]	; 0x90
70000390:	f240 4365 	movw	r3, #1125	; 0x465
70000394:	4628      	mov	r0, r5
70000396:	6073      	str	r3, [r6, #4]
70000398:	f8c4 3098 	str.w	r3, [r4, #152]	; 0x98
7000039c:	f248 33d6 	movw	r3, #33750	; 0x83d6
700003a0:	f8c4 309c 	str.w	r3, [r4, #156]	; 0x9c
700003a4:	4b04      	ldr	r3, [pc, #16]	; (700003b8 <jxf57_get_init_info+0x90>)
700003a6:	60b3      	str	r3, [r6, #8]
700003a8:	e7c4      	b.n	70000334 <jxf57_get_init_info+0xc>
700003aa:	bf00      	nop
700003ac:	7000004c 	.word	0x7000004c
700003b0:	7000006c 	.word	0x7000006c
700003b4:	05265c00 	.word	0x05265c00
700003b8:	41ed097b 	.word	0x41ed097b

700003bc <jxf57_start>:
700003bc:	b918      	cbnz	r0, 700003c6 <jxf57_start+0xa>
700003be:	4b03      	ldr	r3, [pc, #12]	; (700003cc <jxf57_start+0x10>)
700003c0:	2200      	movs	r2, #0
700003c2:	60da      	str	r2, [r3, #12]
700003c4:	4770      	bx	lr
700003c6:	f06f 0015 	mvn.w	r0, #21
700003ca:	4770      	bx	lr
700003cc:	7000004c 	.word	0x7000004c

700003d0 <jxf57_get_tuned_dgain>:
700003d0:	b920      	cbnz	r0, 700003dc <jxf57_get_tuned_dgain+0xc>
700003d2:	b119      	cbz	r1, 700003dc <jxf57_get_tuned_dgain+0xc>
700003d4:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
700003d8:	600b      	str	r3, [r1, #0]
700003da:	4770      	bx	lr
700003dc:	f06f 0015 	mvn.w	r0, #21
700003e0:	4770      	bx	lr
	...

700003e4 <jxf57_get_exposure_gain_info>:
700003e4:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
700003e8:	4614      	mov	r4, r2
700003ea:	2800      	cmp	r0, #0
700003ec:	d14b      	bne.n	70000486 <jxf57_get_exposure_gain_info+0xa2>
700003ee:	2900      	cmp	r1, #0
700003f0:	d049      	beq.n	70000486 <jxf57_get_exposure_gain_info+0xa2>
700003f2:	2a00      	cmp	r2, #0
700003f4:	d047      	beq.n	70000486 <jxf57_get_exposure_gain_info+0xa2>
700003f6:	f8d1 8000 	ldr.w	r8, [r1]
700003fa:	1d15      	adds	r5, r2, #4
700003fc:	4f23      	ldr	r7, [pc, #140]	; (7000048c <jxf57_get_exposure_gain_info+0xa8>)
700003fe:	698e      	ldr	r6, [r1, #24]
70000400:	4641      	mov	r1, r8
70000402:	68f8      	ldr	r0, [r7, #12]
70000404:	f000 fde8 	bl	70000fd8 <__aeabi_fsub>
70000408:	2100      	movs	r1, #0
7000040a:	4681      	mov	r9, r0
7000040c:	f001 f8a0 	bl	70001550 <__aeabi_fcmpge>
70000410:	2800      	cmp	r0, #0
70000412:	d033      	beq.n	7000047c <jxf57_get_exposure_gain_info+0x98>
70000414:	491e      	ldr	r1, [pc, #120]	; (70000490 <jxf57_get_exposure_gain_info+0xac>)
70000416:	4648      	mov	r0, r9
70000418:	f001 f8a4 	bl	70001564 <__aeabi_fcmpgt>
7000041c:	b1a8      	cbz	r0, 7000044a <jxf57_get_exposure_gain_info+0x66>
7000041e:	68b9      	ldr	r1, [r7, #8]
70000420:	4640      	mov	r0, r8
70000422:	f000 ff97 	bl	70001354 <__aeabi_fdiv>
70000426:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
7000042a:	f000 fdd7 	bl	70000fdc <__addsf3>
7000042e:	f001 f8a3 	bl	70001578 <__aeabi_f2uiz>
70000432:	f3c0 2307 	ubfx	r3, r0, #8, #8
70000436:	2202      	movs	r2, #2
70000438:	81e3      	strh	r3, [r4, #14]
7000043a:	2301      	movs	r3, #1
7000043c:	81a2      	strh	r2, [r4, #12]
7000043e:	8423      	strh	r3, [r4, #32]
70000440:	b2c3      	uxtb	r3, r0
70000442:	4610      	mov	r0, r2
70000444:	f8c7 800c 	str.w	r8, [r7, #12]
70000448:	8463      	strh	r3, [r4, #34]	; 0x22
7000044a:	2114      	movs	r1, #20
7000044c:	8a3f      	ldrh	r7, [r7, #16]
7000044e:	2300      	movs	r3, #0
70000450:	4341      	muls	r1, r0
70000452:	3003      	adds	r0, #3
70000454:	186a      	adds	r2, r5, r1
70000456:	8157      	strh	r7, [r2, #10]
70000458:	2723      	movs	r7, #35	; 0x23
7000045a:	8113      	strh	r3, [r2, #8]
7000045c:	f101 0214 	add.w	r2, r1, #20
70000460:	3128      	adds	r1, #40	; 0x28
70000462:	442a      	add	r2, r5
70000464:	4429      	add	r1, r5
70000466:	8117      	strh	r7, [r2, #8]
70000468:	0a37      	lsrs	r7, r6, #8
7000046a:	b2f6      	uxtb	r6, r6
7000046c:	8157      	strh	r7, [r2, #10]
7000046e:	2222      	movs	r2, #34	; 0x22
70000470:	814e      	strh	r6, [r1, #10]
70000472:	810a      	strh	r2, [r1, #8]
70000474:	6020      	str	r0, [r4, #0]
70000476:	4618      	mov	r0, r3
70000478:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
7000047c:	4905      	ldr	r1, [pc, #20]	; (70000494 <jxf57_get_exposure_gain_info+0xb0>)
7000047e:	4648      	mov	r0, r9
70000480:	f001 f852 	bl	70001528 <__aeabi_fcmplt>
70000484:	e7ca      	b.n	7000041c <jxf57_get_exposure_gain_info+0x38>
70000486:	f06f 0015 	mvn.w	r0, #21
7000048a:	e7f5      	b.n	70000478 <jxf57_get_exposure_gain_info+0x94>
7000048c:	7000004c 	.word	0x7000004c
70000490:	3a83126f 	.word	0x3a83126f
70000494:	ba83126f 	.word	0xba83126f

70000498 <jxf57_set_mirror_flip>:
70000498:	784b      	ldrb	r3, [r1, #1]
7000049a:	780a      	ldrb	r2, [r1, #0]
7000049c:	2b00      	cmp	r3, #0
7000049e:	bf14      	ite	ne
700004a0:	2302      	movne	r3, #2
700004a2:	2300      	moveq	r3, #0
700004a4:	2a00      	cmp	r2, #0
700004a6:	bf18      	it	ne
700004a8:	f043 0301 	orrne.w	r3, r3, #1
700004ac:	2201      	movs	r2, #1
700004ae:	2b02      	cmp	r3, #2
700004b0:	708a      	strb	r2, [r1, #2]
700004b2:	d009      	beq.n	700004c8 <jxf57_set_mirror_flip+0x30>
700004b4:	2b03      	cmp	r3, #3
700004b6:	d00b      	beq.n	700004d0 <jxf57_set_mirror_flip+0x38>
700004b8:	4293      	cmp	r3, r2
700004ba:	d007      	beq.n	700004cc <jxf57_set_mirror_flip+0x34>
700004bc:	4b05      	ldr	r3, [pc, #20]	; (700004d4 <jxf57_set_mirror_flip+0x3c>)
700004be:	610b      	str	r3, [r1, #16]
700004c0:	2301      	movs	r3, #1
700004c2:	2000      	movs	r0, #0
700004c4:	604b      	str	r3, [r1, #4]
700004c6:	4770      	bx	lr
700004c8:	4b03      	ldr	r3, [pc, #12]	; (700004d8 <jxf57_set_mirror_flip+0x40>)
700004ca:	e7f8      	b.n	700004be <jxf57_set_mirror_flip+0x26>
700004cc:	4b03      	ldr	r3, [pc, #12]	; (700004dc <jxf57_set_mirror_flip+0x44>)
700004ce:	e7f6      	b.n	700004be <jxf57_set_mirror_flip+0x26>
700004d0:	2312      	movs	r3, #18
700004d2:	e7f4      	b.n	700004be <jxf57_set_mirror_flip+0x26>
700004d4:	00300012 	.word	0x00300012
700004d8:	00200012 	.word	0x00200012
700004dc:	00100012 	.word	0x00100012

700004e0 <jxf57_check>:
700004e0:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
700004e2:	4f1d      	ldr	r7, [pc, #116]	; (70000558 <jxf57_check+0x78>)
700004e4:	4605      	mov	r5, r0
700004e6:	683b      	ldr	r3, [r7, #0]
700004e8:	6c1b      	ldr	r3, [r3, #64]	; 0x40
700004ea:	4798      	blx	r3
700004ec:	2801      	cmp	r0, #1
700004ee:	dc2f      	bgt.n	70000550 <jxf57_check+0x70>
700004f0:	4b1a      	ldr	r3, [pc, #104]	; (7000055c <jxf57_check+0x7c>)
700004f2:	f853 2020 	ldr.w	r2, [r3, r0, lsl #2]
700004f6:	4b1a      	ldr	r3, [pc, #104]	; (70000560 <jxf57_check+0x80>)
700004f8:	601a      	str	r2, [r3, #0]
700004fa:	683b      	ldr	r3, [r7, #0]
700004fc:	685b      	ldr	r3, [r3, #4]
700004fe:	4798      	blx	r3
70000500:	230a      	movs	r3, #10
70000502:	a901      	add	r1, sp, #4
70000504:	4628      	mov	r0, r5
70000506:	f8ad 3004 	strh.w	r3, [sp, #4]
7000050a:	683b      	ldr	r3, [r7, #0]
7000050c:	68db      	ldr	r3, [r3, #12]
7000050e:	4798      	blx	r3
70000510:	4604      	mov	r4, r0
70000512:	b128      	cbz	r0, 70000520 <jxf57_check+0x40>
70000514:	683b      	ldr	r3, [r7, #0]
70000516:	689b      	ldr	r3, [r3, #8]
70000518:	4798      	blx	r3
7000051a:	4620      	mov	r0, r4
7000051c:	b003      	add	sp, #12
7000051e:	bdf0      	pop	{r4, r5, r6, r7, pc}
70000520:	230b      	movs	r3, #11
70000522:	a901      	add	r1, sp, #4
70000524:	4628      	mov	r0, r5
70000526:	f8bd 6006 	ldrh.w	r6, [sp, #6]
7000052a:	f8ad 3004 	strh.w	r3, [sp, #4]
7000052e:	683b      	ldr	r3, [r7, #0]
70000530:	68db      	ldr	r3, [r3, #12]
70000532:	4798      	blx	r3
70000534:	4604      	mov	r4, r0
70000536:	2800      	cmp	r0, #0
70000538:	d1ec      	bne.n	70000514 <jxf57_check+0x34>
7000053a:	683b      	ldr	r3, [r7, #0]
7000053c:	f8bd 5006 	ldrh.w	r5, [sp, #6]
70000540:	689b      	ldr	r3, [r3, #8]
70000542:	4798      	blx	r3
70000544:	f640 0375 	movw	r3, #2165	; 0x875
70000548:	ea45 2506 	orr.w	r5, r5, r6, lsl #8
7000054c:	429d      	cmp	r5, r3
7000054e:	d0e4      	beq.n	7000051a <jxf57_check+0x3a>
70000550:	f06f 0415 	mvn.w	r4, #21
70000554:	e7e1      	b.n	7000051a <jxf57_check+0x3a>
70000556:	bf00      	nop
70000558:	70000048 	.word	0x70000048
7000055c:	70000258 	.word	0x70000258
70000560:	70000254 	.word	0x70000254

70000564 <jxf57_get_slave_addr_num>:
70000564:	2002      	movs	r0, #2
70000566:	4770      	bx	lr

70000568 <jxf57_get_tuned_again>:
70000568:	b570      	push	{r4, r5, r6, lr}
7000056a:	460e      	mov	r6, r1
7000056c:	2800      	cmp	r0, #0
7000056e:	f040 80ab 	bne.w	700006c8 <jxf57_get_tuned_again+0x160>
70000572:	2900      	cmp	r1, #0
70000574:	f000 80a8 	beq.w	700006c8 <jxf57_get_tuned_again+0x160>
70000578:	680c      	ldr	r4, [r1, #0]
7000057a:	f04f 517e 	mov.w	r1, #1065353216	; 0x3f800000
7000057e:	4620      	mov	r0, r4
70000580:	f000 ffe6 	bl	70001550 <__aeabi_fcmpge>
70000584:	b338      	cbz	r0, 700005d6 <jxf57_get_tuned_again+0x6e>
70000586:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
7000058a:	4620      	mov	r0, r4
7000058c:	f000 ffcc 	bl	70001528 <__aeabi_fcmplt>
70000590:	b308      	cbz	r0, 700005d6 <jxf57_get_tuned_again+0x6e>
70000592:	4620      	mov	r0, r4
70000594:	f000 fc4c 	bl	70000e30 <__aeabi_f2d>
70000598:	2200      	movs	r2, #0
7000059a:	4b4d      	ldr	r3, [pc, #308]	; (700006d0 <jxf57_get_tuned_again+0x168>)
7000059c:	f000 fae8 	bl	70000b70 <__aeabi_dsub>
700005a0:	2200      	movs	r2, #0
700005a2:	4b4c      	ldr	r3, [pc, #304]	; (700006d4 <jxf57_get_tuned_again+0x16c>)
700005a4:	f000 f902 	bl	700007ac <__aeabi_dmul>
700005a8:	f000 fc9a 	bl	70000ee0 <__aeabi_d2iz>
700005ac:	4b4a      	ldr	r3, [pc, #296]	; (700006d8 <jxf57_get_tuned_again+0x170>)
700005ae:	b284      	uxth	r4, r0
700005b0:	6118      	str	r0, [r3, #16]
700005b2:	4620      	mov	r0, r4
700005b4:	f000 fdc2 	bl	7000113c <__aeabi_ui2f>
700005b8:	2c0f      	cmp	r4, #15
700005ba:	d85e      	bhi.n	7000067a <jxf57_get_tuned_again+0x112>
700005bc:	f000 fc38 	bl	70000e30 <__aeabi_f2d>
700005c0:	2200      	movs	r2, #0
700005c2:	4b46      	ldr	r3, [pc, #280]	; (700006dc <jxf57_get_tuned_again+0x174>)
700005c4:	f000 f8f2 	bl	700007ac <__aeabi_dmul>
700005c8:	2200      	movs	r2, #0
700005ca:	4b41      	ldr	r3, [pc, #260]	; (700006d0 <jxf57_get_tuned_again+0x168>)
700005cc:	f000 fad2 	bl	70000b74 <__adddf3>
700005d0:	f000 fcae 	bl	70000f30 <__aeabi_d2f>
700005d4:	e059      	b.n	7000068a <jxf57_get_tuned_again+0x122>
700005d6:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
700005da:	4620      	mov	r0, r4
700005dc:	f000 ffb8 	bl	70001550 <__aeabi_fcmpge>
700005e0:	b1b0      	cbz	r0, 70000610 <jxf57_get_tuned_again+0xa8>
700005e2:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
700005e6:	4620      	mov	r0, r4
700005e8:	f000 ff9e 	bl	70001528 <__aeabi_fcmplt>
700005ec:	b180      	cbz	r0, 70000610 <jxf57_get_tuned_again+0xa8>
700005ee:	4620      	mov	r0, r4
700005f0:	f000 fc1e 	bl	70000e30 <__aeabi_f2d>
700005f4:	2200      	movs	r2, #0
700005f6:	f04f 4380 	mov.w	r3, #1073741824	; 0x40000000
700005fa:	f000 fab9 	bl	70000b70 <__aeabi_dsub>
700005fe:	2200      	movs	r2, #0
70000600:	4b37      	ldr	r3, [pc, #220]	; (700006e0 <jxf57_get_tuned_again+0x178>)
70000602:	f000 f8d3 	bl	700007ac <__aeabi_dmul>
70000606:	2200      	movs	r2, #0
70000608:	4b32      	ldr	r3, [pc, #200]	; (700006d4 <jxf57_get_tuned_again+0x16c>)
7000060a:	f000 fab3 	bl	70000b74 <__adddf3>
7000060e:	e7cb      	b.n	700005a8 <jxf57_get_tuned_again+0x40>
70000610:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
70000614:	4620      	mov	r0, r4
70000616:	f000 ff9b 	bl	70001550 <__aeabi_fcmpge>
7000061a:	b198      	cbz	r0, 70000644 <jxf57_get_tuned_again+0xdc>
7000061c:	f04f 4182 	mov.w	r1, #1090519040	; 0x41000000
70000620:	4620      	mov	r0, r4
70000622:	f000 ff81 	bl	70001528 <__aeabi_fcmplt>
70000626:	b168      	cbz	r0, 70000644 <jxf57_get_tuned_again+0xdc>
70000628:	4620      	mov	r0, r4
7000062a:	f000 fc01 	bl	70000e30 <__aeabi_f2d>
7000062e:	2200      	movs	r2, #0
70000630:	4b2c      	ldr	r3, [pc, #176]	; (700006e4 <jxf57_get_tuned_again+0x17c>)
70000632:	f000 fa9d 	bl	70000b70 <__aeabi_dsub>
70000636:	2200      	movs	r2, #0
70000638:	4b2a      	ldr	r3, [pc, #168]	; (700006e4 <jxf57_get_tuned_again+0x17c>)
7000063a:	f000 f8b7 	bl	700007ac <__aeabi_dmul>
7000063e:	2200      	movs	r2, #0
70000640:	4b29      	ldr	r3, [pc, #164]	; (700006e8 <jxf57_get_tuned_again+0x180>)
70000642:	e7e2      	b.n	7000060a <jxf57_get_tuned_again+0xa2>
70000644:	f04f 4182 	mov.w	r1, #1090519040	; 0x41000000
70000648:	4620      	mov	r0, r4
7000064a:	f000 ff81 	bl	70001550 <__aeabi_fcmpge>
7000064e:	b190      	cbz	r0, 70000676 <jxf57_get_tuned_again+0x10e>
70000650:	4926      	ldr	r1, [pc, #152]	; (700006ec <jxf57_get_tuned_again+0x184>)
70000652:	4620      	mov	r0, r4
70000654:	f000 ff72 	bl	7000153c <__aeabi_fcmple>
70000658:	b168      	cbz	r0, 70000676 <jxf57_get_tuned_again+0x10e>
7000065a:	4620      	mov	r0, r4
7000065c:	f000 fbe8 	bl	70000e30 <__aeabi_f2d>
70000660:	2200      	movs	r2, #0
70000662:	4b1f      	ldr	r3, [pc, #124]	; (700006e0 <jxf57_get_tuned_again+0x178>)
70000664:	f000 fa84 	bl	70000b70 <__aeabi_dsub>
70000668:	4602      	mov	r2, r0
7000066a:	460b      	mov	r3, r1
7000066c:	f000 fa82 	bl	70000b74 <__adddf3>
70000670:	2200      	movs	r2, #0
70000672:	4b1f      	ldr	r3, [pc, #124]	; (700006f0 <jxf57_get_tuned_again+0x188>)
70000674:	e7c9      	b.n	7000060a <jxf57_get_tuned_again+0xa2>
70000676:	203f      	movs	r0, #63	; 0x3f
70000678:	e798      	b.n	700005ac <jxf57_get_tuned_again+0x44>
7000067a:	f1a4 0310 	sub.w	r3, r4, #16
7000067e:	2b0f      	cmp	r3, #15
70000680:	d807      	bhi.n	70000692 <jxf57_get_tuned_again+0x12a>
70000682:	f04f 5178 	mov.w	r1, #1040187392	; 0x3e000000
70000686:	f000 fdb1 	bl	700011ec <__aeabi_fmul>
7000068a:	4605      	mov	r5, r0
7000068c:	2000      	movs	r0, #0
7000068e:	6035      	str	r5, [r6, #0]
70000690:	bd70      	pop	{r4, r5, r6, pc}
70000692:	f1a4 0320 	sub.w	r3, r4, #32
70000696:	2b0f      	cmp	r3, #15
70000698:	d80a      	bhi.n	700006b0 <jxf57_get_tuned_again+0x148>
7000069a:	f000 fbc9 	bl	70000e30 <__aeabi_f2d>
7000069e:	2200      	movs	r2, #0
700006a0:	4b14      	ldr	r3, [pc, #80]	; (700006f4 <jxf57_get_tuned_again+0x18c>)
700006a2:	f000 f883 	bl	700007ac <__aeabi_dmul>
700006a6:	2200      	movs	r2, #0
700006a8:	4b0e      	ldr	r3, [pc, #56]	; (700006e4 <jxf57_get_tuned_again+0x17c>)
700006aa:	f000 fa61 	bl	70000b70 <__aeabi_dsub>
700006ae:	e78f      	b.n	700005d0 <jxf57_get_tuned_again+0x68>
700006b0:	3c30      	subs	r4, #48	; 0x30
700006b2:	2c0f      	cmp	r4, #15
700006b4:	d8ea      	bhi.n	7000068c <jxf57_get_tuned_again+0x124>
700006b6:	f000 fbbb 	bl	70000e30 <__aeabi_f2d>
700006ba:	2200      	movs	r2, #0
700006bc:	4b0e      	ldr	r3, [pc, #56]	; (700006f8 <jxf57_get_tuned_again+0x190>)
700006be:	f000 f875 	bl	700007ac <__aeabi_dmul>
700006c2:	2200      	movs	r2, #0
700006c4:	4b03      	ldr	r3, [pc, #12]	; (700006d4 <jxf57_get_tuned_again+0x16c>)
700006c6:	e7f0      	b.n	700006aa <jxf57_get_tuned_again+0x142>
700006c8:	f06f 0015 	mvn.w	r0, #21
700006cc:	e7e0      	b.n	70000690 <jxf57_get_tuned_again+0x128>
700006ce:	bf00      	nop
700006d0:	3ff00000 	.word	0x3ff00000
700006d4:	40300000 	.word	0x40300000
700006d8:	7000004c 	.word	0x7000004c
700006dc:	3fb00000 	.word	0x3fb00000
700006e0:	40200000 	.word	0x40200000
700006e4:	40100000 	.word	0x40100000
700006e8:	40400000 	.word	0x40400000
700006ec:	417c0000 	.word	0x417c0000
700006f0:	40480000 	.word	0x40480000
700006f4:	3fd00000 	.word	0x3fd00000
700006f8:	3fe00000 	.word	0x3fe00000

700006fc <clip_d_word>:
700006fc:	4603      	mov	r3, r0
700006fe:	4610      	mov	r0, r2
70000700:	4293      	cmp	r3, r2
70000702:	d803      	bhi.n	7000070c <clip_d_word+0x10>
70000704:	428b      	cmp	r3, r1
70000706:	bf38      	it	cc
70000708:	460b      	movcc	r3, r1
7000070a:	4618      	mov	r0, r3
7000070c:	4770      	bx	lr
	...

70000710 <rts_isp_get_sensor_ops>:
70000710:	4800      	ldr	r0, [pc, #0]	; (70000714 <rts_isp_get_sensor_ops+0x4>)
70000712:	4770      	bx	lr
70000714:	70000718 	.word	0x70000718

70000718 <jxf57_ops>:
70000718:	73000005 3566786a 00000037 00000000     ...sjxf57.......
	...
7000073c:	70000271 70000329 00000000 70000569     q..p)..p....i..p
7000074c:	700003d1 700003e5 00000000 00000000     ...p...p........
7000075c:	700003bd 00000000 00000000 00000000     ...p............
7000076c:	70000499 00000000 00000000 00000000     ...p............
7000077c:	700004e1 00000000 00000000 00000000     ...p............
7000078c:	70000565 00000000 00000000 00000000     e..p............
	...

700007ac <__aeabi_dmul>:
700007ac:	b570      	push	{r4, r5, r6, lr}
700007ae:	f04f 0cff 	mov.w	ip, #255	; 0xff
700007b2:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
700007b6:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
700007ba:	bf1d      	ittte	ne
700007bc:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
700007c0:	ea94 0f0c 	teqne	r4, ip
700007c4:	ea95 0f0c 	teqne	r5, ip
700007c8:	f000 f8de 	bleq	70000988 <__aeabi_dmul+0x1dc>
700007cc:	442c      	add	r4, r5
700007ce:	ea81 0603 	eor.w	r6, r1, r3
700007d2:	ea21 514c 	bic.w	r1, r1, ip, lsl #21
700007d6:	ea23 534c 	bic.w	r3, r3, ip, lsl #21
700007da:	ea50 3501 	orrs.w	r5, r0, r1, lsl #12
700007de:	bf18      	it	ne
700007e0:	ea52 3503 	orrsne.w	r5, r2, r3, lsl #12
700007e4:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
700007e8:	f443 1380 	orr.w	r3, r3, #1048576	; 0x100000
700007ec:	d038      	beq.n	70000860 <__aeabi_dmul+0xb4>
700007ee:	fba0 ce02 	umull	ip, lr, r0, r2
700007f2:	f04f 0500 	mov.w	r5, #0
700007f6:	fbe1 e502 	umlal	lr, r5, r1, r2
700007fa:	f006 4200 	and.w	r2, r6, #2147483648	; 0x80000000
700007fe:	fbe0 e503 	umlal	lr, r5, r0, r3
70000802:	f04f 0600 	mov.w	r6, #0
70000806:	fbe1 5603 	umlal	r5, r6, r1, r3
7000080a:	f09c 0f00 	teq	ip, #0
7000080e:	bf18      	it	ne
70000810:	f04e 0e01 	orrne.w	lr, lr, #1
70000814:	f1a4 04ff 	sub.w	r4, r4, #255	; 0xff
70000818:	f5b6 7f00 	cmp.w	r6, #512	; 0x200
7000081c:	f564 7440 	sbc.w	r4, r4, #768	; 0x300
70000820:	d204      	bcs.n	7000082c <__aeabi_dmul+0x80>
70000822:	ea5f 0e4e 	movs.w	lr, lr, lsl #1
70000826:	416d      	adcs	r5, r5
70000828:	eb46 0606 	adc.w	r6, r6, r6
7000082c:	ea42 21c6 	orr.w	r1, r2, r6, lsl #11
70000830:	ea41 5155 	orr.w	r1, r1, r5, lsr #21
70000834:	ea4f 20c5 	mov.w	r0, r5, lsl #11
70000838:	ea40 505e 	orr.w	r0, r0, lr, lsr #21
7000083c:	ea4f 2ece 	mov.w	lr, lr, lsl #11
70000840:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
70000844:	bf88      	it	hi
70000846:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
7000084a:	d81e      	bhi.n	7000088a <__aeabi_dmul+0xde>
7000084c:	f1be 4f00 	cmp.w	lr, #2147483648	; 0x80000000
70000850:	bf08      	it	eq
70000852:	ea5f 0e50 	movseq.w	lr, r0, lsr #1
70000856:	f150 0000 	adcs.w	r0, r0, #0
7000085a:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
7000085e:	bd70      	pop	{r4, r5, r6, pc}
70000860:	f006 4600 	and.w	r6, r6, #2147483648	; 0x80000000
70000864:	ea46 0101 	orr.w	r1, r6, r1
70000868:	ea40 0002 	orr.w	r0, r0, r2
7000086c:	ea81 0103 	eor.w	r1, r1, r3
70000870:	ebb4 045c 	subs.w	r4, r4, ip, lsr #1
70000874:	bfc2      	ittt	gt
70000876:	ebd4 050c 	rsbsgt	r5, r4, ip
7000087a:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
7000087e:	bd70      	popgt	{r4, r5, r6, pc}
70000880:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70000884:	f04f 0e00 	mov.w	lr, #0
70000888:	3c01      	subs	r4, #1
7000088a:	f300 80ab 	bgt.w	700009e4 <__aeabi_dmul+0x238>
7000088e:	f114 0f36 	cmn.w	r4, #54	; 0x36
70000892:	bfde      	ittt	le
70000894:	2000      	movle	r0, #0
70000896:	f001 4100 	andle.w	r1, r1, #2147483648	; 0x80000000
7000089a:	bd70      	pople	{r4, r5, r6, pc}
7000089c:	f1c4 0400 	rsb	r4, r4, #0
700008a0:	3c20      	subs	r4, #32
700008a2:	da35      	bge.n	70000910 <__aeabi_dmul+0x164>
700008a4:	340c      	adds	r4, #12
700008a6:	dc1b      	bgt.n	700008e0 <__aeabi_dmul+0x134>
700008a8:	f104 0414 	add.w	r4, r4, #20
700008ac:	f1c4 0520 	rsb	r5, r4, #32
700008b0:	fa00 f305 	lsl.w	r3, r0, r5
700008b4:	fa20 f004 	lsr.w	r0, r0, r4
700008b8:	fa01 f205 	lsl.w	r2, r1, r5
700008bc:	ea40 0002 	orr.w	r0, r0, r2
700008c0:	f001 4200 	and.w	r2, r1, #2147483648	; 0x80000000
700008c4:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
700008c8:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
700008cc:	fa21 f604 	lsr.w	r6, r1, r4
700008d0:	eb42 0106 	adc.w	r1, r2, r6
700008d4:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
700008d8:	bf08      	it	eq
700008da:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
700008de:	bd70      	pop	{r4, r5, r6, pc}
700008e0:	f1c4 040c 	rsb	r4, r4, #12
700008e4:	f1c4 0520 	rsb	r5, r4, #32
700008e8:	fa00 f304 	lsl.w	r3, r0, r4
700008ec:	fa20 f005 	lsr.w	r0, r0, r5
700008f0:	fa01 f204 	lsl.w	r2, r1, r4
700008f4:	ea40 0002 	orr.w	r0, r0, r2
700008f8:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700008fc:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
70000900:	f141 0100 	adc.w	r1, r1, #0
70000904:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70000908:	bf08      	it	eq
7000090a:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
7000090e:	bd70      	pop	{r4, r5, r6, pc}
70000910:	f1c4 0520 	rsb	r5, r4, #32
70000914:	fa00 f205 	lsl.w	r2, r0, r5
70000918:	ea4e 0e02 	orr.w	lr, lr, r2
7000091c:	fa20 f304 	lsr.w	r3, r0, r4
70000920:	fa01 f205 	lsl.w	r2, r1, r5
70000924:	ea43 0302 	orr.w	r3, r3, r2
70000928:	fa21 f004 	lsr.w	r0, r1, r4
7000092c:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70000930:	fa21 f204 	lsr.w	r2, r1, r4
70000934:	ea20 0002 	bic.w	r0, r0, r2
70000938:	eb00 70d3 	add.w	r0, r0, r3, lsr #31
7000093c:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70000940:	bf08      	it	eq
70000942:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70000946:	bd70      	pop	{r4, r5, r6, pc}
70000948:	f094 0f00 	teq	r4, #0
7000094c:	d10f      	bne.n	7000096e <__aeabi_dmul+0x1c2>
7000094e:	f001 4600 	and.w	r6, r1, #2147483648	; 0x80000000
70000952:	0040      	lsls	r0, r0, #1
70000954:	eb41 0101 	adc.w	r1, r1, r1
70000958:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
7000095c:	bf08      	it	eq
7000095e:	3c01      	subeq	r4, #1
70000960:	d0f7      	beq.n	70000952 <__aeabi_dmul+0x1a6>
70000962:	ea41 0106 	orr.w	r1, r1, r6
70000966:	f095 0f00 	teq	r5, #0
7000096a:	bf18      	it	ne
7000096c:	4770      	bxne	lr
7000096e:	f003 4600 	and.w	r6, r3, #2147483648	; 0x80000000
70000972:	0052      	lsls	r2, r2, #1
70000974:	eb43 0303 	adc.w	r3, r3, r3
70000978:	f413 1f80 	tst.w	r3, #1048576	; 0x100000
7000097c:	bf08      	it	eq
7000097e:	3d01      	subeq	r5, #1
70000980:	d0f7      	beq.n	70000972 <__aeabi_dmul+0x1c6>
70000982:	ea43 0306 	orr.w	r3, r3, r6
70000986:	4770      	bx	lr
70000988:	ea94 0f0c 	teq	r4, ip
7000098c:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
70000990:	bf18      	it	ne
70000992:	ea95 0f0c 	teqne	r5, ip
70000996:	d00c      	beq.n	700009b2 <__aeabi_dmul+0x206>
70000998:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
7000099c:	bf18      	it	ne
7000099e:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
700009a2:	d1d1      	bne.n	70000948 <__aeabi_dmul+0x19c>
700009a4:	ea81 0103 	eor.w	r1, r1, r3
700009a8:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700009ac:	f04f 0000 	mov.w	r0, #0
700009b0:	bd70      	pop	{r4, r5, r6, pc}
700009b2:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
700009b6:	bf06      	itte	eq
700009b8:	4610      	moveq	r0, r2
700009ba:	4619      	moveq	r1, r3
700009bc:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
700009c0:	d019      	beq.n	700009f6 <__aeabi_dmul+0x24a>
700009c2:	ea94 0f0c 	teq	r4, ip
700009c6:	d102      	bne.n	700009ce <__aeabi_dmul+0x222>
700009c8:	ea50 3601 	orrs.w	r6, r0, r1, lsl #12
700009cc:	d113      	bne.n	700009f6 <__aeabi_dmul+0x24a>
700009ce:	ea95 0f0c 	teq	r5, ip
700009d2:	d105      	bne.n	700009e0 <__aeabi_dmul+0x234>
700009d4:	ea52 3603 	orrs.w	r6, r2, r3, lsl #12
700009d8:	bf1c      	itt	ne
700009da:	4610      	movne	r0, r2
700009dc:	4619      	movne	r1, r3
700009de:	d10a      	bne.n	700009f6 <__aeabi_dmul+0x24a>
700009e0:	ea81 0103 	eor.w	r1, r1, r3
700009e4:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700009e8:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
700009ec:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
700009f0:	f04f 0000 	mov.w	r0, #0
700009f4:	bd70      	pop	{r4, r5, r6, pc}
700009f6:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
700009fa:	f441 0178 	orr.w	r1, r1, #16252928	; 0xf80000
700009fe:	bd70      	pop	{r4, r5, r6, pc}
70000a00:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000a04:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000a08:	bf1e      	ittt	ne
70000a0a:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000a0e:	ea92 0f0c 	teqne	r2, ip
70000a12:	ea93 0f0c 	teqne	r3, ip
70000a16:	d06f      	beq.n	70000af8 <__aeabi_dmul+0x34c>
70000a18:	441a      	add	r2, r3
70000a1a:	ea80 0c01 	eor.w	ip, r0, r1
70000a1e:	0240      	lsls	r0, r0, #9
70000a20:	bf18      	it	ne
70000a22:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000a26:	d01e      	beq.n	70000a66 <__aeabi_dmul+0x2ba>
70000a28:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000a2c:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000a30:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000a34:	fba0 3101 	umull	r3, r1, r0, r1
70000a38:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000a3c:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000a40:	bf3e      	ittt	cc
70000a42:	0049      	lslcc	r1, r1, #1
70000a44:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000a48:	005b      	lslcc	r3, r3, #1
70000a4a:	ea40 0001 	orr.w	r0, r0, r1
70000a4e:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000a52:	2afd      	cmp	r2, #253	; 0xfd
70000a54:	d81d      	bhi.n	70000a92 <__aeabi_dmul+0x2e6>
70000a56:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000a5a:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000a5e:	bf08      	it	eq
70000a60:	f020 0001 	biceq.w	r0, r0, #1
70000a64:	4770      	bx	lr
70000a66:	f090 0f00 	teq	r0, #0
70000a6a:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000a6e:	bf08      	it	eq
70000a70:	0249      	lsleq	r1, r1, #9
70000a72:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000a76:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000a7a:	3a7f      	subs	r2, #127	; 0x7f
70000a7c:	bfc2      	ittt	gt
70000a7e:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000a82:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000a86:	4770      	bxgt	lr
70000a88:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000a8c:	f04f 0300 	mov.w	r3, #0
70000a90:	3a01      	subs	r2, #1
70000a92:	dc5d      	bgt.n	70000b50 <__aeabi_dmul+0x3a4>
70000a94:	f112 0f19 	cmn.w	r2, #25
70000a98:	bfdc      	itt	le
70000a9a:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000a9e:	4770      	bxle	lr
70000aa0:	f1c2 0200 	rsb	r2, r2, #0
70000aa4:	0041      	lsls	r1, r0, #1
70000aa6:	fa21 f102 	lsr.w	r1, r1, r2
70000aaa:	f1c2 0220 	rsb	r2, r2, #32
70000aae:	fa00 fc02 	lsl.w	ip, r0, r2
70000ab2:	ea5f 0031 	movs.w	r0, r1, rrx
70000ab6:	f140 0000 	adc.w	r0, r0, #0
70000aba:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000abe:	bf08      	it	eq
70000ac0:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000ac4:	4770      	bx	lr
70000ac6:	f092 0f00 	teq	r2, #0
70000aca:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000ace:	bf02      	ittt	eq
70000ad0:	0040      	lsleq	r0, r0, #1
70000ad2:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000ad6:	3a01      	subeq	r2, #1
70000ad8:	d0f9      	beq.n	70000ace <__aeabi_dmul+0x322>
70000ada:	ea40 000c 	orr.w	r0, r0, ip
70000ade:	f093 0f00 	teq	r3, #0
70000ae2:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000ae6:	bf02      	ittt	eq
70000ae8:	0049      	lsleq	r1, r1, #1
70000aea:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000aee:	3b01      	subeq	r3, #1
70000af0:	d0f9      	beq.n	70000ae6 <__aeabi_dmul+0x33a>
70000af2:	ea41 010c 	orr.w	r1, r1, ip
70000af6:	e78f      	b.n	70000a18 <__aeabi_dmul+0x26c>
70000af8:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000afc:	ea92 0f0c 	teq	r2, ip
70000b00:	bf18      	it	ne
70000b02:	ea93 0f0c 	teqne	r3, ip
70000b06:	d00a      	beq.n	70000b1e <__aeabi_dmul+0x372>
70000b08:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000b0c:	bf18      	it	ne
70000b0e:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000b12:	d1d8      	bne.n	70000ac6 <__aeabi_dmul+0x31a>
70000b14:	ea80 0001 	eor.w	r0, r0, r1
70000b18:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000b1c:	4770      	bx	lr
70000b1e:	f090 0f00 	teq	r0, #0
70000b22:	bf17      	itett	ne
70000b24:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000b28:	4608      	moveq	r0, r1
70000b2a:	f091 0f00 	teqne	r1, #0
70000b2e:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000b32:	d014      	beq.n	70000b5e <__aeabi_dmul+0x3b2>
70000b34:	ea92 0f0c 	teq	r2, ip
70000b38:	d101      	bne.n	70000b3e <__aeabi_dmul+0x392>
70000b3a:	0242      	lsls	r2, r0, #9
70000b3c:	d10f      	bne.n	70000b5e <__aeabi_dmul+0x3b2>
70000b3e:	ea93 0f0c 	teq	r3, ip
70000b42:	d103      	bne.n	70000b4c <__aeabi_dmul+0x3a0>
70000b44:	024b      	lsls	r3, r1, #9
70000b46:	bf18      	it	ne
70000b48:	4608      	movne	r0, r1
70000b4a:	d108      	bne.n	70000b5e <__aeabi_dmul+0x3b2>
70000b4c:	ea80 0001 	eor.w	r0, r0, r1
70000b50:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000b54:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000b58:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000b5c:	4770      	bx	lr
70000b5e:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000b62:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000b66:	4770      	bx	lr

70000b68 <__aeabi_drsub>:
70000b68:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000
70000b6c:	e002      	b.n	70000b74 <__adddf3>
70000b6e:	bf00      	nop

70000b70 <__aeabi_dsub>:
70000b70:	f083 4300 	eor.w	r3, r3, #2147483648	; 0x80000000

70000b74 <__adddf3>:
70000b74:	b530      	push	{r4, r5, lr}
70000b76:	ea4f 0441 	mov.w	r4, r1, lsl #1
70000b7a:	ea4f 0543 	mov.w	r5, r3, lsl #1
70000b7e:	ea94 0f05 	teq	r4, r5
70000b82:	bf08      	it	eq
70000b84:	ea90 0f02 	teqeq	r0, r2
70000b88:	bf1f      	itttt	ne
70000b8a:	ea54 0c00 	orrsne.w	ip, r4, r0
70000b8e:	ea55 0c02 	orrsne.w	ip, r5, r2
70000b92:	ea7f 5c64 	mvnsne.w	ip, r4, asr #21
70000b96:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70000b9a:	f000 80e2 	beq.w	70000d62 <__adddf3+0x1ee>
70000b9e:	ea4f 5454 	mov.w	r4, r4, lsr #21
70000ba2:	ebd4 5555 	rsbs	r5, r4, r5, lsr #21
70000ba6:	bfb8      	it	lt
70000ba8:	426d      	neglt	r5, r5
70000baa:	dd0c      	ble.n	70000bc6 <__adddf3+0x52>
70000bac:	442c      	add	r4, r5
70000bae:	ea80 0202 	eor.w	r2, r0, r2
70000bb2:	ea81 0303 	eor.w	r3, r1, r3
70000bb6:	ea82 0000 	eor.w	r0, r2, r0
70000bba:	ea83 0101 	eor.w	r1, r3, r1
70000bbe:	ea80 0202 	eor.w	r2, r0, r2
70000bc2:	ea81 0303 	eor.w	r3, r1, r3
70000bc6:	2d36      	cmp	r5, #54	; 0x36
70000bc8:	bf88      	it	hi
70000bca:	bd30      	pophi	{r4, r5, pc}
70000bcc:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000bd0:	ea4f 3101 	mov.w	r1, r1, lsl #12
70000bd4:	f44f 1c80 	mov.w	ip, #1048576	; 0x100000
70000bd8:	ea4c 3111 	orr.w	r1, ip, r1, lsr #12
70000bdc:	d002      	beq.n	70000be4 <__adddf3+0x70>
70000bde:	4240      	negs	r0, r0
70000be0:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000be4:	f013 4f00 	tst.w	r3, #2147483648	; 0x80000000
70000be8:	ea4f 3303 	mov.w	r3, r3, lsl #12
70000bec:	ea4c 3313 	orr.w	r3, ip, r3, lsr #12
70000bf0:	d002      	beq.n	70000bf8 <__adddf3+0x84>
70000bf2:	4252      	negs	r2, r2
70000bf4:	eb63 0343 	sbc.w	r3, r3, r3, lsl #1
70000bf8:	ea94 0f05 	teq	r4, r5
70000bfc:	f000 80a7 	beq.w	70000d4e <__adddf3+0x1da>
70000c00:	f1a4 0401 	sub.w	r4, r4, #1
70000c04:	f1d5 0e20 	rsbs	lr, r5, #32
70000c08:	db0d      	blt.n	70000c26 <__adddf3+0xb2>
70000c0a:	fa02 fc0e 	lsl.w	ip, r2, lr
70000c0e:	fa22 f205 	lsr.w	r2, r2, r5
70000c12:	1880      	adds	r0, r0, r2
70000c14:	f141 0100 	adc.w	r1, r1, #0
70000c18:	fa03 f20e 	lsl.w	r2, r3, lr
70000c1c:	1880      	adds	r0, r0, r2
70000c1e:	fa43 f305 	asr.w	r3, r3, r5
70000c22:	4159      	adcs	r1, r3
70000c24:	e00e      	b.n	70000c44 <__adddf3+0xd0>
70000c26:	f1a5 0520 	sub.w	r5, r5, #32
70000c2a:	f10e 0e20 	add.w	lr, lr, #32
70000c2e:	2a01      	cmp	r2, #1
70000c30:	fa03 fc0e 	lsl.w	ip, r3, lr
70000c34:	bf28      	it	cs
70000c36:	f04c 0c02 	orrcs.w	ip, ip, #2
70000c3a:	fa43 f305 	asr.w	r3, r3, r5
70000c3e:	18c0      	adds	r0, r0, r3
70000c40:	eb51 71e3 	adcs.w	r1, r1, r3, asr #31
70000c44:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000c48:	d507      	bpl.n	70000c5a <__adddf3+0xe6>
70000c4a:	f04f 0e00 	mov.w	lr, #0
70000c4e:	f1dc 0c00 	rsbs	ip, ip, #0
70000c52:	eb7e 0000 	sbcs.w	r0, lr, r0
70000c56:	eb6e 0101 	sbc.w	r1, lr, r1
70000c5a:	f5b1 1f80 	cmp.w	r1, #1048576	; 0x100000
70000c5e:	d31b      	bcc.n	70000c98 <__adddf3+0x124>
70000c60:	f5b1 1f00 	cmp.w	r1, #2097152	; 0x200000
70000c64:	d30c      	bcc.n	70000c80 <__adddf3+0x10c>
70000c66:	0849      	lsrs	r1, r1, #1
70000c68:	ea5f 0030 	movs.w	r0, r0, rrx
70000c6c:	ea4f 0c3c 	mov.w	ip, ip, rrx
70000c70:	f104 0401 	add.w	r4, r4, #1
70000c74:	ea4f 5244 	mov.w	r2, r4, lsl #21
70000c78:	f512 0f80 	cmn.w	r2, #4194304	; 0x400000
70000c7c:	f080 809a 	bcs.w	70000db4 <__adddf3+0x240>
70000c80:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000c84:	bf08      	it	eq
70000c86:	ea5f 0c50 	movseq.w	ip, r0, lsr #1
70000c8a:	f150 0000 	adcs.w	r0, r0, #0
70000c8e:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
70000c92:	ea41 0105 	orr.w	r1, r1, r5
70000c96:	bd30      	pop	{r4, r5, pc}
70000c98:	ea5f 0c4c 	movs.w	ip, ip, lsl #1
70000c9c:	4140      	adcs	r0, r0
70000c9e:	eb41 0101 	adc.w	r1, r1, r1
70000ca2:	3c01      	subs	r4, #1
70000ca4:	bf28      	it	cs
70000ca6:	f5b1 1f80 	cmpcs.w	r1, #1048576	; 0x100000
70000caa:	d2e9      	bcs.n	70000c80 <__adddf3+0x10c>
70000cac:	f091 0f00 	teq	r1, #0
70000cb0:	bf04      	itt	eq
70000cb2:	4601      	moveq	r1, r0
70000cb4:	2000      	moveq	r0, #0
70000cb6:	fab1 f381 	clz	r3, r1
70000cba:	bf08      	it	eq
70000cbc:	3320      	addeq	r3, #32
70000cbe:	f1a3 030b 	sub.w	r3, r3, #11
70000cc2:	f1b3 0220 	subs.w	r2, r3, #32
70000cc6:	da0c      	bge.n	70000ce2 <__adddf3+0x16e>
70000cc8:	320c      	adds	r2, #12
70000cca:	dd08      	ble.n	70000cde <__adddf3+0x16a>
70000ccc:	f102 0c14 	add.w	ip, r2, #20
70000cd0:	f1c2 020c 	rsb	r2, r2, #12
70000cd4:	fa01 f00c 	lsl.w	r0, r1, ip
70000cd8:	fa21 f102 	lsr.w	r1, r1, r2
70000cdc:	e00c      	b.n	70000cf8 <__adddf3+0x184>
70000cde:	f102 0214 	add.w	r2, r2, #20
70000ce2:	bfd8      	it	le
70000ce4:	f1c2 0c20 	rsble	ip, r2, #32
70000ce8:	fa01 f102 	lsl.w	r1, r1, r2
70000cec:	fa20 fc0c 	lsr.w	ip, r0, ip
70000cf0:	bfdc      	itt	le
70000cf2:	ea41 010c 	orrle.w	r1, r1, ip
70000cf6:	4090      	lslle	r0, r2
70000cf8:	1ae4      	subs	r4, r4, r3
70000cfa:	bfa2      	ittt	ge
70000cfc:	eb01 5104 	addge.w	r1, r1, r4, lsl #20
70000d00:	4329      	orrge	r1, r5
70000d02:	bd30      	popge	{r4, r5, pc}
70000d04:	ea6f 0404 	mvn.w	r4, r4
70000d08:	3c1f      	subs	r4, #31
70000d0a:	da1c      	bge.n	70000d46 <__adddf3+0x1d2>
70000d0c:	340c      	adds	r4, #12
70000d0e:	dc0e      	bgt.n	70000d2e <__adddf3+0x1ba>
70000d10:	f104 0414 	add.w	r4, r4, #20
70000d14:	f1c4 0220 	rsb	r2, r4, #32
70000d18:	fa20 f004 	lsr.w	r0, r0, r4
70000d1c:	fa01 f302 	lsl.w	r3, r1, r2
70000d20:	ea40 0003 	orr.w	r0, r0, r3
70000d24:	fa21 f304 	lsr.w	r3, r1, r4
70000d28:	ea45 0103 	orr.w	r1, r5, r3
70000d2c:	bd30      	pop	{r4, r5, pc}
70000d2e:	f1c4 040c 	rsb	r4, r4, #12
70000d32:	f1c4 0220 	rsb	r2, r4, #32
70000d36:	fa20 f002 	lsr.w	r0, r0, r2
70000d3a:	fa01 f304 	lsl.w	r3, r1, r4
70000d3e:	ea40 0003 	orr.w	r0, r0, r3
70000d42:	4629      	mov	r1, r5
70000d44:	bd30      	pop	{r4, r5, pc}
70000d46:	fa21 f004 	lsr.w	r0, r1, r4
70000d4a:	4629      	mov	r1, r5
70000d4c:	bd30      	pop	{r4, r5, pc}
70000d4e:	f094 0f00 	teq	r4, #0
70000d52:	f483 1380 	eor.w	r3, r3, #1048576	; 0x100000
70000d56:	bf06      	itte	eq
70000d58:	f481 1180 	eoreq.w	r1, r1, #1048576	; 0x100000
70000d5c:	3401      	addeq	r4, #1
70000d5e:	3d01      	subne	r5, #1
70000d60:	e74e      	b.n	70000c00 <__adddf3+0x8c>
70000d62:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70000d66:	bf18      	it	ne
70000d68:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70000d6c:	d029      	beq.n	70000dc2 <__adddf3+0x24e>
70000d6e:	ea94 0f05 	teq	r4, r5
70000d72:	bf08      	it	eq
70000d74:	ea90 0f02 	teqeq	r0, r2
70000d78:	d005      	beq.n	70000d86 <__adddf3+0x212>
70000d7a:	ea54 0c00 	orrs.w	ip, r4, r0
70000d7e:	bf04      	itt	eq
70000d80:	4619      	moveq	r1, r3
70000d82:	4610      	moveq	r0, r2
70000d84:	bd30      	pop	{r4, r5, pc}
70000d86:	ea91 0f03 	teq	r1, r3
70000d8a:	bf1e      	ittt	ne
70000d8c:	2100      	movne	r1, #0
70000d8e:	2000      	movne	r0, #0
70000d90:	bd30      	popne	{r4, r5, pc}
70000d92:	ea5f 5c54 	movs.w	ip, r4, lsr #21
70000d96:	d105      	bne.n	70000da4 <__adddf3+0x230>
70000d98:	0040      	lsls	r0, r0, #1
70000d9a:	4149      	adcs	r1, r1
70000d9c:	bf28      	it	cs
70000d9e:	f041 4100 	orrcs.w	r1, r1, #2147483648	; 0x80000000
70000da2:	bd30      	pop	{r4, r5, pc}
70000da4:	f514 0480 	adds.w	r4, r4, #4194304	; 0x400000
70000da8:	bf3c      	itt	cc
70000daa:	f501 1180 	addcc.w	r1, r1, #1048576	; 0x100000
70000dae:	bd30      	popcc	{r4, r5, pc}
70000db0:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000db4:	f045 41fe 	orr.w	r1, r5, #2130706432	; 0x7f000000
70000db8:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
70000dbc:	f04f 0000 	mov.w	r0, #0
70000dc0:	bd30      	pop	{r4, r5, pc}
70000dc2:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70000dc6:	bf1a      	itte	ne
70000dc8:	4619      	movne	r1, r3
70000dca:	4610      	movne	r0, r2
70000dcc:	ea7f 5c65 	mvnseq.w	ip, r5, asr #21
70000dd0:	bf1c      	itt	ne
70000dd2:	460b      	movne	r3, r1
70000dd4:	4602      	movne	r2, r0
70000dd6:	ea50 3401 	orrs.w	r4, r0, r1, lsl #12
70000dda:	bf06      	itte	eq
70000ddc:	ea52 3503 	orrseq.w	r5, r2, r3, lsl #12
70000de0:	ea91 0f03 	teqeq	r1, r3
70000de4:	f441 2100 	orrne.w	r1, r1, #524288	; 0x80000
70000de8:	bd30      	pop	{r4, r5, pc}
70000dea:	bf00      	nop

70000dec <__aeabi_ui2d>:
70000dec:	f090 0f00 	teq	r0, #0
70000df0:	bf04      	itt	eq
70000df2:	2100      	moveq	r1, #0
70000df4:	4770      	bxeq	lr
70000df6:	b530      	push	{r4, r5, lr}
70000df8:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000dfc:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000e00:	f04f 0500 	mov.w	r5, #0
70000e04:	f04f 0100 	mov.w	r1, #0
70000e08:	e750      	b.n	70000cac <__adddf3+0x138>
70000e0a:	bf00      	nop

70000e0c <__aeabi_i2d>:
70000e0c:	f090 0f00 	teq	r0, #0
70000e10:	bf04      	itt	eq
70000e12:	2100      	moveq	r1, #0
70000e14:	4770      	bxeq	lr
70000e16:	b530      	push	{r4, r5, lr}
70000e18:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000e1c:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000e20:	f010 4500 	ands.w	r5, r0, #2147483648	; 0x80000000
70000e24:	bf48      	it	mi
70000e26:	4240      	negmi	r0, r0
70000e28:	f04f 0100 	mov.w	r1, #0
70000e2c:	e73e      	b.n	70000cac <__adddf3+0x138>
70000e2e:	bf00      	nop

70000e30 <__aeabi_f2d>:
70000e30:	0042      	lsls	r2, r0, #1
70000e32:	ea4f 01e2 	mov.w	r1, r2, asr #3
70000e36:	ea4f 0131 	mov.w	r1, r1, rrx
70000e3a:	ea4f 7002 	mov.w	r0, r2, lsl #28
70000e3e:	bf1f      	itttt	ne
70000e40:	f012 437f 	andsne.w	r3, r2, #4278190080	; 0xff000000
70000e44:	f093 4f7f 	teqne	r3, #4278190080	; 0xff000000
70000e48:	f081 5160 	eorne.w	r1, r1, #939524096	; 0x38000000
70000e4c:	4770      	bxne	lr
70000e4e:	f032 427f 	bics.w	r2, r2, #4278190080	; 0xff000000
70000e52:	bf08      	it	eq
70000e54:	4770      	bxeq	lr
70000e56:	f093 4f7f 	teq	r3, #4278190080	; 0xff000000
70000e5a:	bf04      	itt	eq
70000e5c:	f441 2100 	orreq.w	r1, r1, #524288	; 0x80000
70000e60:	4770      	bxeq	lr
70000e62:	b530      	push	{r4, r5, lr}
70000e64:	f44f 7460 	mov.w	r4, #896	; 0x380
70000e68:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000e6c:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
70000e70:	e71c      	b.n	70000cac <__adddf3+0x138>
70000e72:	bf00      	nop

70000e74 <__aeabi_ul2d>:
70000e74:	ea50 0201 	orrs.w	r2, r0, r1
70000e78:	bf08      	it	eq
70000e7a:	4770      	bxeq	lr
70000e7c:	b530      	push	{r4, r5, lr}
70000e7e:	f04f 0500 	mov.w	r5, #0
70000e82:	e00a      	b.n	70000e9a <__aeabi_l2d+0x16>

70000e84 <__aeabi_l2d>:
70000e84:	ea50 0201 	orrs.w	r2, r0, r1
70000e88:	bf08      	it	eq
70000e8a:	4770      	bxeq	lr
70000e8c:	b530      	push	{r4, r5, lr}
70000e8e:	f011 4500 	ands.w	r5, r1, #2147483648	; 0x80000000
70000e92:	d502      	bpl.n	70000e9a <__aeabi_l2d+0x16>
70000e94:	4240      	negs	r0, r0
70000e96:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000e9a:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000e9e:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000ea2:	ea5f 5c91 	movs.w	ip, r1, lsr #22
70000ea6:	f43f aed8 	beq.w	70000c5a <__adddf3+0xe6>
70000eaa:	f04f 0203 	mov.w	r2, #3
70000eae:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70000eb2:	bf18      	it	ne
70000eb4:	3203      	addne	r2, #3
70000eb6:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70000eba:	bf18      	it	ne
70000ebc:	3203      	addne	r2, #3
70000ebe:	eb02 02dc 	add.w	r2, r2, ip, lsr #3
70000ec2:	f1c2 0320 	rsb	r3, r2, #32
70000ec6:	fa00 fc03 	lsl.w	ip, r0, r3
70000eca:	fa20 f002 	lsr.w	r0, r0, r2
70000ece:	fa01 fe03 	lsl.w	lr, r1, r3
70000ed2:	ea40 000e 	orr.w	r0, r0, lr
70000ed6:	fa21 f102 	lsr.w	r1, r1, r2
70000eda:	4414      	add	r4, r2
70000edc:	e6bd      	b.n	70000c5a <__adddf3+0xe6>
70000ede:	bf00      	nop

70000ee0 <__aeabi_d2iz>:
70000ee0:	ea4f 0241 	mov.w	r2, r1, lsl #1
70000ee4:	f512 1200 	adds.w	r2, r2, #2097152	; 0x200000
70000ee8:	d215      	bcs.n	70000f16 <__aeabi_d2iz+0x36>
70000eea:	d511      	bpl.n	70000f10 <__aeabi_d2iz+0x30>
70000eec:	f46f 7378 	mvn.w	r3, #992	; 0x3e0
70000ef0:	ebb3 5262 	subs.w	r2, r3, r2, asr #21
70000ef4:	d912      	bls.n	70000f1c <__aeabi_d2iz+0x3c>
70000ef6:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70000efa:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000efe:	ea43 5350 	orr.w	r3, r3, r0, lsr #21
70000f02:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000f06:	fa23 f002 	lsr.w	r0, r3, r2
70000f0a:	bf18      	it	ne
70000f0c:	4240      	negne	r0, r0
70000f0e:	4770      	bx	lr
70000f10:	f04f 0000 	mov.w	r0, #0
70000f14:	4770      	bx	lr
70000f16:	ea50 3001 	orrs.w	r0, r0, r1, lsl #12
70000f1a:	d105      	bne.n	70000f28 <__aeabi_d2iz+0x48>
70000f1c:	f011 4000 	ands.w	r0, r1, #2147483648	; 0x80000000
70000f20:	bf08      	it	eq
70000f22:	f06f 4000 	mvneq.w	r0, #2147483648	; 0x80000000
70000f26:	4770      	bx	lr
70000f28:	f04f 0000 	mov.w	r0, #0
70000f2c:	4770      	bx	lr
70000f2e:	bf00      	nop

70000f30 <__aeabi_d2f>:
70000f30:	ea4f 0241 	mov.w	r2, r1, lsl #1
70000f34:	f1b2 43e0 	subs.w	r3, r2, #1879048192	; 0x70000000
70000f38:	bf24      	itt	cs
70000f3a:	f5b3 1c00 	subscs.w	ip, r3, #2097152	; 0x200000
70000f3e:	f1dc 5cfe 	rsbscs	ip, ip, #532676608	; 0x1fc00000
70000f42:	d90d      	bls.n	70000f60 <__aeabi_d2f+0x30>
70000f44:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000f48:	ea4f 02c0 	mov.w	r2, r0, lsl #3
70000f4c:	ea4c 7050 	orr.w	r0, ip, r0, lsr #29
70000f50:	f1b2 4f00 	cmp.w	r2, #2147483648	; 0x80000000
70000f54:	eb40 0083 	adc.w	r0, r0, r3, lsl #2
70000f58:	bf08      	it	eq
70000f5a:	f020 0001 	biceq.w	r0, r0, #1
70000f5e:	4770      	bx	lr
70000f60:	f011 4f80 	tst.w	r1, #1073741824	; 0x40000000
70000f64:	d121      	bne.n	70000faa <__aeabi_d2f+0x7a>
70000f66:	f113 7238 	adds.w	r2, r3, #48234496	; 0x2e00000
70000f6a:	bfbc      	itt	lt
70000f6c:	f001 4000 	andlt.w	r0, r1, #2147483648	; 0x80000000
70000f70:	4770      	bxlt	lr
70000f72:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70000f76:	ea4f 5252 	mov.w	r2, r2, lsr #21
70000f7a:	f1c2 0218 	rsb	r2, r2, #24
70000f7e:	f1c2 0c20 	rsb	ip, r2, #32
70000f82:	fa10 f30c 	lsls.w	r3, r0, ip
70000f86:	fa20 f002 	lsr.w	r0, r0, r2
70000f8a:	bf18      	it	ne
70000f8c:	f040 0001 	orrne.w	r0, r0, #1
70000f90:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70000f94:	ea4f 23d3 	mov.w	r3, r3, lsr #11
70000f98:	fa03 fc0c 	lsl.w	ip, r3, ip
70000f9c:	ea40 000c 	orr.w	r0, r0, ip
70000fa0:	fa23 f302 	lsr.w	r3, r3, r2
70000fa4:	ea4f 0343 	mov.w	r3, r3, lsl #1
70000fa8:	e7cc      	b.n	70000f44 <__aeabi_d2f+0x14>
70000faa:	ea7f 5362 	mvns.w	r3, r2, asr #21
70000fae:	d107      	bne.n	70000fc0 <__aeabi_d2f+0x90>
70000fb0:	ea50 3301 	orrs.w	r3, r0, r1, lsl #12
70000fb4:	bf1e      	ittt	ne
70000fb6:	f04f 40fe 	movne.w	r0, #2130706432	; 0x7f000000
70000fba:	f440 0040 	orrne.w	r0, r0, #12582912	; 0xc00000
70000fbe:	4770      	bxne	lr
70000fc0:	f001 4000 	and.w	r0, r1, #2147483648	; 0x80000000
70000fc4:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000fc8:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000fcc:	4770      	bx	lr
70000fce:	bf00      	nop

70000fd0 <__aeabi_frsub>:
70000fd0:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70000fd4:	e002      	b.n	70000fdc <__addsf3>
70000fd6:	bf00      	nop

70000fd8 <__aeabi_fsub>:
70000fd8:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

70000fdc <__addsf3>:
70000fdc:	0042      	lsls	r2, r0, #1
70000fde:	bf1f      	itttt	ne
70000fe0:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70000fe4:	ea92 0f03 	teqne	r2, r3
70000fe8:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
70000fec:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000ff0:	d06a      	beq.n	700010c8 <__addsf3+0xec>
70000ff2:	ea4f 6212 	mov.w	r2, r2, lsr #24
70000ff6:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
70000ffa:	bfc1      	itttt	gt
70000ffc:	18d2      	addgt	r2, r2, r3
70000ffe:	4041      	eorgt	r1, r0
70001000:	4048      	eorgt	r0, r1
70001002:	4041      	eorgt	r1, r0
70001004:	bfb8      	it	lt
70001006:	425b      	neglt	r3, r3
70001008:	2b19      	cmp	r3, #25
7000100a:	bf88      	it	hi
7000100c:	4770      	bxhi	lr
7000100e:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
70001012:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001016:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
7000101a:	bf18      	it	ne
7000101c:	4240      	negne	r0, r0
7000101e:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70001022:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
70001026:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
7000102a:	bf18      	it	ne
7000102c:	4249      	negne	r1, r1
7000102e:	ea92 0f03 	teq	r2, r3
70001032:	d03f      	beq.n	700010b4 <__addsf3+0xd8>
70001034:	f1a2 0201 	sub.w	r2, r2, #1
70001038:	fa41 fc03 	asr.w	ip, r1, r3
7000103c:	eb10 000c 	adds.w	r0, r0, ip
70001040:	f1c3 0320 	rsb	r3, r3, #32
70001044:	fa01 f103 	lsl.w	r1, r1, r3
70001048:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
7000104c:	d502      	bpl.n	70001054 <__addsf3+0x78>
7000104e:	4249      	negs	r1, r1
70001050:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70001054:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70001058:	d313      	bcc.n	70001082 <__addsf3+0xa6>
7000105a:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
7000105e:	d306      	bcc.n	7000106e <__addsf3+0x92>
70001060:	0840      	lsrs	r0, r0, #1
70001062:	ea4f 0131 	mov.w	r1, r1, rrx
70001066:	f102 0201 	add.w	r2, r2, #1
7000106a:	2afe      	cmp	r2, #254	; 0xfe
7000106c:	d251      	bcs.n	70001112 <__addsf3+0x136>
7000106e:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
70001072:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70001076:	bf08      	it	eq
70001078:	f020 0001 	biceq.w	r0, r0, #1
7000107c:	ea40 0003 	orr.w	r0, r0, r3
70001080:	4770      	bx	lr
70001082:	0049      	lsls	r1, r1, #1
70001084:	eb40 0000 	adc.w	r0, r0, r0
70001088:	3a01      	subs	r2, #1
7000108a:	bf28      	it	cs
7000108c:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70001090:	d2ed      	bcs.n	7000106e <__addsf3+0x92>
70001092:	fab0 fc80 	clz	ip, r0
70001096:	f1ac 0c08 	sub.w	ip, ip, #8
7000109a:	ebb2 020c 	subs.w	r2, r2, ip
7000109e:	fa00 f00c 	lsl.w	r0, r0, ip
700010a2:	bfaa      	itet	ge
700010a4:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
700010a8:	4252      	neglt	r2, r2
700010aa:	4318      	orrge	r0, r3
700010ac:	bfbc      	itt	lt
700010ae:	40d0      	lsrlt	r0, r2
700010b0:	4318      	orrlt	r0, r3
700010b2:	4770      	bx	lr
700010b4:	f092 0f00 	teq	r2, #0
700010b8:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
700010bc:	bf06      	itte	eq
700010be:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
700010c2:	3201      	addeq	r2, #1
700010c4:	3b01      	subne	r3, #1
700010c6:	e7b5      	b.n	70001034 <__addsf3+0x58>
700010c8:	ea4f 0341 	mov.w	r3, r1, lsl #1
700010cc:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700010d0:	bf18      	it	ne
700010d2:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700010d6:	d021      	beq.n	7000111c <__addsf3+0x140>
700010d8:	ea92 0f03 	teq	r2, r3
700010dc:	d004      	beq.n	700010e8 <__addsf3+0x10c>
700010de:	f092 0f00 	teq	r2, #0
700010e2:	bf08      	it	eq
700010e4:	4608      	moveq	r0, r1
700010e6:	4770      	bx	lr
700010e8:	ea90 0f01 	teq	r0, r1
700010ec:	bf1c      	itt	ne
700010ee:	2000      	movne	r0, #0
700010f0:	4770      	bxne	lr
700010f2:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
700010f6:	d104      	bne.n	70001102 <__addsf3+0x126>
700010f8:	0040      	lsls	r0, r0, #1
700010fa:	bf28      	it	cs
700010fc:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
70001100:	4770      	bx	lr
70001102:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
70001106:	bf3c      	itt	cc
70001108:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
7000110c:	4770      	bxcc	lr
7000110e:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70001112:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
70001116:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
7000111a:	4770      	bx	lr
7000111c:	ea7f 6222 	mvns.w	r2, r2, asr #24
70001120:	bf16      	itet	ne
70001122:	4608      	movne	r0, r1
70001124:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70001128:	4601      	movne	r1, r0
7000112a:	0242      	lsls	r2, r0, #9
7000112c:	bf06      	itte	eq
7000112e:	ea5f 2341 	movseq.w	r3, r1, lsl #9
70001132:	ea90 0f01 	teqeq	r0, r1
70001136:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
7000113a:	4770      	bx	lr

7000113c <__aeabi_ui2f>:
7000113c:	f04f 0300 	mov.w	r3, #0
70001140:	e004      	b.n	7000114c <__aeabi_i2f+0x8>
70001142:	bf00      	nop

70001144 <__aeabi_i2f>:
70001144:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70001148:	bf48      	it	mi
7000114a:	4240      	negmi	r0, r0
7000114c:	ea5f 0c00 	movs.w	ip, r0
70001150:	bf08      	it	eq
70001152:	4770      	bxeq	lr
70001154:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70001158:	4601      	mov	r1, r0
7000115a:	f04f 0000 	mov.w	r0, #0
7000115e:	e01c      	b.n	7000119a <__aeabi_l2f+0x2a>

70001160 <__aeabi_ul2f>:
70001160:	ea50 0201 	orrs.w	r2, r0, r1
70001164:	bf08      	it	eq
70001166:	4770      	bxeq	lr
70001168:	f04f 0300 	mov.w	r3, #0
7000116c:	e00a      	b.n	70001184 <__aeabi_l2f+0x14>
7000116e:	bf00      	nop

70001170 <__aeabi_l2f>:
70001170:	ea50 0201 	orrs.w	r2, r0, r1
70001174:	bf08      	it	eq
70001176:	4770      	bxeq	lr
70001178:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
7000117c:	d502      	bpl.n	70001184 <__aeabi_l2f+0x14>
7000117e:	4240      	negs	r0, r0
70001180:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70001184:	ea5f 0c01 	movs.w	ip, r1
70001188:	bf02      	ittt	eq
7000118a:	4684      	moveq	ip, r0
7000118c:	4601      	moveq	r1, r0
7000118e:	2000      	moveq	r0, #0
70001190:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70001194:	bf08      	it	eq
70001196:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
7000119a:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
7000119e:	fabc f28c 	clz	r2, ip
700011a2:	3a08      	subs	r2, #8
700011a4:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
700011a8:	db10      	blt.n	700011cc <__aeabi_l2f+0x5c>
700011aa:	fa01 fc02 	lsl.w	ip, r1, r2
700011ae:	4463      	add	r3, ip
700011b0:	fa00 fc02 	lsl.w	ip, r0, r2
700011b4:	f1c2 0220 	rsb	r2, r2, #32
700011b8:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
700011bc:	fa20 f202 	lsr.w	r2, r0, r2
700011c0:	eb43 0002 	adc.w	r0, r3, r2
700011c4:	bf08      	it	eq
700011c6:	f020 0001 	biceq.w	r0, r0, #1
700011ca:	4770      	bx	lr
700011cc:	f102 0220 	add.w	r2, r2, #32
700011d0:	fa01 fc02 	lsl.w	ip, r1, r2
700011d4:	f1c2 0220 	rsb	r2, r2, #32
700011d8:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
700011dc:	fa21 f202 	lsr.w	r2, r1, r2
700011e0:	eb43 0002 	adc.w	r0, r3, r2
700011e4:	bf08      	it	eq
700011e6:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
700011ea:	4770      	bx	lr

700011ec <__aeabi_fmul>:
700011ec:	f04f 0cff 	mov.w	ip, #255	; 0xff
700011f0:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
700011f4:	bf1e      	ittt	ne
700011f6:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
700011fa:	ea92 0f0c 	teqne	r2, ip
700011fe:	ea93 0f0c 	teqne	r3, ip
70001202:	d06f      	beq.n	700012e4 <__aeabi_fmul+0xf8>
70001204:	441a      	add	r2, r3
70001206:	ea80 0c01 	eor.w	ip, r0, r1
7000120a:	0240      	lsls	r0, r0, #9
7000120c:	bf18      	it	ne
7000120e:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70001212:	d01e      	beq.n	70001252 <__aeabi_fmul+0x66>
70001214:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70001218:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
7000121c:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70001220:	fba0 3101 	umull	r3, r1, r0, r1
70001224:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70001228:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
7000122c:	bf3e      	ittt	cc
7000122e:	0049      	lslcc	r1, r1, #1
70001230:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70001234:	005b      	lslcc	r3, r3, #1
70001236:	ea40 0001 	orr.w	r0, r0, r1
7000123a:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
7000123e:	2afd      	cmp	r2, #253	; 0xfd
70001240:	d81d      	bhi.n	7000127e <__aeabi_fmul+0x92>
70001242:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70001246:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
7000124a:	bf08      	it	eq
7000124c:	f020 0001 	biceq.w	r0, r0, #1
70001250:	4770      	bx	lr
70001252:	f090 0f00 	teq	r0, #0
70001256:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
7000125a:	bf08      	it	eq
7000125c:	0249      	lsleq	r1, r1, #9
7000125e:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70001262:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70001266:	3a7f      	subs	r2, #127	; 0x7f
70001268:	bfc2      	ittt	gt
7000126a:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
7000126e:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70001272:	4770      	bxgt	lr
70001274:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001278:	f04f 0300 	mov.w	r3, #0
7000127c:	3a01      	subs	r2, #1
7000127e:	dc5d      	bgt.n	7000133c <__aeabi_fmul+0x150>
70001280:	f112 0f19 	cmn.w	r2, #25
70001284:	bfdc      	itt	le
70001286:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
7000128a:	4770      	bxle	lr
7000128c:	f1c2 0200 	rsb	r2, r2, #0
70001290:	0041      	lsls	r1, r0, #1
70001292:	fa21 f102 	lsr.w	r1, r1, r2
70001296:	f1c2 0220 	rsb	r2, r2, #32
7000129a:	fa00 fc02 	lsl.w	ip, r0, r2
7000129e:	ea5f 0031 	movs.w	r0, r1, rrx
700012a2:	f140 0000 	adc.w	r0, r0, #0
700012a6:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
700012aa:	bf08      	it	eq
700012ac:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
700012b0:	4770      	bx	lr
700012b2:	f092 0f00 	teq	r2, #0
700012b6:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
700012ba:	bf02      	ittt	eq
700012bc:	0040      	lsleq	r0, r0, #1
700012be:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
700012c2:	3a01      	subeq	r2, #1
700012c4:	d0f9      	beq.n	700012ba <__aeabi_fmul+0xce>
700012c6:	ea40 000c 	orr.w	r0, r0, ip
700012ca:	f093 0f00 	teq	r3, #0
700012ce:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
700012d2:	bf02      	ittt	eq
700012d4:	0049      	lsleq	r1, r1, #1
700012d6:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
700012da:	3b01      	subeq	r3, #1
700012dc:	d0f9      	beq.n	700012d2 <__aeabi_fmul+0xe6>
700012de:	ea41 010c 	orr.w	r1, r1, ip
700012e2:	e78f      	b.n	70001204 <__aeabi_fmul+0x18>
700012e4:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
700012e8:	ea92 0f0c 	teq	r2, ip
700012ec:	bf18      	it	ne
700012ee:	ea93 0f0c 	teqne	r3, ip
700012f2:	d00a      	beq.n	7000130a <__aeabi_fmul+0x11e>
700012f4:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
700012f8:	bf18      	it	ne
700012fa:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
700012fe:	d1d8      	bne.n	700012b2 <__aeabi_fmul+0xc6>
70001300:	ea80 0001 	eor.w	r0, r0, r1
70001304:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70001308:	4770      	bx	lr
7000130a:	f090 0f00 	teq	r0, #0
7000130e:	bf17      	itett	ne
70001310:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70001314:	4608      	moveq	r0, r1
70001316:	f091 0f00 	teqne	r1, #0
7000131a:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
7000131e:	d014      	beq.n	7000134a <__aeabi_fmul+0x15e>
70001320:	ea92 0f0c 	teq	r2, ip
70001324:	d101      	bne.n	7000132a <__aeabi_fmul+0x13e>
70001326:	0242      	lsls	r2, r0, #9
70001328:	d10f      	bne.n	7000134a <__aeabi_fmul+0x15e>
7000132a:	ea93 0f0c 	teq	r3, ip
7000132e:	d103      	bne.n	70001338 <__aeabi_fmul+0x14c>
70001330:	024b      	lsls	r3, r1, #9
70001332:	bf18      	it	ne
70001334:	4608      	movne	r0, r1
70001336:	d108      	bne.n	7000134a <__aeabi_fmul+0x15e>
70001338:	ea80 0001 	eor.w	r0, r0, r1
7000133c:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70001340:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70001344:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001348:	4770      	bx	lr
7000134a:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
7000134e:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70001352:	4770      	bx	lr

70001354 <__aeabi_fdiv>:
70001354:	f04f 0cff 	mov.w	ip, #255	; 0xff
70001358:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
7000135c:	bf1e      	ittt	ne
7000135e:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70001362:	ea92 0f0c 	teqne	r2, ip
70001366:	ea93 0f0c 	teqne	r3, ip
7000136a:	d069      	beq.n	70001440 <__aeabi_fdiv+0xec>
7000136c:	eba2 0203 	sub.w	r2, r2, r3
70001370:	ea80 0c01 	eor.w	ip, r0, r1
70001374:	0249      	lsls	r1, r1, #9
70001376:	ea4f 2040 	mov.w	r0, r0, lsl #9
7000137a:	d037      	beq.n	700013ec <__aeabi_fdiv+0x98>
7000137c:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70001380:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70001384:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70001388:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
7000138c:	428b      	cmp	r3, r1
7000138e:	bf38      	it	cc
70001390:	005b      	lslcc	r3, r3, #1
70001392:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70001396:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
7000139a:	428b      	cmp	r3, r1
7000139c:	bf24      	itt	cs
7000139e:	1a5b      	subcs	r3, r3, r1
700013a0:	ea40 000c 	orrcs.w	r0, r0, ip
700013a4:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
700013a8:	bf24      	itt	cs
700013aa:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
700013ae:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
700013b2:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
700013b6:	bf24      	itt	cs
700013b8:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
700013bc:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
700013c0:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
700013c4:	bf24      	itt	cs
700013c6:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
700013ca:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
700013ce:	011b      	lsls	r3, r3, #4
700013d0:	bf18      	it	ne
700013d2:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
700013d6:	d1e0      	bne.n	7000139a <__aeabi_fdiv+0x46>
700013d8:	2afd      	cmp	r2, #253	; 0xfd
700013da:	f63f af50 	bhi.w	7000127e <__aeabi_fmul+0x92>
700013de:	428b      	cmp	r3, r1
700013e0:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
700013e4:	bf08      	it	eq
700013e6:	f020 0001 	biceq.w	r0, r0, #1
700013ea:	4770      	bx	lr
700013ec:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
700013f0:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
700013f4:	327f      	adds	r2, #127	; 0x7f
700013f6:	bfc2      	ittt	gt
700013f8:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
700013fc:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70001400:	4770      	bxgt	lr
70001402:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001406:	f04f 0300 	mov.w	r3, #0
7000140a:	3a01      	subs	r2, #1
7000140c:	e737      	b.n	7000127e <__aeabi_fmul+0x92>
7000140e:	f092 0f00 	teq	r2, #0
70001412:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70001416:	bf02      	ittt	eq
70001418:	0040      	lsleq	r0, r0, #1
7000141a:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
7000141e:	3a01      	subeq	r2, #1
70001420:	d0f9      	beq.n	70001416 <__aeabi_fdiv+0xc2>
70001422:	ea40 000c 	orr.w	r0, r0, ip
70001426:	f093 0f00 	teq	r3, #0
7000142a:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
7000142e:	bf02      	ittt	eq
70001430:	0049      	lsleq	r1, r1, #1
70001432:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70001436:	3b01      	subeq	r3, #1
70001438:	d0f9      	beq.n	7000142e <__aeabi_fdiv+0xda>
7000143a:	ea41 010c 	orr.w	r1, r1, ip
7000143e:	e795      	b.n	7000136c <__aeabi_fdiv+0x18>
70001440:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70001444:	ea92 0f0c 	teq	r2, ip
70001448:	d108      	bne.n	7000145c <__aeabi_fdiv+0x108>
7000144a:	0242      	lsls	r2, r0, #9
7000144c:	f47f af7d 	bne.w	7000134a <__aeabi_fmul+0x15e>
70001450:	ea93 0f0c 	teq	r3, ip
70001454:	f47f af70 	bne.w	70001338 <__aeabi_fmul+0x14c>
70001458:	4608      	mov	r0, r1
7000145a:	e776      	b.n	7000134a <__aeabi_fmul+0x15e>
7000145c:	ea93 0f0c 	teq	r3, ip
70001460:	d104      	bne.n	7000146c <__aeabi_fdiv+0x118>
70001462:	024b      	lsls	r3, r1, #9
70001464:	f43f af4c 	beq.w	70001300 <__aeabi_fmul+0x114>
70001468:	4608      	mov	r0, r1
7000146a:	e76e      	b.n	7000134a <__aeabi_fmul+0x15e>
7000146c:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70001470:	bf18      	it	ne
70001472:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70001476:	d1ca      	bne.n	7000140e <__aeabi_fdiv+0xba>
70001478:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
7000147c:	f47f af5c 	bne.w	70001338 <__aeabi_fmul+0x14c>
70001480:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70001484:	f47f af3c 	bne.w	70001300 <__aeabi_fmul+0x114>
70001488:	e75f      	b.n	7000134a <__aeabi_fmul+0x15e>
7000148a:	bf00      	nop

7000148c <__gesf2>:
7000148c:	f04f 3cff 	mov.w	ip, #4294967295
70001490:	e006      	b.n	700014a0 <__cmpsf2+0x4>
70001492:	bf00      	nop

70001494 <__lesf2>:
70001494:	f04f 0c01 	mov.w	ip, #1
70001498:	e002      	b.n	700014a0 <__cmpsf2+0x4>
7000149a:	bf00      	nop

7000149c <__cmpsf2>:
7000149c:	f04f 0c01 	mov.w	ip, #1
700014a0:	f84d cd04 	str.w	ip, [sp, #-4]!
700014a4:	ea4f 0240 	mov.w	r2, r0, lsl #1
700014a8:	ea4f 0341 	mov.w	r3, r1, lsl #1
700014ac:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700014b0:	bf18      	it	ne
700014b2:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700014b6:	d011      	beq.n	700014dc <__cmpsf2+0x40>
700014b8:	b001      	add	sp, #4
700014ba:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
700014be:	bf18      	it	ne
700014c0:	ea90 0f01 	teqne	r0, r1
700014c4:	bf58      	it	pl
700014c6:	ebb2 0003 	subspl.w	r0, r2, r3
700014ca:	bf88      	it	hi
700014cc:	17c8      	asrhi	r0, r1, #31
700014ce:	bf38      	it	cc
700014d0:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
700014d4:	bf18      	it	ne
700014d6:	f040 0001 	orrne.w	r0, r0, #1
700014da:	4770      	bx	lr
700014dc:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700014e0:	d102      	bne.n	700014e8 <__cmpsf2+0x4c>
700014e2:	ea5f 2c40 	movs.w	ip, r0, lsl #9
700014e6:	d105      	bne.n	700014f4 <__cmpsf2+0x58>
700014e8:	ea7f 6c23 	mvns.w	ip, r3, asr #24
700014ec:	d1e4      	bne.n	700014b8 <__cmpsf2+0x1c>
700014ee:	ea5f 2c41 	movs.w	ip, r1, lsl #9
700014f2:	d0e1      	beq.n	700014b8 <__cmpsf2+0x1c>
700014f4:	f85d 0b04 	ldr.w	r0, [sp], #4
700014f8:	4770      	bx	lr
700014fa:	bf00      	nop

700014fc <__aeabi_cfrcmple>:
700014fc:	4684      	mov	ip, r0
700014fe:	4608      	mov	r0, r1
70001500:	4661      	mov	r1, ip
70001502:	e7ff      	b.n	70001504 <__aeabi_cfcmpeq>

70001504 <__aeabi_cfcmpeq>:
70001504:	b50f      	push	{r0, r1, r2, r3, lr}
70001506:	f7ff ffc9 	bl	7000149c <__cmpsf2>
7000150a:	2800      	cmp	r0, #0
7000150c:	bf48      	it	mi
7000150e:	f110 0f00 	cmnmi.w	r0, #0
70001512:	bd0f      	pop	{r0, r1, r2, r3, pc}

70001514 <__aeabi_fcmpeq>:
70001514:	f84d ed08 	str.w	lr, [sp, #-8]!
70001518:	f7ff fff4 	bl	70001504 <__aeabi_cfcmpeq>
7000151c:	bf0c      	ite	eq
7000151e:	2001      	moveq	r0, #1
70001520:	2000      	movne	r0, #0
70001522:	f85d fb08 	ldr.w	pc, [sp], #8
70001526:	bf00      	nop

70001528 <__aeabi_fcmplt>:
70001528:	f84d ed08 	str.w	lr, [sp, #-8]!
7000152c:	f7ff ffea 	bl	70001504 <__aeabi_cfcmpeq>
70001530:	bf34      	ite	cc
70001532:	2001      	movcc	r0, #1
70001534:	2000      	movcs	r0, #0
70001536:	f85d fb08 	ldr.w	pc, [sp], #8
7000153a:	bf00      	nop

7000153c <__aeabi_fcmple>:
7000153c:	f84d ed08 	str.w	lr, [sp, #-8]!
70001540:	f7ff ffe0 	bl	70001504 <__aeabi_cfcmpeq>
70001544:	bf94      	ite	ls
70001546:	2001      	movls	r0, #1
70001548:	2000      	movhi	r0, #0
7000154a:	f85d fb08 	ldr.w	pc, [sp], #8
7000154e:	bf00      	nop

70001550 <__aeabi_fcmpge>:
70001550:	f84d ed08 	str.w	lr, [sp, #-8]!
70001554:	f7ff ffd2 	bl	700014fc <__aeabi_cfrcmple>
70001558:	bf94      	ite	ls
7000155a:	2001      	movls	r0, #1
7000155c:	2000      	movhi	r0, #0
7000155e:	f85d fb08 	ldr.w	pc, [sp], #8
70001562:	bf00      	nop

70001564 <__aeabi_fcmpgt>:
70001564:	f84d ed08 	str.w	lr, [sp, #-8]!
70001568:	f7ff ffc8 	bl	700014fc <__aeabi_cfrcmple>
7000156c:	bf34      	ite	cc
7000156e:	2001      	movcc	r0, #1
70001570:	2000      	movcs	r0, #0
70001572:	f85d fb08 	ldr.w	pc, [sp], #8
70001576:	bf00      	nop

70001578 <__aeabi_f2uiz>:
70001578:	0042      	lsls	r2, r0, #1
7000157a:	d20e      	bcs.n	7000159a <__aeabi_f2uiz+0x22>
7000157c:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70001580:	d30b      	bcc.n	7000159a <__aeabi_f2uiz+0x22>
70001582:	f04f 039e 	mov.w	r3, #158	; 0x9e
70001586:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
7000158a:	d409      	bmi.n	700015a0 <__aeabi_f2uiz+0x28>
7000158c:	ea4f 2300 	mov.w	r3, r0, lsl #8
70001590:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70001594:	fa23 f002 	lsr.w	r0, r3, r2
70001598:	4770      	bx	lr
7000159a:	f04f 0000 	mov.w	r0, #0
7000159e:	4770      	bx	lr
700015a0:	f112 0f61 	cmn.w	r2, #97	; 0x61
700015a4:	d101      	bne.n	700015aa <__aeabi_f2uiz+0x32>
700015a6:	0242      	lsls	r2, r0, #9
700015a8:	d102      	bne.n	700015b0 <__aeabi_f2uiz+0x38>
700015aa:	f04f 30ff 	mov.w	r0, #4294967295
700015ae:	4770      	bx	lr
700015b0:	f04f 0000 	mov.w	r0, #0
700015b4:	4770      	bx	lr
700015b6:	bf00      	nop
