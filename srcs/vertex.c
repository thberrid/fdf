/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:33:00 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/27 05:22:12 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	vertex_decrement(t_vertex *this, t_vertex *vector)
{
	/*
	ft_putstr("< ");
	ft_putnbr(this->z);
	ft_putchar('\n');
	*/
	this->x -= vector->x;
	this->y -= vector->y;
	this->z = (this->z * -1) + vector->z;
	/*
	ft_putstr("> ");
	ft_putnbr(this->z);
	ft_putchar('\n');
	ft_putchar('\n');
	*/
}
