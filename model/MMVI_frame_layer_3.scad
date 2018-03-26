// File: MMVI_frame.scad
// Author: Aksel Thomas
// Date: 2/22/2018

// The purpose of this file is the custom frame.

include <led.scad>
include <pushbutton.scad>
include <dowel.scad>
include <arduino.scad>
include <model_constants.scad>
include <plate.scad>

GROUND_OFFSET = 16.3;

// increases the resolution of components using arcs
$fn = 100;


// For visualizing layer 3
//arduino(xt = 103.4, yt = -ARDUINO_L / 2 + 7, zt = 75);
//
//pushbutton(xt = 115 + PUSHBUTTON_BODY_L / 2, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H - 3, zt = 79 + ARDUINO_H);
//
//translate([0, 0, 79 + ARDUINO_H + 0]) {
//    // mode LED
//    led(color = "green", xt = 115 + 7.1 + LED_CASE_D, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3.25 + LED_CASE_D / 2);
//        
//    // back LED
//    led(xt = 115, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H + 3.25 + LED_CASE_D / 2);
//    
//    // right LED
//    led(xt = 156.82 - DOWEL_L - 3 - ARDUINO_BOLT_HOLE_D / 2 + 0.2, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H - 3 + LED_CASE_D / 2 + 2, rotation = true);
//    
//    // front LED
//    led(xt = 103.4 + ARDUINO_PCB_W + 6.5 + LED_CASE_D / 4, yt = H_BRIDGE_LOWER_W / 2 + 3.15 + (LED_CASE_D) / 2);
//    
//    // left LED
//    led(xt = 103.4 + ARDUINO_PCB_W + 0.5 + (LED_CASE_D - 2) / 2 + (LED_CASE_D - 2) / 2, yt = H_BRIDGE_LOWER_W / 2 + 6 + ARDUINO_BOLT_HOLE_D + (LED_CASE_D - 2) / 2, rotation = true);
//
//}

rotate([0, 180, 0]) {

// layer 3 back right portion
union() {
 
    // Pushbutton protrusion
    plate(l = PUSHBUTTON_BODY_L - 3, w = PUSHBUTTON_BODY_W, h = 4, xt = 115 + PUSHBUTTON_BODY_L / 2 + 1.5, yt = -H_BRIDGE_LOWER_W / 2 - SENSOR_TOTAL_H - 3, zt = 79 + ARDUINO_H - 4, color = "DarkViolet");
    
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

translate([-15, -30, 0]) {
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
}
}