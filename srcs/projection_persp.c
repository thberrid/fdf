/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_persp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 05:39:44 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/08 21:01:08 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <math.h>

void		perspective(t_vertex *dest, t_vertex *src)
{
/*
	(void)src;
	t_matrix	p;
	t_vertex	*v;
	float s;
	float f;

	s = 1 / (tan((50 / 2) * (M_PI/180)));
	p.row_len = 1;
	f = 0.01;
	p.column_len = 3;
	malloc_matrix(&p);
	v = &((t_vertex *)p.value[0])[0];
	v->x = 1;
	v->y = 0;
	v->z = 0;
	v = &((t_vertex *)p.value[0])[1];
	v->x = 0;
	v->y = 1;
	v->z = 0;
	v = &((t_vertex *)p.value[0])[2];
	v->x = 0;
	v->y = 0;
	v->z = -1;
	unsigned int i;
	unsigned int j;
	i = 0;
	while (i < p.row_len)
	{
		j = 0;
		while (j < p.column_len)
		{
			matrix_transform(&p, dest);
			j += 1;
		}
		i += 1;
	}
	
*/
	t_pixel bonus;
	
	bonus.x = src->x;
	if (src->x > 1)
		bonus.x += 1;
	bonus.y = src->y;
	if (src->y > 1)
		bonus.y += 1;
	dest->x = (src->x)  / (src->z) + bonus.x;
	dest->y = (src->y) / (src->z) + bonus.y;
	dest->z = src->z;
/*
	ft_putstr("persp ");
	ft_putfloat(dest->x, 5);
	ft_putchar('\n');
	ft_putfloat(dest->y, 5);
	ft_putchar('\n');
	ft_putfloat(dest->z, 5);
	ft_putchar('\n');
*/
}
