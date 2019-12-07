/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 12:00:16 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	clean_w(t_window *w)
{
	matrix_free(&w->vertices);
	mlx_destroy_image(w->mlx, w->img.id);
	mlx_destroy_window(w->mlx, w->ptr);
}

int		get_keypressed(unsigned int keycode, t_window *w)
{
	matrix_free(&w->plan);
	matrix_free(&w->px_coord);
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		clean_w(w);
		system("leaks fdf");
		exit(0);
	}
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		vertices_rotate(w, keycode);
	if (keycode == KEY_TOP || keycode == KEY_BOTTOM)
		vertices_scale(&w->vertices, (keycode == KEY_BOTTOM) ? .75 : 1.25);
	if (!matrix_init(&w->plan, &w->vertices, sizeof(t_vertex)))
		return (0);
	if (w->proj_type == ORTHO)
		matrix_apply(&w->plan, &w->vertices, &ortho);
	else
		matrix_apply(&w->plan, &w->vertices, &perspective);
	if (!matrix_init(&w->px_coord, &w->plan, sizeof(t_pixel)))
		return (0);
	img_build(&w->px_coord, &w->plan, w);
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
	ft_strcpy(w->name, "ok boomer");
}

int		main(int ac, char **av)
{
	t_window		w;

	window_init(&w);
	if (ac == 2 && map_parse(&(w.vertices), av[1]))
	{
		if (!matrix_init(&w.plan, &(w.vertices), sizeof(t_vertex)))
			return (0);
		if (!vertices_auto_adjust_scale(&w, &w.plan))
			return (0);
		matrix_init(&w.px_coord, &w.plan, sizeof(t_pixel));
		img_build(&w.px_coord, &w.plan, &w);
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
