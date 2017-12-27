// Lock.

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "Account.h"
#include "pstat.h"

struct pstat pstat[NPROC];
char type[100] = { "unlockNoUser" };
char *argv[] = { type, 0 };


int main(int argc, char** argv){
  int  fd;


  if((fd = open(AccountFile, O_RDONLY)) >= 0)
    close(fd);
  else{
    exec(type, argv);
    exit();
  }

  strcpy(type, "unlock");
  exec(type, argv);
  exit();
}
