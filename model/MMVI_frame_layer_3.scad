// File: MMVI_frame.scad
// Author: Aksel Thomas
// Date: 2/22/2018

// The purpose of this file is the custom frame.

include <modified_led_system.scad>
include <arduino.scad>
include <model_constants.scad>
include <plate.scad>

GROUND_OFFSET = 16.3;

// increases the resolution of components using arcs
$fn = 100;


difference() {

    // about 5 mm to place Arduino into

    plate(l = ARDUINO_W + 14, w = ARDUINO_L + 4, h = ARDUINO_H, xt = 98, yt = -ARDUINO_L / 2 - 2, zt = 50 + GROUND_OFFSET, color = "DarkViolet");

    arduino(xt = 137, zt = 60 + GROUND_OFFSET);
    
    plate(l = ARDUINO_W + 16, w = ARDUINO_L + 6, h = ARDUINO_H, xt = 97, yt = -ARDUINO_L / 2 - 3, zt = 58 + GROUND_OFFSET, color = "DarkViolet");

    modified_led_system(zt = 75, xt = 104);

}
