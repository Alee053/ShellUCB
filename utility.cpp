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

void getCmdArg(string &cmd, string &arg, string &redir, string &pwd,
               istream &stream) {
  if (&stream == &cin) {
    // Mostrar directorio antes de cada comando
    cout << pwd << ": ";
  }
  string input;
  getline(stream, input);
  cmd = arg = redir = "";
  int field = 0;
  for (char c : input) {
    if (c == ' ' && field == 0) {
      field = 1;
      continue;
    } else if (c == '<' || c == '>') {
      field = 2;
    }
    if (field == 0)
      cmd += c;
    else if (field == 1)
      arg += c;
    else if (field == 2)
      redir += c;
  }
  int cut = 0;
  while (arg[arg.length() - cut - 1] == ' ')
    cut++;
  arg = arg.substr(0, arg.length() - cut);
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

void getInOutRedir(string redir, string &input, string &output, bool &append) {
  // Verificar si hay que truncar archivo o anadir (append)
  for (int i = 1; i < redir.length(); i++) {
    if (redir[i] == '>' && redir[i - 1] == '>') {
      append = 1;
      break;
    }
  }
  // Extraer nombres de archivos input output
  input = output = "";
  bool in_out = 0; // in:0 out:1
  bool space = 0;
  for (int i = 1; i < redir.length(); i++) {
    if (redir[i - 1] == '>' && redir[i] == ' ') {
      in_out = 1;
      space = 0;
      continue;
    }
    if (redir[i - 1] == '<' && redir[i] == ' ') {
      in_out = 0;
      space = 0;
      continue;
    }

    if (redir[i] == ' ')
      space = 1;

    if (!in_out && !space)
      input += redir[i];
    if (in_out && !space)
      output += redir[i];
  }
}
