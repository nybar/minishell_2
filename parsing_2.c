/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:22:36 by bbach             #+#    #+#             */
/*   Updated: 2023/11/18 21:23:00 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char    *input_dequoted(char *input, t_minishell *minishell)
{
    int     i;
    int     j;
    char    *dequoted;
    
    i = 0;
    j = 0;
    dequoted = malloc(sizeof(char) * (ft_strlen(input) + 1));