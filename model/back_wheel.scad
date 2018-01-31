// File: back_wheel.scad
// Author: Aksel Thomas
// Date: 12/15/2017

include <model_constants.scad>;

module back_wheel(xt = 0, yt = 0, zt = 0, color = [0.2, 0.2, 0.2]) {
    color(color) {
        translate([xt, yt, zt]) {
            rotate(a = 90, v = [1, 0, 0]) {
                difference() {
                    cylinder(d = BACK_WHEEL_D, h = BACK_WHEEL_H, center = true);
                    cylinder(d = MOTOR_SHAFT_D, h = BACK_WHEEL_H, center = true);
                }
                translate([0, 0, BACK_WHEEL_H / 2 + BACK_WHEEL_NUB_H / 2]) {
                    difference() {
                        cylinder(d = BACK_WHEEL_NUB_D, h = BACK_WHEEL_NUB_H, center = true);
                        cylinder(d = MOTOR_SHAFT_D, h = BACK_WHEEL_NUB_H, center = true);
                    }
                }
            }
        }   
    }
}
