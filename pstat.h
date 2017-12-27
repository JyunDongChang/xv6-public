#include "param.h"

struct pstat{
  int  state;     // Process Stste
  int  pid;       // Process ID
  int  uid;       // User ID Who is Login
  int  euid;      // User ID Who is Excute
  char name[16];  // Process name (debugging)
  int  priority;  // Priority Information For Future
};
