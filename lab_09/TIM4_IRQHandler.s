	INCLUDE core_cm4_constants.s		; Load Cortex-M4 Definitions
	INCLUDE stm32l476xx_constants.s     ; Load STM32L4 Definitions 

	AREA	handler, CODE
	EXPORT	TIM4_IRQHandler
	EXPORT	timespan
	EXPORT	lastCounter
	EXPORT	overflow
	ALIGN		

TIM4_IRQHandler PROC
					
				PUSH {r4, r6, r10, lr}
				
				LDR r0, =TIM4_BASE		
				LDR r2, [r0, #TIM_SR]	
				AND r3, r2, #TIM_SR_UIF	; Check update flag
				CBZ r3, check_CCFlag	; Branch if zero
				
				LDR r3, =overflow
				LDR r1, [r3]			; Load overflow
				ADD r1, r1, #1			; Increment overflow counter
				STR r1, [r3]			; Store overflow
				
				BIC r2, r2, #TIM_SR_UIF	; Clear update flag
				STR r2, [r0, #TIM_SR]	; Update status register
			
check_CCFlag	AND r2, r2, #TIM_SR_CC1IF ; Check capture flag
				CBZ r2, exit			; Branch if zero
				
				LDR r0, =TIM4_BASE		; Load base mem address
				LDR r1, [r0, #TIM_CCR1]	; Read new value
				
				LDR r2, =lastCounter
				LDR r0, [r2]			; Load last counter value
				STR r1, [r2]			; Store new counter value
				CBZ r0, clearOverflow	; Branch if zero
				
				LDR r3, =overflow
				LDR r4, [r3]			; Load overflow value
				LSL r4, r4, #16			; Mult. by 2^16
				ADD r6, r1, r4
				SUB r10, r6, r0			
				LDR r2, =timespan
				STR r10, [r2]			; Update timespan
				
clearOverflow 	MOV r0, #0
				LDR r3, =overflow
				STR r0, [r3]			; Clear overflow
exit			POP {r4, r6, r10, pc}
				ENDP
					
		ALIGN			

		AREA    myData, DATA, READWRITE
		ALIGN
array	DCD    1, 2, 3, 4
timespan	DCD	0
lastCounter	DCD	0
overflow	DCD	0
		END
