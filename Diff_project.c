#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define N 100000
#define M 1000

void function();
void take_input(char[]);
void remove_space(char[]);
int n_order_diff(char[]);
void delete_order(char[], int);
void bracket_handle(char[]);
void functions(char[]);
void destroyArray(char[]);
char **chain_rule(char[]);
char *string_minimization(char[], int, int);
//void find_bracket_to_stack(char[], int, char[][]);
//void differentiate(char[]);
//void partition(char[], int , int );

struct parenthesis_position{
    int stackstart[M];
    int stackend[M];
	int b_no;
}string;



int main(void){
   function();

}

void function(){
    char input[M];
    char stack_push[M][100];

    take_input(input);
    remove_space(input);
    printf("%s",input);

    int order= n_order_diff(input);
    printf("\nOrder of differentiation: %d\n\n",order);

    delete_order(input,order);
    bracket_handle(input);

    printf("=>%s\n",input);

    //find_bracket_to_stack(input, M, stack_push);
    for(int i=0;i<100;i++){
        printf("%s\n", stack_push[i]);
    }

    //partition(input, 0, strlen(input));
}

void take_input(char *input){

    //gets(input);
    //strcpy(input,"d/dx(d/dx(d/dx(10 * x^122 + logx + x^x^ tanx - 3 * e^x + ln(sinx))))");
    strcpy(input,"d/dx(10* x^3 + x^5 - 45 * (tanx) ^ 9+x^2+2*x+(tanx)^5+log(tan(5*x+2))+5*x-(tanx)^5+7*x^2-x+x-5*(tanx)^5)");
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
	destroyArray(temp);

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


void functions(char *input){
    char func[50][20]={
                            {"ln"},{"log"},{"sin"},{"cos"},{"cosec"},{"tan"},{"sec"},{"cot"},
                            {"arcsin"},{"arccos"},{"arccosec"},{"arctan"},{"arcsec"},{"arccot"}
    };
    char var='x';
    char oper[50][5]={
                            {"+"},{"-"},{"*"},{"/"},{"^"},
    };


}

char **chain_rule(char *input){
	int i,j=0,k=0;
	char temp[M][M];


	for(i=0;i<string.b_no;i++){
		strcpy(temp[j],string_minimization(input, string.stackstart[string.b_no-i-1], string.stackend[0]));
		j++;
	}
}

char *string_minimization(char *input, int start, int end){
    char *temp=(int*)malloc(sizeof(char)*100);

    for(int i=start;i<=end;i++){
        temp[i-start]=input[i];
    }
    temp[end]='\0';
    return temp;
}


void destroyArray(char* arr)
{
    //free(*arr);
    free(arr);
}

/*void stack()

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
