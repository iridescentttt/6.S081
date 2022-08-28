#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void work(int *p){
  int num[36]={};
  int res=1,cnt=0;
  int pp[2];
  pipe(pp);
  while(res){
    res=read(p[0],num+cnt,4);
    cnt++;
  }
  if(cnt==1)return;
  fprintf(1,"prime %d\n",num[0]);
  if(fork()==0){
    close(pp[1]);
    work(pp);
    close(pp[0]);
  }
else {
    for(int i=0;i<cnt;i++){
      if(num[i]%num[0]==0)continue;
      write(pp[1],&num[i],4);
    }
    close(pp[0]);
    close(pp[1]);
    wait(0);
  }
  exit(0);
}
int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  if(fork()==0)
  {
    close(p[1]);
    work(p);
    close(p[0]);
  }
else{
    for(int i=2;i<=35;i++){
      write(p[1],&i,4);
    } 
    close(p[1]);
    close(p[0]);
    wait(0);
  }
  exit(0);
}
