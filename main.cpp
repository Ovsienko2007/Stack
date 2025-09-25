#include "stack.h"

int main(){
    stack_t stack = {};
    init_stack(&stack);

    for (int i = 0; i < 100; i++){
        push_stack(&stack, i);
    }

    printf("%d %d\n", stack.capacity, stack.size);

    for (int i = 0; i < 30; i++){
        printf("%d ", pop_stack(&stack));
    }

    printf("\n%d %d\n", stack.capacity, stack.size);
    
    return 0;
}