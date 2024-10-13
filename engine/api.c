#include <stdio.h>
#include <stdarg.h>

// Function to read an integer from the user
void getint(int* buffer) {
    if (scanf("%d", buffer) != 1) { // Check if an integer was read successfully
        printf("Invalid input! Please enter an integer.\n");
        // Clear the input buffer
        while (getchar() != '\n'); // Discard invalid input
        *buffer = 0; // Reset buffer value
    }
}

// Function to ask a question and get an integer response
void askintquestion(const char* question, int answeramount, int* buffer, ...) {
    va_list args;
    va_start(args, buffer); // Initialize variable arguments

    printf("%s\n", question); // Print the question

    // Loop through each argument based on answeramount
    for (int i = 0; i < answeramount; i++) {
        char *answer = va_arg(args, char*); // Get the next string argument
        printf("Answer %d: %s\n", i, answer);
    }

    va_end(args); // Clean up variable argument list
    scanf("%d", buffer); // Get the user's response and store it in the location pointed to by buffer
}