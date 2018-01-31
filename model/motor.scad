//Scott Bohon
//MM6
//motor
//Date: 12/15/2017

include <model_constants.scad>;

module motor (xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        //body
        translate([0, 0, 0]) {
            color("gold")
            cube([MOTOR_BODY_L, MOTOR_BODY_W, MOTOR_BODY_H], center = true);
        }  
       
        //shaft
        rotate(a = 90, v = [0, 1, 0]) {
            translate([0, 0, MOTOR_SHAFT_H / 2 + MOTOR_BODY_L / 2]) {
                color("silver")
                cylinder(d = MOTOR_SHAFT_D, h = MOTOR_SHAFT_H, center = true);
            }
        }
    }
}
