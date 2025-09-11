typedef struct State {
    char * regs [256];
} State;

#include "core.h"

void echo_0(State *state) {
    printf("ECHO: \n");
}

void echo_1 (State *state, char *arg0) {
    printf("ECHO: %s\n", arg0);
}

void echo_2 (State *state, char *arg0, char *arg1) {
    printf("ECHO: %s|%s\n", arg0, arg1);
}

void echo_3 (State *state, char *arg0, char *arg1, char *arg2) {
    printf("ECHO: %s|%s|%s\n", arg0, arg1, arg2);
}

void print_1 (State *state , char *idx) {
    if (state->regs[atoi(idx)] != NULL) {
        printf("%s\n", state->regs[atoi(idx)]);
    }
}

void printregs_0 (State *state) {
    for (int i = 0; i < 256; i++) {
        if (state->regs[i] != NULL) {
            printf("%d = %s\n", i, state->regs[i]);
        }
    }
}

void store_2 (State *state, char *idx, char *what) {
    free(state->regs[atoi(idx)]);
    state->regs[atoi(idx)] = (char*)malloc(strlen(what) + 1);
    strcpy(state->regs[atoi(idx)], what);
}

void copy_2 (State *state, char *dst, char *src) {
    if (atoi(dst) == atoi(src)) return;
    free(state->regs[atoi(dst)]);
    state->regs[atoi(dst)] = (char*)malloc(strlen (state->regs[atoi(src)]) + 1);
    strcpy(state->regs[atoi(dst)], state->regs[atoi(src)]);
}

void clear_1 (State *state, char *idx) {
    state->regs[atoi(idx)] = NULL;
}