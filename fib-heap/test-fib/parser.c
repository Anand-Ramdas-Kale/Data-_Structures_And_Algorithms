#include "parser.h"

pnode *parse(char *file_path) {
    int file_descriptor = open(file_path, O_RDONLY, 0);
    pnode head;
    pnode *ll = &head;
    ll->next = NULL;
    bool done = false;

    char c = 0;

    while (read(file_descriptor, &c, 1) > 0 && !done) {
        switch (c) {
            case 'A':
                ll->op = 'A';
                break;
            case 'I':
                ll->op = 'I';
                break;
            case 'E':
                ll->op = 'E';
                break;
            case ',':
                ll->next = malloc(sizeof(pnode));
                ll = ll->next;
                memset(ll, 0, sizeof(pnode));
                break;
            case '[':
                ll->next = malloc(sizeof(pnode));
                ll = ll->next;
                memset(ll, 0, sizeof(pnode));
                break;
            case ']':
                done = true;
                break;
            default:
        }
    }

    done = false;
    while (read(file_descriptor, &c, 1) > 0 && !done) {
        if (c >= '0' && c <= '9') {
            ll->key *= 10;
            ll->key += c - '0';
        } else {
            switch (c) {
                case ',':
                    ll = ll->next;
                    break;
                case '[':
                    ll = head.next;
                    break;
                case ']':
                    done = true;
                    break;
                default:
            }
        }
    }

    close(file_descriptor);
    return head.next;
}

pnode *execute_ll(pnode *ll) {
    pnode *head = ll;
    Heap *H = NULL;
    while (ll) {
        switch (ll->op) {
            case 'A':
                H = MAKE_FIB_HEAP();
                break;
            case 'I':
                Node *new = malloc(sizeof(Node));
                new->key = ll->key;
                new->child = NULL;
                FIB_HEAP_INSERT(H, new);
                break;
            case 'E':
                Node *n = FIB_HEAP_EXTRACT_MIN(H);
                if (n) {
                    ll->key = n->key;
                    free(n);
                } else {
                    ll->key = 0;
                }
                break;
        }
        ll = ll->next;
    }
    return head;
}

void print_result(pnode *ll) {
    printf("\nRESULTS\n");
    while (ll) {
        printf("%c: %ld\n", ll->op, ll->key);
        ll = ll->next;
    }
}
