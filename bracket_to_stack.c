#include"main.h"

char *find_bracket_to_stack(char *input){
    int i,k=0,j=0;
    char temp[1000][1000];
    for(i=0;i<strlen(input);i++){
        temp[j][k++]=input[i];      //push
        if(input[i+1]=='('){
           j++;
           k=0;                     //split
        }
        if(input[i+1]==')'){
            return temp[j];
        }
    }
}
