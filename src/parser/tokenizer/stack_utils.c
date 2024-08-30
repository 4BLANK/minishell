#include "../../../includes/minishell.h"

int	ft_stack_size(t_token *s)
{
	if (s == NULL)
		return (0);
	return (1 + ft_stack_size(s->next));
}

void	reverse_rotate(t_token **s)
{
	t_token	*second_last;
	t_token	*last;

	if (ft_stack_size(*s) < 2)
		return ;
	last = *s;
	second_last = NULL;
	while (last->next != NULL)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *s;
	*s = last;
}

void	rotate(t_token **s)
{
	t_token	*first;
	t_token	*secound;
	t_token	*current;

	if (ft_stack_size(*s) < 2)
		return ;
	first = *s;
	secound = (*s)->next;
	current = secound;
	while (current->next != NULL)
		current = current->next;
	first->next = NULL;
	current->next = first;
	*s = secound;
}