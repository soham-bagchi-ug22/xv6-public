#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"
#include "spinlock.h"

struct ptable{
  struct spinlock lock;
  struct proc proc[NPROC];
};

// Declare ptable as an extern
extern struct ptable ptable;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


// Settickets() syscall
int 
sys_settickets(void)
{
  int num;
  int return_val = argint(0, &num);
  if (return_val == -1)
  {
    // Indicating that the value obtained at the address stored in %ebx
    // is not within the current process space. This implies that we need
    // to revert to the default case of setting the no. of tickets of the 
    // current process to 1 
    struct proc *ptr = myproc();
    ptr->tickets = 1;
    return 0;
    
  }
  else 
  {
    if (num < 1 && num > MAXTICKETS)
    {
      // User passed in a number that is less that 1
      return -1;  
    }

    struct proc *ptr = myproc();
    ptr->tickets = num;
    return 0;

  }
}

// Getpinfo() syscall
int 
sys_getpinfo(void)
{
 
  acquire(&ptable.lock);
  struct pstat *ptr1;
  struct proc *proc1; // We declare a process that we will use to iterate over the processes in the process table
  
  int return_val = argptr(0, (void*)&ptr1, sizeof(*ptr1));
  if (return_val != 0)
  {
    return -1;
  }
  else
  {
    // Check if the pointer that the user entered is valid
    // i.e., check if it is not a bad/NULL pointer
    if (ptr1 == 0)
    {
      return -1;
    }
    

    for (proc1 = ptable.proc; proc1 < &ptable.proc[NPROC]; proc1++)
    {
      int i = proc1 - ptable.proc; // We subtract the address of the current proc no. from the index of the first proc in the proc array   
      if (proc1->state != UNUSED)  // If a process is unused, it has not been initialized as of now
      {
        ptr1->inuse[i] = proc1->inuse;
        ptr1->tickets[i] = proc1->tickets;
        ptr1->pid[i] = proc1->pid;
        ptr1->ticks[i] = proc1->ticks;
      }
    }

    release(&ptable.lock);
    return 0;
  
    

  }


}