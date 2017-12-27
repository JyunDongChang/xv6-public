// UnlockNoUser.

#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char** argv){
  char buf[100];
  printf(1, "Enter O For Unlock\n");
  
  while(1){
    scanf(buf, 100);
    if(strcompare(buf, "O") == 0)
      break;
    else
      printf(1, "Error Enter, Please Enter O To Unlock\n");
  }

  printf(1, "\n");
  setreuid(0);
  exit(); 
}
