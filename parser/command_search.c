/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:30:02 by larlena           #+#    #+#             */
/*   Updated: 2021/05/17 13:50:56 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_search_builtin_commands(t_all *all, t_list *parser, char *command)
{
	size_t	len;

	len = ft_strlen(command) + 1;
	if (!ft_strncmp(command, "export", len))
	{
		if (((t_parser *)parser->content)->arg[1])
			ft_export_add(all, ((t_parser *)parser->content));
		else
			ft_export(all);
	}
	else if (!ft_strncmp(command, "unset", len))
		ft_unset(all, ((t_parser *)parser->content));
	else if (!ft_strncmp(command, "exit", len))
		ft_exit(all, ((t_parser *)parser->content));
	else if (!ft_strncmp(command, "echo", len))
		ft_echo(all, ((t_parser *)parser->content));
	else if (!ft_strncmp(command, "cd", len))
		ft_cd(all, ((t_parser *)parser->content));
	else if (!ft_strncmp(command, "pwd", len))
		ft_pwd(all);
	else if (!ft_strncmp(command, "env", len))
		ft_env(all);
	else
		return (-1);
	return (0);
}

void		ft_add_slash(char **src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		ft_rewrite(&src[i], '/');
		i++;
	}
}

size_t		ft_arrlen(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_add_emty_line(char **src)
{
	char	**dst;
	size_t	arrsize;

	arrsize = ft_arrlen(src);
	dst = ft_rewrite_arr(src, arrsize);
	dst[arrsize] = ft_strdup("");
	return (dst);
}

char	**ft_add_present_dir(void)
{
	char	**dst;
	char	tmp[1024];

	getcwd(tmp, 1024);
	dst = ft_calloc(sizeof(char *), 2);
	*dst = ft_strdup(tmp);
	ft_add_slash(dst);
	return (dst);
}

static char	**ft_get_path(t_all *all, char *command)
{
	t_dictionary	*buf;
	char			**dst;

	if (!ft_strncmp("./", command, 2) || !ft_strncmp("../", command, 3))
		dst = ft_add_present_dir();
	else
	{
		buf = ft_dic_get_value(all->env, "PATH");
		if (!buf)
			return (NULL);
		dst = ft_split(buf->value, ':');
		ft_add_slash(dst);
		dst = ft_add_emty_line(dst);
	}
	return (dst);
}

static int	ft_executin_command(t_all *all, t_list *parser,
								char *path, char *command)
{
	int		fd;
	char	*tmp;

	tmp = ft_strjoin(path, command);
	fd = open(tmp, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	execve(tmp, ((t_parser *)parser->content)->arg, ft_get_env(all));
	free(tmp);
	return (0);
}

void	ft_search_fork_commands(t_all *all, t_list *parser, char *command)
{
	char	**path;
	size_t	i;

	i = -1;
	path = ft_get_path(all, command);
	if (!path)
		exit(0);
	while (path[++i])
	{
		if (!ft_executin_command(all, parser, path[i], command))
			exit(0);
		free(path[i]);
	}
	free(path);
}

void	ft_fd_replacement(t_list *begin, t_list *previous, t_list *present)
{
	if (begin == present)
	{
		if (((t_parser *)present->content)->redfd[FD_R])
			dup2(((t_parser *)present->content)->redfd[FD_R], FD_R);
		if (((t_parser *)present->content)->redfd[FD_W])
			dup2(((t_parser *)present->content)->redfd[FD_W], FD_W);
		else
			dup2(((t_parser *)present->content)->pipefd[FD_W], FD_W);
	}
	else if (present->next != NULL)
	{
		if (((t_parser *)present->content)->redfd[FD_R])
			dup2(((t_parser *)present->content)->redfd[FD_R], FD_R);
		else
			dup2(((t_parser *)previous->content)->pipefd[FD_R], FD_R);
		if (((t_parser *)present->content)->redfd[FD_W])
			dup2(((t_parser *)present->content)->redfd[FD_W], FD_W);
		else
			dup2(((t_parser *)present->content)->pipefd[FD_W], FD_W);
	}
	else
	{
		if (((t_parser *)present->content)->redfd[FD_W])
			dup2(((t_parser *)present->content)->redfd[FD_W], FD_W);
		if (((t_parser *)present->content)->redfd[FD_R])
			dup2(((t_parser *)present->content)->redfd[FD_R], FD_R);
		else
			dup2(((t_parser *)previous->content)->pipefd[FD_R], FD_R);
	}
}

t_list	*ft_search_previous(t_list *begin, t_list *present)
{
	if (begin == present)
		return (begin);
	while (begin->next != present)
		begin = begin->next;
	return (begin);
}

int	ft_search_commands(t_all *all, t_list *parser)
{
	ft_fd_replacement(all->parser,  ft_search_previous(all->parser, parser), parser);
	if (!ft_search_builtin_commands(all, parser,
			((t_parser *)parser->content)->arg[0]))
		exit(all->err);
	ft_search_fork_commands(all, parser,
		((t_parser *)parser->content)->arg[0]);
	exit(127);
	return (0);
}
