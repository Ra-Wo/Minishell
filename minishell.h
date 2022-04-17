/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:19:02 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/15 12:21:15 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "./utils/execution/GetNextLine/get_next_line.h"

typedef struct s_vars {
	char		*input;
	int			fd[2];
	int			last_fd_pipe;
	int			i;
	t_parm_lst	*lst;
}	t_vars;

typedef struct s_env
{
	char			*title;
	char			*data;
	struct s_env	*next;
}	t_env;

typedef struct s_vars_execute_cmd {
	char	*path;
	int		pid;
}	t_exec_vars;

typedef struct s_replace_dollar {
	char	*before;
	char	*after;
	char	*data;
	char	*new;
	char	*backup;
}	t_replace_dollar;
typedef struct s_vars_glo {
	int		pid;
	t_env	*env;
	int		exit_status;
	int		input_has_redirect;
	int		output_has_redirect;
	int		old_fd[2];
}	t_vars_glo;

t_vars_glo	g_vars;

/* Functions */
void			reading_input(t_vars *vars);
int				arr_len(char **arr);
void			arr_free(char **arr);
void			free_parms(t_parm_lst **lst);
t_parm_lst		*check_redirections(char **parms);
char			**custom_split(char const *s, char c);
int				is_all_redirection(char *parm);
int				all_redirections_len(char **parms);
int				check_quotes(char *str);
void			cpy(char *dst, char const *src, int n);
char			**quote_split(char const *s, char c);
void			check_overwrite(char ***content);
void			print_arr(char **cpy);
int				check_exit(t_vars *vars);
char			*redirection1(char *parm, int *i, char *backup,
					char *before_after[3]);
char			**delete_line(char **str, int where);
void			fix_redirection(char **parm);
int				replace_all_dollar_sign(t_vars *vars);

// execution 
void			create_env(char **env);
void			free_env(void);
int				exec(t_parm_lst *lst, t_vars *vars);
int				execute_cmd(t_parm_lst *cmd, t_vars *vars);
int				redirect_input(t_parm_lst *cmd);
int				redirect_output(t_parm_lst *cmd);
char			*get_path_cmd(char *cmd);
char			*ft_pathjoin(char const *s1, char const *s2);
int				handle_redirection(t_parm_lst *cmd);
void			handle_out_in_of_pipe(t_vars *vars, t_parm_lst *cmd);
int				compare(char *str1, char *str2);

int				check_builtins(t_parm_lst *cmd, t_vars *vars);
void			echo(t_parm_lst *cmd);
int				cd(t_parm_lst *cmd);
void			pwd(t_parm_lst *cmd);
void			env(void);
int				export(t_parm_lst *cmd, t_vars *vars);
void			unset(t_parm_lst *cmd);
char			**env_struct_to_array(void);
int				check_heredoc(t_parm_lst *cmd);
int				run_heredoc(t_parm_lst *cmd, int *i);
char			**insert_line(char **str, char *str_to_insert, int where);
void			check_exit_status_var(int status);
void			add_path_to_env(char *str);
void			f_exit(t_parm_lst *cmd, t_vars *vars, char *path);
void			f_free(t_parm_lst *cmd, t_vars *vars, char *path);
void			print_export(void);
void			ctrl_c(int s);
void			ctrl_c_when_cmd_is_running(int s);
void			ctrl_backslash(int s);
int				get_data_from_a_file(t_parm_lst *cmd, int *i);
char			*env_get_title(char *line);
char			*env_get_data(char *line);
t_env			*create_new_env_element(char *title, char *data);
char			*replace_dollar_sign(char *str);
void			add_to_env(char *title, char *data);
int				check_builtins_from_child(t_parm_lst *cmd, t_vars *vars);
int				exit_the_program(t_parm_lst *cmd, t_vars *vars);
void			free_replace_dollar(t_replace_dollar *replace, int free_backup);

#endif