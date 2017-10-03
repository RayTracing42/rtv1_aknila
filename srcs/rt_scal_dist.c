/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scal_dist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/08/12 00:03:01 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double	scal(t_crd a, t_crd b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	scal_sqrd(t_crd a)
{
	return (scal(a, a));
}

double	do_dist_sqrd(t_crd a, t_crd b)
{
	return (pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

double	do_dist(t_crd a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}
