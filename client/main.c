#include "client.h"
#include "util.h"

int main (int argc, char **argv)
{
	/* normalización de argumentos para simplificar el cliente */
	argv_toupper (argc, argv);

	/* inicialización del cliente */
	return client_run (argc, argv);
}
