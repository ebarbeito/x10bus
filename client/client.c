#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "command.h"

void apphelp (const char *app)
{
	appinfo (app);
	fprintf (stdout, "\nParámetros:\n"
	                 "-h                              : muestra esta ayuda.\n"
	                 "comando1 [comando2 ... comandoN]: comandos de envío al CM11\n\n"
	                 "Lista de comandos:\n"
	                 "- Direcciones: A1, A2, ..., A16, B1, B2, ..., B16, ..., P1, P2, ..., P16\n"
	                 "- Funciones: ON, OFF, BRIGHT, DIM0, DIM1, DIM2, ..., DIM100\n\n"
	                 "Ejemplo: %s A1 A2 DIM10", app);
}

void appinfo (const char *app)
{
	fprintf (stdout, "Interfaz para servicios de control mediante bus domótico X10\n"
	                 "Uso: %s [-h] comando1 [comando2 ... comandoN]\n", app);
}

int client_run (int argc, char **argv)
{
	FILE *fout = stdout;         /* los comandos se escribirán en fout */
	struct command *cmd = NULL;  /* lista de comandos de entrada */
	int ncmd = 0;                /* número de comandos de entrada */
	int i;
	
	/* precondición 1: llamada con argumentos */
	if (argc == 1) {
		appinfo (argv[0]);
		return EXIT_FAILURE;
	}

	/* precondición 2: llamada a la ayuda */
	if (argc == 2 && !strcmp (argv[1], ARG_HELP)) {
		apphelp (argv[0]);
		return EXIT_SUCCESS;
	}

	/* inicialización de la lista de comandos a enviar */
	cmd = command_init ();
	if (cmd == NULL)
	{
		fprintf (stderr, "Lista de comandos no iniciada.\n");
		return EXIT_FAILURE;
	}

	/* construcción de la lista de comandos a enviar */
	ncmd = command_make (cmd, argc, argv);

	/* envío de comandos a la salida indicada */
	for (i = 0; i < ncmd; ++i)
		fprintf (fout, "%c %c ", cmd[i].header, cmd[i].code);
	
	command_free (cmd);

	return EXIT_SUCCESS;
}
