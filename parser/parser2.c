/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamilog <tahasamiloglu@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:27:36 by msamilog          #+#    #+#             */
/*   Updated: 2024/05/09 20:09:46 by msamilog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* int	(*ft_controlbuiltin(char *str)) (t_global *mini, struct s_simple_cmds *temp)
{
	if (!str)
		return (NULL);
	if (!ft_strcmp(str, "export"))
		return (&ft_export);
	else if (!ft_strcmp(str, "echo"))
		return (&ft_echo);
	else if (!ft_strcmp(str, "env"))
		return (&ft_env);
	else if (!ft_strcmp(str, "exit"))
		return (&ft_exit);
	else if (!ft_strcmp(str, "cd"))
		return (&ft_cd);
	else if (!ft_strcmp(str, "pwd"))
		return (&ft_pwd);
	else if (!ft_strcmp(str, "unset"))
		return (&ft_unset);
	else
		return (NULL);
}

void	ft_init_builtin(t_global *mini)
{
	t_simple_cmds	*temp;

	temp = mini->p_head;
	while (temp)
	{
		temp->builtin = ft_controlbuiltin(temp->str[0]);
		temp = temp->next;
	}
} */

int	ft_pipesize(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer && lexer->token != PIPE)
	{
		i++;
		lexer = lexer->next;
	}
	return (i);
}

void	ft_init_matrix(t_global *mini)
{
	t_lexer			*temp;
	t_simple_cmds	*temp_s;
	int				i;

	temp = mini->head;
	temp_s = mini->p_head;
	while (temp_s)
	{
		i = 0;
		temp_s->str = malloc((ft_pipesize(temp) + 1) * sizeof(char *));
		while (temp && temp->token != PIPE)
		{
			temp_s->str[i++] = ft_strdup(temp->str);
			temp = temp->next;
		}
		if (temp)
			temp = temp->next;
		temp_s->str[i] = NULL;
		temp_s = temp_s->next;
	}
}
