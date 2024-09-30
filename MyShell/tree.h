#include "list.h"
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>

enum type_of_next{
    NXT, AND, OR   // виды связей соседних команд в списке команд
};

struct cmd_inf {
    char ** argv; // список из имени команды и аргументов
    char *infile; // переназначенный файл стандартного ввода
    char *outfile; // переназначенный файл стандартного вывода
    int append;
    int backgrnd; // =1, если команда подлежит выполнению в фоновом режиме
    struct cmd_inf* pipe; // следующая команда после "|"
    struct cmd_inf* next; // следующая после ";"
};

typedef struct cmd_inf *tree;
typedef struct cmd_inf node;

void print_tree(tree, int);
tree build_tree(list);
void clear_tree(tree);