/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:58:53 by msimao            #+#    #+#             */
/*   Updated: 2024/09/23 10:21:40 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_atoll(const char *nptr)
{
	long long	nbr;
	int			sign;

	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	nbr = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + (*nptr - '0');
		nptr++;
	}
	return (nbr * sign);
}

static int	is_lower(char *str)
{
	int	len;
	int	len_max;

	len = ft_strlen(str);
	len_max = 19;
	if (str[0] == '-')
	{
		if (len < len_max + 1)
			return (1);
		if (len > len_max + 1 || ft_strcmp(str, "-9223372036854775808") > 0)
			return (0);
	}
	else
	{
		if (str[0] == '+')
			len_max += 1;
		if (len < len_max)
			return (1);
		if (len > len_max || ft_strcmp(str, "9223372036854775807") > 0)
			return (0);
	}
	return (1);
}

static void	exit_error(t_cmd *cmd, t_data *data)
{
	cmd_error(cmd->name, cmd->arg_lst->data, \
	"numeric argument required");
	data->exit_code = 2;
	clear_data(data);
	exit(2);
}

void	ft_exit(t_cmd *cmd, t_data *data)
{
	int	i;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd && cmd->arg_count >= 1)
	{
		if (!ft_isdigit(cmd->arg_lst->data[0])
			&& cmd->arg_lst->data[0] != '+' && cmd->arg_lst->data[0] != '-')
			exit_error(cmd, data);
		i = 1;
		while (ft_isdigit(cmd->arg_lst->data[i]))
			i++;
		if (cmd->arg_lst->data[i] && !ft_isdigit(cmd->arg_lst->data[i]))
			exit_error(cmd, data);
		if (!is_lower(cmd->arg_lst->data))
			exit_error(cmd, data);
		data->exit_code = ft_atoll(cmd->arg_lst->data);
	}
	if (cmd && cmd->arg_count > 1)
		return (data->exit_code = 127,
			cmd_error(cmd->name, NULL, "too many arguments"));
	clear_data(data);
	if (data->exit_code < 0)
		exit(256 + data->exit_code);
	exit(data->exit_code);
}
