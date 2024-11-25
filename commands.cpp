#include "commands.hpp"
// TODO Implementar comprobacion folder
//      ../ / ./
void cd(string directorio, string &pwd) {
  pwd += "/" + directorio;
}
void clr() { system("clear"); }
void dir(string directorio) {
  string cmd = "ls " + directorio;
  system(cmd.c_str());
}
void environ() {}
void echo() {
  string comentario;
  cin >> comentario;
  cout << comentario << endl;
}
void help(string arg) {
 string more= "more" + arg;
system(more.c_str());
}
void pause() { system("pause"); }

bool commands(string cmd, string arg, string &pwd) {
  if (cmd == "cd")
    cd(arg, pwd);
  else if (cmd == "clr")
    clr();
  else if (cmd == "dir")
    dir(arg);
  else if (cmd == "echo") {
    echo();
  } else if (cmd == "environ") {

  } else if (cmd == "help") {

  } else if (cmd == "pause")
    system("pause");
  else if (cmd == "quit")
    return 0;
  else
    cout << "Comando inexistente" << endl;
  return 1;
}