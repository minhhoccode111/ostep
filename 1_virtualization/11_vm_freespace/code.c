
// memory header
typedef struct {
  int size;
  int magic;
} header_t;

// free list node
typedef struct __node_t {
  int size;
  struct __node_t *next;
} node_t;

// code to initializa the Free List
// node_t *head = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANON |
// MAP_PRIVATE, -1, 0);

// head->size = 4096 - sizeof(node_t);
// head->next = NULL;

// mmap(): is used to request a check of free memory (4KB in this case) from the
// OS head: is a pointer to the beginning of this memory chunk the size of the
// first free block is set to 4096 minus the size of the node structure
// (node_t), which tracks the free block head->next = NULL: indicates that there
// is only one free block initially, so the `next` pointer is `NULL`
