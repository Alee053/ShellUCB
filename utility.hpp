#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string ssystem(const char *command);

void getCmdArg(string &cmd, string &arg, string &pwd, istream &stream);

string fusionarDirs(string pwd, string dir);