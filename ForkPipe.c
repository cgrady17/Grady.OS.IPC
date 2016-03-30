#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

int main() {
    int c1, c2;

    printf("I am child1");

    c1 = fork();

    printf("I have been forked: %d", c1);
}