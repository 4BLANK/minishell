#include "../../../includes/minishell.h"

static void insert_tok(t_token **toks, char *str, size_t start, size_t end);
static void find_token_end(char *str, size_t *end);

t_token *split_tokens(char *str)
{
    t_token *toklst;
    size_t end;
    size_t start;

    end = 0;
    toklst = NULL;
    while (str[end])
    {
        if (str[end] && !is_space(str[end]))
        {
            start = end;
            find_token_end(str, &end);
            insert_tok(&toklst, str, start, end);
        }
        if (str[end] != '\0')
            end++;
    }
    return (toklst);
}


static void find_token_end(char *str, size_t *end)
{
    int quote_flag;
    char quote_type;

    quote_flag = 0;
    while (str[*end])
    {
        if (quote_flag == 0 && (str[*end] == QUOTE || str[*end] == DQUOTE))
        {
            quote_flag = 1;
            quote_type = str[*end];
        }
        else if (quote_flag == 1 && str[*end] == quote_type)
        {
            quote_flag = 0;
            if (str[*end + 1] && is_space(str[*end + 1]))
            {
                (*end)++;
                break;
            }
        }
        else if (is_space(str[*end]) && quote_flag == 0)
            break;
        (*end)++;
    }
}

static void insert_tok(t_token **toks, char *str, size_t start, size_t end)
{
    char *tmp;
    t_token *tok;

    if (end != start)
    {
        tmp = ft_substr(str, start, end - start);
        if (tmp != NULL)
        {
            tok = ft_lstnew_token(tmp);
            if (tok != NULL)
                ft_lstadd_token_back(toks, tok);
        }
    }
}