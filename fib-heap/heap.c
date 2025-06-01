// reference : CLRS: Introduction to Algorithms - 3E V-19, 

Heap *MAKE_FIB_HEAP() {
    Heap *new = malloc(sizeof Heap);
    memset(new, 0, sizeof(Heap));
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
    free (H1);
    H2->min = min;
    return H2;
}
