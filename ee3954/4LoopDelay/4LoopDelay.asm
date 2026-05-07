;=========================================================
; 75-Minute Delay Subroutine
; Device: PIC16F18875
; Fosc = 4 MHz  →  1 µs instruction cycle
;=========================================================

Delay75min:

        movlw   d'255'
        movwf   L4              ; Outer loop

Loop4:
        movlw   d'255'
        movwf   L3

Loop3:
        movlw   d'255'
        movwf   L2

Loop2:
        movlw   d'255'
        movwf   L1

Loop1:
        decfsz  L1, f           ; 1 cycle (2 when zero)
        goto    Loop1           ; 2 cycles

        decfsz  L2, f
        goto    Loop2

        decfsz  L3, f
        goto    Loop3

        decfsz  L4, f
        goto    Loop4

        return
