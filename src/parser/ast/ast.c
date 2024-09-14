#include "../../../includes/parser.h"

t_ast_node *command_line(t_token **cur_token);

t_ast_node *command_line_or(t_token **cur_token);
t_ast_node *command_line_or_1(t_token **cur_token);
t_ast_node *command_line_or_2(t_token **cur_token);

t_ast_node *command_line_and(t_token **cur_token);
t_ast_node *command_line_and_1(t_token **cur_token);
t_ast_node *command_line_and_2(t_token **cur_token);

t_ast_node *grouped_command(t_token **cur_token);
t_ast_node *grouped_command_1(t_token **cur_token);
t_ast_node *grouped_command_2(t_token **cur_token);

t_ast_node *pipe_line(t_token **cur_token);
t_ast_node *pipe_line_1(t_token **cur_token);
t_ast_node *pipe_line_2(t_token **cur_token);

bool check_token(t_lexeme token_lex, t_token **cur_tok)
{
    if (*cur_tok == NULL)
        return (NULL);
    if ((*cur_tok)->lexem == token_lex)
    {
        *cur_tok = (*cur_tok)->next;
        return (true);
    }
    *cur_tok = (*cur_tok)->next;    
    return (false);
}

t_ast_node *command_line(t_token **cur_token)
{
    return (command_line_or(cur_token));
}

t_ast_node *command_line_or(t_token **cur_token)
{
    t_ast_node *node;
    t_token *save_token;

    save_token = *cur_token;
    if ((node = command_line_or_1(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = command_line_or_2(cur_token)) != NULL)
        return (node);
    return (NULL);
}

t_ast_node *command_line_or_1(t_token **cur_token)
{
    t_ast_node *cmd_and_1;
    t_ast_node *cmd_and_2;
    t_ast_node *head_node;
    t_token *save;

    save = *cur_token;
    if ((cmd_and_1 = command_line_and(cur_token)) == NULL)
        return NULL;
    if (!check_token(OR, cur_token))
    {
        *cur_token = save;
        ast_distroy(&cmd_and_1);
        return NULL;
    }
    if ((cmd_and_2 = command_line_or(cur_token)) == NULL)
        return NULL;
    head_node = ast_create_node(OR_NODE, NULL, NULL);
    if (head_node == NULL)
        return NULL;
    head_node->data.childs.left = cmd_and_1;
    head_node->data.childs.right = cmd_and_2;
    return head_node;
}

t_ast_node *command_line_or_2(t_token **cur_token)
{
    return (command_line_and(cur_token));
}


t_ast_node *command_line_and(t_token **cur_token)
{
    t_ast_node *node;
    t_token *save_token;

    save_token = *cur_token;
    if ((node = command_line_and_1(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = command_line_and_2(cur_token)) != NULL)
        return (node);
    return (NULL);
}

t_ast_node *command_line_and_1(t_token **cur_token)
{
    t_ast_node *cmd_and;
    t_ast_node *group;
    t_ast_node *head_node;
    t_token *save;

    save = *cur_token;
    if ((group = grouped_command(cur_token)) == NULL)
        return NULL;
    if (!check_token(AND, cur_token))
    {
        *cur_token = save;
        ast_distroy(&group);
        return NULL;
    }
    if ((cmd_and = command_line_and(cur_token)) == NULL)
        return NULL;
    head_node = ast_create_node(AND_NODE, NULL, NULL);
    if (head_node == NULL)
        return NULL;
    head_node->data.childs.left = group;
    head_node->data.childs.right = cmd_and;
    return head_node;
}

t_ast_node *command_line_and_2(t_token **cur_token)
{
    return (grouped_command(cur_token));
}

t_ast_node *grouped_command(t_token **cur_token)
{
    t_ast_node *node;
    t_token *save_token;

    save_token = *cur_token;
    if ((node = grouped_command_1(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = grouped_command_2(cur_token)) != NULL)
        return (node);
    return (NULL);
}

t_ast_node *grouped_command_1(t_token **cur_token)
{
    t_ast_node *cmd;

    cmd = NULL;
    if (!check_token(OPEN_P, cur_token))
        return NULL;
    if ((cmd = command_line(cur_token)) == NULL)
        return (NULL);
    if (!check_token(CLOSE_P, cur_token))
    {
        ast_distroy(&cmd);
        return NULL;
    }
    return (cmd);
}

t_ast_node *grouped_command_2(t_token **cur_token)
{
    return(pipe_line(cur_token));
}

t_ast_node *pipe_line(t_token **cur_token)
{
    t_ast_node *node;
    t_token *save_token;

    save_token = *cur_token;
    if ((node = pipe_line_1(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = pipe_line_2(cur_token)) != NULL)
        return (node);
    return (NULL);
}


t_ast_node *pipe_line_1(t_token **cur_token)
{
    t_ast_node *cmd;
    t_ast_node *pipeline;
    t_ast_node *head_node;
    t_token *save;

    save = *cur_token;
    if ((cmd = form_command(cur_token)) == NULL)
        return NULL;
    if (!check_token(PIPE, cur_token))
    {
        *cur_token = save;
        ast_distroy(&cmd);
        return NULL;
    }
    if ((pipeline = pipe_line(cur_token)) == NULL)
        return NULL;
    head_node = ast_create_node(PIPELINE, NULL, NULL);
    if (head_node == NULL)
        return NULL;
    head_node->data.childs.left = cmd;
    head_node->data.childs.right = pipeline;
    return head_node;
}

t_ast_node *pipe_line_2(t_token **cur_token)
{
    return (form_command(cur_token));
}

// t_ast_node *command(t_token **cur_token)
// {
//     t_ast_node *cmd;
//     t_argument *args;

//     cmd = NULL;
//     args = NULL;
//     if (current_token->lexem != CMD)
//     {
//         cmd = ast_create_node(COMMAND, NULL, NULL);
//         if (cmd == NULL)
//             return (NULL);
//         cmd->data.childs.left = ast_create_node(ARGUMENTS, NULL, NULL);
//         cmd->data.childs.left->data.arg_list = NULL;
//     }
//     else
//     {
//         cmd = ast_create_node(COMMAND, NULL, NULL);
//         if (cmd == NULL)
//             return NULL;
//         args = args_table(&current_token, ARGUMENTS);
//         cmd->data.childs.left = ast_create_node(ARGUMENTS, args, NULL);
//     } 
//     if (redirection_found(current_token))
//     {
//         while(current_token != NULL && is_schar(current_token->lexem) == 0)
//             current_token = current_token->next;
//         cmd->data.childs.right = get_redirection_tree(REDIRECTION);
//     }
//     else 
//         cmd->data.childs.right = NULL;        
//     return cmd;
// }

// // int isschar(t_token current_token)
// // {
// //     if (current_token == NULL || current_token->lexem == PIPE || current_token->lexem == AND 
// //         || current_token->lexem == OR || current_token->lexem == OPEN_P || current_token->lexem == CLOSE_P)
// // }

// t_ast_node *get_redirection_tree(t_node_type type)
// {
//     t_ast_node *root;
//     t_argument *args;

//     root = NULL;
//     args = NULL;
//     if (current_token == NULL || current_token->lexem == PIPE || current_token->lexem == AND 
//         || current_token->lexem == OR || current_token->lexem == OPEN_P || current_token->lexem == CLOSE_P)
//         return root;
//     root = ast_create_node(REDIRECTION, NULL, NULL);
//     if (root == NULL)
//         return NULL;
//     args = args_table(&current_token, ARGUMENTS);
//     root->data.childs.left = ast_create_node(ARGUMENTS, args, NULL);
//     // if (current_token != NULL && current_token->lexem != PIPE && current_token->lexem != AND 
//     //     && current_token->lexem != OR && current_token->lexem != CLOSE_P && current_token->lexem != OPEN_P)
//     //     current_token = current_token->next;
//     // while(current_token != NULL && is_schar(current_token->lexem) == 0)
//     //     current_token = current_token->next;
//     if (current_token != NULL && current_token->lexem == PIPE && current_token->lexem == AND 
//         && current_token->lexem == OR && current_token->lexem == CLOSE_P && current_token->lexem == OPEN_P)
//         root->data.childs.right = NULL;
//     else 
//         root->data.childs.right = get_redirection_tree(type);
//     return root;
// }

t_ast_node *build_ast(t_token *tokens)
{
    t_ast_node *ast;
    t_token *cur_token;

    ast = NULL;
    cur_token = NULL;
    if (tokens == NULL)
        return (NULL);
    cur_token = tokens;
    ast = command_line(&cur_token);
    if (cur_token != NULL)
    {
        print_error("ast error!\n", 2);
        return (NULL);
    }
    return (ast);
}