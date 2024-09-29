#include "../../../includes/parser.h"

t_ast_node *grouped_command(t_token **cur_token)
{
    t_ast_node *node;
    t_token *save_token;

    save_token = *cur_token;
    node = grouped_command_0(cur_token);
     if (node != NULL)
        return (node);
    *cur_token = save_token;
    node = grouped_command_1(cur_token);
    if (node != NULL)
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
    cmd = command_line(cur_token);
    if (cmd == NULL)
        return (NULL);
    if (!check_token(CLOSE_P, cur_token))
    {
        ast_distroy(&cmd, 0);
        return NULL;
    }
    // printf(RED "\n=====================\n" RESET);
    // print_lst(*cur_token);
    if (*cur_token == NULL || is_schar((*cur_token)->lexem) != 1)
    {
        ast_distroy(&cmd, 0);
        return NULL;
    }
    else 
    {
        files = get_files(cur_token);
        // print_files(files);
        if (files == NULL)
        {
            ast_distroy(&cmd, 0);
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
    cmd = command_line(cur_token);
    if (cmd == NULL)
        return (NULL);
    if (!check_token(CLOSE_P, cur_token))
    {
        ast_distroy(&cmd, 0);
        return (NULL);
    }
    group = ast_create_node(GROUP_NODE, NULL, NULL);
    if (group == NULL)
        return (NULL);
    group->data.childs.left = cmd;
    group->data.childs.right = NULL;
    return (group);
}