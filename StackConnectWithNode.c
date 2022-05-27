#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define N 100000
#define M 1000

struct part{
    int countArray[M];
    char t_array[M][M];
    char func_derivative[M][M];
    char stack_operator[M];
}partitionOfString;

int find_operator(char sign){
	if(sign == '(') return 7;
	else if(sign == '^') return 6;
    else if(sign == '*') return 5;
    else if(sign == '/') return 4;
    else if(sign == '+') return 3;
    else if(sign == '-') return 2;
    else if(sign == ')') return 1;
    else return 0;
}

int stack_building(char *input){
    int i,j,count=0,p=0;
    int sign;
    int bracket =0;

    for(i=0;i<strlen(input);i++){
           // printf("me? %d", strlen(input));
            sign = find_operator(input[i]);
            if(sign==7){
                partitionOfString.stack_operator[count]=input[i];
                j=i+1;
                bracket=1;
                while(j<strlen(input)){
                    if(find_operator(input[j])==7)bracket++;
                    if(find_operator(input[j])==1)bracket--;
                    if(bracket==0)break;

                    partitionOfString.t_array[count][p++]=input[j];
                    j++;
                }
                count++;
                p=0;
            }
            else if(i==0 && sign!=0){
                partitionOfString.t_array[count][p++]=input[i];
            }
            else if(sign!=0){
                partitionOfString.stack_operator[count]=input[i];
                count++;
               // i++;
                p=0;
            }

            else partitionOfString.t_array[count][p++]=input[i];

            if(i==strlen(input)-1){
                    count++;
                    i++;
                    p=0;
            }

    }

    return count;

}


int main(void){
   char *input={"(10+x)*(log(tanx)+3)"};
    int size= stack_building(input);
    printf("%d\n",size);
    for(int i=0;i<size;i++){
        printf("%c\t%s\n", partitionOfString.stack_operator[i], partitionOfString.t_array[i]);
    }

}


