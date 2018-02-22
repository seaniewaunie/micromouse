// File: MMVI_frame.scad
// Author: Aksel Thomas
// Date: 2/22/2018

// The purpose of this file is the custom frame.

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
environment(xt = 0, yt = -48, zt = 0);

difference() {

    plate(l = 40, w = 62, h = 25, xt = 110, yt = -31, zt = 4, color = "DarkViolet");

    driven_wheel_system(xt = 120, zt = GROUND_OFFSET);

    plate(l = MOTOR_BODY_W, w = 62, h = MOTOR_BODY_H / 2 + 2, xt = 115, yt = -31, zt = GROUND_OFFSET + (MOTOR_BODY_H / 2) - 1, color = "DarkViolet");
    
    tenergy_battery(yt = -TENERGY_L / 2, xt = 130, zt = -6.24 + GROUND_OFFSET);
    
}


difference() {

    plate(l = 20, w = TENERGY_L + 8, h = 25, xt = 150, yt = -(TENERGY_L + 8) / 2, zt = 4, color = "DarkViolet");

    tenergy_battery(yt = -TENERGY_L / 2, xt = 130, zt = -6.24 + GROUND_OFFSET);

}

driven_wheel_system(zt = GROUND_OFFSET);
    
side_sensor_system(xt = SENSOR_FORE_AFT_OFFSET, zt = GROUND_OFFSET);

h_bridge(xt = -30 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2, zt = 9 + GROUND_OFFSET);

// Front sensor
rotate([-90, 0, -90]) {
    sensor(yt = -20 - GROUND_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET);
}

tenergy_battery(yt = -TENERGY_L/2, xt = 10, zt = -12 + GROUND_OFFSET);

caster_ball(xt = 48, yt = -CASTER_BALL_HOUSING_L / 2, zt = -13.61 + GROUND_OFFSET);

arduino(xt = 20, zt = 50 + GROUND_OFFSET);

led_system(zt = 100, xt = 20);

pushbutton(zt = 90, yt = 15);
