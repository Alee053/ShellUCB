#pragma once

#include "utility.hpp"
#include <filesystem>
#include <iostream>
#include <string>

using namespace std;

void cd(string directorio, string &pwd);
void clr();
void dir(string directorio, string pwd);
void environ();
void echo(string comentario);
void help();
void pause();

bool commands(string cmd, string arg, string &pwd);