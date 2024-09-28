#include "../../../includes/parser.h"

// t_argument *args_table(t_token **tokens, t_node_type type)
// {
//     t_argument *args;
//     int flag;

//     flag = 0;
//     args = NULL;
//     if ((*tokens) != NULL && is_schar((*tokens)->lexem) == 1)
//         flag = 1;
//     while ((*tokens) != NULL && (*tokens)->lexem != PIPE 
//         && (*tokens)->lexem != AND && (*tokens)->lexem != OR
//         && (*tokens)->lexem != OPEN_P && (*tokens)->lexem != CLOSE_P)
//     {
//         if (type == ARGUMENTS)
//         {
//             if (is_schar((*tokens)->lexem) != 0 && flag != 1)
//                 return args;
//             ft_argsadd_back(&args, ft_argsnew(ft_strdup((*tokens)->content)));
//         }
//         flag = 0;
//         *tokens = (*tokens)->next;
//     }
//     // if (*tokens != NULL)
//     //     printf("%s\n", lexs_type[(*tokens)->lexem]);
//     return args;
// }

// int redirection_found(t_token *tokens)
// {
//     while (tokens != NULL && tokens->lexem != PIPE && tokens->lexem != OR 
//         && tokens->lexem != AND && tokens->lexem != CLOSE_P && tokens->lexem != OPEN_P)
//     {
//         if (tokens->lexem == I_REDIRECTION || tokens->lexem == O_REDIRECTION 
//             || tokens->lexem == HEREDOC || tokens->lexem == APPEND)
//         {
//             return 1;
//         }
//         tokens = tokens->next;
//     }
//     return 0;
// }

t_ast_node *ast_create_node(t_node_type type, t_argument *args, t_file *files)
{
    t_ast_node *new_node;

    new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
    if (new_node == NULL)
        return NULL;
    // ptr_collector(new_node, NULL, NULL);        
    new_node->type = type;
    new_node->data.childs.right = NULL;
    new_node->data.childs.left = NULL;
    if (args != NULL)
        new_node->data.arg_list = args;
    else if (files != NULL)
        new_node->data.files = files;
    return new_node;
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

void	clear_fileslst(t_file **lst)
{
	t_file	*node;
	t_file	*next;

	if (lst && *lst)
	{
		node = *lst;
		while (node != NULL)
		{
			next = node->next;
		    free(node->name);
		    free(node);
			node = next;
		}
		*lst = NULL;
	}
}

void destroy_ast_core(t_ast_node *node)
{
    if (!node)
        return;
    if (node->type != REDIRECTION && node->type != ARGUMENTS)
    {
        if (node->data.childs.left)
        {
            destroy_ast_core(node->data.childs.left);
            //free(node->data.childs.left);
        }
        if (node->data.childs.right)
        {
            destroy_ast_core(node->data.childs.right);
            //free(node->data.childs.right);
        }
    }
    else
    {
        if (node->type == REDIRECTION)
        {
            clear_fileslst(&node->data.files);
        }
        else if (node->type == ARGUMENTS)
        {
            clear_argslst(&node->data.arg_list); 
        }
    }
    free(node);
}

void ast_distroy(t_ast_node **node)
{
    if (*node)
    {
        destroy_ast_core(*node);
        *node = NULL;
    }
}

void	addfile_back(t_file **lst, t_file *new)
{
	t_file	*node;

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

t_file	*new_file(void *file_name, t_lexeme filetype)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	file->name = file_name;
    file->type = filetype;
	file->next = NULL;
	return (file);
}

t_ast_node *form_command(t_token **tokenlst)
{
    void *tmp;
    t_file *files;
    t_argument *args;
    t_ast_node *command;
    int lex_tmp;

    args = NULL;
    files = NULL;
    command  = NULL;
    while (*tokenlst != NULL && is_schar((*tokenlst)->lexem) != 2)
    {
        if (is_schar((*tokenlst)->lexem) == 1)
        {
            lex_tmp = (*tokenlst)->lexem;
            *tokenlst = (*tokenlst)->next;
            if ((*tokenlst)->lexem == AMBIGUOUS)
                lex_tmp = AMBIGUOUS;
            tmp = (t_file *)new_file(ft_strdup((*tokenlst)->content), lex_tmp);
            if (tmp == NULL)
                return (NULL);
            addfile_back(&files, tmp);
        }
        else if (is_schar((*tokenlst)->lexem) == 0)
        {
            tmp = (t_argument *)ft_argsnew(ft_strdup((*tokenlst)->content));
            if (tmp == NULL)
                return (NULL);
            ft_argsadd_back(&args, tmp);
        }
        tmp = NULL;
        *tokenlst = (*tokenlst)->next;
    }
    if (args == NULL && files == NULL)
        return (NULL);
    // ptr_collector(NULL, files, NULL);
    // ptr_collector(NULL, files, args);    
    command = ast_create_node(COMMAND, NULL, NULL);
    if (command == NULL)
        return NULL;
    command->data.childs.left = ast_create_node(ARGUMENTS, args, NULL);
    command->data.childs.right = ast_create_node(REDIRECTION, NULL, files);
    return (command);
}