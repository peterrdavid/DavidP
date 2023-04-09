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
void displayFinalScore(name30 playerName, int playerScore);

int addRecord(struct recordTag *main, int i);
void editRecord(struct recordTag *main, int ctr);
int deleteRecord(struct recordTag *main, int ctr);
int importRecord(struct recordTag *main, int i);
void exportRecord(struct recordTag *main, int ctr);

int displayPlay(int index, struct scoreTag *score, struct recordTag *main, int ctr);
int displayTopics(struct recordTag *main, int ctr);
void displayScores(struct scoreTag *score);

void displayMainMenu(void);
int displayManageData(struct recordTag *recordMain, int ctr);
int displayPlayGame(int index, struct recordTag *recordMain, int ctr);
int displayExit(int nExitChoice);

void printScores(struct scoreTag *score, int len);
void printRecord(struct recordTag *main, int i);

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

    printf("----------------------------------------------------\n");
    printf("RECORD ALREADY EXISTS.\n");
    printf("Enter any key to go back...\n");
    scanf("%d", &nBack);
}

void
displaySuccessAdded()
{
    int nBack;
    printf("----------------------------------------------------\n");
    printf("SUCCESSFULLY ADDED!\n");
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
displayFinalScore(name30 playerName, int playerScore)
{
    int nBack;

    system("clear");
    printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
    printf("----------------------------------------------------\n");
    printf("PLAY GAME\n");
    printf("----------------------------------------------------\n");
    printf("THANK YOU FOR PLAYING, %s!\n\n", playerName);
    printf("Your final accumulated score is %d.\n", playerScore);
    printf("----------------------------------------------------\n");
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
            printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
            printf("----------------------------------------------------\n");
            printf("ADD A RECORD\n");
            printf("----------------------------------------------------\n");
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
    int nBack;

    do
    {
        nTopics = 0;
        kLast = 0;
        ctrQuestion = 0;
        nStopQuestion = 0;

        system("clear");
        printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
        printf("----------------------------------------------------\n");
        printf("EDIT A RECORD\n");
        printf("----------------------------------------------------\n");

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

        printf("----------------------------------------------------\n");
        printf("Enter topic: ");
        scanf("%d", &nTopicChoice);

        // if user chooses back to manage data, it will go under this condition, which will terminate the do-while
        if(nTopicChoice == kLast)
        {
            nStop = 1;
        }
        else if(nTopicChoice > 0 && nTopicChoice < kLast)
        {
            do
            {
                system("clear");
                printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
                printf("----------------------------------------------------\n");
                printf("EDIT A RECORD\n");
                printf("----------------------------------------------------\n");
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

                printf("----------------------------------------------------\n");
                printf("Enter number to edit: ");
                scanf("%d", &nChoice);
                if(nChoice >= nQuestionNum || nChoice <= 0)
                {
                    printf("\nINVALID INPUT!\n");
                    printf("Enter any key to go back...\n");
                    scanf("%d", &nBack);
                }
            } while(nChoice >= nQuestionNum || nChoice <= 0);

            for(int z = 0; z < ctr; z++)
            {
                if(nChoice == main[z].num && strcmp(topics[nTopicChoice-1], main[z].topic) == 0)
                    index = z;
            }
            do
            {
                system("clear");
                printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
                printf("----------------------------------------------------\n");
                printf("EDIT A RECORD\n");
                printf("----------------------------------------------------\n");
                printf("CHOSEN RECORD: \n");
                printf("[1] TOPIC: %s\n", main[index].topic);
                printf("[2] QUESTION: %s\n", main[index].question);
                printf("[3] CHOICE 1: %s\n", main[index].choice1);
                printf("[4] CHOICE 2: %s\n", main[index].choice2);
                printf("[5] CHOICE 3: %s\n", main[index].choice3);
                printf("[6] ANSWER: %s\n", main[index].answer);

                printf("----------------------------------------------------\n");
            
                printf("Enter field to be edited: ");
                scanf("%d", &nEditChoice);
                if(nEditChoice >= 7 || nEditChoice <= 0)
                {
                    printf("\nINVALID INPUT!\n");
                    printf("Enter any key to go back...\n");
                    scanf("%d", &nBack);
                }
            } while(nEditChoice >= 7 || nEditChoice <= 0);

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
                    displaySuccessEdited();
                    break;
                case 2:
                    do
                    {
                        nStopQuestion = 0;
                        printf("Enter NEW QUESTION: ");
                        scanf("%c", &ch);
                        getString(edit.editQuestion);
                        for(int x = 0; x < ctr; x++)
                        {
                            if(strcmp(edit.editQuestion, main[x].question) == 0)
                            {
                                printf("RECORD ALREADY EXISTS.\n");
                                nStopQuestion = 1;
                            }
                        }
                    } while(nStopQuestion == 1);
                    strcpy(main[index].question, edit.editQuestion);
                    displaySuccessEdited();
                    break;
                case 3:
                    printf("Enter NEW CHOICE 1: ");
                    scanf("%s", edit.editChoice1);
                    strcpy(main[index].choice1, edit.editChoice1);
                    displaySuccessEdited();
                    break;
                case 4:
                    printf("Enter NEW CHOICE 2: ");
                    scanf("%s", edit.editChoice2);
                    strcpy(main[index].choice2, edit.editChoice2);
                    displaySuccessEdited();
                    break;
                case 5:
                    printf("Enter NEW CHOICE 3: ");
                    scanf("%s", edit.editChoice3);
                    strcpy(main[index].choice3, edit.editChoice3);
                    displaySuccessEdited();
                    break;
                case 6:
                    printf("Enter NEW ANSWER: ");
                    scanf("%s", edit.editAnswer);
                    strcpy(main[index].answer, edit.editAnswer);
                    displaySuccessEdited();
                    break;
            }
        }
        else
        {
            printf("\nINVALID INPUT!\n");
            printf("Enter any key to go back...\n");
            scanf("%d", &nBack);
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
    int nBack;

    do
    {
        nTopics = 0;
        kLast = 0;

        system("clear");
        printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
        printf("----------------------------------------------------\n");
        printf("DELETE A RECORD\n");
        printf("----------------------------------------------------\n");
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

        printf("----------------------------------------------------\n");
        printf("Enter topic: ");
        scanf("%d", &nTopicChoice);

        // if user chooses back to manage data, it will go under this condition, which will terminate the do-while
        if(nTopicChoice == kLast)
        {
            nStop = 1;
        }
        else if(nTopicChoice > 0 && nTopicChoice < kLast)
        {
            do
            {
                system("clear");
                printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
                printf("----------------------------------------------------\n");
                printf("DELETE A RECORD\n");
                printf("----------------------------------------------------\n");
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

                printf("----------------------------------------------------\n");
                printf("Enter number to delete: ");
                scanf("%d", &nChoice);
                if(nChoice >= nQuestionNum || nChoice <= 0)
                {
                    printf("\nINVALID INPUT!\n");
                    printf("Enter any key to go back...\n");
                    scanf("%d", &nBack);
                }
            } while(nChoice >= nQuestionNum || nChoice <= 0);

            for(int z = 0; z < ctr; z++)
            {
                if(nChoice == main[z].num && strcmp(topics[nTopicChoice-1], main[z].topic) == 0)
                    index = z;
            }
            do
            {
                system("clear");
                printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
                printf("----------------------------------------------------\n");
                printf("DELETE A RECORD\n");
                printf("----------------------------------------------------\n");
                printf("CHOSEN RECORD: \n");
                printf("[1] TOPIC: %s\n", main[index].topic);
                printf("[2] QUESTION: %s\n", main[index].question);
                printf("[3] CHOICE 1: %s\n", main[index].choice1);
                printf("[4] CHOICE 2: %s\n", main[index].choice2);
                printf("[5] CHOICE 3: %s\n", main[index].choice3);
                printf("[6] ANSWER: %s\n", main[index].answer);

                printf("----------------------------------------------------\n");
                printf("Delete this record?: \n");
                printf("[1] YES\n");
                printf("[2] NO\n");
                printf("----------------------------------------------------\n");
                printf("Enter choice: ");
                scanf("%d", &nDeleteChoice);
                if(nDeleteChoice != 1 && nDeleteChoice != 2)
                {
                    printf("\nINVALID INPUT!\n");
                    printf("Enter any key to go back...\n");
                    scanf("%d", &nBack);
                }
            } while(nDeleteChoice != 1 && nDeleteChoice != 2);

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
            }
        }
        else
        {
            printf("\nINVALID INPUT!\n");
            printf("Enter any key to go back...\n");
            scanf("%d", &nBack);
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
    int nBack;

    do
    {
        system("clear");
        printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
        printf("----------------------------------------------------\n");
        printf("IMPORT DATA\n");
        printf("----------------------------------------------------\n");
        printf("Enter file name: ");
        scanf("%s", filename);

        fp = fopen(filename, "r");

        if(fp == 0)
        {
            printf("\nFile not found.\n");
            printf("----------------------------------------------------\n");
            printf("Would you like to try again?: \n");
            printf("[1] YES\n");
            printf("[2] NO, go back to MANAGE DATA\n");
            printf("----------------------------------------------------\n");
            printf("Enter choice: ");
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
                    nStop = 1;
                    printf("\nINVALID INPUT!\n");
                    printf("Enter any key to go back...\n");
                    scanf("%d", &nBack);
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

    system("clear");
    printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
    printf("----------------------------------------------------\n");
    printf("EXPORT DATA\n");
    printf("----------------------------------------------------\n");

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

int 
displayPlay(int index, struct scoreTag *score, struct recordTag *main, int ctr)
{
    FILE *fpScore;
    int nStop = 0;
    int nReturn;
    int nPlayer = 1;
    int nFound = 0; // this will change into 1 if a player is already existing in the records 
    int nPlayerIndex = 0; // index of the existing player


    struct scoreTag temp;
    temp.playerScore = 0;
    temp.playerRow = index + 1;

    system("clear");
    printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
    printf("----------------------------------------------------\n");
    printf("PLAY GAME\n");
    printf("----------------------------------------------------\n");
    printf("Enter player's name: ");
    scanf("%s", temp.playerName);

    do
    {
        nReturn = 0;
        system("clear");
        printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
        printf("----------------------------------------------------\n");
        printf("PLAY GAME\n");
        printf("----------------------------------------------------\n");
        printf("[PLAYER] %s's Score: %d\n", temp.playerName, temp.playerScore);
        printf("----------------------------------------------------\n");
        printf("Enter [0] to END GAME\n");
        printf("----------------------------------------------------\n");

        printf("TOPICS:\n");
        nReturn = displayTopics(main, ctr); // returns 0 if incorrect answer, returns 1 if correct answer, returns 2 if end game
        if(nReturn == 1)
            temp.playerScore++;
        else if(nReturn == 2)
        {
            for(int i = 0; i < 20; i++)
            {
                if(strcmp(temp.playerName, score[i].playerName) == 0)
                {
                    nFound = 1;
                    nPlayerIndex = i;
                }
            }
            if(nFound == 1)
            {
                score[nPlayerIndex].playerScore += temp.playerScore;
                displayFinalScore(temp.playerName, score[nPlayerIndex].playerScore);
                nPlayer = 0;
            }
            else
            {
                strcpy(score[index].playerName, temp.playerName);
                score[index].playerScore = temp.playerScore;
                score[index].playerRow = temp.playerRow;
                displayFinalScore(score[index].playerName, score[index].playerScore);
                nPlayer = 1;
            }
            nStop = 1;
        }
    } while (nStop == 0);

    return nPlayer;
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
    int nReturn = 0;
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
        printf("----------------------------------------------------\n");
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
                        printf("----------------------------------------------------\n");
                        printf("QUESTION:\n");
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
                printf("----------------------------------------------------\n");
                printf("Enter answer: ");
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
displayScores(struct scoreTag *score)
{
    FILE *fp;
    int ctr = 0; // this counts how many player name and scores have been stored
    int i = 0;
    int nBack;
    struct scoreTag temp;
    int nContent = 0;

    fp = fopen("score.txt", "r");

    while (!feof(fp) && i < 20)
    {
        fscanf(fp, "%s\n", score[i].playerName);
        fscanf(fp, "%d\n\n", &score[i].playerScore);
        score[i].playerRow = i + 1;
        ctr++;
        i++;
    }

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

    fseek(fp, 0, SEEK_END); // move to end of file
    if (ftell(fp) != 0) // this checks if score.txt has content
        nContent = 1; // if it has content, assign 1

    system("clear");
    printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
    printf("----------------------------------------------------\n");
    printf("VIEW SCORE\n");
    printf("----------------------------------------------------\n");
    printf("%31s\n\n", "SCOREBOARD");
    if(nContent)
    {
        printf("     %-11s %-10s %10s %8s\n", "RANK", "NAME", "SCORE", "ROW");
        for(int j = 0; j < ctr; j++)
        {
            printf("       %-9d %-11s %7d %9d\n", j+1, score[j].playerName, score[j].playerScore, score[j].playerRow);
        }
        printf("\n----------------------------------------------------\n");
        printf("Enter any key to go back... ");
        scanf("%d", &nBack);
    }
    else
    {
        printf("No scores to display.\n");
        printf("\n----------------------------------------------------\n");
        printf("\nEnter any key to go back... ");
        scanf("%d", &nBack);
    }


    fclose(fp);
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
    int ctrRecord = 0; // counter for how many records have been stored
    int ctr = 0; 
    int index = 0;
    int nIndex = 0;

    do
    {
        ctr = ctrRecord;
        index = nIndex;
        system("clear");
        printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
        printf("----------------------------------------------------\n");
        printf("MAIN MENU\n");
        printf("----------------------------------------------------\n");
        printf("%s\n", "[1] Manage Data");
        printf("%s\n", "[2] Play");
        printf("%s\n", "[3] Exit");
        printf("----------------------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &nMenuChoice);

        switch(nMenuChoice)
        {
            case 1:
                // MANAGE DATA
                ctrRecord = displayManageData(recordMain, ctr);
                break;
            case 2:
                // PLAY
                nIndex = displayPlayGame(index, recordMain, ctrRecord);
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
displayManageData(struct recordTag *recordMain, int ctr)
{
    char Password[6] = "peter";
    char Back[5] = "BACK";
    char Input[6];
    int nStop1 = 0, nStop2 = 0;
    int nContinue = 0;
    int nChoice = 0;
    int nBack = 0;
    int nAdd = 0; // returns 0 if record is existing, returns 1 if record is added
    char c;
    int nDelete = 0; // return 0 if no record was deleted, returns the number of records deleted
    int nImport = 0; // number of records imported

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
            printf("\nINCORRECT PASSWORD!\n");
            printf("Try again or enter BACK to go back to the main menu.\n");
        }
    }while(nStop1 != 1);
    
    if(nContinue == 1)
    {
        do{
            scanf("%c", &c);
            system("clear");
            printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
            printf("----------------------------------------------------\n");
            printf("MANAGE DATA\n");
            printf("----------------------------------------------------\n");
            printf("[1] Add a Record\n");
            printf("[2] Edit a Record\n");
            printf("[3] Delete a Record\n");
            printf("[4] Import Data\n");
            printf("[5] Export Data\n");
            printf("[6] Back to MAIN MENU\n");
            printf("----------------------------------------------------\n");
            printf("Enter choice: ");
            scanf("%d", &nChoice);
            
            switch(nChoice)
            {
                case 1:
                    // ADD A RECORD
                    system("clear");
                    printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
                    printf("----------------------------------------------------\n");
                    printf("ADD A RECORD\n");
                    printf("----------------------------------------------------\n");
                    nAdd = addRecord(recordMain, ctr); // returns 0 if record is existing, returns 1 if record is added 
                    if(nAdd != 0 && ctr < 20) // if record is added, it will enter this condition 
                        ctr++;
                    break;
                case 2:
                    // EDIT A RECORD
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

int
displayPlayGame(int index, struct recordTag *recordMain, int ctr)
{
    int nChoice;
    int nExit = 0;
    int nBack;
    int nPlayers;

    struct scoreTag score[20]; // up to 20 players

    FILE *fpScore;

    fpScore = fopen("score.txt", "a");

    do
    {
        nPlayers = 0;

        system("clear");
        printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
        printf("----------------------------------------------------\n");
        printf("PLAY\n");
        printf("----------------------------------------------------\n");
        printf("[1] Play Game\n");
        printf("[2] View Scores\n");
        printf("[3] Exit\n");
        printf("----------------------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &nChoice);
        switch(nChoice)
        {
            case 1:
                // PLAY
                nPlayers = displayPlay(index, score, recordMain, ctr); // returns 1 if new player is added, returns 0 if player is existing 
                if(nPlayers == 1)
                    index++;
                break;
            case 2:
                // VIEW SCORES
                displayScores(score);
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

        printScores(score, index);
        
    } while(nExit == 0);

    fclose(fpScore);

    return index;
}

int
displayExit(int nExitChoice)
{
    int nChoice;
    int nBack;

    do
    {
        system("clear");
        printf("\n\n%40s\n\n","GENERAL KNOWLEDGE QUIZ GAME");
        printf("----------------------------------------------------\n");
        printf("EXIT\n");
        printf("----------------------------------------------------\n");
        printf("Are you sure you want to exit the program?: \n");
        printf("[1] Yes\n");
        printf("[2] No\n");
        printf("----------------------------------------------------\n");
    
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
                printf("Enter any key to go back...\n");
                scanf("%d", &nBack);
                break;
        }
    } while(nExitChoice == 0);
   
    return nExitChoice;
}

// PRINT functions

void
printScores(struct scoreTag *score, int len)
{
    FILE *fpScore;

    fpScore = fopen("score.txt", "w");

    for(int i = 0; i < len; i++)
    {
        fprintf(fpScore, "%s\n", score[i].playerName);
        fprintf(fpScore, "%d\n\n", score[i].playerScore);
    }

    fclose(fpScore);
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
