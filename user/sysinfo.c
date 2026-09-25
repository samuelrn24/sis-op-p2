#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct sysinfo info;

  if (sysinfo(&info) < 0) {
    fprintf(2, "sysinfo error\n");
    exit(1);
  }

  printf("Free Memory: %d MB\n", (int)info.free_memory_mb);
  printf("Used Pages: %d\n", (int)info.used_pages);
  printf("Available Pages: %d\n", (int)info.available_pages);
  printf("Runnable Processes: %d\n", (int)info.runnable_procs);

  exit(0);
}