/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:22:00 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/19 08:25:46 by thberrid         ###   ########.fr       */
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
	unsigned int	padding;
	void			**value;
	unsigned int	type;
}				t_matrix;

/*
**	GRAPHIC RELATED STRUCT
*/

# define RED	16
# define GREEN	8
# define BLUE	0
# define ALPHA	24	// 0 <-> 255 = 100% <-> 0% OPACITY

typedef struct	s_pixel
{
	int	x;
	int	y;
	int	color;
}				t_pixel;

typedef struct	s_vertex
{
	float	x;
	float	y;
	float	z;
}				t_vertex;

typedef	struct	s_window
{
	void			*ptr;
	void			*mlx;
	unsigned int	width;
	unsigned int	height;
	char			name[32];
}				t_window;

# define INT	sizeof(int)
# define FLOAT	sizeof(float)
# define PTR	sizeof(void *)
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

/*
**	MATRIX BASIC MANIPULATION
*/

int				matrix_addrow(t_matrix *matrix, char **raw, float y, 
					void (*set_row)(t_matrix *, char **, float y));
void			matrix_free(t_matrix *matrix);

void			row_setvertex(t_matrix *matrix, char **raw, float y);

/*
**	DRAWING
*/

int		plan_init(t_matrix *vertices, t_matrix *plan);
void	color_add(int *color, unsigned char value, unsigned char field);
void	color_remove(int *color, unsigned char value, unsigned char field);

/*
**	PROJECTIONS
*/

int		perspective(t_matrix *map, t_matrix *plan);

#endif
