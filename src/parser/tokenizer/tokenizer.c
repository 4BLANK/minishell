#include "../../../includes/minishell.h"

static int check_quote(char c, int *flag, char *quote)
{
    if (*flag == 0 && (c == QUOTE || c == DQUOTE))
    {
        *flag = 1;
        *quote = c;
    }
    else if (*flag == 1 && c == *quote)
        *flag = 0;
    return (*flag);
}

static int find_tok_end(char *line, size_t start, int *flag, char *quote)
{
    size_t itr;

    itr = start;
    while (line[itr])
    {
        if (check_quote(line[itr], flag, quote))
        {
            if (*flag == 0 && line[itr + 1] && is_space(line[itr + 1]))
            {
                itr++;
                break;
            }
        }
        else if (is_space(line[itr]) && *flag == 0)
            break;
        itr++;
    }
    return (itr);
}

static int extract_tok(char *s, size_t start, size_t end, t_token **toks)
{
    char *holder;
    t_token *tok;

    holder = ft_substr(s, start, end - start);
    if (holder == NULL)
        return (EXIT_FAILURE);
    tok = ft_lstnew_token(holder);
    if (tok == NULL)
        return (EXIT_FAILURE);
    ft_lstadd_token_back(toks, tok);
    return (EXIT_SUCCESS);
}

int tokens_spliter(char *line, t_token **toklst)
{
    size_t itr;
    size_t tok_end;
    int quote_flag;
    char quote_type;

    itr = 0;
    quote_flag = 0;
    while (line[itr])
    {
        if (!is_space(line[itr]))
        {
            tok_end = find_tok_end(line, itr, &quote_flag, &quote_type);
            if (quote_flag == 1)
                return (print_error("unclosed quote detected!\n", 2));
            if (itr == tok_end || extract_tok(line, itr, tok_end, toklst))
                return (print_error("tokenizer error!\n", 2));
            itr = tok_end;
        }
        if (line[itr] != '\0')
            itr++;
    }
    return (EXIT_SUCCESS);
}