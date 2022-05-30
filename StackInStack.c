#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define N 100
#define M 100

int find_operator(char);
int find_if_it_is_root(int *, int*);
void push(char, int, int);
int visit_if_node_available(int);
void chain_rule_implementation(char*);
void nonRootDerivatives(char *);
void derivativeOfFunctionOfNonRoot(int , int , int);
void derivativeOfFunction(int ,int );
void rulebook();
void displayInputRequest();
void bracket_handle(char *);
void delete_order(char *, int);
int n_order_diff(char *);
void remove_space(char *);
void take_input(char *);
void func_precedence_implement(int);
int nodevisit(int[], int , int);
int check_visit(int[], int, int);
void oper_action(int, int, int);
void stack_building_nonRoot(char *, int );
void stack_building(char* , int);
double constant_oper(double, double, char);

int numberOfStack;
int max;

struct part{
    int countArray;
    char t_array[M][M];
    char func_derivative[M][M];
    char stack_operator[M];
}partitionOfString[M];

struct stack{
    char left_node[M];
    char right_node[M];
    char oper;

}partition;

struct node{
    int data[M];

    int next[M];
}linkNode;

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

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void push(char character, int index, int arrayIndex){
    partitionOfString[index].t_array[0][arrayIndex]=character;
    return;
}


int visit_if_node_available(int index){
    while(index){
       if(strlen(partitionOfString[index].t_array[0])==0)return index;
       index++;
    }
    return index;
}

void chain_rule_implementation(char *input){
    int i=0,j, sign,nodeIndex;
    int indexOfStack=0;
    int stringlength=0;
    linkNode.data[0]=0;

    while(i<strlen(input)){
        sign= find_operator(input[i]);
        if(sign==1){
            nodeIndex=indexOfStack;
            for(j=0;j<=max;j++){
                if(linkNode.next[j]==indexOfStack){
                    indexOfStack=linkNode.data[j];
                    break;
                }
            }
            stringlength= strlen(partitionOfString[indexOfStack].t_array[0]);
            strcat(partitionOfString[indexOfStack].t_array[0], partitionOfString[nodeIndex].t_array[0]);
            //sprintf("%s%s",partitionOfString[indexOfStack].t_array[0],partitionOfString[nodeIndex].t_array[0]);
        }
        stringlength= strlen(partitionOfString[indexOfStack].t_array[0]);
        push(input[i], indexOfStack, stringlength);

        if(sign==7){
            nodeIndex=indexOfStack;
            indexOfStack= visit_if_node_available(indexOfStack+1);
            linkNode.data[nodeIndex]=nodeIndex;
            linkNode.next[nodeIndex]=indexOfStack;
            if(max<indexOfStack)max=indexOfStack;
        }

        i++;
        //printf("\n %d %s\n",max, partitionOfString[numberOfStack].t_array[0]);
    }
}

void nonRootDerivatives(char *string){
        if(strcmp("cosec(",string)==0){
            strcpy(string,"-cot()*cosecx()");
        }
        else if(strcmp("cot(",string)==0){
            strcpy(string,"-cosec()^2");
        }
        else if(strcmp("sec(",string)==0){
            strcpy(string,"sec()*tan()");
        }
        else if(strcmp("ln(",string)==0){
            strcpy(string,"1/()");
        }
        else if(strcmp("log(",string)==0){
            strcpy(string,"lna/()");
        }
        else if(strcmp("arcsin(",string)==0){
            strcpy(string,"1/((1-()^2)^(1/2))");
        }
        else if(strcmp("arccos(",string)==0){
            strcpy(string,"-1/((1-()^2)^(1/2))");
        }
        else if(strcmp("arctan(",string)==0){
            strcpy(string,"1/(1+()^2)");
        }
        else if(strcmp("arcsec(",string)==0){
            strcpy(string,"1/(()*(()^2-1)^(1/2)");
        }
        else if(strcmp("arccosec(",string)==0){
            strcpy(string,"-1/(()*(()^2-1)^(1/2)");
        }
        else if(strcmp("arccot(",string)==0){
            strcpy(string,"-1/(1+()^2)");
        }
        else if(strcmp("sin(",string)==0){
            strcpy(string,"cos()");
        }
        else if(strcmp("cos(",string)==0){
            strcpy(string,"-sin()");
        }
        else if(strcmp("tan(",string)==0){
            strcpy(string,"sec()^2");
        }
        else if(strcmp("ln(",string)==0){
            strcpy(string,"1/()");
        }
        else if(strcmp("log(",string)==0){
            strcpy(string,"lna/()");
        }
}

void derivativeOfFunctionOfNonRoot(int index, int arraySize, int stringIndex){
    int i,k1, j=0,k=0, count, bracket;
    int lastvisit=-1;
    int size= strlen(partitionOfString[index].t_array[stringIndex]);

    char temp[100], temp1[100], temp2[100];
    for(i=0;i<size;i++){
        temp1[i]=partitionOfString[index].t_array[stringIndex][i];

        if(partitionOfString[index].t_array[stringIndex][i]=='('){
            if(lastvisit>=i)continue;
            nonRootDerivatives(temp1);
            bracket=1;
        //printf("tir %s", temp1);
            for(j=0;j<size-i;j++){
                if(partitionOfString[index].t_array[stringIndex][i+j+1]=='(')bracket++;
                if(partitionOfString[index].t_array[stringIndex][i+j+1]==')')bracket--;
                if(bracket==0){
                    temp[j]='\0';
                    lastvisit=i+j+1;
                    break;
                }
                temp[j]=partitionOfString[index].t_array[stringIndex][i+j+1];
                //printf("%c %d ",temp[j],size-i);
            }
            //printf(" temp =%s   ", temp);
            k=0;
            for(j=0;j<strlen(temp1);j++){
                temp2[k++]=temp1[j];
                if(temp1[j]=='(' && temp1[j+1]==')'){
                //strcat(temp2, temp);
                    for(k1=0;k1<strlen(temp);k1++)temp2[k++]=temp[k1];
                }
            }
            temp2[k++]='*';
            temp2[k]='\0';

            //printf("t=%s\t",temp2);
            for(j=max;j>=0;j--){
                if(strcmp(temp, partitionOfString[j].t_array[stringIndex])==0){
                        //printf("dev=%d %s\n",j, partitionOfString[j].func_derivative[count]);
                    strcat(temp2, partitionOfString[j].func_derivative[stringIndex]);
                    if(strlen(temp2)==2)sprintf(temp2,"(%s)",partitionOfString[j].func_derivative[stringIndex]);

                }
            }

        }
    }
    //int count1=partitionOfString[index].countArray-1;
    strcpy(partitionOfString[index].func_derivative[stringIndex],temp2);
    printf("%s -> %s\n",partitionOfString[index].t_array[stringIndex],partitionOfString[index].func_derivative[stringIndex]);

}

void derivativeOfFunction(int index,int i){
    int j;

    char *temp;
            temp= strstr(partitionOfString[index].t_array[i],"x");
            if(temp==NULL){
                strcpy(partitionOfString[index].func_derivative[i],"0");
                return;
            }

        if(strcmp("x",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"1");
        }
        else if(strcmp("sinx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"cosx");
        }
        else if(strcmp("cosx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"-sinx");
        }
        else if(strcmp("tanx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"(secx)^2");
        }
        else if(strcmp("cosecx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"-cotx*cosecx");
        }
        else if(strcmp("cotx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"-(cosecx)^2");
        }
        else if(strcmp("secx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"secx*tanx");
        }

        else if(strcmp("lnx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"1/x");
        }
        else if(strcmp("logx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"lna/x");
        }
        else if(strcmp("arcsinx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"1/((1-x^2)^(1/2))");
        }
        else if(strcmp("arccosx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"-1/((1-x^2)^(1/2))");
        }
        else if(strcmp("arctanx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"1/(1+x^2)");
        }
        else if(strcmp("arcsecx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"1/(x*(x^2-1)^(1/2)");
        }
        else if(strcmp("arccosecx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"-1/(x*(x^2-1)^(1/2)");
        }
        else if(strcmp("arccotx",partitionOfString[index].t_array[i])==0){
            strcpy(partitionOfString[index].func_derivative[i],"-1/(1+x^2)");
        }

}

int find_if_it_is_root(int *roots, int *notRoots){
    int i,j=0,k=0;
    char *temp;

    for(i=0;i<=max;i++){
       temp=strstr(partitionOfString[i].t_array[0],"(") ;
       if(temp)notRoots[k++]=i;
       else roots[j++]=i;
    }
    return j;
}

void stack_building(char *input, int index){
    int i,j,count=1,p=0;
    int sign;
    int bracket =0;

    for(i=0;i<strlen(input);i++){
            sign = find_operator(input[i]);
            if(i==0 && sign!=0){
                partitionOfString[index].t_array[count][p++]=input[i];
            }
            else if(sign!=0){
                partitionOfString[index].stack_operator[count]=input[i];
                count++;
               // i++;
                p=0;
            }

            else partitionOfString[index].t_array[count][p++]=input[i];

            if(i==strlen(input)-1){
                     count++;
                    i++;
                    p=0;
            }

    }

    partitionOfString[index].countArray=count;

}

void stack_building_nonRoot(char *input, int index){
    int i,j,count=1,p=0,k=0;
    int sign;
    int bracket =0;

    for(i=0;i<strlen(input);i++){
            sign = find_operator(input[i]);
            if(sign==7){
                    bracket=0;
                    while(i<strlen(input)){
                        if(find_operator(input[i])==7)bracket++;
                        else if(find_operator(input[i])==1)bracket--;
                        partitionOfString[index].t_array[count][p++]=input[i];
                       // printf("%d %s\n",bracket, partitionOfString[index].t_array[count]);
                        if(bracket==0)break;
                        i++;
                    }
            }
            else if(i==0 && sign!=0){
                partitionOfString[index].t_array[count][p++]=input[i];
            }
            else if(sign!=0){
                partitionOfString[index].stack_operator[count]=input[i];
                count++;
               // i++;
                p=0;
            }

            else partitionOfString[index].t_array[count][p++]=input[i];

            if(i==strlen(input)-1){
                     count++;
                    i++;
                    p=0;
            }
        //printf("%s\n", partitionOfString[index].t_array[count]);
    }

    partitionOfString[index].countArray=count;

}

double constant_oper(double value1, double value2, char oper){
        double value3;

        if(oper=='+')value3=value1+value2;
        if(oper=='-')value3=value1-value2;
        if(oper=='*')value3=value1*value2;
        if(oper=='/')value3=value1/value2;
        if(oper=='^')value3=(int)value1^(int)value2;
        return value3;
}

void oper_action(int index, int index1,int structIndex){
    double value3;
    int length;
    int constant;
    int constant1;
    char *temporary=(char*)malloc(M*sizeof(char));
    char temp[100];
    char *tmp, *tmp1;
    tmp= strstr(partition.left_node,"x");
    tmp1= strstr(partition.right_node,"x");

    if(!tmp && !tmp1){
        double value1=atof(partition.left_node);
        double value2=atof(partition.right_node);
        value3=constant_oper(value1, value2, partition.oper);
        char *temp1=(char*)malloc(M*sizeof(char));
        sprintf(temp1, "%d", value3);
        strcpy(partitionOfString[structIndex].t_array[index1],temp1);
        partitionOfString[structIndex].stack_operator[index]='\0';
        partitionOfString[structIndex].func_derivative[index][0]='\0';
        sprintf(temp,"%s","0");
        return;
    }

    else{
        if(partition.oper=='^'){
            if(!tmp){
                sprintf(temp, "%s*ln%s", partition.right_node, partition.left_node);
            }
            else if(!tmp1){
                constant=atoi(partition.right_node)-1;
                sprintf(temp, "%s*%s^%d",partition.right_node, partition.left_node, constant);
            }
            else{
                sprintf(temp, "%s%c%s*(%s*%s/%s+ln(%s)*%s)",partition.left_node, partition.oper, partition.right_node, partition.left_node,partitionOfString[structIndex].func_derivative[index1],partition.right_node,partition.right_node,partitionOfString[structIndex].func_derivative[index]);
            }


        }
        else if(partition.oper=='+' || partition.oper=='-'){
            if(!tmp){
                sprintf(temp, "%s", partitionOfString[structIndex].func_derivative[index1]);
            }
            else if(!tmp1){
                sprintf(temp, "%s",partitionOfString[structIndex].func_derivative[index]);
            }
            else{
                sprintf(temp, "%s%c%s", partitionOfString[structIndex].func_derivative[index],partition.oper, partitionOfString[structIndex].func_derivative[index1]);
            }

        }
        else if(partition.oper=='*'){
            if(!tmp){
                sprintf(temp, "%s*%s", partition.left_node, partitionOfString[structIndex].func_derivative[index1]);
            }
            else if(!tmp1){
                sprintf(temp, "%s*%s ",partitionOfString[structIndex].func_derivative[index],partition.right_node);
            }
            else{
                sprintf(temp, "%s*%s+%s*%s",partition.left_node ,partitionOfString[structIndex].func_derivative[index1],partition.right_node, partitionOfString[structIndex].func_derivative[index]);
            }
        }
        else if(partition.oper=='/'){
            if(!tmp){
                sprintf(temp, "%s*%s/(%s)^2", partition.left_node, partition.right_node, partitionOfString[structIndex].func_derivative[index1]);
            }
            else if(!tmp1){
                sprintf(temp, "%s/%s ",partitionOfString[structIndex].func_derivative[index],partition.right_node);
            }
            else{
                sprintf(temp,"(%s*%s-%s*%s)/(%s)^2",partition.right_node,partitionOfString[structIndex].func_derivative[index],partition.left_node,partitionOfString[structIndex].func_derivative[index1],partition.right_node);
            }
        }
    }
        strcpy(partitionOfString[structIndex].func_derivative[index1], temp);
        int len=strlen(partitionOfString[structIndex].t_array[index]);
        partitionOfString[structIndex].t_array[index][len++]=partitionOfString[structIndex].stack_operator[index];
        partitionOfString[structIndex].t_array[index][len]='\0';

        strcat(partitionOfString[structIndex].t_array[index], partitionOfString[structIndex].t_array[index1]);
        strcpy(partitionOfString[structIndex].t_array[index1], partitionOfString[structIndex].t_array[index]);

    partitionOfString[structIndex].stack_operator[index]='\0';
    partitionOfString[structIndex].func_derivative[index][0]='\0';
    return;
}


int check_visit(int visit[], int index, int arraysize){
    int i;
    for(i=0;i<arraysize;i++){
        if(index==visit[i])return 0;
    }
    return 1;
}


int nodevisit(int visit[], int index, int arraysize){
    int i;
    int index1=index;
    int next;

    for(i=0;i<arraysize;i++){
        if(index==visit[i]){
                if(index==1)break;
            index=nodevisit(visit, index-1, arraysize);
            break;
        }
    }
    if(index==1 && visit[0]==1){
        for(i=1;i<arraysize;i++){
            if(visit[i]!=i && index1!=i)return i;
        }
        return arraysize+1;
    }

    return index;
}


void func_precedence_implement(int index){
    int i;
    int visited[100];
    int j=2,countvisited=0;
    int k=0;
    char op1, op2;
    int size= partitionOfString[index].countArray;


    for(i=1;i<size;){
            if(i==j)j++;
            else if(i>j)j=i+1;

             op1=partitionOfString[index].stack_operator[i];
             op2=partitionOfString[index].stack_operator[j];
        if(find_operator(op1)==6 && find_operator(op2)==6){
            i++;
        }
        if(i>=size || j>=size)break;

        else if(find_operator(op1)>=find_operator(op2)){
                //printf("visited: %d %d\n",i,j);
                //printf("de %s %s\n",partitionOfString[index].func_derivative[i],partitionOfString[index].func_derivative[j]);
            strcpy(partition.left_node,partitionOfString[index].t_array[i]);
            strcpy(partition.right_node,partitionOfString[index].t_array[i+1]);
            partition.oper=partitionOfString[index].stack_operator[i];
                //printf("sending it %d  %s %s\n",size, partition.left_node,partition.right_node);
                oper_action(i,j,index);
            partition.left_node[0]='\0';
            partition.right_node[0]='\0';

            if(check_visit(visited, i, countvisited)==1)visited[countvisited++]=i;
                //printf("noh %d\n",visited[countvisited-1]);

            qsort(visited, countvisited, sizeof(int), cmpfunc);
            //for(int p=0;p<=countvisited; p++)printf("previsit %d ",visited[p]);

            j=visited[countvisited-1]+1;
            i=nodevisit(visited, i, countvisited);

        }
        else{
            i++;
        }
    }

}

void take_input(char *input){
    //strcpy(input,"d/dx(3*sinx-ln2)");
    //strcpy(input,"d/dx(10+x/tanx*sinx+lnx+x-5*x)");
    //char input[]={"(10+x)*(log(tanx)+3-(x^x)^x)"};
   //char input[]={"5*sinx+3"};
    //char input[]={"sin(x^x)+secx"};
    gets(input);
    //strcpy(input,"d/dx(d/dx(d/dx(-10 * x^122 + logx + x^x^ tanx - 3 * e^x + sinx)))");
    //strcpy(input,"d/dx( x* (sin(log(x^5)))^ln(x)  + x^3 + x^x^x - 45 * ((tanx)*x) ^ 9+2*(sin(cos(-3*x+7*tanx)))+(tanx)^5+7*x^2-x+x-5*(tanx)^5)");
    return;
}


void remove_space(char *input){
    int i,j=0;
    char space=' ';
    char temp[M];

    for(i=0;i<strlen(input);){
            if(input[i]==space)i++;
        temp[j++]=input[i++];
    }
    temp[j]='\0';
    strcpy(input,temp);
    return;
}


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

void bracket_handle(char *input) {
    int i,j=0;
    int b_start=0;
    int b_end=0 ;

    for(i=0;i<strlen(input);i++){
               if(input[i]=='('){
                    b_start++;
               }
               else if(input[i]==')'){
                    b_end++;
               }
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

void displayInputRequest(){
    printf("Enter the function with order of differentiation:\n(i.e.for one order of derivative: d/dx(f(x)))\n");
}

void rulebook(){
    char input[M];
    numberOfStack=0;
    max=0;

    displayInputRequest();
    take_input(input);
    remove_space(input);
    printf("%s",input);

    int order= n_order_diff(input);
    printf("\nOrder of differentiation: %d\n\n",order);

    delete_order(input,order);
    bracket_handle(input);

    while(order>0){
        int rootArray[100],notRootArray[100], arraysize,size;
        int i,j,k;
        chain_rule_implementation(input);

   arraysize= find_if_it_is_root(rootArray, notRootArray);
   for(i=0;i<arraysize;i++){
        stack_building(partitionOfString[rootArray[i]].t_array[0],rootArray[i]);
        size=partitionOfString[rootArray[i]].countArray;
        partitionOfString[rootArray[i]].stack_operator[size]='.';
        for(int k=0;k<size;k++)derivativeOfFunction(rootArray[i],k);
        //for(j=1;j<size;j++)printf("%d\t%s\t%c\t%s\n",rootArray[i],partitionOfString[rootArray[i]].t_array[j], partitionOfString[rootArray[i]].stack_operator[j], partitionOfString[rootArray[i]].func_derivative[j]);
        func_precedence_implement(rootArray[i]);

        for(j=1;j<size;j++){
            if(strcmp(input,partitionOfString[rootArray[i]].t_array[j])==0)
                printf("%s\n",partitionOfString[rootArray[i]].func_derivative[j]);
        }
   }
    for(i=max-arraysize;i>=0;i--){
        stack_building_nonRoot(partitionOfString[notRootArray[i]].t_array[0],notRootArray[i]);
        size=partitionOfString[notRootArray[i]].countArray;
        for(j=size-1;j>0;j--){
                if(strstr(partitionOfString[notRootArray[i]].t_array[j],"(")==NULL)derivativeOfFunction(notRootArray[i],j);
                else{
                    derivativeOfFunctionOfNonRoot(notRootArray[i], max, j);
                    strcpy(partitionOfString[notRootArray[i]].func_derivative[j],partitionOfString[notRootArray[i]].func_derivative[j]);
                }
            //printf("non %d,%d\t%s\t%c\t%s\n",notRootArray[i],j,partitionOfString[notRootArray[i]].t_array[j], partitionOfString[notRootArray[i]].stack_operator[j], partitionOfString[notRootArray[i]].func_derivative[j]);
        }
            for(j=1;j<size;j++){
                    if(strcmp(input,partitionOfString[rootArray[i]].t_array[j])==0)
                    printf("no %s\n",partitionOfString[notRootArray[i]].func_derivative[j]);
            }
        }

        order--;
    }

}

int main(void){
   rulebook();

}
