#include "commands.hpp"
#include "utility.hpp"

// Comando cd, usa directorio como argumento y pwd para simular movimiento entre
// directorios desde el shell
void cd(string directorio, string &pwd) {
  // Si no tiene argumento, solo imprime el directorio actual
  if (!directorio.length()) {
    cout << pwd << endl;
    return;
  }
  // Se une el directorio pwd con directorio, respetando comandos relativos (./
  // ../ .)
  string temp = fusionarDirs(pwd, directorio);
  // Si es que es un directorio valido, se actualiza el pwd
  if (filesystem::is_directory(filesystem::path(temp)))
    pwd = temp;
  else
    cout << "Directorio invalido" << endl;
}
// Comando clr, hace llamado a comando clear del shell superior
void clr() { system("clear"); }
// Comando dir, pide directorio para mostrar archivos, pwd para usar la ruta
// absoluta oStream es un output stream, para redireccionar salidas, si no hay
// redireccion usa cout
void dir(string directorio, string pwd, ostream &oStream) {
  // Se une el directorio pwd con directorio, respetando comandos relativos (./
  // ../ .)
  string temp = fusionarDirs(pwd, directorio);
  // Si es que es directorio valido, se hace llamado a ls con el directorio
  // final, y se lo imprime a la salida indicada (archivo o cout)
  if (filesystem::is_directory(filesystem::path(temp)))
    oStream << ssystem(("ls " + temp).c_str()) << endl;
  else
    oStream << "Directorio invalido" << endl;
}
// Comando environ, muestra variables de entorno, tambien permite redireccion
void environ(ostream &oStream) {
  // Se abre el archivo que contiene las variables de entorno y se intenta hacer
  // lectura
  ifstream environFile("/proc/self/environ");
  if (!environFile) {
    oStream << "No se pudo acceder a las variables de entorno." << endl;
    return;
  }

  // Genera el mensake a imprimir, leyendo el archivo caracter por caracter
  string variable;
  char ch;
  while (environFile.get(ch)) {
    if (ch == '\0') {
      oStream << variable << endl; // Imprime la variable cuando encuentra '\0'
      variable = "";               // Reinicia la variable
    } else {
      variable += ch; // Añade el carácter a la variable actual
    }
  }
}
// Comando echo, imprime un mensaje arbitrario y permite redireccion de I/O
void echo(string comentario, ostream &oStream) {
  // Si el mensaje no es vacio, imprime en la salida redireccionada
  if (comentario.length())
    oStream << comentario << endl;
}
// Comando help, imprime el README.txt usando el comando more, permite
// redireccion de I/O
void help(ostream &oStream) {
  system("stty rows 2");
  string cmd = "more README.txt";
  oStream << ssystem(cmd.c_str()) << endl;
}
// Comando pause, pausa ejecucion hasta presionar una tecla
void pause() {
  cout << "Shell pausado, pulse ENTER para continuar" << endl;
  cin.ignore();
}

// Maneja las llamadas de comandos externos
void general(string cmd, string arg) { system((cmd + arg).c_str()); }

// Maneja todas las llamadas a comandos, encargandose de redireccion de I/O y
// comandos externos
bool commands(string cmd, string arg, string redir, string &pwd) {
  // Separa el string de redireccion general, en nombres de archivos
  // individuales
  string input, output;
  bool append = 0;
  getInOutRedir(redir, input, output, append);

  // Crea el stream de salida para archivos
  ofstream fileStream;
  bool redirToFile = 0;
  if (output.length()) {
    if (append) // Si append es verdadero, se le anade al abrir el archivo
      fileStream.open(output, ios::app);
    else
      fileStream.open(output);
    if (fileStream.is_open())
      redirToFile = 1;
    else
      cout << "Archivo de escritura invalido" << endl;
  }

  // Crea un string para almacenar todo lo contenido en el archivo de lectura
  string fileContent = "";

  // Si no esta vacio, lee caracter por caracter
  if (input.length()) {
    ifstream tempInput(input);
    if (tempInput.is_open()) {
      char c;
      while (tempInput.get(c))
        fileContent += c;
      arg = fileContent;
    } else
      cout << "Archivo de lectura invalido" << input << endl;
  }

  // Ccrea el stream general, si hay redireccion, se usa el fileStream, sino el
  // cout
  ostream &outputStream = (redirToFile ? fileStream : cout);

  // Ifs para manejar comandos
  if (cmd == "cd")
    cd(arg, pwd); // Argumentos y ruta actual
  else if (cmd == "clr")
    clr();
  else if (cmd == "dir")
    dir(arg, pwd,
        outputStream); // Argumentos, directorio actual y stream especifico
  else if (cmd == "echo")
    echo(arg, outputStream); // Argumentos y stream especifico
  else if (cmd == "environ")
    environ(outputStream); // Stream especifico
  else if (cmd == "help")
    help(outputStream); // Stream especifico
  else if (cmd == "pause")
    pause();
  else if (cmd == "quit")
    return 0;
  else
    general(cmd,
            arg + " " +
                redir); // Si es comando externo, se envia el comando tal cual,
                        // uniendo argumentos y opciones de redireccion
  return 1;
}

// Maneja ejecucion de shell sin argumentos, y comandos internos
void manageInternal() {

  // Creacion varaibles, comando, argumentos, y opciones de redireccion
  string cmd, arg, redir;
  string pwd = ssystem("pwd"); // Se inicializa el pwd en la carpeta actual

  // Mientras no se ejecute quit, se separa el input en cmd, arg y redir
  while (1) {
    getCmdArg(cmd, arg, redir, pwd, std::cin);
    if (!commands(cmd, arg, redir, pwd))
      break;
  }
}

// Maneja llamadas al shell externas con argumento (batchfile)
// y lo ejecuta como script
void manageBatchfile(string filename) {
  ifstream batchfile(filename);

  // Se abre archivo para ejecutar como script
  if (!batchfile.is_open()) {
    cout << "Archivo invalido" << endl;
    return;
  }

  // Leer linea por linea y ejecutar
  string line;
  string pwd = ssystem("pwd"), cmd, arg, redir;
  cmd = arg = "";
  while (1) {
    getCmdArg(cmd, arg, redir, pwd, batchfile);
    if (!commands(cmd, arg, redir, pwd) || batchfile.eof())
      break;
  }
}
