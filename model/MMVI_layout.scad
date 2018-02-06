// File: MMVI_layout.scad
// Author: Aksel Thomas
// Date: 2/2/2018

// The purpose of this file is to lay out the components roughly where
// they will go in relation to each other in the robot.

// TODO: Add USB battery pack

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
include <usb_battery.scad>;
include <model_constants.scad>;

WHEEL_OFFSET = 55;
MOTOR_OFFSET_FROM_WHEEL = -33.5;
SIDE_SENSOR_HEIGHT_OFFSET = -22;
SIDE_SENSOR_FORE_AFT_OFFSET = -55;
FRONT_SENSOR_FORE_AFT_OFFSET = 70;
FRONT_SENSOR_HEIGHT_OFFSET = 17;
GROUND_OFFSET = -36;

translate([0, 0, 36]) {

// The ground (not part of the model, shown for reference)
plate(l = 180, w = 180, zt = GROUND_OFFSET, color="palegreen");

wall_segment(xt = -WALL_SEGMENT_L / 2, yt = 90, zt = GROUND_OFFSET);

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

rotate([0, 0, 90]) {
    arduino(zt = 15);
}

caster_wheel(xt = 70, yt = -CASTER_WHEEL_PLATE_L / 2, zt = 6);

// Right sensor
rotate(a = 90, v = [1, 0, 0]) {
    sensor(xt = SIDE_SENSOR_FORE_AFT_OFFSET, yt = SIDE_SENSOR_HEIGHT_OFFSET, zt = 5);
}

// Left sensor
rotate(a = 270, v = [1, 0, 0]) {
    sensor(xt = SIDE_SENSOR_FORE_AFT_OFFSET, yt = -SIDE_SENSOR_HEIGHT_OFFSET, zt = 5);
}

// Front sensor
rotate([90, 0, 90]) {
    sensor(yt = FRONT_SENSOR_HEIGHT_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET);
}

rotate([0, 0, 90]) {
    tenergy_battery(xt = -TENERGY_L/2, yt = -70, zt = 12);
}

h_bridge(zt = 40);

rotate([0, 0, 90]) {
    usb_battery(xt = -USB_BATTERY_L/2, yt = -120);
}

pushbutton(zt = 60);

led(zt = 90, color = "green");

led(yt = 40, zt = 50);

led(yt = -40, zt = 50);

led(xt = 30, zt = 50);

led(xt = -30, zt = 50);

}