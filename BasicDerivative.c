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

struct stack{
    char left_node[M];
    char right_node[M];
    char oper;

}partition;

struct output{
    char out[M];
}output;

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

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
            strcpy(partitionOfString.func_derivative[i],"0");
        }
    }
}

void oper_action(int index, int index1){
    int value3;
    int length;
    char *temporary=(char*)malloc(M*sizeof(char));
    char temp[100];

    if(partition.left_node[0]>47 && partition.left_node[0]<58 && partition.right_node[0]>47 && partition.right_node[0]<58){
        int value1=atoi(partition.left_node);
        int value2=atoi(partition.right_node);
        if(partition.oper=='+')value3=value1+value2;
        if(partition.oper=='-')value3=value1-value2;
        if(partition.oper=='*')value3=value1*value2;
        if(partition.oper=='/')value3=value1/value2;
        if(partition.oper=='^')value3=value1^value2;
        char *temp1=(char*)malloc(M*sizeof(char));
        sprintf(temp1, "%d", value3);
        sprintf(temp,"%s","0");
    }

    else{
        if(partition.oper=='^'){

        }
        else if(partition.oper=='+' || partition.oper=='-'){
            sprintf(temp, "%s%c%s", partitionOfString.func_derivative[index],partition.oper, partitionOfString.func_derivative[index1]);
        }
        else if(partition.oper=='*'){
            sprintf(temp, "%s*%s+%s*%s",partition.left_node ,partitionOfString.func_derivative[index1],partition.right_node, partitionOfString.func_derivative[index]);
        }
        else if(partition.oper=='/'){
            sprintf(temp,"(%s*%s-%s*%s)/(%s)^2",partition.right_node,partitionOfString.func_derivative[index],partition.left_node,partitionOfString.func_derivative[index1],partition.right_node);
        }
    }
        strcpy(partitionOfString.func_derivative[index1], temp);
        //printf("%s %d %c %d %s\n",partitionOfString.func_derivative[index], index, partition.oper, index1, partitionOfString.func_derivative[index1]);
    partitionOfString.stack_operator[index]='\0';
    partitionOfString.func_derivative[index][0]='\0';
    return;
}

int nodevisit(int visit[], int index, int arraysize){
    int i;
    int index1=index;
    int next;

    for(i=0;i<arraysize;i++){
        if(index==visit[i]){
                if(index==0)break;
            index=nodevisit(visit, index-1, arraysize);
            break;
        }
    }
    if(index==0 && visit[0]==0){
        for(i=1;i<arraysize;i++){
            if(visit[i]!=i && index1!=i)return i;
        }
        return arraysize+1;
    }

    return index;
}

int check_visit(int visit[], int index, int arraysize){
    int i;
    for(i=0;i<arraysize;i++){
        if(index==visit[i])return 0;
    }
    return 1;
}

void func_precedence_implement(int size){
    int i;
    int visited[100];
    int j=1,countvisited=0;
    int k=0;
    char op1, op2;
    for(i=0;i<size;){
            if(i==j)j++;
            else if(i>j)j=i+1;

             op1=partitionOfString.stack_operator[i];
             op2=partitionOfString.stack_operator[j];
        if(find_operator(op1)>=find_operator(op2)){
                //printf("visited: %d %d\n",i,j);
            strcpy(partition.left_node,partitionOfString.t_array[i]);
            strcpy(partition.right_node,partitionOfString.t_array[i+1]);
            partition.oper=partitionOfString.stack_operator[i];
                //printf("%s %s\n", partition.left_node,partition.right_node);
                oper_action(i,j);
            partition.left_node[0]='\0';
            partition.right_node[0]='\0';

            if(check_visit(visited, i, countvisited)==1)visited[countvisited++]=i;
                //printf("noh %d\n",visited[countvisited-1]);

            qsort(visited, countvisited, sizeof(int), cmpfunc);
            //for(int p=0;p<=countvisited; p++)printf("pre %d ",visited[p]);

            j=visited[countvisited-1]+1;
            i=nodevisit(visited, i, countvisited);

        }
        else{
            i++;
        }
    }

}



int main(){
    char *input={"10+x/tanx*sinx+lnx+x-5*x"};
    int size= stack_building(input);
    partitionOfString.stack_operator[size]=')';
    derivativeOfFunction(size);
    printf("%s\n", input);
    func_precedence_implement(size);

    for(int i=0;i<size;i++)printf("%s\n",partitionOfString.func_derivative[i]);
}
