#include "commands.hpp"
#include "utility.hpp"
#include <iostream>
using namespace std;

const int TAM = 100;

int main() {
  string cmd, arg;
  string pwd;

  while (1) {
    getCmdArg(cmd, arg);
    commands(cmd, arg);
  }
  return 0;
}

// TODO
/*
    pwd global
    cambiar todas funciones a pwd y args
*/
