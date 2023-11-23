/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:35:25 by bbach             #+#    #+#             */
/*   Updated: 2023/11/23 11:38:24 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void    sort_input(t_minish *minish, char *input)
{
    int     i;
    int     j;
    int     k;
    char    **tab;
    
    (void)minish;
    i = 0;
    j = 0;
    k = str_in_input(input);
    tab = malloc(sizeof(char *) * (k + 1));
    if (!tab)
        return ;
    k = 0;
    while (input[i])
    {
        if (ft_isalnum(input[i]) == SUCCESS)
        {
            j = i;
            while (ft_isalnum(input[i]) == SUCCESS)
                i++;
            tab[k] = ft_strndup(input + j, i - j);
            k++;
            j = 0;
        }
        i++;
    }
    tab[k] = NULL;
    k = 0;
    while (tab[k])
    {
        printf("tab[%d] = %s\n", k, tab[k]);
        k++;
    }
}

int     str_in_input(char *str)
{
    int     i;
    int     j;

    j = 0;
    i = 0;
    while (str[i])
    {
        if (ft_isalnum(str[i]) == SUCCESS)
        {
            while (ft_isalnum(str[i]) == SUCCESS)
                i++;
            j++;
        }
        i++;
    }
    return (j);
}
char	*ft_strndup(char *s, int n)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (dst == NULL)
		return (NULL);
	while (s[i] && i < n)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}