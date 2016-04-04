#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main() {

    // Child process ids
    int c1, c2, data;

    // Pipe arrays
    int filedes1[2], filedes2[2];

    FILE *fd;

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

    // Create Child 1
    if ((c1 = fork()) < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed.\n");
        return EXIT_FAILURE;
    } else if (c1 == 0) {
        // CHILD 1
        // Output the process id
        printf("Child 1 PID: %d\n", getpid());

        // Open a file for writing
        fd = fopen("c1file", "w");
        close(filedes1[1]);
        close(filedes2[0]);
        close(filedes2[1]);

        for (int i = 0; i < 25; i++) {
            // Read data from filedes1
            read(filedes1[0], (char *)&data, sizeof(int));

            // Output value of data
            fprintf(fd, "Received %d\n", data);
        }

        return EXIT_SUCCESS;
    } else if ((c2 = fork()) < 0) {
        fprintf(stderr, "Fork failed.\n");
        return EXIT_FAILURE;
    } else if (c2 == 0) {
        // CHILD 2
        printf("Child 2 PID: %d\n", getpid());
        close(filedes1[0]);
        close(filedes2[1]);

        // Open the file for writing
        fd = fopen("c2file", "w");

        // Loop for 25 times
        for (int i = 0; i < 25; i++) {
            // Read data from filedes2
            read(filedes2[0], (char *)&data, sizeof(int));
            // Output value of data being received
            fprintf(fd, "Received %d\n", data);
            // Increment data by 5
            data = data + 5;
            // Output value of data being sent
            fprintf(fd, "Sending %d\n", data);
            // Write data to filedes1
            write(filedes1[1], (void *)&data, sizeof(int));
        }

        // Exit the program
        return EXIT_SUCCESS;
    }

    // PARENT PROCESS
    // Output process id
    printf("Parent PID: %d\n", getpid());
    // Open file "pfile" for writing
    fd = fopen("pfile", "w");

    // Close other ends of pipes
    close(filedes1[0]);
    close(filedes1[1]);
    close(filedes2[0]);

    // Loop 25 times
    for (int i = 0; i < 25; i++) {
        // Output value of i
        fprintf(fd, "Sending %d\n", i);

        // Write value of i
        write(filedes2[1], (void *)&i, sizeof(int));
    }

    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);
}