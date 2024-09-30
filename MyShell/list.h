#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define ERROR_CHECK if(errno != 0){ fprintf(stderr, "Memory allocation error\n"); perror(NULL); exit(errno);}
typedef char** list;
list split_into_words();
void printlist(list);
void clearlist(list*);
void print_entry();