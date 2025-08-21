#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>


fd_set	rfds, wfds, afds;
int		max_fd = 0, count = 0;
char*	msgs[63000];
int		ids[63000];
char	buff_read[1001], buff_write[42];


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

void fatal_error() {
	write(2, "Fatal error\n", 12);
	exit(1);
}

void notify_other(int author, char *msg) {
	for (int fd = 0; fd <= max_fd; fd ++) {
		if (fd != author && FD_ISSET(fd, &wfds)) {
			send(fd, msg, strlen(msg), 0);
		}
	}
	
}

int create_socket() {

	max_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (max_fd < 0) {
		//printf("here1");
		fatal_error();
	}
	FD_SET(max_fd, &afds);
	return max_fd;

}

void add_client(int fd) {
	if (fd > max_fd)
		max_fd = fd;
	ids[fd] = count++;
	msgs[fd] = NULL;
	FD_SET(fd, &afds);
	sprintf(buff_write, "server: client %d just arrived\n", fd);
	notify_other(fd, buff_write);
}

void send_msg(int fd) {
	char *msg;

	while (extract_message(&(msgs[fd]), &msg)) {
		sprintf(buff_write, "client %d: ", ids[fd]);
		notify_other(fd, buff_write);
		notify_other(fd, msg);
		free(msg);
	} 

}

void remove_client(int fd) {
	sprintf(buff_write, "server: client %d just left\n", fd);
	notify_other(fd, buff_write);
	free(msgs[fd]);
	FD_CLR(fd, &afds);
	close(fd);
}

int main(int ac, char** av) {
	int sockfd;
	struct sockaddr_in servaddr; 

	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	FD_ZERO(&afds);
	sockfd = create_socket();

	// socket create and verification 
	// sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	// if (sockfd < 0) { 
	// 	fatal_error(); 
	// } 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));

	// int opt = 1;
	// if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
	// 	perror("setsockopt");
	// 	fatal_error();
	// }

	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		//printf("here2");
		fatal_error();
	} 
	if (listen(sockfd, SOMAXCONN) != 0) {
		//printf("here3");
		fatal_error();
	}

	while (1) {
		wfds = rfds = afds;

		if (select(max_fd + 1, &rfds, &wfds, NULL, NULL) < 0) {
			//printf("here4");
			fatal_error();
		}
		for (int fd = 0; fd <= max_fd; fd++) {
			if (!FD_ISSET(fd, &rfds))
				continue;
			
			if (sockfd == fd) {
				socklen_t addrlen = sizeof(servaddr);
				int client_fd = accept(fd, (struct sockaddr*)&servaddr, &addrlen);
				if (client_fd >= 0) {
					add_client(client_fd); // Исправлено: передаем client_fd вместо fd
					break;
				}
			}
			else {
				int read_bytes = recv(fd, buff_read, 1000, 0); // Исправлено: используем fd вместо sockfd
				if (read_bytes <= 0) {
					remove_client(fd);
					break;
				}
				buff_read[read_bytes] = '\0';
				msgs[fd] = str_join(msgs[fd], buff_read);
				send_msg(fd);
			}
		}

	}

	/*
	len = sizeof(cli);
	connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	if (connfd < 0) { 
        //printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        //printf("server acccept the client...\n");
	*/
	return (0);
}