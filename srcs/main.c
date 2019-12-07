/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 22:47:17 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	clean_w_and_exit(t_window *w)
{
	matrix_free(&w->vertices);
	mlx_destroy_image(w->mlx, w->img.id);
	mlx_destroy_window(w->mlx, w->ptr);
	exit(0);
}

/*
** to search leaks, put before the exit = system("leaks fdf");
*/

int		get_keypressed(unsigned int keycode, t_window *w)
{
	matrix_free(&w->plan);
	matrix_free(&w->px_coord);
	if (keycode == KEY_PERSP)
		w->proj_type = PERSP;
	if (keycode == KEY_ORTHO)
		w->proj_type = ORTHO;
	if (keycode == KEY_ESC || keycode == KEY_Q)
		clean_w_and_exit(w);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		if (!vertices_rotate(w, keycode))
			return (0);
	if (keycode == KEY_TOP || keycode == KEY_BOTTOM)
		if (!vertices_scale(&w->vertices, (keycode == KEY_BOTTOM) ? .75 : 1.25))
			return (0);
	if (!matrix_init(&w->plan, &w->vertices, sizeof(t_vertex)))
		return (0);
	if (w->proj_type == ORTHO)
		matrix_apply(&w->plan, &w->vertices, &ortho);
	else
	{
		matrix_apply(&w->plan, &w->vertices, &perspective);
//		if (keycode == KEY_PERSP)
//			vertices_auto_adjust_scale(w, &w->plan);
	}
	if (!matrix_init(&w->px_coord, &w->plan, sizeof(t_pixel)))
		return (0);
	img_build(&w->px_coord, &w->plan, w);
	if (w->proj_type == PERSP)
		img_scaling(&w->px_coord, &w->plan, w);
	if (!ft_ischarset(keycode + 1, KEYS_TRANSLATION))
		img_centering(&w->px_coord, w);
	draw_obj(w);
	return (1);
}

void	print_usage(void)
{
	ft_putendl("\n< >      - rotations");
	ft_putendl("^ v      - zoom");
	ft_putendl("\n\"ok boomer\" - kevin\n");
}

void	window_init(t_window *w)
{
	ft_bzero(w, sizeof(t_window));
	w->width = 750;
	w->height = 750;
	w->proj_type = PERSP;
	ft_strcpy(w->name, "ok boomer");
}

void	vertex_remove_null(t_matrix *vertices)
{
	t_vertex	min;

	min.x = matrix_get(vertices, FT_INTMAX, X, &get_min);
	/*
	if (min.x < 0)
		min.x *= -1;
	if (!min.x)
		min.x = 1;
		*/
	min.x = 10;
	min.z = 0;
	min.y = matrix_get(vertices, FT_INTMIN, Y, &get_max);
	if (min.y > 0)
		min.y *= -2;
	if (!min.y)
		min.y = -10;
	/*
	min.z = matrix_get(vertices, FT_INTMAX, Z, &get_min);
	if (min.z < 0)
		min.z *= -1;
	if (!min.z)
		min.z = 1;
	*/
	matrix_set(vertices, &min, &vertex_increment);
}

int		main(int ac, char **av)
{
	t_window		w;

	window_init(&w);
	if (ac == 2)
	{
		if (!map_parse(&(w.vertices), av[1]))
			return (0);
		if (!matrix_init(&w.plan, &(w.vertices), sizeof(t_vertex))
			|| !w.vertices.row_len)
			return (0);
		vertex_remove_null(&w.vertices);	
		vertices_lookat(&w);
		matrix_apply(&w.plan, &w.vertices, &perspective);
//		if (!vertices_auto_adjust_scale(&w, &w.plan))
//			return (0);
		if (!matrix_init(&w.px_coord, &w.plan, sizeof(t_pixel)))
			return (0);
		img_build(&w.px_coord, &w.plan, &w);
		if (w.proj_type == PERSP)
			img_scaling(&w.px_coord, &w.plan, &w);
		img_centering(&w.px_coord, &w);
		print_usage();
		w.mlx = mlx_init();
		w.ptr = mlx_new_window(w.mlx, w.width, w.height, w.name);
		draw_obj(&w);
		mlx_key_hook(w.ptr, &get_keypressed, &w);
		mlx_loop(w.mlx);
	}
	return (0);
}
