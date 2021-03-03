ECE 271 Microcomputer Architecture and Applications
University of Maine
Spring 2018     

Name
-----------
```
Ben Ropple
```

Summary of Lab Status
-------
- [X] Pre-lab Assignment (2 points) 
- [X] Basic in-lab assignments (15 points)
- [X] Something cool (3 points)

What is your something cool?
The RIGHT and UP keys on the joystick play different animations on the LCD. The center button calls
the DisplayName function.

Post-lab Questions
1) It would need 30 pins to drive the LCD, not including the COM terminals. Each SEG line drives
4 segments, which are compared to the COM terminals to determine whether or not the segment is on.

2) No, a GPIO Pin can only perform one function at any given time, as it is set to a specific 
function in the MODE register.

3) The LCD driver for the screen on the board is built in to the processor. The COM driver controls
the SEG drivers. The number of COM drivers in comparison to the number of SEG drivers active
determines the duty ratio. For instance, if there's 4 SEG terminals for every one COM, then it's
1/4 duty ratio.

4) The processor can drive the LCD display with up to 8 common terminals and 44 segment terminals
 with either a maximum of 176 (44 SEG and 4 COM) or 320 (40x8) pixels. The LCD RAM has 16 x 32-bit
registers for storing pixel information.

5) The LCD has 96 pixels on our board. Not all of the LCD ram is available because some of 
it is reserved.

Lab Credits
-------
* Did you received any help from someone other than Prof. Zhu and lab teaching assistants?
Lily Bragg helped me understand the LCD initialization.

Suggestions and Comments
-------
* Report typos, errors, or suggestions into the "typos" session on piazza site (https://piazza.com/maine/spring2018/ece271)
* I offer one dollar each new typo or error in the 3rd edition.
