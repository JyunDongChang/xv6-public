#define Folder "etc"
#define AccountFile "etc/passwd"
#define PasswordFile "etc/shadow" // Set for future
#define Total 10
struct accountData{
  char user[100];
  char password[100];
  int  uid;
  int  gid;
  char description[200];
  char index[50];
  char shell[50];
};
