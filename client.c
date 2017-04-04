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

//example args: p3client –s itsunix.albany.edu –p 61494 –a 88
//or p3client -h

#define SIZE 1024

int main(int argc, char *argv[])
{
	char * hostname = (char *)malloc(256 * sizeof(char));
	
	int port_no, num;
	
	struct sockaddr_in server_addr;
	
	struct hostent *serv;
	
	int sockfd, server_len, bytes_read;
	
	char * send = (char *)malloc(SIZE * sizeof(char));

	char * recv = (char *)malloc(SIZE * sizeof(char));
	
	char * temp = (char *)malloc(SIZE * sizeof(char));
	
	if(argv[1][1] == 'h')//help flag
	{
		fprintf(stdout, "p3client: a networking tool that can request a conversion (Arabic number <-> Roman numeral) from a server.\nBasic usage: p3client -s [hostname] -p [port] -[options] [value]\nOptions:\n\t-h, --help\t\t\t\tshow this help message and exit\n\t-a, --Arabic to Roman conversion\tvalue must be an integer\n\t-r, --Roman to Arabic conversion\tvalue must be a string of characters\n");
		
		exit(1);
	}
	
	//FOR HOSTNAME INFO
	if(strcmp(argv[1], "-s") != 0) //if -s flag not present
	{
		fprintf(stderr, "Error -- flag missing: -s\n");
	}
	
	else //store hostname
	{
		strcpy(hostname, argv[2]);
	}
	
	//FOR PORT INFO
	if(strcmp(argv[3], "-p") != 0) //if -p flag not present
	{
		fprintf(stderr, "Error -- flag missing: -p\n");
	}
	
	else //store port number
	{
		port_no = atoi(argv[4]);
	}
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Socket creation failure\n");
		exit(1);
	}
	
	serv = gethostbyname(hostname);
	
    memset((char *) &server_addr, 0, sizeof(server_addr));
	
    server_addr.sin_family = AF_INET;
    memcpy((char *)serv->h_addr, (char *)&server_addr.sin_addr.s_addr, serv->h_length);
    server_addr.sin_port = htons((unsigned short) port_no);
	
	server_len = sizeof(server_addr);
	
	memset(send, 0, SIZE);
	
	memset(recv, 0, SIZE);
	
	strcpy(send, argv[5]);
	
	strcpy(temp, argv[6]);
	
	strcat(send, temp);
	
	bytes_read = sendto(sockfd, send, strlen(send), 0, (struct sockaddr *)&server_addr, server_len); 
	
	//FOR CONVERSION TYPE
	if(argv[5][1] == 'a') //if -a flag present
	{
		//Arabic to Roman conversion
		bytes_read = recvfrom(sockfd, recv, SIZE, 0, (struct sockaddr *)&server_addr, &server_len);
		
		fprintf(stdout, "%s\n", recv);
	}
	
	else if(argv[5][1] == 'r') //if -r flag present
	{
		//Roman to Arabic conversion--server
		/*store the number of roman numerals by using 
		int len = strlen(argv[6]) and allocate that much memory for string pointer to the numerals*/
		bytes_read = recvfrom(sockfd, (void *)&num, sizeof(num), 0, (struct sockaddr *)&server_addr, &server_len);
		fprintf(stdout, "%d\n", num);
	}
	
	else//if -a or -r flag not present
	{
		fprintf(stderr, "Error -- indicate flag -a or -r for conversion type\n");
		exit(1);
	}
	
	return 0;
	
}