#include "custom_stack.h"

int main()
{
    CStack stack;
    stack_ctor(&stack);
    printf(
        "|*Data Value After Push Canary*    \n"
        "|                         left: %llu\n"
        "|                        right: %llu \n"
        "|                     left_ptr: %p    \n"
        "|                    right_ptr: %p     \n"
        "|                  int_0_value: %d      \n"
        "|                  int_1_value: %d       \n"
        "|-----------------------------------------\n",
          stack.data[0],   stack.data[1], 
          stack.data[0],   stack.data[1],
          stack.data[0],   stack.data[1]
          );
    return 0;
}