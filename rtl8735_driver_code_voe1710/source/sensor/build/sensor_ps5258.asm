
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	05 06 00 70 cd 00 00 70                             ...p...p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

7000006c <g_ps5258_i2c_init_regs_asic>:
7000006c:	0b 01 07 00 78 01 b0 00 79 01 7a 00 0a 02 35 00     ....x...y.z...5.
7000007c:	0d 02 01 00 2d 02 01 00 1c 02 00 00 3c 02 37 00     ....-.......<.7.
7000008c:	40 02 15 00 54 02 61 00 59 06 5e 00 84 06 00 00     @...T.a.Y.^.....
7000009c:	85 06 02 00 9a 06 00 00 ac 06 04 00 02 0b 02 00     ................
700000ac:	0c 0b 00 00 b0 14 01 00 0f 14 01 00 11 01 01 00     ................
700000bc:	0f 01 01 00                                         ....

700000c0 <real_slave_addr>:
700000c0:	48 00 00 00                                         H...

700000c4 <slave_addr_list>:
700000c4:	48 00 00 00 4c 00 00 00                             H...L...

700000cc <rts_isp_set_voe_ops>:
700000cc:	4b01      	ldr	r3, [pc, #4]	; (700000d4 <rts_isp_set_voe_ops+0x8>)
700000ce:	6018      	str	r0, [r3, #0]
700000d0:	4770      	bx	lr
700000d2:	bf00      	nop
700000d4:	70000048 	.word	0x70000048

700000d8 <isp_driver_is_fpga>:
700000d8:	2000      	movs	r0, #0
700000da:	4770      	bx	lr

700000dc <ps5258_get_info>:
700000dc:	b510      	push	{r4, lr}
700000de:	2800      	cmp	r0, #0
700000e0:	d13e      	bne.n	70000160 <ps5258_get_info+0x84>
700000e2:	2900      	cmp	r1, #0
700000e4:	d03c      	beq.n	70000160 <ps5258_get_info+0x84>
700000e6:	4b20      	ldr	r3, [pc, #128]	; (70000168 <ps5258_get_info+0x8c>)
700000e8:	f44f 62f0 	mov.w	r2, #1920	; 0x780
700000ec:	4c1f      	ldr	r4, [pc, #124]	; (7000016c <ps5258_get_info+0x90>)
700000ee:	610b      	str	r3, [r1, #16]
700000f0:	f44f 6387 	mov.w	r3, #1080	; 0x438
700000f4:	7108      	strb	r0, [r1, #4]
700000f6:	f881 00a4 	strb.w	r0, [r1, #164]	; 0xa4
700000fa:	f8c1 00a8 	str.w	r0, [r1, #168]	; 0xa8
700000fe:	f881 00b0 	strb.w	r0, [r1, #176]	; 0xb0
70000102:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
70000106:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
7000010a:	e9c1 2302 	strd	r2, r3, [r1, #8]
7000010e:	4a18      	ldr	r2, [pc, #96]	; (70000170 <ps5258_get_info+0x94>)
70000110:	2301      	movs	r3, #1
70000112:	6812      	ldr	r2, [r2, #0]
70000114:	600b      	str	r3, [r1, #0]
70000116:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
7000011a:	4a16      	ldr	r2, [pc, #88]	; (70000174 <ps5258_get_info+0x98>)
7000011c:	f8c1 30b4 	str.w	r3, [r1, #180]	; 0xb4
70000120:	7812      	ldrb	r2, [r2, #0]
70000122:	f8c1 32d4 	str.w	r3, [r1, #724]	; 0x2d4
70000126:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
7000012a:	2203      	movs	r2, #3
7000012c:	f881 2098 	strb.w	r2, [r1, #152]	; 0x98
70000130:	f241 3288 	movw	r2, #5000	; 0x1388
70000134:	e9c1 4227 	strd	r4, r2, [r1, #156]	; 0x9c
70000138:	f241 7470 	movw	r4, #6000	; 0x1770
7000013c:	f44f 727a 	mov.w	r2, #1000	; 0x3e8
70000140:	f8c1 40b8 	str.w	r4, [r1, #184]	; 0xb8
70000144:	f44f 7481 	mov.w	r4, #258	; 0x102
70000148:	f8c1 20ac 	str.w	r2, [r1, #172]	; 0xac
7000014c:	f8a1 4086 	strh.w	r4, [r1, #134]	; 0x86
70000150:	2404      	movs	r4, #4
70000152:	e9c1 3324 	strd	r3, r3, [r1, #144]	; 0x90
70000156:	f8c1 4088 	str.w	r4, [r1, #136]	; 0x88
7000015a:	e9c1 02b7 	strd	r0, r2, [r1, #732]	; 0x2dc
7000015e:	bd10      	pop	{r4, pc}
70000160:	f06f 0015 	mvn.w	r0, #21
70000164:	e7fb      	b.n	7000015e <ps5258_get_info+0x82>
70000166:	bf00      	nop
70000168:	41f00000 	.word	0x41f00000
7000016c:	019bfcc0 	.word	0x019bfcc0
70000170:	700000c0 	.word	0x700000c0
70000174:	7000004c 	.word	0x7000004c

70000178 <ps5258_get_init_info>:
70000178:	b570      	push	{r4, r5, r6, lr}
7000017a:	460b      	mov	r3, r1
7000017c:	4614      	mov	r4, r2
7000017e:	4605      	mov	r5, r0
70000180:	b110      	cbz	r0, 70000188 <ps5258_get_init_info+0x10>
70000182:	f06f 0015 	mvn.w	r0, #21
70000186:	bd70      	pop	{r4, r5, r6, pc}
70000188:	2a00      	cmp	r2, #0
7000018a:	d0fa      	beq.n	70000182 <ps5258_get_init_info+0xa>
7000018c:	780a      	ldrb	r2, [r1, #0]
7000018e:	4e1b      	ldr	r6, [pc, #108]	; (700001fc <ps5258_get_init_info+0x84>)
70000190:	491b      	ldr	r1, [pc, #108]	; (70000200 <ps5258_get_init_info+0x88>)
70000192:	68d8      	ldr	r0, [r3, #12]
70000194:	7032      	strb	r2, [r6, #0]
70000196:	f001 f92f 	bl	700013f8 <__aeabi_fcmpeq>
7000019a:	2800      	cmp	r0, #0
7000019c:	d0f1      	beq.n	70000182 <ps5258_get_init_info+0xa>
7000019e:	4b19      	ldr	r3, [pc, #100]	; (70000204 <ps5258_get_init_info+0x8c>)
700001a0:	f44f 62f1 	mov.w	r2, #1928	; 0x788
700001a4:	f640 0098 	movw	r0, #2200	; 0x898
700001a8:	60a5      	str	r5, [r4, #8]
700001aa:	6063      	str	r3, [r4, #4]
700001ac:	2315      	movs	r3, #21
700001ae:	f8c4 5088 	str.w	r5, [r4, #136]	; 0x88
700001b2:	6023      	str	r3, [r4, #0]
700001b4:	2302      	movs	r3, #2
700001b6:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
700001ba:	f240 4303 	movw	r3, #1027	; 0x403
700001be:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
700001c2:	230a      	movs	r3, #10
700001c4:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
700001c8:	2304      	movs	r3, #4
700001ca:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
700001ce:	f44f 6388 	mov.w	r3, #1088	; 0x440
700001d2:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
700001d6:	2301      	movs	r3, #1
700001d8:	f8c4 308c 	str.w	r3, [r4, #140]	; 0x8c
700001dc:	4b0a      	ldr	r3, [pc, #40]	; (70000208 <ps5258_get_init_info+0x90>)
700001de:	e9c4 3024 	strd	r3, r0, [r4, #144]	; 0x90
700001e2:	f240 4365 	movw	r3, #1125	; 0x465
700001e6:	4628      	mov	r0, r5
700001e8:	6073      	str	r3, [r6, #4]
700001ea:	f8c4 3098 	str.w	r3, [r4, #152]	; 0x98
700001ee:	f244 13eb 	movw	r3, #16875	; 0x41eb
700001f2:	f8c4 309c 	str.w	r3, [r4, #156]	; 0x9c
700001f6:	4b05      	ldr	r3, [pc, #20]	; (7000020c <ps5258_get_init_info+0x94>)
700001f8:	60b3      	str	r3, [r6, #8]
700001fa:	e7c4      	b.n	70000186 <ps5258_get_init_info+0xe>
700001fc:	7000004c 	.word	0x7000004c
70000200:	41f00000 	.word	0x41f00000
70000204:	7000006c 	.word	0x7000006c
70000208:	046cf710 	.word	0x046cf710
7000020c:	41ed097b 	.word	0x41ed097b

70000210 <ps5258_start>:
70000210:	b918      	cbnz	r0, 7000021a <ps5258_start+0xa>
70000212:	4b03      	ldr	r3, [pc, #12]	; (70000220 <ps5258_start+0x10>)
70000214:	2200      	movs	r2, #0
70000216:	60da      	str	r2, [r3, #12]
70000218:	4770      	bx	lr
7000021a:	f06f 0015 	mvn.w	r0, #21
7000021e:	4770      	bx	lr
70000220:	7000004c 	.word	0x7000004c

70000224 <ps5258_get_tuned_dgain>:
70000224:	b920      	cbnz	r0, 70000230 <ps5258_get_tuned_dgain+0xc>
70000226:	b119      	cbz	r1, 70000230 <ps5258_get_tuned_dgain+0xc>
70000228:	f04f 537e 	mov.w	r3, #1065353216	; 0x3f800000
7000022c:	600b      	str	r3, [r1, #0]
7000022e:	4770      	bx	lr
70000230:	f06f 0015 	mvn.w	r0, #21
70000234:	4770      	bx	lr
	...

70000238 <ps5258_get_exposure_gain_info>:
70000238:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
7000023c:	4614      	mov	r4, r2
7000023e:	2800      	cmp	r0, #0
70000240:	d15d      	bne.n	700002fe <ps5258_get_exposure_gain_info+0xc6>
70000242:	2900      	cmp	r1, #0
70000244:	d05b      	beq.n	700002fe <ps5258_get_exposure_gain_info+0xc6>
70000246:	2a00      	cmp	r2, #0
70000248:	d059      	beq.n	700002fe <ps5258_get_exposure_gain_info+0xc6>
7000024a:	698b      	ldr	r3, [r1, #24]
7000024c:	1d16      	adds	r6, r2, #4
7000024e:	f44f 728b 	mov.w	r2, #278	; 0x116
70000252:	f8d1 8000 	ldr.w	r8, [r1]
70000256:	b29d      	uxth	r5, r3
70000258:	4f2a      	ldr	r7, [pc, #168]	; (70000304 <ps5258_get_exposure_gain_info+0xcc>)
7000025a:	81a2      	strh	r2, [r4, #12]
7000025c:	0a1a      	lsrs	r2, r3, #8
7000025e:	b2db      	uxtb	r3, r3
70000260:	4641      	mov	r1, r8
70000262:	81e2      	strh	r2, [r4, #14]
70000264:	f240 1217 	movw	r2, #279	; 0x117
70000268:	68f8      	ldr	r0, [r7, #12]
7000026a:	8422      	strh	r2, [r4, #32]
7000026c:	8463      	strh	r3, [r4, #34]	; 0x22
7000026e:	f000 fe25 	bl	70000ebc <__aeabi_fsub>
70000272:	2100      	movs	r1, #0
70000274:	4681      	mov	r9, r0
70000276:	f001 f8dd 	bl	70001434 <__aeabi_fcmpge>
7000027a:	2800      	cmp	r0, #0
7000027c:	d038      	beq.n	700002f0 <ps5258_get_exposure_gain_info+0xb8>
7000027e:	4922      	ldr	r1, [pc, #136]	; (70000308 <ps5258_get_exposure_gain_info+0xd0>)
70000280:	4648      	mov	r0, r9
70000282:	f001 f8e1 	bl	70001448 <__aeabi_fcmpgt>
70000286:	2800      	cmp	r0, #0
70000288:	d037      	beq.n	700002fa <ps5258_get_exposure_gain_info+0xc2>
7000028a:	68b9      	ldr	r1, [r7, #8]
7000028c:	4640      	mov	r0, r8
7000028e:	f000 ffd3 	bl	70001238 <__aeabi_fdiv>
70000292:	f04f 517c 	mov.w	r1, #1056964608	; 0x3f000000
70000296:	f000 fe13 	bl	70000ec0 <__addsf3>
7000029a:	f001 f8df 	bl	7000145c <__aeabi_f2uiz>
7000029e:	1e6b      	subs	r3, r5, #1
700002a0:	b280      	uxth	r0, r0
700002a2:	b29b      	uxth	r3, r3
700002a4:	4283      	cmp	r3, r0
700002a6:	d303      	bcc.n	700002b0 <ps5258_get_exposure_gain_info+0x78>
700002a8:	2802      	cmp	r0, #2
700002aa:	4603      	mov	r3, r0
700002ac:	bf38      	it	cc
700002ae:	2302      	movcc	r3, #2
700002b0:	1aed      	subs	r5, r5, r3
700002b2:	f44f 738c 	mov.w	r3, #280	; 0x118
700002b6:	f8c7 800c 	str.w	r8, [r7, #12]
700002ba:	86a3      	strh	r3, [r4, #52]	; 0x34
700002bc:	f3c5 2307 	ubfx	r3, r5, #8, #8
700002c0:	b2ed      	uxtb	r5, r5
700002c2:	86e3      	strh	r3, [r4, #54]	; 0x36
700002c4:	f240 1319 	movw	r3, #281	; 0x119
700002c8:	f8a4 504a 	strh.w	r5, [r4, #74]	; 0x4a
700002cc:	f8a4 3048 	strh.w	r3, [r4, #72]	; 0x48
700002d0:	2304      	movs	r3, #4
700002d2:	2214      	movs	r2, #20
700002d4:	8a39      	ldrh	r1, [r7, #16]
700002d6:	f240 102b 	movw	r0, #299	; 0x12b
700002da:	fb02 6203 	mla	r2, r2, r3, r6
700002de:	3302      	adds	r3, #2
700002e0:	8110      	strh	r0, [r2, #8]
700002e2:	2000      	movs	r0, #0
700002e4:	8151      	strh	r1, [r2, #10]
700002e6:	4909      	ldr	r1, [pc, #36]	; (7000030c <ps5258_get_exposure_gain_info+0xd4>)
700002e8:	61d1      	str	r1, [r2, #28]
700002ea:	6023      	str	r3, [r4, #0]
700002ec:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
700002f0:	4907      	ldr	r1, [pc, #28]	; (70000310 <ps5258_get_exposure_gain_info+0xd8>)
700002f2:	4648      	mov	r0, r9
700002f4:	f001 f88a 	bl	7000140c <__aeabi_fcmplt>
700002f8:	e7c5      	b.n	70000286 <ps5258_get_exposure_gain_info+0x4e>
700002fa:	2302      	movs	r3, #2
700002fc:	e7e9      	b.n	700002d2 <ps5258_get_exposure_gain_info+0x9a>
700002fe:	f06f 0015 	mvn.w	r0, #21
70000302:	e7f3      	b.n	700002ec <ps5258_get_exposure_gain_info+0xb4>
70000304:	7000004c 	.word	0x7000004c
70000308:	3a83126f 	.word	0x3a83126f
7000030c:	00010111 	.word	0x00010111
70000310:	ba83126f 	.word	0xba83126f

70000314 <ps5258_set_mirror_flip>:
70000314:	784b      	ldrb	r3, [r1, #1]
70000316:	780a      	ldrb	r2, [r1, #0]
70000318:	2b00      	cmp	r3, #0
7000031a:	bf14      	ite	ne
7000031c:	2302      	movne	r3, #2
7000031e:	2300      	moveq	r3, #0
70000320:	2a00      	cmp	r2, #0
70000322:	bf18      	it	ne
70000324:	f043 0301 	orrne.w	r3, r3, #1
70000328:	2201      	movs	r2, #1
7000032a:	2b02      	cmp	r3, #2
7000032c:	708a      	strb	r2, [r1, #2]
7000032e:	d014      	beq.n	7000035a <ps5258_set_mirror_flip+0x46>
70000330:	2b03      	cmp	r3, #3
70000332:	d01b      	beq.n	7000036c <ps5258_set_mirror_flip+0x58>
70000334:	4293      	cmp	r3, r2
70000336:	f44f 73a0 	mov.w	r3, #320	; 0x140
7000033a:	610b      	str	r3, [r1, #16]
7000033c:	d010      	beq.n	70000360 <ps5258_set_mirror_flip+0x4c>
7000033e:	f240 1341 	movw	r3, #321	; 0x141
70000342:	624b      	str	r3, [r1, #36]	; 0x24
70000344:	f240 1349 	movw	r3, #329	; 0x149
70000348:	638b      	str	r3, [r1, #56]	; 0x38
7000034a:	4b0a      	ldr	r3, [pc, #40]	; (70000374 <ps5258_set_mirror_flip+0x60>)
7000034c:	64cb      	str	r3, [r1, #76]	; 0x4c
7000034e:	2000      	movs	r0, #0
70000350:	4b09      	ldr	r3, [pc, #36]	; (70000378 <ps5258_set_mirror_flip+0x64>)
70000352:	660b      	str	r3, [r1, #96]	; 0x60
70000354:	2305      	movs	r3, #5
70000356:	604b      	str	r3, [r1, #4]
70000358:	4770      	bx	lr
7000035a:	4b08      	ldr	r3, [pc, #32]	; (7000037c <ps5258_set_mirror_flip+0x68>)
7000035c:	610b      	str	r3, [r1, #16]
7000035e:	e7ee      	b.n	7000033e <ps5258_set_mirror_flip+0x2a>
70000360:	4b07      	ldr	r3, [pc, #28]	; (70000380 <ps5258_set_mirror_flip+0x6c>)
70000362:	624b      	str	r3, [r1, #36]	; 0x24
70000364:	4b07      	ldr	r3, [pc, #28]	; (70000384 <ps5258_set_mirror_flip+0x70>)
70000366:	638b      	str	r3, [r1, #56]	; 0x38
70000368:	4b07      	ldr	r3, [pc, #28]	; (70000388 <ps5258_set_mirror_flip+0x74>)
7000036a:	e7ef      	b.n	7000034c <ps5258_set_mirror_flip+0x38>
7000036c:	4b03      	ldr	r3, [pc, #12]	; (7000037c <ps5258_set_mirror_flip+0x68>)
7000036e:	610b      	str	r3, [r1, #16]
70000370:	3301      	adds	r3, #1
70000372:	e7f6      	b.n	70000362 <ps5258_set_mirror_flip+0x4e>
70000374:	0002014a 	.word	0x0002014a
70000378:	00010111 	.word	0x00010111
7000037c:	00010140 	.word	0x00010140
70000380:	00010141 	.word	0x00010141
70000384:	00040149 	.word	0x00040149
70000388:	0044014a 	.word	0x0044014a

7000038c <ps5258_check>:
7000038c:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
7000038e:	4d1e      	ldr	r5, [pc, #120]	; (70000408 <ps5258_check+0x7c>)
70000390:	4606      	mov	r6, r0
70000392:	682b      	ldr	r3, [r5, #0]
70000394:	6c1b      	ldr	r3, [r3, #64]	; 0x40
70000396:	4798      	blx	r3
70000398:	2801      	cmp	r0, #1
7000039a:	dc31      	bgt.n	70000400 <ps5258_check+0x74>
7000039c:	4b1b      	ldr	r3, [pc, #108]	; (7000040c <ps5258_check+0x80>)
7000039e:	f853 2020 	ldr.w	r2, [r3, r0, lsl #2]
700003a2:	4b1b      	ldr	r3, [pc, #108]	; (70000410 <ps5258_check+0x84>)
700003a4:	601a      	str	r2, [r3, #0]
700003a6:	682b      	ldr	r3, [r5, #0]
700003a8:	685b      	ldr	r3, [r3, #4]
700003aa:	4798      	blx	r3
700003ac:	f44f 7380 	mov.w	r3, #256	; 0x100
700003b0:	a901      	add	r1, sp, #4
700003b2:	4630      	mov	r0, r6
700003b4:	f8ad 3004 	strh.w	r3, [sp, #4]
700003b8:	682b      	ldr	r3, [r5, #0]
700003ba:	68db      	ldr	r3, [r3, #12]
700003bc:	4798      	blx	r3
700003be:	4604      	mov	r4, r0
700003c0:	b128      	cbz	r0, 700003ce <ps5258_check+0x42>
700003c2:	682b      	ldr	r3, [r5, #0]
700003c4:	689b      	ldr	r3, [r3, #8]
700003c6:	4798      	blx	r3
700003c8:	4620      	mov	r0, r4
700003ca:	b003      	add	sp, #12
700003cc:	bdf0      	pop	{r4, r5, r6, r7, pc}
700003ce:	f240 1301 	movw	r3, #257	; 0x101
700003d2:	a901      	add	r1, sp, #4
700003d4:	4630      	mov	r0, r6
700003d6:	f8bd 7006 	ldrh.w	r7, [sp, #6]
700003da:	f8ad 3004 	strh.w	r3, [sp, #4]
700003de:	682b      	ldr	r3, [r5, #0]
700003e0:	68db      	ldr	r3, [r3, #12]
700003e2:	4798      	blx	r3
700003e4:	682b      	ldr	r3, [r5, #0]
700003e6:	4604      	mov	r4, r0
700003e8:	689b      	ldr	r3, [r3, #8]
700003ea:	4798      	blx	r3
700003ec:	2c00      	cmp	r4, #0
700003ee:	d1eb      	bne.n	700003c8 <ps5258_check+0x3c>
700003f0:	f8bd 3006 	ldrh.w	r3, [sp, #6]
700003f4:	f245 2258 	movw	r2, #21080	; 0x5258
700003f8:	ea43 2307 	orr.w	r3, r3, r7, lsl #8
700003fc:	4293      	cmp	r3, r2
700003fe:	d0e3      	beq.n	700003c8 <ps5258_check+0x3c>
70000400:	f06f 0415 	mvn.w	r4, #21
70000404:	e7e0      	b.n	700003c8 <ps5258_check+0x3c>
70000406:	bf00      	nop
70000408:	70000048 	.word	0x70000048
7000040c:	700000c4 	.word	0x700000c4
70000410:	700000c0 	.word	0x700000c0

70000414 <ps5258_get_slave_addr_num>:
70000414:	2002      	movs	r0, #2
70000416:	4770      	bx	lr

70000418 <ps5258_get_tuned_again>:
70000418:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
7000041a:	460f      	mov	r7, r1
7000041c:	2400      	movs	r4, #0
7000041e:	2800      	cmp	r0, #0
70000420:	f040 80ca 	bne.w	700005b8 <ps5258_get_tuned_again+0x1a0>
70000424:	2900      	cmp	r1, #0
70000426:	f000 80c7 	beq.w	700005b8 <ps5258_get_tuned_again+0x1a0>
7000042a:	680d      	ldr	r5, [r1, #0]
7000042c:	f04f 517e 	mov.w	r1, #1065353216	; 0x3f800000
70000430:	4628      	mov	r0, r5
70000432:	f000 ffff 	bl	70001434 <__aeabi_fcmpge>
70000436:	b338      	cbz	r0, 70000488 <ps5258_get_tuned_again+0x70>
70000438:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
7000043c:	4628      	mov	r0, r5
7000043e:	f000 ffe5 	bl	7000140c <__aeabi_fcmplt>
70000442:	b308      	cbz	r0, 70000488 <ps5258_get_tuned_again+0x70>
70000444:	4628      	mov	r0, r5
70000446:	f000 fc6d 	bl	70000d24 <__aeabi_f2d>
7000044a:	2200      	movs	r2, #0
7000044c:	4b5c      	ldr	r3, [pc, #368]	; (700005c0 <ps5258_get_tuned_again+0x1a8>)
7000044e:	f000 fb09 	bl	70000a64 <__aeabi_dsub>
70000452:	2200      	movs	r2, #0
70000454:	4b5b      	ldr	r3, [pc, #364]	; (700005c4 <ps5258_get_tuned_again+0x1ac>)
70000456:	f000 f923 	bl	700006a0 <__aeabi_dmul>
7000045a:	f000 fcbb 	bl	70000dd4 <__aeabi_d2uiz>
7000045e:	b284      	uxth	r4, r0
70000460:	4b59      	ldr	r3, [pc, #356]	; (700005c8 <ps5258_get_tuned_again+0x1b0>)
70000462:	4620      	mov	r0, r4
70000464:	611c      	str	r4, [r3, #16]
70000466:	f000 fddb 	bl	70001020 <__aeabi_ui2f>
7000046a:	2c0f      	cmp	r4, #15
7000046c:	d875      	bhi.n	7000055a <ps5258_get_tuned_again+0x142>
7000046e:	f000 fc59 	bl	70000d24 <__aeabi_f2d>
70000472:	2200      	movs	r2, #0
70000474:	4b55      	ldr	r3, [pc, #340]	; (700005cc <ps5258_get_tuned_again+0x1b4>)
70000476:	f000 f913 	bl	700006a0 <__aeabi_dmul>
7000047a:	2200      	movs	r2, #0
7000047c:	4b50      	ldr	r3, [pc, #320]	; (700005c0 <ps5258_get_tuned_again+0x1a8>)
7000047e:	f000 faf3 	bl	70000a68 <__adddf3>
70000482:	f000 fcc7 	bl	70000e14 <__aeabi_d2f>
70000486:	e070      	b.n	7000056a <ps5258_get_tuned_again+0x152>
70000488:	f04f 4180 	mov.w	r1, #1073741824	; 0x40000000
7000048c:	4628      	mov	r0, r5
7000048e:	f000 ffd1 	bl	70001434 <__aeabi_fcmpge>
70000492:	b1b0      	cbz	r0, 700004c2 <ps5258_get_tuned_again+0xaa>
70000494:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
70000498:	4628      	mov	r0, r5
7000049a:	f000 ffb7 	bl	7000140c <__aeabi_fcmplt>
7000049e:	b180      	cbz	r0, 700004c2 <ps5258_get_tuned_again+0xaa>
700004a0:	4628      	mov	r0, r5
700004a2:	f000 fc3f 	bl	70000d24 <__aeabi_f2d>
700004a6:	2200      	movs	r2, #0
700004a8:	f04f 4380 	mov.w	r3, #1073741824	; 0x40000000
700004ac:	f000 fada 	bl	70000a64 <__aeabi_dsub>
700004b0:	2200      	movs	r2, #0
700004b2:	4b47      	ldr	r3, [pc, #284]	; (700005d0 <ps5258_get_tuned_again+0x1b8>)
700004b4:	f000 f8f4 	bl	700006a0 <__aeabi_dmul>
700004b8:	2200      	movs	r2, #0
700004ba:	4b42      	ldr	r3, [pc, #264]	; (700005c4 <ps5258_get_tuned_again+0x1ac>)
700004bc:	f000 fad4 	bl	70000a68 <__adddf3>
700004c0:	e7cb      	b.n	7000045a <ps5258_get_tuned_again+0x42>
700004c2:	f04f 4181 	mov.w	r1, #1082130432	; 0x40800000
700004c6:	4628      	mov	r0, r5
700004c8:	f000 ffb4 	bl	70001434 <__aeabi_fcmpge>
700004cc:	b198      	cbz	r0, 700004f6 <ps5258_get_tuned_again+0xde>
700004ce:	f04f 4182 	mov.w	r1, #1090519040	; 0x41000000
700004d2:	4628      	mov	r0, r5
700004d4:	f000 ff9a 	bl	7000140c <__aeabi_fcmplt>
700004d8:	b168      	cbz	r0, 700004f6 <ps5258_get_tuned_again+0xde>
700004da:	4628      	mov	r0, r5
700004dc:	f000 fc22 	bl	70000d24 <__aeabi_f2d>
700004e0:	2200      	movs	r2, #0
700004e2:	4b3c      	ldr	r3, [pc, #240]	; (700005d4 <ps5258_get_tuned_again+0x1bc>)
700004e4:	f000 fabe 	bl	70000a64 <__aeabi_dsub>
700004e8:	2200      	movs	r2, #0
700004ea:	4b3a      	ldr	r3, [pc, #232]	; (700005d4 <ps5258_get_tuned_again+0x1bc>)
700004ec:	f000 f8d8 	bl	700006a0 <__aeabi_dmul>
700004f0:	2200      	movs	r2, #0
700004f2:	4b39      	ldr	r3, [pc, #228]	; (700005d8 <ps5258_get_tuned_again+0x1c0>)
700004f4:	e7e2      	b.n	700004bc <ps5258_get_tuned_again+0xa4>
700004f6:	f04f 4182 	mov.w	r1, #1090519040	; 0x41000000
700004fa:	4628      	mov	r0, r5
700004fc:	f000 ff9a 	bl	70001434 <__aeabi_fcmpge>
70000500:	b198      	cbz	r0, 7000052a <ps5258_get_tuned_again+0x112>
70000502:	f04f 4183 	mov.w	r1, #1098907648	; 0x41800000
70000506:	4628      	mov	r0, r5
70000508:	f000 ff80 	bl	7000140c <__aeabi_fcmplt>
7000050c:	b168      	cbz	r0, 7000052a <ps5258_get_tuned_again+0x112>
7000050e:	4628      	mov	r0, r5
70000510:	f000 fc08 	bl	70000d24 <__aeabi_f2d>
70000514:	2200      	movs	r2, #0
70000516:	4b2e      	ldr	r3, [pc, #184]	; (700005d0 <ps5258_get_tuned_again+0x1b8>)
70000518:	f000 faa4 	bl	70000a64 <__aeabi_dsub>
7000051c:	4602      	mov	r2, r0
7000051e:	460b      	mov	r3, r1
70000520:	f000 faa2 	bl	70000a68 <__adddf3>
70000524:	2200      	movs	r2, #0
70000526:	4b2d      	ldr	r3, [pc, #180]	; (700005dc <ps5258_get_tuned_again+0x1c4>)
70000528:	e7c8      	b.n	700004bc <ps5258_get_tuned_again+0xa4>
7000052a:	f04f 4183 	mov.w	r1, #1098907648	; 0x41800000
7000052e:	4628      	mov	r0, r5
70000530:	f000 ff80 	bl	70001434 <__aeabi_fcmpge>
70000534:	2800      	cmp	r0, #0
70000536:	d093      	beq.n	70000460 <ps5258_get_tuned_again+0x48>
70000538:	f04f 4184 	mov.w	r1, #1107296256	; 0x42000000
7000053c:	4628      	mov	r0, r5
7000053e:	f000 ff6f 	bl	70001420 <__aeabi_fcmple>
70000542:	2800      	cmp	r0, #0
70000544:	d08c      	beq.n	70000460 <ps5258_get_tuned_again+0x48>
70000546:	4628      	mov	r0, r5
70000548:	f000 fbec 	bl	70000d24 <__aeabi_f2d>
7000054c:	2200      	movs	r2, #0
7000054e:	4b1d      	ldr	r3, [pc, #116]	; (700005c4 <ps5258_get_tuned_again+0x1ac>)
70000550:	f000 fa88 	bl	70000a64 <__aeabi_dsub>
70000554:	2200      	movs	r2, #0
70000556:	4b22      	ldr	r3, [pc, #136]	; (700005e0 <ps5258_get_tuned_again+0x1c8>)
70000558:	e7b0      	b.n	700004bc <ps5258_get_tuned_again+0xa4>
7000055a:	f1a4 0310 	sub.w	r3, r4, #16
7000055e:	2b0f      	cmp	r3, #15
70000560:	d807      	bhi.n	70000572 <ps5258_get_tuned_again+0x15a>
70000562:	f04f 5178 	mov.w	r1, #1040187392	; 0x3e000000
70000566:	f000 fdb3 	bl	700010d0 <__aeabi_fmul>
7000056a:	4606      	mov	r6, r0
7000056c:	2000      	movs	r0, #0
7000056e:	603e      	str	r6, [r7, #0]
70000570:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
70000572:	f1a4 0320 	sub.w	r3, r4, #32
70000576:	2b0f      	cmp	r3, #15
70000578:	d80a      	bhi.n	70000590 <ps5258_get_tuned_again+0x178>
7000057a:	f000 fbd3 	bl	70000d24 <__aeabi_f2d>
7000057e:	2200      	movs	r2, #0
70000580:	4b18      	ldr	r3, [pc, #96]	; (700005e4 <ps5258_get_tuned_again+0x1cc>)
70000582:	f000 f88d 	bl	700006a0 <__aeabi_dmul>
70000586:	2200      	movs	r2, #0
70000588:	4b12      	ldr	r3, [pc, #72]	; (700005d4 <ps5258_get_tuned_again+0x1bc>)
7000058a:	f000 fa6b 	bl	70000a64 <__aeabi_dsub>
7000058e:	e778      	b.n	70000482 <ps5258_get_tuned_again+0x6a>
70000590:	f1a4 0330 	sub.w	r3, r4, #48	; 0x30
70000594:	2b0f      	cmp	r3, #15
70000596:	d808      	bhi.n	700005aa <ps5258_get_tuned_again+0x192>
70000598:	f000 fbc4 	bl	70000d24 <__aeabi_f2d>
7000059c:	2200      	movs	r2, #0
7000059e:	4b12      	ldr	r3, [pc, #72]	; (700005e8 <ps5258_get_tuned_again+0x1d0>)
700005a0:	f000 f87e 	bl	700006a0 <__aeabi_dmul>
700005a4:	2200      	movs	r2, #0
700005a6:	4b07      	ldr	r3, [pc, #28]	; (700005c4 <ps5258_get_tuned_again+0x1ac>)
700005a8:	e7ef      	b.n	7000058a <ps5258_get_tuned_again+0x172>
700005aa:	3c40      	subs	r4, #64	; 0x40
700005ac:	2c10      	cmp	r4, #16
700005ae:	d8dd      	bhi.n	7000056c <ps5258_get_tuned_again+0x154>
700005b0:	490e      	ldr	r1, [pc, #56]	; (700005ec <ps5258_get_tuned_again+0x1d4>)
700005b2:	f000 fc83 	bl	70000ebc <__aeabi_fsub>
700005b6:	e7d8      	b.n	7000056a <ps5258_get_tuned_again+0x152>
700005b8:	f06f 0015 	mvn.w	r0, #21
700005bc:	e7d8      	b.n	70000570 <ps5258_get_tuned_again+0x158>
700005be:	bf00      	nop
700005c0:	3ff00000 	.word	0x3ff00000
700005c4:	40300000 	.word	0x40300000
700005c8:	7000004c 	.word	0x7000004c
700005cc:	3fb00000 	.word	0x3fb00000
700005d0:	40200000 	.word	0x40200000
700005d4:	40100000 	.word	0x40100000
700005d8:	40400000 	.word	0x40400000
700005dc:	40480000 	.word	0x40480000
700005e0:	40500000 	.word	0x40500000
700005e4:	3fd00000 	.word	0x3fd00000
700005e8:	3fe00000 	.word	0x3fe00000
700005ec:	42400000 	.word	0x42400000

700005f0 <clip_d_word>:
700005f0:	4603      	mov	r3, r0
700005f2:	4610      	mov	r0, r2
700005f4:	4293      	cmp	r3, r2
700005f6:	d803      	bhi.n	70000600 <clip_d_word+0x10>
700005f8:	428b      	cmp	r3, r1
700005fa:	bf38      	it	cc
700005fc:	460b      	movcc	r3, r1
700005fe:	4618      	mov	r0, r3
70000600:	4770      	bx	lr
	...

70000604 <rts_isp_get_sensor_ops>:
70000604:	4800      	ldr	r0, [pc, #0]	; (70000608 <rts_isp_get_sensor_ops+0x4>)
70000606:	4770      	bx	lr
70000608:	7000060c 	.word	0x7000060c

7000060c <ps5258_ops>:
7000060c:	73000005 32357370 00003835 00000000     ...sps5258......
	...
70000630:	700000dd 70000179 00000000 70000419     ...py..p.......p
70000640:	70000225 70000239 00000000 00000000     %..p9..p........
70000650:	70000211 00000000 00000000 00000000     ...p............
70000660:	70000315 00000000 00000000 00000000     ...p............
70000670:	7000038d 00000000 00000000 00000000     ...p............
70000680:	70000415 00000000 00000000 00000000     ...p............
	...

700006a0 <__aeabi_dmul>:
700006a0:	b570      	push	{r4, r5, r6, lr}
700006a2:	f04f 0cff 	mov.w	ip, #255	; 0xff
700006a6:	f44c 6ce0 	orr.w	ip, ip, #1792	; 0x700
700006aa:	ea1c 5411 	ands.w	r4, ip, r1, lsr #20
700006ae:	bf1d      	ittte	ne
700006b0:	ea1c 5513 	andsne.w	r5, ip, r3, lsr #20
700006b4:	ea94 0f0c 	teqne	r4, ip
700006b8:	ea95 0f0c 	teqne	r5, ip
700006bc:	f000 f8de 	bleq	7000087c <__aeabi_dmul+0x1dc>
700006c0:	442c      	add	r4, r5
700006c2:	ea81 0603 	eor.w	r6, r1, r3
700006c6:	ea21 514c 	bic.w	r1, r1, ip, lsl #21
700006ca:	ea23 534c 	bic.w	r3, r3, ip, lsl #21
700006ce:	ea50 3501 	orrs.w	r5, r0, r1, lsl #12
700006d2:	bf18      	it	ne
700006d4:	ea52 3503 	orrsne.w	r5, r2, r3, lsl #12
700006d8:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
700006dc:	f443 1380 	orr.w	r3, r3, #1048576	; 0x100000
700006e0:	d038      	beq.n	70000754 <__aeabi_dmul+0xb4>
700006e2:	fba0 ce02 	umull	ip, lr, r0, r2
700006e6:	f04f 0500 	mov.w	r5, #0
700006ea:	fbe1 e502 	umlal	lr, r5, r1, r2
700006ee:	f006 4200 	and.w	r2, r6, #2147483648	; 0x80000000
700006f2:	fbe0 e503 	umlal	lr, r5, r0, r3
700006f6:	f04f 0600 	mov.w	r6, #0
700006fa:	fbe1 5603 	umlal	r5, r6, r1, r3
700006fe:	f09c 0f00 	teq	ip, #0
70000702:	bf18      	it	ne
70000704:	f04e 0e01 	orrne.w	lr, lr, #1
70000708:	f1a4 04ff 	sub.w	r4, r4, #255	; 0xff
7000070c:	f5b6 7f00 	cmp.w	r6, #512	; 0x200
70000710:	f564 7440 	sbc.w	r4, r4, #768	; 0x300
70000714:	d204      	bcs.n	70000720 <__aeabi_dmul+0x80>
70000716:	ea5f 0e4e 	movs.w	lr, lr, lsl #1
7000071a:	416d      	adcs	r5, r5
7000071c:	eb46 0606 	adc.w	r6, r6, r6
70000720:	ea42 21c6 	orr.w	r1, r2, r6, lsl #11
70000724:	ea41 5155 	orr.w	r1, r1, r5, lsr #21
70000728:	ea4f 20c5 	mov.w	r0, r5, lsl #11
7000072c:	ea40 505e 	orr.w	r0, r0, lr, lsr #21
70000730:	ea4f 2ece 	mov.w	lr, lr, lsl #11
70000734:	f1b4 0cfd 	subs.w	ip, r4, #253	; 0xfd
70000738:	bf88      	it	hi
7000073a:	f5bc 6fe0 	cmphi.w	ip, #1792	; 0x700
7000073e:	d81e      	bhi.n	7000077e <__aeabi_dmul+0xde>
70000740:	f1be 4f00 	cmp.w	lr, #2147483648	; 0x80000000
70000744:	bf08      	it	eq
70000746:	ea5f 0e50 	movseq.w	lr, r0, lsr #1
7000074a:	f150 0000 	adcs.w	r0, r0, #0
7000074e:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
70000752:	bd70      	pop	{r4, r5, r6, pc}
70000754:	f006 4600 	and.w	r6, r6, #2147483648	; 0x80000000
70000758:	ea46 0101 	orr.w	r1, r6, r1
7000075c:	ea40 0002 	orr.w	r0, r0, r2
70000760:	ea81 0103 	eor.w	r1, r1, r3
70000764:	ebb4 045c 	subs.w	r4, r4, ip, lsr #1
70000768:	bfc2      	ittt	gt
7000076a:	ebd4 050c 	rsbsgt	r5, r4, ip
7000076e:	ea41 5104 	orrgt.w	r1, r1, r4, lsl #20
70000772:	bd70      	popgt	{r4, r5, r6, pc}
70000774:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70000778:	f04f 0e00 	mov.w	lr, #0
7000077c:	3c01      	subs	r4, #1
7000077e:	f300 80ab 	bgt.w	700008d8 <__aeabi_dmul+0x238>
70000782:	f114 0f36 	cmn.w	r4, #54	; 0x36
70000786:	bfde      	ittt	le
70000788:	2000      	movle	r0, #0
7000078a:	f001 4100 	andle.w	r1, r1, #2147483648	; 0x80000000
7000078e:	bd70      	pople	{r4, r5, r6, pc}
70000790:	f1c4 0400 	rsb	r4, r4, #0
70000794:	3c20      	subs	r4, #32
70000796:	da35      	bge.n	70000804 <__aeabi_dmul+0x164>
70000798:	340c      	adds	r4, #12
7000079a:	dc1b      	bgt.n	700007d4 <__aeabi_dmul+0x134>
7000079c:	f104 0414 	add.w	r4, r4, #20
700007a0:	f1c4 0520 	rsb	r5, r4, #32
700007a4:	fa00 f305 	lsl.w	r3, r0, r5
700007a8:	fa20 f004 	lsr.w	r0, r0, r4
700007ac:	fa01 f205 	lsl.w	r2, r1, r5
700007b0:	ea40 0002 	orr.w	r0, r0, r2
700007b4:	f001 4200 	and.w	r2, r1, #2147483648	; 0x80000000
700007b8:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
700007bc:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
700007c0:	fa21 f604 	lsr.w	r6, r1, r4
700007c4:	eb42 0106 	adc.w	r1, r2, r6
700007c8:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
700007cc:	bf08      	it	eq
700007ce:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
700007d2:	bd70      	pop	{r4, r5, r6, pc}
700007d4:	f1c4 040c 	rsb	r4, r4, #12
700007d8:	f1c4 0520 	rsb	r5, r4, #32
700007dc:	fa00 f304 	lsl.w	r3, r0, r4
700007e0:	fa20 f005 	lsr.w	r0, r0, r5
700007e4:	fa01 f204 	lsl.w	r2, r1, r4
700007e8:	ea40 0002 	orr.w	r0, r0, r2
700007ec:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700007f0:	eb10 70d3 	adds.w	r0, r0, r3, lsr #31
700007f4:	f141 0100 	adc.w	r1, r1, #0
700007f8:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
700007fc:	bf08      	it	eq
700007fe:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
70000802:	bd70      	pop	{r4, r5, r6, pc}
70000804:	f1c4 0520 	rsb	r5, r4, #32
70000808:	fa00 f205 	lsl.w	r2, r0, r5
7000080c:	ea4e 0e02 	orr.w	lr, lr, r2
70000810:	fa20 f304 	lsr.w	r3, r0, r4
70000814:	fa01 f205 	lsl.w	r2, r1, r5
70000818:	ea43 0302 	orr.w	r3, r3, r2
7000081c:	fa21 f004 	lsr.w	r0, r1, r4
70000820:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
70000824:	fa21 f204 	lsr.w	r2, r1, r4
70000828:	ea20 0002 	bic.w	r0, r0, r2
7000082c:	eb00 70d3 	add.w	r0, r0, r3, lsr #31
70000830:	ea5e 0e43 	orrs.w	lr, lr, r3, lsl #1
70000834:	bf08      	it	eq
70000836:	ea20 70d3 	biceq.w	r0, r0, r3, lsr #31
7000083a:	bd70      	pop	{r4, r5, r6, pc}
7000083c:	f094 0f00 	teq	r4, #0
70000840:	d10f      	bne.n	70000862 <__aeabi_dmul+0x1c2>
70000842:	f001 4600 	and.w	r6, r1, #2147483648	; 0x80000000
70000846:	0040      	lsls	r0, r0, #1
70000848:	eb41 0101 	adc.w	r1, r1, r1
7000084c:	f411 1f80 	tst.w	r1, #1048576	; 0x100000
70000850:	bf08      	it	eq
70000852:	3c01      	subeq	r4, #1
70000854:	d0f7      	beq.n	70000846 <__aeabi_dmul+0x1a6>
70000856:	ea41 0106 	orr.w	r1, r1, r6
7000085a:	f095 0f00 	teq	r5, #0
7000085e:	bf18      	it	ne
70000860:	4770      	bxne	lr
70000862:	f003 4600 	and.w	r6, r3, #2147483648	; 0x80000000
70000866:	0052      	lsls	r2, r2, #1
70000868:	eb43 0303 	adc.w	r3, r3, r3
7000086c:	f413 1f80 	tst.w	r3, #1048576	; 0x100000
70000870:	bf08      	it	eq
70000872:	3d01      	subeq	r5, #1
70000874:	d0f7      	beq.n	70000866 <__aeabi_dmul+0x1c6>
70000876:	ea43 0306 	orr.w	r3, r3, r6
7000087a:	4770      	bx	lr
7000087c:	ea94 0f0c 	teq	r4, ip
70000880:	ea0c 5513 	and.w	r5, ip, r3, lsr #20
70000884:	bf18      	it	ne
70000886:	ea95 0f0c 	teqne	r5, ip
7000088a:	d00c      	beq.n	700008a6 <__aeabi_dmul+0x206>
7000088c:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
70000890:	bf18      	it	ne
70000892:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
70000896:	d1d1      	bne.n	7000083c <__aeabi_dmul+0x19c>
70000898:	ea81 0103 	eor.w	r1, r1, r3
7000089c:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700008a0:	f04f 0000 	mov.w	r0, #0
700008a4:	bd70      	pop	{r4, r5, r6, pc}
700008a6:	ea50 0641 	orrs.w	r6, r0, r1, lsl #1
700008aa:	bf06      	itte	eq
700008ac:	4610      	moveq	r0, r2
700008ae:	4619      	moveq	r1, r3
700008b0:	ea52 0643 	orrsne.w	r6, r2, r3, lsl #1
700008b4:	d019      	beq.n	700008ea <__aeabi_dmul+0x24a>
700008b6:	ea94 0f0c 	teq	r4, ip
700008ba:	d102      	bne.n	700008c2 <__aeabi_dmul+0x222>
700008bc:	ea50 3601 	orrs.w	r6, r0, r1, lsl #12
700008c0:	d113      	bne.n	700008ea <__aeabi_dmul+0x24a>
700008c2:	ea95 0f0c 	teq	r5, ip
700008c6:	d105      	bne.n	700008d4 <__aeabi_dmul+0x234>
700008c8:	ea52 3603 	orrs.w	r6, r2, r3, lsl #12
700008cc:	bf1c      	itt	ne
700008ce:	4610      	movne	r0, r2
700008d0:	4619      	movne	r1, r3
700008d2:	d10a      	bne.n	700008ea <__aeabi_dmul+0x24a>
700008d4:	ea81 0103 	eor.w	r1, r1, r3
700008d8:	f001 4100 	and.w	r1, r1, #2147483648	; 0x80000000
700008dc:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
700008e0:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
700008e4:	f04f 0000 	mov.w	r0, #0
700008e8:	bd70      	pop	{r4, r5, r6, pc}
700008ea:	f041 41fe 	orr.w	r1, r1, #2130706432	; 0x7f000000
700008ee:	f441 0178 	orr.w	r1, r1, #16252928	; 0xf80000
700008f2:	bd70      	pop	{r4, r5, r6, pc}
700008f4:	f04f 0cff 	mov.w	ip, #255	; 0xff
700008f8:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
700008fc:	bf1e      	ittt	ne
700008fe:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70000902:	ea92 0f0c 	teqne	r2, ip
70000906:	ea93 0f0c 	teqne	r3, ip
7000090a:	d06f      	beq.n	700009ec <__aeabi_dmul+0x34c>
7000090c:	441a      	add	r2, r3
7000090e:	ea80 0c01 	eor.w	ip, r0, r1
70000912:	0240      	lsls	r0, r0, #9
70000914:	bf18      	it	ne
70000916:	ea5f 2141 	movsne.w	r1, r1, lsl #9
7000091a:	d01e      	beq.n	7000095a <__aeabi_dmul+0x2ba>
7000091c:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
70000920:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70000924:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70000928:	fba0 3101 	umull	r3, r1, r0, r1
7000092c:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70000930:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70000934:	bf3e      	ittt	cc
70000936:	0049      	lslcc	r1, r1, #1
70000938:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
7000093c:	005b      	lslcc	r3, r3, #1
7000093e:	ea40 0001 	orr.w	r0, r0, r1
70000942:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70000946:	2afd      	cmp	r2, #253	; 0xfd
70000948:	d81d      	bhi.n	70000986 <__aeabi_dmul+0x2e6>
7000094a:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
7000094e:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000952:	bf08      	it	eq
70000954:	f020 0001 	biceq.w	r0, r0, #1
70000958:	4770      	bx	lr
7000095a:	f090 0f00 	teq	r0, #0
7000095e:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
70000962:	bf08      	it	eq
70000964:	0249      	lsleq	r1, r1, #9
70000966:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
7000096a:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
7000096e:	3a7f      	subs	r2, #127	; 0x7f
70000970:	bfc2      	ittt	gt
70000972:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70000976:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
7000097a:	4770      	bxgt	lr
7000097c:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000980:	f04f 0300 	mov.w	r3, #0
70000984:	3a01      	subs	r2, #1
70000986:	dc5d      	bgt.n	70000a44 <__aeabi_dmul+0x3a4>
70000988:	f112 0f19 	cmn.w	r2, #25
7000098c:	bfdc      	itt	le
7000098e:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
70000992:	4770      	bxle	lr
70000994:	f1c2 0200 	rsb	r2, r2, #0
70000998:	0041      	lsls	r1, r0, #1
7000099a:	fa21 f102 	lsr.w	r1, r1, r2
7000099e:	f1c2 0220 	rsb	r2, r2, #32
700009a2:	fa00 fc02 	lsl.w	ip, r0, r2
700009a6:	ea5f 0031 	movs.w	r0, r1, rrx
700009aa:	f140 0000 	adc.w	r0, r0, #0
700009ae:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
700009b2:	bf08      	it	eq
700009b4:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
700009b8:	4770      	bx	lr
700009ba:	f092 0f00 	teq	r2, #0
700009be:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
700009c2:	bf02      	ittt	eq
700009c4:	0040      	lsleq	r0, r0, #1
700009c6:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
700009ca:	3a01      	subeq	r2, #1
700009cc:	d0f9      	beq.n	700009c2 <__aeabi_dmul+0x322>
700009ce:	ea40 000c 	orr.w	r0, r0, ip
700009d2:	f093 0f00 	teq	r3, #0
700009d6:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
700009da:	bf02      	ittt	eq
700009dc:	0049      	lsleq	r1, r1, #1
700009de:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
700009e2:	3b01      	subeq	r3, #1
700009e4:	d0f9      	beq.n	700009da <__aeabi_dmul+0x33a>
700009e6:	ea41 010c 	orr.w	r1, r1, ip
700009ea:	e78f      	b.n	7000090c <__aeabi_dmul+0x26c>
700009ec:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
700009f0:	ea92 0f0c 	teq	r2, ip
700009f4:	bf18      	it	ne
700009f6:	ea93 0f0c 	teqne	r3, ip
700009fa:	d00a      	beq.n	70000a12 <__aeabi_dmul+0x372>
700009fc:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70000a00:	bf18      	it	ne
70000a02:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
70000a06:	d1d8      	bne.n	700009ba <__aeabi_dmul+0x31a>
70000a08:	ea80 0001 	eor.w	r0, r0, r1
70000a0c:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000a10:	4770      	bx	lr
70000a12:	f090 0f00 	teq	r0, #0
70000a16:	bf17      	itett	ne
70000a18:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
70000a1c:	4608      	moveq	r0, r1
70000a1e:	f091 0f00 	teqne	r1, #0
70000a22:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70000a26:	d014      	beq.n	70000a52 <__aeabi_dmul+0x3b2>
70000a28:	ea92 0f0c 	teq	r2, ip
70000a2c:	d101      	bne.n	70000a32 <__aeabi_dmul+0x392>
70000a2e:	0242      	lsls	r2, r0, #9
70000a30:	d10f      	bne.n	70000a52 <__aeabi_dmul+0x3b2>
70000a32:	ea93 0f0c 	teq	r3, ip
70000a36:	d103      	bne.n	70000a40 <__aeabi_dmul+0x3a0>
70000a38:	024b      	lsls	r3, r1, #9
70000a3a:	bf18      	it	ne
70000a3c:	4608      	movne	r0, r1
70000a3e:	d108      	bne.n	70000a52 <__aeabi_dmul+0x3b2>
70000a40:	ea80 0001 	eor.w	r0, r0, r1
70000a44:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70000a48:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000a4c:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000a50:	4770      	bx	lr
70000a52:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000a56:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70000a5a:	4770      	bx	lr

70000a5c <__aeabi_drsub>:
70000a5c:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000
70000a60:	e002      	b.n	70000a68 <__adddf3>
70000a62:	bf00      	nop

70000a64 <__aeabi_dsub>:
70000a64:	f083 4300 	eor.w	r3, r3, #2147483648	; 0x80000000

70000a68 <__adddf3>:
70000a68:	b530      	push	{r4, r5, lr}
70000a6a:	ea4f 0441 	mov.w	r4, r1, lsl #1
70000a6e:	ea4f 0543 	mov.w	r5, r3, lsl #1
70000a72:	ea94 0f05 	teq	r4, r5
70000a76:	bf08      	it	eq
70000a78:	ea90 0f02 	teqeq	r0, r2
70000a7c:	bf1f      	itttt	ne
70000a7e:	ea54 0c00 	orrsne.w	ip, r4, r0
70000a82:	ea55 0c02 	orrsne.w	ip, r5, r2
70000a86:	ea7f 5c64 	mvnsne.w	ip, r4, asr #21
70000a8a:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70000a8e:	f000 80e2 	beq.w	70000c56 <__adddf3+0x1ee>
70000a92:	ea4f 5454 	mov.w	r4, r4, lsr #21
70000a96:	ebd4 5555 	rsbs	r5, r4, r5, lsr #21
70000a9a:	bfb8      	it	lt
70000a9c:	426d      	neglt	r5, r5
70000a9e:	dd0c      	ble.n	70000aba <__adddf3+0x52>
70000aa0:	442c      	add	r4, r5
70000aa2:	ea80 0202 	eor.w	r2, r0, r2
70000aa6:	ea81 0303 	eor.w	r3, r1, r3
70000aaa:	ea82 0000 	eor.w	r0, r2, r0
70000aae:	ea83 0101 	eor.w	r1, r3, r1
70000ab2:	ea80 0202 	eor.w	r2, r0, r2
70000ab6:	ea81 0303 	eor.w	r3, r1, r3
70000aba:	2d36      	cmp	r5, #54	; 0x36
70000abc:	bf88      	it	hi
70000abe:	bd30      	pophi	{r4, r5, pc}
70000ac0:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000ac4:	ea4f 3101 	mov.w	r1, r1, lsl #12
70000ac8:	f44f 1c80 	mov.w	ip, #1048576	; 0x100000
70000acc:	ea4c 3111 	orr.w	r1, ip, r1, lsr #12
70000ad0:	d002      	beq.n	70000ad8 <__adddf3+0x70>
70000ad2:	4240      	negs	r0, r0
70000ad4:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000ad8:	f013 4f00 	tst.w	r3, #2147483648	; 0x80000000
70000adc:	ea4f 3303 	mov.w	r3, r3, lsl #12
70000ae0:	ea4c 3313 	orr.w	r3, ip, r3, lsr #12
70000ae4:	d002      	beq.n	70000aec <__adddf3+0x84>
70000ae6:	4252      	negs	r2, r2
70000ae8:	eb63 0343 	sbc.w	r3, r3, r3, lsl #1
70000aec:	ea94 0f05 	teq	r4, r5
70000af0:	f000 80a7 	beq.w	70000c42 <__adddf3+0x1da>
70000af4:	f1a4 0401 	sub.w	r4, r4, #1
70000af8:	f1d5 0e20 	rsbs	lr, r5, #32
70000afc:	db0d      	blt.n	70000b1a <__adddf3+0xb2>
70000afe:	fa02 fc0e 	lsl.w	ip, r2, lr
70000b02:	fa22 f205 	lsr.w	r2, r2, r5
70000b06:	1880      	adds	r0, r0, r2
70000b08:	f141 0100 	adc.w	r1, r1, #0
70000b0c:	fa03 f20e 	lsl.w	r2, r3, lr
70000b10:	1880      	adds	r0, r0, r2
70000b12:	fa43 f305 	asr.w	r3, r3, r5
70000b16:	4159      	adcs	r1, r3
70000b18:	e00e      	b.n	70000b38 <__adddf3+0xd0>
70000b1a:	f1a5 0520 	sub.w	r5, r5, #32
70000b1e:	f10e 0e20 	add.w	lr, lr, #32
70000b22:	2a01      	cmp	r2, #1
70000b24:	fa03 fc0e 	lsl.w	ip, r3, lr
70000b28:	bf28      	it	cs
70000b2a:	f04c 0c02 	orrcs.w	ip, ip, #2
70000b2e:	fa43 f305 	asr.w	r3, r3, r5
70000b32:	18c0      	adds	r0, r0, r3
70000b34:	eb51 71e3 	adcs.w	r1, r1, r3, asr #31
70000b38:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000b3c:	d507      	bpl.n	70000b4e <__adddf3+0xe6>
70000b3e:	f04f 0e00 	mov.w	lr, #0
70000b42:	f1dc 0c00 	rsbs	ip, ip, #0
70000b46:	eb7e 0000 	sbcs.w	r0, lr, r0
70000b4a:	eb6e 0101 	sbc.w	r1, lr, r1
70000b4e:	f5b1 1f80 	cmp.w	r1, #1048576	; 0x100000
70000b52:	d31b      	bcc.n	70000b8c <__adddf3+0x124>
70000b54:	f5b1 1f00 	cmp.w	r1, #2097152	; 0x200000
70000b58:	d30c      	bcc.n	70000b74 <__adddf3+0x10c>
70000b5a:	0849      	lsrs	r1, r1, #1
70000b5c:	ea5f 0030 	movs.w	r0, r0, rrx
70000b60:	ea4f 0c3c 	mov.w	ip, ip, rrx
70000b64:	f104 0401 	add.w	r4, r4, #1
70000b68:	ea4f 5244 	mov.w	r2, r4, lsl #21
70000b6c:	f512 0f80 	cmn.w	r2, #4194304	; 0x400000
70000b70:	f080 809a 	bcs.w	70000ca8 <__adddf3+0x240>
70000b74:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
70000b78:	bf08      	it	eq
70000b7a:	ea5f 0c50 	movseq.w	ip, r0, lsr #1
70000b7e:	f150 0000 	adcs.w	r0, r0, #0
70000b82:	eb41 5104 	adc.w	r1, r1, r4, lsl #20
70000b86:	ea41 0105 	orr.w	r1, r1, r5
70000b8a:	bd30      	pop	{r4, r5, pc}
70000b8c:	ea5f 0c4c 	movs.w	ip, ip, lsl #1
70000b90:	4140      	adcs	r0, r0
70000b92:	eb41 0101 	adc.w	r1, r1, r1
70000b96:	3c01      	subs	r4, #1
70000b98:	bf28      	it	cs
70000b9a:	f5b1 1f80 	cmpcs.w	r1, #1048576	; 0x100000
70000b9e:	d2e9      	bcs.n	70000b74 <__adddf3+0x10c>
70000ba0:	f091 0f00 	teq	r1, #0
70000ba4:	bf04      	itt	eq
70000ba6:	4601      	moveq	r1, r0
70000ba8:	2000      	moveq	r0, #0
70000baa:	fab1 f381 	clz	r3, r1
70000bae:	bf08      	it	eq
70000bb0:	3320      	addeq	r3, #32
70000bb2:	f1a3 030b 	sub.w	r3, r3, #11
70000bb6:	f1b3 0220 	subs.w	r2, r3, #32
70000bba:	da0c      	bge.n	70000bd6 <__adddf3+0x16e>
70000bbc:	320c      	adds	r2, #12
70000bbe:	dd08      	ble.n	70000bd2 <__adddf3+0x16a>
70000bc0:	f102 0c14 	add.w	ip, r2, #20
70000bc4:	f1c2 020c 	rsb	r2, r2, #12
70000bc8:	fa01 f00c 	lsl.w	r0, r1, ip
70000bcc:	fa21 f102 	lsr.w	r1, r1, r2
70000bd0:	e00c      	b.n	70000bec <__adddf3+0x184>
70000bd2:	f102 0214 	add.w	r2, r2, #20
70000bd6:	bfd8      	it	le
70000bd8:	f1c2 0c20 	rsble	ip, r2, #32
70000bdc:	fa01 f102 	lsl.w	r1, r1, r2
70000be0:	fa20 fc0c 	lsr.w	ip, r0, ip
70000be4:	bfdc      	itt	le
70000be6:	ea41 010c 	orrle.w	r1, r1, ip
70000bea:	4090      	lslle	r0, r2
70000bec:	1ae4      	subs	r4, r4, r3
70000bee:	bfa2      	ittt	ge
70000bf0:	eb01 5104 	addge.w	r1, r1, r4, lsl #20
70000bf4:	4329      	orrge	r1, r5
70000bf6:	bd30      	popge	{r4, r5, pc}
70000bf8:	ea6f 0404 	mvn.w	r4, r4
70000bfc:	3c1f      	subs	r4, #31
70000bfe:	da1c      	bge.n	70000c3a <__adddf3+0x1d2>
70000c00:	340c      	adds	r4, #12
70000c02:	dc0e      	bgt.n	70000c22 <__adddf3+0x1ba>
70000c04:	f104 0414 	add.w	r4, r4, #20
70000c08:	f1c4 0220 	rsb	r2, r4, #32
70000c0c:	fa20 f004 	lsr.w	r0, r0, r4
70000c10:	fa01 f302 	lsl.w	r3, r1, r2
70000c14:	ea40 0003 	orr.w	r0, r0, r3
70000c18:	fa21 f304 	lsr.w	r3, r1, r4
70000c1c:	ea45 0103 	orr.w	r1, r5, r3
70000c20:	bd30      	pop	{r4, r5, pc}
70000c22:	f1c4 040c 	rsb	r4, r4, #12
70000c26:	f1c4 0220 	rsb	r2, r4, #32
70000c2a:	fa20 f002 	lsr.w	r0, r0, r2
70000c2e:	fa01 f304 	lsl.w	r3, r1, r4
70000c32:	ea40 0003 	orr.w	r0, r0, r3
70000c36:	4629      	mov	r1, r5
70000c38:	bd30      	pop	{r4, r5, pc}
70000c3a:	fa21 f004 	lsr.w	r0, r1, r4
70000c3e:	4629      	mov	r1, r5
70000c40:	bd30      	pop	{r4, r5, pc}
70000c42:	f094 0f00 	teq	r4, #0
70000c46:	f483 1380 	eor.w	r3, r3, #1048576	; 0x100000
70000c4a:	bf06      	itte	eq
70000c4c:	f481 1180 	eoreq.w	r1, r1, #1048576	; 0x100000
70000c50:	3401      	addeq	r4, #1
70000c52:	3d01      	subne	r5, #1
70000c54:	e74e      	b.n	70000af4 <__adddf3+0x8c>
70000c56:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70000c5a:	bf18      	it	ne
70000c5c:	ea7f 5c65 	mvnsne.w	ip, r5, asr #21
70000c60:	d029      	beq.n	70000cb6 <__adddf3+0x24e>
70000c62:	ea94 0f05 	teq	r4, r5
70000c66:	bf08      	it	eq
70000c68:	ea90 0f02 	teqeq	r0, r2
70000c6c:	d005      	beq.n	70000c7a <__adddf3+0x212>
70000c6e:	ea54 0c00 	orrs.w	ip, r4, r0
70000c72:	bf04      	itt	eq
70000c74:	4619      	moveq	r1, r3
70000c76:	4610      	moveq	r0, r2
70000c78:	bd30      	pop	{r4, r5, pc}
70000c7a:	ea91 0f03 	teq	r1, r3
70000c7e:	bf1e      	ittt	ne
70000c80:	2100      	movne	r1, #0
70000c82:	2000      	movne	r0, #0
70000c84:	bd30      	popne	{r4, r5, pc}
70000c86:	ea5f 5c54 	movs.w	ip, r4, lsr #21
70000c8a:	d105      	bne.n	70000c98 <__adddf3+0x230>
70000c8c:	0040      	lsls	r0, r0, #1
70000c8e:	4149      	adcs	r1, r1
70000c90:	bf28      	it	cs
70000c92:	f041 4100 	orrcs.w	r1, r1, #2147483648	; 0x80000000
70000c96:	bd30      	pop	{r4, r5, pc}
70000c98:	f514 0480 	adds.w	r4, r4, #4194304	; 0x400000
70000c9c:	bf3c      	itt	cc
70000c9e:	f501 1180 	addcc.w	r1, r1, #1048576	; 0x100000
70000ca2:	bd30      	popcc	{r4, r5, pc}
70000ca4:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000ca8:	f045 41fe 	orr.w	r1, r5, #2130706432	; 0x7f000000
70000cac:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
70000cb0:	f04f 0000 	mov.w	r0, #0
70000cb4:	bd30      	pop	{r4, r5, pc}
70000cb6:	ea7f 5c64 	mvns.w	ip, r4, asr #21
70000cba:	bf1a      	itte	ne
70000cbc:	4619      	movne	r1, r3
70000cbe:	4610      	movne	r0, r2
70000cc0:	ea7f 5c65 	mvnseq.w	ip, r5, asr #21
70000cc4:	bf1c      	itt	ne
70000cc6:	460b      	movne	r3, r1
70000cc8:	4602      	movne	r2, r0
70000cca:	ea50 3401 	orrs.w	r4, r0, r1, lsl #12
70000cce:	bf06      	itte	eq
70000cd0:	ea52 3503 	orrseq.w	r5, r2, r3, lsl #12
70000cd4:	ea91 0f03 	teqeq	r1, r3
70000cd8:	f441 2100 	orrne.w	r1, r1, #524288	; 0x80000
70000cdc:	bd30      	pop	{r4, r5, pc}
70000cde:	bf00      	nop

70000ce0 <__aeabi_ui2d>:
70000ce0:	f090 0f00 	teq	r0, #0
70000ce4:	bf04      	itt	eq
70000ce6:	2100      	moveq	r1, #0
70000ce8:	4770      	bxeq	lr
70000cea:	b530      	push	{r4, r5, lr}
70000cec:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000cf0:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000cf4:	f04f 0500 	mov.w	r5, #0
70000cf8:	f04f 0100 	mov.w	r1, #0
70000cfc:	e750      	b.n	70000ba0 <__adddf3+0x138>
70000cfe:	bf00      	nop

70000d00 <__aeabi_i2d>:
70000d00:	f090 0f00 	teq	r0, #0
70000d04:	bf04      	itt	eq
70000d06:	2100      	moveq	r1, #0
70000d08:	4770      	bxeq	lr
70000d0a:	b530      	push	{r4, r5, lr}
70000d0c:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000d10:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000d14:	f010 4500 	ands.w	r5, r0, #2147483648	; 0x80000000
70000d18:	bf48      	it	mi
70000d1a:	4240      	negmi	r0, r0
70000d1c:	f04f 0100 	mov.w	r1, #0
70000d20:	e73e      	b.n	70000ba0 <__adddf3+0x138>
70000d22:	bf00      	nop

70000d24 <__aeabi_f2d>:
70000d24:	0042      	lsls	r2, r0, #1
70000d26:	ea4f 01e2 	mov.w	r1, r2, asr #3
70000d2a:	ea4f 0131 	mov.w	r1, r1, rrx
70000d2e:	ea4f 7002 	mov.w	r0, r2, lsl #28
70000d32:	bf1f      	itttt	ne
70000d34:	f012 437f 	andsne.w	r3, r2, #4278190080	; 0xff000000
70000d38:	f093 4f7f 	teqne	r3, #4278190080	; 0xff000000
70000d3c:	f081 5160 	eorne.w	r1, r1, #939524096	; 0x38000000
70000d40:	4770      	bxne	lr
70000d42:	f032 427f 	bics.w	r2, r2, #4278190080	; 0xff000000
70000d46:	bf08      	it	eq
70000d48:	4770      	bxeq	lr
70000d4a:	f093 4f7f 	teq	r3, #4278190080	; 0xff000000
70000d4e:	bf04      	itt	eq
70000d50:	f441 2100 	orreq.w	r1, r1, #524288	; 0x80000
70000d54:	4770      	bxeq	lr
70000d56:	b530      	push	{r4, r5, lr}
70000d58:	f44f 7460 	mov.w	r4, #896	; 0x380
70000d5c:	f001 4500 	and.w	r5, r1, #2147483648	; 0x80000000
70000d60:	f021 4100 	bic.w	r1, r1, #2147483648	; 0x80000000
70000d64:	e71c      	b.n	70000ba0 <__adddf3+0x138>
70000d66:	bf00      	nop

70000d68 <__aeabi_ul2d>:
70000d68:	ea50 0201 	orrs.w	r2, r0, r1
70000d6c:	bf08      	it	eq
70000d6e:	4770      	bxeq	lr
70000d70:	b530      	push	{r4, r5, lr}
70000d72:	f04f 0500 	mov.w	r5, #0
70000d76:	e00a      	b.n	70000d8e <__aeabi_l2d+0x16>

70000d78 <__aeabi_l2d>:
70000d78:	ea50 0201 	orrs.w	r2, r0, r1
70000d7c:	bf08      	it	eq
70000d7e:	4770      	bxeq	lr
70000d80:	b530      	push	{r4, r5, lr}
70000d82:	f011 4500 	ands.w	r5, r1, #2147483648	; 0x80000000
70000d86:	d502      	bpl.n	70000d8e <__aeabi_l2d+0x16>
70000d88:	4240      	negs	r0, r0
70000d8a:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70000d8e:	f44f 6480 	mov.w	r4, #1024	; 0x400
70000d92:	f104 0432 	add.w	r4, r4, #50	; 0x32
70000d96:	ea5f 5c91 	movs.w	ip, r1, lsr #22
70000d9a:	f43f aed8 	beq.w	70000b4e <__adddf3+0xe6>
70000d9e:	f04f 0203 	mov.w	r2, #3
70000da2:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70000da6:	bf18      	it	ne
70000da8:	3203      	addne	r2, #3
70000daa:	ea5f 0cdc 	movs.w	ip, ip, lsr #3
70000dae:	bf18      	it	ne
70000db0:	3203      	addne	r2, #3
70000db2:	eb02 02dc 	add.w	r2, r2, ip, lsr #3
70000db6:	f1c2 0320 	rsb	r3, r2, #32
70000dba:	fa00 fc03 	lsl.w	ip, r0, r3
70000dbe:	fa20 f002 	lsr.w	r0, r0, r2
70000dc2:	fa01 fe03 	lsl.w	lr, r1, r3
70000dc6:	ea40 000e 	orr.w	r0, r0, lr
70000dca:	fa21 f102 	lsr.w	r1, r1, r2
70000dce:	4414      	add	r4, r2
70000dd0:	e6bd      	b.n	70000b4e <__adddf3+0xe6>
70000dd2:	bf00      	nop

70000dd4 <__aeabi_d2uiz>:
70000dd4:	004a      	lsls	r2, r1, #1
70000dd6:	d211      	bcs.n	70000dfc <__aeabi_d2uiz+0x28>
70000dd8:	f512 1200 	adds.w	r2, r2, #2097152	; 0x200000
70000ddc:	d211      	bcs.n	70000e02 <__aeabi_d2uiz+0x2e>
70000dde:	d50d      	bpl.n	70000dfc <__aeabi_d2uiz+0x28>
70000de0:	f46f 7378 	mvn.w	r3, #992	; 0x3e0
70000de4:	ebb3 5262 	subs.w	r2, r3, r2, asr #21
70000de8:	d40e      	bmi.n	70000e08 <__aeabi_d2uiz+0x34>
70000dea:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70000dee:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70000df2:	ea43 5350 	orr.w	r3, r3, r0, lsr #21
70000df6:	fa23 f002 	lsr.w	r0, r3, r2
70000dfa:	4770      	bx	lr
70000dfc:	f04f 0000 	mov.w	r0, #0
70000e00:	4770      	bx	lr
70000e02:	ea50 3001 	orrs.w	r0, r0, r1, lsl #12
70000e06:	d102      	bne.n	70000e0e <__aeabi_d2uiz+0x3a>
70000e08:	f04f 30ff 	mov.w	r0, #4294967295
70000e0c:	4770      	bx	lr
70000e0e:	f04f 0000 	mov.w	r0, #0
70000e12:	4770      	bx	lr

70000e14 <__aeabi_d2f>:
70000e14:	ea4f 0241 	mov.w	r2, r1, lsl #1
70000e18:	f1b2 43e0 	subs.w	r3, r2, #1879048192	; 0x70000000
70000e1c:	bf24      	itt	cs
70000e1e:	f5b3 1c00 	subscs.w	ip, r3, #2097152	; 0x200000
70000e22:	f1dc 5cfe 	rsbscs	ip, ip, #532676608	; 0x1fc00000
70000e26:	d90d      	bls.n	70000e44 <__aeabi_d2f+0x30>
70000e28:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70000e2c:	ea4f 02c0 	mov.w	r2, r0, lsl #3
70000e30:	ea4c 7050 	orr.w	r0, ip, r0, lsr #29
70000e34:	f1b2 4f00 	cmp.w	r2, #2147483648	; 0x80000000
70000e38:	eb40 0083 	adc.w	r0, r0, r3, lsl #2
70000e3c:	bf08      	it	eq
70000e3e:	f020 0001 	biceq.w	r0, r0, #1
70000e42:	4770      	bx	lr
70000e44:	f011 4f80 	tst.w	r1, #1073741824	; 0x40000000
70000e48:	d121      	bne.n	70000e8e <__aeabi_d2f+0x7a>
70000e4a:	f113 7238 	adds.w	r2, r3, #48234496	; 0x2e00000
70000e4e:	bfbc      	itt	lt
70000e50:	f001 4000 	andlt.w	r0, r1, #2147483648	; 0x80000000
70000e54:	4770      	bxlt	lr
70000e56:	f441 1180 	orr.w	r1, r1, #1048576	; 0x100000
70000e5a:	ea4f 5252 	mov.w	r2, r2, lsr #21
70000e5e:	f1c2 0218 	rsb	r2, r2, #24
70000e62:	f1c2 0c20 	rsb	ip, r2, #32
70000e66:	fa10 f30c 	lsls.w	r3, r0, ip
70000e6a:	fa20 f002 	lsr.w	r0, r0, r2
70000e6e:	bf18      	it	ne
70000e70:	f040 0001 	orrne.w	r0, r0, #1
70000e74:	ea4f 23c1 	mov.w	r3, r1, lsl #11
70000e78:	ea4f 23d3 	mov.w	r3, r3, lsr #11
70000e7c:	fa03 fc0c 	lsl.w	ip, r3, ip
70000e80:	ea40 000c 	orr.w	r0, r0, ip
70000e84:	fa23 f302 	lsr.w	r3, r3, r2
70000e88:	ea4f 0343 	mov.w	r3, r3, lsl #1
70000e8c:	e7cc      	b.n	70000e28 <__aeabi_d2f+0x14>
70000e8e:	ea7f 5362 	mvns.w	r3, r2, asr #21
70000e92:	d107      	bne.n	70000ea4 <__aeabi_d2f+0x90>
70000e94:	ea50 3301 	orrs.w	r3, r0, r1, lsl #12
70000e98:	bf1e      	ittt	ne
70000e9a:	f04f 40fe 	movne.w	r0, #2130706432	; 0x7f000000
70000e9e:	f440 0040 	orrne.w	r0, r0, #12582912	; 0xc00000
70000ea2:	4770      	bxne	lr
70000ea4:	f001 4000 	and.w	r0, r1, #2147483648	; 0x80000000
70000ea8:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70000eac:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000eb0:	4770      	bx	lr
70000eb2:	bf00      	nop

70000eb4 <__aeabi_frsub>:
70000eb4:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
70000eb8:	e002      	b.n	70000ec0 <__addsf3>
70000eba:	bf00      	nop

70000ebc <__aeabi_fsub>:
70000ebc:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

70000ec0 <__addsf3>:
70000ec0:	0042      	lsls	r2, r0, #1
70000ec2:	bf1f      	itttt	ne
70000ec4:	ea5f 0341 	movsne.w	r3, r1, lsl #1
70000ec8:	ea92 0f03 	teqne	r2, r3
70000ecc:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
70000ed0:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000ed4:	d06a      	beq.n	70000fac <__addsf3+0xec>
70000ed6:	ea4f 6212 	mov.w	r2, r2, lsr #24
70000eda:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
70000ede:	bfc1      	itttt	gt
70000ee0:	18d2      	addgt	r2, r2, r3
70000ee2:	4041      	eorgt	r1, r0
70000ee4:	4048      	eorgt	r0, r1
70000ee6:	4041      	eorgt	r1, r0
70000ee8:	bfb8      	it	lt
70000eea:	425b      	neglt	r3, r3
70000eec:	2b19      	cmp	r3, #25
70000eee:	bf88      	it	hi
70000ef0:	4770      	bxhi	lr
70000ef2:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
70000ef6:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000efa:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
70000efe:	bf18      	it	ne
70000f00:	4240      	negne	r0, r0
70000f02:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
70000f06:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
70000f0a:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
70000f0e:	bf18      	it	ne
70000f10:	4249      	negne	r1, r1
70000f12:	ea92 0f03 	teq	r2, r3
70000f16:	d03f      	beq.n	70000f98 <__addsf3+0xd8>
70000f18:	f1a2 0201 	sub.w	r2, r2, #1
70000f1c:	fa41 fc03 	asr.w	ip, r1, r3
70000f20:	eb10 000c 	adds.w	r0, r0, ip
70000f24:	f1c3 0320 	rsb	r3, r3, #32
70000f28:	fa01 f103 	lsl.w	r1, r1, r3
70000f2c:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000f30:	d502      	bpl.n	70000f38 <__addsf3+0x78>
70000f32:	4249      	negs	r1, r1
70000f34:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
70000f38:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
70000f3c:	d313      	bcc.n	70000f66 <__addsf3+0xa6>
70000f3e:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
70000f42:	d306      	bcc.n	70000f52 <__addsf3+0x92>
70000f44:	0840      	lsrs	r0, r0, #1
70000f46:	ea4f 0131 	mov.w	r1, r1, rrx
70000f4a:	f102 0201 	add.w	r2, r2, #1
70000f4e:	2afe      	cmp	r2, #254	; 0xfe
70000f50:	d251      	bcs.n	70000ff6 <__addsf3+0x136>
70000f52:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
70000f56:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
70000f5a:	bf08      	it	eq
70000f5c:	f020 0001 	biceq.w	r0, r0, #1
70000f60:	ea40 0003 	orr.w	r0, r0, r3
70000f64:	4770      	bx	lr
70000f66:	0049      	lsls	r1, r1, #1
70000f68:	eb40 0000 	adc.w	r0, r0, r0
70000f6c:	3a01      	subs	r2, #1
70000f6e:	bf28      	it	cs
70000f70:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
70000f74:	d2ed      	bcs.n	70000f52 <__addsf3+0x92>
70000f76:	fab0 fc80 	clz	ip, r0
70000f7a:	f1ac 0c08 	sub.w	ip, ip, #8
70000f7e:	ebb2 020c 	subs.w	r2, r2, ip
70000f82:	fa00 f00c 	lsl.w	r0, r0, ip
70000f86:	bfaa      	itet	ge
70000f88:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
70000f8c:	4252      	neglt	r2, r2
70000f8e:	4318      	orrge	r0, r3
70000f90:	bfbc      	itt	lt
70000f92:	40d0      	lsrlt	r0, r2
70000f94:	4318      	orrlt	r0, r3
70000f96:	4770      	bx	lr
70000f98:	f092 0f00 	teq	r2, #0
70000f9c:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
70000fa0:	bf06      	itte	eq
70000fa2:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
70000fa6:	3201      	addeq	r2, #1
70000fa8:	3b01      	subne	r3, #1
70000faa:	e7b5      	b.n	70000f18 <__addsf3+0x58>
70000fac:	ea4f 0341 	mov.w	r3, r1, lsl #1
70000fb0:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000fb4:	bf18      	it	ne
70000fb6:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000fba:	d021      	beq.n	70001000 <__addsf3+0x140>
70000fbc:	ea92 0f03 	teq	r2, r3
70000fc0:	d004      	beq.n	70000fcc <__addsf3+0x10c>
70000fc2:	f092 0f00 	teq	r2, #0
70000fc6:	bf08      	it	eq
70000fc8:	4608      	moveq	r0, r1
70000fca:	4770      	bx	lr
70000fcc:	ea90 0f01 	teq	r0, r1
70000fd0:	bf1c      	itt	ne
70000fd2:	2000      	movne	r0, #0
70000fd4:	4770      	bxne	lr
70000fd6:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
70000fda:	d104      	bne.n	70000fe6 <__addsf3+0x126>
70000fdc:	0040      	lsls	r0, r0, #1
70000fde:	bf28      	it	cs
70000fe0:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
70000fe4:	4770      	bx	lr
70000fe6:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
70000fea:	bf3c      	itt	cc
70000fec:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
70000ff0:	4770      	bxcc	lr
70000ff2:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
70000ff6:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
70000ffa:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
70000ffe:	4770      	bx	lr
70001000:	ea7f 6222 	mvns.w	r2, r2, asr #24
70001004:	bf16      	itet	ne
70001006:	4608      	movne	r0, r1
70001008:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
7000100c:	4601      	movne	r1, r0
7000100e:	0242      	lsls	r2, r0, #9
70001010:	bf06      	itte	eq
70001012:	ea5f 2341 	movseq.w	r3, r1, lsl #9
70001016:	ea90 0f01 	teqeq	r0, r1
7000101a:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
7000101e:	4770      	bx	lr

70001020 <__aeabi_ui2f>:
70001020:	f04f 0300 	mov.w	r3, #0
70001024:	e004      	b.n	70001030 <__aeabi_i2f+0x8>
70001026:	bf00      	nop

70001028 <__aeabi_i2f>:
70001028:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
7000102c:	bf48      	it	mi
7000102e:	4240      	negmi	r0, r0
70001030:	ea5f 0c00 	movs.w	ip, r0
70001034:	bf08      	it	eq
70001036:	4770      	bxeq	lr
70001038:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
7000103c:	4601      	mov	r1, r0
7000103e:	f04f 0000 	mov.w	r0, #0
70001042:	e01c      	b.n	7000107e <__aeabi_l2f+0x2a>

70001044 <__aeabi_ul2f>:
70001044:	ea50 0201 	orrs.w	r2, r0, r1
70001048:	bf08      	it	eq
7000104a:	4770      	bxeq	lr
7000104c:	f04f 0300 	mov.w	r3, #0
70001050:	e00a      	b.n	70001068 <__aeabi_l2f+0x14>
70001052:	bf00      	nop

70001054 <__aeabi_l2f>:
70001054:	ea50 0201 	orrs.w	r2, r0, r1
70001058:	bf08      	it	eq
7000105a:	4770      	bxeq	lr
7000105c:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
70001060:	d502      	bpl.n	70001068 <__aeabi_l2f+0x14>
70001062:	4240      	negs	r0, r0
70001064:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
70001068:	ea5f 0c01 	movs.w	ip, r1
7000106c:	bf02      	ittt	eq
7000106e:	4684      	moveq	ip, r0
70001070:	4601      	moveq	r1, r0
70001072:	2000      	moveq	r0, #0
70001074:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
70001078:	bf08      	it	eq
7000107a:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
7000107e:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
70001082:	fabc f28c 	clz	r2, ip
70001086:	3a08      	subs	r2, #8
70001088:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
7000108c:	db10      	blt.n	700010b0 <__aeabi_l2f+0x5c>
7000108e:	fa01 fc02 	lsl.w	ip, r1, r2
70001092:	4463      	add	r3, ip
70001094:	fa00 fc02 	lsl.w	ip, r0, r2
70001098:	f1c2 0220 	rsb	r2, r2, #32
7000109c:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
700010a0:	fa20 f202 	lsr.w	r2, r0, r2
700010a4:	eb43 0002 	adc.w	r0, r3, r2
700010a8:	bf08      	it	eq
700010aa:	f020 0001 	biceq.w	r0, r0, #1
700010ae:	4770      	bx	lr
700010b0:	f102 0220 	add.w	r2, r2, #32
700010b4:	fa01 fc02 	lsl.w	ip, r1, r2
700010b8:	f1c2 0220 	rsb	r2, r2, #32
700010bc:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
700010c0:	fa21 f202 	lsr.w	r2, r1, r2
700010c4:	eb43 0002 	adc.w	r0, r3, r2
700010c8:	bf08      	it	eq
700010ca:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
700010ce:	4770      	bx	lr

700010d0 <__aeabi_fmul>:
700010d0:	f04f 0cff 	mov.w	ip, #255	; 0xff
700010d4:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
700010d8:	bf1e      	ittt	ne
700010da:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
700010de:	ea92 0f0c 	teqne	r2, ip
700010e2:	ea93 0f0c 	teqne	r3, ip
700010e6:	d06f      	beq.n	700011c8 <__aeabi_fmul+0xf8>
700010e8:	441a      	add	r2, r3
700010ea:	ea80 0c01 	eor.w	ip, r0, r1
700010ee:	0240      	lsls	r0, r0, #9
700010f0:	bf18      	it	ne
700010f2:	ea5f 2141 	movsne.w	r1, r1, lsl #9
700010f6:	d01e      	beq.n	70001136 <__aeabi_fmul+0x66>
700010f8:	f04f 6300 	mov.w	r3, #134217728	; 0x8000000
700010fc:	ea43 1050 	orr.w	r0, r3, r0, lsr #5
70001100:	ea43 1151 	orr.w	r1, r3, r1, lsr #5
70001104:	fba0 3101 	umull	r3, r1, r0, r1
70001108:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
7000110c:	f5b1 0f00 	cmp.w	r1, #8388608	; 0x800000
70001110:	bf3e      	ittt	cc
70001112:	0049      	lslcc	r1, r1, #1
70001114:	ea41 71d3 	orrcc.w	r1, r1, r3, lsr #31
70001118:	005b      	lslcc	r3, r3, #1
7000111a:	ea40 0001 	orr.w	r0, r0, r1
7000111e:	f162 027f 	sbc.w	r2, r2, #127	; 0x7f
70001122:	2afd      	cmp	r2, #253	; 0xfd
70001124:	d81d      	bhi.n	70001162 <__aeabi_fmul+0x92>
70001126:	f1b3 4f00 	cmp.w	r3, #2147483648	; 0x80000000
7000112a:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
7000112e:	bf08      	it	eq
70001130:	f020 0001 	biceq.w	r0, r0, #1
70001134:	4770      	bx	lr
70001136:	f090 0f00 	teq	r0, #0
7000113a:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
7000113e:	bf08      	it	eq
70001140:	0249      	lsleq	r1, r1, #9
70001142:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
70001146:	ea40 2051 	orr.w	r0, r0, r1, lsr #9
7000114a:	3a7f      	subs	r2, #127	; 0x7f
7000114c:	bfc2      	ittt	gt
7000114e:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
70001152:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
70001156:	4770      	bxgt	lr
70001158:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
7000115c:	f04f 0300 	mov.w	r3, #0
70001160:	3a01      	subs	r2, #1
70001162:	dc5d      	bgt.n	70001220 <__aeabi_fmul+0x150>
70001164:	f112 0f19 	cmn.w	r2, #25
70001168:	bfdc      	itt	le
7000116a:	f000 4000 	andle.w	r0, r0, #2147483648	; 0x80000000
7000116e:	4770      	bxle	lr
70001170:	f1c2 0200 	rsb	r2, r2, #0
70001174:	0041      	lsls	r1, r0, #1
70001176:	fa21 f102 	lsr.w	r1, r1, r2
7000117a:	f1c2 0220 	rsb	r2, r2, #32
7000117e:	fa00 fc02 	lsl.w	ip, r0, r2
70001182:	ea5f 0031 	movs.w	r0, r1, rrx
70001186:	f140 0000 	adc.w	r0, r0, #0
7000118a:	ea53 034c 	orrs.w	r3, r3, ip, lsl #1
7000118e:	bf08      	it	eq
70001190:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
70001194:	4770      	bx	lr
70001196:	f092 0f00 	teq	r2, #0
7000119a:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
7000119e:	bf02      	ittt	eq
700011a0:	0040      	lsleq	r0, r0, #1
700011a2:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
700011a6:	3a01      	subeq	r2, #1
700011a8:	d0f9      	beq.n	7000119e <__aeabi_fmul+0xce>
700011aa:	ea40 000c 	orr.w	r0, r0, ip
700011ae:	f093 0f00 	teq	r3, #0
700011b2:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
700011b6:	bf02      	ittt	eq
700011b8:	0049      	lsleq	r1, r1, #1
700011ba:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
700011be:	3b01      	subeq	r3, #1
700011c0:	d0f9      	beq.n	700011b6 <__aeabi_fmul+0xe6>
700011c2:	ea41 010c 	orr.w	r1, r1, ip
700011c6:	e78f      	b.n	700010e8 <__aeabi_fmul+0x18>
700011c8:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
700011cc:	ea92 0f0c 	teq	r2, ip
700011d0:	bf18      	it	ne
700011d2:	ea93 0f0c 	teqne	r3, ip
700011d6:	d00a      	beq.n	700011ee <__aeabi_fmul+0x11e>
700011d8:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
700011dc:	bf18      	it	ne
700011de:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
700011e2:	d1d8      	bne.n	70001196 <__aeabi_fmul+0xc6>
700011e4:	ea80 0001 	eor.w	r0, r0, r1
700011e8:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
700011ec:	4770      	bx	lr
700011ee:	f090 0f00 	teq	r0, #0
700011f2:	bf17      	itett	ne
700011f4:	f090 4f00 	teqne	r0, #2147483648	; 0x80000000
700011f8:	4608      	moveq	r0, r1
700011fa:	f091 0f00 	teqne	r1, #0
700011fe:	f091 4f00 	teqne	r1, #2147483648	; 0x80000000
70001202:	d014      	beq.n	7000122e <__aeabi_fmul+0x15e>
70001204:	ea92 0f0c 	teq	r2, ip
70001208:	d101      	bne.n	7000120e <__aeabi_fmul+0x13e>
7000120a:	0242      	lsls	r2, r0, #9
7000120c:	d10f      	bne.n	7000122e <__aeabi_fmul+0x15e>
7000120e:	ea93 0f0c 	teq	r3, ip
70001212:	d103      	bne.n	7000121c <__aeabi_fmul+0x14c>
70001214:	024b      	lsls	r3, r1, #9
70001216:	bf18      	it	ne
70001218:	4608      	movne	r0, r1
7000121a:	d108      	bne.n	7000122e <__aeabi_fmul+0x15e>
7000121c:	ea80 0001 	eor.w	r0, r0, r1
70001220:	f000 4000 	and.w	r0, r0, #2147483648	; 0x80000000
70001224:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70001228:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
7000122c:	4770      	bx	lr
7000122e:	f040 40fe 	orr.w	r0, r0, #2130706432	; 0x7f000000
70001232:	f440 0040 	orr.w	r0, r0, #12582912	; 0xc00000
70001236:	4770      	bx	lr

70001238 <__aeabi_fdiv>:
70001238:	f04f 0cff 	mov.w	ip, #255	; 0xff
7000123c:	ea1c 52d0 	ands.w	r2, ip, r0, lsr #23
70001240:	bf1e      	ittt	ne
70001242:	ea1c 53d1 	andsne.w	r3, ip, r1, lsr #23
70001246:	ea92 0f0c 	teqne	r2, ip
7000124a:	ea93 0f0c 	teqne	r3, ip
7000124e:	d069      	beq.n	70001324 <__aeabi_fdiv+0xec>
70001250:	eba2 0203 	sub.w	r2, r2, r3
70001254:	ea80 0c01 	eor.w	ip, r0, r1
70001258:	0249      	lsls	r1, r1, #9
7000125a:	ea4f 2040 	mov.w	r0, r0, lsl #9
7000125e:	d037      	beq.n	700012d0 <__aeabi_fdiv+0x98>
70001260:	f04f 5380 	mov.w	r3, #268435456	; 0x10000000
70001264:	ea43 1111 	orr.w	r1, r3, r1, lsr #4
70001268:	ea43 1310 	orr.w	r3, r3, r0, lsr #4
7000126c:	f00c 4000 	and.w	r0, ip, #2147483648	; 0x80000000
70001270:	428b      	cmp	r3, r1
70001272:	bf38      	it	cc
70001274:	005b      	lslcc	r3, r3, #1
70001276:	f142 027d 	adc.w	r2, r2, #125	; 0x7d
7000127a:	f44f 0c00 	mov.w	ip, #8388608	; 0x800000
7000127e:	428b      	cmp	r3, r1
70001280:	bf24      	itt	cs
70001282:	1a5b      	subcs	r3, r3, r1
70001284:	ea40 000c 	orrcs.w	r0, r0, ip
70001288:	ebb3 0f51 	cmp.w	r3, r1, lsr #1
7000128c:	bf24      	itt	cs
7000128e:	eba3 0351 	subcs.w	r3, r3, r1, lsr #1
70001292:	ea40 005c 	orrcs.w	r0, r0, ip, lsr #1
70001296:	ebb3 0f91 	cmp.w	r3, r1, lsr #2
7000129a:	bf24      	itt	cs
7000129c:	eba3 0391 	subcs.w	r3, r3, r1, lsr #2
700012a0:	ea40 009c 	orrcs.w	r0, r0, ip, lsr #2
700012a4:	ebb3 0fd1 	cmp.w	r3, r1, lsr #3
700012a8:	bf24      	itt	cs
700012aa:	eba3 03d1 	subcs.w	r3, r3, r1, lsr #3
700012ae:	ea40 00dc 	orrcs.w	r0, r0, ip, lsr #3
700012b2:	011b      	lsls	r3, r3, #4
700012b4:	bf18      	it	ne
700012b6:	ea5f 1c1c 	movsne.w	ip, ip, lsr #4
700012ba:	d1e0      	bne.n	7000127e <__aeabi_fdiv+0x46>
700012bc:	2afd      	cmp	r2, #253	; 0xfd
700012be:	f63f af50 	bhi.w	70001162 <__aeabi_fmul+0x92>
700012c2:	428b      	cmp	r3, r1
700012c4:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
700012c8:	bf08      	it	eq
700012ca:	f020 0001 	biceq.w	r0, r0, #1
700012ce:	4770      	bx	lr
700012d0:	f00c 4c00 	and.w	ip, ip, #2147483648	; 0x80000000
700012d4:	ea4c 2050 	orr.w	r0, ip, r0, lsr #9
700012d8:	327f      	adds	r2, #127	; 0x7f
700012da:	bfc2      	ittt	gt
700012dc:	f1d2 03ff 	rsbsgt	r3, r2, #255	; 0xff
700012e0:	ea40 50c2 	orrgt.w	r0, r0, r2, lsl #23
700012e4:	4770      	bxgt	lr
700012e6:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
700012ea:	f04f 0300 	mov.w	r3, #0
700012ee:	3a01      	subs	r2, #1
700012f0:	e737      	b.n	70001162 <__aeabi_fmul+0x92>
700012f2:	f092 0f00 	teq	r2, #0
700012f6:	f000 4c00 	and.w	ip, r0, #2147483648	; 0x80000000
700012fa:	bf02      	ittt	eq
700012fc:	0040      	lsleq	r0, r0, #1
700012fe:	f410 0f00 	tsteq.w	r0, #8388608	; 0x800000
70001302:	3a01      	subeq	r2, #1
70001304:	d0f9      	beq.n	700012fa <__aeabi_fdiv+0xc2>
70001306:	ea40 000c 	orr.w	r0, r0, ip
7000130a:	f093 0f00 	teq	r3, #0
7000130e:	f001 4c00 	and.w	ip, r1, #2147483648	; 0x80000000
70001312:	bf02      	ittt	eq
70001314:	0049      	lsleq	r1, r1, #1
70001316:	f411 0f00 	tsteq.w	r1, #8388608	; 0x800000
7000131a:	3b01      	subeq	r3, #1
7000131c:	d0f9      	beq.n	70001312 <__aeabi_fdiv+0xda>
7000131e:	ea41 010c 	orr.w	r1, r1, ip
70001322:	e795      	b.n	70001250 <__aeabi_fdiv+0x18>
70001324:	ea0c 53d1 	and.w	r3, ip, r1, lsr #23
70001328:	ea92 0f0c 	teq	r2, ip
7000132c:	d108      	bne.n	70001340 <__aeabi_fdiv+0x108>
7000132e:	0242      	lsls	r2, r0, #9
70001330:	f47f af7d 	bne.w	7000122e <__aeabi_fmul+0x15e>
70001334:	ea93 0f0c 	teq	r3, ip
70001338:	f47f af70 	bne.w	7000121c <__aeabi_fmul+0x14c>
7000133c:	4608      	mov	r0, r1
7000133e:	e776      	b.n	7000122e <__aeabi_fmul+0x15e>
70001340:	ea93 0f0c 	teq	r3, ip
70001344:	d104      	bne.n	70001350 <__aeabi_fdiv+0x118>
70001346:	024b      	lsls	r3, r1, #9
70001348:	f43f af4c 	beq.w	700011e4 <__aeabi_fmul+0x114>
7000134c:	4608      	mov	r0, r1
7000134e:	e76e      	b.n	7000122e <__aeabi_fmul+0x15e>
70001350:	f030 4c00 	bics.w	ip, r0, #2147483648	; 0x80000000
70001354:	bf18      	it	ne
70001356:	f031 4c00 	bicsne.w	ip, r1, #2147483648	; 0x80000000
7000135a:	d1ca      	bne.n	700012f2 <__aeabi_fdiv+0xba>
7000135c:	f030 4200 	bics.w	r2, r0, #2147483648	; 0x80000000
70001360:	f47f af5c 	bne.w	7000121c <__aeabi_fmul+0x14c>
70001364:	f031 4300 	bics.w	r3, r1, #2147483648	; 0x80000000
70001368:	f47f af3c 	bne.w	700011e4 <__aeabi_fmul+0x114>
7000136c:	e75f      	b.n	7000122e <__aeabi_fmul+0x15e>
7000136e:	bf00      	nop

70001370 <__gesf2>:
70001370:	f04f 3cff 	mov.w	ip, #4294967295
70001374:	e006      	b.n	70001384 <__cmpsf2+0x4>
70001376:	bf00      	nop

70001378 <__lesf2>:
70001378:	f04f 0c01 	mov.w	ip, #1
7000137c:	e002      	b.n	70001384 <__cmpsf2+0x4>
7000137e:	bf00      	nop

70001380 <__cmpsf2>:
70001380:	f04f 0c01 	mov.w	ip, #1
70001384:	f84d cd04 	str.w	ip, [sp, #-4]!
70001388:	ea4f 0240 	mov.w	r2, r0, lsl #1
7000138c:	ea4f 0341 	mov.w	r3, r1, lsl #1
70001390:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70001394:	bf18      	it	ne
70001396:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
7000139a:	d011      	beq.n	700013c0 <__cmpsf2+0x40>
7000139c:	b001      	add	sp, #4
7000139e:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
700013a2:	bf18      	it	ne
700013a4:	ea90 0f01 	teqne	r0, r1
700013a8:	bf58      	it	pl
700013aa:	ebb2 0003 	subspl.w	r0, r2, r3
700013ae:	bf88      	it	hi
700013b0:	17c8      	asrhi	r0, r1, #31
700013b2:	bf38      	it	cc
700013b4:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
700013b8:	bf18      	it	ne
700013ba:	f040 0001 	orrne.w	r0, r0, #1
700013be:	4770      	bx	lr
700013c0:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700013c4:	d102      	bne.n	700013cc <__cmpsf2+0x4c>
700013c6:	ea5f 2c40 	movs.w	ip, r0, lsl #9
700013ca:	d105      	bne.n	700013d8 <__cmpsf2+0x58>
700013cc:	ea7f 6c23 	mvns.w	ip, r3, asr #24
700013d0:	d1e4      	bne.n	7000139c <__cmpsf2+0x1c>
700013d2:	ea5f 2c41 	movs.w	ip, r1, lsl #9
700013d6:	d0e1      	beq.n	7000139c <__cmpsf2+0x1c>
700013d8:	f85d 0b04 	ldr.w	r0, [sp], #4
700013dc:	4770      	bx	lr
700013de:	bf00      	nop

700013e0 <__aeabi_cfrcmple>:
700013e0:	4684      	mov	ip, r0
700013e2:	4608      	mov	r0, r1
700013e4:	4661      	mov	r1, ip
700013e6:	e7ff      	b.n	700013e8 <__aeabi_cfcmpeq>

700013e8 <__aeabi_cfcmpeq>:
700013e8:	b50f      	push	{r0, r1, r2, r3, lr}
700013ea:	f7ff ffc9 	bl	70001380 <__cmpsf2>
700013ee:	2800      	cmp	r0, #0
700013f0:	bf48      	it	mi
700013f2:	f110 0f00 	cmnmi.w	r0, #0
700013f6:	bd0f      	pop	{r0, r1, r2, r3, pc}

700013f8 <__aeabi_fcmpeq>:
700013f8:	f84d ed08 	str.w	lr, [sp, #-8]!
700013fc:	f7ff fff4 	bl	700013e8 <__aeabi_cfcmpeq>
70001400:	bf0c      	ite	eq
70001402:	2001      	moveq	r0, #1
70001404:	2000      	movne	r0, #0
70001406:	f85d fb08 	ldr.w	pc, [sp], #8
7000140a:	bf00      	nop

7000140c <__aeabi_fcmplt>:
7000140c:	f84d ed08 	str.w	lr, [sp, #-8]!
70001410:	f7ff ffea 	bl	700013e8 <__aeabi_cfcmpeq>
70001414:	bf34      	ite	cc
70001416:	2001      	movcc	r0, #1
70001418:	2000      	movcs	r0, #0
7000141a:	f85d fb08 	ldr.w	pc, [sp], #8
7000141e:	bf00      	nop

70001420 <__aeabi_fcmple>:
70001420:	f84d ed08 	str.w	lr, [sp, #-8]!
70001424:	f7ff ffe0 	bl	700013e8 <__aeabi_cfcmpeq>
70001428:	bf94      	ite	ls
7000142a:	2001      	movls	r0, #1
7000142c:	2000      	movhi	r0, #0
7000142e:	f85d fb08 	ldr.w	pc, [sp], #8
70001432:	bf00      	nop

70001434 <__aeabi_fcmpge>:
70001434:	f84d ed08 	str.w	lr, [sp, #-8]!
70001438:	f7ff ffd2 	bl	700013e0 <__aeabi_cfrcmple>
7000143c:	bf94      	ite	ls
7000143e:	2001      	movls	r0, #1
70001440:	2000      	movhi	r0, #0
70001442:	f85d fb08 	ldr.w	pc, [sp], #8
70001446:	bf00      	nop

70001448 <__aeabi_fcmpgt>:
70001448:	f84d ed08 	str.w	lr, [sp, #-8]!
7000144c:	f7ff ffc8 	bl	700013e0 <__aeabi_cfrcmple>
70001450:	bf34      	ite	cc
70001452:	2001      	movcc	r0, #1
70001454:	2000      	movcs	r0, #0
70001456:	f85d fb08 	ldr.w	pc, [sp], #8
7000145a:	bf00      	nop

7000145c <__aeabi_f2uiz>:
7000145c:	0042      	lsls	r2, r0, #1
7000145e:	d20e      	bcs.n	7000147e <__aeabi_f2uiz+0x22>
70001460:	f1b2 4ffe 	cmp.w	r2, #2130706432	; 0x7f000000
70001464:	d30b      	bcc.n	7000147e <__aeabi_f2uiz+0x22>
70001466:	f04f 039e 	mov.w	r3, #158	; 0x9e
7000146a:	ebb3 6212 	subs.w	r2, r3, r2, lsr #24
7000146e:	d409      	bmi.n	70001484 <__aeabi_f2uiz+0x28>
70001470:	ea4f 2300 	mov.w	r3, r0, lsl #8
70001474:	f043 4300 	orr.w	r3, r3, #2147483648	; 0x80000000
70001478:	fa23 f002 	lsr.w	r0, r3, r2
7000147c:	4770      	bx	lr
7000147e:	f04f 0000 	mov.w	r0, #0
70001482:	4770      	bx	lr
70001484:	f112 0f61 	cmn.w	r2, #97	; 0x61
70001488:	d101      	bne.n	7000148e <__aeabi_f2uiz+0x32>
7000148a:	0242      	lsls	r2, r0, #9
7000148c:	d102      	bne.n	70001494 <__aeabi_f2uiz+0x38>
7000148e:	f04f 30ff 	mov.w	r0, #4294967295
70001492:	4770      	bx	lr
70001494:	f04f 0000 	mov.w	r0, #0
70001498:	4770      	bx	lr
7000149a:	bf00      	nop
