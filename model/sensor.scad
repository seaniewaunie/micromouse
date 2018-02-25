//Scott Bohon
//MM6
//Sensor
//Date: 12/15/2017

include <model_constants.scad>;

module sensor (xt = 0, yt = 0, zt = 0) {
   
    translate([xt, yt, zt]) {
    
        //sensor speaker1
        translate([SENSOR_DISTANCE_BW_BARREL_FOCI / 2, 0, SENSOR_BARREL_H / 2 + SENSOR_PCB_H]) {
            color("silver")
            cylinder(d = SENSOR_BARREL_D, h = SENSOR_BARREL_H, center = true);
        }
        
        //sensor speaker2
        translate([-SENSOR_DISTANCE_BW_BARREL_FOCI / 2, 0, SENSOR_BARREL_H / 2 + SENSOR_PCB_H]) {
            color("silver")
            cylinder(d = SENSOR_BARREL_D, h = SENSOR_BARREL_H, center = true);
        }
        
        //sensor pcb
        translate([0, 0, SENSOR_PCB_H]) {
            rotate(a = 0, v = [1, 0, 0]) {
                color("blue")
                cube([SENSOR_PCB_W, SENSOR_PCB_L, SENSOR_PCB_H], center = true);
            }
        }
        
        translate([0, -(SENSOR_PCB_L / 2 + SENSOR_PINS_L / 2) + SENSOR_PINS_OFFSET, SENSOR_PCB_H / 2 - SENSOR_PINS_H / 2]) {
            color("silver") {
                cube([SENSOR_PINS_W, SENSOR_PINS_L, SENSOR_PINS_H], center = true);
            }
        }
        
        translate([-SENSOR_CAP_L / 2, SENSOR_PCB_L / 2 - SENSOR_CAP_W, SENSOR_PCB_H + SENSOR_CAP_H / 2]) {
            color("silver") {
                cube([SENSOR_CAP_L, SENSOR_CAP_W, SENSOR_CAP_H]);
            }
        }

        translate([-SENSOR_CAP_L / 2, -SENSOR_PCB_L / 2, SENSOR_PCB_H + SENSOR_CAP_H / 2]) {
            color("silver") {
                cube([SENSOR_SOLDER_JOINT_L, SENSOR_SOLDER_JOINT_W, SENSOR_SOLDER_JOINT_H]);
            }
        }

        
    }
}
