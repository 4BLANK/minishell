#include "../../../includes/parser.h"

t_token *current_token = NULL;



t_ast_node *command_line();
// t_ast_node *command_line_1();
// t_ast_node *command_line_2();

// t_ast_node *command_line_tail(t_ast_node *left_node);

// t_ast_node *command_line_1();
// t_ast_node *command_line_2();
// t_ast_node *command_line_3();

t_ast_node *command_line_or();
t_ast_node *command_line_or_1();
t_ast_node *command_line_or_2();

t_ast_node *command_line_and();
t_ast_node *command_line_and_1();
t_ast_node *command_line_and_2();

t_ast_node *grouped_command();
t_ast_node *grouped_command_1();
t_ast_node *grouped_command_2();

t_ast_node *pipe_line();
t_ast_node *pipe_line_1();
t_ast_node *pipe_line_2();

t_ast_node *command();

bool check_token(t_lexeme token_lex)
{
    if (current_token == NULL)
        return NULL;
    // printf("%s\n", lexs_type[current_token->lexem]);
    if (current_token->lexem == token_lex)
    {
        current_token = current_token->next;
        return true;
    }
    current_token = current_token->next;    
    return false;
}

t_ast_node *command_line()
{
    return (command_line_or());
}

t_ast_node *command_line_or()
{
    t_ast_node *node;
    t_token *save_token;

    save_token = current_token;
    if ((node = command_line_or_1()) != NULL)
        return (node);
    current_token = save_token;
    if ((node = command_line_or_2()) != NULL)
        return (node);
    return (NULL);
}

t_ast_node *command_line_or_1()
{
    t_ast_node *cmd_and_1;
    t_ast_node *cmd_and_2;
    t_ast_node *head_node;
    t_token *save;

    save = current_token;
    if ((cmd_and_1 = command_line_and()) == NULL)
        return NULL;
    if (!check_token(OR))
    {
        current_token = save;
        ast_delete(cmd_and_1);
        return NULL;
    }
    if ((cmd_and_2 = command_line_or()) == NULL)
        return NULL;
    head_node = ast_create_node(OR_NODE, NULL);
    if (head_node == NULL)
        return NULL;
    head_node->data.childs.left = cmd_and_1;
    head_node->data.childs.right = cmd_and_2;
    return head_node;
}

t_ast_node *command_line_or_2()
{
    return (command_line_and());
}


t_ast_node *command_line_and()
{
    t_ast_node *node;
    t_token *save_token;

    save_token = current_token;
    if ((node = command_line_and_1()) != NULL)
        return (node);
    current_token = save_token;
    if ((node = command_line_and_2()) != NULL)
        return (node);
    return (NULL);
}

t_ast_node *command_line_and_1()
{
    t_ast_node *cmd_and;
    t_ast_node *group;
    t_ast_node *head_node;
    t_token *save;

    save = current_token;
    if ((group = grouped_command()) == NULL)
        return NULL;
    if (!check_token(AND))
    {
        current_token = save;
        ast_delete(group);
        return NULL;
    }
    if ((cmd_and = command_line_and()) == NULL)
        return NULL;
    head_node = ast_create_node(AND_NODE, NULL);
    if (head_node == NULL)
        return NULL;
    head_node->data.childs.left = group;
    head_node->data.childs.right = cmd_and;
    return head_node;
}

t_ast_node *command_line_and_2()
{
    return (grouped_command());
}

t_ast_node *grouped_command()
{
    t_ast_node *node;
    t_token *save_token;

    save_token = current_token;
    if ((node = grouped_command_1()) != NULL)
        return (node);
    current_token = save_token;
    if ((node = grouped_command_2()) != NULL)
        return (node);
    return (NULL);
}

t_ast_node *grouped_command_1()
{
    t_ast_node *cmd;

    if (!check_token(OPEN_P))
        return NULL;
    if ((cmd = command_line()) == NULL)
        return (NULL);
    if (!check_token(CLOSE_P))
    {
        ast_delete(cmd);
        return NULL;
    }
    return cmd;
}

t_ast_node *grouped_command_2()
{
    return(pipe_line());
}

t_ast_node *pipe_line()
{
    t_ast_node *node;
    t_token *save_token;

    save_token = current_token;
    if ((node = pipe_line_1()) != NULL)
        return (node);
    current_token = save_token;
    if ((node = pipe_line_2()) != NULL)
        return (node);
    return (NULL);
}


t_ast_node *pipe_line_1()
{
    t_ast_node *cmd;
    t_ast_node *pipeline;
    t_ast_node *head_node;
    t_token *save;

    save = current_token;
    if ((cmd = command()) == NULL)
        return NULL;
    if (!check_token(PIPE))
    {
        current_token = save;
        ast_delete(cmd);
        return NULL;
    }
    if ((pipeline = pipe_line()) == NULL)
        return NULL;
    head_node = ast_create_node(PIPELINE, NULL);
    if (head_node == NULL)
        return NULL;
    head_node->data.childs.left = cmd;
    head_node->data.childs.right = pipeline;
    return head_node;
}

t_ast_node *pipe_line_2()
{
    return (command());
}

t_ast_node *command()
{
    t_ast_node *cmd;
    t_argument *args;

    cmd = NULL;
    args = NULL;
    if (current_token->lexem != CMD)
    {
        cmd = ast_create_node(COMMAND, NULL);
        if (cmd == NULL)
            return (NULL);
        cmd->data.childs.left = ast_create_node(ARGUMENTS, NULL);
        cmd->data.childs.left->data.arg_list = NULL;
    }
    else
    {
        cmd = ast_create_node(COMMAND, NULL);
        if (cmd == NULL)
            return NULL;
        args = args_table(&current_token, ARGUMENTS);
        cmd->data.childs.left = ast_create_node(ARGUMENTS, args);
    } 
    if (redirection_found(current_token))
    {
        while(current_token != NULL && is_schar(current_token->lexem) == 0)
            current_token = current_token->next;
        cmd->data.childs.right = get_redirection_tree(REDIRECTION);
    }
    else 
        cmd->data.childs.right = NULL;        
    return cmd;
}

// int isschar(t_token current_token)
// {
//     if (current_token == NULL || current_token->lexem == PIPE || current_token->lexem == AND 
//         || current_token->lexem == OR || current_token->lexem == OPEN_P || current_token->lexem == CLOSE_P)
// }

t_ast_node *get_redirection_tree(t_node_type type)
{
    t_ast_node *root;
    t_argument *args;

    root = NULL;
    args = NULL;
    if (current_token == NULL || current_token->lexem == PIPE || current_token->lexem == AND 
        || current_token->lexem == OR || current_token->lexem == OPEN_P || current_token->lexem == CLOSE_P)
        return root;
    root = ast_create_node(REDIRECTION, NULL);
    if (root == NULL)
        return NULL;
    args = args_table(&current_token, ARGUMENTS);
    root->data.childs.left = ast_create_node(ARGUMENTS, args);
    // if (current_token != NULL && current_token->lexem != PIPE && current_token->lexem != AND 
    //     && current_token->lexem != OR && current_token->lexem != CLOSE_P && current_token->lexem != OPEN_P)
    //     current_token = current_token->next;
    // while(current_token != NULL && is_schar(current_token->lexem) == 0)
    //     current_token = current_token->next;
    if (current_token != NULL && current_token->lexem == PIPE && current_token->lexem == AND 
        && current_token->lexem == OR && current_token->lexem == CLOSE_P && current_token->lexem == OPEN_P)
        root->data.childs.right = NULL;
    else 
        root->data.childs.right = get_redirection_tree(type);
    return root;
}

t_ast_node *build_ast(t_token *tokens)
{
    t_ast_node *ast;
    if (tokens == NULL)
        return NULL;
    current_token = tokens;
    ast = command_line();
    if (current_token != NULL)
    {
        print_error("ast error!\n", 2);
        return NULL;
    }
    return ast;
}