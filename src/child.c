#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    char FileName_child[256];
    ssize_t b3 = read(STDIN_FILENO, FileName_child, sizeof(FileName_child));
    FileName_child[b3-1] = '\0';
    int file = open(FileName_child, O_WRONLY |O_CREAT|O_TRUNC|S_IWUSR);
    if(file == -1) {
        perror("file opening error");
        return 1;
    }

    char Stroka_child[256];
    ssize_t b4 = read(STDIN_FILENO, Stroka_child, sizeof(Stroka_child));
    Stroka_child[b4-1] = '\0';

    if(Stroka_child[b4 - 2] == '.' || Stroka_child[b4 - 2] == ';') {
        write(STDOUT_FILENO,Stroka_child, sizeof(Stroka_child));
        write(file, Stroka_child, strlen(Stroka_child));
    } else {
        write(STDERR_FILENO, "Error\n", 6);
    }

    close(file);
    return 0;
}
  