// File: modified_led_system.scad
// Author: Aksel Thomas
// Date: 2/22/2018

// This file contains the LED's for the robot.

include <model_constants.scad>
include <modified_led.scad>

module modified_led_system(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        
        // mode LED
        modified_led(color = "green", yt = 20);
        
        // four directional LED's
        modified_led(yt = 10);
        modified_led(yt = -10);
        modified_led(xt = 4);
        modified_led(xt = -4);
    }
}
