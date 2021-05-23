# soal-shift-sisop-modul-3-I02-2021

## Member's Name
- Muhammad Naufal Alif Islami (05111942000008)
- Drigo Alexander SIhombing (05111942000020)
- Fitriana Zahirah Tsabit (05111942000011)

## Question 1:
a) When a client is connected to the server, there are two main options. They are register and login. If the user has chosen the register option, the client will prompt an id and password to be sent to the server. Users can also login to the server. Login is successful if the id and the password sent to the server matched with one of the accounts listed on the server application. This system can accepts multiple connections at once. A connection is counted when a client application is connected to the server. If there are 2 connections or more then we must wait for the first client to exit the application to be able to login and use the application. Keverk wanted the file that stores the id and password named account.txt with the following format :

akun.txt
id:password
id2:password2

Client : 
   
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
        
  Server :     
  
        FILE *fdir;
        fdir = fopen("akun.txt","a+");    
        clear_buffer(command);
        valread = read(socketfd, command, BUFSIZ);
        if(strcmp(command,"register")==0)
        { 
            char buffers[BUFSIZ];
            clear_buffer(buffers);
            valread = read(socketfd,buffers,BUFSIZ);
            printf("Registrasi Sukses\n"); 
            fprintf(fdir,"%s\n",buffers);
            send(socketfd,"Register Success",strlen("Register Success"),0);
        }
        else if (strcmp(command,"login")==0)
        {
            char temp[BUFSIZ];
            char userada[10];
            char buffers[BUFSIZ];
            int flag = 0;
            clear_buffer(buffers);
            valread = read(socketfd,buffers,BUFSIZ);
            strcpy(userpass,buffers);
            while(fgets(temp, BUFSIZ, fdir) != NULL) 
            {
                if((strstr(temp, buffers)) != NULL) 
                {
                    printf("Login Berhasil\n");
                    flag = 1;
                    char kata[20] = "Login Success";
                    send(socketfd,kata, strlen(kata),0);
                    break;
                }                
            }

            if(flag == 0)
            {
                printf("Login Gagal\n");
                char kata[20] = "Login Failed";
                send(socketfd,kata, strlen(kata),0);
            }
        }
        
   File : 
   
   <img width="127" alt="Screen Shot 2021-05-23 at 21 19 55" src="https://user-images.githubusercontent.com/73428164/119264275-a8a5ce00-bc0c-11eb-90ff-47342c890aee.png">

   <img width="127" alt="Screen Shot 2021-05-23 at 21 18 56" src="https://user-images.githubusercontent.com/73428164/119264237-7eeca700-bc0c-11eb-9146-d355082f9ebc.png">
   
  
  
 b) The system has a database on a file named files.tsv. The content of the file is the file path on the server, publisher, and the year of publication. For every insertion and removal of a file in the folder FILES on the server, the file files.tsv will be affected. Folder FILES are made, automatically when the server is started
 
 c) Not only that, Keverk is asked to make a feature such that clients are able to insert new files to the server. FILES directory have a structure as follows :
 
  Client : 
  
        if(strcmp(command2,"add")==0){
                        char buffer[BUFSIZ];
                        int valread;
                        char pub[20],tahun_pub[10],path_file[50],add_data[110],len_data[20],temp_files[BUFSIZ];
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
                        while(fgets(temp_files, BUFSIZ, fd) != NULL) {
                            send(new_socket, temp_files, strlen(temp_files), 0);
                            bzero(temp_files, BUFSIZ) ;
                        }
                        fclose(fd); 
                        clear_buffer(buffer);
                        valread = read(new_socket , buffer, BUFSIZ);
                        if (strcmp(buffer, "complete") == 0) {
                            printf("Adding data complete\n");
                        } 
                        else {
                            printf("There's a problem adding data\n");
                        }

                    }
                    
                    
   Server : 
   
   
            else if(strcmp(command,"add")==0)
        {
            char buffers[BUFSIZ];
            printf("Adding to Database :\n");
            send(socketfd, "success", strlen("success"), 0);
            FILE *fdirc;
            fdirc = fopen("file.tsv", "a+");
            if (fdirc == NULL) {
                perror("No File");
                exit(EXIT_FAILURE);
            }
            clear_buffer(buffers);
            valread = read(socketfd, buffers, BUFSIZ);
            char filename[50];
            char pub[50];
            char tahun_pub[10];            
            join(buffers, filename, pub, tahun_pub);
            char data[200];
            sprintf(data, "FILES/%s\t%s\t%s", filename, pub, tahun_pub);
            upload(socketfd,filename);
            send(socketfd, "complete", strlen("complete"), 0);
            fprintf(fdirc, "%s\n", data);
            FILE* log = fopen("running.log", "a") ;
            fprintf(log, "Tambah : %s (%s)\n", filename, userpass);
            fclose(log) ;
            fclose(fdirc);
        }

     


## Question 2:
Crypto (you) is Loba's friend. One morning, Crypto saw Loba who was overwhelmed with his boss's assignment. Since Crypto is such a challenging person, he wanted to help Loba with his job. The details of the assignment are:

a)  Create a matrix multiplication program (4x3 and 3x6) and then display the results. The matrix will contain the numbers 1-20 (no need to create a number filter).

Input the elements of matrix 1 (matrix 4x3) and matrix 2 (matrix 3x6)

    printf("Enter matrix 4x3 : \n");
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 3; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }

    printf("Enter matrix 3x6 : \n");
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 6; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }
    
Calculate the multiplication of matrix 1 and matrix 2    
    
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 6; j++) {
            for(k = 0; k < 3; k++) {
                res += matrix1[i][k] * matrix2[k][j];
            }
            multires[i][j] = res;
            res = 0;
        }
    }
    
Display the result of the matrix multiplication
    
    printf("Multiplication result : \n");
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 6; j++) {
            printf("%d ", multires[i][j]); 
        }
        printf("\n");
    }
    
`Shared memory` to exchange data (result of matrix multiplication) between program [soal2a.c](/soal2/soal2a.c) and [soal2b.c](soal2/soal2b.c) 
    
    key_t key = 1234;
    int *value;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);
    .
    .
    .
    .
    .
    .
    sleep(5);

    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);

b)  Create a program using the output matrix of the previous program (program soal2a.c) (Note!: Use shared memory). Then the matrix will be calculated with the new matrix. As follows an example of calculation for the existing matrix. The calculation is that each cell originating from matrix A becomes a number for factorial, then cells from matrix  B become the maximum factorial limit (from largest to smallest) (Note!: Use threads for calculations in each cell). 

c)  For fear of lags in the process of helping Loba, Crypto also created a program (soal2c.c) to check the top 5 processes consuming computer resources with the command  “ps aux | sort -nrk 3,3 | head -5” (Note !: You must use IPC Pipes)

## Question 3:
