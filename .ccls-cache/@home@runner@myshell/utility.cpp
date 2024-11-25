#include "utility.hpp"

string ssystem(const char *command) {
  char tmpname[L_tmpnam];
  tmpnam(tmpname);
  string scommand = command;
  string cmd = scommand + " >> " + tmpname;
  system(cmd.c_str());
  ifstream file(tmpname, ios::in | ios::binary);
  string result;
  if (file) {
    while (!file.eof())
      result.push_back(file.get());
    file.close();
  }
  remove(tmpname);
  result = result.substr(0, result.length() - 2);
  return result;
}

void getCmdArg(string &cmd, string &arg) {
  // Mostrar directorio antes de cada comando
  cout << ssystem("pwd") << ": ";
  string input;
  getline(cin, input);
  cmd = arg = "";
  bool space = 0;
  for (char c : input) {
    if (c == ' ') {
      space = 1;
      continue;
    }
    if (!space)
      cmd += c;
    else
      arg += c;
  }
}
