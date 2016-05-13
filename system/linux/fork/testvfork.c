#include <stdio.h>

int main() {
    int count = 1;
    int child;

    printf("Before create son, the father's count is:%d\n", count);
    if(!(child = vfork())) {
        printf("This is son, his pid is: %d and the count is: %d\n", getpid(), ++count);
        exit(1);
    } else {
        printf("After son, This is father, his pid is: %d and the count is: %d, and the child is: %d\n", getpid(), count, child);
    }
}