#include "utility.hpp"

string ssystem(const char *command) {
  char tmpname[100];
  mkstemp(tmpname);
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

void getCmdArg(string &cmd, string &arg, string &pwd, istream &stream) {
  if (&stream == &cin) {
    // Mostrar directorio antes de cada comando
    cout << pwd << ": ";
  }
  string input;
  getline(stream, input);
  cmd = arg = "";
  bool space = 0;
  for (char c : input) {
    if (c == ' ' && !space) {
      space = 1;
      continue;
    }
    if (!space)
      cmd += c;
    else
      arg += c;
  }
}

string fusionarDirs(string pwd, string dir) {
  string backup = pwd;
  if (dir[0] == '/')
    pwd = dir;
  else if (dir[0] == '.' && dir[1] == '.' && dir[2] == '/') {
    int pos = pwd.length() - 2;
    while (pwd[pos] != '/') {
      pos--;
    }
    pos++;
    pwd = pwd.substr(0, pos);
  } else if (dir[0] == '.' && dir[1] == '/')
    pwd += "/" + dir.substr(2, dir.length() - 2);
  else if (dir[0] == '.' && dir[1] != '/')
    pwd += "/" + dir.substr(1, dir.length() - 1);
  else if (dir[0] != '.' && dir[1] != '/')
    if (pwd[pwd.length() - 1] != '/')
      pwd += "/" + dir;
    else
      pwd += dir;
  else {
    return backup;
  }

  return pwd;
}