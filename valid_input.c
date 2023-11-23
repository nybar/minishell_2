/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:18:37 by bbach             #+#    #+#             */
/*   Updated: 2023/11/18 15:59:18 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int     valid_input(char *input)
{
    int     i;

    if (!input)
        return (FAILURE);
    i = 0;
    if (input[i] == '\0')
        return (FAILURE);
    return (SUCCESS);
}