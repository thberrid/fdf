/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_persp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 05:39:44 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/25 07:47:24 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void		perspective(t_vertex *dest, t_vertex *src)
{
	/*
	ft_putfloat(src->x, 10);
	ft_putstr(" / ");
	ft_putfloat(src->x + 1, 10);
	ft_putchar('\n');
	*/
	dest->x = src->x / (src->z + 1);
	dest->y = src->y / (src->z + 1);
	dest->z = src->z;
	/*
	ft_putstr("dest. x ");
	ft_putfloat(dest->x, 10);
	ft_putchar('\n');
	*/
}
