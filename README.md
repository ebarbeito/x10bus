#Interfaz para servicios de control mediante bus domótico X10
Sistema de control de buses domóticos compatibles con el protocolo X10. Consta de cuatro partes: un cliente de comandos X10, el controlador CM11a, controlador de puerto serie y el servidor CM11 en un ejecutable Win32.

Para la compilación y generación de ejecutables se ha utilizado el toolkit MinGW (Minimalist GNU for Windows, http://www.mingw.org/).

##Notas de uso rápidas
###Compilación con make
Requiere gcc.exe y make.exe en el PATH. Abrir una terminal. Dentro del directorio del proyecto:

```$ make_bin.bat # crea ejecutables cliente.exe y controlador.exe
$ make_clean.bat # limpia ficheros .o y .exe creados por make_bin.bat
```

###Compilación manual
Abrir una terminal. Dentro del directorio del proyecto:

```$ cd serial
$ gcc -ansi -Wall -W -g -c serial.c -o serial.o
$ cd ..\controller
$ gcc -ansi -Wall -W -g -I..\serial ..\serial\serial.o *.c -o ..\controller.exe
$ cd ..\client
$ gcc -ansi -Wall -W -g *.c -o ..\client.exe
$ cd ..
```

###Prueba del proyecto
Abrir dos terminales y situarlos en el directorio del proyecto:

* Terminal del servidor: `$ server\cm11server.exe COM1`
* Terminal del cliente: `$ client A1 A2 DIM10 | controller`

###Prueba alternativa (solo prueba del cliente)
Se puede probar el cliente ejecutándolo por separado. Mostrar por pantalla la lista de bytes en formato carácter que enviará al controlador en caso de concatenarle su salida a la entrada del mismo mediante una tubería.

```$ client a1 b2 c2 d7 on dim10 off
? f ?  ? . ?  ? b ?  ? " ?  ? d ?  ? $ ?  ? c ?  ? # ? 
```

##Agradecimientos
A mi amigo Marcos A. S. por estar siempre ahí para ayudar. Eres un crack! ;)

##Licencia
GPL
