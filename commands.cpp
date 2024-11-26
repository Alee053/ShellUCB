#include "commands.hpp"
#include "utility.hpp"

// TODO Implementar comprobacion folder
//      ../ / ./
void cd(string directorio, string &pwd) {
  if (!directorio.length()) {
    cout << pwd << endl;
    return;
  }
  string temp = fusionarDirs(pwd, directorio);
  if (filesystem::is_directory(filesystem::path(temp)))
    pwd = temp;
  else
    cout << "Directorio invalido" << endl;
}
void clr() { system("clear"); }
void dir(string directorio, string pwd) {
  string temp = fusionarDirs(pwd, directorio);
  if (filesystem::is_directory(filesystem::path(temp)))
    system(("ls " + temp).c_str());
  else
    cout << "Directorio invalido";
}
void environ() {
  ifstream environFile("/proc/self/environ");
  if (!environFile) {
    cout << "No se pudo acceder a las variables de entorno." << endl;
    return;
  }

  string variable;
  char ch;
  while (environFile.get(ch)) {
    if (ch == '\0') {
      cout << variable << endl; // Imprime la variable cuando encuentra '\0'
      variable = "";            // Reinicia la variable
    } else {
      variable += ch; // Añade el carácter a la variable actual
    }
  }
}
void echo(string comentario) {
  if (comentario.length())
    cout << comentario << endl;
}
void help() {
  system("stty rows 2");
  string read = "README.txt";
  string more = "more " + read;
  system(more.c_str());
}
void pause() {
  cout << "Shell pausado, pulse ENTER para continuar" << endl;
  cin.ignore();
}

void general(string cmd, string arg) { system((cmd + arg).c_str()); }

bool commands(string cmd, string arg, string &pwd) {
  if (cmd == "cd")
    cd(arg, pwd);
  else if (cmd == "clr")
    clr();
  else if (cmd == "dir")
    dir(arg, pwd);
  else if (cmd == "echo") {
    echo(arg);
  } else if (cmd == "environ")
    environ();
  else if (cmd == "help")
    help();
  else if (cmd == "pause")
    pause();
  else if (cmd == "quit")
    return 0;
  else
    general(cmd, arg);
  return 1;
}

void manageInternal() {

  string cmd, arg;
  string pwd = ssystem("pwd");

  while (1) {
    getCmdArg(cmd, arg, pwd, std::cin);
    if (!commands(cmd, arg, pwd))
      break;
  }
}

void manageBatchfile(string filename) {
  ifstream batchfile(filename);

  if (!batchfile.is_open()) {
    cout << "Archivo invalido" << endl;
    return;
  }

  string line;
  string pwd = ssystem("pwd"), cmd, arg;
  cmd = arg = "";
  while (1) {
    getCmdArg(cmd, arg, pwd, batchfile);
    if (!commands(cmd, arg, pwd)||batchfile.eof())
      break;
  }
}
