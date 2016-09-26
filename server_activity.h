#ifndef __server_activity_included__
#define __server_activity_included__

void create_server_activity(int srv_sockfd, int cli_sockfd);

int do_server_activity(int sockfd);

#endif /* !__server_activity_included__ */
