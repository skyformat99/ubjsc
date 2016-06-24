#include <stdlib.h>

#include "test_list.h"

test_list *test_list_new()
{
    test_list *this;
    this=(test_list *)malloc(sizeof(struct test_list));

    this->obj=0;
    this->free=0;

    this->prev=this;
    this->next=this;

    return this;
}

void test_list_free(test_list *this)
{
    test_list *it=this->next;

    while(this!=it)
    {
        if(0!=it->free)
        {
            (it->free)(it->obj);
        }

        this->next=it->next;
        free(it);
        it = this->next;
    }

    free(this);
}


void test_list_add(test_list *this,void *obj,test_list_free_f free)
{
    test_list *it=test_list_new();
    it->obj=obj;
    it->free=free;

    this->prev->next=it;
    it->prev=this->prev;
    this->prev=it;
    it->next=this;
}

int test_list_len(test_list *this)
{
    test_list *it=this->next;
    int i =0;

    while(this != it)
    {
        i++;
        it=it->next;
    }

    return i;
}

void *test_list_get(test_list *this,int pos)
{
    test_list *it=this->next;
    int i=0;
    while(it != this && i < pos)
    {
        i++;
        it=it->next;
    }
    if(it==this)
    {
        return 0;
    }
    return it->obj;
}
