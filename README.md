# ENGR-103-Video-Game
This is for my ENGR 103 class. We were tasked to create a video game for our final project in the class on an Arduino Circuit Playground.

This game is a 1v1 game where the first person to click their button when the LED pops up wins. The board will turn on the LEDS and a timer will begin. Whoever presses the button first will have their side of the board blink green. The loser's side will show red LEDs. A score will be kept and whoever wins 3 games first wins the game and a victory song will play. The game automatically restarts and will do so until the circuitboard is unplugged from the power device. Moving the switch will trigger practice mode, where the player has unlimited attempts to get faster at the game. The serial monitor will print the amount of time it took you to click the button to track improvement.

Each player will use their button to click once they see the LEDS on the circuit board pop up. During practice mode, the user can use either button to practice.

The switch will be used to go from game mode to practice mode. During game mode, there are two players, scores will be kept and a winner will be announced. During practice mode, one person will use the board to try and improve how fast they react to the lights. They will need to look at the serial monitor to track progress.

Outputs will include the LEDS. These will turn on when the game starts. The pixels will clear once a button is pressed. Then, lights on the winners side will blink green and the lights on the losers will be red. The speaker will play a victory song when one person has won 3 games in a row.
