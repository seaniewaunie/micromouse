// File: tenergy_battery.scad
// Author: Aksel Thomas
// Date: 1/31/2018

include <model_constants.scad>;

module tenergy_battery(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        color("white") {
            cube([TENERGY_L, TENERGY_W, TENERGY_H]);
        }
        color("black") {
            translate([TENERGY_L/4, TENERGY_W/2, TENERGY_H]) {
                text("Tenergy");
            }
        }
    }
}