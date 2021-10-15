#include "custom_stack.h"


STACK_STATUS stack_ctor(CStack *stack)
{
    stack->capacity = stack->item_size = STACK_NULL;
    
    stack->data = (STACK_DATA_TYPE*) malloc(2 * sizeof(STACK_DATA_TYPE));

    *(STACK_CANARY_TYPE*)   stack->data                  = STACK_BEGIN_CANARY;
    *(STACK_CANARY_TYPE*) ( stack->data + sizeof(char) ) = STACK_END_CANARY  ;

    return STACK_WORKS;
}   