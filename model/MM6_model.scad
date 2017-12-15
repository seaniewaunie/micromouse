//units in mm

include <led.scad>;
include <arduino.scad>;
include <back_wheel.scad>;
include <plate.scad>;

led(xt=0, yt=0, zt=40, color="green");

plate();

arduino();

back_wheel(xt=0, yt=-60, zt=0);