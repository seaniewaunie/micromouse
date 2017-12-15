//units in mm

include <led.scad>;
include <arduino.scad>;
include <back_wheel.scad>;
include <plate.scad>;
include <motor.scad>;
include <sensor.scad>;

led(xt=0, yt=-10, zt=40, color="red");

plate();

arduino();

translate([0, 20, 50]) {
motor();
}

translate([0, -20, -50]) {
sensor();
}

back_wheel(xt=0, yt=-60, zt=0);