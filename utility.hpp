#pragma once
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

string ssystem(const char *command);

void getCmdArg(string &cmd, string &arg, string &pwd);

int checkDirectoryExists(string path);

string fusionarDirs(string pwd, string dir);