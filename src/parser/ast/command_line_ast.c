#include "../../../includes/parser.h"

t_ast_node *command_line(t_token **cur_token)
{
    t_ast_node *node;
    t_token *save_token;

    save_token = *cur_token;
    node = command_line_1(cur_token);
    if (node != NULL)
        return (node);
    *cur_token = save_token;
    node = command_line_2(cur_token);
    if (node != NULL)
        return (node);
    *cur_token = save_token;
    node = command_line_4(cur_token);
    if (node != NULL)
        return (node);
    *cur_token = save_token;
    node = command_line_3(cur_token);
    if (node != NULL)
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
    group = grouped_command(cur_token);
    if (group == NULL)
        return (NULL);
    if (!check_token(OR, cur_token))
    {
        *cur_token = save;
        ast_distroy(&group, 0);
        return (NULL);
    }
    cmd_line_right = command_line(cur_token);
    if (cmd_line_right == NULL)
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
    group = grouped_command(cur_token);
    if (group == NULL)
        return (NULL);
    if (!check_token(AND, cur_token))
    {
        *cur_token = save;
        ast_distroy(&group, 0);
        return (NULL);
    }
    cmd_line_right = command_line(cur_token);
    if (cmd_line_right == NULL)
        return (NULL);
    cmd_line = ast_create_node(AND_NODE, NULL, NULL);
    if (cmd_line == NULL)
        return (NULL);
    cmd_line->data.childs.left = group;
    cmd_line->data.childs.right = cmd_line_right;
    return (cmd_line);
}


t_ast_node *command_line_3(t_token **cur_token)
{
    return (grouped_command(cur_token));
}

t_ast_node *command_line_4(t_token **cur_token)
{
    return (command_line_or(cur_token));
}