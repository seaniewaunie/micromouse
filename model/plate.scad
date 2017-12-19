// File: plate.scad
// Author: Aksel Thomas
// Date: 12/15/2017

include <model_constants.scad>;

module plate(l = PLATE_L, w = PLATE_W, h = PLATE_H, color = "silver") {
    color(color)
    cube([l, w, h], center = true);
}
