#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define N 100
#define M 100


struct part{
    int countArray[M];
    char t_array[M][M];
    char func_derivative[M][M];
    char stack_operator[M];
}partitionOfString[M];

//int numberOfStack=0;
//int max=0;

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

int numberOfStack=0;
int max=0;

void chain_rule(char *input){
    int bracket = 0,p=0,j;
    int count[100]={0};

    for(int i=0;i<strlen(input);i++){
        partitionOfString[numberOfStack].t_array[0][p++]=input[i];
        else if(find_operator(input[i])==7){
            numberOfStack++;
            count[numberOfStack]=p;
            p=count[numberOfStack];
        }

        if(max<numberOfStack)max=numberOfStack;
        printf("\n%s", partitionOfString[numberOfStack].t_array[0]);
    }
    for(int i=0;i<=max;i++){
        printf("%d\n", count[i]);
    }
}


int main(void){
    printf("oi?");
   char input[]={"(10+x)*(log(tanx)+3-(x^x)^x)"};

   chain_rule(input);
   for(int i=0;i<=max;i++){
    printf("\n %d %s\n",i, partitionOfString[i].t_array[0]);
   }

    //int size= stack_building(input);

}


/*int stack_building(char *input){
    int i,j,count=0,p=0;
    int sign;
    int bracket =0;

    for(i=0;i<strlen(input);i++){
            sign = find_operator(input[i]);

            if(i==0 && sign!=0){
                partitionOfString[numberOfStack].t_array[count][p++]=input[i];
            }
            else if(sign!=0){
                partitionOfString[numberOfStack].stack_operator[count]=input[i];
                count++;
               // i++;
                p=0;
            }

            else partitionOfString[numberOfStack].t_array[count][p++]=input[i];

            if(i==strlen(input)-1){
                     count++;
                    i++;
                    p=0;
            }

    }

    return count;

}

*/
