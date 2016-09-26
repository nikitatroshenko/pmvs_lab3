#include <pthread.h>
#include "server_activity.h"
#include <stdio.h>

void *connection_handler_start_routine(void *arg)
{
	int cli_sfd = *(int *)arg;
	printf("tsfd=%d\n", cli_sfd);
	do_server_activity(cli_sfd);
	close(cli_sfd);

	return NULL;
}

void create_server_activity(int srv_sfd, int cli_sfd)
{
	pthread_t tid;
	int _cli_sfd;
	
	printf("msfd=%d\n", _cli_sfd);
	pthread_create(&tid, NULL, connection_handler_start_routine, &_cli_sfd);
}
