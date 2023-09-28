#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <omp.h>
#include <pthread.h>

int main() {
    int s[9][9];
    int c[9] = {0,0,0,0,0,0,0,0,0};
    int failFlag = 0;
    FILE *fp = fopen("input.txt","r");
    for (int i = 0; i < 9; i++) {
        fscanf(fp,"%d %d %d %d %d %d %d %d %d",&s[i][0],&s[i][1],&s[i][2],&s[i][3],&s[i][4],&s[i][5],&s[i][6],&s[i][7],&s[i][8]);
        printf("%d %d %d %d %d %d %d %d %d\n",s[i][0],s[i][1],s[i][2],s[i][3],s[i][4],s[i][5],s[i][6],s[i][7],s[i][8]);
        for (int j = 0; j < 9; j++) {
            c[s[i][j]-1] = c[s[i][j]-1]+1;
            if (c[s[i][j]-1] > i+1) {
                failFlag = 1;
                break;
            }
        }
        if (failFlag) {
            printf("no bueno\n");
            return 0;
        }
        printf("%d %d %d %d %d %d %d %d %d\n",c[0],c[1],c[2],c[3],c[4],c[5],c[6],c[7],c[8]);
        printf("\n");
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            c[s[j][i]-1] = c[s[j][i]-1]+1;
            if (c[s[j][i]-1] > i+1) {
                failFlag = 1;
                break;
            }
        }
    }
    printf("that's a good solution\n");
}
