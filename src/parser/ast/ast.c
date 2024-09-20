#include "../../../includes/parser.h"

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
    t_ast_node *node;
    t_token *save_token;

    save_token = *cur_token;
    if ((node = command_line_1(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = command_line_2(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = command_line_3(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = command_line_4(cur_token)) != NULL)
        return (node);
    return (NULL);
}

t_ast_node *command_line_1(t_token **cur_token)
{
    t_ast_node *cmd_line;
    t_ast_node *group;
    t_ast_node *cmd_line_right;
    t_token *save;

    save = *cur_token;
    if ((group = grouped_command(cur_token)) == NULL)
        return (NULL);
    if (!check_token(OR, cur_token))
    {
        *cur_token = save;
        ast_distroy(&group);
        return (NULL);
    }
    if ((cmd_line_right = command_line(cur_token)) == NULL)
        return (NULL);
    cmd_line = ast_create_node(OR_NODE, NULL, NULL);
    if (cmd_line == NULL)
        return (NULL);
    cmd_line->data.childs.left = group;
    cmd_line->data.childs.right = cmd_line_right;
    return (cmd_line);
}

t_ast_node *command_line_2(t_token **cur_token)
{
    t_ast_node *cmd_line;
    t_ast_node *group;
    t_ast_node *cmd_line_right;
    t_token *save;

    save = *cur_token;
    if ((group = grouped_command(cur_token)) == NULL)
        return (NULL);
    if (!check_token(AND, cur_token))
    {
        *cur_token = save;
        ast_distroy(&group);
        return (NULL);
    }
    if ((cmd_line_right = command_line(cur_token)) == NULL)
        return (NULL);
    cmd_line = ast_create_node(AND_NODE, NULL, NULL);
    if (cmd_line == NULL)
        return (NULL);
    cmd_line->data.childs.left = group;
    cmd_line->data.childs.right = cmd_line_right;
    return (cmd_line);
}

// t_ast_node *command_line_3(t_token **cur_token)
// {
//     t_ast_node *cmd_line;
//     t_ast_node *group;
//     t_ast_node *cmd_line_right;
//     t_token *save;

//     save = *cur_token;
//     if ((group = grouped_command(cur_token)) == NULL)
//         return (NULL);
//     if (!check_token(PIPE, cur_token))
//     {
//         *cur_token = save;
//         ast_distroy(&group);
//         return (NULL);
//     }
//     if ((cmd_line_right = command_line(cur_token)) == NULL)
//         return (NULL);
//     cmd_line = ast_create_node(PIPELINE, NULL, NULL);
//     if (cmd_line == NULL)
//         return (NULL);
//     cmd_line->data.childs.left = group;
//     cmd_line->data.childs.right = cmd_line_right;
//     return (cmd_line);
// }

t_ast_node *command_line_3(t_token **cur_token)
{
    return (grouped_command(cur_token));
}

t_ast_node *command_line_4(t_token **cur_token)
{
    return (command_line_or(cur_token));
}

t_ast_node *grouped_command(t_token **cur_token)
{
    t_ast_node *node;
    t_token *save_token;

    save_token = *cur_token;
     if ((node = grouped_command_0(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = grouped_command_1(cur_token)) != NULL)
        return (node);
    // *cur_token = save_token;
    // if ((node = grouped_command_2(cur_token)) != NULL)
    //     return (node);
    return (NULL);
}

t_file *get_files(t_token **tokenlst)
{
    t_file *files;
    t_file *tmp;
    char *str;
    int lex_tmp;

    files = NULL;
    
    tmp = NULL;
    lex_tmp = 0;
    if (*tokenlst == NULL || is_schar((*tokenlst)->lexem) != 1)
        return NULL;
    while (*tokenlst != NULL && is_schar((*tokenlst)->lexem) != 2)
    {
        str = NULL;
        if (is_schar((*tokenlst)->lexem) == 1)
        {
            lex_tmp = (*tokenlst)->lexem;
            *tokenlst = (*tokenlst)->next;
            str = ft_strdup((*tokenlst)->content);
            tmp = new_file(ft_strdup((*tokenlst)->content), lex_tmp);
            free(str);
            if (tmp == NULL)
                return (NULL);
            addfile_back(&files, tmp);
        }   
        *tokenlst = (*tokenlst)->next;
    }
    return (files);
}

t_ast_node *grouped_command_0(t_token **cur_token)
{
    t_ast_node *cmd;
    t_ast_node *group;
    // t_file *tmp;
    t_file *files;
    // int lex_tmp;

    cmd = NULL;
    files = NULL;
    if (!check_token(OPEN_P, cur_token))
        return (NULL);
    if ((cmd = command_line(cur_token)) == NULL)
        return (NULL);
    if (!check_token(CLOSE_P, cur_token))
    {
        ast_distroy(&cmd);
        return NULL;
    }
    // printf(RED "\n=====================\n" RESET);
    // print_lst(*cur_token);
    if (*cur_token == NULL || is_schar((*cur_token)->lexem) != 1)
    {
        ast_distroy(&cmd);
        return NULL;
    }
    else 
    {
        files = get_files(cur_token);
        // print_files(files);
        if (files == NULL)
        {
            ast_distroy(&cmd);
            return (NULL);
        }
        group = ast_create_node(GROUP_NODE, NULL, NULL);
        if (group == NULL)
            return NULL;
        group->data.childs.left = cmd;
        group->data.childs.right = ast_create_node(REDIRECTION, NULL, files);
    }
    return (group);
}

t_ast_node *grouped_command_1(t_token **cur_token)
{
    t_ast_node *cmd;
    t_ast_node *group;

    cmd = NULL;
    if (!check_token(OPEN_P, cur_token))
        return (NULL);
    if ((cmd = command_line(cur_token)) == NULL)
        return (NULL);
    if (!check_token(CLOSE_P, cur_token))
    {
        ast_distroy(&cmd);
        return (NULL);
    }
    group = ast_create_node(GROUP_NODE, NULL, NULL);
    if (group == NULL)
        return (NULL);
    group->data.childs.left = cmd;
    group->data.childs.right = NULL;
    return (group);
}

// t_ast_node *grouped_command_2(t_token **cur_token)
// {
//     return(command_line_or(cur_token));
// }


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
    {
        ast_distroy(&cmd_and_1);
        return NULL;
    }
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
    if ((group = pipe_line(cur_token)) == NULL)
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
    return (pipe_line(cur_token));
}


t_ast_node *pipe_line(t_token **cur_token)
{
    t_ast_node *node;
    t_token *save_token;

    save_token = *cur_token;
    if ((node = pipe_line_3(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = pipe_line_1(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = pipe_line_4(cur_token)) != NULL)
        return (node);
    *cur_token = save_token;
    if ((node = pipe_line_2(cur_token)) != NULL)
        return (node);
    return (NULL);
}

t_ast_node *pipe_line_3(t_token **cur_token)
{
    t_ast_node *cmd;
    t_ast_node *pipeline;
    t_ast_node *head_node;
    t_token *save;

    save = *cur_token;
    if ((cmd = grouped_command(cur_token)) == NULL)
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

t_ast_node *pipe_line_4(t_token **cur_token)
{
    return (grouped_command(cur_token));
}

t_ast_node *pipe_line_2(t_token **cur_token)
{
    return (form_command(cur_token));
}

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
        printf("%s\n", cur_token->content);
        print_error("ast error!\n", 2);
        return (NULL);
    }
    return (ast);
}