/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:09:47 by msamilog          #+#    #+#             */
/*   Updated: 2024/05/09 19:15:16 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i <= n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i <= n)
	{
		dest[i++] = '\0';
	}
	return (dest);
}

void	ft_spt3(char ***tokens, int *i, int *tok_len, char **str)
{
	if (*tok_len > 0)
	{
		(*tokens)[*i] = (char *)malloc((*tok_len + 1) \
			* sizeof(char));
		ft_strncpy((*tokens)[*i], (*str) - *tok_len, *tok_len);
		(*tokens)[*i][*tok_len] = '\0';
		(*i)++;
	}
	(*tokens)[*i] = (char *)malloc(2 * sizeof(char));
	ft_strncpy((*tokens)[*i], (*str), 1);
	(*tokens)[*i][1] = '\0';
	(*i)++;
	(*str)++;
	(*tok_len) = 0;
}

void	ft_spt4(char ***tokens, int *i, int *tok_len, char **str)
{
	(*tokens)[*i] = (char *)malloc((*tok_len + 1) * sizeof(char));
	ft_strncpy((*tokens)[*i], (*str) - *tok_len, *tok_len);
	(*tokens)[*i][*tok_len] = '\0';
	(*i)++;
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i] != NULL)
			free(tokens[i++]);
		free(tokens);
	}
}

char	**ft_setenv(char **ev)
{
	int		i;
	char	**arr;

	i = 0;
	while (ev[i])
		i++;
	arr = malloc(sizeof(char *) * (i + 1));
	arr[i] = NULL;
	while (i--)
		arr[i] = ft_strdup(ev[i]);
	return (arr);
}
