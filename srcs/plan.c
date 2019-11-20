/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 08:12:06 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/20 08:00:15 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
**	CREATE AN EMPTY PLAN
*/

int		plan_init(t_matrix *vertices, t_matrix *plan)
{
	unsigned int	i;

	ft_bzero(plan, sizeof(t_matrix));
	i = 0;
	plan->row_len = vertices->row_len;
	plan->column_len = vertices->column_len;
	if (!(plan->value = ft_memalloc(PTR * vertices->row_len)))
		return (0);
	while (i < vertices->row_len)
	{
		if (!(plan->value[i] = ft_memalloc(VERTEX * vertices->column_len)))
			return (0);
		i += 1;
	}
	return (1);
}
