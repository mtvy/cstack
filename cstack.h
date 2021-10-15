//=================================================================================================================
//           [$ Date: 10.10.2021 $]
//
//           [If RUSSIAN CHARS below are UNREADABLE, check this file codepage. It should be CP1251, or UTF-8 etc.]
//=================================================================================================================
//!
//! @mainpage 
//!          
//! @copyright  (C) Mtvy (Matvei Prudnikov)
//! @author     Telegram <@mtvyp>
//! @date     
//!
//! @note     
//!
//! @warning  
//!
//! @file     
//!
//! @brief    
//!
//=================================================================================================================

#ifndef CHRLIB_HEADER_INCLUDE
#define CHRLIB_HEADER_INCLUDE

#include <stdio.h>
#include <stdlib.h>


typedef int STACK_DATA_TYPE;

typedef unsigned long long STACK_CANARY_TYPE;

const STACK_CANARY_TYPE STACK_BEGIN_CANARY = 0xABC0C0DE;
const STACK_CANARY_TYPE STACK_END_CANARY   = 0xABC1C0DE;


enum STACK_STATUS
{
    STACK_NULL ,
    STACK_WORKS,
    STACK_WRONG,
};

enum STACK_CONSTS
{
    STACK_INIT_CAPACITY_CONST = 2,
};

struct CStack
{
    STACK_DATA_TYPE *data;

    size_t capacity;
    size_t item_size;
};

STACK_STATUS stack_ctor(CStack *stack);

STACK_STATUS stack_dtor(CStack *stack);

STACK_STATUS stack_push(CStack *stack, int* item);

STACK_STATUS stack_pop (CStack *stack, STACK_DATA_TYPE* item);

STACK_STATUS stack_dump(CStack *stack);

STACK_STATUS stack_dumpToStream(CStack *stack, FILE *out);

STACK_STATUS stack_reallocate(CStack *stack, size_t capacity);

STACK_STATUS stack_healthCheck(CStack *stack); 


#endif // CHRLIB_HEADER_INCLUDE
