// File: MMVI_frame_dowels.scad
// Author: Aksel Thomas
// Date: 2/27/2018

// This file contains the dowels to be 3D printed.

include <dowel.scad>

rotate([90, 0, 0]) {
    dowel();
    dowel(xt = 5);
    dowel(xt = 10);
    dowel(xt = 15);
    dowel(xt = 20);
    dowel(xt = 25);
    dowel(xt = 30);
}