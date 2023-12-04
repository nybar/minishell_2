/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:30:49 by bbach             #+#    #+#             */
/*   Updated: 2023/12/04 12:08:51 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    char *line;
    t_lst *token_list;

    while (1)
    {
        line = readline(">$ ");
        if (!line)
            break;
        add_history(line);;
        token_list = tokenize_input(line);

        // Parcours de la liste de tokens et exécution des commandes
        t_node *current = token_list->head;
        while (current != NULL)
        {
            execute_command(current, env);
            current = current->next;
        }

        free(line);
    }

    return 0;
}