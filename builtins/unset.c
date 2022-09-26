/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:21:26 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 16:33:13 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	dl_node(t_data **data, t_envp *node)
{
	t_envp	*tmp;

	tmp = (*data)->envp;
	while (tmp)
	{
		if (tmp->next && tmp->next->key == node->key)
		{
			tmp->next = tmp->next->next;
			free(node->key);
			free(node->val);
			free(node);
			break ;
		}
		tmp = tmp->next;
	}
}

int	unset(t_data *data)
{
	t_envp	*tmp;
	int		i;
	int		j;

	i = 1;
	tmp = NULL;
	if (!data->builtins->command[i])
		return (EXIT_SUCCESS);
	while (data->builtins->command[i])
	{
		j = 0;
		tmp = ft_getenvp(data, data->builtins->command[i]);
		if (tmp != NULL)
			dl_node(&data, tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}
