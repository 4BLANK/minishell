/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:06:01 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/12 01:36:57 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_ast_node **ast, char *line)
{
	t_token	*tokenlst;
	int status;

	status = 0;
	tokenlst = NULL;
	if (modify_line(&line) > 0)
		return (free(line), PARSE_ERROR);
	if (tokens_spliter(line, &tokenlst))
		return (tokens_lstclear(&tokenlst), PARSE_ERROR);
	status = validate_token(&tokenlst);
	if (status != 0)
		return (tokens_lstclear(&tokenlst), status);
	lexer(tokenlst);
	if (expander_core(&tokenlst))
		return (PARSE_ERROR);
	*ast = build_ast(tokenlst);
	tokens_lstclear(&tokenlst);
	return (EXIT_SUCCESS);
}
