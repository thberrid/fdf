/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 06:53:37 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/18 07:09:07 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	color_add(int *color, unsigned char value, unsigned char field)
{
	*color |= (value << field);
}

void	color_remove(int *color, unsigned char value, unsigned char field)
{
	*color ^= (value << field);
}
