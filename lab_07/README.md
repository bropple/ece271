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
- [X] Something cool (3 points): LCD and Joystick

What is your something cool?
The LCD Displays the mode the board is in (LED, MOTOR, or JOYCLK), and after the LED and MOTOR functions finish, you
can toggle between 90, -90, and 0 degrees using the center joystick button in JOYCLK mode.

Post-lab Questions
1) You would set the counting mode to up-counting, set PSC to 2999. (16M/PSC+1) then equals 5333. so ARR = 5333,
so then ARR*1/(5333)=1Hz. CRR equals 1/2 ARR, so it equals about 1500.

2) The smallest PWM frequency that can be generated is 0.003725 Hz.
   (16M/1+65539) = 244.16 Hz
   (1+65539) * (1/244.126) = 268.468
   1/268.468 = 0.003725 Hz = smallest possible frequency.

Lab Credits
-------
* Did you received any help from someone other than Prof. Zhu and lab teaching assistants?
Lily Bragg helped me out a lot with this lab.

Suggestions and Comments
-------
* Report typos, errors, or suggestions into the "typos" session on piazza site (https://piazza.com/maine/spring2018/ece271)
* I offer one dollar each new typo or error in the 3rd edition.
