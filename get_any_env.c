/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_any_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 22:04:30 by bbach             #+#    #+#             */
/*   Updated: 2023/12/06 13:18:47 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
char **get_my_env(char **env)
{
    int i;
    int j;
    char **my_env;

    i = 0;
    j = 0;
    while (env[i])
        i++;
    my_env = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (env[i])
    {
        my_env[j] = ft_strdup(env[i]);
        j++;
        i++;
    }
    my_env[j] = NULL;
    i = 0;
    return (my_env);
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
       // ft_printf("str_tmp = %s\n", str_tmp);
        tmp = ft_strsplit(str_tmp, '=');
        if (ft_strcmp(tmp[0], key) == SUCCESS)
        {
            value = ft_strdup(tmp[1]);
            // ft_printf("key = %s\n", key);
            // ft_printf("tmp de 0 = %s\n", tmp[0]);
            // ft_printf("value = %s\n", value);
            free(str_tmp);
            ft_free_2d_array(tmp);
            return (value);
        }
        i++;
    }
    ft_printf("Error: key not found in env\n");
    return (NULL);
}
void    ft_free_2d_array(char **array)
{
    if (array)
    {
        int     i;

        i = 0;
        while (array[i])
        {
            free(array[i]);
            i++;
        }
        free(array);
    }
}