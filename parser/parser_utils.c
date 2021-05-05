/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlena <larlena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:28:15 by larlena           #+#    #+#             */
/*   Updated: 2021/04/26 17:34:18 by larlena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_clear_parser(t_list *parser)
{
	t_list	*tmp;

	while (parser)
	{
		tmp = parser->next;
		ft_free(((t_parser *)parser->content)->arg);
		free(parser->content);
		free(parser);
		parser = tmp;
	}
}

void	ft_create_new_list_parser(t_list **parser)
{
	ft_lstadd_front(parser, ft_lstnew(ft_malloc(sizeof(t_parser))));
	((t_parser *)(*parser)->content)->arg = ft_calloc(sizeof(char *), 2);
	((t_parser *)(*parser)->content)->arg[0] = ft_calloc(sizeof(char), 1);
}

void	ft_initialization_struct_parser(t_all *all, t_list **parser)
{
	all->ln = 0;
	ft_create_new_list_parser(parser);
	(*parser)->next = NULL;
}

void	ft_rewrite(char **src, char c)
{
	char	*dst;
	size_t	size;

	size = ft_strlen(*src);
	dst = ft_calloc(sizeof(char), size + 2);
	ft_memcpy(dst, *src, size);
	dst[size] = c;
	free(*src);
	*src = dst;
}

char	**ft_rewrite_arr(char **arg, size_t size)
{
	char	**dst;
	size_t	i;

	i = -1;
	dst = (char **)calloc(sizeof(char *), size + 2);
	dst[size] = (char *)calloc(sizeof(char), 1);
	while (++i < size)
		dst[i] = arg[i];
	free(arg);
	return (dst);
}
