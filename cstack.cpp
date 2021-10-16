#include "cstack.h"

STACK_STATUS stack_is_valid(void *ptr)
{
    if ( ptr == NULL ) return STACK_INVALID;
    
    return STACK_VALID;
}

STACK_STATUS stack_check_health(CStack *stack)
{
    return STACK_VALID;
}

STACK_STATUS stack_put_canary(CStack *stack, STACK_CONSTS BYTES, STACK_CANARY_TYPE SIDE_CANARY)
{
    return stack_is_valid( &(*(STACK_CANARY_TYPE*) (stack->data + BYTES) = SIDE_CANARY) );
}

STACK_STATUS stack_reallocate(CStack *stack, size_t capacity)
{
    return stack_is_valid( stack->data = (STACK_DATA_TYPE*) malloc(capacity * sizeof(STACK_DATA_TYPE)) );
}

STACK_STATUS stack_ctor(CStack *stack)
{
    stack->capacity = stack->item_size = STACK_NULL;
    
    stack_reallocate(stack, STACK_INIT_CAPACITY   );
    
    stack_put_canary(stack, STACK_NULL     , STACK_BEGIN_CANARY);
    stack_put_canary(stack, STACK_PICK_NEXT, STACK_END_CANARY  );

    return stack_is_valid(stack);
}

STACK_STATUS stack_dtor(CStack *stack)
{
    stack_is_valid    (stack);
    stack_check_health(stack);
    
    stack->capacity = stack->item_size = STACK_NUMBER_POISON;

    /*

    
    

    if (!ptrValid(this_->dataWrapper)) {
        fprintf(this_->logStream, "ERROR: pointer to the data is invalid!\n");
        return STACK_BAD_DATA_PTR;
    }

    free(this_->dataWrapper);
    
    this_->dataWrapper = (STACK_CANARY_TYPE*)STACK_FREED_PTR;
    this_->data        = (STACK_TYPE*)STACK_FREED_PTR;

    return STACK_HEALTH_CHECK(this_);
    */
}

/*
static bool ptrValid(const void* ptr)         
{
    if (ptr == NULL) {
        return false;
    }

    #ifdef STACK_USE_PTR_POISON
        if ((size_t)ptr>>4 == (size_t)STACK_BAD_PTR_MASK) {           
            return false;
        }
    #endif  
    
    #ifdef STACK_USE_PTR_SYS_CHECK
        #ifdef __unix__
            size_t page_size = sysconf(_SC_PAGESIZE);
            void *base = (void *)((((size_t)ptr) / page_size) * page_size);
            return msync(base, page_size, MS_ASYNC) == 0;
         #else 
            #ifdef _WIN32
                MEMORY_BASIC_INFORMATION mbi = {};
                if (!VirtualQuery(ptr, &mbi, sizeof (mbi)))
                    return false;

                if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
                    return false;  // Guard page -> bad ptr
    
                DWORD readRights = PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY
                    | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
    
                return (mbi.Protect & readRights) != 0;
            #else
                fprintf(stderr, "WARNING: your OS is unsupported, system pointer checks are diabled!\n");
            #endif
       #endif
    #endif

    return true;
}
*/
