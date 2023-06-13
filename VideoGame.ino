#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

float midi[127];
int A_four = 440; // a is 440 hz...
int goodSong[9][2] = 
{
    {70, 100},  // song[0][0]], song[0][1]] Bb
    {66, 100},  // song[1][0]], song[1][1]] F#
    {70, 100},  // song[2][0]], song[2][1]] Bb
    {72, 100},  // song[3][0]], song[3][1]] C
    {74, 100},  // song[4][0]], song[4][1]] D
    {72, 100},  // song[5][0]], song[5][1]] C
    {70, 100},  // song[0][0]], song[0][1]] Bb
    {66, 100},  // song[1][0]], song[1][1]] F#
    {65, 400},  // song[1][0]], song[1][1]] F
};

//these variables measure the players time and scores
int playeroneScore; //variable measures player one's score
int playertwoScore; //variable measures player two's score
float playeroneTime; //variable measures player one's time
float playertwoTime; //variable measures player two's time
float practiceTime; //variable measures player's time

//these variables are for the reading and functionality of the left and right buttons
volatile bool A_Flag = 0; //sets variable to false initially, will be changed to true in a later function
volatile bool B_Flag = 0; //sets variable to false initially, will be changed to true in a later function
const int buttonAPin = 4; //this sets a constant (unchanging) variable for button A to pin 4
const int buttonBPin = 5; //this sets a constant (unchanging) variable for button B to pin 5

//these variables are here to ensure the proper reading and functionality of the switch
volatile bool switchFlag = 0; //switchFlag will be set to true in a function to run the game
volatile bool switchState = 0; //variable that will be assigned to read the state of the switch if changed.
const int switchPin = 7; //the digital pin for the switch is D7, so this variable is assigned to 7

void setup() 
{
  CircuitPlayground.begin(); //starting base for arduino
  generateMIDI(); // Custom function for calculating and storing the frequency value associated for each MIDI pitch number
  Serial.begin(9600); //needed for the serial to print; sets speed to 9600
  attachInterrupt(digitalPinToInterrupt(buttonAPin), aButton, FALLING); //runs function for button A to read if pressed
  attachInterrupt(digitalPinToInterrupt(buttonBPin), bButton, FALLING); //runs function for button B to read if pressed
  attachInterrupt(digitalPinToInterrupt(switchPin), switchCase, CHANGE); //runs function for switch to read if changed
  switchState = digitalRead(switchPin); //sets switchState to read the switch pin (7)
}

void loop() 
{
  if (switchFlag == 1) //reads the switch pin and sets it to the switch state; switchFlag is set to 1 during interrupt
  {
    switchState = digitalRead(switchPin); //sets switchState to digitalRead
  }
  if (switchState == 0) //if the switch is on the right side
  {
    CircuitPlayground.clearPixels(); //clear the LEDS
    delay(3000); //wait for 3 seconds
    blink(); //The board lights up blue for all LEDS
    delay(2000); //The board stays lit for 2 seconds
    if (A_Flag == 1) //if button A is pressed
    {
      playeroneTime = millis(); //millis is the number of milliseconds since the program started.
      Serial.print("P1 time: "); //prints "P1 time:"
      Serial.println(playeroneTime); //follows "p1 time:" and begins a new line
      A_Flag = 0; //A_flag set to 0 so the time doesn't keep printing
    }
  }
  else if (switchState == 1) //if the switch is on the left side
  {
    if (playeroneScore == 3 || playertwoScore == 3) //if either player reaches a score of 3
    {
      weezer(); //plays the Buddy Holly lick from Weezer
      playeroneScore = 0; //sets playeroneScore to 0
      playertwoScore = 0; //sets playertwoScore to 0
    }
    else if (playeroneScore <= 3 || playertwoScore <= 3) //if neither player has reached a score of 3
    {
      CircuitPlayground.clearPixels(); //clear the LEDS
      delay(3000); //wait for 3 seconds
      blink(); //The board lights up blue for all LEDS
      delay(2000); //The board stays lit for 2 seconds
      if (A_Flag == 1) //if button A is pressed
      {
        playeroneTime = millis(); //millis is the number of milliseconds since the program started.
        Serial.print("P1 time: "); //prints "P1 time:"
        Serial.println(playeroneTime); //follows "p1 time:" and begins a new line
        A_Flag = 0; //A_flag set to 0 so the time doesn't keep printing
      }
      if (B_Flag == 1) //if button B is pressed
      {
        playertwoTime = millis(); //millis is the number of milliseconds since the program started.
        Serial.print("P2 time: "); //prints "P2 time:"
        Serial.println(playertwoTime); //follows "p1 time:" and begins a new line
        B_Flag = 0; //B_flag set to 0 so the time doesn't keep printing
      }
      if (playeroneTime < playertwoTime) //if playerone clicked the button faster
      {
        CircuitPlayground.clearPixels(); //clear the LEDS
        delay(500); //wait 500 milliseconds
        playeroneScore++; //increase playerone's score
        playeroneWin(); //green LEDS blink on winner's sinde
        playertwoLose(); //red LEDS on loser's side
        delay(1000); //wait 1 second
      }
      else if (playertwoTime < playeroneTime) //if playertwo clicked the button faster
      {
        CircuitPlayground.clearPixels(); //clear the LEDS
        delay(500); //wait 500 milliseconds
        playertwoScore++; //increase playertwo's score
        playertwoWin(); //green LEDS blink on winner's side
        playeroneLose(); //red LEDS on loser's side
        delay(1000); //wait 1 second
      }
    }
  }
}

void aButton() //interrupt function for when the left button is pressed
{
A_Flag = 1; //sets flag to true when the button is pressed
}

void bButton() //interrupt function for when the right button is pressed
{
B_Flag = 1; //sets flag to true when the button is pressed
}

void switchCase() //interrupt function for when the switch changes sides
{
switchFlag = 1; //sets flag to true if the switch is changed
}


void blink() //light function
{
  for(int i=0; i<10; ++i) 
  {
    CircuitPlayground.setPixelColor(i, 0, 0 , 255); //sets all LEDS to blue
  }
}

void playeroneWin() //blinking light function when player 1 wins
{
  for(int i=5; i<10; ++i) //for LEDS 5-9, green flashes on each LED
  {
    CircuitPlayground.setPixelColor(i, 0, 255, 0); //sets LED to green
    delay(200); //delays 200ms
    CircuitPlayground.setPixelColor(i, 0, 0, 0); //clears LED
    delay(200); //delays 200ms
  }
}
void playeroneLose() //light function for if player 1 loses
{
    for(int i=5; i<10; ++i) //for LEDS 5-9, the LEDS will be red
  {
    CircuitPlayground.setPixelColor(i, 255, 0, 0); //sets LED to red
  }
}
void playertwoWin() //blinking light function when player 2 wins
{
  for(int i=0; i<5; ++i) 
  {
    CircuitPlayground.setPixelColor(i, 0, 255, 0); //for LEDS 0-4, green flashes on each LED
    delay(200); //delays 200ms
    CircuitPlayground.setPixelColor(i, 0, 0, 0); //clears LED 
    delay(200); //delays 200ms
  }
}
void playertwoLose() //light function for if player 2 loses
{
    for(int i=0; i<5; ++i) //for LEDS 0-4, the LEDS will be red
  {
    CircuitPlayground.setPixelColor(i, 255, 0, 0); //sets LED to red
  }
}

void weezer()
{
  for(int i = 0; i < sizeof(goodSong) / sizeof(goodSong[0]); i++) // Calculate how many rows are in the array using: sizeof(song) / sizeof(song[0])
    {
      CircuitPlayground.playTone(midi[goodSong[i][0]], goodSong[i][1]); //Plays the buddy holly lick based on list at the top of this code
      delay(1);
    }
}
void generateMIDI() //this function is used for sounds
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
  }
}