#pragma once
// Includes necesarios para compilacion del archivo .cpp
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Declaracion de funciones

string systemGet(const char *cmd);

string fusionarDirs(string pwd, string dir);

void getCmdArg(string &cmd, string &arg, string &redir, string &pwd,
               istream &stream);

void getInOutRedir(string redir, string &input, string &output, bool &append);

string cutEnd(string str, int n);
