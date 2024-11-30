PROYECTO MYSHELL 
El proyeto consiste en una produccion/simulacion de un SHELL basado en Sistema Operativo de Ubuntu.
El SHELL desarrollado maneja distintos comandos aplicados para distintas funciones, ejecutadas en una terminal que muestra todos
los resultados a los comandos y los argumentos que el usuario provee.
	
	-COMANDOS:
		Para el manejo del SHELL a traves de terminal, contamos con  los siguientes comandos:
			DIR: Estando en un directorio, ejecutar este comando dara como resultado la impresion de todos los archivos que este directorio/carpeta contiene, dandole un argumento del
			nombre de una carpeta existente, permitira mostrar los arvhicos contenidos en esa carpeta.
			Ejemplo: dir /home
			CD: Permite cambiar el directorio actual, moviendo a un un directorio que puede ser el predecesor al directorio actual, o puede ser uno que se encuentra
			dentro del directorio actual.
			Ejemplo: cd /
			ENVIRON:Muestra todas las variables de entorno del SHELL, siendo un ejemplo: HOME(directorio principal del sistema),LANG(idioma predeterminado),
			entre otros.
			HELP:El comando imprimira, por partes, en pantalla las funcionalidades de todos los comandos presentes en el SHELL, pulsando ENTER, la impresion
			del texto continuara hasta que el archivo termine de ser leido.
			ECHO: Imprime en pantalla o redirecciona a un archivo el argumento que recibe junto al comando.
			Ejemplo: Hola Mundo!
			PAUSE:Pausa la ejecucion del SHELL.
			QUIT: Termina el proceso y apaga el SHELL.

	-REDIRECCIONAMIENTO:
		Funcion del SHELL que permite copiar:
			-Un cierto texto de una parte del SHELL a un archivo.
			-Sacar informacion de un archivo e imprimirlo en el SHELL.
			-Obtener la informacion de un archivo y guardarlo dentro de otro.
		La funcion de redireccion se basa en el manejo de los caracteres "<" y ">", estos siendo interpretados por el SHELL para poder ejecurtar una funcion distinta:
			- "<" Obtendra la informacion contenida en el archivo seleccionado.
			- ">" La informacion es enviada a un archivo (En caso de no existir sera creado).
			- ">>" La informacion que sera redireccionada, contara con un append, lo que hara que la informacion anterior del archivo se almacene y se añada esta nueva.
		Ejemplo: echo < in > out
 	
	-EJECUCION EN SEGUNDO PLANO:
		Cualidad del SHELL que permite ejecutarse en distintas terminales, al mismo tiempo.
		Podemos iniciar nuestro SHELL desde terminales diferentes con el comando ./myshell, el cual llamara al SHELL para ser ejecutado las veces que sea necesario, permitiendo su uso simultaneo.
