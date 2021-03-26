#include<stdio.h>
#include<string.h>
#include<string.h>
#include<time.h>
#include<dos.h>
#include <windows.h>
#include <stdbool.h>

typedef struct {
    char winner[10];
    int moves[50];
    int numberOfMoves;
} game;

//stack for order of play
int playOrder[100], last = -1;

int stack[8], top = -1;

int board_rows = 7;
int board_columns = 5;

game start();
void instructions();
void history();
int winCheck();
int horizontalCheck();
int verticalCheck();
int diagonalCheck();
void printBoard();
void takeTurn();
void pushOrder();
void findPosition();
void replayGame(game curGame);

int num_cols = 5;
int num_rows = 7;
int b = 0;
char board[100][100];
int position [5] = { 0 };
int num_of_games = 0;

int main()
{
    int option;
    int flag =1;
    game games[20];


    while (flag = 1)
    {
        system("cls");  
        printf("\n1. Start Game \n2. History \n3. Instructions \n4. Exit Game\n");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                printf("\nYou've chosen to start a new game");
                game gameCur = start();
                games[num_of_games] = gameCur;
                num_of_games++;
                break;

            case 2:
                printf("\nYou've chosen to view the previous games");
                history(games);
                break;
            
            case 3:
                printf("\nYou've chosen to view the instructions");
                instructions();
                break;
            
            case 4:
                printf("\nYou've chosen to exit the game");
                printf("\nThanks for playing :)");
                flag = 0;
                return 0;

            default:
                printf("\nPlease choose a valid option.");
                Sleep(3000);
                break;
        }
    }
    return 0;
}

game start(){

    int order[50] = {0};
    int pos = 0;
    game currentGame={"",NULL,0};

    char input[10];
    int column;
    int turn = 0;
    int flag2 = 0;
    int win;

    printf("\n      ***Welcome to Connect 4***");

    printBoard(board);

    for(int i = 0; i < num_cols*num_rows;i++ ){
        //pushOrder(column);

        if (turn%2 == 0){
            while (flag2 == 0){

                printf("\nPlayer1: Which column would you like to play in? (1-5)");

                scanf("%s", &input);
                column=atoi(input);

                if(strcmp(input,"undo") == 0){
                    //carry out the undo function
                    flag2=1;
                }
                else if (strcmp(input,"redo") == 0){
                    // carry out the redo function
                    flag2=1;
                }
                else if(column>num_cols || column < 0) {
                    flag2=1;
                }
                else {
                    printf("\nPlease enter a valid input:");
                }
            }
            flag2 = 0;
            board [position[column-1]][column-1] ='X';
        }
        else{
            while (flag2 == 0){

                printf("\nPlayer2: Which column would you like to play in? (1-5)");

                scanf("%s", &input);
                column=atoi(input);

                if(strcmp(input,"undo") == 0){
                    //carry out the undo function
                    flag2=1;
                }
                else if (strcmp(input,"redo") == 0){
                    // carry out the redo function
                    flag2=1;
                }
                else if(column>num_cols || column < 0) {
                    flag2=1;
                }
                else {
                    printf("\nPlease enter a valid input:");
                }
            }
            flag2 = 0;
            board [position[column-1]][column-1] ='O';
        }
        order[pos] = column;
        pos++;

        turn++;
        position[column-1] +=1;

        printBoard();
        win = winCheck();
        if (win == 1) 
        {
            //save the game to history and then exit the game back to main menu.
            if (turn%2 != 0) strcpy(currentGame.winner,"Player 1");
            else strcpy(currentGame.winner,"Player 2");
                                   
            for (int i = 0; i < 50; i++)
            {
                currentGame.moves[i] = order[i];
            }
            currentGame.numberOfMoves = turn;

            for (int i = 0; i < 5; i++)
            {
                position[i] = 0;
            }

            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 100; j++){
                    board[i][j] = ' ';
                }
            }

            printf("DEBUG: \nwinner is: %s", currentGame.winner);
            Sleep(4000);

            return currentGame;
        }           
    }
    printf("You ran out of moves...");

    Sleep(3000);

    return currentGame;
}

void printBoard(){
    
    int row,col,a,c;
    if(b==0){                               
        for(a=0;a<num_rows;a++){
                for(c=0;c<num_cols;c++)
                board[a][c]=' ';
        }
    }
    b++;

    system("cls");                          
    for(row=num_rows-1; row>=0; row--)
    {        
        for(col=0; col<num_cols; col++)
        {
            printf("| %c ",board[row][col]);
        }
        printf("|\n");
        for(a=0; a<num_cols; a++) printf("____");
        printf("\n");
    }


    for(a=0; a<num_cols; a++)printf("%*d",4,a+1);
    printf("\n");

    Sleep(3000);
}

void pushOrder(int column){
    playOrder[last] = column;
    last++;
}

void history(game games[50]){

    int option;

    printf("\n\n");
    printf("\n\n");
    printf("\nWelcome to the History Page:");

    printf("\nPrevious Matches:\n");
    for (int i = 0; i < num_of_games; i++){ //this will print all the previous matched dates, who won, moves taken.
        printf("\nWinner: %s \nNumber of moves: %d", games[i].winner, games[i].numberOfMoves);
        for (int j = 0; j < games[i].numberOfMoves; j++)
        {
            printf("\n column: %d",games[i].moves[j]);
        }
    } 
  
    printf("\n\nWhich game would you like to review?");
    scanf("%d", &option);

    replayGame(games[option-1]);

}

void replayGame(game curGame){

}

void instructions(){
    printf("\n\n");
    printf("\nWelcome to the Instructions Page:");
    printf("\nChoose a column to pace your token");
    printf("\nPress U to undo a previous move");
    printf("\nPress R to redo a move");
    printf("\nTo win you must have 4 tokens in a row");
    printf("\nPrevious games can be viewed by pressing '2' in the Main Menu");
    printf("\n\n");
}

int winCheck(){
    int win = 0;

    if (horizontalCheck() == 1){
        printf("You Won with a horizontal 4\n");
        win = 1;
    }
    else if(verticalCheck() == 1){
        printf("You Won with a vertical 4\n");
        win = 1;
    } 
    else if(rightDiagonalCheck() == 1){
        printf("You Won with a right diagonal 4\n");
        win = 1;
    }
    else if(leftDiagonalCheck() == 1){
        printf("You Won with a left diagonal 4\n");
        win = 1;
    }
    return win;
}

int horizontalCheck(){
    //Function to check horizontal win 
    int win = 0;

    for (int i = num_rows-1; i>=0;i--){
        for (int j = 0; j<num_cols-3; j++){
            
            win = fourInaRow(board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]);
            if (win == 1) return win;
        }
    }
    return win;
}

int verticalCheck(){
    //Function to check vertical win 
    int win = 0;

    for (int i = 0; i<num_cols; i++){
        for (int j = num_rows-1; j>=3;j--){
            
            win = fourInaRow(board[j][i],board[j-1][i],board[j-2][i],board[j-3][i]);
            if (win == 1) return win;
        }
    }
    return win;
}

int rightDiagonalCheck(){
    //Function to check diagonal win
    int win = 0;

    for (int i = 0; i<num_cols-3; i++){
        for (int j = num_rows-1; j>=3;j--){
            
            win = fourInaRow(board[j][i],board[j-1][i+1],board[j-2][i+2],board[j-3][i+3]);
            if (win == 1) return win;
        }
    }
    return win; 
}

int leftDiagonalCheck(){
    //Function to check diagonal win
    int win = 0;

    for (int i = 3; i<num_cols; i++){
        for (int j = num_rows-1; j>=3;j--){
            
            win = fourInaRow(board[j][i],board[j-1][i-1],board[j-2][i-2],board[j-3][i-3]);
            if (win == 1) return win;
        }
    }
    return win; 
}

int fourInaRow(char first, char second, char third, char fourth){

    if(first == second && first == third && first == fourth && first != ' ')
    {
        printf("\nGG Boys\n");
        return 1;
    }
    else 
        return 0;
}

/*

    ::::TO DO LIST::::
    
- make the undo function.
- make the redo function.
- finish the replay game function. 
- allow the computer to play against you.
- option to play different game board sizes.

*/