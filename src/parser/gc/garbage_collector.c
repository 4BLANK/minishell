#include "../../../includes/minishell.h"

t_ast_gc *new_gb(void *ptr)
{
    t_ast_gc *gb;
    
    gb = malloc(sizeof(t_ast_gc));
    if (gb == NULL)
        return (NULL);
    gb->ptr = ptr;
    gb->next = NULL;
    return (gb);
}

void add_gb(t_ast_gc **lst, t_ast_gc *new_node)
{
	t_ast_gc    *node;

	if (new_node != NULL)
	{
		if (*lst == NULL)
			*lst = new_node;
		else
		{
			node = *lst;
			while (node->next != NULL)
			{
				node = node->next;
			}
			node->next = new_node;
		}
	}
}

void ptr_collector(void *ptr)
{
    t_ast_gc *gb;

    gb = new_gb(ptr);
    if (gb == NULL)
        return (gb);
    add_gb(&sh->trash, gb);
}