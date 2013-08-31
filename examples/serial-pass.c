
//Written by Jasper den Ouden
//Released into the public domain

#include "../serial.c"
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int fd;

void terminate (int param)
{
    write(0, "Terminating program: %d\n", param);
    int n=0,c=0;
    while(c=close(fd) && n<1024){ n++; }
    if( c!=0 ){ printf("Close failed; %d", c); }
    exit(1);
}

int id_baud(int i) //Figure baud rate.
{
switch(i)
{   case 0: return B0;

case 50: return B50;

case 75: return B75;

case 110: return B110;

case 134: return B134;

case 150: return B150;

case 200: return B200;

case 300: return B300;

case 600: return B600;

case 1200: return B1200;

case 1800: return B1800;

case 2400: return B2400;

case 4800: return B4800;

case 9600: return B9600;

case 19200: return B19200;

case 38400: return B38400;
}
return -1;
}

int main(int argc, const char* argv[])
{
    signal(SIGINT,terminate);
    int baudrate = B9600;
    if( argc>2 ){ baudrate = id_baud(atoi(argv[2])); }
    if( baudrate==-1 ){ printf("Baudrate not recognized."); }
    fd = serial_open(argc>1 ? argv[1] :"/dev/ttyACM0", baudrate);

    if( argc>1){ printf("file %s\n", argv[1]); }
    if( argc>2)
    { printf("baudrate %s (%d) : ('termios code' %d)\n", argv[2],atoi(argv[2]),baudrate); }
    if( fd<0 ){ printf("fd looks wrong(%d), exiting.\n", fd); return fd; }
    printf("started (%d)\n", fd);

    while(1)
    {   char byte;
        if( read(fd,&byte,1)==1 )
        { write(0,&byte,1); }
        if( read(0,&byte,1)==1 ){ while(write(fd,&byte,1)!=1){ write(0,&byte,1); } }
    }
}
