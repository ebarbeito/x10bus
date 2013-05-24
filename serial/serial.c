#include "serial.h"

/* Apertura del puerto serie COM2 */
int serial_open (const char *com)
{
	int fSuccess;

	idComDev = CreateFile(com, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if(idComDev == INVALID_HANDLE_VALUE)
		return 0;

	fSuccess = GetCommState(idComDev, &dcb);
	if(!fSuccess)
		return 0;

	dcb.BaudRate = CBR_4800;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;

	fSuccess = SetCommState(idComDev, &dcb);
	if(!fSuccess)
		return 0;

	if(!SetCommMask(idComDev, EV_RXCHAR))
	{
		SetCommMask(idComDev, 0);
		CloseHandle(idComDev);
		return 0;
	}

	return 1;
}

/* Cierre del puerto serie */
void serial_close (void)
{
	SetCommMask(idComDev, 0);
	CloseHandle(idComDev);
}

/* Lectura de 1 byte del puerto serie */
void serial_read (unsigned char *buf)
{
   DWORD x;
   COMSTAT cs;

   ClearCommError(idComDev, &x, &cs);
   ReadFile(idComDev, buf, 1, &x, &ov);
}

/* Escribir  1 byte por el puerto serie */
void serial_write (unsigned char buf)
{
   DWORD l, p;
   l = 1;
   p = 0;
   while(l) {
      if(!WriteFile(idComDev, &buf, l, &n, &ov)) {
         if(GetLastError() != 997) {
            ;/* Error de comunicación */
         }
         return;
      }
      p += n;
      l -= n;
   }
}
