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
   /* struct constant{
        int number[M];
        int position[M];
    }number_c;*/
    char stack_operator[M];
}partitionOfString;

struct stack{
    char left_node[M];
    char right_node[M];
    char oper;

}partition;

struct output{
    char out[M];
}output;

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

    char var='x';
   // char oper[50]={ "+-*^" };

    for(i=0;i<strlen(input);i++){
            sign = find_operator(input[i]);
            if(i==0 && sign!=0){
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

void derivativeOfFunction(int size){
    int i;
    for(i=0;i<size;i++){
        if(strcmp("sin",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"cos");
        }
        if(strcmp("cos",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"-sin");
        }
        if(strcmp("tan",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"sec^");
        }
        if(strcmp("ln",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"1/");
        }
        if(strcmp("log",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"lna/");
        }
        if(strcmp("x",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"1");
        }
        if(strcmp("sinx",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"cosx");
        }
        if(strcmp("cosx",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"-sinx");
        }
        if(strcmp("tanx",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"(secx)^2");
        }
        if(strcmp("lnx",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"1/x");
        }
        if(strcmp("logx",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"lna/x");
        }
        if(strcmp("x",partitionOfString.t_array[i])==0){
            strcpy(partitionOfString.func_derivative[i],"1");
        }
        if(partitionOfString.t_array[i][0]>47 && partitionOfString.t_array[i][0]<58){
            strcpy(partitionOfString.func_derivative[i],"1");
        }
    }
}

void oper_action(int index){
    int value3;
    int length;

    if(partition.left_node[0]>47 && partition.left_node[0]<58 && partition.right_node[0]>47 && partition.right_node[0]<58){
        int value1=atoi(partition.left_node);
        int value2=atoi(partition.right_node);
        if(partition.oper=='+')value3=value1+value2;
        if(partition.oper=='-')value3=value1-value2;
        if(partition.oper=='*')value3=value1*value2;
        if(partition.oper=='/')value3=value1/value2;
        if(partition.oper=='^')value3=value1^value2;
        char *temp=(char*)malloc(M*sizeof(char));
        sprintf(temp, "%d", value3);
        strcat(output.out,"0");
    }

    else if(partition.left_node[0]>47 && partition.left_node[0]<58){
        length= strlen(output.out);
        strcat(output.out, partition.left_node);
        output.out[length]=partition.oper;
        partition.left_node[length+1]='\0';
        strcat(output.out,partition.right_node);
    }

    else{
        if(partition.oper=='+'){
                length= strlen(output.out);
            strcat(output.out,partitionOfString.func_derivative[index]);
            output.out[length]='+';
            output.out[length+1]='\0';
            strcat(output.out,partitionOfString.func_derivative[index+1]);
        }
        else if(partition.oper=='*'){
            strcat(output.out, partition.right_node);
            length= strlen(output.out);
            output.out[length]=partition.oper;
            partition.left_node[length+1]='\0';
            strcat(output.out,partitionOfString.func_derivative[index]);
            length= strlen(output.out);
            output.out[length]='+';
            output.out[length+1]='\0';
            strcat(output.out, partition.left_node);
            length= strlen(output.out);
            output.out[length]=partition.oper;
            partition.left_node[length+1]='\0';
            strcat(output.out,partitionOfString.func_derivative[index+1]);
        }
    }
    return;
}

void func_precedence_implement(int size){
    int i;
    for(i=0;i<size-1;i++){
        if(find_operator(partitionOfString.stack_operator[i])>find_operator(partitionOfString.stack_operator[i+1])){
            strcpy(partition.left_node,partitionOfString.t_array[i]);
            strcpy(partition.right_node,partitionOfString.t_array[i+1]);
            partition.oper=partitionOfString.stack_operator[i];
            //printf("%s %c %s\n", partition.left_node, partition.oper, partition.right_node);
            oper_action(i);
            partition.left_node[0]='\0';
            partition.right_node[0]='\0';
        }
    }

}



int main(){
    //char *input={"x*(sin(log(x^5)))^ln(x)+x^3+x^x^x-45*((tanx)*x)^9+2*(sin(cos(-3*x+7*tanx)))+(tanx)^5+7*x^2-x+x-5*(tanx)^5)"};
    char *input={"x*tanx+sinx"};
    int size= stack_building(input);
    derivativeOfFunction(size);
    printf("%s\n", input);
    //for(int i=0;i<size;i++){
      //  printf("%s\t%c\t\t%s\n",partitionOfString.t_array[i], partitionOfString.stack_operator[i],partitionOfString.func_derivative[i]);
    //}
    func_precedence_implement(size);

    printf("=%s\n",output.out);
}
