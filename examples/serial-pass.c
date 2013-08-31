
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

int main(int argc, const char* argv[])
{
    signal(SIGINT,terminate);
    int baudrate = B9600;
    if( argc>2 ){ baudrate = identify_baud_str(argv[2]); }
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
