# soal-shift-sisop-modul-3-I02-2021

## Member's Name
- Muhammad Naufal Alif Islami (05111942000008)
- Drigo Alexander SIhombing (05111942000020)
- Fitriana Zahirah Tsabit (05111942000011)

## Question 1:

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
