#include "../../../includes/parser.h"

t_argument *args_table(t_token **tokens, t_node_type type)
{
    t_argument *args;
    int flag;

    flag = 0;
    args = NULL;
    if ((*tokens) != NULL && is_schar((*tokens)->lexem) == 1)
        flag = 1;
    while ((*tokens) != NULL && (*tokens)->lexem != PIPE 
        && (*tokens)->lexem != AND && (*tokens)->lexem != OR
        && (*tokens)->lexem != OPEN_P && (*tokens)->lexem != CLOSE_P)
    {
        if (type == ARGUMENTS)
        {
            if (is_schar((*tokens)->lexem) != 0 && flag != 1)
                return args;
            ft_argsadd_back(&args, ft_argsnew(ft_strdup((*tokens)->content)));
        }
        flag = 0;
        *tokens = (*tokens)->next;
    }
    // if (*tokens != NULL)
    //     printf("%s\n", lexs_type[(*tokens)->lexem]);
    return args;
}

int redirection_found(t_token *tokens)
{
    while (tokens != NULL && tokens->lexem != PIPE && tokens->lexem != OR 
        && tokens->lexem != AND && tokens->lexem != CLOSE_P && tokens->lexem != OPEN_P)
    {
        if (tokens->lexem == I_REDIRECTION || tokens->lexem == O_REDIRECTION 
            || tokens->lexem == HEREDOC || tokens->lexem == APPEND)
        {
            return 1;
        }
        tokens = tokens->next;
    }
    return 0;
}

t_ast_node *ast_create_node(t_node_type type, t_argument *args)
{
    t_ast_node *new_node;

    new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
    if (new_node == NULL)
        return NULL;
    new_node->type = type;
    new_node->data.childs.right = NULL;
    new_node->data.childs.left = NULL;
    if (args != NULL)
        new_node->data.arg_list = args;
    return new_node;
}

void ast_delete(t_ast_node *node)
{
    if (node == NULL)
        return ;
    if (node->type == ARGUMENTS)
    {
        free(node->data.arg_list);
        free(node);
        return ;
    }
    if (node->data.childs.right == NULL 
        && node->data.childs.left == NULL)
        free(node);
    ast_delete(node->data.childs.left);
    ast_delete(node->data.childs.right);
}