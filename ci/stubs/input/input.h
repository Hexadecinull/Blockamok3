#pragma once
struct controller_data_s {
    int up,down,left,right,a,b,x,y,lb,rb,ls,rs,start,back,lt,rt;
    short s1_x,s1_y,s2_x,s2_y;
};
void usb_do_poll(void);
void get_controller_data(struct controller_data_s *cd,int port);
