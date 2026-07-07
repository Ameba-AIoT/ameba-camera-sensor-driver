
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	81 04 00 70 11 01 00 70                             ...p...p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <bVts>:
7000004c:	00 00 00 00                                         ....

70000050 <g_status>:
	...

70000070 <g_ps5262_i2c_init_regs_asic>:
70000070:	ff 56 00 00 0b 41 83 00 14 01 08 00 15 01 98 00     .V...A..........
70000080:	62 01 02 00 78 41 b0 00 79 41 4a 00 26 02 16 00     b...xA..yAJ.&...
70000090:	27 02 1f 00 25 02 11 00 42 02 11 00 46 02 19 00     '...%...B...F...
700000a0:	47 02 26 00 48 02 61 00 49 02 11 00 12 42 c0 00     G.&.H.a.I....B..
700000b0:	54 06 01 00 55 06 f5 00 57 06 19 00 59 06 90 00     T...U...W...Y...
700000c0:	5b 06 2b 00 a3 06 40 00 ac 06 08 00 06 09 08 00     [.+...@.........
700000d0:	08 09 1c 00 0f 09 08 00 11 09 1c 00 19 09 03 00     ................
700000e0:	1a 09 03 00 0c 0b 00 00 15 14 05 00 17 14 03 00     ................
700000f0:	18 14 03 00 5b 14 10 00 0f 14 01 00 11 01 01 00     ....[...........
70000100:	0f 01 01 00                                         ....

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

70000120 <ps5262_get_info>:
70000120:	b510      	push	{r4, lr}
70000122:	bba8      	cbnz	r0, 70000190 <ps5262_get_info+0x70>
70000124:	b3a1      	cbz	r1, 70000190 <ps5262_get_info+0x70>
70000126:	f44f 62f0 	mov.w	r2, #1920	; 0x780
7000012a:	f44f 6387 	mov.w	r3, #1080	; 0x438
7000012e:	f24c 3450 	movw	r4, #50000	; 0xc350
70000132:	f8df c064 	ldr.w	ip, [pc, #100]	; 70000198 <ps5262_get_info+0x78>
70000136:	7108      	strb	r0, [r1, #4]
70000138:	f881 0098 	strb.w	r0, [r1, #152]	; 0x98
7000013c:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
70000140:	f8c1 02dc 	str.w	r0, [r1, #732]	; 0x2dc
70000144:	e9c1 2302 	strd	r2, r3, [r1, #8]
70000148:	4a14      	ldr	r2, [pc, #80]	; (7000019c <ps5262_get_info+0x7c>)
7000014a:	4b15      	ldr	r3, [pc, #84]	; (700001a0 <ps5262_get_info+0x80>)
7000014c:	6812      	ldr	r2, [r2, #0]
7000014e:	610b      	str	r3, [r1, #16]
70000150:	2301      	movs	r3, #1
70000152:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
70000156:	4a13      	ldr	r2, [pc, #76]	; (700001a4 <ps5262_get_info+0x84>)
70000158:	600b      	str	r3, [r1, #0]
7000015a:	7812      	ldrb	r2, [r2, #0]
7000015c:	f8c1 32d4 	str.w	r3, [r1, #724]	; 0x2d4
70000160:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
70000164:	2203      	movs	r2, #3
70000166:	e9c1 c42a 	strd	ip, r4, [r1, #168]	; 0xa8
7000016a:	f881 20a4 	strb.w	r2, [r1, #164]	; 0xa4
7000016e:	f44f 7481 	mov.w	r4, #258	; 0x102
70000172:	f8c1 2088 	str.w	r2, [r1, #136]	; 0x88
70000176:	f881 22d8 	strb.w	r2, [r1, #728]	; 0x2d8
7000017a:	f44f 727a 	mov.w	r2, #1000	; 0x3e8
7000017e:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
70000182:	f8c1 22e0 	str.w	r2, [r1, #736]	; 0x2e0
70000186:	e9c1 0024 	strd	r0, r0, [r1, #144]	; 0x90
7000018a:	e9c1 3027 	strd	r3, r0, [r1, #156]	; 0x9c
7000018e:	bd10      	pop	{r4, pc}
70000190:	f06f 0015 	mvn.w	r0, #21
70000194:	e7fb      	b.n	7000018e <ps5262_get_info+0x6e>
70000196:	bf00      	nop
70000198:	019bfcc0 	.word	0x019bfcc0
7000019c:	70000104 	.word	0x70000104
700001a0:	41f00000 	.word	0x41f00000
700001a4:	70000050 	.word	0x70000050

700001a8 <ps5262_get_init_info>:
700001a8:	b538      	push	{r3, r4, r5, lr}
700001aa:	4614      	mov	r4, r2
700001ac:	4605      	mov	r5, r0
700001ae:	2800      	cmp	r0, #0
700001b0:	d138      	bne.n	70000224 <ps5262_get_init_info+0x7c>
700001b2:	2a00      	cmp	r2, #0
700001b4:	d036      	beq.n	70000224 <ps5262_get_init_info+0x7c>
700001b6:	68c8      	ldr	r0, [r1, #12]
700001b8:	f000 fdda 	bl	70000d70 <__aeabi_f2uiz>
700001bc:	b280      	uxth	r0, r0
700001be:	281e      	cmp	r0, #30
700001c0:	d130      	bne.n	70000224 <ps5262_get_init_info+0x7c>
700001c2:	4b1a      	ldr	r3, [pc, #104]	; (7000022c <ps5262_get_init_info+0x84>)
700001c4:	f44f 61f1 	mov.w	r1, #1928	; 0x788
700001c8:	f640 1c42 	movw	ip, #2370	; 0x942
700001cc:	f240 4265 	movw	r2, #1125	; 0x465
700001d0:	6063      	str	r3, [r4, #4]
700001d2:	2325      	movs	r3, #37	; 0x25
700001d4:	f8c4 2098 	str.w	r2, [r4, #152]	; 0x98
700001d8:	4628      	mov	r0, r5
700001da:	6023      	str	r3, [r4, #0]
700001dc:	2305      	movs	r3, #5
700001de:	f8c4 5088 	str.w	r5, [r4, #136]	; 0x88
700001e2:	60a3      	str	r3, [r4, #8]
700001e4:	2302      	movs	r3, #2
700001e6:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
700001ea:	f240 4303 	movw	r3, #1027	; 0x403
700001ee:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
700001f2:	230a      	movs	r3, #10
700001f4:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
700001f8:	2304      	movs	r3, #4
700001fa:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
700001fe:	f44f 6388 	mov.w	r3, #1088	; 0x440
70000202:	e9c4 1320 	strd	r1, r3, [r4, #128]	; 0x80
70000206:	2301      	movs	r3, #1
70000208:	f8c4 308c 	str.w	r3, [r4, #140]	; 0x8c
7000020c:	4b08      	ldr	r3, [pc, #32]	; (70000230 <ps5262_get_init_info+0x88>)
7000020e:	e9c4 3c24 	strd	r3, ip, [r4, #144]	; 0x90
70000212:	4b08      	ldr	r3, [pc, #32]	; (70000234 <ps5262_get_init_info+0x8c>)
70000214:	605a      	str	r2, [r3, #4]
70000216:	f248 32d6 	movw	r2, #33750	; 0x83d6
7000021a:	f8c4 209c 	str.w	r2, [r4, #156]	; 0x9c
7000021e:	4a06      	ldr	r2, [pc, #24]	; (70000238 <ps5262_get_init_info+0x90>)
70000220:	609a      	str	r2, [r3, #8]
70000222:	bd38      	pop	{r3, r4, r5, pc}
70000224:	f06f 0015 	mvn.w	r0, #21
70000228:	e7fb      	b.n	70000222 <ps5262_get_init_info+0x7a>
7000022a:	bf00      	nop
7000022c:	70000070 	.word	0x70000070
70000230:	04c4b400 	.word	0x04c4b400
70000234:	70000050 	.word	0x70000050
70000238:	41ed0000 	.word	0x41ed0000

7000023c <ps5262_start>:
7000023c:	b918      	cbnz	r0, 70000246 <ps5262_start+0xa>
7000023e:	4b03      	ldr	r3, [pc, #12]	; (7000024c <ps5262_start+0x10>)
70000240:	2200      	movs	r2, #0
70000242:	60da      	str	r2, [r3, #12]
70000244:	4770      	bx	lr
70000246:	f06f 0015 	mvn.w	r0, #21
7000024a:	4770      	bx	lr
7000024c:	70000050 	.word	0x70000050

70000250 <ps5262_get_exposure_range>:
70000250:	b570      	push	{r4, r5, r6, lr}
70000252:	460c      	mov	r4, r1
70000254:	b970      	cbnz	r0, 70000274 <ps5262_get_exposure_range+0x24>
70000256:	4909      	ldr	r1, [pc, #36]	; (7000027c <ps5262_get_exposure_range+0x2c>)
70000258:	780d      	ldrb	r5, [r1, #0]
7000025a:	b955      	cbnz	r5, 70000272 <ps5262_get_exposure_range+0x22>
7000025c:	688e      	ldr	r6, [r1, #8]
7000025e:	4620      	mov	r0, r4
70000260:	601e      	str	r6, [r3, #0]
70000262:	f000 fb67 	bl	70000934 <__aeabi_ui2f>
70000266:	4631      	mov	r1, r6
70000268:	f000 fbbc 	bl	700009e4 <__aeabi_fmul>
7000026c:	9b04      	ldr	r3, [sp, #16]
7000026e:	6018      	str	r0, [r3, #0]
70000270:	4628      	mov	r0, r5
70000272:	bd70      	pop	{r4, r5, r6, pc}
70000274:	f06f 0015 	mvn.w	r0, #21
70000278:	e7fb      	b.n	70000272 <ps5262_get_exposure_range+0x22>
7000027a:	bf00      	nop
7000027c:	70000050 	.word	0x70000050

70000280 <ps5262_get_tuned_dgain>:
70000280:	b920      	cbnz	r0, 7000028c <ps5262_get_tuned_dgain+0xc>
70000282:	b119      	cbz	r1, 7000028c <ps5262_get_tuned_dgain+0xc>
70000284:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
70000288:	600b      	str	r3, [r1, #0]
7000028a:	4770      	bx	lr
7000028c:	f06f 0015 	mvn.w	r0, #21
70000290:	4770      	bx	lr
	...

70000294 <ps5262_get_exposure_gain_info>:
70000294:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
70000298:	4688      	mov	r8, r1
7000029a:	4614      	mov	r4, r2
7000029c:	2800      	cmp	r0, #0
7000029e:	d169      	bne.n	70000374 <ps5262_get_exposure_gain_info+0xe0>
700002a0:	2900      	cmp	r1, #0
700002a2:	d067      	beq.n	70000374 <ps5262_get_exposure_gain_info+0xe0>
700002a4:	2a00      	cmp	r2, #0
700002a6:	d065      	beq.n	70000374 <ps5262_get_exposure_gain_info+0xe0>
700002a8:	680f      	ldr	r7, [r1, #0]
700002aa:	1d15      	adds	r5, r2, #4
700002ac:	4e33      	ldr	r6, [pc, #204]	; (7000037c <ps5262_get_exposure_gain_info+0xe8>)
700002ae:	4639      	mov	r1, r7
700002b0:	68f0      	ldr	r0, [r6, #12]
700002b2:	f000 fa8d 	bl	700007d0 <__aeabi_fsub>
700002b6:	2100      	movs	r1, #0
700002b8:	4681      	mov	r9, r0
700002ba:	f000 fd45 	bl	70000d48 <__aeabi_fcmpge>
700002be:	2800      	cmp	r0, #0
700002c0:	d051      	beq.n	70000366 <ps5262_get_exposure_gain_info+0xd2>
700002c2:	492f      	ldr	r1, [pc, #188]	; (70000380 <ps5262_get_exposure_gain_info+0xec>)
700002c4:	4648      	mov	r0, r9
700002c6:	f000 fd49 	bl	70000d5c <__aeabi_fcmpgt>
700002ca:	2800      	cmp	r0, #0
700002cc:	d03c      	beq.n	70000348 <ps5262_get_exposure_gain_info+0xb4>
700002ce:	68b1      	ldr	r1, [r6, #8]
700002d0:	4638      	mov	r0, r7
700002d2:	f000 fc3b 	bl	70000b4c <__aeabi_fdiv>
700002d6:	f8d8 8018 	ldr.w	r8, [r8, #24]
700002da:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
700002de:	f000 fa79 	bl	700007d4 <__addsf3>
700002e2:	f000 fd45 	bl	70000d70 <__aeabi_f2uiz>
700002e6:	fa1f f388 	uxth.w	r3, r8
700002ea:	b280      	uxth	r0, r0
700002ec:	1e9a      	subs	r2, r3, #2
700002ee:	b292      	uxth	r2, r2
700002f0:	4282      	cmp	r2, r0
700002f2:	d303      	bcc.n	700002fc <ps5262_get_exposure_gain_info+0x68>
700002f4:	2801      	cmp	r0, #1
700002f6:	4602      	mov	r2, r0
700002f8:	bf38      	it	cc
700002fa:	2201      	movcc	r2, #1
700002fc:	4821      	ldr	r0, [pc, #132]	; (70000384 <ps5262_get_exposure_gain_info+0xf0>)
700002fe:	6801      	ldr	r1, [r0, #0]
70000300:	4541      	cmp	r1, r8
70000302:	d035      	beq.n	70000370 <ps5262_get_exposure_gain_info+0xdc>
70000304:	f44f 718b 	mov.w	r1, #278	; 0x116
70000308:	b2db      	uxtb	r3, r3
7000030a:	f8c0 8000 	str.w	r8, [r0]
7000030e:	2002      	movs	r0, #2
70000310:	81a1      	strh	r1, [r4, #12]
70000312:	ea4f 2118 	mov.w	r1, r8, lsr #8
70000316:	8463      	strh	r3, [r4, #34]	; 0x22
70000318:	81e1      	strh	r1, [r4, #14]
7000031a:	f240 1117 	movw	r1, #279	; 0x117
7000031e:	8421      	strh	r1, [r4, #32]
70000320:	2314      	movs	r3, #20
70000322:	f44f 7c8c 	mov.w	ip, #280	; 0x118
70000326:	4343      	muls	r3, r0
70000328:	3002      	adds	r0, #2
7000032a:	18e9      	adds	r1, r5, r3
7000032c:	3314      	adds	r3, #20
7000032e:	f8a1 c008 	strh.w	ip, [r1, #8]
70000332:	ea4f 2c12 	mov.w	ip, r2, lsr #8
70000336:	442b      	add	r3, r5
70000338:	b2d2      	uxtb	r2, r2
7000033a:	f8a1 c00a 	strh.w	ip, [r1, #10]
7000033e:	f240 1119 	movw	r1, #281	; 0x119
70000342:	815a      	strh	r2, [r3, #10]
70000344:	8119      	strh	r1, [r3, #8]
70000346:	60f7      	str	r7, [r6, #12]
70000348:	2314      	movs	r3, #20
7000034a:	f240 122b 	movw	r2, #299	; 0x12b
7000034e:	fb03 5500 	mla	r5, r3, r0, r5
70000352:	8a33      	ldrh	r3, [r6, #16]
70000354:	3002      	adds	r0, #2
70000356:	816b      	strh	r3, [r5, #10]
70000358:	4b0b      	ldr	r3, [pc, #44]	; (70000388 <ps5262_get_exposure_gain_info+0xf4>)
7000035a:	812a      	strh	r2, [r5, #8]
7000035c:	61eb      	str	r3, [r5, #28]
7000035e:	6020      	str	r0, [r4, #0]
70000360:	2000      	movs	r0, #0
70000362:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
70000366:	4909      	ldr	r1, [pc, #36]	; (7000038c <ps5262_get_exposure_gain_info+0xf8>)
70000368:	4648      	mov	r0, r9
7000036a:	f000 fcd9 	bl	70000d20 <__aeabi_fcmplt>
7000036e:	e7ac      	b.n	700002ca <ps5262_get_exposure_gain_info+0x36>
70000370:	2000      	movs	r0, #0
70000372:	e7d5      	b.n	70000320 <ps5262_get_exposure_gain_info+0x8c>
70000374:	f06f 0015 	mvn.w	r0, #21
70000378:	e7f3      	b.n	70000362 <ps5262_get_exposure_gain_info+0xce>
7000037a:	bf00      	nop
7000037c:	70000050 	.word	0x70000050
70000380:	3a83126f 	.word	0x3a83126f
70000384:	7000004c 	.word	0x7000004c
70000388:	00010111 	.word	0x00010111
7000038c:	ba83126f 	.word	0xba83126f

70000390 <ps5262_set_mirror_flip>:
70000390:	2301      	movs	r3, #1
70000392:	708b      	strb	r3, [r1, #2]
70000394:	2300      	movs	r3, #0
70000396:	4618      	mov	r0, r3
70000398:	604b      	str	r3, [r1, #4]
7000039a:	4770      	bx	lr

7000039c <ps5262_check>:
7000039c:	b573      	push	{r0, r1, r4, r5, r6, lr}
7000039e:	4d18      	ldr	r5, [pc, #96]	; (70000400 <ps5262_check+0x64>)
700003a0:	4604      	mov	r4, r0
700003a2:	682b      	ldr	r3, [r5, #0]
700003a4:	6c1b      	ldr	r3, [r3, #64]	; 0x40
700003a6:	4798      	blx	r3
700003a8:	2801      	cmp	r0, #1
700003aa:	dc25      	bgt.n	700003f8 <ps5262_check+0x5c>
700003ac:	4b15      	ldr	r3, [pc, #84]	; (70000404 <ps5262_check+0x68>)
700003ae:	f853 2020 	ldr.w	r2, [r3, r0, lsl #2]
700003b2:	4b15      	ldr	r3, [pc, #84]	; (70000408 <ps5262_check+0x6c>)
700003b4:	601a      	str	r2, [r3, #0]
700003b6:	682b      	ldr	r3, [r5, #0]
700003b8:	685b      	ldr	r3, [r3, #4]
700003ba:	4798      	blx	r3
700003bc:	f44f 4382 	mov.w	r3, #16640	; 0x4100
700003c0:	a901      	add	r1, sp, #4
700003c2:	4620      	mov	r0, r4
700003c4:	f8ad 3004 	strh.w	r3, [sp, #4]
700003c8:	682b      	ldr	r3, [r5, #0]
700003ca:	68db      	ldr	r3, [r3, #12]
700003cc:	4798      	blx	r3
700003ce:	b9a8      	cbnz	r0, 700003fc <ps5262_check+0x60>
700003d0:	f244 1301 	movw	r3, #16641	; 0x4101
700003d4:	a901      	add	r1, sp, #4
700003d6:	4620      	mov	r0, r4
700003d8:	f8bd 6006 	ldrh.w	r6, [sp, #6]
700003dc:	f8ad 3004 	strh.w	r3, [sp, #4]
700003e0:	682b      	ldr	r3, [r5, #0]
700003e2:	68db      	ldr	r3, [r3, #12]
700003e4:	4798      	blx	r3
700003e6:	b948      	cbnz	r0, 700003fc <ps5262_check+0x60>
700003e8:	f8bd 3006 	ldrh.w	r3, [sp, #6]
700003ec:	f245 2262 	movw	r2, #21090	; 0x5262
700003f0:	ea43 2306 	orr.w	r3, r3, r6, lsl #8
700003f4:	4293      	cmp	r3, r2
700003f6:	d001      	beq.n	700003fc <ps5262_check+0x60>
700003f8:	f06f 0015 	mvn.w	r0, #21
700003fc:	b002      	add	sp, #8
700003fe:	bd70      	pop	{r4, r5, r6, pc}
70000400:	70000048 	.word	0x70000048
70000404:	70000108 	.word	0x70000108
70000408:	70000104 	.word	0x70000104

7000040c <ps5262_get_slave_addr_num>:
7000040c:	2002      	movs	r0, #2
7000040e:	4770      	bx	lr

70000410 <ps5262_get_tuned_again>:
70000410:	b570      	push	{r4, r5, r6, lr}
70000412:	460d      	mov	r5, r1
70000414:	4604      	mov	r4, r0
70000416:	bb10      	cbnz	r0, 7000045e <ps5262_get_tuned_again+0x4e>
70000418:	b309      	cbz	r1, 7000045e <ps5262_get_tuned_again+0x4e>
7000041a:	f04f 4187 	mov.w	r1, #1132462080	; 0x43800000
7000041e:	6828      	ldr	r0, [r5, #0]
70000420:	f000 fae0 	bl	700009e4 <__aeabi_fmul>
70000424:	f000 fca4 	bl	70000d70 <__aeabi_f2uiz>
70000428:	4a0e      	ldr	r2, [pc, #56]	; (70000464 <ps5262_get_tuned_again+0x54>)
7000042a:	b280      	uxth	r0, r0
7000042c:	4623      	mov	r3, r4
7000042e:	f852 1b04 	ldr.w	r1, [r2], #4
70000432:	461c      	mov	r4, r3
70000434:	3301      	adds	r3, #1
70000436:	4288      	cmp	r0, r1
70000438:	d30e      	bcc.n	70000458 <ps5262_get_tuned_again+0x48>
7000043a:	6816      	ldr	r6, [r2, #0]
7000043c:	42b0      	cmp	r0, r6
7000043e:	d20b      	bcs.n	70000458 <ps5262_get_tuned_again+0x48>
70000440:	4b09      	ldr	r3, [pc, #36]	; (70000468 <ps5262_get_tuned_again+0x58>)
70000442:	b288      	uxth	r0, r1
70000444:	611c      	str	r4, [r3, #16]
70000446:	f000 fa79 	bl	7000093c <__aeabi_i2f>
7000044a:	f04f 516e 	mov.w	r1, #998244352	; 0x3b800000
7000044e:	f000 fac9 	bl	700009e4 <__aeabi_fmul>
70000452:	6028      	str	r0, [r5, #0]
70000454:	2000      	movs	r0, #0
70000456:	bd70      	pop	{r4, r5, r6, pc}
70000458:	2b50      	cmp	r3, #80	; 0x50
7000045a:	d1e8      	bne.n	7000042e <ps5262_get_tuned_again+0x1e>
7000045c:	e7f3      	b.n	70000446 <ps5262_get_tuned_again+0x36>
7000045e:	f06f 0015 	mvn.w	r0, #21
70000462:	e7f8      	b.n	70000456 <ps5262_get_tuned_again+0x46>
70000464:	70000488 	.word	0x70000488
70000468:	70000050 	.word	0x70000050

7000046c <clip_d_word>:
7000046c:	4603      	mov	r3, r0
7000046e:	4610      	mov	r0, r2
70000470:	4293      	cmp	r3, r2
70000472:	d803      	bhi.n	7000047c <clip_d_word+0x10>
70000474:	428b      	cmp	r3, r1
70000476:	bf38      	it	cc
70000478:	460b      	movcc	r3, r1
7000047a:	4618      	mov	r0, r3
7000047c:	4770      	bx	lr
	...

70000480 <rts_isp_get_sensor_ops>:
70000480:	4800      	ldr	r0, [pc, #0]	; (70000484 <rts_isp_get_sensor_ops+0x4>)
70000482:	4770      	bx	lr
70000484:	700005cc 	.word	0x700005cc

70000488 <ps5262_gain_table>:
70000488:	00000100 00000110 00000120 00000130     ........ ...0...
70000498:	00000140 00000150 00000160 00000170     @...P...`...p...
700004a8:	00000180 00000190 000001a0 000001b0     ................
700004b8:	000001c0 000001d0 000001e0 000001f0     ................
700004c8:	00000200 00000220 00000240 00000260     .... ...@...`...
700004d8:	00000280 000002a0 000002c0 000002e0     ................
700004e8:	00000300 00000320 00000340 00000360     .... ...@...`...
700004f8:	00000380 000003a0 000003c0 000003e0     ................
70000508:	00000400 00000440 00000480 000004c0     ....@...........
70000518:	00000500 00000540 00000580 000005c0     ....@...........
70000528:	00000600 00000640 00000680 000006c0     ....@...........
70000538:	00000700 00000740 00000780 000007c0     ....@...........
70000548:	00000800 00000880 00000900 00000980     ................
70000558:	00000a00 00000a80 00000b00 00000b80     ................
70000568:	00000c00 00000c80 00000d00 00000d80     ................
70000578:	00000e00 00000e80 00000f00 00000f80     ................
70000588:	00001000 00001100 00001200 00001300     ................
70000598:	00001400 00001500 00001600 00001700     ................
700005a8:	00001800 00001900 00001a00 00001b00     ................
700005b8:	00001c00 00001d00 00001e00 00001f00     ................
700005c8:	00002000                                . ..

700005cc <ps5262_ops>:
700005cc:	73000005 32357370 00003236 00000000     ...sps5262......
	...
700005f0:	70000121 700001a9 70000251 70000411     !..p...pQ..p...p
70000600:	70000281 70000295 00000000 00000000     ...p...p........
70000610:	7000023d 00000000 00000000 00000000     =..p............
70000620:	70000391 00000000 00000000 00000000     ...p............
70000630:	7000039d 00000000 00000000 00000000     ...p............
70000640:	7000040d 00000000 00000000 00000000     ...p............
	...
70000660:	0cfff04f 52d0ea1c ea1cbf1e ea9253d1     O......R.....S..
70000670:	ea930f0c d06f0f0c ea80441a 02400c01     ......o..D....@.
70000680:	ea5fbf18 d01e2141 6300f04f 1050ea43     .._.A!..O..cC.P.
70000690:	1151ea43 3101fba0 4000f00c 0f00f5b1     C.Q....1...@....
700006a0:	0049bf3e 71d3ea41 ea40005b f1620001     >.I.A..q[.@...b.
700006b0:	2afd027f f1b3d81d eb404f00 bf0850c2     ...*.....O@..P..
700006c0:	0001f020 f0904770 f00c0f00 bf084c00      ...pG.......L..
700006d0:	ea4c0249 ea402050 3a7f2051 f1d2bfc2     I.L.P @.Q .:....
700006e0:	ea4003ff 477050c2 0000f440 0300f04f     ..@..PpG@...O...
700006f0:	dc5d3a01 0f19f112 f000bfdc 47704000     .:]..........@pG
70000700:	0200f1c2 fa210041 f1c2f102 fa000220     ....A.!..... ...
70000710:	ea5ffc02 f1400031 ea530000 bf08034c     .._.1.@...S.L...
70000720:	70dcea20 f0924770 f0000f00 bf024c00      ..ppG.......L..
70000730:	f4100040 3a010f00 ea40d0f9 f093000c     @......:..@.....
70000740:	f0010f00 bf024c00 f4110049 3b010f00     .....L..I......;
70000750:	ea41d0f9 e78f010c 53d1ea0c 0f0cea92     ..A........S....
70000760:	ea93bf18 d00a0f0c 4c00f030 f031bf18     ........0..L..1.
70000770:	d1d84c00 0001ea80 4000f000 f0904770     .L.........@pG..
70000780:	bf170f00 4f00f090 f0914608 f0910f00     .......O.F......
70000790:	d0144f00 0f0cea92 0242d101 ea93d10f     .O........B.....
700007a0:	d1030f0c bf18024b d1084608 0001ea80     ....K....F......
700007b0:	4000f000 40fef040 0000f440 f0404770     ...@@..@@...pG@.
700007c0:	f44040fe 47700040                       .@@.@.pG

700007c8 <__aeabi_frsub>:
700007c8:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
700007cc:	e002      	b.n	700007d4 <__addsf3>
700007ce:	bf00      	nop

700007d0 <__aeabi_fsub>:
700007d0:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

700007d4 <__addsf3>:
700007d4:	0042      	lsls	r2, r0, #1
700007d6:	bf1f      	itttt	ne
700007d8:	ea5f 0341 	movsne.w	r3, r1, lsl #1
700007dc:	ea92 0f03 	teqne	r2, r3
700007e0:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
700007e4:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700007e8:	d06a      	beq.n	700008c0 <__addsf3+0xec>
700007ea:	ea4f 6212 	mov.w	r2, r2, lsr #24
700007ee:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
700007f2:	bfc1      	itttt	gt
700007f4:	18d2      	addgt	r2, r2, r3
700007f6:	4041      	eorgt	r1, r0
700007f8:	4048      	eorgt	r0, r1
700007fa:	4041      	eorgt	r1, r0
700007fc:	bfb8      	it	lt
700007fe:	425b      	neglt	r3, r3
70000800:	2b19      	cmp	r3, #25
70000802:	bf88      	it	hi
70000804:	4770      	bxhi	lr
70000806:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
7000080a:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
7000080e:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
70000812:	bf18      	it	ne
70000814:	4240      	negne	r0, r0
70000816:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
7000081a:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
7000081e:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
70000822:	bf18      	it	ne
70000824:	4249      	negne	r1, r1
70000826:	ea92 0f03 	teq	r2, r3
7000082a:	d03f      	beq.n	700008ac <__addsf3+0xd8>
7000082c:	f1a2 0201 	sub.w	r2, r2, #1
70000830:	fa41 fc03 	asr.w	ip, r1, r3
70000834:	eb10 000c 	adds.w	r0, r0, ip
70000838:	f1c3 0320 	rsb	r3, r3, #32
7000083c:	fa01 f103 	lsl.w	r1, r1, r3
70000840:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000844:	d502      	bpl.n	7000084c <__addsf3+0x78>
70000846:	4249      	negs	r1, r1
70000848:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
7000084c:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70000850:	d313      	bcc.n	7000087a <__addsf3+0xa6>
70000852:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
70000856:	d306      	bcc.n	70000866 <__addsf3+0x92>
70000858:	0840      	lsrs	r0, r0, #1
7000085a:	ea4f 0131 	mov.w	r1, r1, rrx
7000085e:	f102 0201 	add.w	r2, r2, #1
70000862:	2afe      	cmp	r2, #254	; 0xfe
70000864:	d251      	bcs.n	7000090a <__addsf3+0x136>
70000866:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
7000086a:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
7000086e:	bf08      	it	eq
70000870:	f020 0001 	biceq.w	r0, r0, #1
70000874:	ea40 0003 	orr.w	r0, r0, r3
70000878:	4770      	bx	lr
7000087a:	0049      	lsls	r1, r1, #1
7000087c:	eb40 0000 	adc.w	r0, r0, r0
70000880:	3a01      	subs	r2, #1
70000882:	bf28      	it	cs
70000884:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70000888:	d2ed      	bcs.n	70000866 <__addsf3+0x92>
7000088a:	fab0 fc80 	clz	ip, r0
7000088e:	f1ac 0c08 	sub.w	ip, ip, #8
70000892:	ebb2 020c 	subs.w	r2, r2, ip
70000896:	fa00 f00c 	lsl.w	r0, r0, ip
7000089a:	bfaa      	itet	ge
7000089c:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
700008a0:	4252      	neglt	r2, r2
700008a2:	4318      	orrge	r0, r3
700008a4:	bfbc      	itt	lt
700008a6:	40d0      	lsrlt	r0, r2
700008a8:	4318      	orrlt	r0, r3
700008aa:	4770      	bx	lr
700008ac:	f092 0f00 	teq	r2, #0
700008b0:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
700008b4:	bf06      	itte	eq
700008b6:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
700008ba:	3201      	addeq	r2, #1
700008bc:	3b01      	subne	r3, #1
700008be:	e7b5      	b.n	7000082c <__addsf3+0x58>
700008c0:	ea4f 0341 	mov.w	r3, r1, lsl #1
700008c4:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700008c8:	bf18      	it	ne
700008ca:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
700008ce:	d021      	beq.n	70000914 <__addsf3+0x140>
700008d0:	ea92 0f03 	teq	r2, r3
700008d4:	d004      	beq.n	700008e0 <__addsf3+0x10c>
700008d6:	f092 0f00 	teq	r2, #0
700008da:	bf08      	it	eq
700008dc:	4608      	moveq	r0, r1
700008de:	4770      	bx	lr
700008e0:	ea90 0f01 	teq	r0, r1
700008e4:	bf1c      	itt	ne
700008e6:	2000      	movne	r0, #0
700008e8:	4770      	bxne	lr
700008ea:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
700008ee:	d104      	bne.n	700008fa <__addsf3+0x126>
700008f0:	0040      	lsls	r0, r0, #1
700008f2:	bf28      	it	cs
700008f4:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
700008f8:	4770      	bx	lr
700008fa:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
700008fe:	bf3c      	itt	cc
70000900:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
70000904:	4770      	bxcc	lr
70000906:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
7000090a:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
7000090e:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000912:	4770      	bx	lr
70000914:	ea7f 6222 	mvns.w	r2, r2, asr #24
70000918:	bf16      	itet	ne
7000091a:	4608      	movne	r0, r1
7000091c:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
70000920:	4601      	movne	r1, r0
70000922:	0242      	lsls	r2, r0, #9
70000924:	bf06      	itte	eq
70000926:	ea5f 2341 	movseq.w	r3, r1, lsl #9
7000092a:	ea90 0f01 	teqeq	r0, r1
7000092e:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
70000932:	4770      	bx	lr

70000934 <__aeabi_ui2f>:
70000934:	f04f 0300 	mov.w	r3, #0
70000938:	e004      	b.n	70000944 <__aeabi_i2f+0x8>
7000093a:	bf00      	nop

7000093c <__aeabi_i2f>:
7000093c:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
70000940:	bf48      	it	mi
70000942:	4240      	negmi	r0, r0
70000944:	ea5f 0c00 	movs.w	ip, r0
70000948:	bf08      	it	eq
7000094a:	4770      	bxeq	lr
7000094c:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
70000950:	4601      	mov	r1, r0
70000952:	f04f 0000 	mov.w	r0, #0
70000956:	e01c      	b.n	70000992 <__aeabi_l2f+0x2a>

70000958 <__aeabi_ul2f>:
70000958:	ea50 0201 	orrs.w	r2, r0, r1
7000095c:	bf08      	it	eq
7000095e:	4770      	bxeq	lr
70000960:	f04f 0300 	mov.w	r3, #0
70000964:	e00a      	b.n	7000097c <__aeabi_l2f+0x14>
70000966:	bf00      	nop

70000968 <__aeabi_l2f>:
70000968:	ea50 0201 	orrs.w	r2, r0, r1
7000096c:	bf08      	it	eq
7000096e:	4770      	bxeq	lr
70000970:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70000974:	d502      	bpl.n	7000097c <__aeabi_l2f+0x14>
70000976:	4240      	negs	r0, r0
70000978:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
7000097c:	ea5f 0c01 	movs.w	ip, r1
70000980:	bf02      	ittt	eq
70000982:	4684      	moveq	ip, r0
70000984:	4601      	moveq	r1, r0
70000986:	2000      	moveq	r0, #0
70000988:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
7000098c:	bf08      	it	eq
7000098e:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
70000992:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
70000996:	fabc f28c 	clz	r2, ip
7000099a:	3a08      	subs	r2, #8
7000099c:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
700009a0:	db10      	blt.n	700009c4 <__aeabi_l2f+0x5c>
700009a2:	fa01 fc02 	lsl.w	ip, r1, r2
700009a6:	4463      	add	r3, ip
700009a8:	fa00 fc02 	lsl.w	ip, r0, r2
700009ac:	f1c2 0220 	rsb	r2, r2, #32
700009b0:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
700009b4:	fa20 f202 	lsr.w	r2, r0, r2
700009b8:	eb43 0002 	adc.w	r0, r3, r2
700009bc:	bf08      	it	eq
700009be:	f020 0001 	biceq.w	r0, r0, #1
700009c2:	4770      	bx	lr
700009c4:	f102 0220 	add.w	r2, r2, #32
700009c8:	fa01 fc02 	lsl.w	ip, r1, r2
700009cc:	f1c2 0220 	rsb	r2, r2, #32
700009d0:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
700009d4:	fa21 f202 	lsr.w	r2, r1, r2
700009d8:	eb43 0002 	adc.w	r0, r3, r2
700009dc:	bf08      	it	eq
700009de:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
700009e2:	4770      	bx	lr

700009e4 <__aeabi_fmul>:
700009e4:	f04f 0cff 	mov.w	ip, #255	; 0xff
700009e8:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
700009ec:	bf1e      	ittt	ne
700009ee:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
700009f2:	ea92 0f0c 	teqne	r2, ip
700009f6:	ea93 0f0c 	teqne	r3, ip
700009fa:	d06f      	beq.n	70000adc <__aeabi_fmul+0xf8>
700009fc:	441a      	add	r2, r3
700009fe:	ea80 0c01 	eor.w	ip, r0, r1
70000a02:	0240      	lsls	r0, r0, #9
70000a04:	bf18      	it	ne
70000a06:	ea5f 2141 	movsne.w	r1, r1, lsl #9
70000a0a:	d01e      	beq.n	70000a4a <__aeabi_fmul+0x66>
70000a0c:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000a10:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000a14:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000a18:	fba0 3101 	umull	r3, r1, r0, r1
70000a1c:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000a20:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000a24:	bf3e      	ittt	cc
70000a26:	0049      	lslcc	r1, r1, #1
70000a28:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70000a2c:	005b      	lslcc	r3, r3, #1
70000a2e:	ea40 0001 	orr.w	r0, r0, r1
70000a32:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000a36:	2afd      	cmp	r2, #253	; 0xfd
70000a38:	d81d      	bhi.n	70000a76 <__aeabi_fmul+0x92>
70000a3a:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
70000a3e:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000a42:	bf08      	it	eq
70000a44:	f020 0001 	biceq.w	r0, r0, #1
70000a48:	4770      	bx	lr
70000a4a:	f090 0f00 	teq	r0, #0
70000a4e:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000a52:	bf08      	it	eq
70000a54:	0249      	lsleq	r1, r1, #9
70000a56:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000a5a:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
70000a5e:	3a7f      	subs	r2, #127	; 0x7f
70000a60:	bfc2      	ittt	gt
70000a62:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000a66:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000a6a:	4770      	bxgt	lr
70000a6c:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000a70:	f04f 0300 	mov.w	r3, #0
70000a74:	3a01      	subs	r2, #1
70000a76:	dc5d      	bgt.n	70000b34 <__aeabi_fmul+0x150>
70000a78:	f112 0f19 	cmn.w	r2, #25
70000a7c:	bfdc      	itt	le
70000a7e:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000a82:	4770      	bxle	lr
70000a84:	f1c2 0200 	rsb	r2, r2, #0
70000a88:	0041      	lsls	r1, r0, #1
70000a8a:	fa21 f102 	lsr.w	r1, r1, r2
70000a8e:	f1c2 0220 	rsb	r2, r2, #32
70000a92:	fa00 fc02 	lsl.w	ip, r0, r2
70000a96:	ea5f 0031 	movs.w	r0, r1, rrx
70000a9a:	f140 0000 	adc.w	r0, r0, #0
70000a9e:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
70000aa2:	bf08      	it	eq
70000aa4:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70000aa8:	4770      	bx	lr
70000aaa:	f092 0f00 	teq	r2, #0
70000aae:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000ab2:	bf02      	ittt	eq
70000ab4:	0040      	lsleq	r0, r0, #1
70000ab6:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000aba:	3a01      	subeq	r2, #1
70000abc:	d0f9      	beq.n	70000ab2 <__aeabi_fmul+0xce>
70000abe:	ea40 000c 	orr.w	r0, r0, ip
70000ac2:	f093 0f00 	teq	r3, #0
70000ac6:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000aca:	bf02      	ittt	eq
70000acc:	0049      	lsleq	r1, r1, #1
70000ace:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000ad2:	3b01      	subeq	r3, #1
70000ad4:	d0f9      	beq.n	70000aca <__aeabi_fmul+0xe6>
70000ad6:	ea41 010c 	orr.w	r1, r1, ip
70000ada:	e78f      	b.n	700009fc <__aeabi_fmul+0x18>
70000adc:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000ae0:	ea92 0f0c 	teq	r2, ip
70000ae4:	bf18      	it	ne
70000ae6:	ea93 0f0c 	teqne	r3, ip
70000aea:	d00a      	beq.n	70000b02 <__aeabi_fmul+0x11e>
70000aec:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000af0:	bf18      	it	ne
70000af2:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000af6:	d1d8      	bne.n	70000aaa <__aeabi_fmul+0xc6>
70000af8:	ea80 0001 	eor.w	r0, r0, r1
70000afc:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000b00:	4770      	bx	lr
70000b02:	f090 0f00 	teq	r0, #0
70000b06:	bf17      	itett	ne
70000b08:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000b0c:	4608      	moveq	r0, r1
70000b0e:	f091 0f00 	teqne	r1, #0
70000b12:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000b16:	d014      	beq.n	70000b42 <__aeabi_fmul+0x15e>
70000b18:	ea92 0f0c 	teq	r2, ip
70000b1c:	d101      	bne.n	70000b22 <__aeabi_fmul+0x13e>
70000b1e:	0242      	lsls	r2, r0, #9
70000b20:	d10f      	bne.n	70000b42 <__aeabi_fmul+0x15e>
70000b22:	ea93 0f0c 	teq	r3, ip
70000b26:	d103      	bne.n	70000b30 <__aeabi_fmul+0x14c>
70000b28:	024b      	lsls	r3, r1, #9
70000b2a:	bf18      	it	ne
70000b2c:	4608      	movne	r0, r1
70000b2e:	d108      	bne.n	70000b42 <__aeabi_fmul+0x15e>
70000b30:	ea80 0001 	eor.w	r0, r0, r1
70000b34:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000b38:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000b3c:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000b40:	4770      	bx	lr
70000b42:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000b46:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000b4a:	4770      	bx	lr

70000b4c <__aeabi_fdiv>:
70000b4c:	f04f 0cff 	mov.w	ip, #255	; 0xff
70000b50:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70000b54:	bf1e      	ittt	ne
70000b56:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000b5a:	ea92 0f0c 	teqne	r2, ip
70000b5e:	ea93 0f0c 	teqne	r3, ip
70000b62:	d069      	beq.n	70000c38 <__aeabi_fdiv+0xec>
70000b64:	eba2 0203 	sub.w	r2, r2, r3
70000b68:	ea80 0c01 	eor.w	ip, r0, r1
70000b6c:	0249      	lsls	r1, r1, #9
70000b6e:	ea4f 2040 	mov.w	r0, r0, lsl #9
70000b72:	d037      	beq.n	70000be4 <__aeabi_fdiv+0x98>
70000b74:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70000b78:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70000b7c:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
70000b80:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000b84:	428b      	cmp	r3, r1
70000b86:	bf38      	it	cc
70000b88:	005b      	lslcc	r3, r3, #1
70000b8a:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
70000b8e:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
70000b92:	428b      	cmp	r3, r1
70000b94:	bf24      	itt	cs
70000b96:	1a5b      	subcs	r3, r3, r1
70000b98:	ea40 000c 	orrcs.w	r0, r0, ip
70000b9c:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
70000ba0:	bf24      	itt	cs
70000ba2:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
70000ba6:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70000baa:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
70000bae:	bf24      	itt	cs
70000bb0:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
70000bb4:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
70000bb8:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
70000bbc:	bf24      	itt	cs
70000bbe:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
70000bc2:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
70000bc6:	011b      	lsls	r3, r3, #4
70000bc8:	bf18      	it	ne
70000bca:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
70000bce:	d1e0      	bne.n	70000b92 <__aeabi_fdiv+0x46>
70000bd0:	2afd      	cmp	r2, #253	; 0xfd
70000bd2:	f63f af50 	bhi.w	70000a76 <__aeabi_fmul+0x92>
70000bd6:	428b      	cmp	r3, r1
70000bd8:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000bdc:	bf08      	it	eq
70000bde:	f020 0001 	biceq.w	r0, r0, #1
70000be2:	4770      	bx	lr
70000be4:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000be8:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70000bec:	327f      	adds	r2, #127	; 0x7f
70000bee:	bfc2      	ittt	gt
70000bf0:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000bf4:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70000bf8:	4770      	bxgt	lr
70000bfa:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000bfe:	f04f 0300 	mov.w	r3, #0
70000c02:	3a01      	subs	r2, #1
70000c04:	e737      	b.n	70000a76 <__aeabi_fmul+0x92>
70000c06:	f092 0f00 	teq	r2, #0
70000c0a:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
70000c0e:	bf02      	ittt	eq
70000c10:	0040      	lsleq	r0, r0, #1
70000c12:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70000c16:	3a01      	subeq	r2, #1
70000c18:	d0f9      	beq.n	70000c0e <__aeabi_fdiv+0xc2>
70000c1a:	ea40 000c 	orr.w	r0, r0, ip
70000c1e:	f093 0f00 	teq	r3, #0
70000c22:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000c26:	bf02      	ittt	eq
70000c28:	0049      	lsleq	r1, r1, #1
70000c2a:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
70000c2e:	3b01      	subeq	r3, #1
70000c30:	d0f9      	beq.n	70000c26 <__aeabi_fdiv+0xda>
70000c32:	ea41 010c 	orr.w	r1, r1, ip
70000c36:	e795      	b.n	70000b64 <__aeabi_fdiv+0x18>
70000c38:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70000c3c:	ea92 0f0c 	teq	r2, ip
70000c40:	d108      	bne.n	70000c54 <__aeabi_fdiv+0x108>
70000c42:	0242      	lsls	r2, r0, #9
70000c44:	f47f af7d 	bne.w	70000b42 <__aeabi_fmul+0x15e>
70000c48:	ea93 0f0c 	teq	r3, ip
70000c4c:	f47f af70 	bne.w	70000b30 <__aeabi_fmul+0x14c>
70000c50:	4608      	mov	r0, r1
70000c52:	e776      	b.n	70000b42 <__aeabi_fmul+0x15e>
70000c54:	ea93 0f0c 	teq	r3, ip
70000c58:	d104      	bne.n	70000c64 <__aeabi_fdiv+0x118>
70000c5a:	024b      	lsls	r3, r1, #9
70000c5c:	f43f af4c 	beq.w	70000af8 <__aeabi_fmul+0x114>
70000c60:	4608      	mov	r0, r1
70000c62:	e76e      	b.n	70000b42 <__aeabi_fmul+0x15e>
70000c64:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000c68:	bf18      	it	ne
70000c6a:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000c6e:	d1ca      	bne.n	70000c06 <__aeabi_fdiv+0xba>
70000c70:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70000c74:	f47f af5c 	bne.w	70000b30 <__aeabi_fmul+0x14c>
70000c78:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70000c7c:	f47f af3c 	bne.w	70000af8 <__aeabi_fmul+0x114>
70000c80:	e75f      	b.n	70000b42 <__aeabi_fmul+0x15e>
70000c82:	bf00      	nop

70000c84 <__gesf2>:
70000c84:	f04f 3cff 	mov.w	ip, #4294967295
70000c88:	e006      	b.n	70000c98 <__cmpsf2+0x4>
70000c8a:	bf00      	nop

70000c8c <__lesf2>:
70000c8c:	f04f 0c01 	mov.w	ip, #1
70000c90:	e002      	b.n	70000c98 <__cmpsf2+0x4>
70000c92:	bf00      	nop

70000c94 <__cmpsf2>:
70000c94:	f04f 0c01 	mov.w	ip, #1
70000c98:	f84d cd04 	str.w	ip, [sp, #-4]!
70000c9c:	ea4f 0240 	mov.w	r2, r0, lsl #1
70000ca0:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000ca4:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000ca8:	bf18      	it	ne
70000caa:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000cae:	d011      	beq.n	70000cd4 <__cmpsf2+0x40>
70000cb0:	b001      	add	sp, #4
70000cb2:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
70000cb6:	bf18      	it	ne
70000cb8:	ea90 0f01 	teqne	r0, r1
70000cbc:	bf58      	it	pl
70000cbe:	ebb2 0003 	subspl.w	r0, r2, r3
70000cc2:	bf88      	it	hi
70000cc4:	17c8      	asrhi	r0, r1, #31
70000cc6:	bf38      	it	cc
70000cc8:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70000ccc:	bf18      	it	ne
70000cce:	f040 0001 	orrne.w	r0, r0, #1
70000cd2:	4770      	bx	lr
70000cd4:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000cd8:	d102      	bne.n	70000ce0 <__cmpsf2+0x4c>
70000cda:	ea5f 2c40 	movs.w	ip, r0, lsl #9
70000cde:	d105      	bne.n	70000cec <__cmpsf2+0x58>
70000ce0:	ea7f 6c23 	mvns.w	ip, r3, asr #24
70000ce4:	d1e4      	bne.n	70000cb0 <__cmpsf2+0x1c>
70000ce6:	ea5f 2c41 	movs.w	ip, r1, lsl #9
70000cea:	d0e1      	beq.n	70000cb0 <__cmpsf2+0x1c>
70000cec:	f85d 0b04 	ldr.w	r0, [sp], #4
70000cf0:	4770      	bx	lr
70000cf2:	bf00      	nop

70000cf4 <__aeabi_cfrcmple>:
70000cf4:	4684      	mov	ip, r0
70000cf6:	4608      	mov	r0, r1
70000cf8:	4661      	mov	r1, ip
70000cfa:	e7ff      	b.n	70000cfc <__aeabi_cfcmpeq>

70000cfc <__aeabi_cfcmpeq>:
70000cfc:	b50f      	push	{r0, r1, r2, r3, lr}
70000cfe:	f7ff ffc9 	bl	70000c94 <__cmpsf2>
70000d02:	2800      	cmp	r0, #0
70000d04:	bf48      	it	mi
70000d06:	f110 0f00 	cmnmi.w	r0, #0
70000d0a:	bd0f      	pop	{r0, r1, r2, r3, pc}

70000d0c <__aeabi_fcmpeq>:
70000d0c:	f84d ed08 	str.w	lr, [sp, #-8]!
70000d10:	f7ff fff4 	bl	70000cfc <__aeabi_cfcmpeq>
70000d14:	bf0c      	ite	eq
70000d16:	2001      	moveq	r0, #1
70000d18:	2000      	movne	r0, #0
70000d1a:	f85d fb08 	ldr.w	pc, [sp], #8
70000d1e:	bf00      	nop

70000d20 <__aeabi_fcmplt>:
70000d20:	f84d ed08 	str.w	lr, [sp, #-8]!
70000d24:	f7ff ffea 	bl	70000cfc <__aeabi_cfcmpeq>
70000d28:	bf34      	ite	cc
70000d2a:	2001      	movcc	r0, #1
70000d2c:	2000      	movcs	r0, #0
70000d2e:	f85d fb08 	ldr.w	pc, [sp], #8
70000d32:	bf00      	nop

70000d34 <__aeabi_fcmple>:
70000d34:	f84d ed08 	str.w	lr, [sp, #-8]!
70000d38:	f7ff ffe0 	bl	70000cfc <__aeabi_cfcmpeq>
70000d3c:	bf94      	ite	ls
70000d3e:	2001      	movls	r0, #1
70000d40:	2000      	movhi	r0, #0
70000d42:	f85d fb08 	ldr.w	pc, [sp], #8
70000d46:	bf00      	nop

70000d48 <__aeabi_fcmpge>:
70000d48:	f84d ed08 	str.w	lr, [sp, #-8]!
70000d4c:	f7ff ffd2 	bl	70000cf4 <__aeabi_cfrcmple>
70000d50:	bf94      	ite	ls
70000d52:	2001      	movls	r0, #1
70000d54:	2000      	movhi	r0, #0
70000d56:	f85d fb08 	ldr.w	pc, [sp], #8
70000d5a:	bf00      	nop

70000d5c <__aeabi_fcmpgt>:
70000d5c:	f84d ed08 	str.w	lr, [sp, #-8]!
70000d60:	f7ff ffc8 	bl	70000cf4 <__aeabi_cfrcmple>
70000d64:	bf34      	ite	cc
70000d66:	2001      	movcc	r0, #1
70000d68:	2000      	movcs	r0, #0
70000d6a:	f85d fb08 	ldr.w	pc, [sp], #8
70000d6e:	bf00      	nop

70000d70 <__aeabi_f2uiz>:
70000d70:	0042      	lsls	r2, r0, #1
70000d72:	d20e      	bcs.n	70000d92 <__aeabi_f2uiz+0x22>
70000d74:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70000d78:	d30b      	bcc.n	70000d92 <__aeabi_f2uiz+0x22>
70000d7a:	f04f 039e 	mov.w	r3, #158	; 0x9e
70000d7e:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
70000d82:	d409      	bmi.n	70000d98 <__aeabi_f2uiz+0x28>
70000d84:	ea4f 2300 	mov.w	r3, r0, lsl #8
70000d88:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000d8c:	fa23 f002 	lsr.w	r0, r3, r2
70000d90:	4770      	bx	lr
70000d92:	f04f 0000 	mov.w	r0, #0
70000d96:	4770      	bx	lr
70000d98:	f112 0f61 	cmn.w	r2, #97	; 0x61
70000d9c:	d101      	bne.n	70000da2 <__aeabi_f2uiz+0x32>
70000d9e:	0242      	lsls	r2, r0, #9
70000da0:	d102      	bne.n	70000da8 <__aeabi_f2uiz+0x38>
70000da2:	f04f 30ff 	mov.w	r0, #4294967295
70000da6:	4770      	bx	lr
70000da8:	f04f 0000 	mov.w	r0, #0
70000dac:	4770      	bx	lr
70000dae:	bf00      	nop
