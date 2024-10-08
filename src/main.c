#include "../includes/minishell.h"

t_shell *sh;

int main (void)
{
  char *line;
  int status;
  // struct sigaction sa;
  t_ast_node *ast;

  ast = NULL;
  sh = setshell(__environ);
  while (1)
  {
    handle_signals(PARENT);
    line = readline("-> ");
    handle_signals(IGNORE);
    if (!line)
      exit_cmd(NULL, &ast);
    if (line[0] != '\0')
      add_history(line);
    status = parser(&ast, line);
    if (status != 0)
      sh->ex_status = status;  
    if (ast != NULL && !status)
    {
      printf(GREEN "\n== AST =================>\n" RESET);
      print_ast_tree(ast, 0);
      // EXECTUTE AST
      sh->ast = ast;
      sh->ex_status = kickoff(ast);
      // DISTROY AST
      free_mem(0);
      /*ast_distroy(&ast, 1);*/
    }
  }  
  return (EXIT_SUCCESS);
}


