#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char topic20[21];
typedef char question150[151];
typedef char choice30[31];
typedef char answer30[31];

struct recordTag
{
    topic20 topic;
    int num;
    question150 question;
    choice30 choice1;
    choice30 choice2;
    choice30 choice3;
    answer30 answer;
};

struct recordAddTag
{
    question150 addQuestion;
    answer30 addAnswer;

    topic20 addTopic;
    choice30 addChoice1;
    choice30 addChoice2;
    choice30 addChoice3;
    int addNum;
};


void getString(question150 ptr);
void displayMainMenu(void);
void displayExistingRecord(void);
int addRecord(struct recordTag *main, struct recordAddTag A, int i);
void printRecord(struct recordTag *main, int i);
void editRecord(struct recordTag *main, int ctr);
void displayManageData(void);
int displayPlay();
int displayExit(int nExitChoice);

int
main()
{
    displayMainMenu();

    return 0;
}

void
getString(question150 ptr)
{
    char ch;
    int i = 0;

    do
    {
        scanf("%c", &ch);

        if(ch != '\n')
        {
            ptr[i] = ch;
            i++;
            ptr[i] = '\0';
        }
    }while (i < 150 && ch != '\n');
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
        system("clear");
        printf("\n");
        printf("MAIN MENU\n");
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
                printf("INVALID INPUT\n");
                printf("Enter any key to go back... ");
                scanf("%d", &nBack);
        }

    }while(nExit != 1);
    
    printf("Program terminated.\n");
}

void
displayExistingRecord()
{
    int nBack;

    printf("Question and answer are already existing in the records.\n");
    printf("Enter any key to go back...\n");
    scanf("%d", &nBack);
}

int
addRecord(struct recordTag *main, struct recordAddTag A, int i)
{
    char c;
    int n = 1;
    int nContinue = 0;
    int z = 1;

    FILE *fp;

    fp = fopen("records.txt", "r");

    scanf("%c", &c);
    printf("Enter question: ");
    getString(A.addQuestion);
    printf("Enter answer: ");
    scanf("%s", A.addAnswer);

    for(int j = 0; j < 20; j++)
    {
        if(strcmp(A.addAnswer, main[j].answer) == 0)
        {
            displayExistingRecord();
            nContinue = 1;
            n = 0;
        }    
    }

    if(nContinue == 0)
    {
        printf("Enter topic: ");
        scanf("%s", A.addTopic);

        printf("Enter choice 1: ");
        scanf("%s", A.addChoice1);
        printf("Enter choice 2: ");
        scanf("%s", A.addChoice2);
        printf("Enter choice 3: ");
        scanf("%s", A.addChoice3);
        for(int k = 0; k < 20; k++)
            if(strcmp(A.addTopic, main[k].topic) == 0)
                A.addNum++;

        strcpy(main[i].topic, A.addTopic);
        main[i].num = A.addNum;
        strcpy(main[i].question, A.addQuestion);
        strcpy(main[i].choice1, A.addChoice1);
        strcpy(main[i].choice2, A.addChoice2);
        strcpy(main[i].choice3, A.addChoice3);
        strcpy(main[i].answer, A.addAnswer);
    }

    fclose(fp);
    return n;
}

void
printRecord(struct recordTag *main, int i)
{
    FILE *fp;

    fp = fopen("records.txt", "a");
    fprintf(fp, "%s\n", main[i].topic);
    fprintf(fp, "%d\n", main[i].num);
    fprintf(fp, "%s\n", main[i].question);
    fprintf(fp, "%s\n", main[i].choice1);
    fprintf(fp, "%s\n", main[i].choice2);
    fprintf(fp, "%s\n", main[i].choice3);
    fprintf(fp, "%s\n", main[i].answer);
    fprintf(fp, "\n");
    fclose(fp);
}

void
editRecord(struct recordTag *main, int ctr)
{
    int nChoice;
    int nFound;
    char topics[20][21]; // maximum 20 topics with 20 letters
    int nTopics = 0;

    for (int j = 0; j < ctr; j++) 
    {
        nFound = 0;
        for(int k = 0; k < ctr; k++)
        {
            if(nFound == 0)
            {
                if(strcmp(main[j].topic, main[k].topic) == 0)
                    nFound = 1;
            }
        }
        if(!nFound)
        {
            strcpy(topics[nTopics], main[j]. topic);
            nTopics++;
        }
    }

    printf("TOPICS: \n");
    for(int z = 0; z < nTopics; z++)
        printf("%s\n", topics[z]);

    printf("\nPlease choose a topic: ");
    scanf("%d", &nChoice);
}

void
displayManageData()
{
    char Password[6] = "peter";
    char Back[5] = "BACK";
    char Input[6];
    int nStop1 = 0, nStop2 = 0;
    int nContinue = 0;
    int nChoice = 0;
    int nBack = 0;
    int i = 0; // index for recordMain
    int n = 0; // returns 0 if record is existing, returns 1 if record is added
    int ctr = 0; // counter for how many records has been stored 
    char c;

    struct recordTag recordMain[20];
    struct recordAddTag record;
    record.addNum = 1;

    FILE *fpRecord;

    fpRecord = fopen("records.txt", "r");
    
    do
    {
        printf("Enter password: ");
        scanf("%s", Input);
        
        if(strcmp(Input, Password) == 0)
        {
            nContinue = 1;
            nStop1 = 1;
        }
        
        else if(strcmp(Input, Back) == 0)
            nStop1 = 1;

        else
        {
            printf("INCORRECT PASSWORD\n");
            printf("Please try again or type BACK to go back to the main menu.\n");
        }
    }while(nStop1 != 1);
    
    if(nContinue == 1)
    {
        do{
            scanf("%c", &c);
            system("clear");
            printf("MANAGE DATA\n");
            printf("[1] Add a record\n");
            printf("[2] Edit a record\n");
            printf("[3] Delete a record\n");
            printf("[4] Import data\n");
            printf("[5] Export data\n");
            printf("[6] Back to MAIN MENU\n");
            
            printf("Enter choice: ");
            scanf("%d", &nChoice);
            
            switch(nChoice)
            {
                case 1:
                    system("clear");
                    printf("ADD A RECORD\n");
                    n = addRecord(recordMain, record, i); // returns 0 if record is existing, returns 1 if record is added 
                    if(n != 0 && ctr < 20) // if record is added, it will enter this condition 
                    {
                        printRecord(recordMain, i);
                        i += 1;
                        ctr += 1;
                    }
                    break;
                case 2:
                    system("clear");
                    printf("EDIT A RECORD\n");
                    editRecord(recordMain, ctr);
                    break;
                case 3:
                    printf("DELETE A RECORD\n");
                    break;
                case 4:
                    printf("IMPORT DATA\n");
                    break;
                case 5:
                    printf("EXPORT DATA\n");
                    break;
                case 6:
                    nStop2 = 1;
                    break;
                default:
                    printf("INVALID INPUT\n");
                    printf("Enter any key to go back... ");
                    scanf("%d", &nBack);
            }
        }while(nStop2 != 1);
    }

    fclose(fpRecord);
}

int
displayPlay()
{

    return 0;
}

int
displayExit(int nExitChoice)
{
    int nChoice;
    int nBack;

    do
    {
        system("clear");
        printf("Are you sure you want to exit the program? \n");
        printf("[1] Yes   [2] No \n");
        printf("Enter choice: ");
        scanf("%d", &nChoice);

        switch(nChoice)
        {
            case 1:
                nExitChoice = 1;
                break;
            case 2:
                nExitChoice = 1;
                break;
            default:
                printf("INVALID INPUT\n");
                printf("Enter any key to go back... ");
                scanf("%d", &nBack);
        }
    }while(nExitChoice != 1);
   
    return nExitChoice;
}
