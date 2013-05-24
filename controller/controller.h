/** \file controller.h
 *
 * \brief Controlador / driver CM11.
 * Estructuras y prototipos de función que declaran un controlador sencillo para
 * transmitir códigos X20 al CM11 vía puerto serie.
 *
 * \author Enrique Barbeito Garcia
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include <stdio.h>

/** interfaz preparada para recibir. OK for transmission */
#define IREADY 0x55

/**
 * obtención, desde la entrada indicada, del par de bytes de envío al CM11.
 * @param fichero de entrada donde recoger los datos.
 * @param primer byte leído.
 * @param segundo byte leído.
 * @return EOF cuando se ha leído todo el fichero, 0 en caso contrario.
 */
int controller_get (FILE *, unsigned char *, unsigned char *);

/**
 * punto de entrada a la lógica del controlador.
 * @return EXIT_SUCCESS si todo fue bien, EXIT_FAILURE en caso contrario.
 */
int controller_run (void);

#endif	/* CONTROLLER_H */
