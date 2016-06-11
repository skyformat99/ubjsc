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

ubjs_result ubjs_trie_node_new(unsigned int, char *, void *,
                               ubjs_trie_node **);
ubjs_result ubjs_trie_node_free(ubjs_trie_node **);
ubjs_result ubjs_trie_iterator_new(ubjs_trie *,
                                   enum ubjs_trie_iterator_direction, ubjs_trie_iterator **);

ubjs_result ubjs_trie_node_new(unsigned int key_length, char *key,
                               void *value, ubjs_trie_node **pthis) {
    ubjs_trie_node *this = (ubjs_trie_node *) malloc(
                               sizeof(struct ubjs_trie_node));

    if (0 == this) {
        return UR_ERROR;
    }
    this->key = (char *) malloc(sizeof(char) * key_length);
    if (0 == this->key) {
        free(this);
        return UR_ERROR;
    }

    strncpy(this->key, key, key_length);
    this->key_length = key_length;
    this->value = value;

    this->prev = 0;
    this->next = 0;
    this->parent = 0;
    this->child = 0;

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

    ubjs_trie_node_free(&(this->next));
    ubjs_trie_node_free(&(this->child));

    this = *pthis;
    free(this->key);
    free(this);
    *pthis = 0;
    return UR_OK;
}

ubjs_result ubjs_trie_iterator_new(ubjs_trie *trie,
                                   enum ubjs_trie_iterator_direction direction, ubjs_trie_iterator **pthis) {
    ubjs_trie_iterator *this = (ubjs_trie_iterator *) malloc(
                                   sizeof(struct ubjs_trie_iterator));

    if (0 == this) {
        return UR_ERROR;
    }

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

    if (0 == this) {
        return UR_ERROR;
    }

    if (UR_ERROR == ubjs_trie_node_new(0, "", 0, &(this->root))) {
        free(this);
        return UR_ERROR;
    }

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

ubjs_result ubjs_trie_put(ubjs_trie *this, unsigned int key_length, char *key,
                          void *value) {
    ubjs_trie_node *new_node;
    ubjs_trie_node *next;
    ubjs_trie_node *parent;
    int i;
    int key_offset;
    int common_key_length;
    char *new_key;

    if (0 == this || 0 == key || 0 == key_length) {
        return UR_ERROR;
    }

    printf("trie put: %d <", key_length);
    for (i = 0; i < key_length; i++) {
        printf("%c", key[i]);
    }
    printf("\n");

    parent = this->root;
    next = parent->child;
    key_offset = 0;

    while (0 != next) {
        printf("at: %d <", next->key_length);
        for (i = 0; i < next->key_length; i++) {
            printf("%c", next->key[i]);
        }
        printf("\n");
        printf("    our key: ");
        for (i = 0; i < key_offset; i++) {
            printf("%c", key[i]);
        }
        printf("___%c___", key[key_offset]);
        for (i = key_offset + 1; i < key_length; i++) {
            printf("%c", key[i]);
        }
        printf("\n");
        printf("    their key: ");
        printf("___%c___", next->key[0]);

        for (i = 1; i < next->key_length; i++) {
            printf("%c", next->key[i]);
        }
        printf("\n");
        if (key[key_offset] > next->key[0]) {
            printf("    next sibling\n");
            if(0 == next->next) {
                printf("        no more siblings, enter them afterwards\n");
                if (UR_ERROR
                        == ubjs_trie_node_new(key_length - key_offset,
                                              key + key_offset, value, &new_node)) {
                    printf("        damn new\n");
                    return UR_ERROR;
                }

                new_node->prev = next;
                new_node->prev->next = new_node;
                return UR_OK;
            }
            next = next->next;
        } else if (key[key_offset] < next->key[0]) {
            printf("    INSERT HERE!\n");
            if (UR_ERROR
                    == ubjs_trie_node_new(key_length - key_offset,
                                          key + key_offset, value, &new_node)) {
                printf("        damn new\n");
                return UR_ERROR;
            }

            new_node->prev = next->prev;
            new_node->next = next;
            if (0 != new_node->prev) {
                // Second or more, just link.
                new_node->prev->next = new_node;
            } else {
                // First - assign them parent.
                new_node->parent = parent;
                parent->child = new_node;
            }
            new_node->next->prev = new_node;
            next->parent = 0;

            return UR_OK;
        } else {
            printf("    we should either go down from this or split it\n");
            printf("    find common key length\n");
            printf("        our key length: %d\n", key_length - key_offset);
            printf("        their key length: %d\n", next->key_length);

            common_key_length = 1;
            while (common_key_length < key_length - key_offset
                    && common_key_length < next->key_length) {
                printf("    at %d: %c vs %c\n",common_key_length,
                       key[key_offset + common_key_length],
                       next->key[common_key_length]);

                if (key[key_offset + common_key_length]
                        != next->key[common_key_length]) {
                    printf("        STOP\n");
                    break;
                }

                printf("        one more\n");
                common_key_length++;
            }

            printf("    so...\n");
            printf("        common key length: %d\n", common_key_length);
            printf("        our key length: %d\n", key_length - key_offset);
            printf("        their key length: %d\n", next->key_length);

            if (common_key_length == key_offset + common_key_length) {
                printf("    matches our key\n");

                if (common_key_length == next->key_length) {
                    printf("    matches also their key, so this is it\n");
                    printf("    replace values\n");

                    (this->free)(next->value);
                    next->value = value;
                    return UR_OK;
                }

                printf("    their key is longer\n");
                printf("    1. create new node and give it new value\n");
                printf("    2. make link parent->new->next");
                printf("        new node: %d <", common_key_length);
                for (i = 0; i < common_key_length; i++) {
                    printf("%c", key[key_offset + i]);
                }
                printf("\n");
                printf("        next node: %d <",
                       next->key_length - common_key_length);
                for (i = 0; i < next->key_length - common_key_length; i++) {
                    printf("%c", next->key[common_key_length + i]);
                }
                printf("\n");

                if (UR_ERROR
                        == ubjs_trie_node_new(key_length - key_offset,
                                              key + key_offset, value, &new_node)) {
                    printf("        damn new\n");
                    return UR_ERROR;
                }

                new_key = (char *) malloc(
                              sizeof(char) * (next->key_length - common_key_length));
                if (0 == new_key) {
                    ubjs_trie_node_free(&new_node);
                    printf("        damn new\n");
                    return UR_ERROR;
                }
                strncpy(new_key, next->key + common_key_length,
                        next->key_length - common_key_length);
                free(next->key);
                next->key = new_key;
                next->key_length -= common_key_length;

                new_node->prev = next->prev;
                new_node->next = next->next;
                if (0 != new_node->prev) {
                    new_node->prev->next = new_node;
                } else {
                    // First - give em parent
                    new_node->parent = parent;
                    parent->child = new_node;
                }
                if (0 != new_node->next) {
                    new_node->next->prev = new_node;
                }
                new_node->child = next;
                next->prev = 0;
                next->next = 0;
                next->parent = new_node;

                return UR_OK;
            } else if (common_key_length == key_offset + common_key_length) {
                printf("    matches their key, our is longer\n");
                printf("    1. create child node\n");
                printf("    2. make link parent->next->new\n");
                printf("    3. reiterate from new with new offset %d\n",
                       key_offset + common_key_length);
                printf("        next node: %d <", common_key_length);
                for (i = 0; i < common_key_length; i++) {
                    printf("%c", next->key[i]);
                }
                printf("\n");
                printf("        new node: %d <",
                       next->key_length - common_key_length);
                for (i = 0; i < key_length - key_offset - common_key_length;
                        i++) {
                    printf("%c", key[key_offset + common_key_length + i]);
                }
                printf("\n");

                if (UR_ERROR
                        == ubjs_trie_node_new(
                            key_length - key_offset - common_key_length,
                            key + key_offset + common_key_length, value,
                            &new_node)) {
                    printf("        damn new\n");
                    return UR_ERROR;
                }

                new_key = (char *) realloc(next->key,
                                           sizeof(char) * (common_key_length));
                if (0 == new_key) {
                    ubjs_trie_node_free(&new_node);
                    printf("        damn new\n");
                    return UR_ERROR;
                }
                next->key = new_key;
                next->key_length = common_key_length;

                new_node->parent = next;
                new_node->child = next->child;
                if (0 != next->child) {
                    new_node->child->parent = new_node;
                }
                next->child = new_node;

                parent = next;
                next = new_node;
                key_offset += common_key_length;
            } else {
                printf("    only partally common\n");
                printf("    1. create new node\n");
                printf("    2. make link parent->new->next\n");
                printf("    3. reiterate from next with new offset %d\n",
                       key_offset + common_key_length);
                printf("        new node: %d <", common_key_length);
                for (i = 0; i < common_key_length; i++) {
                    printf("%c", next->key[i]);
                }
                printf("\n");
                printf("        next node: %d <",
                       next->key_length - common_key_length);
                for (i = 0; i < next->key_length - common_key_length; i++) {
                    printf("%c", next->key[i + common_key_length]);
                }
                printf("\n");

                if (UR_ERROR
                        == ubjs_trie_node_new(common_key_length, key, value,
                                              &new_node)) {
                    printf("        damn new\n");
                    return UR_ERROR;
                }

                new_key = (char *) malloc(
                              sizeof(char) * (next->key_length - common_key_length));
                if (0 == new_key) {
                    ubjs_trie_node_free(&new_node);
                    printf("        damn new\n");
                    return UR_ERROR;
                }
                strncpy(new_key, next->key + common_key_length,
                        next->key_length - common_key_length);
                free(next->key);
                next->key = new_key;
                next->key_length -= common_key_length;

                new_node->next = next->next;
                new_node->prev = next->prev;
                if (0 != new_node->next) {
                    new_node->next->prev = new_node;
                }
                if (0 != new_node->prev) {
                    new_node->prev->next = new_node;
                } else {
                    new_node->parent = parent;
                    parent->child = new_node;
                }
                new_node->child = next;
                next->parent = new_node;
                next->next = 0;
                next->prev = 0;

                next = new_node;
                key_offset += common_key_length;
            }
        }
    }

    printf("    create new only child\n");
    if (UR_ERROR
            == ubjs_trie_node_new(key_length - key_offset,
                                  key + key_offset, value, &new_node)) {
        printf("        damn new\n");
        return UR_ERROR;
    }

    new_node->parent=parent;
    parent->child=new_node;
    return UR_OK;
}


ubjs_result ubjs_trie_get(ubjs_trie *, unsigned int, char *, void **);
ubjs_result ubjs_trie_delete(ubjs_trie *, unsigned int, char *);

ubjs_result ubjs_trie_iterate_forward(ubjs_trie *, ubjs_trie_iterator **);
ubjs_result ubjs_trie_iterate_backward(ubjs_trie *, ubjs_trie_iterator **);
ubjs_result ubjs_trie_iterator_next(ubjs_trie_iterator *);
ubjs_result ubjs_trie_iterator_get_key_length(ubjs_trie_iterator *,
        unsigned int *);
ubjs_result ubjs_trie_iterator_copy_key(ubjs_trie_iterator *, char *);
ubjs_result ubjs_trie_iterator_get_value(ubjs_trie_iterator *, void *);
