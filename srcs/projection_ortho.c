/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_ortho.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 01:21:44 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 20:15:50 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	ortho(t_vertex *dest, t_vertex *src)
{
	dest->x = src->x + (src->z / 2);
	dest->y = src->y + src->z;
	dest->z = src->z;
	ft_putstr("ortho ");
	ft_putfloat(dest->x, 5);
	ft_putchar('\n');
	ft_putfloat(dest->y, 5);
	ft_putchar('\n');
	ft_putfloat(dest->z, 5);
	ft_putchar('\n');
}
