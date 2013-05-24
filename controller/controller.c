#include <stdlib.h>
#include "controller.h"
#include "serial.h"

#define PCOM "COM2"

int controller_get (FILE *fd, unsigned char *b1, unsigned char *b2)
{
	return fscanf (fd, "%c %c ", b1, b2);
}

int controller_run (void)
{
	FILE *fin = stdin;          /* los comandos se leerán de fin */
	int ack = 0;                /* transmisión realizada con éxito */
	unsigned char byte1 = '\0'; /* primer byte leído */
	unsigned char byte2 = '\0'; /* segundo byte leído */
	unsigned char byter = '\0'; /* byte recibido del CM11 (checksum y IREADY) */
	unsigned char checksum = 0; /* suma de comprobación */
	int i;

	if (!serial_open (PCOM))
	{
		fprintf (stderr, "No se ha podido abrir el puerto %s\n", PCOM);
		return EXIT_FAILURE;
	}

	/* lectura de comandos desde la entrada indicada (fin) */
	for (; controller_get (fin, &byte1, &byte2) != EOF; ack = 0)
	{
		do  /* envíar bytes hasta recibir confirmación del CM11 */
		{
			/* envío al puerto serie del par de bytes leídos de la entrada indicada */
			fprintf (stdout, "\nEnviando 0x%.2X 0x%.2X ...\n", byte1, byte2);
			serial_write (byte1);
			serial_write (byte2);

			/* cálculo de la suma de comprobación. con checksum &= 0xFF se
			   fija una márcara para desechar acarreo y no desbordar 1 byte */
			checksum = byte1 + byte2;
			checksum &= 0xFF;

			/* el CM11 envía un checksum. lo recogemos del puerto serie */
			serial_read (&byter);
			fprintf (stdout, "Bytes enviados.\n"
							 " - Checksum calculado: 0x%.2X\n"
							 " - Checksum  recibido: 0x%.2X\n", checksum, byter);

			/* enviar un ACK cuando el checksum recibido coincida
			   los checksum deben coincidir, sino reenviar bytes */
			if (checksum == byter)
			{
				for (i = 0; byter != IREADY; ++i)
				{
					/* enviar ACK hasta recibir IREADY */
					fprintf (stdout, "OK. Enviando ACK(%d) ...\n", i);
					serial_write ((unsigned char)0x0);
					serial_read (&byter);
				}

				fprintf (stdout, "ACK enviado. Interfaz preparada.\n");
				ack = 1; /* recibido IREADY. no volver a enviar bytes */
			}
			else
				fprintf (stderr, "Los checksum NO coinciden. Reenviando bytes.\n\n");

		}
		while (!ack);
	}

	/* cierre del puerto serie y finalización del controlador */
	serial_close ();
	return EXIT_SUCCESS;
}
