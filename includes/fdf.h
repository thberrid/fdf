/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:22:00 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/18 07:11:53 by thberrid         ###   ########.fr       */
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
	unsigned char	type;
	int				**value;
	unsigned int	padding;
}				t_matrix;

/*
**	MLX STRUCT
*/

# define RED	16
# define GREEN	8
# define BLUE	0
# define ALPHA	24	// 0 <-> 255 = 100% <-> 0% OPACITY

# define FORCE_UINT(x)	*((unsigned int *)&x)
# define FORCE_INT(x)	*((int *)&x)

typedef struct	s_pixel
{
	int	x;
	int	y;
	int	color;
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
void			arr_free(void *arr, unsigned int step, unsigned int len);

/*
**	DRAWING
*/

void	color_add(int *color, unsigned char value, unsigned char field);
void	color_remove(int *color, unsigned char value, unsigned char field);

/*
**	CALCULUS
*/

#endif
