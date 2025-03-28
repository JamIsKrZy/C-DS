#include <stdio.h>

int main() {
    printf("Hello " "World!\n"); // Prints: Hello World!

    const char *msg = "This is "
                      "a single string "
                      "across multiple lines.";
    printf("%s\n", msg);

    return 0;
}