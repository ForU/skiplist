#ifndef INCLUDE_SKIP_LIST_H
#define INCLUDE_SKIP_LIST_H

#define MAX_SKIP_LIST_LEVEL 8

typedef int key_t;
typedef int value_t;
typedef struct skip_node_t skip_node_t;
typedef struct skip_list_t skip_list_t;

struct skip_node_t {
    key_t key;
    value_t value;                 /* void* */
    struct skip_node_t* forwards[1];
};

struct skip_list_t {
    int level;                  /* start from 0(included) */
    skip_node_t* header;
};


skip_list_t *skip_list_create();
void skip_list_destroy(skip_list_t* sl);

int skip_list_insert(key_t key, value_t value, skip_list_t* sl);
int skip_list_delete(key_t key, value_t value, skip_list_t* sl);
int skip_list_search(key_t key, value_t *value, skip_list_t* sl);

#endif /* INCLUDE_SKIP_LIST_H */
