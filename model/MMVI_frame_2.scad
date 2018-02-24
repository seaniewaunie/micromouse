// File: MMVI_frame.scad
// Author: Aksel Thomas
// Date: 2/22/2018

// The purpose of this file is the custom frame.

include <driven_wheel_system.scad>
include <environment.scad>
include <side_sensor_system.scad>
include <led_system.scad>
include <modified_led_system.scad>
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

union() {

difference() {

    plate(l = 40, w = 69, h = 21, xt = 110, yt = -34.5, zt = 3, color = "DarkViolet");
    
    plate(l = 10, w = 69 - 2 * DOWEL_XY_BUFFER_ZONE, h = 6, xt = 110 - MOTOR_BODY_W / 2, yt = -34.5 + DOWEL_XY_BUFFER_ZONE, zt = GROUND_OFFSET - 3, color = "DarkViolet");


    driven_wheel_system(xt = 120, zt = GROUND_OFFSET);

    plate(l = MOTOR_BODY_W, w = 62, h = MOTOR_BODY_H + 4, xt = 115, yt = -31, zt = GROUND_OFFSET  - (MOTOR_BODY_H / 2 ), color = "DarkViolet");
    
    tenergy_battery(yt = -TENERGY_L / 2, xt = 130, zt = -11.24 + GROUND_OFFSET);

    rotate([90, 0, 0]) {
        translate([120, GROUND_OFFSET, -35.5]) {
            color("DarkViolet") {
                cylinder(d = 5, h = MOTOR_SHAFT_H / 2, center="true");
            }
        }
    }

    rotate([90, 0, 0]) {
        translate([120, GROUND_OFFSET, 30]) {
            color("DarkViolet") {
                cylinder(d = 5, h = MOTOR_SHAFT_H / 2, center="true");
            }
        }
    }    
}

plate(l = 3.5, w = CASTER_BALL_HOUSING_L, h = CASTER_BALL_HOUSING_H, xt = 166.5, yt = -CASTER_BALL_HOUSING_L / 2, zt = -10.61 + GROUND_OFFSET, color = "DarkViolet");

difference() {

    plate(l = 20, w = TENERGY_L + 8, h = 21, xt = 150, yt = -(TENERGY_L + 8) / 2, zt = 3, color = "DarkViolet");

    plate(l = 4.5, w = TENERGY_L + 10, h = 12, xt = 166, yt = -(TENERGY_L + 10) / 2, zt = -11.24 + GROUND_OFFSET + TENERGY_H / 2 - 6, color = "DarkViolet");


    tenergy_battery(yt = -TENERGY_L / 2, xt = 130, zt = -11.24 + GROUND_OFFSET);

}

difference() {
    plate(l = CASTER_BALL_HOUSING_W, w = CASTER_BALL_HOUSING_L, h = CASTER_BALL_HOUSING_H, xt = 170, yt = -CASTER_BALL_HOUSING_L / 2, zt = -10.61 + GROUND_OFFSET, color = "DarkViolet");

    caster_ball(xt = 170, yt = -CASTER_BALL_HOUSING_L / 2, zt = -13.61 + GROUND_OFFSET);

}
}

//difference() {
//
//    // exposes 1 mm of top of H-bridge & 3 mm of each side sensor barrel
//    plate(l = H_BRIDGE_LOWER_L + SENSOR_TOTAL_H - 1, w = H_BRIDGE_LOWER_W + 2 * SENSOR_TOTAL_H - 6, h = H_BRIDGE_UPPER_H, xt = 103, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3, zt = 8 + GROUND_OFFSET, color = "DarkViolet");
//
//    // box representing H-bridge & extra space to sides & front
//    plate(l = H_BRIDGE_LOWER_L + 6, w = H_BRIDGE_LOWER_W + 5, h = H_BRIDGE_UPPER_H, xt = 82.5 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2 - 2.5, zt = 13.5 + GROUND_OFFSET);
//        
//    plate(l = H_BRIDGE_LOWER_L, w = H_BRIDGE_LOWER_W, h = H_BRIDGE_UPPER_H, xt = 85 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2, zt = 10 + GROUND_OFFSET);
//
//    side_sensor_system(xt = 115 + SENSOR_FORE_AFT_OFFSET, zt = GROUND_OFFSET);
//
//    //h_bridge(xt = 85 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2, zt = 9 + GROUND_OFFSET);
//    rotate([-90, 0, -90]) {
//        sensor(yt = -25 - GROUND_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET + 115);
//    }
//}
//
//difference() {
//
//    // about 5 mm to place Arduino into
//
//    plate(l = ARDUINO_W + 14, w = ARDUINO_L + 4, h = ARDUINO_H, xt = 98, yt = -ARDUINO_L / 2 - 2, zt = 50 + GROUND_OFFSET, color = "DarkViolet");
//
//    arduino(xt = 137, zt = 60 + GROUND_OFFSET);
//    
//    plate(l = ARDUINO_W + 16, w = ARDUINO_L + 6, h = ARDUINO_H, xt = 97, yt = -ARDUINO_L / 2 - 3, zt = 58 + GROUND_OFFSET, color = "DarkViolet");
//
//    modified_led_system(zt = 75, xt = 104);
//
//}

    //led_system(zt = 75, xt = 104);

driven_wheel_system(zt = GROUND_OFFSET);
    
side_sensor_system(xt = SENSOR_FORE_AFT_OFFSET, zt = GROUND_OFFSET);

h_bridge(xt = -30 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2, zt = 9 + GROUND_OFFSET);

// Front sensor
rotate([-90, 0, -90]) {
    sensor(yt = -25 - GROUND_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET);
}

tenergy_battery(yt = -TENERGY_L/2, xt = 10, zt = -12 + GROUND_OFFSET);

caster_ball(xt = 48, yt = -CASTER_BALL_HOUSING_L / 2, zt = -13.61 + GROUND_OFFSET);

arduino(xt = 20, zt = 50 + GROUND_OFFSET);

modified_led_system(zt = 75, xt = -20);

pushbutton(zt = 90, yt = 15);
