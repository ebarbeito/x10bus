#ifndef SERIAL_H
#define	SERIAL_H

#include <windows.h>

/* variables para utilización de puertos serie */
HANDLE idComDev;
OVERLAPPED ov;
DCB dcb;
DWORD n;

int serial_open (const char *);
void serial_close (void);
void serial_read (unsigned char *);
void serial_write (unsigned char);

#endif	/* SERIAL_H */
