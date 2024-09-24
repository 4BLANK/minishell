#include "../includes/minishell.h"

t_shell *sh;

int main (void)
{
  char *line;
  // struct sigaction sa;
  t_ast_node *ast;

  ast = NULL;
  sh = setshell(__environ);
  sh->tmps = NULL;
  while (1)
  {
    handle_signals(PARENT);
    line = readline("-> ");
    handle_signals(IGNORE);
    if (!line)
      exit(0);
    add_history(line);
    sh->ex_status = parser(&ast, line);
    if (ast != NULL)
    {
      // printf(GREEN "\n== AST =================>\n" RESET);
      print_ast_tree(ast, 0);
      // EXECTUTE AST
      sh->ex_status = kickoff(ast);
      // DISTROY AST
      distroy_tmps(&sh->tmps);
      ast_distroy(&ast);
    }
  }  
  return (EXIT_SUCCESS);
}
