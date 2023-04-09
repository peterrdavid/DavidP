#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef char topic20[21];
typedef char question150[151];
typedef char choice30[31];
typedef char answer30[31];
typedef char filename30[31];
typedef char name30[31];

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

struct recordImportTag
{
    topic20 importTopic;
    int importNum;
    question150 importQuestion;
    choice30 importChoice1;
    choice30 importChoice2;
    choice30 importChoice3;
    answer30 importAnswer;
};

struct scoreTag
{
    name30 playerName;
    int playerScore;
    int playerRow;
};

void getString(question150 question);
void getFileString(FILE *fp, question150 tempQuestion);

void displayExistingRecord(struct recordTag main);
void displaySuccessAdded(void);
void displaySuccessEdited(void);
void displaySuccessDeleted(void);
void displaySuccessImported(void);
void displaySuccessExported(void);
void displayFinalScore(FILE *fp, name30 playerName, int playerScore);

int addRecord(struct recordTag *main, int i);
void editRecord(struct recordTag *main, int ctr);
int deleteRecord(struct recordTag *main, int ctr);
int importRecord(struct recordTag *main, int i);
void exportRecord(struct recordTag *main, int ctr);

void displayPlay(FILE *fpScore, struct recordTag *main, int ctr);
int displayTopics(struct recordTag *main, int ctr);
void displayScores(FILE *fp);

void displayMainMenu(void);
int displayManageData(struct recordTag *recordMain);
void displayPlayGame(struct recordTag *recordMain, int ctr);
int displayExit(int nExitChoice);

void printRecord(struct recordTag *main, int i);
void printRecordImport(struct recordTag *recordMain, int len);

// MAIN function

int
main()
{
    displayMainMenu();

    return 0;
}

// string functions

void
getString(question150 question)
{
    char ch;
    int i = 0;

    do
    {
        scanf("%c", &ch);

        if(ch != '\n')
        {
            question[i] = ch;
            i++;
            question[i] = '\0';
        }
    }while (i < 150 && ch != '\n');
}

void
getFileString(FILE *fp, question150 tempQuestion)
{
    char ch;
    int i = 0;
    int nEnd;

    do
    {
        nEnd = fscanf(fp, "%c", &ch);

        if(i > 151 || ch == '\n')
            nEnd = 0;
        else
        {
            tempQuestion[i] = ch;
            tempQuestion[i+1] = '\0';
            i++;
        }
    }while (nEnd == 1);
}

// display functions

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

void
displaySuccessImported()
{
    int nBack;

    printf("\nSUCCESSFULLY IMPORTED!\n");
    printf("Press any key to go back... ");
    scanf("%d", &nBack);
}

void
displaySuccessExported()
{
    int nBack;

    printf("\nSUCCESSFULLY EXPORTED!\n");
    printf("Press any key to go back... ");
    scanf("%d", &nBack);
}

void
displayFinalScore(FILE *fp, name30 playerName, int playerScore)
{
    int nBack;

    fp = fopen("score.txt", "a");

    fprintf(fp, "%s\n", playerName);
    fprintf(fp, "%d\n\n", playerScore);

    fclose(fp);

    system("clear");
    printf("THANK YOU FOR PLAYING!\n");
    printf("-----------------------\n");
    printf("[PLAYER] %s, your final accumulated score is %d\n", playerName, playerScore);
    printf("\n-----------------------\n");
    printf("Enter any key to go back... ");
    scanf("%d", &nBack);
}

// MANAGE DATA functions

int
addRecord(struct recordTag *main, int i)
{
    struct recordAddTag A;
    A.addNum = 1;
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
    char ch;

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
            if(strcmp(topics[k], "\0") != 0)
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
                        scanf("%c", &ch);
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
            printf("Please enter your choice: ");
            scanf("%d", &nDeleteChoice);

            switch(nDeleteChoice)
            {
                case 1:
                    for(int i = index; i < ctr-1; i++)
                    {
                        strcpy(main[i].topic, main[i+1].topic);
                        main[i].num = main[i+1].num;
                        strcpy(main[i].question, main[i+1].question);
                        strcpy(main[i].choice1, main[i+1].choice1);
                        strcpy(main[i].choice2, main[i+1].choice2);
                        strcpy(main[i].choice3, main[i+1].choice3);
                        strcpy(main[i].answer, main[i+1].answer);
                    }
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

int
importRecord(struct recordTag *main, int index)
{

    FILE *fp;
    filename30 filename;
    struct recordImportTag recordImport[20];
    int ctr = 0;
    int i = 0;
    int nStop = 1;
    int nChoice;
    int nGetInput = 0;

    do
    {
        printf("Enter file name: ");
        scanf("%s", filename);

        fp = fopen(filename, "r");

        if(fp == 0)
        {
            printf("File not found.\n");
            printf("[1] Try again\n");
            printf("[2] Back to MANAGE DATA\n");
            scanf("%d", &nChoice);
            switch(nChoice)
            {
                case 1: 
                    nStop = 1;
                    break;
                case 2:
                    nStop = 0;
                    break;
                default:
                    printf("Invalid choice.\n");
                    nStop = 1;
                    break;
            }
        }
        else
        {
            nStop = 0;
            nGetInput = 1;
        }
    } while(nStop == 1);

    if(nGetInput == 1)
    {
        while (!feof(fp) && i < 20)
        {
            fscanf(fp, "%s\n", recordImport[i].importTopic);
            fscanf(fp, "%d\n", &recordImport[i].importNum);
            getFileString(fp, recordImport[i].importQuestion);
            fscanf(fp, "%s\n", recordImport[i].importChoice1);
            fscanf(fp, "%s\n", recordImport[i].importChoice2);
            fscanf(fp, "%s\n", recordImport[i].importChoice3);
            fscanf(fp, "%s\n\n", recordImport[i].importAnswer);

            strcpy(main[index].topic, recordImport[i].importTopic);
            main[index].num = recordImport[i].importNum;
            strcpy(main[index].question, recordImport[i].importQuestion);
            strcpy(main[index].choice1, recordImport[i].importChoice1);
            strcpy(main[index].choice2, recordImport[i].importChoice2);
            strcpy(main[index].choice3, recordImport[i].importChoice3);
            strcpy(main[index].answer, recordImport[i].importAnswer);

            i++;
            ctr++;
            index++;
        }
        displaySuccessImported();
    }

    fclose(fp);
    
    return ctr;
}

void
exportRecord(struct recordTag *main, int ctr)
{
    FILE *fp;
    filename30 filename;

    printf("Please enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "w");

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

    fclose(fp);

    displaySuccessExported();
}

// PLAY functions

void 
displayPlay(FILE *fpScore, struct recordTag *main, int ctr)
{
    name30 playerName;
    int nStop = 0;
    int playerScore = 0;
    int nReturn;

    system("clear");
    printf("QUIZ GAME\n");
    printf("-----------------------\n");
    printf("Enter player's name: ");
    scanf("%s", playerName);

    do
    {
        nReturn = 0;
        system("clear");
        printf("QUIZ GAME\n");
        printf("-----------------------\n");
        printf("SCORE: \n");
        printf("[PLAYER] %s: %d\n", playerName, playerScore);
        printf("-----------------------\n");
        printf("Enter [0] to END GAME\n");
        printf("-----------------------\n");

        printf("TOPICS:\n");
        nReturn = displayTopics(main, ctr); // returns 0 if incorrect answer, returns 1 if correct answer, returns 2 if end game
        if(nReturn == 1)
            playerScore++;
        else if(nReturn == 2)
        {
            displayFinalScore(fpScore, playerName, playerScore);
            nStop = 1;
        }

    } while (nStop == 0);
}

int
displayTopics(struct recordTag *main, int ctr)
{
    int nFound;
    int nTopics = 0;
    char topics[20][21];
    int j;
    int nTopicChoice;
    int ctrQuestion; // this counts how many questions there are under the chosen topic
    int randomQuestion;
    int nQuestion;
    char cAnswer;
    answer30 answer;
    struct recordTag temp;
    int nReturn = 0;
    int nBack;
    int index = 0; // this gets the index of the random question 
    srand(time(NULL));
    int nContinue;
    int nStop = 0;

    // this for-loop gets all the unique topics and stores them to the array topics[20][21]
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

    // this prints all the unique topics
    for(int k = 0; k < nTopics; k++)
    {
        if(strcmp(topics[k], "\0") != 0)
            printf("[%d] %s\n", k+1, topics[k]);
    }
    
    do
    {
        printf("-----------------------\n");
        printf("Please choose a topic: ");
        scanf("%d", &nTopicChoice);
        
        // if player enters 0, it will terminate the do-while loop and return 2
        if(nTopicChoice == 0)
        {
            nReturn = 2;
            nStop = 1; // this terminates the do-while loop
        }

        // if player enters a valid topic choice, it will enter this condition
        else if(nTopicChoice > 0 && nTopicChoice <= nTopics)
        {
            ctrQuestion = 0;
            // this for-loop count the number of questions under the chosen topic
            for(int k = 0; k < ctr; k++)
            {
                if(strcmp(topics[nTopicChoice-1], main[k].topic) == 0)
                    ctrQuestion++;
            }

            randomQuestion = rand() % ctrQuestion + 1; // this generates the random question number to be answered

            // this for-loop dislays the random question and gets the answer to check if it's correct or not
            nQuestion = 0;
            for(int k = 0; k < ctr; k++)
            {
                if(strcmp(topics[nTopicChoice-1], main[k].topic) == 0)
                {
                     nQuestion++;
                    if(nQuestion == randomQuestion)
                    {
                        printf("%s\n", main[k].question);
                        printf("CHOICES:\n");
                        printf("[A] %s\n", main[k].choice1);
                        printf("[B] %s\n", main[k].choice2);
                        printf("[C] %s\n", main[k].choice3);
                        index = k;
                    }
                }
            }
            // this do-while loop will only terminate once the user inputs a valid answer
            do
            {        
                printf("-----------------------\n");
                printf("Please enter your answer: ");
                scanf(" %c", &cAnswer);
                if(cAnswer != 'A' && cAnswer != 'B' && cAnswer != 'C' && cAnswer != '0')
                    printf("INVALID ANSWER! Try again.\n");
            } while(cAnswer != 'A' && cAnswer != 'B' && cAnswer != 'C' && cAnswer != '0');

            switch(cAnswer)
            {
                case 'A':
                    if(strcmp(main[index].choice1, main[index].answer) == 0)
                    {
                        printf("\nNice, your answer is CORRECT!\n");
                        printf("Enter any key to continue... ");
                        scanf("%d", &nContinue);
                        nReturn = 1;
                    }
                    else
                    {
                        printf("\nSorry, your answer is INCORRECT.\n");
                        printf("Enter any key to continue... ");
                        scanf("%d", &nContinue);
                    }
                    break;
                case 'B':
                    if(strcmp(main[index].choice2, main[index].answer) == 0)
                    {
                        printf("\nNice, your answer is CORRECT!\n");
                        printf("Enter any key to continue... ");
                        scanf("%d", &nContinue);
                        nReturn = 1;
                    }
                    else
                    {
                        printf("\nSorry, your answer is INCORRECT.\n");
                        printf("Enter any key to continue... ");
                        scanf("%d", &nContinue);
                    }
                    break;
                case 'C':
                    if(strcmp(main[index].choice3, main[index].answer) == 0)
                    {
                        printf("\nNice, your answer is CORRECT!\n");
                        printf("Enter any key to continue... ");
                        scanf("%d", &nContinue);
                        nReturn = 1;
                    }
                    else
                    {
                        printf("\nSorry, your answer is INCORRECT.\n");
                        printf("Enter any key to continue... ");
                        scanf("%d", &nContinue);
                    }
                    break;
                case '0':
                    nReturn = 2;
                    break;
            }
            nStop = 1; // this terminates the do-while loop
        }
        
        // if the player enters an invalid choice, it will enter this condition which will ask for an input again
        else
            printf("INVALID CHOICE! Try again.\n");
    } while(nStop == 0);

    return nReturn;
}

void 
displayScores(FILE *fp)
{
    struct scoreTag score[20]; // up to 20 players
    int ctr = 0; // this counts how many player name and scores have been stored
    int i = 0;
    int nBack;
    struct scoreTag temp;

    fp = fopen("score.txt", "r");

    while (!feof(fp) && i < 20)
    {
        fscanf(fp, "%s\n", score[i].playerName);
        fscanf(fp, "%d\n\n", &score[i].playerScore);
        score[i].playerRow = i + 1;
        ctr++;
        i++;
    }

    fclose(fp);

    // bubble sort to arrange player score in decreasing
    for(int i = 0; i < ctr; i++) 
    {
        for(int j = i + 1; j < ctr; j++) 
        {
            if(score[i].playerScore < score[j].playerScore) 
            {
                // swap 
                temp = score[i];
                score[i] = score[j];
                score[j] = temp;
            }
        }
    }

    system("clear");
    printf("SCOREBOARD\n\n");
    printf("RANK    NAME    SCORE   ROW\n");
    for(int j = 0; j < ctr; j++)
    {
        printf("[%d]    %s    %d   %d\n", j+1, score[j].playerName, score[j].playerScore, score[j].playerRow);
    }
    
    printf("\nPress any key to go back... ");
    scanf("%d", &nBack);
}

// MENU functions

void
displayMainMenu()
{
    int nMenuChoice;
    int nExit = 0;
    int nExitChoice = 0;
    int nBack;

    struct recordTag recordMain[20];
    int ctr = 0;

    do
    {
        system("clear");
        printf("\n");
        printf("MAIN MENU\n");
        printf("-----------------------\n");
        printf("%s\n", "[1] Manage Data");
        printf("%s\n", "[2] Play");
        printf("%s\n", "[3] Exit");
        printf("-----------------------\n");
        printf("Enter choice: ");
        scanf("%d", &nMenuChoice);

        switch(nMenuChoice)
        {
            case 1:
                // MANAGE DATA
                ctr = displayManageData(recordMain);
                break;
            case 2:
                // PLAY
                displayPlayGame(recordMain, ctr);
                break;
            case 3:
                // EXIT
                nExit = displayExit(nExitChoice); // returns 1 if players wants to terminate the program, returns 2 if otherwise
                if(nExit == 2)
                    nExit = 0;
                break;
            default:
                // input is not in the choices
                printf("\nINVALID INPUT!\n");
                printf("Enter any key to go back... ");
                scanf("%d", &nBack);
                break;
        }
    }while(nExit == 0);
    
    printf("Program terminated.\n");
}

int
displayManageData(struct recordTag *recordMain)
{
    char Password[6] = "peter";
    char Back[5] = "BACK";
    char Input[6];
    int nStop1 = 0, nStop2 = 0;
    int nContinue = 0;
    int nChoice = 0;
    int nBack = 0;
    int nAdd = 0; // returns 0 if record is existing, returns 1 if record is added
    int ctr = 0; // counter for how many records has been stored 
    char c;
    int nDelete = 0; // return 0 if no record was deleted, returns the number of records deleted
    int nImport = 0; // number of records imported

    FILE *fpRecord;

    fpRecord = fopen("records.txt", "r");
    
    do
    {
        printf("Please enter your password: ");
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
            printf("-----------------------\n");
            printf("[1] Add a record\n");
            printf("[2] Edit a record\n");
            printf("[3] Delete a record\n");
            printf("[4] Import data\n");
            printf("[5] Export data\n");
            printf("[6] Back to MAIN MENU\n");
            printf("-----------------------\n");
            printf("Pleas enter your choice: ");
            scanf("%d", &nChoice);
            
            switch(nChoice)
            {
                case 1:
                    // ADD A RECORD
                    system("clear");
                    printf("ADD A RECORD\n");
                    nAdd = addRecord(recordMain, ctr); // returns 0 if record is existing, returns 1 if record is added 
                    if(nAdd != 0 && ctr < 20) // if record is added, it will enter this condition 
                        ctr++;
                    break;
                case 2:
                    // EDIT A RECORD
                    system("clear");
                    editRecord(recordMain, ctr);
                    break;
                case 3:
                    // DELETE A RECORD
                    nDelete = deleteRecord(recordMain, ctr); // returns 0 if no record deleted, returns the number of records deleted
                    if(nDelete != 0) // if record is deleted, it will enter this condition
                        ctr -= nDelete; // the number of records deleted will be subtracted from the total number of records 
                    break;
                case 4:
                    // IMPORT DATA
                    nImport = importRecord(recordMain, ctr); // returns the number of records imported
                    ctr += nImport;
                    break;
                case 5:
                    // EXPORT DATA
                    exportRecord(recordMain, ctr);
                    break;
                case 6:
                    nStop2 = 1;
                    break;
                default:
                    printf("\nINVALID INPUT!\n");
                    printf("Enter any key to go back... ");
                    scanf("%d", &nBack);
            }
        }while(nStop2 != 1);
    }

    fclose(fpRecord);

    return ctr;
}

void
displayPlayGame(struct recordTag *recordMain, int ctr)
{
    int nChoice;
    int nExit = 0;
    int nExitChoice = 0;
    int nBack;
    char c;

    FILE *fpScore;

    fpScore = fopen("score.txt", "a");

    do
    {
        system("clear");
        printf("PLAY GAME\n");
        printf("-----------------------\n");
        printf("[1] Play\n");
        printf("[2] View Scores\n");
        printf("[3] Exit\n");
        printf("-----------------------\n");
        printf("Please enter your choice: ");
        scanf("%d", &nChoice);
        switch(nChoice)

        {
            case 1:
                // PLAY
                displayPlay(fpScore, recordMain, ctr);
                break;
            case 2:
                // VIEW SCORES
                displayScores(fpScore);
                break;
            case 3:
                // EXIT 
                nExit = 1;
                break;
            default:
                // input is not in the choices
                printf("\nINVALID INPUT!\n");
                printf("Enter any key to go back... ");
                scanf("%d", &nBack);
                break;
        }
    } while(nExit == 0);

    fclose(fpScore);
}

int
displayExit(int nExitChoice)
{
    int nChoice;
    int nBack;

    do
    {
        system("clear");
        printf("EXIT\n");
        printf("-----------------------\n");
        printf("Are you sure you want to exit the program? \n");
        printf("[1] Yes   [2] No \n");
        printf("-----------------------\n");
        printf("Enter choice: ");
        scanf("%d", &nChoice);

        switch(nChoice)
        {
            case 1:
                nExitChoice = 1;
                break;
            case 2:
                nExitChoice = 2;
                break;
            default:
                printf("\nINVALID INPUT!\n");
                printf("Enter any key to go back... ");
                scanf("%d", &nBack);
                break;
        }
    }while(nExitChoice == 0);
   
    return nExitChoice;
}

// PRINT functions

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

void 
printRecordImport(struct recordTag *recordMain, int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%s\n", recordMain[i].topic);
        printf("%d\n", recordMain[i].num);
        printf("%s\n", recordMain[i].question);
        printf("%s\n", recordMain[i].choice1);
        printf("%s\n", recordMain[i].choice2);
        printf("%s\n", recordMain[i].choice3);
        printf("%s\n\n", recordMain[i].answer);
    }
}