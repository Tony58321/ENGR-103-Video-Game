# ENGR-103-Video-Game
This is for my ENGR 103 class. We were tasked to create a video game for our final project in the class on an Arduino Circuit Playground.

This game is a 1v1 game where the first person to click their button when the LED pops up wins. Both players click their buttons at the same time. The board will turn on the LEDS and a timer will begin. Whoever presses the button first will have their side of the board shine green. The loser's side will be blank or red (haven't decided yet).The players can then click both buttons again to play again. A score will be kept and whoever wins 3 games first wins the game and a victory song will play. Moving the switch will trigger practice mode, where the player has unlimited attempts to get faster at the game. The serial monitor will print the amount of time it took you to click the button to track improvement.

Each player must click their button at the same time to start the game. They will use their button to click once they see the LEDS on the circuit board pop up. During practice mode, the user can use either button to practice.

The switch will be used to go from game mode to practice mode. During game mode, there are two players, scores will be kept and a winner will be announced. During practice mode, one person will use the board to try and improve how fast they react to the lights.

Outputs will include the LEDS. These will shine when both players are ready to start the game. The pixels will clear once a button is pressed. Then lights on the winners side will be green and the lights on the losers will be blank or red.

The speaker will play a victory song when one person has won 3 games in a row.
