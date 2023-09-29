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
    
    int fd1[2];
    int fd2[2];
    int fd3[2];

    if(pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1) {
        write(STDERR_FILENO, "Pipe was not created", 20);
    }
    
    pid_t child = create_process();
    
    
    if(child == 0){
        close(fd1[1]);
        dup2(fd1[0], STDIN_FILENO);

        close(fd3[1]);
        dup2(fd3[0], STDIN_FILENO);

        close(fd2[0]);
        dup2(fd2[1], STDOUT_FILENO);

        execvp("./child", argv);

    } else {
        char FileName[256];
        ssize_t b1 = read(STDIN_FILENO, FileName, sizeof(FileName));
        FileName[b1 - 1] = '\0';

        char Stroka[256];
        ssize_t b2 = read(STDIN_FILENO, Stroka, sizeof(Stroka));
        Stroka[b2-1] = '\0';

        close(fd1[0]);
        write(fd1[1], FileName, sizeof(FileName));
        close(fd1[1]);

        close(fd3[0]);
        write(fd3[1], Stroka, sizeof(Stroka));
        close(fd3[1]);

        waitpid(child, NULL, WUNTRACED);

        char answer[256];
        close(fd2[1]);
        read(fd2[0],answer, sizeof(answer));
        close(fd2[0]);

        printf("%s\n", answer);
    }
    return 0;
}