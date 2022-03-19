#include"main.h"

void bracket_handle(char *input) {
    int i,j=0;
    int b_start=0;
    int b_end=0 ;

    for(i=0;i<strlen(input);i++){
               if(input[i]=='(')b_start++;
               else if(input[i]==')')b_end++;
            if(b_end>b_start){
                printf("Error in parenthesis!");
                exit(0);
            }
    }

    if(b_end!=b_start){
                printf("Error in parenthesis!");
                exit(0);
            }

}

