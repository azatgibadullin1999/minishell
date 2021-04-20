/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_ss.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlena <larlena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:49:01 by larlena           #+#    #+#             */
/*   Updated: 2021/04/20 14:03:57 by larlena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_semicolon(t_all *all, t_list **parser, const char *str)
{
	while (str[all->j + 1] == ' ')
		all->j++;
	ft_command_execution(all);
	ft_initialization_struct_parser(all, parser);
	return (0);
}

