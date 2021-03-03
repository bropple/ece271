; Ben Ropple
; 4/16/2018
; Lab 9
; Ultrasonic Sensor in Assembly
; Clock Frequency: 32KHz

	INCLUDE core_cm4_constants.s		; Load Cortex-M4 Definitions
	INCLUDE stm32l476xx_constants.s     ; Load STM32L4 Definitions 

	AREA    main, CODE
	EXPORT	__main				; make __main visible to linker
	IMPORT	timespan
	IMPORT	TIM4_init
	IMPORT	TIM4_IRQHandler
	IMPORT	lastCounter
	IMPORT	overflow
	IMPORT	printLCD
	IMPORT	GPIO_init
	IMPORT	HSI_init
	IMPORT	itoa
	IMPORT	LCD_Initialization
	ALIGN
	ENTRY			
				
__main	PROC
		
		BL HSI_init						;Initialize HSI, GPIO, TIM4, and LCD
		BL GPIO_init					
		BL TIM4_init					
		BL LCD_Initialization			
		
loop	MOV r7, #0
		MOV r8, #0
		
count2	ADD	r7, r7, #1					;Delay
		CMP	r7, #600
		BLE	count2
		ADD	r8, r8, #1
		CMP r8, #600
		BLE count2
		LDR r0, =GPIOE_BASE				;Trigger 
		LDR r1, [r0, #GPIO_ODR]
		ORR r1, r1, #GPIO_ODR_ODR_11
		STR r1, [r0, #GPIO_ODR]
		
		MOV r7, #0
		MOV r8, #0
		
count1	ADD	r7, r7, #1					;Delay
		CMP	r7, #600
		BLE	count1
		ADD	r8, r8, #1
		CMP r8, #600
		BLE count1
		LDR r0, =GPIOE_BASE				;Trigger
		LDR r1, [r0, #GPIO_ODR]
		BIC r1, r1, #GPIO_ODR_ODR_11
		STR r1, [r0, #GPIO_ODR]
		LDR	r0, [r1]
		BL printLCD						;Display Distance on the LCD
		B loop		;repeat forever
		
stop 	B 		stop     ; dead loop & program hangs here
			
		ENDP
					
		ALIGN			

		AREA    myData, DATA, READWRITE
		ALIGN
array	DCD    1, 2, 3, 4
		END
