// Unlock.

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "Account.h"

int main(int argc, char** argv){
  char data[512];
  char user[100];
  char buf[100];
  int  fd;
  int  i;

  if((fd = open(AccountFile, O_RDONLY)) < 0)
    exit();
  else{
    read(fd, data, sizeof(data));
    close(fd);

    printf(1, "%s", "Input User For Unlock: ");
    while(1){
      scanf(buf, 100);
      if((i = findUser(data, buf)) < 0){
        printf(1, "%s\n\n%s", "User Not Found", "Input User For Unlock: ");
        continue;
      }
      else if(i != getreuid()){
        printf(1, "%s\n\n%s", "Can't Unlock By Other Users", "Input User For Unlock: ");
        continue;
      }
        
      strcpy(user, buf);
	  
      printf(1, "%s", "Input Password: ");
      scanf(buf, 100);
      
      if(checkPassword(data, buf, user) < 0){
        printf(1, "%s\n\n%s", "Wrong Password", "Input User For Unlock: ");
        continue;
      }
      else{
        printf(1, "%s\n\n", "Unlock Succed");
        setreuid(i);
        break;
      }
    }

    exit();
  }
}
