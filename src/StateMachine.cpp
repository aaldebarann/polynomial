#include "StateMachine.h"

StateMachine::StateMachine(int start_state) {
    current_state = start_state;
}

void StateMachine::Move(char c) {
    switch (c) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            current_state = v1[current_state];
            break;
        case '+':
        case '-':
            current_state = v2[current_state];
            break;
        case '*':
            current_state = v3[current_state];
            break;
        case '^':
            current_state = v4[current_state];
            break;
        case 'x':
            current_state = v5[current_state];
            break;
        case 'y':
            current_state = v6[current_state];
            break;
        case 'z':
            current_state = v7[current_state];
            break;
        case ',':
        case '.':
            current_state = v8[current_state];
            break;
        default:
            break;
    }
}