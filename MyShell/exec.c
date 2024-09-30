#include "exec.h"
void launch_node(tree t){
    #define OPEN_ERROR_CHECK if(f < 0){fprintf(stderr, "Не удалось открыть файл\n");exit(1);}
    int f, fd[2], in, out, next_in, i, count;
    tree tmp;
    if(t->pipe != NULL){
        count = 2;
        pipe(fd);
        out = fd[1];
        next_in = fd[0];
        if(fork() == 0){
            close(next_in);
            dup2(out, 1);
            close(out);
            if(t->infile != NULL){
                f = open(t->infile, O_RDONLY);
                OPEN_ERROR_CHECK
                dup2(f, 0);
                close(f);
            }
            execvp(t->argv[0], t->argv);
        }
        tmp = t->pipe;
        in = next_in;
        while(tmp->pipe != NULL){
            close(out);
            pipe(fd);
            out = fd[1];
            next_in = fd[0];
            if(fork() == 0){
                close(next_in);
                dup2(in, 0);
                close(in);
                dup2(out, 1);
                close(out);
                execvp(tmp->argv[0], tmp->argv);
            }
            count++;
            close(in);
            in = next_in;
            tmp = tmp->pipe;
        }
        close(out);
        if(fork() == 0){
            dup2(in, 0);
            close(in);
            if(tmp->outfile != NULL){
                f = open(tmp->outfile, O_WRONLY|O_CREAT|(tmp->append == 0 ? O_TRUNC : O_APPEND));
                OPEN_ERROR_CHECK
                dup2(f, 1);
                close(f);
            }
            execvp(tmp->argv[0], tmp->argv);
        }
        close(in);
        if(t->backgrnd == 0) for(i = 0; i < count; i++) wait(NULL);
    }
    else{
        if(fork() == 0){
            if(t->infile != NULL){
                f = open(t->infile, O_RDONLY);
                OPEN_ERROR_CHECK
                dup2(f, 0);
                close(f);
            }
            if(t->outfile != NULL){
                f = open(t->outfile, O_WRONLY|O_CREAT|(t->append == 0 ? O_TRUNC : O_APPEND));
                OPEN_ERROR_CHECK
                dup2(f, 1);
                close(f);
            }
            execvp(t->argv[0], t->argv);
        }
        if (t->backgrnd == 0) wait(NULL);
    }
}
void execute(tree t){
    while(t != NULL){
        if(t->backgrnd == 0){
            launch_node(t);
        }
        else{
            if(fork() == 0){
                launch_node(t);
                exit(0);
            }
            wait(NULL);
        }
        t = t->next;
    }
    return;
}