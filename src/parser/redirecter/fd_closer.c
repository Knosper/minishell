/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_closer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:30:42 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/21 11:41:30 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void 	close_fd_in_out(t_data *data)
{
	if (data->fd->fd_in != STDIN_FILENO)
	{
		if (close(data->fd->fd_in) < 0)
		{
			perror(NULL);
			data->parse_error = true;
		}
	}
	if (data->fd->fd_out != STDOUT_FILENO)
	{
		if (close(data->fd->fd_out) < 0)
		{
			perror(NULL);
			data->parse_error = true;
		}
	}
}

void 	close_unused_fd_out(t_data *data)
{
	if (data->fd->fd_out == STDOUT_FILENO)
		return ;
	else if (close(data->fd->fd_out) < 0)
	{
		perror(NULL);
		data->parse_error = true;
	}
}

void	close_unused_fd_in(t_data *data)
{
	if (data->fd->fd_in == STDIN_FILENO)
		return ;
	else if (close(data->fd->fd_in) < 0)
	{
		perror(NULL);
		data->parse_error = true;
	}
}