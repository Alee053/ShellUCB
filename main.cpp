// Includes necesarios para funcionamiento, y orden
#include "commands.hpp"
#include "utility.hpp"
using namespace std;

// Main con argumentos externos
int main(int argc, char **argv) {
  // Si es que se ejecuta con argumento, ejecutar archivo ingresado como script,
  // sino, ejecucion normal interna
  if (argc > 1)
    manageBatchfile(argv[1]);
  else
    manageInternal();
  return 0;
}
