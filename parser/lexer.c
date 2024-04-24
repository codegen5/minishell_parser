/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:15:39 by msamilog          #+#    #+#             */
/*   Updated: 2024/04/24 20:18:16 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote(char *line)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			flag = 1;
			while (line[++i] && flag == 1)
			{
				if (line[i] == '"')
					flag = 0;
				if (line[i] == '|' || line[i] == '>' \
				|| line[i] == '<')
					flag = 0;
			}
			continue ;
		}
		else if (line[i] == '\'')
		{
			flag = 1;
			while (line[++i] && flag == 1)
			{
				if (line[i] == '\'')
					flag = 0;
				if (line[i] == '|' || line[i] == '>' \
				|| line[i] == '<')
					flag = 0;
			}
			continue ;
		}
		i++;
	}
	return (flag);
}

void	ft_init_lexer(t_global *mini, char *line)
{
	char	**lexers;
	char	**tokens;
	int		i;
	int		j;

	lexers = ft_split(line, "\t ");
	if (!lexers)
		return ;
	i = 0;
	while (lexers[i])
	{
		if (!ft_quote(lexers[i]))
			tokens = ft_split_tok(lexers[i], "|<>");
		else
			tokens = ft_split(lexers[i], " ");
		j = 0;
		while (tokens[j])
			ft_push_back(mini, tokens[j++]);
		free_tokens(tokens);
		i++;
	}
	free_tokens(lexers);
}
