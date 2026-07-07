
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	b1 06 00 70 ad 02 00 70                             ...p...p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

70000060 <g_gc4653_i2c_init_regs>:
70000060:	fe 03 f0 00 fe 03 00 00 17 03 00 00 20 03 77 00     ............ .w.
70000070:	24 03 c8 00 25 03 06 00 26 03 6c 00 27 03 03 00     $...%...&.l.'...
70000080:	34 03 40 00 36 03 6c 00 37 03 82 00 15 03 25 00     4.@.6.l.7.....%.
70000090:	1c 03 c6 00 87 02 18 00 84 00 00 00 87 00 50 00     ..............P.
700000a0:	9d 02 08 00 90 02 00 00 40 03 0b 00 41 03 b8 00     ........@...A...
700000b0:	45 03 06 00 4b 03 b0 00 52 03 08 00 54 03 08 00     E...K...R...T...
700000c0:	d1 02 e0 00 23 02 f2 00 38 02 a4 00 ce 02 7f 00     ....#...8.......
700000d0:	32 02 c4 00 d3 02 05 00 43 02 06 00 ee 02 30 00     2.......C.....0.
700000e0:	6f 02 70 00 57 02 09 00 11 02 02 00 19 02 09 00     o.p.W...........
700000f0:	3f 02 2d 00 18 05 00 00 19 05 01 00 15 05 08 00     ?.-.............
70000100:	d9 02 3f 00 da 02 02 00 db 02 e8 00 e6 02 20 00     ..?........... .
70000110:	1b 02 10 00 52 02 22 00 4e 02 22 00 c4 02 01 00     ....R.".N.".....
70000120:	1d 02 17 00 4a 02 01 00 ca 02 02 00 62 02 10 00     ....J.......b...
70000130:	9a 02 20 00 1c 02 0e 00 98 02 03 00 9c 02 00 00     .. .............
70000140:	7e 02 14 00 c2 02 10 00 40 05 20 00 46 05 01 00     ~.......@. .F...
70000150:	48 05 01 00 44 05 01 00 42 02 1b 00 c0 02 1b 00     H...D...B.......
70000160:	c3 02 20 00 e4 02 10 00 2e 02 00 00 7b 02 3f 00     .. .........{.?.
70000170:	69 02 0f 00 d2 02 40 00 7c 02 08 00 3a 02 2e 00     i.....@.|...:...
70000180:	45 02 ce 00 30 05 20 00 31 05 02 00 28 02 50 00     E...0. .1...(.P.
70000190:	ab 02 00 00 50 02 00 00 21 02 50 00 ac 02 00 00     ....P...!.P.....
700001a0:	a5 02 02 00 60 02 0b 00 16 02 04 00 99 02 1c 00     ....`...........
700001b0:	bb 02 0d 00 a3 02 02 00 a4 02 02 00 1e 02 02 00     ................
700001c0:	4f 02 08 00 8c 02 08 00 32 05 3f 00 33 05 02 00     O.......2.?.3...
700001d0:	77 02 c0 00 76 02 c0 00 39 02 c0 00 02 02 05 00     w...v...9.......
700001e0:	03 02 d0 00 05 02 c0 00 b0 02 68 00 02 00 a9 00     ..........h.....
700001f0:	04 00 01 00 1a 02 98 00 66 02 a0 00 20 00 01 00     ........f... ...
70000200:	21 00 03 00 22 00 00 00 23 00 04 00 4c 03 0a 00     !..."...#...L...
70000210:	4d 03 08 00 4e 03 05 00 4f 03 a8 00 42 03 06 00     M...N...O...B...
70000220:	43 03 40 00 fe 03 10 00 fe 03 00 00 06 01 78 00     C.@...........x.
70000230:	08 01 0c 00 14 01 01 00 15 01 12 00 80 01 46 00     ..............F.
70000240:	81 01 30 00 82 01 05 00 85 01 01 00 fe 03 10 00     ..0.............
70000250:	fe 03 00 00 00 01 09 00 0f 00 00 00 80 00 02 00     ................
70000260:	97 00 0a 00 98 00 10 00 99 00 05 00 9a 00 b0 00     ................
70000270:	17 03 08 00 67 0a 80 00 70 0a 03 00 82 0a 00 00     ....g...p.......
70000280:	83 0a 10 00 80 0a 2b 00 be 05 00 00 a9 05 01 00     ......+.........
70000290:	13 03 80 00 be 05 01 00 17 03 00 00 67 0a 00 00     ............g...

700002a0 <real_slave_addr>:
700002a0:	29 00 00 00                                         )...

700002a4 <slave_addr_list>:
700002a4:	29 00 00 00 10 00 00 00                             ).......

700002ac <rts_isp_set_voe_ops>:
700002ac:	4b01      	ldr	r3, [pc, #4]	; (700002b4 <rts_isp_set_voe_ops+0x8>)
700002ae:	6018      	str	r0, [r3, #0]
700002b0:	4770      	bx	lr
700002b2:	bf00      	nop
700002b4:	70000048 	.word	0x70000048

700002b8 <isp_driver_is_fpga>:
700002b8:	2000      	movs	r0, #0
700002ba:	4770      	bx	lr

700002bc <gc4653_get_info>:
700002bc:	b530      	push	{r4, r5, lr}
700002be:	2800      	cmp	r0, #0
700002c0:	d14f      	bne.n	70000362 <gc4653_get_info+0xa6>
700002c2:	2900      	cmp	r1, #0
700002c4:	d04d      	beq.n	70000362 <gc4653_get_info+0xa6>
700002c6:	f44f 6220 	mov.w	r2, #2560	; 0xa00
700002ca:	f44f 63b4 	mov.w	r3, #1440	; 0x5a0
700002ce:	f44f 747a 	mov.w	r4, #1000	; 0x3e8
700002d2:	4d25      	ldr	r5, [pc, #148]	; (70000368 <gc4653_get_info+0xac>)
700002d4:	7108      	strb	r0, [r1, #4]
700002d6:	f8c1 40ac 	str.w	r4, [r1, #172]	; 0xac
700002da:	f8c1 00a8 	str.w	r0, [r1, #168]	; 0xa8
700002de:	f881 00c8 	strb.w	r0, [r1, #200]	; 0xc8
700002e2:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
700002e6:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
700002ea:	f8c1 02dc 	str.w	r0, [r1, #732]	; 0x2dc
700002ee:	e9c1 2302 	strd	r2, r3, [r1, #8]
700002f2:	4b1e      	ldr	r3, [pc, #120]	; (7000036c <gc4653_get_info+0xb0>)
700002f4:	4a1e      	ldr	r2, [pc, #120]	; (70000370 <gc4653_get_info+0xb4>)
700002f6:	610b      	str	r3, [r1, #16]
700002f8:	2301      	movs	r3, #1
700002fa:	6812      	ldr	r2, [r2, #0]
700002fc:	600b      	str	r3, [r1, #0]
700002fe:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
70000302:	4a1c      	ldr	r2, [pc, #112]	; (70000374 <gc4653_get_info+0xb8>)
70000304:	f881 3098 	strb.w	r3, [r1, #152]	; 0x98
70000308:	7812      	ldrb	r2, [r2, #0]
7000030a:	f881 30bc 	strb.w	r3, [r1, #188]	; 0xbc
7000030e:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
70000312:	2203      	movs	r2, #3
70000314:	e9c1 3430 	strd	r3, r4, [r1, #192]	; 0xc0
70000318:	e9c1 3433 	strd	r3, r4, [r1, #204]	; 0xcc
7000031c:	e9c1 542d 	strd	r5, r4, [r1, #180]	; 0xb4
70000320:	f44f 7481 	mov.w	r4, #258	; 0x102
70000324:	f881 20a4 	strb.w	r2, [r1, #164]	; 0xa4
70000328:	f881 20b0 	strb.w	r2, [r1, #176]	; 0xb0
7000032c:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
70000330:	2406      	movs	r4, #6
70000332:	f8c1 4088 	str.w	r4, [r1, #136]	; 0x88
70000336:	f242 7410 	movw	r4, #10000	; 0x2710
7000033a:	e9c1 0024 	strd	r0, r0, [r1, #144]	; 0x90
7000033e:	e9c1 0027 	strd	r0, r0, [r1, #156]	; 0x9c
70000342:	f8c1 42e0 	str.w	r4, [r1, #736]	; 0x2e0
70000346:	f881 32e4 	strb.w	r3, [r1, #740]	; 0x2e4
7000034a:	4b0b      	ldr	r3, [pc, #44]	; (70000378 <gc4653_get_info+0xbc>)
7000034c:	f8c1 02e8 	str.w	r0, [r1, #744]	; 0x2e8
70000350:	f8c1 32ec 	str.w	r3, [r1, #748]	; 0x2ec
70000354:	f881 22f0 	strb.w	r2, [r1, #752]	; 0x2f0
70000358:	f8c1 22d4 	str.w	r2, [r1, #724]	; 0x2d4
7000035c:	e9c1 04bd 	strd	r0, r4, [r1, #756]	; 0x2f4
70000360:	bd30      	pop	{r4, r5, pc}
70000362:	f06f 0015 	mvn.w	r0, #21
70000366:	e7fb      	b.n	70000360 <gc4653_get_info+0xa4>
70000368:	016e3600 	.word	0x016e3600
7000036c:	41f00000 	.word	0x41f00000
70000370:	700002a0 	.word	0x700002a0
70000374:	7000004c 	.word	0x7000004c
70000378:	000186a0 	.word	0x000186a0

7000037c <gc4653_get_init_info>:
7000037c:	b570      	push	{r4, r5, r6, lr}
7000037e:	4614      	mov	r4, r2
70000380:	4605      	mov	r5, r0
70000382:	b110      	cbz	r0, 7000038a <gc4653_get_init_info+0xe>
70000384:	f06f 0015 	mvn.w	r0, #21
70000388:	bd70      	pop	{r4, r5, r6, pc}
7000038a:	2a00      	cmp	r2, #0
7000038c:	d0fa      	beq.n	70000384 <gc4653_get_init_info+0x8>
7000038e:	780b      	ldrb	r3, [r1, #0]
70000390:	4e1c      	ldr	r6, [pc, #112]	; (70000404 <gc4653_get_init_info+0x88>)
70000392:	68c8      	ldr	r0, [r1, #12]
70000394:	7033      	strb	r3, [r6, #0]
70000396:	f000 fdb7 	bl	70000f08 <__aeabi_f2uiz>
7000039a:	b280      	uxth	r0, r0
7000039c:	f000 fb9a 	bl	70000ad4 <__aeabi_i2f>
700003a0:	4919      	ldr	r1, [pc, #100]	; (70000408 <gc4653_get_init_info+0x8c>)
700003a2:	f000 fd7f 	bl	70000ea4 <__aeabi_fcmpeq>
700003a6:	2800      	cmp	r0, #0
700003a8:	d0ec      	beq.n	70000384 <gc4653_get_init_info+0x8>
700003aa:	4b18      	ldr	r3, [pc, #96]	; (7000040c <gc4653_get_init_info+0x90>)
700003ac:	f640 2208 	movw	r2, #2568	; 0xa08
700003b0:	f44f 6134 	mov.w	r1, #2880	; 0xb40
700003b4:	60a5      	str	r5, [r4, #8]
700003b6:	6063      	str	r3, [r4, #4]
700003b8:	2390      	movs	r3, #144	; 0x90
700003ba:	4628      	mov	r0, r5
700003bc:	6023      	str	r3, [r4, #0]
700003be:	2302      	movs	r3, #2
700003c0:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
700003c4:	f240 6303 	movw	r3, #1539	; 0x603
700003c8:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
700003cc:	230a      	movs	r3, #10
700003ce:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
700003d2:	2304      	movs	r3, #4
700003d4:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
700003d8:	f44f 63b5 	mov.w	r3, #1448	; 0x5a8
700003dc:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
700003e0:	4b0b      	ldr	r3, [pc, #44]	; (70000410 <gc4653_get_init_info+0x94>)
700003e2:	f242 3228 	movw	r2, #9000	; 0x2328
700003e6:	e9c4 3124 	strd	r3, r1, [r4, #144]	; 0x90
700003ea:	f240 53dc 	movw	r3, #1500	; 0x5dc
700003ee:	e9c4 3226 	strd	r3, r2, [r4, #152]	; 0x98
700003f2:	6073      	str	r3, [r6, #4]
700003f4:	2300      	movs	r3, #0
700003f6:	4a07      	ldr	r2, [pc, #28]	; (70000414 <gc4653_get_init_info+0x98>)
700003f8:	60f3      	str	r3, [r6, #12]
700003fa:	60b2      	str	r2, [r6, #8]
700003fc:	e9c4 5522 	strd	r5, r5, [r4, #136]	; 0x88
70000400:	e7c2      	b.n	70000388 <gc4653_get_init_info+0xc>
70000402:	bf00      	nop
70000404:	7000004c 	.word	0x7000004c
70000408:	41f00000 	.word	0x41f00000
7000040c:	70000060 	.word	0x70000060
70000410:	07b98a00 	.word	0x07b98a00
70000414:	41b1c71c 	.word	0x41b1c71c

70000418 <gc4653_start>:
70000418:	b918      	cbnz	r0, 70000422 <gc4653_start+0xa>
7000041a:	4b03      	ldr	r3, [pc, #12]	; (70000428 <gc4653_start+0x10>)
7000041c:	2200      	movs	r2, #0
7000041e:	60da      	str	r2, [r3, #12]
70000420:	4770      	bx	lr
70000422:	f06f 0015 	mvn.w	r0, #21
70000426:	4770      	bx	lr
70000428:	7000004c 	.word	0x7000004c

7000042c <gc4653_get_tuned_dgain>:
7000042c:	b920      	cbnz	r0, 70000438 <gc4653_get_tuned_dgain+0xc>
7000042e:	b119      	cbz	r1, 70000438 <gc4653_get_tuned_dgain+0xc>
70000430:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
70000434:	600b      	str	r3, [r1, #0]
70000436:	4770      	bx	lr
70000438:	f06f 0015 	mvn.w	r0, #21
7000043c:	4770      	bx	lr
	...

70000440 <gc4653_get_exposure_gain_info>:
70000440:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
70000444:	4615      	mov	r5, r2
70000446:	2800      	cmp	r0, #0
70000448:	f040 8093 	bne.w	70000572 <gc4653_get_exposure_gain_info+0x132>
7000044c:	2900      	cmp	r1, #0
7000044e:	f000 8090 	beq.w	70000572 <gc4653_get_exposure_gain_info+0x132>
70000452:	2a00      	cmp	r2, #0
70000454:	f000 808d 	beq.w	70000572 <gc4653_get_exposure_gain_info+0x132>
70000458:	f8d1 8000 	ldr.w	r8, [r1]
7000045c:	1d14      	adds	r4, r2, #4
7000045e:	4f46      	ldr	r7, [pc, #280]	; (70000578 <gc4653_get_exposure_gain_info+0x138>)
70000460:	698e      	ldr	r6, [r1, #24]
70000462:	4641      	mov	r1, r8
70000464:	68f8      	ldr	r0, [r7, #12]
70000466:	f000 fa7f 	bl	70000968 <__aeabi_fsub>
7000046a:	2100      	movs	r1, #0
7000046c:	4681      	mov	r9, r0
7000046e:	f000 fd37 	bl	70000ee0 <__aeabi_fcmpge>
70000472:	2800      	cmp	r0, #0
70000474:	d078      	beq.n	70000568 <gc4653_get_exposure_gain_info+0x128>
70000476:	4941      	ldr	r1, [pc, #260]	; (7000057c <gc4653_get_exposure_gain_info+0x13c>)
70000478:	4648      	mov	r0, r9
7000047a:	f000 fd3b 	bl	70000ef4 <__aeabi_fcmpgt>
7000047e:	b1b8      	cbz	r0, 700004b0 <gc4653_get_exposure_gain_info+0x70>
70000480:	68b9      	ldr	r1, [r7, #8]
70000482:	4640      	mov	r0, r8
70000484:	f000 fc2e 	bl	70000ce4 <__aeabi_fdiv>
70000488:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
7000048c:	f000 fa6e 	bl	7000096c <__addsf3>
70000490:	f000 fd3a 	bl	70000f08 <__aeabi_f2uiz>
70000494:	f240 2302 	movw	r3, #514	; 0x202
70000498:	81ab      	strh	r3, [r5, #12]
7000049a:	f3c0 2307 	ubfx	r3, r0, #8, #8
7000049e:	b2c0      	uxtb	r0, r0
700004a0:	81eb      	strh	r3, [r5, #14]
700004a2:	f240 2303 	movw	r3, #515	; 0x203
700004a6:	8468      	strh	r0, [r5, #34]	; 0x22
700004a8:	2002      	movs	r0, #2
700004aa:	842b      	strh	r3, [r5, #32]
700004ac:	f8c7 800c 	str.w	r8, [r7, #12]
700004b0:	693f      	ldr	r7, [r7, #16]
700004b2:	220a      	movs	r2, #10
700004b4:	f8df c0c8 	ldr.w	ip, [pc, #200]	; 70000580 <gc4653_get_exposure_gain_info+0x140>
700004b8:	2314      	movs	r3, #20
700004ba:	4357      	muls	r7, r2
700004bc:	f240 28b3 	movw	r8, #691	; 0x2b3
700004c0:	4343      	muls	r3, r0
700004c2:	3009      	adds	r0, #9
700004c4:	eb0c 0207 	add.w	r2, ip, r7
700004c8:	f81c 7007 	ldrb.w	r7, [ip, r7]
700004cc:	18e1      	adds	r1, r4, r3
700004ce:	f44f 7c2d 	mov.w	ip, #692	; 0x2b4
700004d2:	f892 e001 	ldrb.w	lr, [r2, #1]
700004d6:	f8a1 8008 	strh.w	r8, [r1, #8]
700004da:	f8a1 e00a 	strh.w	lr, [r1, #10]
700004de:	f103 0114 	add.w	r1, r3, #20
700004e2:	4421      	add	r1, r4
700004e4:	f8a1 c008 	strh.w	ip, [r1, #8]
700004e8:	f44f 7c2e 	mov.w	ip, #696	; 0x2b8
700004ec:	814f      	strh	r7, [r1, #10]
700004ee:	f103 0128 	add.w	r1, r3, #40	; 0x28
700004f2:	7897      	ldrb	r7, [r2, #2]
700004f4:	4421      	add	r1, r4
700004f6:	f8a1 c008 	strh.w	ip, [r1, #8]
700004fa:	f240 2cb9 	movw	ip, #697	; 0x2b9
700004fe:	814f      	strh	r7, [r1, #10]
70000500:	f103 013c 	add.w	r1, r3, #60	; 0x3c
70000504:	78d7      	ldrb	r7, [r2, #3]
70000506:	4421      	add	r1, r4
70000508:	f8a1 c008 	strh.w	ip, [r1, #8]
7000050c:	f240 5c15 	movw	ip, #1301	; 0x515
70000510:	814f      	strh	r7, [r1, #10]
70000512:	f103 0150 	add.w	r1, r3, #80	; 0x50
70000516:	7917      	ldrb	r7, [r2, #4]
70000518:	4421      	add	r1, r4
7000051a:	f8a1 c008 	strh.w	ip, [r1, #8]
7000051e:	f240 5c19 	movw	ip, #1305	; 0x519
70000522:	814f      	strh	r7, [r1, #10]
70000524:	f103 0164 	add.w	r1, r3, #100	; 0x64
70000528:	7957      	ldrb	r7, [r2, #5]
7000052a:	4421      	add	r1, r4
7000052c:	7992      	ldrb	r2, [r2, #6]
7000052e:	814f      	strh	r7, [r1, #10]
70000530:	f240 27d9 	movw	r7, #729	; 0x2d9
70000534:	f8a1 c008 	strh.w	ip, [r1, #8]
70000538:	f103 0178 	add.w	r1, r3, #120	; 0x78
7000053c:	4421      	add	r1, r4
7000053e:	814a      	strh	r2, [r1, #10]
70000540:	f103 028c 	add.w	r2, r3, #140	; 0x8c
70000544:	810f      	strh	r7, [r1, #8]
70000546:	f44f 7150 	mov.w	r1, #832	; 0x340
7000054a:	4422      	add	r2, r4
7000054c:	33a0      	adds	r3, #160	; 0xa0
7000054e:	8111      	strh	r1, [r2, #8]
70000550:	0a31      	lsrs	r1, r6, #8
70000552:	4423      	add	r3, r4
70000554:	b2f6      	uxtb	r6, r6
70000556:	8151      	strh	r1, [r2, #10]
70000558:	f240 3241 	movw	r2, #833	; 0x341
7000055c:	815e      	strh	r6, [r3, #10]
7000055e:	811a      	strh	r2, [r3, #8]
70000560:	6028      	str	r0, [r5, #0]
70000562:	2000      	movs	r0, #0
70000564:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
70000568:	4906      	ldr	r1, [pc, #24]	; (70000584 <gc4653_get_exposure_gain_info+0x144>)
7000056a:	4648      	mov	r0, r9
7000056c:	f000 fca4 	bl	70000eb8 <__aeabi_fcmplt>
70000570:	e785      	b.n	7000047e <gc4653_get_exposure_gain_info+0x3e>
70000572:	f06f 0015 	mvn.w	r0, #21
70000576:	e7f5      	b.n	70000564 <gc4653_get_exposure_gain_info+0x124>
70000578:	7000004c 	.word	0x7000004c
7000057c:	3a83126f 	.word	0x3a83126f
70000580:	700006b8 	.word	0x700006b8
70000584:	ba83126f 	.word	0xba83126f

70000588 <gc4653_set_mirror_flip>:
70000588:	784b      	ldrb	r3, [r1, #1]
7000058a:	780a      	ldrb	r2, [r1, #0]
7000058c:	2b00      	cmp	r3, #0
7000058e:	bf14      	ite	ne
70000590:	2302      	movne	r3, #2
70000592:	2300      	moveq	r3, #0
70000594:	2a00      	cmp	r2, #0
70000596:	bf18      	it	ne
70000598:	f043 0301 	orrne.w	r3, r3, #1
7000059c:	2201      	movs	r2, #1
7000059e:	2b02      	cmp	r3, #2
700005a0:	708a      	strb	r2, [r1, #2]
700005a2:	d00b      	beq.n	700005bc <gc4653_set_mirror_flip+0x34>
700005a4:	2b03      	cmp	r3, #3
700005a6:	d00b      	beq.n	700005c0 <gc4653_set_mirror_flip+0x38>
700005a8:	4293      	cmp	r3, r2
700005aa:	bf14      	ite	ne
700005ac:	f240 1301 	movwne	r3, #257	; 0x101
700005b0:	4b04      	ldreq	r3, [pc, #16]	; (700005c4 <gc4653_set_mirror_flip+0x3c>)
700005b2:	610b      	str	r3, [r1, #16]
700005b4:	2301      	movs	r3, #1
700005b6:	2000      	movs	r0, #0
700005b8:	604b      	str	r3, [r1, #4]
700005ba:	4770      	bx	lr
700005bc:	4b02      	ldr	r3, [pc, #8]	; (700005c8 <gc4653_set_mirror_flip+0x40>)
700005be:	e7f8      	b.n	700005b2 <gc4653_set_mirror_flip+0x2a>
700005c0:	4b02      	ldr	r3, [pc, #8]	; (700005cc <gc4653_set_mirror_flip+0x44>)
700005c2:	e7f6      	b.n	700005b2 <gc4653_set_mirror_flip+0x2a>
700005c4:	00010101 	.word	0x00010101
700005c8:	00020101 	.word	0x00020101
700005cc:	00030101 	.word	0x00030101

700005d0 <gc4653_check>:
700005d0:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
700005d2:	4d19      	ldr	r5, [pc, #100]	; (70000638 <gc4653_check+0x68>)
700005d4:	4606      	mov	r6, r0
700005d6:	682b      	ldr	r3, [r5, #0]
700005d8:	685b      	ldr	r3, [r3, #4]
700005da:	4798      	blx	r3
700005dc:	f44f 737c 	mov.w	r3, #1008	; 0x3f0
700005e0:	a901      	add	r1, sp, #4
700005e2:	4630      	mov	r0, r6
700005e4:	f8ad 3004 	strh.w	r3, [sp, #4]
700005e8:	682b      	ldr	r3, [r5, #0]
700005ea:	68db      	ldr	r3, [r3, #12]
700005ec:	4798      	blx	r3
700005ee:	4604      	mov	r4, r0
700005f0:	b128      	cbz	r0, 700005fe <gc4653_check+0x2e>
700005f2:	682b      	ldr	r3, [r5, #0]
700005f4:	689b      	ldr	r3, [r3, #8]
700005f6:	4798      	blx	r3
700005f8:	4620      	mov	r0, r4
700005fa:	b003      	add	sp, #12
700005fc:	bdf0      	pop	{r4, r5, r6, r7, pc}
700005fe:	f240 33f1 	movw	r3, #1009	; 0x3f1
70000602:	a901      	add	r1, sp, #4
70000604:	4630      	mov	r0, r6
70000606:	f8bd 7006 	ldrh.w	r7, [sp, #6]
7000060a:	f8ad 3004 	strh.w	r3, [sp, #4]
7000060e:	682b      	ldr	r3, [r5, #0]
70000610:	68db      	ldr	r3, [r3, #12]
70000612:	4798      	blx	r3
70000614:	682b      	ldr	r3, [r5, #0]
70000616:	4604      	mov	r4, r0
70000618:	689b      	ldr	r3, [r3, #8]
7000061a:	4798      	blx	r3
7000061c:	2c00      	cmp	r4, #0
7000061e:	d1eb      	bne.n	700005f8 <gc4653_check+0x28>
70000620:	f8bd 3006 	ldrh.w	r3, [sp, #6]
70000624:	f244 6253 	movw	r2, #18003	; 0x4653
70000628:	ea43 2307 	orr.w	r3, r3, r7, lsl #8
7000062c:	4293      	cmp	r3, r2
7000062e:	bf18      	it	ne
70000630:	f06f 0415 	mvnne.w	r4, #21
70000634:	e7e0      	b.n	700005f8 <gc4653_check+0x28>
70000636:	bf00      	nop
70000638:	70000048 	.word	0x70000048

7000063c <gc4653_get_slave_addr_num>:
7000063c:	2002      	movs	r0, #2
7000063e:	4770      	bx	lr

70000640 <gc4653_get_tuned_again>:
70000640:	b570      	push	{r4, r5, r6, lr}
70000642:	460d      	mov	r5, r1
70000644:	4604      	mov	r4, r0
70000646:	bb60      	cbnz	r0, 700006a2 <gc4653_get_tuned_again+0x62>
70000648:	b359      	cbz	r1, 700006a2 <gc4653_get_tuned_again+0x62>
7000064a:	f04f 4185 	mov.w	r1, #1115684864	; 0x42800000
7000064e:	6828      	ldr	r0, [r5, #0]
70000650:	f000 fa94 	bl	70000b7c <__aeabi_fmul>
70000654:	f000 fc58 	bl	70000f08 <__aeabi_f2uiz>
70000658:	b280      	uxth	r0, r0
7000065a:	f5b0 6f80 	cmp.w	r0, #1024	; 0x400
7000065e:	d30d      	bcc.n	7000067c <gc4653_get_tuned_again+0x3c>
70000660:	4b11      	ldr	r3, [pc, #68]	; (700006a8 <gc4653_get_tuned_again+0x68>)
70000662:	2210      	movs	r2, #16
70000664:	f44f 6080 	mov.w	r0, #1024	; 0x400
70000668:	611a      	str	r2, [r3, #16]
7000066a:	f000 fa33 	bl	70000ad4 <__aeabi_i2f>
7000066e:	f04f 5172 	mov.w	r1, #1015021568	; 0x3c800000
70000672:	f000 fa83 	bl	70000b7c <__aeabi_fmul>
70000676:	6028      	str	r0, [r5, #0]
70000678:	2000      	movs	r0, #0
7000067a:	bd70      	pop	{r4, r5, r6, pc}
7000067c:	4a0b      	ldr	r2, [pc, #44]	; (700006ac <gc4653_get_tuned_again+0x6c>)
7000067e:	4623      	mov	r3, r4
70000680:	8911      	ldrh	r1, [r2, #8]
70000682:	461c      	mov	r4, r3
70000684:	3301      	adds	r3, #1
70000686:	4288      	cmp	r0, r1
70000688:	d306      	bcc.n	70000698 <gc4653_get_tuned_again+0x58>
7000068a:	8a56      	ldrh	r6, [r2, #18]
7000068c:	4286      	cmp	r6, r0
7000068e:	d903      	bls.n	70000698 <gc4653_get_tuned_again+0x58>
70000690:	4b05      	ldr	r3, [pc, #20]	; (700006a8 <gc4653_get_tuned_again+0x68>)
70000692:	4608      	mov	r0, r1
70000694:	611c      	str	r4, [r3, #16]
70000696:	e7e8      	b.n	7000066a <gc4653_get_tuned_again+0x2a>
70000698:	2b10      	cmp	r3, #16
7000069a:	f102 020a 	add.w	r2, r2, #10
7000069e:	d1ef      	bne.n	70000680 <gc4653_get_tuned_again+0x40>
700006a0:	e7e3      	b.n	7000066a <gc4653_get_tuned_again+0x2a>
700006a2:	f06f 0015 	mvn.w	r0, #21
700006a6:	e7e8      	b.n	7000067a <gc4653_get_tuned_again+0x3a>
700006a8:	7000004c 	.word	0x7000004c
700006ac:	700006b8 	.word	0x700006b8

700006b0 <rts_isp_get_sensor_ops>:
700006b0:	4800      	ldr	r0, [pc, #0]	; (700006b4 <rts_isp_get_sensor_ops+0x4>)
700006b2:	4770      	bx	lr
700006b4:	70000764 	.word	0x70000764

700006b8 <g_gc4653_gain_config>:
700006b8:	00010000 005c1e30 20000040 1e300b01     ....0.\.@.. ..0.
700006c8:	004b005c 19010100 005b1d30 21000059     \.K.....0.[.Y..!
700006d8:	1e302a01 006a005c 00020200 005c1e30     .*0.\.j.....0.\.
700006e8:	22000080 1d301702 0097005b 33020300     ..."..0.[......3
700006f8:	00541620 230000b3 17201403 00d40055      .T....#.. .U...
70000708:	00040400 00551720 24000100 19202f04     .... .U....$./ .
70000718:	012f0057 26050500 00571920 25000166     W./....& .W.f..%
70000728:	1b202806 01a80059 00080c00 005b1d20     .( .Y....... .[.
70000738:	2c000200 1f201e09 025e005d 0c0b0d00     ...,.. .].^.....
70000748:	005f2120 2d0002cc 2420110d 03510062      !_....-.. $b.Q.
70000758:	00101c00 00642620 00000400              .... &d.....

70000764 <gc4653_ops>:
70000764:	73000005 36346367 00003335 00000000     ...sgc4653......
	...
70000788:	700002bd 7000037d 00000000 70000641     ...p}..p....A..p
70000798:	7000042d 70000441 00000000 00000000     -..pA..p........
700007a8:	70000419 00000000 00000000 00000000     ...p............
700007b8:	70000589 00000000 00000000 00000000     ...p............
700007c8:	700005d1 00000000 00000000 00000000     ...p............
700007d8:	7000063d 00000000 00000000 00000000     =..p............
	...
700007f8:	0cfff04f 52d0ea1c ea1cbf1e ea9253d1     O......R.....S..
70000808:	ea930f0c d06f0f0c ea80441a 02400c01     ......o..D....@.
70000818:	ea5fbf18 d01e2141 6300f04f 1050ea43     .._.A!..O..cC.P.
70000828:	1151ea43 3101fba0 4000f00c 0f00f5b1     C.Q....1...@....
70000838:	0049bf3e 71d3ea41 ea40005b f1620001     >.I.A..q[.@...b.
70000848:	2afd027f f1b3d81d eb404f00 bf0850c2     ...*.....O@..P..
70000858:	0001f020 f0904770 f00c0f00 bf084c00      ...pG.......L..
70000868:	ea4c0249 ea402050 3a7f2051 f1d2bfc2     I.L.P @.Q .:....
70000878:	ea4003ff 477050c2 0000f440 0300f04f     ..@..PpG@...O...
70000888:	dc5d3a01 0f19f112 f000bfdc 47704000     .:]..........@pG
70000898:	0200f1c2 fa210041 f1c2f102 fa000220     ....A.!..... ...
700008a8:	ea5ffc02 f1400031 ea530000 bf08034c     .._.1.@...S.L...
700008b8:	70dcea20 f0924770 f0000f00 bf024c00      ..ppG.......L..
700008c8:	f4100040 3a010f00 ea40d0f9 f093000c     @......:..@.....
700008d8:	f0010f00 bf024c00 f4110049 3b010f00     .....L..I......;
700008e8:	ea41d0f9 e78f010c 53d1ea0c 0f0cea92     ..A........S....
700008f8:	ea93bf18 d00a0f0c 4c00f030 f031bf18     ........0..L..1.
70000908:	d1d84c00 0001ea80 4000f000 f0904770     .L.........@pG..
70000918:	bf170f00 4f00f090 f0914608 f0910f00     .......O.F......
70000928:	d0144f00 0f0cea92 0242d101 ea93d10f     .O........B.....
70000938:	d1030f0c bf18024b d1084608 0001ea80     ....K....F......
70000948:	4000f000 40fef040 0000f440 f0404770     ...@@..@@...pG@.
70000958:	f44040fe 47700040                       .@@.@.pG

70000960 <__aeabi_frsub>:
70000960:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70000964:	e002      	b.n	7000096c <__addsf3>
70000966:	bf00      	nop

70000968 <__aeabi_fsub>:
70000968:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

7000096c <__addsf3>:
7000096c:	0042      	lsls	r2, r0, #1
7000096e:	bf1f      	itttt	ne
70000970:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70000974:	ea92 0f03 	teqne	r2, r3
70000978:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
7000097c:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000980:	d06a      	beq.n	70000a58 <__addsf3+0xec>
70000982:	ea4f 6212 	mov.w	r2, r2, lsr #24
70000986:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
7000098a:	bfc1      	itttt	gt
7000098c:	18d2      	addgt	r2, r2, r3
7000098e:	4041      	eorgt	r1, r0
70000990:	4048      	eorgt	r0, r1
70000992:	4041      	eorgt	r1, r0
70000994:	bfb8      	it	lt
70000996:	425b      	neglt	r3, r3
70000998:	2b19      	cmp	r3, #25
7000099a:	bf88      	it	hi
7000099c:	4770      	bxhi	lr
7000099e:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
700009a2:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700009a6:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
700009aa:	bf18      	it	ne
700009ac:	4240      	negne	r0, r0
700009ae:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
700009b2:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
700009b6:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
700009ba:	bf18      	it	ne
700009bc:	4249      	negne	r1, r1
700009be:	ea92 0f03 	teq	r2, r3
700009c2:	d03f      	beq.n	70000a44 <__addsf3+0xd8>
700009c4:	f1a2 0201 	sub.w	r2, r2, #1
700009c8:	fa41 fc03 	asr.w	ip, r1, r3
700009cc:	eb10 000c 	adds.w	r0, r0, ip
700009d0:	f1c3 0320 	rsb	r3, r3, #32
700009d4:	fa01 f103 	lsl.w	r1, r1, r3
700009d8:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
700009dc:	d502      	bpl.n	700009e4 <__addsf3+0x78>
700009de:	4249      	negs	r1, r1
700009e0:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
700009e4:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
700009e8:	d313      	bcc.n	70000a12 <__addsf3+0xa6>
700009ea:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
700009ee:	d306      	bcc.n	700009fe <__addsf3+0x92>
700009f0:	0840      	lsrs	r0, r0, #1
700009f2:	ea4f 0131 	mov.w	r1, r1, rrx
700009f6:	f102 0201 	add.w	r2, r2, #1
700009fa:	2afe      	cmp	r2, #254	; 0xfe
700009fc:	d251      	bcs.n	70000aa2 <__addsf3+0x136>
700009fe:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
70000a02:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000a06:	bf08      	it	eq
70000a08:	f020 0001 	biceq.w	r0, r0, #1
70000a0c:	ea40 0003 	orr.w	r0, r0, r3
70000a10:	4770      	bx	lr
70000a12:	0049      	lsls	r1, r1, #1
70000a14:	eb40 0000 	adc.w	r0, r0, r0
70000a18:	3a01      	subs	r2, #1
70000a1a:	bf28      	it	cs
70000a1c:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70000a20:	d2ed      	bcs.n	700009fe <__addsf3+0x92>
70000a22:	fab0 fc80 	clz	ip, r0
70000a26:	f1ac 0c08 	sub.w	ip, ip, #8
70000a2a:	ebb2 020c 	subs.w	r2, r2, ip
70000a2e:	fa00 f00c 	lsl.w	r0, r0, ip
70000a32:	bfaa      	itet	ge
70000a34:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
70000a38:	4252      	neglt	r2, r2
70000a3a:	4318      	orrge	r0, r3
70000a3c:	bfbc      	itt	lt
70000a3e:	40d0      	lsrlt	r0, r2
70000a40:	4318      	orrlt	r0, r3
70000a42:	4770      	bx	lr
70000a44:	f092 0f00 	teq	r2, #0
70000a48:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
70000a4c:	bf06      	itte	eq
70000a4e:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
70000a52:	3201      	addeq	r2, #1
70000a54:	3b01      	subne	r3, #1
70000a56:	e7b5      	b.n	700009c4 <__addsf3+0x58>
70000a58:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000a5c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000a60:	bf18      	it	ne
70000a62:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000a66:	d021      	beq.n	70000aac <__addsf3+0x140>
70000a68:	ea92 0f03 	teq	r2, r3
70000a6c:	d004      	beq.n	70000a78 <__addsf3+0x10c>
70000a6e:	f092 0f00 	teq	r2, #0
70000a72:	bf08      	it	eq
70000a74:	4608      	moveq	r0, r1
70000a76:	4770      	bx	lr
70000a78:	ea90 0f01 	teq	r0, r1
70000a7c:	bf1c      	itt	ne
70000a7e:	2000      	movne	r0, #0
70000a80:	4770      	bxne	lr
70000a82:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
70000a86:	d104      	bne.n	70000a92 <__addsf3+0x126>
70000a88:	0040      	lsls	r0, r0, #1
70000a8a:	bf28      	it	cs
70000a8c:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
70000a90:	4770      	bx	lr
70000a92:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
70000a96:	bf3c      	itt	cc
70000a98:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
70000a9c:	4770      	bxcc	lr
70000a9e:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000aa2:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
70000aa6:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000aaa:	4770      	bx	lr
70000aac:	ea7f 6222 	mvns.w	r2, r2, asr #24
70000ab0:	bf16      	itet	ne
70000ab2:	4608      	movne	r0, r1
70000ab4:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70000ab8:	4601      	movne	r1, r0
70000aba:	0242      	lsls	r2, r0, #9
70000abc:	bf06      	itte	eq
70000abe:	ea5f 2341 	movseq.w	r3, r1, lsl #9
70000ac2:	ea90 0f01 	teqeq	r0, r1
70000ac6:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
70000aca:	4770      	bx	lr

70000acc <__aeabi_ui2f>:
70000acc:	f04f 0300 	mov.w	r3, #0
70000ad0:	e004      	b.n	70000adc <__aeabi_i2f+0x8>
70000ad2:	bf00      	nop

70000ad4 <__aeabi_i2f>:
70000ad4:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70000ad8:	bf48      	it	mi
70000ada:	4240      	negmi	r0, r0
70000adc:	ea5f 0c00 	movs.w	ip, r0
70000ae0:	bf08      	it	eq
70000ae2:	4770      	bxeq	lr
70000ae4:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70000ae8:	4601      	mov	r1, r0
70000aea:	f04f 0000 	mov.w	r0, #0
70000aee:	e01c      	b.n	70000b2a <__aeabi_l2f+0x2a>

70000af0 <__aeabi_ul2f>:
70000af0:	ea50 0201 	orrs.w	r2, r0, r1
70000af4:	bf08      	it	eq
70000af6:	4770      	bxeq	lr
70000af8:	f04f 0300 	mov.w	r3, #0
70000afc:	e00a      	b.n	70000b14 <__aeabi_l2f+0x14>
70000afe:	bf00      	nop

70000b00 <__aeabi_l2f>:
70000b00:	ea50 0201 	orrs.w	r2, r0, r1
70000b04:	bf08      	it	eq
70000b06:	4770      	bxeq	lr
70000b08:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70000b0c:	d502      	bpl.n	70000b14 <__aeabi_l2f+0x14>
70000b0e:	4240      	negs	r0, r0
70000b10:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000b14:	ea5f 0c01 	movs.w	ip, r1
70000b18:	bf02      	ittt	eq
70000b1a:	4684      	moveq	ip, r0
70000b1c:	4601      	moveq	r1, r0
70000b1e:	2000      	moveq	r0, #0
70000b20:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70000b24:	bf08      	it	eq
70000b26:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70000b2a:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
70000b2e:	fabc f28c 	clz	r2, ip
70000b32:	3a08      	subs	r2, #8
70000b34:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
70000b38:	db10      	blt.n	70000b5c <__aeabi_l2f+0x5c>
70000b3a:	fa01 fc02 	lsl.w	ip, r1, r2
70000b3e:	4463      	add	r3, ip
70000b40:	fa00 fc02 	lsl.w	ip, r0, r2
70000b44:	f1c2 0220 	rsb	r2, r2, #32
70000b48:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000b4c:	fa20 f202 	lsr.w	r2, r0, r2
70000b50:	eb43 0002 	adc.w	r0, r3, r2
70000b54:	bf08      	it	eq
70000b56:	f020 0001 	biceq.w	r0, r0, #1
70000b5a:	4770      	bx	lr
70000b5c:	f102 0220 	add.w	r2, r2, #32
70000b60:	fa01 fc02 	lsl.w	ip, r1, r2
70000b64:	f1c2 0220 	rsb	r2, r2, #32
70000b68:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
70000b6c:	fa21 f202 	lsr.w	r2, r1, r2
70000b70:	eb43 0002 	adc.w	r0, r3, r2
70000b74:	bf08      	it	eq
70000b76:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000b7a:	4770      	bx	lr

70000b7c <__aeabi_fmul>:
70000b7c:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000b80:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000b84:	bf1e      	ittt	ne
70000b86:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000b8a:	ea92 0f0c 	teqne	r2, ip
70000b8e:	ea93 0f0c 	teqne	r3, ip
70000b92:	d06f      	beq.n	70000c74 <__aeabi_fmul+0xf8>
70000b94:	441a      	add	r2, r3
70000b96:	ea80 0c01 	eor.w	ip, r0, r1
70000b9a:	0240      	lsls	r0, r0, #9
70000b9c:	bf18      	it	ne
70000b9e:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000ba2:	d01e      	beq.n	70000be2 <__aeabi_fmul+0x66>
70000ba4:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000ba8:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000bac:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000bb0:	fba0 3101 	umull	r3, r1, r0, r1
70000bb4:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000bb8:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000bbc:	bf3e      	ittt	cc
70000bbe:	0049      	lslcc	r1, r1, #1
70000bc0:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000bc4:	005b      	lslcc	r3, r3, #1
70000bc6:	ea40 0001 	orr.w	r0, r0, r1
70000bca:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000bce:	2afd      	cmp	r2, #253	; 0xfd
70000bd0:	d81d      	bhi.n	70000c0e <__aeabi_fmul+0x92>
70000bd2:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000bd6:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000bda:	bf08      	it	eq
70000bdc:	f020 0001 	biceq.w	r0, r0, #1
70000be0:	4770      	bx	lr
70000be2:	f090 0f00 	teq	r0, #0
70000be6:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000bea:	bf08      	it	eq
70000bec:	0249      	lsleq	r1, r1, #9
70000bee:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000bf2:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000bf6:	3a7f      	subs	r2, #127	; 0x7f
70000bf8:	bfc2      	ittt	gt
70000bfa:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000bfe:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000c02:	4770      	bxgt	lr
70000c04:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000c08:	f04f 0300 	mov.w	r3, #0
70000c0c:	3a01      	subs	r2, #1
70000c0e:	dc5d      	bgt.n	70000ccc <__aeabi_fmul+0x150>
70000c10:	f112 0f19 	cmn.w	r2, #25
70000c14:	bfdc      	itt	le
70000c16:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000c1a:	4770      	bxle	lr
70000c1c:	f1c2 0200 	rsb	r2, r2, #0
70000c20:	0041      	lsls	r1, r0, #1
70000c22:	fa21 f102 	lsr.w	r1, r1, r2
70000c26:	f1c2 0220 	rsb	r2, r2, #32
70000c2a:	fa00 fc02 	lsl.w	ip, r0, r2
70000c2e:	ea5f 0031 	movs.w	r0, r1, rrx
70000c32:	f140 0000 	adc.w	r0, r0, #0
70000c36:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000c3a:	bf08      	it	eq
70000c3c:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000c40:	4770      	bx	lr
70000c42:	f092 0f00 	teq	r2, #0
70000c46:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000c4a:	bf02      	ittt	eq
70000c4c:	0040      	lsleq	r0, r0, #1
70000c4e:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000c52:	3a01      	subeq	r2, #1
70000c54:	d0f9      	beq.n	70000c4a <__aeabi_fmul+0xce>
70000c56:	ea40 000c 	orr.w	r0, r0, ip
70000c5a:	f093 0f00 	teq	r3, #0
70000c5e:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000c62:	bf02      	ittt	eq
70000c64:	0049      	lsleq	r1, r1, #1
70000c66:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000c6a:	3b01      	subeq	r3, #1
70000c6c:	d0f9      	beq.n	70000c62 <__aeabi_fmul+0xe6>
70000c6e:	ea41 010c 	orr.w	r1, r1, ip
70000c72:	e78f      	b.n	70000b94 <__aeabi_fmul+0x18>
70000c74:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000c78:	ea92 0f0c 	teq	r2, ip
70000c7c:	bf18      	it	ne
70000c7e:	ea93 0f0c 	teqne	r3, ip
70000c82:	d00a      	beq.n	70000c9a <__aeabi_fmul+0x11e>
70000c84:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000c88:	bf18      	it	ne
70000c8a:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000c8e:	d1d8      	bne.n	70000c42 <__aeabi_fmul+0xc6>
70000c90:	ea80 0001 	eor.w	r0, r0, r1
70000c94:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000c98:	4770      	bx	lr
70000c9a:	f090 0f00 	teq	r0, #0
70000c9e:	bf17      	itett	ne
70000ca0:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000ca4:	4608      	moveq	r0, r1
70000ca6:	f091 0f00 	teqne	r1, #0
70000caa:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000cae:	d014      	beq.n	70000cda <__aeabi_fmul+0x15e>
70000cb0:	ea92 0f0c 	teq	r2, ip
70000cb4:	d101      	bne.n	70000cba <__aeabi_fmul+0x13e>
70000cb6:	0242      	lsls	r2, r0, #9
70000cb8:	d10f      	bne.n	70000cda <__aeabi_fmul+0x15e>
70000cba:	ea93 0f0c 	teq	r3, ip
70000cbe:	d103      	bne.n	70000cc8 <__aeabi_fmul+0x14c>
70000cc0:	024b      	lsls	r3, r1, #9
70000cc2:	bf18      	it	ne
70000cc4:	4608      	movne	r0, r1
70000cc6:	d108      	bne.n	70000cda <__aeabi_fmul+0x15e>
70000cc8:	ea80 0001 	eor.w	r0, r0, r1
70000ccc:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000cd0:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000cd4:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000cd8:	4770      	bx	lr
70000cda:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000cde:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000ce2:	4770      	bx	lr

70000ce4 <__aeabi_fdiv>:
70000ce4:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000ce8:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000cec:	bf1e      	ittt	ne
70000cee:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000cf2:	ea92 0f0c 	teqne	r2, ip
70000cf6:	ea93 0f0c 	teqne	r3, ip
70000cfa:	d069      	beq.n	70000dd0 <__aeabi_fdiv+0xec>
70000cfc:	eba2 0203 	sub.w	r2, r2, r3
70000d00:	ea80 0c01 	eor.w	ip, r0, r1
70000d04:	0249      	lsls	r1, r1, #9
70000d06:	ea4f 2040 	mov.w	r0, r0, lsl #9
70000d0a:	d037      	beq.n	70000d7c <__aeabi_fdiv+0x98>
70000d0c:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70000d10:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70000d14:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70000d18:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000d1c:	428b      	cmp	r3, r1
70000d1e:	bf38      	it	cc
70000d20:	005b      	lslcc	r3, r3, #1
70000d22:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70000d26:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70000d2a:	428b      	cmp	r3, r1
70000d2c:	bf24      	itt	cs
70000d2e:	1a5b      	subcs	r3, r3, r1
70000d30:	ea40 000c 	orrcs.w	r0, r0, ip
70000d34:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70000d38:	bf24      	itt	cs
70000d3a:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
70000d3e:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70000d42:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70000d46:	bf24      	itt	cs
70000d48:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
70000d4c:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
70000d50:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
70000d54:	bf24      	itt	cs
70000d56:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
70000d5a:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
70000d5e:	011b      	lsls	r3, r3, #4
70000d60:	bf18      	it	ne
70000d62:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70000d66:	d1e0      	bne.n	70000d2a <__aeabi_fdiv+0x46>
70000d68:	2afd      	cmp	r2, #253	; 0xfd
70000d6a:	f63f af50 	bhi.w	70000c0e <__aeabi_fmul+0x92>
70000d6e:	428b      	cmp	r3, r1
70000d70:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000d74:	bf08      	it	eq
70000d76:	f020 0001 	biceq.w	r0, r0, #1
70000d7a:	4770      	bx	lr
70000d7c:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000d80:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000d84:	327f      	adds	r2, #127	; 0x7f
70000d86:	bfc2      	ittt	gt
70000d88:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000d8c:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000d90:	4770      	bxgt	lr
70000d92:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000d96:	f04f 0300 	mov.w	r3, #0
70000d9a:	3a01      	subs	r2, #1
70000d9c:	e737      	b.n	70000c0e <__aeabi_fmul+0x92>
70000d9e:	f092 0f00 	teq	r2, #0
70000da2:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000da6:	bf02      	ittt	eq
70000da8:	0040      	lsleq	r0, r0, #1
70000daa:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000dae:	3a01      	subeq	r2, #1
70000db0:	d0f9      	beq.n	70000da6 <__aeabi_fdiv+0xc2>
70000db2:	ea40 000c 	orr.w	r0, r0, ip
70000db6:	f093 0f00 	teq	r3, #0
70000dba:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000dbe:	bf02      	ittt	eq
70000dc0:	0049      	lsleq	r1, r1, #1
70000dc2:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000dc6:	3b01      	subeq	r3, #1
70000dc8:	d0f9      	beq.n	70000dbe <__aeabi_fdiv+0xda>
70000dca:	ea41 010c 	orr.w	r1, r1, ip
70000dce:	e795      	b.n	70000cfc <__aeabi_fdiv+0x18>
70000dd0:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000dd4:	ea92 0f0c 	teq	r2, ip
70000dd8:	d108      	bne.n	70000dec <__aeabi_fdiv+0x108>
70000dda:	0242      	lsls	r2, r0, #9
70000ddc:	f47f af7d 	bne.w	70000cda <__aeabi_fmul+0x15e>
70000de0:	ea93 0f0c 	teq	r3, ip
70000de4:	f47f af70 	bne.w	70000cc8 <__aeabi_fmul+0x14c>
70000de8:	4608      	mov	r0, r1
70000dea:	e776      	b.n	70000cda <__aeabi_fmul+0x15e>
70000dec:	ea93 0f0c 	teq	r3, ip
70000df0:	d104      	bne.n	70000dfc <__aeabi_fdiv+0x118>
70000df2:	024b      	lsls	r3, r1, #9
70000df4:	f43f af4c 	beq.w	70000c90 <__aeabi_fmul+0x114>
70000df8:	4608      	mov	r0, r1
70000dfa:	e76e      	b.n	70000cda <__aeabi_fmul+0x15e>
70000dfc:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000e00:	bf18      	it	ne
70000e02:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000e06:	d1ca      	bne.n	70000d9e <__aeabi_fdiv+0xba>
70000e08:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70000e0c:	f47f af5c 	bne.w	70000cc8 <__aeabi_fmul+0x14c>
70000e10:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70000e14:	f47f af3c 	bne.w	70000c90 <__aeabi_fmul+0x114>
70000e18:	e75f      	b.n	70000cda <__aeabi_fmul+0x15e>
70000e1a:	bf00      	nop

70000e1c <__gesf2>:
70000e1c:	f04f 3cff 	mov.w	ip, #4294967295
70000e20:	e006      	b.n	70000e30 <__cmpsf2+0x4>
70000e22:	bf00      	nop

70000e24 <__lesf2>:
70000e24:	f04f 0c01 	mov.w	ip, #1
70000e28:	e002      	b.n	70000e30 <__cmpsf2+0x4>
70000e2a:	bf00      	nop

70000e2c <__cmpsf2>:
70000e2c:	f04f 0c01 	mov.w	ip, #1
70000e30:	f84d cd04 	str.w	ip, [sp, #-4]!
70000e34:	ea4f 0240 	mov.w	r2, r0, lsl #1
70000e38:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000e3c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000e40:	bf18      	it	ne
70000e42:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000e46:	d011      	beq.n	70000e6c <__cmpsf2+0x40>
70000e48:	b001      	add	sp, #4
70000e4a:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
70000e4e:	bf18      	it	ne
70000e50:	ea90 0f01 	teqne	r0, r1
70000e54:	bf58      	it	pl
70000e56:	ebb2 0003 	subspl.w	r0, r2, r3
70000e5a:	bf88      	it	hi
70000e5c:	17c8      	asrhi	r0, r1, #31
70000e5e:	bf38      	it	cc
70000e60:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70000e64:	bf18      	it	ne
70000e66:	f040 0001 	orrne.w	r0, r0, #1
70000e6a:	4770      	bx	lr
70000e6c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000e70:	d102      	bne.n	70000e78 <__cmpsf2+0x4c>
70000e72:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70000e76:	d105      	bne.n	70000e84 <__cmpsf2+0x58>
70000e78:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70000e7c:	d1e4      	bne.n	70000e48 <__cmpsf2+0x1c>
70000e7e:	ea5f 2c41 	movs.w	ip, r1, lsl #9
70000e82:	d0e1      	beq.n	70000e48 <__cmpsf2+0x1c>
70000e84:	f85d 0b04 	ldr.w	r0, [sp], #4
70000e88:	4770      	bx	lr
70000e8a:	bf00      	nop

70000e8c <__aeabi_cfrcmple>:
70000e8c:	4684      	mov	ip, r0
70000e8e:	4608      	mov	r0, r1
70000e90:	4661      	mov	r1, ip
70000e92:	e7ff      	b.n	70000e94 <__aeabi_cfcmpeq>

70000e94 <__aeabi_cfcmpeq>:
70000e94:	b50f      	push	{r0, r1, r2, r3, lr}
70000e96:	f7ff ffc9 	bl	70000e2c <__cmpsf2>
70000e9a:	2800      	cmp	r0, #0
70000e9c:	bf48      	it	mi
70000e9e:	f110 0f00 	cmnmi.w	r0, #0
70000ea2:	bd0f      	pop	{r0, r1, r2, r3, pc}

70000ea4 <__aeabi_fcmpeq>:
70000ea4:	f84d ed08 	str.w	lr, [sp, #-8]!
70000ea8:	f7ff fff4 	bl	70000e94 <__aeabi_cfcmpeq>
70000eac:	bf0c      	ite	eq
70000eae:	2001      	moveq	r0, #1
70000eb0:	2000      	movne	r0, #0
70000eb2:	f85d fb08 	ldr.w	pc, [sp], #8
70000eb6:	bf00      	nop

70000eb8 <__aeabi_fcmplt>:
70000eb8:	f84d ed08 	str.w	lr, [sp, #-8]!
70000ebc:	f7ff ffea 	bl	70000e94 <__aeabi_cfcmpeq>
70000ec0:	bf34      	ite	cc
70000ec2:	2001      	movcc	r0, #1
70000ec4:	2000      	movcs	r0, #0
70000ec6:	f85d fb08 	ldr.w	pc, [sp], #8
70000eca:	bf00      	nop

70000ecc <__aeabi_fcmple>:
70000ecc:	f84d ed08 	str.w	lr, [sp, #-8]!
70000ed0:	f7ff ffe0 	bl	70000e94 <__aeabi_cfcmpeq>
70000ed4:	bf94      	ite	ls
70000ed6:	2001      	movls	r0, #1
70000ed8:	2000      	movhi	r0, #0
70000eda:	f85d fb08 	ldr.w	pc, [sp], #8
70000ede:	bf00      	nop

70000ee0 <__aeabi_fcmpge>:
70000ee0:	f84d ed08 	str.w	lr, [sp, #-8]!
70000ee4:	f7ff ffd2 	bl	70000e8c <__aeabi_cfrcmple>
70000ee8:	bf94      	ite	ls
70000eea:	2001      	movls	r0, #1
70000eec:	2000      	movhi	r0, #0
70000eee:	f85d fb08 	ldr.w	pc, [sp], #8
70000ef2:	bf00      	nop

70000ef4 <__aeabi_fcmpgt>:
70000ef4:	f84d ed08 	str.w	lr, [sp, #-8]!
70000ef8:	f7ff ffc8 	bl	70000e8c <__aeabi_cfrcmple>
70000efc:	bf34      	ite	cc
70000efe:	2001      	movcc	r0, #1
70000f00:	2000      	movcs	r0, #0
70000f02:	f85d fb08 	ldr.w	pc, [sp], #8
70000f06:	bf00      	nop

70000f08 <__aeabi_f2uiz>:
70000f08:	0042      	lsls	r2, r0, #1
70000f0a:	d20e      	bcs.n	70000f2a <__aeabi_f2uiz+0x22>
70000f0c:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70000f10:	d30b      	bcc.n	70000f2a <__aeabi_f2uiz+0x22>
70000f12:	f04f 039e 	mov.w	r3, #158	; 0x9e
70000f16:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70000f1a:	d409      	bmi.n	70000f30 <__aeabi_f2uiz+0x28>
70000f1c:	ea4f 2300 	mov.w	r3, r0, lsl #8
70000f20:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000f24:	fa23 f002 	lsr.w	r0, r3, r2
70000f28:	4770      	bx	lr
70000f2a:	f04f 0000 	mov.w	r0, #0
70000f2e:	4770      	bx	lr
70000f30:	f112 0f61 	cmn.w	r2, #97	; 0x61
70000f34:	d101      	bne.n	70000f3a <__aeabi_f2uiz+0x32>
70000f36:	0242      	lsls	r2, r0, #9
70000f38:	d102      	bne.n	70000f40 <__aeabi_f2uiz+0x38>
70000f3a:	f04f 30ff 	mov.w	r0, #4294967295
70000f3e:	4770      	bx	lr
70000f40:	f04f 0000 	mov.w	r0, #0
70000f44:	4770      	bx	lr
70000f46:	bf00      	nop
