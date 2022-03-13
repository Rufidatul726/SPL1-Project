#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>


void take_input(char[]);
void remove_space(char[]);
int n_order_diff(char[]);
void delete_order(char[], int);
void functions(char[]);
void implementation_sum_rule(char[]);
void func_intro(char[], int );
char * power_Func(char[]);
int check_digit(char[]);
char *Pow_diff(char[], int);
void part(char[], char[], int, int );
void find_coeff(char[]);
void simplification(char[]);
 void insert(char [], char [], int);
 
 
int main(void){
    char input[100000];

    int i;

    take_input(input);

    remove_space(input);

    printf("%s",input);

    int order= n_order_diff(input);
    printf("\nOrder of differentiation: %d\n\n",order);

    delete_order(input,order);

    printf("  %s\n",input);
    
    simplification(input);
    printf(" uwu %s\n",input);

    for(i=0;i<order;i++){
        implementation_sum_rule(input);

        printf("\n\n%s\n",input);
        
        
    }

    
}


void take_input(char *a){
        //gets(a);
        //strcpy(a,"d/dx(d/dx(d/dx(10 * x^122 + logx + x^x^ tanx - 3 * e^x + ln(sinx))))");
        strcpy(a,"d/dx(10* x^3 + x^5 - 45 * (tanx) ^ 9)+x^2+2*x+(tanx)^5+log(tan(5*x+2))+5*x-(tanx)^5+7*x^2-x+x-5*(tanx)^5)");
        return;
}


void remove_space(char *a){
    int i,j=0;
    char space=' ';
    char s[100000];

    for(i=0;i<strlen(a);){
            if(a[i]==space)i++;
        s[j++]=a[i++];
    }
    s[j]='\0';
    strcpy(a,s);

    return;
}

int n_order_diff(char *a){
        int i=0, count=0;

        for(i=0;i<strlen(a);i++){
            if(a[i]=='d' && a[i+1]=='/' && a[i+2]=='d' && a[i+3]=='x'){
                    count++;
                    i=i+2;
                    }
        }
        return count;

}

void delete_order(char *a, int n){
    int i;
    
    int x=4+(n-1)*5+1;

    for(i=0;i<strlen(a)-n-x;i++){
        a[i]=a[i+x];
    }
    a[i]='\0';
}

char *power_Func(char *a){
        int power;
        char *r;
        char *left;
        static char right[1000][1000];
        int i=0;
        int flag=0;

        for(int i=0;i<strlen(a);i++){
            if(a[i]=='^'){
                flag=1;
                break;
            }
        }

        if(flag==0)return a;

        left = strtok(a, "^");

        while(left!=NULL){
            strcpy(right[i],left);
            //printf("%s\n",right[i]);
            i++;

            left = strtok(NULL, "^");
        }
        int count=i;
        for(i=count-1;i>=0;i--){
            power= check_digit(right[i]);
            if(right[i]>0 && i!=0){
                    r=Pow_diff(right[i-1],power);
            }
        }

        return r;
}

void implementation_sum_rule(char *a){
        char r1[1000];
        char *r;
        char rest[1000], rest1[1000];
        static char out[10000][100];
        out[0][0]='+';
        int i=0,j=1,count=0;
        int from_where=0;

        for(i=0;i<=strlen(a);i++){
            if(a[i]=='+' || a[i]=='-' || a[i]=='\0' ){
                out[count][j]='\0';
                printf("=>");
                 r=power_Func(out[count]);

                find_coeff(r);
                strcat(r1,r);
                 printf("%s ",r1);
                 part(a, rest,i,strlen(a));
                printf("%s\n", rest);
                    count++;
                    j=0;
                    from_where=i;

            }
            out[count][j++]=a[i];
        }

        strcpy(a,r1);
        r=NULL;
        r1[0]='\0';

}


int check_digit(char *a){
    int ch=0;

    if(a[0]>47 && a[0]<58)ch=atoi(a);

    return ch;
}

char *Pow_diff(char *what_to_differentiate, int power){
    int j;
    int changed_power=power-1;
    int len_main=strlen(what_to_differentiate);
    char str[1000],chn_str[1000];

    sprintf(str, "%d" , power);
    sprintf(chn_str, "%d", changed_power);

    static char result[1000][1000];


    for(int i=len_main;i>=0;i--){

        if(what_to_differentiate[i-1]=='*'  ||
            what_to_differentiate[i-1]=='/'  ||
            what_to_differentiate[i-1]=='+'  ||
            what_to_differentiate[i-1]=='-'  ||
            what_to_differentiate[i-1]=='^'  ||
            i==0){
                part(what_to_differentiate, result[0],0,i-1);
                part(what_to_differentiate, result[1],i,len_main);
                    break;
            }
    }

    strcat(result[0],str);
    strcat(result[0],"*");
    strcat(result[0], result[1]);
    if(power!=2){
        strcat(result[0],"^");
        strcat(result[0],chn_str);
    }

    return result[0];
}

void part(char *from, char *to, int start, int end){
        int i, j=0;
        for(i=start;i<=end;){
            to[j++]=from[i++];
        }
        to[j]='\0';
}

void find_coeff(char *from){
        int i,j=0;
        int count=0;
        int where_to_part[1000]={0};
        int part_end[1000]={0};
        int coeff[50]={0};
        char str[1000][1000];

        for(i=0;i<strlen(from);i++){
            if((from[i-1]=='+'  || from[i-1]=='-'  || from[i-1]=='*'  ||   from[i-1]=='/')  && (from[i]> 47 && from[i]<58)){
                for(j=i;j<strlen(from);j++){
                    coeff[count]=coeff[count]*10+from[j]-48;
                    from[j]='`';                                                                                            //remove the coeffs
                    if(from[j+1]<48 || from[j+1]>57){
                            where_to_part[count]=i;
                            if(from[i-1]=='*')coeff[count]=coeff[count-1]*coeff[count];
                            if(from[i-1]=='/')coeff[count]=coeff[count-1]/coeff[count];
                             i=i+j;
                             part_end[count]=j;
                            count++;
                            break;
                    }
                }
            }
        }

        sprintf(str[0], "%d" , coeff[count-1]);

        if(count==0){
                strcpy(from, from);
                return;
        }

        part(from, str[1], 0, where_to_part[0]-1);
        part(from, str[2], part_end[count-1]+1 , strlen(from));

        strcat(str[1], str[0]);
        strcat(str[1],str[2]);

        strcpy(from, str[1]);

}      


 void insert(char *from, char *insert_string, int pos){
        char x[1000];
        int i, j=0;
        for(i=0;i<pos;i++){
            x[i]=from[i];
        }
        for(i=pos;i<strlen(insert_string)+pos;i++){
            x[i]=insert_string[i-pos];
        }
        
        for(i=pos+strlen(insert_string);i<strlen(from)+strlen(insert_string);i++){
            x[i]=from[i-strlen(insert_string)];
        }
        x[i]='\0';
                    
        strcpy(from, x);
}


void simplification(char *a) {
       int i,j=1,k=0;
    int count=0;
               
    //parting in substring to compare
    char part[1000][1000];
    part[0][0]='+';
    for(i=0;i<strlen(a);i++){
         part[count][j++]=a[i];
        if(a[i+1]=='+' || a[i+1]=='-'  || a[i+1]=='\0'){
               //printf("%s ",part[count]);
            count++;
            j=0;
        }
    }
    
      //Normalizing
    char temp[5]={"1*"};
    for(i=0;i<count;i++){
        if(part[i][1]<='0' || part[i][1]>='9'){
            insert(part[i],temp,1);
        }
        //printf("Norm %s\n", part[i]);
    }
    
    //finding coefficient
    char coefficient[1000][100]={'0'};
    int coeff[10000];
    for(i=0;i<count;i++){
        for(j=0;j<strlen(part[i]);j++){
            coefficient[i][k++]=part[i][j];
            if((part[i][j+1]<48|| part[i][j+1]>57)){
                    k=0;
                    break;}
        }
        //printf("%s\t",coefficient[i]);
        coeff[i]=atoi(coefficient[i]);
        //printf("%d\n",coeff[i]);
    }
    
    //simplifying
   char nocoeff[1000][100];
    
    for(i=0;i<count;i++){
        k=0;
        for(j=strlen(coefficient[i]);j<strlen(part[i]);j++){
            nocoeff[i][k++]=part[i][j];
        }
        //printf("%s\n", nocoeff[i]);
    }
    
    //comparing
    int val=0;
    int value[1000]={0};
    for(i=0;i<count;i++){
        if(nocoeff[i][0]=='\0')continue;
        for(j=i+1;j<count;j++){
            val= strcmp(nocoeff[i], nocoeff[j]);
            //printf("%s,%s\n",nocoeff[i], nocoeff[j]);
            if(val==0){
                coeff[i]=coeff[i]+coeff[j];
                nocoeff[j][0]='\0';
            }
            sprintf(coefficient[i], "%d", coeff[i]);
            if(coeff[i]==0){
                coefficient[i][0]='\0';
                nocoeff[i][0]='\0';
            }
        }
    }
    
    
    char temparray[100][100];
    j=0;
    int countagain=0;
    for(i=0;i<count;i++){
        if(nocoeff[i][0]=='\0' ){
            countagain++;
            continue;
        }
        
        strcpy(temparray[j],coefficient[i]);
        strcat(temparray[j++],nocoeff[i]);
        nocoeff[i][0]='\0';
    }
    j=0;
     a[0]='\0';
    strcat(a,temparray[0]);

    for(i=0;i<count-countagain;i++){
              if(temparray[j][0]!='-')strcat(a,"+");
        strcat(a, temparray[j]);
        strcpy(nocoeff[i],temparray[j++]);
        //printf("%s ",nocoeff[i]);
    }

}


void functions(char *input){
    char func[100][100]={
                            {"ln"},{"log"},{"sin"},{"cos"},{"cosec"},{"tan"},{"sec"},{"cot"},
                            {"arcsin"},{"arccos"},{"arccosec"},{"arctan"},{"arcsec"},{"arccot"}
    };
    char var='x';
    char oper[100][10]={
                            {"+"},{"-"},{"*"},{"/"},{"^"},
    };
    char stack_pop[100]={"....."};


    //find function
    int length=strlen(input);
    int k=0;
    char temp_for_push[1000][100];
    
    for(int i=0;i<length;i++){
        for(int j=0;j<strlen(func[k]);j++){
            if(input[i]!=func[j]){
                k++;
                break;
            }
        }
    }
}



