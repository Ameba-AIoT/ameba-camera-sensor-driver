
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	69 05 00 70 11 01 00 70                             i..p...p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

7000006c <g_ps5268_i2c_init_regs_asic>:
7000006c:	0b 01 07 00 14 01 12 00 15 01 c0 00 78 01 c0 00     ............x...
7000007c:	79 01 2a 00 2e 02 0e 00 2f 02 19 00 2d 02 01 00     y.*...../...-...
7000008c:	26 02 b1 00 27 02 39 00 1c 02 00 00 33 02 70 00     &...'.9.....3.p.
7000009c:	4b 02 05 00 4d 02 11 00 52 02 16 00 53 02 26 00     K...M...R...S.&.
700000ac:	54 02 61 00 55 02 11 00 64 06 02 00 65 06 ad 00     T.a.U...d...e...
700000bc:	02 0b 02 00 0a 0b ff 00 0c 0b 00 00 00 12 00 00     ................
700000cc:	01 12 01 00 00 13 00 00 01 13 01 00 09 14 1a 00     ................
700000dc:	0a 14 15 00 11 14 01 00 15 14 04 00 17 14 03 00     ................
700000ec:	18 14 02 00 06 14 04 00 10 14 02 00 0f 14 01 00     ................
700000fc:	11 01 01 00 0f 01 01 00                             ........

70000104 <real_slave_addr>:
70000104:	48 00 00 00                                         H...

70000108 <slave_addr_list>:
70000108:	48 00 00 00 4c 00 00 00                             H...L...

70000110 <rts_isp_set_voe_ops>:
70000110:	4b01      	ldr	r3, [pc, #4]	; (70000118 <rts_isp_set_voe_ops+0x8>)
70000112:	6018      	str	r0, [r3, #0]
70000114:	4770      	bx	lr
70000116:	bf00      	nop
70000118:	70000048 	.word	0x70000048

7000011c <isp_driver_is_fpga>:
7000011c:	2000      	movs	r0, #0
7000011e:	4770      	bx	lr

70000120 <ps5268_get_info>:
70000120:	b530      	push	{r4, r5, lr}
70000122:	2800      	cmp	r0, #0
70000124:	d156      	bne.n	700001d4 <ps5268_get_info+0xb4>
70000126:	2900      	cmp	r1, #0
70000128:	d054      	beq.n	700001d4 <ps5268_get_info+0xb4>
7000012a:	4b2c      	ldr	r3, [pc, #176]	; (700001dc <ps5268_get_info+0xbc>)
7000012c:	f44f 62f0 	mov.w	r2, #1920	; 0x780
70000130:	f241 3488 	movw	r4, #5000	; 0x1388
70000134:	f8df c0a8 	ldr.w	ip, [pc, #168]	; 700001e0 <ps5268_get_info+0xc0>
70000138:	610b      	str	r3, [r1, #16]
7000013a:	f44f 6387 	mov.w	r3, #1080	; 0x438
7000013e:	f44f 757a 	mov.w	r5, #1000	; 0x3e8
70000142:	7108      	strb	r0, [r1, #4]
70000144:	f881 0084 	strb.w	r0, [r1, #132]	; 0x84
70000148:	f8c1 009c 	str.w	r0, [r1, #156]	; 0x9c
7000014c:	f8c1 50a0 	str.w	r5, [r1, #160]	; 0xa0
70000150:	f881 00b0 	strb.w	r0, [r1, #176]	; 0xb0
70000154:	f881 00bc 	strb.w	r0, [r1, #188]	; 0xbc
70000158:	f881 00c8 	strb.w	r0, [r1, #200]	; 0xc8
7000015c:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
70000160:	f8c1 02dc 	str.w	r0, [r1, #732]	; 0x2dc
70000164:	e9c1 2302 	strd	r2, r3, [r1, #8]
70000168:	4a1e      	ldr	r2, [pc, #120]	; (700001e4 <ps5268_get_info+0xc4>)
7000016a:	2301      	movs	r3, #1
7000016c:	6812      	ldr	r2, [r2, #0]
7000016e:	600b      	str	r3, [r1, #0]
70000170:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
70000174:	f44f 7281 	mov.w	r2, #258	; 0x102
70000178:	f881 3098 	strb.w	r3, [r1, #152]	; 0x98
7000017c:	f8a1 2086 	strh.w	r2, [r1, #134]	; 0x86
70000180:	4a19      	ldr	r2, [pc, #100]	; (700001e8 <ps5268_get_info+0xc8>)
70000182:	f8c1 30cc 	str.w	r3, [r1, #204]	; 0xcc
70000186:	7010      	strb	r0, [r2, #0]
70000188:	2203      	movs	r2, #3
7000018a:	e9c1 c42a 	strd	ip, r4, [r1, #168]	; 0xa8
7000018e:	e9c1 0430 	strd	r0, r4, [r1, #192]	; 0xc0
70000192:	f24c 3450 	movw	r4, #50000	; 0xc350
70000196:	f881 208c 	strb.w	r2, [r1, #140]	; 0x8c
7000019a:	f881 20a4 	strb.w	r2, [r1, #164]	; 0xa4
7000019e:	f8c1 40d0 	str.w	r4, [r1, #208]	; 0xd0
700001a2:	2406      	movs	r4, #6
700001a4:	f8c1 4088 	str.w	r4, [r1, #136]	; 0x88
700001a8:	f242 7410 	movw	r4, #10000	; 0x2710
700001ac:	e9c1 352d 	strd	r3, r5, [r1, #180]	; 0xb4
700001b0:	e9c1 0024 	strd	r0, r0, [r1, #144]	; 0x90
700001b4:	f8c1 42e0 	str.w	r4, [r1, #736]	; 0x2e0
700001b8:	f881 32e4 	strb.w	r3, [r1, #740]	; 0x2e4
700001bc:	4b0b      	ldr	r3, [pc, #44]	; (700001ec <ps5268_get_info+0xcc>)
700001be:	f8c1 02e8 	str.w	r0, [r1, #744]	; 0x2e8
700001c2:	f8c1 32ec 	str.w	r3, [r1, #748]	; 0x2ec
700001c6:	f881 22f0 	strb.w	r2, [r1, #752]	; 0x2f0
700001ca:	f8c1 22d4 	str.w	r2, [r1, #724]	; 0x2d4
700001ce:	e9c1 04bd 	strd	r0, r4, [r1, #756]	; 0x2f4
700001d2:	bd30      	pop	{r4, r5, pc}
700001d4:	f06f 0015 	mvn.w	r0, #21
700001d8:	e7fb      	b.n	700001d2 <ps5268_get_info+0xb2>
700001da:	bf00      	nop
700001dc:	41f00000 	.word	0x41f00000
700001e0:	016e3600 	.word	0x016e3600
700001e4:	70000104 	.word	0x70000104
700001e8:	7000004c 	.word	0x7000004c
700001ec:	000186a0 	.word	0x000186a0

700001f0 <ps5268_get_init_info>:
700001f0:	b570      	push	{r4, r5, r6, lr}
700001f2:	460b      	mov	r3, r1
700001f4:	4614      	mov	r4, r2
700001f6:	4605      	mov	r5, r0
700001f8:	b110      	cbz	r0, 70000200 <ps5268_get_init_info+0x10>
700001fa:	f06f 0015 	mvn.w	r0, #21
700001fe:	bd70      	pop	{r4, r5, r6, pc}
70000200:	2a00      	cmp	r2, #0
70000202:	d0fa      	beq.n	700001fa <ps5268_get_init_info+0xa>
70000204:	780a      	ldrb	r2, [r1, #0]
70000206:	4e1e      	ldr	r6, [pc, #120]	; (70000280 <ps5268_get_init_info+0x90>)
70000208:	491e      	ldr	r1, [pc, #120]	; (70000284 <ps5268_get_init_info+0x94>)
7000020a:	68d8      	ldr	r0, [r3, #12]
7000020c:	7032      	strb	r2, [r6, #0]
7000020e:	f000 fdfb 	bl	70000e08 <__aeabi_fcmpeq>
70000212:	2800      	cmp	r0, #0
70000214:	d0f1      	beq.n	700001fa <ps5268_get_init_info+0xa>
70000216:	4b1c      	ldr	r3, [pc, #112]	; (70000288 <ps5268_get_init_info+0x98>)
70000218:	481c      	ldr	r0, [pc, #112]	; (7000028c <ps5268_get_init_info+0x9c>)
7000021a:	681b      	ldr	r3, [r3, #0]
7000021c:	681b      	ldr	r3, [r3, #0]
7000021e:	4798      	blx	r3
70000220:	4b1b      	ldr	r3, [pc, #108]	; (70000290 <ps5268_get_init_info+0xa0>)
70000222:	f44f 62f1 	mov.w	r2, #1928	; 0x788
70000226:	f44f 6016 	mov.w	r0, #2400	; 0x960
7000022a:	6063      	str	r3, [r4, #4]
7000022c:	2326      	movs	r3, #38	; 0x26
7000022e:	60a5      	str	r5, [r4, #8]
70000230:	6023      	str	r3, [r4, #0]
70000232:	2302      	movs	r3, #2
70000234:	f8c4 5088 	str.w	r5, [r4, #136]	; 0x88
70000238:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
7000023c:	f240 4303 	movw	r3, #1027	; 0x403
70000240:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
70000244:	230a      	movs	r3, #10
70000246:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
7000024a:	2304      	movs	r3, #4
7000024c:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
70000250:	f44f 6388 	mov.w	r3, #1088	; 0x440
70000254:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
70000258:	2301      	movs	r3, #1
7000025a:	f8c4 308c 	str.w	r3, [r4, #140]	; 0x8c
7000025e:	4b0d      	ldr	r3, [pc, #52]	; (70000294 <ps5268_get_init_info+0xa4>)
70000260:	e9c4 3024 	strd	r3, r0, [r4, #144]	; 0x90
70000264:	f240 4365 	movw	r3, #1125	; 0x465
70000268:	4628      	mov	r0, r5
7000026a:	6073      	str	r3, [r6, #4]
7000026c:	f8c4 3098 	str.w	r3, [r4, #152]	; 0x98
70000270:	f248 33d6 	movw	r3, #33750	; 0x83d6
70000274:	f8c4 309c 	str.w	r3, [r4, #156]	; 0x9c
70000278:	4b07      	ldr	r3, [pc, #28]	; (70000298 <ps5268_get_init_info+0xa8>)
7000027a:	60b3      	str	r3, [r6, #8]
7000027c:	e7bf      	b.n	700001fe <ps5268_get_init_info+0xe>
7000027e:	bf00      	nop
70000280:	7000004c 	.word	0x7000004c
70000284:	41f00000 	.word	0x41f00000
70000288:	70000048 	.word	0x70000048
7000028c:	70000570 	.word	0x70000570
70000290:	7000006c 	.word	0x7000006c
70000294:	04d3f640 	.word	0x04d3f640
70000298:	41ed097b 	.word	0x41ed097b

7000029c <ps5268_start>:
7000029c:	b918      	cbnz	r0, 700002a6 <ps5268_start+0xa>
7000029e:	4b03      	ldr	r3, [pc, #12]	; (700002ac <ps5268_start+0x10>)
700002a0:	2200      	movs	r2, #0
700002a2:	60da      	str	r2, [r3, #12]
700002a4:	4770      	bx	lr
700002a6:	f06f 0015 	mvn.w	r0, #21
700002aa:	4770      	bx	lr
700002ac:	7000004c 	.word	0x7000004c

700002b0 <ps5268_get_tuned_dgain>:
700002b0:	b920      	cbnz	r0, 700002bc <ps5268_get_tuned_dgain+0xc>
700002b2:	b119      	cbz	r1, 700002bc <ps5268_get_tuned_dgain+0xc>
700002b4:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
700002b8:	600b      	str	r3, [r1, #0]
700002ba:	4770      	bx	lr
700002bc:	f06f 0015 	mvn.w	r0, #21
700002c0:	4770      	bx	lr
	...

700002c4 <ps5268_get_exposure_gain_info>:
700002c4:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
700002c8:	4614      	mov	r4, r2
700002ca:	2800      	cmp	r0, #0
700002cc:	d16d      	bne.n	700003aa <ps5268_get_exposure_gain_info+0xe6>
700002ce:	2900      	cmp	r1, #0
700002d0:	d06b      	beq.n	700003aa <ps5268_get_exposure_gain_info+0xe6>
700002d2:	2a00      	cmp	r2, #0
700002d4:	d069      	beq.n	700003aa <ps5268_get_exposure_gain_info+0xe6>
700002d6:	8b0d      	ldrh	r5, [r1, #24]
700002d8:	f8d1 8000 	ldr.w	r8, [r1]
700002dc:	3d01      	subs	r5, #1
700002de:	4f34      	ldr	r7, [pc, #208]	; (700003b0 <ps5268_get_exposure_gain_info+0xec>)
700002e0:	4640      	mov	r0, r8
700002e2:	eb05 75d5 	add.w	r5, r5, r5, lsr #31
700002e6:	68b9      	ldr	r1, [r7, #8]
700002e8:	f000 fcae 	bl	70000c48 <__aeabi_fdiv>
700002ec:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
700002f0:	f025 0501 	bic.w	r5, r5, #1
700002f4:	f000 faec 	bl	700008d0 <__addsf3>
700002f8:	f000 fdb8 	bl	70000e6c <__aeabi_f2uiz>
700002fc:	b2ad      	uxth	r5, r5
700002fe:	b280      	uxth	r0, r0
70000300:	42a8      	cmp	r0, r5
70000302:	d840      	bhi.n	70000386 <ps5268_get_exposure_gain_info+0xc2>
70000304:	2802      	cmp	r0, #2
70000306:	bf38      	it	cc
70000308:	2002      	movcc	r0, #2
7000030a:	1c6e      	adds	r6, r5, #1
7000030c:	1a36      	subs	r6, r6, r0
7000030e:	b2b6      	uxth	r6, r6
70000310:	42b5      	cmp	r5, r6
70000312:	d33a      	bcc.n	7000038a <ps5268_get_exposure_gain_info+0xc6>
70000314:	2e02      	cmp	r6, #2
70000316:	bf38      	it	cc
70000318:	2602      	movcc	r6, #2
7000031a:	4641      	mov	r1, r8
7000031c:	68f8      	ldr	r0, [r7, #12]
7000031e:	f000 fad5 	bl	700008cc <__aeabi_fsub>
70000322:	2100      	movs	r1, #0
70000324:	4681      	mov	r9, r0
70000326:	ea4f 2a15 	mov.w	sl, r5, lsr #8
7000032a:	f000 fd8b 	bl	70000e44 <__aeabi_fcmpge>
7000032e:	b2ed      	uxtb	r5, r5
70000330:	b368      	cbz	r0, 7000038e <ps5268_get_exposure_gain_info+0xca>
70000332:	4920      	ldr	r1, [pc, #128]	; (700003b4 <ps5268_get_exposure_gain_info+0xf0>)
70000334:	4648      	mov	r0, r9
70000336:	f000 fd8f 	bl	70000e58 <__aeabi_fcmpgt>
7000033a:	f44f 738b 	mov.w	r3, #278	; 0x116
7000033e:	f8a4 a00e 	strh.w	sl, [r4, #14]
70000342:	8465      	strh	r5, [r4, #34]	; 0x22
70000344:	81a3      	strh	r3, [r4, #12]
70000346:	f240 1317 	movw	r3, #279	; 0x117
7000034a:	8423      	strh	r3, [r4, #32]
7000034c:	b320      	cbz	r0, 70000398 <ps5268_get_exposure_gain_info+0xd4>
7000034e:	f240 132b 	movw	r3, #299	; 0x12b
70000352:	f8c7 800c 	str.w	r8, [r7, #12]
70000356:	86a3      	strh	r3, [r4, #52]	; 0x34
70000358:	2300      	movs	r3, #0
7000035a:	86e3      	strh	r3, [r4, #54]	; 0x36
7000035c:	f44f 738c 	mov.w	r3, #280	; 0x118
70000360:	f8a4 3048 	strh.w	r3, [r4, #72]	; 0x48
70000364:	0a33      	lsrs	r3, r6, #8
70000366:	b2f6      	uxtb	r6, r6
70000368:	f8a4 304a 	strh.w	r3, [r4, #74]	; 0x4a
7000036c:	f240 1319 	movw	r3, #281	; 0x119
70000370:	f8a4 605e 	strh.w	r6, [r4, #94]	; 0x5e
70000374:	f8a4 305c 	strh.w	r3, [r4, #92]	; 0x5c
70000378:	4b0f      	ldr	r3, [pc, #60]	; (700003b8 <ps5268_get_exposure_gain_info+0xf4>)
7000037a:	6723      	str	r3, [r4, #112]	; 0x70
7000037c:	2306      	movs	r3, #6
7000037e:	2000      	movs	r0, #0
70000380:	6023      	str	r3, [r4, #0]
70000382:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
70000386:	4628      	mov	r0, r5
70000388:	e7bf      	b.n	7000030a <ps5268_get_exposure_gain_info+0x46>
7000038a:	462e      	mov	r6, r5
7000038c:	e7c5      	b.n	7000031a <ps5268_get_exposure_gain_info+0x56>
7000038e:	490b      	ldr	r1, [pc, #44]	; (700003bc <ps5268_get_exposure_gain_info+0xf8>)
70000390:	4648      	mov	r0, r9
70000392:	f000 fd43 	bl	70000e1c <__aeabi_fcmplt>
70000396:	e7d0      	b.n	7000033a <ps5268_get_exposure_gain_info+0x76>
70000398:	7c3b      	ldrb	r3, [r7, #16]
7000039a:	f240 122b 	movw	r2, #299	; 0x12b
7000039e:	86e3      	strh	r3, [r4, #54]	; 0x36
700003a0:	4b05      	ldr	r3, [pc, #20]	; (700003b8 <ps5268_get_exposure_gain_info+0xf4>)
700003a2:	86a2      	strh	r2, [r4, #52]	; 0x34
700003a4:	64a3      	str	r3, [r4, #72]	; 0x48
700003a6:	2304      	movs	r3, #4
700003a8:	e7e9      	b.n	7000037e <ps5268_get_exposure_gain_info+0xba>
700003aa:	f06f 0015 	mvn.w	r0, #21
700003ae:	e7e8      	b.n	70000382 <ps5268_get_exposure_gain_info+0xbe>
700003b0:	7000004c 	.word	0x7000004c
700003b4:	3a83126f 	.word	0x3a83126f
700003b8:	00010111 	.word	0x00010111
700003bc:	ba83126f 	.word	0xba83126f

700003c0 <ps5268_set_mirror_flip>:
700003c0:	784b      	ldrb	r3, [r1, #1]
700003c2:	780a      	ldrb	r2, [r1, #0]
700003c4:	2b00      	cmp	r3, #0
700003c6:	bf14      	ite	ne
700003c8:	2302      	movne	r3, #2
700003ca:	2300      	moveq	r3, #0
700003cc:	2a00      	cmp	r2, #0
700003ce:	bf18      	it	ne
700003d0:	f043 0301 	orrne.w	r3, r3, #1
700003d4:	2201      	movs	r2, #1
700003d6:	2b02      	cmp	r3, #2
700003d8:	708a      	strb	r2, [r1, #2]
700003da:	d015      	beq.n	70000408 <ps5268_set_mirror_flip+0x48>
700003dc:	2b03      	cmp	r3, #3
700003de:	d01d      	beq.n	7000041c <ps5268_set_mirror_flip+0x5c>
700003e0:	4293      	cmp	r3, r2
700003e2:	f240 1241 	movw	r2, #321	; 0x141
700003e6:	4b0f      	ldr	r3, [pc, #60]	; (70000424 <ps5268_set_mirror_flip+0x64>)
700003e8:	bf14      	ite	ne
700003ea:	f44f 70a0 	movne.w	r0, #320	; 0x140
700003ee:	480e      	ldreq	r0, [pc, #56]	; (70000428 <ps5268_set_mirror_flip+0x68>)
700003f0:	624a      	str	r2, [r1, #36]	; 0x24
700003f2:	f240 1249 	movw	r2, #329	; 0x149
700003f6:	6108      	str	r0, [r1, #16]
700003f8:	638a      	str	r2, [r1, #56]	; 0x38
700003fa:	64cb      	str	r3, [r1, #76]	; 0x4c
700003fc:	2000      	movs	r0, #0
700003fe:	4b0b      	ldr	r3, [pc, #44]	; (7000042c <ps5268_set_mirror_flip+0x6c>)
70000400:	660b      	str	r3, [r1, #96]	; 0x60
70000402:	2305      	movs	r3, #5
70000404:	604b      	str	r3, [r1, #4]
70000406:	4770      	bx	lr
70000408:	f44f 73a0 	mov.w	r3, #320	; 0x140
7000040c:	610b      	str	r3, [r1, #16]
7000040e:	f103 1301 	add.w	r3, r3, #65537	; 0x10001
70000412:	624b      	str	r3, [r1, #36]	; 0x24
70000414:	4b06      	ldr	r3, [pc, #24]	; (70000430 <ps5268_set_mirror_flip+0x70>)
70000416:	638b      	str	r3, [r1, #56]	; 0x38
70000418:	4b06      	ldr	r3, [pc, #24]	; (70000434 <ps5268_set_mirror_flip+0x74>)
7000041a:	e7ee      	b.n	700003fa <ps5268_set_mirror_flip+0x3a>
7000041c:	4b02      	ldr	r3, [pc, #8]	; (70000428 <ps5268_set_mirror_flip+0x68>)
7000041e:	610b      	str	r3, [r1, #16]
70000420:	3301      	adds	r3, #1
70000422:	e7f6      	b.n	70000412 <ps5268_set_mirror_flip+0x52>
70000424:	0002014a 	.word	0x0002014a
70000428:	00010140 	.word	0x00010140
7000042c:	00010111 	.word	0x00010111
70000430:	00040149 	.word	0x00040149
70000434:	0044014a 	.word	0x0044014a

70000438 <ps5268_check>:
70000438:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
7000043a:	4d1e      	ldr	r5, [pc, #120]	; (700004b4 <ps5268_check+0x7c>)
7000043c:	4606      	mov	r6, r0
7000043e:	682b      	ldr	r3, [r5, #0]
70000440:	6c1b      	ldr	r3, [r3, #64]	; 0x40
70000442:	4798      	blx	r3
70000444:	2801      	cmp	r0, #1
70000446:	dc31      	bgt.n	700004ac <ps5268_check+0x74>
70000448:	4b1b      	ldr	r3, [pc, #108]	; (700004b8 <ps5268_check+0x80>)
7000044a:	f853 2020 	ldr.w	r2, [r3, r0, lsl #2]
7000044e:	4b1b      	ldr	r3, [pc, #108]	; (700004bc <ps5268_check+0x84>)
70000450:	601a      	str	r2, [r3, #0]
70000452:	682b      	ldr	r3, [r5, #0]
70000454:	685b      	ldr	r3, [r3, #4]
70000456:	4798      	blx	r3
70000458:	f44f 7380 	mov.w	r3, #256	; 0x100
7000045c:	a901      	add	r1, sp, #4
7000045e:	4630      	mov	r0, r6
70000460:	f8ad 3004 	strh.w	r3, [sp, #4]
70000464:	682b      	ldr	r3, [r5, #0]
70000466:	68db      	ldr	r3, [r3, #12]
70000468:	4798      	blx	r3
7000046a:	4604      	mov	r4, r0
7000046c:	b128      	cbz	r0, 7000047a <ps5268_check+0x42>
7000046e:	682b      	ldr	r3, [r5, #0]
70000470:	689b      	ldr	r3, [r3, #8]
70000472:	4798      	blx	r3
70000474:	4620      	mov	r0, r4
70000476:	b003      	add	sp, #12
70000478:	bdf0      	pop	{r4, r5, r6, r7, pc}
7000047a:	f240 1301 	movw	r3, #257	; 0x101
7000047e:	a901      	add	r1, sp, #4
70000480:	4630      	mov	r0, r6
70000482:	f8bd 7006 	ldrh.w	r7, [sp, #6]
70000486:	f8ad 3004 	strh.w	r3, [sp, #4]
7000048a:	682b      	ldr	r3, [r5, #0]
7000048c:	68db      	ldr	r3, [r3, #12]
7000048e:	4798      	blx	r3
70000490:	682b      	ldr	r3, [r5, #0]
70000492:	4604      	mov	r4, r0
70000494:	689b      	ldr	r3, [r3, #8]
70000496:	4798      	blx	r3
70000498:	2c00      	cmp	r4, #0
7000049a:	d1eb      	bne.n	70000474 <ps5268_check+0x3c>
7000049c:	f8bd 3006 	ldrh.w	r3, [sp, #6]
700004a0:	f245 2268 	movw	r2, #21096	; 0x5268
700004a4:	ea43 2307 	orr.w	r3, r3, r7, lsl #8
700004a8:	4293      	cmp	r3, r2
700004aa:	d0e3      	beq.n	70000474 <ps5268_check+0x3c>
700004ac:	f06f 0415 	mvn.w	r4, #21
700004b0:	e7e0      	b.n	70000474 <ps5268_check+0x3c>
700004b2:	bf00      	nop
700004b4:	70000048 	.word	0x70000048
700004b8:	70000108 	.word	0x70000108
700004bc:	70000104 	.word	0x70000104

700004c0 <ps5268_get_slave_addr_num>:
700004c0:	2002      	movs	r0, #2
700004c2:	4770      	bx	lr

700004c4 <ps5268_get_tuned_again>:
700004c4:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
700004c8:	460d      	mov	r5, r1
700004ca:	2800      	cmp	r0, #0
700004cc:	d13b      	bne.n	70000546 <ps5268_get_tuned_again+0x82>
700004ce:	2900      	cmp	r1, #0
700004d0:	d039      	beq.n	70000546 <ps5268_get_tuned_again+0x82>
700004d2:	f8d1 8000 	ldr.w	r8, [r1]
700004d6:	f04f 4184 	mov.w	r1, #1107296256	; 0x42000000
700004da:	4640      	mov	r0, r8
700004dc:	f000 fcb2 	bl	70000e44 <__aeabi_fcmpge>
700004e0:	4604      	mov	r4, r0
700004e2:	b128      	cbz	r0, 700004f0 <ps5268_get_tuned_again+0x2c>
700004e4:	4b19      	ldr	r3, [pc, #100]	; (7000054c <ps5268_get_tuned_again+0x88>)
700004e6:	2250      	movs	r2, #80	; 0x50
700004e8:	611a      	str	r2, [r3, #16]
700004ea:	f04f 4384 	mov.w	r3, #1107296256	; 0x42000000
700004ee:	e01b      	b.n	70000528 <ps5268_get_tuned_again+0x64>
700004f0:	4e17      	ldr	r6, [pc, #92]	; (70000550 <ps5268_get_tuned_again+0x8c>)
700004f2:	4637      	mov	r7, r6
700004f4:	6871      	ldr	r1, [r6, #4]
700004f6:	4640      	mov	r0, r8
700004f8:	46a1      	mov	r9, r4
700004fa:	3401      	adds	r4, #1
700004fc:	f000 fca2 	bl	70000e44 <__aeabi_fcmpge>
70000500:	b1b0      	cbz	r0, 70000530 <ps5268_get_tuned_again+0x6c>
70000502:	68f1      	ldr	r1, [r6, #12]
70000504:	4640      	mov	r0, r8
70000506:	f000 fc89 	bl	70000e1c <__aeabi_fcmplt>
7000050a:	b188      	cbz	r0, 70000530 <ps5268_get_tuned_again+0x6c>
7000050c:	f817 2039 	ldrb.w	r2, [r7, r9, lsl #3]
70000510:	4b0e      	ldr	r3, [pc, #56]	; (7000054c <ps5268_get_tuned_again+0x88>)
70000512:	2a4f      	cmp	r2, #79	; 0x4f
70000514:	611a      	str	r2, [r3, #16]
70000516:	d8e8      	bhi.n	700004ea <ps5268_get_tuned_again+0x26>
70000518:	2300      	movs	r3, #0
7000051a:	f817 1033 	ldrb.w	r1, [r7, r3, lsl #3]
7000051e:	4291      	cmp	r1, r2
70000520:	d10c      	bne.n	7000053c <ps5268_get_tuned_again+0x78>
70000522:	eb07 03c3 	add.w	r3, r7, r3, lsl #3
70000526:	685b      	ldr	r3, [r3, #4]
70000528:	2000      	movs	r0, #0
7000052a:	602b      	str	r3, [r5, #0]
7000052c:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
70000530:	2c50      	cmp	r4, #80	; 0x50
70000532:	f106 0608 	add.w	r6, r6, #8
70000536:	d1dd      	bne.n	700004f4 <ps5268_get_tuned_again+0x30>
70000538:	2200      	movs	r2, #0
7000053a:	e7e9      	b.n	70000510 <ps5268_get_tuned_again+0x4c>
7000053c:	3301      	adds	r3, #1
7000053e:	2b50      	cmp	r3, #80	; 0x50
70000540:	d1eb      	bne.n	7000051a <ps5268_get_tuned_again+0x56>
70000542:	2300      	movs	r3, #0
70000544:	e7f0      	b.n	70000528 <ps5268_get_tuned_again+0x64>
70000546:	f06f 0015 	mvn.w	r0, #21
7000054a:	e7ef      	b.n	7000052c <ps5268_get_tuned_again+0x68>
7000054c:	7000004c 	.word	0x7000004c
70000550:	700005a8 	.word	0x700005a8

70000554 <clip_d_word>:
70000554:	4603      	mov	r3, r0
70000556:	4610      	mov	r0, r2
70000558:	4293      	cmp	r3, r2
7000055a:	d803      	bhi.n	70000564 <clip_d_word+0x10>
7000055c:	428b      	cmp	r3, r1
7000055e:	bf38      	it	cc
70000560:	460b      	movcc	r3, r1
70000562:	4618      	mov	r0, r3
70000564:	4770      	bx	lr
	...

70000568 <rts_isp_get_sensor_ops>:
70000568:	4800      	ldr	r0, [pc, #0]	; (7000056c <rts_isp_get_sensor_ops+0x4>)
7000056a:	4770      	bx	lr
7000056c:	70000830 	.word	0x70000830
70000570:	6e65535b 	.word	0x6e65535b
70000574:	20726f73 	.word	0x20726f73
70000578:	76697244 	.word	0x76697244
7000057c:	205d7265 	.word	0x205d7265
70000580:	65746e45 	.word	0x65746e45
70000584:	73702072 	.word	0x73702072
70000588:	38363235 	.word	0x38363235
7000058c:	7465675f 	.word	0x7465675f
70000590:	696e695f 	.word	0x696e695f
70000594:	6e695f74 	.word	0x6e695f74
70000598:	203a6f66 	.word	0x203a6f66
7000059c:	36313630 	.word	0x36313630
700005a0:	3136312e 	.word	0x3136312e
700005a4:	000a0d37 	.word	0x000a0d37

700005a8 <gain_mapping>:
700005a8:	00000000 3f800000 00000001 3f880000     .......?.......?
700005b8:	00000002 3f900000 00000003 3f980000     .......?.......?
700005c8:	00000004 3fa00000 00000005 3fa80000     .......?.......?
700005d8:	00000006 3fb00000 00000007 3fb80000     .......?.......?
700005e8:	00000008 3fc00000 00000009 3fc80000     .......?.......?
700005f8:	0000000a 3fd00000 0000000b 3fd80000     .......?.......?
70000608:	0000000c 3fe00000 0000000d 3fe80000     .......?.......?
70000618:	0000000e 3ff00000 0000000f 3ff80000     .......?.......?
70000628:	00000010 40000000 00000011 40080000     .......@.......@
70000638:	00000012 40100000 00000013 40180000     .......@.......@
70000648:	00000014 40200000 00000015 40280000     ...... @......(@
70000658:	00000016 40300000 00000017 40380000     ......0@......8@
70000668:	00000018 40400000 00000019 40480000     ......@@......H@
70000678:	0000001a 40500000 0000001b 40580000     ......P@......X@
70000688:	0000001c 40600000 0000001d 40680000     ......`@......h@
70000698:	0000001e 40700000 0000001f 40780000     ......p@......x@
700006a8:	00000020 40800000 00000021 40880000      ......@!......@
700006b8:	00000022 40900000 00000023 40980000     "......@#......@
700006c8:	00000024 40a00000 00000025 40a80000     $......@%......@
700006d8:	00000026 40b00000 00000027 40b80000     &......@'......@
700006e8:	00000028 40c00000 00000029 40c80000     (......@)......@
700006f8:	0000002a 40d00000 0000002b 40d80000     *......@+......@
70000708:	0000002c 40e00000 0000002d 40e80000     ,......@-......@
70000718:	0000002e 40f00000 0000002f 40f80000     .......@/......@
70000728:	00000030 41000000 00000031 41080000     0......A1......A
70000738:	00000032 41100000 00000033 41180000     2......A3......A
70000748:	00000034 41200000 00000035 41280000     4..... A5.....(A
70000758:	00000036 41300000 00000037 41380000     6.....0A7.....8A
70000768:	00000038 41400000 00000039 41480000     8.....@A9.....HA
70000778:	0000003a 41500000 0000003b 41580000     :.....PA;.....XA
70000788:	0000003c 41600000 0000003d 41680000     <.....`A=.....hA
70000798:	0000003e 41700000 0000003f 41780000     >.....pA?.....xA
700007a8:	00000040 41800000 00000041 41880000     @......AA......A
700007b8:	00000042 41900000 00000043 41980000     B......AC......A
700007c8:	00000044 41a00000 00000045 41a80000     D......AE......A
700007d8:	00000046 41b00000 00000047 41b80000     F......AG......A
700007e8:	00000048 41c00000 00000049 41c80000     H......AI......A
700007f8:	0000004a 41d00000 0000004b 41d80000     J......AK......A
70000808:	0000004c 41e00000 0000004d 41e80000     L......AM......A
70000818:	0000004e 41f00000 0000004f 41f80000     N......AO......A
70000828:	00000050 42000000                       P......B

70000830 <ps5268_ops>:
70000830:	73000005 32357370 00003836 00000000     ...sps5268......
	...
70000854:	70000121 700001f1 00000000 700004c5     !..p...p.......p
70000864:	700002b1 700002c5 00000000 00000000     ...p...p........
70000874:	7000029d 00000000 00000000 00000000     ...p............
70000884:	700003c1 00000000 00000000 00000000     ...p............
70000894:	70000439 00000000 00000000 00000000     9..p............
700008a4:	700004c1 00000000 00000000 00000000     ...p............
	...

700008c4 <__aeabi_frsub>:
700008c4:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
700008c8:	e002      	b.n	700008d0 <__addsf3>
700008ca:	bf00      	nop

700008cc <__aeabi_fsub>:
700008cc:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

700008d0 <__addsf3>:
700008d0:	0042      	lsls	r2, r0, #1
700008d2:	bf1f      	itttt	ne
700008d4:	ea5f 0341 	movsne.w	r3, r1, lsl #1
700008d8:	ea92 0f03 	teqne	r2, r3
700008dc:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
700008e0:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700008e4:	d06a      	beq.n	700009bc <__addsf3+0xec>
700008e6:	ea4f 6212 	mov.w	r2, r2, lsr #24
700008ea:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
700008ee:	bfc1      	itttt	gt
700008f0:	18d2      	addgt	r2, r2, r3
700008f2:	4041      	eorgt	r1, r0
700008f4:	4048      	eorgt	r0, r1
700008f6:	4041      	eorgt	r1, r0
700008f8:	bfb8      	it	lt
700008fa:	425b      	neglt	r3, r3
700008fc:	2b19      	cmp	r3, #25
700008fe:	bf88      	it	hi
70000900:	4770      	bxhi	lr
70000902:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
70000906:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
7000090a:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
7000090e:	bf18      	it	ne
70000910:	4240      	negne	r0, r0
70000912:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000916:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
7000091a:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
7000091e:	bf18      	it	ne
70000920:	4249      	negne	r1, r1
70000922:	ea92 0f03 	teq	r2, r3
70000926:	d03f      	beq.n	700009a8 <__addsf3+0xd8>
70000928:	f1a2 0201 	sub.w	r2, r2, #1
7000092c:	fa41 fc03 	asr.w	ip, r1, r3
70000930:	eb10 000c 	adds.w	r0, r0, ip
70000934:	f1c3 0320 	rsb	r3, r3, #32
70000938:	fa01 f103 	lsl.w	r1, r1, r3
7000093c:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000940:	d502      	bpl.n	70000948 <__addsf3+0x78>
70000942:	4249      	negs	r1, r1
70000944:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70000948:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
7000094c:	d313      	bcc.n	70000976 <__addsf3+0xa6>
7000094e:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
70000952:	d306      	bcc.n	70000962 <__addsf3+0x92>
70000954:	0840      	lsrs	r0, r0, #1
70000956:	ea4f 0131 	mov.w	r1, r1, rrx
7000095a:	f102 0201 	add.w	r2, r2, #1
7000095e:	2afe      	cmp	r2, #254	; 0xfe
70000960:	d251      	bcs.n	70000a06 <__addsf3+0x136>
70000962:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
70000966:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
7000096a:	bf08      	it	eq
7000096c:	f020 0001 	biceq.w	r0, r0, #1
70000970:	ea40 0003 	orr.w	r0, r0, r3
70000974:	4770      	bx	lr
70000976:	0049      	lsls	r1, r1, #1
70000978:	eb40 0000 	adc.w	r0, r0, r0
7000097c:	3a01      	subs	r2, #1
7000097e:	bf28      	it	cs
70000980:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70000984:	d2ed      	bcs.n	70000962 <__addsf3+0x92>
70000986:	fab0 fc80 	clz	ip, r0
7000098a:	f1ac 0c08 	sub.w	ip, ip, #8
7000098e:	ebb2 020c 	subs.w	r2, r2, ip
70000992:	fa00 f00c 	lsl.w	r0, r0, ip
70000996:	bfaa      	itet	ge
70000998:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
7000099c:	4252      	neglt	r2, r2
7000099e:	4318      	orrge	r0, r3
700009a0:	bfbc      	itt	lt
700009a2:	40d0      	lsrlt	r0, r2
700009a4:	4318      	orrlt	r0, r3
700009a6:	4770      	bx	lr
700009a8:	f092 0f00 	teq	r2, #0
700009ac:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
700009b0:	bf06      	itte	eq
700009b2:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
700009b6:	3201      	addeq	r2, #1
700009b8:	3b01      	subne	r3, #1
700009ba:	e7b5      	b.n	70000928 <__addsf3+0x58>
700009bc:	ea4f 0341 	mov.w	r3, r1, lsl #1
700009c0:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700009c4:	bf18      	it	ne
700009c6:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700009ca:	d021      	beq.n	70000a10 <__addsf3+0x140>
700009cc:	ea92 0f03 	teq	r2, r3
700009d0:	d004      	beq.n	700009dc <__addsf3+0x10c>
700009d2:	f092 0f00 	teq	r2, #0
700009d6:	bf08      	it	eq
700009d8:	4608      	moveq	r0, r1
700009da:	4770      	bx	lr
700009dc:	ea90 0f01 	teq	r0, r1
700009e0:	bf1c      	itt	ne
700009e2:	2000      	movne	r0, #0
700009e4:	4770      	bxne	lr
700009e6:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
700009ea:	d104      	bne.n	700009f6 <__addsf3+0x126>
700009ec:	0040      	lsls	r0, r0, #1
700009ee:	bf28      	it	cs
700009f0:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
700009f4:	4770      	bx	lr
700009f6:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
700009fa:	bf3c      	itt	cc
700009fc:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
70000a00:	4770      	bxcc	lr
70000a02:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000a06:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
70000a0a:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000a0e:	4770      	bx	lr
70000a10:	ea7f 6222 	mvns.w	r2, r2, asr #24
70000a14:	bf16      	itet	ne
70000a16:	4608      	movne	r0, r1
70000a18:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70000a1c:	4601      	movne	r1, r0
70000a1e:	0242      	lsls	r2, r0, #9
70000a20:	bf06      	itte	eq
70000a22:	ea5f 2341 	movseq.w	r3, r1, lsl #9
70000a26:	ea90 0f01 	teqeq	r0, r1
70000a2a:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
70000a2e:	4770      	bx	lr

70000a30 <__aeabi_ui2f>:
70000a30:	f04f 0300 	mov.w	r3, #0
70000a34:	e004      	b.n	70000a40 <__aeabi_i2f+0x8>
70000a36:	bf00      	nop

70000a38 <__aeabi_i2f>:
70000a38:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70000a3c:	bf48      	it	mi
70000a3e:	4240      	negmi	r0, r0
70000a40:	ea5f 0c00 	movs.w	ip, r0
70000a44:	bf08      	it	eq
70000a46:	4770      	bxeq	lr
70000a48:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70000a4c:	4601      	mov	r1, r0
70000a4e:	f04f 0000 	mov.w	r0, #0
70000a52:	e01c      	b.n	70000a8e <__aeabi_l2f+0x2a>

70000a54 <__aeabi_ul2f>:
70000a54:	ea50 0201 	orrs.w	r2, r0, r1
70000a58:	bf08      	it	eq
70000a5a:	4770      	bxeq	lr
70000a5c:	f04f 0300 	mov.w	r3, #0
70000a60:	e00a      	b.n	70000a78 <__aeabi_l2f+0x14>
70000a62:	bf00      	nop

70000a64 <__aeabi_l2f>:
70000a64:	ea50 0201 	orrs.w	r2, r0, r1
70000a68:	bf08      	it	eq
70000a6a:	4770      	bxeq	lr
70000a6c:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70000a70:	d502      	bpl.n	70000a78 <__aeabi_l2f+0x14>
70000a72:	4240      	negs	r0, r0
70000a74:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000a78:	ea5f 0c01 	movs.w	ip, r1
70000a7c:	bf02      	ittt	eq
70000a7e:	4684      	moveq	ip, r0
70000a80:	4601      	moveq	r1, r0
70000a82:	2000      	moveq	r0, #0
70000a84:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70000a88:	bf08      	it	eq
70000a8a:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70000a8e:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
70000a92:	fabc f28c 	clz	r2, ip
70000a96:	3a08      	subs	r2, #8
70000a98:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
70000a9c:	db10      	blt.n	70000ac0 <__aeabi_l2f+0x5c>
70000a9e:	fa01 fc02 	lsl.w	ip, r1, r2
70000aa2:	4463      	add	r3, ip
70000aa4:	fa00 fc02 	lsl.w	ip, r0, r2
70000aa8:	f1c2 0220 	rsb	r2, r2, #32
70000aac:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000ab0:	fa20 f202 	lsr.w	r2, r0, r2
70000ab4:	eb43 0002 	adc.w	r0, r3, r2
70000ab8:	bf08      	it	eq
70000aba:	f020 0001 	biceq.w	r0, r0, #1
70000abe:	4770      	bx	lr
70000ac0:	f102 0220 	add.w	r2, r2, #32
70000ac4:	fa01 fc02 	lsl.w	ip, r1, r2
70000ac8:	f1c2 0220 	rsb	r2, r2, #32
70000acc:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
70000ad0:	fa21 f202 	lsr.w	r2, r1, r2
70000ad4:	eb43 0002 	adc.w	r0, r3, r2
70000ad8:	bf08      	it	eq
70000ada:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000ade:	4770      	bx	lr

70000ae0 <__aeabi_fmul>:
70000ae0:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000ae4:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000ae8:	bf1e      	ittt	ne
70000aea:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000aee:	ea92 0f0c 	teqne	r2, ip
70000af2:	ea93 0f0c 	teqne	r3, ip
70000af6:	d06f      	beq.n	70000bd8 <__aeabi_fmul+0xf8>
70000af8:	441a      	add	r2, r3
70000afa:	ea80 0c01 	eor.w	ip, r0, r1
70000afe:	0240      	lsls	r0, r0, #9
70000b00:	bf18      	it	ne
70000b02:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000b06:	d01e      	beq.n	70000b46 <__aeabi_fmul+0x66>
70000b08:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000b0c:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000b10:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000b14:	fba0 3101 	umull	r3, r1, r0, r1
70000b18:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000b1c:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000b20:	bf3e      	ittt	cc
70000b22:	0049      	lslcc	r1, r1, #1
70000b24:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000b28:	005b      	lslcc	r3, r3, #1
70000b2a:	ea40 0001 	orr.w	r0, r0, r1
70000b2e:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000b32:	2afd      	cmp	r2, #253	; 0xfd
70000b34:	d81d      	bhi.n	70000b72 <__aeabi_fmul+0x92>
70000b36:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000b3a:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000b3e:	bf08      	it	eq
70000b40:	f020 0001 	biceq.w	r0, r0, #1
70000b44:	4770      	bx	lr
70000b46:	f090 0f00 	teq	r0, #0
70000b4a:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000b4e:	bf08      	it	eq
70000b50:	0249      	lsleq	r1, r1, #9
70000b52:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000b56:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000b5a:	3a7f      	subs	r2, #127	; 0x7f
70000b5c:	bfc2      	ittt	gt
70000b5e:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000b62:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000b66:	4770      	bxgt	lr
70000b68:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000b6c:	f04f 0300 	mov.w	r3, #0
70000b70:	3a01      	subs	r2, #1
70000b72:	dc5d      	bgt.n	70000c30 <__aeabi_fmul+0x150>
70000b74:	f112 0f19 	cmn.w	r2, #25
70000b78:	bfdc      	itt	le
70000b7a:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000b7e:	4770      	bxle	lr
70000b80:	f1c2 0200 	rsb	r2, r2, #0
70000b84:	0041      	lsls	r1, r0, #1
70000b86:	fa21 f102 	lsr.w	r1, r1, r2
70000b8a:	f1c2 0220 	rsb	r2, r2, #32
70000b8e:	fa00 fc02 	lsl.w	ip, r0, r2
70000b92:	ea5f 0031 	movs.w	r0, r1, rrx
70000b96:	f140 0000 	adc.w	r0, r0, #0
70000b9a:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000b9e:	bf08      	it	eq
70000ba0:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000ba4:	4770      	bx	lr
70000ba6:	f092 0f00 	teq	r2, #0
70000baa:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000bae:	bf02      	ittt	eq
70000bb0:	0040      	lsleq	r0, r0, #1
70000bb2:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000bb6:	3a01      	subeq	r2, #1
70000bb8:	d0f9      	beq.n	70000bae <__aeabi_fmul+0xce>
70000bba:	ea40 000c 	orr.w	r0, r0, ip
70000bbe:	f093 0f00 	teq	r3, #0
70000bc2:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000bc6:	bf02      	ittt	eq
70000bc8:	0049      	lsleq	r1, r1, #1
70000bca:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000bce:	3b01      	subeq	r3, #1
70000bd0:	d0f9      	beq.n	70000bc6 <__aeabi_fmul+0xe6>
70000bd2:	ea41 010c 	orr.w	r1, r1, ip
70000bd6:	e78f      	b.n	70000af8 <__aeabi_fmul+0x18>
70000bd8:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000bdc:	ea92 0f0c 	teq	r2, ip
70000be0:	bf18      	it	ne
70000be2:	ea93 0f0c 	teqne	r3, ip
70000be6:	d00a      	beq.n	70000bfe <__aeabi_fmul+0x11e>
70000be8:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000bec:	bf18      	it	ne
70000bee:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000bf2:	d1d8      	bne.n	70000ba6 <__aeabi_fmul+0xc6>
70000bf4:	ea80 0001 	eor.w	r0, r0, r1
70000bf8:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000bfc:	4770      	bx	lr
70000bfe:	f090 0f00 	teq	r0, #0
70000c02:	bf17      	itett	ne
70000c04:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000c08:	4608      	moveq	r0, r1
70000c0a:	f091 0f00 	teqne	r1, #0
70000c0e:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000c12:	d014      	beq.n	70000c3e <__aeabi_fmul+0x15e>
70000c14:	ea92 0f0c 	teq	r2, ip
70000c18:	d101      	bne.n	70000c1e <__aeabi_fmul+0x13e>
70000c1a:	0242      	lsls	r2, r0, #9
70000c1c:	d10f      	bne.n	70000c3e <__aeabi_fmul+0x15e>
70000c1e:	ea93 0f0c 	teq	r3, ip
70000c22:	d103      	bne.n	70000c2c <__aeabi_fmul+0x14c>
70000c24:	024b      	lsls	r3, r1, #9
70000c26:	bf18      	it	ne
70000c28:	4608      	movne	r0, r1
70000c2a:	d108      	bne.n	70000c3e <__aeabi_fmul+0x15e>
70000c2c:	ea80 0001 	eor.w	r0, r0, r1
70000c30:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000c34:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000c38:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000c3c:	4770      	bx	lr
70000c3e:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000c42:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000c46:	4770      	bx	lr

70000c48 <__aeabi_fdiv>:
70000c48:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000c4c:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000c50:	bf1e      	ittt	ne
70000c52:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000c56:	ea92 0f0c 	teqne	r2, ip
70000c5a:	ea93 0f0c 	teqne	r3, ip
70000c5e:	d069      	beq.n	70000d34 <__aeabi_fdiv+0xec>
70000c60:	eba2 0203 	sub.w	r2, r2, r3
70000c64:	ea80 0c01 	eor.w	ip, r0, r1
70000c68:	0249      	lsls	r1, r1, #9
70000c6a:	ea4f 2040 	mov.w	r0, r0, lsl #9
70000c6e:	d037      	beq.n	70000ce0 <__aeabi_fdiv+0x98>
70000c70:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70000c74:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70000c78:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70000c7c:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000c80:	428b      	cmp	r3, r1
70000c82:	bf38      	it	cc
70000c84:	005b      	lslcc	r3, r3, #1
70000c86:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70000c8a:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70000c8e:	428b      	cmp	r3, r1
70000c90:	bf24      	itt	cs
70000c92:	1a5b      	subcs	r3, r3, r1
70000c94:	ea40 000c 	orrcs.w	r0, r0, ip
70000c98:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70000c9c:	bf24      	itt	cs
70000c9e:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
70000ca2:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70000ca6:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70000caa:	bf24      	itt	cs
70000cac:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
70000cb0:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
70000cb4:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
70000cb8:	bf24      	itt	cs
70000cba:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
70000cbe:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
70000cc2:	011b      	lsls	r3, r3, #4
70000cc4:	bf18      	it	ne
70000cc6:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70000cca:	d1e0      	bne.n	70000c8e <__aeabi_fdiv+0x46>
70000ccc:	2afd      	cmp	r2, #253	; 0xfd
70000cce:	f63f af50 	bhi.w	70000b72 <__aeabi_fmul+0x92>
70000cd2:	428b      	cmp	r3, r1
70000cd4:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000cd8:	bf08      	it	eq
70000cda:	f020 0001 	biceq.w	r0, r0, #1
70000cde:	4770      	bx	lr
70000ce0:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000ce4:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000ce8:	327f      	adds	r2, #127	; 0x7f
70000cea:	bfc2      	ittt	gt
70000cec:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000cf0:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000cf4:	4770      	bxgt	lr
70000cf6:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000cfa:	f04f 0300 	mov.w	r3, #0
70000cfe:	3a01      	subs	r2, #1
70000d00:	e737      	b.n	70000b72 <__aeabi_fmul+0x92>
70000d02:	f092 0f00 	teq	r2, #0
70000d06:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000d0a:	bf02      	ittt	eq
70000d0c:	0040      	lsleq	r0, r0, #1
70000d0e:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000d12:	3a01      	subeq	r2, #1
70000d14:	d0f9      	beq.n	70000d0a <__aeabi_fdiv+0xc2>
70000d16:	ea40 000c 	orr.w	r0, r0, ip
70000d1a:	f093 0f00 	teq	r3, #0
70000d1e:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000d22:	bf02      	ittt	eq
70000d24:	0049      	lsleq	r1, r1, #1
70000d26:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000d2a:	3b01      	subeq	r3, #1
70000d2c:	d0f9      	beq.n	70000d22 <__aeabi_fdiv+0xda>
70000d2e:	ea41 010c 	orr.w	r1, r1, ip
70000d32:	e795      	b.n	70000c60 <__aeabi_fdiv+0x18>
70000d34:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000d38:	ea92 0f0c 	teq	r2, ip
70000d3c:	d108      	bne.n	70000d50 <__aeabi_fdiv+0x108>
70000d3e:	0242      	lsls	r2, r0, #9
70000d40:	f47f af7d 	bne.w	70000c3e <__aeabi_fmul+0x15e>
70000d44:	ea93 0f0c 	teq	r3, ip
70000d48:	f47f af70 	bne.w	70000c2c <__aeabi_fmul+0x14c>
70000d4c:	4608      	mov	r0, r1
70000d4e:	e776      	b.n	70000c3e <__aeabi_fmul+0x15e>
70000d50:	ea93 0f0c 	teq	r3, ip
70000d54:	d104      	bne.n	70000d60 <__aeabi_fdiv+0x118>
70000d56:	024b      	lsls	r3, r1, #9
70000d58:	f43f af4c 	beq.w	70000bf4 <__aeabi_fmul+0x114>
70000d5c:	4608      	mov	r0, r1
70000d5e:	e76e      	b.n	70000c3e <__aeabi_fmul+0x15e>
70000d60:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000d64:	bf18      	it	ne
70000d66:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000d6a:	d1ca      	bne.n	70000d02 <__aeabi_fdiv+0xba>
70000d6c:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70000d70:	f47f af5c 	bne.w	70000c2c <__aeabi_fmul+0x14c>
70000d74:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70000d78:	f47f af3c 	bne.w	70000bf4 <__aeabi_fmul+0x114>
70000d7c:	e75f      	b.n	70000c3e <__aeabi_fmul+0x15e>
70000d7e:	bf00      	nop

70000d80 <__gesf2>:
70000d80:	f04f 3cff 	mov.w	ip, #4294967295
70000d84:	e006      	b.n	70000d94 <__cmpsf2+0x4>
70000d86:	bf00      	nop

70000d88 <__lesf2>:
70000d88:	f04f 0c01 	mov.w	ip, #1
70000d8c:	e002      	b.n	70000d94 <__cmpsf2+0x4>
70000d8e:	bf00      	nop

70000d90 <__cmpsf2>:
70000d90:	f04f 0c01 	mov.w	ip, #1
70000d94:	f84d cd04 	str.w	ip, [sp, #-4]!
70000d98:	ea4f 0240 	mov.w	r2, r0, lsl #1
70000d9c:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000da0:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000da4:	bf18      	it	ne
70000da6:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000daa:	d011      	beq.n	70000dd0 <__cmpsf2+0x40>
70000dac:	b001      	add	sp, #4
70000dae:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
70000db2:	bf18      	it	ne
70000db4:	ea90 0f01 	teqne	r0, r1
70000db8:	bf58      	it	pl
70000dba:	ebb2 0003 	subspl.w	r0, r2, r3
70000dbe:	bf88      	it	hi
70000dc0:	17c8      	asrhi	r0, r1, #31
70000dc2:	bf38      	it	cc
70000dc4:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70000dc8:	bf18      	it	ne
70000dca:	f040 0001 	orrne.w	r0, r0, #1
70000dce:	4770      	bx	lr
70000dd0:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000dd4:	d102      	bne.n	70000ddc <__cmpsf2+0x4c>
70000dd6:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70000dda:	d105      	bne.n	70000de8 <__cmpsf2+0x58>
70000ddc:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70000de0:	d1e4      	bne.n	70000dac <__cmpsf2+0x1c>
70000de2:	ea5f 2c41 	movs.w	ip, r1, lsl #9
70000de6:	d0e1      	beq.n	70000dac <__cmpsf2+0x1c>
70000de8:	f85d 0b04 	ldr.w	r0, [sp], #4
70000dec:	4770      	bx	lr
70000dee:	bf00      	nop

70000df0 <__aeabi_cfrcmple>:
70000df0:	4684      	mov	ip, r0
70000df2:	4608      	mov	r0, r1
70000df4:	4661      	mov	r1, ip
70000df6:	e7ff      	b.n	70000df8 <__aeabi_cfcmpeq>

70000df8 <__aeabi_cfcmpeq>:
70000df8:	b50f      	push	{r0, r1, r2, r3, lr}
70000dfa:	f7ff ffc9 	bl	70000d90 <__cmpsf2>
70000dfe:	2800      	cmp	r0, #0
70000e00:	bf48      	it	mi
70000e02:	f110 0f00 	cmnmi.w	r0, #0
70000e06:	bd0f      	pop	{r0, r1, r2, r3, pc}

70000e08 <__aeabi_fcmpeq>:
70000e08:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e0c:	f7ff fff4 	bl	70000df8 <__aeabi_cfcmpeq>
70000e10:	bf0c      	ite	eq
70000e12:	2001      	moveq	r0, #1
70000e14:	2000      	movne	r0, #0
70000e16:	f85d fb08 	ldr.w	pc, [sp], #8
70000e1a:	bf00      	nop

70000e1c <__aeabi_fcmplt>:
70000e1c:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e20:	f7ff ffea 	bl	70000df8 <__aeabi_cfcmpeq>
70000e24:	bf34      	ite	cc
70000e26:	2001      	movcc	r0, #1
70000e28:	2000      	movcs	r0, #0
70000e2a:	f85d fb08 	ldr.w	pc, [sp], #8
70000e2e:	bf00      	nop

70000e30 <__aeabi_fcmple>:
70000e30:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e34:	f7ff ffe0 	bl	70000df8 <__aeabi_cfcmpeq>
70000e38:	bf94      	ite	ls
70000e3a:	2001      	movls	r0, #1
70000e3c:	2000      	movhi	r0, #0
70000e3e:	f85d fb08 	ldr.w	pc, [sp], #8
70000e42:	bf00      	nop

70000e44 <__aeabi_fcmpge>:
70000e44:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e48:	f7ff ffd2 	bl	70000df0 <__aeabi_cfrcmple>
70000e4c:	bf94      	ite	ls
70000e4e:	2001      	movls	r0, #1
70000e50:	2000      	movhi	r0, #0
70000e52:	f85d fb08 	ldr.w	pc, [sp], #8
70000e56:	bf00      	nop

70000e58 <__aeabi_fcmpgt>:
70000e58:	f84d ed08 	str.w	lr, [sp, #-8]!
70000e5c:	f7ff ffc8 	bl	70000df0 <__aeabi_cfrcmple>
70000e60:	bf34      	ite	cc
70000e62:	2001      	movcc	r0, #1
70000e64:	2000      	movcs	r0, #0
70000e66:	f85d fb08 	ldr.w	pc, [sp], #8
70000e6a:	bf00      	nop

70000e6c <__aeabi_f2uiz>:
70000e6c:	0042      	lsls	r2, r0, #1
70000e6e:	d20e      	bcs.n	70000e8e <__aeabi_f2uiz+0x22>
70000e70:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70000e74:	d30b      	bcc.n	70000e8e <__aeabi_f2uiz+0x22>
70000e76:	f04f 039e 	mov.w	r3, #158	; 0x9e
70000e7a:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70000e7e:	d409      	bmi.n	70000e94 <__aeabi_f2uiz+0x28>
70000e80:	ea4f 2300 	mov.w	r3, r0, lsl #8
70000e84:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000e88:	fa23 f002 	lsr.w	r0, r3, r2
70000e8c:	4770      	bx	lr
70000e8e:	f04f 0000 	mov.w	r0, #0
70000e92:	4770      	bx	lr
70000e94:	f112 0f61 	cmn.w	r2, #97	; 0x61
70000e98:	d101      	bne.n	70000e9e <__aeabi_f2uiz+0x32>
70000e9a:	0242      	lsls	r2, r0, #9
70000e9c:	d102      	bne.n	70000ea4 <__aeabi_f2uiz+0x38>
70000e9e:	f04f 30ff 	mov.w	r0, #4294967295
70000ea2:	4770      	bx	lr
70000ea4:	f04f 0000 	mov.w	r0, #0
70000ea8:	4770      	bx	lr
70000eaa:	bf00      	nop
