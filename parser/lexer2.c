/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:15:22 by msamilog          #+#    #+#             */
/*   Updated: 2024/05/09 19:03:40 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_first_node(t_global *mini, char *str)
{
	mini->head = (t_lexer *)malloc(sizeof(t_lexer));
	if (!mini->head)
		return ;
	mini->head->next = NULL;
	mini->head->prev = NULL;
	mini->head->token = ft_find_token(str);
	mini->head->str = ft_strdup(str);
	mini->head->i = 0;
	if (str[0] == '"')
		mini->head->is_quote = 2;
	else if (str[0] == '\'')
		mini->head->is_quote = 1;
	else
		mini->head->is_quote = 0;
}

void	ft_last_node(t_global *mini, char *str)
{
	t_lexer	*new;
	t_lexer	*temp;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return ;
	new->next = NULL;
	new->token = ft_find_token(str);
	new->str = ft_strdup(str);
	temp = mini->head;
	while (temp->next)
		temp = temp->next;
	new->prev = temp;
	temp->next = new;
	new->i = new->prev->i + 1;
	if (str[0] == '"')
		new->is_quote = 2;
	else if (str[0] == '\'')
		new->is_quote = 1;
	else
		new->is_quote = 0;
}

int	ft_find_token(char *str)
{
	if (!ft_strcmp("|", str))
		return (1);
	if (!ft_strcmp(">>", str))
		return (3);
	if (!ft_strcmp(">", str))
		return (2);
	if (!ft_strcmp("<<", str))
		return (5);
	if (!ft_strcmp("<", str))
		return (4);
	return (0);
}
