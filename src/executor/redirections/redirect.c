#include "../../../includes/minishell.h"

int redirect(t_ast_node *cmd, int *left, int *right)
{
  t_file *tmp;
  int status;

  if (!(cmd->data.childs.right))
    return (EXIT_SUCCESS);
  tmp = cmd->data.childs.right->data.files;
  status = EXIT_SUCCESS;
  while (tmp)
  {
    if (tmp->type == O_REDIRECTION)
    {
      *right = 0;
      status = redirect_output(tmp->name);
    }
    if (tmp->type == I_REDIRECTION || tmp->type == HEREDOC)
    {
      *left = 0;
      status = redirect_input(tmp->name);
    }
    if (tmp->type == APPEND)
    {
      *right = 0;
      status = append_redirect_output(tmp->name);
    }
    if (status)
      return (status);
    tmp = tmp->next;
  }
  return (0);
}
