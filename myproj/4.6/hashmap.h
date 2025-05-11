#include <stdint.h>
#include <stdlib.h>

typedef const void *cpvoid;

typedef int (*EqualFunc)(cpvoid a, cpvoid b);

typedef uint32_t (*HashFunc)(cpvoid key);

typedef struct Node {
    int fl;
    cpvoid key;
    cpvoid value;
} Node;

typedef struct HashMap {
    EqualFunc eq;
    HashFunc hash;
    int size;
    Node *nodes;
} HashMap;

HashMap HM_Init(EqualFunc ef, HashFunc hf, int size);

void HM_Destroy(HashMap *self);

cpvoid HM_Get(const HashMap *self, cpvoid key);

void HM_Set(HashMap *self, cpvoid key, cpvoid value);