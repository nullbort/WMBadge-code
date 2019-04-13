/*
||
 || @author Matthew
 || @version 1.0
                   ATtiny 85/45
                      _____
            RESET   -|     |-  VCC
                    -|     |-  LED 2
                    -|     |-  LED 1
               GND  -|_____|-  LED 3
 */
/*
This example uses 6 LEDs connected to pins 0, 1, and 2.
For more details see http://projectsfromtech.blogspot.com/
* https://projectsfromtech.blogspot.com/2013/07/charlieplexing-on-attiny85-3-pins-6-leds.html
 */

#include <Charlieplex.h>


const int ledpin1 = 1;    // Charlieplexed for 6 LEDs
const int ledpin2 = 2; 
const int ledpin3 = 0;



#define NUMBER_OF_PINS 3
//define pins in the order you want to adress them
byte pins[] = {ledpin1, ledpin2, ledpin3};


//initialize object
Charlieplex charlieplex = Charlieplex(pins , NUMBER_OF_PINS);

/*
//individual 'pins' , adress charlieplex pins as you would adress an array
charliePin led1 = { 0 , 1 }; // Set the pins the LEDs are connected to.
charliePin led2 = { 1 , 2 }; // If the wrong LED lights, change it here.
charliePin led3 = { 2 , 0 };
charliePin led4 = { 0 , 2 };
charliePin led5 = { 2 , 1 }; 
charliePin led6 = { 1 , 0 };
*/
charliePin led1 = { 0 , 1 };
charliePin led2 = { 1 , 2 };
charliePin led3 = { 0 , 2 };
charliePin led4 = { 2 , 0 };
charliePin led5 = { 2 , 1 }; 
charliePin led6 = { 1 , 0 };

void setup(){ 
  /*nothing*/
}

void loop(){
   
  charlieplex.charlieWrite(led1,HIGH);
  delay(1000);
  charlieplex.clear();    // Must clear the LED to avoid lighting additional LEDs unintentionally
                          // This sets all 3 pins as an input
  charlieplex.charlieWrite(led2,HIGH);
  delay(1000); 
  charlieplex.clear();
  
  charlieplex.charlieWrite(led3,HIGH);
  delay(1000);
  charlieplex.clear();

  charlieplex.charlieWrite(led4,HIGH);
  delay(1000);
  charlieplex.clear();
    
  charlieplex.charlieWrite(led5,HIGH);
  delay(1000);
  charlieplex.clear();
  
  charlieplex.charlieWrite(led6,HIGH);
  delay(1000);
  charlieplex.clear();
  
}


