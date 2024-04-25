#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 4096

int collatz(int n){
    if (n % 2 == 0){
        return n / 2;
    }
    else{
        return 3 * n + 1;
    }
}

int main (int argc, char *argv[]){
    if (argc != 2){
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int startNumber = atoi(argv[1]);

    if (startNumber <= 0){
        printf("Please insert an integer\n");
        return 1;
    }

    // Create a shared memory
    int shm_fod = shm_open("/collatz_memmory", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fod, SIZE);

    // Memory map the shared memory object
    int *resultBuf = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fod, 0);

    pid_t pid = fork();
    if (pid > 0){
        // Parent process
        wait(NULL);
        for (int i = 0; resultBuf[i] != 1; i++){
            printf("%d\n", resultBuf[i]);
        }
        printf("1\n");

        // Unmap the shared memory segment
        munmap(resultBuf, SIZE);
        close(shm_fod);
        shm_unlink("/collatz_memmory");
        return 0;
    }
    else if (pid == 0){
        // Child process
        int currentNumber = startNumber;
        int i = 0;
        while (currentNumber != 1){
            resultBuf[i] = currentNumber;
            currentNumber = collatz(currentNumber);
            i++;
        }
        resultBuf[i] = currentNumber;
    }
    else{
        printf("Folk failed\n");
        return 1;
    }
}