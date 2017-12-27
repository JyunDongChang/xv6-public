// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "Account.h"

char type[100] = { "login" };
char *argv[] = { type, 0 };

int
main(void)
{
  int pid, wpid, fd;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
    if((fd = open(AccountFile, O_RDONLY)) < 0 && getreuid() >= 0)
      printf(1, "init: starting sh\n\n");
    else if(getreuid() >= 0)
      printf(1, "init: starting login\n\n");
    
    pid = fork();
    //printf(1, "Pid: %d ForkPid: %d\n", getpid(), pid);

    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      if(getreuid() >= 0)
        exec("login", argv);
      else if(fd > 0)
        exec("login", argv);
      else{
        strcpy(argv[0], "unlockNoUser");
        exec("unlockNoUser", argv);
        strcpy(argv[0], "login");
      }

      printf(1, "init: exec failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
