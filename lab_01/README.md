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
When I press the UP button, it says "Hello World" in morse code.

Post-lab Questions
1) The hardware debouncing circuit is an RC circuit: there is a capacitor in series with the button
itself, which filters out high frequencies. The capacitor is charged when the button is not pressed,
and discharges when the button is pressed. When the button is released again, the capacitor doesn't
have enough time to recharge, so it can't bring the processor pin to a low voltage. This stops the
'bounce', and makes the button perform as expected.

2) A counter debouncer is a typical solution for software debouncing. This method scans for the button
press and needs several positive readings before confirming whether or not the button is pressed.

3) The low-speed setting is recommended for controlling the LEDs because high-speed can cause
interference in other circuits on the board. The large amplitude and sharp edges of the high-speed
setting can cause malfunctions through induction or conduction, which can make the circuit behave
unexpectedly.

Lab Credits
-------
* Did you received any help from someone other than Prof. Zhu and lab teaching assistants?
Lily Bragg and Austin Stover helped me quite a bit.

Suggestions and Comments
-------
* Report typos, errors, or suggestions into the "typos" session on piazza site (https://piazza.com/maine/spring2018/ece271)
* I offer one dollar each new typo or error in the 3rd edition.
