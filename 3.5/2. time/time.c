
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
int main(int argc, char* argv[])
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    __pid_t pid;
    pid = fork();
    
    if (pid > 0)
    {
        wait(NULL);
    } else
    if (pid == 0)
    {
        execl("/bin/sh","sh", "-c", argv[1], NULL);
    }
    else
    {
        wait(NULL);
        
    }
    gettimeofday(&end, NULL);
    double time_taken;
 
    time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("Thoi gian thuc thi: %f\n", time_taken);
    exit(0);

}