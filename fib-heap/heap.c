// reference : CLRS: Introduction to Algorithms - 3E V-19, 

#include "heap.h"
#define INDENT_WIDTH 2

static inline uint32_t D(uint32_t n) {
    return 32 + 5 - __builtin_clz(n - 1); // can be made more accurate, but this works fine
}

Heap *MAKE_FIB_HEAP() {
    Heap *new = malloc(sizeof(Heap));
    memset(new, 0, sizeof(Heap));
    return new;
}

void FIB_HEAP_INSERT(Heap *H, Node *x) {
    /* we are assuming that the key and data attributes are already filled */
    /* Also H is never NULL */
    /* degree, parent, mark = 0 */
    x->parent = NULL;
    x->degree = 0;
    x->mark   = false;

    /* is heap empty? */
    if (H->min == NULL) {   // yes
        x->left = x->right = x;
        H->min  = x;
    } else {                // no
        /* inserting in the root list */
        Node *min = H->min;
        x->left = min->left;
        min->left = x;
        x->left->right = x;
        x->right = min;

        /* updating the minimum if necessary */
        if (min->key > x->key) {
            H->min = x;
        }
    }
    H->num_roots += 1;
    H->n += 1;
}

Heap *FIB_HEAP_UNION(Heap *H1, Heap *H2) {
    Node *min1 = H1->min;
    Node *min2 = H2->min;

    if (min1 == NULL) {
        free(H1);
        return H2;
    }
    if (min2 == NULL) {
        free(H2);
        return H1;
    }

    Node *min = min1;
    if (min->key > min2->key) min = min2;

    min2->right->left = min1->left;
    min1->left->right = min2->right;
    min2->right = min1;
    min1->left  = min2;
    H2->n += H1->n;
    H2->num_roots += H1->num_roots;
    free (H1);
    H2->min = min;
    return H2;
}


void FIB_HEAP_LINK(Heap *H, Node *y, Node *x) {
    /* remove y from root list of H */
    y->left->right = y->right;
    y->right->left = y->left;
    
    /* make y a child of x */
    Node *child_list = x->child;
    if (child_list) {
        /* (insert y into child list of x) */
        child_list->left->right = y;
        y->left = child_list->left;
        child_list->left = y;
        y->right = child_list;
    } else {
        y->left = y;
        y->right = y;
        x->child = y;
    }
    x->degree += 1;
    H->num_roots -= 1;
    y->mark = false;
    y->parent = x;
}

void CONSOLIDATE(Heap *H) {
    /* this will always be called when there are nonzero roots in root list of H */
    /* let A[0 .. D(H.n)] be a new array */
    int max_degree = D(H->n);
    Node *A[max_degree];
    Node *next = H->min;
    memset(A, 0, sizeof(Node *) * max_degree);
    uint32_t pending_nodes = H->num_roots;
    while (pending_nodes) {
        Node *x = next;             // the node bing processed
        uint32_t d = x->degree;     // the degree of the node being processed
        next = next->right;

        while (A[d]) {
            Node *y = A[d];
            if (y->key < x->key) {
                Node *temp = y;
                y = x;
                x = temp;
            }
            FIB_HEAP_LINK(H, y, x);
            A[d] = NULL;
            d += 1;
        }
        A[d] = x;                   // insert x in correct position accoriding to its degree
        pending_nodes -= 1;         // if i was writing this in asm i would have checked flags instead of testl
    }

    Node dummy = {.key = MAX_KEY_INVALID};
    dummy.left = &dummy;
    dummy.right = &dummy;
    Node *min = &dummy;
    uint32_t num_roots = 0;

    /* formation of new root list for H */
    for (int i = 0; i < max_degree; i += 1) {
        Node *node;
        if ((node = A[i])) {
            (dummy.left)->right = node;
            node->left = dummy.left;
            dummy.left = node;
            node->right = &dummy;
            if (min->key > node->key) {
                min = node;
            }
            num_roots += 1;
        }
    }
    H->min = min;
    (dummy.left)->right = dummy.right;
    (dummy.right)->left = dummy.left;
    H->num_roots = num_roots;
}

Node *FIB_HEAP_EXTRACT_MIN(Heap *H) {
    Node *z = H->min;
    if (z) { // if z is not null
        /* Add each children of z to root list of H */
        Node *x = z->child;
        if (x) {
            Node *cursor = x;
            do {
                cursor->parent = NULL;
                cursor = cursor->left;
            } while (cursor != x);
            Node *right_end = x->left;
            Node *left_end = x;
            z->left->right = left_end;
            left_end->left = z->left;
            z->left = right_end;
            right_end->right = z;
            H->num_roots += z->degree;
        }
        /* remove z from root list of H */
        Node *left;
        Node *right;
        if ((left = z->left) != z) {
            right = z->right;
            left->right = right;
            right->left = left;
        }
        H->n -= 1;
        H->num_roots -= 1;
        z->parent = NULL;
        if (z->right == z) H->min = NULL; else H->min = z->right, CONSOLIDATE(H); // is any child left?
    }
    return z;
}

void FIB_HEAP_PRINT_DFS(Node *node, uint32_t depth) {
    if (!node) {
        return ;
    }
    Node *ll = node;
    do {
        printf("%*s%ld\n",depth * INDENT_WIDTH, "", ll->key);
        FIB_HEAP_PRINT_DFS(ll->child, depth + 1);
        ll = ll->right;
    } while (ll != node);
}

void FIB_HEAP_PRINT(Heap *H) {
    if (H) {
        FIB_HEAP_PRINT_DFS(H->min, 0);
    }
}
