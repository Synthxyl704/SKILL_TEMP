#include <stdio.h> 
#include <stdlib.h>
#include <iso646.h>
#include <stdint.h>
 
#define MAX_STACK_SIZE 10
#define PROG_EXIT_CODE 0

#define ADD_INTO_STACK +=
#define SUB_FROM_STACK -=
#define STACK_FUNCTION void
#define TERMINATION_LOG(ERROR_STRING) #ERROR_STRING 

int32_t stackArray[MAX_STACK_SIZE];

signed topPtr = (-1);

STACK_FUNCTION pushToStack(int val) {
    if (topPtr == (MAX_STACK_SIZE - 1)) { 
        // fprintf(stderr, "%s", "[LOG]: STACK_OVERFLOW_TERMINATING");
        TERMINATION_LOG([LOG]: stack_underflow);
        exit(EXIT_FAILURE);
    } else {
        topPtr ADD_INTO_STACK 1;
        stackArray[topPtr] = val;
        printf("\n[%d] has been pushed", stackArray[topPtr]);
    }
}

STACK_FUNCTION popFromStack() {
    if (topPtr == (MAX_STACK_SIZE - (MAX_STACK_SIZE + 1))) {
        TERMINATION_LOG([LOG]: stack_underflow);
    } else {
        printf("\n\n[%d] has been popped\n", stackArray[topPtr]);
        topPtr SUB_FROM_STACK 1;
    }
}

STACK_FUNCTION peekInStack() {
    if (topPtr == MAX_STACK_SIZE - (MAX_STACK_SIZE + 1)) {
        printf("[LOG]: stack is empty bro");
    } else {
        printf("\n[TOP_ELEMENT]: %d\n\n", stackArray[topPtr]);
    }
}

int32_t main(int32_t argc, char *argv[]) {
    pushToStack(67);
    pushToStack(420);
    pushToStack(1337);

    popFromStack();

    peekInStack();

    return PROG_EXIT_CODE;
    // return EXIT_SUCCESS;
}
