#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

// example: p3server –p 61494
//or p3server -h

#define SIZE 1024

int main(int argc, char *argv[])
{
	int sockfd, count, client_len, bytes_read, num, data_len;
	
	char flag;
	
	char * data = (char *)malloc(SIZE * sizeof(char));
	
	char * send = (char *)malloc(SIZE * sizeof(char));
	
	char * temp = (char *)malloc(SIZE * sizeof(char));
	
	struct sockaddr_in server_addr, client_addr;
	
	if(argv[1][1] == 'h')//help flag
	{
		fprintf(stdout, "p3server: a UDP server that acts as an Arabic number <-> Roman numeral converter.\nBasic usage: p3server [options]\nOptions:\n\t-h,\t   --help\t\tshow this help message and exit\n\t-p [port], --port number\tclients can request from the server with this port\nNote: this server uses a connectionless transport protocol.\n");
		
		exit(1);
	}
	
	int port_no = atoi(argv[2]);
	
	//create socket
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Socket creation failure");
		exit(1);
	}
	
	//allocate memory for socket structure
	memset((char *)&server_addr, 0, sizeof(server_addr));
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons((unsigned short) port_no);
	
	//bind socket to host address
	if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)))
	{
		perror("Binding failure");
		exit(1);
	}
	 
	client_len = sizeof(client_addr);
	
	memset(data, 0, SIZE);
	
	while(1)
	{
		bytes_read = recvfrom(sockfd, data, SIZE, 0, (struct sockaddr *)&client_addr, &client_len);

		flag = data[1];

		strncpy(temp, data + 2, bytes_read - 2);
		
		data_len = bytes_read - 2;
			
		if(flag == 'r')
		{
			//romanToArabic
			//convertToArabic		
			
			num = convertToArabic(temp, data_len);
			
			memset(temp, '\0', sizeof(temp));

			bytes_read = sendto(sockfd, (void *)&num, sizeof(int), 0, (struct sockaddr *)&client_addr, client_len);
		}
		else if(flag == 'a')
		{
			//arabicToRoman
			//convertToRoman
			
			send = (char *)convertToRoman(temp);
			
			memset(temp, '\0', sizeof(temp));
			
			bytes_read = sendto(sockfd, send, strlen(send) , 0, (struct sockaddr *)&client_addr, client_len);
			
		}
	}
}