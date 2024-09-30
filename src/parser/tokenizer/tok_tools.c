#include "../../../includes/minishell.h"

void	tokens_lstclear(t_token **lst)
{
	t_token	*node;
	t_token	*next;

	if (lst && *lst)
	{
		node = *lst;
		while (node != NULL)
		{
			next = node->next;
		  free(node->content);
		  free(node);
			node = next;
		}
		*lst = NULL;
	}
}