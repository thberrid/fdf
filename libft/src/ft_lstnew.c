/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 15:48:26 by thberrid          #+#    #+#             */
/*   Updated: 2019/04/19 18:12:17 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new)
	{
		new->next = NULL;
		if (content)
		{
			new->content = ft_memalloc(content_size);
			if (new->content)
			{
				new->content = ft_memcpy(new->content, content, content_size);
				new->content_size = content_size;
			}
			else
				ft_memdel((void **)new);
		}
		else
		{
			new->content = NULL;
			new->content_size = 0;
		}
	}
	return (new);
}
