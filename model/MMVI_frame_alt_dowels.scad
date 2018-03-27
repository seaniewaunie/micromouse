// File: MMVI_frame_dowels.scad
// Author: Aksel Thomas
// Date: 2/27/2018

// This file contains the dowels to be 3D printed.

include <alternate_dowel.scad>

rotate([90, 0, 0]) {
    alternate_dowel();
    alternate_dowel(xt = 7);
    alternate_dowel(xt = 14);
    alternate_dowel(xt = 21);
    alternate_dowel(xt = 28);
    alternate_dowel(xt = 35);
    alternate_dowel(xt = 42);
}