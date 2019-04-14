/*
 * WMBadge.ino
 * Chris Ritchie
 * 13.04.2019
 *
 * https://projectsfromtech.blogspot.com/2013/07/charlieplexing-on-attiny85-3-pins-6-leds.html
 */

#include <Charlieplex.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>



const int ledPin1 = 1;    // Charlieplexed for 6 LEDs
const int ledPin2 = 2;
const int ledPin3 = 0;
const int ledDelay = 500;
const int startBttn = 3;
bool turnedOn = false;
boolean bttnState;

#define NUMBER_OF_PINS 3
//define pins in the order you want to adress them
byte pins[] = {ledPin1, ledPin2, ledPin3};


//initialize object
Charlieplex charlieplex = Charlieplex(pins, NUMBER_OF_PINS);

charliePin led1 = { 0, 1 };
charliePin led2 = { 1, 2 };
charliePin led3 = { 0, 2 };
charliePin led4 = { 2, 0 };
charliePin led5 = { 2, 1 };
charliePin led6 = { 1, 0 };

typedef struct
{
    charliePin name;
} LEDS;

LEDS flash[6] {
    {led1},
    {led2},
    {led3},
    {led4},
    {led5},
    {led6}
};



void setup()
{
    pinMode(startBttn, INPUT_PULLUP);
}

void loop() {
    bttnState = digitalRead(startBttn); // Check state of button
    if (bttnState == LOW)
    {
        if(turnedOn == true) turnedOn = false;
        else turnedOn = true;
    }

    if(turnedOn == true)
    {
        delay(500);
        for(int i=0; i<3; i++)
            spinClockwise();

        delay(1000);
        for(int i=0; i<3; i++)
            spinCounterClosewise();
    }
    else
        sleep();
}

void spinClockwise()
{
    for(int i = 0; i<=5; i++)
    {
        bttnState = digitalRead(startBttn);
        if(bttnState == LOW)
        {
            turnedOn = false;
            break;
        }

        charlieplex.charlieWrite(flash[i].name,HIGH);
        delay(ledDelay);
        charlieplex.clear();
    }
}

void spinCounterClosewise()
{
    for(int i = 5; i>=0; i--)
    {
        bttnState = digitalRead(startBttn);
        if(bttnState == LOW)
        {
            turnedOn = false;
            break;
        }

        charlieplex.charlieWrite(flash[i].name,HIGH);
        delay(ledDelay);
        charlieplex.clear();
    }
    /*
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
        * */
}

void sleep() {

    GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
    PCMSK |= _BV(PCINT2);                   // Use PB2 as interrupt pin
    PCMSK |= _BV(PCINT3);                   // Use PB3 as interrupt pin
    PCMSK |= _BV(PCINT4);                   // Use PB4 as interrupt pin
    ADCSRA &= ~_BV(ADEN);                   // ADC off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement

    sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();                                  // Enable interrupts
    sleep_cpu();                            // sleep

    cli();                                  // Disable interrupts
    PCMSK &= ~_BV(PCINT2);                  // Turn off PB2 as interrupt pin
    PCMSK &= ~_BV(PCINT3);                  // Turn off PB3 as interrupt pin
    PCMSK &= ~_BV(PCINT4);                  // Turn off PB4 as interrupt pin
    sleep_disable();                        // Clear SE bit
    ADCSRA |= _BV(ADEN);                    // ADC on

    sei();                                  // Enable interrupts
} // sleep

ISR(PCINT0_vect) {
    // This is called when the interrupt occurs, but I don't need to do anything in it
}
