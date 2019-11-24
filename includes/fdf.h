/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:22:00 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/20 09:49:26 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <mlx.h>
# include <keycodes.h>

/*
**	MATRICES STRUCT
*/

typedef struct	s_matrix
{
	unsigned int	row_len;
	unsigned int	column_len;
	void			**value;
	unsigned int	type;
}				t_matrix;

typedef struct	s_vertex
{
	float	x;
	float	y;
	float	z;
}				t_vertex;

/*
**	GRAPHIC RELATED STRUCT
*/

/*
**	ALPHA		 (0 <-> 255)  ==  (100% <-> 0% OPACITY)
*/

# define RED	16
# define GREEN	8
# define BLUE	0
# define ALPHA	24

typedef struct	s_pixel
{
	unsigned int	x;
	unsigned int	y;
	int				color;
}				t_pixel;

typedef struct 	s_img
{
	void	*id;
	char	*data;
	int		bits_px;
	int		size_line;
	int		endian;
}				t_img;

typedef	struct	s_window
{
	void			*ptr;
	void			*mlx;
	t_img			img;
	unsigned int	width;
	unsigned int	height;
	char			name[32];
}				t_window;

# define INT	sizeof(int)
# define FLOAT	sizeof(float)
# define PTR	sizeof(void *)
# define VERTEX	sizeof(t_vertex)

# define FORCE_UINT(x)	*((unsigned int *)&x)
# define FORCE_INT(x)	*((int *)&x)

/*
**	PARSING
*/

int				map_parse(t_matrix *matrix, char *path);
unsigned int	raw_len(char **raw);
void			map_print(t_matrix *matrix);
int				matrix_addrow(t_matrix *matrix, char **raw, float y);

/*
**	MATRIX BASIC MANIPULATION
*/

float			matrix_get(t_matrix *vertices, float value,
					float (*f)(float, float));
void			matrix_set(t_matrix *vertices, t_vertex *vector,
					void (*f)(t_vertex *, t_vertex *));
void			matrix_apply(t_matrix *vertices, t_matrix *vectors,
					void (*f)(t_vertex *, t_vertex *));
void			matrix_free(t_matrix *matrix);
void			vertex_decrement(t_vertex *this, t_vertex *vector);

/*
**	DRAWING
*/

int				plan_init(t_matrix *vertices, t_matrix *plan);
void			color_add(int *color, unsigned char value, unsigned char field);
void			color_remove(int *color, unsigned char value,
					unsigned char field);

/*
**	PROJECTIONS
*/

void			perspective(t_vertex *map, t_vertex *vertices);

#endif
