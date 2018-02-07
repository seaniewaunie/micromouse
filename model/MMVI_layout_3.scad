// File: MMVI_layout.scad
// Author: Aksel Thomas
// Date: 2/2/2018

// The purpose of this file is to lay out the components roughly where
// they will go in relation to each other in the robot.

include <led.scad>;
include <arduino.scad>;
include <32_mm_wheel.scad>;
include <plate.scad>;
include <motor.scad>;
include <sensor.scad>;
include <tenergy_battery.scad>;
include <usb_battery.scad>;
include <pushbutton.scad>;
include <h_bridge.scad>;
include <caster_wheel.scad>;
include <caster_ball.scad>;
include <wall_segment.scad>;
include <model_constants.scad>;

WHEEL_OFFSET = 45;
MOTOR_OFFSET_FROM_WHEEL = -28.5;
SIDE_SENSOR_HEIGHT_OFFSET = 25;
SIDE_SENSOR_FORE_AFT_OFFSET = -7;
FRONT_SENSOR_FORE_AFT_OFFSET = 15;
FRONT_SENSOR_HEIGHT_OFFSET = 22;
GROUND_OFFSET = -16;

translate([0, 0, -GROUND_OFFSET]) {

$fn = 100;  // increases the resolution of components using arcs

translate([75, 0, GROUND_OFFSET]) {

    // The ground (not part of the model, shown for reference)
    plate(l = 180, w = 180, yt = 39, color="palegreen");

    // Wall (not part of the model)
    wall_segment(xt = -WALL_SEGMENT_L / 2, yt = 125);

}

translate([5, 0, 0]) {
    // Right back wheel and motor
    // Assumes the motor output shaft overlaps wheel by 6 mm
    32_mm_wheel(yt = WHEEL_OFFSET);
    rotate(a = 90, v = [0, 0, 1]) {
        motor(xt = WHEEL_OFFSET + MOTOR_OFFSET_FROM_WHEEL);
    }

    // Left back wheel and motor
    // Assumes the motor output shaft overlaps wheel by 6 mm
    rotate(a = 180, v = [1, 0, 0]) {
        32_mm_wheel(yt = WHEEL_OFFSET);
    }
    rotate(a = 270, v = [0, 0, 1]) {
        motor(xt = WHEEL_OFFSET + MOTOR_OFFSET_FROM_WHEEL);
    }
}

rotate([0, 0, 90]) {
    arduino(yt = -30, zt = 50);
}

rotate([0, 0, 90]) {
    caster_ball(xt = -CASTER_BALL_HOUSING_L / 2, yt = -61, zt = -11.1);
}

translate([30, 0, 0]) {

    // Right sensor
    rotate([90, 180, 0]) {
        sensor(xt = -SIDE_SENSOR_FORE_AFT_OFFSET, yt = -SIDE_SENSOR_HEIGHT_OFFSET, zt = 22);
    }

    // Left sensor
    rotate([270, 0, 0]) {
        sensor(xt = SIDE_SENSOR_FORE_AFT_OFFSET, yt = -SIDE_SENSOR_HEIGHT_OFFSET, zt = 22);
    }

    // Front sensor
    rotate([270, 0, 270]) {
        sensor(yt = -FRONT_SENSOR_HEIGHT_OFFSET, zt = FRONT_SENSOR_FORE_AFT_OFFSET);
    }

    h_bridge(xt = -6, zt = 25);
}

rotate([0, 0, 90]) {
    tenergy_battery(xt = -TENERGY_L/2, yt = -47, zt = -12);
}

//rotate([0, 90, 90]) {
//    usb_battery(xt = -83, yt = -65, zt = 27);
//}

rotate([0, 0, 90]) {
    usb_battery(xt = -USB_BATTERY_L/2, yt = -88, zt = -13);
}

translate([0, 0, 30]) {

    pushbutton(zt = 60);

    led(zt = 90, color = "green");

    led(yt = 40, zt = 50);

    led(yt = -40, zt = 50);

    led(xt = 15, zt = 50);

    led(xt = -25, zt = 50);
}

}