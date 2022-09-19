/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:07:45 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/19 13:17:25 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int pwd(void)
{
    char    *path;

	path = NULL;
    path = getcwd(path, 0);
    if (!path || errno != 0)
        return (error("Error in pwd.c\n", errno));
    printf("path = %s\n", path);
    free(path);
    return (EXIT_SUCCESS);
}
