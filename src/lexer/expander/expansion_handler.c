/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:49:28 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/14 16:02:08 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

/* Expands return of the last pipe process, based on the global g_exit_code. */
void	expand_last_return(t_data *data, t_lex *lex)
{
	char	*exit_code;
	bool	is_sep;

	exit_code = ft_itoa(g_exit_code);
	lex->buf = ft_strjoin(lex->buf, exit_code);
	free(exit_code);
	exit_code = NULL;
	lex->i++;
	lex->c = data->input[lex->i];
	is_sep = check_sep(data, lex->c);
	while (is_sep == false && lex->c != '\0')
	{
		is_sep = check_sep(data, lex->c);
		if (is_sep == true)
			break ;
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
		lex->c = data->input[lex->i];
	}
}

/*
 * Here happens the real expansion of the content:
 *
 * Compares the expandable content the DOLLAR sign with the envp. linked list.
 * If envp. with such key exist, the value of the appropriate envp->key becomes
 * is added to the buffer and becomes a token.
 * */
void	try_expansion(t_data *data, t_lex *lex)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(lex->buf, tmp->key) == 0)
		{
			free(lex->buf);
			lex->buf = NULL;
			lex->buf = ft_strjoin(lex->buf, tmp->val);
			return ;
		}
		tmp = tmp->next;
	}
	free(lex->buf);
	lex->buf = NULL;
}


void	try_double_quote_expansion(t_data *data, t_lex *lex, char *quote_buf)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(quote_buf, tmp->key) == 0)
		{
			lex->buf = ft_strjoin(lex->buf, tmp->val);
			return ;
		}
		tmp = tmp->next;
	}
}

/* Expands all expandable content after the DOLLAR sign */
void	expand_parameter(t_data *data, t_lex *lex)
{
	bool	is_sep;
	char 	*quote_buf;

	quote_buf = NULL;
	is_sep = check_sep(data, lex->c);

	if (lex->double_quote_mode == true)
	{
		while (lex->c != DOLLAR && lex->c != DOUBLE_QUOTE && lex->c != SINGLE_QUOTE && lex->c != SLASH)
		{
			quote_buf = ft_join_char(quote_buf, lex->c);
			lex->i++;
			lex->c = data->input[lex->i];
		}
		if (quote_buf != NULL)
		{
			try_double_quote_expansion(data, lex, quote_buf);
			free(quote_buf);
			quote_buf = NULL;
		}
	}
	else
	{
		while (is_sep == false && lex->c != '\0')
		{
			is_sep = check_sep(data, lex->c);
			if (is_sep == true || lex->c == SLASH)
				break ;
			lex->buf = ft_join_char(lex->buf, lex->c);
			lex->i++;
			lex->c = data->input[lex->i];
		}
		if (lex->buf != NULL)
			try_expansion(data, lex);
	}
}

/*
	Decides based on the current character how to expand the dollar sign.
 	Expands the input into a token and adds it to the token list.
*/
void	handle_expandable_parameter(t_data *data, t_lex *lex)
{
	bool	is_sep;

	lex->i++;
	lex->c = data->input[lex->i];
	is_sep = check_sep(data, lex->c);
	if (lex->c == '?')
		expand_last_return(data, lex);
	else if (is_sep == true || lex->c == '\0')
	{
		if (lex->c == SINGLE_QUOTE || lex->c == DOUBLE_QUOTE)
		{
			if (lex->single_quote_mode == true
				|| lex->double_quote_mode == true)
				lex->buf = ft_join_char(lex->buf, DOLLAR);
		}
	}
	else
		expand_parameter(data, lex);
	if (lex->buf != NULL && lex->double_quote_mode == false)
		add_token(data, lex);
}

/* Handles different expansion cases if dollar sign has occurred */
void	handle_expansion(t_data *data, t_lex *lex)
{
	lex->expansion = true;
	if (lex->buf != NULL && lex->double_quote_mode == false)
		add_token(data, lex);
	if (data->input[lex->i + 1] == SPACE || data->input[lex->i + 1] == '\0')
	{
		handle_one_dollar(data, lex);
		return ;
	}
	else if (data->input[lex->i + 1] == DOLLAR)
	{
		handle_multiple_dollars(data, lex);
		return ;
	}
	else
		handle_expandable_parameter(data, lex);
	lex->expansion = false;
}
