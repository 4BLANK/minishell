#include "../../../includes/minishell.h"

size_t count_matched(char *str, t_argument *e_args)
{
    size_t count;

    count = 0;
    while (e_args != NULL)
    {   
        if (ft_strncmp(str, e_args->content, ft_strlen(str)) == 0)
            count++;
        e_args = e_args->next;
    }
    return (count);
}

char **get_matched(char *str, t_argument *e_args)
{
    char **match_str;
    size_t count;
    
    match_str = NULL;
    count = count_matched(str, e_args);
    if (count == 0)
        return (NULL);
    match_str = (char **)malloc(sizeof(char *) * (count + 1));
    if (match_str == NULL)
        return NULL;
    count = 0;
    while (e_args != NULL)
    {   
        if (ft_strncmp(str, e_args->content, ft_strlen(str)) == 0)
        {
            match_str[count] = ft_strdup(e_args->content);
            count++;
        }
        e_args = e_args->next;
    }
    match_str[count] = NULL;
    return (match_str);
}

void cmp_entries(char *str, t_argument *e_args)
{
    char **splited_str;
    char **matched;

    matched = NULL;
    splited_str = ft_split(str, '*');
    if (splited_str == NULL)
        return ;
    matched = get_matched_front(str, e_args);
    if (matched = NULL)
        return ;
    
}

int wildcard(char *arg)
{
    struct dirent *de;
    t_argument *e_args;
    char *tmp;
    t_argument *var;
    DIR *dir;

    // arg = modify_str(arg);
    dir = opendir(".");
    if (dir == NULL)
    {
        ft_putstr_fd("open dir error", 2);
        return (EXIT_FAILURE);
    }
    de = readdir(dir);
    while (de != NULL)
    {
        var = ft_argsnew(ft_strdup(de->d_name));
        if (var == NULL)
        {
            closedir(dir);
            return (EXIT_SUCCESS);
        }
        ft_argsadd_back(&e_args, var);
        de = readdir(dir);
    }
    cmp_entries(arg, e_args);
    // new function
    // tmp = ft_strrchr(arg, '*');
    // if (tmp != NULL)
    // {

    // }
}