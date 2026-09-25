#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"
#include "sysinfo.h"

extern char *syscall_names[];
extern int target_trace_id;

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  kexit(n);
  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return kfork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return kwait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  argint(0, &n);
  argint(1, &t);
  addr = myproc()->sz;

  if (t == SBRK_EAGER || n < 0) {
    if (growproc(n) < 0) {
      return -1;
    }
  } else {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    if (addr + n < addr)
      return -1;
    if (addr + n > TRAPFRAME)
      return -1;
    myproc()->sz += n;
  }
  return addr;
}

uint64
sys_pause(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if (n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n) {
    if (killed(myproc())) {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kkill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_trace(void)
{
  char syscall_name[32];

  if(argstr(0, syscall_name, 32) < 0) {
    return -1;
  }

  // Buscar el ID numérico iterando sobre el arreglo de nombres
  // Hay un máximo de 23 syscalls registradas actualmente
  for(int i = 1; i <= 23; i++) { 
    if(syscall_names[i] != 0 && strncmp(syscall_name, syscall_names[i], 32) == 0) {
      target_trace_id = i; 
      return 0; 
    }
  }

  return -1;
}

uint64
sys_sysinfo(void)
{
  struct sysinfo info;
  uint64 addr;

  // Extraer la dirección de memoria que nos manda el usuario (sin condicional if)
  argaddr(0, &addr);

  // Usar tus funciones para llenar la estructura con los datos
  collect_mem_info(&info.free_memory_mb, &info.used_pages, &info.available_pages);
  info.runnable_procs = count_runnable_procs();

  // Copiar la estructura llena hacia el programa de usuario de forma segura
  if(copyout(myproc()->pagetable, addr, (char *)&info, sizeof(info)) < 0)
    return -1;

  return 0;
}