// File: MMVI_layout.scad
// Author: Aksel Thomas
// Date: 2/2/2018

// The purpose of this file is to lay out the components roughly where
// they will go in relation to each other in the robot.

include <driven_wheel_system.scad>
include <environment.scad>
include <side_sensor_system.scad>
include <led_system.scad>
include <arduino.scad>
include <sensor.scad>
include <tenergy_battery.scad>
include <pushbutton.scad>
include <h_bridge.scad>
include <caster_ball.scad>
include <model_constants.scad>

SENSOR_FORE_AFT_OFFSET = 20;
FRONT_SENSOR_FORE_AFT_OFFSET = 15 + SENSOR_FORE_AFT_OFFSET;
GROUND_OFFSET = 16.3;

// increases the resolution of components using arcs
$fn = 100;

// not part of the robot model
environment(xt = 70, yt = 44, zt = 0);

driven_wheel_system(zt = GROUND_OFFSET);
    
side_sensor_system(xt = SENSOR_FORE_AFT_OFFSET, zt = GROUND_OFFSET);

h_bridge(xt = -6 + SENSOR_FORE_AFT_OFFSET, zt = 25 + GROUND_OFFSET);

// Front sensor
rotate([-90, 0, -90]) {
    sensor(yt = -22 - GROUND_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET);
}

tenergy_battery(yt = -TENERGY_L/2, xt = 10, zt = -12 + GROUND_OFFSET);

caster_ball(xt = 48, yt = -CASTER_BALL_HOUSING_L / 2, zt = -13.61 + GROUND_OFFSET);

arduino(xt = 20, zt = 50 + GROUND_OFFSET);

led_system(zt = 100, xt = 20);

pushbutton(zt = 90, yt = 15);
