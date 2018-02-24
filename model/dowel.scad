// File: dowel.scad
// Author: Aksel Thomas
// Date: 2/24/2018

include <model_constants.scad>

module dowel(xt = 0, yt = 0, zt = 0, color = "wheat") {
    translate([xt, yt, zt]) {
        color(color) {
            cube([DOWEL_L, DOWEL_W, DOWEL_H]);
        }
    }
}
