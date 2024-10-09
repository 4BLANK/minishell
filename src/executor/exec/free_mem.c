#include "../../../includes/minishell.h"

static void	too_manylines(int *status)
{
	if (sh && sh->args)
	{
		free_strarray(sh->args);
		sh->args = NULL;
	}
	if (sh && sh->ast)
	{
		ast_distroy(&(sh->ast), 1);
		sh->ast = NULL;
	}
	if (sh && sh->envlst)
	{
		distroy_envlst(&(sh->envlst));
		sh->envlst = NULL;
	}
	if (sh)
	{
		*status = sh->ex_status;
		free(sh);
		sh = NULL;
	}
}

int	free_mem(int flag)
{
	int	status;

	status = 0;
	if (flag == 1)
		too_manylines(&status);
	else
	{
		if (sh && sh->args)
		{
			free_strarray(sh->args);
			sh->args = NULL;
		}
		if (sh && sh->ast)
		{
			ast_distroy(&(sh->ast), 1);
			sh->ast = NULL;
		}
	}
	return (status);
}
