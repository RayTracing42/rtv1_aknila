/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_start_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/10/04 00:13:08 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	aff_pt2(int x, int y, t_find *fnd, t_ptr *ptr, int color)
{
	// (void)fnd;

	if (fnd->fd == 0)
	{
		// if (x < 400)
			// printf("color = %x, x = %d, y = %d\n", color, x, y);
		mlx_pix_img(ptr, x, y, color);
		// fnd->color = 0x00000000;
	}
	// else
	// {
		// printf("color : %x, distance = %f, pt : x = %f, y = %f, z = %f\n", fnd->color, fnd->t, fnd->pt.x, fnd->pt.y, fnd->pt.z);
	// }
}

void	find_light(t_ptr *ptr, t_lst *lst, int x, int y, int color)
{
	t_crd	o_vec;
	t_crd	d_vec;
	// t_crd	tmp;
	t_lst	*tmp2;

	tmp2 = lst;
	while (ft_strcmp(tmp2->name, "lumiere"))
		tmp2 = tmp2->next;
	ptr->cam->pos = ptr->fnd->pt;
	o_vec = ptr->fnd->pt;
	d_vec = mkvec(o_vec, tmp2->obj->pos);
	d_vec = norma(d_vec);
	// printf("x = %f, y = %f, z = %f\n", d_vec.x, d_vec.y, d_vec.z);
	o_vec = vec_add(o_vec, vec_prod(d_vec, 0.001));
	tmp2 = lst;
	while (tmp2)
	{
		if (tmp2->find_obj)
			tmp2->find_obj(o_vec, d_vec, *tmp2->obj, ptr);
		tmp2 = tmp2->next;
	}
	aff_pt2(x, y, ptr->fnd, ptr, color);
}

void	aff_pt(int x, int y, t_find *fnd, t_ptr *ptr, t_lst *lst)
{
	(void)lst;
	if (fnd->fd == 1)
	{
		fnd->fd = 0;
		if (fnd->t < 2000000)
		{
			// fnd->t = 200000;
			// find_light(ptr, lst, x, y, fnd->color);
			mlx_pix_img(ptr, x, y, fnd->color);
		}
		fnd->t = 2000000;
		fnd->color = 0x00000000;
	}
}

void	start_find(t_ptr *ptr, int x, int y, t_lst *lst)
{
	t_crd	o_vec;
	t_crd	d_vec;
	t_crd	tmp;
	t_lst	*tmp2;	

	tmp2 = lst;
	while (tmp2)
	{
		if (!ft_strcmp(tmp2->name, "camera"))
		{
			ptr->cam->pos = tmp2->obj->pos;
			tmp = vec_add(tmp2->obj->upleft, vec_prod(tmp2->obj->idt.x, x));
			tmp = vec_sub(tmp, vec_prod(tmp2->obj->idt.y, y));
			o_vec = tmp2->obj->pos;
			d_vec = mkvec(o_vec, tmp);
			d_vec = norma(d_vec);
		}
		if (tmp2->find_obj)
			tmp2->find_obj(o_vec, d_vec, *tmp2->obj, ptr);
		tmp2 = tmp2->next;
	}
	aff_pt(x, y, ptr->fnd, ptr, lst);
}

void	start_rend(t_ptr *ptr, t_lst *lst)
{
	int		x;
	int		y;
	x = 0;
	while (x < SIZE_X)
	{
		y = 0;
		while (y < SIZE_Y)
		{
			start_find(ptr, x, y, lst); 
			y++;
		}
		x++;
	}
	// apl_filtre(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img->ptr_img, 0, 0);
}

void	check_main(t_lst *lst)
{
	t_ptr	*ptr;
	t_img	img;

	ptr = (t_ptr *)malloc(sizeof(t_ptr));
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, SIZE_X, SIZE_Y, "RT");
	img.ptr_img = mlx_new_image(ptr->mlx, SIZE_X, SIZE_Y);
	img.bts = mlx_get_data_addr(img.ptr_img, &(img.bpp),
		&(img.size_line), &(img.end));
	ptr->img = &img;
	init_env(ptr);
	start_rend(ptr, lst);
	mlx_hook(ptr->win, 17, (1L << 17), rt_close, NULL);
	mlx_hook(ptr->win, 2, 3, rt_key, &ptr);
	mlx_loop(ptr->mlx);
}

int		main(int argc, char **argv)
{
	t_lst	*lst;

	lst = NULL;
	if (argc == 2)
	{
		if (!(lst = file_extract(argv[1])))
		{
			ft_error(9);
			return (-1);
		}
		else
			check_main(lst);
	}
	else
		ft_error(1);
	return (0);
}
