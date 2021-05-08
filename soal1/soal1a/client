#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
  
int main(int argc, char const *argv[]) {

    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

char input[10];
char pass[100],user[100]
while(1){
input[10] = {0};
pass[100] = {0};
user[100] = {0};

Printf("Login / Register\n");
scanf("%s",input);
if(strcmp(input,"Login") == 0)
{
send(new_socket,"Login",strlen("Login"),0);
printf("Username: \nPassword : ");
scanf("%s",user);
scanf("%s", pass);
strcat(user,":");
strcat(user,pass);
send(new_socket , user , strlen(user), 0)
read(new_socket, buffer, 1024);
printf("%s\n",buffer);
}

else if(strcmp(input,"Register") == 0)
{
send(new_socket,"Login",strlen("Login"),0);
printf("Username: \nPassword : ");
scanf("%s",user);
scanf("%s", pass);
strcat(user,":");
strcat(user,pass);
send(new_socket , user , strlen(user), 0)
read(new_socket, buffer, 1024);
printf("%s\n",buffer);
}

else{
printf("error");
}
    return 0;
}
