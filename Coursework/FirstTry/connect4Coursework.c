#include<stdio.h>
#include<string.h>
#include<string.h>

int main(){
    int flag=1;

    while(flag==1){                         //FLAG TO START A NEW GAME
    printf("\nDo you want to go to main menue yes/no?");
    scanf("%s",&check);
    if(strcmp(check,yes)==0)start();        //ASKING FOR CONTINUE
    else flag=0;
    }
    return 0;
}