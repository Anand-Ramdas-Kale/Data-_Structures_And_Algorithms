#include "../heap.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

struct pnode {
    struct pnode *next;
    char op;
    uint64_t key;
};

typedef struct pnode pnode;

pnode *parse(char *file_path);
void print_result(pnode *ll);
pnode *execute_ll(pnode *ll);
