#pragma once
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>

using namespace std;

string ssystem(const char *cmd);

void getCmdArg(string &cmd, string &arg, string &pwd, istream &stream);

string fusionarDirs(string pwd, string dir);