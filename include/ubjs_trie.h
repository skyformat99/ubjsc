#ifndef HAVE_UBJS_TRIE
#define HAVE_UBJS_TRIE

#include "ubjs_common.h"

typedef struct ubjs_trie ubjs_trie;
typedef struct ubjs_trie_iterator ubjs_trie_iterator;
typedef void (*ubjs_trie_value_free)(void *);

struct ubjs_trie;
struct ubjs_trie_iterator;

ubjs_result ubjs_trie_alloc(ubjs_trie_value_free free, ubjs_trie **);
ubjs_result ubjs_trie_free(ubjs_trie **);
ubjs_result ubjs_trie_put(ubjs_trie *, unsigned int,char *, void *);
ubjs_result ubjs_trie_get(ubjs_trie *, unsigned int,char *, void **);
ubjs_result ubjs_trie_delete(ubjs_trie *, unsigned int,char *);

ubjs_result ubjs_trie_iterate_forward(ubjs_trie *,ubjs_trie_iterator **);
ubjs_result ubjs_trie_iterate_backward(ubjs_trie *,ubjs_trie_iterator **);
ubjs_result ubjs_trie_iterator_next(ubjs_trie_iterator *);
ubjs_result ubjs_trie_iterator_get_key_length(ubjs_trie_iterator *,unsigned int *);
ubjs_result ubjs_trie_iterator_copy_key(ubjs_trie_iterator *,char *);
ubjs_result ubjs_trie_iterator_get_value(ubjs_trie_iterator *,void  *);
ubjs_result ubjs_trie_iterator_free(ubjs_trie_iterator **);

#endif
