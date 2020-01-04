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

void		perspective(t_vertex *dest, t_vertex *src, float norm)
{
	int		focal;
	float	scale;

	focal = 2;
	scale = ((src->z / (norm)) * focal);
	if (scale < 0)
		scale *= -1;
	dest->x = src->x + (src->z / 2);
	dest->y = src->y + src->z;
	dest->x /= scale;
	dest->y /= scale;
}
