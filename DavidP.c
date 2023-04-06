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

struct recordEditTag
{
    topic20 editTopic;
    question150 editQuestion;
    choice30 editChoice1;
    choice30 editChoice2;
    choice30 editChoice3;
    answer30 editAnswer;

};

void getString(question150 ptr);

void displayExistingRecord(struct recordTag main);
void displaySuccessAdded(void);
void displaySuccessEdited(void);
void displaySuccessDeleted(void);

int addRecord(struct recordTag *main, struct recordAddTag A, int i);
void editRecord(struct recordTag *main, int ctr);
int deleteRecord(struct recordTag *main, int ctr);


void displayMainMenu(void);
void displayManageData(void);
int displayPlay();
int displayExit(int nExitChoice);

void printRecord(struct recordTag *main, int i);

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
displayInvalidChoice()
{
    int nBack;

    printf("You have entered an invalid choice.\n");
    printf("Press any key to go back...");
    scanf("%d", &nBack);
}
void
displayExistingRecord(struct recordTag main)
{
    int nBack;

    printf("TOPIC: %s\n", main.topic);
    printf("QUESTION: %s\n", main.question);
    printf("CHOICE 1: %s\n", main.choice1);
    printf("CHOICE 2: %s\n", main.choice2);
    printf("CHOICE 3: %s\n", main.choice3);
    printf("ANSWER: %s\n", main.answer);

    printf("\nRECORD ALREADY EXISTS.\n");
    printf("Enter any key to go back...\n");
    scanf("%d", &nBack);
}

void
displaySuccessAdded()
{
    int nBack;

    printf("\nSUCCESSFULLY ADDED!\n");
    printf("Press any key to go back... ");
    scanf("%d", &nBack);
}

void
displaySuccessEdited()
{
    int nBack;

    printf("\nSUCCESSFULLY CHANGED!\n");
    printf("Press any key to go back... ");
    scanf("%d", &nBack);
}

void
displaySuccessDeleted()
{
    int nBack;

    printf("\nSUCCESSFULLY DELETED!\n");
    printf("Press any key to go back... ");
    scanf("%d", &nBack);
}

int
addRecord(struct recordTag *main, struct recordAddTag A, int i)
{
    char c;
    int n = 1;
    int nContinue = 0;

    FILE *fp;

    fp = fopen("records.txt", "r");

    scanf("%c", &c);
    printf("Enter question: ");
    getString(A.addQuestion);
    printf("Enter answer: ");
    scanf("%s", A.addAnswer);

    for(int j = 0; j < 20; j++)
    {
        if(strcmp(A.addQuestion, main[j].question) == 0)
        {
            system("clear");
            displayExistingRecord(main[j]);
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

        displaySuccessAdded();
    }

    fclose(fp);
    return n;
}

void
editRecord(struct recordTag *main, int ctr)
{
    int nTopicChoice;
    int nFound;
    int nChoice;
    char topics[20][21]; // maximum 20 topics with 20 letters
    int nTopics;
    int j;
    int kLast; // last number of unique topics 
    int index; // the index of the record to be edited
    int nEditChoice; 
    struct recordEditTag edit; // this will store the edited record
    int nStop = 0; // this stops the do-while loop and returns back to MANAGE DATA 
    int ctrQuestion; // this counts how many questions there are under a topic
    int nStopQuestion; // this stops the do-while loop if the question has no duplicate
    struct recordTag temp;
    int nQuestionNum; // this resets the question number per topic 

    do
    {
        nTopics = 0;
        kLast = 0;
        ctrQuestion = 0;
        nStopQuestion = 0;

        system("clear");
        printf("EDIT A RECORD\n");
        for (int i = 0; i < ctr; i++) 
        {
            nFound = 0;
            j = 0;
            while(!nFound && j < nTopics)
            {
                if(strcmp(main[i].topic, topics[j]) == 0)
                    nFound = 1;
                j++;
            }
            if(!nFound)
            {
                strcpy(topics[nTopics], main[i].topic);
                nTopics++;
            }
        }

        printf("TOPICS: \n");
        for(int k = 0; k < nTopics; k++)
        {
            printf("[%d] %s\n", k+1, topics[k]);
            kLast = k + 2;
        }
        printf("[%d] Back to MANAGE DATA\n", kLast);

        printf("\nPlease choose a topic: ");
        scanf("%d", &nTopicChoice);

        if(nTopicChoice == kLast)
        {
            nStop = 1;
        }
        else
        {
            printf("QUESTIONS: \n");
            
            // bubble sort to arrange question number in ascending 
            for(int i = 0; i < ctr-1; i++) 
            {
                for(int j = 0; j < ctr-i-1; j++) 
                {
                    if(main[j].num > main[j+1].num) 
                    {
                        // swap main[j] and main[j+1]
                        temp = main[j];
                        main[j] = main[j+1];
                        main[j+1] = temp;
                    }
                }
            }

            nQuestionNum = 1;
            for(int k = 0; k < ctr; k++)
            {
                if(strcmp(topics[nTopicChoice-1], main[k].topic) == 0)
                {
                    printf("[%d] ", nQuestionNum);
                    printf("%s\n", main[k].question);
                    main[k].num = nQuestionNum;
                    nQuestionNum++;
                }
            }

            printf("\nPlease choose which number to edit: ");
            scanf("%d", &nChoice);

            for(int z = 0; z < ctr; z++)
            {
                if(nChoice == main[z].num && strcmp(topics[nTopicChoice-1], main[z].topic) == 0)
                    index = z;
            }

            printf("CHOSEN RECORD: \n");
            printf("[1] TOPIC: %s\n", main[index].topic);
            printf("[2] QUESTION: %s\n", main[index].question);
            printf("[3] CHOICE 1: %s\n", main[index].choice1);
            printf("[4] CHOICE 2: %s\n", main[index].choice2);
            printf("[5] CHOICE 3: %s\n", main[index].choice3);
            printf("[6] ANSWER: %s\n", main[index].answer);

            printf("\nPlease choose a field to be modified: ");
            scanf("%d", &nEditChoice);

            switch(nEditChoice)
            {
                case 1:
                    printf("Enter NEW TOPIC: ");
                    scanf("%s", edit.editTopic);
                    strcpy(main[index].topic, edit.editTopic);
                    for(int r = 0; r < ctr; r++)
                    {
                        if(strcmp(main[index].topic, main[r].topic) == 0)
                            ctrQuestion++;
                        main[index].num = ctrQuestion;
                    }
                    printf("NEW TOPIC: %s\n", main[index].topic);
                    displaySuccessEdited();
                    break;
                case 2:
                    do
                    {
                        printf("Enter NEW QUESTION: ");
                        getString(edit.editQuestion);
                        for(int x = 0; x < ctr; x++)
                        {
                            if(strcmp(edit.editQuestion, main[x].question) == 0)
                            {
                                displayExistingRecord(main[x]);
                                nStopQuestion = 1;
                            }
                        }
                    } while(nStopQuestion == 1);
                    strcpy(main[index].question, edit.editQuestion);
                    printf("NEW QUESTION: %s\n", main[index].question);
                    displaySuccessEdited();
                    break;
                case 3:
                    printf("Enter NEW CHOICE 1: ");
                    scanf("%s", edit.editChoice1);
                    strcpy(main[index].choice1, edit.editChoice1);
                    printf("NEW CHOICE 1: %s\n", main[index].choice1);
                    displaySuccessEdited();
                    break;
                case 4:
                    printf("Enter NEW CHOICE 2: ");
                    scanf("%s", edit.editChoice2);
                    strcpy(main[index].choice2, edit.editChoice2);
                    printf("NEW CHOICE 2: %s\n", main[index].choice2);
                    displaySuccessEdited();
                    break;
                case 5:
                    printf("Enter NEW CHOICE 3: ");
                    scanf("%s", edit.editChoice3);
                    strcpy(main[index].choice3, edit.editChoice3);
                    printf("NEW CHOICE 3: %s\n", main[index].choice3);
                    displaySuccessEdited();
                    break;
                case 6:
                    printf("Enter NEW ANSWER: ");
                        scanf("%s", edit.editAnswer);
                        strcpy(main[index].answer, edit.editAnswer);
                        printf("NEW ANSWER: %s\n", main[index].answer);
                        displaySuccessEdited();
                        break;
                default:
                    displayInvalidChoice();
                    break;
            }
        }
        // this nested for loop makes the 2-D array topics empty
        for (int i = 0; i < 20; i++) 
            strcpy(topics[i], "\0");

    } while(nStop == 0);
}

int 
deleteRecord(struct recordTag *main, int ctr)
{
    int nTopicChoice;
    int nFound;
    int nChoice;
    char topics[20][21]; // maximum 20 topics with 20 letters
    int nTopics;
    int j;
    int kLast; // last number of unique topics 
    int index; // the index of the record to be edited
    int nDeleteChoice; 
    int nStop = 0; // this stops the do-while loop and returns back to MANAGE DATA 
    struct recordTag temp;
    int nQuestionNum; // this resets the question number per topic 
    int nDelete = 0; // this counts how many records were deleted

    do
    {
        nTopics = 0;
        kLast = 0;

        system("clear");
        printf("DELETE A RECORD\n");
        for (int i = 0; i < ctr; i++) 
        {
            nFound = 0;
            j = 0;
            while(!nFound && j < nTopics)
            {
                if(strcmp(main[i].topic, topics[j]) == 0)
                    nFound = 1;
                j++;
            }
            if(!nFound)
            {
                strcpy(topics[nTopics], main[i].topic);
                nTopics++;
            }
        }

        printf("TOPICS: \n");
        for(int k = 0; k < nTopics; k++)
        {
            printf("[%d] %s\n", k+1, topics[k]);
            kLast = k + 2;
        }
        printf("[%d] Back to MANAGE DATA\n", kLast);

        printf("\nPlease choose a topic: ");
        scanf("%d", &nTopicChoice);

        if(nTopicChoice == kLast)
        {
            nStop = 1;
        }
        else
        {
            printf("QUESTIONS: \n");
            
            // bubble sort to arrange question number in ascending 
            for(int i = 0; i < ctr-1; i++) 
            {
                for(int j = 0; j < ctr-i-1; j++) 
                {
                    if(main[j].num > main[j+1].num) 
                    {
                        // swap main[j] and main[j+1]
                        temp = main[j];
                        main[j] = main[j+1];
                        main[j+1] = temp;
                    }
                }
            }

            nQuestionNum = 1;
            for(int k = 0; k < ctr; k++)
            {
                if(strcmp(topics[nTopicChoice-1], main[k].topic) == 0)
                {
                    printf("[%d] ", nQuestionNum);
                    printf("%s\n", main[k].question);
                    main[k].num = nQuestionNum;
                    nQuestionNum++;
                }
            }

            printf("\nPlease choose which number to delete: ");
            scanf("%d", &nChoice);

            for(int z = 0; z < ctr; z++)
            {
                if(nChoice == main[z].num && strcmp(topics[nTopicChoice-1], main[z].topic) == 0)
                    index = z;
            }

            printf("CHOSEN RECORD: \n");
            printf("[1] TOPIC: %s\n", main[index].topic);
            printf("[2] QUESTION: %s\n", main[index].question);
            printf("[3] CHOICE 1: %s\n", main[index].choice1);
            printf("[4] CHOICE 2: %s\n", main[index].choice2);
            printf("[5] CHOICE 3: %s\n", main[index].choice3);
            printf("[6] ANSWER: %s\n", main[index].answer);

            printf("\nDelete this record?: \n");
            printf("[1] YES\n");
            printf("[2] NO\n");
            printf("Please enter your choice:");
            scanf("%d", &nDeleteChoice);

            switch(nDeleteChoice)
            {
                case 1:
                    strcpy(main[index].topic, "\0");
                    main[index].num = -1;
                    strcpy(main[index].question, "\0");
                    strcpy(main[index].choice1, "\0");
                    strcpy(main[index].choice2, "\0");
                    strcpy(main[index].choice3, "\0");
                    strcpy(main[index].answer, "\0");
                    nStop = 1;
                    nDelete++;
                    displaySuccessDeleted();
                    break;
                case 2:
                    break;
                default:
                    displayInvalidChoice();
                    break;
            }
        }
        // this nested for loop makes the 2-D array topics empty
        for (int i = 0; i < 20; i++) 
            strcpy(topics[i], "\0");

    } while(nStop == 0);
    return nDelete;
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
    int nAdd = 0; // returns 0 if record is existing, returns 1 if record is added
    int ctr = 0; // counter for how many records has been stored 
    char c;
    int nDelete = 0; // return 0 if no record was deleted, returns the number of records deleted

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
                    // ADD A RECORD
                    system("clear");
                    printf("ADD A RECORD\n");
                    nAdd = addRecord(recordMain, record, i); // returns 0 if record is existing, returns 1 if record is added 
                    if(nAdd != 0 && ctr < 20) // if record is added, it will enter this condition 
                    {
                        i++;
                        ctr++;
                    }
                    printRecord(recordMain, ctr);
                    break;
                case 2:
                    // EDIT A RECORD
                    system("clear");
                    editRecord(recordMain, ctr);
                    printRecord(recordMain, ctr);
                    break;
                case 3:
                    // DELETE A RECORD
                    nDelete = deleteRecord(recordMain, ctr);
                    if(nDelete != 0)
                        ctr -= nDelete;
                    printRecord(recordMain, ctr);
                    break;
                case 4:
                    // IMPORT DATA
                    
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


void
printRecord(struct recordTag *main, int ctr)
{
    FILE *fp;

    fp = fopen("records.txt", "a");
    for(int i = 0; i < ctr; i++)
    {
        fprintf(fp, "%s\n", main[i].topic);
        fprintf(fp, "%d\n", main[i].num);
        fprintf(fp, "%s\n", main[i].question);
        fprintf(fp, "%s\n", main[i].choice1);
        fprintf(fp, "%s\n", main[i].choice2);
        fprintf(fp, "%s\n", main[i].choice3);
        fprintf(fp, "%s\n", main[i].answer);
        fprintf(fp, "\n");
    }

    fprintf(fp, "------\n");
    fclose(fp);
}
