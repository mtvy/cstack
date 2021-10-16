#include "cstack.h"

int main()
{
    CStack stack;
    
    stack_ctor(&stack);

    STACK_PRINT_CANNY

    return 0;
}
