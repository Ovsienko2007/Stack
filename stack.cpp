#include "stack.h"

static void print_error(error_t error, FILE *stream);

int init_stack(stack_t *stack){
    if (stack == NULL) return 1;
    
    *stack = {
        .size = 0,
        .capacity = startStackSize,
        .data = (stackElemType *)calloc(startStackSize, sizeof(stackElemType))
    };

    if (stack == NULL) return 1;

    return 0;
}

void push_stack(stack_t *stack, stackElemType new_elem){
    if (stack == NULL) return;

    stack->data[stack->size] = new_elem;
    stack->size++;

    if (stack->size == stack->capacity){
        stack->capacity *= 2;
        stackElemType *new_data = (stackElemType *)realloc(stack->data, stack->capacity * sizeof(stackElemType));
        stack->data = new_data;
    }

    if (stack == NULL) return;
}

stackElemType pop_stack(stack_t *stack){
    if (stack == NULL) return 1;

    stack->size--;

    return stack->data[stack->size];
}

error_t stack_verify(stack_t *stack){
    if (stack == NULL) return null_ptr;
    return no_error;
}

void print_dump(stack_t *stack, error_t error, error_position error_pos){
#ifdef CONSOLE
    FILE *stream = stdout;
#else 
    FILE *stream = fopen("dump.txt", "a");
#endif

    if (stream == NULL) return;
    fprintf(stream, CONSOLE_RED "StackDump called from %s:%d from func %s\n" CONSOLE_RESET,
           error_pos.file, error_pos.line, error_pos.func);
    print_error(error, stream);

    if (stack != NULL){
        return;
    }

#ifndef CONSOLE
    fclose(stream);
#endif
}

static void print_error(error_t error, FILE *stream){
    if (stream == NULL) return;

    switch (error){
        case no_error:
            fprintf(stream, "No error\n");
            break;
        case init_err:
            fprintf(stream, "Initialization error\n");
            break;
        case null_ptr:
            fprintf(stream, "Null ptr\n");
            break;
        default:
            break;
    }
}