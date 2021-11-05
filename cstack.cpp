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

STACK_STATUS stack_dump(CStack *stack, FILE *log_file, const int line, const char* file, const char* stack_name)
{
    //
    
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

    free(dup_data);

    return stack_is_valid(stack);
}

STACK_STATUS stack_ctor(CStack *stack)
{
    stack->capacity = stack->item_size = stack->hash = STACK_NULL;

    stack->data = {};

    stack_reallocate(stack, stack->capacity);

    stack->capacity = stack->item_size = STACK_INIT_NUM;

    stack_put_canary(stack, STACK_NULL     , STACK_BEGIN_CANARY);
    stack_put_canary(stack, STACK_PICK_NEXT, STACK_END_CANARY  );

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
        stack->capacity = stack->capacity + 2;
        stack->status   = stack_reallocate(stack, stack->capacity);
    }

    stack->data[stack->item_size - 1] = (STACK_DATA_TYPE) item;

    stack_put_canary(stack, stack->capacity, STACK_END_CANARY);
    
    stack->item_size++;

    stack_calculate_hash(stack);

    return stack_is_valid(stack);
}

STACK_STATUS stack_pop (CStack *stack, STACK_DATA_TYPE* item)
{
    if ( stack_check_health(stack) == STACK_INVALID ) return stack->status;

    *item = stack->data[--stack->item_size];
    stack->data[stack->item_size] = STACK_DATA_POISON;

    return stack_is_valid(stack);
}

/*



*/



/*


static stack_status stack_dumpToStream(const stack *this_, FILE *out)
{
    STACK_PTR_VALIDATE(this_);

    fprintf(out, "%s\n", STACK_LOG_DELIM);
    fprintf(out, "| Stack [%p] :\n", this_);
    fprintf(out, "|----------------\n");

    fprintf(out, "| Current status = %d\n", this_->status); 
    if (this_->status & STACK_BAD_STRUCT_PTR)
        fprintf(out, "| Bad self ptr \n");
    if (this_->status & STACK_BAD_MEM_ALLOC)
        fprintf(out, "| Bad memory allocation \n");
    if (this_->status & STACK_INTEGRITY_VIOLATED)
        fprintf(out, "| Stack integrity violated \n");
    if (this_->status & STACK_DATA_INTEGRITY_VIOLATED)
        fprintf(out, "| Data integrity violated \n");
    if (this_->status & STACK_LEFT_STRUCT_CANARY_CORRUPT)
        fprintf(out, "| Left structure canary corrupted \n");
    if (this_->status & STACK_RIGHT_STRUCT_CANARY_CORRUPT)
        fprintf(out, "| Right structure canary corrupted \n");
    if (this_->status & STACK_LEFT_DATA_CANARY_CORRUPT)
        fprintf(out, "| Left data canary corrupted \n");
    if (this_->status & STACK_RIGHT_DATA_CANARY_CORRUPT)
        fprintf(out, "| Right data canary corrupted \n");
    if (this_->status & STACK_BAD_STRUCT_HASH)
        fprintf(out, "| Bad structure hash, stack may be corrupted \n");
    if (this_->status & STACK_BAD_DATA_HASH)
        fprintf(out, "| Bad data hash, stack data may be corrupted \n");
    if (this_->status & STACK_BAD_CAPACITY)
        fprintf(out, "| Bad capacity, capacity value differs from the allocated one\n");

    size_t capacity = this_->capacity;
    #ifdef STACK_USE_CAPACITY_SYS_CHECK
        if (this_->status & STACK_BAD_CAPACITY) {
            capacity = stack_getRealCapacity(this_->dataWrapper);
            if (capacity == STACK_SIZE_T_POISON) {
                capacity = this_->capacity;
            }
        }
    #endif
 
    if (STACK_VERBOSE >= 1) {
        fprintf(out, "|----------------\n");
        fprintf(out, "| Capacity         = %zu\n", this_->capacity);
        #ifdef STACK_USE_CAPACITY_SYS_CHECK
            fprintf(out, "| Real capacity    = %zu\n", capacity);
        #endif
        fprintf(out, "| Len              = %zu\n", this_->len);
        fprintf(out, "| Data wrapper ptr = %p\n",  this_->dataWrapper);
        fprintf(out, "| Data ptr         = %p\n",  this_->data);
        fprintf(out, "| Elem size        = %zu\n", sizeof(STACK_TYPE));
        #ifdef STACK_USE_STRUCT_HASH
            fprintf(out, "| Struct hash      = %zu\n", this_->structHash);
        #endif
        #ifdef STACK_USE_DATA_HASH
            fprintf(out, "| Data hash        = %zu\n", this_->dataHash);
        #endif
        fprintf(out, "|   {\n");

        #ifdef STACK_USE_CANARY                    //TODO read about graphviz 
            for (size_t i = 0; i < STACK_CANARY_WRAPPER_LEN; ++i) {                 
                    fprintf(out, "| l   %llx\n", LEFT_CANARY_WRAPPER[i]);           // `l` for left canary
            }
        #endif
        
        size_t cap = fmin(this_->len, capacity);          // in case structure is corrupt and len > capacity

        for (size_t i = 0; i < cap; ++i) {
                fprintf(out, "| *   %d\n", this_->data[i]);      //TODO add generalized print // `*` for in-use cells
        }

        bool printAll = true;
    
        
        #ifdef STACK_USE_POISON
            if (capacity == this_->capacity) {
                printAll = false;
                for (size_t i = this_->len; i < capacity; ++i) {
                    if (!stack_isPoisoned(&this_->data[i]))
                        printAll = true;
                }
            }
        #endif  
        

        if (capacity < this_->len)
            printAll = true;

        if (capacity - this_->len > 10 && !printAll) {                      // shortens outp of the same poison     
            fprintf(out, "|     %x\n", this_->data[this_->len]);
            fprintf(out, "|     %x\n", this_->data[this_->len]);
            fprintf(out, "|     %x\n", this_->data[this_->len]);
            fprintf(out, "|     ...\n");
            fprintf(out, "|     %x\n", this_->data[this_->len]);
            fprintf(out, "|     %x\n", this_->data[this_->len]);
        }
        else {
            for (size_t i = this_->len; i < capacity; ++i) {
                fprintf(out, "|     %x\n", this_->data[i]);
            }
        }
    
        #ifdef STACK_USE_CANARY             
            #ifdef STACK_USE_CAPACITY_SYS_CHECK
                for (size_t i = 0; i < STACK_CANARY_WRAPPER_LEN; ++i) {
                    fprintf(out, "| r   %llx\n", ((STACK_CANARY_TYPE*)((char*)this_->dataWrapper + STACK_CANARY_WRAPPER_LEN * sizeof(STACK_CANARY_TYPE) + capacity * sizeof(STACK_TYPE)))[i]);
                }
            #else
                for (size_t i = 0; i < STACK_CANARY_WRAPPER_LEN; ++i) {
                        fprintf(out, "| r   %llx\n", RIGHT_CANARY_WRAPPER[i]);  // `r` for right canary
                }
            #endif
        #endif

        fprintf(out, "|  }\n");
    }
    fprintf(out, "%s\n", STACK_LOG_DELIM);

    return this_->status;
}


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
