/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vec_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/08/15 16:58:15 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_crd		vec_cross(t_crd a, t_crd b)
{
	t_crd	c;

	c.x = a.y * b.z - b.y * a.z;
	c.y = a.z * b.x - b.z * a.x;
	c.z = a.x * b.y - b.x * a.y;
	return (c);
}

t_crd		vec_add(t_crd a, t_crd b)
{
	t_crd	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_crd		vec_sub(t_crd a, t_crd b)
{
	t_crd	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_crd		vec_prod(t_crd a, double i)
{
	t_crd	c;

	c.x = a.x * i;
	c.y = a.y * i;
	c.z = a.z * i;
	return (c);
}

t_crd		norma(t_crd a)
{
	double	dist;

	dist = do_dist(a);
	a.x = a.x / dist;
	a.y = a.y / dist;
	a.z = a.z / dist;
	return (a);
}
