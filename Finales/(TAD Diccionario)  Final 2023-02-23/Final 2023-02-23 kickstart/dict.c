#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include <string.h>
#include "key_value.h"  /* key_t               */
#include "dict.h"       /* intarface           */

struct _s_dict {
    unsigned int size;
    struct _node_t * first;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};



struct _node_t * create_node(key_t k, value_t v) {
    struct _node_t *new_node=malloc(sizeof(struct _node_t));
    new_node->key=k;
    new_node->value=v;
    new_node->next=NULL;
    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    node=NULL;
    return node;
}

static bool invrep(dict_t dict) {
    bool valid = (dict != NULL);
    unsigned int remove = 0;
    struct _node_t *aux = dict->first;
    while (aux != NULL) {
        remove++;
        aux = aux->next;
    }

    return (valid && (dict->size == remove));
}
// --- Interface functions ---

dict_t dict_empty(void) {
    dict_t new_dict = malloc(sizeof(struct _s_dict));
    assert(new_dict != NULL);
    new_dict->first = NULL;
    new_dict->size = 0;
    assert(dict_length(new_dict) == 0);
    return new_dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(dict != NULL);

    if (dict->size == 0) {
        dict->first = create_node(word,def);
        dict->size++;
        return dict;
    }
    
    key_t key = word;
    
    struct _node_t *aux = dict->first;
    while (aux->next != NULL) {
        if (key_eq(key ,aux->key)) {
            aux->value = def;
            return dict;
        }
        aux = aux->next;
    }
    aux->next = create_node(word,def);
    dict->size++;
    
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    value_t value = NULL;
    struct _node_t *aux = dict->first;
    while (aux != NULL) {
        if (key_eq(word, aux->key)) {
            value = aux->value;
            return value;
        }
        
        aux = aux->next;    
    }
    assert(invrep(dict) && (value != NULL) == dict_exists(dict,word));
    return value;
}

bool dict_exists(dict_t dict, key_t word) {
    bool word_in_dict = false;
    struct _node_t *aux = dict->first;
    while (aux != NULL) {
        if (key_eq(word, aux->key)) {
            word_in_dict = true;
            return word_in_dict;
        }
        aux = aux->next;
    }
    return word_in_dict;
}

unsigned int dict_length(dict_t dict) {
    return(dict->size);
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));

    struct _node_t *prev = NULL;
    struct _node_t *remove = dict->first;
    while (remove != NULL) {
        if (key_eq(remove->key, word)) {
            if (prev == NULL) {
                dict->first = remove->next;
            } else {
                prev->next = remove->next;
            }
            

            dict->size--;
            destroy_node(remove);
            break;
        }
        
        prev = remove;
        remove = remove->next;
    }
    assert(invrep(dict) && !dict_exists(dict,word));
    return dict;
}


void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    for (struct _node_t *check=dict->first; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));

    while (dict->first != NULL) {
        struct _node_t *aux = dict->first;
        dict->first = dict->first->next;
        dict->size--;
        aux = destroy_node(aux);
    }

    assert(invrep(dict) && dict->size == 0);
    return dict;

}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict=NULL;
    assert(dict==NULL);
    return dict;
}

