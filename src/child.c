#include <unistd.h>

int main() {
    char _string[256];
    int bytesRead;

    while (1) {
        bytesRead = read(STDIN_FILENO, _string, sizeof(_string));
        
        if (_string[bytesRead - 2] == ';' || _string[bytesRead - 2] == '.') {
            // строка заканчивается на ";" или "."
            write(STDOUT_FILENO, _string, bytesRead);
        } else {
            // строка не соответствует условию
            write(STDERR_FILENO, "Ошибка: строка не заканчивается на \";\" или \".\"\n", 80);
            exit(-1);
        }
    }

    return 0;
}