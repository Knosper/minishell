/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:35:33 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/06 19:34:46 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data 	data;

	init(&data, envp);

	while (data.exit_minishell != false)
	{
//		line = ft_readline();
//		check_line();
//		if (line == ok)
//			addline_to_history;
//		lexer();
//		parser();
//		exec();
	}
//	free_all_ressources();

	init();


}


/*
 * 	//history maker

 * */