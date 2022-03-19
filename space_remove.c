#include"main.h"

void remove_space(char *input){
    int i,j=0;
    char space=' ';
    char temp[100000];

    for(i=0;i<strlen(input);){
            if(input[i]==space)i++;
        temp[j++]=input[i++];
    }
    temp[j]='\0';
    strcpy(input,temp);

    return;
}
