// File: led.scad
// Author: Aksel Thomas
// Date: 12/15/2017

led_cylinder_r = 3;
led_cylinder_h = 9;
led_lead_r = 1/4;
led_lead_short_h = 26;
led_lead_long_h = 28;

module led(xt=0, yt=0, zt=0, color="red") {

translate([xt, yt, zt]) {

translate([0, 0, 18.5]) {
    color(color)
    cylinder(r=led_cylinder_r, h=led_cylinder_h, center = true);
}

translate([0, 1, 1]) {
    color("silver")
    cylinder(r=led_lead_r, h=led_lead_short_h, center = true);
}

translate([0, -1, 0]) {
    color("silver")
    cylinder(r=led_lead_r, h=led_lead_long_h, center = true);
}

}

}