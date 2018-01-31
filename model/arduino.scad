// File: arduino.scad
// Author: Aksel Thomas
// Date: 12/15/2017

include <model_constants.scad>

module arduino(xt = 0, yt = 0, zt = 0) {
    color([0, 0.5, 0.5]) {
        translate([xt, yt, zt]) {
            cube([ARDUINO_L, ARDUINO_W, ARDUINO_H], center = true);
        }
    }
}
