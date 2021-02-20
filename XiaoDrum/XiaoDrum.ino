/*********************************************************************
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 Copyright (c) 2019 Ha Thach for Adafruit Industries
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

/* This sketch is enumerated as USB MIDI device. 
 * Following library is required
 * - MIDI Library by Forty Seven Effects
 *   https://github.com/FortySevenEffects/arduino_midi_library
 *   
 *  drum code comes from
 *  https://github.com/RyoKosaka/drums/tree/master/arduino/piezo_peak_test
 *   
 *   
 *   
 *   Hardware
 *   
 *   Seeeduino XIAO
 *   
 *   A6 - ––––––––––– [1M] –––––––––––––– gnd
 *               \-----|<----/                      3v3 zener
 *                 |       |
 *                 |+piezo-|
 *   
 *   gnd ----|<--[470]---  7 
 *   
 *   in words: connect a 1 M ohm resistor between the 2 Piezo leads. 
 *             comnnect the plus (red) lead of the piezo to pin 6 on the XIAO (A6)
 *             connect the neg (black lead) of the piezo to pin GND on the XIAO
 *   optional: connect a 3V3 zenerdiode with the bar facing the A6 side across the resistor
 *   
 *   connect an LED in series with a 470 ohm (not ciritical, higher is better) resistor 
 *   to Pin 7 and GND. The short lead of the LED should be tied to gnd. 
 */

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

boolean piezo = false;



// Create a new instance of the Arduino MIDI Library,
// and attach usb_midi as the transport.
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);


void setup()
{
  pinMode(7,OUTPUT); // Led connected to pin 7
  
  usb_midi.setStringDescriptor("SAMDrum MIDI");

  // Initialize MIDI, and listen to all MIDI channels
  // This will also call usb_midi's begin()
  MIDI.begin(MIDI_CHANNEL_OMNI);

  Serial.begin(115200);

  // wait until device mounted
  while( !USBDevice.mounted() ) delay(1);
}

void loop()
{

  int sensorValue = analogRead(A6);
  int MAX;

  if (sensorValue > 20 &&  piezo == false) {
    int peak1 = analogRead(A6);
    MAX = peak1;
    delay(1);
    int peak2 = analogRead(A6);

    if (peak2 > MAX) {
      MAX = peak2;
    }

    delay(1);
    int peak3 = analogRead(A6);

    if (peak3 > MAX) {
      MAX = peak3;
    }

    delay(1);
    int peak4 = analogRead(A6);

    if (peak4 > MAX) {
      MAX = peak4;
    }

    delay(1);
    int peak5 = analogRead(A6);

    if (peak5 > MAX) {
      MAX = peak5;
    }

    delay(1);
    int peak6 = analogRead(A6);

    if (peak6 > MAX) {
      MAX = peak6;
    }

    MAX = map(MAX, 20, 800, 1, 127);

    if(MAX <= 1){
      MAX = 1;
    }

    if(MAX >= 127){
      MAX = 127;
    }
   
   
   digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)

    MIDI.sendNoteOn(38, MAX, 1); //snare note is 38
    MIDI.sendNoteOff(38, 0, 1);
    delay(20);
   // Serial.println(MAX);
    digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW

    piezo = true;

    delay(30); //mask time

  }

  if (sensorValue <= 0 && piezo == true) {
    piezo = false;
  }

}
