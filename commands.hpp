#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include "utility.hpp"

using namespace std;

void cd(string directorio, string &pwd);
void clr();
void dir(string directorio, string pwd);
/* void environ(); */
void echo(string comentario);
void help();
void pause();

bool commands(string cmd, string arg, string &pwd);