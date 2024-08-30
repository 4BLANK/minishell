#include "../includes/minishell.h"

//TODO: ADD HISTORY
//TODO: FIX REDIRECTION AST
//TODO: parser()
//TODO: expand exit status
int main (int ac, char **av, char **env)
{
    char *line;
    t_ast_node *ast;

    (void)ac;
    (void)av;
    ast = NULL;
    while (1)
    {
        line = readline("-> ");
        add_history(line);
        parser(&ast, line, env);
        print_ast_tree(ast, 0);
        if (execute_cmd(ast, env))
            printf("execute error\n");
    }   
    return (0);
}
