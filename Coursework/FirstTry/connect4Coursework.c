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
    int numberOfRows;
    int numberOfColumns;
} game;

game start(int gamemode);
void instructions();
void history();
int winCheck();
int horizontalCheck();
int verticalCheck();
int diagonalCheck();
void printBoard();
void clearBoard();
void takeTurn();
void findPosition();
void replayGame(game curGame);
void undoMove(int columnNum);
void redoMove();
int chooseGameMode();
void gameSettings();

int num_cols = 7;
int num_rows = 7;
int b = 0;
char board[100][100];
int position [100] = { 0 };
int num_of_games = 0;

int main()
{
    char input[10];
    int option;
    int showMenu = 1;
    int gameMode;
    game games[20];

    while (showMenu)
    {
        system("cls");  
        printf("\n1. Start Game \n2. History \n3. Instructions \n4. Change Game Settings \n5. Exit Game\n");
        scanf("%s", input);

        //check if the user input is numeric
        if (isdigit(atoi(input)) == 0){
            option=atoi(input);
        }
        else option = 6;

        switch(option)
        {
            case 1:
                printf("\nYou've chosen to start a new game");
                gameMode = chooseGameMode();
                game gameCur = start(gameMode);
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
                printf("\nYou've chosen to change the game environment");
                gameSettings();

                break;

            case 5:
                printf("\nYou've chosen to exit the game");
                printf("\nThanks for playing :)");
                showMenu = 0;
                return 0;

            default:
                printf("\nPlease choose a valid option.");
                Sleep(3000);
                break;
        }
    }
    return 0;
}

void gameSettings(){
    printf("\nHow many rows would you like the game board to be?");
    scanf("%d", &num_rows);
    printf("\nHow many columns would you like the game board to be?");
    scanf("%d", &num_cols);
}

int chooseGameMode(){

    char input[10];
    int option;


    printf("\n      **Game Mode**");
    printf("\n1. Player Vs. Player  \n2. Player Vs. Easy AI \n3. Player Vs. Difficult AI");
    scanf("%s", input);

    //check if the user input is numeric
    if (isdigit(atoi(input)) == 0){
        option=atoi(input);
    }
    else option = 6;

    switch(option)
    {
        case 1: 
            return 1;
        break;

        case 2:
            return 2;
        break;

        case 3:
            return 3;
        break;
    }
    return 0;
}

game start(int gamemode){

    int order[50], last = 0;
    int redoArray[50], finalRedoElement = 0;
    game currentGame={"",NULL,0, num_rows, num_cols};

    char input[10];
    int column;
    int waitngforValidMove = 1;
    int win = 0;

    printf("\n      ***Welcome to Connect 4***");

    printBoard(board);

    while(last<num_cols*num_rows){
        if (last%2 == 0){
            while (waitngforValidMove){
                printf("\nPlayer1: Which column would you like to play in? (1-5)");

                scanf("%s", &input);
                column=atoi(input);

                if(strcmp(input,"undo") == 0){
                    //carry out the undo function

                    if (last > 0){
                    redoArray[finalRedoElement] = order[last-1];
                    finalRedoElement++;

                    board [position[order[last-1]-1]-1][order[last-1]-1] =' ';
                    position[order[last-1]-1]--;

                    last--;
                    waitngforValidMove=0;
                    }
                    else{
                        printf("\nYou must first make a move before you undo.");
                    }
                }
                else if (strcmp(input,"redo") == 0){
                    // carry out the redo function

                    if (finalRedoElement > 0){
                        finalRedoElement--;
                        board [position[redoArray[finalRedoElement]-1]][redoArray[finalRedoElement]-1] ='X';
                    
                        order[last] = redoArray[finalRedoElement];
                        position[order[last]-1] +=1;
                        last++;

                        waitngforValidMove=0;
                    }
                    else{
                        printf("\nThere are no more moves to redo.");
                    }

                }
                else if(column<=num_cols && column > 0) {
                    if (position[column-1] < num_rows){
                        board [position[column-1]][column-1] ='X';
                        order[last] = column;
                        last++;
                        position[column-1] +=1;

                        waitngforValidMove=0;
                    }
                    else{
                        printf("\nThere is no space left in this column. Try another.");
                    }

                }
                else {
                    printf("\nPlease enter a valid input:");
                }
            }
            waitngforValidMove = 1;
        }
        else if (gamemode == 1){
            while (waitngforValidMove){

                printf("\nPlayer2: Which column would you like to play in? (1-5)");

                scanf("%s", &input);
                column=atoi(input);

                if(strcmp(input,"undo") == 0){
                    //carry out the undo function

                    if (last > 0){
                    redoArray[finalRedoElement] = order[last-1];
                    finalRedoElement++;

                    board [position[order[last-1]-1]-1][order[last-1]-1] =' ';
                    position[order[last-1]-1]--;

                    last--;
                    waitngforValidMove=0;
                    }
                    else{
                        printf("\nYou must first make a move before you undo.");
                    }

                }
                else if (strcmp(input,"redo") == 0){
                    // carry out the redo function
                    if (finalRedoElement > 0){
                        finalRedoElement--;
                        board [position[redoArray[finalRedoElement]-1]][redoArray[finalRedoElement]-1] ='O';
                    
                        order[last] = redoArray[finalRedoElement];
                        position[order[last]-1] +=1;
                        last++;

                        waitngforValidMove=0;
                    }
                    else{
                        printf("\nThere are no more moves to redo.");
                    }
                }
                else if(column<=num_cols && column > 0) {
                    if (position[column-1] < num_rows){
                        board [position[column-1]][column-1] ='O';
                        order[last] = column;
                        last++;
                        position[column-1] +=1;

                        waitngforValidMove=0;
                    }
                    else{
                        printf("\nThere is no space left in this column. Try another.");
                    }
                }
                else {
                    printf("\nPlease enter a valid input:");
                }
            }
            waitngforValidMove = 1;
        }
        else if (gamemode == 2){
            printf("\nOne day there will be a simple AI implemented.");


        }
        else if (gamemode == 3){
            printf("\nOne day there will be a difficult AI implemented.");
            break;
        }
        else{
            printf("\n You did not choose a game mode to play.");
            break;
        }


        printBoard();
        if (last>6) win = winCheck();
        if (win) 
        {
            //save the game to history and then exit the game back to main menu.
            if (last%2 != 0) strcpy(currentGame.winner,"Player 1");
            else strcpy(currentGame.winner,"Player 2");
                                   
            for (int i = 0; i < 50; i++)
            {
                currentGame.moves[i] = order[i];
            }
            currentGame.numberOfMoves = last;
            currentGame.numberOfRows = num_rows;
            currentGame.numberOfColumns = num_cols;

            clearBoard();

            printf("DEBUG: \nwinner is: %s", currentGame.winner);
            Sleep(4000);

            return currentGame;
        }           
    }
    printf("You ran out of moves...");

    Sleep(3000);
    clearBoard();

    return currentGame;
}

void undoMove(int columnNum){
    printf("\nYou've tried to undo your previous move.");

    Sleep(3000);
}

void clearBoard(){
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++){
            board[i][j] = ' ';
        }
    }

    for (int i = 0; i < num_cols; i++)
    {
        position[i] = 0;
    }
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
}

void history(game games[50]){

    int option;

    printf("\n\n");
    printf("\n\n");
    printf("\nWelcome to the History Page:");

    printf("\nPrevious Matches:\n");
    for (int i = 0; i < num_of_games; i++){ //this will print all the previous matched dates, who won, moves taken.
        printf("\nWinner: %s \nNumber of moves: %d\nNumber of Rows: %d \nNumber of Columns: %d", games[i].winner, games[i].numberOfMoves, games[i].numberOfRows, games[i].numberOfColumns);
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

    num_rows = curGame.numberOfRows;
    num_cols = curGame.numberOfColumns;

    for (int i = 0; i < curGame.numberOfMoves; i++){
        if (i%2 == 0){
            // print X
            board [position[curGame.moves[i]-1]][curGame.moves[i]-1] ='X';
        }
        else{
            //print O
            board [position[curGame.moves[i]-1]][curGame.moves[i]-1] ='O';
        }
        position[curGame.moves[i]-1] +=1;

        printBoard();
        Sleep(200);
    }

    printf("The game replay has concluded");
    clearBoard();
    Sleep(6000);
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

    Sleep(10000);
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
Minimum Requirements:
    -
    -

Additional Marks:
    - allow the computer to play against you.(SEMI-IMPORTANT!)
    - option to play different game board sizes. (NOT AS IMPORTANT!)

*/