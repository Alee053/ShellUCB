#include "commands.hpp"
#include "utility.hpp"

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
void dir(string directorio, string pwd, ostream &oStream) {
  string temp = fusionarDirs(pwd, directorio);
  if (filesystem::is_directory(filesystem::path(temp)))
    oStream << ssystem(("ls " + temp).c_str()) << endl;
  else
    oStream << "Directorio invalido" << endl;
}
void environ(ostream &oStream) {
  ifstream environFile("/proc/self/environ");
  if (!environFile) {
    oStream << "No se pudo acceder a las variables de entorno." << endl;
    return;
  }

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
void echo(string comentario, ostream &oStream) {
  if (comentario.length())
    oStream << comentario << endl;
}
void help(ostream &oStream) {
  system("stty rows 2");
  string read = "README.txt";
  string more = "more " + read;
  oStream << ssystem(more.c_str()) << endl;
}
void pause() {
  cout << "Shell pausado, pulse ENTER para continuar" << endl;
  cin.ignore();
}

void general(string cmd, string arg) { system((cmd + arg).c_str()); }

bool commands(string cmd, string arg, string redir, string &pwd) {

  string input, output;
  bool append = 0;
  getInOutRedir(redir, input, output, append);

  ofstream fileStream;
  bool redirToFile = 0;
  if (output.length()) {
    if (append)
      fileStream.open(output, ios::app);
    else
      fileStream.open(output);
    if (fileStream.is_open())
      redirToFile = 1;
    else
      cout << "Archivo de escritura invalido" << endl;
  }

  string fileContent = "";

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

  ostream &outputStream = (redirToFile ? fileStream : cout);

  if (cmd == "cd")
    cd(arg, pwd);
  else if (cmd == "clr")
    clr();
  else if (cmd == "dir")
    dir(arg, pwd, outputStream);
  else if (cmd == "echo")
    echo(arg, outputStream);
  else if (cmd == "environ")
    environ(outputStream);
  else if (cmd == "help")
    help(outputStream);
  else if (cmd == "pause")
    pause();
  else if (cmd == "quit")
    return 0;
  else
    general(cmd, arg + " " + redir);
  return 1;
}

void manageInternal() {

  string cmd, arg, redir;
  string pwd = ssystem("pwd");

  while (1) {
    getCmdArg(cmd, arg, redir, pwd, std::cin);
    if (!commands(cmd, arg, redir, pwd))
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
  string pwd = ssystem("pwd"), cmd, arg, redir;
  cmd = arg = "";
  while (1) {
    getCmdArg(cmd, arg, redir, pwd, batchfile);
    if (!commands(cmd, arg, redir, pwd) || batchfile.eof())
      break;
  }
}
