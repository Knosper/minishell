/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:54:52 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/09 19:56:23 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void lex_pipe(t_lex *lex)
{
	if (lex->c == '|')
	{
		lex->flag = REDIRECT_OUT;
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
	}
}

static void lex_redirect_out(t_data *data, t_lex *lex)
{
	if (lex->c == '>')
	{
		lex->flag = REDIRECT_OUT;
		lex->buf = ft_join_char(lex->buf, lex->c);
		printf("char: %c\n", lex->c);
		printf("buffer: %s\n", lex->buf);
		lex->i++;
		lex->c = data->input[lex->i];
		if (lex->c == '>')
		{
			lex->flag = APPEND_IN;
			lex->buf = ft_join_char(lex->buf, lex->c);
			lex->i++;
		}
	}
}

static void lex_redirect_in(t_data *data, t_lex *lex)
{
	if (lex->c == '<')
	{
		lex->flag = REDIRECT_IN;
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
		lex->c = data->input[lex->i];
		if (lex->c == '<')
		{
			lex->flag = HEREDOC;
			lex->buf = ft_join_char(lex->buf, lex->c);
			lex->i++;
		}
	}
}

void	handle_redirections(t_data *data, t_lex *lex)
{
	if (lex->c == '<')
		lex_redirect_in(data, lex);
	else if ( lex->c == '>')
		lex_redirect_out(data, lex);
	else
		lex_pipe(lex);
	if (data->input[lex->i + 1] == DELIMITER)
		return ;
	else
		add_token(data, lex);
}

bool	find_redirections(t_lex *lex)
{
	if (lex->c == '<' || lex->c == '>' || lex->c == '|')
		return (true);
	return (false);
}
