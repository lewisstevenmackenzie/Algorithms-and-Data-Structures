#include <stdio.h>

int main(int argc, char **argv)
{

    typedef struct module
    {
        char module_id [30]
    };

    typedef struct student
    {
        int id;
        char name [30];
        struct module modules[2];
    };
    


    printf("Hello Bitches!");

    int grades[] = {55,88,66,99};

    for (int i = 0; i < 4; i++)
    {
        printf("\n%d", grades[i]);
    }

    

}