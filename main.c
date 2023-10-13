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


void* checkRows(void* param){ //check all rows
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
    pthread_exit(0);
}

void* checkCols(void* param){ //check all columns
    int c[9] = {0}; 
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            c[s[j][i]-1]++;
        }
        for (int j = 0; j < 9; j++){
            if (c[j] != i+1) {
                solved = "NO";
            }
        }
    }
    pthread_exit(0);
}

void* checkSquares(void* param){ //check all squares
    int c[9] = {0}; 
    gridCoord* sq = (gridCoord*) param;
    for(int i = 0; i < 9; i++){
        int startX = sq[i].x;
        int startY = sq[i].y;
        for(int x = startX; x < startX+3; x++){
            for(int y = startY; y < startY+3; y++){
                c[s[x][y]-1]++;
            }
        }

        for (int j = 0; j < 9; j++) {
            if (c[j] != i+1) {
                solved = "NO";
            }
        }
    }
    pthread_exit(0);
}

void* checkSingleRow(void* param){ //check a single row.  param is an integer pointer to the index of the row to check
    int c[9] = {0};
    int row = (*(int *)param);
    for (int i = 0; i < 9; i++) {
        c[s[row][i]-1]++;
    }
    for (int i = 0; i < 9; i++){
        if (c[i] != 1) {
            solved = "NO";
        }
    }
    pthread_exit(0);
}

void* checkSingleCol(void* param){ //check a single column.  param is an integer pointer to the index of the column to check
    int c[9] = {0};
    int col = (*(int *)param);
    for (int i = 0; i < 9; i++) {
        c[s[i][col]-1]++;
    }
    for (int i = 0; i < 9; i++){
        if (c[i] != 1) {
            solved = "NO";
        }
    }
    pthread_exit(0);
} 

void* checkSingleSquare(void* param){ //checks a single square.  param is a pointer to a gridCoord, which contains row and col index of the first number in the square
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

void multiProcessCheck(){ //check all rows, columns, and squares, with a process for each category
    int SIZE = 4096;
    char* name = "solution?";
    char* ptr = "";
    int shm_fd;
    int c[9] = {0};
    pid_t pid1 = fork();
    if(pid1 == 0){
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
        exit(0);
    }
    pid_t pid2 = fork();
    if(pid2 == 0){
        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
        ftruncate(shm_fd, SIZE);
        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++) {
                c[s[j][i]-1]++;
            }
            for (int j = 0; j < 9; j++){
                if (c[j] != i+1) {
                    sprintf(ptr, "%s", "NO");
                }
            }
        }
        exit(0);
    }
    pid_t pid3 = fork();
    if(pid3 == 0){
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
                    c[s[x][y]-1]++;
                }
            }

            for (int j = 0; j < 9; j++) {
                if (c[j] != i+1) {
                    sprintf(ptr, "%s", "NO");
                }
            }
        }
        exit(0);
    } 
    
    if(pid1 > 0 && pid2 > 0 && pid3 > 0){
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        waitpid(pid3, NULL, 0);
        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
        ftruncate(shm_fd, SIZE);
        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if(strlen(ptr) != 0){
            solved = ptr;
        }
        shm_unlink(name);
    } 
}

int main(int argc, char **argv){
    FILE *fp = fopen("input.txt","r");
    time_t st = clock();
    time_t msPerS = CLOCKS_PER_SEC/100000;
    int option = atoi(argv[1]);
    for (int i = 0; i < 9; i++) {
        fscanf(fp,"%d %d %d %d %d %d %d %d %d",&s[i][0],&s[i][1],&s[i][2],&s[i][3],&s[i][4],&s[i][5],&s[i][6],&s[i][7],&s[i][8]);
        printf("%d %d %d %d %d %d %d %d %d\n",s[i][0],s[i][1],s[i][2],s[i][3],s[i][4],s[i][5],s[i][6],s[i][7],s[i][8]);
    }

    if(option == 1){
        // for(int att = 0; att < 10; att++){
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
            pthread_create(&threads[0], NULL, checkRows, NULL);
            pthread_create(&threads[1], NULL, checkCols, NULL);
            pthread_create(&threads[2], NULL, checkSquares, sqPos);

            pthread_join(threads[0], NULL);
            pthread_join(threads[1], NULL);
            pthread_join(threads[2], NULL);
        // }    
        // time_t ft = clock() - st;
        // printf("SOLUTION: %s (%ld ns)\n",solved, ft/msPerS);
    }

    if(option == 2){
        // for(int att = 0; att < 10; att++){
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
            int params[9] = {0,1,2,3,4,5,6,7,8};
            for(int i = 0; i < 9; i++) {
                pthread_create(&threads[i], NULL, checkSingleRow, &params[i]);
                pthread_create(&threads[i+9], NULL, checkSingleCol, &params[i]);
                pthread_create(&threads[i+18], NULL, checkSingleSquare, &sqPos[i]);
            }
            for(int i = 0; i < 27; i++) {
                pthread_join(threads[i], NULL);
            }
        // }
        
        // if(att % 1000 == 0){
            //     printf("Here is the index:%d, (%ld ms)\n", att, (clock() - st));
            // }
        // time_t ft = clock() - st;
        // printf("SOLUTION: %s (%ld ns)\n",solved, ft/msPerS);
    }

    if(option == 3){
        // for(int att = 0; att < 10; att++){
            multiProcessCheck();
        // }
        
        // time_t ft = clock() - st;
        // printf("SOLUTION: %s (%ld ns)\n",solved, ft/msPerS);
    }
    
    fclose(fp);
    time_t ft = clock() - st;
    printf("SOLUTION: %s (%ld ns)\n",solved, ft/msPerS);
    
    return 0;
}