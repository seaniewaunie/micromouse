//units in mm

include <led.scad>;
include <arduino.scad>;
include <back_wheel.scad>;
include <plate.scad>;
include <motor.scad>;
include <sensor.scad>;
include <tenergy_battery.scad>;
include <pushbutton.scad>;
include <h_bridge.scad>;
include <caster_wheel.scad>;
include <model_constants.scad>;

led(xt = 0, yt = -10, zt = 50, color = "red");

// Not sure if we need a plate
// plate();

arduino();

translate([0, 20, 50]) {
motor();
}

translate([0, -20, -50]) {
sensor();
}

back_wheel(xt = 0, yt = -60, zt = 0);

tenergy_battery(xt = 0, yt = 60, zt = 0);

pushbutton(xt = 0, yt = 50, zt = 30);

h_bridge(xt = 0, yt = 50, zt = -60);

caster_wheel(xt = 0, yt = -120, zt = 0);