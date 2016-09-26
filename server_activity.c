#include "server_activity.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 * SERVER_ACTIVITY()
 *
 * There is a separate instance of this
 * function for each connection. It
 * recieves a file name from client and
 * sends it`s contents back to the
 * client.
 *
 * PARAMS
 * int sockfd -- a file descriptor for
 *               client socket
 *
 * RETURN VALUE
 * If function succeed, it returns zero.
 * Otherwise return value is nonzero.
 */
int do_server_activity(int sockfd)
{
	int n;
	char buf[256];
	FILE *f;

	memset(buf, 0, 256);
	if (read(sockfd, buf, 255) < 0) {
		perror("ERROR reading from socket");
		return 1;
	}

	system("ls");

	f = fopen(buf, "rb");
	if (f == NULL) {
		perror("Failed to open file");
		/*fprintf(stderr, "Could not open %s for reading.\n", buf);*/
		return 1;
	}

	while ((n = fread(buf, 1, 255, f)) > 0) {
		if (write(sockfd, buf, n) < 0) {
			perror("ERROR writing to socket");
			return 1;
		}
	}

	fclose(f);

	return 0;
}
