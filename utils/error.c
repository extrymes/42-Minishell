/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:33:32 by sabras            #+#    #+#             */
/*   Updated: 2024/08/26 13:40:57 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *error)
{
	ft_putstr_fd(RED "error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n" RESET, 2);
}
