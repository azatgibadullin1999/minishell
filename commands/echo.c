/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlena <larlena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 20:14:26 by hapryl            #+#    #+#             */
/*   Updated: 2021/04/20 19:16:26 by larlena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/commands.h"

void	ft_echo(t_all *all, t_parser *parser)
{
	int	i;

	i = 2;
	if (!ft_strchr(parser->arg[1], 'n'))
		while (parser->arg[i])
		{
			ft_putendl_fd(parser->arg[i], 1);
			i++;
		}
	else
		while (parser->arg[i])
		{
			if (i != 2)
				ft_putchar_fd(' ', 1);
			ft_putstr_fd(parser->arg[i], 1);
			i++;
		}
	exit(0);
}
