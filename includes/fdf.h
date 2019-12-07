/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:22:00 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 12:30:11 by thberrid         ###   ########.fr       */
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

# define RED	16
# define GREEN	8
# define BLUE	0
# define ALPHA	24

typedef struct	s_pixel
{
	int		x;
	int		y;
	int		color;
	float	step_red;
	float	step_green;
}				t_pixel;

typedef struct	s_img
{
	void			*id;
	char			*data;
	int				bits_px;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}				t_img;

# define ORTHO	0
# define PERSP	1

typedef	struct	s_window
{
	void			*ptr;
	void			*mlx;
	t_img			img;
	t_matrix		px_coord;
	t_matrix		vertices;
	unsigned char	proj_type;
	unsigned int	width;
	unsigned int	height;
	char			name[32];
	t_matrix		plan;
}				t_window;

/*
**	PARSING
*/

int				map_parse(t_matrix *matrix, char *path);
unsigned int	raw_len(char **raw);
void			raw_free(char **raw);
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
void			vertex_increment(t_vertex *this, t_vertex *vector);
float			get_min(float value, t_vertex *new_value,
					unsigned char dimension);
float			get_max(float value, t_vertex *new_value,
					unsigned char dimension);
void			print_this(t_vertex *this, t_vertex *nullit);
void			matrix_transform(t_matrix *scale, t_vertex *vertices);
int				vertices_scale(t_matrix *vertices, float coef);
int				vertices_auto_adjust_scale(t_window *w, t_matrix *plan);
int				malloc_matrix(t_matrix *matrix);

/*
**	DRAWING
*/

void			img_build(t_matrix *img, t_matrix *plan, t_window *w);
void			img_scaling(t_matrix *img, t_matrix *plan, t_window *w);
void			color_add(int *color, unsigned char value, unsigned char field);
void			color_incr(int *color, unsigned char value,
					unsigned char field);
void			color_decr(int *color, unsigned char value,
					unsigned char field);
void			color_remove(int *color, unsigned char value,
					unsigned char field);
void			color_setwhite(int *color);
int				draw_obj(t_window *w);
int				int_minmax(t_matrix *matrix, int def_val, int dimension,
					int (*f)(int, t_pixel *, int));
int				is_sup(int a, t_pixel *px, int dimension);
int				int_range(t_matrix *matrix, int dimension);
void			img_centering(t_matrix *img, t_window *w);

void			bresen_set_delta(t_pixel *delta, t_pixel *start, t_pixel *end);
unsigned int	bresen_set_deltafast(t_pixel *start, t_pixel *end);
float			bresen_update_error(float error, t_pixel *start, t_pixel *end,
					t_pixel *pen);
void			bresen_init_stepcolor(unsigned int delta_fast, t_pixel *pen,
					t_pixel *start, t_pixel *end);
void			bresen_increm_color(t_pixel *start, t_pixel *end, t_pixel *pen,
					unsigned int step_color);
void			bresen_update_color(t_pixel *pen, t_pixel *start, t_pixel *end,
					unsigned int delta_fast);

int				set_rotation_angle(t_matrix *matrix, double theta);
int				set_scale(t_matrix *matrix, float coef);
void			matrix_transform(t_matrix *rot, t_vertex *vertices);
int				vertices_scale(t_matrix *vertices, float coef);
int				vertices_rotate(t_window *w, unsigned int keycode);

void			foreach_edges_draw(t_img *img, t_window *w);
void			draw_edges(t_img *img, t_matrix *pixels, unsigned int x,
					unsigned int y);
void			draw_line(t_pixel *start, t_pixel *end, t_img *img);
int				draw_obj(t_window *w);

/*
**	PROJECTIONS
*/

void			perspective(t_vertex *map, t_vertex *vertices);
void			ortho(t_vertex *map, t_vertex *vertices);
int				get_dimension(int dimension, t_pixel *px);
void			apply_scale(t_matrix *img, t_matrix *plan, t_window *w,
					float scaler);
unsigned char	get_alt_color(float y, float max);
unsigned char	get_alt_alpha(float y, float max);

#endif
