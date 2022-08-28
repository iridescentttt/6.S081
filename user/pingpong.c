#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  if(fork()==0)
  {
    read(p[0],"pingpong",1);
    fprintf(2,"%d: received ping\n",getpid());
    write(p[1],"pingpong",1);
    close(p[0]);
    close(p[1]);
  }
else{
    write(p[1],"pingpong",1);
    read(p[0],"pingpong",1);
    fprintf(2,"%d: received pong\n",getpid());
    close(p[0]);
    close(p[1]);
  }
  exit(0);
}
