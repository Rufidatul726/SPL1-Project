#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define N 100000
#define M 1000

void rulebook();
int precedence(char);
int func_name(int, int);
int find_operator(char);
int find_bracket(char);
int operator_name();
int parenthesis_recognition();
void take_input(char[]);
void remove_space(char[]);
int n_order_diff(char[]);
void delete_order(char[], int);
void bracket_handle(char[]);
int functions(char[], int);
char **chain_rule(char[]); 
char *string_minimization(char[], int, int);

struct stack{
    char *left_node;
    char *right_node;
    char oper;

};


struct parenthesis_position{
    int stackstart[M];
    int stackend[M];
	int b_no;
}string;

struct part{
    int countArray[M];
    char t_array[M][M];
    char stack_operator[M];
}partitionOfString[M];

int main(void){
   rulebook();

}

void rulebook(){
    char input[M];
    char stack_push[M][100];

    take_input(input);
    remove_space(input);
    printf("%s",input);

    int order= n_order_diff(input);
    printf("\nOrder of differentiation: %d\n\n",order);

    delete_order(input,order);
    bracket_handle(input);

    int size= functions(input, 0);
    //size = func_name(size, 1);

    for(int i=0;i<size;i++){
        printf("%s\t%c\n", partitionOfString[0].t_array[i], partitionOfString[0].stack_operator[i]);
    }

}

int precedence(char sign)
{
	if(sign == '^') return 3;
    else if(sign == '*' || sign == '/') return 2;
    else if(sign == '+' || sign == '-') return 1;
    else return 0;
}

//finding nested structure
int func_name(int size, int index){
    int i=0,j,k=0;

   // for(i=0;;i++){
        for(k=0;k<size;k++){
            for(j=0;j<strlen(partitionOfString[i].t_array[k]);j++){
                if(partitionOfString[i].t_array[k][j]=='('){
                   size= functions(partitionOfString[i].t_array[k], i+1);
                  i++;
                  break;
                }
            }
        }
   // }
   return i;

}

void take_input(char *input){

    //gets(input);
    //strcpy(input,"d/dx(d/dx(d/dx(-10 * (-x)^122 + logx + x^x^ tanx - 3 * e^x + ln(sinx))))");
    strcpy(input,"d/dx( x* (sin(log(x^5)))^ln(x)  + x^3 + x^x^x - 45 * ((tanx)*x) ^ 9+2*(sin(cos(-3*x+7*tanx)))+(tanx)^5+7*x^2-x+x-5*(tanx)^5)");
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
                    string.stackstart[b_start]=i;
                    b_start++;
               }
               else if(input[i]==')'){
                    string.stackend[b_end]=i;
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

    string.b_no=b_start;

}

char **chain_rule(char *input){
	int i,j=0,k=0;
	char temp[M][M];


	for(i=0;i<string.b_no;i++){
		strcpy(temp[j],string_minimization(input, string.stackstart[string.b_no-i-1], string.stackend[0]));
		j++;
	}
}

int functions(char *input, int index){
    int i,j,count=0,p=0;
    int sign;
    int bracket =0;
   
   // char oper[50]={ "+-*^" };

    for(i=0;i<strlen(input);i++){
            sign = find_operator(input[i]);
            if(sign!=0){
                partitionOfString[index].countArray[count]=i;
                partitionOfString[index].stack_operator[count]=input[i];
                count++;
               // i++;
                p=0;
            }

            else partitionOfString[index].t_array[count][p++]=input[i];

           if(input[i+1]=='('){
                for(;;){
                     partitionOfString[index].t_array[count][p++]=input[++i];

                     if(input[i]=='(')bracket++;
                     else if(input[i]==')')bracket--;
                        if(bracket==0)break;

                }
                //partitionOfString.countArray[count]=i;
                  sign = find_operator(input[i+1]);
                if(sign!=0){
                    partitionOfString[index].countArray[count]=i;
                    partitionOfString[index].stack_operator[count]=input[i+1];
                    count++;
                    i++;
                    p=0;
                }
                //break;
            }
            /*if(input[i+1]==')'){
                partitionOfString.countArray[count]=i;
                count++;
                p=0;
                break;
            }*/
            if(i==strlen(input)-1){
                     partitionOfString[index].countArray[count]=i;
                     count++;
                    i++;
                    p=0;
            }

    }

    return count;

}

char *string_minimization(char *input, int start, int end){
    char *temp=malloc(sizeof(char)*100);

    for(int i=start;i<=end;i++){
        temp[i-start]=input[i];
    }
    temp[end]='\0';
    return temp;
}

int find_operator(char sign)
{
	if(sign == '^') return 5;
    else if(sign == '*') return 4;
    else if(sign == '/') return 3;
    else if(sign == '+') return 2;
    else if(sign == '-') return 1;
    else return 0;
}

int find_bracket(char sign)
{
	if(sign == '(') return 2;
    else if(sign == ')') return 1;
    else return 0;
}

/*

void find_bracket_to_stack(char *input, int N, char *temp[N]);{
    int i,k=0,j=0;
    //char temp[M][M];
    for(i=0;i<strlen(input);i++){
        temp[j][k++]=input[i];      //push
        if(input[i+1]=='('){
           j++;
           k=0;                     //split
        }
        if(input[i+1]==')'){
            j--;
        }
    }
}

void differentiate(char *part_from_bracket){
    int i,k=0,j=0;


}
*/
/*void partition(char *input, int start, int end){
    int i,j=0;

    for(i=start;i<strlen(input);i++){
        if(input[i+1]=='+' || input[i+1]=='-'  || input[i+1]=='\0')start_to_stack(input);
    }

}

void start_to_stack(char *input){
    int i,j=0;


}*/

/*char *sine(char *input_part){
    char *temp="cos(";
    return  temp;
}

char *cosine(char *input_part){
    char *temp="-sin(......)";
    return  temp;
}

char *tangent(char *input_part){
    char *temp="(sec(......)^2)";
    return  temp;
}

char *cosecant(char *input_part){
    char *temp="-cosec(......)*cot(......)";
    return  temp;
}

char *secant(char *input_part){
    char *temp="sec(......)tan(......)";
    return  temp;
}

char *cotanget(char *input_part){
    char *temp="(cosec(......))^2";
    return  temp;
}

char *ln(char *input_part){
    char *temp="1/(......)";
    return temp;
}

char *logarithm(char *input_part){
    char *temp="1/(lna*(......))";
    return temp;
}


*/
