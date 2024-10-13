/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:30:53 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/13 00:30:54 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*sh;

int	main(void)
{
	char		*line;
	int			status;
	t_ast_node	*ast;

	ast = NULL;
	sh = setshell(__environ);
	while (1)
	{
		handle_signals(PARENT);
		line = readline("-> ");
		handle_signals(IGNORE);
		if (!line)
			exit_cmd(NULL, &ast);
		if (line[0] != '\0')
			add_history(line);
		status = parser(&ast, line);
		if (status != 0)
			sh->ex_status = status;
		if (ast != NULL && status == 0)
		{
			sh->ast = ast;
			sh->ex_status = kickoff(ast);
			free_mem(0);
		}
		else 
			sh->ex_status = status;
	}
	return (EXIT_SUCCESS);
}
