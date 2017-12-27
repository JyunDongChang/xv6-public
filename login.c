// Login.

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "Account.h"
#include "pstat.h"

struct pstat pstat[NPROC];

char shell[100] = { "sh" };
char *argv[] = { shell, 0 };

int main(int argc, char** argv){
  char data[512];
  char user[100];
  char buf[100];
  int  fd;
  int  i;

  if((fd = open(AccountFile, O_RDONLY)) < 0){  
    exec(shell, argv);
    exit();
  }
  else{
    read(fd, data, sizeof(data));
    close(fd);

    printf(1, "%s", "Input User For Login: ");
    while(1){
      scanf(buf, 100);
      if((i = findUser(data, buf)) < 0){
        printf(1, "%s\n\n%s", "User Not Found", "Input User For Login: ");
        continue;
      }
      strcpy(user, buf);
	  
      printf(1, "%s", "Input Password: ");
      scanf(buf, 100);
      
      if(checkPassword(data, buf, user) < 0){
        printf(1, "%s\n\n%s", "Wrong Password", "Input User For Login: ");
        continue;
      }
      else{
        printf(1, "%s\n\n", "Login Succed");
        setreuid(i);
        break;
      }
    }

    getpstat(pstat);
    for(i = 0; i<NPROC; i++){
      if(pstat[i].state > 0 && pstat[i].pid != 1 && pstat[i].pid != getpid() && pstat[i].uid == getreuid() && strcompare(pstat[i].name, "sh") == 0)
        exit();
    }

    printf(1, "%s\n", "Starting sh");
    exec(shell, argv);
    exit();
  }
}
