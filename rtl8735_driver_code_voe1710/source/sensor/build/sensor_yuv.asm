
sensor.axf:     file format elf32-littlearm


Disassembly of section .sensor:

70000040 <sensor_entry>:
70000040:	b1 01 00 70 6d 00 00 70                             ...pm..p

70000048 <voe_ops>:
70000048:	00 00 00 00                                         ....

7000004c <g_status>:
	...

7000006c <rts_isp_set_voe_ops>:
7000006c:	4b01      	ldr	r3, [pc, #4]	; (70000074 <rts_isp_set_voe_ops+0x8>)
7000006e:	6018      	str	r0, [r3, #0]
70000070:	4770      	bx	lr
70000072:	bf00      	nop
70000074:	70000048 	.word	0x70000048

70000078 <isp_driver_is_fpga>:
70000078:	2000      	movs	r0, #0
7000007a:	4770      	bx	lr

7000007c <YUV_SENSOR_get_info>:
7000007c:	bb80      	cbnz	r0, 700000e0 <YUV_SENSOR_get_info+0x64>
7000007e:	b379      	cbz	r1, 700000e0 <YUV_SENSOR_get_info+0x64>
70000080:	4b19      	ldr	r3, [pc, #100]	; (700000e8 <YUV_SENSOR_get_info+0x6c>)
70000082:	f44f 62a0 	mov.w	r2, #1280	; 0x500
70000086:	7108      	strb	r0, [r1, #4]
70000088:	610b      	str	r3, [r1, #16]
7000008a:	f44f 7334 	mov.w	r3, #720	; 0x2d0
7000008e:	f881 0098 	strb.w	r0, [r1, #152]	; 0x98
70000092:	f881 008c 	strb.w	r0, [r1, #140]	; 0x8c
70000096:	f881 02d8 	strb.w	r0, [r1, #728]	; 0x2d8
7000009a:	f8c1 02dc 	str.w	r0, [r1, #732]	; 0x2dc
7000009e:	e9c1 2302 	strd	r2, r3, [r1, #8]
700000a2:	4a12      	ldr	r2, [pc, #72]	; (700000ec <YUV_SENSOR_get_info+0x70>)
700000a4:	2301      	movs	r3, #1
700000a6:	7812      	ldrb	r2, [r2, #0]
700000a8:	600b      	str	r3, [r1, #0]
700000aa:	f881 2084 	strb.w	r2, [r1, #132]	; 0x84
700000ae:	f241 3288 	movw	r2, #5000	; 0x1388
700000b2:	f8c1 309c 	str.w	r3, [r1, #156]	; 0x9c
700000b6:	f8c1 20a0 	str.w	r2, [r1, #160]	; 0xa0
700000ba:	2248      	movs	r2, #72	; 0x48
700000bc:	f8c1 32d4 	str.w	r3, [r1, #724]	; 0x2d4
700000c0:	f881 2085 	strb.w	r2, [r1, #133]	; 0x85
700000c4:	f44f 7281 	mov.w	r2, #258	; 0x102
700000c8:	f8a1 2086 	strh.w	r2, [r1, #134]	; 0x86
700000cc:	2202      	movs	r2, #2
700000ce:	f8c1 2088 	str.w	r2, [r1, #136]	; 0x88
700000d2:	f44f 727a 	mov.w	r2, #1000	; 0x3e8
700000d6:	e9c1 0024 	strd	r0, r0, [r1, #144]	; 0x90
700000da:	f8c1 22e0 	str.w	r2, [r1, #736]	; 0x2e0
700000de:	4770      	bx	lr
700000e0:	f06f 0015 	mvn.w	r0, #21
700000e4:	4770      	bx	lr
700000e6:	bf00      	nop
700000e8:	41f00000 	.word	0x41f00000
700000ec:	7000004c 	.word	0x7000004c

700000f0 <YUV_SENSOR_get_init_info>:
700000f0:	b570      	push	{r4, r5, r6, lr}
700000f2:	460b      	mov	r3, r1
700000f4:	4614      	mov	r4, r2
700000f6:	4605      	mov	r5, r0
700000f8:	b110      	cbz	r0, 70000100 <YUV_SENSOR_get_init_info+0x10>
700000fa:	f06f 0015 	mvn.w	r0, #21
700000fe:	bd70      	pop	{r4, r5, r6, pc}
70000100:	2a00      	cmp	r2, #0
70000102:	d0fa      	beq.n	700000fa <YUV_SENSOR_get_init_info+0xa>
70000104:	780a      	ldrb	r2, [r1, #0]
70000106:	4e19      	ldr	r6, [pc, #100]	; (7000016c <YUV_SENSOR_get_init_info+0x7c>)
70000108:	4919      	ldr	r1, [pc, #100]	; (70000170 <YUV_SENSOR_get_init_info+0x80>)
7000010a:	68d8      	ldr	r0, [r3, #12]
7000010c:	7032      	strb	r2, [r6, #0]
7000010e:	f000 f8e1 	bl	700002d4 <__aeabi_fcmpeq>
70000112:	2800      	cmp	r0, #0
70000114:	d0f1      	beq.n	700000fa <YUV_SENSOR_get_init_info+0xa>
70000116:	2302      	movs	r3, #2
70000118:	f44f 62a0 	mov.w	r2, #1280	; 0x500
7000011c:	f44f 61fa 	mov.w	r1, #2000	; 0x7d0
70000120:	4628      	mov	r0, r5
70000122:	f884 3064 	strb.w	r3, [r4, #100]	; 0x64
70000126:	f240 4303 	movw	r3, #1027	; 0x403
7000012a:	f884 5076 	strb.w	r5, [r4, #118]	; 0x76
7000012e:	f8a4 3068 	strh.w	r3, [r4, #104]	; 0x68
70000132:	2304      	movs	r3, #4
70000134:	f884 3060 	strb.w	r3, [r4, #96]	; 0x60
70000138:	f44f 7384 	mov.w	r3, #264	; 0x108
7000013c:	f8a4 3074 	strh.w	r3, [r4, #116]	; 0x74
70000140:	f44f 7334 	mov.w	r3, #720	; 0x2d0
70000144:	e9c4 2320 	strd	r2, r3, [r4, #128]	; 0x80
70000148:	4b0a      	ldr	r3, [pc, #40]	; (70000174 <YUV_SENSOR_get_init_info+0x84>)
7000014a:	e9c4 3124 	strd	r3, r1, [r4, #144]	; 0x90
7000014e:	f240 23ee 	movw	r3, #750	; 0x2ee
70000152:	6073      	str	r3, [r6, #4]
70000154:	f8c4 3098 	str.w	r3, [r4, #152]	; 0x98
70000158:	f642 33f2 	movw	r3, #11250	; 0x2bf2
7000015c:	f8c4 309c 	str.w	r3, [r4, #156]	; 0x9c
70000160:	4b05      	ldr	r3, [pc, #20]	; (70000178 <YUV_SENSOR_get_init_info+0x88>)
70000162:	e9c4 5522 	strd	r5, r5, [r4, #136]	; 0x88
70000166:	60b3      	str	r3, [r6, #8]
70000168:	e7c9      	b.n	700000fe <YUV_SENSOR_get_init_info+0xe>
7000016a:	bf00      	nop
7000016c:	7000004c 	.word	0x7000004c
70000170:	41f00000 	.word	0x41f00000
70000174:	055d4a80 	.word	0x055d4a80
70000178:	41b1c71c 	.word	0x41b1c71c

7000017c <YUV_SENSOR_start>:
7000017c:	b918      	cbnz	r0, 70000186 <YUV_SENSOR_start+0xa>
7000017e:	4b03      	ldr	r3, [pc, #12]	; (7000018c <YUV_SENSOR_start+0x10>)
70000180:	2200      	movs	r2, #0
70000182:	60da      	str	r2, [r3, #12]
70000184:	4770      	bx	lr
70000186:	f06f 0015 	mvn.w	r0, #21
7000018a:	4770      	bx	lr
7000018c:	7000004c 	.word	0x7000004c

70000190 <YUV_SENSOR_get_tuned_again>:
70000190:	2000      	movs	r0, #0
70000192:	4770      	bx	lr

70000194 <YUV_SENSOR_get_exposure_gain_info>:
70000194:	2000      	movs	r0, #0
70000196:	4770      	bx	lr

70000198 <YUV_SENSOR_get_tuned_dgain>:
70000198:	2000      	movs	r0, #0
7000019a:	4770      	bx	lr

7000019c <clip_d_word>:
7000019c:	4603      	mov	r3, r0
7000019e:	4610      	mov	r0, r2
700001a0:	4293      	cmp	r3, r2
700001a2:	d803      	bhi.n	700001ac <clip_d_word+0x10>
700001a4:	428b      	cmp	r3, r1
700001a6:	bf38      	it	cc
700001a8:	460b      	movcc	r3, r1
700001aa:	4618      	mov	r0, r3
700001ac:	4770      	bx	lr
	...

700001b0 <rts_isp_get_sensor_ops>:
700001b0:	4800      	ldr	r0, [pc, #0]	; (700001b4 <rts_isp_get_sensor_ops+0x4>)
700001b2:	4770      	bx	lr
700001b4:	700001b8 	.word	0x700001b8

700001b8 <YUV_SENSOR_ops>:
700001b8:	73000005 5f565559 534e4553 0000524f     ...sYUV_SENSOR..
	...
700001dc:	7000007d 700000f1 00000000 70000191     }..p...p.......p
700001ec:	70000199 70000195 00000000 00000000     ...p...p........
700001fc:	7000017d 00000000 00000000 00000000     }..p............
	...

7000024c <__gesf2>:
7000024c:	f04f 3cff 	mov.w	ip, #4294967295
70000250:	e006      	b.n	70000260 <__cmpsf2+0x4>
70000252:	bf00      	nop

70000254 <__lesf2>:
70000254:	f04f 0c01 	mov.w	ip, #1
70000258:	e002      	b.n	70000260 <__cmpsf2+0x4>
7000025a:	bf00      	nop

7000025c <__cmpsf2>:
7000025c:	f04f 0c01 	mov.w	ip, #1
70000260:	f84d cd04 	str.w	ip, [sp, #-4]!
70000264:	ea4f 0240 	mov.w	r2, r0, lsl #1
70000268:	ea4f 0341 	mov.w	r3, r1, lsl #1
7000026c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
70000270:	bf18      	it	ne
70000272:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
70000276:	d011      	beq.n	7000029c <__cmpsf2+0x40>
70000278:	b001      	add	sp, #4
7000027a:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
7000027e:	bf18      	it	ne
70000280:	ea90 0f01 	teqne	r0, r1
70000284:	bf58      	it	pl
70000286:	ebb2 0003 	subspl.w	r0, r2, r3
7000028a:	bf88      	it	hi
7000028c:	17c8      	asrhi	r0, r1, #31
7000028e:	bf38      	it	cc
70000290:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
70000294:	bf18      	it	ne
70000296:	f040 0001 	orrne.w	r0, r0, #1
7000029a:	4770      	bx	lr
7000029c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
700002a0:	d102      	bne.n	700002a8 <__cmpsf2+0x4c>
700002a2:	ea5f 2c40 	movs.w	ip, r0, lsl #9
700002a6:	d105      	bne.n	700002b4 <__cmpsf2+0x58>
700002a8:	ea7f 6c23 	mvns.w	ip, r3, asr #24
700002ac:	d1e4      	bne.n	70000278 <__cmpsf2+0x1c>
700002ae:	ea5f 2c41 	movs.w	ip, r1, lsl #9
700002b2:	d0e1      	beq.n	70000278 <__cmpsf2+0x1c>
700002b4:	f85d 0b04 	ldr.w	r0, [sp], #4
700002b8:	4770      	bx	lr
700002ba:	bf00      	nop

700002bc <__aeabi_cfrcmple>:
700002bc:	4684      	mov	ip, r0
700002be:	4608      	mov	r0, r1
700002c0:	4661      	mov	r1, ip
700002c2:	e7ff      	b.n	700002c4 <__aeabi_cfcmpeq>

700002c4 <__aeabi_cfcmpeq>:
700002c4:	b50f      	push	{r0, r1, r2, r3, lr}
700002c6:	f7ff ffc9 	bl	7000025c <__cmpsf2>
700002ca:	2800      	cmp	r0, #0
700002cc:	bf48      	it	mi
700002ce:	f110 0f00 	cmnmi.w	r0, #0
700002d2:	bd0f      	pop	{r0, r1, r2, r3, pc}

700002d4 <__aeabi_fcmpeq>:
700002d4:	f84d ed08 	str.w	lr, [sp, #-8]!
700002d8:	f7ff fff4 	bl	700002c4 <__aeabi_cfcmpeq>
700002dc:	bf0c      	ite	eq
700002de:	2001      	moveq	r0, #1
700002e0:	2000      	movne	r0, #0
700002e2:	f85d fb08 	ldr.w	pc, [sp], #8
700002e6:	bf00      	nop

700002e8 <__aeabi_fcmplt>:
700002e8:	f84d ed08 	str.w	lr, [sp, #-8]!
700002ec:	f7ff ffea 	bl	700002c4 <__aeabi_cfcmpeq>
700002f0:	bf34      	ite	cc
700002f2:	2001      	movcc	r0, #1
700002f4:	2000      	movcs	r0, #0
700002f6:	f85d fb08 	ldr.w	pc, [sp], #8
700002fa:	bf00      	nop

700002fc <__aeabi_fcmple>:
700002fc:	f84d ed08 	str.w	lr, [sp, #-8]!
70000300:	f7ff ffe0 	bl	700002c4 <__aeabi_cfcmpeq>
70000304:	bf94      	ite	ls
70000306:	2001      	movls	r0, #1
70000308:	2000      	movhi	r0, #0
7000030a:	f85d fb08 	ldr.w	pc, [sp], #8
7000030e:	bf00      	nop

70000310 <__aeabi_fcmpge>:
70000310:	f84d ed08 	str.w	lr, [sp, #-8]!
70000314:	f7ff ffd2 	bl	700002bc <__aeabi_cfrcmple>
70000318:	bf94      	ite	ls
7000031a:	2001      	movls	r0, #1
7000031c:	2000      	movhi	r0, #0
7000031e:	f85d fb08 	ldr.w	pc, [sp], #8
70000322:	bf00      	nop

70000324 <__aeabi_fcmpgt>:
70000324:	f84d ed08 	str.w	lr, [sp, #-8]!
70000328:	f7ff ffc8 	bl	700002bc <__aeabi_cfrcmple>
7000032c:	bf34      	ite	cc
7000032e:	2001      	movcc	r0, #1
70000330:	2000      	movcs	r0, #0
70000332:	f85d fb08 	ldr.w	pc, [sp], #8
70000336:	bf00      	nop
