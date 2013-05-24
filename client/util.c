#include <ctype.h>
#include <string.h>
#include "util.h"

void argv_toupper (int argc, char **argv)
{
	int i, j;

	/* recorrido de argumentos caracter por caracter */
	/* convertir caracteres entre [a..z] a mayúscula */
	for (i = 1; i < argc; ++i)
		for (j = 0; j < (int)strlen (argv[i]); ++j)
			if (argv[i][j] >= 'a' && argv[i][j] <= 'z')
				argv[i][j] = toupper (argv[i][j]);
}
