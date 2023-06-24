#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    } else {
        // Parent process
        printf("Parent process:\n");
        printf("PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    }

    return 0;
}
