// File: dowel.scad
// Author: Aksel Thomas
// Date: 2/24/2018

include <model_constants.scad>

module alternate_dowel(xt = 0, yt = 0, zt = 0, color = "wheat") {
    translate([xt, yt, zt]) {
        color(color) {
            cube([DOWEL_L - 0.1, DOWEL_W - 0.1, DOWEL_H - 2]);
        }
    }
}
