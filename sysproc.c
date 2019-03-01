#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


extern const int totalTickets; // cs202


// cs202 ----->
int 
sys_info(void)
{
	int type = 0, val = 0;
	argint(0, &type);
	
	if(type == 1)
		val = getProcCount();
	else if(type == 2)
		val = getSysCallCount();
	else if(type == 3)
		val = getPageSize();
	
	return info(type, val);
}

int
sys_settickets(void)
{
	struct proc *curproc = myproc();
	
	int val;
	if(argint(0, &val) < 0)
		return -1;

	setTickets(curproc, val);

	return 0;
}

int
sys_showpinfo(void)
{	
	showProcesses();	
	return 0;
}

int
sys_setstride(void)
{
	int val = 0;
	argint(0, &val);	
	
	setStride(val);
	
	return 0;
}
// cs202 <-----

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
