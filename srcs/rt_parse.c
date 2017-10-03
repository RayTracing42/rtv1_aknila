/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/08/12 00:03:40 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_lst	*lst_join(t_lst *lst, t_lst *nw)
{
	t_lst	*tmp;

	tmp = NULL;
	if (lst == NULL)
		lst = nw;
	else
	{
		tmp = lst;
		while (tmp && tmp->next)
			tmp = tmp->next;
		nw->prev = tmp;
		tmp->next = nw;
	}
	return (lst);
}

t_lst	*make_list(char *buf)
{
	t_lst	*lst;
	int		i;

	i = 0;
	if (!(lst = (t_lst *)malloc(sizeof(t_lst))))
		ft_error(3);
	while (!issp(buf[i]))
		i++;
	lst->name = ft_strsub(buf, 0, i);
	lst->obj = make_obj(lst->name, buf, i);
	if (!ft_strcmp(lst->name, "plan"))
		lst->find_obj = find_plan;
	else if (!ft_strcmp(lst->name, "sphere"))
		lst->find_obj = find_sphere;
	else if (!ft_strcmp(lst->name, "cylindre"))
		lst->find_obj = find_cylindre;
	else if (!ft_strcmp(lst->name, "cone"))
		lst->find_obj = find_cone;
	else
		lst->find_obj = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

int		val_fd(char *filename, char **buf)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (!(*buf = (char *)malloc(sizeof(char))))
		ft_error(3);
	if (read(fd, *buf, 1) == -1)
		ft_error(2);
	close(fd);
	free(*buf);
	fd = open(filename, O_RDONLY);
	return (fd);
}

t_lst	*file_extract(char *filename)
{
	int		fd;
	char	*buf;
	int		ret;
	t_lst	*lst;
	t_lst	*tmp;

	lst = NULL;
	fd = val_fd(filename, &buf);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &buf);
		if (ret == 0)
			break ;
		if (buf[0] == '\0')
			ft_error(2);
		if (check_buf(buf) == -1)
			ft_error(2);
		tmp = NULL;
		tmp = make_list(buf);
		free(buf);
		lst = lst_join(lst, tmp);
	}
	return (lst);
}
