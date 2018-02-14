// File: MMVI_layout.scad
// Author: Aksel Thomas
// Date: 2/2/2018

// The purpose of this file is to lay out the components roughly where
// they will go in relation to each other in the robot.

include <driven_wheel_system.scad>
include <environment.scad>
include <side_sensor_system.scad>
include <led.scad>;
include <arduino.scad>;
include <32_mm_wheel.scad>;
include <plate.scad>;
include <motor.scad>;
include <sensor.scad>;
include <tenergy_battery.scad>;
include <usb_battery.scad>;
include <pushbutton.scad>;
include <h_bridge.scad>;
include <caster_wheel.scad>;
include <caster_ball.scad>;
include <wall_segment.scad>;
include <model_constants.scad>;

SENSOR_FORE_AFT_OFFSET = 20;

FRONT_SENSOR_FORE_AFT_OFFSET = 15;
FRONT_SENSOR_HEIGHT_OFFSET = 22;
GROUND_OFFSET = -16;

translate([0, 0, -GROUND_OFFSET]) {

$fn = 100;  // increases the resolution of components using arcs

environment(xt = 70, yt = 44, zt = GROUND_OFFSET);

driven_wheel_system();
    
arduino(xt = 20, zt = 50);

rotate([0, 0, 90]) {
    caster_ball(xt = -CASTER_BALL_HOUSING_L / 2, yt = -61, zt = -11.1);
}

side_sensor_system(xt = SENSOR_FORE_AFT_OFFSET);

// Front sensor
rotate([270, 0, 270]) {
    sensor(yt = -FRONT_SENSOR_HEIGHT_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET + SENSOR_FORE_AFT_OFFSET);
}

h_bridge(xt = -6 + SENSOR_FORE_AFT_OFFSET, zt = 25);

tenergy_battery(yt = -TENERGY_L/2, xt = 10, zt = -12);

translate([0, 0, 30]) {

    pushbutton(zt = 60);

    led(zt = 90, color = "green");

    led(yt = 40, zt = 50);

    led(yt = -40, zt = 50);

    led(xt = 15, zt = 50);

    led(xt = -25, zt = 50);
}

}