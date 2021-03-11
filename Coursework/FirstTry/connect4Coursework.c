#include<stdio.h>
#include<string.h>
#include<string.h>
#include<time.h>
#include<dos.h>
#include <windows.h>

typedef struct {
    char winner[10];
    int moves[50];
    int numberOfMoves;
} game;

int board_rows = 7;
int board_columns = 5;

game start();
void instructions();
void history();
int winCheck();
int horizontalCheck();
int verticalCheck();
int diagonalCheck();


int main(){
    int option;
    int flag =1;
    game games[20];


    while (flag = 1){
        system("cls");  
        printf("\n1. Start Game \n2. History \n3. Instructions \n4. Exit Game\n");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
            printf("\nyou've chosen 1");
            game gameCur = start();
          //  games = gameCur.moves;

            break;

            case 2:
            printf("\nyou've chosen 2");
            history();
            break;
            
            case 3:
            printf("\nyou've chosen 3");
            instructions();
            break;
            
            case 4:
            printf("\nyou've chosen 4");
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

    game currentGame;
    int location;

    system("cls");  
    printf("\n\n");
    printf("\nWelcome to Connect 4");
    printf("\n\n");

    printf("\nBuilding Game Board...");
    for (int i = 0; i<7; i++){
        printf("\n| | | | | |");
    }
    printf("\n-----------");
    printf("\n 1 2 3 4 5");

    printf("Which column would you like to place your token?");
    scanf("%d", &location);





    Sleep(3000);
    return currentGame;
}

void history(){

    int option;

    printf("\n\n");
    printf("\n\n");
    printf("\nWelcome to the History Page:");

    printf("\nPrevious Matches:");
    for (int i = 0; i<50;i++){ //this will print all the previous matched dates, who won, moves taken.
       // printf("%s %s %d", games[i].winner, games[i].numberOfMoves);
    }  
    printf("\n\nWhich game would you like to review?");
    scanf("%d", &option);

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
        printf("You Won");
        win = 1;
    }
    else if(verticalCheck() == 1){
        printf("You Won");
        win = 1;
    } 
    else if(diagonalCheck() == 1){
        printf("You Won");
        win = 1;
    }

    return win;
}

int horizontalCheck(){
    //Function to check horizontal win 
    int win = 0;

    return win;
}

int verticalCheck(){
    //Function to check vertical win 
    int win = 0;

    return win;
}

int diagonalCheck(){
    //Function to check diagonal win
    int win = 0;

    return win; 
}



