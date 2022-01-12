#include "header.h"

int main (){
    int userInput;
    tweet * newNode = NULL;
    tweet * headNode = NULL;
    tweet * node;

    do{
        printf("\n");
        printf("1. Create a new tweet\n");
        printf("2. Display tweets\n");
        printf("3. Search a tweet (by keyword)\n");
        printf("4. Find how many words are \"stop words\"\n");
        printf("5. Delete the nth tweet\n");
        printf("6. Save tweets to a file\n");
        printf("7. Exit\n\n");
        printf("Choose a menu option: ");
        scanf("%d", &userInput);
        getchar();
        printf("\n");

        if(userInput==1){
            node = (tweet*)malloc(sizeof(tweet));
            newNode = createTweet(node);  //assigning newNode the address of the last node

            if(headNode==NULL){ //checking if head node is empty
                headNode = newNode; //assigning head node
            }
            else{
                addNodeToList(&headNode, newNode);  //address of first tweet and address of last tweet created respectively
            }
        }

        else if(userInput==2){
            displayTweets(headNode);  //headNode holds the entry point to the top of the list
        }
        else if(userInput==3){
            searchTweetsByKeyword(headNode);  //headNode holds the entry point to the top of the list
        }
        else if(userInput==4){
            countStopWords(headNode);
        }
        else if(userInput==5){
            deleteTweet(&headNode);
        }
        else if(userInput==6){
            saveTweetsToFile(headNode);
        }
        else{
            if(userInput!=7){
                printf("Invalid menu option\n");
            }
        }
    }while(userInput!=7);

    free(node);
    return 0;
}
