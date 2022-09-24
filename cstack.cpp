#include "cstack.h"


HASH_TYPE sumHash(void *ptr, size_t size, HASH_TYPE hash = 0)
{
    HASH_TYPE *copy_ptr = (HASH_TYPE*) ptr;

    for (size_t i = 0; i < size; i++)
    {
        hash += *(copy_ptr + i);
    }

    return hash;
}


void stack_calculate_hash(CStack *stack)
{
    stack->hash = sumHash( &( stack->data     ), sizeof( &stack->data     ));
    stack->hash = sumHash( &( stack->capacity ), sizeof( &stack->capacity ));
    stack->hash = sumHash( &( stack->item_size), sizeof( &stack->item_size));
    stack->hash = sumHash( &( stack->status   ), sizeof( &stack->status   ));
}


STACK_STATUS stack_is_valid(void *ptr)
{
    if ( ptr == NULL || ptr == (STACK_DATA_TYPE*) STACK_NULL ) return STACK_INVALID;
    
    return STACK_VALID;
}


STACK_STATUS stack_check_health(CStack *stack)
{
    return STACK_VALID;
}


STACK_STATUS stack_put_canary(CStack *stack, size_t bytes, STACK_CANARY_TYPE SIDE_CANARY)
{
    return stack_is_valid( &(*(STACK_CANARY_TYPE*) (stack->data + bytes) = SIDE_CANARY) );
}


STACK_STATUS stack_dump(CStack *stack, FILE *log, const char* func, const int line, const char *file, const char *item)
{   
    assert (stack);
    assert (func);
    assert (file);
    assert (item);

    unsigned int error_code = stack_is_valid(stack);
    
    if (error_code == STACK_VALID)
    {
        fprintf(log, "\nSTACK [OK]: ");
    }

    else
    {
        fprintf(log, "\nSTACK [ERROR][ERR_CODE: %X]", error_code);
    }

    fprintf(log, "[%p]\n Dump for \"%s\" called in function "
	         "%s, line %d, file \"%s\"\n\n"
	         "\t{\n\titem_size = %lu \n"
                      "\tcapacity  = %lu \n"
                      "\thash_sum  = %llX\n"
                 "\t}\n", &stack->data, item, func, line, file, 
	         stack->item_size, stack->capacity, stack->hash
	   );

    return stack_is_valid(stack);
}


STACK_STATUS stack_reallocate(CStack *stack, size_t capacity)
{ 
    STACK_DATA_TYPE *dup_data = stack->data;
    
    stack->data = (STACK_DATA_TYPE*) calloc( capacity, sizeof(STACK_DATA_TYPE) );
    
    for (int index = 0; index < stack->item_size; index++)
    {
        stack->data[index] = *dup_data;
        dup_data++;
    }

    return stack_is_valid(stack);
}


STACK_STATUS stack_ctor(CStack *stack)
{
    stack->item_size = stack->hash = STACK_NULL;

    stack_reallocate(stack, STACK_INIT_NUM);

    stack_put_canary(stack, STACK_NULL     , STACK_BEGIN_CANARY);
    stack_put_canary(stack, STACK_PICK_NEXT, STACK_END_CANARY  );

    stack->capacity = stack->item_size = STACK_INIT_NUM;

    stack_calculate_hash(stack);

    return stack_is_valid(stack);
}


STACK_STATUS stack_dtor(CStack *stack)
{
    stack_is_valid    (stack);
    stack_check_health(stack);
    
    stack->capacity = stack->item_size = STACK_NUMBER_POISON;

    free(stack->data);

    stack->data = (STACK_DATA_TYPE*) STACK_NULL;

    return stack_is_valid(stack);
}


STACK_STATUS stack_push(CStack *stack, int item)
{
    stack_is_valid(stack);

    if ( stack_check_health(stack) == STACK_INVALID ) return stack->status;

    if ( stack->item_size == stack->capacity )
    {
        stack->status = stack_reallocate(stack, stack->capacity++);
    }

    stack->data[stack->item_size - 1] = (STACK_DATA_TYPE) item;

    stack_put_canary(stack, stack->capacity - 1, STACK_END_CANARY);
    
    stack->item_size++;

    stack_calculate_hash(stack);

    return stack_is_valid(stack);
}


STACK_STATUS stack_pop (CStack *stack, STACK_DATA_TYPE *item)
{
    if ( stack_check_health(stack) == STACK_INVALID ) return stack->status;

    *item = stack->data[stack->capacity - 1];
    stack->data[stack->capacity] = STACK_DATA_POISON;

    stack->capacity-- ;
    stack->item_size--;

    return stack_is_valid(stack);
}


int UnitTest()
{   
    CStack stack = {};
    FILE* log = fopen ("stack.txt", "wa+");

    stack_ctor(&stack);
    STACK_DUMP(&stack, log)
    
    printf ("STACK HASH: %llX\n", stack.hash);

    STACK_PRINT(stack.capacity, stack.data)
    
    stack_push(&stack, 8);
    stack_push(&stack, 2);
    stack_push(&stack, 4);
    stack_push(&stack, 9);

    STACK_PRINT(stack.capacity, stack.data)

    stack_pop(&stack, &stack.data[stack.item_size - 2]);
    stack_pop(&stack, &stack.data[stack.item_size - 2]);
    stack_pop(&stack, &stack.data[stack.item_size - 2]);
    
    STACK_PRINT(stack.capacity, stack.data)
    
    STACK_DUMP(&stack, log)
    stack_dtor(&stack);

    return 0;
}
