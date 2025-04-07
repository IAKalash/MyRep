#include "decls.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h> 
    
    //prints ’ECHO: ’ and all passed strings separated by ’|’

static int parseidx(const char *idx){
    return atoi(idx);
}

void echo_0(State *state){
    printf("ECHO: \n");
}

void echo_1(State *state , char *arg0){
    printf("ECHO: %s\n",arg0);
}

void echo_2(State *state , char *arg0 , char *arg1){
    printf("ECHO: %s|%s",arg0,arg1);
}

void echo_3(State *state , char *arg0 , char *arg1 , char *arg2){
    printf("ECHO: %s|%s|%s\n",arg0,arg1,arg2);
}

//prints contents of I-th register (it must not be NULL)
    //[idx] contains decimal representation of I
void print_1(State *state , char *idx){
    int i = parseidx(idx);
    if (i>=0 && i<256 && state->regs[i]!=NULL){
        printf("%s\n",state->regs[i]);
    }
}

//prints all non-NULL registers with their values (sorted by register number)
void printregs_0(State *state){
    for(int i = 0; i< 256;i++){
        if(state->regs[i]!=NULL){
            printf("%d = %s\n",i,state->regs[i]);
        }
    }
}

//saves a copy of string [what] into I-th register
//[idx] contains decimal representation of I
void store_2(State *state , char *idx , char *what){
    int i = parseidx(idx);
    if (i>=0 && i<256){
        free(state->regs[i]);
        state->regs[i]=(char *)malloc(strlen(what)+1);
        strcpy(state->regs[i],what);
    }
}
    


//copies contents of S-th register into D-th register (S-th register is not NULL)
//[dst] and [src] contain decimal representations of D and S respectively
//BEWARE: [dst] and [src] are allowed to be equal indices
void copy_2(State *state , char *dst , char *src){
    int d = parseidx(dst);
    int s = parseidx(src);

    if(d==s){
        return;
    }

    free(state->regs[d]);
    state->regs[d]=(char *)malloc(strlen(state->regs[s])+1);
    strcpy(state->regs[d],state->regs[s]);
    
}

//assigns NULL to I-th register
//[idx] contains decimal representation of I
void clear_1(State *state , char *idx){
    int i = parseidx(idx);
    if(state->regs[i]!=NULL){
        free(state->regs[i]);
        state->regs[i]=NULL;
    }
}