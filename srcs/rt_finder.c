/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_finder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/08/12 22:48:40 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	solve_it(t_crd a, int color, t_ptr *ptr, t_ptd vec)
{
	double	det;
	t_crd	tt;

	det = a.y * a.y - 4 * a.x * a.z;
	if (det < 0.0001)
		return ;
	tt.x = (-a.y + sqrt(det)) / (2 * a.x);
	tt.y = (-a.y - sqrt(det)) / (2 * a.x);
	tt.z = (tt.x < tt.y && tt.x > 0 ? tt.x : tt.y);
	if (tt.z > 0 && (ptr->fnd->fd == 0 || (ptr->fnd->fd == 1 && tt.z <
		ptr->fnd->t)))
	{
		ptr->fnd->t = tt.z;
		ptr->fnd->color = color;
		ptr->fnd->fd = 1;
		ptr->fnd->pt = vec_add(vec.x, vec_prod(vec.y, tt.z));
	}
}

void	find_plan(t_crd o_vec, t_crd d_vec, t_obj pln, t_ptr *ptr)
{
	double	t;

	t = -((scal(pln.n, o_vec) - scal(pln.n, pln.pt)) / (scal(pln.n, d_vec)));
	if (t > 0.0001)
	{
		if (ptr->fnd->fd == 0 || (ptr->fnd->fd == 1 && t < ptr->fnd->t))
		{
			ptr->fnd->t = t;
			ptr->fnd->color = pln.color;
			ptr->fnd->fd = 1;
			ptr->fnd->pt = vec_add(o_vec, vec_prod(d_vec, t));
		}
	}
}

void	find_sphere(t_crd o_vec, t_crd d_vec, t_obj sph, t_ptr *ptr)
{
	t_crd		a;

	a.x = pow(d_vec.x, 2) + pow(d_vec.y, 2) + pow(d_vec.z, 2);
	a.y = 2 * (d_vec.x * (o_vec.x - sph.ctr.x) + d_vec.y * (o_vec.y - sph.ctr.y)
		+ d_vec.z * (o_vec.z - sph.ctr.z));
	a.z = (pow(o_vec.x - sph.ctr.x, 2) + pow(o_vec.y - sph.ctr.y, 2) +
		pow(o_vec.z - sph.ctr.z, 2)) - pow(sph.ray, 2);
	solve_it(a, sph.color, ptr, (t_ptd){o_vec, d_vec});
}

void	find_cylindre(t_crd o_vec, t_crd d_vec, t_obj cld, t_ptr *ptr)
{
	t_crd		a;
	t_crd		d;
	t_crd		tmp;
	t_crd		tmp2;

	d = vec_sub(o_vec, cld.ctr);
	tmp = vec_prod(cld.n, scal(d_vec, cld.n));
	tmp = vec_sub(d_vec, tmp);
	a.x = scal(tmp, tmp);
	tmp2 = vec_prod(cld.n, scal(d, cld.n));
	tmp2 = vec_sub(d, tmp2);
	a.y = 2 * scal(tmp, tmp2);
	a.z = scal(tmp2, tmp2) - pow(cld.ray, 2.);
	solve_it(a, cld.color, ptr, (t_ptd){o_vec, d_vec});
}

void	find_cone(t_crd o_vec, t_crd d_vec, t_obj cne, t_ptr *ptr)
{
	double		angle;
	t_crd		a;
	t_crd		d;
	t_crd		tmp;
	t_crd		tmp2;

	angle = cne.angle * (PI / 180);
	d = vec_sub(o_vec, cne.ctr);
	tmp = vec_prod(cne.n, scal(d_vec, cne.n));
	tmp = vec_sub(d_vec, tmp);
	a.x = pow(cos(angle), 2.) * scal(tmp, tmp) - pow(sin(angle), 2.) *
	pow(scal(d_vec, cne.n), 2.);
	tmp2 = vec_prod(cne.n, scal(d, cne.n));
	tmp2 = vec_sub(d, tmp2);
	a.y = 2. * pow(cos(angle), 2.) * scal(tmp, tmp2) - 2. * pow(sin(angle), 2.)
	* scal(d_vec, cne.n) * scal(d, cne.n);
	a.z = pow(cos(angle), 2.) * scal(tmp2, tmp2) - pow(sin(angle), 2.) *
	pow(scal(d, cne.n), 2.);
	solve_it(a, cne.color, ptr, (t_ptd){o_vec, d_vec});
}
