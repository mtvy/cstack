#include "cstack.h"

int main()
{
    CStack stack;
    
    stack_ctor(&stack);

    STACK_PRINT_CANARY

    printf("VALID? - %d\n", stack_dtor(&stack));

    return 0;
}
