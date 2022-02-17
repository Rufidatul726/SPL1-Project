#include<stdio.h>
#include<string.h>
#include<math.h>
#include<conio.h>

char *take_input(void);
int n_order_diff(char[]);

char *take_input(void){
     static char input[1000]="d/dx(d/dx(d/dx(10 * x^2 + logx + tanx - 3 * e^x + ln(sinx))))";
    //static char input[1000];
    //scanf("%[^\n ]",input);
    //gets(input);
    return input;
}

void remove_space(char *a){
    int i,j=0;
    char s[100000];

    for(i=0;i<strlen(a);){
            if(a[i]==' ')i++;
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


int main(void){

    char *input= take_input();
    remove_space(input);

    printf("%s",input);

    int order= n_order_diff(input);
    printf("\nOrder of differentiation: %d\n",order);

    delete_order(input,order);

    printf("%s\n",input);
}
