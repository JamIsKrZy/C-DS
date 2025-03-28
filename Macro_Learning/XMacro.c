#include <stdio.h>

// Define error codes using X-Macros
#define ERROR_CODES \
    X(SUCCESS, "Success") \
    X(NOT_FOUND, "Not Found") \
    X(ACCESS_DENIED, "Access Denied") \
    X(TIMEOUT, "Operation Timed Out") \
    X(OUT_OF_MEMORY, "Out of Memory")

// Step 1: Generate the enum
typedef enum {
    #define X(name, str) name,
    ERROR_CODES
    #undef X
} ErrorCode;

// Step 2: Generate a function to convert enum to string
const char* error_to_string(ErrorCode err) {
    switch (err) {
        #define X(name, str) case name: return str;
        ERROR_CODES
        #undef X
        default: return "Unknown Error";
    }
}

// Step 3: Generate an array of all error codes
const char *error_strings[] = {
    #define X(name, str) str,
    ERROR_CODES
    #undef X
};

int main() {
    ErrorCode err = NOT_FOUND;

    printf("Error Code: %d\n", err);
    printf("Error Message: %s\n", error_to_string(err));

    // Print all error messages
    printf("\nAll Errors:\n");
    for (int i = 0; i < sizeof(error_strings) / sizeof(error_strings[0]); i++) {
        printf("  [%d] %s\n", i, error_strings[i]);
    }

    return 0;
}