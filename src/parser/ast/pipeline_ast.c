#include "../../../includes/parser.h"

static t_ast_node *pipe_line_3(t_token **cur_token);
static t_ast_node *pipe_line_1(t_token **cur_token);
static t_ast_node *pipe_line_4(t_token **cur_token);
static t_ast_node *pipe_line_2(t_token **cur_token);

t_ast_node *pipe_line(t_token **cur_token)
{
    t_ast_node *node;
    t_token *save_token;

    save_token = *cur_token;
    node = pipe_line_3(cur_token);
    if (node != NULL)
        return (node);
    *cur_token = save_token;
    node = pipe_line_1(cur_token);
    if (node != NULL)
        return (node);
    *cur_token = save_token;
    node = pipe_line_4(cur_token);
    if (node != NULL)
        return (node);
    *cur_token = save_token;
    node = pipe_line_2(cur_token);
   if (node != NULL)
        return (node);
    return (NULL);
}

static t_ast_node *pipe_line_3(t_token **cur_token)
{
    t_ast_node *cmd;
    t_ast_node *pipeline;
    t_ast_node *head_node;
    t_token *save;

    save = *cur_token;
    cmd = grouped_command(cur_token);
    if (cmd == NULL)
        return NULL;
    if (!check_token(PIPE, cur_token))
    {
        *cur_token = save;
        ast_distroy(&cmd, 0);
        return NULL;
    }
    pipeline = pipe_line(cur_token);
    if (pipeline == NULL)
        return NULL;
    head_node = ast_create_node(PIPELINE, NULL, NULL);
    if (head_node == NULL)
        return NULL;
    head_node->data.childs.left = cmd;
    head_node->data.childs.right = pipeline;
    return head_node;
}

static t_ast_node *pipe_line_1(t_token **cur_token)
{
    t_ast_node *cmd;
    t_ast_node *pipeline;
    t_ast_node *head_node;
    t_token *save;

    save = *cur_token;
    cmd = form_command(cur_token);
    if (cmd == NULL)
        return NULL;
    if (!check_token(PIPE, cur_token))
    {
        *cur_token = save;
        ast_distroy(&cmd, 0);
        return NULL;
    }
    pipeline = pipe_line(cur_token);
    if (pipeline == NULL)
        return NULL;
    head_node = ast_create_node(PIPELINE, NULL, NULL);
    if (head_node == NULL)
        return NULL;
    head_node->data.childs.left = cmd;
    head_node->data.childs.right = pipeline;
    return head_node;
}

static t_ast_node *pipe_line_4(t_token **cur_token)
{
    return (grouped_command(cur_token));
}

static t_ast_node *pipe_line_2(t_token **cur_token)
{
    return (form_command(cur_token));
}

