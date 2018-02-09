// File: 32_mm_wheel.scad
// Author: Aksel Thomas
// Date: 2/06/2018

include <model_constants.scad>;

module 32_mm_wheel(xt = 0, yt = 0, zt = 0, color = [0.2, 0.2, 0.2]) {
    color(color) {
        translate([xt, yt, zt]) {
            rotate(a = 90, v = [1, 0, 0]) {
                difference() {
                    cylinder(d = 32_MM_WHEEL_D, h = 32_MM_WHEEL_H, center = true);
                    cylinder(d = MOTOR_SHAFT_D, h = 32_MM_WHEEL_H, center = true);
                }
                translate([0, 0, 32_MM_WHEEL_H / 2 + 32_MM_WHEEL_NUB_H / 2]) {
                    difference() {
                        cylinder(d = 32_MM_WHEEL_NUB_D, h = 32_MM_WHEEL_NUB_H, center = true);
                        cylinder(d = MOTOR_SHAFT_D, h = 32_MM_WHEEL_NUB_H, center = true);
                    }
                }
            }
        }   
    }
}