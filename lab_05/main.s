;Ben Ropple
;2/25/2018
;Lab 5
;Objective: Rewrite Lab 4 in Assembly.
;			Make the motor rotate 360 degrees.

	INCLUDE core_cm4_constants.s		; Load Cortex-M4 Definitions
	INCLUDE stm32l476xx_constants.s     ; Load STM32L4 Definitions 

	AREA    main, CODE, READONLY
	EXPORT	__main				; make __main visible to linker
	IMPORT LCD_Initialization
	IMPORT MotorKey
	ALIGN
	ENTRY			
				
__main	PROC
	
		; Enable the clock to GPIO Port B	
		LDR r0, =RCC_BASE
		LDR r1, [r0, #RCC_AHB2ENR]
		ORR r1, r1, #RCC_AHB2ENR_GPIOBEN
		STR r1, [r0, #RCC_AHB2ENR]

		; MODE: 00: Input mode,              01: General purpose output mode
		;       10: Alternate function mode, 11: Analog mode (reset state)
		LDR r0, =GPIOB_BASE
		LDR r1, [r0, #GPIO_MODER]
		
		;Set GPIOB's Mode Register
		AND r1, #0
		ORR r1, r1, #GPIO_MODER_MODER2_0
		ORR r1, r1, #GPIO_MODER_MODER3_0
		ORR r1, r1, #GPIO_MODER_MODER6_0
		ORR r1, r1, #GPIO_MODER_MODER7_0
		STR r1, [r0, #GPIO_MODER]
		
		BL LCD_Initialization

keypad	MOV r0, #0
		BL	MotorKey
		MOV r2, r0 ;output of MotorKey
		MOV r3, #0
		MOV r4, #0
		MOV r5, #0
		MOV r6, #0
		MOV r7, #0
		LDR r0, =GPIOB_BASE

fstep
loop1	CMP r3, r2 ;outer loop
		BGT end3
		
loop2	CMP r4, #3 ;FullStepper
		BGT end2

loop3	CMP r5, #2000 ;delay1
		BGT end1
		ADD r5, r5, #1
		B loop3
		
loop4	CMP	r6, #200 ;delay2
		BGT loop3
		ADD r6, r6, #1
		B loop4
		
end1	LDR r1, [r0, #GPIO_ODR]
		AND r1, r1, #0
		STR r1, [r0, #GPIO_ODR]
		MOV r5, #0 ;reset delay
		MOV r6, #0 
		CMP r4, #0
		BNE else1
		
if1		LDR r1, [r0, #GPIO_ODR]
		ORR r1, r1, #GPIO_ODR_ODR_2
		ORR r1, r1, #GPIO_ODR_ODR_7
		STR r1, [r0, #GPIO_ODR]
		
else1	CMP r4, #1
		BNE else2
		
if2		LDR r1, [r0, #GPIO_ODR]
		ORR r1, r1, #GPIO_ODR_ODR_2
		ORR r1, r1, #GPIO_ODR_ODR_6
		STR r1, [r0, #GPIO_ODR]
		
else2	CMP r4, #2
		BNE else3
		
if3		LDR r1, [r0, #GPIO_ODR]	;If r4 == 0, set ODR 6 and 3
		ORR r1, r1, #GPIO_ODR_ODR_6
		ORR r1, r1, #GPIO_ODR_ODR_3
		STR r1, [r0, #GPIO_ODR]
		
else3	CMP r4, #3
		BNE else4
		
if4		LDR r1, [r0, #GPIO_ODR]
		ORR r1, r1, #GPIO_ODR_ODR_3
		ORR r1, r1, #GPIO_ODR_ODR_7
		STR r1, [r0, #GPIO_ODR]
		
else4	ADD r4, r4, #1
		B loop2

end2	MOV r4, #0
		ADD r3, r3, #1
		B loop1

end3	MOV r3, #0
		LDR r1, [r0, #GPIO_ODR]
		AND r1, r1, #0
		STR r1, [r0, #GPIO_ODR]
	
		B keypad

stop 	B 		stop     		; dead loop & program hangs here

	ENDP
					
	ALIGN			

	AREA    myData, DATA, READWRITE
	ALIGN
array	DCD   1, 2, 3, 4
	END
		