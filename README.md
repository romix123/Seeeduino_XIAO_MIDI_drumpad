# Seeeduino_XIAO_MIDI_drumpad
 XIAO based MIDI drumpad 


 This sketch is enumerated as USB MIDI device. 
 
  Following librarues are required
  - Adafruit TinyUSB Library for Arduino
  	https://github.com/adafruit/Adafruit_TinyUSB_Arduino
  
  - MIDI Library by Forty Seven Effects
    https://github.com/FortySevenEffects/arduino_midi_library
    
   drum code comes from
   https://github.com/RyoKosaka/drums/tree/master/arduino/piezo_peak_test
    
    
    
    Hardware
    
    Seeeduino XIAO
    
    A6 - ––––––––––– [1M] –––––––––––––– gnd
                \-----|<----/                      3v3 zener
                  |       |
                  |+piezo-|
    
    gnd ----|<--[470]---  7 
    
    in words: connect a 1 M ohm resistor between the 2 Piezo leads. 
              comnnect the plus (red) lead of the piezo to pin 6 on the XIAO (A6)
              connect the neg (black lead) of the piezo to pin GND on the XIAO
    optional: connect a 3V3 zenerdiode with the bar facing the A6 side across the resistor
    
    connect an LED in series with a 470 ohm (not ciritical, higher is better) resistor 
    to Pin 7 and GND. The short lead of the LED should be tied to gnd. 
 /