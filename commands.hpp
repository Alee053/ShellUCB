#pragma once

#include <iostream>
#include <string>;

using namespace std;

void cd(string directorio);
void clr();
void dir();
void environ();
void echo();
void help();
void pause();

bool commands(string cmd,string arg);
