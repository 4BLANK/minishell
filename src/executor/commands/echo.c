#include "../../../lib/libft/libft.h"
#include <stdio.h>

int check_nl_flag(const char *str)
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

void print_with_nl(const char **args)
{
  int i;

  i = 0;
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

void print_without_nl(const char **args)
{
  int i;

  i = 0;
  while (args[i])
  {
    printf("%s", args[i]);
    i++;
    if (args[i])
      printf(" ");
  }
}

void echo(const char **args, int ac)
{
  int i;

  i = 0;
  if (ft_strncmp(args[i], "-n", 2))
  {
    if (check_nl_flag(args[i]))
      print_with_nl(args);
    else
      print_without_nl(args + 1);
  }
  else
    print_without_nl(args + 1);
}
