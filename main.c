#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <omp.h>
#include <pthread.h>

int main(int argc, char** argv) {
    char* solved = "YES";
    int option;
    int s[9][9];
    int c[9] = {0,0,0,0,0,0,0,0,0};
    int c2[9] = {0,0,0,0,0,0,0,0,0};
    int c3[9] = {0,0,0,0,0,0,0,0,0}; 
    int failFlag = 0;
    if (argc==2) {
        option = atoi(argv[1]);
    } else {
        printf("Error: single integer argument required.\n");
        return 0;
    }
    FILE *fp = fopen("input.txt","r");
    time_t st = time(NULL);
    printf("BOARD STATE IN input.txt:\n");
    for (int i = 0; i < 9; i++) {
        fscanf(fp,"%d %d %d %d %d %d %d %d %d",&s[i][0],&s[i][1],&s[i][2],&s[i][3],&s[i][4],&s[i][5],&s[i][6],&s[i][7],&s[i][8]);
        printf("%d %d %d %d %d %d %d %d %d\n",s[i][0],s[i][1],s[i][2],s[i][3],s[i][4],s[i][5],s[i][6],s[i][7],s[i][8]);
    }
    if (option == 1) {
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++) {
                c[s[i][j]-1]++;
                c2[s[j][i]-1]++;
            }
            for (int j = 0; j < 9; j++){
                if (c[j] != i+1 || c2[j] != i+1) {
                    solved = "NO";
                }
            }
        }
        // squares implementation
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
    } else if (option == 2) {

    } else if (option == 3) {

    }
    for (int i = 0;i<9;i++) {
        if (c[i] != 9 || c2[i] !=9) {
            solved = "NO";
        }
    }
    //printf("%d %d %d %d %d %d %d %d %d\n",c3[0],c3[1],c3[2],c3[3],c3[4],c3[5],c3[6],c3[7],c3[8]);
    // }
    // printf("that's a good solution\n");
    time_t ft = time(NULL) - st;
    printf("SOLUTION: %s (%ld seconds)",solved, ft);
    fclose(fp);

    //my attempt
}