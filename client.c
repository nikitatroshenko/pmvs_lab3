#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

void handle_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	int mysfd, portno;
	int n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
	char *p;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s hostname port", argv[0]);
		exit(1);
	}

	mysfd = socket(AF_INET, SOCK_STREAM, 0);
	if (mysfd == -1)
		handle_error("ERROR on creating socket");

	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr, "ERROR no host '%s'", argv[1]);
		exit(EXIT_FAILURE);
	}

	portno = atoi(argv[2]);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy(&serv_addr.sin_addr, server->h_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(mysfd, (struct sockaddr *)&serv_addr,
		sizeof(serv_addr)) == -1)
		handle_error("Error on connecting host");

	printf("Enter file name on host machine: ");
	memset(buffer, 0, 256);
	fgets(buffer, 255, stdin);
	for (p = buffer; *p != '\0'; p++) {
		if (*p == '\n') {
			*p = '\0';
			break;
		}
	}

	if (write(mysfd, buffer, strlen(buffer)) == -1)
		handle_error("Error on writing to socket");

	memset(buffer, 0, 256);
	while ((n = read(mysfd, buffer, 255)) > 0)
		fwrite(buffer, 1, n, stdout);

	close(mysfd);
	return 0;
}

