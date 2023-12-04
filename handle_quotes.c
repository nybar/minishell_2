/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:52:40 by bbach             #+#    #+#             */
/*   Updated: 2023/12/02 21:57:14 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	process_quotes(t_lexer *lx)
{
	char	current;
	char	*token;

	while ((current = lx->line[lx->index]) != '\0')
	{
		if (get_type(current, lx) == '\'' || get_type(current, lx) == '\"')
		{
			if (lx->state == START)
			{
				lx->state = IN_WORD;
				lx->quote_type = current;
				lx->quote_start = lx->index;
			}
			else if (lx->state == IN_WORD && current == lx->quote_type)
			{
				lx->state = START;
				lx->quote_end = lx->index;
				if ((lx->quote_type == '\"' || lx->quote_type == '\'') && lx->quote_end > lx->quote_start + 1)
				{
					token = ft_strndup(lx->line + lx->quote_start + 1, lx->quote_end - lx->quote_start - 1);
					add_token(lx, token);
				}
				lx->start = lx->index + 1;
				return;
			}
		}
		lx->index++;
	}
}

void	process_no_quotes(t_lexer *lx)
{
	char	*token;

	token = ft_strndup(lx->line + lx->start, lx->end - lx->start);
	add_token(lx, token);
}

void	tokenize_last_word(t_lexer *lx)
{
	char	*token;

	token = ft_strndup(lx->line + lx->start, lx->index - lx->start);
	add_token(lx, token);
}

// void tokenize_word(t_lexer *lx)
// {
//     char *token;

//     if (lx->end > lx->start)
//     {
//         token = ft_strndup(lx->line + lx->start, lx->end - lx->start);
//         ft_printf("token: %s\n", token);
//         add_token(lx, token);
//     }
//     lx->start = lx->index + 1;
// }