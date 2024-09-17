/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:33:57 by sabras            #+#    #+#             */
/*   Updated: 2024/09/17 15:50:55 by sabras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "errors.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# define BUILTINS "cd echo env exit export pwd unset"

// -- Structures --
typedef struct s_data	t_data;
typedef struct s_entry	t_entry;
typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;
typedef struct s_arg	t_arg;
typedef struct s_file	t_file;
typedef struct s_parse	t_parse;
typedef struct s_pipex	t_pipex;

struct s_data
{
	char	*user;
	char	*home;
	char	*pwd;
	char	**env;
	int		stdin_fd;
	int		stdout_fd;
	int		exit_code;
	t_entry	*entry;
};

struct s_entry
{
	t_token	*token_lst;
	t_cmd	*cmd_lst;
	int		cmd_count;
	char	*prompt;
	char	*input;
};

struct s_token
{
	char	*content;
	int		type;
	int		has_quote;
	t_token	*next;
};

struct s_cmd
{
	char	*name;
	char	*path;
	t_arg	*arg_lst;
	int		arg_count;
	t_file	*file_lst;
	char	*err;
	t_cmd	*next;
};

struct s_arg
{
	char	*data;
	t_arg	*next;
};

struct s_file
{
	char	*name;
	int		redir;
	t_file	*next;
};

struct s_parse
{
	char	*input;
	char	*parsed;
	char	quote;
	int		size;
	int		i;
	int		j;
};

struct s_pipex
{
	int		saved_stdin;
	int		saved_stdout;
	int		infile;
	int		outfile;
	pid_t	*pid;
	int		here_doc;
	int		tube[2];
};

// -- Enumerations --
enum e_types
{
	WORD,
	PIPE,
	FILE_IN,
	HERE_DOC,
	FILE_OUT,
	FILE_OUT_APP
};

// --- Parsing ---
// tokenize.c
void	tokenize_input(t_data *data, char *input);

// input.c
void	*parse_input(t_data *data, t_entry *entry);

// wildcards.c
void	handle_wilcards(t_data *data, char *content);

// variables.c
char	*handle_variables(t_data *data, char *input, int heredoc);

// command.c
char	*get_cmd_name(t_data *data, char *path);
char	*get_cmd_path(t_data *data, char *name);
int		check_command(t_data *data, char *content, char **err);
int		is_builtin(t_data *data, char *content);

// prompt.c
char	*create_prompt(t_data *data);

// environment.c
void	read_env(t_data *data, char **env);
char	*ft_getenv(char *key, char **env);

// syntax.c
int		check_syntax(t_data *data, t_token *token_lst);

// metachars.c
char	toggle_quote(char c, char quote);
int		is_opt(char c);
int		is_quote(char c);
int		check_key(char c);
int		check_tilde(char c);

// --- Execution ---
void	exec_data(t_data *data);
void	one_cmd(t_data *data, t_pipex *pipex);
void	ft_exec(t_cmd *cmd, t_data *data);
int		set_file(t_file *file, t_pipex *pipex, t_data *data);
t_cmd	*get_cmd_by_id(t_cmd *cmd_lst, int id);
void	error_exec(t_data *data, char *str);
void	ft_close(int fd);
void	reset_std(t_data *data);
void	stop_process(t_data *data, t_pipex *pipex);
void	clear_fd(int fd1, int fd2);

// builtins
void	builtins(t_cmd *cmd, t_data *data, int in_fork);
void	ft_echo(t_data *data, t_cmd *cmd);
void	ft_cd(t_cmd *cmd, t_data *data);
void	ft_env(t_data *data, t_cmd *cmd);
void	ft_pwd(t_data *data);
void	ft_exit(t_cmd *cmd, t_data *data);

void	ft_export(t_cmd *cmd, t_data *data);
void	print_x(char *str, int a);
char	*copy_to(char *env, char c, char start);
int		is_var_exists(char **env, char *str);
char	**copy_tab(t_data *data);
int		check_arg(char *str);
void	set_var(t_data *data, char *path);
char	**sort_env(t_data *data);
int		is_join(char *str);

void	*ft_unset(t_cmd *cmd, t_data *data);

// --- Structs ---
// data.c
t_data	init_data(char **env);
void	clear_data(t_data *data);

// entry.c
t_entry	*init_entry(t_data *data);
void	clear_entry(t_entry *entry);

// token.c
t_token	*init_token(t_data *data, char *content, int type, int has_quote);
void	add_token(t_entry *entry, t_token *token);
int		get_token_type(char *content);
void	clear_token_lst(t_token *token_lst);

// cmd.c
t_cmd	*init_cmd(t_data *data);
void	add_cmd(t_entry *entry, t_cmd *cmd);
void	set_cmd_data(t_data *data, t_cmd *cmd, char *content);
void	clear_cmd_lst(t_cmd *cmd_lst);

// arg.c
t_arg	*init_arg(t_data *data, char *content);
void	add_arg(t_data *data, t_cmd *cmd, char *content);
void	clear_arg_lst(t_arg *arg_lst);

// file.c
t_file	*init_file(t_data *data, char *name, int redir);
void	add_file(t_data *data, t_cmd *cmd, char *content, int redir);
void	clear_file_lst(t_file *file_lst);

// parse.c
t_parse	init_parse(t_data *data, char *input);

// --- Utils ---
// signals.c
void	handle_signals(int in_process);
void	reset_signal_status(void);

// events.c
int		rl_event_handler(void);

// memory.c
char	*ft_realloc(char *s, size_t size);
void	*ft_realloc2(void *ptr, size_t original_size, size_t new_size);
char	*alloc_str(t_data *data, char *str);
void	free_split(char **tab);

// string.c
char	*strjoin_free(char *s1, char *s2, int to_free);
int		is_alpha(char *str);

// strjoin_free.c
char	*strjoin_free(char *s1, char *s2, int to_free);

// strcmp
int		ft_strcmp(char *s1, char *s2);

// error.c
void	syntax_error(t_data *data, char *token);
void	cmd_error(char *cmd, char *arg, char *err);
void	heredoc_warning(char *delimiter);
char	*get_error(t_data *data, char *content, char *err, int code);
void	throw_error(t_data *data, char *err);

#endif
