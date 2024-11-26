#pragma once
// Includes necesarios para compilacion del archivo .cpp
#include "utility.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Declaracion de funciones

void cd(string directorio, string &pwd);
void clr();
void dir(string directorio, string pwd, ostream &oStream);
void environ(ostream &oStream);
void echo(string comentario, ostream &oStream);
void help(ostream &oStream);
void pause();

bool commands(string cmd, string arg, string redir, string &pwd);

void general(string cmd, string arg);

bool commands(string cmd, string arg, string &pwd);

void manageInternal();

void manageBatchfile(string filename);