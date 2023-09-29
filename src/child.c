#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char FileName_child[256];
    ssize_t b3 = read(STDIN_FILENO, FileName_child, sizeof(FileName_child));
    FileName_child[b3-1] = '\0';
    
    char Stroka_child[256];
    ssize_t b4 = read(STDIN_FILENO, Stroka_child, sizeof(Stroka_child));
    Stroka_child[b4-1] = '\0';

    if(Stroka_child[b4 - 2] == '.' || Stroka_child[b4 - 2] == ';') {
        printf("%s\n", Stroka_child);
    } else {
        write(STDERR_FILENO, "Error", 6);
    }


    return 0;
}
  