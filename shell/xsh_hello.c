#include <xinu.h>
#include <stdio.h>
#include <string.h>

shellcmd xsh_hello(int nargs, char *args[]) {
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
        printf("Usage: %s\n\n", args[0]);
        printf("Description:\n");
        printf("\tType %s string \n",args[0]);
        return 0;
    }
//print welcome statement only when no of arguments are too few or more
    if(nargs==2){
        printf("hello , %s, Welcome to the world of Xinu!", args[1]);
    }
    else if(nargs >2){
        fprintf(stderr, "%s: Too may arguments\n", args[0]);
    }

    
    else {
        fprintf(stderr, "%s: Too few arguments\n", args[0]);

    }
    
    printf("\n");
    
    return 0;
}
