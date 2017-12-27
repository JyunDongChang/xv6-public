//Logout.

#include "types.h"
#include "stat.h"
#include "param.h"
#include "user.h"
#include "pstat.h"

struct pstat pstat[NPROC];

int main(int argc, char* argv[]){
  int i;

  getpstat(pstat);
  for(i = 0; i<NPROC; i++){
    if(pstat[i].state > 0 && pstat[i].pid != 1 && pstat[i].pid != getpid() && pstat[i].uid == getreuid())
      kill(pstat[i].pid);
  }

  setreuid(-1);
  kill(getpid());
  exit();
}
