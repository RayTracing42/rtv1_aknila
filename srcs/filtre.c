/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 02:49:45 by aancel            #+#    #+#             */
/*   Updated: 2017/08/23 13:12:06 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int **tabncpy(int **m, int x, int y, int n)
{
	int **tab;
	int a;
	int b;

	tab = (int **)malloc(sizeof(int *) * n);
	a = 0;
	while (a < n)
	{
		tab[a] = (int *)malloc(sizeof(int) * n);
		b = 0;
		while (b < n)
		{
			tab[a][b] = m[y + a][x + b];
			b++;
		}
		a++;
	}
	return (tab);
}

int matr_prod(int **m1, int **m2)
{
	int m3[3][3];
	int a;
	int b;
	int tmp;

	a = 0;
	while (a < 3)
	{
		b = 0;
		while (b < 3)
		{
			m3[a][b] = m1[a][0] * m2[0][b] + m1[a][1] * m2[1][b] + m1[a][2] * m2[2][b];
			b++;
		}
		a++;
	}
	tmp = 0;
	a = 0;
	while (a < 3)
	{
		b = 0;
		while (b < 3)
		{
			tmp += m3[a][b];
			b++;
		}
		a++;
	}


	// m3[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0];
	// m3[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1];
	// m3[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2];
	// m3[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0];
	// m3[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1];
	// m3[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2];
	// m3[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0];
	// m3[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1];
	// m3[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2];
	// return (m3[0][0] + m3[0][1] + m3[0][2] + m3[1][0] + m3[1][1] + m3[1][2] + m3[2][0] + m3[2][1] + m3[2][2]);
	return (tmp);
}

int		**mkmatrice(void)
{
	int **dest;
	int i;

	if (!(dest = (int **)malloc(sizeof(int *) * 3)))
		exit (-1);
	i = 0;
	while (i < 3)
	{
		if (!(dest[i] = (int *)malloc(sizeof(int) * 3)))
			exit (-1);
		i++;
	}
	dest[0][0] = 0;
	dest[0][1] = 0;
	dest[0][2] = 0;
	dest[1][0] = 0;
	dest[1][1] = 1;
	dest[1][2] = 0;
	dest[2][0] = 0;
	dest[2][1] = 0;
	dest[2][2] = 0;
	return (dest);
}

void	apl_filtre(t_ptr *ptr)
{
	t_img	flt;
	t_img	flt2;
	int 	**mat;
	int		tmp;
	t_pti	a;
	t_pti	b;
	int		color;

	flt.ptr_img = mlx_new_image(ptr->mlx, SIZE_X, SIZE_Y);
	flt.bts = mlx_get_data_addr(flt.ptr_img, &(flt.bpp),
		&(flt.size_line), &(flt.end));
	flt2.ptr_img = mlx_new_image(ptr->mlx, SIZE_X, SIZE_Y);
	flt2.bts = mlx_get_data_addr(flt2.ptr_img, &(flt2.bpp),
		&(flt2.size_line), &(flt2.end));
	mat = NULL;
	mat = mkmatrice();
	ft_putendl("on rentre");
	color = 0;
	while (color < 3)
	{	
		a.y = 0;
		while (a.y < SIZE_Y)
		{
			a.x = 0;
			while (a.x < SIZE_X)
			{
				if (a.x != 0 && a.y != 0 && a.x != (SIZE_X - 1) && a.y != (SIZE_Y - 1))
				{
					tmp = 0;
					b.y = -1;
					while (b.y <= 1)
					{
						b.x = -1;
						while (b.x <= 1)
						{
							tmp += mat[1 + b.y][1 + b.x] * ptr->img->bts[((a.y + b.y) * ptr->img->size_line) + ((ptr->img->bpp / 8) * (a.x + b.x)) + color];
							b.x++;
						}
						b.y++;
					}



					tmp = 0;
					











					tmp /= 9;
					tmp = (tmp > 255 ? 255 : tmp);
					tmp = (tmp < 0 ? 0 : tmp);
					flt.bts[(a.y * flt.size_line) +
						((flt.bpp / 8) * a.x) + color] = tmp / 9;
				}
				else
				{
					flt.bts[(a.y * flt.size_line) +
						((flt.bpp / 8) * a.x) + color] =
						ptr->img->bts[(a.y * ptr->img->size_line) +
						((ptr->img->bpp / 8) * a.x) + color];
				}
				a.x++;
			}
			a.y++;
		}
		color++;
	}
	// color = 0;
	// while (color < 3)
	// {	
	// 	a.y = 0;
	// 	while (a.y < SIZE_Y)
	// 	{
	// 		a.x = 0;
	// 		while (a.x < SIZE_X)
	// 		{
	// 			if (a.x != 0 && a.y != 0 && a.x != (SIZE_X - 1) && a.y != (SIZE_Y - 1))
	// 			{
	// 				tmp = 0;
	// 				b.y = -1;
	// 				while (b.y <= 1)
	// 				{
	// 					b.x = -1;
	// 					while (b.x <= 1)
	// 					{
	// 						tmp += mat[1 + b.y][1 + b.x] * flt.bts[((a.y + b.y) * flt.size_line) + ((flt.bpp / 8) * (a.x + b.x)) + color];
	// 						b.x++;
	// 					}
	// 					b.y++;
	// 				}
	// 				flt2.bts[(a.y * flt2.size_line) +
	// 					((flt2.bpp / 8) * a.x) + color] = tmp / 9;
	// 			}
	// 			else
	// 			{
	// 				flt2.bts[(a.y * flt2.size_line) +
	// 					((flt2.bpp / 8) * a.x) + color] =
	// 					flt.bts[(a.y * flt.size_line) +
	// 					((flt.bpp / 8) * a.x) + color];
	// 			}
	// 			a.x++;
	// 		}
	// 		a.y++;
	// 	}
	// 	color++;
	// }
	// mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img->ptr_img, 0, 0);
	mlx_put_image_to_window(ptr->mlx, ptr->win, flt.ptr_img, 0, 0);
}

void	aff_image_filtre(int x, int y, t_ptr *ptr)
{
	if (1)
	{
		apl_filtre(ptr);
	}
	else
	{
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img->ptr_img, x, y);
	}
}

/*

Image en void* = liste de nombre en int*

Donc : une image comme represente le tab1 est pareil que le tab2

tab1 :	1 2 3
		4 5 6
		7 8 9

tab2 :	1 2 3 4 5 6 7 8 9

tab1[2][2] = tab2[8]
tab1 est defini par tab1[SIZE_Y][SIZE_X]
donc tab1[y][x] = tab2[y * SIZE_Y + x] avec 0 <= x < SIZE_X et 0 <= y < SIZE_Y
donc on peut faire une boucle qui ressemble a :

y = 0;
while (y < SIZE_Y)
{
	x = 0;
	while (x < SIZE_X)
	{
		dest[y * SIZE_Y + x] = ...
		x++;
	}
	y++;
}

pour appliquer le filtre, on multiplie par une matrice : 	| a b c |
															| d e f |
															| g h i |

donc si x > 0 et y > 0 :	 dest[y * SIZE_Y + x] = a * tab1[y - 1][x - 1] + b * tab1[y - 1][x] + c * tab1[y - 1][x + 1] +
													d *   tab1[y][x - 1]   + e *   tab1[y][x]   + f *   tab1[y][x + 1]   +
													g * tab1[y + 1][x - 1] + h * tab1[y + 1][x] + i * tab1[y + 1][x + 1]

									tab1[x][y] est au milieu car on applique la matrice sur ce pixel par rapport a ceux autour

la matrice etant un tableau du style matrice[y1][x1] en dimension 3x3 avec -1 <= y1 <= 1 et -1 <= x1 <= 1

donc on peut faire une boucle pour avoir une case de la matrice a chaque fois en fonction de x1 et y1 de la sorte :

y1 = -1;
while (y1 <= 1)
{
	x1 = -1;
	while (x1 <= 1)
	{
		matrice[1 + y1][1 + x1];     <-- valeur qui ira de 'a' jusque 'i';
		x1++;
	}
	y1++;
}

pour eviter des lignes interminables et incomprehensibles, en passsant par un tmp pour stocker le resultat de
chaque factorisation, on obtient :

tmp = 0;
y1 = -1;
while (y1 <= 1)
{
	x1 = -1;
	while (x1 <= 1)
	{
		tmp += matrice[1 + y1][1 + x1] * ...;
		x1++;
	}
	y1++;
}

en remplaçant '...' par la valeur de tab1 en fonction de x1 et y1 on arrive a :

tmp = 0;
y1 = -1;
while (y1 <= 1)
{
	x1 = -1;
	while (x1 <= 1)
	{
		tmp += matrice[1 + y1][1 + x1] * tab1[y + y1][x + x1];  ou  matrice[1 + y1][1 + x1] * tab2[(y + y1) * SIZE_Y + (x + x1)]
		x1++;
	}
	y1++;
}

et a la fin on inject tmp dans dest[y * SIZE_Y + x]

~~~~ pour rappel dest et tab2 ont tous deux la meme taille ~~~~


*/
