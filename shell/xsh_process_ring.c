#include <xinu.h>
#include <stdlib.h> 
#include <stdio.h>
#include <process_ring.h>

void print_usage(void){
    printf("Usage: ...\n");
}
int32 p;
int32 r;
volatile int32 rounds;
shellcmd xsh_process_ring(int argc, char *args[])
{
    p = 2; /*  defaults values*/
    r = 3;
    rounds = 0;
    int32 i,j,k;
    char sync = 'p';
    for(i = 1; i < argc; i++){
        if (0 == strncmp("-p", args[i], 3)){
            if (! (i + 1 < argc)) {
                print_usage();
                printf("-p flag expected an argument\n");
                return SHELL_ERROR;
            }
            p = atoi(args[i + 1]);
            if (!(0 <= p && p <= 64)) {
                /* Processes out of range */
                print_usage();
                printf("-p flag expected a number between 0 - 64\n");
                return SHELL_ERROR;
            }
            i += 1;
        }
        else if (0 == strncmp("-r", args[i], 3)) {
            if (! (i + 1 < argc)) {
                print_usage();
                printf("-r flag expected an argument\n");
                return SHELL_ERROR;
            }
            r = atoi(args[i + 1]);
            if (!(r > 0)) {
                print_usage();
                printf("-r flag expected a number greater than 0\n");
                return SHELL_ERROR;
            }
            i += 1;
        }
        else if(0 == strncmp("-i", args[i], 3))
	 {
            if(0 == strncmp("sync", args[i+1], 4))
            {
                sync = 's';
            }
            else if(!(0 == strncmp("poll", args[i+1], 4)))
            {
                print_usage();
                printf("-i flag expected either POLL or SYNC\n");
                return SHELL_ERROR;
            }
            i += 1;
        }
        else
	{
            print_usage();
            printf("invalid flag");
        }
    }
    // for other processes and round values
    printf("Number of Processes: %d\n",p);
    printf("Number of Rounds: %d\n",r);
    volatile int32 countdown = (p * r) - 1;
    if(sync == 'p')
    {
        volatile int32 mailbox[p];
        mailbox[0] = countdown;
        for(k=1;k<p;k++)
            mailbox[k] = -1;
        for(j=0;j<p;j++)
        {
            resume(create(process_ring,1024,20,"polling",3,j,&countdown,mailbox));
        }
        while(countdown >= 0);
    }
    // when messaging is involved
    else if(sync == 's')
    {
	pid32 parent_pid = getpid();
        volatile pid32 messagepass[p];
        for(j=0;j<p;j++)
        {
            messagepass[j] = create(process_ring_message,1024,20,"messagepassing",3,j,messagepass,parent_pid);
            resume(messagepass[j]);
        }
        send(messagepass[0],countdown);
	receive();
    }
    return SHELL_OK;
}
