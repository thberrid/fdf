/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_persp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 05:39:44 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/19 08:11:25 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		projection_perspective(t_matrix *vertices, t_matrix *plan)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < vertices->row_len)
	{
		j = 0;
		while (j < vertices->column_len)
		{
			projection((t_vertex *)vertices->value[][])
			j += 1;
		}
		i += 1;
	}
	return (1);
}
