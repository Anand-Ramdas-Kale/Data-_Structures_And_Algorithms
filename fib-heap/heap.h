// strictly not compatible with c++
#ifndef heap.h_
#define heap.h_

// reference : CLRS: Introduction to Algorithms - 3E, 

/* Data associated to the keys */
typedef struct data {
    uint64_t record;        // actual data, to make it... general implementation, might be a pointer to data
} data_t;

/* The Nodes in Heap */
typedef struct Node {
    uint64_t key;           // key, might be char key[big]
    data_t data;            // data associated with this key
    bool mark;              // mark
    uint32_t degree;        // number of children, not including parent
    struct Node *parent;    // pointer to parent node
    struct Node *left;      // pointer to left node in circular-doubly-linked list
    struct Node *right;     // pointer to right node in circular-doubly-linked list
} Node;

/* The main heap structure */
typedef struct Heap {
    uint32_t n;             // number of trees in heap at top level
    Node *min;              // pointer to minimum node (root of a tree)
} Heap;

/* functions */

/* procedure allocates and returns the Fibonacci heap object H, where H.n = 0 and H.min = NIL */
Heap *MAKE_FIB_HEAP();
Heap *FIB_HEAP_UNION(Heap*, Heap*);
void FIB_HEAP_INSERT(Heap *H, Node *x);

#endif  // heap.h_

