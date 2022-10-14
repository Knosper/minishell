/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:22:41 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/14 15:13:44 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

/*
 * In case of multiple DOLLAR signs in a row and SPACE sign
 * creates a token with many DOLLAR sign in content.
 * NO expansion of multiple return values is supported!
 * */
void	handle_multiple_dollars(t_data *data, t_lex *lex)
{
	bool	is_sep;

	while (lex->c == DOLLAR)
	{
		lex->buf = ft_join_char(lex->buf, DOLLAR);
		lex->i++;
		lex->c = data->input[lex->i];
	}
	is_sep = check_sep(data, lex->c);
	if (is_sep == true && lex->c != DOUBLE_QUOTE && lex->c != SINGLE_QUOTE)
	{
		lex->expansion = false;
		if (lex->double_quote_mode == false)
			add_token(data, lex);
	}
	else
	{
		if (lex->double_quote_mode == false)
			add_token(data, lex);
		lex->expansion = false;
	}
}

/*
 * In case of only one DOLLAR and SPACE sign - creates a token with dollar
 * sign in content.
 * */
void	handle_one_dollar(t_data *data, t_lex *lex)
{
	bool	is_sep;

	lex->buf = ft_join_char(lex->buf, DOLLAR);
	is_sep = check_sep(data, lex->c);
	if (is_sep == true && lex->c != DOUBLE_QUOTE && lex->c != SINGLE_QUOTE)
	{
		lex->expansion = false;
		if (lex->double_quote_mode == false)
			add_token(data, lex);
	}
	else
	{
		if (lex->double_quote_mode == false)
			add_token(data, lex);
		lex->expansion = false;
	}
	lex->i++;
}
