#include "../../includes/minishell.h"

int check_nl_flag(char *str)
{
  int i;

  i = 0;
  while (str[i])
  {
    if (str[i] != '-' && str[i] != 'n')
      return (1);
    i++;
  }
  return (0);
}

void print_with_nl(char **args)
{
  int i;

  i = 0;
  if (!args)
      printf("\n");
  while (args[i])
  {
    printf("%s", args[i]);
    i++;
    if (args[i])
      printf(" ");
    else
      printf("\n");
  }
}

void print_without_nl(char **args)
{
  int i;

  i = 0;
  if (!args)
    return ;
  while (args[i])
  {
    printf("%s", args[i]);
    i++;
    if (args[i])
      printf(" ");
  }
}

int echo(char **args)
{
    if (!args[1])
    {
        printf("\n");
        return (EXIT_SUCCESS);
    }
    if (!ft_strncmp(args[1], "-n", 2))
    {
        if (check_nl_flag(args[1]))
            print_with_nl(args + 1);
        else
            print_without_nl(args + 2);
    }
    else
        print_with_nl(args + 1);
    return (EXIT_SUCCESS);
}
