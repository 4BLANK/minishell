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

// ============================================================================ //

t_ast_node *alloc_ast_node(t_node_type type, t_argument *args)
{
    t_ast_node *new_node;

    new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
    if (new_node == NULL)
        return NULL;
    new_node->type = type;
    if (args != NULL)
        new_node->data.arg_list = args;
    return new_node;
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



int pipe_exist(t_token *tokens)
{
    while (tokens != NULL)
    {
        if (tokens->lexem == PIPE)
            return 1;
        tokens = tokens->next;
    }
    return 0;
}

// t_ast_node *insert_right(t_ast_node *root, t_token *node){} 
// t_ast_node *insert_left(t_node_type *head, t_node_type *node){}

// ls > ls > ls



// t_ast_node *new_ast_node(t_node_type type, t_token *tokens)
// {
//     t_ast_node *node;
//     t_token *tmp;

//     tmp = NULL;
//     node = alloc_ast_node(type, NULL);
//     if (type == COMMAND && tokens != NULL)
//     {
//         node->data.childs.right = alloc_ast_node(ARGUMENTS, args_table(tokens, ARGUMENTS));
//         if (redirection_found(tokens))
//         {
//             while(tokens != NULL && is_schar(tokens->lexem) == 0)
//                 tokens = tokens->next;
//             node->data.childs.left = get_redirection_tree(REDIRECTION, tokens);
            
//         }
//     }
//     return node;
// }


// t_ast_node *generate_ast_tree(t_token *tokens)
// {
//     t_ast_node *root;
//     t_ast_node *tmp;
//     t_token *head;

//     head = tokens;
//     root = NULL;
//     tmp = NULL;
//     while (head != NULL)
//     {
//         if (root == NULL)
//         {
//             root = new_ast_node(COMMAND, head);
//         }
//         else 
//         {
//             if (head->lexem == CMD)
//             {
//                 tmp = new_ast_node(COMMAND, head);
//                 if (root->data.childs.right == NULL)
//                 {
//                     root->data.childs.right = tmp;
//                 }
//                 else 
//                 {
//                     root->data.childs.left = tmp;
//                 }
//                 tmp = NULL;
//             }
//             else if (head->lexem == PIPE)
//             {

//                 tmp = new_ast_node(PIPELINE, NULL);
//                 {
//                     tmp->data.childs.right = root;
//                     root = tmp;
//                 }
//                 root = tmp;
//                 tmp = NULL;
//             }
//         }
//         head = head->next;
//     }
//     return root;
// }

void print_args(t_argument *args)
{
    while (args != NULL)
    {
        printf("[ %s ] -> ", args->content);
        args = args->next;
    }
    printf("[ null ]");
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
    printf("--> %s ", ast_node_types[ast_tree->type]);
    if (ast_tree->type == ARGUMENTS)
        print_args(ast_tree->data.arg_list);
    printf("\n");
    if (ast_tree->type == COMMAND || ast_tree->type == PIPELINE || ast_tree->type == REDIRECTION
    || ast_tree->type == AND_NODE || ast_tree->type == OR_NODE)
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