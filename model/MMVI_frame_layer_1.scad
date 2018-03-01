// File: MMVI_frame.scad
// Author: Aksel Thomas
// Date: 2/22/2018

// The purpose of this file is the custom frame.

include <plate.scad>
include <driven_wheel_system.scad>
include <tenergy_battery.scad>
include <caster_ball.scad>
include <dowel.scad>
include <model_constants.scad>
include <environment.scad>

GROUND_OFFSET = 16.3;

// increases the resolution of components using arcs
$fn = 100;

translate([0, 0, 0]) {

// not part of the robot model
//environment(xt = 0, yt = -48, zt = 0);

// For visualizing the bottom layer
//driven_wheel_system(xt = 120 + 1, zt = GROUND_OFFSET);
//tenergy_battery(yt = -TENERGY_L / 2, xt = 130, zt = -11.24 + GROUND_OFFSET);
//caster_ball(xt = 170, yt = -CASTER_BALL_HOUSING_L / 2, zt = -13.61 + GROUND_OFFSET);

// bottom layer
union() {

    // rear portion of bottom layer
    difference() {
        plate(l = 40, w = 69, h = 21, xt = 110, yt = -34.5, zt = 3, color = "DarkViolet");

        // Tenergy floor cutouts
        plate(l = TENERGY_W, w = 12, h = 6, xt = 130, yt = -6 + TENERGY_L / 5, zt = 2, color = "DarkViolet");

        plate(l = TENERGY_W, w = 12, h = 6, xt = 130, yt = -6 - TENERGY_L / 5, zt = 2, color = "DarkViolet");

        // motor wiring/cooling cutout
        plate(l = 6.1, w = 5.5 + MOTOR_BODY_L, h = 15, xt = 109, yt = -2.75 - MOTOR_BODY_L / 2, zt = GROUND_OFFSET - MOTOR_BODY_H / 2, color = "DarkViolet");

        driven_wheel_system(xt = 120 + 1, zt = GROUND_OFFSET);

        // open space between motors
        plate(l = MOTOR_BODY_W + 2, w = 62, h = MOTOR_BODY_H + 4, xt = 115, yt = -31, zt = GROUND_OFFSET  - (MOTOR_BODY_H / 2 ), color = "DarkViolet");
        
        // open space between motors
        plate(l = MOTOR_BODY_W + 2, w = MOTOR_BODY_L, h = MOTOR_BODY_H + 4, xt = 115, yt = 17.2 - MOTOR_BODY_L / 2, zt = GROUND_OFFSET  - (MOTOR_BODY_H / 2 ), color = "DarkViolet");

        // open space between motors
        plate(l = MOTOR_BODY_W + 2, w = MOTOR_BODY_L, h = MOTOR_BODY_H + 4, xt = 115, yt = -17.2 - MOTOR_BODY_L / 2, zt = GROUND_OFFSET  - (MOTOR_BODY_H / 2 ), color = "DarkViolet");
        
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
