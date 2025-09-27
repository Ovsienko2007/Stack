#include "stack.h"

int main(){
    stack_t stack = {};
    init_stack(&stack);

    for (int i = 0; i < 16; i++){
        pop_stack(&stack);
    }

    return 0;
}