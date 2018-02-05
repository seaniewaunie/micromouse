// File: usb_battery.scad
// Author: Aksel Thomas
// Date: 2/5/2018

include <model_constants.scad>;

module usb_battery(xt = 0, yt = 0, zt = 0, color = "dodgerblue") {
    color(color) {
        translate([xt, yt, zt]) {
            cube([USB_BATTERY_L, USB_BATTERY_W, USB_BATTERY_H]);
        }
    }
}