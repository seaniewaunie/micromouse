// File: pushbutton.scad
// Author: Aksel Thomas
// Date: 1/31/2018

include <model_constants.scad>

module pushbutton(xt = 0, yt = 0, zt = 0) {
    color([0.2, 0.2, 0.2]) {
        translate([xt, yt, zt]) {
            cube([PUSHBUTTON_BODY_L, PUSHBUTTON_BODY_W, PUSHBUTTON_BODY_H]);
            translate([PUSHBUTTON_BODY_L / 2, PUSHBUTTON_BODY_W / 2, PUSHBUTTON_BODY_H]) {
                cylinder(d = PUSHBUTTON_CYLINDER_D, h = PUSHBUTTON_CLYINDER_H);
            }
        }
    }
}