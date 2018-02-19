// File: driven_wheel_system.scad
// Author: Aksel Thomas
// Date: 2/13/2018

// This file contains the driven wheel subsystem.

include <model_constants.scad>
include <32_mm_wheel.scad>
include <motor.scad>

WHEEL_OFFSET = 42;
// Assumes the motor output shaft overlaps wheel by ~6 mm
MOTOR_OFFSET_FROM_WHEEL = -24.8;

module driven_wheel_system(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        // Right wheel
        32_mm_wheel(yt = WHEEL_OFFSET);
        
        // Left wheel
        rotate([180, 0, 0]) {
            32_mm_wheel(yt = WHEEL_OFFSET);
        }
        
        // Right motor
        rotate([0, 0, 90]) {
            motor(xt = WHEEL_OFFSET + MOTOR_OFFSET_FROM_WHEEL);
        }
        
        // Left motor
        rotate([0, 0, 270]) {
            motor(xt = WHEEL_OFFSET + MOTOR_OFFSET_FROM_WHEEL);
        }
    }
}