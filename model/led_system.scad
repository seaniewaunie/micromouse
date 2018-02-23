// File: led_system.scad
// Author: Aksel Thomas
// Date: 2/13/2018

// This file contains the LED's for the robot.

include <model_constants.scad>
include <led.scad>

module led_system(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        
        // mode LED
        led(color = "green", yt = 20);
        
        // four directional LED's
        led(yt = 10);
        led(yt = -10);
        led(xt = 4);
        led(xt = -4);
    }
}
