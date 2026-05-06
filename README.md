# Arduino-Based-Reaction-Game
A simple 2 player reaction-based game (first to 3 points) implemented using an Arduino Uno.

To start the game, both players need to simultaneously hold their buttons. The program counts down with a green, yellow, and red LED alongside an active buzzer to prepare the players to react.

A random value is set by the program to determine when the appropriate press period is. 

When it's time to press, the active buzzer is turned on and two white LEDs turn on to indicate to the players to press. 

If a player presses prematurely, their respective white LED will blink and the round is restarted.

if neither player presses their buttons, after 3 seconds the round is restarted.

The player to press first will have their white LED still on while the losing player's white LED is off. 

Points are indicated by the respective blue LEDs found on both sides and will not reset until one of the players has obtained 3 points.

Required Materials:

    -Arduino Uno
    -2 tactile buttons
    -Breadboard
    -9 resistors 330ohm recommended
    -Active buzzer
    -9 LEDs
    -Jumper wires
