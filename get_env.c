/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:43:56 by bbach             #+#    #+#             */
/*   Updated: 2023/11/23 11:58:46 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char **get_my_env(char **env, t_minish *minish)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (env[i])
        i++;
    minish->my_env = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (env[i])
    {
        minish->my_env[j] = ft_strdup(env[i]);
        j++;
        i++;
    }
    minish->my_env[j] = NULL;
    i = 0;
    // while (minish->my_env[i])
    // {
    //     ft_printf("my_env[%d] = %s\n", i, minish->my_env[i]);
    //     i++;
    // }
    return (minish->my_env);
}
char    *get_value_any_env(char **any_env, char *key)
{
    int     i;
    char    *value;
    char    *str_tmp;
    char    **tmp; 

    i = 0;
    while (any_env[i])
    {
        str_tmp = ft_strdup(any_env[i]);
        tmp = ft_strsplit(str_tmp, '=');
        if (ft_strcmp(tmp[0], key) == SUCCESS)
        {
            value = ft_strdup(tmp[1]);
            ft_printf("value = %s\n", value);
            return (value);
        }
    }
    ft_printf("Error: key not found in env\n");
    return (NULL);
}

int     ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (-1);
        i++;
    }
    return (0);
}

char    **ft_strsplit(char *str, char c)
{
    int     i;
    int     j;
    int     k;
    char    **tab;

    i = 0;
    j = 0;
    k = 0;
    tab = malloc(sizeof(char *) * (ft_strlen(str) + 1));
    if (!tab)
        return (NULL);
    while (str[i])
    {
        if (str[i] == c)
        {
            tab[k] = ft_strndup(str + j, i - j);
            k++;
            j = i + 1;
        }
        i++;
    }
    tab[k] = ft_strndup(str + j, i - j);
    tab[k + 1] = NULL;
    return (tab);
}