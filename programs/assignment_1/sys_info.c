#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(int argc, char *argv[]){

    pid_t pid;  //process id of parent and child process
    int fd[2],nbytes; //fd array,  reading and writing for pipe
    char buffer[80];
    pipe(fd);
    pid = fork(); //fork to create processes
// to check valid input format
    if (argc!=2) {
	fprintf(stderr, "Not valid!!\n");
	_exit(0);
	}
//return 0 for child process
    if (pid == 0){
        pid = getpid();
        printf("Child PID = %d \n",pid);
        printf("%s", buffer);
        close(fd[1]); //explicitly closing the pipe
        nbytes = read(fd[0], buffer, sizeof(buffer));
        if ( strcmp(buffer, "/bin/echo") == 0) {

                execl(buffer,"echo","Hello world",(char* ) NULL);
        }
        else if (strcmp(buffer, "/bin/date") == 0) {
                execl(buffer,"date", (char *)NULL);
        }
        else if (strcmp(buffer, "/usr/bin/uname") == 0) {
                execl( buffer,"uname" , (char *)NULL);
        }
        else if (strcmp(buffer, "/bin/hostname") == 0) {
                execl( buffer,"hostname", (char *)NULL);
        }
	else {
		fprintf(stderr, "Invalid argument\n");
	}

        _exit(0);

               }

//parent process
     else{

        pid = getpid();
        printf("Parent PID = %d \n",pid);
        close(fd[0]); //closing the pipe
        write(fd[1], argv[1], strlen(argv[1])+1);
        sleep(1); //for parent process to wait till child exit
        _exit(0);
       }
    }


