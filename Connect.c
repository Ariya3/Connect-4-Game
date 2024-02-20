#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include "slist.c"
#include "slist.h"

#define NUM_ROWS 6
#define NUM_COLS 7
char board[NUM_ROWS][NUM_COLS];

typedef enum {F = 0,T = 1} Bool;

//linked list
slist* movesList;

//gets column num from player
int GetColumn(char player){
    int column;
    
    printf("%s to play. Pick a column (1-7):", player=='R' ? "Red":"Yellow");
    int num_values = scanf("%d", &column);
    while(getchar() != '\n'); // clear buffer of newline

    // re-prompt if player enters invalid guess
    while (num_values != 1 || column < 1 || column > NUM_COLS){
        printf("Make sure the column is between 1 and 7: \n");
        num_values = scanf("%d", &column);
        while(getchar() != '\n');
    }
    return column-1;
}

//checks if theres 4 colors in a row for winner
char CheckWinner(char board[][NUM_COLS]){
    // check rows for four sequential tokens
    for (int r = 0; r < NUM_ROWS; r++){
        char prev = board[r][0];
        int num = 1;
        for (int c = 1; c < NUM_COLS; c++){
            if (board[r][c] == prev){
                num++;
            } else {
                prev = board[r][c]; num = 1;
            }

            if (num == 4 && prev != ' '){
                return prev;
            }
        }
    }

    // check columns for four sequential tokens
    for (int c = 0; c < NUM_COLS; c++){
        char prev = board[0][c];
        int num = 1;
        for (int r = 1; r < NUM_ROWS; r++){
            if (board[r][c] == prev){
                num++;
            } else {
                prev = board[r][c]; num = 1;
            }

            if (num == 4 && prev != ' '){
                return prev;
            }
        }
    }
    return ' ';
}


//checks if board is full
Bool CheckBoardFull(char board[][NUM_COLS]){
    for (int c = 0; c < NUM_COLS; c++){
        if (board[NUM_ROWS-1][c] == ' '){
            return F;
        }
        return T;
    }
}

//returns the next available row for a given column
int GetEmptyRow(char board[][NUM_COLS], int col){
    int row = 0;
    while (row < NUM_ROWS && board[row][col] != ' '){
        row++;
    }
    return row;
}


//prints the current board
void PrintBoard(char board[][NUM_COLS]){
    for (int r = NUM_ROWS-1; r >= 0; r--){
        for (int c = 0; c < NUM_COLS; c++){
            printf("|%c", board[r][c]);
        }
        printf("|\n");
    }
}


//records the move (column and player) in the linked list
void RecordMove(int col, char player){
    //create a string of the move like R2
    char move[3];
    sprintf(move, "%c%d", player, col + 1);

    //put move into linked list
    insertTail(movesList, move);
}


//replays the game by showing the moves from the linked list
void ReplayGame(){
    struct node* current = movesList -> head;

    while(current != NULL){
        char move[3];
        strcpy(move, current -> data);
        int col = move[1] - '0' -1; //extract the colum from the move
        char player = move[0]; //extract the player from the move

        int row = GetEmptyRow(board, col);
        board[row][col] = player;
        PrintBoard(board);

        char winner = CheckWinner(board);
        if(winner != ' '){
            printf("You win, %s!\n", winner == 'R' ? "Red" : "Yellow");
            break; //end replay if winner found
        } else if (CheckBoardFull(board)){
            printf("It's a tie!\n");
            break; //end replay if tie
        }

        //delay so doesn't go so fast durring output
        Sleep(1);

        current = current -> next;
    }
}

//starts the actual game of connect 4
void PlayConnectFour(){
// create an empty board
    char board[NUM_ROWS][NUM_COLS];
    for (int r = 0; r < NUM_ROWS; r++){
        for (int c = 0; c < NUM_COLS; c++){
            board[r][c] = ' ';
        }
    }
    
    PrintBoard(board);
    char player = 'R';
    Bool game_over = F;
    
    while (!game_over){
        int col = GetColumn(player);
        int row = GetEmptyRow(board, col);
       
        while (row > 5){
            printf("that column is full, pick another...\n");
            col = GetColumn(player);
            row = GetEmptyRow(board, col);
        }

        board[row][col] = player;
        RecordMove(col, player);
        PrintBoard(board);

        char winner = CheckWinner(board);
        if (winner != ' '){
            printf("You win, %s!\n", winner=='R' ? "Red":"Yellow");
            game_over = T;
        } else if (CheckBoardFull(board)){
            printf("It's a tie!\n");
            game_over = T;
        }
        
        player = (player == 'R' ? 'Y' : 'R');
    }
    printf("Good game!\n");
}


//frees memory used by the linked list
void FreeMemory(){
    freeList(movesList);
}

//main method
int main(){
    printf("Welcome! Press 'q' to quit, 'p' to play, or 'r' to replay:\n");
    
    char c;
    Bool done = F;
    
    //starts the loop for the game
    while(!done){
        printf("Press 'q' to quit, 'p' to play, or 'r' to replay:\n");
        scanf(" %c", &c);
        
        switch(c){
            case 'q':
                done = T;
                printf("Bye Bye!\n");
                break;
            case 'p':
                movesList = createList();
                PlayConnectFour();
                FreeMemory();
                break;
            case 'r':
                if(movesList != NULL){
                    ReplayGame();
                } else {
                    printf("No moves to replay\n");
                }
                break;
            default:
                printf("Invalid input, please enter 'p', 'r', or 'q'\n");
        }
    }
    return 0;
}