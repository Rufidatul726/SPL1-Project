#include"main.h"

void function(){
    char input[100000];

    take_input(input);
    remove_space(input);
    printf("%s",input);

    int order= n_order_diff(input);
    printf("\nOrder of differentiation: %d\n\n",order);

    delete_order(input,order);
    bracket_handle(input);

    printf("=>%s\n",input);

    //partition(input, 0, strlen(input));
}
