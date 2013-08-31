//Written by Jasper den Ouden
//Released into the public domain

#include "../serial.c"

#include <stdio.h>
#include <signal.h>

int fd;

void terminate (int param)
{
  printf ("Terminating program: %d\n", param);
  int n=0,c=0;
  while(c=close(fd) && n<1024){ n++; }
  if( c!=0 ){ printf("Close failed; %d", c); }
  exit(1);
}

int main()
{
  signal(SIGINT,terminate);

  fd = serial_open("/dev/ttyACM0", B57600);
  char tmp[256]; int i=0;
  printf(" loop\n");
  while(1)
    { int r=0,n=0;
      while( r!=1 )
	{ r= read(fd, tmp+i, 1);
	  /*	  if( r<0 )
	    { if( m==0 ){ printf("\n `read` error occured! %d\n", r); } 
	      m++; if( m> 1024*1024 ){ m=0; }
	    } */
	  if( r>1 ){ printf("\n Got more characters than asked for! %d\n",r);
	             return;
	  }
	  if( n++ > 1024 )
	    { tmp[i]='\0'; printf(tmp); i=0;
	      n=0;
	    }
	}	  
      if( tmp[i]=='\n' || i==254 )
	{ tmp[i+1]='\0';
	  printf(tmp); i=0;
	}
      else{ i++; }
    }
}
