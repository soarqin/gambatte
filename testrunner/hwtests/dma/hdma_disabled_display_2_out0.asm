.size 8000

.code@48
	jp lstatint

.code@100
	jp lbegin

.data@143
	c0

.code@150
lbegin:
	ld c, 44
	ld b, 97
lbegin_waitly97:
	ldff a, (c)
	cmp a, b
	jpnz lbegin_waitly97
	ld a, 99
	ldff(45), a
	ld a, 40
	ldff(41), a
	ld a, 00
	ld(8000), a
	ld a, 01
	ld(c000), a
	ld a, bf
	ldff(51), a
	ld a, f0
	ldff(52), a
	ldff(54), a
	ld a, 9f
	ldff(53), a
	xor a, a
	ldff(0f), a
	ld a, 02
	ldff(ff), a
	ei
	ld hl, 8000
	halt

.code@1000
lstatint:
	xor a, a
	ldff(40), a
	ld b, 07
	ld a, 81
	ldff(55), a

.code@1200
	ld a, (hl)
	and a, b
	ld(ff80), a
	ld a, 91
	ldff(40), a
	jp lprintff80

.code@7000
lprintff80:
	ld c, 44
	ld b, 91
lprintff80_waitvblank:
	ldff a, (c)
	cmp a, b
	jrnz lprintff80_waitvblank
	xor a, a
	ldff(40), a
	ld bc, 7a00
	ld hl, 8000
	ld d, a0
lprintff80_copytiles:
	ld a, (bc)
	inc bc
	ld(hl++), a
	dec d
	jrnz lprintff80_copytiles
	ld a, c0
	ldff(47), a
	ld a, 80
	ldff(68), a
	ld a, ff
	ldff(69), a
	ldff(69), a
	ldff(69), a
	ldff(69), a
	ldff(69), a
	ldff(69), a
	ld a, 00
	ldff(69), a
	ldff(69), a
	ldff a, (80)
	ld(9800), a
	xor a, a
	ldff(43), a
	ld a, 91
	ldff(40), a
lprintff80_limbo:
	jr lprintff80_limbo

.data@7a00
	00 00 7f 7f 41 41 41 41
	41 41 41 41 41 41 7f 7f
	00 00 08 08 08 08 08 08
	08 08 08 08 08 08 08 08
	00 00 7f 7f 01 01 01 01
	7f 7f 40 40 40 40 7f 7f
	00 00 7f 7f 01 01 01 01
	3f 3f 01 01 01 01 7f 7f
	00 00 41 41 41 41 41 41
	7f 7f 01 01 01 01 01 01
	00 00 7f 7f 40 40 40 40
	7e 7e 01 01 01 01 7e 7e
	00 00 7f 7f 40 40 40 40
	7f 7f 41 41 41 41 7f 7f
	00 00 7f 7f 01 01 02 02
	04 04 08 08 10 10 10 10
	00 00 3e 3e 41 41 41 41
	3e 3e 41 41 41 41 3e 3e
	00 00 7f 7f 41 41 41 41
	7f 7f 01 01 01 01 7f 7f

