#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STANDART_DUMP(stack, error) show_dump(stack, error, error_position {__FILE__, __FUNCTION__,  __LINE__}, standart_mod)
#define USER_DUMP(stack, error)  show_dump(stack, error, error_position {__FILE__, __FUNCTION__,  __LINE__}, user_mod)

enum error_t{
    no_error                = 0,
    null_stack_ptr          = 1,
    null_data_ptr           = 2,
    capacity_less_then_zero = 3,
    size_less_then_zero     = 4,
    capacity_less_then_size = 5,
    size_zero               = 6,
    not_null_data_ptr       = 7,
    left_canary_death       = 8,
    right_canary_death      = 9
};

enum verify_mod{
    standart        = 0,
    check_null_size = 1,
    init_mod        = 2
};

enum dump_mod{
    standart_mod    = 0,
    user_mod        = 2,
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

struct dump_colors{
    const char  *red;
    const char  *yellow;
    const char  *blue;
    const char  *pirple;
    const char  *reset;
};

const int bird = 0xDEADBEEF;

const int startStackSize = 16;

int init_stack(stack_t *stack, error_t *error = NULL);

int destroy_stack(stack_t *stack, error_t *error = NULL);

void push_stack(stack_t *stack, stackElemType new_elem, error_t *error = NULL);

stackElemType pop_stack(stack_t *stack, error_t *error = NULL);

void show_dump(stack_t *stack, error_t error, error_position error_pos, dump_mod mod);

void print_error(error_t error, FILE *stream = stdout);

#endif