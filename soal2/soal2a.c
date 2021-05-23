#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

void main() {
    // key_t key = 1234;
    // int *value;

    // int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    // value = shmat(shmid, NULL, 0);

    int matrix1[4][3], matrix2[3][6], multires[4][6];
    int i, j, k, res = 0;

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

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 6; j++) {
            for(k = 0; k < 3; k++) {
                res += matrix1[i][k] * matrix2[k][j];
            }
            multires[i][j] = res;
            res = 0;
        }
    }

    printf("Multiplication result : \n");
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 6; j++) {
            printf("%d ", multires[i][j]); 
        }
        printf("\n");
    }

    // sleep(5);

    // shmdt(value);
    // shmctl(shmid, IPC_RMID, NULL);

}
