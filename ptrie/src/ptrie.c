#include <stdlib.h>
#include <string.h>

#include "../include/ptrie.h"

typedef struct ptrie_node ptrie_node;
typedef struct ptrie_iterator ptrie_iterator;
typedef void (*ptrie_value_free)(void *);

enum ptrie_iterator_direction {
    UTID_FORWARD, UTID_BACKWARD
};

struct ptrie_node {
    unsigned int key_length;
    char *key;
    void *value;

    ptrie_node *next;
    ptrie_node *prev;
    ptrie_node *up;
    ptrie_node *down;
};

struct ptrie {
    ptrie_value_free free;
    ptrie_node *root;
};

struct ptrie_iterator {
    ptrie *trie;
    ptrie_node *at;
    enum ptrie_iterator_direction direction;
};

ptrie_result ptrie_node_new(unsigned int, char *, void *,
                            ptrie_node **);
ptrie_result ptrie_node_free(ptrie_node **);
ptrie_result ptrie_iterator_new(ptrie *,
                                enum ptrie_iterator_direction, ptrie_iterator **);
static ptrie_result ptrie_put_above(ptrie_node *,unsigned int, char *, void *, ptrie_node **);
static ptrie_result ptrie_put_middle_prevnext(ptrie_node *,ptrie_node *,ptrie_node *,unsigned int , char *,void *);
static ptrie_result ptrie_node_shift_key(ptrie_node *,unsigned int);
static ptrie_result ptrie_node_prepend_key(ptrie_node *,unsigned int,char *);
static ptrie_result ptrie_print_node(ptrie_node *,unsigned int);

ptrie_result ptrie_node_new(unsigned int key_length, char *key,
                            void *value, ptrie_node **pthis) {
    if(0 == key || 0 == pthis) {
        return UR_ERROR;
    }


    ptrie_node *this = (ptrie_node *) malloc(
                           sizeof(struct ptrie_node));
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

ptrie_result ptrie_node_free(ptrie_node **pthis) {
    ptrie_node *this;

    if (0 == pthis) {
        return UR_ERROR;
    }

    this = *pthis;
    if(0 == this) {
        return UR_ERROR;
    }

    free(this->key);
    ptrie_node_free(&(this->next));
    ptrie_node_free(&(this->down));

    free(this);
    *pthis = 0;
    return UR_OK;
}

ptrie_result ptrie_iterator_new(ptrie *trie,
                                enum ptrie_iterator_direction direction, ptrie_iterator **pthis) {
    ptrie_iterator *this = (ptrie_iterator *) malloc(
                               sizeof(struct ptrie_iterator));

    this->trie = trie;
    this->at = trie->root;
    this->direction = direction;
    *pthis = this;
    return UR_OK;
}

ptrie_result ptrie_iterator_free(ptrie_iterator **pthis) {
    ptrie_iterator *this;
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

ptrie_result ptrie_new(ptrie_value_free free, ptrie **pthis) {
    if(0 == pthis || 0 == free) {
        return UR_ERROR;
    }

    ptrie *this = (ptrie *) malloc(sizeof(struct ptrie));
    ptrie_node_new(0, "", 0, &(this->root));

    this->free = free;
    *pthis = this;
    return UR_OK;
}

ptrie_result ptrie_free(ptrie **pthis) {
    ptrie *this;
    if (0 == pthis) {
        return UR_ERROR;
    }

    this = *pthis;
    if(0 == this) {
        return UR_ERROR;
    }

    ptrie_node_free(&(this->root));
    free(this);
    *pthis = 0;
    return UR_OK;
}


static ptrie_result ptrie_put_above(ptrie_node *down,unsigned int key_length, char *key,
                                    void *value, ptrie_node **panew) {
    ptrie_node *anew;

    ptrie_node_new(key_length, key, value, &anew);

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


static ptrie_result ptrie_put_middle_prevnext(ptrie_node *up, ptrie_node *prev,ptrie_node *next,unsigned int key_length, char *key,
        void *value) {
    ptrie_node *anew;

    ptrie_node_new(key_length, key, value, &anew);

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

static ptrie_result ptrie_node_shift_key(ptrie_node *this,unsigned int pos) {
    char *nkey;

    nkey=(char *)malloc(sizeof(char)*(this->key_length-pos));
    strncpy(nkey, this->key+pos, this->key_length-pos);
    free(this->key);

    this->key=nkey;
    this->key_length-=pos;
    return UR_OK;
}

static ptrie_result ptrie_node_prepend_key(ptrie_node *this,unsigned int len,char *pre) {
    char *nkey;

    nkey=(char *)malloc(sizeof(char)*(this->key_length+len));
    strncpy(nkey, pre, len);
    strncpy(nkey+len, this->key, this->key_length);
    free(this->key);

    this->key=nkey;
    this->key_length+=len;
    return UR_OK;
}

ptrie_result ptrie_put(ptrie *this, unsigned int key_length, char *key,
                       void *value) {
    ptrie_node *at;
    ptrie_node *up;
    ptrie_node *middle;
    int common_key_length;

    if (0 == this || 0 == key || 0 == key_length || 0 == value) {
        return UR_ERROR;
    }

    up = this->root;
    at = up->down;

    if(0 == at) {
        ptrie_put_middle_prevnext(up, 0, 0, key_length,key,value);

        printf("AFTER PUT\n");
        ptrie_print_node(this->root, 0);

        return UR_OK;
    }

    while (1) {
        if (*key > at->key[0]) {
            if(0 == at->next) {
                ptrie_put_middle_prevnext(at->up, at, 0, key_length,key,value);
                printf("AFTER PUT\n");
                ptrie_print_node(this->root, 0);
                return UR_OK;
            }
            at = at->next;
        } else if (*key < at->key[0]) {
            ptrie_put_middle_prevnext(at->up, at->prev, at, key_length, key, value);
            printf("AFTER PUT\n");
            ptrie_print_node(this->root, 0);
            return UR_OK;
        } else {

            common_key_length = 1;
            while (common_key_length < key_length
                    && common_key_length < at->key_length) {

                if (key[ common_key_length]
                        != at->key[common_key_length]) {
                    break;
                }

                common_key_length++;
            }

            if (common_key_length == key_length && common_key_length == at->key_length) {

                (this->free)(at->value);
                at->value = value;

                printf("AFTER PUT\n");
                ptrie_print_node(this->root, 0);
                return UR_OK;
            } else if(common_key_length == key_length) {
                ptrie_put_above(at, key_length, key, value, 0);
                ptrie_node_shift_key(at, common_key_length);

                printf("AFTER PUT\n");
                ptrie_print_node(this->root, 0);
                return UR_OK;
            } else if(common_key_length == at->key_length) {
                key += common_key_length;
                key_length -= common_key_length;

                if(0 == at->down) {
                    ptrie_put_middle_prevnext(at, 0, 0, key_length,key,value);
                    printf("AFTER PUT\n");
                    ptrie_print_node(this->root, 0);
                    return UR_OK;
                }
                up = at;
                at = up->down;
            } else {
                ptrie_put_above(at, common_key_length, key, 0, &middle);
                ptrie_node_shift_key(at, common_key_length);

                up = middle;
                key += common_key_length;
                key_length -= common_key_length;
            }
        }
    }
}

ptrie_result ptrie_get(ptrie *this, unsigned int key_length, char *key, void **pvalue) {
    ptrie_node *at;
    ptrie_node *up;

    if (0 == this || 0 == key || 0 == key_length || 0 == pvalue) {
        return UR_ERROR;
    }

    up = this->root;
    at = up->down;

    while (0 != at && key_length > 0) {
        if (*key > at->key[0]) {
            if(0 == at->next) {
                return UR_ERROR;
            }
            at = at->next;
        } else if (*key < at->key[0]) {
            return UR_ERROR;
        } else {
            if(at->key_length == key_length) {
                *pvalue = at->value;
                return UR_OK;
            }

            if(at->key_length > key_length) {
                return UR_ERROR;
            }

            key_length -= at->key_length;
            key += at->key_length;
            up = at;
            at = up->down;
        }
    }

    return UR_ERROR;
}


ptrie_result ptrie_delete(ptrie *this, unsigned int key_length, char *key) {
    ptrie_node *at;
    ptrie_node *tmp;
    ptrie_node *up;

    if (0 == this || 0 == key || 0 == key_length) {
        return UR_ERROR;
    }

    up = this->root;
    at = up->down;

    printf("\nBEFORE DELETE\n");
    unsigned int i;
    printf("%d <", key_length);
    for(i=0; i<key_length; i++) {
        printf("%c",key[i]);
    }
    printf(">\n");
    ptrie_print_node(this->root, 0);

    while (0 != at && key_length > 0) {
        printf("AT\n");
        printf("%d <", at->key_length);
        for(i=0; i<at->key_length; i++) {
            printf("%c",at->key[i]);
        }
        printf(">\n");

        if (*key > at->key[0]) {
            if(0 == at->next) {
                printf("    NO MORE\n");
                return UR_ERROR;
            }
            at = at->next;
        } else if (*key < at->key[0]) {
            printf("ALREADY PAST\n");
            return UR_ERROR;
        }

        if(at->key_length == key_length) {
            if(0 == at->value) {
                printf("NO VALUE\n");
                return UR_ERROR;
            }

            (this->free)(at->value);
            at->value=0;

            if(0 != at->down) {
                if(0 != at->down->next) {
                    printf("AFTER DELETE - FREE ONLY\n");
                    ptrie_print_node(this->root, 0);
                    return UR_OK;
                }

                ptrie_node_prepend_key(at->down, at->key_length, at->key);
                at->down->next=at->next;
                at->down->prev=at->prev;

                if(0 != at->next) {
                    at->next->prev=at->down;
                }

                if(0 != at->prev) {
                    at->prev->next=at->down;
                } else {
                    at->up->down=at->down;
                }
            } else {
                if(0 != at->next) {
                    at->next->prev=at->prev;
                }

                if(0 != at->prev) {
                    at->prev->next=at->next;
                } else {
                    at->up->down=at->next;
                    if(0 != at->next) {
                        at->next->up=at->up;
                    }
                }
            }

            at->next=0;
            at->down=0;
            ptrie_node_free(&at);

            printf("AFTER DELETE\n");
            ptrie_print_node(this->root, 0);
            return UR_OK;
        }

        if(at->key_length > key_length) {
            printf("TOO SHORT KEY\n");
            return UR_ERROR;
        }

        key_length -= at->key_length;
        key += at->key_length;
        up = at;
        at = up->down;
    }

    printf("NOT FOUND\n");
    return UR_ERROR;
}

ptrie_result ptrie_iterate_forward(ptrie *, ptrie_iterator **);
ptrie_result ptrie_iterate_backward(ptrie *, ptrie_iterator **);
ptrie_result ptrie_iterator_next(ptrie_iterator *);
ptrie_result ptrie_iterator_get_key_length(ptrie_iterator *,
        unsigned int *);
ptrie_result ptrie_iterator_copy_key(ptrie_iterator *, char *);
ptrie_result ptrie_iterator_get_value(ptrie_iterator *, void *);

static ptrie_result ptrie_print_node(ptrie_node *node,unsigned int indent) {
    ptrie_node *it;
    unsigned int i;

    if(0 == node) {
        return UR_OK;
    }
    for(i=0; i<indent; i++) {
        printf("    |");
    }
    printf(">");

    printf("%d <", node->key_length);
    for(i=0; i<node->key_length; i++) {
        printf("%c",node->key[i]);
    }
    printf(">\n");

    for(it=node->down; 0!=it; it=it->next) {
        ptrie_print_node(it,indent+1);
    }

    return UR_OK;
}
