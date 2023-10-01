#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/fcntl.h>

int create_process() {
    pid_t new_procces = fork();
    if( new_procces == -1) {
        write(STDERR_FILENO, "fork", 5);
        exit(-1);
    }

    return new_procces;
}

int main (int argc, char *argv[]) {
    
    int pipe1[2];
    int pipe2[2];
    int pipe3[2];

    if(pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        write(STDERR_FILENO, "Pipe was not created", 21);
    }
    
    pid_t child = create_process();
    
    
    if(child == 0){
        close(pipe1[1]);
        dup2(pipe1[0], STDIN_FILENO);

        close(pipe3[1]);
        dup2(pipe3[0], STDIN_FILENO);

        close(pipe2[0]);
        dup2(pipe2[1], STDOUT_FILENO);

        execvp("./child", argv);

    } else {
        char FileName[256];
        ssize_t b1 = read(STDIN_FILENO, FileName, sizeof(FileName));
        FileName[b1 - 1] = '\0';

        char Stroka[256];
        ssize_t b2 = read(STDIN_FILENO, Stroka, sizeof(Stroka));
        Stroka[b2-1] = '\0';

        close(pipe1[0]);
        write(pipe1[1], FileName, sizeof(FileName));
        close(pipe1[1]);

        close(pipe3[0]);
        write(pipe3[1], Stroka, sizeof(Stroka));
        close(pipe3[1]);

        char answer[256];
        close(pipe2[1]);
        read(pipe2[0],answer, sizeof(answer));
        close(pipe2[0]);

        write(STDOUT_FILENO, answer, sizeof(answer));
    }
    return 0;
}