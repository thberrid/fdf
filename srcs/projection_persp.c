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

	dest->x = (src->x) / (src->z) + src->x;
	dest->y = (src->y) / (src->z) + src->y;

	dest->z = src->z;
}
