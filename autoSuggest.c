#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#define Alpha_size 26
typedef struct n
{
    bool isEOW;
    struct n* next[Alpha_size];
} Node;

Node*createNode()
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->isEOW = false;
    for(int i = 0; i < Alpha_size; i++)
        newNode->next[i] = NULL;
    return newNode;
}

void insertWord(Node* root,char* word)
{
    Node* temp = root;
    for(int i = 0; word[i] != '\0' ; i++)
    {
        int idx = word[i] - 'a';
        if(temp->next[idx] == NULL)
        {
            temp->next[idx] = createNode();
            temp = temp->next[idx];
        }
        else
            temp = temp->next[idx];
    }
    temp->isEOW = true;
    printf("\nInserted %s\n",word);
}

void printAllWords(Node* root, char* prefix)
{
    if(root->isEOW == true)
        printf("%s\n",prefix);
    for(int i = 0; i < Alpha_size; i++)
    {
        if(root->next[i] != NULL)
        {
            char c = 'a' + i;
            int l = strlen(prefix);
            char np[l+2];
            strcpy(np,prefix);
            np[l] = c;
            np[l+1] = '\0';
            printAllWords(root->next[i],np);
        }
    }
}

void autoSuggest(Node* root,char* prefix)
{
    for(int i = 0; prefix[i] != '\0'; i++)
    {
        int idx = prefix[i] - 'a';
        if(root->next[idx] != NULL)
            root = root->next[idx];
        else
        {
            printf("No suitable word available starting with %s\n",prefix);
            return;
        }
    }
    printAllWords(root,prefix);
}

int showMenu()
{
    int choice;
    printf("Menu\n====\n1.Insert Word\n2.Auto Suggest Word\n3.Print All Words\n4.Exit\n");
    printf("Your choice:\t");
    scanf("%d",&choice);
    return choice;
}

int main()
{
    Node* root = createNode();
    char word[100];
    FILE* fp = fopen("dictionary.txt","r");
    if(fp == NULL)
        printf("File not found!\n");
    while(!feof(fp))
    {
        fscanf(fp,"%s",word);
        insertWord(root,word);
    }
    fclose(fp);
    while(1)
    {
        int choice = showMenu();
        switch(choice)
        {
        case 1:
            printf("Enter a word:\t");
            scanf("%s",word);
            insertWord(root,word);
            break;
        case 2:
            printf("Enter a prefix:\t");
            scanf("%s",word);
            autoSuggest(root,word);
            break;
        case 3:
            printAllWords(root,"");
            break;
        case 4:
            exit(0);
        default:
            printf("Wrong Choice! Try Again.\n");
            break;
        }
    }
    return 0;
}
