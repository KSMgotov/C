#include "list.h"
/*Очистка списка*/
void clearlist(char*** lst){
    int i;
    if (*lst == NULL) return;
    for (i = 0; (*lst)[i] != NULL; i++)
        free((*lst)[i]);
    free(*lst);
    *lst = NULL;
}
/*Инициализация пустого списка*/
void null_list(list* lst, int* sizelist, int* curlist){
    *sizelist = 0;
    *curlist = 0;
    *lst = NULL;
}
/*Завершение создания списка*/
void termlist(list* lst, int* sizelist, int curlist){
    if (*lst == NULL) return;
    if (curlist > ((*sizelist) - 1)){
        *lst = realloc(*lst, ((*sizelist) + 1)*sizeof(**lst));
        //ERROR_CHECK
    }
    (*lst)[curlist] = NULL;
    *lst = realloc(*lst, ((*sizelist) = curlist+1)*sizeof(**lst));
    //ERROR_CHECK
}
/*Обнуление буфера под слово*/
void nullbuf(char** buf, int* sizebuf, int* curbuf){
    *buf = NULL;
    *sizebuf = 0;
    *curbuf = 0;
}
/*Добавление символа в слово*/
void addsym(int c, char** buf, int* sizebuf, int* curbuf){
    #define SIZE 16
    if ((*curbuf) > (*sizebuf) - 1)
    *buf = realloc(*buf, (*sizebuf) += SIZE);
    //ERROR_CHECK
    (*buf)[(*curbuf)++] = c;
}
/*Добавление слова в список*/
void addword(char*** lst, char** buf, int* sizebuf, int* sizelist, int* curbuf, int* curlist){
    #define SIZE 16
    if ((*curbuf) > (*sizebuf) - 1){
        *buf = realloc(*buf, (*sizebuf) += 1);
        //ERROR_CHECK
    }
    (*buf)[(*curbuf)++] = '\0';
    *buf = realloc(*buf, (*sizebuf) = (*curbuf));
    //ERROR_CHECK
    if ((*curlist) > (*sizelist) - 1){
        *lst = realloc(*lst, ((*sizelist) += SIZE)*sizeof(**lst));
        //ERROR_CHECK
    }
    (*lst)[(*curlist)++] = *buf;    
}
/*Печать списка*/
void printlist(char** lst){
    int i = 0;
    if (lst == NULL) return;
    while(lst[i] != NULL)
        printf("%s\n", lst[i++]);
}
/*Сортировка списка*/
void sortlist(char *** lst, int sizelist){
    char* temp;
    if (*lst == NULL) return;
    for (int i = 0; i < sizelist-2; i++)
        for(int j = i+1; j < sizelist-1; j++){
            if(strcmp((*lst)[i],(*lst)[j]) > 0){
                temp = (*lst)[i];
                (*lst)[i] = (*lst)[j];
                (*lst)[j] = temp;
            }
        }
}
/*Проверка на специальные символы*/
int symset(int c){
    return c != '\n' && c != ' ' &&
    c != '\t' && c != '>' && c != '<' &&
    c != '&' && c != '|' && c != ',' && c != ';'
    && c != EOF;
}
void print_entry(){
    int i, red = 227, green = 50, blue = 200;
    char* s, *color;
    s = malloc(1000);
    color = malloc(1000);
    snprintf(s, 1000, "%s%s%s%s", getenv("USER"), "@", getenv("PWD"), ">>");
    snprintf(color, 1000, "%s%d%s%d%s%d%s", "\033[38;2;", red, ";", green, ";" , blue, "m");
    i = 0;
    printf("%s", "\033[1m");
    printf("%s", color);
    while(s[i] != '\0'){
        putchar(s[i]);
        red = red - 3;
        green = green + 3;
        snprintf(color, 1000, "%s%d%s%d%s%d%s", "\033[38;2;", red, ";", green, ";" , blue, "m");
        printf("%s", color);
        i++;
    }
    free(s);
    free(color);
    printf("%s", "\033[0m");
    return;
}
list split_into_words(){
    typedef enum {Start, Word, Greater, Greater2} vertex;
    vertex V = Start;
    int c,temp;
    list lst;
    char* buf;
    int sizebuf;
    int sizelist;
    int curbuf;
    int curlist;
    c = getchar();
    while(c == '\n'){
        print_entry();
        c = getchar();
    }
    if(c == EOF){
        printf("\n");
        exit(0);
    }
    null_list(&lst, &sizelist, &curlist);
        while (1) switch(V){
        case Start:
            if(c == ' ' || c == '\t') c = getchar();
            else if (c == EOF || c == '\n' || c == '#'){
                termlist(&lst, &sizelist, curlist);
                return lst;
            }
            else {
                nullbuf(&buf, &sizebuf, &curbuf);
                addsym(c, &buf, &sizebuf, &curbuf);
                if(c == '>' || c == '|'){
                    V = Greater;
                    temp = c;
                }
                else V = (c == '<' || c == ',' || c == ';' || c == '&')? Greater2 : Word;
                c = getchar();
            }
        break;
        case Word:
            if(symset(c)){
                addsym(c, &buf, &sizebuf, &curbuf);
                c = getchar();
            }
            else{
                V = Start;
                addword(&lst, &buf, &sizebuf, &sizelist, &curbuf, &curlist);
            }
        break;
        case Greater:
            if(c == temp){
                addsym(c, &buf, &sizebuf, &curbuf);
                c = getchar();
                V = Greater2;
            }
            else{
                V = Start;
                addword(&lst, &buf, &sizebuf, &sizelist, &curbuf, &curlist);
            }
        break;
        case Greater2:
            V = Start;
            addword(&lst, &buf, &sizebuf, &sizelist, &curbuf, &curlist);
        break;
    }
}