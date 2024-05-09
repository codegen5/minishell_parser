/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:22:50 by msamilog          #+#    #+#             */
/*   Updated: 2024/05/09 18:46:34 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_index(t_global *mini)
{
	t_lexer	*temp;
	int		i;

	temp = mini->head;
	i = 0;
	while (temp)
	{
		temp->i = i++;
		temp = temp->next;
	}
}

void	ft_delete_node(int index, t_global *mini)
{
	t_lexer	*temp;

	temp = mini->head;
	if (!temp)
		return ;
	while (temp->i != index && temp->next)
		temp = temp->next;
	if (temp->i != index)
		return ;
	if (temp->prev)
		temp->prev->next = temp->next;
	else
		mini->head = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp->str);
	free(temp);
	ft_set_index(mini);
}

int	ft_size_cmds(t_global *mini)
{
	t_simple_cmds	*temp;
	int				size;

	size = 0;
	temp = mini->p_head;
	while (temp)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}
