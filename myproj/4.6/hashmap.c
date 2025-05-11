#include "hashmap.h"

HashMap HM_Init(EqualFunc ef, HashFunc hf, int size) {
    HashMap table = {0};
    table.size = size;
    table.eq = ef;
    table.hash = hf;
    table.nodes = (Node *)calloc(size, sizeof(Node));
    return table;
}

void HM_Destroy(HashMap *self) {
    free(self->nodes);
    self->size = 0;
}

cpvoid HM_Get(const HashMap *self, cpvoid key) {
    int nkey = self->hash(key) % self->size;

    for (int i = 0; i < self->size; ++i) {
        if (self->nodes[(nkey + i) % self->size].fl) {
            if (self->eq(key, self->nodes[(nkey + i) % self->size].key)) {
                return self->nodes[(nkey + i) % self->size].value;
            }
        }
    }
    return NULL;
}

void HM_Set(HashMap *self, cpvoid key, cpvoid value) {
    int nkey = self->hash(key) % self->size;

    for (int i = 0; i < self->size; ++i) {
        if (!self->nodes[(nkey + i) % self->size].fl) {
            self->nodes[(nkey + i) % self->size].key = key;
            self->nodes[(nkey + i) % self->size].value = value;
            self->nodes[(nkey + i) % self->size].fl = 1;
            break;
        }
        else if (self->eq(key, self->nodes[(nkey + i) % self->size].key)) {
            self->nodes[(nkey + i) % self->size].value = value;
            break;
        }
    }
}