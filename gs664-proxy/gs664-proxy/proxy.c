/*
 * proxy.c - A Simple Sequential Web proxy
 *
 * Course Name: 14:332:456-Network Centric Programming
 * Assignment 2
 * Student Name: Gunbir Singh
 * 
 * IMPORTANT: Give a high level description of your code here. You
 * must also provide a header comment at the beginning of each
 * function that describes what that function does.
 */ 

#include "csapp.h"
#include <sys/socket.h>

/*
 * Function prototypes
 */
void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, char *uri, int size);
 
/* 
 * main - Main routine for the proxy program 
 */
int main(int argc, char **argv)
{
	int listenfd; 
	int connfd; 
	int serverfd; 
	int len;	
	struct sockaddr_in cliaddr; 
	struct sockaddr_in servaddr; 
	struct hostent *hp;	
	char *haddrp;
	rio_t rio;
	rio_t rio2;
	char dummyBuffer[MAXBUF];   
	char dummyBuffer2[MAXBUF];  
	char dummyBuffer3[MAXBUF];  
	char dummyBuffer4[MAXBUF];  
	char dummyBuffer5[MAXBUF];  
	char dummyBuffer6[MAXBUF];  
	char dummyBuffer7[MAXBUF];  
	char dummyBuffer8[MAXBUF];  
	char fullUrlBuffer[MAXBUF]; 
	char parsedUrlBuffer[MAXBUF];	
	char parsedPortNPath[MAXBUF];	
	char port[MAXBUF];		
	char urlBuffer[MAXBUF];		
	char pathBuffer[MAXBUF];	
	char clientRequest[MAXBUF];	
	int n;	
	char GET[3];	
	char http[30];	
	int portNumber = 80;	
	char* token;
	int isPath;	

	/* Check arguments */
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
		exit(0);
	}

	//Get a descriptor for stream socket communicating with IPv4 Internet Protocals
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	//Zero out servaddr stucture
	bzero(&servaddr, sizeof(servaddr));
	//Set server family to IPv4
	servaddr.sin_family = AF_INET;
	//Set the internet address
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	//Set port to user defined number
	servaddr.sin_port = htons(atoi(argv[1]));

	//Bind name to the new socket
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	//Listen for connection on the newly defined scoket
	listen(listenfd, LISTENQ);	

	while(1)
	{
		//Get size of the client
		len = sizeof(cliaddr);

		//Accept the connection over the socket and store connection file descriptor
		connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, (socklen_t *) &len);

		if(connfd < 0)
		{
			exit(0);
		}

		/* Determine the domain name and IP address of the client */
		hp = Gethostbyaddr((const char *)&cliaddr.sin_addr.s_addr, 
					sizeof(cliaddr.sin_addr.s_addr), AF_INET);
		haddrp = inet_ntoa(cliaddr.sin_addr);

		printf("Proxy established connection with %s (%s)\n", hp->h_name, haddrp);

		//Initialize the rio structure
		Rio_readinitb(&rio, connfd);


		/**
			BEGIN READING FROM THE BROWSER!
		**/
		//read first line into buffer
		if((n = rio_readlineb(&rio, dummyBuffer, sizeof(dummyBuffer))) > 0)
		{
			if(strncmp(dummyBuffer, "GET", 3) == 0)
			{
				printf("\n\nConnection Information\n--------------------------------\n");
				printf("%s", dummyBuffer);
				
				//Grab important members from the buffer
				sscanf(dummyBuffer, "%s %s %s", GET, fullUrlBuffer, http);
				
				//Uncomment to verify correct members were grabbed.
				//printf("\n%s\n%s\n%s\n\n", GET, fullUrlBuffer, http);

				//Remove http:// from the url
				sscanf(fullUrlBuffer, "http://%s", parsedUrlBuffer);
				
				//Uncomment to verify if the url was correctly parsed
				//printf("\n%s\n\n", parsedUrlBuffer);
				
				//Determine if a port number was provided and if it is correctly formatted
				if(strstr(parsedUrlBuffer, ":") != NULL)
				{
					
					strcpy(urlBuffer, strtok(parsedUrlBuffer, ":"));
					//printf("%s\n", urlBuffer);
					
					//Remove the port and path 
					strcpy(parsedPortNPath, strtok(NULL, ":"));
					//printf("%s\n", parsedPortNPath);

					//Grab the port
					strcpy(port, strtok(parsedPortNPath, "/"));
					//printf("%s\n", port);
					
					//Convert to an Integer
					portNumber = atoi(port);
					//printf("%d\n", portNumber);

					if((token = strtok(NULL, "")) != NULL)
					{ 
						isPath = 0;
						//Grab the path
						strcpy(pathBuffer, token);
						printf("%s\n", pathBuffer);
					}
					else
					{
						isPath = 1;	
					}
				}
				else
				{
					strcpy(urlBuffer, strtok(parsedUrlBuffer, "/"));
					printf("%s\n", urlBuffer);
					
					if((token = strtok(NULL, "")) != NULL)
					{ 
						isPath = 0;
						//Grab the path
						strcpy(pathBuffer, token);
						printf("%s\n", pathBuffer);
					}
					else
					{
						isPath = 1;
					}
				}

			}
			else
			{//Something was returned but it is not correct.
				exit(0);
			}
		}
		else
		{	//Leave if nothing was returned
			exit(0);
		}

		//Read Host information into buffer if it exists
		if((n = rio_readlineb(&rio, dummyBuffer2, sizeof(dummyBuffer2))) > 0)
		{
			printf("%s", dummyBuffer2);
		}
	
		//Read User-Agent information into buffer if it exists
		if((n = rio_readlineb(&rio, dummyBuffer3, sizeof(dummyBuffer3))) > 0)
		{
			printf("%s", dummyBuffer3);
		}

		//Read Accept information into buffer if it exists
		if((n = rio_readlineb(&rio, dummyBuffer4, sizeof(dummyBuffer4))) > 0)
		{
			printf("%s", dummyBuffer4);
		}

		//Read Accept-Language information into buffer if it exists
		if((n = rio_readlineb(&rio, dummyBuffer5, sizeof(dummyBuffer5))) > 0)
		{
			printf("%s", dummyBuffer5);
		}

		//Read Accept-Encoding information into buffer if it exists
		if((n = rio_readlineb(&rio, dummyBuffer6, sizeof(dummyBuffer6))) > 0)
		{
			printf("%s", dummyBuffer6);
		}

		//Read Cookie information into buffer if it exists
		if((n = rio_readlineb(&rio, dummyBuffer7, sizeof(dummyBuffer7))) > 0)
		{
			printf("%s", dummyBuffer7);
		}

		//Read Connection information if it exists
		if((n = rio_readlineb(&rio, dummyBuffer8, sizeof(dummyBuffer8))) > 0)
		{
			printf("%s", dummyBuffer8);
		}

		printf("\n\n");

		//Open up connection with the server and get the file descriptor
		serverfd = Open_clientfd(urlBuffer, portNumber); 

		//Initialize new rio structure
		Rio_readinitb(&rio2, serverfd);

		if(isPath == 0)
		{
			//Make the HTTP request
			sprintf(clientRequest, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", 					pathBuffer, urlBuffer);		
		}
		else
		{
			//Make the HTTP request
			sprintf(clientRequest, "GET / HTTP/1.1\r\nHost: %s\r\n\r\n", 					urlBuffer);	
		}

		printf("ClientRequst:\n%s\n", clientRequest);
		
		Rio_writen(serverfd, clientRequest, sizeof(clientRequest));

		len = 0;


		while((n = Rio_readlineb(&rio2, dummyBuffer, sizeof(dummyBuffer))) > 0)
		{
			write(connfd, dummyBuffer, n);
			len += n;	
			bzero(dummyBuffer, sizeof(dummyBuffer));	
		}

		FILE *log = fopen("proxy.log", "a");
		char logEntry[2000];
		format_log_entry(logEntry, &cliaddr, fullUrlBuffer, len);
		fprintf(log, "%s\n", logEntry);
		printf("Log Entry Appended: %s\n", logEntry);
		fclose(log);
		//bzero(dummyBuffer, sizeof(dummyBuffer));
		//bzero(dummyBuffer2, sizeof(dummyBuffer2));
		//bzero(dummyBuffer3, sizeof(dummyBuffer3));
		//bzero(dummyBuffer4, sizeof(dummyBuffer4));
		//bzero(dummyBuffer5, sizeof(dummyBuffer5));
		//bzero(dummyBuffer6, sizeof(dummyBuffer6));
		//bzero(dummyBuffer7, sizeof(dummyBuffer7));
		//bzero(dummyBuffer8, sizeof(dummyBuffer8));
		//bzero(clientRequest, sizeof(clientRequest));
		//bzero(pathBuffer, sizeof(pathBuffer));
		//bzero(urlBuffer, sizeof(urlBuffer));
		//bzero(parsedUrlBuffer, sizeof(parsedUrlBuffer));
		//bzero(parsedPortNPath, sizeof(parsedPortNPath));
		//bzero(fullUrlBuffer, sizeof(fullUrlBuffer));

		Close(serverfd);
		Close(connfd);

	
	}

	exit(0);
}

/*
 * format_log_entry - Create a formatted log entry in logstring. 
 * 
 * The inputs are the socket address of the requesting client
 * (sockaddr), the URI from the request (uri), and the size in bytes
 * of the response from the server (size).
 */
void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, char *uri, int size)
{
	time_t now;
	char time_str[MAXLINE];
	unsigned long host;
	unsigned char a, b, c, d;

	/* Get a formatted time string */
	now = time(NULL);
	strftime(time_str, MAXLINE, "%a %d %b %Y %H:%M:%S %Z", localtime(&now));

	/* 
	* Convert the IP address in network byte order to dotted decimal
	* form. Note that we could have used inet_ntoa, but chose not to
	* because inet_ntoa is a Class 3 thread unsafe function that
	* returns a pointer to a static variable (Ch 13, CS:APP).
	*/
	host = ntohl(sockaddr->sin_addr.s_addr);
	a = host >> 24;
	b = (host >> 16) & 0xff;
	c = (host >> 8) & 0xff;
	d = host & 0xff;


	/* Return the formatted log entry string */
	sprintf(logstring, "%s: %d.%d.%d.%d %s", time_str, a, b, c, d, uri);
}
