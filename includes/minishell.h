/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 18:13:49 by hapryl            #+#    #+#             */
/*   Updated: 2021/04/12 19:23:16 by hapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <term.h>
# include <errno.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../Libft/libft.h"
# include "utils.h"
typedef struct s_parser
{
	char	**arg;
	int		i;
	int		j;
	int		fd_r;
	int		fd_w;
}				t_parser;
typedef struct s_all
{
	char			str[2056];
	char			buff[100];
	int				i;
	char			**envc;
	char			*flags;
	t_dictionary	*env;
	t_dllist		*history;
	t_parser		parser;
}				t_all;
# include "parser.h"
# include "commands.h"

extern int result;

int			ft_analize_string(t_all *all);
void		ft_set_env(t_all *all, char **env);
char		**ft_get_env(t_all *all);
int			ft_type(t_all *all);


#endif