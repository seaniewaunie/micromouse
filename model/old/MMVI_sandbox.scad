// File: MMVI_sandbox.scad
// Author: Aksel Thomas
// Date: 2/2/2018

// The purpose of this file is to be a sandbox for viewing various
// components.
// The units are in mm.

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

arduino(xt = 0, yt = 0, zt = 0);

motor(xt = 0, yt = 20, zt = 50);

sensor(xt = 0, yt = -20, zt = -50);

back_wheel(xt = 0, yt = -60, zt = 0);

tenergy_battery(xt = 0, yt = 60, zt = 0);

pushbutton(xt = 0, yt = 50, zt = 30);

h_bridge(xt = 0, yt = 50, zt = -60);

caster_wheel(xt = 0, yt = -120, zt = 0);