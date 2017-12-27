#include "types.h"
#include "stat.h"
#include "user.h"

int strcompare(const char *a, const char *b){
  int i = 0;
  int error = 0;
  if(a[i] != b[i] && (a[i] == 0 || b[i] == 0))
    error = -1;
  while(a[i]!=0 && b[i]!=0){
    if(a[i] != b[i]) { error = -1; break; }
    else {i++;}
  }
  return error;
}

void scanf(char *a, int max){
  gets(a, max);
  if(a[strlen(a)-1] == '\n') { a[strlen(a)-1] = '\0'; }
}

void concat(char* a, char* b){
  while(*a++ != 0)
    ;
  a--;
  strcpy(a, b);
}

char* itoa(int a, char* out){
  char buf[100];
  int  i = 0;
  int  n;
  while(a != 0 || i == 0){
    buf[i] = (a % 10) + 48;
    a = a/10;
    i++;
  }

  for(n = 0; n<i; n++)
    out[n] = buf[i-n-1];
  out[n] = '\0';
  return out;
}

