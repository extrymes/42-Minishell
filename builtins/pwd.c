/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:46:46 by msimao            #+#    #+#             */
/*   Updated: 2024/09/11 13:32:02 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_data *data)
{
	ft_putstr_fd(data->pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	data->exit_code = 0;
}
