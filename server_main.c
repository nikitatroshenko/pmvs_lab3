#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_BACKLOG 5

void handle_error(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	int serv_sfd, cli_sfd, portno;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t cli_addr_len;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s port", argv[0]);
		exit(EXIT_FAILURE);
	}

	serv_sfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (serv_sfd == -1)
		handle_error("ERROR opening socket");

	portno = atoi(argv[1]);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(serv_sfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) == -1)
		handle_error("ERROR on binding");

	fprintf(stderr, "Listening...\n");
	if (-1 == listen(serv_sfd, LISTEN_BACKLOG)) {
		perror("ERROR listening");
	}

	while (1) {
		cli_addr_len = sizeof(struct sockaddr_in);
		cli_sfd = accept(serv_sfd, (struct sockaddr *) &cli_addr,
				&cli_addr_len);
		if (cli_sfd == -1)
			handle_error("ERROR accepting");
		
		fprintf(stderr, "CLient connected!\n");
		create_server_activity(serv_sfd, cli_sfd);
		/* do_server_activity(cli_sfd); */
	}
}

