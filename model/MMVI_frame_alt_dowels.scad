// File: MMVI_frame_dowels.scad
// Author: Aksel Thomas
// Date: 2/27/2018

// This file contains the dowels to be 3D printed.

include <alternate_dowel.scad>

rotate([90, 0, 0]) {
    alternate_dowel();
    alternate_dowel(xt = 5);
    alternate_dowel(xt = 10);
    alternate_dowel(xt = 15);
    alternate_dowel(xt = 20);
    alternate_dowel(xt = 25);
    alternate_dowel(xt = 30);
}