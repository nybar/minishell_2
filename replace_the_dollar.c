/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_the_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:27:34 by bbach             #+#    #+#             */
/*   Updated: 2023/12/06 14:42:41 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*replace_the_dollar(char *str, char **env)
{
    int		i;
    int		j;
    int index;
    char	*tmp;

    index = 0;
    i = 0;
    j = 0;
    tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!tmp)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '$')
        {
            index = i - 1;
            while(str[i] && str[i] != ' ')
            {
                tmp[j] = str[i + 1];
                i++;
                j++;
            }
            tmp[j] = '\0';
            if (get_value_any_env(env, tmp) && ft_strcmp(tmp, "$") != 0)
            {
                char *tmp2 = ft_strndup(str, index);
                char *tmp3 = ft_strjoin(tmp2, get_value_any_env(env, tmp));
                ft_printf("new input: %s\n", tmp3);
                free(tmp2);
                free(tmp);
                return (tmp3);
            }
            else
            {
                free(tmp);
                return (ft_printf("Variable not found\n"), NULL);
            }
        }
        i++;
    }
    free(tmp);
    return (NULL);
}