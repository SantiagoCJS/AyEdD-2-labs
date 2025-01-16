#include <stdlib.h>   /* malloc(), free(), NULL  */
#include <stdbool.h>  /* Definition of bool      */
#include <stdio.h>    /* printf()                */
#include <assert.h>   /* assert()                */

#include "plist.h"      /* Iterface */

struct s_node {
    t_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_plist {
    struct s_node *first;
    t_elem pivot;
    unsigned int length;
};

/* Creates a single node in dynamic memory containing the element <e>. */
static node_t create_node(t_elem e) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

/* Destroys a single node */
static node_t destroy_node(node_t node) {
    free(node);
    node = NULL;
    return node;
}

/* Representation invariant */
static bool invrep(plist l) {
    return (l->length >= 4 || l->length < 4);
}

/* CONSTRUCTORS */

plist plist_create(t_elem pivot) {
    struct s_plist *new_plist = malloc(sizeof(struct s_plist));
    assert(new_plist != NULL);
    new_plist->pivot = pivot;
    new_plist->first = create_node(pivot);
    new_plist->length = 1;
    assert(invrep(new_plist) && plist_is_empty(new_plist));
    return new_plist;
}

plist plist_add(plist l, t_elem e) {
    assert(invrep(l));
    if (t_elem_eq(e,l->pivot))
    {
        printf("No pueden agregarse elementos igual al pivot.");
        exit(1);
    }

    if (t_elem_less(e, l->pivot))
    {
        struct s_node *aux = l->first;
        struct s_node *prev = NULL;
        while (!t_elem_eq(aux->elem, l->pivot))
        {
            prev = aux;
            aux = aux->next;
        }
        struct s_node *papa = create_node(e);
        if (prev == NULL)
        {
            l->first = papa;
            papa->next = aux;
        } else {
        prev->next = papa;
        papa->next = aux;

        }
        
    }

    if (t_elem_greater(e,l->pivot))
    {
        struct s_node * aux = l->first;
        while (!t_elem_eq(aux->elem, l->pivot))
        {
            aux = aux->next;
        }
        struct s_node *papa = create_node(e);
        struct s_node *nex_piv = aux->next;
        aux->next = papa;
        papa->next = nex_piv;
    }
    l->length = l->length + 1;
    assert(invrep(l) && !plist_is_empty(l));
    return l;
}

/* OPERATIONS   */
unsigned int plist_length(plist l) {
     return l->length;
}

bool plist_is_empty(plist l) {
    assert(invrep(l));
    return (l->length == 1);
}

t_elem plist_get_pivot(plist l) {
    assert(invrep(l));
    t_elem piv = l->pivot;
    return piv;
}

plist plist_delete_prev(plist l) {
    assert(invrep(l));
    if (l->length == 1)
    {
        printf("Intentaste eliminar el elemento anterior al pivote en una lista que no lo tiene.");
        exit(1);
    }
    
    struct s_node *aux = l->first;
    struct s_node *prev = NULL;
    if (l->first->elem == l->pivot)
    {
        return l;
    }
    
    while (!t_elem_eq(aux->next->elem, l->pivot))
    {
        prev = aux;
        aux = aux->next;
    }
    if (prev == NULL)
    {
        l->first = aux->next;
        destroy_node(aux);
    } else {
        prev->next = aux->next;
    }
    
    l->length --;
    assert(invrep(l));
    return l;
    
}

plist plist_delete_next(plist l) {
    assert(invrep(l));
    if (l->length == 1)
    {
        printf("Intentaste eliminar el elemento anterior al pivote en una lista que no lo tiene.");
        exit(1);
    }

    struct s_node *aux = l->first;
    while (!t_elem_eq(aux->elem, l->pivot))
    {
        aux = aux->next;
    }
    
    if (aux->next == NULL)
    {
        printf("2Intentaste eliminar el elemento anterior al pivote en una lista que no lo tiene.");
        return l;
    } else {
        aux->next = aux->next->next;
    }
    
    l->length --;
    assert(invrep(l));
    return l;
}

unsigned int plist_count(plist l, t_elem e) {
    assert(invrep(l));
    struct s_node *aux = l->first;
    unsigned int times_e_in_l = 0;
    while (aux != NULL)
    {
        if (t_elem_eq(e,aux->elem))
        {
            times_e_in_l = times_e_in_l + 1;
        }
        
        aux = aux->next;
    }
    
    assert(invrep(l));
    return times_e_in_l;
}

//////Funciones auxiliares para ordenar el array/////////

static void insert(t_elem a[], unsigned int i) {

    for (unsigned int j = i;j>0 && (a[j]<a[j-1]) ; j--){  
        t_elem stmp= a[j];
        a[j] = a[j-1];
        a[j-1] = stmp;
    }

}

void insertion_sort(t_elem a[], unsigned int length) {
    if (length == 1) {
        printf("ERROR. ARRAY VACIO.\n");
        return;
    }

    for (unsigned int i = 1u; i < length; i++) {
        insert(a, i);
    }
}
/////////////
t_elem * plist_to_array(plist l) {
    assert(invrep(l));
    t_elem *array = NULL;
    array = malloc(l->length * sizeof(t_elem));
        if (array==NULL){
            printf("ERROR AL ASIGNAR MEMORIA PARA EL ARRAY\n");
        }

    struct s_node *aux = l->first;
    unsigned int i = 0;
    unsigned int length = l->length;
    while (length != 0)
    {
        printf("ENTRE AL WHILE\n");
        printf("i: %u\n", i);
        unsigned int asd = aux->elem;
        printf("aux.elem: %u\n", asd);
        array[i] = aux->elem;
        aux = aux->next;
        i++;
        length--;
    }
    

    //sorting the array

    insertion_sort(array,l->length);

    return array;
}

void plist_dump(plist l) {
    assert(invrep(l));
    if (plist_is_empty(l)) {
        printf("[]");
    } else {
        t_elem *elems = plist_to_array(l);
        printf("[ ");
        t_elem_dump(elems[0]);
        for (unsigned int i=1; i < plist_length(l); i++) {
            printf(", ");
            t_elem_dump(elems[i]);
        }
        printf(" ]");
        free(elems);
    }
}

plist plist_destroy(plist l) {
    assert(invrep(l));
    struct s_node *aux = l->first;
    while (aux != NULL)
    {
        struct s_node *destroy = aux;
        aux = aux->next;
        destroy_node(destroy);
    }
    free(l);
    l = NULL;
    return l;  
}

