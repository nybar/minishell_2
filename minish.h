/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:58:48 by bbach             #+#    #+#             */
/*   Updated: 2023/11/23 11:58:42 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include "./includes/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

typedef struct s_minish
{
    char    *input;
    char    **my_env;
}           t_minish;


// valid_input.c

int     valid_input(char *input);

// parsing.c

void    sort_input(t_minish *minish, char *input);
int     str_in_input(char *str);
char    *ft_strndup(char *s, int n);

// get_env.c

char    **get_my_env(char **env, t_minish *minish);
char    *get_value_any_env(char **any_env, char *key);
int      ft_strcmp(char *s1,char *s2);
char     **ft_strsplit(char *str, char c);

#endif