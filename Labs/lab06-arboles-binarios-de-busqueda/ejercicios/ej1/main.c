/* First, the standard lib includes, alphabetically ordered. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h"  /* TAD abb. */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* Parse the filepath given in command line arguments. */
    filepath = parse_filepath(argc, argv);

    /* Parse the file to obtain an abb with the elements. */
    abb tree = abb_from_file(filepath);

    /* Dumping the tree. */
    abb_dump(tree, ABB_IN_ORDER);
    if (!abb_is_empty(tree)) {
        printf("\n");
        printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
                                                       abb_min(tree),
                                                       abb_max(tree));
    } else {
        printf("\nÁrbol vacío.\n");
    }

    int option = 0;
    while (option != 7) {
        printf("\n");
        printf("╔══════════════════════════════════════════════════════════╗\n");
        printf("║   MENÚ PRINCIPAL - Arbol Binario de Busqueda - OPCIONES  ║\n");
        printf("╠══════════════════════════════════════════════════════════╣\n");
        printf("║ 1. Mostrar árbol por pantalla                            ║\n");
        printf("║ 2. Agregar un elemento                                   ║\n");
        printf("║ 3. Eliminar un elemento                                  ║\n");
        printf("║ 4. Chequear existencia de elemento                       ║\n");
        printf("║ 5. Mostrar longitud del árbol                            ║\n");
        printf("║ 6. Mostrar raiz, máximo y mínimo del árbol               ║\n");
        printf("║ 7. Salir                                                 ║\n");
        printf("╚══════════════════════════════════════════════════════════╝\n");
        printf("Ingrese una opción: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                abb_dump(tree, ABB_PRE_ORDER);
                break;
            case 2: {
                int element;
                printf("Ingrese el elemento a agregar: ");
                scanf("%d", &element);
                tree = abb_add(tree, element);
                abb_dump(tree, ABB_IN_ORDER);
                break;
            }
            case 3: {
                int element;
                printf("Ingrese el elemento a eliminar: ");
                scanf("%d", &element);
                tree = abb_remove(tree, element);
                break;
            }
            case 4: {
                int element;
                printf("Ingrese el elemento a chequear: ");
                scanf("%d", &element);
                if (abb_exists(tree, element)) {
                    printf("El elemento %d está en el árbol.", element);
                } else {
                    printf("El elemento %d no está en el árbol.", element);
                }
                break;
            }
            case 5: {
                    printf("La longitud del árbol es: %d.\n", abb_length(tree));
                break;
            }
            case 6:
                printf("Raíz: %d.\n", abb_root(tree));
                printf("Mínimo: %d.\n", abb_min(tree));
                printf("Máximo: %d.\n", abb_max(tree));
                break;
            case 7:
                break;
            default:
                printf("Opción inválida. Por favor, ingrese una opción válida.\n");
                break;
        }
    }

    tree = abb_destroy(tree);
    /*
     * Modificar e implementar con un ciclo una interfaz que permita al usuario
     * realizar una de las siguientes operaciones en cada iteración:
     *
     * 1 ........ Mostrar árbol por pantalla
     * 2 ........ Agregar un elemento
     * 3 ........ Eliminar un elemento
     * 4 ........ Chequear existencia de elemento
     * 5 ........ Mostrar longitud del árbol
     * 6 ........ Mostrar raiz, máximo y mínimo del árbol
     * 7 ........ Salir
     *
     * Se debe solicitar un número de entrada para realizar una de las acciones.
     *
     * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
     * elemento a agregar, eliminar o chequear respectivamente.
     *
     * Al salir debe liberarse toda la memoria utilizada.
     *
     */
    return (EXIT_SUCCESS);
}
