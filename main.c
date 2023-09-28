#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <omp.h>
#include <pthread.h>

void main() {
    int s[9][9];
    FILE *fp = fopen("input.txt","r");
    for (int i = 0; i < 9; i++) {
        fscanf(fp,"%d %d %d %d %d %d %d %d %d",&s[i][0],&s[i][1],&s[i][2],&s[i][3],&s[i][4],&s[i][5],&s[i][6],&s[i][7],&s[i][8]);
        printf("%d %d %d %d %d %d %d %d %d\n",s[i][0],s[i][1],s[i][2],s[i][3],s[i][4],s[i][5],s[i][6],s[i][7],s[i][8]);
        // for (int j = 0; j < 9; j++) {
        //     solution[i][j] = getw()
        // }
    }
}