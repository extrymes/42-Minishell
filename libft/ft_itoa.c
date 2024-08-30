/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:44:09 by sabras            #+#    #+#             */
/*   Updated: 2024/05/08 14:19:34 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_calcul_size(long nbr)
{
	size_t	size;

	size = 1;
	if (nbr < 0)
	{
		size++;
		nbr = -nbr;
	}
	while (nbr >= 10)
	{
		size++;
		nbr /= 10;
	}
	return (size);
}

static void	ft_fill_str(char *str, long nbr, size_t idx)
{
	if (nbr >= 10)
		ft_fill_str(str, nbr / 10, idx - 1);
	str[idx] = nbr % 10 + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	size;

	nbr = n;
	size = ft_calcul_size(nbr);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	ft_fill_str(str, nbr, size - 1);
	str[size] = '\0';
	return (str);
}
