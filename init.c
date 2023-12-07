/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 12:25:33 by bbach             #+#    #+#             */
/*   Updated: 2023/12/04 19:05:56 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	init_lexer(t_lexer *lx, char *line)
{
    lx->line = line;
    lx->quote_type = '\0';
    lx->index = -1;
    lx->start = 0;
    lx->end = 0;
    lx->quote_start = 0;
    lx->quote_end = 0;
    lx->token_list = malloc(sizeof(t_lst));
    if (!lx->token_list)
        exit(EXIT_FAILURE);
    lx->token_list->head = NULL;
    lx->state = START;
    lx->quotes = NO_QUOTES;
}