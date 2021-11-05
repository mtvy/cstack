#include "cstack.h"

int main()
{
    CStack stack;
    stack_ctor(&stack);

    STACK_PRINT_CANARY

    stack_push(&stack, 8);
    
    STACK_PRINT_CANARY
    
    stack_push(&stack, -2);
    
    STACK_PRINT_CANARY

    stack_pop(&stack, &stack.data[1]);

    STACK_PRINT_CANARY
    
    stack_push(&stack, 3);

    STACK_PRINT_CANARY

    stack_dtor(&stack);

    return 0;
}
