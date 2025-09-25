#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef CONSOLE

#define CONSOLE_RED        "\033[31m"
#define CONSOLE_YELLOW     "\033[33m"
#define CONSOLE_RESET      "\033[39m"

#else 

#define CONSOLE_RED        ""
#define CONSOLE_YELLOW     ""
#define CONSOLE_RESET      ""

#endif


#define DUMP print_dump(NULL, no_error, error_position {__FILE__, __FUNCTION__,  __LINE__})

enum error_t{
    no_error = 0,
    null_ptr = 1,
    init_err = 2
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

const int startStackSize = 16;

int init_stack(stack_t *stack);

void push_stack(stack_t *stack, stackElemType new_elem);

stackElemType pop_stack(stack_t *stack);

error_t stack_verify(stack_t *stack);

void print_dump(stack_t *stack, error_t error, error_position error_pos);

#endif