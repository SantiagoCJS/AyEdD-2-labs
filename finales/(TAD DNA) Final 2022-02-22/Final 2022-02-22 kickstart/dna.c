#include "dna.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct _node {
    nucleobase_t elem;
    struct _node *next;
};

struct _dna_t
{
    struct _node* chain;
    unsigned int lenght;
};

static struct _node* single_node(nucleobase_t e)
{
    struct _node *node = calloc(1, sizeof(struct _node));
    assert(node != NULL);
    node->elem = e;
    node->next = NULL;
    return (node);
}

dna_t dna_T()
{
    dna_t res = malloc(sizeof(struct _dna_t));
    assert(res != NULL);
    struct _node *new_node = single_node(T);
    res->chain = new_node;
    res->lenght = 1;
    return res;
}

dna_t dna_C()
{
    dna_t res = malloc(sizeof(struct _dna_t));
    assert(res != NULL);
    struct _node *new_node = single_node(C);
    res->chain = new_node;
    res->lenght = 1;
    return res;
}

dna_t dna_A()
{
    dna_t res = malloc(sizeof(struct _dna_t));
    assert(res != NULL);
    struct _node *new_node = single_node(A);
    res->chain = new_node;
    res->lenght = 1;
    return res;
}

dna_t dna_G()
{
    dna_t res = malloc(sizeof(struct _dna_t));
    assert(res != NULL);
    struct _node *new_node = single_node(G);
    res->chain = new_node;
    res->lenght = 1;
    return res;
}


dna_t dna_join(dna_t first, dna_t second)
{
    struct _node *aux = NULL;
    aux = first->chain;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    aux->next = second->chain;
    first->lenght = first->lenght + second->lenght;
    return first;
}

unsigned int dna_length(dna_t dna)
{
    unsigned int res = dna->lenght;
    return res;
}

void dna_print(dna_t dna)
{
    struct _node *aux = dna->chain;
    for (unsigned i = 1; i <= dna_length(dna); i++)
    {
        if (i == 1)
        {
            printf("[");
        }
        printf("%d", aux->elem);
        aux = aux->next;

        if (i == dna_length(dna))
        {
            printf("]");
        }
        
    }
    
}

bool dna_is_prefix(dna_t first, dna_t second)
{
    printf("empiezo dna_is_prefix\n");
    bool is_prefix = false;
    struct _node *aux1 = first->chain;
    struct _node *aux2 = second->chain;
    if (first->lenght <= second->lenght)
    {
        /* code */
    while (aux1 != NULL)
    {
        is_prefix = (aux1->elem==aux2->elem);
        aux1 = aux1->next;
        aux2 = aux2->next;
        if (!is_prefix)
        {
            return is_prefix;
        }
        
    }
    }
    
    printf("termino dna_is_prefix\n");
    
    return is_prefix;
}

bool dna_is_equal(dna_t first, dna_t second)
{
    bool is_equal = false;
    dna_print(first);
    dna_print(second);
    if (first->lenght != second->lenght)
    {
        return is_equal;
    }
    struct _node *aux1 = first->chain;
    struct _node *aux2 = second->chain;
    while (aux1 != NULL)
    {

        is_equal = (aux1->elem == aux2->elem);
        aux1 = aux1->next;
        aux2 = aux2->next;
    }
    
    return is_equal;
}

dna_t *dna_cut(dna_t dna, unsigned int count)
{
    dna_t first = malloc(sizeof(struct  _dna_t));
    dna_t second = malloc(sizeof(struct  _dna_t));
    unsigned i= 1;
    
    struct _node *aux = dna->chain;
    while (i <= count)
    {
        aux = aux->next;
        i++;
    }
    
    struct _node *aux2 = aux->next;
    aux->next = NULL;
    first->chain = aux;
    first->lenght = count;
    second->chain = aux2;
    second->lenght = dna->lenght - count;
    dna_t *res = calloc(2, sizeof(struct _dna_t));
    res[0] = first;
    res[1]= second;
    
    return res;
}

static struct _node* destroy_node(struct _node *node) {


   if (node != NULL){
    free(node);
   }

    return node;
}

dna_t dna_destroy(dna_t dna)
{
    printf("empiezo a borrar \n");
    if (dna->lenght == 0)
    {
        return dna;
    }
    
    struct _node *aux = dna->chain;
    struct _node *prev = NULL;
    while (aux != NULL)
    {
        prev = aux;
        aux = aux->next;
        destroy_node(prev);
    }
    printf("termino de borrar \n");
     
     free(dna);
     dna = NULL;
    return dna;
}
