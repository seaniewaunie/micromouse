// File: led_system.scad
// Author: Aksel Thomas
// Date: 2/13/2018

// This file contains the LED's for the robot.

include <model_constants.scad>
include <led.scad>

module led_system(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        
        // mode LED
        led(color = "green");
        
        // four directional LED's
        led(yt = 20);
        led(yt = -20);
        led(xt = 15);
        led(xt = -15);
    }
}
