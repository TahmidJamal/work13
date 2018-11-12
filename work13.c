#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>

static void sighandler (int signo) {
	if (signo == SIGINT) {
		printf("SIGINT detected\n");
		printf("Recording message to sighandles.txt noting exit due to SIGINT\n");

		time_t rawtime;
		time(&rawtime);
		struct tm *time_info = localtime(&rawtime);
		char time[25];
		time = asctime(time_info);
		printf("Time: %s\n", time );

		char note[29] = "Program exited due to SIGINT\n";
		printf("Note: %s\n", note );
		
		char message[52];
		strcat(message, time);
		strcat(message, note);
		strcat(message, "\n\n");
		printf("message: %s\n", message );

		int fd = open("sighandles.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (write(fd, message, sizeof(message)) == -1) {
			printf("Error writing to sighandles.txt\n%s\n", strerror(errno));
		}
		if (close(fd) == -1) {
			printf("Error closing sighandles.txt\n%s\n", strerror(errno));
		}
		exit(0);
	}
	else if (signo == SIGUSR1) {
		printf("Parent PID: %d\n", getppid());
	}
}

int main() {
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);

	while (1) {
		printf("My PID: %d\n", getpid());
		sleep(1);
	}

	return 0;
}