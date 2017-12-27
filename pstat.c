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
    if(pstat[i].state > 0)
      printf(1, "%s\t %d\t %d\n", pstat[i].name, pstat[i].pid, pstat[i].uid);
  }
  printf(1, "\n"); 
  exit();
}
