//TEST 阿國
#include <assert.h>
#include <string.h>

#include <termio.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <qstring.h>
#include <stdbool.h>
#include <stdio.h>
#include <qstring.h>
#define debug
//com.example.test1

//phoebe test!!
int dev_Open(QString strPort , bool isusb )
{
    struct termio tio;
    int tty_fd;
    const char *port;

    bool isusb_flag;
    isusb_flag = isusb;
    char out[4] ;

    out[0]='\x30';
    out[1]='\x31';
    out[2]='\x0a';
    out[3]='\x0d';
    if (isusb_flag)
    {
        printf ("printer usb flag = true \n");
    }
    if (strPort == NULL)
        return -1;

    port = strPort.toStdString().c_str();
    printf ("get port name : %s \n" , port);

   // tty_fd = open(port, O_RDWR );
    if (!isusb_flag)
    {
   printf("is OPENING RS232 DEVICE\n" );
        tty_fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    }else
    {
           printf("is OPENING USB DEVICE\n port = _ %s _\n" ,port );
           tty_fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    }


    if (tty_fd == -1 )
    {
     printf("open port fail -> rtn = %d \n" ,tty_fd);
         return -1;
    }else
    {
      printf( "open port  pass\n" );
    }

    if (!isusb_flag)
    {
       printf ("is RS232 DEVICE\n" );
    if (ioctl(tty_fd, TCGETA, &tio)){
            close(tty_fd);
            return -1;
        }

        tio.c_iflag &= ~( INLCR | ICRNL | IUCLC | ISTRIP | BRKINT);
        tio.c_iflag = tio.c_iflag | IGNBRK | IGNPAR;
        tio.c_oflag &= ~( OPOST );
        tio.c_lflag &= ~( ECHO | ISIG | ICANON);
        tio.c_cflag |= (CLOCAL | CREAD);
        tio.c_cflag = (tio.c_cflag & ~CBAUD) | B2400;
        tio.c_cflag &= ~(PARENB | PARODD); // no parity
        tio.c_cflag = (tio.c_cflag & ~CSIZE) | CS8;
        tio.c_cflag &= ~CSTOPB; // 1 stop bit; If CSTOPB is set, two stop bits are used.

        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=0;


        if (ioctl(tty_fd, TCSETA, &tio)){
            close(tty_fd);
            return -1;
        }
    }

    return tty_fd;
}
int dev_Close( int fd)
{
    int rtn=0 ;
    if (fd == -1)
    {
        return -1;
    }
#ifdef debug

    rtn = close(fd);
     printf("close port -> rtn = %d \n" ,rtn);
    return rtn;
#else
     printf("port closed\n");
    return close(fd);
#endif
}


int dev_Write( int fd, QString strBuffer)
{
    const char *buffer;
    int total_bytes = 0;
    int buffer_len;
    int i =0;
#ifdef debug
    if (fd == -1)
    {
         printf("write port fail-> fd = -1 \n");
            return -1;
    }
    if (strBuffer == NULL)
    {
        printf("write port fail-> strBuffer = null \n");
        return -1;
    }
    buffer = strBuffer.toStdString().c_str();

        if (buffer == NULL)
            return -1;

        buffer_len = strBuffer.length();

        if (buffer_len <=0 )
            return 0;
        total_bytes = write(fd, buffer, buffer_len);

        printf("write length = %d -> total_bytes = %d \n show data in below \n " ,buffer_len,total_bytes);

        for (i =0 ; i < buffer_len ; i++)
        {

            printf(" %x " ,buffer[i]);
        }
        printf("\n" );

#else
    if (fd == -1)
        return -1;
    if (strBuffer == NULL)
        return -1;

    buffer = strBuffer.toStdString().c_str();
    if (buffer == NULL)
        return -1;
     buffer_len = strBuffer.length();
    if (buffer_len <=0 )
        return 0;
    total_bytes = write(fd, buffer, buffer_len);

#endif
    usleep(1000);
    return total_bytes;
}


#define MAX_BUFFER_LEN 64
QString dev_Read(int fd)  //read for scanner
{
    char buffer[MAX_BUFFER_LEN];
    char outbuffer[MAX_BUFFER_LEN];
    int bytes;
    int i = 0 ;
    if (fd == -1)
        return NULL;

    // printf("ReadByte -> ready to read \n");
     memset(outbuffer,0x00,sizeof(outbuffer));
      memset(buffer,0x00,sizeof(buffer));
    bytes = read(fd,(char *) buffer, MAX_BUFFER_LEN-1);
    if (bytes == -1)
    {        

        memset(buffer,0x00,sizeof(buffer));
        buffer[0] = '\0';

    }else if (bytes >0)
    {
        buffer[bytes-1] = '\0';
      //  printf("ReadByte ->counts = %d  , buffer = %s \n" ,bytes ,buffer);
    }
    QString str = QString(buffer);
   //  printf("ReadByte -> read bytes -> %d \n" , bytes);

/*
    for (i= 0 ; i < bytes ; i ++)
    {
          printf("Read Byte -> %d ibytes = %x \n" ,i,buffer[i]);

    }*/
  // memcpy(outbuffer,buffer,sizeof(buffer));
  // sprintf(outbuffer,buffer);
  // printf("outbuffer ->  ibytes = %x %x %x %x %x \n" ,buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);

   return str;

}

int dev_SetSpeed( int fd, int speed)
{
    struct termio tio;

    if (fd == -1)
        return -1;

    if (ioctl(fd, TCGETA, &tio))
        return -1;

    switch (speed) {
    case 1200:
        tio.c_cflag = (tio.c_cflag & ~CBAUD) | B1200;
        break;
    case 2400:
        tio.c_cflag = (tio.c_cflag & ~CBAUD) | B2400;
        break;
    case 4800:
        tio.c_cflag = (tio.c_cflag & ~CBAUD) | B4800;
        break;
    case 9600:
        tio.c_cflag = (tio.c_cflag & ~CBAUD) | B9600;
        break;
    case 19200:
        tio.c_cflag = (tio.c_cflag & ~CBAUD) | B19200;
        break;
    case 38400:
        tio.c_cflag = (tio.c_cflag & ~CBAUD) | B38400;
        break;
    case 57600:
        tio.c_cflag = (tio.c_cflag & ~CBAUD) | B57600;
        break;
    case 115200:
        tio.c_cflag = (tio.c_cflag & ~CBAUD) | B115200;
        break;
    case 230400:
        tio.c_cflag = (tio.c_cflag & ~CBAUD) | B230400;
        break;
    }
    printf("Set Speed -> rate = %d \n" ,speed);
    if (ioctl(fd, TCSETA, &tio))
        return -1;

    return 0;
}





