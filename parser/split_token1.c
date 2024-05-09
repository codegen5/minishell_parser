/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:53:04 by msamilog          #+#    #+#             */
/*   Updated: 2024/05/09 18:46:57 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_delimiter(char c)
{
	char	*del;

	del = "|<>";
	while (*del)
	{
		if (c == *del)
			return (1);
		del++;
	}
	return (0);
}

void	ft_spt1(char **str, int *is_token, int *count, int skip)
{
	if ((*is_token))
	{
		(*is_token) = 0;
		(*count)++;
	}
	(*count)++;
	(*str) += skip;
}

void	ft_spt2(char ***tokens, int *i, int *tok_len, char **str)
{
	if (*tok_len > 0)
	{
		(*tokens)[*i] = (char *)malloc((*tok_len + 1) \
			* sizeof(char));
		ft_strncpy((*tokens)[*i], (*str) - *tok_len, *tok_len);
		(*tokens)[*i][*tok_len] = '\0';
		(*i)++;
	}
	(*tokens)[*i] = (char *)malloc(3 * sizeof(char));
	ft_strncpy((*tokens)[*i], (*str), 2);
	(*tokens)[*i][2] = '\0';
	(*i)++;
	(*str) += 2;
	(*tok_len) = 0;
}

int	count_tokens(char *str)
{
	int	count;
	int	is_token;

	count = 0;
	is_token = 0;
	while (*str)
	{
		if (strncmp(str, ">>", 2) == 0 || strncmp(str, "<<", 2) == 0)
			ft_spt1(&str, &is_token, &count, 2);
		else if (is_delimiter(*str))
			ft_spt1(&str, &is_token, &count, 1);
		else
		{
			is_token = 1;
			str++;
		}
	}
	if (is_token)
		count++;
	return (count);
}

char	**ft_split_tok(char *str)
{
	int		token_count;
	char	**tokens;
	int		index;
	int		token_length;

	token_count = count_tokens(str);
	tokens = (char **)malloc((token_count + 1) * sizeof(char *));
	index = 0;
	token_length = 0;
	while (*str)
	{
		if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
			ft_spt2(&tokens, &index, &token_length, &str);
		else if (is_delimiter(*str))
			ft_spt3(&tokens, &index, &token_length, &str);
		else
		{
			token_length++;
			str++;
		}
	}
	if (token_length > 0)
		ft_spt4(&tokens, &index, &token_length, &str);
	tokens[index] = NULL;
	return (tokens);
}
