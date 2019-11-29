/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 06:53:37 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/29 07:27:53 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
**	00	00	00	00
**	 A	 R	 G	 B
**	
**	field = R | G | B | A 
**	value <= 0 && value >= 255
*/

void	color_add(int *color, unsigned char value, unsigned char field)
{
	*color |= (value << field);
}

void	color_incr(int *color, unsigned char value, unsigned char field)
{
	*color += (value << field);
}

void	color_remove(int *color, unsigned char value, unsigned char field)
{
	*color ^= (value << field);
}
