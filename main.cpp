#include "commands.hpp"
#include "utility.hpp"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  if (argc > 1)
    manageBatchfile(argv[1]);
  else
    manageInternal();
  return 0;
}
