//Scott Bohon
//MM6
//Sensor
//Date: 12/15/2017

//units in mm
//sensor

module sensor ()
{
    sensor_barrel_r = 8;
    sensor_barrel_h = 12;
    sensor_pcb_l = 21;
    sensor_pcb_w = 46;
    sensor_pcb_h = 3;
    sensor_total_h = 15;
    distance_bw_speaker_foci = 30;
    
    //sensor speaker1
    
    translate([distance_bw_speaker_foci/2, 0, sensor_barrel_h/2+sensor_pcb_h]){
       color("silver")
        cylinder(r=sensor_barrel_r, h=sensor_barrel_h, center = true);
    }
    
    //sensor speaker2
    translate([-distance_bw_speaker_foci/2, 0, sensor_barrel_h/2+sensor_pcb_h]){
        color("silver")

        cylinder(r=sensor_barrel_r, h=sensor_barrel_h, center = true);
    }
    //sensor pcb
    translate([0,0,sensor_pcb_h]){
    rotate(a=0, v=[1,0,0]){
        color("blue")
        cube([sensor_pcb_w,sensor_pcb_l,sensor_pcb_h], center = true);
    }
    }
    
}

sensor();