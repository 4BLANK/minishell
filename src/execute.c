#include "../includes/minishell.h"

// count the number of nodes in the linked list
size_t *lstsize(t_argument *lst)
{
    int count;
    t_argument *current;
    
    count = 0;
    current = lst;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return (count);
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

int execute_cmd(t_ast_node *cmd)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        return (EXIT_FAILURE);
    else if (pid == 0)
    {
        // child
    }
    else 
    {
        // parent
    }
    return (EXIT_FAILURE);
}