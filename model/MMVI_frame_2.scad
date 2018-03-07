// File: MMVI_frame.scad
// Author: Aksel Thomas
// Date: 2/22/2018

// The purpose of this file is the custom frame.

include <driven_wheel_system.scad>
include <environment.scad>
include <side_sensor_system.scad>
include <led.scad>
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
//environment(xt = 0, yt = -48, zt = 0);

// For visualizing layer 1
driven_wheel_system(xt = 120 + 1, zt = GROUND_OFFSET);
tenergy_battery(yt = -TENERGY_L / 2, xt = 130, zt = -11.24 + GROUND_OFFSET);
caster_ball(xt = 170, yt = -CASTER_BALL_HOUSING_L / 2, zt = -13.61 + GROUND_OFFSET);

// layer 1
union() {

    // rear portion of bottom layer
    difference() {
        plate(l = 40, w = 69, h = 21, xt = 110, yt = -34.5, zt = 3, color = "DarkViolet");

        // Tenergy floor cutouts
        plate(l = TENERGY_W, w = 12, h = 6, xt = 130, yt = -6 + TENERGY_L / 5, zt = 2, color = "DarkViolet");

        plate(l = TENERGY_W, w = 12, h = 6, xt = 130, yt = -6 - TENERGY_L / 5, zt = 2, color = "DarkViolet");

        // motor wiring/cooling cutout
        plate(l = 6.1, w = 5.5 + MOTOR_BODY_L, h = 15, xt = 109, yt = -2.75 - MOTOR_BODY_L / 2, zt = GROUND_OFFSET - MOTOR_BODY_H / 2, color = "DarkViolet");

        driven_wheel_system(xt = 120 + 1.5, zt = GROUND_OFFSET);

        // open space between motors
        plate(l = MOTOR_BODY_W + 3, w = 62, h = MOTOR_BODY_H + 4, xt = 115, yt = -31, zt = GROUND_OFFSET  - (MOTOR_BODY_H / 2 ), color = "DarkViolet");
        
        // open space between motors
        plate(l = MOTOR_BODY_W + 3, w = MOTOR_BODY_L, h = MOTOR_BODY_H + 4, xt = 115, yt = 17.2 - MOTOR_BODY_L / 2, zt = GROUND_OFFSET  - (MOTOR_BODY_H / 2 ), color = "DarkViolet");

        // open space between motors
        plate(l = MOTOR_BODY_W + 3, w = MOTOR_BODY_L, h = MOTOR_BODY_H + 4, xt = 115, yt = -17.2 - MOTOR_BODY_L / 2, zt = GROUND_OFFSET  - (MOTOR_BODY_H / 2 ), color = "DarkViolet");
        
        tenergy_battery(yt = -TENERGY_L / 2, xt = 130, zt = -11.24 + GROUND_OFFSET);

        // back-right dowel
        dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = -34.5 + DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H / 2);

        // back-left dowel
        dowel(xt = 115 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_L / 2, yt = 34.5 - DOWEL_XY_BUFFER_ZONE / 2 - DOWEL_W / 2, zt = -11.248 + GROUND_OFFSET + TENERGY_H - DOWEL_H / 2);

        // the holes for motor shafts
        rotate([90, 0, 0]) {
            translate([120 + 1, GROUND_OFFSET, -35.5]) {
                color("DarkViolet") {
                    cylinder(d = 5, h = MOTOR_SHAFT_H / 2, center="true");
                }
            }
        }

        rotate([90, 0, 0]) {
            translate([120 + 1, GROUND_OFFSET, 30]) {
                color("DarkViolet") {
                    cylinder(d = 5, h = MOTOR_SHAFT_H / 2, center="true");
                }
            }
        }    
    }

    difference () {
        // central closure between Tenergy and caster ball
        plate(l = 3.5, w = CASTER_BALL_HOUSING_L, h = 2 * CASTER_BALL_HOUSING_H + 1, xt = 166.5, yt = -CASTER_BALL_HOUSING_L / 2, zt = -10.61 + GROUND_OFFSET, color = "DarkViolet");
        
        // wall depression between Tenergy & caster ball
        plate(l = CASTER_BALL_HOUSING_W, w = CASTER_BALL_HOUSING_L, h = CASTER_BALL_HOUSING_H, xt = 169, yt = -CASTER_BALL_HOUSING_L / 2, zt = -13.61 + GROUND_OFFSET, color = "DarkViolet");

    }

    difference() {
        plate(l = 20, w = TENERGY_L + 8, h = 21, xt = 150, yt = -(TENERGY_L + 8) / 2, zt = 3, color = "DarkViolet");

        // Tenergy floor cutouts
        plate(l = TENERGY_W, w = 12, h = 6, xt = 130, yt = -6 + TENERGY_L / 5, zt = 2, color = "DarkViolet");

        plate(l = TENERGY_W, w = 12, h = 6, xt = 130, yt = -6 - TENERGY_L / 5, zt = 2, color = "DarkViolet");

        // wall depression between Tenergy & caster ball
        plate(l = CASTER_BALL_HOUSING_W, w = CASTER_BALL_HOUSING_L, h = CASTER_BALL_HOUSING_H, xt = 169, yt = -CASTER_BALL_HOUSING_L / 2, zt = -13.61 + GROUND_OFFSET, color = "DarkViolet");


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
    

// For visualizing layer 2
side_sensor_system(xt = 115 + SENSOR_FORE_AFT_OFFSET, zt = GROUND_OFFSET + 2.5);
rotate([-90, 0, -90]) {
    sensor(yt = -25 - GROUND_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET + 115);
}
h_bridge(xt = 85.4 + SENSOR_FORE_AFT_OFFSET, yt = -H_BRIDGE_LOWER_W / 2, zt = 10 + GROUND_OFFSET);

// layer 2
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
    //dowel(xt = 103.4 + 1, yt = 33.2 - DOWEL_W, zt = GROUND_OFFSET + 33.8);

    // top front right dowel
    // ~4 mm into top of layer 2
    dowel(xt = 156.82 - DOWEL_L - 3, yt = -32.2, zt = GROUND_OFFSET + 33.8);

//    // top front left dowel
    // ~4 mm into top of layer 2
    dowel(xt = 161.82 - DOWEL_L - 3, yt = 28.2 - DOWEL_W, zt = GROUND_OFFSET + 33.8);

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

// For visualizing layer 3
arduino(xt = 103.4, yt = -ARDUINO_L / 2 + 7, zt = 75);

translate([0, 0, 79 + ARDUINO_H + 5]) {
    // mode LED
    led(color = "green", xt = 115 + 7.1 + LED_CASE_D, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3.25 + LED_CASE_D / 2);
        
    // back LED
    led(xt = 115, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3.25 + LED_CASE_D / 2);
    
    // right LED
    led(xt = 156.82 - DOWEL_L - 3 - ARDUINO_BOLT_HOLE_D / 2 + 0.2, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H - 3 + LED_CASE_D / 2 + 2, rotation = true);
    
    
    // front LED
    led(xt = 103.4 + ARDUINO_PCB_W + 6.5 + LED_CASE_D / 4, yt = H_BRIDGE_LOWER_W / 2 + 3.15 + (LED_CASE_D) / 2);
    
    led(xt = 103.4 + ARDUINO_PCB_W + 0.5 + (LED_CASE_D - 2) / 2 + (LED_CASE_D - 2) / 2, yt = H_BRIDGE_LOWER_W / 2 + 6 + ARDUINO_BOLT_HOLE_D + (LED_CASE_D - 2) / 2, rotation = true);

}

// layer 3 back right portion
union() {
    
    // Mode LED protrusion
    difference() {
        plate(l = LED_CASE_D, w = 6, h = 4, xt = 103.4 + ARDUINO_PCB_W - 40.8 + ARDUINO_BOLT_HOLE_D / 2 + 7.1, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3, zt = 75 + ARDUINO_H, color = "DarkViolet");
        
        translate([115 + 7.1 + LED_CASE_D - (LED_CASE_D - 3) / 2, -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3.25 + LED_CASE_D / 2 - (LED_CASE_D - 2) / 2, 74 + ARDUINO_H]) {
            cube([LED_CASE_D - 3, LED_CASE_D - 2, LED_CASE_H]);
        }
    }
    
    // Back LED protrusion
    difference() {
        plate(l = LED_CASE_D, w = 6, h = 4, xt = 103.4 + ARDUINO_PCB_W - 40.8 + ARDUINO_BOLT_HOLE_D / 2 - LED_CASE_D, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3, zt = 75 + ARDUINO_H, color = "DarkViolet");
        
        translate([115 - (LED_CASE_D - 3) / 2, -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3.25 + LED_CASE_D / 2 - (LED_CASE_D - 2) / 2, 74 + ARDUINO_H]) {
            cube([LED_CASE_D - 3, LED_CASE_D - 2, LED_CASE_H]);
        }
    }    
    
    // support
    difference() {
        plate(l = ARDUINO_PCB_W - 33.7 + ARDUINO_BOLT_HOLE_D / 2, w = 6, h = ARDUINO_H + 20, xt = 103.4, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3, zt = 55, color = "DarkViolet");

        dowel(xt = 103.4 + 1, yt = -33.2, zt = GROUND_OFFSET + 32.8);
        
        // chops out to form an L-shaped support
        plate(l = ARDUINO_PCB_W - 41 + ARDUINO_BOLT_HOLE_D / 2 + 1.2, w = 8, h = 35, xt = 102.4, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 2, zt = 61, color = "DarkViolet");
    }
 
    
    // over-mounted back right bolthole
    difference() {
        plate(l = 7.1, w = 13, h = 4, xt = 103.4 + ARDUINO_PCB_W - 40.8 + ARDUINO_BOLT_HOLE_D / 2, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3, zt = 75 + ARDUINO_H, color = "DarkViolet");
 
        translate([103.4 + ARDUINO_PCB_W - 34.1376 - ARDUINO_BOLT_HOLE_D / 2, -ARDUINO_L / 2 + 7 + 1.09 + ARDUINO_BOLT_HOLE_D / 2, 69]) {
            cylinder(d = ARDUINO_BOLT_HOLE_D, h = ARDUINO_H + 17);
        }
    }
    
}

// layer 3 front right portion
union() {
    
    // Right LED protrusion
    difference() {
        plate(l = 7.1, w = 4, h = 4, xt = 103.4 + ARDUINO_PCB_W - 6.15 - ARDUINO_BOLT_HOLE_D - 2, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H - 3 + 2, zt = 75 + ARDUINO_H, color = "DarkViolet");
        
        translate([156.82 - DOWEL_L - 3 - ARDUINO_BOLT_HOLE_D / 2 - ((LED_CASE_D - 2) / 2) + 0.2, -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H - 3 + (LED_CASE_D - 3) / 2 + 2, 74 + ARDUINO_H]) {
            cube([LED_CASE_D - 2, LED_CASE_D - 3, LED_CASE_H]);
        }
    }

    // support
    difference() {
        plate(l = 7 + ARDUINO_BOLT_HOLE_D, w = 6.5, h = ARDUINO_H + 20, xt = 103.4 + ARDUINO_PCB_W - 6.15 - ARDUINO_BOLT_HOLE_D - 2, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3, zt = 55, color = "DarkViolet");
        
        dowel(xt = 156.82 - DOWEL_L - 3, yt = -32.2, zt = GROUND_OFFSET + 32.8);
        
        // chops out to form an L-shaped support
        plate(l = 10, w = 8, h = 35, xt = 103.4 + ARDUINO_PCB_W - 6.15 + 2, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 2, zt = 61, color = "DarkViolet");
        
    }
    
    // over-mounted front right bolthole
    difference() {
        plate(l = 4 + ARDUINO_BOLT_HOLE_D, w = 13, h = 4, xt = 103.4 + ARDUINO_PCB_W - 6.15 - ARDUINO_BOLT_HOLE_D - 2, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3, zt = 75 + ARDUINO_H, color = "DarkViolet");
        
        translate([103.4 + ARDUINO_PCB_W - 6.15 - ARDUINO_BOLT_HOLE_D / 2, -ARDUINO_L / 2 + 7 + 0.91 + ARDUINO_BOLT_HOLE_D / 2, 69]) {
            cylinder(d = ARDUINO_BOLT_HOLE_D, h = ARDUINO_H + 17);
        }
    }
}

// layer 3 front left portion
union() {
    
    // Front LED protrusion
    difference() {
        plate(l = LED_CASE_D - 1, w = 7.1, h = 4, xt = 103.4 + ARDUINO_PCB_W + 6.5, yt = H_BRIDGE_LOWER_W / 2 + 2.3, zt = 75 + ARDUINO_H, color = "DarkViolet");
        
        translate([103.4 + ARDUINO_PCB_W + 6.5, H_BRIDGE_LOWER_W / 2 + 2.3 + 0.6 + (LED_CASE_D - 3) / 2 + 0.15, 74 + ARDUINO_H]) {
            cube([LED_CASE_D - 3, LED_CASE_D - 2, LED_CASE_H]);
        }
    }
    
    // Left LED protrusion
    difference() {
        plate(l = 6, w = 4, h = 4, xt = 103.4 + ARDUINO_PCB_W + 0.5, yt = H_BRIDGE_LOWER_W / 2 + 6.3 + ARDUINO_BOLT_HOLE_D, zt = 75 + ARDUINO_H, color = "DarkViolet");
        
        translate([103.4 + ARDUINO_PCB_W + 0.5 + (LED_CASE_D - 2) / 2 - 0.25, H_BRIDGE_LOWER_W / 2 + 6.3 + ARDUINO_BOLT_HOLE_D, 74 + ARDUINO_H]) {
            cube([LED_CASE_D - 2, LED_CASE_D - 3, LED_CASE_H]);
        }
    }

    
    // support
    difference() {
        plate(l = 10, w = 4 + ARDUINO_BOLT_HOLE_D, h = ARDUINO_H + 20, xt = 103.4 + ARDUINO_PCB_W - 3.5, yt = H_BRIDGE_LOWER_W / 2 + 2.3, zt = 55, color = "DarkViolet");

        dowel(xt = 161.82 - DOWEL_L - 3, yt = 28.2 - DOWEL_W, zt = GROUND_OFFSET + 32.8);
        
        // chops out to form an L-shaped support
        plate(l = 5, w = 6 + ARDUINO_BOLT_HOLE_D, h = ARDUINO_H + 20, xt = 103.4 + ARDUINO_PCB_W - 4.5, yt = H_BRIDGE_LOWER_W / 2 + 1.3, zt = 61, color = "DarkViolet");

    }    

    // over-mounted front left bolthole
    difference() {
        plate(l = 12.5, w = 4 + ARDUINO_BOLT_HOLE_D, h = 4, xt = 103.4 + ARDUINO_PCB_W - 6, yt = H_BRIDGE_LOWER_W / 2 + 2.3, zt = 75 + ARDUINO_H, color = "DarkViolet");

        translate([103.4 + ARDUINO_PCB_W - 1.09 - ARDUINO_BOLT_HOLE_D / 2, ARDUINO_L / 2 + 7 - 12.27 - ARDUINO_BOLT_HOLE_D / 2, 69]) {
            cylinder(d = ARDUINO_BOLT_HOLE_D, h = ARDUINO_H + 17);
        }
    }
}


pushbutton(zt = 90, yt = 15);
