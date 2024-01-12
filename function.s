.syntax unified
.cpu cortex-m4
.thumb

.section .text
.global disco_lights
.type disco_lights, %function

disco_lights:
    push {r4-r11, lr}        @ Save registers and the link register

    @ Initialize GPIO pins to output for the RGB LED
    ldr r1, =0x4004B000      @ Base address of PORTC (For Red LED)
    ldr r0, =0x400FF080      @ Base address of GPIOC
    movs r2, #(1 << 9)       @ LED mask for PTC9 (Red)
    str r2, [r1, #4]         @ Set PTC9 to output in PDDR
    bic r2, r2               @ Clear the bit to turn off the Red LED
    str r2, [r0, #4]         @ Apply to PDOR

    ldr r1, =0x4004D000      @ Base address of PORTE (For Green LED)
    ldr r0, =0x400FF100      @ Base address of GPIOE
    movs r3, #(1 << 6)       @ LED mask for PTE6 (Green)
    str r3, [r1, #4]         @ Set PTE6 to output in PDDR
    bic r3, r3               @ Clear the bit to turn off the Green LED
    str r3, [r0, #4]         @ Apply to PDOR

    ldr r1, =0x40049000      @ Base address of PORTA (For Blue LED)
    ldr r0, =0x400FF040      @ Base address of GPIOA
    movs r4, #(1 << 11)      @ LED mask for PTA11 (Blue)
    str r4, [r1, #4]         @ Set PTA11 to output in PDDR
    bic r4, r4               @ Clear the bit to turn off the Blue LED
    str r4, [r0, #4]         @ Apply to PDOR

    mov r5, #250             @number of iteration

disco_loop:
    @ Toggle Red LED
    ldr r0, =0x400FF080
    ldr r2, [r0]
    eors r2, r2, #(1 << 9)
    str r2, [r0]
    movs r0, #1              @ Argument for delay_ms
    bl delay_ms              @ Call delay_ms

    @ Toggle Green LED
    ldr r0, =0x400FF100
    ldr r3, [r0]
    eors r3, r3, #(1 << 6)
    str r3, [r0]
    movs r0, #1              @ Argument for delay_ms
    bl delay_ms              @ Call delay_ms

    @ Toggle Blue LED
    ldr r0, =0x400FF040
    ldr r4, [r0]
    eors r4, r4, #(1 << 11)
    str r4, [r0]
    movs r0, #1              @ Argument for delay_ms
    bl delay_ms              @ Call delay_ms

    @ Decrement the loop counter and check if we're done
    subs r5, r5, #1
    bne disco_loop

    @ Turn all LEDs off before exiting
    ldr r0, =0x400FF080
    ldr r2, [r0]
    orrs r2, r2, #(1 << 9)
    str r2, [r0]

    ldr r0, =0x400FF100
    ldr r3, [r0]
    orrs r3, r3, #(1 << 6)
    str r3, [r0]

    ldr r0, =0x400FF040
    ldr r4, [r0]
    orrs r4, r4, #(1 << 11)
    str r4, [r0]

    pop {r4-r11, pc}         @ Restore registers and return
