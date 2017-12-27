#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "Account.h"

int main(int argc, char** argv){
  int fd;
  char data[2048];

  fd = open(AccountFile, O_RDONLY);
  read(fd, data, sizeof(data));
  close(fd);

  printf(1, "%s\n", data);
  exit();
}
