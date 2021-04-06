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
int rightdiagonalCheck();
int leftdiagonalCheck();
void printBoard();
void clearBoard();
void takeTurn();
void findPosition();
void replayGame(game curGame);
void redoMove();
int chooseGameMode();
void gameSettings();
void recordMove(int *order, int *last, int *column, int *finalRedoElement,int *waitingforValidMove);
void undoMove(int *order, int *last, int *redoArray, int *finalRedoElement, int *waitingforValidMove);
void redoMove(int *order, int *last, int *redoArray, int *finalRedoElement, int *waitingforValidMove);
void loadState();
void saveState();
int isNumeric(char value[10]);

int num_cols = 7;
int num_rows = 7;
int b = 0;
char board[100][100];
int position [100] = { 0 };
int num_of_games = 0;
game games[50];


int main()
{
    char userInput[10];
    int option;
    int showMenu = 1;
    int gameMode;
    loadState();

    while (showMenu)
    {
        system("cls");  
        printf("\n1. Start Game \n2. History \n3. Instructions \n4. Change Game Settings \n5. Save Games \n6. Exit Game\n");
        scanf("%s", userInput);

        //check if the user input is numeric
        if (isNumeric(userInput)) {
            option=atoi(userInput);
        }
        else { 
            option = 6;
        }
        switch(option) {
            case 1:
                gameMode = chooseGameMode();
                game gameCur = start(gameMode);
                games[num_of_games] = gameCur;
                num_of_games++;
                break;

            case 2:
                history();
                break;
            
            case 3:
                instructions();
                break;
            
            case 4:
                gameSettings();
                break;

            case 5:
                printf("\nSaving the game History");
                saveState();
                Sleep(1000);
                break;

            case 6:
                printf("\nYou've chosen to exit the game");
                printf("\nThanks for playing :)");
                printf("\nPress any key to exit...\n");
                getch();  
                showMenu = 0;
                return 0;

            default:
                printf("\nPlease choose a valid option.");
                printf("\nPress any key to exit...\n");
                getch();
                break;
        }
    }
    return 0;
}

void gameSettings(){
    char userInput[10];
    system("cls");  

    do{
        printf("\nHow many rows would you like the game board to be?");
        scanf("%s", userInput);

        if (isNumeric(userInput)) {
            num_rows = atoi(userInput);
        } else {
            printf("\nEnter a number");
        }
    }
    while (!isNumeric(userInput));

    do{
        printf("\nHow many columns would you like the game board to be?");
        scanf("%s", userInput);

        if (isNumeric(userInput)) {
            num_cols = atoi(userInput);
        } else {
            printf("\nEnter a number");
        }       
    }
    while (!isNumeric(userInput));
}

int isNumeric(char stringInput[10]){
    for (int i = 0; stringInput[i] != '\0'; i++){
        if (!isdigit(stringInput[i])){
            return 0;
        }
    }
    return stringInput[0] != '\0';
}

int chooseGameMode(){
    char input[10];
    int option;

    do {
        system("cls");  
        printf("\n      **Game Mode**");
        printf("\n1. Player Vs. Player  \n2. Player Vs. Easy AI \n3. Player Vs. Difficult AI");
        scanf("%s", input);
        option = atoi(input);
    }
    while(!isNumeric(input) || option > 3 || option < 1);

    return option;
}

game start(int gamemode){
    int order[50], last = 0;
    int redoArray[50], finalRedoElement = 0;
    game currentGame={"",0,0, num_rows, num_cols};

    char input[10];
    int column;
    int waitingforValidMove = 1;
    int win = 0;

    printf("\n      ***Welcome to Connect 4***");
    printBoard(board);

    while(last<num_cols*num_rows) {
        if (last%2 == 0) {
            while (waitingforValidMove) {
                printf("\nPlayer1: Which column would you like to play in? (1-5)");

                scanf("%s", &input);
                column=atoi(input);

                if(strcmp(input,"undo") == 0) {
                    //carry out the undo function
                    undoMove(order, &last, redoArray, &finalRedoElement, &waitingforValidMove);
                } 
                else if (strcmp(input,"redo") == 0) {
                    // carry out the redo function
                    redoMove(order, &last, redoArray, &finalRedoElement, &waitingforValidMove);
                } 
                else if(column<=num_cols && column > 0) {
                    recordMove(order, &last, &column, &finalRedoElement,&waitingforValidMove);
                } 
                else {
                    printf("\nPlease enter a valid input:");
                }
            }
            waitingforValidMove = 1;
        }
        else if (gamemode == 1){
            //This will be used for player 2 when they are a real person.
            while (waitingforValidMove){

                printf("\nPlayer2: Which column would you like to play in? (1-5)");
                scanf("%s", &input);
                column=atoi(input);

                if(strcmp(input,"undo") == 0){
                    //carry out the undo function
                    undoMove(order, &last, redoArray, &finalRedoElement, &waitingforValidMove);
                }
                else if (strcmp(input,"redo") == 0){
                    // carry out the redo function
                    redoMove(order, &last, redoArray, &finalRedoElement, &waitingforValidMove);
                }
                else if(column<=num_cols && column > 0) {
                    //record a move
                    recordMove(order, &last, &column, &finalRedoElement,&waitingforValidMove);
                }
                else {
                    printf("\nPlease enter a valid input:");
                }
            }
            waitingforValidMove = 1;
        }
        else if (gamemode == 2){
            //This is the simple AI as player 2.

            //Random number within 1 & column number is generated
            column = rand() % num_cols;

            recordMove(order, &last, &column, &finalRedoElement,&waitingforValidMove);
        }
        else if (gamemode == 3){
            printf("\nOne day there will be a difficult AI implemented.");
            break;
        }
        
        printBoard();
        if (last > 6) win = winCheck();
        if (win) {
            //save the game to history and then exit the game back to main menu.
            if (last%2 != 0) strcpy(currentGame.winner,"Player1");
            else strcpy(currentGame.winner,"Player2");
                                    
            for (int i = 0; i < 50; i++) {
                currentGame.moves[i] = order[i];
            }
            currentGame.numberOfMoves = last;
            currentGame.numberOfRows = num_rows;
            currentGame.numberOfColumns = num_cols;

            clearBoard();

            printf("\nWinner is: %s", currentGame.winner);
            printf("\nPress any key to exit...\n");
            getch();
            return currentGame;
        }           
    }
    printf("You ran out of moves...");

    printf("\nPress any key to exit...\n");
    getch();
    clearBoard();

    return currentGame;
}

void recordMove(int *order, int *last, int *column, int *finalRedoElement, int *waitingforValidMove){
    if (position[*column-1] < num_rows) {
        if (*last%2 == 0) {
            board [position[*column-1]][*column-1] ='X';
        } else {
            board [position[*column-1]][*column-1] ='O';   
        }
    
    if (*finalRedoElement != 0 ) {
        *finalRedoElement = 0;
    }
        order[*last] = *column;
        *last =*last+1;
        position[*column-1] +=1;
        *waitingforValidMove=0;
    } else {
        printf("\nThere is no space left in this column. Try another.");
    }
}

void redoMove(int *order, int *last, int *redoArray, int *finalRedoElement, int *waitingforValidMove){ 
    if (*finalRedoElement > 0) {
        *finalRedoElement = *finalRedoElement-1;
        printf("\nredos left: %d", *finalRedoElement);
        if(*last%2==0) {
            board [position[redoArray[*finalRedoElement]-1]][redoArray[*finalRedoElement]-1] ='X';
        } else {
            board [position[redoArray[*finalRedoElement]-1]][redoArray[*finalRedoElement]-1] ='O';
        }
        order[*last] = redoArray[*finalRedoElement];
        position[order[*last]-1] +=1;
        *last = *last+1;
        *waitingforValidMove=0;
    } else {
        printf("\nThere are no more moves to redo.");
    }
}

void undoMove(int *order, int *last, int *redoArray, int *finalRedoElement, int *waitingforValidMove){
    if (*last > 0) {
        redoArray[*finalRedoElement] = order[*last-1];
        *finalRedoElement = *finalRedoElement+1;

        board [position[order[*last-1]-1]-1][order[*last-1]-1] =' ';
        position[order[*last-1]-1]--;

        *last = *last-1;
        *waitingforValidMove=0;
    } else {
        printf("\nYou must first make a move before you undo.");
    }
    return;
}

void clearBoard(){
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            board[i][j] = ' ';
        }
    }

    for (int i = 0; i < num_cols; i++) {
        position[i] = 0;
    }
}

void printBoard(){
    int row,col,a,c;
    if(b == 0) {                               
        for(a=0;a<num_rows;a++) {
                for(c=0;c<num_cols;c++)
                board[a][c]=' ';
        }
    }
    b++;

    system("cls");                          
    for(row=num_rows-1; row>=0; row--) {        
        for(col=0; col<num_cols; col++) {
            printf("| %c ",board[row][col]);
        }
        printf("|\n");
        for(a=0; a<num_cols; a++) printf("____");
        printf("\n");
    }

    for(a=0; a<num_cols; a++)printf("%*d",4,a+1);
    printf("\n");
}

void history(){

    char optionChar[10];
    int optionInt;

    system("cls");
    printf("\nWelcome to the History Page:");
    printf("\nPrevious Matches:");

    for (int i = 0; i < num_of_games; i++) { //this will print all the previous matched dates, who won, moves taken.
        printf("\n\nGame %d \n________ \nWinner: %s \nNumber of moves: %d\nNumber of Rows: %d \nNumber of Columns: %d",i+1, games[i].winner, games[i].numberOfMoves, games[i].numberOfRows, games[i].numberOfColumns);
    } 
  
    do {
        printf("\n\nWhich game would you like to review?");
        scanf("%s", optionChar);
    }
    while(!isNumeric(optionChar));

    optionInt = atoi(optionChar);

    if (optionInt <= num_of_games && optionInt !=0){
        replayGame(games[optionInt-1]);
    } else {
        printf("The game you chose has not yet been played");
        printf("\nPress any key to exit...\n");
        getch();
    }
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

        Sleep(200);
        printBoard();
    }

    printf("The game replay has concluded");
    clearBoard();
    printf("\nPress any key to exit...\n");
    getch();
    }

void instructions(){
    printf("\n\n");
    printf("\nWelcome to the Instructions Page:");
    printf("\nChoose a column to pace your token");
    printf("\nType undo to undo a previous move");
    printf("\nType redo to redo a move");
    printf("\nTo win you must have 4 tokens in a row"); 
    printf("\nPrevious games can be viewed by pressing '2' in the Main Menu");
    printf("\n\n");
    printf("\nPress any key to exit...\n");
    getch();
 
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

    for (int i = 0; i < num_rows; i++){
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
        for (int j = 0; j < num_rows-3;j++){
            
            win = fourInaRow(board[j][i],board[j+1][i],board[j+2][i],board[j+3][i]);
            if (win == 1) return win;
        }
    }
    return win;
}

int rightDiagonalCheck(){
    //Function to check diagonal win
    int win = 0;

    for (int i = 0; i<num_cols-3; i++){
        for (int j = 0; j < num_rows; j++){

            win = fourInaRow(board[j][i],board[j+1][i+1],board[j+2][i+2],board[j+3][i+3]);           
            if (win == 1) return win;
        }
    }
    return win; 
}

int leftDiagonalCheck(){
    //Function to check diagonal win
    int win = 0;

    for (int i = 3; i<num_cols; i++){
        for (int j = 0; j < num_rows; j++){
            win = fourInaRow(board[j][i],board[j+1][i-1],board[j+2][i-2],board[j+3][i-3]);
            if (win == 1) return win;
        }
    }
    return win; 
}

int fourInaRow(char first, char second, char third, char fourth){

    if(first == second && first == third && first == fourth && first != ' ') {
        printf("\nGG Boys\n");
        return 1;
    } else {
        return 0;
    }
}

void loadState(){
    char line [200];
    int counter = 0;

    FILE * save_history_file = fopen("saveHistory.csv", "r");

    while ( fgets ( line , sizeof(line) , save_history_file ) != NULL ) {
        
        char *token;

        token = strtok(line, ", ");

        while (token != NULL) {

            if (counter == 0) {
                strcpy(games[num_of_games].winner,token);
                counter++;
            }
            else if (counter == 1) {
                games[num_of_games].numberOfMoves = atoi(token);
                counter++;
            }
            else if (counter == 2) {
                games[num_of_games].numberOfColumns = atoi(token);
                counter++;
            }
            else if (counter == 3) {
                games[num_of_games].numberOfRows = atoi(token);
                counter++;
            } else {
                games[num_of_games].moves[counter-4] = atoi(token);
                counter++;
            }
            printf("%s", token);
            token = strtok(NULL, ", ");
        }
        printf("\n");
        
        counter = 0;
        num_of_games++;
    }
    fclose(save_history_file);
    return;
}

void saveState(){
    FILE * save_history_file = fopen("saveHistory.csv", "w+");
    char result[100];
    char snum[2];

    for (int i = 0; i < num_of_games; i++) {
        sprintf(result, "%s, %d, %d, %d", games[i].winner, games[i].numberOfMoves, games[i].numberOfColumns, games[i].numberOfRows);
        
        for (int j = 0; j < games[i].numberOfMoves; j++) {
            strcat(result, ", ");
            itoa(games[i].moves[j], snum, 10);
            strcat(result, snum);
        }
        strcat(result, "\n");
        fprintf(save_history_file, "%s", result);
    }
    fclose(save_history_file);
    return;
}
/*

    ::::TO DO LIST::::
Minimum Requirements:
    -
    -

Additional Marks:
    - allow the computer to play against you.(SEMI-IMPORTANT!)

Other Tasks:
    - Refactor the printBoard Function
*/