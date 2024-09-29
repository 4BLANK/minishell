#include "../../../includes/minishell.h"

// void distroy_gc(t_ast_gc **lst)
// {
// 	t_ast_gc	*node;
// 	t_ast_gc	*next;

// 	if (lst && *lst)
// 	{
// 		node = *lst;
// 		while (node != NULL)
// 		{
// 			next = node->next;
// 		    if (node->node != NULL)
// 				free(node->node);
// 			else if (node->files != NULL)
// 				clear_fileslst(&(node->files), 0);
// 			else if (node->args != NULL)
// 				clear_argslst(&(node->args));
// 			free(node);
// 			node = next;
// 		}
// 		*lst = NULL;
// 	}
// }

// t_ast_gc *new_gb(t_ast_node *n, t_file *f, t_argument *a)
// {
//     t_ast_gc *gb;
    
//     gb = malloc(sizeof(t_ast_gc));
//     if (gb == NULL)
//         return (NULL);
//     gb->node = n;
// 	gb->files = f;
//     gb->args = a;
//     return (gb);
// }

// void add_gb(t_ast_gc **lst, t_ast_gc *new_node)
// {
// 	t_ast_gc    *node;

// 	if (new_node != NULL)
// 	{
// 		if (*lst == NULL)
// 			*lst = new_node;
// 		else
// 		{
// 			node = *lst;
// 			while (node->next != NULL)
// 			{
// 				node = node->next;
// 			}
// 			node->next = new_node;
// 		}
// 	}
// }

// void ptr_collector(t_ast_node *n, t_file *f, t_argument *a)
// {
//     t_ast_gc *gb;

//     gb = new_gb(n, f, a);
//     if (gb == NULL)
//         return ;
//     add_gb(&sh->trash, gb);
// }