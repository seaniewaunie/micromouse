// File: MMVI_layout.scad
// Author: Aksel Thomas
// Date: 2/2/2018

// The purpose of this file is to lay out the components roughly where
// they will go in relation to each other in the robot.

include <led.scad>;
include <arduino.scad>;
include <32_mm_wheel.scad>;
include <plate.scad>;
include <motor.scad>;
include <sensor.scad>;
include <tenergy_battery.scad>;
include <pushbutton.scad>;
include <h_bridge.scad>;
include <caster_wheel.scad>;
include <caster_ball.scad>;
include <wall_segment.scad>;
include <model_constants.scad>;

WHEEL_OFFSET = 50;
MOTOR_OFFSET_FROM_WHEEL = -30.5;
SIDE_SENSOR_HEIGHT_OFFSET = 0;
SIDE_SENSOR_FORE_AFT_OFFSET = 45;
FRONT_SENSOR_FORE_AFT_OFFSET = 15;
FRONT_SENSOR_HEIGHT_OFFSET = 20;
GROUND_OFFSET = -16;

// The ground (not part of the model, shown for reference)
plate(l = 180, w = 180, zt = GROUND_OFFSET, color="palegreen");

wall_segment(xt = -WALL_SEGMENT_L / 2, yt = 90, zt = GROUND_OFFSET);

// Right back wheel and motor
// Assumes the motor output shaft overlaps wheel by 4 mm
32_mm_wheel(yt = WHEEL_OFFSET);
rotate(a = 90, v = [0, 0, 1]) {
    motor(xt = WHEEL_OFFSET + MOTOR_OFFSET_FROM_WHEEL);
}

// Left back wheel and motor
// Assumes the motor output shaft overlaps wheel by 1 mm
rotate(a = 180, v = [1, 0, 0]) {
    32_mm_wheel(yt = WHEEL_OFFSET);
}
rotate(a = 270, v = [0, 0, 1]) {
    motor(xt = WHEEL_OFFSET + MOTOR_OFFSET_FROM_WHEEL);
}

rotate([0, 0, 90]) {
    arduino(yt = 15, zt = 15);
}

rotate([0, 0, 90]) {
    caster_ball(xt = HOUSING_W / 2, yt = -70, zt = -11.1);
}

// Right sensor
rotate(a = 90, v = [1, 0, 0]) {
    sensor(xt = SIDE_SENSOR_FORE_AFT_OFFSET, yt = SIDE_SENSOR_HEIGHT_OFFSET, zt = 7);
}

// Left sensor
rotate(a = 270, v = [1, 0, 0]) {
    sensor(xt = SIDE_SENSOR_FORE_AFT_OFFSET, yt = -SIDE_SENSOR_HEIGHT_OFFSET, zt = 7);
}

// Front sensor
rotate([90, 0, 90]) {
    sensor(yt = FRONT_SENSOR_HEIGHT_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET);
}

rotate([0, 0, 90]) {
    tenergy_battery(xt = -TENERGY_L/2, yt = -55, zt = 35);
}

h_bridge(xt = -15, zt = 40);

pushbutton(zt = 60);

led(zt = 90, color = "green");

led(yt = 40, zt = 50);

led(yt = -40, zt = 50);

led(xt = 15, zt = 50);

led(xt = -45, zt = 50);