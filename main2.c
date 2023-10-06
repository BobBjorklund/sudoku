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


void* doWork(void* param){
    int c[9] = {0,0,0,0,0,0,0,0,0};
    int c2[9] = {0,0,0,0,0,0,0,0,0};
    int c3[9] = {0,0,0,0,0,0,0,0,0}; 
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
    int c[9] = {0,0,0,0,0,0,0,0,0};
    int c2[9] = {0,0,0,0,0,0,0,0,0};
    int c3[9] = {0,0,0,0,0,0,0,0,0}; 
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
    int c[9] = {0,0,0,0,0,0,0,0,0};
    int c2[9] = {0,0,0,0,0,0,0,0,0};
    int c3[9] = {0,0,0,0,0,0,0,0,0}; 
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j++){
            c3[s[i][j]-1]++;
        }
    }
    for (int j = 0; j < 9; j++) {
        if (c3[j] != 1) {
            solved = "NO";
        }
    }
    for (int i = 0; i < 3; i ++) {
        for (int j = 3; j < 6; j++){
            c3[s[i][j]-1]++;
        }
    }
    for (int j = 0; j < 9; j++) {
        if (c3[j] != 2) {
            solved = "NO";
        }
    }
    for (int i = 0; i < 3; i ++) {
        for (int j = 6; j < 9; j++){
            c3[s[i][j]-1]++;
        }
    }
    for (int j = 0; j < 9; j++) {
        if (c3[j] != 3) {
            solved = "NO";
        }
    }
    for (int i = 3; i < 6; i ++) {
        for (int j = 0; j < 3; j++){
            c3[s[i][j]-1]++;
        }
    }
    for (int j = 0; j < 9; j++) {
        if (c3[j] != 4) {
            solved = "NO";
        }
    }
    for (int i = 3; i < 6; i ++) {
        for (int j = 3; j < 6; j++){
            c3[s[i][j]-1]++;
        }
    }
    for (int j = 0; j < 9; j++) {
        if (c3[j] != 5) {
            solved = "NO";
        }
    }
    for (int i = 3; i < 6; i ++) {
        for (int j = 6; j < 9; j++){
            c3[s[i][j]-1]++;
        }
    }
    for (int j = 0; j < 9; j++) {
        if (c3[j] != 6) {
            solved = "NO";
        }
    }
    for (int i = 6; i < 9; i ++) {
        for (int j = 0; j < 3; j++){
            c3[s[i][j]-1]++;
        }
    }
    for (int j = 0; j < 9; j++) {
        if (c3[j] != 7) {
            solved = "NO";
        }
    }
    for (int i = 6; i < 9; i ++) {
        for (int j = 3; j < 6; j++){
            c3[s[i][j]-1]++;
        }
    }
    for (int j = 0; j < 9; j++) {
        if (c3[j] != 8) {
            solved = "NO";
        }
    }
    for (int i = 6; i < 9; i ++) {
        for (int j = 6; j < 9; j++){
            c3[s[i][j]-1]++;
        }
    }
    for (int j = 0; j < 9; j++) {
        if (c3[j] != 9) {
            solved = "NO";
        }
    }
}

void* doWork3(void* param){
    int c[9] = {0,0,0,0,0,0,0,0,0};
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
    int c2[9] = {0,0,0,0,0,0,0,0,0};
    int index = (*(int *)param);
    for (int i = 0; i < 9; i++) {
        c2[s[i][index]-1]++;
    }
    for (int i = 0; i < 9; i++){
        if (c2[i] != 1) {
            solved = "NO";
        }
    }
    pthread_exit(0);
} 

void* doWork5(void* param){
    int c3[9] = {0,0,0,0,0,0,0,0,0}; 
    int index = (*(int *)param) - 1;
    if ((index) == 0){
        for (int i = 0; i < 3; i ++) {
            for (int j = 0; j < 3; j++){
                c3[s[i][j]-1]++;
            }
        }
        for (int j = 0; j < 9; j++) {
            if (c3[j] != 1) {
                solved = "NO";
            }
        }
    } else if ((index) == 1){
        for (int i = 0; i < 3; i ++) {
            for (int j = 3; j < 6; j++){
                c3[s[i][j]-1]++;
            }
        }
        for (int j = 0; j < 9; j++) {
            if (c3[j] != 1) {
                solved = "NO";
            }
        }
    } else if ((index) == 2){
        for (int i = 0; i < 3; i ++) {
            for (int j = 6; j < 9; j++){
                c3[s[i][j]-1]++;
            }
        }
        for (int j = 0; j < 9; j++) {
            if (c3[j] != 1) {
                solved = "NO";
            }
        }
    } else if ((index) == 3){
        for (int i = 3; i < 6; i ++) {
            for (int j = 0; j < 3; j++){
                c3[s[i][j]-1]++;
            }
        }
        for (int j = 0; j < 9; j++) {
            if (c3[j] != 1) {
                solved = "NO";
            }
        }
    } else if ((index) == 4){
        for (int i = 3; i < 6; i ++) {
            for (int j = 3; j < 6; j++){
                c3[s[i][j]-1]++;
            }
        }
        for (int j = 0; j < 9; j++) {
            if (c3[j] != 1) {
                solved = "NO";
            }
        }
    } else if ((index) == 5){
        for (int i = 3; i < 6; i ++) {
            for (int j = 6; j < 9; j++){
                c3[s[i][j]-1]++;
            }
        }
        for (int j = 0; j < 9; j++) {
            if (c3[j] != 1) {
                solved = "NO";
            }
        }
    } else if ((index) == 6){
        for (int i = 6; i < 9; i ++) {
            for (int j = 0; j < 3; j++){
                c3[s[i][j]-1]++;
            }
        }
        for (int j = 0; j < 9; j++) {
            if (c3[j] != 1) {
                solved = "NO";
            }
        }
    } else if ((index) == 7){
        for (int i = 6; i < 9; i ++) {
            for (int j = 3; j < 6; j++){
                c3[s[i][j]-1]++;
            }
        }
        for (int j = 0; j < 9; j++) {
            if (c3[j] != 1) {
                solved = "NO";
            }
        }
    } else if ((index) == 8){
        for (int i = 6; i < 9; i ++) {
            for (int j = 6; j < 9; j++){
                c3[s[i][j]-1]++;
            }
        }
        for (int j = 0; j < 9; j++) {
            if (c3[j] != 1) {
                solved = "NO";
            }
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
                // c2[s[j][i]-1]++;
            }
            for (int j = 0; j < 9; j++){
                if (c[j] != i+1) {
                    // || c2[j] != i+1
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
                for (int i = 0; i < 3; i ++) {
                    for (int j = 0; j < 3; j++){
                        c3[s[i][j]-1]++;
                    }
                }
                for (int j = 0; j < 9; j++) {
                    if (c3[j] != 1) {
                        sprintf(ptr, "%s", "NO");
                    }
                }
                for (int i = 0; i < 3; i ++) {
                    for (int j = 3; j < 6; j++){
                        c3[s[i][j]-1]++;
                    }
                }
                for (int j = 0; j < 9; j++) {
                    if (c3[j] != 2) {
                        sprintf(ptr, "%s", "NO");
                    }
                }
                for (int i = 0; i < 3; i ++) {
                    for (int j = 6; j < 9; j++){
                        c3[s[i][j]-1]++;
                    }
                }
                for (int j = 0; j < 9; j++) {
                    if (c3[j] != 3) {
                        sprintf(ptr, "%s", "NO");
                    }
                }
                for (int i = 3; i < 6; i ++) {
                    for (int j = 0; j < 3; j++){
                        c3[s[i][j]-1]++;
                    }
                }
                for (int j = 0; j < 9; j++) {
                    if (c3[j] != 4) {
                        sprintf(ptr, "%s", "NO");
                    }
                }
                for (int i = 3; i < 6; i ++) {
                    for (int j = 3; j < 6; j++){
                        c3[s[i][j]-1]++;
                    }
                }
                for (int j = 0; j < 9; j++) {
                    if (c3[j] != 5) {
                        sprintf(ptr, "%s", "NO");
                    }
                }
                for (int i = 3; i < 6; i ++) {
                    for (int j = 6; j < 9; j++){
                        c3[s[i][j]-1]++;
                    }
                }
                for (int j = 0; j < 9; j++) {
                    if (c3[j] != 6) {
                        sprintf(ptr, "%s", "NO");
                    }
                }
                for (int i = 6; i < 9; i ++) {
                    for (int j = 0; j < 3; j++){
                        c3[s[i][j]-1]++;
                    }
                }
                for (int j = 0; j < 9; j++) {
                    if (c3[j] != 7) {
                        sprintf(ptr, "%s", "NO");
                    }
                }
                for (int i = 6; i < 9; i ++) {
                    for (int j = 3; j < 6; j++){
                        c3[s[i][j]-1]++;
                    }
                }
                for (int j = 0; j < 9; j++) {
                    if (c3[j] != 8) {
                        sprintf(ptr, "%s", "NO");
                    }
                }
                for (int i = 6; i < 9; i ++) {
                    for (int j = 6; j < 9; j++){
                        c3[s[i][j]-1]++;
                    }
                }
                for (int j = 0; j < 9; j++) {
                    if (c3[j] != 9) {
                        sprintf(ptr, "%s", "NO");
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
        pthread_create(&threads[0], NULL, doWork, NULL);
        pthread_create(&threads[1], NULL, doWork1, NULL);
        pthread_create(&threads[2], NULL, doWork2, NULL);

        pthread_join(threads[0], NULL);
        pthread_join(threads[1], NULL);
        pthread_join(threads[2], NULL);

        time_t ft = time(NULL) - st;
        printf("SOLUTION: %s (%ld seconds)",solved, ft);
    }

    if(option == 2){
        pthread_t threads[27];
        for(int i = 0; i < 9; i++) {
            pthread_create(&threads[i], NULL, doWork3, &i);
            pthread_create(&threads[i+9], NULL, doWork4, &i);
            pthread_create(&threads[i+18], NULL, doWork5, &i);
        }
        for(int i = 0; i < 27; i++) {
            pthread_join(threads[i], NULL);
        }
        time_t ft = time(NULL) - st;
        printf("SOLUTION: %s (%ld seconds)",solved, ft);
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