#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "Account.h"
struct accountData account;

int main(int argc, char* argv[]){
  char buf[100];
  char user[100];
  char temp[512];
  char data[512];
  char out[100];
  int  state = 0;
  int  fd;
  int  testI = 0;
  int  i;

  testI = fd = open(AccountFile, O_RDWR);
  if(testI < 0){
    mkdir(Folder);
    fd = open(AccountFile, O_CREATE | O_RDWR);
    if(fd<0)
      printf(1, "%s\n", "ERROR");
  }
  read(fd, data, sizeof(data));
  close(fd);

  printf(1, "%s\n", "Input Function: useradd, passwd, userdel");
  printf(1, "%s", "Input: ");
  scanf(buf, 100);

  if(strcompare(buf, "useradd") == 0) { state = 1; }
  else if(strcompare(buf, "passwd") == 0) { state = 2; }
  else if(strcompare(buf, "userdel") == 0) { state = 3; }

  

  switch(state){
    case 1:
      if(testI >= 0)
        i = findNullUid(data);
      else
        i = 0, data[0] = '\0';

      printf(1, "%s", "Input User Name: ");
      scanf(buf, 100);
      if(testI != 0)
        if(findUser(data, buf) >= 0){
          printf(1, "%d %s\n", findUser(data, buf), "User Exist");
          break;
        }
      strcpy(account.user, buf);
      printf(1, "%s", "Input User Password: ");
      scanf(buf, 100);
      strcpy(account.password, buf);
      account.uid = i;
      account.gid = i;
      strcpy(account.description, "");
      strcpy(account.index, "");
      strcpy(account.shell, "sh");

      strcpy(temp, account.user);
      concat(temp, ";");
      concat(temp, account.password);
      concat(temp, ";");
      concat(temp, itoa(account.uid, out));
      concat(temp, ";");
      concat(temp, itoa(account.gid, out));
      concat(temp, ";");
      concat(temp, account.description);
      concat(temp, ";");
      concat(temp, account.index);
      concat(temp, ";");
      concat(temp, account.shell);
      concat(temp, "\n");
      printf(1, "%s", temp);
      
      concat(data, temp);
      break;

    case 2:
      printf(1, "%s", "Input User Name For Change Password: ");
      scanf(buf, 100);
	  
      if((i = findUser(data, buf)) < 0){
        printf(1, "%s\n", "User Not Found");
        break;
      }
      strcpy(user, buf);
	  
      printf(1, "%s", "Input Old Password For Set New Password: ");
      scanf(buf, 100);
      if(checkPassword(data, buf, user) < 0){
        printf(1, "%s\n", "Wrong Password");
        break;
      }

      printf(1, "%s", "InputNewPassword: ");
      scanf(buf, 100);
      changePassword(data, buf, user);

      break;
      
    case 3:
      printf(1, "%s", "Input User Name For Delete: ");
      scanf(buf, 100);
      if((i = findUser(data, buf)) < 0){
        printf(1, "%s\n", "User Not Found");
        break;
      }
      strcpy(user, buf);
	  
      printf(1, "%s", "Input Old Password For Delete: ");
      scanf(buf, 100);
      if(checkPassword(data, buf, user) < 0){
        printf(1, "%s\n", "Wrong Password");
        break;
      }

      deleteAccount(data, user);
      break;
  }
  
  printf(1, "\n");
  open(AccountFile, O_RDWR);
  write(fd, data, sizeof(data));
  close(fd);

  exit();
}
