/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:06:01 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/11 02:07:48 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_ast_node **ast, char *line)
{
	t_token	*tokenlst;

	tokenlst = NULL;
	if (modify_line(&line) > 0)
		return (free(line), PARSE_ERROR);
	if (tokens_spliter(line, &tokenlst) || validate_token(&tokenlst))
	{
		tokens_lstclear(&tokenlst);
		return (PARSE_ERROR);
	}
	lexer(tokenlst);
	// printf(GREEN "== TOKENS LIST =========>\n" RESET);
	// print_lst(tokenlst);
	if (expander_core(&tokenlst))
		return (PARSE_ERROR);
	*ast = build_ast(tokenlst);
	tokens_lstclear(&tokenlst);
	return (EXIT_SUCCESS);
}
