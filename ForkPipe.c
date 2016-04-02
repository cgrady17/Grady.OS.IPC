#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    // Child process ids
    int c1, c2;

    // Pipe arrays
    int filedes1[2], filedes2[2];

    // Create Pipe 1
    if (pipe(filedes1)) {
        // Pipe failed
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }

    // Create Pipe 2
    if (pipe(filedes2)) {
        // Pipe failed
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }

    /* Create Child 1 */
    c1 = fork();
    if (c1 < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed.\n");
        return EXIT_FAILURE;
    }

    c2 = fork();
    if (c2 < 0) {
        fprintf(stderr, "Fork failed.\n");
        return EXIT_FAILURE;
    }
}