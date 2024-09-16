#include "../../includes/minishell.h"

void handler(int sig)
{
  if (sig == SIGINT)
  {
    rl_on_new_line();
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_redisplay();
  }
}

void handle_signals(int mode)
{
  if (mode == PARENT)
  {
    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
  }
  if (mode == CHILD)
  {
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
  }
  if (mode == IGNORE)
  {
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
  }
}
