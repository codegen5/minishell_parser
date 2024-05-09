/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:50 by msamilog          #+#    #+#             */
/*   Updated: 2024/05/09 18:46:21 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_tokens(t_global *mini)
{
	t_lexer	*tmp;

	tmp = mini->head;
	while (tmp)
	{
		if (tmp->token >= 2 && tmp->next && tmp->next->token)
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			g_global.error_num = 258;
			return (0);
		}
		else if (tmp->token >= 2 && !tmp->next)
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			g_global.error_num = 258;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_check_pipe(t_global *mini)
{
	t_lexer	*tmp;

	tmp = mini->head;
	while (tmp)
	{
		if (tmp->token == 1 && tmp->prev && tmp->prev->token == 1)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			g_global.error_num = 258;
			return (0);
		}
		else if (tmp->token == 1 && (!tmp->next || !tmp->prev))
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			g_global.error_num = 258;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_check_error(t_global *mini)
{
	return (!ft_check_pipe(mini) || !ft_check_tokens(mini));
}
