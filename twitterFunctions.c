#include "header.h"

void addNodeToList(tweet**tweetList,tweet * node){
    tweet ** trace = tweetList;
    while(*trace){
        trace = &(*trace)->next;  //stepping from the head of the list until reaching pointer to NULL (end of list)
    }
    node->next = *trace;
    *trace = node;  //trace is now at the end of the list so now we can position node here
}

tweet * createTweet( tweet * tweetList){
    int sumUser = 0;
    char username[51];
    char tweet[141];

    printf("Enter a username: ");
    fgets(username, 51, stdin);
    size_t s = strlen(username);         //removed trailing \n to be able to get movie name
    if(username[s-1] == '\n'){
        username[s-1] = '\0';
    }
    strcpy(tweetList->user, username);

    printf("Enter the user's tweet: ");
    fgets(tweet, 141, stdin);
    s = strlen(tweet);         //removed trailing \n to be able to get movie name
    if(tweet[s-1] == '\n'){
        tweet[s-1] = '\0';
    }
    strcpy(tweetList->text, tweet);

    tweetList->next = NULL;  //new node should be at the end of the list and therefore points to NULL
    /*testing*/
    /*printf("%s\n", tweetList->user);
    printf("%s\n", tweetList->text);*/

    for(int i=0; i<(strlen(username)-1); i++){
        sumUser = sumUser + username[i];
    }
    tweetList->id = (sumUser + (strlen(tweet)-1)); // -1 from strlen to remove newline
    printf("Your computer-generated userid is %d\n", tweetList->id);

    return tweetList; //returns the address of the new tweet
}

void deleteTweet(tweet ** tweetList){
    tweet ** temp = tweetList;
    tweet ** trace = tweetList;
    tweet ** deletedTweet = tweetList;
    tweet ** previous = tweetList;

    int numTweets = 0;
    int delete;

    //stepping from the head of the list until reaching pointer to NULL (end of list)
    while(*trace){
        trace = &(*trace)->next;
        numTweets++;              //count after each step
    }

    if(numTweets==1){
        printf("Currently there is %d tweet.\n", numTweets);
        printf("Do you wish to delete this tweet - enter 1 for yes: ");
    }
    else{
        printf("\nCurrently there are %d tweets.\n", numTweets);
        printf("Which tweet do you wish to delete - enter a value between 1 and %d: ", numTweets);
    }
    scanf("%d", &delete);

    //stepping from the head of the list until reaching the node to be deleted for ID extraction
    for(int i=0; i<=(delete-2); i++){
        deletedTweet = &(*deletedTweet)->next;
    }

    if(delete==1){
        tweetList = temp;
        (&(**deletedTweet))->id = (&(**temp))->id; // id of head to be removed
        printf("Tweet %d deleted. There are now %d tweets left.\n\n", (&(**deletedTweet))->id, (numTweets-1));
        *temp = (&(**temp))->next;
    }
    else{
        printf("Tweet %d deleted. There are now %d tweets left.\n\n", (&(**deletedTweet))->id, (numTweets-1));
    }
    
    //stepping from the head of the list until reaching the node previous to the one to be deleted
    for(int i=0; i<=(delete-2); i++){
        if(delete==2){
            (&(**previous))->next = (&(**previous))->next->next;
        }
        else if(numTweets == delete){
            if(i==(delete-2)){
                (&(**previous))->next = NULL;
            }
            else{
                previous = &(*previous)->next;
            }
        }
        else{
            previous = &(*previous)->next;
            (&(**previous))->next = (&(**previous))->next->next;
        }
    }
}

void displayTweets(tweet * tweetList){
    tweet * temp = malloc(sizeof(tweet));
    temp = tweetList; //using a temp of type tweet to avoid losing the head node

    printf("\n");
    while(temp!=NULL){  //stepping until reaching the end of the list
        printf("%d: Created by %s: %s\n", temp->id, temp->user, temp->text);
        temp = temp->next;  //moving temp to the next node
    }
    printf("\n");
}

void saveTweetsToFile(tweet * tweetList){
    char filename[20];
    tweet * temp = tweetList;

    printf("Enter the filename where you like to store your tweets: ");
    scanf("%s", filename);
    getchar();
    FILE * fp = fopen(filename, "w");             //creating file pointer

    while(fp == NULL){
        printf("Could not open file.\n");           //checking for unsuccessful opening
        printf("Enter the filename where you like to store your tweets: ");
        scanf("%s", filename);
        getchar();
        fp = fopen(filename, "w");             //creating file pointer
    }

    while(temp!=NULL){
        fprintf(fp, "%d,", temp->id);
        fprintf(fp, "%s,", temp->user);
        fprintf(fp, "%s", temp->text);
        temp = temp->next;
        fprintf(fp, "\n");
    }
    printf("Tweets exported!\n");
}

int searchTweetsByKeyword(tweet * tweetList){
    char keyword[51];
    char keyword2[51];  //using a keyword2 to convert to lowercase without changing the original keyword
    char text[141];     //using text to convert to lowercase without changing the original text
    int matchFound=0;
    char *check;
    tweet * temp = malloc(sizeof(tweet));
    temp = tweetList; //using a temp of type tweet to avoid losing the head node

    printf("Enter a keyword to search: ");
    scanf("%s", keyword);

    strcpy(keyword2,keyword);
    for(int i=0; i<strlen(keyword2); i++){
        keyword2[i] = tolower(keyword2[i]); //treating all input as lowercase to be case-insensitive
    }

    while(temp!=NULL){  //stepping until reaching the end of the list
        strcpy(text, temp->text);
        for(int i=0; i<strlen(text); i++){
            text[i] = tolower(text[i]);  //turning whole tweet into lowercase characters
        }
        check = strstr(text, keyword2); // chechking the existence of keyword within each tweet

        if(check != NULL){
            printf("Match found for '%s': %s wrote: \"%s\"\n", keyword, temp->user, temp->text);
            matchFound = 1;
        }
        temp = temp->next;  //moving temp to the next node
    }
    free(temp);
    if(matchFound==1){
        return 1;
    }
    return 0;
}

void countStopWords(tweet * tweetList){
    char text[141];     //using text to convert to lowercase without changing the original text
    int countStopWords = 0;
    int totalCount=0;
    int countTweets = 0;
    const char *stopWords[25] = {"a","an","and","are","as","at","be","by","for","from","has","he","in",
                                "is","it","its","of","on","that","the","to","was","were","will","with"};
    char *check;
    tweet * temp = tweetList; //using a temp of type tweet to avoid losing the head node

    while(temp!=NULL){  //stepping until reaching the end of the list
        strcpy(text, temp->text);
        for(int i=0; i<strlen(text); i++){
            text[i] = tolower(text[i]);  //turning whole tweet into lowercase characters
        }

        // chechking the existence of a stop word within each tweet
        for(int i=0; i<25; i++){
            check = NULL;
            check = strstr(text, stopWords[i]);

            if(check){
                if(check == text){  //checking if stop word is at the beginning of the string
                    //printf("%s\n", check);
                    countStopWords++;
                }
                else if(*(check-1) == ' '){ //checking if the stopword is on its own or embedded in another word
                    //printf("%s\n", check);
                    countStopWords++;
                }
            }
        }
        if(countStopWords>0){
            countTweets++;
            totalCount = totalCount + countStopWords;
        }
        countStopWords=0;
        temp = temp->next;  //moving temp to the next node
    }
    printf("Across %d tweets, %d stop words were found.\n", countTweets, totalCount);
}
