#include <stdio.h>
#include <stdarg.h>

#define LOG_INFO(fmt, ...) printf("[INFO] " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) fprintf(stderr, "[ERROR] " fmt "\n", ##__VA_ARGS__)

int main() {
    int num = 42;
    const char *name = "Alice";

    LOG_INFO("Hello, World!");
    LOG_INFO("The number is %d", num);
    LOG_INFO("User: %s with ID %d", name, num);

    LOG_ERROR("File not found: %s", "data.txt");
    LOG_ERROR("Failed to allocate memory!");

    return 0;
}