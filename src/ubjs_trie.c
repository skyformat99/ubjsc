#include <stdlib.h>
#include <stdio.h>
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
    ubjs_trie_node *up;
    ubjs_trie_node *down;
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

ubjs_result ubjs_trie_node_new(unsigned int, char *, void *,
                               ubjs_trie_node **);
ubjs_result ubjs_trie_node_free(ubjs_trie_node **);
ubjs_result ubjs_trie_iterator_new(ubjs_trie *,
                                   enum ubjs_trie_iterator_direction, ubjs_trie_iterator **);
static ubjs_result ubjs_trie_put_above(ubjs_trie_node *,unsigned int, char *, void *, ubjs_trie_node **);
static ubjs_result ubjs_trie_put_middle_prevnext(ubjs_trie_node *,ubjs_trie_node *,ubjs_trie_node *,unsigned int , char *,void *);
static ubjs_result ubjs_trie_node_shift_key(ubjs_trie_node *,unsigned int);
static void __print_node(ubjs_trie_node *);
static void __print_node_and_children(ubjs_trie_node *, unsigned int);
static void __print_key_value(unsigned int,char *,void *);
static ubjs_result ubjs_trie_delete_node(ubjs_trie *,ubjs_trie_node *);

ubjs_result ubjs_trie_node_new(unsigned int key_length, char *key,
                               void *value, ubjs_trie_node **pthis) {
    if(0 == key || 0 == pthis) {
        return UR_ERROR;
    }


    ubjs_trie_node *this = (ubjs_trie_node *) malloc(
                               sizeof(struct ubjs_trie_node));
    this->key = (char *) malloc(sizeof(char) * key_length);

    strncpy(this->key, key, key_length);
    this->key_length = key_length;
    this->value = value;

    this->prev = 0;
    this->next = 0;
    this->up = 0;
    this->down = 0;

    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_trie_node_free(ubjs_trie_node **pthis) {
    ubjs_trie_node *this;

    if (0 == pthis) {
        return UR_ERROR;
    }

    this = *pthis;
    if(0 == this) {
        return UR_ERROR;
    }

    free(this->key);
    ubjs_trie_node_free(&(this->next));
    ubjs_trie_node_free(&(this->down));

    free(this);
    *pthis = 0;
    return UR_OK;
}

ubjs_result ubjs_trie_iterator_new(ubjs_trie *trie,
                                   enum ubjs_trie_iterator_direction direction, ubjs_trie_iterator **pthis) {
    ubjs_trie_iterator *this = (ubjs_trie_iterator *) malloc(
                                   sizeof(struct ubjs_trie_iterator));

    this->trie = trie;
    this->at = trie->root;
    this->direction = direction;
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_trie_iterator_free(ubjs_trie_iterator **pthis) {
    ubjs_trie_iterator *this;
    if (0 == pthis) {
        return UR_ERROR;
    }

    this = *pthis;
    if (0 == this) {
        return UR_ERROR;
    }

    free(this);
    *pthis = 0;
    return UR_OK;
}

ubjs_result ubjs_trie_new(ubjs_trie_value_free free, ubjs_trie **pthis) {
    if(0 == pthis || 0 == free) {
        return UR_ERROR;
    }

    ubjs_trie *this = (ubjs_trie *) malloc(sizeof(struct ubjs_trie));
    ubjs_trie_node_new(0, "", 0, &(this->root));

    printf("\n\n\n========================================\n\n\n");
    this->free = free;
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_trie_free(ubjs_trie **pthis) {
    ubjs_trie *this;
    if (0 == pthis) {
        return UR_ERROR;
    }

    this = *pthis;
    if(0 == this) {
        return UR_ERROR;
    }

    ubjs_trie_node_free(&(this->root));
    free(this);
    *pthis = 0;
    return UR_OK;
}


static ubjs_result ubjs_trie_put_above(ubjs_trie_node *down,unsigned int key_length, char *key,
                                       void *value, ubjs_trie_node **panew) {
    ubjs_trie_node *anew;

    ubjs_trie_node_new(key_length, key, value, &anew);

    anew->up=down->up;
    anew->down=down;
    anew->prev = down->prev;
    anew->next = down->next;

    if(0 != anew->next) {
        anew->next->prev=anew;
    }

    if(0 != anew->prev) {
        anew->prev->next=anew;
    } else {
        anew->up->down=anew;
    }

    down->up=anew;
    down->next=0;
    down->prev=0;

    if(0 != panew) {
        *panew = anew;
    }
    return UR_OK;
}


static ubjs_result ubjs_trie_put_middle_prevnext(ubjs_trie_node *up, ubjs_trie_node *prev,ubjs_trie_node *next,unsigned int key_length, char *key,
        void *value) {
    ubjs_trie_node *anew;

    ubjs_trie_node_new(key_length, key, value, &anew);

    anew->prev=prev;
    anew->next=next;
    if(0 != next) {
        next->prev=anew;
        next->up=0;
    }
    if(0 != prev) {
        prev->next=anew;
    } else {
        anew->up=up;
        anew->up->down=anew;
    }
    return UR_OK;
}

static void __print_key_value(unsigned int key_length, char *key,
                              void *value) {
    int i;
    printf("%d <", key_length);
    for (i = 0; i < key_length; i++) {
        printf("%c", key[i]);
    }
    printf(">: %d", value);
}

static void __print_node(ubjs_trie_node *node) {
    printf("%d ", node);
    __print_key_value(node->key_length,node->key,node->value);
    printf(" (up-down: %d / %d)", node->up, node->down);
    printf(" (prev-next: %d / %d)", node->prev, node->next);
}

static void __print_node_and_children(ubjs_trie_node *at, unsigned int indent) {
    int i;
    ubjs_trie_node *j;

    for(i=0; i<indent; i++) {
        printf("    ");
    }
    printf("> ");
    __print_node(at);
    printf("\n");

    for(j=at->down; 0!=j; j=j->next) {
        __print_node_and_children(j, indent+1);
    }
}

static ubjs_result ubjs_trie_node_shift_key(ubjs_trie_node *this,unsigned int pos) {
    char *nkey;

    nkey=(char *)malloc(sizeof(char)*(this->key_length-pos));
    strncpy(nkey, this->key+pos, this->key_length-pos);
    free(this->key);

    this->key=nkey;
    this->key_length-=pos;
    return UR_OK;
}

ubjs_result ubjs_trie_put(ubjs_trie *this, unsigned int key_length, char *key,
                          void *value) {
    ubjs_trie_node *at;
    ubjs_trie_node *up;
    ubjs_trie_node *middle;
    int common_key_length;

    if (0 == this || 0 == key || 0 == key_length || 0 == value) {
        return UR_ERROR;
    }

    printf("\nTRIE PUT\n");
    __print_key_value(key_length,key,value);
    printf("\n");

    up = this->root;
    at = up->down;

    if(0 == at) {
        printf("    empty trie, insert under root\n");
        ubjs_trie_put_middle_prevnext(up, 0, 0, key_length,key,value);

        printf("Result:\n");
        __print_node_and_children(this->root, 0);
        return UR_OK;
    }

    while (1) {
        printf("ITERATION\n");
        printf("at: \n");
        __print_node_and_children(at, 0);
        printf("try put: ");
        __print_key_value(key_length,key,value);
        printf("\n");
        printf("cmp: %d\n", (*key - at->key[0]));

        if (*key > at->key[0]) {
            printf("        next sibling\n");
            if(0 == at->next) {
                printf("        last, put at the end\n");
                ubjs_trie_put_middle_prevnext(at->up, at, 0, key_length,key,value);

                printf("Result:\n");
                __print_node_and_children(this->root, 0);
                return UR_OK;
            }
            at = at->next;
        } else if (*key < at->key[0]) {
            printf("        INSERT HERE!\n");
            ubjs_trie_put_middle_prevnext(at->up, at->prev, at, key_length, key, value);

            printf("Result:\n");
            __print_node_and_children(this->root, 0);
            return UR_OK;
        } else {
            printf("    split or merge\n");

            common_key_length = 1;
            while (common_key_length < key_length
                    && common_key_length < at->key_length) {
                printf("        at %d: %c vs %c\n",common_key_length,
                       key[common_key_length],
                       at->key[common_key_length]);

                if (key[ common_key_length]
                        != at->key[common_key_length]) {
                    printf("            STOP\n");
                    break;
                }

                printf("            one more\n");
                common_key_length++;
            }

            printf("    common key length: %d\n", common_key_length);
            printf("    our key length: %d\n", key_length);
            printf("    their key length: %d\n", at->key_length);

            if (common_key_length == key_length && common_key_length == at->key_length) {
                printf("KEYS ARE THE SAME, REPLACE VALUES\n");

                (this->free)(at->value);
                at->value = value;

                printf("Result:\n");
                __print_node_and_children(this->root, 0);
                return UR_OK;
            } else if(common_key_length == key_length) {
                printf("    common key == our key\n");
                printf("    parent->at ==> parent->new->at\n");
                ubjs_trie_put_above(at, key_length, key, value, 0);
                ubjs_trie_node_shift_key(at, common_key_length);

                printf("Result:\n");
                __print_node_and_children(this->root, 0);
                return UR_OK;
            } else if(common_key_length == at->key_length) {
                printf("    common key == their key\n");
                printf("    reiterate from them\n");
                key += common_key_length;
                key_length -= common_key_length;

                if(0 == at->down) {
                    printf("    no children, become the first\n");
                    ubjs_trie_put_middle_prevnext(at, 0, 0, key_length,key,value);

                    printf("Result:\n");
                    __print_node_and_children(this->root, 0);
                    return UR_OK;
                }
                up = at;
                at = up->down;
            } else {
                printf("    partially common key\n");
                printf("    create a middle node, and reiterate from it\n");
                ubjs_trie_put_above(at, common_key_length, key, 0, &middle);
                ubjs_trie_node_shift_key(at, common_key_length);
                printf("        middle: ");
                __print_node(middle);
                printf("\n");
                printf("        fixed at: ");
                __print_node(at);
                printf("\n");

                up = middle;
                key += common_key_length;
                key_length -= common_key_length;
            }
        }
    }
}

ubjs_result ubjs_trie_get(ubjs_trie *this, unsigned int key_length, char *key, void **pvalue) {
    ubjs_trie_node *at;
    ubjs_trie_node *up;

    if (0 == this || 0 == key || 0 == key_length || 0 == pvalue) {
        return UR_ERROR;
    }

    printf("\nTRIE GET\n");
    __print_key_value(key_length,key,0);
    printf("\n");

    up = this->root;
    at = up->down;

    while (0 != at && key_length > 0) {
        printf("ITERATION\n");
        printf("at: \n");
        __print_node_and_children(at, 0);
        printf("try get: ");
        __print_key_value(key_length,key,0);
        printf("\n");
        printf("cmp: %d\n", (*key - at->key[0]));

        if (*key > at->key[0]) {
            printf("        next sibling\n");
            if(0 == at->next) {
                printf("        that was last one\n");
                return UR_ERROR;
            }
            at = at->next;
        } else if (*key < at->key[0]) {
            printf("        too far\n");
            return UR_ERROR;
        } else {
            printf("    can be it\n");
            if(at->key_length == key_length) {
                printf("THIS IS IT!!!!\n");
                *pvalue = at->value;
                return UR_OK;
            }

            if(at->key_length > key_length) {
                printf("    too far\n");
                return UR_ERROR;
            }

            printf("maybe in its children\n");
            key_length -= at->key_length;
            key += at->key_length;
            up = at;
            at = up->down;
        }
    }
    printf("did not found :/\n");

    return UR_ERROR;
}

static ubjs_result ubjs_trie_delete_node(ubjs_trie *this,ubjs_trie_node *node) {
    if(0 != node->next) {
        node->next->prev=node->prev;
    }

    if(0 != node->prev) {
        node->prev->next=node->next;
    } else {
        node->up->down=node->next;
        if(0 != node->next) {
            node->next->up=node->up;
        }
    }

    node->next=0;
    node->down=0;
    (this->free)(node->value);
    return ubjs_trie_node_free(&node);
}

ubjs_result ubjs_trie_delete(ubjs_trie *this, unsigned int key_length, char *key) {
    ubjs_trie_node *at;
    ubjs_trie_node *up;

    if (0 == this || 0 == key || 0 == key_length) {
        return UR_ERROR;
    }

    printf("\nTRIE DELETE\n");
    __print_key_value(key_length,key,0);
    printf("\n");

    up = this->root;
    at = up->down;

    while (0 != at && key_length > 0) {
        printf("ITERATION\n");
        printf("at: \n");
        __print_node_and_children(at, 0);
        printf("try get: ");
        __print_key_value(key_length,key,0);
        printf("\n");
        printf("cmp: %d\n", (*key - at->key[0]));

        if (*key > at->key[0]) {
            printf("        next sibling\n");
            if(0 == at->next) {
                printf("        that was last one\n");
                return UR_ERROR;
            }
            at = at->next;
        } else if (*key < at->key[0]) {
            printf("        too far\n");
            return UR_ERROR;
        } else {
            printf("    can be it\n");
            if(at->key_length == key_length) {
                printf("THIS IS IT!!!!\n");
                printf("before:\n");
                __print_node_and_children(this->root, 0);
                printf("\n");
                ubjs_trie_delete_node(this, at);
                printf("after:\n");
                __print_node_and_children(this->root, 0);
                printf("\n");
                return UR_OK;
            }

            if(at->key_length > key_length) {
                printf("    too far\n");
                return UR_ERROR;
            }

            printf("maybe in its children\n");
            key_length -= at->key_length;
            key += at->key_length;
            up = at;
            at = up->down;
        }
    }

    printf("did not found :/\n");
    return UR_ERROR;
}


ubjs_result ubjs_trie_iterate_forward(ubjs_trie *, ubjs_trie_iterator **);
ubjs_result ubjs_trie_iterate_backward(ubjs_trie *, ubjs_trie_iterator **);
ubjs_result ubjs_trie_iterator_next(ubjs_trie_iterator *);
ubjs_result ubjs_trie_iterator_get_key_length(ubjs_trie_iterator *,
        unsigned int *);
ubjs_result ubjs_trie_iterator_copy_key(ubjs_trie_iterator *, char *);
ubjs_result ubjs_trie_iterator_get_value(ubjs_trie_iterator *, void *);
