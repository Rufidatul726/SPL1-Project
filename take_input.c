#include"main.h"

void take_input(){
    char input[10000];
        //gets(a);
        //strcpy(a,"d/dx(d/dx(d/dx(10 * x^122 + logx + x^x^ tanx - 3 * e^x + ln(sinx))))");
        strcpy(input,"d/dx(10* x^3 + x^5 - 45 * (tanx) ^ 9)");
        
    remove_space(input);
    printf("%s\n",input);
        
    int order= n_order_diff(input);
    printf("\nOrder of differentiation: %d\n\n",order);
        
    delete_order(input,order);    
    
    printf("%s\n",input);
}
