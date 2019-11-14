/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:22:00 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/14 02:25:55 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>

typedef struct	s_hexcolor
{
	unsigned int	r : 8;
	unsigned int	g : 8;
	unsigned int	b : 8;
	unsigned int	a : 8;
}				t_hexcolor;

typedef struct	s_pixel
{
	int			x;
	int			y;
	t_hexcolor	color;
}				t_pixel;

typedef	struct	s_window
{
	void			*ptr;
	void			*mlx;
	unsigned int	width;
	unsigned int	height;
	char			name[32];
}				t_window;

#endif
