#include "../../../includes/minishell.h"

void	ft_argsadd_back(t_argument **lst, t_argument *new)
{
	t_argument	*node;

	if (new != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			node = *lst;
			while (node->next != NULL)
			{
				node = node->next;
			}
			node->next = new;
		}
	}
}

t_argument	*ft_argsnew(void *content)
{
	t_argument	*node;

	node = (t_argument *)malloc(sizeof(t_argument));
	if (node == NULL)
		return (0);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	clear_argslst(t_argument **lst)
{
	t_argument	*node;
	t_argument	*next;

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

int is_schar (t_lexeme lexem)
{
    if (lexem == O_REDIRECTION || lexem == I_REDIRECTION 
        || lexem == HEREDOC || lexem == APPEND)
        return 1;
    else if (lexem == PIPE || lexem == AND || lexem == OR 
        || lexem == OPEN_P || lexem == CLOSE_P)
        return 2;
    return 0;
}

void print_args(t_argument *args)
{
    while (args != NULL)
    {
        printf(" %s ->", args->content);
        args = args->next;
    }
    printf(" null");
}

void print_files(t_file *files)
{
    while (files != NULL)
    {
        printf(" %s(%s) ->", files->name, lexs_type[files->type]);
        files = files->next;
    }
    printf(" null");
}

void print_space(int space)
{
    int i;

    i = -1;
    while (++i < space)
        printf("  ");
}

void print_ast_tree(t_ast_node *ast_tree, int space)
{
    if (ast_tree == NULL)
        return ;
    print_space(space);
    printf(" > %s ", ast_node_types[ast_tree->type]);
    if (ast_tree->type == ARGUMENTS)
    {
        printf("|");
        print_args(ast_tree->data.arg_list);
    }
    else if (ast_tree->type == REDIRECTION)
    {
        printf("|");
        print_files(ast_tree->data.files);
    }
    printf("\n");
    if (ast_tree->type == COMMAND || ast_tree->type == PIPELINE /*|| ast_tree->type == REDIRECTION*/
    || ast_tree->type == AND_NODE || ast_tree->type == OR_NODE 
    || ast_tree->type == GROUP_NODE)
    {
        if (ast_tree->data.childs.left != NULL)
        {
            print_ast_tree(ast_tree->data.childs.left, space + 1);
        }
        else
        {
            print_space(space + 1);
            printf("\n");
        }

        if (ast_tree->data.childs.right != NULL)
        {
            print_ast_tree(ast_tree->data.childs.right, space + 1);
        }
        else
        {
            print_space(space + 1);
            printf("\n");
        }
    }
}