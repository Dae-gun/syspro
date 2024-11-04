#include <stdio.h>
#include <unistd.h>
int main()
{    
    printf("my processor number : [%d] \n", getpid());
    printf("my parent processor number : [%d] \n", getppid());
}

