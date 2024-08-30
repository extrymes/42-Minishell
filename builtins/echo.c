
#include "../includes/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	is_n;
	int	i;

	is_n = 0;
	i = 0;
	if (cmd->flag_lst->str && cmd->flag_lst->str[0] == '-'
		&& cmd->flag_lst->str[1] == 'n')
	{
		is_n = 1;
		cmd->flag_lst = cmd->flag_lst->next;
	}
	while (cmd->flag_lst)
	{
		ft_putstr_fd(cmd->flag_lst->str, STDOUT_FILENO);
		cmd->flag_lst = cmd->flag_lst->next;
		if (cmd->flag_lst)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (is_n != 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
