#include <stdlib.h>   /* malloc(), free(), NULL  */
#include <stdbool.h>  /* Definition of bool      */
#include <stdio.h>    /* printf()                */
#include <assert.h>   /* assert()                */

#include "plist.h"      /* Iterface */

struct s_node {
    t_elem elem;
    bool is_ppiv;           //indicates if the node has the pivot
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_plist {
    struct s_node *head;    //points the first node
    unsigned int count;     //keeps track of how many nodes there are
    t_elem ppiv;            //guarda el valor del ppiv para agilizar
};

/* Creates a single node in dynamic memory containing the element <e>. */
static node_t create_node(t_elem e) {
    printf("creando nodo\n");

  struct s_node *new_node = malloc(sizeof(struct s_node));

    if (new_node==NULL){   //shows error message if malloc fails
        printf("ERROR ALOCANDO MEMORIA.");
        return NULL;
    }
    new_node->elem = e;
    new_node->is_ppiv = false;
    new_node->next = NULL;
printf("saliendo del nodo\n");

    return new_node;
}
/* Destroys a single node */
static node_t destroy_node(node_t node) {
printf("destruyendo nodo\n");

   if (node != NULL){
    free(node);
   }

    return node;
}

/* Representation invariant */
static bool invrep(plist l) {
    if(l->head==NULL){
        return false;
    }
    return true;
}

/* CONSTRUCTORS */

plist plist_create(t_elem pivot) {
printf("creando lista\n");

    plist newlist = malloc(sizeof(struct s_plist));
    if(newlist == NULL){
        printf("Error creando newlist\n");
        return NULL;
    }
    newlist->head = create_node(pivot);
    
    if(newlist->head == NULL){
        printf("Error al crear la nueva lista\n");
        return newlist;
    }
    newlist->head->is_ppiv=true;
    newlist->ppiv = pivot;

    newlist->count=1;
    assert(plist_is_empty(newlist));
    return newlist;
}

plist plist_add(plist l, t_elem e) { //agrega el elem e a la lista, no puede ser ppiv 
    printf("agregar nodo\n");
    //assert(!t_elem_eq(e,l->ppiv));
    struct s_node *newnode = create_node(e);
    
    if(l->head==NULL){
        printf("Error lista nula\n");
        return l;
    }
    printf("agregar 1\n");
    struct s_node *tmp = l->head;
    
    printf("agregar 2\n");
    struct s_node *tmp2 = tmp;
printf("agregar 3\n");
    
    if(plist_is_empty(l)){
        if(t_elem_less(e,tmp->elem)){
            l->head = newnode;
            newnode->next = tmp;
            l->count++;
            return l;
        }else if (t_elem_greater(e,tmp->elem)){
            l->head->next=newnode;
            l->count++;
            return l;
        }

    }else{
    
    while(tmp != NULL && tmp->elem != l->ppiv) {
    tmp2 = tmp;  
    tmp = tmp->next;
}

        
        if (t_elem_less(e,tmp->elem)){
            tmp2->next = newnode;
            newnode->next = tmp;
            l->count++;
            printf("agrego x izq\n");

        } else {
            tmp2 = tmp->next;
            tmp->next = newnode;
            newnode->next = tmp2;
            l->count++;
            printf("agrego x der\n");

        }
    }

    
    assert(!plist_is_empty(l));
    printf("saliendo de agregar\n");

return l;
}

/* OPERATIONS   */
unsigned int plist_length(plist l) {
    unsigned int res = l->count;
    return res;
}

bool plist_is_empty(plist l) {
    bool res = (l->count == 1 && l->head->is_ppiv==true) || (l->head == NULL);
    
    return res;
}

t_elem plist_get_pivot(plist l) {
    t_elem res = l->ppiv;
    return res;
}

plist plist_delete_prev(plist l) { 
printf("entrando a delete prev\n");
    assert(!plist_is_empty(l));

    unsigned int a=0;

    struct s_node *tmp = l->head;
    struct s_node *tmp2 = NULL;
    struct s_node *tmp3 = NULL;
  
    while(tmp->is_ppiv!=true){
        tmp=tmp->next;
        a++;
        
    }
if (tmp != NULL && tmp->next != NULL) {
    tmp2 = tmp->next->next;
    tmp3 = tmp->next;
    destroy_node(tmp3);
    tmp->next = tmp2;
}


    if (a > 1) { 
    for(unsigned int i=0;i<a-2;i++){
        tmp2=tmp2->next; //apunta al nodo anterior a eliminar
    }
    tmp3 = tmp2->next;
    tmp2->next=tmp;
    l->count--;
    destroy_node(tmp3);
}
return l;
}

plist plist_delete_next(plist l) {
    printf("ENTRANDO A DELETE NEXT\n");

    if(plist_is_empty(l)){
        printf("nada que borrar\n");
        return l;
        }

    struct s_node *tmp = l->head;
    struct s_node *tmp2 = NULL;
    struct s_node *tmp3 = NULL;
    if(l->head->next==NULL){
        printf("nada que borrar\n");
        return l;
    }
    while(tmp->is_ppiv != true){    //tmp va a encontrar al ppiv
        tmp = tmp->next;
    }
    if(tmp->next==NULL){
        printf("nada que borrar\n");
        return l;
    }
    if(tmp->next->next == NULL){
        tmp3 = tmp->next;
        destroy_node(tmp3);
        printf("nnNULL\n");
        return l;
    }else{
    tmp2 = tmp->next->next;
    tmp3 = tmp->next;
    destroy_node(tmp3);
    
    tmp->next = tmp2;
 }   printf("POST DELETE NEXT\n");

    return l;
}

unsigned int plist_count(plist l, t_elem e) {
    unsigned int res=0;
    struct s_node *tmp = NULL;
    tmp = l->head;

    while(tmp->next != NULL){    
        tmp = tmp->next;
        if (tmp->elem==e){
            res++;
        }
    }
return res;
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
    t_elem *array = NULL;
    array = malloc(l->count * sizeof(t_elem));
        if (array==NULL){
            printf("ERROR AL ASIGNAR MEMORIA PARA EL ARRAY\n");
        }

    struct s_node *tmp = l->head;
      for (unsigned int i = 0; i < l->count; i++){
            array[i] = tmp->elem;
            tmp = tmp->next;
        }

    //sorting the array

    insertion_sort(array,l->count);

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

    struct s_node *tmp1 = l->head;
    while (tmp1 != NULL){
        struct s_node *tmp2 = tmp1->next;
        destroy_node(tmp1);
        tmp1 = tmp2; 
    }
    
    free(l);
    
    return NULL;
}

