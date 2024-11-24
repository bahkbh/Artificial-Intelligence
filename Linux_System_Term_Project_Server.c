#include <arpa/inet.h> 
#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>  

void error_handling(char *toserver);

int main(int argc, char *argv[])

{
	int serv_sock;
	int clnt_sock;
	int strr_len;
	int a;
	int file_descriptor;
	char toserver[40];
	char buf[1460];
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

        socklen_t clnt_addr_size;
        if (argc != 2)
        {printf("Usage:%s <port>\n", argv[0]);
        exit(1);}
        serv_sock = socket(PF_INET, SOCK_STREAM, 0); 
        if (serv_sock == -1)
        error_handling("socket() error");
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(atoi(argv[1]));
        if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) 
        error_handling("bind() error");
        if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size); 
        if (clnt_sock == -1)
        error_handling("accept() error");
 	
 	strr_len = read(clnt_sock, toserver, sizeof(toserver) - 1);
	if (strr_len == -1)
	error_handling("read() error");

	printf("%s\n", toserver);

	file_descriptor=open("test.mp4", 0);
	if (file_descriptor==-1)
		error_handling("File Open Error");
	while(1) 
	{ 
	a=read(file_descriptor, buf, 1460);
        write(clnt_sock, buf, a); 
        if(a==0){
        printf("Succesfully Sended test.mp4!\n");
        break;
        }
	} 
        
        close(file_descriptor);
        close(clnt_sock);
        close(serv_sock);

        return 0;

}

 
void error_handling(char *toserver)

{

        fputs(toserver, stderr);

        fputc('\n', stderr);

        exit(1);

}

