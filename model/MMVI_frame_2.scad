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

translate([0, 0, 0]) {

// not part of the robot model
environment(xt = 0, yt = -48, zt = 0);

// For visualizing the bottom layer
//driven_wheel_system(xt = 120, zt = GROUND_OFFSET);
//tenergy_battery(yt = -TENERGY_L / 2, xt = 130, zt = -11.24 + GROUND_OFFSET);
//caster_ball(xt = 170, yt = -CASTER_BALL_HOUSING_L / 2, zt = -13.61 + GROUND_OFFSET);


// bottom layer
union() {

    // rear portion of bottom layer
    difference() {
        plate(l = 40, w = 69, h = 21, xt = 110, yt = -34.5, zt = 3, color = "DarkViolet");
        
        // motor wiring/cooling cutout
        plate(l = 10, w = 69 - 2 * DOWEL_XY_BUFFER_ZONE, h = 6, xt = 110 - MOTOR_BODY_W / 2, yt = -34.5 + DOWEL_XY_BUFFER_ZONE, zt = GROUND_OFFSET - 3, color = "DarkViolet");

        driven_wheel_system(xt = 120, zt = GROUND_OFFSET);

        // open space between motors
        plate(l = MOTOR_BODY_W, w = 62, h = MOTOR_BODY_H + 4, xt = 115, yt = -31, zt = GROUND_OFFSET  - (MOTOR_BODY_H / 2 ), color = "DarkViolet");
        
        tenergy_battery(yt = -TENERGY_L / 2, xt = 130, zt = -11.24 + GROUND_OFFSET);

        // back-right dowel
        dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -34.5 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H / 2);

        // back-left dowel
        dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = 34.5 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H / 2);

        // the holes for motor shafts
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

    // central closure between Tenergy and caster ball
    plate(l = 3.5, w = CASTER_BALL_HOUSING_L, h = 2 * CASTER_BALL_HOUSING_H + 1, xt = 166.5, yt = -CASTER_BALL_HOUSING_L / 2, zt = -10.61 + GROUND_OFFSET, color = "DarkViolet");

    difference() {
        plate(l = 20, w = TENERGY_L + 8, h = 21, xt = 150, yt = -(TENERGY_L + 8) / 2, zt = 3, color = "DarkViolet");

        // Tenergy wiring/cooling cutout
        plate(l = 4.5, w = TENERGY_L + 10, h = 12, xt = 166, yt = -(TENERGY_L + 10) / 2, zt = -11.24 + GROUND_OFFSET + TENERGY_H / 2 - 6, color = "DarkViolet");

        // required for front right dowel
        dowel(xt = 160.82 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -TENERGY_L / 2 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.24 + GROUND_OFFSET + TENERGY_H - DOWEL_H / 2);
        
        // required for front left dowel
        dowel(xt = 160.82 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = TENERGY_L / 2 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.24 + GROUND_OFFSET + TENERGY_H - DOWEL_H / 2);

        tenergy_battery(yt = -TENERGY_L / 2, xt = 130, zt = -11.24 + GROUND_OFFSET);
    }

    // front-right dowel
    difference() {
        plate(l = DOWEL_XY_BUFFER_ZONE, w = DOWEL_XY_BUFFER_ZONE, h = DOWEL_H, xt = 160.82 - DOWEL_XY_BUFFER_ZONE, yt = -TENERGY_L / 2 - DOWEL_XY_BUFFER_ZONE, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H, color = "DarkViolet");

        dowel(xt = 160.82 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -TENERGY_L / 2 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H / 2);
    }

    // front-left dowel
    difference() {
        plate(l = DOWEL_XY_BUFFER_ZONE, w = DOWEL_XY_BUFFER_ZONE, h = DOWEL_H, xt = 160.82 - DOWEL_XY_BUFFER_ZONE, yt = TENERGY_L / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H, color = "DarkViolet");

        dowel(xt = 160.82 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = TENERGY_L / 2 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H / 2);
    }


    // back-left dowel
    //difference() {
    //
    //    plate(l = DOWEL_XY_BUFFER_ZONE - 1, w = DOWEL_XY_BUFFER_ZONE, h = DOWEL_H, xt = 116 - DOWEL_XY_BUFFER_ZONE, yt = 34.5 - DOWEL_XY_BUFFER_ZONE, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H, color = "DarkViolet");
    //
    //    dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = 34.5 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H / 2);
    //
    //}

    difference() {
        // caster ball upport support
        plate(l = CASTER_BALL_HOUSING_W, w = CASTER_BALL_HOUSING_L, h = CASTER_BALL_HOUSING_H, xt = 170, yt = -CASTER_BALL_HOUSING_L / 2, zt = -10.61 + GROUND_OFFSET, color = "DarkViolet");

        caster_ball(xt = 170, yt = -CASTER_BALL_HOUSING_L / 2, zt = -13.61 + GROUND_OFFSET);

        // hole for right caster ball screw
        translate([170 + CASTER_BALL_HOUSING_W / 2, (-CASTER_BALL_HOUSING_L / 2) + (CASTER_BALL_SCREW_HOLE_D / 2) + CASTER_BALL_EDGE_TO_HOLE_L, -10.61 + GROUND_OFFSET]) {
            color("DarkViolet") {
                cylinder(d = CASTER_BALL_SCREW_HOLE_D, h = CASTER_BALL_HOUSING_H + 1);
            }
        }

        // hole for left caster ball screw
        translate([170 + CASTER_BALL_HOUSING_W / 2, (CASTER_BALL_HOUSING_L / 2) - (CASTER_BALL_SCREW_HOLE_D / 2) - CASTER_BALL_EDGE_TO_HOLE_L, -10.61 + GROUND_OFFSET]) {
            color("DarkViolet") {
                cylinder(d = CASTER_BALL_SCREW_HOLE_D, h = CASTER_BALL_HOUSING_H + 1);
            }
        }
    }
}
}

// For visualizing lower dowels
//dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -34.5 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H + 4);
//dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = 34.5 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H + 4);
//dowel(xt = 160.82 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -TENERGY_L / 2 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = 1 + GROUND_OFFSET);
//dowel(xt = 160.82 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = TENERGY_L / 2 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = 1 + GROUND_OFFSET);
    

// For visualizing 2nd layer
//side_sensor_system(xt = 115 + SENSOR_FORE_AFT_OFFSET, zt = GROUND_OFFSET + 2.5);
//rotate([-90, 0, -90]) {
//    sensor(yt = -25 - GROUND_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET + 115);
//}
//h_bridge(xt = 85 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2, zt = 10 + GROUND_OFFSET);

// middle layer
union() {

    // front right dowel
    difference() {
        plate(l = DOWEL_XY_BUFFER_ZONE, w = DOWEL_XY_BUFFER_ZONE, h = DOWEL_H + 2, xt = 160.82 - DOWEL_XY_BUFFER_ZONE, yt = -TENERGY_L / 2 - DOWEL_XY_BUFFER_ZONE, zt = 8 + GROUND_OFFSET, color = "DarkViolet");

        dowel(xt = 160.82 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -TENERGY_L / 2 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = 8 + GROUND_OFFSET);
    }

    // connector between front right dowel support & middle layer
    plate(l = DOWEL_XY_BUFFER_ZONE, w = 1, h = DOWEL_H + 2, xt = 160.82 - DOWEL_XY_BUFFER_ZONE, yt = -TENERGY_L / 2, zt = 8 + GROUND_OFFSET, color = "DarkViolet");

    // front left dowel
    difference() {
        plate(l = DOWEL_XY_BUFFER_ZONE, w = DOWEL_XY_BUFFER_ZONE, h = DOWEL_H + 2, xt = 160.82 - DOWEL_XY_BUFFER_ZONE, yt = TENERGY_L / 2, zt = 8 + GROUND_OFFSET, color = "DarkViolet");

        dowel(xt = 160.82 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = TENERGY_L / 2 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = 8 + GROUND_OFFSET);
    }

    // connector between front left dowel support & middle layer
    plate(l = DOWEL_XY_BUFFER_ZONE, w = 1, h = DOWEL_H + 2, xt = 160.82 - DOWEL_XY_BUFFER_ZONE, yt = TENERGY_L / 2 - 1, zt = 8 + GROUND_OFFSET, color = "DarkViolet");



difference() {

    // exposes ~3 mm of each side sensor barrel
    plate(l = H_BRIDGE_LOWER_L + SENSOR_TOTAL_H - 1, w = H_BRIDGE_LOWER_W + 2 * SENSOR_TOTAL_H - 6, h = H_BRIDGE_UPPER_H + .85, xt = 103, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3, zt = 8 + GROUND_OFFSET, color = "DarkViolet");

    // back right dowel
    dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -34.5 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H + 4);

    dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = 34.5 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H + 4);

    // front-right dowel
    difference() {
        plate(l = DOWEL_XY_BUFFER_ZONE, w = DOWEL_XY_BUFFER_ZONE, h = DOWEL_H, xt = 160.5 - DOWEL_XY_BUFFER_ZONE, yt = -TENERGY_L / 2 - DOWEL_XY_BUFFER_ZONE, zt = -11.248 + GROUND_OFFSET + TENERGY_H, color = "blue");

        dowel(xt = 160.5 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -TENERGY_L / 2 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H / 2);
    }

    // box representing H-bridge & extra space to sides & front
    plate(l = H_BRIDGE_LOWER_L + 6, w = H_BRIDGE_LOWER_W + 5, h = H_BRIDGE_UPPER_H, xt = 82.5 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2 - 2.5, zt = 13.5 + GROUND_OFFSET, color = "DarkViolet");
      
    // provides sunken platform for H-bridge  
    plate(l = H_BRIDGE_LOWER_L, w = H_BRIDGE_LOWER_W, h = H_BRIDGE_UPPER_H, xt = 85 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2, zt = 10 + GROUND_OFFSET, color = "DarkViolet");

    side_sensor_system(xt = 115 + SENSOR_FORE_AFT_OFFSET, zt = GROUND_OFFSET + 2.5);

    // side-of-H-bridge wiring cutouts (x2)
    plate(l = H_BRIDGE_LOWER_L, w = SENSOR_TOTAL_H, h = 3.75, xt = 105.33, yt = -39, zt = 13.5 + GROUND_OFFSET, color = "DarkViolet");
    
    plate(l = H_BRIDGE_LOWER_L, w = SENSOR_TOTAL_H, h = 3.75, xt = 105.33, yt = 22 + SENSOR_PINS_H, zt = 13.5 + GROUND_OFFSET, color = "DarkViolet");

    // hollows out H-bridge platform
    plate(l = H_BRIDGE_LOWER_L - 3.6, w = H_BRIDGE_LOWER_W - 3.6, h = 6, xt = 85 + SENSOR_FORE_AFT_OFFSET + 1.8, yt = -H_BRIDGE_LOWER_W / 2 + 1.8, zt = 5 + GROUND_OFFSET, color = "DarkViolet");

    rotate([-90, 0, -90]) {
        sensor(yt = -25 - GROUND_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET + 115);
    }
    
    // reduces height of frame above front sensor
    plate(l = SENSOR_TOTAL_H, w = SENSOR_PCB_W, h = 10, xt = SENSOR_FORE_AFT_OFFSET + 115 + 11, yt = -SENSOR_PCB_W / 2, zt = 35 + GROUND_OFFSET, color = "DarkViolet");

    // cooling slot below front sensor
    plate(l = SENSOR_TOTAL_H, w = H_BRIDGE_LOWER_W - 4, h = 3.15, xt = SENSOR_FORE_AFT_OFFSET + 115 + 11, yt = -H_BRIDGE_LOWER_W / 2 + 2, zt = 11.661 + GROUND_OFFSET, color = "DarkViolet");

}

    // back-right dowel
//difference() {
//
//    plate(l = DOWEL_XY_BUFFER_ZONE - 1, w = DOWEL_XY_BUFFER_ZONE, h = DOWEL_H - 5.25, xt = 116 - DOWEL_XY_BUFFER_ZONE, yt = -34.5, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H + 10.25, color = "DarkViolet");
//
////    plate(l = DOWEL_L, w = DOWEL_W, h = DOWEL_H - 7.25, xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -34.5 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H + 10.25, color = "Blue");
//    
//        dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -34.5 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H + 4);
//
//    
//    //dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -34.5 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H + 9);
//
//}


}

//    plate(l = SENSOR_TOTAL_H, w = H_BRIDGE_LOWER_W - 4, h = 3, xt = SENSOR_FORE_AFT_OFFSET + 115 + 11, yt = -H_BRIDGE_LOWER_W / 2 + 2, zt = 11.661 + GROUND_OFFSET, color = "Gray");


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
    
arduino(xt = 20, zt = 50 + GROUND_OFFSET);

modified_led_system(zt = 75, xt = -20);

pushbutton(zt = 90, yt = 15);
