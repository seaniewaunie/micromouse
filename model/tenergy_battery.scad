// File: tenergy_battery.scad
// Author: Aksel Thomas
// Date: 1/31/2018

include <model_constants.scad>;

module tenergy_battery(xt = 0, yt = 0, zt = 0) {
    color("white") {
        translate([xt, yt, zt]) {
            cube([TENERGY_L, TENERGY_W, TENERGY_H], center = true);
        }
    }
}