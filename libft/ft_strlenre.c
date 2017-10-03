/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenre.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 11:04:25 by aancel            #+#    #+#             */
/*   Updated: 2017/01/07 11:04:34 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

size_t		ft_strlenre(const char *str, const char c)
{
	int i;

	i = -1;
	while (str[++i] != c && str[i] != '\0')
		;
	return (i);
}
