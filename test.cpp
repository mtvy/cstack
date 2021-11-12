#include "cstack.h"

int main()
{
    CStack stack;
    stack_ctor(&stack);

    STACK_PRINT_CANARY
    STACK_PRINT(stack.capacity, stack.data)

    stack_push(&stack, 8);
    STACK_PRINT(stack.capacity, stack.data)
    
    stack_push(&stack, -2);
    STACK_PRINT(stack.capacity, stack.data)
    
    stack_push(&stack, 3);

    stack_push(&stack, 3);

    stack_push(&stack, 3);

    stack_push(&stack, 3);

    stack_push(&stack, -234);

    stack_push(&stack, 123);

    stack_push(&stack, 44);

    stack_push(&stack, 3);

    STACK_PRINT(stack.capacity, stack.data)

    stack_pop(&stack, &stack.data[stack.capacity - 1]);

    STACK_PRINT(stack.capacity, stack.data)
    
    stack_push(&stack, 3);

    stack_dtor(&stack);

    return 0;
}
