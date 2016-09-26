#include "server_activity.h"
#include <stdlib.h>
#include <unistd.h>

void create_server_activity(int srv_sockfd, int cli_sockfd)
{
	int pid;

	pid = fork();
	switch (pid) {
	case -1: {
		perror("Error on fork");
		exit(1);
	}
	case 0: {
		int _errno;

		close(srv_sockfd);
		_errno = do_server_activity(cli_sockfd);
		exit(_errno);
	}
	default: {
		close(cli_sockfd);
	}
	}
}

