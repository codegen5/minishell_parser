/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:43:16 by msamilog          #+#    #+#             */
/*   Updated: 2024/05/09 18:46:49 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parser_firstnode(t_global *mini, t_lexer *lexer)
{
	t_simple_cmds	*new;
	int				i;

	ft_skipinit(&new, 0);
	new->prev = NULL;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token)
		{
			ft_parser_lexpush_back(new, lexer->str);
			ft_parser_lexpush_back(new, lexer->next->str);
			i = lexer->i;
			lexer = lexer->next->next;
			ft_delete_node(i, mini);
			ft_delete_node(i, mini);
			new->num_redirections++;
			continue ;
		}
		lexer = lexer->next;
	}
	mini->p_head = new;
}

void	ft_skipinit(t_simple_cmds **new, int flag)
{
	static int	i = 0;
	char		*num;
	char		*temp;

	if (flag)
	{
		i = 0;
		return ;
	}
	(*new) = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	(*new)->next = NULL;
	(*new)->num_redirections = 0;
	temp = ft_strdup("/Users/msamilog/temps/"); // Change this path to current user path
	num = ft_itoa(i++);
	(*new)->hd_file_name = ft_strjoin(temp, num);
	free(num);
	free(temp);
	(*new)->str = NULL;
	(*new)->redirections = NULL;
	(*new)->in_her = 0;
}

void	ft_parser_lastnode(t_global *mini, t_lexer *lexer)
{
	t_simple_cmds	*new;
	t_simple_cmds	*temp;
	int				i;

	ft_skipinit(&new, 0);
	temp = mini->p_head;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token)
		{
			ft_parser_lexpush_back(new, lexer->str);
			ft_parser_lexpush_back(new, lexer->next->str);
			i = lexer->i;
			lexer = lexer->next->next;
			ft_delete_node(i, mini);
			ft_delete_node(i, mini);
			new->num_redirections++;
			continue ;
		}
		lexer = lexer->next;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void	ft_parser_pushback(t_global *mini, t_lexer *lexer)
{
	if (!mini->p_head)
		ft_parser_firstnode(mini, lexer);
	else
		ft_parser_lastnode(mini, lexer);
}

void	ft_init_parser(t_global *mini)
{
	t_lexer	*lexer;
	t_lexer	*forward;

	lexer = mini->head;
	forward = lexer;
	mini->p_head = NULL;
	if (!lexer)
		return ;
	while (lexer)
	{
		while (forward && forward->token != PIPE)
			forward = forward->next;
		if (forward)
			forward = forward->next;
		ft_parser_pushback(mini, lexer);
		lexer = forward;
	}
	ft_init_matrix(mini);
	// ft_init_builtin(mini);
}
