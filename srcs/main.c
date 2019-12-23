/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/08 23:15:34 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	clean_w_and_exit(t_window *w)
{
	matrix_free(&w->obj_vertices);
	mlx_destroy_image(w->mlx, w->img.id);
	mlx_destroy_window(w->mlx, w->ptr);
	exit(0);
}

void	vertex_remove_null(t_matrix *vertices)
{
	t_vertex	min;

	min.x = matrix_get(vertices, FT_INTMAX, X, &get_min);
	min.y = matrix_get(vertices, FT_INTMAX, Y, &get_min);
	min.z = matrix_get(vertices, FT_INTMAX, Z, &get_min);
	min.x *= 2;
	min.y *= 2;
	min.z *= 2;
	if (min.x == 0)
		min.x = 1;
	if (min.y == 0)
		min.y = 1;
	if (min.z == 0)
		min.z = 1;
	if (min.x < 0)
		min.x *= -1;
	if (min.y < 0)
		min.y *= -1;
	if (min.z < 0)
		min.z *= -1;
	matrix_set(vertices, &min, &vertex_increment);
}

/*
** to search leaks, put before the exit = system("leaks fdf");
*/

int		get_keypressed(unsigned int keycode, t_window *w)
{
//	matrix_free(&w->proj_plan);
//	matrix_free(&w->px_coord);
	if (keycode == KEY_ESC || keycode == KEY_Q)
		clean_w_and_exit(w);
	if (keycode == KEY_PERSP)
		w->proj_type = PERSP;
	if (keycode == KEY_ORTHO)
		w->proj_type = ORTHO;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		if (!vertices_rotate(&w->obj_vertices, &angle_y, keycode == KEY_LEFT ? -25.0 : 25.0))
			return (0);
	if (keycode == KEY_TOP || keycode == KEY_BOTTOM)
		if (!vertices_scale(&w->obj_vertices, (keycode == KEY_BOTTOM) ? .75 : 1.25))
			return (0);
	matrix_cpy(&w->camera, &w->obj_vertices);
//	if (!matrix_init(&w->plan, &w->vertices, sizeof(t_vertex)))
//		return (0);
	if (w->proj_type == ORTHO)
		matrix_apply(&w->proj_plan, &w->camera, &ortho);
	else
	{
		vertices_rotate(&w->camera, &angle_x, 24.5);		// angle x buggy but ok
		if (keycode == KEY_PLUS)
			w->angle += 1;
		if (keycode == KEY_MINUS)
			w->angle -= 1;
		vertex_remove_null(&w->camera);
//		vertices_rotate(&w->camera, &angle_y, w->angle * 25.0);		// ange y buggy but ok
//		vertices_rotate(&w->camera, &angle_z, w->angle * 25.0);		// => angle z ok
			matrix_apply(&w->proj_plan, &w->camera, &perspective);
//		if (keycode == KEY_PERSP)
		//	vertices_auto_adjust_scale(w, &w->proj_plan);
	}

	if (!matrix_init(&w->px_coord, &w->proj_plan, sizeof(t_pixel)))
		return (0);
//	img_setcolors(&w->px_coord, &w->obj_vertices, w);
	img_setcolors(&w->px_coord, &w->obj_vertices);
	img_setalpha(&w->px_coord, &w->camera);
	img_setpositions(&w->px_coord, &w->proj_plan, w);
	img_centering(&w->px_coord, w);
//	if (w->proj_type == PERSP)
//		img_scaling(&w->px_coord, &w->proj_plan, w);
//	if (!ft_ischarset(keycode + 1, KEYS_TRANSLATION))
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
	w->proj_type = ORTHO;
	ft_strcpy(w->name, "ok boomer");
}

int		main(int ac, char **av)
{
	t_window		w;

	window_init(&w);
	if (ac == 2)
	{
		if (!map_parse(&(w.obj_vertices), av[1]))
			return (0);
		if (!matrix_init(&w.proj_plan, &w.obj_vertices, sizeof(t_vertex))
			|| !w.obj_vertices.row_len)
			return (0);
		if (!matrix_init(&w.px_coord, &w.obj_vertices, sizeof(t_pixel)))
			return (0);
		if (!matrix_init(&w.camera, &w.obj_vertices, sizeof(t_pixel)))
			return (0);
		matrix_cpy(&w.camera, &w.obj_vertices);
		matrix_apply(&w.proj_plan, &w.camera, &ortho);
		if (!vertices_auto_adjust_scale(&w, &w.proj_plan))
			return (0);
		img_setcolors(&w.px_coord, &w.obj_vertices);
		img_setalpha(&w.px_coord, &w.camera);
		img_setpositions(&w.px_coord, &w.proj_plan, &w);
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
