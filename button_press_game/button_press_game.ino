/*
  State change detection (edge detection)
 	
 Often, you don't need to know the state of a digital input all the time,
 but you just need to know when the input changes from one state to another.
 For example, you want to know when a button goes from OFF to ON.  This is called
 state change detection, or edge detection.
 
 This example shows how to detect when a button or button changes from off to on
 and on to off.
 	
 The circuit:
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 * LED attached from pin 13 to ground (or use the built-in LED on
   most Arduino boards)
 
 created  27 Sep 2005
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.
 	
 http://arduino.cc/en/Tutorial/ButtonStateChange
 
 */
 // LEDs in pins 5 through 12
 // 5-8 are next to the player 1 button
 //
#define LED11 11
#define LED10 10
#define LED9 9
#define LED8 8
#define LED7 7
#define LED6 6
#define LED5 5
#define LED4 4

// buttons on pins 2 and 13
#define BUTTON2 2
#define BUTTON12 12

#define NPLAYERS 2

// this constant won't change:

// Variables will change:
const int debounceDelay = 50; // the debounce time

int buttonPushCounter[NPLAYERS] = {0};   // counter for the number of button presses
int buttonState[NPLAYERS] = {0};         // current state of the button
int lastButtonState[NPLAYERS] = {0};     // previous state of the button

long lastFlashTime[NPLAYERS] = {0};      // last time that the LED side was randomized
long flashTime = 100;                      // time between LED randomizations
long winPush = 10;                        // number of pushes needed to win

long winTime = 0;                        // last time of a win
long celebrationTime = 5000;              // time for celebration after a win

float rand1 = 0;                          // random variable

void setup() {
  // initialize button pins as input:
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON12, INPUT);
  // initialize the LED pins as output:  
  
 pinMode(LED4, OUTPUT);
 pinMode(LED11, OUTPUT);
 pinMode(LED10, OUTPUT);
 pinMode(LED9, OUTPUT);
 pinMode(LED8, OUTPUT);
 pinMode(LED7, OUTPUT);
 pinMode(LED6, OUTPUT);
 pinMode(LED5, OUTPUT);
 
 for (long i=0; i<NPLAYERS; i++) {
   buttonPushCounter[i] = 0;
   buttonState[i] = LOW;
   lastButtonState[i] = LOW;
   lastFlashTime[i] = 0;
   
 }
  
  // initialize serial communication
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  buttonState[0] = digitalRead(BUTTON2);
  buttonState[1] = digitalRead(BUTTON12);
  
  /*for (long i=0; i<NPLAYERS; i++) {
  
    if (buttonState[i] != lastButtonState[i]) {
      // reset the debouncing timer
      lastDebounceTime[i] = millis();
    } 
    
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {

         if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    
    }
   }
   }*/  
  

  // compare the buttonState to its previous state
  for (long i=0; i<NPLAYERS; i++) {
    if (buttonState[i] != lastButtonState[i]) {
      // if the state has changed, increment the counter
      if (buttonState[i] == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        buttonPushCounter[i]++;
        Serial.print("Player ");
        Serial.print(i+1);
        Serial.print(" number of button pushes:  ");
        Serial.println(buttonPushCounter[i]);
      } 
      else {
        // if the current state is LOW then the button
        // wend from on to off:
        
      }
    }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState[i] = buttonState[i];
  }
  
  
  
  
  // turns on the LED every four button pushes by 
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of 
  // the division of two numbers:
  
  // for player one
  // uses LEDs 5-8
  
  if (buttonPushCounter[0] > buttonPushCounter[1] && buttonPushCounter[0] > winPush) {
    
    winTime = millis();
    
    while (millis() - winTime < celebrationTime) {
    
      if (millis() - lastFlashTime[0] > flashTime) {
        
        for (long i=LED4; i<=LED7; i++) {
          
          rand1 = random(0,10000);
          if (rand1/10000>0.5) {
            digitalWrite(i, HIGH);
          } else {
            digitalWrite(i, LOW);
          }
        }
        
        lastFlashTime[0] = millis();
        
      }
    
    }
    
    for (long i=0; i<NPLAYERS; i++) 
      buttonPushCounter[i] = 0;

    
  } else {
   
     digitalWrite(LED4, LOW);
     digitalWrite(LED7, LOW);
     digitalWrite(LED6, LOW);
     digitalWrite(LED5, LOW);
    
  }
  
  // for player two
  // uses LEDs 9-12
  
  if (buttonPushCounter[1] > buttonPushCounter[0] && buttonPushCounter[1] > winPush) {

    if (millis() - lastFlashTime[1] > flashTime) {

      winTime = millis();
      
      while (millis() - winTime < celebrationTime) {
  
        if (millis() - lastFlashTime[1] > flashTime) {
          for (long i=LED8; i<=LED11; i++) {
            
            rand1 = random(0,10000);
            if (rand1/10000>0.5)
              digitalWrite(i, HIGH);
            else
              digitalWrite(i, LOW);
              
          }
      
        lastFlashTime[1] = millis();
        
       }
       
      }
    
     }

    for (long i=0; i<NPLAYERS; i++) 
      buttonPushCounter[i] = 0;
      
    winPush = random(10,25);
     
    } else {
 
     digitalWrite(LED8, LOW);
     digitalWrite(LED11, LOW);
     digitalWrite(LED10, LOW);
     digitalWrite(LED9, LOW);

  
  }
  
}









