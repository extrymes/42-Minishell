/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:23:54 by msimao            #+#    #+#             */
/*   Updated: 2024/08/30 15:00:32 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtins(t_cmd *cmd, t_entry *entry, char **envp)
{
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		ft_echo(cmd); //fais a modif
	if (ft_strncmp(cmd->name, "pwd" , 3) == 0)
		ft_pwd(cmd, envp); //fais a modif
	if (ft_strncmp(cmd->name, "env", 3) == 0)
		ft_env(cmd, envp); //fais a modif
	if (ft_strncmp(cmd->name, "cd", 2) == 0)
		ft_cd(cmd, envp);//pas fais
	if (ft_strncmp(cmd->name, "exit", 3) == 0)
		ft_exit(cmd, envp); //pas fais
	if (ft_strncmp(cmd->name, "export", 6) == 0)
		ft_export(cmd, envp); //pas fais
	if (ft_strncmp(cmd->name, "unset", 5) == 0)
		ft_unset(cmd, envp); //pas fais
	else
		return ;
	free_entry(entry);
	exit(EXIT_SUCCESS);
}
