// File: MMVI_layout.scad
// Author: Aksel Thomas
// Date: 2/2/2018

// The purpose of this file is to lay out the components roughly where
// they will go in relation to each other in the robot.

include <led.scad>;
include <arduino.scad>;
include <back_wheel.scad>;
include <plate.scad>;
include <motor.scad>;
include <sensor.scad>;
include <tenergy_battery.scad>;
include <pushbutton.scad>;
include <h_bridge.scad>;
include <caster_wheel.scad>;
include <wall_segment.scad>;
include <model_constants.scad>;

WHEEL_OFFSET = 90;
MOTOR_OFFSET_FROM_WHEEL = -33.5;
SENSOR_HEIGHT_OFFSET = 20;
SENSOR_FORE_AFT_OFFSET = 80;
GROUND_OFFSET = -36;

// The ground (not part of the model, shown for reference)
plate(l = 300, w = 400, zt = GROUND_OFFSET, color="palegreen");

wall_segment(xt = -WALL_SEGMENT_L / 2, yt = 150, zt = GROUND_OFFSET);

// Right back wheel and motor
// Assumes the motor output shaft overlaps wheel by 1 mm
back_wheel(yt = WHEEL_OFFSET);
rotate(a = 90, v = [0, 0, 1]) {
    motor(xt = WHEEL_OFFSET + MOTOR_OFFSET_FROM_WHEEL);
}

// Left back wheel and motor
// Assumes the motor output shaft overlaps wheel by 1 mm
rotate(a = 180, v = [1, 0, 0]) {
    back_wheel(yt = WHEEL_OFFSET);
}
rotate(a = 270, v = [0, 0, 1]) {
    motor(xt = WHEEL_OFFSET + MOTOR_OFFSET_FROM_WHEEL);
}

arduino();

caster_wheel(xt = 100, yt = -CASTER_WHEEL_PLATE_L / 2, zt = 6);

rotate(a = 90, v = [1, 0, 0]) {
    sensor(xt = SENSOR_FORE_AFT_OFFSET, yt = SENSOR_HEIGHT_OFFSET, zt = 5);
}

rotate(a = 270, v = [1, 0, 0]) {
    sensor(xt = SENSOR_FORE_AFT_OFFSET, yt = -SENSOR_HEIGHT_OFFSET, zt = 5);
}