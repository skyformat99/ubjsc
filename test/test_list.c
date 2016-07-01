#include <stdlib.h>

#include "test_list.h"

void test_list_new(test_list **pthis)
{
    test_list *this;
    this=(test_list *)malloc(sizeof(struct test_list));

    this->obj=0;
    this->free=0;

    this->prev=this;
    this->next=this;

    *pthis=this;
}

void test_list_free(test_list **pthis)
{
    test_list *this;
    test_list *it;

    if(0 == pthis) {
        return;
    }

    this=*pthis;
    it=this->next;

    while(this!=it)
    {
        if(0!=it->free)
        {
            (it->free)(&(it->obj));
        }

        this->next=it->next;
        free(it);
        it = this->next;
    }

    free(this);
    *pthis=0;
}


void test_list_add(test_list *this,void *obj,test_list_free_f free)
{
    test_list *it;
    if(0 == this) {
        return;
    }

    test_list_new(&it);
    it->obj=obj;
    it->free=free;

    this->prev->next=it;
    it->prev=this->prev;
    this->prev=it;
    it->next=this;
}

void test_list_len(test_list *this,unsigned int *plen)
{
    test_list *it;
    int i=0;

    if(0 == this) {
        return;
    }

    it=this->next;

    while(this != it)
    {
        i++;
        it=it->next;
    }

    *plen=i;
}

void test_list_get(test_list *this,int pos,void **pout)
{
    test_list *it;
    int i=0;

    if(0 == this) {
        return;
    }

    it=this->next;
    while(it != this && i < pos)
    {
        i++;
        it=it->next;
    }

    if(it==this)
    {
        return;
    }

    *pout=it->obj;
}
