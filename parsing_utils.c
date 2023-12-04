/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:03:38 by bbach             #+#    #+#             */
/*   Updated: 2023/12/04 12:42:29 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char get_type(char c, t_lexer *lx)
{
    if (c == '\'' || c == '\"')
        return c;
    else if (c == ' ')
        return ' ';
    else if (c == '\n')
        return '\n';
    else if (lx->state == START)
        return 'W';
    return 'C';
}

char *ft_strndup(char *str, int n)
{
    char *dest;
    int i;

    i = 0;
    dest = malloc(sizeof(char) * (n + 1));
    if (!dest)
        exit(EXIT_FAILURE);
    while (str[i] != '\0' && i < n)
    {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

t_node *create_new_token(char *value, t_lexer *lexer)
{
    (void)lexer; // TODO: remove this line (it's here to avoid a warning
    t_node *new_token;

    new_token = malloc(sizeof(t_node));
    if (new_token == NULL)
    {
        ft_putstr_fd("Erreur d'allocation mémoire pour le token", 2);
        exit(EXIT_FAILURE);
    }
    new_token->value = ft_strdup(value);
    if (new_token->value == NULL)
    {
        ft_putstr_fd("Erreur d'allocation mémoire pour le token", 2);
        exit(EXIT_FAILURE);
    }
    new_token->next = NULL;
    new_token->token = determine_token_type(value);
    return (new_token);
}

TOKEN	determine_token_type(char *value)
{
	if (ft_strcmp(value, "|") == 0)
		return (T_BAR);
	else if (ft_strcmp(value, "&") == 0)
		return (T_AMPER);
	else if (ft_strcmp(value, "<") == 0)
		return (T_LT);
	else if (ft_strcmp(value, ">") == 0)
		return (T_GT);
	else if (ft_strcmp(value, ">>") == 0)
		return (T_GTGT);
	else if (ft_strcmp(value, "\n") == 0)
		return (T_NL);
	else if (ft_strcmp(value, "") == 0)
		return (T_EOF);
	return (T_WORD);
}

void	add_token(t_lexer *lexer, char *token_value)
{
	t_node	*new_token;

	new_token = create_new_token(token_value, lexer);
    if (!lexer->token_list->head)
        lexer->token_list->head = new_token;
    else
	    add_token_to_list(&(lexer->token_list->head), new_token);
}

void	add_token_to_list(t_node **head, t_node *new_token)
{
	if (*head == NULL)
		*head = new_token;
	else
	{
		t_node *temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
	}
}

char *ft_strcat(char *dest, const char *src) 
{
    char *ptr = dest;

    while (*ptr != '\0')
        ptr++;
    while (*src != '\0') 
    {
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';
    return dest;
}
