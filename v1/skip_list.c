#include <string.h>
#include <stdlib.h>

#include "skip_list.h"

static int gen_level()
{
    // business-depended.
    return 3;
}

static skip_node_t *skip_node_create(key_t key, value_t value, int level)
{
    int size = sizeof(skip_node_t) + level * sizeof(skip_node_t*);
    skip_node_t* self = (skip_node_t*)malloc( size );

    if ( ! self ) {
        return NULL;
    }

    memset(self, 0, size);
    self->key = key;
    self->value = value;

    return self;
}

skip_list_t *skip_list_create()
{
    skip_list_t* self = (skip_list_t*)malloc(sizeof(skip_list_t));
    if ( ! self ) {
        return NULL;
    }

    self->level = 0;
    self->header = skip_node_create(0, 0, MAX_SKIP_LIST_LEVEL);
    if ( ! self->header ) {
        free(self);
        return NULL;
    }

    int i = 0;
    for ( ; i < MAX_SKIP_LIST_LEVEL;  ++i) {
        self->header->forwards[i] = NULL;
    }

    return self;
}

void skip_list_destroy(skip_list_t* sl)
{
    /* In fact, skip list is a list of nodes which contains multiple forwards
     * pointers, about which we do not care in destroy, we only care about
     * nodes. And EVENTUALLY, to destroy a skip list is just same as to
     * destroy a normal list
     * */

    skip_node_t *cur = sl->header;
    skip_node_t *tmp;           /* used to back up next pointer */
    while ( cur ) {
        tmp = cur->forwards[0];
        free(cur);
        cur = tmp;
    }
    free(sl);
}

int skip_list_insert(key_t key, value_t value, skip_list_t* sl)
{
    skip_node_t *prev, *cur;
    prev = sl->header;
    cur = NULL;

    /* store the node at where cur drop to lower level */
    skip_node_t* prev_nodes_path[MAX_SKIP_LIST_LEVEL];
    memset(prev_nodes_path, 0, MAX_SKIP_LIST_LEVEL);

    /* first, find the insert position */
    int l = sl->level - 1;
    for ( ; l >= 0; --l) {
        while ( (cur = prev->forwards[l]) && cur->key < key )
            prev = cur;
        prev_nodes_path[l] = prev;
    }

    /* return if cur's key is the same as key, say, already exists,
     * with value updated.*/
    if ( cur && cur->key == key ) {
        cur->value = value;
        return 1;
    }

    /* create a new node with newly-generated level  */
    int node_level = gen_level();
    skip_node_t *node = skip_node_create(key, value, node_level);
    if ( ! node ) {
        return 0;
    }

    /* update skip list's level and the corresponding forwards pointers
     * if the newly-generated level for current node is greater than
     * that of skip list.
     * */
    if ( node_level > sl->level ) {
        l = sl->level;
        for ( ; l < node_level; ++l ) {
            prev_nodes_path[l] = sl->header;
        }
        /* update after upper actions */
        sl->level = node_level;
    }

    /* insert newly-created node into skip list with both the node' members
     * properly initialized and the skip list is properly updated by prev_nodes_path.
     * */
    l = node_level - 1;
    for ( ; l >= 0; --l ) {
        node->forwards[l] = prev_nodes_path[l]->forwards[l];
        prev_nodes_path[l]->forwards[l] = node;
    }
    return 1;
}

int skip_list_delete(key_t key, value_t value, skip_list_t* sl)
{
    skip_node_t *prev, *cur;
    prev = sl->header;
    cur = NULL;

    /* store the node's prevvious pointers */
    skip_node_t* prev_nodes_path[MAX_SKIP_LIST_LEVEL];
    memset(prev_nodes_path, 0, MAX_SKIP_LIST_LEVEL);

    /* first, find the node */
    int skip_list_level = sl->level;
    int l = skip_list_level - 1;
    for ( ; l >= 0; --l) {
        while ( (cur = prev->forwards[l]) && cur->key < key )
            prev = cur;
        prev_nodes_path[l] = prev;
    }

    /* return if not exists.*/
    if ( ! cur || (cur && cur->key != key)) {
        return 0;
    }

    /* update skip list's pointers by prev_nodes_path and remove current node */
    for ( l = skip_list_level - 1; l >= 0; --l ) {
        if ( prev_nodes_path[l]->forwards[l] == cur ) {
            prev_nodes_path[l]->forwards[l] = cur->forwards[l];
            if ( sl->header->forwards[l] == NULL ) {
                --sl->level;
            }
        }
    }
    free(cur);

    return 1;
}

int skip_list_search(key_t key, value_t *value, skip_list_t* sl)
{
    skip_node_t *prev, *cur;
    prev = sl->header;
    cur = NULL;

    int skip_list_level = sl->level;
    int l = skip_list_level - 1;
    for ( ; l >= 0; --l) {
        while ( (cur = prev->forwards[l]) && cur->key < key )
            prev = cur;
    }
    if ( cur ) {
        *value = cur->value;
    }
    /* return if not exists.*/
    return (cur != NULL);
}

