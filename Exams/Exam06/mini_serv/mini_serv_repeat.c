#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int	fd_max = 0, count = 0;
fd_set rfds, wfds, afds;
char buff_read[1001], buff_write[40];
char* msgs[62000];
int	ids[62000];

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

void fatal_error() {
	write(2, "Fatal error\n", 12);
	exit(1);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

int	create_socket() {
	fd_max = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_max < 0)
		fatal_error();
	FD_SET(fd_max, &afds);
	return fd_max;
}

void notify_all(int author, char* msg) {
	for (int fd = 0; fd <= fd_max; fd ++) {
		if (FD_ISSET(fd, &wfds) && fd != author)
			send(fd, msg, strlen(msg), 0);
	}
	write(1, msg, strlen(msg));
}

void add_client(int fd) {
	if (fd > fd_max)
		fd_max = fd;
	ids[fd] = count++;
	msgs[fd] = NULL;
	FD_SET(fd, &afds);
	sprintf(buff_write, "server: client %d just arrived\n", ids[fd]);
	notify_all(fd, buff_write);
}

void remove_client(int fd) {
	sprintf(buff_write, "server: client %d just left\n", ids[fd]);
	notify_all(fd, buff_write);
	FD_CLR(fd, &afds);
	close(fd);
	// what we do with ids and msgs?
}

void send_message(int fd) {
	char *msg;

	while (extract_message(&(msgs[fd]), &msg)) 
	{
		sprintf(buff_write, "client %d: ", ids[fd]);
		notify_all(fd, buff_write);
		notify_all(fd, msg);
		free(msg);
	}
}

int main(int ac, char **av) {
	int sockfd, connfd;
	struct sockaddr_in servaddr; 

	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	FD_ZERO(&afds);
	sockfd = create_socket();
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1])); 
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		fatal_error();
	}
	if (listen(sockfd, 180) != 0) { // ???? name of macro
		fatal_error();
	}

	while (1) {
		wfds = rfds = afds;

		if (select(fd_max + 1, &rfds, &wfds, NULL, NULL) < 0)
			fatal_error();

		for (int fd=0; fd <= fd_max; fd ++) {
			if (!FD_ISSET(fd, &rfds))
				continue;
			
			if (fd == sockfd) {
				socklen_t acc = sizeof(servaddr);
				connfd = accept(sockfd, (struct sockaddr *)&servaddr, &acc);
				if (connfd >= 0) {
					add_client(connfd);
					break;
				}
			}
			else {
				printf("here2\n");
				int bytes_read = recv(fd, buff_read, 1000, 0);
				if (bytes_read <= 0) {
					remove_client(fd);
					break;
				}
				buff_read[bytes_read] = '\0';
				msgs[fd] = str_join(msgs[fd], buff_read);
				send_message(fd);
				// send msg
				// remove client if recv <= 0
			}
		}
		


	}
	// len = sizeof(cli);
	// connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	// if (connfd < 0) { 
    //     printf("server acccept failed...\n"); 
    //     exit(0); 
    // } 
    // else
    //     printf("server acccept the client...\n");
}