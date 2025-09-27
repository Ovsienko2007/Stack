#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef CONSOLE_OUTPUT

#define CONSOLE_RED        "\033[31m"
#define CONSOLE_YELLOW     "\033[33m"
#define CONSOLE_BLUE       "\033[34m"
#define CONSOLE_PIRPLE     "\033[35m"
#define CONSOLE_RESET      "\033[39m"

#else 

#define CONSOLE_RED        ""
#define CONSOLE_YELLOW     ""
#define CONSOLE_BLUE       ""
#define CONSOLE_PIRPLE     ""
#define CONSOLE_RESET      ""

#endif

#define DUMP(stack, error) print_dump(stack, error, error_position {__FILE__, __FUNCTION__,  __LINE__})

enum error_t{
    no_error                = 0,
    null_stack_ptr          = 1,
    null_data_ptr           = 2,
    capacity_less_then_zero = 3,
    size_less_then_zero     = 4,
    capacity_less_then_size = 5,
    size_zero               = 6,
    not_null_data_ptr       = 7
};

enum verify_mod{
    standart        = 0,
    check_null_size = 1,
    init_mod        = 2
};

struct error_position{
    const char *file;
    const char *func;
    int line;
};

typedef int stackElemType;

struct stack_t{
    int size;
    int capacity;
    stackElemType *data;
};

const int bird = 0xDEADBEEF;

const int startStackSize = 16;

int init_stack(stack_t *stack, error_t *error = NULL);

int destroy_stack(stack_t *stack, error_t *error = NULL);

void push_stack(stack_t *stack, stackElemType new_elem, error_t *error = NULL);

stackElemType pop_stack(stack_t *stack, error_t *error = NULL);

void print_dump(stack_t *stack, error_t error, error_position error_pos);

#endif