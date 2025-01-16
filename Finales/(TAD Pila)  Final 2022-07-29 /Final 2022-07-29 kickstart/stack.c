#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct s_node {
    struct s_node *next;
    unsigned int used;
    stack_elem *chunk;
};

struct _s_stack {
    struct s_node *top;
    unsigned int size;
};

static bool
valid_chunks(stack s) {
    bool valid=true;
    struct s_node *check=s->top;
    if (check!=NULL) {
        valid = valid && check->chunk != NULL;
        valid = valid && check->used <= CHUNK_CAPACITY;
    }
    return valid;
}

static bool
invrep(stack s) {
    return (s!=NULL && valid_chunks(s));
    bool resp = true;
    resp = (s != NULL);
    unsigned int length = 0;
    struct s_node *aux = s->top;
    while (aux != NULL)
    {
        length++;
        aux = aux->next;
    }
    
    resp = resp && (length == s->size);
    return resp;
}

static struct s_node *
create_node(void) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert (new_node != NULL);
    new_node->next = NULL;
    new_node->used = 0;
    new_node->chunk = calloc(CHUNK_CAPACITY, sizeof(stack_elem));

    return new_node;
}


static struct s_node *
destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next = NULL;
    free(node->chunk);
    free(node);
    node = NULL;
    
    return node;
}

stack stack_empty(void) {
    struct _s_stack *new_stack = malloc(sizeof(struct _s_stack));
    new_stack->top = create_node();
    new_stack->size = 0u;

    return new_stack;
}


stack stack_push(stack s, stack_elem e) {
    
    //assert(invrep(s));
    struct s_node *aux = s->top;
    //printf("AUX.USED: %d", aux->used);
    if (aux->used == CHUNK_CAPACITY)
    {
        //printf("aux.used: %d\n", aux->used);
        s->top = create_node();
        s->top->next = aux;
        s->top->chunk[0] = e;
        s->top->used = 1;
        //printf("A:aux.used: %d\n", aux->used);
        
    } else {
        //printf("aux.used:%d\n", aux->used);
        aux->chunk[aux->used] = e;
        aux->used = aux->used + 1;
       // printf("Baux.used:%d\n", aux->used);
    }
    s->size ++;
    
    assert(invrep(s) && !stack_is_empty(s));
    return s;

}




stack stack_pop(stack s) {
    assert(invrep(s) && (!stack_is_empty(s)));
    struct s_node *aux = s->top;
    if (aux->used == 1)
    {
        if (s->size == 1)
        {
            s = stack_empty();
            printf("LA CONCHA DE LA LORA2 y s.size: %d\n", stack_size(s));
            s->size = 0;
            return s;
        } else {
            s->top = s->top->next;
            destroy_node(aux);
        }
        
    } else {
        aux->used = aux->used - 1;
    }
    s->size = s->size - 1;
    return s;
    
} 


unsigned int stack_size(stack s) {
    return s->size;
}

void stack_top(stack s, stack_elem *top) {
    *top =  s->top->chunk[s->top->used];
}

bool stack_is_empty(stack s) {
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s) {
    stack_elem *array = calloc(s->size, sizeof(stack_elem));
    assert(array != NULL);

    int pos = s->size - 1;

    struct s_node *aux = s->top;

    while (pos >= 0)
    {
        for (int i = aux->used - 1; i >= 0; i--)
        {
            array[pos] = aux->chunk[i];
            pos = pos - 1; 
        }
        
        aux = aux->next;
    }
    
    return array;
}



stack stack_destroy(stack s) {
    struct s_node *aux = NULL;
    while (s->top != NULL)
    {
        aux = s->top;
        s->top = s->top->next;
        aux = destroy_node(aux);
    }
    free(s);
    s = NULL;
    return s;
}

