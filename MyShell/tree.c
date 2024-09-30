#include "tree.h"
void make_shift(int n){
    while(n--)
        putc(' ', stderr);
}

void print_argv(char **p, int shift){
    char **q=p;
    if(p!=NULL){
        while(*p!=NULL){
             make_shift(shift);
             fprintf(stderr, "argv[%d]=%s\n",(int) (p-q), *p);
             p++;
        }
    }
}
void clear_tree(tree t){
    int i = 0;
    if(t == NULL) return;
    clear_tree(t->next);
    t->next = NULL;
    clear_tree(t->pipe);
    t->pipe = NULL;
    free(t->infile);
    free(t->outfile);
    while((t->argv)[i] != NULL){
        free((t->argv)[i]);
        i++;
    }
    free(t->argv);
    free(t);
    return;
}
void print_tree(tree t, int shift){
    char **p;
    if(t==NULL)
        return;
    p=t->argv;
    if(p!=NULL)
        print_argv(p, shift);
    else{
        make_shift(shift);
        fprintf(stderr, "psubshell\n");
    }
    make_shift(shift);
    if(t->infile==NULL)
        fprintf(stderr, "infile=NULL\n");
    else
        fprintf(stderr, "infile=%s\n", t->infile);
    make_shift(shift);
    if(t->outfile==NULL)
        fprintf(stderr, "outfile=NULL\n");
    else
        fprintf(stderr, "outfile=%s\n", t->outfile);
    make_shift(shift);
    fprintf(stderr, "append=%d\n", t->append);
    make_shift(shift);
    fprintf(stderr, "background=%d\n", t->backgrnd);
    make_shift(shift);
    if(t->pipe==NULL)
        fprintf(stderr, "pipe=NULL \n");
    else{
        fprintf(stderr, "pipe---> \n");
        print_tree(t->pipe, shift+5);
    }
    make_shift(shift);
    if(t->next==NULL)
        fprintf(stderr, "next=NULL \n");
    else{
        fprintf(stderr, "next---> \n");
        print_tree(t->next, shift+5);
    }
}
int not_special(char* s){
    return (strcmp(s, "|") && strcmp(s, ";") && strcmp(s, "<") && strcmp(s, ">") && strcmp(s, ">>") && strcmp(s, "&"));
}
void read_arguments(tree t, list l, int* track){
    int i = 0, maxlen = 0, last_arg;
    while((l[i] != NULL) && (not_special(l[i]))){
        if(strlen(l[i]) > maxlen) maxlen = strlen(l[i]);
        i++;
    }
    t->argv = calloc(i+1, sizeof(char*));
    last_arg = i;
    for(i = 0; i < last_arg; i++){
        (t->argv)[i] = malloc(maxlen+1);
        strcpy((t->argv)[i], l[i]);
    }
    (t->argv)[last_arg] = NULL;
    *track = *track + last_arg;
}
tree new_node(){
    tree t;
    t = malloc(sizeof(node));
    t->infile = NULL;
    t->outfile = NULL;
    t->append = 0;
    t->backgrnd = 0;
    t->pipe = NULL;
    t->argv = NULL;
    return t;
}
tree build_tree(list l){
    #define SYNTAX_ERROR {fprintf(stderr, "Некорректный синтаксис\n");clear_tree(t);return NULL;}
    typedef enum{Start, New_Command, Check} vertex;
    vertex V = Start;
    tree t = NULL, current, tmp;
    int i = 0;
    if(l == NULL) return NULL;
    t = new_node();
    current = t;
    while(1) 
        switch(V){
        case Start:
            read_arguments(current, l + i, &i);
            V = Check;
        case Check:
            if(l[i] == NULL) return t;
            if(strcmp(l[i], "|") == 0){
                tmp = current;
                while(strcmp(l[i], "|") == 0){
                    current->pipe = new_node();
                    i++;
                    read_arguments(current->pipe, l + i, &i);
                    if(l[i] == NULL) return t;
                    current = current->pipe;
                }
                current = tmp;
            }
            if(strcmp(l[i], "<") == 0){
                i++;
                if(l[i] == NULL) SYNTAX_ERROR;
                current->infile = malloc(strlen(l[i] + 1));
                strcpy(current->infile, l[i]);
                i++;
            }
            if(strcmp(l[i], ">") == 0){
                i++;
                if(l[i] == NULL) SYNTAX_ERROR;
                tmp = current;
                while(tmp->pipe != NULL) tmp = tmp->pipe;
                tmp->outfile = malloc(strlen(l[i] + 1));
                strcpy(tmp->outfile, l[i]);
                i++;
            }
            if(strcmp(l[i], ">>") == 0){
                i++;
                if(l[i] == NULL) SYNTAX_ERROR;
                tmp = current;
                while(tmp->pipe != 0) tmp = tmp->pipe;
                tmp->outfile = malloc(strlen(l[i] + 1));
                strcpy(tmp->outfile, l[i]);
                tmp->append = 1;
                i++;

            }
            if(strcmp(l[i], ";") == 0){
                V = New_Command;
                break;
            }
            if(strcmp(l[i], "&") == 0){
                current->backgrnd = 1;
                tmp = current;
                while((tmp->pipe) != NULL){
                    tmp = tmp->pipe;
                    tmp->backgrnd = 1;
                }
                V = New_Command;
            }
        break;
        case New_Command:
            i++;
            if(l[i] == NULL) return t;
            current->next = new_node();
            current = current->next;
            V = Start;
    }
}