/*
 * WMBadge.ino
 * Chris Ritchie
 * 13.04.2019
 *
 * https://projectsfromtech.blogspot.com/2013/07/charlieplexing-on-attiny85-3-pins-6-leds.html
 */

#include <Charlieplex.h>


const int ledPin1 = 1;    // Charlieplexed for 6 LEDs
const int ledPin2 = 2;
const int ledPin3 = 0;
const int ledDelay = 500;


#define NUMBER_OF_PINS 3  //define pins in the order you want to adress them
byte pins[] = {ledPin1, ledPin2, ledPin3};


//initialize object
Charlieplex charlieplex = Charlieplex(pins, NUMBER_OF_PINS);

charliePin led1 = { 0, 1 };
charliePin led2 = { 1, 2 };
charliePin led3 = { 0, 2 };
charliePin led4 = { 2, 0 };
charliePin led5 = { 2, 1 };
charliePin led6 = { 1, 0 };

void setup() {}

void loop() {
    for(int i=0; i<3; i++)
        spinClockwise();
    delay(100);
    for(int i=0; i<3; i++)
        spinCounterClosewise();
}

void spinClockwise()
{
    charlieplex.charlieWrite(led1,HIGH);
    delay(ledDelay);
    charlieplex.clear();

    charlieplex.charlieWrite(led2,HIGH);
    delay(ledDelay);
    charlieplex.clear();

    charlieplex.charlieWrite(led3,HIGH);
    delay(ledDelay);
    charlieplex.clear();

    charlieplex.charlieWrite(led4,HIGH);
    delay(ledDelay);
    charlieplex.clear();

    charlieplex.charlieWrite(led5,HIGH);
    delay(ledDelay);
    charlieplex.clear();

    charlieplex.charlieWrite(led6,HIGH);
    delay(ledDelay);
    charlieplex.clear();
}

void spinCounterClosewise()
{
    charlieplex.charlieWrite(led6,HIGH);
    delay(ledDelay);
    charlieplex.clear();

    charlieplex.charlieWrite(led5,HIGH);
    delay(ledDelay);
    charlieplex.clear();

    charlieplex.charlieWrite(led4,HIGH);
    delay(ledDelay);
    charlieplex.clear();

    charlieplex.charlieWrite(led3,HIGH);
    delay(ledDelay);
    charlieplex.clear();

    charlieplex.charlieWrite(led2,HIGH);
    delay(ledDelay);
    charlieplex.clear();

    charlieplex.charlieWrite(led1,HIGH);
    delay(ledDelay);
    charlieplex.clear();
}
