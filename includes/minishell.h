/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:33:57 by sabras            #+#    #+#             */
/*   Updated: 2024/08/31 11:24:40 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
// # include <sys/stat.h>
# include <fcntl.h>

// -- Structures --
typedef struct s_flag	t_flag;
typedef struct s_cmd	t_cmd;
typedef struct s_entry	t_entry;
typedef struct s_data	t_data;

struct s_flag
{
	char	*str;
	t_flag	*next;
};

struct s_cmd
{
	char	*name;
	char	*path;
	t_flag	*flag_lst;
	int		flag_count;
	t_cmd	*next;
};

struct s_entry
{
	t_cmd	*cmd_lst;
	int		cmd_count;
	char	*input;
	int		outfile;
	int		infile;
};

struct s_data
{
	char	*user;
	char	*home;
	char	*pwd;
	char	*prompt;
	char	**env;
	t_entry	entry;
};

// --- Parsing ---
// input.c
void	parse_input(t_data *data, t_entry *entry);
int		find_cmd(t_data *data, char *word);
char	*get_word(t_data *data, char *str);
char	*get_cmd_path(t_data *data, char *word);

// input_utils.c
int		count_spaces(char *str);
int		count_word_len(char *str);

// prompt.c
char	*create_prompt(t_data *data);

// env.c
void	read_env(t_data *data, char **env);
char	*ft_getenv(char *key, char **env);

// --- Execution ---
typedef struct s_pipex
{
	pid_t	*pid;
	int		outfile;
	int		infile;
	int		here_doc;
	int		tube[2];
}	t_pipex;

void	one_cmd(t_entry *entry, t_pipex *pipex, char **envp);
void	ft_exec(t_cmd *cmd, char **envp, t_entry *entry);
void	set_file(t_entry *entry, t_pipex *pipex);
t_cmd	*get_cmd_by_id(t_cmd *cmd_lst, int id);
void	free_entry(t_entry *entry);
void	error_exec(t_cmd *cmd_lst, t_entry *entry);
void	ft_close(int fd);

void	free_flag_lst(t_flag *flags);

// builtins
void	builtins(t_cmd *cmd, t_entry *entry, char **envp);
void	ft_echo(t_cmd *cmd);
void	ft_cd(t_cmd *cmd, char **envp);
void	ft_env(t_cmd *cmd, char **envp);
void	ft_pwd(t_cmd *cmd, char **envp);
void	ft_exit(t_cmd *cmd, char **envp);
void	ft_export(t_cmd *cmd, char **envp);
void	ft_unset(t_cmd *cmd, char **envp);

// --- Utils ---
// data.c
t_data	init_data(char **env);
void	clear_data(t_data *data);

// entry.c
t_entry	init_entry(void);
void	clear_entry(t_entry *entry);

// cmd.c
t_cmd	*init_cmd(char *name, char *path, t_data *data);
void	add_cmd(t_entry *entry, t_cmd *cmd);
void	clear_cmd_lst(t_cmd *cmd_lst);

// flag.c
t_flag	*init_flag(char *str, t_data *data);
void	clear_flag_lst(t_flag *flag_lst);

// realloc.c
char	*ft_realloc(char *s, size_t size, t_data *data);

// strjoin_free.c
char	*strjoin_free(char *s1, char *s2, int to_free);

// error.c
void	throw_error(char *error, t_data *data);

#endif
