#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  // RNF-04: Los errores deben reportarse a stderr (descriptor 2)
  // RNF-05: Terminar con valor diferente de cero ante un error
  if(argc < 2){
    fprintf(2, "Uso: trace <nombre_syscall>\n");
    exit(1); 
  }
  
  if(trace(argv[1]) < 0) {
    fprintf(2, "Error: la syscall trace fallo\n");
    exit(1);
  }
  
  printf("Monitoreo activado para: %s\n", argv[1]);
  exit(0);
}