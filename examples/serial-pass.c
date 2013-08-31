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

//This variable is used throughout to refer to the file that represents the
// usb line.
int fd; 

void terminate (int param)
{
    write(0, "Terminating program: %d\n", param);
    int n=0,c=0;
    while(c=close(fd) && n<1024){ n++; }
    if( c!=0 ){ printf("Close failed; returned: %d, file interger: %d\n", c,fd); }
    exit(1);
}

int main(int argc, const char* argv[])
{
//Run this function when interrupt.(for instance when control-C)
    signal(SIGINT,terminate); 
//Gets baudrate, defaultly 9600. If it doesnt match communication will fail.
    int baudrate = B9600; 
    if( argc>2 ){ baudrate = identify_baud_str(argv[2]); }
    if( baudrate==-1 ){ printf("Baudrate not recognized."); }
//Get integer representing the file, again looks if you provided which file you wanted.
    fd = serial_open(argc>1 ? argv[1] :"/dev/ttyUSB0", baudrate);

//Starts by printing some info for you.
    if( argc>1){ printf("file %s\n", argv[1]); }
    if( argc>2)
    { printf("baudrate %s (%d) : ('termios code' %d)\n", argv[2],atoi(argv[2]),baudrate); }
    if( fd<0 )
    { printf("fd looks wrong(%d), probably opening failed, exiting.\n", fd); return fd; }
    printf("started (%d)\n", fd);

    while(1)
    {   char byte; //Gives is some memory to work with.
        if( read(fd,&byte,1)==1 ) //See if anything received..
        {   while(write(0,&byte,1)!=1){}; } //If so, echo back.
        
        if( read(0,&byte,1)==1 ) //If user enters data in stdin, write it.
        {   while(write(fd,&byte,1)!=1){} }
    }
}
