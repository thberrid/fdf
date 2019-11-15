/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:22:00 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/15 08:07:35 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <mlx.h>

/*
**	MATRICES STRUCT
*/

typedef struct	s_matrix
{
	unsigned int	row_len;
	unsigned int	column_len;
	int				**value;
}				t_matrix;

/*
**	MLX STRUCT
*/

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

/*
**	PARSING
*/

int				map_parse(t_matrix *matrix, char *path);
unsigned int	raw_len(char **raw);

/*
**	MATRIX BASIC MANIPULATION
*/

int				matrix_addrow(t_matrix *matrix, char **raw);
void			matrix_print(t_matrix *matrix);
void			matrix_free(t_matrix *matrix);

/*
**	DRAWING
*/

/*
**	CALCULUS
*/

#endif
