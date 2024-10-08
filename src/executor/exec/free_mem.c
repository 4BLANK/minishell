#include "../../../includes/minishell.h"

void free_mem()
{
  if (sh->args)
  {
    free_strarray(sh->args);
    sh->args = NULL;
  }
  if (sh->envlst)
  {
    distroy_envlst(&(sh->envlst));
    sh->envlst = NULL;
  }
  if (sh->ast)
  {
    ast_distroy(&(sh->ast), 1);
    sh->ast = NULL;
  }
}
