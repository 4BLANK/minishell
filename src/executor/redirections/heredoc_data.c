#include "../../../includes/minishell.h"

void set_heredoc_signal_data(t_token **t, char *f, char *d, int fd)
{
  shd()->tokens = t;
  shd()->filename = f;
  shd()->delimiter = d;
  shd()->fd = fd;
}

t_hdata *shd()
{
  static t_hdata hdata;
  return (&hdata);
}
