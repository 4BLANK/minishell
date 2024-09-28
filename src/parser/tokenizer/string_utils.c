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

size_t rm_quotelen(char *str)
{
    size_t len;
    size_t i;
    int flag;
    char quote;

    i = 0;
    flag = 0;
    len = 0;
    while (str[i])
    {
        if (flag == 0 && (str[i] == QUOTE || str[i] == DQUOTE))
        {
            flag = 1;
            quote = str[i];
        }
        else if (flag == 1 && str[i] == quote)
            flag = 0;
        else 
            len++;
        i++;
    }
    return (len);
}

static int check_quote(char c, int *flag, char *quote)
{
    int result;

    result = 0;
    if (*flag == 0 && (c == QUOTE || c == DQUOTE))
    {
        *flag = 1;
        *quote = c;
        result = 1;
    }
    else if (*flag == 1 && c == *quote)
    {
        result = 1;
        *flag = 0;
    }
    return (result);
}

char *remove_quote(char *str)
{
    int i;
    int j;
    char *newstr;
    char quote;
    int flag;

    i = 0;
    j = 0;
    flag = 0;
    if (str == NULL)
        return (NULL);
    newstr = malloc(sizeof(char) * (rm_quotelen(str) + 1));
    if (newstr == NULL)
        return (NULL);
    while (str[i])
    {
        if(!check_quote(str[i], &flag, &quote))
            newstr[j++] = str[i];
        i++;
    }
    newstr[j] = '\0';
    free(str);
    return (newstr);
}

// int check_for_echo(t_token *tokens)
// {
//     char *holder;
//     int i;

//     i = 0;
//     holder = ft_strdup(ft_lstlast_token(tokens)->content);
//     while (holder[i] && (holder[i] != DQUOTE && holder[i] != QUOTE))
//         i++;
//     holder = remove_quote(holder);
//     if (!ft_strncmp("echo", holder, 4) && ft_strlen(holder) == 4)
//     {
//         free(holder);
//         return 1;
//     }
//     free(holder);
//     return 0;
// }

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

int schar_detected(char c)
{
    if (c == CPIPE || c == GREATER 
        || c == LESS || c == AMPERSAND 
        || c == OPAREN || c == CPAREN)
        return (1);
    return (0);
}

int toggle_quotes(char c, int flag)
{
    if (flag == 0 && (c == DQUOTE ||  c == QUOTE))
        flag = 1;
    else if (flag == 1 && (c == DQUOTE ||  c == QUOTE))
        flag = 0;
    return (flag);
}

size_t handle_ampersand(char *line, ssize_t i)
{
    size_t count;

    count = 0;
    if (!i || line[i - 1] != AMPERSAND)
    {
        if (line[i + 1] && line[i + 1] == AMPERSAND)
            count++;
    }
    return (count);
}

size_t count_operator(char *line, ssize_t i)
{
    size_t count;

    count = 0;
    if (line[i] == OPAREN || line[i] == CPAREN)
        count++;
    else if (line[i] == GREATER && (!i || line[i - 1] != GREATER))
        count++;
    else if (line[i] == LESS && (!i || line[i - 1] != LESS))
        count++;
    else if (line[i] == CPIPE && (!i || line[i - 1] != CPIPE))
        count++;
    return (count);
}

size_t count_schar(char *line)
{
    ssize_t i;
    int flag;
    size_t count;

    i = -1;
    flag = 0;
    count = 0;
    while (line[++i])
    {
        flag = toggle_quotes(line[i], flag);
        if (flag == 0 && schar_detected(line[i]))
        {
            if (line[i] == AMPERSAND)
                count += handle_ampersand(line, i);
            else
                count += count_operator(line, i);
        }
    }
    return (count);
}

void process_character(char *newline, char *line, size_t *i, size_t *j)
{
    if (line[*i] == CPAREN || line[*i] == OPAREN)
    {
        newline[(*j)++] = ' ';
        newline[*j] = line[*i];
        newline[++(*j)] = ' ';
    }
    else if (line[*i] == AMPERSAND)
    {
        if (*i != 0 && line[*i - 1] != line[*i] 
            && line[*i + 1] && line[*i + 1] == line[*i])
            newline[(*j)++] = ' ';
        newline[*j] = line[*i];
        if (line[*i + 1] && line[*i + 1] != line[*i] 
            && (*i != 0 && line[*i - 1] == line[*i]))
            newline[++(*j)] = ' ';
    }
    else
    {
        if ((*i != 0 && line[*i - 1] != line[*i]))
            newline[(*j)++] = ' ';
        newline[*j] = line[*i];
        if (line[*i + 1] && line[*i + 1] != line[*i])
            newline[++(*j)] = ' ';
    }
}

char *expand_line(char *line, size_t len)
{
    size_t i;
    size_t j;
    int flag;
    char *newline;

    flag = 0;
    i = 0;
    j = 0;
    newline = (char *)malloc(sizeof(char) * len);
    if (newline == NULL)
        return (NULL);
    while (line[i])
    {
        flag = toggle_quotes(line[i], flag);
        if (flag == 0 && schar_detected(line[i]))
            process_character(newline, line, &i, &j);
        else 
            newline[j] = line[i];
        j++;
        i++;
    }
    newline[j] = '\0';
    return (newline);
}


// char *expand_line(char *line, size_t len)
// {
//     char *newline;
//     size_t i;
//     size_t j;
//     int flag;

//     i = -1;
//     j = 0;
//     flag = 0;
//     newline = (char *)malloc (sizeof(char) * len);
//     while (line[++i])
//     {
//         flag = toggle_quotes(line[i], flag);
//         if (flag == 0 && schar_detected(line[i]))
//         {
//             if (line[i] == CPAREN || line[i] == OPAREN)
//             {
//                 newline[j++] = ' ';
//                 newline[j] = line[i];
//                 newline[++j] = ' ';
//             }
//             else if (line[i] == AMPERSAND)
//             {
//                 if (i != 0 && line[i - 1] != line[i] && line[i + 1] && line[i + 1] == line[i])
//                     newline[j++] = ' ';
//                 newline[j] = line[i];
//                 if (line[i + 1] && line[i + 1] != line[i] && (i != 0 && line[i - 1] == line[i]))
//                     newline[++j] = ' ';
//             }
//             else 
//             {
//                 if ((i != 0 && line[i - 1] != line[i]))
//                     newline[j++] = ' ';
//                 newline[j] = line[i];
//                 if (line[i + 1] && line[i + 1] != line[i])
//                     newline[++j] = ' ';
//             }
//         }
//         else 
//             newline[j] = line[i];
//         j++;
//     }
//     newline[j] = '\0';
//     return (newline);
// }

int get_expanded_line(char **line)
{
    char *newline;
    size_t len;

    len = 0;
    if (*line == NULL)
        return (EXIT_FAILURE);
    len = ft_strlen(*line) + (count_schar(*line) * 2) + 1;
    newline = expand_line(*line, len);
    if (newline == NULL)
        return (EXIT_FAILURE);
    free(*line);
    *line = newline;
    return (EXIT_SUCCESS);
}

int modify_line(char **line)
{
    if (get_expanded_line(line))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}