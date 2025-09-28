#include "stack.h"

int main(){
    stack_t stack = {};
    init_stack(&stack);

    for (int i = 0; i < 2; i++){
        push_stack(&stack, i);
    }
    USER_DUMP(&stack, no_error);

    for (int i = 0; i < 3; i++){
        pop_stack(&stack);
    }

    destroy_stack(&stack);

    return 0;
}