/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:59:29 by msamilog          #+#    #+#             */
/*   Updated: 2024/05/10 16:57:34 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(char *line,	t_global *mini)
{
	while (1)
	{
		g_global.test1 = 0;
		g_global.a = 0;
		g_global.test2 = 0;
		line = readline("minishell$ ");
		if (line == NULL)
			exit(1);
		if (line[0])
			add_history(line);
		ft_init_lexer(mini, line);
		if (ft_check_error(mini))
		{
			ft_deallocate_lexer(mini);
			free(line);
			continue ;
		}
		// ft_expand(mini);
		ft_init_parser(mini);
		// ft_executer(mini);
		ft_deallocate_all(mini);
		free(line);
	}
}

int	main(int ac, char **av, char **ev)
{
	char		*line;
	t_global	mini;

	if (ac > 1)
		exit(1);
	line = NULL;
	(void)av;
	mini.env = ft_setenv(ev);
	mini.export = ft_setenv(ev);
	mini.head = NULL;
	mini.p_head = NULL;
	g_global.env = ev;
	// signal(SIGQUIT, sigquit_handler);
	// signal(SIGINT, ft_handler);
	minishell_loop(line, &mini);
	return (0);
}
