/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabras <sabras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:33:57 by sabras            #+#    #+#             */
/*   Updated: 2024/09/08 22:32:05 by sabras           ###   ########.fr       */
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
# define BUILTINS "cd echo env exit export pwd unset"

// -- Structures --
typedef struct s_data	t_data;
typedef struct s_entry	t_entry;
typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;
typedef struct s_arg	t_arg;
typedef struct s_parse	t_parse;
typedef struct s_pipex	t_pipex;

struct s_data
{
	char	*user;
	char	*home;
	char	*pwd;
	char	**env;
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
	t_token	*next;
};

struct s_cmd
{
	char	*name;
	char	*path;
	t_arg	*arg_lst;
	int		arg_count;
	int		infile;
	int		outfile;
	t_cmd	*next;
};

struct s_arg
{
	char	*data;
	t_arg	*next;
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
	pid_t	*pid;
	int		here_doc;
	int		tube[2];
};

// -- Enumerations --
enum e_redir
{
	FILE_IN = 1, // '<'
	HERE_DOC = 2, // '<<'
	FILE_OUT = 3, // '>'
	FILE_OUT_APP = 4 // '>>'
};

// --- Parsing ---
// tokenize.c
void	tokenize_input(t_data *data, char *input);

// input.c
void	parse_input(t_data *data, t_entry *entry);

// input_utils.c
char	*insert_value(t_data *data, t_parse *p);
char	*insert_home(t_data *data, t_parse *p);

// command.c
char	*get_cmd_name(t_data *data, char *path);
char	*get_cmd_path(t_data *data, char *name);
int		is_command(t_data *data, char *content);

// prompt.c
char	*create_prompt(t_data *data);

// environment.c
void	read_env(t_data *data, char **env);
char	*ft_getenv(char *key, char **env);

// syntax.c
int		check_syntax(t_token *token_lst);
int		check_redir(char *s);

// metachars.c
char	toggle_quote(char c, char quote);
int		is_opt(char c);
int		is_quote(char c);
int		is_valid_key(char c);
int		is_valid_tilde(char c);

// --- Execution ---
void	pipex(t_data *data);
void	one_cmd(t_data *data, t_pipex *pipex);
void	ft_exec(t_cmd *cmd, t_data *data);
void	set_file(t_pipex *pipex);
t_cmd	*get_cmd_by_id(t_cmd *cmd_lst, int id);
void	error_exec(t_data *data);
void	ft_close(int fd);
void	reset_std(t_pipex *pipex);

// builtins
void	builtins(t_cmd *cmd, t_data *data, int in_fork);
int		check_exit(t_data *data);
void	ft_echo(t_cmd *cmd);
void	ft_cd(t_cmd *cmd, t_data *data);
void	ft_env(t_data *data);
void	ft_pwd(t_data *data);
void	ft_exit(t_data *data);

void	ft_export(t_cmd *cmd, t_data *data);
int		is_var_exists(char **env, char *str);
char	**copy_tab(t_data *data);

void	ft_unset(t_cmd *cmd, t_data *data);

// --- Structs ---
// data.c
t_data	init_data(char **env);
void	clear_data(t_data *data);

// entry.c
t_entry	*init_entry(t_data *data);
void	clear_entry(t_entry *entry);

// token.c
void	add_token(t_data *data, t_entry *entry, char *content);
void	clear_token_lst(t_token *token_lst);

// cmd.c
t_cmd	*init_cmd(t_data *data, char *content);
void	add_cmd(t_entry *entry, t_cmd *cmd);
void	clear_cmd_lst(t_cmd *cmd_lst);

// arg.c
t_arg	*init_arg(t_data *data, char *content);
void	add_arg(t_data *data, t_cmd *cmd, char *content);
void	clear_arg_lst(t_arg *arg_lst);

// parse.c
t_parse	init_parse(t_data *data, char *input);
void	clear_parse(t_parse *parse);

// --- Utils ---
// memory.c
char	*ft_realloc(char *s, size_t size);
void	*ft_realloc2(void *ptr, size_t original_size, size_t new_size);
char	*alloc_str(t_data *data, char *str);
void	free_split(char **tab);

// strjoin_free.c
char	*strjoin_free(char *s1, char *s2, int to_free);

// strcmp
int		ft_strcmp(char *s1, char *s2);

// error.c
void	print_syntax_error(char *token);
void	print_cmd_error(char *cmd, char *err, char *arg);
void	throw_error(char *err, t_data *data);

#endif
