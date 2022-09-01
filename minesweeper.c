#include <stdlib.h>
#include <stdio.h>
#include <time.h>



void shuffleBoard(int (*board)[10], int bombAmount, int height, int width);
void bombMaker(int (*board)[10], int r, int c, int height, int width);
void printBoard(int (*board)[10], int height, int width);
void showSolution(int (*board)[10], int height, int width);
int makeMove(int (*board)[10], int height, int width);
void shatter(int (*board)[10], int r, int c, int height, int width);
int winCheck(int (*board)[10], int height, int width);
void mainLoop(int (*board)[10], int height, int width);

void shuffleBoard(int (*board)[10], int bombAmount, int height, int width) 
{
    // 0=safe unknown  1=bomb unknown  2=safe known
    // -2=safe unknown  -1=bomb unknown  0-8=safe known
    // 0-8=safe unknown 9=bomb 10-18=safe known
    
    srand(time(NULL));
    
    for(int b=0; b<bombAmount; b++)
    {
        int r=rand()%height;
        int c=rand()%width;
        if(board[r][c]==9)
        {
            b-=1;
            continue;
        }
        bombMaker(board, r, c, height, width);
    }
}

void bombMaker(int (*board)[10], int r, int c, int height, int width)
{
    board[r][c]=9;
    for(int checkR=-1; checkR<=1; checkR++)
    {
        if((0<=checkR+r)&&(checkR+r<height))
        {
            for(int checkC=-1; checkC<=1; checkC++)
            {
                if((0<=checkC+c)&&(checkC+c<width))
                {
                    if(board[checkR+r][checkC+c]!=9)
                    {
                        board[checkR+r][checkC+c]++;
                    }
                }
            }
        }
    }
}

void printBoard(int (*board)[10], int height, int width) 
{
    printf("  ");
    for(int c=0; c<width; c++)
    {
        printf("%d ", c);
    }
    printf("\n");
    for(int r=0; r<height; r++)
    {
        printf("%d ", r);
        for(int c=0; c<width; c++)
        {
            if(board[r][c]==9) //bomb
            {
                // printf("💣");
                printf("🟩");
            }
            else if(9>board[r][c]) //known
            {
                printf("🟩");
            }
            else if(board[r][c]==10) //known, 0 neighbors
            {
                printf("🟦");
            }
            else
            {
                switch(board[r][c]-10)
                {
                    case 1: printf("1️⃣ "); break;
                    case 2: printf("2️⃣ "); break;
                    case 3: printf("3️⃣ "); break;
                    case 4: printf("4️⃣ "); break;
                    case 5: printf("5️⃣ "); break;
                    case 6: printf("6️⃣ "); break;
                    case 7: printf("7️⃣ "); break;
                    case 8: printf("8️⃣ "); break;
                }
                // printf("%d ", board[r][c]-10);
            }
        }
        printf("\n");
    }
}

void showSolution(int (*board)[10], int height, int width) 
{
    printf("  ");
    for(int c=0; c<width; c++)
    {
        printf("%d ", c);
    }
    printf("\n");
    for(int r=0; r<height; r++)
    {
        printf("%d ", r);
        for(int c=0; c<width; c++)
        {
            if(board[r][c]==9) //bomb
            {
                printf("💣");
                // printf("🟩");
            }
            else if(9>board[r][c]) //known
            {
                printf("🟩");
            }
            else if(board[r][c]==10) //known, 0 neighbors
            {
                printf("🟦");
            }
            else
            {
                switch(board[r][c]-10)
                {
                    case 1: printf("1️⃣ "); break;
                    case 2: printf("2️⃣ "); break;
                    case 3: printf("3️⃣ "); break;
                    case 4: printf("4️⃣ "); break;
                    case 5: printf("5️⃣ "); break;
                    case 6: printf("6️⃣ "); break;
                    case 7: printf("7️⃣ "); break;
                    case 8: printf("8️⃣ "); break;
                }
                // printf("%d ", board[r][c]-10);
            }
        }
        printf("\n");
    }
}

int makeMove(int (*board)[10], int height, int width) 
{
    // get move
    int r=-1;
    int c=-1;
    while(1)
    {
        printf("Your move (r, c): ");
        scanf("%d %d", &r, &c);
        if(((0>r)||(r>height-1))||((0>c)||(c>width-1)))
        {
            printf("Error: out of range.\n");
            continue;
        }
        if(9<board[r][c]) //known
        {
            printf("That spot is already known.\n");
            continue;
        }
        break;
    }
    if(board[r][c]==9) //bomb
    {
        return 1;
    }
    if(board[r][c]==0) //unknown 0
    {
        shatter(board, r, c, height, width);
        return 0;
    }
    board[r][c]+=10; //unknown
    return 0;
}

void shatter(int (*board)[10], int r, int c, int height, int width) //assume board[r][c]=10
{
    board[r][c]=10;
    for(int checkR=-1; checkR<=1; checkR++)
    {
        if((0<=checkR+r)&&(checkR+r<height))
        {
            for(int checkC=-1; checkC<=1; checkC++)
            {
                if((0<=checkC+c)&&(checkC+c<width))
                {
                    if(board[checkR+r][checkC+c]==0)
                    {
                        printf("%d, %d\n", checkR+r, checkC+c);
                        shatter(board, checkR+r, checkC+c, height, width);
                    }
                    if(board[checkR+r][checkC+c]<9)
                    {
                        board[checkR+r][checkC+c]+=10;
                    }
                }
            }
        }
    }
}

int winCheck(int (*board)[10], int height, int width) 
{
    for(int r=0; r<height; r++)
    {
        for(int c=0; c<width; c++)
        {
            if(board[r][c]<9)
            {
                return 0;
            }
        }
    }
    return 1;
}

void mainLoop(int (*board)[10], int height, int width) 
{
    if(winCheck(board, height, width)==1)
    {
        showSolution(board, height, width);
        printf("Empty Board!"); 
        return;
    }

    while(1)
    {
        printBoard(board, height, width);
        if(makeMove(board, height, width))
        {
            showSolution(board, height, width);
            printf("You Lose!");
            break;
        }
        if(winCheck(board, height, width))
        {
            showSolution(board, height, width);
            printf("You Win!");
            break;
        }
    }
}

int main()
{
    int height=5, width=10;
    int board[10][10]={0, };
    shuffleBoard(board, 10, height, width);
    mainLoop(board, height, width);
    return 0;
}