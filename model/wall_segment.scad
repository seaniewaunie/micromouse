// File: wall_segment.scad
// Author: Aksel Thomas
// Date: 2/2/2018

include <model_constants.scad>

module wall_segment(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        color("white") {
            cube([WALL_SEGMENT_L, WALL_SEGMENT_W, WALL_SEGMENT_H]);
        }
        color("red") {
            translate([0, 0, WALL_SEGMENT_H]) {
                cube([WALL_SEGMENT_L, WALL_SEGMENT_W, PLATE_H]);
            }
        }
    }
}