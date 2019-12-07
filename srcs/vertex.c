/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:33:00 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 02:42:26 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	vertex_decrement(t_vertex *this, t_vertex *vector)
{
	this->x -= vector->x;
	this->y -= vector->y;
	this->z = (this->z * -1) + vector->z;
}

void	vertex_increment(t_vertex *this, t_vertex *vector)
{
	this->x += vector->x;
	this->y += vector->y;
	this->z += vector->z;
}
