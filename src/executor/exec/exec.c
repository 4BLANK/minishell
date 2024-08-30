#include "../../../lib/libft/libft.h"
#include <unistd.h>

void execute_simple_commands(const char *pathname, char *const *args)
{
  execv(pathname, args + 1);
}

void execute_command()
