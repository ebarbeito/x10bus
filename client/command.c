#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "util.h"

unsigned char hcode [] = {
	/*A*/ 0x6, /*B*/ 0xE, /*C*/ 0x2, /*D*/ 0xA,
	/*E*/ 0x1, /*F*/ 0x9, /*G*/ 0x5, /*H*/ 0xD,
	/*I*/ 0x7, /*J*/ 0xF, /*K*/ 0x3, /*L*/ 0xB,
	/*M*/ 0x0, /*N*/ 0x8, /*O*/ 0x4, /*P*/ 0xC
};

unsigned char dcode [] = {
	/*  */ 0x0,
	/* 1*/ 0x6, /* 2*/ 0xE, /* 3*/ 0x2, /* 4*/ 0xA,
	/* 5*/ 0x1, /* 6*/ 0x9, /* 7*/ 0x5, /* 8*/ 0xD,
	/* 9*/ 0x7, /*10*/ 0xF, /*11*/ 0x3, /*12*/ 0xB,
	/*13*/ 0x0, /*14*/ 0x8, /*15*/ 0x4, /*16*/ 0xC
};

unsigned char fcode [] = {
	/* ON     */ 0x2,
	/* OFF    */ 0x3,
	/* DIM    */ 0x4,
	/* BRIGHT */ 0x5
};

char *fname [] = {
	"ON",
	"OFF",
	"DIM",
	"BRIGHT"
};

struct command * command_init (void)
{
	int i;
	struct command *result = (struct command *)malloc (NCMD * sizeof (struct command));
	if (result)
	{
		for (i = 0; i < NCMD; ++i)
		{
			result[i].header = '\0';
			result[i].code   = '\0';
			result[i].code_l = '\0';
			result[i].code_r = '\0';
			result[i].is_address = 0;
		}
	}

	return result;
}

int command_exist (const struct command *cmd, const int ncmd, const unsigned char code)
{
	int result = 0;
	int i;

	for (i = 0; !result && i < ncmd; ++i)
		if (cmd[i].code == code)
			result = i;

	return result;
}

void command_free (struct command *cmd)
{
	if (cmd != NULL)
	{
		free (cmd);
		cmd = NULL;
	}
}

int command_make (struct command *cmd, int argc, char **argv)
{
	int result = 0;
	struct command *cmd_func;    /* comandos de función */
	unsigned char header = '\0';
	unsigned char code = '\0';
	int i, j, ncmd = 0, nfunc = 0;

	/* inicialización del lista de comandos de función */
	cmd_func = command_init ();
	if (cmd_func == NULL)
		return result;

	/* argumentos de entrada a lista de comandos */
	for (i = 1; i < argc; ++i, code = '\0')
	{
		/* argumento introducido inválido, desechar */
		if (argv[i][0] < MIN_HCODE || argv[i][0] > MAX_HCODE)
			continue;

		/* el argumento es una dirección */
		if (atoi(argv[i]+1) >= MIN_DCODE && atoi(argv[i]+1) <= MAX_DCODE)
		{
			code = hcode[get_hcode(argv[i][0])] << 4;
			code |= dcode[atoi(argv[i]+1)];

			/* desechar comandos repetidos */
			if (!command_exist (cmd, result, code))
			{
				cmd[result].header = 0x4;
				cmd[result].code = code;
				cmd[result].code_l = hcode[get_hcode(argv[i][0])];
				cmd[result].code_r = dcode[atoi(argv[i]+1)];
				cmd[result].is_address = 1;
				result++;
			}
		}
		/* caso contrario: se trata de una función */
		else
		{
			/* función ON */
			if (!strcmp (argv[i], fname[ON]))
			{
				header = 0x6;
				code = fcode[ON];
			}
			/* función OFF */
			else if (!strcmp (argv[i], fname[OFF]))
			{
				header = 0x6;
				code = fcode[OFF];
			}
			/* función DIM */
			else if (argv[i][0] == 'D' && argv[i][1] == 'I' && argv[i][2] == 'M' &&
			    strlen (argv[i]) <= 6)
			{
				header = get_regulation (atoi (argv[i]+3));
				header = header << 3;
				header |= 0x6;
				code = fcode[DIM];
			}

			/* función válida: recoger código (sin repetidos) */
			if (code != '\0')
			{
				if (!command_exist (cmd_func, nfunc, code))
				{
					cmd_func[nfunc].header = header;
					cmd_func[nfunc].code = code;
					cmd_func[nfunc].is_address = 0;
					nfunc++;
				}
			}
		}
	}

	/* inserción de comandos de función a la lista de comandos */
	for (i = 0; i < nfunc; ++i)
		for (j = 0, ncmd = result, code = '\0'; j < ncmd; ++j)
		{
			code = cmd[j].code_l << 4;
			code |= cmd_func[i].code;

			if (!command_exist (cmd, result, code))
			{
				cmd[result].header = cmd_func[i].header;
				cmd[result].code = code;
				cmd[result].code_l = cmd[j].code_l;
				cmd[result].code_r = cmd_func[i].code;
				cmd[result].is_address = 0;
				result++;
			}
		}

	command_free (cmd_func);
	return result;
}

hcode_t get_hcode (const char c)
{
	hcode_t result;

	switch (c)
	{
	case 'A' : result = A; break;
	case 'B' : result = B; break;
	case 'C' : result = C; break;
	case 'D' : result = D; break;
	case 'E' : result = E; break;
	case 'F' : result = F; break;
	case 'G' : result = G; break;
	case 'H' : result = H; break;
	case 'I' : result = I; break;
	case 'J' : result = J; break;
	case 'K' : result = K; break;
	case 'L' : result = L; break;
	case 'M' : result = M; break;
	case 'N' : result = N; break;
	case 'O' : result = O; break;
	case 'P' : result = P; break;
	default  :             break;
	}

	return result;
}

unsigned char get_regulation (int percent)
{
	unsigned char result = 0x0;

	/* percent es un porcentaje [0..100] */
	if (percent >= 0 && percent <= 100)
		result = MAX_DIM * percent / 100;
	
	return result;
}
