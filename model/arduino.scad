// File: arduino.scad
// Author: Aksel Thomas
// Date: 12/15/2017

include <model_constants.scad>

module arduino() {
    color([0, 0.5, 0.5]) {
        translate([0, 0, ARDUINO_H / 2]) {
            cube([ARDUINO_L, ARDUINO_W, ARDUINO_H], center = true);
        }
    }
}
