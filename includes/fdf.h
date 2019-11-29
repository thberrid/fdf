/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:22:00 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/29 02:10:15 by thberrid         ###   ########.fr       */
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

# define X 0
# define Y 1
# define Z 2

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
	int	x;
	int	y;
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
	t_matrix		px_coord;
	t_matrix		vertices;
	unsigned int	width;
	unsigned int	height;
	char			name[32];
}				t_window;

# define INT	sizeof(int)
# define FLOAT	sizeof(float)
# define PTR	sizeof(void *)
# define VERTEX	sizeof(t_vertex)
# define PIXEL	sizeof(t_pixel)

# define FORCE_UINT(x)	*((unsigned int *)&x)
# define FORCE_INT(x)	*((int *)&x)

# define ABS(x)			(x < 0 ? -x : x)

/*
**	PARSING
*/

int				map_parse(t_matrix *matrix, char *path);
unsigned int	raw_len(char **raw);
void			map_print(t_matrix *matrix);
int				matrix_addrow(t_matrix *matrix, char **raw, float y);
float			get_range(t_matrix *plan, unsigned char dimension);

/*
**	MATRIX BASIC MANIPULATION
*/

float			matrix_get(t_matrix *vertices, float value, 
					unsigned char dimension, 
					float (*f)(float, t_vertex*, unsigned char));
void			matrix_set(t_matrix *vertices, t_vertex *vector,
					void (*f)(t_vertex *, t_vertex *));
void			matrix_apply(t_matrix *vertices, t_matrix *vectors,
					void (*f)(t_vertex *, t_vertex *));
void			matrix_cpy(t_matrix *dest, t_matrix *src, t_vertex *vector,
					void (*f)(t_vertex *, t_vertex *, t_vertex *));
void			matrix_free(t_matrix *matrix);
int				matrix_init(t_matrix *vertices, t_matrix *plan, 
					unsigned char type);
void			vertex_decrement(t_vertex *this, t_vertex *vector);
float			get_min(float value, t_vertex *new_value, unsigned char dimension);
float			get_max(float value, t_vertex *new_value, unsigned char dimension);
void			print_this(t_vertex *this, t_vertex *nullit);

/*
**	DRAWING
*/

void			img_build(t_matrix *img, t_matrix *plan, t_window *w);
void			color_add(int *color, unsigned char value, unsigned char field);
void			color_remove(int *color, unsigned char value,
					unsigned char field);
int				draw_px(unsigned int keycode, t_window *w);

/*
**	PROJECTIONS
*/

void			perspective(t_vertex *map, t_vertex *vertices);
void			ortho(t_vertex *map, t_vertex *vertices);

#endif
