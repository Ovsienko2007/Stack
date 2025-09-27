#include "stack.h"

int main(){
    stack_t stack = {};
    init_stack(&stack);

    for (int i = 0; i < 16; i++){
        push_stack(&stack, i);
        DUMP(&stack, no_error);
    }
    
    return 0;
}