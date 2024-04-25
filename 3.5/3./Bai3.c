#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define STUDENT_ID "22520501"
void sigint_handler(int signum) {
    printf("count.sh has stopped\n");
    exit(0);
}

int main() {
    printf("Welcome to IT007, I am %s!\n", STUDENT_ID);
    signal(SIGINT, sigint_handler);
    system("./count.sh 120");

    return 0;
}
