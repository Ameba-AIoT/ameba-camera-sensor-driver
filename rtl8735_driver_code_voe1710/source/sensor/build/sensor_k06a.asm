
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	3d 07 00 70 49 02 00 70                             =..pI..p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

70000070 <g_k06a_i2c_init_regs_asic>:
70000070:	12 00 70 00 48 00 86 00 48 00 06 00 0e 00 11 00     ..p.H...H.......
70000080:	0f 00 04 00 10 00 48 00 11 00 80 00 46 00 08 00     ......H.....F...
70000090:	7f 00 5e 00 0d 00 a0 00 57 00 67 00 58 00 1f 00     ..^.....W.g.X...
700000a0:	5f 00 41 00 60 00 20 00 20 00 c0 00 21 00 03 00     _.A.`. . ...!...
700000b0:	22 00 dc 00 23 00 05 00 24 00 82 00 25 00 a8 00     "...#...$...%...
700000c0:	26 00 52 00 27 00 bb 00 28 00 15 00 29 00 03 00     &.R.'...(...)...
700000d0:	2a 00 b6 00 2b 00 13 00 2c 00 00 00 2d 00 00 00     *...+...,...-...
700000e0:	2e 00 6f 00 2f 00 04 00 41 00 06 00 42 00 05 00     ..o./...A...B...
700000f0:	47 00 46 00 76 00 8a 00 77 00 0c 00 80 00 01 00     G.F.v...w.......
70000100:	af 00 12 00 aa 00 84 00 1d 00 00 00 1e 00 04 00     ................
70000110:	6c 00 40 00 9e 00 38 00 0c 00 00 00 6e 00 2c 00     l.@...8.....n.,.
70000120:	70 00 f9 00 71 00 dd 00 72 00 d5 00 73 00 5a 00     p...q...r...s.Z.
70000130:	74 00 02 00 78 00 1c 00 89 00 01 00 6b 00 20 00     t...x.......k. .
70000140:	86 00 40 00 6f 00 00 00 30 00 8d 00 31 00 08 00     ..@.o...0...1...
70000150:	32 00 20 00 33 00 5c 00 34 00 30 00 35 00 30 00     2. .3.\.4.0.5.0.
70000160:	3a 00 b9 00 56 00 92 00 59 00 40 00 5a 00 01 00     :...V...Y.@.Z...
70000170:	61 00 00 00 64 00 c0 00 85 00 44 00 8a 00 00 00     a...d.....D.....
70000180:	91 00 58 00 94 00 a0 00 9b 00 8f 00 a6 00 02 00     ..X.............
70000190:	a7 00 a0 00 a9 00 48 00 45 00 09 00 5b 00 a5 00     ......H.E...[...
700001a0:	5c 00 8c 00 5d 00 97 00 5e 00 48 00 65 00 32 00     \...]...^.H.e.2.
700001b0:	66 00 80 00 67 00 44 00 68 00 00 00 69 00 74 00     f...g.D.h...i.t.
700001c0:	6a 00 2b 00 7a 00 82 00 8d 00 6f 00 8f 00 90 00     j.+.z.....o.....
700001d0:	a4 00 c7 00 a5 00 af 00 b7 00 61 00 97 00 20 00     ..........a... .
700001e0:	13 00 81 00 96 00 84 00 4a 00 01 00 7e 00 4c 00     ........J...~.L.
700001f0:	8e 00 80 00 50 00 02 00 93 00 00 00 b5 00 4c 00     ....P.........L.
70000200:	b1 00 00 00 a1 00 0f 00 a3 00 40 00 49 00 40 00     ..........@.I.@.
70000210:	8c 00 ff 00 8b 00 01 00 bc 00 11 00 82 00 00 00     ................
70000220:	9f 00 50 00 19 00 20 00 1b 00 4f 00 12 00 30 00     ..P... ...O...0.
70000230:	48 00 86 00 48 00 06 00 00 00 10 00                 H...H.......

7000023c <real_slave_addr>:
7000023c:	40 00 00 00                                         @...

70000240 <slave_addr_list>:
70000240:	40 00 00 00 46 00 00 00                             @...F...

70000248 <rts_isp_set_voe_ops>:
70000248:	4b01      	ldr	r3, [pc, #4]	; (70000250 <rts_isp_set_voe_ops+0x8>)
7000024a:	6018      	str	r0, [r3, #0]
7000024c:	4770      	bx	lr
7000024e:	bf00      	nop
70000250:	70000048 	.word	0x70000048

70000254 <isp_driver_is_fpga>:
70000254:	2000      	movs	r0, #0
70000256:	4770      	bx	lr

70000258 <k06a_get_info>:
70000258:	b530      	push	{r4, r5, lr}
7000025a:	2800      	cmp	r0, #0
7000025c:	d14d      	bne.n	700002fa <k06a_get_info+0xa2>
7000025e:	2900      	cmp	r1, #0
70000260:	d04b      	beq.n	700002fa <k06a_get_info+0xa2>
70000262:	f44f 6220 	mov.w	r2, #2560	; 0xa00
70000266:	f44f 63b4 	mov.w	r3, #1440	; 0x5a0
7000026a:	f44f 747a 	mov.w	r4, #1000	; 0x3e8
7000026e:	4d24      	ldr	r5, [pc, #144]	; (70000300 <k06a_get_info+0xa8>)
70000270:	7108      	strb	r0, [r1, #4]
70000272:	f881 00b0 	strb.w	r0, [r1, #176]	; 0xb0
70000276:	f8c1 00b4 	str.w	r0, [r1, #180]	; 0xb4
7000027a:	f881 00bc 	strb.w	r0, [r1, #188]	; 0xbc
7000027e:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
70000282:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
70000286:	f8c1 02dc 	str.w	r0, [r1, #732]	; 0x2dc
7000028a:	e9c1 2302 	strd	r2, r3, [r1, #8]
7000028e:	4b1d      	ldr	r3, [pc, #116]	; (70000304 <k06a_get_info+0xac>)
70000290:	4a1d      	ldr	r2, [pc, #116]	; (70000308 <k06a_get_info+0xb0>)
70000292:	610b      	str	r3, [r1, #16]
70000294:	2301      	movs	r3, #1
70000296:	6812      	ldr	r2, [r2, #0]
70000298:	600b      	str	r3, [r1, #0]
7000029a:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
7000029e:	4a1b      	ldr	r2, [pc, #108]	; (7000030c <k06a_get_info+0xb4>)
700002a0:	f881 3098 	strb.w	r3, [r1, #152]	; 0x98
700002a4:	7812      	ldrb	r2, [r2, #0]
700002a6:	f881 30c8 	strb.w	r3, [r1, #200]	; 0xc8
700002aa:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
700002ae:	2203      	movs	r2, #3
700002b0:	e9c1 542a 	strd	r5, r4, [r1, #168]	; 0xa8
700002b4:	e9c1 3430 	strd	r3, r4, [r1, #192]	; 0xc0
700002b8:	e9c1 0433 	strd	r0, r4, [r1, #204]	; 0xcc
700002bc:	f240 1401 	movw	r4, #257	; 0x101
700002c0:	f242 7510 	movw	r5, #10000	; 0x2710
700002c4:	f881 20a4 	strb.w	r2, [r1, #164]	; 0xa4
700002c8:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
700002cc:	2406      	movs	r4, #6
700002ce:	f8c1 50b8 	str.w	r5, [r1, #184]	; 0xb8
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
700002fe:	e7fb      	b.n	700002f8 <k06a_get_info+0xa0>
70000300:	016e3600 	.word	0x016e3600
70000304:	41f00000 	.word	0x41f00000
70000308:	7000023c 	.word	0x7000023c
7000030c:	7000004c 	.word	0x7000004c

70000310 <k06a_get_init_info>:
70000310:	b570      	push	{r4, r5, r6, lr}
70000312:	4614      	mov	r4, r2
70000314:	4605      	mov	r5, r0
70000316:	b110      	cbz	r0, 7000031e <k06a_get_init_info+0xe>
70000318:	f06f 0015 	mvn.w	r0, #21
7000031c:	bd70      	pop	{r4, r5, r6, pc}
7000031e:	2a00      	cmp	r2, #0
70000320:	d0fa      	beq.n	70000318 <k06a_get_init_info+0x8>
70000322:	780b      	ldrb	r3, [r1, #0]
70000324:	4e20      	ldr	r6, [pc, #128]	; (700003a8 <k06a_get_init_info+0x98>)
70000326:	68c8      	ldr	r0, [r1, #12]
70000328:	7033      	strb	r3, [r6, #0]
7000032a:	f001 f93b 	bl	700015a4 <__aeabi_f2uiz>
7000032e:	b280      	uxth	r0, r0
70000330:	f000 ff1e 	bl	70001170 <__aeabi_i2f>
70000334:	491d      	ldr	r1, [pc, #116]	; (700003ac <k06a_get_init_info+0x9c>)
70000336:	f001 f903 	bl	70001540 <__aeabi_fcmpeq>
7000033a:	2800      	cmp	r0, #0
7000033c:	d0ec      	beq.n	70000318 <k06a_get_init_info+0x8>
7000033e:	4b1c      	ldr	r3, [pc, #112]	; (700003b0 <k06a_get_init_info+0xa0>)
70000340:	f640 2208 	movw	r2, #2568	; 0xa08
70000344:	2105      	movs	r1, #5
70000346:	f44f 6070 	mov.w	r0, #3840	; 0xf00
7000034a:	6063      	str	r3, [r4, #4]
7000034c:	2373      	movs	r3, #115	; 0x73
7000034e:	60a5      	str	r5, [r4, #8]
70000350:	6023      	str	r3, [r4, #0]
70000352:	f106 0318 	add.w	r3, r6, #24
70000356:	6165      	str	r5, [r4, #20]
70000358:	6123      	str	r3, [r4, #16]
7000035a:	2303      	movs	r3, #3
7000035c:	60e3      	str	r3, [r4, #12]
7000035e:	2302      	movs	r3, #2
70000360:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
70000364:	f240 3303 	movw	r3, #771	; 0x303
70000368:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
7000036c:	230a      	movs	r3, #10
7000036e:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
70000372:	2304      	movs	r3, #4
70000374:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
70000378:	f44f 63b5 	mov.w	r3, #1448	; 0x5a8
7000037c:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
70000380:	2301      	movs	r3, #1
70000382:	e9c4 1322 	strd	r1, r3, [r4, #136]	; 0x88
70000386:	4b0b      	ldr	r3, [pc, #44]	; (700003b4 <k06a_get_init_info+0xa4>)
70000388:	e9c4 3024 	strd	r3, r0, [r4, #144]	; 0x90
7000038c:	f240 53dc 	movw	r3, #1500	; 0x5dc
70000390:	4628      	mov	r0, r5
70000392:	6073      	str	r3, [r6, #4]
70000394:	f8c4 3098 	str.w	r3, [r4, #152]	; 0x98
70000398:	f64a 73c8 	movw	r3, #45000	; 0xafc8
7000039c:	f8c4 309c 	str.w	r3, [r4, #156]	; 0x9c
700003a0:	4b05      	ldr	r3, [pc, #20]	; (700003b8 <k06a_get_init_info+0xa8>)
700003a2:	60b3      	str	r3, [r6, #8]
700003a4:	e7ba      	b.n	7000031c <k06a_get_init_info+0xc>
700003a6:	bf00      	nop
700003a8:	7000004c 	.word	0x7000004c
700003ac:	41f00000 	.word	0x41f00000
700003b0:	70000070 	.word	0x70000070
700003b4:	0a4cb800 	.word	0x0a4cb800
700003b8:	41b1c71c 	.word	0x41b1c71c

700003bc <k06a_start>:
700003bc:	b918      	cbnz	r0, 700003c6 <k06a_start+0xa>
700003be:	4b03      	ldr	r3, [pc, #12]	; (700003cc <k06a_start+0x10>)
700003c0:	2200      	movs	r2, #0
700003c2:	60da      	str	r2, [r3, #12]
700003c4:	4770      	bx	lr
700003c6:	f06f 0015 	mvn.w	r0, #21
700003ca:	4770      	bx	lr
700003cc:	7000004c 	.word	0x7000004c

700003d0 <k06a_get_tuned_dgain>:
700003d0:	b920      	cbnz	r0, 700003dc <k06a_get_tuned_dgain+0xc>
700003d2:	b119      	cbz	r1, 700003dc <k06a_get_tuned_dgain+0xc>
700003d4:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
700003d8:	600b      	str	r3, [r1, #0]
700003da:	4770      	bx	lr
700003dc:	f06f 0015 	mvn.w	r0, #21
700003e0:	4770      	bx	lr
	...

700003e4 <k06a_get_exposure_gain_info>:
700003e4:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
700003e8:	4614      	mov	r4, r2
700003ea:	2800      	cmp	r0, #0
700003ec:	d14b      	bne.n	70000486 <k06a_get_exposure_gain_info+0xa2>
700003ee:	2900      	cmp	r1, #0
700003f0:	d049      	beq.n	70000486 <k06a_get_exposure_gain_info+0xa2>
700003f2:	2a00      	cmp	r2, #0
700003f4:	d047      	beq.n	70000486 <k06a_get_exposure_gain_info+0xa2>
700003f6:	f8d1 8000 	ldr.w	r8, [r1]
700003fa:	1d15      	adds	r5, r2, #4
700003fc:	4f23      	ldr	r7, [pc, #140]	; (7000048c <k06a_get_exposure_gain_info+0xa8>)
700003fe:	698e      	ldr	r6, [r1, #24]
70000400:	4641      	mov	r1, r8
70000402:	68f8      	ldr	r0, [r7, #12]
70000404:	f000 fdfe 	bl	70001004 <__aeabi_fsub>
70000408:	2100      	movs	r1, #0
7000040a:	4681      	mov	r9, r0
7000040c:	f001 f8b6 	bl	7000157c <__aeabi_fcmpge>
70000410:	2800      	cmp	r0, #0
70000412:	d033      	beq.n	7000047c <k06a_get_exposure_gain_info+0x98>
70000414:	491e      	ldr	r1, [pc, #120]	; (70000490 <k06a_get_exposure_gain_info+0xac>)
70000416:	4648      	mov	r0, r9
70000418:	f001 f8ba 	bl	70001590 <__aeabi_fcmpgt>
7000041c:	b1a8      	cbz	r0, 7000044a <k06a_get_exposure_gain_info+0x66>
7000041e:	68b9      	ldr	r1, [r7, #8]
70000420:	4640      	mov	r0, r8
70000422:	f000 ffad 	bl	70001380 <__aeabi_fdiv>
70000426:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
7000042a:	f000 fded 	bl	70001008 <__addsf3>
7000042e:	f001 f8b9 	bl	700015a4 <__aeabi_f2uiz>
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
7000044c:	8abf      	ldrh	r7, [r7, #20]
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
7000047c:	4905      	ldr	r1, [pc, #20]	; (70000494 <k06a_get_exposure_gain_info+0xb0>)
7000047e:	4648      	mov	r0, r9
70000480:	f001 f868 	bl	70001554 <__aeabi_fcmplt>
70000484:	e7ca      	b.n	7000041c <k06a_get_exposure_gain_info+0x38>
70000486:	f06f 0015 	mvn.w	r0, #21
7000048a:	e7f5      	b.n	70000478 <k06a_get_exposure_gain_info+0x94>
7000048c:	7000004c 	.word	0x7000004c
70000490:	3a83126f 	.word	0x3a83126f
70000494:	ba83126f 	.word	0xba83126f

70000498 <k06a_set_mirror_flip>:
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
700004b2:	d00b      	beq.n	700004cc <k06a_set_mirror_flip+0x34>
700004b4:	2b03      	cmp	r3, #3
700004b6:	d00f      	beq.n	700004d8 <k06a_set_mirror_flip+0x40>
700004b8:	4293      	cmp	r3, r2
700004ba:	4b08      	ldr	r3, [pc, #32]	; (700004dc <k06a_set_mirror_flip+0x44>)
700004bc:	d00a      	beq.n	700004d4 <k06a_set_mirror_flip+0x3c>
700004be:	4a08      	ldr	r2, [pc, #32]	; (700004e0 <k06a_set_mirror_flip+0x48>)
700004c0:	610a      	str	r2, [r1, #16]
700004c2:	624b      	str	r3, [r1, #36]	; 0x24
700004c4:	2302      	movs	r3, #2
700004c6:	2000      	movs	r0, #0
700004c8:	604b      	str	r3, [r1, #4]
700004ca:	4770      	bx	lr
700004cc:	4b05      	ldr	r3, [pc, #20]	; (700004e4 <k06a_set_mirror_flip+0x4c>)
700004ce:	610b      	str	r3, [r1, #16]
700004d0:	4b05      	ldr	r3, [pc, #20]	; (700004e8 <k06a_set_mirror_flip+0x50>)
700004d2:	e7f6      	b.n	700004c2 <k06a_set_mirror_flip+0x2a>
700004d4:	4a05      	ldr	r2, [pc, #20]	; (700004ec <k06a_set_mirror_flip+0x54>)
700004d6:	e7f3      	b.n	700004c0 <k06a_set_mirror_flip+0x28>
700004d8:	2312      	movs	r3, #18
700004da:	e7f8      	b.n	700004ce <k06a_set_mirror_flip+0x36>
700004dc:	008400aa 	.word	0x008400aa
700004e0:	00300012 	.word	0x00300012
700004e4:	00100012 	.word	0x00100012
700004e8:	008b00aa 	.word	0x008b00aa
700004ec:	00200012 	.word	0x00200012

700004f0 <k06a_check>:
700004f0:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
700004f2:	4f1d      	ldr	r7, [pc, #116]	; (70000568 <k06a_check+0x78>)
700004f4:	4605      	mov	r5, r0
700004f6:	683b      	ldr	r3, [r7, #0]
700004f8:	6c1b      	ldr	r3, [r3, #64]	; 0x40
700004fa:	4798      	blx	r3
700004fc:	2801      	cmp	r0, #1
700004fe:	dc2f      	bgt.n	70000560 <k06a_check+0x70>
70000500:	4b1a      	ldr	r3, [pc, #104]	; (7000056c <k06a_check+0x7c>)
70000502:	f853 2020 	ldr.w	r2, [r3, r0, lsl #2]
70000506:	4b1a      	ldr	r3, [pc, #104]	; (70000570 <k06a_check+0x80>)
70000508:	601a      	str	r2, [r3, #0]
7000050a:	683b      	ldr	r3, [r7, #0]
7000050c:	685b      	ldr	r3, [r3, #4]
7000050e:	4798      	blx	r3
70000510:	230a      	movs	r3, #10
70000512:	a901      	add	r1, sp, #4
70000514:	4628      	mov	r0, r5
70000516:	f8ad 3004 	strh.w	r3, [sp, #4]
7000051a:	683b      	ldr	r3, [r7, #0]
7000051c:	68db      	ldr	r3, [r3, #12]
7000051e:	4798      	blx	r3
70000520:	4604      	mov	r4, r0
70000522:	b128      	cbz	r0, 70000530 <k06a_check+0x40>
70000524:	683b      	ldr	r3, [r7, #0]
70000526:	689b      	ldr	r3, [r3, #8]
70000528:	4798      	blx	r3
7000052a:	4620      	mov	r0, r4
7000052c:	b003      	add	sp, #12
7000052e:	bdf0      	pop	{r4, r5, r6, r7, pc}
70000530:	230b      	movs	r3, #11
70000532:	a901      	add	r1, sp, #4
70000534:	4628      	mov	r0, r5
70000536:	f8bd 6006 	ldrh.w	r6, [sp, #6]
7000053a:	f8ad 3004 	strh.w	r3, [sp, #4]
7000053e:	683b      	ldr	r3, [r7, #0]
70000540:	68db      	ldr	r3, [r3, #12]
70000542:	4798      	blx	r3
70000544:	4604      	mov	r4, r0
70000546:	2800      	cmp	r0, #0
70000548:	d1ec      	bne.n	70000524 <k06a_check+0x34>
7000054a:	683b      	ldr	r3, [r7, #0]
7000054c:	f8bd 5006 	ldrh.w	r5, [sp, #6]
70000550:	689b      	ldr	r3, [r3, #8]
70000552:	4798      	blx	r3
70000554:	f640 0352 	movw	r3, #2130	; 0x852
70000558:	ea45 2506 	orr.w	r5, r5, r6, lsl #8
7000055c:	429d      	cmp	r5, r3
7000055e:	d0e4      	beq.n	7000052a <k06a_check+0x3a>
70000560:	f06f 0415 	mvn.w	r4, #21
70000564:	e7e1      	b.n	7000052a <k06a_check+0x3a>
70000566:	bf00      	nop
70000568:	70000048 	.word	0x70000048
7000056c:	70000240 	.word	0x70000240
70000570:	7000023c 	.word	0x7000023c

70000574 <k06a_get_slave_addr_num>:
70000574:	2002      	movs	r0, #2
70000576:	4770      	bx	lr

70000578 <k06a_get_exposure_range>:
70000578:	460a      	mov	r2, r1
7000057a:	b538      	push	{r3, r4, r5, lr}
7000057c:	b970      	cbnz	r0, 7000059c <k06a_get_exposure_range+0x24>
7000057e:	4909      	ldr	r1, [pc, #36]	; (700005a4 <k06a_get_exposure_range+0x2c>)
70000580:	780c      	ldrb	r4, [r1, #0]
70000582:	b954      	cbnz	r4, 7000059a <k06a_get_exposure_range+0x22>
70000584:	688d      	ldr	r5, [r1, #8]
70000586:	1f10      	subs	r0, r2, #4
70000588:	601d      	str	r5, [r3, #0]
7000058a:	f000 fded 	bl	70001168 <__aeabi_ui2f>
7000058e:	4629      	mov	r1, r5
70000590:	f000 fe42 	bl	70001218 <__aeabi_fmul>
70000594:	9b04      	ldr	r3, [sp, #16]
70000596:	6018      	str	r0, [r3, #0]
70000598:	4620      	mov	r0, r4
7000059a:	bd38      	pop	{r3, r4, r5, pc}
7000059c:	f06f 0015 	mvn.w	r0, #21
700005a0:	e7fb      	b.n	7000059a <k06a_get_exposure_range+0x22>
700005a2:	bf00      	nop
700005a4:	7000004c 	.word	0x7000004c

700005a8 <k06a_get_tuned_again>:
700005a8:	b570      	push	{r4, r5, r6, lr}
700005aa:	460e      	mov	r6, r1
700005ac:	2800      	cmp	r0, #0
700005ae:	f040 80ab 	bne.w	70000708 <k06a_get_tuned_again+0x160>
700005b2:	2900      	cmp	r1, #0
700005b4:	f000 80a8 	beq.w	70000708 <k06a_get_tuned_again+0x160>
700005b8:	680c      	ldr	r4, [r1, #0]
700005ba:	f04f 517e 	mov.w	r1, #1065353216	; 0x3f800000
700005be:	4620      	mov	r0, r4
700005c0:	f000 ffdc 	bl	7000157c <__aeabi_fcmpge>
700005c4:	b338      	cbz	r0, 70000616 <k06a_get_tuned_again+0x6e>
700005c6:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
700005ca:	4620      	mov	r0, r4
700005cc:	f000 ffc2 	bl	70001554 <__aeabi_fcmplt>
700005d0:	b308      	cbz	r0, 70000616 <k06a_get_tuned_again+0x6e>
700005d2:	4620      	mov	r0, r4
700005d4:	f000 fc42 	bl	70000e5c <__aeabi_f2d>
700005d8:	2200      	movs	r2, #0
700005da:	4b4d      	ldr	r3, [pc, #308]	; (70000710 <k06a_get_tuned_again+0x168>)
700005dc:	f000 fade 	bl	70000b9c <__aeabi_dsub>
700005e0:	2200      	movs	r2, #0
700005e2:	4b4c      	ldr	r3, [pc, #304]	; (70000714 <k06a_get_tuned_again+0x16c>)
700005e4:	f000 f8f8 	bl	700007d8 <__aeabi_dmul>
700005e8:	f000 fc90 	bl	70000f0c <__aeabi_d2iz>
700005ec:	4b4a      	ldr	r3, [pc, #296]	; (70000718 <k06a_get_tuned_again+0x170>)
700005ee:	b284      	uxth	r4, r0
700005f0:	6158      	str	r0, [r3, #20]
700005f2:	4620      	mov	r0, r4
700005f4:	f000 fdb8 	bl	70001168 <__aeabi_ui2f>
700005f8:	2c0f      	cmp	r4, #15
700005fa:	d85e      	bhi.n	700006ba <k06a_get_tuned_again+0x112>
700005fc:	f000 fc2e 	bl	70000e5c <__aeabi_f2d>
70000600:	2200      	movs	r2, #0
70000602:	4b46      	ldr	r3, [pc, #280]	; (7000071c <k06a_get_tuned_again+0x174>)
70000604:	f000 f8e8 	bl	700007d8 <__aeabi_dmul>
70000608:	2200      	movs	r2, #0
7000060a:	4b41      	ldr	r3, [pc, #260]	; (70000710 <k06a_get_tuned_again+0x168>)
7000060c:	f000 fac8 	bl	70000ba0 <__adddf3>
70000610:	f000 fca4 	bl	70000f5c <__aeabi_d2f>
70000614:	e059      	b.n	700006ca <k06a_get_tuned_again+0x122>
70000616:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
7000061a:	4620      	mov	r0, r4
7000061c:	f000 ffae 	bl	7000157c <__aeabi_fcmpge>
70000620:	b1b0      	cbz	r0, 70000650 <k06a_get_tuned_again+0xa8>
70000622:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
70000626:	4620      	mov	r0, r4
70000628:	f000 ff94 	bl	70001554 <__aeabi_fcmplt>
7000062c:	b180      	cbz	r0, 70000650 <k06a_get_tuned_again+0xa8>
7000062e:	4620      	mov	r0, r4
70000630:	f000 fc14 	bl	70000e5c <__aeabi_f2d>
70000634:	2200      	movs	r2, #0
70000636:	f04f 4380 	mov.w	r3, #1073741824	; 0x40000000
7000063a:	f000 faaf 	bl	70000b9c <__aeabi_dsub>
7000063e:	2200      	movs	r2, #0
70000640:	4b37      	ldr	r3, [pc, #220]	; (70000720 <k06a_get_tuned_again+0x178>)
70000642:	f000 f8c9 	bl	700007d8 <__aeabi_dmul>
70000646:	2200      	movs	r2, #0
70000648:	4b32      	ldr	r3, [pc, #200]	; (70000714 <k06a_get_tuned_again+0x16c>)
7000064a:	f000 faa9 	bl	70000ba0 <__adddf3>
7000064e:	e7cb      	b.n	700005e8 <k06a_get_tuned_again+0x40>
70000650:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
70000654:	4620      	mov	r0, r4
70000656:	f000 ff91 	bl	7000157c <__aeabi_fcmpge>
7000065a:	b198      	cbz	r0, 70000684 <k06a_get_tuned_again+0xdc>
7000065c:	f04f 4182 	mov.w	r1, #1090519040	; 0x41000000
70000660:	4620      	mov	r0, r4
70000662:	f000 ff77 	bl	70001554 <__aeabi_fcmplt>
70000666:	b168      	cbz	r0, 70000684 <k06a_get_tuned_again+0xdc>
70000668:	4620      	mov	r0, r4
7000066a:	f000 fbf7 	bl	70000e5c <__aeabi_f2d>
7000066e:	2200      	movs	r2, #0
70000670:	4b2c      	ldr	r3, [pc, #176]	; (70000724 <k06a_get_tuned_again+0x17c>)
70000672:	f000 fa93 	bl	70000b9c <__aeabi_dsub>
70000676:	2200      	movs	r2, #0
70000678:	4b2a      	ldr	r3, [pc, #168]	; (70000724 <k06a_get_tuned_again+0x17c>)
7000067a:	f000 f8ad 	bl	700007d8 <__aeabi_dmul>
7000067e:	2200      	movs	r2, #0
70000680:	4b29      	ldr	r3, [pc, #164]	; (70000728 <k06a_get_tuned_again+0x180>)
70000682:	e7e2      	b.n	7000064a <k06a_get_tuned_again+0xa2>
70000684:	f04f 4182 	mov.w	r1, #1090519040	; 0x41000000
70000688:	4620      	mov	r0, r4
7000068a:	f000 ff77 	bl	7000157c <__aeabi_fcmpge>
7000068e:	b190      	cbz	r0, 700006b6 <k06a_get_tuned_again+0x10e>
70000690:	4926      	ldr	r1, [pc, #152]	; (7000072c <k06a_get_tuned_again+0x184>)
70000692:	4620      	mov	r0, r4
70000694:	f000 ff68 	bl	70001568 <__aeabi_fcmple>
70000698:	b168      	cbz	r0, 700006b6 <k06a_get_tuned_again+0x10e>
7000069a:	4620      	mov	r0, r4
7000069c:	f000 fbde 	bl	70000e5c <__aeabi_f2d>
700006a0:	2200      	movs	r2, #0
700006a2:	4b1f      	ldr	r3, [pc, #124]	; (70000720 <k06a_get_tuned_again+0x178>)
700006a4:	f000 fa7a 	bl	70000b9c <__aeabi_dsub>
700006a8:	4602      	mov	r2, r0
700006aa:	460b      	mov	r3, r1
700006ac:	f000 fa78 	bl	70000ba0 <__adddf3>
700006b0:	2200      	movs	r2, #0
700006b2:	4b1f      	ldr	r3, [pc, #124]	; (70000730 <k06a_get_tuned_again+0x188>)
700006b4:	e7c9      	b.n	7000064a <k06a_get_tuned_again+0xa2>
700006b6:	203f      	movs	r0, #63	; 0x3f
700006b8:	e798      	b.n	700005ec <k06a_get_tuned_again+0x44>
700006ba:	f1a4 0310 	sub.w	r3, r4, #16
700006be:	2b0f      	cmp	r3, #15
700006c0:	d807      	bhi.n	700006d2 <k06a_get_tuned_again+0x12a>
700006c2:	f04f 5178 	mov.w	r1, #1040187392	; 0x3e000000
700006c6:	f000 fda7 	bl	70001218 <__aeabi_fmul>
700006ca:	4605      	mov	r5, r0
700006cc:	2000      	movs	r0, #0
700006ce:	6035      	str	r5, [r6, #0]
700006d0:	bd70      	pop	{r4, r5, r6, pc}
700006d2:	f1a4 0320 	sub.w	r3, r4, #32
700006d6:	2b0f      	cmp	r3, #15
700006d8:	d80a      	bhi.n	700006f0 <k06a_get_tuned_again+0x148>
700006da:	f000 fbbf 	bl	70000e5c <__aeabi_f2d>
700006de:	2200      	movs	r2, #0
700006e0:	4b14      	ldr	r3, [pc, #80]	; (70000734 <k06a_get_tuned_again+0x18c>)
700006e2:	f000 f879 	bl	700007d8 <__aeabi_dmul>
700006e6:	2200      	movs	r2, #0
700006e8:	4b0e      	ldr	r3, [pc, #56]	; (70000724 <k06a_get_tuned_again+0x17c>)
700006ea:	f000 fa57 	bl	70000b9c <__aeabi_dsub>
700006ee:	e78f      	b.n	70000610 <k06a_get_tuned_again+0x68>
700006f0:	3c30      	subs	r4, #48	; 0x30
700006f2:	2c0f      	cmp	r4, #15
700006f4:	d8ea      	bhi.n	700006cc <k06a_get_tuned_again+0x124>
700006f6:	f000 fbb1 	bl	70000e5c <__aeabi_f2d>
700006fa:	2200      	movs	r2, #0
700006fc:	4b0e      	ldr	r3, [pc, #56]	; (70000738 <k06a_get_tuned_again+0x190>)
700006fe:	f000 f86b 	bl	700007d8 <__aeabi_dmul>
70000702:	2200      	movs	r2, #0
70000704:	4b03      	ldr	r3, [pc, #12]	; (70000714 <k06a_get_tuned_again+0x16c>)
70000706:	e7f0      	b.n	700006ea <k06a_get_tuned_again+0x142>
70000708:	f06f 0015 	mvn.w	r0, #21
7000070c:	e7e0      	b.n	700006d0 <k06a_get_tuned_again+0x128>
7000070e:	bf00      	nop
70000710:	3ff00000 	.word	0x3ff00000
70000714:	40300000 	.word	0x40300000
70000718:	7000004c 	.word	0x7000004c
7000071c:	3fb00000 	.word	0x3fb00000
70000720:	40200000 	.word	0x40200000
70000724:	40100000 	.word	0x40100000
70000728:	40400000 	.word	0x40400000
7000072c:	417c0000 	.word	0x417c0000
70000730:	40480000 	.word	0x40480000
70000734:	3fd00000 	.word	0x3fd00000
70000738:	3fe00000 	.word	0x3fe00000

7000073c <rts_isp_get_sensor_ops>:
7000073c:	4800      	ldr	r0, [pc, #0]	; (70000740 <rts_isp_get_sensor_ops+0x4>)
7000073e:	4770      	bx	lr
70000740:	70000744 	.word	0x70000744

70000744 <k06a_ops>:
70000744:	73000005 6136306b 00000000 00000000     ...sk06a........
	...
70000768:	70000259 70000311 70000579 700005a9     Y..p...py..p...p
70000778:	700003d1 700003e5 00000000 00000000     ...p...p........
70000788:	700003bd 00000000 00000000 00000000     ...p............
70000798:	70000499 00000000 00000000 00000000     ...p............
700007a8:	700004f1 00000000 00000000 00000000     ...p............
700007b8:	70000575 00000000 00000000 00000000     u..p............
	...

700007d8 <__aeabi_dmul>:
700007d8:	b570      	push	{r4, r5, r6, lr}
700007da:	f04f 0cff 	mov.w	ip, #255	; 0xff
700007de:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
700007e2:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
700007e6:	bf1d      	ittte	ne
700007e8:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
700007ec:	ea94 0f0c 	teqne	r4, ip
700007f0:	ea95 0f0c 	teqne	r5, ip
700007f4:	f000 f8de 	bleq	700009b4 <__aeabi_dmul+0x1dc>
700007f8:	442c      	add	r4, r5
700007fa:	ea81 0603 	eor.w	r6, r1, r3
700007fe:	ea21 514c 	bic.w	r1, r1, ip, lsl #21
70000802:	ea23 534c 	bic.w	r3, r3, ip, lsl #21
70000806:	ea50 3501 	orrs.w	r5, r0, r1, lsl #12
7000080a:	bf18      	it	ne
7000080c:	ea52 3503 	orrsne.w	r5, r2, r3, lsl #12
70000810:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70000814:	f443 1380 	orr.w	r3, r3, #1048576	; 0x100000
70000818:	d038      	beq.n	7000088c <__aeabi_dmul+0xb4>
7000081a:	fba0 ce02 	umull	ip, lr, r0, r2
7000081e:	f04f 0500 	mov.w	r5, #0
70000822:	fbe1 e502 	umlal	lr, r5, r1, r2
70000826:	f006 4200 	and.w	r2, r6, #2147483648	; 0x80000000
7000082a:	fbe0 e503 	umlal	lr, r5, r0, r3
7000082e:	f04f 0600 	mov.w	r6, #0
70000832:	fbe1 5603 	umlal	r5, r6, r1, r3
70000836:	f09c 0f00 	teq	ip, #0
7000083a:	bf18      	it	ne
7000083c:	f04e 0e01 	orrne.w	lr, lr, #1
70000840:	f1a4 04ff 	sub.w	r4, r4, #255	; 0xff
70000844:	f5b6 7f00 	cmp.w	r6, #512	; 0x200
70000848:	f564 7440 	sbc.w	r4, r4, #768	; 0x300
7000084c:	d204      	bcs.n	70000858 <__aeabi_dmul+0x80>
7000084e:	ea5f 0e4e 	movs.w	lr, lr, lsl #1
70000852:	416d      	adcs	r5, r5
70000854:	eb46 0606 	adc.w	r6, r6, r6
70000858:	ea42 21c6 	orr.w	r1, r2, r6, lsl #11
7000085c:	ea41 5155 	orr.w	r1, r1, r5, lsr #21
70000860:	ea4f 20c5 	mov.w	r0, r5, lsl #11
70000864:	ea40 505e 	orr.w	r0, r0, lr, lsr #21
70000868:	ea4f 2ece 	mov.w	lr, lr, lsl #11
7000086c:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
70000870:	bf88      	it	hi
70000872:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
70000876:	d81e      	bhi.n	700008b6 <__aeabi_dmul+0xde>
70000878:	f1be 4f00 	cmp.w	lr, #2147483648	; 0x80000000
7000087c:	bf08      	it	eq
7000087e:	ea5f 0e50 	movseq.w	lr, r0, lsr #1
70000882:	f150 0000 	adcs.w	r0, r0, #0
70000886:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
7000088a:	bd70      	pop	{r4, r5, r6, pc}
7000088c:	f006 4600 	and.w	r6, r6, #2147483648	; 0x80000000
70000890:	ea46 0101 	orr.w	r1, r6, r1
70000894:	ea40 0002 	orr.w	r0, r0, r2
70000898:	ea81 0103 	eor.w	r1, r1, r3
7000089c:	ebb4 045c 	subs.w	r4, r4, ip, lsr #1
700008a0:	bfc2      	ittt	gt
700008a2:	ebd4 050c 	rsbsgt	r5, r4, ip
700008a6:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
700008aa:	bd70      	popgt	{r4, r5, r6, pc}
700008ac:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
700008b0:	f04f 0e00 	mov.w	lr, #0
700008b4:	3c01      	subs	r4, #1
700008b6:	f300 80ab 	bgt.w	70000a10 <__aeabi_dmul+0x238>
700008ba:	f114 0f36 	cmn.w	r4, #54	; 0x36
700008be:	bfde      	ittt	le
700008c0:	2000      	movle	r0, #0
700008c2:	f001 4100 	andle.w	r1, r1, #2147483648	; 0x80000000
700008c6:	bd70      	pople	{r4, r5, r6, pc}
700008c8:	f1c4 0400 	rsb	r4, r4, #0
700008cc:	3c20      	subs	r4, #32
700008ce:	da35      	bge.n	7000093c <__aeabi_dmul+0x164>
700008d0:	340c      	adds	r4, #12
700008d2:	dc1b      	bgt.n	7000090c <__aeabi_dmul+0x134>
700008d4:	f104 0414 	add.w	r4, r4, #20
700008d8:	f1c4 0520 	rsb	r5, r4, #32
700008dc:	fa00 f305 	lsl.w	r3, r0, r5
700008e0:	fa20 f004 	lsr.w	r0, r0, r4
700008e4:	fa01 f205 	lsl.w	r2, r1, r5
700008e8:	ea40 0002 	orr.w	r0, r0, r2
700008ec:	f001 4200 	and.w	r2, r1, #2147483648	; 0x80000000
700008f0:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
700008f4:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
700008f8:	fa21 f604 	lsr.w	r6, r1, r4
700008fc:	eb42 0106 	adc.w	r1, r2, r6
70000900:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70000904:	bf08      	it	eq
70000906:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
7000090a:	bd70      	pop	{r4, r5, r6, pc}
7000090c:	f1c4 040c 	rsb	r4, r4, #12
70000910:	f1c4 0520 	rsb	r5, r4, #32
70000914:	fa00 f304 	lsl.w	r3, r0, r4
70000918:	fa20 f005 	lsr.w	r0, r0, r5
7000091c:	fa01 f204 	lsl.w	r2, r1, r4
70000920:	ea40 0002 	orr.w	r0, r0, r2
70000924:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70000928:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
7000092c:	f141 0100 	adc.w	r1, r1, #0
70000930:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70000934:	bf08      	it	eq
70000936:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
7000093a:	bd70      	pop	{r4, r5, r6, pc}
7000093c:	f1c4 0520 	rsb	r5, r4, #32
70000940:	fa00 f205 	lsl.w	r2, r0, r5
70000944:	ea4e 0e02 	orr.w	lr, lr, r2
70000948:	fa20 f304 	lsr.w	r3, r0, r4
7000094c:	fa01 f205 	lsl.w	r2, r1, r5
70000950:	ea43 0302 	orr.w	r3, r3, r2
70000954:	fa21 f004 	lsr.w	r0, r1, r4
70000958:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
7000095c:	fa21 f204 	lsr.w	r2, r1, r4
70000960:	ea20 0002 	bic.w	r0, r0, r2
70000964:	eb00 70d3 	add.w	r0, r0, r3, lsr #31
70000968:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
7000096c:	bf08      	it	eq
7000096e:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70000972:	bd70      	pop	{r4, r5, r6, pc}
70000974:	f094 0f00 	teq	r4, #0
70000978:	d10f      	bne.n	7000099a <__aeabi_dmul+0x1c2>
7000097a:	f001 4600 	and.w	r6, r1, #2147483648	; 0x80000000
7000097e:	0040      	lsls	r0, r0, #1
70000980:	eb41 0101 	adc.w	r1, r1, r1
70000984:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
70000988:	bf08      	it	eq
7000098a:	3c01      	subeq	r4, #1
7000098c:	d0f7      	beq.n	7000097e <__aeabi_dmul+0x1a6>
7000098e:	ea41 0106 	orr.w	r1, r1, r6
70000992:	f095 0f00 	teq	r5, #0
70000996:	bf18      	it	ne
70000998:	4770      	bxne	lr
7000099a:	f003 4600 	and.w	r6, r3, #2147483648	; 0x80000000
7000099e:	0052      	lsls	r2, r2, #1
700009a0:	eb43 0303 	adc.w	r3, r3, r3
700009a4:	f413 1f80 	tst.w	r3, #1048576	; 0x100000
700009a8:	bf08      	it	eq
700009aa:	3d01      	subeq	r5, #1
700009ac:	d0f7      	beq.n	7000099e <__aeabi_dmul+0x1c6>
700009ae:	ea43 0306 	orr.w	r3, r3, r6
700009b2:	4770      	bx	lr
700009b4:	ea94 0f0c 	teq	r4, ip
700009b8:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
700009bc:	bf18      	it	ne
700009be:	ea95 0f0c 	teqne	r5, ip
700009c2:	d00c      	beq.n	700009de <__aeabi_dmul+0x206>
700009c4:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
700009c8:	bf18      	it	ne
700009ca:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
700009ce:	d1d1      	bne.n	70000974 <__aeabi_dmul+0x19c>
700009d0:	ea81 0103 	eor.w	r1, r1, r3
700009d4:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700009d8:	f04f 0000 	mov.w	r0, #0
700009dc:	bd70      	pop	{r4, r5, r6, pc}
700009de:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
700009e2:	bf06      	itte	eq
700009e4:	4610      	moveq	r0, r2
700009e6:	4619      	moveq	r1, r3
700009e8:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
700009ec:	d019      	beq.n	70000a22 <__aeabi_dmul+0x24a>
700009ee:	ea94 0f0c 	teq	r4, ip
700009f2:	d102      	bne.n	700009fa <__aeabi_dmul+0x222>
700009f4:	ea50 3601 	orrs.w	r6, r0, r1, lsl #12
700009f8:	d113      	bne.n	70000a22 <__aeabi_dmul+0x24a>
700009fa:	ea95 0f0c 	teq	r5, ip
700009fe:	d105      	bne.n	70000a0c <__aeabi_dmul+0x234>
70000a00:	ea52 3603 	orrs.w	r6, r2, r3, lsl #12
70000a04:	bf1c      	itt	ne
70000a06:	4610      	movne	r0, r2
70000a08:	4619      	movne	r1, r3
70000a0a:	d10a      	bne.n	70000a22 <__aeabi_dmul+0x24a>
70000a0c:	ea81 0103 	eor.w	r1, r1, r3
70000a10:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70000a14:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
70000a18:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
70000a1c:	f04f 0000 	mov.w	r0, #0
70000a20:	bd70      	pop	{r4, r5, r6, pc}
70000a22:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
70000a26:	f441 0178 	orr.w	r1, r1, #16252928	; 0xf80000
70000a2a:	bd70      	pop	{r4, r5, r6, pc}
70000a2c:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000a30:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000a34:	bf1e      	ittt	ne
70000a36:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000a3a:	ea92 0f0c 	teqne	r2, ip
70000a3e:	ea93 0f0c 	teqne	r3, ip
70000a42:	d06f      	beq.n	70000b24 <__aeabi_dmul+0x34c>
70000a44:	441a      	add	r2, r3
70000a46:	ea80 0c01 	eor.w	ip, r0, r1
70000a4a:	0240      	lsls	r0, r0, #9
70000a4c:	bf18      	it	ne
70000a4e:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000a52:	d01e      	beq.n	70000a92 <__aeabi_dmul+0x2ba>
70000a54:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000a58:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000a5c:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000a60:	fba0 3101 	umull	r3, r1, r0, r1
70000a64:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000a68:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000a6c:	bf3e      	ittt	cc
70000a6e:	0049      	lslcc	r1, r1, #1
70000a70:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000a74:	005b      	lslcc	r3, r3, #1
70000a76:	ea40 0001 	orr.w	r0, r0, r1
70000a7a:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000a7e:	2afd      	cmp	r2, #253	; 0xfd
70000a80:	d81d      	bhi.n	70000abe <__aeabi_dmul+0x2e6>
70000a82:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000a86:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000a8a:	bf08      	it	eq
70000a8c:	f020 0001 	biceq.w	r0, r0, #1
70000a90:	4770      	bx	lr
70000a92:	f090 0f00 	teq	r0, #0
70000a96:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000a9a:	bf08      	it	eq
70000a9c:	0249      	lsleq	r1, r1, #9
70000a9e:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000aa2:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000aa6:	3a7f      	subs	r2, #127	; 0x7f
70000aa8:	bfc2      	ittt	gt
70000aaa:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000aae:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000ab2:	4770      	bxgt	lr
70000ab4:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000ab8:	f04f 0300 	mov.w	r3, #0
70000abc:	3a01      	subs	r2, #1
70000abe:	dc5d      	bgt.n	70000b7c <__aeabi_dmul+0x3a4>
70000ac0:	f112 0f19 	cmn.w	r2, #25
70000ac4:	bfdc      	itt	le
70000ac6:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000aca:	4770      	bxle	lr
70000acc:	f1c2 0200 	rsb	r2, r2, #0
70000ad0:	0041      	lsls	r1, r0, #1
70000ad2:	fa21 f102 	lsr.w	r1, r1, r2
70000ad6:	f1c2 0220 	rsb	r2, r2, #32
70000ada:	fa00 fc02 	lsl.w	ip, r0, r2
70000ade:	ea5f 0031 	movs.w	r0, r1, rrx
70000ae2:	f140 0000 	adc.w	r0, r0, #0
70000ae6:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000aea:	bf08      	it	eq
70000aec:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000af0:	4770      	bx	lr
70000af2:	f092 0f00 	teq	r2, #0
70000af6:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000afa:	bf02      	ittt	eq
70000afc:	0040      	lsleq	r0, r0, #1
70000afe:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000b02:	3a01      	subeq	r2, #1
70000b04:	d0f9      	beq.n	70000afa <__aeabi_dmul+0x322>
70000b06:	ea40 000c 	orr.w	r0, r0, ip
70000b0a:	f093 0f00 	teq	r3, #0
70000b0e:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000b12:	bf02      	ittt	eq
70000b14:	0049      	lsleq	r1, r1, #1
70000b16:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000b1a:	3b01      	subeq	r3, #1
70000b1c:	d0f9      	beq.n	70000b12 <__aeabi_dmul+0x33a>
70000b1e:	ea41 010c 	orr.w	r1, r1, ip
70000b22:	e78f      	b.n	70000a44 <__aeabi_dmul+0x26c>
70000b24:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000b28:	ea92 0f0c 	teq	r2, ip
70000b2c:	bf18      	it	ne
70000b2e:	ea93 0f0c 	teqne	r3, ip
70000b32:	d00a      	beq.n	70000b4a <__aeabi_dmul+0x372>
70000b34:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000b38:	bf18      	it	ne
70000b3a:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000b3e:	d1d8      	bne.n	70000af2 <__aeabi_dmul+0x31a>
70000b40:	ea80 0001 	eor.w	r0, r0, r1
70000b44:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000b48:	4770      	bx	lr
70000b4a:	f090 0f00 	teq	r0, #0
70000b4e:	bf17      	itett	ne
70000b50:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000b54:	4608      	moveq	r0, r1
70000b56:	f091 0f00 	teqne	r1, #0
70000b5a:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000b5e:	d014      	beq.n	70000b8a <__aeabi_dmul+0x3b2>
70000b60:	ea92 0f0c 	teq	r2, ip
70000b64:	d101      	bne.n	70000b6a <__aeabi_dmul+0x392>
70000b66:	0242      	lsls	r2, r0, #9
70000b68:	d10f      	bne.n	70000b8a <__aeabi_dmul+0x3b2>
70000b6a:	ea93 0f0c 	teq	r3, ip
70000b6e:	d103      	bne.n	70000b78 <__aeabi_dmul+0x3a0>
70000b70:	024b      	lsls	r3, r1, #9
70000b72:	bf18      	it	ne
70000b74:	4608      	movne	r0, r1
70000b76:	d108      	bne.n	70000b8a <__aeabi_dmul+0x3b2>
70000b78:	ea80 0001 	eor.w	r0, r0, r1
70000b7c:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000b80:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000b84:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000b88:	4770      	bx	lr
70000b8a:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000b8e:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000b92:	4770      	bx	lr

70000b94 <__aeabi_drsub>:
70000b94:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000
70000b98:	e002      	b.n	70000ba0 <__adddf3>
70000b9a:	bf00      	nop

70000b9c <__aeabi_dsub>:
70000b9c:	f083 4300 	eor.w	r3, r3, #2147483648	; 0x80000000

70000ba0 <__adddf3>:
70000ba0:	b530      	push	{r4, r5, lr}
70000ba2:	ea4f 0441 	mov.w	r4, r1, lsl #1
70000ba6:	ea4f 0543 	mov.w	r5, r3, lsl #1
70000baa:	ea94 0f05 	teq	r4, r5
70000bae:	bf08      	it	eq
70000bb0:	ea90 0f02 	teqeq	r0, r2
70000bb4:	bf1f      	itttt	ne
70000bb6:	ea54 0c00 	orrsne.w	ip, r4, r0
70000bba:	ea55 0c02 	orrsne.w	ip, r5, r2
70000bbe:	ea7f 5c64 	mvnsne.w	ip, r4, asr #21
70000bc2:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70000bc6:	f000 80e2 	beq.w	70000d8e <__adddf3+0x1ee>
70000bca:	ea4f 5454 	mov.w	r4, r4, lsr #21
70000bce:	ebd4 5555 	rsbs	r5, r4, r5, lsr #21
70000bd2:	bfb8      	it	lt
70000bd4:	426d      	neglt	r5, r5
70000bd6:	dd0c      	ble.n	70000bf2 <__adddf3+0x52>
70000bd8:	442c      	add	r4, r5
70000bda:	ea80 0202 	eor.w	r2, r0, r2
70000bde:	ea81 0303 	eor.w	r3, r1, r3
70000be2:	ea82 0000 	eor.w	r0, r2, r0
70000be6:	ea83 0101 	eor.w	r1, r3, r1
70000bea:	ea80 0202 	eor.w	r2, r0, r2
70000bee:	ea81 0303 	eor.w	r3, r1, r3
70000bf2:	2d36      	cmp	r5, #54	; 0x36
70000bf4:	bf88      	it	hi
70000bf6:	bd30      	pophi	{r4, r5, pc}
70000bf8:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000bfc:	ea4f 3101 	mov.w	r1, r1, lsl #12
70000c00:	f44f 1c80 	mov.w	ip, #1048576	; 0x100000
70000c04:	ea4c 3111 	orr.w	r1, ip, r1, lsr #12
70000c08:	d002      	beq.n	70000c10 <__adddf3+0x70>
70000c0a:	4240      	negs	r0, r0
70000c0c:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000c10:	f013 4f00 	tst.w	r3, #2147483648	; 0x80000000
70000c14:	ea4f 3303 	mov.w	r3, r3, lsl #12
70000c18:	ea4c 3313 	orr.w	r3, ip, r3, lsr #12
70000c1c:	d002      	beq.n	70000c24 <__adddf3+0x84>
70000c1e:	4252      	negs	r2, r2
70000c20:	eb63 0343 	sbc.w	r3, r3, r3, lsl #1
70000c24:	ea94 0f05 	teq	r4, r5
70000c28:	f000 80a7 	beq.w	70000d7a <__adddf3+0x1da>
70000c2c:	f1a4 0401 	sub.w	r4, r4, #1
70000c30:	f1d5 0e20 	rsbs	lr, r5, #32
70000c34:	db0d      	blt.n	70000c52 <__adddf3+0xb2>
70000c36:	fa02 fc0e 	lsl.w	ip, r2, lr
70000c3a:	fa22 f205 	lsr.w	r2, r2, r5
70000c3e:	1880      	adds	r0, r0, r2
70000c40:	f141 0100 	adc.w	r1, r1, #0
70000c44:	fa03 f20e 	lsl.w	r2, r3, lr
70000c48:	1880      	adds	r0, r0, r2
70000c4a:	fa43 f305 	asr.w	r3, r3, r5
70000c4e:	4159      	adcs	r1, r3
70000c50:	e00e      	b.n	70000c70 <__adddf3+0xd0>
70000c52:	f1a5 0520 	sub.w	r5, r5, #32
70000c56:	f10e 0e20 	add.w	lr, lr, #32
70000c5a:	2a01      	cmp	r2, #1
70000c5c:	fa03 fc0e 	lsl.w	ip, r3, lr
70000c60:	bf28      	it	cs
70000c62:	f04c 0c02 	orrcs.w	ip, ip, #2
70000c66:	fa43 f305 	asr.w	r3, r3, r5
70000c6a:	18c0      	adds	r0, r0, r3
70000c6c:	eb51 71e3 	adcs.w	r1, r1, r3, asr #31
70000c70:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000c74:	d507      	bpl.n	70000c86 <__adddf3+0xe6>
70000c76:	f04f 0e00 	mov.w	lr, #0
70000c7a:	f1dc 0c00 	rsbs	ip, ip, #0
70000c7e:	eb7e 0000 	sbcs.w	r0, lr, r0
70000c82:	eb6e 0101 	sbc.w	r1, lr, r1
70000c86:	f5b1 1f80 	cmp.w	r1, #1048576	; 0x100000
70000c8a:	d31b      	bcc.n	70000cc4 <__adddf3+0x124>
70000c8c:	f5b1 1f00 	cmp.w	r1, #2097152	; 0x200000
70000c90:	d30c      	bcc.n	70000cac <__adddf3+0x10c>
70000c92:	0849      	lsrs	r1, r1, #1
70000c94:	ea5f 0030 	movs.w	r0, r0, rrx
70000c98:	ea4f 0c3c 	mov.w	ip, ip, rrx
70000c9c:	f104 0401 	add.w	r4, r4, #1
70000ca0:	ea4f 5244 	mov.w	r2, r4, lsl #21
70000ca4:	f512 0f80 	cmn.w	r2, #4194304	; 0x400000
70000ca8:	f080 809a 	bcs.w	70000de0 <__adddf3+0x240>
70000cac:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000cb0:	bf08      	it	eq
70000cb2:	ea5f 0c50 	movseq.w	ip, r0, lsr #1
70000cb6:	f150 0000 	adcs.w	r0, r0, #0
70000cba:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
70000cbe:	ea41 0105 	orr.w	r1, r1, r5
70000cc2:	bd30      	pop	{r4, r5, pc}
70000cc4:	ea5f 0c4c 	movs.w	ip, ip, lsl #1
70000cc8:	4140      	adcs	r0, r0
70000cca:	eb41 0101 	adc.w	r1, r1, r1
70000cce:	3c01      	subs	r4, #1
70000cd0:	bf28      	it	cs
70000cd2:	f5b1 1f80 	cmpcs.w	r1, #1048576	; 0x100000
70000cd6:	d2e9      	bcs.n	70000cac <__adddf3+0x10c>
70000cd8:	f091 0f00 	teq	r1, #0
70000cdc:	bf04      	itt	eq
70000cde:	4601      	moveq	r1, r0
70000ce0:	2000      	moveq	r0, #0
70000ce2:	fab1 f381 	clz	r3, r1
70000ce6:	bf08      	it	eq
70000ce8:	3320      	addeq	r3, #32
70000cea:	f1a3 030b 	sub.w	r3, r3, #11
70000cee:	f1b3 0220 	subs.w	r2, r3, #32
70000cf2:	da0c      	bge.n	70000d0e <__adddf3+0x16e>
70000cf4:	320c      	adds	r2, #12
70000cf6:	dd08      	ble.n	70000d0a <__adddf3+0x16a>
70000cf8:	f102 0c14 	add.w	ip, r2, #20
70000cfc:	f1c2 020c 	rsb	r2, r2, #12
70000d00:	fa01 f00c 	lsl.w	r0, r1, ip
70000d04:	fa21 f102 	lsr.w	r1, r1, r2
70000d08:	e00c      	b.n	70000d24 <__adddf3+0x184>
70000d0a:	f102 0214 	add.w	r2, r2, #20
70000d0e:	bfd8      	it	le
70000d10:	f1c2 0c20 	rsble	ip, r2, #32
70000d14:	fa01 f102 	lsl.w	r1, r1, r2
70000d18:	fa20 fc0c 	lsr.w	ip, r0, ip
70000d1c:	bfdc      	itt	le
70000d1e:	ea41 010c 	orrle.w	r1, r1, ip
70000d22:	4090      	lslle	r0, r2
70000d24:	1ae4      	subs	r4, r4, r3
70000d26:	bfa2      	ittt	ge
70000d28:	eb01 5104 	addge.w	r1, r1, r4, lsl #20
70000d2c:	4329      	orrge	r1, r5
70000d2e:	bd30      	popge	{r4, r5, pc}
70000d30:	ea6f 0404 	mvn.w	r4, r4
70000d34:	3c1f      	subs	r4, #31
70000d36:	da1c      	bge.n	70000d72 <__adddf3+0x1d2>
70000d38:	340c      	adds	r4, #12
70000d3a:	dc0e      	bgt.n	70000d5a <__adddf3+0x1ba>
70000d3c:	f104 0414 	add.w	r4, r4, #20
70000d40:	f1c4 0220 	rsb	r2, r4, #32
70000d44:	fa20 f004 	lsr.w	r0, r0, r4
70000d48:	fa01 f302 	lsl.w	r3, r1, r2
70000d4c:	ea40 0003 	orr.w	r0, r0, r3
70000d50:	fa21 f304 	lsr.w	r3, r1, r4
70000d54:	ea45 0103 	orr.w	r1, r5, r3
70000d58:	bd30      	pop	{r4, r5, pc}
70000d5a:	f1c4 040c 	rsb	r4, r4, #12
70000d5e:	f1c4 0220 	rsb	r2, r4, #32
70000d62:	fa20 f002 	lsr.w	r0, r0, r2
70000d66:	fa01 f304 	lsl.w	r3, r1, r4
70000d6a:	ea40 0003 	orr.w	r0, r0, r3
70000d6e:	4629      	mov	r1, r5
70000d70:	bd30      	pop	{r4, r5, pc}
70000d72:	fa21 f004 	lsr.w	r0, r1, r4
70000d76:	4629      	mov	r1, r5
70000d78:	bd30      	pop	{r4, r5, pc}
70000d7a:	f094 0f00 	teq	r4, #0
70000d7e:	f483 1380 	eor.w	r3, r3, #1048576	; 0x100000
70000d82:	bf06      	itte	eq
70000d84:	f481 1180 	eoreq.w	r1, r1, #1048576	; 0x100000
70000d88:	3401      	addeq	r4, #1
70000d8a:	3d01      	subne	r5, #1
70000d8c:	e74e      	b.n	70000c2c <__adddf3+0x8c>
70000d8e:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70000d92:	bf18      	it	ne
70000d94:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70000d98:	d029      	beq.n	70000dee <__adddf3+0x24e>
70000d9a:	ea94 0f05 	teq	r4, r5
70000d9e:	bf08      	it	eq
70000da0:	ea90 0f02 	teqeq	r0, r2
70000da4:	d005      	beq.n	70000db2 <__adddf3+0x212>
70000da6:	ea54 0c00 	orrs.w	ip, r4, r0
70000daa:	bf04      	itt	eq
70000dac:	4619      	moveq	r1, r3
70000dae:	4610      	moveq	r0, r2
70000db0:	bd30      	pop	{r4, r5, pc}
70000db2:	ea91 0f03 	teq	r1, r3
70000db6:	bf1e      	ittt	ne
70000db8:	2100      	movne	r1, #0
70000dba:	2000      	movne	r0, #0
70000dbc:	bd30      	popne	{r4, r5, pc}
70000dbe:	ea5f 5c54 	movs.w	ip, r4, lsr #21
70000dc2:	d105      	bne.n	70000dd0 <__adddf3+0x230>
70000dc4:	0040      	lsls	r0, r0, #1
70000dc6:	4149      	adcs	r1, r1
70000dc8:	bf28      	it	cs
70000dca:	f041 4100 	orrcs.w	r1, r1, #2147483648	; 0x80000000
70000dce:	bd30      	pop	{r4, r5, pc}
70000dd0:	f514 0480 	adds.w	r4, r4, #4194304	; 0x400000
70000dd4:	bf3c      	itt	cc
70000dd6:	f501 1180 	addcc.w	r1, r1, #1048576	; 0x100000
70000dda:	bd30      	popcc	{r4, r5, pc}
70000ddc:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000de0:	f045 41fe 	orr.w	r1, r5, #2130706432	; 0x7f000000
70000de4:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
70000de8:	f04f 0000 	mov.w	r0, #0
70000dec:	bd30      	pop	{r4, r5, pc}
70000dee:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70000df2:	bf1a      	itte	ne
70000df4:	4619      	movne	r1, r3
70000df6:	4610      	movne	r0, r2
70000df8:	ea7f 5c65 	mvnseq.w	ip, r5, asr #21
70000dfc:	bf1c      	itt	ne
70000dfe:	460b      	movne	r3, r1
70000e00:	4602      	movne	r2, r0
70000e02:	ea50 3401 	orrs.w	r4, r0, r1, lsl #12
70000e06:	bf06      	itte	eq
70000e08:	ea52 3503 	orrseq.w	r5, r2, r3, lsl #12
70000e0c:	ea91 0f03 	teqeq	r1, r3
70000e10:	f441 2100 	orrne.w	r1, r1, #524288	; 0x80000
70000e14:	bd30      	pop	{r4, r5, pc}
70000e16:	bf00      	nop

70000e18 <__aeabi_ui2d>:
70000e18:	f090 0f00 	teq	r0, #0
70000e1c:	bf04      	itt	eq
70000e1e:	2100      	moveq	r1, #0
70000e20:	4770      	bxeq	lr
70000e22:	b530      	push	{r4, r5, lr}
70000e24:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000e28:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000e2c:	f04f 0500 	mov.w	r5, #0
70000e30:	f04f 0100 	mov.w	r1, #0
70000e34:	e750      	b.n	70000cd8 <__adddf3+0x138>
70000e36:	bf00      	nop

70000e38 <__aeabi_i2d>:
70000e38:	f090 0f00 	teq	r0, #0
70000e3c:	bf04      	itt	eq
70000e3e:	2100      	moveq	r1, #0
70000e40:	4770      	bxeq	lr
70000e42:	b530      	push	{r4, r5, lr}
70000e44:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000e48:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000e4c:	f010 4500 	ands.w	r5, r0, #2147483648	; 0x80000000
70000e50:	bf48      	it	mi
70000e52:	4240      	negmi	r0, r0
70000e54:	f04f 0100 	mov.w	r1, #0
70000e58:	e73e      	b.n	70000cd8 <__adddf3+0x138>
70000e5a:	bf00      	nop

70000e5c <__aeabi_f2d>:
70000e5c:	0042      	lsls	r2, r0, #1
70000e5e:	ea4f 01e2 	mov.w	r1, r2, asr #3
70000e62:	ea4f 0131 	mov.w	r1, r1, rrx
70000e66:	ea4f 7002 	mov.w	r0, r2, lsl #28
70000e6a:	bf1f      	itttt	ne
70000e6c:	f012 437f 	andsne.w	r3, r2, #4278190080	; 0xff000000
70000e70:	f093 4f7f 	teqne	r3, #4278190080	; 0xff000000
70000e74:	f081 5160 	eorne.w	r1, r1, #939524096	; 0x38000000
70000e78:	4770      	bxne	lr
70000e7a:	f032 427f 	bics.w	r2, r2, #4278190080	; 0xff000000
70000e7e:	bf08      	it	eq
70000e80:	4770      	bxeq	lr
70000e82:	f093 4f7f 	teq	r3, #4278190080	; 0xff000000
70000e86:	bf04      	itt	eq
70000e88:	f441 2100 	orreq.w	r1, r1, #524288	; 0x80000
70000e8c:	4770      	bxeq	lr
70000e8e:	b530      	push	{r4, r5, lr}
70000e90:	f44f 7460 	mov.w	r4, #896	; 0x380
70000e94:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000e98:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
70000e9c:	e71c      	b.n	70000cd8 <__adddf3+0x138>
70000e9e:	bf00      	nop

70000ea0 <__aeabi_ul2d>:
70000ea0:	ea50 0201 	orrs.w	r2, r0, r1
70000ea4:	bf08      	it	eq
70000ea6:	4770      	bxeq	lr
70000ea8:	b530      	push	{r4, r5, lr}
70000eaa:	f04f 0500 	mov.w	r5, #0
70000eae:	e00a      	b.n	70000ec6 <__aeabi_l2d+0x16>

70000eb0 <__aeabi_l2d>:
70000eb0:	ea50 0201 	orrs.w	r2, r0, r1
70000eb4:	bf08      	it	eq
70000eb6:	4770      	bxeq	lr
70000eb8:	b530      	push	{r4, r5, lr}
70000eba:	f011 4500 	ands.w	r5, r1, #2147483648	; 0x80000000
70000ebe:	d502      	bpl.n	70000ec6 <__aeabi_l2d+0x16>
70000ec0:	4240      	negs	r0, r0
70000ec2:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000ec6:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000eca:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000ece:	ea5f 5c91 	movs.w	ip, r1, lsr #22
70000ed2:	f43f aed8 	beq.w	70000c86 <__adddf3+0xe6>
70000ed6:	f04f 0203 	mov.w	r2, #3
70000eda:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70000ede:	bf18      	it	ne
70000ee0:	3203      	addne	r2, #3
70000ee2:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70000ee6:	bf18      	it	ne
70000ee8:	3203      	addne	r2, #3
70000eea:	eb02 02dc 	add.w	r2, r2, ip, lsr #3
70000eee:	f1c2 0320 	rsb	r3, r2, #32
70000ef2:	fa00 fc03 	lsl.w	ip, r0, r3
70000ef6:	fa20 f002 	lsr.w	r0, r0, r2
70000efa:	fa01 fe03 	lsl.w	lr, r1, r3
70000efe:	ea40 000e 	orr.w	r0, r0, lr
70000f02:	fa21 f102 	lsr.w	r1, r1, r2
70000f06:	4414      	add	r4, r2
70000f08:	e6bd      	b.n	70000c86 <__adddf3+0xe6>
70000f0a:	bf00      	nop

70000f0c <__aeabi_d2iz>:
70000f0c:	ea4f 0241 	mov.w	r2, r1, lsl #1
70000f10:	f512 1200 	adds.w	r2, r2, #2097152	; 0x200000
70000f14:	d215      	bcs.n	70000f42 <__aeabi_d2iz+0x36>
70000f16:	d511      	bpl.n	70000f3c <__aeabi_d2iz+0x30>
70000f18:	f46f 7378 	mvn.w	r3, #992	; 0x3e0
70000f1c:	ebb3 5262 	subs.w	r2, r3, r2, asr #21
70000f20:	d912      	bls.n	70000f48 <__aeabi_d2iz+0x3c>
70000f22:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70000f26:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000f2a:	ea43 5350 	orr.w	r3, r3, r0, lsr #21
70000f2e:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000f32:	fa23 f002 	lsr.w	r0, r3, r2
70000f36:	bf18      	it	ne
70000f38:	4240      	negne	r0, r0
70000f3a:	4770      	bx	lr
70000f3c:	f04f 0000 	mov.w	r0, #0
70000f40:	4770      	bx	lr
70000f42:	ea50 3001 	orrs.w	r0, r0, r1, lsl #12
70000f46:	d105      	bne.n	70000f54 <__aeabi_d2iz+0x48>
70000f48:	f011 4000 	ands.w	r0, r1, #2147483648	; 0x80000000
70000f4c:	bf08      	it	eq
70000f4e:	f06f 4000 	mvneq.w	r0, #2147483648	; 0x80000000
70000f52:	4770      	bx	lr
70000f54:	f04f 0000 	mov.w	r0, #0
70000f58:	4770      	bx	lr
70000f5a:	bf00      	nop

70000f5c <__aeabi_d2f>:
70000f5c:	ea4f 0241 	mov.w	r2, r1, lsl #1
70000f60:	f1b2 43e0 	subs.w	r3, r2, #1879048192	; 0x70000000
70000f64:	bf24      	itt	cs
70000f66:	f5b3 1c00 	subscs.w	ip, r3, #2097152	; 0x200000
70000f6a:	f1dc 5cfe 	rsbscs	ip, ip, #532676608	; 0x1fc00000
70000f6e:	d90d      	bls.n	70000f8c <__aeabi_d2f+0x30>
70000f70:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000f74:	ea4f 02c0 	mov.w	r2, r0, lsl #3
70000f78:	ea4c 7050 	orr.w	r0, ip, r0, lsr #29
70000f7c:	f1b2 4f00 	cmp.w	r2, #2147483648	; 0x80000000
70000f80:	eb40 0083 	adc.w	r0, r0, r3, lsl #2
70000f84:	bf08      	it	eq
70000f86:	f020 0001 	biceq.w	r0, r0, #1
70000f8a:	4770      	bx	lr
70000f8c:	f011 4f80 	tst.w	r1, #1073741824	; 0x40000000
70000f90:	d121      	bne.n	70000fd6 <__aeabi_d2f+0x7a>
70000f92:	f113 7238 	adds.w	r2, r3, #48234496	; 0x2e00000
70000f96:	bfbc      	itt	lt
70000f98:	f001 4000 	andlt.w	r0, r1, #2147483648	; 0x80000000
70000f9c:	4770      	bxlt	lr
70000f9e:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70000fa2:	ea4f 5252 	mov.w	r2, r2, lsr #21
70000fa6:	f1c2 0218 	rsb	r2, r2, #24
70000faa:	f1c2 0c20 	rsb	ip, r2, #32
70000fae:	fa10 f30c 	lsls.w	r3, r0, ip
70000fb2:	fa20 f002 	lsr.w	r0, r0, r2
70000fb6:	bf18      	it	ne
70000fb8:	f040 0001 	orrne.w	r0, r0, #1
70000fbc:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70000fc0:	ea4f 23d3 	mov.w	r3, r3, lsr #11
70000fc4:	fa03 fc0c 	lsl.w	ip, r3, ip
70000fc8:	ea40 000c 	orr.w	r0, r0, ip
70000fcc:	fa23 f302 	lsr.w	r3, r3, r2
70000fd0:	ea4f 0343 	mov.w	r3, r3, lsl #1
70000fd4:	e7cc      	b.n	70000f70 <__aeabi_d2f+0x14>
70000fd6:	ea7f 5362 	mvns.w	r3, r2, asr #21
70000fda:	d107      	bne.n	70000fec <__aeabi_d2f+0x90>
70000fdc:	ea50 3301 	orrs.w	r3, r0, r1, lsl #12
70000fe0:	bf1e      	ittt	ne
70000fe2:	f04f 40fe 	movne.w	r0, #2130706432	; 0x7f000000
70000fe6:	f440 0040 	orrne.w	r0, r0, #12582912	; 0xc00000
70000fea:	4770      	bxne	lr
70000fec:	f001 4000 	and.w	r0, r1, #2147483648	; 0x80000000
70000ff0:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000ff4:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000ff8:	4770      	bx	lr
70000ffa:	bf00      	nop

70000ffc <__aeabi_frsub>:
70000ffc:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70001000:	e002      	b.n	70001008 <__addsf3>
70001002:	bf00      	nop

70001004 <__aeabi_fsub>:
70001004:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

70001008 <__addsf3>:
70001008:	0042      	lsls	r2, r0, #1
7000100a:	bf1f      	itttt	ne
7000100c:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70001010:	ea92 0f03 	teqne	r2, r3
70001014:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
70001018:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
7000101c:	d06a      	beq.n	700010f4 <__addsf3+0xec>
7000101e:	ea4f 6212 	mov.w	r2, r2, lsr #24
70001022:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
70001026:	bfc1      	itttt	gt
70001028:	18d2      	addgt	r2, r2, r3
7000102a:	4041      	eorgt	r1, r0
7000102c:	4048      	eorgt	r0, r1
7000102e:	4041      	eorgt	r1, r0
70001030:	bfb8      	it	lt
70001032:	425b      	neglt	r3, r3
70001034:	2b19      	cmp	r3, #25
70001036:	bf88      	it	hi
70001038:	4770      	bxhi	lr
7000103a:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
7000103e:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001042:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
70001046:	bf18      	it	ne
70001048:	4240      	negne	r0, r0
7000104a:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
7000104e:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
70001052:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
70001056:	bf18      	it	ne
70001058:	4249      	negne	r1, r1
7000105a:	ea92 0f03 	teq	r2, r3
7000105e:	d03f      	beq.n	700010e0 <__addsf3+0xd8>
70001060:	f1a2 0201 	sub.w	r2, r2, #1
70001064:	fa41 fc03 	asr.w	ip, r1, r3
70001068:	eb10 000c 	adds.w	r0, r0, ip
7000106c:	f1c3 0320 	rsb	r3, r3, #32
70001070:	fa01 f103 	lsl.w	r1, r1, r3
70001074:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70001078:	d502      	bpl.n	70001080 <__addsf3+0x78>
7000107a:	4249      	negs	r1, r1
7000107c:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70001080:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70001084:	d313      	bcc.n	700010ae <__addsf3+0xa6>
70001086:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
7000108a:	d306      	bcc.n	7000109a <__addsf3+0x92>
7000108c:	0840      	lsrs	r0, r0, #1
7000108e:	ea4f 0131 	mov.w	r1, r1, rrx
70001092:	f102 0201 	add.w	r2, r2, #1
70001096:	2afe      	cmp	r2, #254	; 0xfe
70001098:	d251      	bcs.n	7000113e <__addsf3+0x136>
7000109a:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
7000109e:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
700010a2:	bf08      	it	eq
700010a4:	f020 0001 	biceq.w	r0, r0, #1
700010a8:	ea40 0003 	orr.w	r0, r0, r3
700010ac:	4770      	bx	lr
700010ae:	0049      	lsls	r1, r1, #1
700010b0:	eb40 0000 	adc.w	r0, r0, r0
700010b4:	3a01      	subs	r2, #1
700010b6:	bf28      	it	cs
700010b8:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
700010bc:	d2ed      	bcs.n	7000109a <__addsf3+0x92>
700010be:	fab0 fc80 	clz	ip, r0
700010c2:	f1ac 0c08 	sub.w	ip, ip, #8
700010c6:	ebb2 020c 	subs.w	r2, r2, ip
700010ca:	fa00 f00c 	lsl.w	r0, r0, ip
700010ce:	bfaa      	itet	ge
700010d0:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
700010d4:	4252      	neglt	r2, r2
700010d6:	4318      	orrge	r0, r3
700010d8:	bfbc      	itt	lt
700010da:	40d0      	lsrlt	r0, r2
700010dc:	4318      	orrlt	r0, r3
700010de:	4770      	bx	lr
700010e0:	f092 0f00 	teq	r2, #0
700010e4:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
700010e8:	bf06      	itte	eq
700010ea:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
700010ee:	3201      	addeq	r2, #1
700010f0:	3b01      	subne	r3, #1
700010f2:	e7b5      	b.n	70001060 <__addsf3+0x58>
700010f4:	ea4f 0341 	mov.w	r3, r1, lsl #1
700010f8:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700010fc:	bf18      	it	ne
700010fe:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70001102:	d021      	beq.n	70001148 <__addsf3+0x140>
70001104:	ea92 0f03 	teq	r2, r3
70001108:	d004      	beq.n	70001114 <__addsf3+0x10c>
7000110a:	f092 0f00 	teq	r2, #0
7000110e:	bf08      	it	eq
70001110:	4608      	moveq	r0, r1
70001112:	4770      	bx	lr
70001114:	ea90 0f01 	teq	r0, r1
70001118:	bf1c      	itt	ne
7000111a:	2000      	movne	r0, #0
7000111c:	4770      	bxne	lr
7000111e:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
70001122:	d104      	bne.n	7000112e <__addsf3+0x126>
70001124:	0040      	lsls	r0, r0, #1
70001126:	bf28      	it	cs
70001128:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
7000112c:	4770      	bx	lr
7000112e:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
70001132:	bf3c      	itt	cc
70001134:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
70001138:	4770      	bxcc	lr
7000113a:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
7000113e:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
70001142:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001146:	4770      	bx	lr
70001148:	ea7f 6222 	mvns.w	r2, r2, asr #24
7000114c:	bf16      	itet	ne
7000114e:	4608      	movne	r0, r1
70001150:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70001154:	4601      	movne	r1, r0
70001156:	0242      	lsls	r2, r0, #9
70001158:	bf06      	itte	eq
7000115a:	ea5f 2341 	movseq.w	r3, r1, lsl #9
7000115e:	ea90 0f01 	teqeq	r0, r1
70001162:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
70001166:	4770      	bx	lr

70001168 <__aeabi_ui2f>:
70001168:	f04f 0300 	mov.w	r3, #0
7000116c:	e004      	b.n	70001178 <__aeabi_i2f+0x8>
7000116e:	bf00      	nop

70001170 <__aeabi_i2f>:
70001170:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70001174:	bf48      	it	mi
70001176:	4240      	negmi	r0, r0
70001178:	ea5f 0c00 	movs.w	ip, r0
7000117c:	bf08      	it	eq
7000117e:	4770      	bxeq	lr
70001180:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70001184:	4601      	mov	r1, r0
70001186:	f04f 0000 	mov.w	r0, #0
7000118a:	e01c      	b.n	700011c6 <__aeabi_l2f+0x2a>

7000118c <__aeabi_ul2f>:
7000118c:	ea50 0201 	orrs.w	r2, r0, r1
70001190:	bf08      	it	eq
70001192:	4770      	bxeq	lr
70001194:	f04f 0300 	mov.w	r3, #0
70001198:	e00a      	b.n	700011b0 <__aeabi_l2f+0x14>
7000119a:	bf00      	nop

7000119c <__aeabi_l2f>:
7000119c:	ea50 0201 	orrs.w	r2, r0, r1
700011a0:	bf08      	it	eq
700011a2:	4770      	bxeq	lr
700011a4:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
700011a8:	d502      	bpl.n	700011b0 <__aeabi_l2f+0x14>
700011aa:	4240      	negs	r0, r0
700011ac:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
700011b0:	ea5f 0c01 	movs.w	ip, r1
700011b4:	bf02      	ittt	eq
700011b6:	4684      	moveq	ip, r0
700011b8:	4601      	moveq	r1, r0
700011ba:	2000      	moveq	r0, #0
700011bc:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
700011c0:	bf08      	it	eq
700011c2:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
700011c6:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
700011ca:	fabc f28c 	clz	r2, ip
700011ce:	3a08      	subs	r2, #8
700011d0:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
700011d4:	db10      	blt.n	700011f8 <__aeabi_l2f+0x5c>
700011d6:	fa01 fc02 	lsl.w	ip, r1, r2
700011da:	4463      	add	r3, ip
700011dc:	fa00 fc02 	lsl.w	ip, r0, r2
700011e0:	f1c2 0220 	rsb	r2, r2, #32
700011e4:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
700011e8:	fa20 f202 	lsr.w	r2, r0, r2
700011ec:	eb43 0002 	adc.w	r0, r3, r2
700011f0:	bf08      	it	eq
700011f2:	f020 0001 	biceq.w	r0, r0, #1
700011f6:	4770      	bx	lr
700011f8:	f102 0220 	add.w	r2, r2, #32
700011fc:	fa01 fc02 	lsl.w	ip, r1, r2
70001200:	f1c2 0220 	rsb	r2, r2, #32
70001204:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
70001208:	fa21 f202 	lsr.w	r2, r1, r2
7000120c:	eb43 0002 	adc.w	r0, r3, r2
70001210:	bf08      	it	eq
70001212:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70001216:	4770      	bx	lr

70001218 <__aeabi_fmul>:
70001218:	f04f 0cff 	mov.w	ip, #255	; 0xff
7000121c:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70001220:	bf1e      	ittt	ne
70001222:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70001226:	ea92 0f0c 	teqne	r2, ip
7000122a:	ea93 0f0c 	teqne	r3, ip
7000122e:	d06f      	beq.n	70001310 <__aeabi_fmul+0xf8>
70001230:	441a      	add	r2, r3
70001232:	ea80 0c01 	eor.w	ip, r0, r1
70001236:	0240      	lsls	r0, r0, #9
70001238:	bf18      	it	ne
7000123a:	ea5f 2141 	movsne.w	r1, r1, lsl #9
7000123e:	d01e      	beq.n	7000127e <__aeabi_fmul+0x66>
70001240:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70001244:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70001248:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
7000124c:	fba0 3101 	umull	r3, r1, r0, r1
70001250:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70001254:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70001258:	bf3e      	ittt	cc
7000125a:	0049      	lslcc	r1, r1, #1
7000125c:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70001260:	005b      	lslcc	r3, r3, #1
70001262:	ea40 0001 	orr.w	r0, r0, r1
70001266:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
7000126a:	2afd      	cmp	r2, #253	; 0xfd
7000126c:	d81d      	bhi.n	700012aa <__aeabi_fmul+0x92>
7000126e:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70001272:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70001276:	bf08      	it	eq
70001278:	f020 0001 	biceq.w	r0, r0, #1
7000127c:	4770      	bx	lr
7000127e:	f090 0f00 	teq	r0, #0
70001282:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70001286:	bf08      	it	eq
70001288:	0249      	lsleq	r1, r1, #9
7000128a:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
7000128e:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70001292:	3a7f      	subs	r2, #127	; 0x7f
70001294:	bfc2      	ittt	gt
70001296:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
7000129a:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
7000129e:	4770      	bxgt	lr
700012a0:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700012a4:	f04f 0300 	mov.w	r3, #0
700012a8:	3a01      	subs	r2, #1
700012aa:	dc5d      	bgt.n	70001368 <__aeabi_fmul+0x150>
700012ac:	f112 0f19 	cmn.w	r2, #25
700012b0:	bfdc      	itt	le
700012b2:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
700012b6:	4770      	bxle	lr
700012b8:	f1c2 0200 	rsb	r2, r2, #0
700012bc:	0041      	lsls	r1, r0, #1
700012be:	fa21 f102 	lsr.w	r1, r1, r2
700012c2:	f1c2 0220 	rsb	r2, r2, #32
700012c6:	fa00 fc02 	lsl.w	ip, r0, r2
700012ca:	ea5f 0031 	movs.w	r0, r1, rrx
700012ce:	f140 0000 	adc.w	r0, r0, #0
700012d2:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
700012d6:	bf08      	it	eq
700012d8:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
700012dc:	4770      	bx	lr
700012de:	f092 0f00 	teq	r2, #0
700012e2:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
700012e6:	bf02      	ittt	eq
700012e8:	0040      	lsleq	r0, r0, #1
700012ea:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
700012ee:	3a01      	subeq	r2, #1
700012f0:	d0f9      	beq.n	700012e6 <__aeabi_fmul+0xce>
700012f2:	ea40 000c 	orr.w	r0, r0, ip
700012f6:	f093 0f00 	teq	r3, #0
700012fa:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
700012fe:	bf02      	ittt	eq
70001300:	0049      	lsleq	r1, r1, #1
70001302:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70001306:	3b01      	subeq	r3, #1
70001308:	d0f9      	beq.n	700012fe <__aeabi_fmul+0xe6>
7000130a:	ea41 010c 	orr.w	r1, r1, ip
7000130e:	e78f      	b.n	70001230 <__aeabi_fmul+0x18>
70001310:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70001314:	ea92 0f0c 	teq	r2, ip
70001318:	bf18      	it	ne
7000131a:	ea93 0f0c 	teqne	r3, ip
7000131e:	d00a      	beq.n	70001336 <__aeabi_fmul+0x11e>
70001320:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70001324:	bf18      	it	ne
70001326:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
7000132a:	d1d8      	bne.n	700012de <__aeabi_fmul+0xc6>
7000132c:	ea80 0001 	eor.w	r0, r0, r1
70001330:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70001334:	4770      	bx	lr
70001336:	f090 0f00 	teq	r0, #0
7000133a:	bf17      	itett	ne
7000133c:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70001340:	4608      	moveq	r0, r1
70001342:	f091 0f00 	teqne	r1, #0
70001346:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
7000134a:	d014      	beq.n	70001376 <__aeabi_fmul+0x15e>
7000134c:	ea92 0f0c 	teq	r2, ip
70001350:	d101      	bne.n	70001356 <__aeabi_fmul+0x13e>
70001352:	0242      	lsls	r2, r0, #9
70001354:	d10f      	bne.n	70001376 <__aeabi_fmul+0x15e>
70001356:	ea93 0f0c 	teq	r3, ip
7000135a:	d103      	bne.n	70001364 <__aeabi_fmul+0x14c>
7000135c:	024b      	lsls	r3, r1, #9
7000135e:	bf18      	it	ne
70001360:	4608      	movne	r0, r1
70001362:	d108      	bne.n	70001376 <__aeabi_fmul+0x15e>
70001364:	ea80 0001 	eor.w	r0, r0, r1
70001368:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
7000136c:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70001370:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001374:	4770      	bx	lr
70001376:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
7000137a:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
7000137e:	4770      	bx	lr

70001380 <__aeabi_fdiv>:
70001380:	f04f 0cff 	mov.w	ip, #255	; 0xff
70001384:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70001388:	bf1e      	ittt	ne
7000138a:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
7000138e:	ea92 0f0c 	teqne	r2, ip
70001392:	ea93 0f0c 	teqne	r3, ip
70001396:	d069      	beq.n	7000146c <__aeabi_fdiv+0xec>
70001398:	eba2 0203 	sub.w	r2, r2, r3
7000139c:	ea80 0c01 	eor.w	ip, r0, r1
700013a0:	0249      	lsls	r1, r1, #9
700013a2:	ea4f 2040 	mov.w	r0, r0, lsl #9
700013a6:	d037      	beq.n	70001418 <__aeabi_fdiv+0x98>
700013a8:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
700013ac:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
700013b0:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
700013b4:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
700013b8:	428b      	cmp	r3, r1
700013ba:	bf38      	it	cc
700013bc:	005b      	lslcc	r3, r3, #1
700013be:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
700013c2:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
700013c6:	428b      	cmp	r3, r1
700013c8:	bf24      	itt	cs
700013ca:	1a5b      	subcs	r3, r3, r1
700013cc:	ea40 000c 	orrcs.w	r0, r0, ip
700013d0:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
700013d4:	bf24      	itt	cs
700013d6:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
700013da:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
700013de:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
700013e2:	bf24      	itt	cs
700013e4:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
700013e8:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
700013ec:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
700013f0:	bf24      	itt	cs
700013f2:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
700013f6:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
700013fa:	011b      	lsls	r3, r3, #4
700013fc:	bf18      	it	ne
700013fe:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70001402:	d1e0      	bne.n	700013c6 <__aeabi_fdiv+0x46>
70001404:	2afd      	cmp	r2, #253	; 0xfd
70001406:	f63f af50 	bhi.w	700012aa <__aeabi_fmul+0x92>
7000140a:	428b      	cmp	r3, r1
7000140c:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70001410:	bf08      	it	eq
70001412:	f020 0001 	biceq.w	r0, r0, #1
70001416:	4770      	bx	lr
70001418:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
7000141c:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70001420:	327f      	adds	r2, #127	; 0x7f
70001422:	bfc2      	ittt	gt
70001424:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70001428:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
7000142c:	4770      	bxgt	lr
7000142e:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70001432:	f04f 0300 	mov.w	r3, #0
70001436:	3a01      	subs	r2, #1
70001438:	e737      	b.n	700012aa <__aeabi_fmul+0x92>
7000143a:	f092 0f00 	teq	r2, #0
7000143e:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70001442:	bf02      	ittt	eq
70001444:	0040      	lsleq	r0, r0, #1
70001446:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
7000144a:	3a01      	subeq	r2, #1
7000144c:	d0f9      	beq.n	70001442 <__aeabi_fdiv+0xc2>
7000144e:	ea40 000c 	orr.w	r0, r0, ip
70001452:	f093 0f00 	teq	r3, #0
70001456:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
7000145a:	bf02      	ittt	eq
7000145c:	0049      	lsleq	r1, r1, #1
7000145e:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70001462:	3b01      	subeq	r3, #1
70001464:	d0f9      	beq.n	7000145a <__aeabi_fdiv+0xda>
70001466:	ea41 010c 	orr.w	r1, r1, ip
7000146a:	e795      	b.n	70001398 <__aeabi_fdiv+0x18>
7000146c:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70001470:	ea92 0f0c 	teq	r2, ip
70001474:	d108      	bne.n	70001488 <__aeabi_fdiv+0x108>
70001476:	0242      	lsls	r2, r0, #9
70001478:	f47f af7d 	bne.w	70001376 <__aeabi_fmul+0x15e>
7000147c:	ea93 0f0c 	teq	r3, ip
70001480:	f47f af70 	bne.w	70001364 <__aeabi_fmul+0x14c>
70001484:	4608      	mov	r0, r1
70001486:	e776      	b.n	70001376 <__aeabi_fmul+0x15e>
70001488:	ea93 0f0c 	teq	r3, ip
7000148c:	d104      	bne.n	70001498 <__aeabi_fdiv+0x118>
7000148e:	024b      	lsls	r3, r1, #9
70001490:	f43f af4c 	beq.w	7000132c <__aeabi_fmul+0x114>
70001494:	4608      	mov	r0, r1
70001496:	e76e      	b.n	70001376 <__aeabi_fmul+0x15e>
70001498:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
7000149c:	bf18      	it	ne
7000149e:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
700014a2:	d1ca      	bne.n	7000143a <__aeabi_fdiv+0xba>
700014a4:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
700014a8:	f47f af5c 	bne.w	70001364 <__aeabi_fmul+0x14c>
700014ac:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
700014b0:	f47f af3c 	bne.w	7000132c <__aeabi_fmul+0x114>
700014b4:	e75f      	b.n	70001376 <__aeabi_fmul+0x15e>
700014b6:	bf00      	nop

700014b8 <__gesf2>:
700014b8:	f04f 3cff 	mov.w	ip, #4294967295
700014bc:	e006      	b.n	700014cc <__cmpsf2+0x4>
700014be:	bf00      	nop

700014c0 <__lesf2>:
700014c0:	f04f 0c01 	mov.w	ip, #1
700014c4:	e002      	b.n	700014cc <__cmpsf2+0x4>
700014c6:	bf00      	nop

700014c8 <__cmpsf2>:
700014c8:	f04f 0c01 	mov.w	ip, #1
700014cc:	f84d cd04 	str.w	ip, [sp, #-4]!
700014d0:	ea4f 0240 	mov.w	r2, r0, lsl #1
700014d4:	ea4f 0341 	mov.w	r3, r1, lsl #1
700014d8:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700014dc:	bf18      	it	ne
700014de:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700014e2:	d011      	beq.n	70001508 <__cmpsf2+0x40>
700014e4:	b001      	add	sp, #4
700014e6:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
700014ea:	bf18      	it	ne
700014ec:	ea90 0f01 	teqne	r0, r1
700014f0:	bf58      	it	pl
700014f2:	ebb2 0003 	subspl.w	r0, r2, r3
700014f6:	bf88      	it	hi
700014f8:	17c8      	asrhi	r0, r1, #31
700014fa:	bf38      	it	cc
700014fc:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70001500:	bf18      	it	ne
70001502:	f040 0001 	orrne.w	r0, r0, #1
70001506:	4770      	bx	lr
70001508:	ea7f 6c22 	mvns.w	ip, r2, asr #24
7000150c:	d102      	bne.n	70001514 <__cmpsf2+0x4c>
7000150e:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70001512:	d105      	bne.n	70001520 <__cmpsf2+0x58>
70001514:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70001518:	d1e4      	bne.n	700014e4 <__cmpsf2+0x1c>
7000151a:	ea5f 2c41 	movs.w	ip, r1, lsl #9
7000151e:	d0e1      	beq.n	700014e4 <__cmpsf2+0x1c>
70001520:	f85d 0b04 	ldr.w	r0, [sp], #4
70001524:	4770      	bx	lr
70001526:	bf00      	nop

70001528 <__aeabi_cfrcmple>:
70001528:	4684      	mov	ip, r0
7000152a:	4608      	mov	r0, r1
7000152c:	4661      	mov	r1, ip
7000152e:	e7ff      	b.n	70001530 <__aeabi_cfcmpeq>

70001530 <__aeabi_cfcmpeq>:
70001530:	b50f      	push	{r0, r1, r2, r3, lr}
70001532:	f7ff ffc9 	bl	700014c8 <__cmpsf2>
70001536:	2800      	cmp	r0, #0
70001538:	bf48      	it	mi
7000153a:	f110 0f00 	cmnmi.w	r0, #0
7000153e:	bd0f      	pop	{r0, r1, r2, r3, pc}

70001540 <__aeabi_fcmpeq>:
70001540:	f84d ed08 	str.w	lr, [sp, #-8]!
70001544:	f7ff fff4 	bl	70001530 <__aeabi_cfcmpeq>
70001548:	bf0c      	ite	eq
7000154a:	2001      	moveq	r0, #1
7000154c:	2000      	movne	r0, #0
7000154e:	f85d fb08 	ldr.w	pc, [sp], #8
70001552:	bf00      	nop

70001554 <__aeabi_fcmplt>:
70001554:	f84d ed08 	str.w	lr, [sp, #-8]!
70001558:	f7ff ffea 	bl	70001530 <__aeabi_cfcmpeq>
7000155c:	bf34      	ite	cc
7000155e:	2001      	movcc	r0, #1
70001560:	2000      	movcs	r0, #0
70001562:	f85d fb08 	ldr.w	pc, [sp], #8
70001566:	bf00      	nop

70001568 <__aeabi_fcmple>:
70001568:	f84d ed08 	str.w	lr, [sp, #-8]!
7000156c:	f7ff ffe0 	bl	70001530 <__aeabi_cfcmpeq>
70001570:	bf94      	ite	ls
70001572:	2001      	movls	r0, #1
70001574:	2000      	movhi	r0, #0
70001576:	f85d fb08 	ldr.w	pc, [sp], #8
7000157a:	bf00      	nop

7000157c <__aeabi_fcmpge>:
7000157c:	f84d ed08 	str.w	lr, [sp, #-8]!
70001580:	f7ff ffd2 	bl	70001528 <__aeabi_cfrcmple>
70001584:	bf94      	ite	ls
70001586:	2001      	movls	r0, #1
70001588:	2000      	movhi	r0, #0
7000158a:	f85d fb08 	ldr.w	pc, [sp], #8
7000158e:	bf00      	nop

70001590 <__aeabi_fcmpgt>:
70001590:	f84d ed08 	str.w	lr, [sp, #-8]!
70001594:	f7ff ffc8 	bl	70001528 <__aeabi_cfrcmple>
70001598:	bf34      	ite	cc
7000159a:	2001      	movcc	r0, #1
7000159c:	2000      	movcs	r0, #0
7000159e:	f85d fb08 	ldr.w	pc, [sp], #8
700015a2:	bf00      	nop

700015a4 <__aeabi_f2uiz>:
700015a4:	0042      	lsls	r2, r0, #1
700015a6:	d20e      	bcs.n	700015c6 <__aeabi_f2uiz+0x22>
700015a8:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
700015ac:	d30b      	bcc.n	700015c6 <__aeabi_f2uiz+0x22>
700015ae:	f04f 039e 	mov.w	r3, #158	; 0x9e
700015b2:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
700015b6:	d409      	bmi.n	700015cc <__aeabi_f2uiz+0x28>
700015b8:	ea4f 2300 	mov.w	r3, r0, lsl #8
700015bc:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
700015c0:	fa23 f002 	lsr.w	r0, r3, r2
700015c4:	4770      	bx	lr
700015c6:	f04f 0000 	mov.w	r0, #0
700015ca:	4770      	bx	lr
700015cc:	f112 0f61 	cmn.w	r2, #97	; 0x61
700015d0:	d101      	bne.n	700015d6 <__aeabi_f2uiz+0x32>
700015d2:	0242      	lsls	r2, r0, #9
700015d4:	d102      	bne.n	700015dc <__aeabi_f2uiz+0x38>
700015d6:	f04f 30ff 	mov.w	r0, #4294967295
700015da:	4770      	bx	lr
700015dc:	f04f 0000 	mov.w	r0, #0
700015e0:	4770      	bx	lr
700015e2:	bf00      	nop
