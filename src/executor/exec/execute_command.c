#include "../../../includes/minishell.h"

int parent_routine(pid_t pid, int *status, char *cmd, t_pair *pl)
{
    ft_printf("\n[DEBUG] BEFORE\n");
    if (pl && !(pl->right) && !(pl->left) && !(is_built_in(cmd)))
    {
        ft_printf("\n[DEBUG] INSIDE\n");
        waitpid(pid, status, 0);
        if (WIFEXITED(*status))
            *status = WEXITSTATUS(*status);
        else
        {
            //*status = WTERMSIG(*status);
            *status += 128;
            ft_printf("\n");
        }
    }
    ft_printf("\n[DEBUG] AFTER\n");
    return (*status);
}

int child_routine(t_ast_node *node, t_pair *pl, int pipefd[2], char **cmd_path)
{
    handle_signals(CHILD);
    if (get_commandpath(cmd_path, sh->args[0]))
      return (EXIT_FAILURE);
    if (redirect(node, &(pl->left), &(pl->right)))
      exit(EXIT_FAILURE);
    if (pl->right)
      dup2(pipefd[1], STDOUT_FILENO);
    if (pl->left)
      dup2(pipefd[0], STDIN_FILENO);
    if (pipefd)
    {
        close(pipefd[1]);
        close(pipefd[0]);
    }
    if (execv(*cmd_path, sh->args) < 0)
      exit(sh->ex_status);
    exit(EXIT_SUCCESS);
}

int execute_command(t_ast_node *node, t_pair *pl, int pipefd[2], pid_t *last_pid)
{
  int status;
  char *cmd_path;
  pid_t pid;

  cmd_path = NULL;
  sh->args = lst_tostrarray(node->data.childs.left->data.arg_list);
  status = 0;
  get_commandpath(&cmd_path, sh->args[0]);
  if (!is_built_in(sh->args[0]) && pre_exec_errors(sh->args[0], cmd_path))
    return (sh->ex_status);
  if (built_ins(sh->args, &status, pl, pipefd))
    return (status);
  pid = fork();
  if (last_pid)
      *last_pid = pid;
  if (pid > 0)
    return (parent_routine(pid, &status, sh->args[0], pl));
  else
    exit(child_routine(node, pl, pipefd, &cmd_path));
}
