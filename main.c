/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:55:26 by bbach             #+#    #+#             */
/*   Updated: 2023/11/18 16:37:29 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int     main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;

    t_minish	minish;

    while (1)
    {
        minish.input = readline("shell>$ : ");
            if (valid_input(minish.input) == SUCCESS)
            {
                add_history(minish.input);
				sort_input(&minish, minish.input);
                free(minish.input);
            }
            else
                free(minish.input);
    }
	return (SUCCESS);
}