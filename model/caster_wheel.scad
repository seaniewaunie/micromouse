// File: caster_wheel.scad
// Author: Aksel Thomas
// Date: 1/31/2018

include <model_constants.scad>

module caster_wheel(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        rotate(a = 90, v = [0, 0, 1]) {        
            color("silver") {
                cube([CASTER_WHEEL_PLATE_L, CASTER_WHEEL_PLATE_W, CASTER_WHEEL_PLATE_H]);
            }
            color([0.2, 0.2, 0.2]) {
                translate([CASTER_WHEEL_PLATE_L / 2, CASTER_WHEEL_Y_OFFSET, -CASTER_WHEEL_Z_OFFSET]) {
                    rotate(a = 90, v = [0, 1, 0]) {
                        cylinder(d = CASTER_WHEEL_D, h = CASTER_WHEEL_H, center = true);
                    }
                }
            }
        }
    }
}