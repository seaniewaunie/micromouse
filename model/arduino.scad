// File: arduino.scad
// Author: Aksel Thomas
// Date: 12/15/2017

include <model_constants.scad>

$fn = 100;

module arduino(xt = 0, yt = 0, zt = 0) {
    color([0, 0.5, 0.5]) {
        translate([xt, yt, zt]) {
            difference() {
                cube([ARDUINO_W, ARDUINO_L, ARDUINO_H]);
                translate([ARDUINO_W - ARDUINO_BOLT_HOLE_1_X_OFFSET, ARDUINO_BOLT_HOLE_1_Y_OFFSET, -1]) {
                    cylinder(d = ARDUINO_BOLT_HOLE_D, h = ARDUINO_H + 2);
                }
                translate([ARDUINO_W - ARDUINO_BOLT_HOLE_2_X_OFFSET, ARDUINO_BOLT_HOLE_2_Y_OFFSET, -1]) {
                    cylinder(d = ARDUINO_BOLT_HOLE_D, h = ARDUINO_H + 2);
                }
                translate([ARDUINO_W - ARDUINO_BOLT_HOLE_3_X_OFFSET, ARDUINO_BOLT_HOLE_3_Y_OFFSET, -1]) {
                    cylinder(d = ARDUINO_BOLT_HOLE_D, h = ARDUINO_H + 2);
                }                
            }
        }
    }
}
