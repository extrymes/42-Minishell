/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:31:42 by sabras            #+#    #+#             */
/*   Updated: 2024/08/30 11:51:43 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_str;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_str = ft_lstnew(lst->content);
		if (!new_str)
			return (ft_lstclear(&new_list, del), NULL);
		new_str->content = f(new_str->content);
		ft_lstadd_back(&new_list, new_str);
		lst = lst->next;
	}
	return (new_list);
}
