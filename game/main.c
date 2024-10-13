#include <api.h>
#include <stdio.h>

int main() {
    int answer = 0;
    askintquestion("Which OS do you use?", 4, answer, "Windows", "macOS", "Linux", "Other");
    return 0;
}
