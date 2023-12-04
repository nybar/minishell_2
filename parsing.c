/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:42:06 by bbach             #+#    #+#             */
/*   Updated: 2023/12/02 22:19:49 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_lst *tokenize_input(char *input_line)
{
    char *line_copy;
    t_lst *tokens;

    line_copy = ft_strdup(input_line);
    if (!line_copy)
        exit(FAILURE);
    tokens = lexer(line_copy);
    free(line_copy);

    return (tokens);
}

t_lst	*lexer(char *line)
{
	t_lexer	*lx;

	lx = malloc(sizeof(t_lexer));
	init_lexer(lx, line);
	while (lx->line[++lx->index] != '\0')
	{
		if (lx->line[lx->index] == '\'' || lx->line[lx->index] == '\"')
			process_quotes(lx);
		else if (lx->line[lx->index] == ' ' || lx->line[lx->index] == '\n')
		{
			lx->end = lx->index;
			if (lx->state == START)
			{
				if (lx->end > lx->start)
					process_no_quotes(lx);
				lx->start = lx->index + 1;
			}
		}
	}
	if (lx->state == START && lx->index > lx->start)
		tokenize_last_word(lx);
	return (lx->token_list);
}

