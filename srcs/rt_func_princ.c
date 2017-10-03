/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_func_princ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/08/12 22:42:04 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		rt_close(void)
{
	exit(0);
	return (0);
}

int		rt_key(int k, t_ptr *ptr)
{
	(void)ptr;
	if (k == 53)
		rt_close();
	return (0);
}

void	init_env(t_ptr *ptr)
{
	t_cam		*cam;
	t_find		*fnd;

	cam = (t_cam *)malloc(sizeof(t_cam));
	fnd = (t_find *)malloc(sizeof(t_find));
	ptr->cam = cam;
	fnd->fd = 1;
	fnd->t = 200000;
	fnd->color = 0x00000000;
	fnd->pt = (t_crd){0, 0, 0};
	ptr->fnd = fnd;
}

int		ft_error(int i)
{
	if (i == 1)
		ft_putendl(C_ROUGE "USAGE : ./rtv1 {scene}" FIN);
	if (i == 2)
		ft_putendl(C_ROUGE "FILE ERROR" FIN);
	if (i == 3)
		ft_putendl(C_ROUGE "MEMORY ERROR" FIN);
	if (i == 4)
		ft_putendl(C_ROUGE "ONLY ONE CAMERA IN THE FILE PLEASE" FIN);
	if (i == 5)
		ft_putendl(C_ROUGE "OBJECT WITH A BAD NUMBER OF PARAMETERS" FIN);
	if (i == 6)
		ft_putendl(C_ROUGE "OBJECT WITH A BAD NAME" FIN);
	if (i == 9)
		ft_putendl(C_ROUGE "THERE ARE A ERROR BUT I DON'T KNOW WHY" FIN);
	exit(-1);
	return (-1);
}
