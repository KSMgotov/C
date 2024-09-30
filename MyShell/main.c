#include "exec.h"
int main(){
    //signal(SIGINT, SIG_IGN);
    while(1){
        print_entry();
        list lst = NULL;
        tree t = NULL;
        lst = split_into_words();
        t = build_tree(lst);
        //print_tree(t, 4);
        execute(t);
        clearlist(&lst);
        clear_tree(t);
    }
    return 0;
}