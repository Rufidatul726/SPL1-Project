#include"main.h"

int n_order_diff(char *input){
        int i=0, count=0;

        for(i=0;i<strlen(input);i++){
            if(input[i]=='d' && input[i+1]=='/' && input[i+2]=='d' && input[i+3]=='x'){
                    count++;
                    i=i+2;
                    }
        }
        return count;

}

void delete_order(char *input, int order){
    int i;

    int x=4+(order-1)*5+1;

    for(i=0;i<strlen(input)-order-x;i++){
        input[i]=input[i+x];
    }
    input[i]='\0';
}


