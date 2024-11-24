#include <arpa/inet.h> 
#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/stat.h>
#include <sys/types.h> 
#include <unistd.h>  

void error_handling(char *toserver);

int main(int argc, char *argv[])

{

	int sock;
	int file_descriptor;
	int a;
	int b;
	char buf[1460];
 	char toserver[] = "Hello Server!";
	struct sockaddr_in serv_addr; 	

        if (argc != 3)
        {printf("Usage: %s <IP> <port>\n", argv[0]);
	exit(1);}
        sock = socket(PF_INET, SOCK_STREAM, 0);    
        if (sock == -1)
        error_handling("socket() error");
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
        serv_addr.sin_port = htons(atoi(argv[2]));
        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) 
        error_handling("connect() error");
        
	write(sock, toserver, sizeof(toserver));
	file_descriptor = open("receivetest.mp4",O_WRONLY|O_CREAT);  
	if (file_descriptor==-1)
	error_handling("File Open Error");
	while(1) 
	{
	a=read(sock, buf, 1460 );
	write(file_descriptor, buf, a);  
	if(a==0){
	b=chmod ("receivetest.mp4",0664);
	if (b==-1)
	error_handling("Mode Change Error");
	printf("Successfully Recieved test.mp4 file!\n");
	break;
	}
	} 

	close(file_descriptor);
	close(sock);

        return 0;

}

 
void error_handling(char *toserver)

{

        fputs(toserver, stderr);

        fputc('\n', stderr);

        exit(1);

}

