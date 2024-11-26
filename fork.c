#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

void err(){
  perror("fork failed");
  exit(1);
}

int child(){
  printf("%d ", getpid());
  long int randNum;
  int fd = open("/dev/urandom", O_RDONLY);
  read(fd, &randNum, 4);
  randNum = randNum % 5 + 1;
  printf("%ldsec\n", randNum);

  sleep(randNum);

  printf("%d finished after %ldsec\n", getpid(), randNum);

  return randNum;
}

int parent(int child1, int child2){
  //printf("child1: %d, child2: %d\n", child1, child2);
  int status;
  int childWhoReturned;
  childWhoReturned = wait(&status);

  int childSleep = WEXITSTATUS(status);

  printf("Main process %d is done. Child %d slept for %dsec\n", getpid(), childWhoReturned, childSleep);
  return 0;
}

int main(){
  pid_t p1, p2;
  printf("%d about to create 2 child processes\n", getpid());

  p1 = fork();
  if (p1 < 0) err();

  else if (p1 == 0){
    return child();
  }

  if (p1 > 0){
    p2 = fork();
    if (p2 == 0){
      return child();
    }

    parent(p1, p2);
  }

  return 0;
}
