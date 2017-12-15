// File: back_wheel.scad
// Author: Aksel Thomas
// Date: 12/15/2017

module back_wheel(xt=0, yt=0, zt=0, color=[.2, .2, .2]) {

color(color)
{
    wheel_d = 72;
    wheel_outside_w = 13; //includes nub
    wheel_inside_w = 8; // without nub
    nub_outside_d = 7;
    nub_inside_d = 3;
    nub_h = 5;    
    
    translate([xt, yt, zt]) {
        rotate(a=90, v=[1,0,0]) {
            difference() {
                cylinder(d=wheel_d, h=wheel_inside_w, center = true);
                cylinder(d=nub_inside_d, h=wheel_inside_w, center = true);
            }
            translate([0, 0, wheel_inside_w / 2 + nub_h / 2]) {
                difference() {
                    cylinder(d=nub_outside_d, h=nub_h, center=true);
                    cylinder(d=nub_inside_d, h=nub_h, center=true);
                }
            }
        }
    }
    
}

}