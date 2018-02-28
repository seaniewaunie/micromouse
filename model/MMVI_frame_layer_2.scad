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
include <dowel.scad>
include <model_constants.scad>

SENSOR_FORE_AFT_OFFSET = 20;
FRONT_SENSOR_FORE_AFT_OFFSET = 15 + SENSOR_FORE_AFT_OFFSET;
GROUND_OFFSET = 16.3;

// increases the resolution of components using arcs
$fn = 100;


// For visualizing 2nd layer
//side_sensor_system(xt = 115 + SENSOR_FORE_AFT_OFFSET, zt = GROUND_OFFSET + 2.5);
//rotate([-90, 0, -90]) {
//    sensor(yt = -25 - GROUND_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET + 115);
//}
//h_bridge(xt = 85.4 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2, zt = 10 + GROUND_OFFSET);

// middle layer
union() {

    // bottom front right dowel
    difference() {
        plate(l = DOWEL_XY_BUFFER_ZONE, w = DOWEL_XY_BUFFER_ZONE, h = DOWEL_H + 2, xt = 160.82 - DOWEL_XY_BUFFER_ZONE, yt = -TENERGY_L / 2 - DOWEL_XY_BUFFER_ZONE, zt = 8 + GROUND_OFFSET, color = "DarkViolet");

        dowel(xt = 160.82 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -TENERGY_L / 2 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = 8 + GROUND_OFFSET);
    }

    // connector between bottom front right dowel support & middle layer
    plate(l = DOWEL_XY_BUFFER_ZONE, w = 1, h = DOWEL_H + 2, xt = 160.82 - DOWEL_XY_BUFFER_ZONE, yt = -TENERGY_L / 2, zt = 8 + GROUND_OFFSET, color = "DarkViolet");

    // bottom front left dowel
    difference() {
        plate(l = DOWEL_XY_BUFFER_ZONE, w = DOWEL_XY_BUFFER_ZONE, h = DOWEL_H + 2, xt = 160.82 - DOWEL_XY_BUFFER_ZONE, yt = TENERGY_L / 2, zt = 8 + GROUND_OFFSET, color = "DarkViolet");

        dowel(xt = 160.82 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = TENERGY_L / 2 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = 8 + GROUND_OFFSET);
    }

    // connector between bottom front left dowel support & middle layer
    plate(l = DOWEL_XY_BUFFER_ZONE, w = 1, h = DOWEL_H + 2, xt = 160.82 - DOWEL_XY_BUFFER_ZONE, yt = TENERGY_L / 2 - 1, zt = 8 + GROUND_OFFSET, color = "DarkViolet");

difference() {

    // exposes ~3 mm of each side sensor barrel
    plate(l = 57.42, w = H_BRIDGE_LOWER_W + 2 * SENSOR_TOTAL_H - 6, h = H_BRIDGE_UPPER_H + .85, xt = 103.4, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3, zt = 8 + GROUND_OFFSET, color = "DarkViolet");

    // top back right dowel
    // ~4 mm into top of layer 2
    dowel(xt = 103.4 + 1, yt = -33.2, zt = GROUND_OFFSET + 33.8);

    // top back left dowel
    // ~4 mm into top of layer 2
    dowel(xt = 103.4 + 1, yt = 33.2 - DOWEL_W, zt = GROUND_OFFSET + 33.8);

    // top front right dowel
    // ~4 mm into top of layer 2
    dowel(xt = 156.82 - DOWEL_L - 3, yt = -32.2, zt = GROUND_OFFSET + 33.8);

//    // top front left dowel
//    // ~5 mm into top of layer 2
//    dowel(xt = 160.82 - DOWEL_L - 3, yt = 31.2 - DOWEL_W, zt = GROUND_OFFSET + 32.8);

    // bottom back right dowel
    dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -34.5 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H + 4);

    // bottom back left dowel
    dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = 34.5 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H + 4);

    // box representing H-bridge & extra space to sides & front
    plate(l = SENSOR_PCB_W + 2 + SENSOR_PINS_H, w = H_BRIDGE_LOWER_W + 4.5, h = H_BRIDGE_UPPER_H, xt = 115 + SENSOR_FORE_AFT_OFFSET - 9 - SENSOR_PCB_W / 2, yt = -H_BRIDGE_LOWER_W / 2 - 2.25, zt = 13.5 + GROUND_OFFSET, color = "DarkViolet");
      
    // provides sunken platform for H-bridge  
    plate(l = H_BRIDGE_LOWER_L, w = H_BRIDGE_LOWER_W, h = H_BRIDGE_UPPER_H, xt = 85.4 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2, zt = 10 + GROUND_OFFSET, color = "DarkViolet");

    side_sensor_system(xt = 115 + SENSOR_FORE_AFT_OFFSET, zt = GROUND_OFFSET + 2.5);

    // right-side-of-H-bridge wiring cutout
    plate(l = H_BRIDGE_LOWER_L, w = SENSOR_TOTAL_H, h = 3.75, xt = 115 + SENSOR_FORE_AFT_OFFSET - 7 - SENSOR_PCB_W / 2, yt = -39, zt = GROUND_OFFSET + 2.5 + 22 - SENSOR_PCB_L / 2 - .7, color = "DarkViolet");
    
    // left-side-of-H-bridge wiring cutout
    plate(l = H_BRIDGE_LOWER_L, w = SENSOR_TOTAL_H, h = 3.75, xt = 115 + SENSOR_FORE_AFT_OFFSET - 7 - SENSOR_PCB_W / 2, yt = 22 + SENSOR_PINS_H, zt = GROUND_OFFSET + 2.5 + 22 - SENSOR_PCB_L / 2 - .7, color = "DarkViolet");

    // hollows out H-bridge platform
    plate(l = H_BRIDGE_LOWER_L - 3.6, w = H_BRIDGE_LOWER_W - 3.6, h = 6, xt = 85.4 + SENSOR_FORE_AFT_OFFSET + 1.8, yt = -H_BRIDGE_LOWER_W / 2 + 1.8, zt = 5 + GROUND_OFFSET, color = "DarkViolet");

    rotate([-90, 0, -90]) {
        sensor(yt = -25 - GROUND_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET + 115);
    }
    
    // reduces height of frame above front sensor
    plate(l = SENSOR_TOTAL_H, w = SENSOR_PCB_W, h = 10, xt = SENSOR_FORE_AFT_OFFSET + 115 + 11, yt = -SENSOR_PCB_W / 2, zt = 35 + GROUND_OFFSET, color = "DarkViolet");

    // cooling slot below front sensor
    plate(l = SENSOR_TOTAL_H, w = H_BRIDGE_LOWER_W - 4, h = 3.16, xt = SENSOR_FORE_AFT_OFFSET + 115 + 11, yt = -H_BRIDGE_LOWER_W / 2 + 2, zt = 25 + GROUND_OFFSET - SENSOR_PCB_L / 2 - 3.15, color = "DarkViolet");

}

}
