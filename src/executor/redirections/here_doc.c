/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 01:41:05 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/13 03:02:53 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*create_file_name(void)
{
	static int	num = 0;
	char		*str;
	char		*res;
	char		*num_value;

	res = NULL;
	num_value = ft_itoa(num);
	str = "/tmp/heredoc_tmp";
	res = ft_strjoin(str, num_value);
	free(num_value);
	num++;
	return (res);
}

static void	clean_a_bit(char *file_name, char **delimiter, t_token **toklst,
		t_pair pair)
{
	free(file_name);
	free(*delimiter);
	*delimiter = NULL;
	tokens_lstclear(toklst);
	distroy_envlst(&sh->envlst);
	free(sh);
	close(pair.left);
	exit(pair.right);
}

static void	parent_rountine(pid_t pid, char *file_name, char **delimiter,
		t_pair *pair)
{
	waitpid(pid, &(pair->right), 0);
	if (WIFEXITED(pair->right))
		pair->right = WEXITSTATUS(pair->right);
	if (pair->right == DOOMSDAY)
	{
		pair->right = 130;
		free(file_name);
		file_name = NULL;
		ft_printf("\n");
	}
	if (!pair->right)
	{
		free(*delimiter);
		*delimiter = file_name;
	}
	close(pair->left);
}

int	here_doc(char **delimiter, int flag, t_token **toklst)
{
	int		fd;
	char	*file_name;
	pid_t	pid;

	t_pair(pair);
	file_name = create_file_name();
	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	pair.left = fd;
	pair.right = 0;
	if (fd < 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid > 0)
		parent_rountine(pid, file_name, delimiter, &pair);
	else if (pid == 0)
	{
		set_heredoc_signal_data(toklst, file_name, *delimiter, fd);
		pair.right = child_routine(delimiter, fd, flag);
		clean_a_bit(file_name, delimiter, toklst, pair);
	}
	else
		clean_a_bit(file_name, delimiter, toklst, pair);
	printf("[DEBUG] => [%d]\n", pair.right);
	return (pair.right);
}
