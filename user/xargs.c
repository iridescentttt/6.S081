#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char input[32];
  char *params[MAXARG];
  int cnt=0,arg_index=0;
  for(int i=1;i<argc;i++)
    params[arg_index++]=argv[i];

  while(1){
    if(read(0,input+cnt,1)==0)
      break;
    if(input[cnt]=='\n'){
      input[cnt]='\0';
      // fprintf(1,"work with line %s\n",input);
      params[arg_index]=input;
      params[arg_index+1]=0;
      if(fork()==0){
        exec(argv[1],params);
        exit(0);
      }
    else {
        wait(0);
      }
      cnt=0;
    }
    cnt++;
  }
  exit(0);
}
