#include "../../../includes/minishell.h"

t_argument *get_curdir_entries(void)
{
    DIR *dir;
    struct dirent *de;
    t_argument *args;
    t_argument *var;
    
    args = NULL;
    var = NULL;
    dir = opendir(".");
    if (dir == NULL)
    {
        ft_putstr_fd("open dir error", 2);
        return (NULL);
    }
    de = readdir(dir);
    while (de != NULL)
    {
        var = ft_argsnew(ft_strdup(de->d_name));
        if (var == NULL)
        {
            closedir(dir);
            return (NULL);
        }
        ft_argsadd_back(&args, var);
        de = readdir(dir);
    }
    closedir(dir);
    return (args); 
}

bool is_match(const char *s, const char *p) {
    
    bool **dp;
    size_t s_len;
    size_t p_len;
    size_t i, j;
    bool result;

    s_len = strlen(s);
    p_len = strlen(p);

    // Allocate the DP table
    dp = (bool **)malloc((s_len + 1) * sizeof(bool *));
    i = 0;
    while (i <= s_len) {
        dp[i] = (bool *)malloc((p_len + 1) * sizeof(bool));
        i++;
    }

    // Initialize dp[0][0] to true (empty pattern matches empty string)
    dp[0][0] = true;

    // Initialize the first row (matching an empty string with the pattern)
    j = 1;
    while (j <= p_len) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 1];  // '*' can match an empty sequence
        } else {
            dp[0][j] = false;  // Other characters can't match an empty string
        }
        j++;
    }

    // Initialize the first column (no pattern matches a non-empty string)
    i = 1;
    while (i <= s_len) {
        dp[i][0] = false;
        i++;
    }

    // Fill the DP table
    i = 1;
    while (i <= s_len) {
        j = 1;
        while (j <= p_len) {
            if (p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  // Match one character
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];  // '*' matches empty or more characters
            } else {
                dp[i][j] = false;  // No match
            }
            j++;
        }
        i++;
    }

    // Store the result before freeing the memory
    result = dp[s_len][p_len];

    // Free the allocated memory
    i = 0;
    while (i <= s_len) {
        free(dp[i]);
        i++;
    }
    free(dp);

    return result;
}

t_argument *wildcard_core(char *pattern)
{
    t_argument *e_args;
    t_argument *e_matched;
    t_argument *tmp;
    
    tmp = NULL;
    e_matched = NULL;
    e_args = get_curdir_entries();
    if (e_args == NULL)
        return (NULL);
    while (e_args != NULL)
    {
        if (is_match(e_args->content, pattern))
        {
            tmp =  ft_argsnew(ft_strdup(e_args->content));
            if (tmp == NULL)
                return (NULL);
            ft_argsadd_back(&e_matched,tmp);
        }
        e_args = e_args->next;
    }
    clear_argslst(&e_args);
    return (e_matched);
}