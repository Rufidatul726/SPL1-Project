#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define N 100000
#define M 1000

void rulebook();
void push(char, int);
char pop(int top);
int precedence(char);
int finding_const();

int find_operator(char);
int operator_name();
int parenthesis_recognition();
void take_input(char[]);
void remove_space(char[]);
int n_order_diff(char[]);
void delete_order(char[], int);
void bracket_handle(char[]);
int stack_building(char[]);
char **chain_rule(char[]);
char *string_minimization(char[], int, int);
void only_constant(char[], int);
void sine(char[], int);
void tangent(char[], int);
void logarithm(char[], int);
void exponential(char[], int);
void only_var_x(char[], int);
void find_function(int);
//char constant(int index);

struct stack{
    char *left_node;
    char *right_node;
    char oper;

};

struct constant{

    int the_const[M];
    int position[M];
}constant;

struct parenthesis_position{
    int stackstart[M];
    int stackend[M];
	int b_no;
}string;

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

    int size= stack_building(input);
    find_function(size);

    for(int i=0;i<size;i++){
        printf("%s\t%c\t%s\n", partitionOfString.t_array[i], partitionOfString.stack_operator[i], partitionOfString.func_derivative[i]);
    }

}

int precedence(char sign){
	if(sign == '^') return 3;
    else if(sign == '*' || sign == '/') return 2;
    else if(sign == '+' || sign == '-') return 1;
    else return 0;
}

int finding_const(int size){
    int i;
    int j;

    for(i=0;i<size;i++){
        if(partitionOfString.t_array[i][0]>='0' && partitionOfString.t_array[i][0]<='9'){
            constant.the_const[j]= atoi(partitionOfString.t_array[i]);
            constant.position[j]=i;
            j++;
        }

    }
    return j;

}

void take_input(char *input){
    //gets(input);
    strcpy(input,"d/dx(d/dx(d/dx(-10 * x^122 + logx + x^x^ tanx - 3 * e^x + sinx)))");
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
                partitionOfString.countArray[count]=i;
                partitionOfString.stack_operator[count]=input[i];
                count++;
               // i++;
                p=0;
            }

            else partitionOfString.t_array[count][p++]=input[i];

           if(input[i+1]=='('){
                for(;;){
                     partitionOfString.t_array[count][p++]=input[++i];

                     if(input[i]=='(')bracket++;
                     else if(input[i]==')')bracket--;
                        if(bracket==0)break;

                }
                //partitionOfString.countArray[count]=i;
                  sign = find_operator(input[i+1]);
                if(sign!=0){
                    partitionOfString.countArray[count]=i;
                    partitionOfString.stack_operator[count]=input[i+1];
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
                     partitionOfString.countArray[count]=i;
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

int find_operator(char sign){
	if(sign == '^') return 5;
    else if(sign == '*') return 4;
    else if(sign == '/') return 3;
    else if(sign == '+') return 2;
    else if(sign == '-') return 1;
    else return 0;
}


void find_function(int count){
    int i,j,k;
    char *func_names[] = {
                            "ln","log","sin","cos","cosec","tan","sec","cot",
                            "arcsin","arccos","arccosec","arctan","arcsec","arccot",
                            "lnx","logx","sinx","cosx","cosecx","tanx","secx","cotx",
                            "arcsinx","arccosx","arccosecx","arctanx","arcsecx","arccotx",
                            "x"
    };

    for(i=0;i<count;i++){
            //if(strcmp(func[j],partitionOfString.t_array[i])==0)
            if((partitionOfString.t_array[i][0]>47 && partitionOfString.t_array[i][0]<58)  ||   partitionOfString.t_array[i][0]=='+' || partitionOfString.t_array[i][0]=='-'){
                //int val= atoi(partitionOfString.t_array[i]);
                only_constant(partitionOfString.t_array[i],i);
            }
            if(strcmp("sinx",partitionOfString.t_array[i])==0){
                sine(partitionOfString.t_array[i], i);
                //strcpy(partitionOfString.func_derivative[i],sine(partitionOfString.t_array[i]));
               // strcpy(partitionOfString.func_derivative[i],"sinx");
            }

            else  if(strcmp("tanx",partitionOfString.t_array[i])==0){
                tangent(partitionOfString.t_array[i], i);
            }

            else  if(strcmp("logx",partitionOfString.t_array[i])==0){
                logarithm(partitionOfString.t_array[i], i);
            }

            else  if(strcmp("x",partitionOfString.t_array[i])==0){
                only_var_x(partitionOfString.t_array[i], i);
            }
            else  if(strcmp("e",partitionOfString.t_array[i])==0){
                exponential(partitionOfString.t_array[i], i);
            }

           /* else  if(strcmp("tanx",partitionOfString.t_array[i])==0){
                //strcpy(partitionOfString.func_derivative[i],sine(partitionOfString.t_array[i]));
                strcpy(partitionOfString.func_derivative[i],"(secx)^2");
            }
            else  if(strcmp("logx",partitionOfString.t_array[i])==0){
                //strcpy(partitionOfString.func_derivative[i],sine(partitionOfString.t_array[i]));
                strcpy(partitionOfString.func_derivative[i],"lna/x");
            }
            else  if(strcmp("lnx",partitionOfString.t_array[i])==0){
                //strcpy(partitionOfString.func_derivative[i],sine(partitionOfString.t_array[i]));
                strcpy(partitionOfString.func_derivative[i],"1/x");
            }*/

    }
}



void sine(char* input_part, int index){
    strcpy(partitionOfString.func_derivative[index],"cosx");
}

void logarithm(char *input_part, int index){
    strcpy(partitionOfString.func_derivative[index],"lna/x");
    //*partitionOfString.func_derivative[index]="1/(lna*(......))";
}

void tangent(char *input_part, int index){
    strcpy(partitionOfString.func_derivative[index],"(secx)^2");
    //*partitionOfString.func_derivative[index]="(secx)^2";
}

void only_var_x(char *input_part, int index){
    partitionOfString.func_derivative[index][0]='1';
}

void only_constant(char *input_part, int index){
    partitionOfString.func_derivative[index][0]='0';
}

void exponential(char *input_part, int index){
    strcpy(partitionOfString.func_derivative[index],"e^x");
}

void cosine(char *input_part){
    char *temp="-sin(......)";
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

