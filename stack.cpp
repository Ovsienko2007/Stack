#include "stack.h"

static error_t stack_verify(stack_t *stack, verify_mod check_type = standart);

static void print_dump(FILE *stream, stack_t *stack,
                       error_t error, error_position error_pos, dump_colors colors) __attribute__((unused));

static void del_colors_input(dump_colors *colors) __attribute__((unused));
static void add_colors_input(dump_colors *colors) __attribute__((unused));

int init_stack(stack_t *stack, error_t *error){
    if (error){
        *error = stack_verify(stack, init_mod);
    }
    if (stack_verify(stack, init_mod)){
        STANDART_DUMP(stack, stack_verify(stack, init_mod));
        return 1;
    }
    
    *stack = {
        .size = 0,
        .capacity = startStackSize - 2,
        .data = (stackElemType *)calloc(startStackSize, sizeof(stackElemType))
    };

    stack->data[0] = bird;
    stack->data[startStackSize - 1] = bird;

    if (error){
        *error = stack_verify(stack);
    }
    if (stack_verify(stack)){
        STANDART_DUMP(stack, stack_verify(stack));
        return 1;
    }

    return 0;
}

int destroy_stack(stack_t *stack, error_t *error){
    if (error){
        *error = stack_verify(stack);
    }
    if (stack_verify(stack)){
        STANDART_DUMP(stack, stack_verify(stack));
        return 1;
    }

    free(stack->data);
    stack->data     = NULL;
    stack->size     = 0;
    stack->capacity = 0;

    return 0;
}

void push_stack(stack_t *stack, stackElemType new_elem, error_t *error){
    if (error){
        *error = stack_verify(stack);
    }
    if (stack_verify(stack)){
        STANDART_DUMP(stack, stack_verify(stack));
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

    if (error){
        *error = stack_verify(stack);
    }
    if (stack_verify(stack)){
        STANDART_DUMP(stack, stack_verify(stack));
        return;
    }
}

stackElemType pop_stack(stack_t *stack, error_t *error){
    if (error){
        *error = stack_verify(stack, check_null_size);
    }
    if (stack_verify(stack, check_null_size)){
        STANDART_DUMP(stack, stack_verify(stack, check_null_size));
        return 0;
    }

    stack->size--;

    if (error){
        *error = stack_verify(stack);
    }
    if (stack_verify(stack)){
        STANDART_DUMP(stack, stack_verify(stack));
        return 0;
    }
    return stack->data[stack->size + 1];
}

void show_dump([[maybe_unused]] stack_t *stack, [[maybe_unused]] error_t error,
                [[maybe_unused]] error_position error_pos, [[maybe_unused]] dump_mod mod){
    bool show_dump = false;

#ifdef SHOW_DUMP
    show_dump = true;
#endif

    if (mod == user_mod || show_dump){
        FILE *stream = stdout;
        dump_colors colors = {};
        add_colors_input(&colors);

        if (!isatty(STDOUT_FILENO)) {
            del_colors_input(&colors);
        }

#ifndef CONSOLE_OUTPUT
        if (mod == standart_mod){
            stream = fopen("dump.txt", "a");
            del_colors_input(&colors);
        }
#endif
        setbuf(stream, NULL);
        print_dump(stream, stack, error, error_pos, colors);

#ifndef CONSOLE_OUTPUT
        if (mod == standart_mod){
            fclose(stream);
        }
#endif
    }
}

static void print_dump(FILE *stream, stack_t *stack, error_t error, error_position error_pos, dump_colors colors){
    static int nam_call = 0;
    nam_call++;

    if (stream == NULL) return;

    fprintf(stream, "%sStackDump called from %s:%d from func %s\n%s",
           colors.red, error_pos.file, error_pos.line, error_pos.func, colors.reset);
    fprintf(stream , "%sThe %d call\n%s", colors.yellow, nam_call, colors.reset);
    if (error != no_error){
        fprintf(stream, "%sError: ", colors.red);
        print_error(error, stream);
        fprintf(stream, "%s", colors.reset);
    }

    if (stack != NULL){
        fprintf(stream, "Stack [0x%p]{\n", stack);

        fprintf(stream, "  size:     %d\n", stack->size);
        fprintf(stream, "  capacity: %d\n", stack->capacity);
        
        if (stack->data != NULL){
            fprintf(stream, "  data [0x%p]{\n" , stack->data);

            for (int stack_position = 0; stack_position < stack->capacity + 2; stack_position++){
                if (stack_position == 1){
                    fprintf(stream, "%s", colors.blue);
                }
                if (stack_position == stack->size + 1 || stack->size < 0){
                    fprintf(stream, "%s", colors.pirple);
                }
                if (stack_position == 0 || stack_position == stack->capacity + 1){
                    fprintf(stream, "%s", colors.yellow);
                    fprintf(stream, "      [canary]\t %#12X\n", stack->data[stack_position]);
                }
                else if (stack_position < stack->size + 1){
                    fprintf(stream, "    * [%d]\t %12d\n", stack_position - 1, stack->data[stack_position]);
                }
                else{
                    fprintf(stream, "      [%d]\t %12d (poision)\n", stack_position - 1, stack->data[stack_position]);
                }
            }
            fprintf(stream, "%s   }\n", colors.reset);
        }
        fprintf(stream, "}\n");
    }
}

static void del_colors_input(dump_colors *colors){
    colors->red    = "";
    colors->yellow = "";
    colors->blue   = "";
    colors->pirple = "";
    colors->reset  = "";
}

static void add_colors_input(dump_colors *colors){
    colors->red    = "\033[31m";
    colors->yellow = "\033[33m";
    colors->blue   = "\033[34m";
    colors->reset  = "\033[39m";
    colors->pirple = "\033[35m";
}

void print_error(error_t error, FILE *stream){
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
            fprintf(stream, "not null data ptr\n");
            break;
        case left_canary_death:
            fprintf(stream, "The left canary was killed!\n");
            break;
        case right_canary_death:
            fprintf(stream, "The right canary was killed!\n");
            break;
        default:
            break;
    }
}

static error_t stack_verify(stack_t *stack, verify_mod check_type){
    if (stack == NULL)                                          return null_stack_ptr;

    if (check_type == init_mod){
        if (stack->data != NULL)                                return not_null_data_ptr;
    } else{
        if (stack->data == NULL)                                return null_data_ptr;
        if (stack->capacity <= 0)                               return capacity_less_then_zero;
        if (stack->size < 0)                                    return size_less_then_zero;
        if (stack->size >= stack->capacity)                     return capacity_less_then_size;
        if (stack->data[0] != bird)                             return left_canary_death;
        if (stack->data[stack->capacity + 1] != bird)           return right_canary_death;
    }

    if (check_type == check_null_size && stack->size == 0) return size_zero;

    return no_error;
}