// File: back_wheel.scad
// Author: Aksel Thomas
// Date: 12/15/2017

module back_wheel(xt=0, yt=0, zt=0, color=[.2, .2, .2]) {

color(color)
{
    wheel_r = 36;
    wheel_w = 13; //includes nub
    translate([xt, yt, zt]) {
        rotate(a=90, v=[1,0,0]) {
            cylinder(r=wheel_r, h=wheel_w, center = true);
        }
    }
}

}
