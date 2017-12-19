//Scott Bohon
//MM6
//Sensor
//Date: 12/15/2017

include <model_constants.scad>;

module sensor () {
    
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
}
