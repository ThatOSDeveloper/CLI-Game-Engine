#include <stdio.h>
#include <stdarg.h>

void askintquestion(char* question, int answeramount, int buffer, ...) {
    va_list args;
    va_start(args, buffer); // Note: `buffer` is used as the last fixed argument

    printf("%s\n", question); // Print the question

    // Loop through each argument based on answeramount
    for (int i = 0; i < answeramount; i++) {
        char *answer = va_arg(args, char*); // Get the next string argument
        printf("Answer %d: %s\n", i + 1, answer);
    }

    va_end(args); // Clean up variable argument list

    // Prompt for an integer input
    int number = 0;
    printf("Please enter an integer: ");
    scanf("%d", &number); // Read an integer from the user
}
