#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
void sigint_handler(int signum) {
    printf("count.sh has stopped\n");
    exit(0);
}
int main() {
    printf("Welcome to IT007, I am %s!\n", "22520501");
    signal (SIGINT, sigint_handler);
    pid_t pid = fork();
    if (pid == 0) { 
        execlp("./count.sh" , "count.sh"  "120", NULL);
        perror("execlp");
        exit(1);

    } else if (pid < 0) {
    perror("fork");
    exit(1);
    }
    waitpid(pid, NULL, 0);
    return 0;
}