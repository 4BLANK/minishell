#include "../../../includes/minishell.h"

static void process_redirection(t_token **tokens, t_lexeme lex);
static void update_command_flag(t_token *tokens, int *command_flag);
static bool is_valid_redirection(t_token *tokens, int *itr, int red_nbr);
static void handle_token_stream(t_token **tokens, int *command_flag);

void red_lexer(t_token *tokens, int red_nbr)
{
    int command_flag;
    int itr;
    t_lexeme lex;

    itr = 0;
    command_flag = 0;
    while (tokens != NULL)
    {
        update_command_flag(tokens, &command_flag);
        if (is_valid_redirection(tokens, &itr, red_nbr))
        {
            lex = tokens->lexem;
            tokens = tokens->next;
            if (tokens != NULL)
                process_redirection(&tokens, lex);
            handle_token_stream(&tokens, &command_flag);
            break;
        }
        tokens = tokens->next;
    }
}

static void update_command_flag(t_token *tokens, int *command_flag)
{
    if (*command_flag == 0 && tokens->lexem == CMD)
        *command_flag = 1;
    else if (*command_flag == 1 && (tokens->lexem == PIPE 
        || tokens->lexem == AND || tokens->lexem == OR 
        || tokens->lexem == OPEN_P || tokens->lexem == CLOSE_P))
        *command_flag = 0;
}


static bool is_valid_redirection(t_token *tokens, int *itr, int red_nbr)
{
    if (is_schar(tokens->lexem) == 1)
    {
        (*itr)++;
        if (*itr == red_nbr)
            return (true);
    }
    return (false);
}


static void process_redirection(t_token **tokens, t_lexeme lex)
{
    if (lex == HEREDOC && (*tokens)->lexem != AMBIGUOUS)
        (*tokens)->lexem = DELIMITER;
    else if ((*tokens)->lexem != AMBIGUOUS)
        (*tokens)->lexem = O_FILE;
    *tokens = (*tokens)->next;
}


static void handle_token_stream(t_token **tokens, int *command_flag)
{
    while (*tokens != NULL && is_schar((*tokens)->lexem) == 0)
    {
        if (*command_flag == 1)
            (*tokens)->lexem = ARG;
        else
        {
            (*tokens)->lexem = CMD;
            *command_flag = 1;
        }
        *tokens = (*tokens)->next;
    }
}


void schar_lexer(t_token *tokens)
{
    while (tokens != NULL)
    {
        if (ft_strcmp(tokens->content, ")"))
            tokens->lexem = CLOSE_P;
        else if (ft_strcmp(tokens->content, "("))
            tokens->lexem = OPEN_P;
        else if (ft_strcmp(tokens->content, ">"))
            tokens->lexem = O_REDIRECTION;
        else if (ft_strcmp(tokens->content, "<"))
            tokens->lexem = I_REDIRECTION;
        else if (ft_strcmp(tokens->content, "<<"))
            tokens->lexem = HEREDOC;
        else if (ft_strcmp(tokens->content, ">>"))
            tokens->lexem = APPEND;
        else if (ft_strcmp(tokens->content, "|"))
            tokens->lexem = PIPE;
        else if (ft_strcmp(tokens->content, "||"))
            tokens->lexem = OR;
        else if (ft_strcmp(tokens->content, "&&"))
            tokens->lexem = AND;
        else if (tokens->lexem != AMBIGUOUS)
            tokens->lexem = STRING;
        tokens = tokens->next;
    }
}

// void red_lexer(t_token *tokens, int red_nbr)
// {
//     int command_flag;
//     int itr;
//     t_lexeme lex;

//     itr = 0;
//     command_flag = 0;
//     while(tokens != NULL)
//     {
//         if (command_flag == 0 && tokens->lexem == CMD)
//             command_flag = 1;
//         else if (command_flag == 1 && (tokens->lexem == PIPE 
//             || tokens->lexem == AND || tokens->lexem == OR
//             || tokens->lexem == OPEN_P || tokens->lexem == CLOSE_P))
//             command_flag = 0;
//         if (is_schar(tokens->lexem) == 1 && ++itr == red_nbr)
//         {
//             lex = tokens->lexem;
//             tokens = tokens->next;
//             if (tokens != NULL)
//             {   
//                 if (lex == HEREDOC && tokens->lexem != AMBIGUOUS)
//                     tokens->lexem = DELIMITER;
//                 else if (tokens->lexem != AMBIGUOUS)
//                     tokens->lexem = O_FILE;
//                 tokens = tokens->next;
//             }
//             while (tokens != NULL && is_schar(tokens->lexem) == 0)
//             {
//                 if (command_flag == 1)
//                     tokens->lexem = ARG;
//                 else if (command_flag == 0)
//                 {
//                     tokens->lexem = CMD;
//                     command_flag = 1;
//                 }
//                 tokens = tokens->next;
//             }
//             break;
//         }
//         tokens = tokens->next;
//     }
// }

void set_lexeme(t_token *token, t_lexeme prev_lexeme)
{
    if (token->lexem == STRING)
    {
        if (prev_lexeme == PIPE || prev_lexeme == AND || prev_lexeme == OR
            || prev_lexeme == OPEN_P || prev_lexeme == CLOSE_P)
            token->lexem = CMD;
        else if (prev_lexeme == I_REDIRECTION || prev_lexeme ==  O_REDIRECTION
            || prev_lexeme == APPEND)
            token->lexem = O_FILE;
        else if (prev_lexeme == CMD || prev_lexeme == ARG)
            token->lexem = ARG;
    }
}

void lexer(t_token *tokens)
{
    t_token *prev_token;
    t_token *tmp;
    int red;

    prev_token = NULL;
    tmp = tokens;
    red = 0;
    schar_lexer(tokens);
    while (tokens != NULL)
    {
        if (is_schar(tokens->lexem))
        {
            red++;
            red_lexer(tmp, red);
        }
        if (prev_token != NULL && tokens->lexem == STRING)
            set_lexeme(tokens, prev_token->lexem);
        else if (prev_token != NULL && tokens->lexem != STRING)
            set_lexeme(tokens, PIPE);
        else if (prev_token == NULL && tokens->lexem == STRING)
            tokens->lexem = CMD;
        prev_token = tokens;
        tokens = tokens->next;
    }
}

