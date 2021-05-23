#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#define PORT 8080

void clear_buffer(char* b) 
{
    int i;
    for (i = 0; i < BUFSIZ ; i++)
        b[i] = '\0';
}

void connect_to_server(int socketfd) 
{
    char buffer[BUFSIZ];
    int valread;
    
    send(socketfd, "satu", strlen("satu"), 0);

    fprintf(stdout, "Menunggu koneksi dari server...\n");
    
    clear_buffer(buffer);
    valread = read(socketfd , buffer, BUFSIZ);
    fprintf(stdout, "Terhubung dengan server\n");

    send(socketfd, "Sukses lagi",strlen("Sukses lagi"),0);
}

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int new_socket = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFSIZ] = {0};
    if ((new_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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
  
    if (connect(new_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    connect_to_server(new_socket);
    while(1)
    {
        char buffer[BUFSIZ], command[BUFSIZ];
        printf("1. Login\n2. Register\n3. Logout\nCommand :\n");
        scanf("%s", command);
        if(strcmp(command,"login")==0)
        {
            send(new_socket,"login", strlen("login"),0);
            char username[200];
            char password[100];
            printf("Username : ");
            scanf("%s", username);
            printf("Password : ");
            scanf("%s", password);
            strcat(username, ":");
            strcat(username, password);

            send(new_socket , username , strlen(username) , 0 );
            clear_buffer(buffer);
            valread = read(new_socket , buffer, BUFSIZ);
            printf("%s\n",buffer);

            if(strcmp(buffer,"Login Success")==0)
            {
                while(1)
                {
                    printf("\n1. Add Database\n2.Exit\nCommand : ");
                    char command2[20];
                    scanf("%s", command2);
                    if(strcmp(command2,"add")==0)
                    {
                        // printf("Ini masuk add");
                        char buffer[BUFSIZ];
                        int valread;
                        char pub[20];
                        char tahun_pub[10];
                        char path_file[50];
                        char add_data[110];
                        char len_data[20];
                        char temp_files[BUFSIZ];

                        send(new_socket, "add", strlen("add"), 0);

                        clear_buffer(buffer);
                        valread = read(new_socket, buffer, BUFSIZ);

                        printf("Publisher: ");
                        scanf("%s", pub);
                        printf("Tahun Publikasi: ");
                        scanf("%s", tahun_pub);
                        printf("Filepath: ");
                        scanf("%s", path_file);

                        sprintf(add_data, "%s:%s:%s", path_file, pub, tahun_pub);

                        send(new_socket, add_data, strlen(add_data), 0);
                        
                        clear_buffer(buffer);
                        valread = read(new_socket, buffer,BUFSIZ);
 
                        send(new_socket, "berhasil",strlen("berhasil"),0);
                    
                        FILE *fd;
                        fd = fopen(path_file, "rb");

                        while(fgets(temp_files, BUFSIZ, fd) != NULL) 
                        {
                            send(new_socket, temp_files, strlen(temp_files), 0);
                            bzero(temp_files, BUFSIZ) ;
                        }
                        fclose(fd) ; 

                        clear_buffer(buffer);
                        valread = read(new_socket , buffer, BUFSIZ);

                        if (strcmp(buffer, "complete") == 0) 
                        {
                            printf("Adding data complete\n");
                        } 
                        else 
                        {
                            printf("There's a problem adding data\n");
                        }

                    }
                    
                    else if(strcmp(command2,"exit")==0)
                    {
                        break;
                    }
                }
            }   
        }
        else if(strcmp(command,"register")==0)
        {
            send(new_socket,"register", strlen("register"),0);
            char username[200];
            char password[100];
            printf("Username : ");
            scanf("%s", username);
            printf("Password : ");
            scanf("%s", password);
            strcat(username, ":");
            strcat(username, password);
            send(new_socket , username , strlen(username) , 0 );
            clear_buffer(buffer);
            valread = read(new_socket , buffer, BUFSIZ);
            printf("%s\n", buffer);
        }
        else if(strcmp(command,"logout")==0)
        {
            break;
        }
    }   
    return 0;
}
