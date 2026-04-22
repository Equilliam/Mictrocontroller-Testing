.global start
.global blink

.include "./m328Pdef.inc"
.def temp = r16
.equ dlyconstant = 500000

.org $0000 jmp RESET
main:
RESET:
    ldi temp, high (RAMEND)
    out SPH, temp
    ldi temp, low (RAMEND)
    out SPL, temp

    ldi temp, 0b000000001
    out DDRB, temp

MAIN:
    sbi PortB, 0
    rcall dlyconstantcbi PortB, 0
    rcall DLY 
    rjmp MAIN

DLY:
    ldi r17, byte3 (dlyconstant)
    ldi r18, high (dlyconstant)
    ldi r19, low (dlyconstant)

    sub1 r17, 1
    sbci r18, 0
    sbci r19, 0
    brcc pc-3

    ret 

