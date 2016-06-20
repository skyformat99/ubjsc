#ifndef HAVE_PTRIE
#define HAVE_PTRIE

typedef enum
{
    UR_OK,
    UR_ERROR
} ptrie_result;

typedef struct ptrie ptrie;
typedef struct ptrie_iterator ptrie_iterator;
typedef void (*ptrie_value_free)(void *);

struct ptrie;
struct ptrie_iterator;

ptrie_result ptrie_new(ptrie_value_free free, ptrie **);
ptrie_result ptrie_free(ptrie **);
ptrie_result ptrie_put(ptrie *, unsigned int,char *, void *);
ptrie_result ptrie_get(ptrie *, unsigned int,char *, void **);
ptrie_result ptrie_delete(ptrie *, unsigned int,char *);

ptrie_result ptrie_iterate_forward(ptrie *,ptrie_iterator **);
ptrie_result ptrie_iterate_backward(ptrie *,ptrie_iterator **);
ptrie_result ptrie_iterator_next(ptrie_iterator *);
ptrie_result ptrie_iterator_get_key_length(ptrie_iterator *,unsigned int *);
ptrie_result ptrie_iterator_copy_key(ptrie_iterator *,char *);
ptrie_result ptrie_iterator_get_value(ptrie_iterator *,void  *);
ptrie_result ptrie_iterator_free(ptrie_iterator **);

#endif
