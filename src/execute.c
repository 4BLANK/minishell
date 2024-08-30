#include "../includes/minishell.h"

size_t lstsize(t_argument *lst)
{
    size_t count;
    t_argument *current;
    
    count = 0;
    current = lst;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return (count);
}

void free_strarray(char **str)
{
    int i;

    i = -1;
    while (str[++i])
        free(str[i]);
    free(str);
}

char **lst_tostrarray(t_argument *head) {

    size_t count;
    char **strarray;
    int i;

    i = 0;
    if (!(count = lstsize(head)))
        return NULL;
    strarray = (char **)malloc(sizeof(char *) * (count + 1));
    if (strarray == NULL)
        return NULL;

    while (head != NULL)
    {
        strarray[i] = ft_strdup(head->content);
        if (strarray[i] == NULL)
            return NULL;
        head = head->next;
        i++;
    }
    strarray[i] = NULL;
    return strarray;
}

void print_strarray(char **str)
{
    int i = -1;
    while (str[++i])
        printf("%s\n", str[i]);
}

int get_commandpath(char **cmd_path, char *cmd, char **env)
{
    char *path;
    char **paths;
    char *tmp;
    int i;

    i = -1;
    path = ft_getenv("PATH", env);
    if (path == NULL)
    {
        *cmd_path = NULL;
        return (EXIT_FAILURE);
    }
    paths = ft_split(path, ':');
    if (paths == NULL)
        return EXIT_FAILURE;
    tmp = ft_strjoin("/", cmd);
    while (paths[++i] != NULL)
    {
        *cmd_path = ft_strjoin(paths[i], tmp);
        if (!access(*cmd_path, X_OK))
        {
            free(path);
            free(tmp);
            free_strarray(paths);
            return (EXIT_SUCCESS);
        }
        free(*cmd_path);
    }
    free(path);
    free(tmp);
    free_strarray(paths);
    return (EXIT_FAILURE);
}   

int execute_cmd(t_ast_node *cmd, char **env)
{
    pid_t pid;
    int status;
    char **args;
    char *cmd_path;

    status = 0;
    if (cmd->type != COMMAND)
        return (EXIT_FAILURE);
    args = lst_tostrarray(cmd->data.childs.left->data.arg_list);
    if (get_commandpath(&cmd_path, args[0], env))
        return (EXIT_FAILURE);
    if ((pid = fork()) < 0)
        return (EXIT_FAILURE);
    else if (pid == 0)
    {
        if (execve(cmd_path, args, NULL) < 0)
            print_error("execv error\n", 2);
    }
    else 
    {
        waitpid(pid, &status, 0);
        if (WEXITSTATUS(status))
            return (EXIT_FAILURE);
        else 
            return EXIT_SUCCESS;
    }
    return (EXIT_FAILURE);
}