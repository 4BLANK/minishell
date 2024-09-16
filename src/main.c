#include "../includes/minishell.h"

t_shell *sh;

int main (void)
{
  char *line;
  t_ast_node *ast;
  
    ast = NULL;
    sh = setshell(__environ);
    while (1)
    {
        line = readline("-> ");
        add_history(line);
        sh->ex_status = parser(&ast, line);
        if (ast != NULL)
        {
            printf(GREEN "\n== AST =================>\n" RESET);
            print_ast_tree(ast, 0);
            // EXECTUTE AST
            //kickoff(ast);
            // DISTROY AST`
            // ast_distroy(&ast);
        }
    }   
    return (EXIT_SUCCESS);
}
