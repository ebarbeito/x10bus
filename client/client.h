/** \file client.h
 *
 * \brief Cliente / interfaz CM11.
 * Estructuras y prototipos de función que declaran una interfaz de usuario
 * sencilla para pasarle comandos al CM11.
 *
 * \author Enrique Barbeito Garcia
 */

#ifndef CLIENT_H
#define	CLIENT_H

/*! argumento para mostrar ayuda por pantalla. */
#define ARG_HELP "-H"

/**
 * muestra ayuda por pantalla del programa cliente.
 * @param app nombre del ejecutable.
 */
void apphelp (const char *);

/**
 * muestra información por pantalla del programa cliente.
 * @param app nombre del ejecutable.
 */
void appinfo (const char *);

/**
 * punto de entrada a la lógica del cliente.
 * @param argc número de argumentos pasados desde línea de comandos.
 * @param argv matriz de argumentos pasados desde línea de comandos.
 * @return EXIT_SUCCESS si todo fue bien, EXIT_FAILURE en caso contrario.
 */
int client_run (int, char **);

#endif	/* CLIENT_H */
