#include <stdio.h>
#include <xinu.h>
#include <stdlib.h>
#include <string.h>


void print_usage()
  printf("Usage: process_ring\n");



void polling_init(int32 p, int32 mailbox[]) {
	for (int32 i=0; i<p; i++) 
		resume(create(polling, 1024, 20, "polling", 3, i, mailbox[i], &mailbox, p));
}

process polling(int32 index, int32 countdown, volatile int32 *mailbox, int32 len) {
	int32 last = countdown+1;
	int32 round = 0;
	while (last>0) {
		int32 tmp = *mailbox[index]
		if (last!=temp) {
			printf("Ring Element %d : Round %d : Value %d\n", index, round, tmp);
			last = tmp;
			round += 1;
			*mailbox[(index+1)%len] = tmp-1;
		}
	}
	return OK;
}
	
shellcmd xsh_process_ring(int argc, char *args[]) {
	int32 p = 2; /* specified defaults */
	int32 r = 3;
	char implementation[80] = "poll";
	int32 arr[p], mailbox[p], i;
	if (argc>1) {
		for(i = 1; i < argc; i++){
			if (!strncmp("-p", args[i], 3)){
				/* parse numeric argument to -p */
				if (!(i+1<argc)) {
					/* No argument after flag */
					print_usage();
					printf("-p flag expected an argument\n");
					return SHELL_ERROR;
				}
				p = atoi(args[i+1]);
				if (!(0 <= p && p <= 64)) {
				/* The number is out of range */
					print_usage();
					printf("-p flag expected a number between 0 - 64\n");
					return SHELL_ERROR;
				}
				i += 1; 
			} else if (!strncmp("-r", args[i], 3)) {
				if (!(i+1<argc)) {
					/* No argument after flag */
					print_usage();
					printf("-r flag expected an argument\n");
					return SHELL_ERROR;
				}
				r = atoi(args[i+1]);
				if (!(0 <= r && r <= 100)) {
				/* The number is out of range */
					print_usage();
					printf("-r flag expected a number between 0 - 100\n");
					return SHELL_ERROR;
				}
				i += 1; 
			} else if (!strncmp("--help", args[i], 7)) {
				if ((i+1<argc)) {
					print_usage();
					printf("--help flag does not take any arguments\n");
					return SHELL_ERROR;
				}
				print_usage();
                printf("\nDescription:\n");
                printf("\tCoordinates processes to count from some number down to zero\n");
                printf("Options:\n");
                printf("\t-p\tthe number of processes <0-64> (default 2)\n");
                printf("\t-r\tthe number of rounds (default 3)\n");
                printf("\t-i\tthe implementation <poll or sync> (default poll)\n");
                printf("\t--help\tdisplay this help and exit\n");
				i += 1; 
			} else {
				printf("process_ring: invalid argument\n");
				printf("Try 'process_ring --help' for more information\n");
			} 	
		}
	} 
	for (i=0; i<p; i++)
		arr[i] = i
	mailbox[0] = p*r-1;
	printf("%s\n", implementation);
	printf("Number of processes: %d\n", p);
	printf("Number of rounds: %d\n", r);
	if(!strncmp(implementation,"poll"))
		polling_init(p, mailbox[])
	return SHELL_OK;
}

