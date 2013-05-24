/** \file command.h
 *
 * \brief Construcción de comandos X10.
 * Estructuras y prototipos de función que permiten definir códigos de
 * transmisión X10 para poder enviarlos al CM11 por el puerto serie.
 *
 * \author Enrique Barbeito Garcia
 */

#ifndef COMMAND_H
#define	COMMAND_H

/*! número de comandos. valor fijo */
#define NCMD 128

/*! número total de códigos de casa */
#define NHCODE 16

/*! valor mínimo de un código de casa */
#define MIN_HCODE 'A'

/*! valor máximo de un código de casa */
#define MAX_HCODE 'P'

/*! valor mínimo de un código de dispositivo */
#define MIN_DCODE  1

/*! valor máximo de un código de dispositivo */
#define MAX_DCODE 16

/*! valor máximo de una regulación DIM */
#define MAX_DIM   22

/*! constantes para códigos de casa */
typedef enum {
	A, B, C, D,
	E, F, G, H,
	I, J, K, L,
	M, N, O, P  } hcode_t;

/*! constantes de códigos de función */
typedef enum {
	ON,
	OFF,
	DIM,
	BRIGHT } fcode_t;

extern unsigned char hcode []; /* vector con valores de cada código de casa */
extern unsigned char dcode []; /* vector con valores de cada código de dispositivo */
extern unsigned char fcode []; /* vector con valores de cada código de función */

/**
 estructura de datos de un comando para enviar por el puerto serie.
 puede ser un comando de dirección (is_address=1) o de función (=0).
 */
struct command
{
	unsigned char header; /* 8bit cabecera dirección|función */
	unsigned char code;   /* 8bit código dirección|función   */
	unsigned char code_l; /* 4bit MSB del campo code         */
	unsigned char code_r; /* 4bit LSB del campo code         */
	int is_address;       /* representa dirección o función? */
};

/**
 * Devuelve una lista de comandos inicializados a valores por defecto.
 * @return vector fijo de NCMD posiciones con la lista de comandos inicializada.
 */
struct command * command_init (void);

/**
 * Comprueba si un código ya ha sido introducido en la lista de comandos.
 * @param cmd lista de comandos donde comprobar existencia de código.
 * @param ncmd dimensión de la lista de comandos.
 * @param code código a comprobar.
 * @return posición en lista donde está el código. 0 en caso de no existir.
 */
int command_exist (const struct command *, const int, const unsigned char);

/**
 * Libera el espacio de memoria reservado de la lista de comandos.
 * @param cmd puntero a la lista de comandos.
 */
void command_free (struct command *);

/**
 * construcción de la lista de comandos para enviar al CM11.
 * @param cmd lista de comandos inicialmente vacía.
 * @param argc número de argumentos pasados desde línea de comandos.
 * @param argv matriz de argumentos pasados desde línea de comandos.
 * @return número de comandos en total añadidos a la lista.
 */
int command_make (struct command *, int, char **);

/**
 * obtención del índice en el vector de códigos de casa.
 * @param c código de casa en formato caracter [A..P]
 * @return índice del vector del código de casa dado.
 */
hcode_t get_hcode (const char);

/**
 * obtención del valor de regulación DIM en función a un porcentaje.
 * @param percent porcentaje de regulación [0..10].
 * @return valor de regulación DIM entre [0..22].
 */
unsigned char get_regulation (int);

#endif	/* COMMAND_H */
