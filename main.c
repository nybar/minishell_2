/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:55:26 by bbach             #+#    #+#             */
/*   Updated: 2023/11/23 13:12:52 by bbach            ###   ########.fr       */
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
                get_my_env(env, &minish);
                get_value_any_env(minish.my_env, "$USER");
                free(minish.input);
            }
            else
                free(minish.input);
    }
	return (SUCCESS);
}