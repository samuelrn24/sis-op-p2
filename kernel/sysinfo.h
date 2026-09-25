#ifndef _SYSINFO_H_
#define _SYSINFO_H_
#include "types.h"

struct sysinfo {
  uint64 free_memory_mb;
  uint64 used_pages;
  uint64 available_pages;
  uint64 runnable_procs;
};

#endif