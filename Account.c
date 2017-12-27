#include "types.h"
#include "stat.h"
#include "user.h"

int findUser(char* data, char* buf){
  char temp[100];
  int i = 0;
  int note = 0;
  int error = -1;

  while(*data != '\0'){
    if(*data == ';')
      note++;
    if(note == 0)
      temp[i++] = *data;
    else if(note == 1){
      temp[i] = '\0';
      i = 0;
      error = strcompare(temp, buf);
      if(error == 0){
	while(note != 3){
          data++;
	  if(note == 2)
	    temp[i++] = *data;
          if(*data == ';')
	    note++;
        }
        temp[i] = '\0';
        error = atoi(temp);
        i = 0;
        break;
      }
      while(*data != '\n')
        data++;
      note = 0;
    }
    else if(*data == '\n')
      note = 0;
    data++;
  }
  return error;
}

int findNullUid(char* data){
  char temp[100];
  int  note = 0;
  int  i = 0;
  int  uid[100];
  int  n = 0;
  
  for(n = 0; n<100; n++)
    uid[n] = -1;
  
  while(*data != '\0'){
    if(*data == ';')
      note++, data++;
    if(*data == '\n')
      note = 0;
    if(note == 2){
      while(*data != ';')
        temp[i++] = *data++;
      data--;
      temp[i] = '\0';
      uid[atoi(temp)] = 1;
      i = 0;
    }
    data++;
  }

  for(n = 0; n<100; n++)
    if(uid[n] == -1)
      break;
 
  if(n<100)
    return n;
  else
    return -1;
}

int checkPassword(char* data, char* buf, char* user){
  char temp[100];
  int i = 0;
  int note = 0;
  int error = -1;

  while(*data != '\0'){
    if(*data == ';')
      note++;
    if(note == 0)
      temp[i++] = *data;
    else if(note == 1){
      temp[i] = '\0';
      error = strcompare(temp, user);
	  i = 0;
	  
      if(error == 0){
	data++;
	while(note!=2){
	  if(*data == ';')
	    note++;
	  temp[i++] = *data;
	  data++;
	}
	temp[i] = '\0';
        error = strcompare(temp, buf);
	i = 0;
        break;
      }
    }
    else if(*data == '\n')
      note = 0;
    data++;
  }
  return error;
}

int changePassword(char* data, char* buf, char* user){
  char temp[100];
  char copy[512];
  int i = 0;
  int note = 0;
  int error = -1;

  while(*data != '\0'){
    if(*data == ';')
      note++;
    if(note == 0)
      temp[i++] = *data;
    else if(note == 1){
      temp[i] = '\0';
      i = 0;
      error = strcompare(temp, user);
      if(error == 0){
        data++, i++;
        while(*data != ';')
          data++, i++;
        data++, i++;
	strcpy(copy, data);
        data = data - i + 1;
        *data = '\0';
        concat(data, buf);
        concat(data, ";");
        concat(data, copy);
        break;
      }
      i = 0;
    }
    else if(*data == '\n')
      note = 0;
    data++;
  }
  
  if(*data == '\0')
    return -1;
  else
    return 0;
}

int deleteAccount(char* data, char* buf){
  char temp[100];
  char copy[512];
  int i = 0;
  int note = 0;
  int error = -1;
  int n = 0;

  while(*data != '\0'){
    if(*data == ';')
      note++;
    if(note == 0)
      temp[i++] = *data;
    else if(note == 1){
      temp[i] = '\0';
      error = strcompare(temp, buf);
      if(error == 0){
	while(*data != '\n')
	  data++, n++;
	data++, n++;
	strcpy(copy, data);
	data -= n;
	*data = '\0';
	concat(data, copy);
        break;
      }
      i = 0;
    }
    else if(*data == '\n')
      note = 0, n = -1;
    data++, n++;
  }
  
  if(*data == '\0')
    return -1;
  else
    return 0;
}

