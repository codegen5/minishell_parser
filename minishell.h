/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:19:21 by tbalci            #+#    #+#             */
/*   Updated: 2024/04/24 20:18:26 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h> 
# include <unistd.h>
# include "./libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <termios.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <signal.h>

typedef enum e_tokens
{
	PIPE = 1,
	RED_OUT,
	APPEND,
	RED_IN,
	HEREDOC
}		t_tokens;

typedef struct s_proc
{
	int		fd[2];
	pid_t	pid;
}		t_proc;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				is_quote;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}		t_lexer;

typedef struct s_global
{
	t_lexer					*head;
	struct s_simple_cmds	*p_head;
	char					**env;
	char					**export;
}		t_global;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_global *, struct s_simple_cmds *);
	int						num_redirections;
	int						in_her;
	char					*hd_file_name;
	t_proc					prcs;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}		t_simple_cmds;

typedef struct s_globals
{
	int		a;
	int		error_num;
	int		in_her;
	int		in_red;
	int		test1;
	int		out_red;
	int		test2;
	char	**env;
}		t_globals;

t_globals	g_global;

char	**ft_setenv(char **ev);
void	minishell_loop(char *line,	t_global *mini);
void	ft_init_lexer(t_global *mini, char *line);
int		ft_quote(char *line);

#endif