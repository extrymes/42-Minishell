/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:13:38 by sabras            #+#    #+#             */
/*   Updated: 2024/05/22 11:43:53 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	if ((!dst || !src) && siz == 0)
		return (0);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	if (siz <= dstlen || siz == 0)
		return (srclen + siz);
	while (src[i] && i < (siz - dstlen - 1))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
