#include<stdio.h>
#include<string.h>
#include<dos.h>
#include <windows.h>

typedef struct {
    char winner[10];
    int moves[50];
    int numberOfMoves;
    int numberOfRows;
    int numberOfColumns;
} game;

int chooseGameMode();
game start(int gamemode);
void clearBoard();
void printGameBoard();
void recordMove(int *order, int *last, int *column, int *finalRedoElement,int *waitingforValidMove);
void undoMove(int *order, int *last, int *redoArray, int *finalRedoElement, int *waitingforValidMove);
void redoMove(int *order, int *last, int *redoArray, int *finalRedoElement, int *waitingforValidMove);
int winCheck();
int horizontalCheck();
int verticalCheck();
int rightdiagonalCheck();
int leftdiagonalCheck();
int fourInaRow(char first, char second, char third, char fourth);
void history();
void replayGame(game curGame);
void instructions();
void gameSettings();
void loadGameState();
void saveGameState();
int isNumeric(char value[10]);

int num_cols = 7;
int num_rows = 7;
char gameBoard[40][40];
int position [40];
int num_of_games = 0;
game games[50];

int chooseGameMode(){
    char userInput[10];
    int option;

    do {
        system("cls");  
        printf("\n      **Game Mode**\n");
        printf("1. Player Vs. Player  \n2. Player Vs. Easy AI \n3. Player Vs. Difficult AI\n");
        scanf("%s", userInput);
        option = atoi(userInput);
    }
    while(!isNumeric(userInput) || option > 3 || option < 1);

    return option;
}

game start(int gamemode){
    clearBoard();
    int order[50], last = 0;
    int redoArray[50], finalRedoElement = 0;
    game currentGame={"",0,0, num_rows, num_cols};

    char input[10];
    int column;
    int waitingforValidMove = 1;

    printf("      ***Welcome to Connect 4***\n");
    printGameBoard();

    while(last<num_cols*num_rows) {
        if (last%2 == 0) {
            while (waitingforValidMove) {
                printf("Player1: Which column would you like to play in? (1 - %d)\n", num_cols);
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
                    printf("Please enter a valid input:\n");
                }
            }
            waitingforValidMove = 1;
        }
        else if (gamemode == 1){
            //This will be used for player 2 when they are a real person.
            while (waitingforValidMove){
                printf("Player2: Which column would you like to play in? (1 - %d)\n", num_cols);
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
                    printf("Please enter a valid input: \n");
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
            printf("One day there will be a difficult AI implemented. \n");
            break;
        }

        printGameBoard();
        if (last > 6){
            if (winCheck()) {
                //save the game to history and then exit the game back to main menu.
                if (last%2 != 0) strcpy(currentGame.winner,"Player1");
                else strcpy(currentGame.winner,"Player2");
                                        
                for (int i = 0; i < 50; i++) {
                    currentGame.moves[i] = order[i];
                }
                currentGame.numberOfMoves = last;
                currentGame.numberOfRows = num_rows;
                currentGame.numberOfColumns = num_cols;

                printf("Winner is: %s \n", currentGame.winner);
                printf("Press any key to exit...\n");
                getch();
                return currentGame;
            } 
        }          
    }
    printf("You ran out of moves...\n");
    printf("Press any key to exit...\n");
    getch();
    return currentGame;
}

void clearBoard(){
    //Function to wipe the gameboard before a new game is played
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            gameBoard[i][j] = ' ';
        }
    }
    for (int i = 0; i < num_cols; i++) {
        position[i] = 0;
    }
}

void printGameBoard(){
    //Function to print the gameboard
    int row, column, a;
    system("cls");                          

    for(row = num_rows-1; row >= 0; row--) {        
        for(column = 0; column < num_cols; column++) {
            printf("| %c ",gameBoard[row][column]);
        }
        printf("|\n");
        for(a = 0; a < num_cols; a++) printf("____");
        printf("\n");
    }

    for(a = 0; a < num_cols; a++) printf("%*d", 4, a+1);
    printf("\n");
}

void recordMove(int *order, int *last, int *column, int *finalRedoElement, int *waitingforValidMove){
    if (position[*column-1] < num_rows) {
        if (*last%2 == 0) {
            gameBoard[position[*column-1]][*column-1] ='X';
        } else {
            gameBoard[position[*column-1]][*column-1] ='O';   
        }
    
    if (*finalRedoElement != 0 ) {
        *finalRedoElement = 0;
    }
        order[*last] = *column;
        *last =*last+1;
        position[*column-1] +=1;
        *waitingforValidMove=0;
    } else {
        printf("There is no space left in this column. Try another.\n");
    }
}

void undoMove(int *order, int *last, int *redoArray, int *finalRedoElement, int *waitingforValidMove){
    if (*last > 0) {
        redoArray[*finalRedoElement] = order[*last-1];
        *finalRedoElement = *finalRedoElement+1;

        gameBoard[position[order[*last-1]-1]-1][order[*last-1]-1] =' ';
        position[order[*last-1]-1]--;

        *last = *last-1;
        *waitingforValidMove=0;
    } else {
        printf("You must first make a move before you undo.\n");
    }
    return;
}

void redoMove(int *order, int *last, int *redoArray, int *finalRedoElement, int *waitingforValidMove){ 
    if (*finalRedoElement > 0) {
        *finalRedoElement = *finalRedoElement-1;
        printf("\nredos left: %d", *finalRedoElement);
        if(*last%2==0) {
            gameBoard[position[redoArray[*finalRedoElement]-1]][redoArray[*finalRedoElement]-1] ='X';
        } else {
            gameBoard[position[redoArray[*finalRedoElement]-1]][redoArray[*finalRedoElement]-1] ='O';
        }
        order[*last] = redoArray[*finalRedoElement];
        position[order[*last]-1] +=1;
        *last = *last+1;
        *waitingforValidMove=0;
    } else {
        printf("There are no more moves to redo.\n");
    }
}

int winCheck(){
    if (horizontalCheck()){
        printf("You Won with a horizontal 4 in a row\n");
        return 1;
    }
    else if(verticalCheck()){
        printf("You Won with a vertical 4 in a row\n");
        return 1;
    } 
    else if(rightDiagonalCheck()){
        printf("You Won with a right diagonal 4 in a row\n");
        return 1;
    }
    else if(leftDiagonalCheck()){
        printf("You Won with a left diagonal 4 in a row\n");
        return 1;
    }
    return 0;
}

int horizontalCheck(){
    //Function to check horizontal win 
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j<num_cols-3; j++){
            if (fourInaRow(gameBoard[i][j],gameBoard[i][j+1],gameBoard[i][j+2],gameBoard[i][j+3])) return 1;
        }
    }
    return 0;
}

int verticalCheck(){
    //Function to check vertical win 
    for (int i = 0; i<num_cols; i++){
        for (int j = 0; j < num_rows-3;j++){
            if (fourInaRow(gameBoard[j][i],gameBoard[j+1][i],gameBoard[j+2][i],gameBoard[j+3][i])) return 1;
        }
    }
    return 0;
}

int rightDiagonalCheck(){
    //Function to check diagonal win
    for (int i = 0; i<num_cols-3; i++){
        for (int j = 0; j < num_rows; j++){
            if (fourInaRow(gameBoard[j][i],gameBoard[j+1][i+1],gameBoard[j+2][i+2],gameBoard[j+3][i+3])) return 1;
        }
    }
    return 0; 
}

int leftDiagonalCheck(){
    //Function to check diagonal win
    for (int i = 3; i<num_cols; i++){
        for (int j = 0; j < num_rows; j++){
            if (fourInaRow(gameBoard[j][i],gameBoard[j+1][i-1],gameBoard[j+2][i-2],gameBoard[j+3][i-3])) return 1;
        }
    }
    return 0; 
}

int fourInaRow(char first, char second, char third, char fourth){
    if(first == second && first == third && first == fourth && first != ' ') {
        printf("\nGG\n");
        return 1;
    } else {
        return 0;
    }
}

void history(){
    char optionChar[10];
    int optionInt;

    system("cls");
    printf("Welcome to the History Page:\n");
    printf("Previous Matches:\n");

    for (int i = 0; i < num_of_games; i++) { //this will print all the previous matched dates, who won, moves taken.
        printf("\n\nGame %d \n________ \nWinner: %s \nNumber of moves: %d\nNumber of Rows: %d \nNumber of Columns: %d",i+1, games[i].winner, games[i].numberOfMoves, games[i].numberOfRows, games[i].numberOfColumns);
    } 
  
    do {
        printf("\n\nWhich game would you like to review?\n");
        scanf("%s", optionChar);
        optionInt = atoi(optionChar);
    }
    while(!isNumeric(optionChar));

    if (optionInt <= num_of_games && optionInt !=0){
        replayGame(games[optionInt-1]);
    } else {
        printf("The game you chose has not yet been played\n");
        printf("Press any key to exit...\n");
        getch();
    }
}

void replayGame(game curGame){
    clearBoard();
    num_rows = curGame.numberOfRows;
    num_cols = curGame.numberOfColumns;

    for (int i = 0; i < curGame.numberOfMoves; i++){
        if (i%2 == 0){
            // print X
            gameBoard[position[curGame.moves[i]-1]][curGame.moves[i]-1] ='X';
        }
        else{
            //print O
            gameBoard[position[curGame.moves[i]-1]][curGame.moves[i]-1] ='O';
        }
        position[curGame.moves[i]-1] +=1;

        Sleep(200);
        printGameBoard();
    }
    printf("The game replay has concluded\n");
    printf("Press any key to exit...\n");
    getch();
}

void instructions(){
    system("cls");
    printf("Welcome to the Instructions Page:\n");
    printf("Choose a column to place your token\n");
    printf("Type undo to undo a previous move\n");
    printf("Type redo to redo the last move\n");
    printf("To win you must have 4 tokens in a row\n"); 
    printf("Previous games can be viewed by pressing '2' in the Main Menu\n");
    printf("\nPress any key to exit...\n");
    getch();
}

void gameSettings(){
    char userInput[10];
    system("cls");  

    do{
        printf("\nHow many rows would you like the game board to be?\n");
        scanf("%s", userInput);
        num_rows = atoi(userInput);

        if (!isNumeric(userInput) || num_rows < 1 || num_rows > 40) {
            printf("Enter a number between 1-40\n");
        }
    }
    while (!isNumeric(userInput) || num_rows < 1 || num_rows > 40);

    do{
        printf("How many columns would you like the game board to be?\n");
        scanf("%s", userInput);
        num_cols = atoi(userInput);

        if (!isNumeric(userInput) || num_cols < 1 || num_cols > 40) {
            printf("Enter a number between 0-40\n");
        }
    }
    while (!isNumeric(userInput) || num_cols < 1 || num_cols > 40);
}

void loadGameState(){
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
            token = strtok(NULL, ", ");
        }       
        counter = 0;
        num_of_games++;
    }
    fclose(save_history_file);
}

void saveGameState(){
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
}

int isNumeric(char stringInput[10]){
    for (int i = 0; stringInput[i] != '\0'; i++){
        if (!isdigit(stringInput[i])){
            return 0;
        }
    }
    return stringInput[0] != '\0';
}

int main() {
    char userInput[10];
    int option;
    int showMenu = 1;
    int gameMode;
    loadGameState();

    while (showMenu) {
        do {
            system("cls");  
            printf("\n1. Start Game \n2. History \n3. Instructions \n4. Change Game Settings \n5. Save Games \n6. Exit Game\n");
            scanf("%s", userInput);
            option = atoi(userInput);
        }
        while(!isNumeric(userInput));

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
                printf("Saving the game History");
                saveGameState();
                Sleep(1000);
                break;

            case 6:
                printf("You've chosen to exit the game\n");
                printf("Thanks for playing :)\n");
                printf("Press any key to exit...\n");
                getch();  
                showMenu = 0;
                return 0;

            default:
                printf("Please choose a valid option.\n");
                printf("Press any key to exit...\n");
                getch();
                break;
        }
    }
    return 0;
}