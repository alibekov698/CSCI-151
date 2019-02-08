/*
* CSCI_151, Assignment 4
* Date: 20 November 2018
* author: Nurbek Alibekov
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    char strData[50];
    struct _Node *next;
} Node;

void writeFile2(char fileName[], char ssData[], Node **oLinkedList){
    FILE *output;//Opens the file
    output = fopen(fileName, "a");
    if(output == NULL){//Checks for validity
        printf("Cannot open output file\n");
        return 1;
    }
    fprintf(output, "%s\n", ssData);//Writes the checked substring to the file

    Node *prev = *oLinkedList;

    while(prev->next != NULL){
        fprintf(output, "%s", prev->strData);//Writes the data in the output linked list out to the file
        prev = prev->next;
    }
    fprintf(output, "%s", prev->strData);
    fprintf(output, "\n");

    fclose(output);//Closes the file
}

int isPalindrome(char str[]){
    int x = 1;

    for(int i = 0; i < strlen(str)/2; i++){//Checks if the string passed in is a palindrome
        if(str[i] != str[strlen(str) - i - 1]){
            x = 0;
        }
    }
    return x;//Returns is a palindrome or not
}

char *getPalindrome(char str[]){
    if(isPalindrome(str)){
        return "Is_Palindrome";//Returns "Is_Palindrome", when the string is a palindrome
    } else {
        return "Not_Palindrome";//Returns "Not_Palindrome", when the string is not a palindrome
    }
}

int howManySubstrings(char subStr[], char str[]){
    int num_occurrences = 0;
    int i = 0;

    while(i <= strlen(str) - strlen(subStr)){//Checks how many non-overlapping occurrences of substring occur in each string
        int j = 0;
        while(j < strlen(subStr)){
            if(str[i+j] != subStr[j]){
                break;
            }
            j++;
        }
        if(j == strlen(subStr)){
            num_occurrences++;
            i = i + j;
            continue;
        }
        i++;
    }
    return num_occurrences;//Returns number of non-overlapping occurrences
}


void freeLinkedlist(Node *head){
    Node *sample;

    while(head != NULL){
        sample = head;
        head = head->next;
        free(sample);
    }
}

void printLinkedlist(Node *head){//Free each node consecutively
    if(head != NULL){
        printf("%s", head->strData);
        printLinkedlist(head->next);
    }
}

void appendNode(Node **oLinkedList, char outputLine[]){

        Node *newNode = (Node*)malloc(sizeof(Node));//Create a node
        Node *prev = *oLinkedList;

        strcpy(newNode->strData, outputLine);
        newNode->next = NULL;

        if(*oLinkedList == NULL){
            *oLinkedList = newNode;//Append the node to the output linked list
            return;
        }

        while(prev->next != NULL){
            prev = prev->next;
        }
        prev->next = newNode;
        return;
}

void checkSubstringPalindrome2(char ssData[], char *iStringData[], Node **oLinkedList, int nrIOfileLines){
    for (int i = 0; i < nrIOfileLines; i++){
        appendNode(&(*oLinkedList), iStringData[i]);
        int x = howManySubstrings(ssData, iStringData[i]);//calls howManySubstrings()
        char str[12];

        sprintf(str, "%d", x);
        appendNode(&(*oLinkedList), "\t");
        appendNode(&(*oLinkedList), str);//Write each output line to the oLinkedList linked list using the output format by calling appendNode()
        appendNode(&*oLinkedList, "\t");
        appendNode(&*oLinkedList, getPalindrome(iStringData[i]));
        appendNode(&*oLinkedList, "\n");
    }
}

void readFile2(char filename[], char *ArrayPtr[]){
    FILE *input;//Opens the file
    input = fopen(filename, "r");
    if(input == NULL){//Checks for validity
        printf("Cannot open input file\n");
        return 1;
    }

    int i = 0, j = 0;
    char word[50];

    do{//Reads and saves the file data to the array of pointers
        char c = fgetc(input);
        if(c == EOF){
            break;
        }
        if(c == '\n'){
            word[j] = '\0';
            ArrayPtr[i] = malloc(sizeof(word));
            strcpy(ArrayPtr[i], word);
            j = 0;
            word[j] = '\0';
            i++;
            continue;
        }
        word[j] = c;
        j++;
    } while(1);

    fclose(input);//Closes the file
}

int countFileLines(char filename[]){
    FILE *input;//Opens the file
    input = fopen(filename, "r");
    if(input == NULL){//Checks for validity
        printf("Cannot open file\n");
        return 1;
    }

    char ch;
    int i = 0, count = 0;
    do {//Counts the number of lines
        ch = fgetc(input);
        if(ch != EOF){
            i++;
        }
        if(ch == '\n'){
            count++;
        }
    } while(ch != EOF);

    fclose(input);//Closes the file
    return count;//Returns the number of lines
}

int main(){

    int cnt_iStrings = countFileLines("iStrings.txt");
    char *arr_iStrings[cnt_iStrings];
    readFile2("iStrings.txt", &arr_iStrings);

    int cnt_subStrings = countFileLines("subStrings.txt");
    char *arr_subStrings[cnt_subStrings];
    readFile2("subStrings.txt", &arr_subStrings);

    for(int i = 0; i < cnt_subStrings; i++){//Calls functions according to the number lines of subStrings
        Node *node = NULL;
        checkSubstringPalindrome2(arr_subStrings[i], &arr_iStrings, &node, cnt_iStrings);
        writeFile2("oStrings.txt", arr_subStrings[i], &node);
    }

    return 0;
}








