/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:36:25 by msimao            #+#    #+#             */
/*   Updated: 2024/08/30 19:40:18 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec(t_cmd *cmd, char **envp, t_entry *entry)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * (cmd->flag_count + 1));
	if (tab == NULL)
		error_exec(cmd, entry);
	tab[0] = ft_strdup(cmd->name);
	if (tab[0] == NULL)
		error_exec(cmd, entry);
	while (cmd->flag_lst)
	{
		tab[i + 1] = ft_strdup(cmd->flag_lst->str);
		if (tab[i + 1] == NULL)
			error_exec(cmd, entry);
		cmd->flag_lst = cmd->flag_lst->next;
		i++;
	}
	tab[i + 1] = 0;
	execve(cmd->path, tab, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	child(t_entry *entry, t_pipex *pipex, char **envp, int i)
{
	pid_t 	pid;
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
		ft_close(pipex->infile);
		cmd = get_cmd_by_id(entry->cmd_lst, i);
		// printf("%s\n", entry->cmd_lst->name);
		if(1)
			builtins(cmd, entry, envp); // strncmp path builtins
		ft_exec(cmd, envp, entry);
	}
	dup2(pipex->tube[0], STDIN_FILENO);
	close(pipex->tube[1]);
	close(pipex->tube[0]);
	return (1);
}

int	parent(t_entry *entry, t_pipex *pipex, char **envp, int i)
{
	pid_t 	pid;
	t_cmd	*cmd;

	pid = fork();
	if (pid < 0)
		return (0); // bon + print
	if (pid == 0)
	{
		free(pipex->pid);
		if (pipex->outfile != 0)
		{
			dup2(pipex->outfile, STDOUT_FILENO);
			close(pipex->outfile);
		}
		close(pipex->tube[1]);
		close(pipex->tube[0]);
		cmd = get_cmd_by_id(entry->cmd_lst, i);
		if (1)
			builtins(cmd, entry, envp); // strncmp path builtins
		ft_exec(cmd, envp, entry);
	}
	ft_close(pipex->outfile);
	waitpid(pid, NULL, 0);
	return (1);
}

void	multi_cmd(t_entry *entry, t_pipex *pipex, char **envp)
{
	int		i;

	i = 0;
	pipex->pid = malloc(sizeof(pid_t) * entry->cmd_count - 1);
	if (!pipex->pid)
		return ; // bon + print
	while (i < entry->cmd_count - 1)
	{
		if (!child(entry, pipex, envp, i))
		{
			free(pipex->pid);
			return ; // bon + print
		}
		i++;
	}
	ft_close(pipex->infile);
	if (parent(entry, pipex, envp, i))
	{
		free(pipex->pid);
		return ; // bon + print
	}
	i -= 1;
	while (i >= 0)
		waitpid(pipex->pid[i--], NULL, 0);
	free(pipex->pid);
}

void	pipex(t_entry *entry, char **envp)
{
	t_pipex	pipex;

	set_file(entry, &pipex);
	if (entry->cmd_count == 1)
	{
		one_cmd(entry, &pipex, envp);
	}
	else
	{
		multi_cmd(entry, &pipex, envp);
		ft_close(pipex.tube[0]);
		ft_close(pipex.tube[1]);
	}
	free_entry(entry);
	ft_close(pipex.outfile);
	return ;
}

int main(int argc, char const *argv[], char **envp)
{
	t_entry		entry;
	t_data		data;
	t_cmd		*cmd_1;
	t_cmd		*cmd_2;
	t_flag		*cmd_1_flag_1;
	t_flag		*cmd_1_flag_2;
	t_flag		*cmd_2_flag_1;
	t_flag		*cmd_2_flag_2;

	entry.infile = 0;
	entry.outfile = 0;
	// entry.outfile = open("test2.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
	// entry.infile = open("test1.txt", O_RDWR, 0644);

	entry.cmd_count = 2;

	cmd_1 = malloc(sizeof(t_cmd));
	cmd_1->name = ft_strdup("ls");
	cmd_1->path = ft_strdup("/usr/bin/ls");
	cmd_1_flag_1 = malloc(sizeof(t_flag));
	cmd_1_flag_2 = malloc(sizeof(t_flag));
	cmd_1_flag_1->str = ft_strdup("-l");
	cmd_1_flag_1->next = cmd_1_flag_2;
	cmd_1_flag_2->str = ft_strdup("-r");
	cmd_1_flag_2->next = NULL;
	cmd_1->flag_lst = cmd_1_flag_1;

	cmd_2 = malloc(sizeof(t_cmd));
	cmd_2->name = ft_strdup("grep");
	cmd_2->path = ft_strdup("/usr/bin/grep");
	cmd_2->next = NULL;
	cmd_2_flag_1 = malloc(sizeof(t_flag));
	// cmd_2_flag_2 = malloc(sizeof(t_flag));
	cmd_2_flag_1->str = ft_strdup("2024");
	cmd_2_flag_1->next = NULL;
	// cmd_2_flag_2->str = ft_strdup("-a");
	// cmd_2_flag_2->next = NULL;
	cmd_2->flag_lst = cmd_2_flag_1;

	cmd_1->next = cmd_2;
	entry.cmd_lst = cmd_1;

	// head_flag = entry.cmd_lst->flags;

	// entry.cmd_lst->flags->str = ft_strdup("-n");
	// entry.cmd_lst->flags = entry.cmd_lst->flags->next;
	// entry.cmd_lst->flags->str = ft_strdup("lou");
	// entry.cmd_lst->flags->next = NULL;
	// entry.cmd_lst->flags = entry.cmd_lst->flags->next;
	// entry.cmd_lst->flags->str = ft_strdup("bla");
	// entry.cmd_lst->flags->next = NULL;

	// entry.cmd_lst->flags = head_flag;
	// entry.cmd_lst = entry.cmd_lst->next;

	// entry.cmd_lst->path = ft_strdup("/usr/bin/echo");
	// entry.cmd_lst->name = ft_strdup("echo");
	// entry.cmd_lst->flags = malloc(sizeof(t_flag) * 2);

	// head_flag = entry.cmd_lst->flags;

	// entry.cmd_lst->flags->str = ft_strdup("hello");
	// entry.cmd_lst->flags->next = NULL;

	// entry.cmd_lst->flags = head_flag;
	// entry.cmd_lst = head_cmd;
	// entry.cmd_lst[2].path = malloc(sizeof(char) * 13);
	// entry.cmd_lst[2].path = "/usr/bin/grep";
	// entry.cmd_lst[2].name = malloc(sizeof(char) * 4);
	// entry.cmd_lst[2].name = "grep";
	// entry.cmd_lst[2].flags = malloc(sizeof(char *) * 1);
	// entry.cmd_lst[2].flags[0] = malloc(sizeof(char) * 2);
	// entry.cmd_lst[2].flags[0] = ":2";

	pipex(&entry, envp);
	printf(GREEN ">>> SUCCESS <<<\n" RESET);
	return 0;
}


