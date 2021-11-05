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

#include <nmmintrin.h>


typedef int STACK_DATA_TYPE;

typedef unsigned long long STACK_CANARY_TYPE;

typedef unsigned long long int HASH_TYPE;

const STACK_CANARY_TYPE STACK_BEGIN_CANARY  = 0xCA0C0DE1;
const STACK_CANARY_TYPE STACK_END_CANARY    = 0xCA0C0DE2;

const size_t STACK_NUMBER_POISON = -8;



enum STACK_STATUS
{
    STACK_INVALID,
    STACK_VALID  ,
};

enum STACK_CONSTS
{
    STACK_NULL     ,
    STACK_PICK_NEXT,
    STACK_INIT_NUM ,
};

enum STACK_POISON
{
    STACK_DATA_POISON = 666,
};


struct CStack
{
    STACK_DATA_TYPE *data     ;
    STACK_STATUS     status   ;
    HASH_TYPE        hash     ;
    size_t           capacity ;
    size_t           item_size;
};

HASH_TYPE sumHash(void *ptr, size_t size, HASH_TYPE hash);

void stack_calculate_hash(CStack *stack);

STACK_STATUS stack_is_valid(void *ptr);

STACK_STATUS stack_check_health(CStack *stack);

STACK_STATUS stack_put_canary(CStack *stack, size_t bytes, STACK_CANARY_TYPE SIDE_CANARY);

STACK_STATUS stack_dump(CStack *stack, FILE *log_file, const int line, const char* file, const char* stack_name);

STACK_STATUS stack_reallocate(CStack *stack, size_t capacity);

STACK_STATUS stack_ctor(CStack *stack);

STACK_STATUS stack_dtor(CStack *stack);

STACK_STATUS stack_push(CStack *stack, int item);

STACK_STATUS stack_pop (CStack *stack, STACK_DATA_TYPE* item);


#define STACK_DUMP (stack, file) stack_dump (stack, file, __LINE__, __FILE__, #stack_name);

#define STACK_PRINT_CANARY  printf(                 \
        "|*Data Value After Push Canary*            \n"    \
        "|                     left_ptr: %p         \n"    \
        "|                    right_ptr: %p         \n"    \
        "|                  int_0_value: %d         \n"    \
        "|                             +---> %p     \n|\n" \
        "|                  int_1_value: %d         \n"    \
        "|                             +---> %p     \n|\n" \
        "|                  int_2_value: %d         \n"    \
        "|                             +---> %p     \n|\n" \
        "|                  int_3_value: %d         \n"    \
        "|                             +---> %p     \n|\n" \
        "|                  int_4_value: %d         \n"    \
        "|                             +---> %p     \n|\n" \
        "|                  int_5_value: %d         \n"    \
        "|                             +---> %p     \n|\n" \
        "|                  int_6_value: %d         \n"    \
        "|                             +---> %p     \n|\n" \
        "|                  int_7_value: %d         \n"    \
        "|                             +---> %p     \n"    \
        "|-------------------------------------------------\n",\
                            stack.data[0],   stack.data[1],    \
                            stack.data[0],   stack.data[0],    \
                            stack.data[1],   stack.data[1],    \
                            stack.data[2],   stack.data[2],    \
                            stack.data[3],   stack.data[3],    \
                            stack.data[4],   stack.data[4],    \
                            stack.data[5],   stack.data[5],    \
                            stack.data[6],   stack.data[6],    \
                            stack.data[7],   stack.data[7]     \
                                  );                           \


#endif // CSTACK_HEADER_INCLUDE
