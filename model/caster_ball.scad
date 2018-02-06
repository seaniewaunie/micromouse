// File: caster_ball.scad
// Author: Aksel Thomas
// Date: 2/06/2018

include <model_constants.scad>

HOUSING_L = 19.05;
HOUSING_W = 13;
HOUSING_H = 6.35;
BALL_D = 9.5;

module caster_ball(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        rotate(a = 90, v = [0, 0, 1]) {        
            color([0.2, 0.2, 0.2]) {
                cube([HOUSING_L, HOUSING_W, HOUSING_H]);
            }
            color("silver") {
                
                translate([HOUSING_L / 2, HOUSING_W / 2, 0]) {
                    sphere(d = 9.5);
                }
            }
        }
    }
}