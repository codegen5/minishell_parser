/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:15:39 by msamilog          #+#    #+#             */
/*   Updated: 2024/05/10 16:57:39 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_push_back(t_global *mini, char *str)
{
	if (!mini->head)
	{
		ft_first_node(mini, str);
		return ;
	}
	ft_last_node(mini, str);
}

void	ft_double_quote(char *line, int *i, int *flag)
{
	*flag = 1;
	while (line[++*i] && *flag == 1)
	{
		if (line[*i] == '"' || line[*i] == '|' || line[*i] == '>' \
		|| line[*i] == '<')
			*flag = 0;
	}
}

void	ft_single_quote(char *line, int *i, int *flag)
{
	*flag = 1;
	while (line[++*i] && *flag == 1)
	{
		if (line[*i] == '\'' || line[*i] == '|' || line[*i] == '>' \
		|| line[*i] == '<')
			*flag = 0;
	}
}

int	ft_quote(char *line)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '"')
			ft_double_quote(line, &i, &flag);
		else if (line[i] == '\'')
			ft_single_quote(line, &i, &flag);
		else
			i++;
	}
	return (flag);
}

void	ft_init_lexer(t_global *mini, char *line)
{
	char	**lexemes;
	char	**tokens;
	int		i;
	int		j;

	lexemes = ft_split(line, ' ');
	if (!lexemes)
		return ;
	i = 0;
	while (lexemes[i])
	{
		if (!ft_quote(lexemes[i]))
			tokens = ft_split_tok(lexemes[i]);
		else
			tokens = ft_split(lexemes[i], ' ');
		j = 0;
		while (tokens[j])
			ft_push_back(mini, tokens[j++]);
		free_tokens(tokens);
		i++;
	}
	free_tokens(lexemes);
}
