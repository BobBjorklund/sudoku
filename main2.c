#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <wait.h>

char* solved = "YES";
int s[9][9];

typedef struct {
    int x;
    int y;
} gridCoord;


void* doWork(void* param){
    int c[9] = {0};
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            c[s[i][j]-1]++;
        }
        for (int j = 0; j < 9; j++){
            if (c[j] != i+1) {
                solved = "NO";
            }
        }
    }
}

void* doWork1(void* param){
    int c2[9] = {0}; 
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            c2[s[j][i]-1]++;
        }
        for (int j = 0; j < 9; j++){
            if (c2[j] != i+1) {
                solved = "NO";
            }
        }
    }
}

void* doWork2(void* param){
    int c3[9] = {0}; 
    gridCoord* sq = (gridCoord*) param;
    for(int i = 0; i < 9; i++){
        int startX = sq[i].x;
        int startY = sq[i].y;
        for(int x = startX; x < startX+3; x++){
            for(int y = startY; y < startY+3; y++){
                c3[s[x][y]-1]++;
            }
        }

        for (int i = 0; i < 9; i++) {
            if (c3[i] != 1) {
            solved = "NO";
            }
        }
    }
}

void* doWork3(void* param){
    int c[9] = {0};
    int index = (*(int *)param);
    for (int j = 0; j < 9; j++) {
        c[s[index][j]-1]++;
    }
    for (int j = 0; j < 9; j++){
        if (c[j] != 1) {
            solved = "NO";
        }
    }
    pthread_exit(0);
}

void* doWork4(void* param){
    int c[9] = {0};
    int index = (*(int *)param);
    for (int i = 0; i < 9; i++) {
        c[s[i][index]-1]++;
    }
    for (int i = 0; i < 9; i++){
        if (c[i] != 1) {
            solved = "NO";
        }
    }
    pthread_exit(0);
} 

void* doWork5(void* param){
    int c[9] = {0}; 
    gridCoord* currPos = (gridCoord*) param;
    int startX = currPos->x;
    int startY = currPos->y;
    for(int x = startX; x < startX+3; x++){
        for(int y = startY; y < startY+3; y++){
            c[s[x][y]-1]++;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (c[i] != 1) {
        solved = "NO";
        }
    }
    pthread_exit(0);
}

void doOption3(time_t start){
    int SIZE = 4096;
    char* name = "solution?";
    char* ptr = "";
    int shm_fd;
    int c[9] = {0,0,0,0,0,0,0,0,0};
    int c2[9] = {0,0,0,0,0,0,0,0,0};
    int c3[9] = {0,0,0,0,0,0,0,0,0}; 
    pid_t pid = fork();
    if(pid == 0){
        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
        ftruncate(shm_fd, SIZE);
        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++) {
                c[s[i][j]-1]++;
            }
            for (int j = 0; j < 9; j++){
                if (c[j] != i+1) {
                    sprintf(ptr, "%s", "NO");
                }
            }
        }
    } else if(pid > 0){
        pid = fork();
        if(pid == 0){
            shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
            ftruncate(shm_fd, SIZE);
            ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
            for (int i = 0; i < 9; i++){
                for (int j = 0; j < 9; j++) {
                    c2[s[j][i]-1]++;
                }
                for (int j = 0; j < 9; j++){
                    if (c2[j] != i+1) {
                        sprintf(ptr, "%s", "NO");
                    }
                }
            }

        } else if(pid > 0){
            pid = fork();
            if(pid == 0){
                shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
                ftruncate(shm_fd, SIZE);
                ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
                gridCoord* sqPos = malloc(9 * sizeof(gridCoord));
                int index = 0;

                for(int i = 0; i < 3; i++){
                    for(int j = 0; j <= 6; j+=3){
                        sqPos[index].x = i * 3;
                        sqPos[index].y = j;
                        index++;
                    }
                }

                for(int i = 0; i < 9; i++){
                    int startX = sqPos[i].x;
                    int startY = sqPos[i].y;
                    for(int x = startX; x < startX+3; x++){
                        for(int y = startY; y < startY+3; y++){
                            c3[s[x][y]-1]++;
                        }
                    }

                    for (int i = 0; i < 9; i++) {
                        if (c3[i] != 1) {
                        solved = "NO";
                        }
                    }
                }
                
            } else if(pid > 0){
                wait(NULL);
                wait(NULL);
                wait(NULL);
                shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
                ftruncate(shm_fd, SIZE);
                ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
                if(strlen(ptr) != 0){
                    solved = ptr;
                }
                time_t ft = time(NULL) - start;
                printf("SOLUTION: %s (%ld seconds)",solved, ft);
                shm_unlink(name);
            }
        }
    }
}

int main(int argc, char **argv){
    FILE *fp = fopen("input.txt","r");
    time_t st = time(NULL);
    int option = atoi(argv[1]);
    for (int i = 0; i < 9; i++) {
        fscanf(fp,"%d %d %d %d %d %d %d %d %d",&s[i][0],&s[i][1],&s[i][2],&s[i][3],&s[i][4],&s[i][5],&s[i][6],&s[i][7],&s[i][8]);
        printf("%d %d %d %d %d %d %d %d %d\n",s[i][0],s[i][1],s[i][2],s[i][3],s[i][4],s[i][5],s[i][6],s[i][7],s[i][8]);
    }

    if(option == 1){
        pthread_t threads[3];
        gridCoord* sqPos = malloc(9 * sizeof(gridCoord));
        int index = 0;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j <= 6; j+=3){
                sqPos[index].x = i * 3;
                sqPos[index].y = j;
                index++;
            }
        }
        pthread_create(&threads[0], NULL, doWork, NULL);
        pthread_create(&threads[1], NULL, doWork1, NULL);
        pthread_create(&threads[2], NULL, doWork2, &sqPos);

        pthread_join(threads[0], NULL);
        pthread_join(threads[1], NULL);
        pthread_join(threads[2], NULL);

        time_t ft = time(NULL) - st;
        printf("SOLUTION: %s (%ld seconds)",solved, ft);
    }

    if(option == 2){
        pthread_t threads[27];
        gridCoord* sqPos = malloc(9 * sizeof(gridCoord));
        int index = 0;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j <= 6; j+=3){
                sqPos[index].x = i * 3;
                sqPos[index].y = j;
                index++;
            }
        }

        for(int i = 0; i < 9; i++) {
            pthread_create(&threads[i], NULL, doWork3, &i);
            pthread_create(&threads[i+9], NULL, doWork4, &i);
            pthread_create(&threads[i+18], NULL, doWork5, &sqPos[i]);
        }
        for(int i = 0; i < 27; i++) {
            pthread_join(threads[i], NULL);
        }
        time_t ft = time(NULL) - st;
        printf("SOLUTION: %s (%ld seconds)",solved, ft);
        free(sqPos);
    }

    if(option == 3){
        doOption3(st);
    }

    // printf("\nHere is the row array:");
    // for(int i  = 0; i < 9; i++){
    //     printf(" %d ", c[i]);
    // }
    // printf("\n");

    // printf("Here is the col array:");
    // for(int i  = 0; i < 9; i++){
    //     printf(" %d ", c2[i]);
    // }
    // printf("\n");

    // printf("Here is the square array:");
    // for(int i  = 0; i < 9; i++){
    //     printf(" %d ", c3[i]);
    // }
    // printf("\n");
    
    fclose(fp);
    return 0;
}