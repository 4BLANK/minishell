#include "../../../includes/minishell.h"

char check_quotes(char *s)
{
    int i;
    
    i = 0;
    while (s[i] && is_space(s[i]))
        i++;
    if (s[i] == DQUOTE || s[i] == QUOTE)
        return (s[i]);
    return (0);
}

char *remove_quote(char *holder, char quote_type)
{
    char *new;
    int i;
    int j;

    i = 0;
    j = 0;
    if (holder == NULL)
        return NULL;
    new = malloc(sizeof(char) * ft_strlen(holder));
    while (holder[i])
    {
        if(holder[i] == quote_type)
            i++;
        new[j++] = holder[i++];
    }
    new[j] = '\0';
    free(holder);
    return (new);
}

int check_for_echo(t_token *tokens)
{
    char *holder;
    int i;

    i = 0;
    holder = ft_strdup(ft_lstlast_token(tokens)->content);
    while (holder[i] && (holder[i] != DQUOTE && holder[i] != QUOTE))
        i++;
    holder = remove_quote(holder, holder[i]);
    // dont remove spaces
    //holder = ft_strtrim(holder, " \t\v\n\r\f");
    if (!ft_strncmp("echo", holder, 4) && ft_strlen(holder) == 4)
    {
        free(holder);
        return 1;
    }
    free(holder);
    return 0;
}

int count_repetition(char *line, char c, int itr)
{
    int i;
    int count;

    i = itr;
    count = 0;
    while (line[i])
    {
        if (line[i] == c)
            count++;
        else 
            break;
        i++;
    }
    return count;
}

int count_special_chars(char *line)
{
    int count;
    int flag;
    int i;

    i = 0;
    flag = 0;
    count = 0;
    while(line[i])
    {
        if (flag == 0 && (line[i] == DQUOTE ||  line[i] == QUOTE))
            flag = 1;
        else if (flag == 1 && (line[i] == DQUOTE ||  line[i] == QUOTE))
            flag = 0;
        if (flag == 0 && (line[i] == CPIPE || line[i] == GREATER
            || line[i] == LESS))
        {
            if (line[i] == GREATER)
            {
                if (count_repetition(line, line[i], i) > 2)
                    print_error("parse error\n", 1);
                else if (line[i + 1] && line[i + 1] == LESS)
                    print_error("parse error\n", 1);
                else if (count_repetition(line, line[i], i) == 2)
                    count++;
                else if (line[i - 1] != GREATER)
                    count++;
            }
            else if (line[i] == LESS)
            {
                if (count_repetition(line, line[i], i) > 2)
                    print_error("parse error\n", 1);
                else if (line[i + 1] && line[i + 1] == GREATER)
                    print_error("parse error\n", 1);
                else if (count_repetition(line, line[i], i) == 2)
                    count ++;
                else if (line[i - 1] != LESS)
                    count++;
            }
            else if (line[i] == CPIPE)
            {
                if (count_repetition(line, line[i], i) > 2)
                    print_error("parse error\n", 1);
                else if (count_repetition(line, line[i], i) == 2)
                    count ++;
                else if (line[i - 1] != CPIPE)
                    count++;
            }
            else if (line[i] == AMPERSAND)
            {
                if (count_repetition(line, line[i], i) > 2)
                    print_error("parse error\n", 1);
                else if (count_repetition(line, line[i], i) == 2)
                    count++;
            }
        }
        i++;
    }
    return count;
}


bool	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
    if (s1[i] - s2[i] == 0)
        return (true);
    else 
       return (false);
}

char *modify_line(char *line)
{
    int i;
    int j;
    int flag;
    char *new_line;

    i = 0;
    j = 0;
    flag = 0;
    new_line = malloc(sizeof(char) * (ft_strlen(line) + count_special_chars(line) * 2 + 1));
    if (new_line == NULL)
        return NULL;
    while (line[i])
    {
        if (flag == 0 && (line[i] == DQUOTE ||  line[i] == QUOTE))
            flag = 1;
        else if (flag == 1 && (line[i] == DQUOTE ||  line[i] == QUOTE))
            flag = 0;
        if (flag == 0 && (line[i] == CPIPE || line[i] == GREATER || line[i] == LESS 
            || (line[i] == AMPERSAND && line[i + 1] && line[i + 1] == AMPERSAND)))
        {
            new_line[j++] = ' ';
            if (line[i + 1] && line[i + 1] != line[i] && line[i - 1] != line[i])
                new_line[j++] = line[i];
            else
            {
                new_line[j++] = line[i++];
                new_line[j++] = line[i];
            }
            new_line[j] = ' ';
        }
        else 
            new_line[j] = line[i];
        i++;
        j++;
    }
    new_line[j] = '\0';
    free(line);
    return new_line;
}