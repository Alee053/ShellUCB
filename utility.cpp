#include "utility.hpp"

string ssystem(const char *cmd) {
  array<char, 128> buffer;
  string result;
  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) !=
         nullptr) {
    result += buffer.data();
  }
  result = result.substr(0, result.length() - 1);
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