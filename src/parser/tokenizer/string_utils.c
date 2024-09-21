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
    int flag;
    int quote;
    int i;

    i = 0;
    flag = 0;
    len = ft_strlen(str);
    while (str[i])
    {
        if (flag == 0 && (str[i] == QUOTE || str[i] == DQUOTE))
        {
            flag = 1;
            quote = str[i];
            len -= 2;
        }
        else if (flag == 1 && str[i] == quote)
            flag = 0;
        i++;
    }
    return (len);
}

//TODO: fix this bug
char *remove_quote(char *str)
{
    char *unqoute_str;
    char quote;
    int flag;
    int i;
    int j;

    i = 0;
    j = 0;
    flag = 0;
    if (str == NULL)
        return (NULL);
    unqoute_str = malloc (sizeof(char) * (rm_quotelen(str) + 1));
    if (unqoute_str == NULL)
        return (NULL);
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
            unqoute_str[j++] = str[i];
        i++;
    }
    free(str);
    unqoute_str[j] = '\0';
    return (unqoute_str);
}

int check_for_echo(t_token *tokens)
{
    char *holder;
    int i;

    i = 0;
    holder = ft_strdup(ft_lstlast_token(tokens)->content);
    while (holder[i] && (holder[i] != DQUOTE && holder[i] != QUOTE))
        i++;
    holder = remove_quote(holder);
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

int count_special_chars(char *line, int *s_count)
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
                    return (print_error("parse error\n", 2));
                else if (line[i + 1] && line[i + 1] == LESS)
                    return (print_error("parse error\n", 2));
                else if (count_repetition(line, line[i], i) == 2)
                    count++;
                else if (i == 0 || line[i - 1] != GREATER)
                    count++;
            }
            else if (line[i] == LESS)
            {
                if (count_repetition(line, line[i], i) > 2)
                   return (print_error("parse error\n", 2));
                else if (line[i + 1] && line[i + 1] == GREATER)
                    return (print_error("parse error\n", 2));
                else if (count_repetition(line, line[i], i) == 2)
                    count ++;
                else if (i == 0 || line[i - 1] != LESS)
                {
                    //printf("1\n");
                    count++;
                }
            }
            else if (line[i] == CPIPE)
            {
                if (count_repetition(line, line[i], i) > 2)
                   return (print_error("parse error\n", 2));
                else if (count_repetition(line, line[i], i) == 2)
                    count ++;
                else if (i == 0 || line[i - 1] != CPIPE)
                    count++;
            }
            else if (i == 0 || line[i] == AMPERSAND)
            {
                if (count_repetition(line, line[i], i) > 2)
                    return (print_error("parse error\n", 2));
                else if (count_repetition(line, line[i], i) == 2)
                    count++;
            }
            else if (line[i] == '(' || line[i] == ')')
                count++;
        }
        i++;
    }
    *s_count = count;
    return (EXIT_SUCCESS);
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

// int modify_line(char **line)
// {
//     int i;
//     int j;
//     int flag;
//     char *tmpline;
//     int schr_count;

//     i = 0;
//     j = 0;
//     flag = 0;
//     if (count_special_chars(*line, &schr_count))
//         return (EXIT_FAILURE);
//     tmpline = malloc(sizeof(char) * (ft_strlen(*line) + schr_count * 2 + 1));
//     if (tmpline == NULL)
//         return (EXIT_FAILURE);
//     while ((*line)[i])
//     {
//         if (flag == 0 && ((*line)[i] == DQUOTE ||  (*line)[i] == QUOTE))
//             flag = 1;
//         else if (flag == 1 && ((*line)[i] == DQUOTE ||  (*line)[i] == QUOTE))
//             flag = 0;
//         if (flag == 0 && ((*line)[i] == CPIPE || (*line)[i] == GREATER || (*line)[i] == LESS 
//             || ((*line)[i] == AMPERSAND && (*line)[i + 1] && (*line)[i + 1] == AMPERSAND) 
//             || (*line)[i] == '(' || (*line)[i] == ')'))
//         {
//             tmpline[j++] = ' ';
//             if ((*line)[i + 1] && (*line)[i + 1] != (*line)[i] && (i == 0 || (*line)[i - 1] != (*line)[i]))
//                 tmpline[j++] = (*line)[i];
//             else
//             {
//                 tmpline[j++] = (*line)[i++];
//                 tmpline[j++] = (*line)[i];
//             }
//             tmpline[j] = ' ';
//         }
//         else 
//             tmpline[j] = (*line)[i];
//         i++;
//         j++;
//     }
//     tmpline[j] = '\0';
//     free(*line);
//     *line = tmpline;
//     return (EXIT_SUCCESS);
// }

int schar_detected(char c)
{
    if (c == CPIPE || c == GREATER 
        || c == LESS || c == AMPERSAND 
        || c == OPAREN || c == CPAREN)
        return (1);
    return (0);
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
        if (flag == 0 && (line[i] == DQUOTE ||  line[i] == QUOTE))
            flag = 1;
        else if (flag == 1 && (line[i] == DQUOTE ||  line[i] == QUOTE))
            flag = 0;
        if (flag == 0 && schar_detected(line[i]))
        {
            if (line[i] == OPAREN || line[i] == CPAREN)
                count++;
            else if (line[i] == GREATER && (!i || line[i - 1] != GREATER))
                    count++;
            else if (line[i] == LESS && (!i || line[i - 1] != LESS))
                count++;
            else if (line[i] == CPIPE && (!i || line[i - 1] != CPIPE))
                count++;
            else if (line[i] == AMPERSAND && (!i || line[i - 1] != AMPERSAND))
            {
                if (line[i + 1] &&  line[i + 1] == AMPERSAND)
                    count++;
            }
        }
    }
    return (count);
}

char *expand_line(char *line, size_t len)
{
    char *newline;
    size_t i;
    size_t j;
    int flag;

    i = -1;
    j = 0;
    flag = 0;
    newline = (char *)malloc (sizeof(char) * len);
    while (line[++i])
    {
        if (flag == 0 && (line[i] == DQUOTE ||  line[i] == QUOTE))
            flag = 1;
        else if (flag == 1 && (line[i] == DQUOTE ||  line[i] == QUOTE))
            flag = 0;
        if (flag == 0 && schar_detected(line[i]))
        {
            if (line[i] == CPAREN || line[i] == OPAREN)
            {
                newline[j++] = ' ';
                newline[j] = line[i];
                newline[++j] = ' ';
            }
            else if (line[i] == AMPERSAND)
            {
                if (i != 0 && line[i - 1] != line[i] && line[i + 1] && line[i + 1] == line[i])
                    newline[j++] = ' ';
                newline[j] = line[i];
                if (line[i + 1] && line[i + 1] != line[i] && (i != 0 && line[i - 1] == line[i]))
                    newline[++j] = ' ';
            }
            else 
            {
                if ((i != 0 && line[i - 1] != line[i]))
                    newline[j++] = ' ';
                newline[j] = line[i];
                if (line[i + 1] && line[i + 1] != line[i])
                    newline[++j] = ' ';
            }
        }
        else 
            newline[j] = line[i];
        j++;
    }
    newline[j] = '\0';
    return (newline);
}

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