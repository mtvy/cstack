//=================================================================================================================
//              [$ Date: 10.10.2021 $]
//=================================================================================================================
//!
//! @mainpage   cstack.h
//!          
//! @copyright  (C) Mtvy (Matvei Prudnikov)
//! @author     Telegram <@mtvyp>
//! @date       10.10.2021
//!
//! @note       Stack library 
//!
//! @file       cstack.h
//!
//=================================================================================================================

#ifndef CSTACK_HEADER_INCLUDE
#define CSTACK_HEADER_INCLUDE

#include <stdio.h>
#include <stdlib.h>


typedef int STACK_DATA_TYPE;

typedef unsigned long long STACK_CANARY_TYPE;

const STACK_CANARY_TYPE STACK_BEGIN_CANARY  = 0xABC0C0DE;
const STACK_CANARY_TYPE STACK_END_CANARY    = 0xABC1C0DE;

const STACK_DATA_TYPE   STACK_DELETE_POISON = 0xFFF; 
const size_t            STACK_NUMBER_POISON = -8   ;



enum STACK_STATUS
{
    STACK_INVALID,
    STACK_VALID  ,
};

enum STACK_CONSTS
{
    STACK_NULL         ,
    STACK_PICK_NEXT    ,
    STACK_INIT_CAPACITY,
};


struct CStack
{
    STACK_DATA_TYPE *data     ;
    size_t           capacity ;
    size_t           item_size;
};


STACK_STATUS stack_is_valid(void *ptr);

STACK_STATUS stack_check_health(CStack *stack);

STACK_STATUS stack_put_canary(CStack *stack, STACK_CONSTS BYTES, STACK_CANARY_TYPE SIDE_CANARY);

STACK_STATUS stack_ctor(CStack *stack);

STACK_STATUS stack_dtor(CStack *stack);

STACK_STATUS stack_push(CStack *stack, int* item);

STACK_STATUS stack_pop (CStack *stack, STACK_DATA_TYPE* item);

STACK_STATUS stack_dump(CStack *stack);

STACK_STATUS stack_dumpToStream(CStack *stack, FILE *out);

STACK_STATUS stack_reallocate(CStack *stack, size_t capacity);



#define STACK_PRINT_CANARY { printf(           \
        "|*Data Value After Push Canary*    \n" \
        "|                     left_ptr: %p  \n" \
        "|                    right_ptr: %p   \n" \
        "|                  int_0_value: %d    \n" \
        "|                  int_1_value: %d     \n" \
        "|---------------------------------------\n",\
          stack.data[0],   stack.data[1],             \
          stack.data[0],   stack.data[1],              \
          stack.data[0],   stack.data[1]                \
                                   );                    \
                           }


#endif // CSTACK_HEADER_INCLUDE
