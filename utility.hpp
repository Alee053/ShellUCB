#pragma once
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

string ssystem(const char *cmd);

void getCmdArg(string &cmd, string &arg, string &redir, string &pwd,
               istream &stream);

string fusionarDirs(string pwd, string dir);

void getInOutRedir(string redir, string &input, string &output, bool &append);
