/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlena <larlena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:31:29 by larlena           #+#    #+#             */
/*   Updated: 2021/05/19 10:36:38 by larlena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_malloc(size_t size)
{
	void	*buf;

	buf = malloc(size);
	if (buf == NULL)
		exit (0);
	return (buf);
}
