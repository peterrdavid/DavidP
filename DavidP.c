#include <stdio.h>
#include <string.h>

void displayMainMenu(void); 
int displayManageData();
int displayPlay();
int displayExit(int nExitChoice);

int
main()
{
    displayMainMenu();

    return 0;
}

void 
displayMainMenu()
{
    int nMenuChoice;
    int nExit = 0;
    int nExitChoice = 0;
    int nBack;

    do
    {
        printf("\n");
        printf("%s\n", "[1] Manage Data");
        printf("%s\n", "[2] Play");
        printf("%s\n", "[3] Exit");
        printf("\n");

        printf("Enter choice: ");
        scanf("%d", &nMenuChoice);

        switch(nMenuChoice)
        {
            case 1:
                displayManageData();
                break;
            case 2:
                displayPlay();
                break;
            case 3:
                nExit = displayExit(nExitChoice);
                break; 
            default:
                printf("INVALID INPUT");
                printf("Enter any key to go back... ");
                scanf("%d", &nBack);
        }

    }while(nExit == 1);
}

int 
displayManageData()
{

}

int
displayPlay()
{

}

int
displayExit(int nExitChoice)
{
    int nChoice;
    int nStop = 0;

    do
    {
         printf("Are you sure you want to exit the program? \n");
        printf("[1] Yes   [2] No \n");
        printf("Enter choice: ");
        scanf("%d", &nChoice);

        switch(nChoice)
        {
            case 1:
                nExitChoice = 1;
                nStop = 1;
                break;
            case 2:
                nStop = 1;
                break;
            default:
                printf("INVALID INPUT");
        }
    }while(nStop == 1);
   
    return nExitChoice;
}