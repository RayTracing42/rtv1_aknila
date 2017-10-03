/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/08/23 13:10:45 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../minilibx_macos/mlx.h"
# include "color.h"
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define ABS(x) ((x) < 0 ? -(x) : (x))
# define SIZE_X 1500
# define SIZE_Y 950
# define PI M_PI
# define RAD(x) PI * x / 180

typedef struct	s_pti
{
	int			x;
	int			y;
}				t_pti;

typedef	struct	s_crd
{
	double		x;
	double		y;
	double		z;
}				t_crd;

typedef struct	s_find
{
	int			fd;
	double		t;
	int			color;
	t_crd		pt;
}				t_find;

typedef struct	s_ptc
{
	t_crd		x;
	t_crd		y;
}				t_ptd;

typedef	struct	s_cam
{
	t_crd		pos;
	t_crd		view;
	t_crd		upleft;
	t_ptd		idt;
	double		fov;
	double		p_height;
	double		p_width;
	double		p_dist;
}				t_cam;

typedef struct	s_lgt
{
	t_crd		pos;
	double		its;
	int			color;
}				t_lgt;

typedef struct	s_obj
{
	t_crd		pos;
	t_crd		ctr;
	t_crd		pt;
	t_crd		n;
	t_crd		view;
	t_crd		upleft;
	t_ptd		idt;
	int			ray;
	double		angle;
	double		its;
	double		fov;
	double		p_height;
	double		p_width;
	double		p_dist;
	int			color;
}				t_obj;

typedef struct	s_img
{
	void		*ptr_img;
	char		*bts;
	int			size_line;
	int			bpp;
	int			end;
}				t_img;

typedef struct	s_ptr
{
	void		*mlx;
	void		*win;
	t_cam		*cam;
	t_img		*img;
	t_find		*fnd;
}				t_ptr;

typedef struct	s_lst
{
	char			*name;
	t_obj			*obj;
	void			(*find_obj)(t_crd, t_crd, t_obj, t_ptr *);
	struct s_lst	*next;
	struct s_lst	*prev;
}				t_lst;

int				rt_close(void);
int				rt_key(int k, t_ptr *ptr);
void			mlx_pix_img(t_ptr *ptr, int x, int y, int color);
double			scal(t_crd a, t_crd b);
double			scal_sqrd(t_crd a);
t_crd			vec_add(t_crd a, t_crd b);
t_crd			vec_sub(t_crd a, t_crd b);
t_crd			vec_prod(t_crd a, double i);
t_crd			mkvec(t_crd a, t_crd b);
t_crd			do_vec(double x, double y, double z);
t_crd			vec_cross(t_crd a, t_crd b);
double			do_dist_sqrd(t_crd a, t_crd b);
double			do_dist(t_crd a);
t_crd			norma(t_crd a);
void			init_env(t_ptr *ptr);
void			find_plan(t_crd o_vec, t_crd d_vec, t_obj pln, t_ptr *ptr);
void			solve_it(t_crd a, int color, t_ptr *ptr, t_ptd vec);
void			find_sphere(t_crd o_vec, t_crd d_vec, t_obj sph, t_ptr *ptr);
void			find_cylindre(t_crd o_vec, t_crd d_vec, t_obj cld, t_ptr *ptr);
void			find_cone(t_crd o_vec, t_crd d_vec, t_obj cne, t_ptr *ptr);
void			aff_pt(int x, int y, t_find *fnd, t_ptr *ptr, t_lst *lst);
void			start_rend(t_ptr *ptr, t_lst *lst);
void			check_main(t_lst *lst);
int				ft_atoi_base(char *str, int base);
int				ft_error(int i);
int				issp(char c);
int				ft_count_s(char *str);
int				check_buf3(char *str, char *name);
int				check_buf2(char *str);
int				check_buf(char *str);
int				get_next_nbr(char *str, int *i, int base);
void			set_obj11(t_obj *obj);
void			set_obj1(char *name, char *str, int i, t_obj *obj);
void			set_obj2(char *name, char *str, int i, t_obj *obj);
void			set_obj3(char *name, char *str, int i, t_obj *obj);
t_obj			*make_obj(char *name, char *str, int i);
t_lst			*lst_join(t_lst	*lst, t_lst *nw);
t_lst			*make_list(char *buf);
t_lst			*file_extract(char *filename);
int				main(int argc, char **argv);
int				range_change_color(int color, int range);
void			apl_filtre(t_ptr *ptr);

#endif
