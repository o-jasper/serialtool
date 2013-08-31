//serial.c
//serialtool
//
// Created by Árpád Goretity on 18/02/2012, modified by Jasper den Ouden.
// Released into the public domain

#include "serial.h"

int serial_open(const char *device, int baud)
{	
    struct termios tio;
    memset(&tio, 0, sizeof(tio));
    
// Open serial port in mode `8N1', non-blocking 
    tio.c_cflag = CS8 | CREAD | CLOCAL;
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 5;
    
    int fd = open(device, O_RDWR | O_NONBLOCK);
    
//Note that `baud' is not an actual baud rate number;
//it's one of the constants (e. g., `B9600') in <termios.h>
    cfsetospeed(&tio, baud);
    cfsetispeed(&tio, baud);
    tcsetattr(fd, TCSANOW, &tio);
    
    return fd;
}

//Note: if you understand pointers, might aswel just use read/write.
//(those are in unistd.h FTR)
uint8_t serial_recv(int fd)
{   uint8_t byte;
    read(fd, &byte, 1);
    return byte;
}

void serial_send(int fd, uint8_t byte)
{   write(fd, &byte, 1); }

int identify_baud(int i)
{   switch(i)
    {   
    case 0: return B0;            
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
int identify_baud_str(const char* str) 
{   return identify_baud(atoi(str)); }
