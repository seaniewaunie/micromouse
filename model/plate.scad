// File: plate.scad
// Author: Aksel Thomas
// Date: 12/15/2017

include <model_constants.scad>;

module plate(l = PLATE_L, w = PLATE_W, h = PLATE_H, xt = 0, yt = 0, zt = 0, color = "silver") {
    color(color)
    translate([xt, yt, zt]) {
        cube([l, w, h], center = true);
    }
}
