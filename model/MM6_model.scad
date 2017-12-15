//units in mm

//sensor
sensor_barrel_r = 8;
sensor_barrel_h = 12;
sensor_pcb_l = 21;
sensor_pcb_w = 46;
sensor_pcb_h = 3;
sensor_total_h = 15;


//center plate
translate([])
{
    cube([70, 54, 0.1], center = true);
}

//arduino
arduino_l = 70;
arduino_w = 54;
arduino_h = 15;
color([0,0.5,0.5])
{
translate([0,0,arduino_h/2])
{
    cube([arduino_l, arduino_w, arduino_h], center = true);
}
}

//wheel1
color([0,0,0])
{
wheel_r = 36;
wheel_w = 13;//includes nub
rotate(a=90, v=[1,0,0])
{
    translate([0,0,-(arduino_w/2 + wheel_w/2)])
    {
        cylinder(r=wheel_r, h=wheel_w, center = true);
    }
}

//wheel2
rotate(a=90, v=[1,0,0])
{
    translate([0,0,30])
    {
        cylinder(r=wheel_r, h=wheel_w, center = true);
    }
}
}