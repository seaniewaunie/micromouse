// File: caster_ball.scad
// Author: Aksel Thomas
// Date: 2/06/2018

include <model_constants.scad>

module caster_ball(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        color([0.2, 0.2, 0.2]) {
            cube([CASTER_BALL_HOUSING_W, CASTER_BALL_HOUSING_L, CASTER_BALL_HOUSING_H]);
        }
        color("silver") {
            
            translate([CASTER_BALL_HOUSING_W / 2, CASTER_BALL_HOUSING_L / 2, 0]) {
                sphere(d = 9.5);
            }
        }
    }
}
