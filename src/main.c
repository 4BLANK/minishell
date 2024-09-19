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
        if (!sh->ex_status)
        {
            printf(GREEN "\n== AST =================>\n" RESET);
            print_ast_tree(ast, 0);
            // EXECTUTE AST
            //kickoff(ast);
            // DISTROY AST`
            //ast_distroy(&ast);
            if (ft_strcmp("export", ast->data.childs.left->data.arg_list->content))
            {
                printf("1\n");
                export_cmd(ast->data.childs.left->data.arg_list);
            }
        }
    }   
    return (EXIT_SUCCESS);
}
