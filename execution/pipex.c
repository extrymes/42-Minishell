/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:36:25 by msimao            #+#    #+#             */
/*   Updated: 2024/09/06 13:37:28 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec(t_cmd *cmd, t_data *data)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * (cmd->arg_count + 2));
	if (tab == NULL)
		error_exec(data);
	tab[0] = ft_strdup(cmd->name);
	if (tab[0] == NULL)
		error_exec(data);
	while (cmd->arg_count != 0 && cmd->arg_lst)
	{
		tab[i + 1] = ft_strdup(cmd->arg_lst->data);
		if (tab[i + 1] == NULL)
			error_exec(data);
		cmd->arg_lst = cmd->arg_lst->next;
		i++;
	}
	tab[i + 1] = 0;
	execve(cmd->path, tab, data->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	child(t_data *data, t_pipex *pipex, int i)
{
	t_cmd	*cmd;

	if (pipe(pipex->tube) < 0)
		return (0); // bon + print
	pipex->pid[i] = fork();
	if (pipex->pid[i] < 0)
		return (0); // bon + print
	if (pipex->pid[i] == 0)
	{
		free(pipex->pid);
		dup2(pipex->tube[1], STDOUT_FILENO);
		close(pipex->tube[1]);
		close(pipex->tube[0]);
		// ft_close(pipex->infile);
		cmd = get_cmd_by_id(data->entry->cmd_lst, i);
		if (cmd->path == NULL)
			builtins(cmd, data, 1); // strncmp path builtins
		ft_exec(cmd, data);
	}
	dup2(pipex->tube[0], STDIN_FILENO);
	close(pipex->tube[1]);
	close(pipex->tube[0]);
	return (1);
}

int	parent(t_data *data, t_pipex *pipex, int i)
{
	pid_t	pid;
	t_cmd	*cmd;

	pid = fork();
	if (pid < 0)
		return (0); // bon + print
	if (pid == 0)
	{
		free(pipex->pid);
		// if (pipex->outfile != 0)
		// {
		// 	dup2(pipex->outfile, STDOUT_FILENO);
		// 	close(pipex->outfile);
		// }
		close(pipex->tube[1]);
		close(pipex->tube[0]);
		cmd = get_cmd_by_id(data->entry->cmd_lst, i);
		if (cmd->path == NULL)
			builtins(cmd, data, 1); // strncmp path builtins
		ft_exec(cmd, data);
	}
	reset_std(pipex);
	return (waitpid(pid, NULL, 0), 1);
}

void	multi_cmd(t_data *data, t_pipex *pipex)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->entry->cmd_count - 1)
	{
		if (!child(data, pipex, i))
		{
			free(pipex->pid);
			return ;// bon + print
		}
		i++;
	}
	// ft_close(pipex->infile);
	if (!parent(data, pipex, i))
	{
		free(pipex->pid);
		return ;// bon + print
	}
	i -= 1;
	j = 0;
	while (j < i)
		waitpid(pipex->pid[j++], NULL, 0);
	free(pipex->pid);
}

void	pipex(t_data *data)
{
	t_pipex	pipex;

	if (data->entry->cmd_count == 0)
		return ;
	if (data->entry->cmd_count == 1)
		one_cmd(data, &pipex);
	else
	{
		set_file(&pipex);
		pipex.pid = malloc(sizeof(pid_t) * data->entry->cmd_count - 1);
		if (!pipex.pid)
			return ; // bon + print
		multi_cmd(data, &pipex);
		ft_close(pipex.tube[0]);
		ft_close(pipex.tube[1]);
	}
	// ft_close(pipex.outfile);
	return ;
}

// static void	print_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		ft_putstr_fd(envp[i++], STDOUT_FILENO);
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 	}
// 	return ;
// }

// t_cmd	*init_cmd2(char *name, char *path)
// {
// 	t_cmd	*cmd;

// 	cmd = malloc(sizeof(t_cmd));
// 	cmd->name = name;
// 	cmd->path = path;
// 	cmd->arg_lst = NULL;
// 	cmd->arg_count = 0;
// 	cmd->infile = 0;
// 	cmd->outfile = 0;
// 	cmd->next = NULL;
// 	return (cmd);
// }

// t_arg	*init_arg2(char *data)
// {
// 	t_arg	*arg;

// 	arg = malloc(sizeof(t_arg));
// 	arg->data = data;
// 	arg->next = NULL;
// 	return (arg);
// }

// int main(int argc, char const *argv[], char **envp)
// {
// 	t_data		data;
// 	t_cmd		*cmd_1;
// 	t_cmd		*cmd_2;
// 	int			i;
// 	int			j;

// 	i = 0;
// 	while(envp[i])
// 		i++;
// 	data.env = malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while(envp[i])
// 	{
// 		data.env[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	data.env[i] = 0;
// 	data.entry = malloc(sizeof(t_entry));
// 	data.entry->input = NULL;
// 	// data.entry->outfile = open("test2.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
// 	// data.entry->infile = open("test2.txt", O_RDWR, 0644);

// 	data.entry->cmd_count = 1;
// 	cmd_1 = init_cmd2(ft_strdup("unset"), NULL);
// 	cmd_1->arg_count = 1;
// 	cmd_1->arg_lst = init_arg2(ft_strdup("PWD"));
// 	// cmd_1->arg_lst->next = init_arg2(ft_strdup("Hello World"));
// 	data.entry->cmd_lst = cmd_1;
// 	// printf("%s\n", data.entry->cmd_lst->name);
// 	// printf("%s\n", data.entry->cmd_lst->arg_lst->data);

// 	pipex(&data);
// 	// print_env(data.env);
// 	// printf(GREEN ">>> SUCCESS <<<\n" RESET);
// 	clear_data(&data);
// 	return 0;
// }
