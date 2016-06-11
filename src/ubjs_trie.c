#include <stdlib.h>
#include <string.h>

#include "../include/ubjs_trie.h"

typedef struct ubjs_trie_node ubjs_trie_node;
typedef struct ubjs_trie_iterator ubjs_trie_iterator;
typedef void (*ubjs_trie_value_free)(void *);

enum ubjs_trie_iterator_direction {
    UTID_FORWARD, UTID_BACKWARD
};

struct ubjs_trie_node {
    unsigned int key_length;
    char *key;
    void *value;

    ubjs_trie_node *next;
    ubjs_trie_node *prev;
    ubjs_trie_node *parent;
    ubjs_trie_node *child;
};

struct ubjs_trie {
    ubjs_trie_value_free free;
    ubjs_trie_node *root;
};

struct ubjs_trie_iterator {
    ubjs_trie *trie;
    ubjs_trie_node *at;
    enum ubjs_trie_iterator_direction direction;
};

ubjs_result ubjs_trie_node_alloc(unsigned int,char *,void *, ubjs_trie_node **);
ubjs_result ubjs_trie_node_free(ubjs_trie_node **);
ubjs_result ubjs_trie_iterator_alloc(ubjs_trie *,enum ubjs_trie_iterator_direction,
                                     ubjs_trie_iterator **);

ubjs_result ubjs_trie_node_alloc(unsigned int key_length,char *key,void *value, ubjs_trie_node **pthis) {
    ubjs_trie_node *this=(ubjs_trie_node *)malloc(sizeof(struct ubjs_trie_node));

    if(0 == this) {
        return UR_ERROR;
    }
    this->key=(char *)malloc(sizeof(char)*key_length);
    if(0 == this->key) {
        free(this);
        return UR_ERROR;
    }

    strncpy(this->key,key,key_length);
    this->key_length=key_length;
    this->value=value;

    this->prev=0;
    this->next=0;
    this->parent=0;
    this->child=0;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_trie_node_free(ubjs_trie_node **pthis) {
    ubjs_trie_node *this;
    if(0 == pthis || 0 == *pthis) {
        return UR_ERROR;
    }

    ubjs_trie_node_free(&(this->next));
    ubjs_trie_node_free(&(this->child));

    this = *pthis;
    free(this->key);
    free(this);
    *pthis=0;
}

ubjs_result ubjs_trie_iterator_alloc(ubjs_trie *trie,enum ubjs_trie_iterator_direction direction,
                                     ubjs_trie_iterator **pthis) {
    ubjs_trie_iterator *this=(ubjs_trie_iterator *)malloc(sizeof(struct ubjs_trie_iterator));

    if(0 == this) {
        return UR_ERROR;
    }

    this->trie=trie;
    this->at=trie->root;
    this->direction=direction;
    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_trie_iterator_free(ubjs_trie_iterator **pthis) {
    ubjs_trie_iterator *this;
    if(0 == pthis || 0 == *pthis) {
        return UR_ERROR;
    }

    this = *pthis;
    free(this);
    *pthis=0;
}

ubjs_result ubjs_trie_alloc(ubjs_trie_value_free free, ubjs_trie **pthis) {
    ubjs_trie *this=(ubjs_trie *)malloc(sizeof(struct ubjs_trie));

    if(0 == this) {
        return UR_ERROR;
    }

    if(UR_ERROR == ubjs_trie_node_alloc(0, "", 0, &(this->root))) {
        free(this);
        return UR_ERROR;
    }

    this->free=free;
    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_trie_free(ubjs_trie **pthis) {
    ubjs_trie *this;
    if(0 == pthis || 0 == *pthis) {
        return UR_ERROR;
    }

    ubjs_trie_node_free(&(this->root));
    free(this);
    *pthis=0;
}

ubjs_result ubjs_trie_put(ubjs_trie *, unsigned int,char *, void *);
ubjs_result ubjs_trie_get(ubjs_trie *, unsigned int,char *, void **);
ubjs_result ubjs_trie_delete(ubjs_trie *, unsigned int,char *);

ubjs_result ubjs_trie_iterate_forward(ubjs_trie *,ubjs_trie_iterator **);
ubjs_result ubjs_trie_iterate_backward(ubjs_trie *,ubjs_trie_iterator **);
ubjs_result ubjs_trie_iterator_next(ubjs_trie_iterator *);
ubjs_result ubjs_trie_iterator_get_key_length(ubjs_trie_iterator *,unsigned int *);
ubjs_result ubjs_trie_iterator_copy_key(ubjs_trie_iterator *,char *);
ubjs_result ubjs_trie_iterator_get_value(ubjs_trie_iterator *,void  *);
