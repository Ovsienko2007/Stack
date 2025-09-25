#include "stack.h"

int main(){
    stack_t stack = {};
    init_stack(&stack);

    for (int i = 0; i < 2; i++){
        push_stack(&stack, i);
    }

    printf("%d %d\n", stack.capacity, stack.size);

    for (int i = 0; i < 3; i++){
        printf("%d ", pop_stack(&stack));
    }
    
    return 0;
}