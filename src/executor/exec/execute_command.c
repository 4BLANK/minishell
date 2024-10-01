#include "../../../includes/minishell.h"

int parent_routine(pid_t pid, int *status, char *cmd_path)
{
  (void) cmd_path;
  waitpid(pid, status, 0);
  if (WIFEXITED(*status))
    *status = WEXITSTATUS(*status);
  else
  {
      //*status = WTERMSIG(*status);
      *status += 128;
      printf("\n");
  }
  return (*status);
}

int child_routine(t_ast_node *node, t_pair *pipe_location, int pipefd[2], char **cmd_path)
{
    handle_signals(CHILD);
    if (get_commandpath(cmd_path, sh->args[0]))
      return (EXIT_FAILURE);
    if (redirect(node, &(pipe_location->left), &(pipe_location->right)))
      exit(EXIT_FAILURE);
    if (pipe_location->right)
      dup2(pipefd[1], STDOUT_FILENO);
    if (pipe_location->left)
      dup2(pipefd[0], STDIN_FILENO);
    if (execv(*cmd_path, sh->args) < 0)
      exit(sh->ex_status);
    exit(EXIT_SUCCESS);
}

int execute_command(t_ast_node *node, int left, int right, int pipefd[2])
{
  int status;
  char *cmd_path;
  pid_t pid;
  t_pair pipe_location;

  cmd_path = NULL;
  pipe_location.left = left;
  pipe_location.right = right;
  sh->args = lst_tostrarray(node->data.childs.left->data.arg_list);
  status = 0;
  get_commandpath(&cmd_path, sh->args[0]);
  if (!is_built_in(sh->args[0]) && pre_exec_errors(sh->args[0], cmd_path))
    return (sh->ex_status);
  if (built_ins(sh->args, &status, &pipe_location, pipefd))
    return (status);
  pid = fork();
  if (pid > 0)
    return (parent_routine(pid, &status, cmd_path));
  else
    exit(child_routine(node, &pipe_location, pipefd, &cmd_path));
}
