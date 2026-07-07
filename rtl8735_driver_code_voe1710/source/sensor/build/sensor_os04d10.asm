
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	7d 06 00 70 35 02 00 70                             }..p5..p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

70000060 <g_os04d10_i2c_init_regs>:
70000060:	fd 00 00 00 20 00 00 00 20 00 01 00 20 00 01 00     .... ... ... ...
70000070:	20 00 01 00 20 00 01 00 31 00 20 00 38 00 15 00      ... ...1. .8...
70000080:	fd 00 01 00 03 00 00 00 04 00 04 00 06 00 01 00     ................
70000090:	24 00 ff 00 42 00 59 00 45 00 02 00 48 00 0c 00     $...B.Y.E...H...
700000a0:	4b 00 88 00 d4 00 05 00 d5 00 d2 00 d7 00 05 00     K...............
700000b0:	d8 00 d2 00 50 00 01 00 51 00 11 00 52 00 18 00     ....P...Q...R...
700000c0:	53 00 01 00 54 00 01 00 55 00 01 00 57 00 08 00     S...T...U...W...
700000d0:	5c 00 40 00 7c 00 1b 00 90 00 60 00 91 00 0f 00     \.@.|.....`.....
700000e0:	92 00 30 00 93 00 3a 00 94 00 0f 00 95 00 84 00     ..0...:.........
700000f0:	98 00 5d 00 a8 00 50 00 aa 00 14 00 ab 00 05 00     ..]...P.........
70000100:	ac 00 14 00 ad 00 05 00 ae 00 47 00 af 00 10 00     ..........G.....
70000110:	c9 00 28 00 ca 00 5e 00 cb 00 5e 00 cc 00 5e 00     ..(...^...^...^.
70000120:	cd 00 5e 00 ce 00 5c 00 cf 00 5c 00 d0 00 5c 00     ..^...\...\...\.
70000130:	d1 00 5c 00 d2 00 7c 00 d3 00 7c 00 db 00 3f 00     ..\...|...|...?.
70000140:	fd 00 01 00 46 00 77 00 dd 00 00 00 de 00 3f 00     ....F.w.......?.
70000150:	fd 00 03 00 2b 00 0a 00 01 00 22 00 02 00 03 00     ....+.....".....
70000160:	00 00 06 00 2a 00 22 00 29 00 0b 00 1e 00 10 00     ....*.".).......
70000170:	1f 00 02 00 1a 00 24 00 1b 00 62 00 1c 00 ce 00     ......$...b.....
70000180:	1d 00 d3 00 04 00 0f 00 36 00 00 00 37 00 05 00     ........6...7...
70000190:	38 00 09 00 39 00 19 00 3a 00 38 00 3b 00 22 00     8...9...:.8.;.".
700001a0:	3c 00 22 00 3d 00 22 00 3e 00 03 00 fd 00 02 00     <.".=.".>.......
700001b0:	ce 00 65 00 fd 00 03 00 03 00 30 00 05 00 00 00     ..e.......0.....
700001c0:	12 00 20 00 13 00 40 00 21 00 ca 00 27 00 85 00     .. ...@.!...'...
700001d0:	2c 00 55 00 2d 00 08 00 2e 00 ca 00 3f 00 e7 00     ,.U.-.......?...
700001e0:	fd 00 00 00 8b 00 01 00 8d 00 00 00 fd 00 01 00     ................
700001f0:	01 00 02 00 fd 00 05 00 c4 00 62 00 c5 00 62 00     ..........b...b.
70000200:	c6 00 62 00 c7 00 62 00 f0 00 40 00 f1 00 40 00     ..b...b...@...@.
70000210:	f2 00 40 00 f3 00 40 00 f4 00 00 00 f9 00 03 00     ..@...@.........
70000220:	fa 00 5d 00 fb 00 6b 00 b1 00 01 00 fd 00 00 00     ..]...k.........
70000230:	20 00 03 00                                          ...

70000234 <rts_isp_set_voe_ops>:
70000234:	4b01      	ldr	r3, [pc, #4]	; (7000023c <rts_isp_set_voe_ops+0x8>)
70000236:	6018      	str	r0, [r3, #0]
70000238:	4770      	bx	lr
7000023a:	bf00      	nop
7000023c:	70000048 	.word	0x70000048

70000240 <isp_driver_is_fpga>:
70000240:	2000      	movs	r0, #0
70000242:	4770      	bx	lr

70000244 <os04d10_get_info>:
70000244:	b510      	push	{r4, lr}
70000246:	2800      	cmp	r0, #0
70000248:	d14a      	bne.n	700002e0 <os04d10_get_info+0x9c>
7000024a:	2900      	cmp	r1, #0
7000024c:	d048      	beq.n	700002e0 <os04d10_get_info+0x9c>
7000024e:	f44f 6220 	mov.w	r2, #2560	; 0xa00
70000252:	f44f 63b4 	mov.w	r3, #1440	; 0x5a0
70000256:	f44f 747a 	mov.w	r4, #1000	; 0x3e8
7000025a:	f8df c08c 	ldr.w	ip, [pc, #140]	; 700002e8 <os04d10_get_info+0xa4>
7000025e:	7108      	strb	r0, [r1, #4]
70000260:	f8c1 009c 	str.w	r0, [r1, #156]	; 0x9c
70000264:	f881 00b0 	strb.w	r0, [r1, #176]	; 0xb0
70000268:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
7000026c:	f881 02e4 	strb.w	r0, [r1, #740]	; 0x2e4
70000270:	e9c1 2302 	strd	r2, r3, [r1, #8]
70000274:	e9c1 c42a 	strd	ip, r4, [r1, #168]	; 0xa8
70000278:	4a1c      	ldr	r2, [pc, #112]	; (700002ec <os04d10_get_info+0xa8>)
7000027a:	f644 6420 	movw	r4, #20000	; 0x4e20
7000027e:	4b1c      	ldr	r3, [pc, #112]	; (700002f0 <os04d10_get_info+0xac>)
70000280:	7812      	ldrb	r2, [r2, #0]
70000282:	f8c1 40c4 	str.w	r4, [r1, #196]	; 0xc4
70000286:	243c      	movs	r4, #60	; 0x3c
70000288:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
7000028c:	f242 7210 	movw	r2, #10000	; 0x2710
70000290:	f881 4085 	strb.w	r4, [r1, #133]	; 0x85
70000294:	f240 1401 	movw	r4, #257	; 0x101
70000298:	610b      	str	r3, [r1, #16]
7000029a:	2301      	movs	r3, #1
7000029c:	f8c1 20a0 	str.w	r2, [r1, #160]	; 0xa0
700002a0:	2203      	movs	r2, #3
700002a2:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
700002a6:	2405      	movs	r4, #5
700002a8:	600b      	str	r3, [r1, #0]
700002aa:	f881 3098 	strb.w	r3, [r1, #152]	; 0x98
700002ae:	f881 20a4 	strb.w	r2, [r1, #164]	; 0xa4
700002b2:	f881 30bc 	strb.w	r3, [r1, #188]	; 0xbc
700002b6:	f8c1 30c0 	str.w	r3, [r1, #192]	; 0xc0
700002ba:	f8c1 4088 	str.w	r4, [r1, #136]	; 0x88
700002be:	f881 22d8 	strb.w	r2, [r1, #728]	; 0x2d8
700002c2:	f881 32f0 	strb.w	r3, [r1, #752]	; 0x2f0
700002c6:	e9c1 0024 	strd	r0, r0, [r1, #144]	; 0x90
700002ca:	e9c1 302d 	strd	r3, r0, [r1, #180]	; 0xb4
700002ce:	e9c1 00b7 	strd	r0, r0, [r1, #732]	; 0x2dc
700002d2:	e9c1 00ba 	strd	r0, r0, [r1, #744]	; 0x2e8
700002d6:	e9c1 00bd 	strd	r0, r0, [r1, #756]	; 0x2f4
700002da:	f8c1 22d4 	str.w	r2, [r1, #724]	; 0x2d4
700002de:	bd10      	pop	{r4, pc}
700002e0:	f06f 0015 	mvn.w	r0, #21
700002e4:	e7fb      	b.n	700002de <os04d10_get_info+0x9a>
700002e6:	bf00      	nop
700002e8:	016e3600 	.word	0x016e3600
700002ec:	7000004c 	.word	0x7000004c
700002f0:	41f00000 	.word	0x41f00000

700002f4 <os04d10_get_init_info>:
700002f4:	2800      	cmp	r0, #0
700002f6:	d135      	bne.n	70000364 <os04d10_get_init_info+0x70>
700002f8:	b3a2      	cbz	r2, 70000364 <os04d10_get_init_info+0x70>
700002fa:	7809      	ldrb	r1, [r1, #0]
700002fc:	f640 2c08 	movw	ip, #2568	; 0xa08
70000300:	4b1a      	ldr	r3, [pc, #104]	; (7000036c <os04d10_get_init_info+0x78>)
70000302:	6090      	str	r0, [r2, #8]
70000304:	7019      	strb	r1, [r3, #0]
70000306:	491a      	ldr	r1, [pc, #104]	; (70000370 <os04d10_get_init_info+0x7c>)
70000308:	f8c2 0088 	str.w	r0, [r2, #136]	; 0x88
7000030c:	6051      	str	r1, [r2, #4]
7000030e:	2175      	movs	r1, #117	; 0x75
70000310:	6011      	str	r1, [r2, #0]
70000312:	2102      	movs	r1, #2
70000314:	f882 1064 	strb.w	r1, [r2, #100]	; 0x64
70000318:	f240 7103 	movw	r1, #1795	; 0x703
7000031c:	f8a2 1068 	strh.w	r1, [r2, #104]	; 0x68
70000320:	210a      	movs	r1, #10
70000322:	f8a2 1074 	strh.w	r1, [r2, #116]	; 0x74
70000326:	2104      	movs	r1, #4
70000328:	f882 1060 	strb.w	r1, [r2, #96]	; 0x60
7000032c:	f44f 61b5 	mov.w	r1, #1448	; 0x5a8
70000330:	e9c2 c120 	strd	ip, r1, [r2, #128]	; 0x80
70000334:	2101      	movs	r1, #1
70000336:	f8c2 108c 	str.w	r1, [r2, #140]	; 0x8c
7000033a:	f640 4138 	movw	r1, #3128	; 0xc38
7000033e:	f8c2 1094 	str.w	r1, [r2, #148]	; 0x94
70000342:	f240 51c1 	movw	r1, #1473	; 0x5c1
70000346:	8259      	strh	r1, [r3, #18]
70000348:	f8c2 1098 	str.w	r1, [r2, #152]	; 0x98
7000034c:	4909      	ldr	r1, [pc, #36]	; (70000374 <os04d10_get_init_info+0x80>)
7000034e:	f8c2 1090 	str.w	r1, [r2, #144]	; 0x90
70000352:	f64f 213e 	movw	r1, #64062	; 0xfa3e
70000356:	f8c2 109c 	str.w	r1, [r2, #156]	; 0x9c
7000035a:	4907      	ldr	r1, [pc, #28]	; (70000378 <os04d10_get_init_info+0x84>)
7000035c:	6059      	str	r1, [r3, #4]
7000035e:	f8c2 10a0 	str.w	r1, [r2, #160]	; 0xa0
70000362:	4770      	bx	lr
70000364:	f06f 0015 	mvn.w	r0, #21
70000368:	4770      	bx	lr
7000036a:	bf00      	nop
7000036c:	7000004c 	.word	0x7000004c
70000370:	70000060 	.word	0x70000060
70000374:	083d2a90 	.word	0x083d2a90
70000378:	41b50954 	.word	0x41b50954

7000037c <os04d10_start>:
7000037c:	b920      	cbnz	r0, 70000388 <os04d10_start+0xc>
7000037e:	4b04      	ldr	r3, [pc, #16]	; (70000390 <os04d10_start+0x14>)
70000380:	2200      	movs	r2, #0
70000382:	8218      	strh	r0, [r3, #16]
70000384:	609a      	str	r2, [r3, #8]
70000386:	4770      	bx	lr
70000388:	f06f 0015 	mvn.w	r0, #21
7000038c:	4770      	bx	lr
7000038e:	bf00      	nop
70000390:	7000004c 	.word	0x7000004c

70000394 <os04d10_get_tuned_dgain>:
70000394:	b920      	cbnz	r0, 700003a0 <os04d10_get_tuned_dgain+0xc>
70000396:	b119      	cbz	r1, 700003a0 <os04d10_get_tuned_dgain+0xc>
70000398:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
7000039c:	600b      	str	r3, [r1, #0]
7000039e:	4770      	bx	lr
700003a0:	f06f 0015 	mvn.w	r0, #21
700003a4:	4770      	bx	lr
	...

700003a8 <os04d10_get_exposure_gain_info>:
700003a8:	e92d 4ff7 	stmdb	sp!, {r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr}
700003ac:	4689      	mov	r9, r1
700003ae:	4614      	mov	r4, r2
700003b0:	2800      	cmp	r0, #0
700003b2:	f040 808d 	bne.w	700004d0 <os04d10_get_exposure_gain_info+0x128>
700003b6:	2900      	cmp	r1, #0
700003b8:	f000 808a 	beq.w	700004d0 <os04d10_get_exposure_gain_info+0x128>
700003bc:	2a00      	cmp	r2, #0
700003be:	f000 8087 	beq.w	700004d0 <os04d10_get_exposure_gain_info+0x128>
700003c2:	6909      	ldr	r1, [r1, #16]
700003c4:	1d16      	adds	r6, r2, #4
700003c6:	f8d9 0008 	ldr.w	r0, [r9, #8]
700003ca:	f000 fb67 	bl	70000a9c <__aeabi_fmul>
700003ce:	f04f 4183 	mov.w	r1, #1098907648	; 0x41800000
700003d2:	f000 fb63 	bl	70000a9c <__aeabi_fmul>
700003d6:	f000 fd27 	bl	70000e28 <__aeabi_f2uiz>
700003da:	b280      	uxth	r0, r0
700003dc:	280f      	cmp	r0, #15
700003de:	d96d      	bls.n	700004bc <os04d10_get_exposure_gain_info+0x114>
700003e0:	28f8      	cmp	r0, #248	; 0xf8
700003e2:	bf28      	it	cs
700003e4:	20f8      	movcs	r0, #248	; 0xf8
700003e6:	4b3c      	ldr	r3, [pc, #240]	; (700004d8 <os04d10_get_exposure_gain_info+0x130>)
700003e8:	4f3c      	ldr	r7, [pc, #240]	; (700004dc <os04d10_get_exposure_gain_info+0x134>)
700003ea:	f8d9 a018 	ldr.w	sl, [r9, #24]
700003ee:	60e3      	str	r3, [r4, #12]
700003f0:	8a3b      	ldrh	r3, [r7, #16]
700003f2:	459a      	cmp	sl, r3
700003f4:	d064      	beq.n	700004c0 <os04d10_get_exposure_gain_info+0x118>
700003f6:	8a7b      	ldrh	r3, [r7, #18]
700003f8:	fa1f f28a 	uxth.w	r2, sl
700003fc:	2105      	movs	r1, #5
700003fe:	f04f 0b03 	mov.w	fp, #3
70000402:	f1c3 0301 	rsb	r3, r3, #1
70000406:	823a      	strh	r2, [r7, #16]
70000408:	8421      	strh	r1, [r4, #32]
7000040a:	4413      	add	r3, r2
7000040c:	f3c3 2107 	ubfx	r1, r3, #8, #8
70000410:	b2db      	uxtb	r3, r3
70000412:	8461      	strh	r1, [r4, #34]	; 0x22
70000414:	2106      	movs	r1, #6
70000416:	86e3      	strh	r3, [r4, #54]	; 0x36
70000418:	86a1      	strh	r1, [r4, #52]	; 0x34
7000041a:	2514      	movs	r5, #20
7000041c:	2224      	movs	r2, #36	; 0x24
7000041e:	f8d9 9000 	ldr.w	r9, [r9]
70000422:	f10b 0801 	add.w	r8, fp, #1
70000426:	fb05 f50b 	mul.w	r5, r5, fp
7000042a:	4649      	mov	r1, r9
7000042c:	1973      	adds	r3, r6, r5
7000042e:	8158      	strh	r0, [r3, #10]
70000430:	811a      	strh	r2, [r3, #8]
70000432:	68b8      	ldr	r0, [r7, #8]
70000434:	f000 fa28 	bl	70000888 <__aeabi_fsub>
70000438:	2100      	movs	r1, #0
7000043a:	9001      	str	r0, [sp, #4]
7000043c:	f000 fce0 	bl	70000e00 <__aeabi_fcmpge>
70000440:	9b01      	ldr	r3, [sp, #4]
70000442:	2800      	cmp	r0, #0
70000444:	d03f      	beq.n	700004c6 <os04d10_get_exposure_gain_info+0x11e>
70000446:	4926      	ldr	r1, [pc, #152]	; (700004e0 <os04d10_get_exposure_gain_info+0x138>)
70000448:	4618      	mov	r0, r3
7000044a:	f000 fce3 	bl	70000e14 <__aeabi_fcmpgt>
7000044e:	b330      	cbz	r0, 7000049e <os04d10_get_exposure_gain_info+0xf6>
70000450:	6879      	ldr	r1, [r7, #4]
70000452:	4648      	mov	r0, r9
70000454:	f000 fbd6 	bl	70000c04 <__aeabi_fdiv>
70000458:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
7000045c:	f000 fa16 	bl	7000088c <__addsf3>
70000460:	f1aa 0a10 	sub.w	sl, sl, #16
70000464:	f000 fce0 	bl	70000e28 <__aeabi_f2uiz>
70000468:	b280      	uxth	r0, r0
7000046a:	4550      	cmp	r0, sl
7000046c:	d803      	bhi.n	70000476 <os04d10_get_exposure_gain_info+0xce>
7000046e:	2801      	cmp	r0, #1
70000470:	bf38      	it	cc
70000472:	2001      	movcc	r0, #1
70000474:	4682      	mov	sl, r0
70000476:	f105 0314 	add.w	r3, r5, #20
7000047a:	2203      	movs	r2, #3
7000047c:	3528      	adds	r5, #40	; 0x28
7000047e:	f10b 0803 	add.w	r8, fp, #3
70000482:	4433      	add	r3, r6
70000484:	f8c7 9008 	str.w	r9, [r7, #8]
70000488:	4435      	add	r5, r6
7000048a:	811a      	strh	r2, [r3, #8]
7000048c:	f3ca 2207 	ubfx	r2, sl, #8, #8
70000490:	fa5f fa8a 	uxtb.w	sl, sl
70000494:	815a      	strh	r2, [r3, #10]
70000496:	2304      	movs	r3, #4
70000498:	f8a5 a00a 	strh.w	sl, [r5, #10]
7000049c:	812b      	strh	r3, [r5, #8]
7000049e:	2314      	movs	r3, #20
700004a0:	2000      	movs	r0, #0
700004a2:	fb03 6608 	mla	r6, r3, r8, r6
700004a6:	f04f 1301 	mov.w	r3, #65537	; 0x10001
700004aa:	60b3      	str	r3, [r6, #8]
700004ac:	23fd      	movs	r3, #253	; 0xfd
700004ae:	61f3      	str	r3, [r6, #28]
700004b0:	f108 0302 	add.w	r3, r8, #2
700004b4:	6023      	str	r3, [r4, #0]
700004b6:	b003      	add	sp, #12
700004b8:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
700004bc:	2010      	movs	r0, #16
700004be:	e792      	b.n	700003e6 <os04d10_get_exposure_gain_info+0x3e>
700004c0:	f04f 0b01 	mov.w	fp, #1
700004c4:	e7a9      	b.n	7000041a <os04d10_get_exposure_gain_info+0x72>
700004c6:	4907      	ldr	r1, [pc, #28]	; (700004e4 <os04d10_get_exposure_gain_info+0x13c>)
700004c8:	4618      	mov	r0, r3
700004ca:	f000 fc85 	bl	70000dd8 <__aeabi_fcmplt>
700004ce:	e7be      	b.n	7000044e <os04d10_get_exposure_gain_info+0xa6>
700004d0:	f06f 0015 	mvn.w	r0, #21
700004d4:	e7ef      	b.n	700004b6 <os04d10_get_exposure_gain_info+0x10e>
700004d6:	bf00      	nop
700004d8:	000100fd 	.word	0x000100fd
700004dc:	7000004c 	.word	0x7000004c
700004e0:	3a83126f 	.word	0x3a83126f
700004e4:	ba83126f 	.word	0xba83126f

700004e8 <os04d10_set_mirror_flip>:
700004e8:	784b      	ldrb	r3, [r1, #1]
700004ea:	780a      	ldrb	r2, [r1, #0]
700004ec:	2b00      	cmp	r3, #0
700004ee:	4826      	ldr	r0, [pc, #152]	; (70000588 <os04d10_set_mirror_flip+0xa0>)
700004f0:	bf14      	ite	ne
700004f2:	2302      	movne	r3, #2
700004f4:	2300      	moveq	r3, #0
700004f6:	6108      	str	r0, [r1, #16]
700004f8:	2a00      	cmp	r2, #0
700004fa:	bf18      	it	ne
700004fc:	f043 0301 	orrne.w	r3, r3, #1
70000500:	2201      	movs	r2, #1
70000502:	2b02      	cmp	r3, #2
70000504:	708a      	strb	r2, [r1, #2]
70000506:	d025      	beq.n	70000554 <os04d10_set_mirror_flip+0x6c>
70000508:	2b03      	cmp	r3, #3
7000050a:	d031      	beq.n	70000570 <os04d10_set_mirror_flip+0x88>
7000050c:	4293      	cmp	r3, r2
7000050e:	d00f      	beq.n	70000530 <os04d10_set_mirror_flip+0x48>
70000510:	2332      	movs	r3, #50	; 0x32
70000512:	2000      	movs	r0, #0
70000514:	624b      	str	r3, [r1, #36]	; 0x24
70000516:	f04f 1301 	mov.w	r3, #65537	; 0x10001
7000051a:	638b      	str	r3, [r1, #56]	; 0x38
7000051c:	23fd      	movs	r3, #253	; 0xfd
7000051e:	64cb      	str	r3, [r1, #76]	; 0x4c
70000520:	4b1a      	ldr	r3, [pc, #104]	; (7000058c <os04d10_set_mirror_flip+0xa4>)
70000522:	f8c3 0c00 	str.w	r0, [r3, #3072]	; 0xc00
70000526:	f8c3 2c04 	str.w	r2, [r3, #3076]	; 0xc04
7000052a:	f8c3 2c10 	str.w	r2, [r3, #3088]	; 0xc10
7000052e:	e00d      	b.n	7000054c <os04d10_set_mirror_flip+0x64>
70000530:	4a17      	ldr	r2, [pc, #92]	; (70000590 <os04d10_set_mirror_flip+0xa8>)
70000532:	624a      	str	r2, [r1, #36]	; 0x24
70000534:	f04f 1201 	mov.w	r2, #65537	; 0x10001
70000538:	638a      	str	r2, [r1, #56]	; 0x38
7000053a:	22fd      	movs	r2, #253	; 0xfd
7000053c:	64ca      	str	r2, [r1, #76]	; 0x4c
7000053e:	4a13      	ldr	r2, [pc, #76]	; (7000058c <os04d10_set_mirror_flip+0xa4>)
70000540:	f8c2 3c00 	str.w	r3, [r2, #3072]	; 0xc00
70000544:	f8c2 3c04 	str.w	r3, [r2, #3076]	; 0xc04
70000548:	f8c2 3c10 	str.w	r3, [r2, #3088]	; 0xc10
7000054c:	2304      	movs	r3, #4
7000054e:	2000      	movs	r0, #0
70000550:	604b      	str	r3, [r1, #4]
70000552:	4770      	bx	lr
70000554:	4b0f      	ldr	r3, [pc, #60]	; (70000594 <os04d10_set_mirror_flip+0xac>)
70000556:	2000      	movs	r0, #0
70000558:	624b      	str	r3, [r1, #36]	; 0x24
7000055a:	f04f 1301 	mov.w	r3, #65537	; 0x10001
7000055e:	638b      	str	r3, [r1, #56]	; 0x38
70000560:	23fd      	movs	r3, #253	; 0xfd
70000562:	64cb      	str	r3, [r1, #76]	; 0x4c
70000564:	4b09      	ldr	r3, [pc, #36]	; (7000058c <os04d10_set_mirror_flip+0xa4>)
70000566:	f8c3 0c00 	str.w	r0, [r3, #3072]	; 0xc00
7000056a:	f8c3 0c04 	str.w	r0, [r3, #3076]	; 0xc04
7000056e:	e7dc      	b.n	7000052a <os04d10_set_mirror_flip+0x42>
70000570:	4b09      	ldr	r3, [pc, #36]	; (70000598 <os04d10_set_mirror_flip+0xb0>)
70000572:	2000      	movs	r0, #0
70000574:	624b      	str	r3, [r1, #36]	; 0x24
70000576:	f04f 1301 	mov.w	r3, #65537	; 0x10001
7000057a:	638b      	str	r3, [r1, #56]	; 0x38
7000057c:	23fd      	movs	r3, #253	; 0xfd
7000057e:	64cb      	str	r3, [r1, #76]	; 0x4c
70000580:	4b02      	ldr	r3, [pc, #8]	; (7000058c <os04d10_set_mirror_flip+0xa4>)
70000582:	f8c3 2c00 	str.w	r2, [r3, #3072]	; 0xc00
70000586:	e7f0      	b.n	7000056a <os04d10_set_mirror_flip+0x82>
70000588:	000100fd 	.word	0x000100fd
7000058c:	40300000 	.word	0x40300000
70000590:	00010032 	.word	0x00010032
70000594:	00020032 	.word	0x00020032
70000598:	00030032 	.word	0x00030032

7000059c <os04d10_check>:
7000059c:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
7000059e:	4d1a      	ldr	r5, [pc, #104]	; (70000608 <os04d10_check+0x6c>)
700005a0:	4606      	mov	r6, r0
700005a2:	682b      	ldr	r3, [r5, #0]
700005a4:	685b      	ldr	r3, [r3, #4]
700005a6:	4798      	blx	r3
700005a8:	23fd      	movs	r3, #253	; 0xfd
700005aa:	a901      	add	r1, sp, #4
700005ac:	4630      	mov	r0, r6
700005ae:	9301      	str	r3, [sp, #4]
700005b0:	682b      	ldr	r3, [r5, #0]
700005b2:	691b      	ldr	r3, [r3, #16]
700005b4:	4798      	blx	r3
700005b6:	4604      	mov	r4, r0
700005b8:	bb00      	cbnz	r0, 700005fc <os04d10_check+0x60>
700005ba:	2304      	movs	r3, #4
700005bc:	a901      	add	r1, sp, #4
700005be:	4630      	mov	r0, r6
700005c0:	f8ad 3004 	strh.w	r3, [sp, #4]
700005c4:	682b      	ldr	r3, [r5, #0]
700005c6:	68db      	ldr	r3, [r3, #12]
700005c8:	4798      	blx	r3
700005ca:	4604      	mov	r4, r0
700005cc:	b9b0      	cbnz	r0, 700005fc <os04d10_check+0x60>
700005ce:	2305      	movs	r3, #5
700005d0:	a901      	add	r1, sp, #4
700005d2:	4630      	mov	r0, r6
700005d4:	f8bd 7006 	ldrh.w	r7, [sp, #6]
700005d8:	f8ad 3004 	strh.w	r3, [sp, #4]
700005dc:	682b      	ldr	r3, [r5, #0]
700005de:	68db      	ldr	r3, [r3, #12]
700005e0:	4798      	blx	r3
700005e2:	4604      	mov	r4, r0
700005e4:	b950      	cbnz	r0, 700005fc <os04d10_check+0x60>
700005e6:	f8bd 3006 	ldrh.w	r3, [sp, #6]
700005ea:	f244 4210 	movw	r2, #17424	; 0x4410
700005ee:	ea43 2307 	orr.w	r3, r3, r7, lsl #8
700005f2:	4293      	cmp	r3, r2
700005f4:	bf0c      	ite	eq
700005f6:	4604      	moveq	r4, r0
700005f8:	f06f 0415 	mvnne.w	r4, #21
700005fc:	682b      	ldr	r3, [r5, #0]
700005fe:	689b      	ldr	r3, [r3, #8]
70000600:	4798      	blx	r3
70000602:	4620      	mov	r0, r4
70000604:	b003      	add	sp, #12
70000606:	bdf0      	pop	{r4, r5, r6, r7, pc}
70000608:	70000048 	.word	0x70000048

7000060c <os04d10_get_exposure_range>:
7000060c:	460a      	mov	r2, r1
7000060e:	b538      	push	{r3, r4, r5, lr}
70000610:	b978      	cbnz	r0, 70000632 <os04d10_get_exposure_range+0x26>
70000612:	4909      	ldr	r1, [pc, #36]	; (70000638 <os04d10_get_exposure_range+0x2c>)
70000614:	780c      	ldrb	r4, [r1, #0]
70000616:	b95c      	cbnz	r4, 70000630 <os04d10_get_exposure_range+0x24>
70000618:	684d      	ldr	r5, [r1, #4]
7000061a:	f1a2 0010 	sub.w	r0, r2, #16
7000061e:	601d      	str	r5, [r3, #0]
70000620:	f000 f9e4 	bl	700009ec <__aeabi_ui2f>
70000624:	4629      	mov	r1, r5
70000626:	f000 fa39 	bl	70000a9c <__aeabi_fmul>
7000062a:	9b04      	ldr	r3, [sp, #16]
7000062c:	6018      	str	r0, [r3, #0]
7000062e:	4620      	mov	r0, r4
70000630:	bd38      	pop	{r3, r4, r5, pc}
70000632:	f06f 0015 	mvn.w	r0, #21
70000636:	e7fb      	b.n	70000630 <os04d10_get_exposure_range+0x24>
70000638:	7000004c 	.word	0x7000004c

7000063c <os04d10_get_tuned_again>:
7000063c:	b510      	push	{r4, lr}
7000063e:	460c      	mov	r4, r1
70000640:	b9c0      	cbnz	r0, 70000674 <os04d10_get_tuned_again+0x38>
70000642:	f04f 4183 	mov.w	r1, #1098907648	; 0x41800000
70000646:	6820      	ldr	r0, [r4, #0]
70000648:	f000 fa28 	bl	70000a9c <__aeabi_fmul>
7000064c:	f000 fbec 	bl	70000e28 <__aeabi_f2uiz>
70000650:	b280      	uxth	r0, r0
70000652:	280f      	cmp	r0, #15
70000654:	d90c      	bls.n	70000670 <os04d10_get_tuned_again+0x34>
70000656:	28f8      	cmp	r0, #248	; 0xf8
70000658:	bf28      	it	cs
7000065a:	20f8      	movcs	r0, #248	; 0xf8
7000065c:	b2c0      	uxtb	r0, r0
7000065e:	f000 f9c5 	bl	700009ec <__aeabi_ui2f>
70000662:	f04f 5176 	mov.w	r1, #1031798784	; 0x3d800000
70000666:	f000 fa19 	bl	70000a9c <__aeabi_fmul>
7000066a:	6020      	str	r0, [r4, #0]
7000066c:	2000      	movs	r0, #0
7000066e:	bd10      	pop	{r4, pc}
70000670:	2010      	movs	r0, #16
70000672:	e7f3      	b.n	7000065c <os04d10_get_tuned_again+0x20>
70000674:	f06f 0015 	mvn.w	r0, #21
70000678:	e7f9      	b.n	7000066e <os04d10_get_tuned_again+0x32>
	...

7000067c <rts_isp_get_sensor_ops>:
7000067c:	4800      	ldr	r0, [pc, #0]	; (70000680 <rts_isp_get_sensor_ops+0x4>)
7000067e:	4770      	bx	lr
70000680:	70000684 	.word	0x70000684

70000684 <os04d10_ops>:
70000684:	73000005 3430736f 00303164 00000000     ...sos04d10.....
	...
700006a8:	70000245 700002f5 7000060d 7000063d     E..p...p...p=..p
700006b8:	70000395 700003a9 00000000 00000000     ...p...p........
700006c8:	7000037d 00000000 00000000 00000000     }..p............
700006d8:	700004e9 00000000 00000000 00000000     ...p............
700006e8:	7000059d 00000000 00000000 00000000     ...p............
	...
70000718:	0cfff04f 52d0ea1c ea1cbf1e ea9253d1     O......R.....S..
70000728:	ea930f0c d06f0f0c ea80441a 02400c01     ......o..D....@.
70000738:	ea5fbf18 d01e2141 6300f04f 1050ea43     .._.A!..O..cC.P.
70000748:	1151ea43 3101fba0 4000f00c 0f00f5b1     C.Q....1...@....
70000758:	0049bf3e 71d3ea41 ea40005b f1620001     >.I.A..q[.@...b.
70000768:	2afd027f f1b3d81d eb404f00 bf0850c2     ...*.....O@..P..
70000778:	0001f020 f0904770 f00c0f00 bf084c00      ...pG.......L..
70000788:	ea4c0249 ea402050 3a7f2051 f1d2bfc2     I.L.P @.Q .:....
70000798:	ea4003ff 477050c2 0000f440 0300f04f     ..@..PpG@...O...
700007a8:	dc5d3a01 0f19f112 f000bfdc 47704000     .:]..........@pG
700007b8:	0200f1c2 fa210041 f1c2f102 fa000220     ....A.!..... ...
700007c8:	ea5ffc02 f1400031 ea530000 bf08034c     .._.1.@...S.L...
700007d8:	70dcea20 f0924770 f0000f00 bf024c00      ..ppG.......L..
700007e8:	f4100040 3a010f00 ea40d0f9 f093000c     @......:..@.....
700007f8:	f0010f00 bf024c00 f4110049 3b010f00     .....L..I......;
70000808:	ea41d0f9 e78f010c 53d1ea0c 0f0cea92     ..A........S....
70000818:	ea93bf18 d00a0f0c 4c00f030 f031bf18     ........0..L..1.
70000828:	d1d84c00 0001ea80 4000f000 f0904770     .L.........@pG..
70000838:	bf170f00 4f00f090 f0914608 f0910f00     .......O.F......
70000848:	d0144f00 0f0cea92 0242d101 ea93d10f     .O........B.....
70000858:	d1030f0c bf18024b d1084608 0001ea80     ....K....F......
70000868:	4000f000 40fef040 0000f440 f0404770     ...@@..@@...pG@.
70000878:	f44040fe 47700040                       .@@.@.pG

70000880 <__aeabi_frsub>:
70000880:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70000884:	e002      	b.n	7000088c <__addsf3>
70000886:	bf00      	nop

70000888 <__aeabi_fsub>:
70000888:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

7000088c <__addsf3>:
7000088c:	0042      	lsls	r2, r0, #1
7000088e:	bf1f      	itttt	ne
70000890:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70000894:	ea92 0f03 	teqne	r2, r3
70000898:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
7000089c:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700008a0:	d06a      	beq.n	70000978 <__addsf3+0xec>
700008a2:	ea4f 6212 	mov.w	r2, r2, lsr #24
700008a6:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
700008aa:	bfc1      	itttt	gt
700008ac:	18d2      	addgt	r2, r2, r3
700008ae:	4041      	eorgt	r1, r0
700008b0:	4048      	eorgt	r0, r1
700008b2:	4041      	eorgt	r1, r0
700008b4:	bfb8      	it	lt
700008b6:	425b      	neglt	r3, r3
700008b8:	2b19      	cmp	r3, #25
700008ba:	bf88      	it	hi
700008bc:	4770      	bxhi	lr
700008be:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
700008c2:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700008c6:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
700008ca:	bf18      	it	ne
700008cc:	4240      	negne	r0, r0
700008ce:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
700008d2:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
700008d6:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
700008da:	bf18      	it	ne
700008dc:	4249      	negne	r1, r1
700008de:	ea92 0f03 	teq	r2, r3
700008e2:	d03f      	beq.n	70000964 <__addsf3+0xd8>
700008e4:	f1a2 0201 	sub.w	r2, r2, #1
700008e8:	fa41 fc03 	asr.w	ip, r1, r3
700008ec:	eb10 000c 	adds.w	r0, r0, ip
700008f0:	f1c3 0320 	rsb	r3, r3, #32
700008f4:	fa01 f103 	lsl.w	r1, r1, r3
700008f8:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
700008fc:	d502      	bpl.n	70000904 <__addsf3+0x78>
700008fe:	4249      	negs	r1, r1
70000900:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70000904:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70000908:	d313      	bcc.n	70000932 <__addsf3+0xa6>
7000090a:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
7000090e:	d306      	bcc.n	7000091e <__addsf3+0x92>
70000910:	0840      	lsrs	r0, r0, #1
70000912:	ea4f 0131 	mov.w	r1, r1, rrx
70000916:	f102 0201 	add.w	r2, r2, #1
7000091a:	2afe      	cmp	r2, #254	; 0xfe
7000091c:	d251      	bcs.n	700009c2 <__addsf3+0x136>
7000091e:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
70000922:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000926:	bf08      	it	eq
70000928:	f020 0001 	biceq.w	r0, r0, #1
7000092c:	ea40 0003 	orr.w	r0, r0, r3
70000930:	4770      	bx	lr
70000932:	0049      	lsls	r1, r1, #1
70000934:	eb40 0000 	adc.w	r0, r0, r0
70000938:	3a01      	subs	r2, #1
7000093a:	bf28      	it	cs
7000093c:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70000940:	d2ed      	bcs.n	7000091e <__addsf3+0x92>
70000942:	fab0 fc80 	clz	ip, r0
70000946:	f1ac 0c08 	sub.w	ip, ip, #8
7000094a:	ebb2 020c 	subs.w	r2, r2, ip
7000094e:	fa00 f00c 	lsl.w	r0, r0, ip
70000952:	bfaa      	itet	ge
70000954:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
70000958:	4252      	neglt	r2, r2
7000095a:	4318      	orrge	r0, r3
7000095c:	bfbc      	itt	lt
7000095e:	40d0      	lsrlt	r0, r2
70000960:	4318      	orrlt	r0, r3
70000962:	4770      	bx	lr
70000964:	f092 0f00 	teq	r2, #0
70000968:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
7000096c:	bf06      	itte	eq
7000096e:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
70000972:	3201      	addeq	r2, #1
70000974:	3b01      	subne	r3, #1
70000976:	e7b5      	b.n	700008e4 <__addsf3+0x58>
70000978:	ea4f 0341 	mov.w	r3, r1, lsl #1
7000097c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000980:	bf18      	it	ne
70000982:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000986:	d021      	beq.n	700009cc <__addsf3+0x140>
70000988:	ea92 0f03 	teq	r2, r3
7000098c:	d004      	beq.n	70000998 <__addsf3+0x10c>
7000098e:	f092 0f00 	teq	r2, #0
70000992:	bf08      	it	eq
70000994:	4608      	moveq	r0, r1
70000996:	4770      	bx	lr
70000998:	ea90 0f01 	teq	r0, r1
7000099c:	bf1c      	itt	ne
7000099e:	2000      	movne	r0, #0
700009a0:	4770      	bxne	lr
700009a2:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
700009a6:	d104      	bne.n	700009b2 <__addsf3+0x126>
700009a8:	0040      	lsls	r0, r0, #1
700009aa:	bf28      	it	cs
700009ac:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
700009b0:	4770      	bx	lr
700009b2:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
700009b6:	bf3c      	itt	cc
700009b8:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
700009bc:	4770      	bxcc	lr
700009be:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
700009c2:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
700009c6:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700009ca:	4770      	bx	lr
700009cc:	ea7f 6222 	mvns.w	r2, r2, asr #24
700009d0:	bf16      	itet	ne
700009d2:	4608      	movne	r0, r1
700009d4:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
700009d8:	4601      	movne	r1, r0
700009da:	0242      	lsls	r2, r0, #9
700009dc:	bf06      	itte	eq
700009de:	ea5f 2341 	movseq.w	r3, r1, lsl #9
700009e2:	ea90 0f01 	teqeq	r0, r1
700009e6:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
700009ea:	4770      	bx	lr

700009ec <__aeabi_ui2f>:
700009ec:	f04f 0300 	mov.w	r3, #0
700009f0:	e004      	b.n	700009fc <__aeabi_i2f+0x8>
700009f2:	bf00      	nop

700009f4 <__aeabi_i2f>:
700009f4:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
700009f8:	bf48      	it	mi
700009fa:	4240      	negmi	r0, r0
700009fc:	ea5f 0c00 	movs.w	ip, r0
70000a00:	bf08      	it	eq
70000a02:	4770      	bxeq	lr
70000a04:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70000a08:	4601      	mov	r1, r0
70000a0a:	f04f 0000 	mov.w	r0, #0
70000a0e:	e01c      	b.n	70000a4a <__aeabi_l2f+0x2a>

70000a10 <__aeabi_ul2f>:
70000a10:	ea50 0201 	orrs.w	r2, r0, r1
70000a14:	bf08      	it	eq
70000a16:	4770      	bxeq	lr
70000a18:	f04f 0300 	mov.w	r3, #0
70000a1c:	e00a      	b.n	70000a34 <__aeabi_l2f+0x14>
70000a1e:	bf00      	nop

70000a20 <__aeabi_l2f>:
70000a20:	ea50 0201 	orrs.w	r2, r0, r1
70000a24:	bf08      	it	eq
70000a26:	4770      	bxeq	lr
70000a28:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70000a2c:	d502      	bpl.n	70000a34 <__aeabi_l2f+0x14>
70000a2e:	4240      	negs	r0, r0
70000a30:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000a34:	ea5f 0c01 	movs.w	ip, r1
70000a38:	bf02      	ittt	eq
70000a3a:	4684      	moveq	ip, r0
70000a3c:	4601      	moveq	r1, r0
70000a3e:	2000      	moveq	r0, #0
70000a40:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70000a44:	bf08      	it	eq
70000a46:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70000a4a:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
70000a4e:	fabc f28c 	clz	r2, ip
70000a52:	3a08      	subs	r2, #8
70000a54:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
70000a58:	db10      	blt.n	70000a7c <__aeabi_l2f+0x5c>
70000a5a:	fa01 fc02 	lsl.w	ip, r1, r2
70000a5e:	4463      	add	r3, ip
70000a60:	fa00 fc02 	lsl.w	ip, r0, r2
70000a64:	f1c2 0220 	rsb	r2, r2, #32
70000a68:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000a6c:	fa20 f202 	lsr.w	r2, r0, r2
70000a70:	eb43 0002 	adc.w	r0, r3, r2
70000a74:	bf08      	it	eq
70000a76:	f020 0001 	biceq.w	r0, r0, #1
70000a7a:	4770      	bx	lr
70000a7c:	f102 0220 	add.w	r2, r2, #32
70000a80:	fa01 fc02 	lsl.w	ip, r1, r2
70000a84:	f1c2 0220 	rsb	r2, r2, #32
70000a88:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
70000a8c:	fa21 f202 	lsr.w	r2, r1, r2
70000a90:	eb43 0002 	adc.w	r0, r3, r2
70000a94:	bf08      	it	eq
70000a96:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000a9a:	4770      	bx	lr

70000a9c <__aeabi_fmul>:
70000a9c:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000aa0:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000aa4:	bf1e      	ittt	ne
70000aa6:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000aaa:	ea92 0f0c 	teqne	r2, ip
70000aae:	ea93 0f0c 	teqne	r3, ip
70000ab2:	d06f      	beq.n	70000b94 <__aeabi_fmul+0xf8>
70000ab4:	441a      	add	r2, r3
70000ab6:	ea80 0c01 	eor.w	ip, r0, r1
70000aba:	0240      	lsls	r0, r0, #9
70000abc:	bf18      	it	ne
70000abe:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000ac2:	d01e      	beq.n	70000b02 <__aeabi_fmul+0x66>
70000ac4:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000ac8:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000acc:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000ad0:	fba0 3101 	umull	r3, r1, r0, r1
70000ad4:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000ad8:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000adc:	bf3e      	ittt	cc
70000ade:	0049      	lslcc	r1, r1, #1
70000ae0:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000ae4:	005b      	lslcc	r3, r3, #1
70000ae6:	ea40 0001 	orr.w	r0, r0, r1
70000aea:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000aee:	2afd      	cmp	r2, #253	; 0xfd
70000af0:	d81d      	bhi.n	70000b2e <__aeabi_fmul+0x92>
70000af2:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000af6:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000afa:	bf08      	it	eq
70000afc:	f020 0001 	biceq.w	r0, r0, #1
70000b00:	4770      	bx	lr
70000b02:	f090 0f00 	teq	r0, #0
70000b06:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000b0a:	bf08      	it	eq
70000b0c:	0249      	lsleq	r1, r1, #9
70000b0e:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000b12:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000b16:	3a7f      	subs	r2, #127	; 0x7f
70000b18:	bfc2      	ittt	gt
70000b1a:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000b1e:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000b22:	4770      	bxgt	lr
70000b24:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000b28:	f04f 0300 	mov.w	r3, #0
70000b2c:	3a01      	subs	r2, #1
70000b2e:	dc5d      	bgt.n	70000bec <__aeabi_fmul+0x150>
70000b30:	f112 0f19 	cmn.w	r2, #25
70000b34:	bfdc      	itt	le
70000b36:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000b3a:	4770      	bxle	lr
70000b3c:	f1c2 0200 	rsb	r2, r2, #0
70000b40:	0041      	lsls	r1, r0, #1
70000b42:	fa21 f102 	lsr.w	r1, r1, r2
70000b46:	f1c2 0220 	rsb	r2, r2, #32
70000b4a:	fa00 fc02 	lsl.w	ip, r0, r2
70000b4e:	ea5f 0031 	movs.w	r0, r1, rrx
70000b52:	f140 0000 	adc.w	r0, r0, #0
70000b56:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000b5a:	bf08      	it	eq
70000b5c:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000b60:	4770      	bx	lr
70000b62:	f092 0f00 	teq	r2, #0
70000b66:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000b6a:	bf02      	ittt	eq
70000b6c:	0040      	lsleq	r0, r0, #1
70000b6e:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000b72:	3a01      	subeq	r2, #1
70000b74:	d0f9      	beq.n	70000b6a <__aeabi_fmul+0xce>
70000b76:	ea40 000c 	orr.w	r0, r0, ip
70000b7a:	f093 0f00 	teq	r3, #0
70000b7e:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000b82:	bf02      	ittt	eq
70000b84:	0049      	lsleq	r1, r1, #1
70000b86:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000b8a:	3b01      	subeq	r3, #1
70000b8c:	d0f9      	beq.n	70000b82 <__aeabi_fmul+0xe6>
70000b8e:	ea41 010c 	orr.w	r1, r1, ip
70000b92:	e78f      	b.n	70000ab4 <__aeabi_fmul+0x18>
70000b94:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000b98:	ea92 0f0c 	teq	r2, ip
70000b9c:	bf18      	it	ne
70000b9e:	ea93 0f0c 	teqne	r3, ip
70000ba2:	d00a      	beq.n	70000bba <__aeabi_fmul+0x11e>
70000ba4:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000ba8:	bf18      	it	ne
70000baa:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000bae:	d1d8      	bne.n	70000b62 <__aeabi_fmul+0xc6>
70000bb0:	ea80 0001 	eor.w	r0, r0, r1
70000bb4:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000bb8:	4770      	bx	lr
70000bba:	f090 0f00 	teq	r0, #0
70000bbe:	bf17      	itett	ne
70000bc0:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000bc4:	4608      	moveq	r0, r1
70000bc6:	f091 0f00 	teqne	r1, #0
70000bca:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000bce:	d014      	beq.n	70000bfa <__aeabi_fmul+0x15e>
70000bd0:	ea92 0f0c 	teq	r2, ip
70000bd4:	d101      	bne.n	70000bda <__aeabi_fmul+0x13e>
70000bd6:	0242      	lsls	r2, r0, #9
70000bd8:	d10f      	bne.n	70000bfa <__aeabi_fmul+0x15e>
70000bda:	ea93 0f0c 	teq	r3, ip
70000bde:	d103      	bne.n	70000be8 <__aeabi_fmul+0x14c>
70000be0:	024b      	lsls	r3, r1, #9
70000be2:	bf18      	it	ne
70000be4:	4608      	movne	r0, r1
70000be6:	d108      	bne.n	70000bfa <__aeabi_fmul+0x15e>
70000be8:	ea80 0001 	eor.w	r0, r0, r1
70000bec:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000bf0:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000bf4:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000bf8:	4770      	bx	lr
70000bfa:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000bfe:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000c02:	4770      	bx	lr

70000c04 <__aeabi_fdiv>:
70000c04:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000c08:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000c0c:	bf1e      	ittt	ne
70000c0e:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000c12:	ea92 0f0c 	teqne	r2, ip
70000c16:	ea93 0f0c 	teqne	r3, ip
70000c1a:	d069      	beq.n	70000cf0 <__aeabi_fdiv+0xec>
70000c1c:	eba2 0203 	sub.w	r2, r2, r3
70000c20:	ea80 0c01 	eor.w	ip, r0, r1
70000c24:	0249      	lsls	r1, r1, #9
70000c26:	ea4f 2040 	mov.w	r0, r0, lsl #9
70000c2a:	d037      	beq.n	70000c9c <__aeabi_fdiv+0x98>
70000c2c:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70000c30:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70000c34:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70000c38:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000c3c:	428b      	cmp	r3, r1
70000c3e:	bf38      	it	cc
70000c40:	005b      	lslcc	r3, r3, #1
70000c42:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70000c46:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70000c4a:	428b      	cmp	r3, r1
70000c4c:	bf24      	itt	cs
70000c4e:	1a5b      	subcs	r3, r3, r1
70000c50:	ea40 000c 	orrcs.w	r0, r0, ip
70000c54:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70000c58:	bf24      	itt	cs
70000c5a:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
70000c5e:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70000c62:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70000c66:	bf24      	itt	cs
70000c68:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
70000c6c:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
70000c70:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
70000c74:	bf24      	itt	cs
70000c76:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
70000c7a:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
70000c7e:	011b      	lsls	r3, r3, #4
70000c80:	bf18      	it	ne
70000c82:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70000c86:	d1e0      	bne.n	70000c4a <__aeabi_fdiv+0x46>
70000c88:	2afd      	cmp	r2, #253	; 0xfd
70000c8a:	f63f af50 	bhi.w	70000b2e <__aeabi_fmul+0x92>
70000c8e:	428b      	cmp	r3, r1
70000c90:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000c94:	bf08      	it	eq
70000c96:	f020 0001 	biceq.w	r0, r0, #1
70000c9a:	4770      	bx	lr
70000c9c:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000ca0:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000ca4:	327f      	adds	r2, #127	; 0x7f
70000ca6:	bfc2      	ittt	gt
70000ca8:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000cac:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000cb0:	4770      	bxgt	lr
70000cb2:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000cb6:	f04f 0300 	mov.w	r3, #0
70000cba:	3a01      	subs	r2, #1
70000cbc:	e737      	b.n	70000b2e <__aeabi_fmul+0x92>
70000cbe:	f092 0f00 	teq	r2, #0
70000cc2:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000cc6:	bf02      	ittt	eq
70000cc8:	0040      	lsleq	r0, r0, #1
70000cca:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000cce:	3a01      	subeq	r2, #1
70000cd0:	d0f9      	beq.n	70000cc6 <__aeabi_fdiv+0xc2>
70000cd2:	ea40 000c 	orr.w	r0, r0, ip
70000cd6:	f093 0f00 	teq	r3, #0
70000cda:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000cde:	bf02      	ittt	eq
70000ce0:	0049      	lsleq	r1, r1, #1
70000ce2:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000ce6:	3b01      	subeq	r3, #1
70000ce8:	d0f9      	beq.n	70000cde <__aeabi_fdiv+0xda>
70000cea:	ea41 010c 	orr.w	r1, r1, ip
70000cee:	e795      	b.n	70000c1c <__aeabi_fdiv+0x18>
70000cf0:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000cf4:	ea92 0f0c 	teq	r2, ip
70000cf8:	d108      	bne.n	70000d0c <__aeabi_fdiv+0x108>
70000cfa:	0242      	lsls	r2, r0, #9
70000cfc:	f47f af7d 	bne.w	70000bfa <__aeabi_fmul+0x15e>
70000d00:	ea93 0f0c 	teq	r3, ip
70000d04:	f47f af70 	bne.w	70000be8 <__aeabi_fmul+0x14c>
70000d08:	4608      	mov	r0, r1
70000d0a:	e776      	b.n	70000bfa <__aeabi_fmul+0x15e>
70000d0c:	ea93 0f0c 	teq	r3, ip
70000d10:	d104      	bne.n	70000d1c <__aeabi_fdiv+0x118>
70000d12:	024b      	lsls	r3, r1, #9
70000d14:	f43f af4c 	beq.w	70000bb0 <__aeabi_fmul+0x114>
70000d18:	4608      	mov	r0, r1
70000d1a:	e76e      	b.n	70000bfa <__aeabi_fmul+0x15e>
70000d1c:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000d20:	bf18      	it	ne
70000d22:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000d26:	d1ca      	bne.n	70000cbe <__aeabi_fdiv+0xba>
70000d28:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70000d2c:	f47f af5c 	bne.w	70000be8 <__aeabi_fmul+0x14c>
70000d30:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70000d34:	f47f af3c 	bne.w	70000bb0 <__aeabi_fmul+0x114>
70000d38:	e75f      	b.n	70000bfa <__aeabi_fmul+0x15e>
70000d3a:	bf00      	nop

70000d3c <__gesf2>:
70000d3c:	f04f 3cff 	mov.w	ip, #4294967295
70000d40:	e006      	b.n	70000d50 <__cmpsf2+0x4>
70000d42:	bf00      	nop

70000d44 <__lesf2>:
70000d44:	f04f 0c01 	mov.w	ip, #1
70000d48:	e002      	b.n	70000d50 <__cmpsf2+0x4>
70000d4a:	bf00      	nop

70000d4c <__cmpsf2>:
70000d4c:	f04f 0c01 	mov.w	ip, #1
70000d50:	f84d cd04 	str.w	ip, [sp, #-4]!
70000d54:	ea4f 0240 	mov.w	r2, r0, lsl #1
70000d58:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000d5c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000d60:	bf18      	it	ne
70000d62:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000d66:	d011      	beq.n	70000d8c <__cmpsf2+0x40>
70000d68:	b001      	add	sp, #4
70000d6a:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
70000d6e:	bf18      	it	ne
70000d70:	ea90 0f01 	teqne	r0, r1
70000d74:	bf58      	it	pl
70000d76:	ebb2 0003 	subspl.w	r0, r2, r3
70000d7a:	bf88      	it	hi
70000d7c:	17c8      	asrhi	r0, r1, #31
70000d7e:	bf38      	it	cc
70000d80:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70000d84:	bf18      	it	ne
70000d86:	f040 0001 	orrne.w	r0, r0, #1
70000d8a:	4770      	bx	lr
70000d8c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000d90:	d102      	bne.n	70000d98 <__cmpsf2+0x4c>
70000d92:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70000d96:	d105      	bne.n	70000da4 <__cmpsf2+0x58>
70000d98:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70000d9c:	d1e4      	bne.n	70000d68 <__cmpsf2+0x1c>
70000d9e:	ea5f 2c41 	movs.w	ip, r1, lsl #9
70000da2:	d0e1      	beq.n	70000d68 <__cmpsf2+0x1c>
70000da4:	f85d 0b04 	ldr.w	r0, [sp], #4
70000da8:	4770      	bx	lr
70000daa:	bf00      	nop

70000dac <__aeabi_cfrcmple>:
70000dac:	4684      	mov	ip, r0
70000dae:	4608      	mov	r0, r1
70000db0:	4661      	mov	r1, ip
70000db2:	e7ff      	b.n	70000db4 <__aeabi_cfcmpeq>

70000db4 <__aeabi_cfcmpeq>:
70000db4:	b50f      	push	{r0, r1, r2, r3, lr}
70000db6:	f7ff ffc9 	bl	70000d4c <__cmpsf2>
70000dba:	2800      	cmp	r0, #0
70000dbc:	bf48      	it	mi
70000dbe:	f110 0f00 	cmnmi.w	r0, #0
70000dc2:	bd0f      	pop	{r0, r1, r2, r3, pc}

70000dc4 <__aeabi_fcmpeq>:
70000dc4:	f84d ed08 	str.w	lr, [sp, #-8]!
70000dc8:	f7ff fff4 	bl	70000db4 <__aeabi_cfcmpeq>
70000dcc:	bf0c      	ite	eq
70000dce:	2001      	moveq	r0, #1
70000dd0:	2000      	movne	r0, #0
70000dd2:	f85d fb08 	ldr.w	pc, [sp], #8
70000dd6:	bf00      	nop

70000dd8 <__aeabi_fcmplt>:
70000dd8:	f84d ed08 	str.w	lr, [sp, #-8]!
70000ddc:	f7ff ffea 	bl	70000db4 <__aeabi_cfcmpeq>
70000de0:	bf34      	ite	cc
70000de2:	2001      	movcc	r0, #1
70000de4:	2000      	movcs	r0, #0
70000de6:	f85d fb08 	ldr.w	pc, [sp], #8
70000dea:	bf00      	nop

70000dec <__aeabi_fcmple>:
70000dec:	f84d ed08 	str.w	lr, [sp, #-8]!
70000df0:	f7ff ffe0 	bl	70000db4 <__aeabi_cfcmpeq>
70000df4:	bf94      	ite	ls
70000df6:	2001      	movls	r0, #1
70000df8:	2000      	movhi	r0, #0
70000dfa:	f85d fb08 	ldr.w	pc, [sp], #8
70000dfe:	bf00      	nop

70000e00 <__aeabi_fcmpge>:
70000e00:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e04:	f7ff ffd2 	bl	70000dac <__aeabi_cfrcmple>
70000e08:	bf94      	ite	ls
70000e0a:	2001      	movls	r0, #1
70000e0c:	2000      	movhi	r0, #0
70000e0e:	f85d fb08 	ldr.w	pc, [sp], #8
70000e12:	bf00      	nop

70000e14 <__aeabi_fcmpgt>:
70000e14:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e18:	f7ff ffc8 	bl	70000dac <__aeabi_cfrcmple>
70000e1c:	bf34      	ite	cc
70000e1e:	2001      	movcc	r0, #1
70000e20:	2000      	movcs	r0, #0
70000e22:	f85d fb08 	ldr.w	pc, [sp], #8
70000e26:	bf00      	nop

70000e28 <__aeabi_f2uiz>:
70000e28:	0042      	lsls	r2, r0, #1
70000e2a:	d20e      	bcs.n	70000e4a <__aeabi_f2uiz+0x22>
70000e2c:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70000e30:	d30b      	bcc.n	70000e4a <__aeabi_f2uiz+0x22>
70000e32:	f04f 039e 	mov.w	r3, #158	; 0x9e
70000e36:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70000e3a:	d409      	bmi.n	70000e50 <__aeabi_f2uiz+0x28>
70000e3c:	ea4f 2300 	mov.w	r3, r0, lsl #8
70000e40:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000e44:	fa23 f002 	lsr.w	r0, r3, r2
70000e48:	4770      	bx	lr
70000e4a:	f04f 0000 	mov.w	r0, #0
70000e4e:	4770      	bx	lr
70000e50:	f112 0f61 	cmn.w	r2, #97	; 0x61
70000e54:	d101      	bne.n	70000e5a <__aeabi_f2uiz+0x32>
70000e56:	0242      	lsls	r2, r0, #9
70000e58:	d102      	bne.n	70000e60 <__aeabi_f2uiz+0x38>
70000e5a:	f04f 30ff 	mov.w	r0, #4294967295
70000e5e:	4770      	bx	lr
70000e60:	f04f 0000 	mov.w	r0, #0
70000e64:	4770      	bx	lr
70000e66:	bf00      	nop
