#include "stack.h"

static void print_error(error_t error, FILE *stream)  __attribute__((unused));

static error_t stack_verify(stack_t *stack, verify_mod check_type = standart);

int init_stack(stack_t *stack, error_t *error){
    if (stack_verify(stack, init_mod)){
        if (error){
            *error = stack_verify(stack);
        }
        DUMP(stack, stack_verify(stack));
        return 1;
    }
    
    *stack = {
        .size = 0,
        .capacity = startStackSize - 2,
        .data = (stackElemType *)calloc(startStackSize, sizeof(stackElemType))
    };

    stack->data[0] = bird;
    stack->data[startStackSize - 1] = bird;

    if (stack_verify(stack)){
        if (error){
            *error = stack_verify(stack);
        }
        DUMP(stack, stack_verify(stack));
        return 1;
    }

    return 0;
}

int destroy_stack(stack_t *stack, error_t *error){
    if (stack_verify(stack)){
        if (error){
            *error = stack_verify(stack);
        }
        DUMP(stack, stack_verify(stack));
        return 1;
    }

    free(stack->data);
    stack->data     = NULL;
    stack->size     = 0;
    stack->capacity = 0;

    return 0;
}

void push_stack(stack_t *stack, stackElemType new_elem, error_t *error){
    if (stack_verify(stack)){
        if (error){
            *error = stack_verify(stack);
        }
        DUMP(stack, stack_verify(stack));
        return;
    }

    stack->data[stack->size + 1] = new_elem;
    stack->size++;

    if (stack->size == stack->capacity){
        stack->capacity *= 2;
        stackElemType *new_data = (stackElemType *)realloc(stack->data, (2 + stack->capacity) * sizeof(stackElemType));
        stack->data = new_data;
        stack->data[stack->capacity + 1] = bird;
    }

    if (stack_verify(stack)){
        if (error){
            *error = stack_verify(stack);
        }
        DUMP(stack, stack_verify(stack));
        return;
    }
}

stackElemType pop_stack(stack_t *stack, error_t *error){
    if (stack_verify(stack, check_null_size)){
        if (error){
            *error = stack_verify(stack);
        }
        DUMP(stack, stack_verify(stack));
        return 0;
    }

    stack->size--;

    if (stack_verify(stack)){
        if (error){
            *error = stack_verify(stack);
        }
        DUMP(stack, stack_verify(stack));
        return 0;
    }
    return stack->data[stack->size];
}

void print_dump([[maybe_unused]] stack_t *stack, [[maybe_unused]] error_t error,
                [[maybe_unused]] error_position error_pos){
#ifdef SHOW_DUMP
#ifdef CONSOLE_OUTPUT
    FILE *stream = stdout;
#else 
    FILE *stream = fopen("dump.txt", "a");
#endif
    setbuf(stdout, NULL);

    static int nam_call = 0;
    nam_call++;

    if (stream == NULL) return;

    fprintf(stream, CONSOLE_RED "StackDump called from %s:%d from func %s\n" CONSOLE_RESET,
           error_pos.file, error_pos.line, error_pos.func);
    fprintf(stream , CONSOLE_YELLOW "The %d call\n" CONSOLE_RESET, nam_call);

    fprintf(stream, CONSOLE_RED "Error: ");
    print_error(error, stream);
    fprintf(stream, "%s", CONSOLE_RESET);

    if (stack != NULL){
        fprintf(stream, "Stack [0x%p]{\n", stack);

        fprintf(stream, "  size:     %d\n", stack->size);
        fprintf(stream, "  capacity: %d\n", stack->capacity);
        fprintf(stream, "  data [0x%p]{\n" , stack->data);

        for (int stack_position = 0; stack_position < stack->capacity + 2; stack_position++){
            if (stack_position == 1){
                fprintf(stream, "%s", CONSOLE_BLUE);
            }
            if (stack_position == stack->size + 1){
                fprintf(stream, "%s", CONSOLE_PIRPLE);
            }
            if (stack_position == 0 || stack_position == stack->capacity + 1){
                fprintf(stream, "%s", CONSOLE_YELLOW);
                fprintf(stream, "      [bird]\t %#12X\n", stack->data[stack_position]);
            }
            else if (stack_position < stack->size + 1){
                fprintf(stream, "    * [%d]\t %12d\n", stack_position - 1, stack->data[stack_position]);
            }
            else{
                fprintf(stream, "      [%d]\t %12d (poision)\n", stack_position - 1, stack->data[stack_position]);
            }
        }

        fprintf(stream, CONSOLE_RESET "   }\n}\n");
    }

#ifndef CONSOLE_OUTPUT
    fclose(stream);
#endif
#endif
}

static void print_error(error_t error, FILE *stream){
    if (stream == NULL) return;

    switch (error){
        case no_error:
            fprintf(stream, "No error\n");
            break;
        case null_stack_ptr:
            fprintf(stream, "Null stack ptr\n");
            break;
        case null_data_ptr:
            fprintf(stream, "Null data ptr\n");
            break;
        case capacity_less_then_zero:
            fprintf(stream, "Capacity less then zero\n");
            break;
        case size_less_then_zero:
            fprintf(stream, "Size less then zero\n");
            break;
        case capacity_less_then_size:
            fprintf(stream, "Capacity less then size\n");
            break;
        case size_zero:
            fprintf(stream, "Zero size\n");
            break;
        case not_null_data_ptr:
            fprintf(stream, "not null data ptr");
        default:
            break;
    }
}

static error_t stack_verify(stack_t *stack, verify_mod check_type){
    if (stack == NULL)                                          return null_stack_ptr;

    if (check_type == init_mod){
        if (stack->data != NULL)                                return not_null_data_ptr;
    } else{
        if (stack->capacity <= 0)                               return capacity_less_then_zero;
        if (stack->size < 0)                                    return size_less_then_zero;
        if (stack->size >= stack->capacity)                     return capacity_less_then_size;
    }

    if (check_type == check_null_size && stack->size == 0)  return size_zero;

    return no_error;
}