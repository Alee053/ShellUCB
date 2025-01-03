#include "utility.hpp"

// Funcion para ejecutar comando en el shell superior y retornar el output
string systemGet(const char *cmd) {
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
  return result;
}

// Funcion que pide una linea como input, ya sea de archivo o cin, y separa en
// comando, argumentos, y opciones de redireccion
void getCmdArg(string &cmd, string &arg, string &redir, string &pwd,
               istream &stream) {
  // Mostrar directorio antes de cada comando, solo si el stream de input es cin
  if (&stream == &cin) {
    cout << pwd << "& ";
  }
  // Leer linea
  string input;
  getline(stream, input);
  cmd = arg = redir = "";
  int field = 0;
  // Separar input en 3 variables
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
  // Eliminar espacios al final de argumentos
  int cut = 0;
  while (arg[arg.length() - cut - 1] == ' ')
    cut++;
  arg = arg.substr(0, arg.length() - cut);
}

// Genera una ruta absluta en base a una ruta absoluta y una relativa/absoluta
string fusionarDirs(string pwd, string dir) {
  // Por si la ruta final es invalida
  string backup = pwd;
  // Diferentes opciones relativas ./ ../ / etc
  if (dir[0] == '/')
    pwd = dir;
  else if (dir[0] == '.' && dir[1] == '.' && dir[2] == '/') {
    while (dir.length()) {
      int pos = pwd.length() - 2;
      while (pwd[pos] != '/') {
        pos--;
      }
      pos++;
      pwd = pwd.substr(0, pos);
      dir = dir.substr(0, dir.length() - 3);
    }

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
  // Borrar si hay / repetidas
  int pos = 0;
  while (pwd[pos++] == '/')
    ;
  pos -= 2;

  pwd = pwd.substr(max(pos, 0), pwd.length() - pos);

  return pwd;
}

// Extrae nombre de archivo de redireccion de input, output y si se quiere hacer
// append en vez de truncar
void getInOutRedir(string redir, string &input, string &output, bool &append) {
  bool hayInput = 0, hayOutput = 0;
  // Verificar si hay que truncar o anadir al archiv
  // Verificar si hay input y output
  for (int i = 1; i < int(redir.length()); i++) {
    if (redir[i] == '>' && redir[i - 1] == '>')
      append = 1;
    if (redir[i] == '>' || redir[i - 1] == '>')
      hayOutput = 1;
    if (redir[i] == '<' || redir[i - 1] == '<')
      hayInput = 1;
  }
  // Extraer nombres de archivos input output
  input = output = "";
  int in_out = 0; // nada:0 out:1 in:2
  bool space = 0;
  for (int i = 1; i < int(redir.length()); i++) {
    if (redir[i - 1] == '>' && redir[i] == ' ') {
      in_out = 1;
      space = 0;
      continue;
    }
    if (redir[i - 1] == '<' && redir[i] == ' ') {
      in_out = 2;
      space = 0;
      continue;
    }

    if (redir[i] == ' ')
      space = 1;

    if (in_out == 2 && !space)
      input += redir[i];
    if (in_out == 1 && !space)
      output += redir[i];
  }
  // Si se mando input o output pero en mal formato
  if (hayInput && !input.length())
    input = "bad parse";
  if (hayOutput && !output.length())
    output = "bad parse";
}

// Corta n caracteres del final de un string
string cutEnd(string str, int n) { return str.substr(0, str.length() - n); }
