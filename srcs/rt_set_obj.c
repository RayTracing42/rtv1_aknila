/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_set_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/08/12 00:02:49 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	set_obj11(t_obj *obj)
{
	obj->view = norma(obj->view);
	obj->upleft = vec_add(obj->pos, vec_sub(vec_add(vec_prod(obj->view,
		obj->p_dist), vec_prod(do_vec(0, 1, 0), obj->p_height / 2.0)),
	vec_prod(do_vec(1, 0, 0), obj->p_width / 2.0)));
	obj->idt.x = vec_prod(do_vec(1, 0, 0), obj->p_width / (double)SIZE_X);
	obj->idt.y = vec_prod(do_vec(0, 1, 0), obj->p_height / (double)SIZE_Y);
}

void	set_obj1(char *name, char *str, int i, t_obj *obj)
{
	int		cp;

	cp = i;
	if (!ft_strcmp(name, "camera"))
	{
		obj->pos = (t_crd){get_next_nbr(str, &cp, 10), get_next_nbr(str,
			&cp, 10), get_next_nbr(str, &cp, 10)};
		obj->view = (t_crd){get_next_nbr(str, &cp, 10), get_next_nbr(str,
			&cp, 10), get_next_nbr(str, &cp, 10)};
		obj->p_dist = get_next_nbr(str, &cp, 10);
		obj->p_width = get_next_nbr(str, &cp, 10);
		obj->p_height = get_next_nbr(str, &cp, 10);
		set_obj11(obj);
	}
	else if (!ft_strcmp(name, "sphere"))
	{
		obj->ctr = (t_crd){get_next_nbr(str, &cp, 10), get_next_nbr(str,
			&cp, 10), get_next_nbr(str, &cp, 10)};
		obj->ray = get_next_nbr(str, &cp, 10);
		obj->color = get_next_nbr(str, &cp, 16);
	}
}

void	set_obj2(char *name, char *str, int i, t_obj *obj)
{
	int		cp;

	cp = i;
	if (!ft_strcmp(name, "plan"))
	{
		obj->pt = (t_crd){get_next_nbr(str, &cp, 10), get_next_nbr(str,
			&cp, 10), get_next_nbr(str, &cp, 10)};
		obj->n = (t_crd){get_next_nbr(str, &cp, 10), get_next_nbr(str,
			&cp, 10), get_next_nbr(str, &cp, 10)};
		obj->n = norma(obj->n);
		obj->color = get_next_nbr(str, &cp, 16);
	}
	else if (!ft_strcmp(name, "cylindre"))
	{
		obj->ctr = (t_crd){get_next_nbr(str, &cp, 10), get_next_nbr(str,
			&cp, 10), get_next_nbr(str, &cp, 10)};
		obj->n = (t_crd){get_next_nbr(str, &cp, 10), get_next_nbr(str,
			&cp, 10), get_next_nbr(str, &cp, 10)};
		obj->n = norma(obj->n);
		obj->ray = get_next_nbr(str, &cp, 10);
		obj->color = get_next_nbr(str, &cp, 16);
	}
}

void	set_obj3(char *name, char *str, int i, t_obj *obj)
{
	int		cp;

	cp = i;
	if (!ft_strcmp(name, "cone"))
	{
		obj->ctr = (t_crd){get_next_nbr(str, &cp, 10), get_next_nbr(str,
			&cp, 10), get_next_nbr(str, &cp, 10)};
		obj->n = (t_crd){get_next_nbr(str, &cp, 10), get_next_nbr(str,
			&cp, 10), get_next_nbr(str, &cp, 10)};
		obj->n = norma(obj->n);
		obj->angle = get_next_nbr(str, &cp, 10);
		obj->color = get_next_nbr(str, &cp, 16);
	}
	else if (!ft_strcmp(name, "lumiere"))
	{
		obj->pos = (t_crd){get_next_nbr(str, &cp, 10), get_next_nbr(str,
			&cp, 10), get_next_nbr(str, &cp, 10)};
		obj->its = get_next_nbr(str, &cp, 10);
		obj->color = get_next_nbr(str, &cp, 16);
	}
}

t_obj	*make_obj(char *name, char *str, int i)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (!ft_strcmp(name, "camera") || !ft_strcmp(name, "sphere"))
		set_obj1(name, str, i, obj);
	else if (!ft_strcmp(name, "plan") || !ft_strcmp(name, "cylindre"))
		set_obj2(name, str, i, obj);
	else if (!ft_strcmp(name, "cone") || !ft_strcmp(name, "lumiere"))
		set_obj3(name, str, i, obj);
	return (obj);
}
