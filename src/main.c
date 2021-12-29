#include "libs/param.h"

void printMouse(MEVENT event, int n, int (*matrix)[n]){
    int x = event.x;
    if (x % 2)
        --x;
    move(event.y, x);
    if (inch()  != 288){
        printw("  ");
        x /= 2;
        matrix[event.y][x]++;
    }
}

int findNeighbors(int n, int (*matrix)[n], int row, int col){
    int count  = 0;
    assert(row && col && col != n);
    for (int i = row-1; i <= row+1; i++)
        for (int  j = col-1; j <= col+1; j++){
            if (i == row && j == col)
                continue;
            if (matrix[i][j])
                count++;
        }
    return count;
}

void drawBoard(int n, int (*matrix)[n], int rows){
    erase();
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < n; j++){
            if (matrix[i][j]){
                int x = j*2;
                int y = i;
                move(y,x);
                printw("  ");
            }
        }

}

void initializeNCurses(){
    initscr();
    raw();		
    cbreak();
    noecho();		
	keypad(stdscr, TRUE);	
    halfdelay(0);
    start_color();
    curs_set(0);
    init_pair(1, COLOR_BLUE, COLOR_WHITE);;
    mousemask(BUTTON1_CLICKED, NULL);
}

int main(void){
    initializeNCurses();
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    max_x /= 2;
    int matrix[max_y][max_x];
    int matrixTemp[max_y][max_x];
    memset(matrix, 0, sizeof(matrix));
    attrset(COLOR_PAIR(1));
    int char_input;
    MEVENT event;
    while(true){
        char_input = getch();
        if(char_input == KEY_MOUSE)
            if(getmouse(&event) == OK)
                printMouse(event, max_x, matrix);
        if (char_input == 'r'){
            memcpy(matrixTemp,matrix, sizeof(matrix));
            #ifdef DEBUG
                FILE *arqqq = fopen("matrixA.txt", "w");
                for (int i  = 0; i < max_y;  i++){
                    for (int j = 0; j < max_x; j++)
                        fprintf(arqqq,"%d ", matrix[i][j]);
                    fprintf(arqqq,"\n");
                }
                fclose(arqqq);
            #endif 
            #ifdef DEBUG
                FILE *arq =  fopen("matrixTemp.txt", "w");
                for (int i  = 0; i < max_y;  i++){
                    for (int j = 0; j < max_x; j++)
                        fprintf(arq,"%d ", matrixTemp[i][j]);
                    fprintf(arq, "\n");
                }
                fclose(arq);
            #endif
            int x = 1, y = 1;
            for (; y < max_y-1;y++)
                for (x = 1; x < max_x-1;x++){
                    int neighbors = findNeighbors(max_x, matrix, y,x);
                    if (neighbors < 2 || neighbors > 3)
                        matrixTemp[y][x] = 0;
                    if (neighbors == 3)
                        matrixTemp[y][x] = 1;
                }
            memcpy(matrix, matrixTemp, sizeof(matrixTemp));
            #ifdef DEBUG
                FILE *arqq = fopen("matrix.txt", "w");
                for (int i  = 0; i < max_y;  i++){
                    for (int j = 0; j < max_x; j++)
                        fprintf(arqq,"%d ", matrix[i][j]);
                    fprintf(arqq,"\n");
                }
                fclose(arqq);
            #endif  
            drawBoard(max_x, matrix, max_y);   
        }
    }
    endwin();
    return 0;
}