#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define num_threads 27

char* solved = "YES";


int c[9] = {0,0,0,0,0,0,0,0,0};
int c2[9] = {0,0,0,0,0,0,0,0,0};
int c3[9] = {0,0,0,0,0,0,0,0,0}; 
int s[9][9];

void* doWork(void* param){
    int index = (*(int *)param);
    for (int j = 0; j < 9; j++) {
            c[s[index][j]-1]++;
        }
        for (int j = 0; j < 9; j++){
            if (c[j] != index+1) {
                solved = "NO";
            }
        }
}

void* doWork2(void* param){
    int index = (*(int *)param);
    for (int i = 0; i < 9; i++) {
        c2[s[i][index]-1]++;
    }
    for (int i = 0; i < 9; i++){
        if (c2[i] != (index)+1) {
            solved = "NO";
        }
    }
} 

void* doWork3(void* param){
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
            if (c3[j] != 2) {
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
            if (c3[j] != 3) {
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
            if (c3[j] != 4) {
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
            if (c3[j] != 5) {
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
            if (c3[j] != 6) {
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
            if (c3[j] != 7) {
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
            if (c3[j] != 8) {
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
            if (c3[j] != 9) {
                solved = "NO";
            }
        }
    }
}

int main(int argc, char **argv){
    pthread_t threads[num_threads];
    FILE *fp = fopen("input.txt","r");
    time_t st = time(NULL);
    int option = atoi(argv[1]);
    
    for (int i = 0; i < 9; i++) {
        fscanf(fp,"%d %d %d %d %d %d %d %d %d",&s[i][0],&s[i][1],&s[i][2],&s[i][3],&s[i][4],&s[i][5],&s[i][6],&s[i][7],&s[i][8]);
        printf("%d %d %d %d %d %d %d %d %d\n",s[i][0],s[i][1],s[i][2],s[i][3],s[i][4],s[i][5],s[i][6],s[i][7],s[i][8]);
    }


    if(option == 2){
        for(int i = 0; i < 9; i++) {
            pthread_create(&threads[i], NULL, doWork, &i);
            pthread_create(&threads[i+9], NULL, doWork2, &i);
            pthread_create(&threads[i+18], NULL, doWork3, &i);
        }
        for(int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }
    }

    printf("Here is the row array:");
    for(int i  = 0; i < 9; i++){
        printf(" %d ", c[i]);
    }
    printf("\n");

    printf("Here is the col array:");
    for(int i  = 0; i < 9; i++){
        printf(" %d ", c2[i]);
    }
    printf("\n");

    printf("Here is the square array:");
    for(int i  = 0; i < 9; i++){
        printf(" %d ", c3[i]);
    }
    printf("\n");



    time_t ft = time(NULL) - st;
    printf("SOLUTION: %s (%ld seconds)",solved, ft);
    fclose(fp);
    return 0;
}