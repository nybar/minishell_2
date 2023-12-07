/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbach <bbach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:07:56 by bbach             #+#    #+#             */
/*   Updated: 2023/12/06 13:29:28 by bbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_command_path(char *command, char **env)
{
	char	**path_dirs;
	char	*full_path;
	int		i;

    ft_printf("$USER %s\n", get_value_any_env(env, "USER"));
	path_dirs = ft_strsplit(get_value_any_env(env, "PATH"), ':');
	i = 0;
	while (path_dirs[i])
	{
        ft_printf("Path dirs:%s\n", path_dirs[i]);
		full_path = find_command_path(command, /*ft_strsplit(path_dirs[i], '/')*/ env);
        // ft_printf("Full path: %s\n", full_path);
		if (full_path)
		{
			ft_free_2d_array(path_dirs); // Libération de la mémoire allouée pour path_dirs
			return (full_path);
		}
		i++;
	}
	ft_free_2d_array(path_dirs); // Libération de la mémoire allouée pour path_dirs
	return (NULL);
}

char	*find_command_path(char *command, char **env)
// {
// 	char	*full_path;
// 	char	*tmp_path;
// 	int		i;

// 	i = 0;
// 	while (path[i])
// 	{
// 		tmp_path = ft_strjoin(path[i], "/");
//         ft_printf("Tmp path: %s\n", tmp_path);
// 		full_path = ft_strcat(tmp_path, command);
// 		// free(tmp_path); // Libération de la mémoire allouée pour tmp_path
//         ft_printf("Full path: %s\n", full_path);
// 		if (access(full_path, F_OK | X_OK) == 0)
//         {
// 			return (full_path);
//         }
// 		free(full_path); // Libération de la mémoire allouée pour full_path
// 		i++;
// 	}
// 	return (NULL);
// }
{
	int     i;
	char    *path_line;
	char    **path;
	int     found;

	found = 0;
	i = -1;
	while (env[++i]) 
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			path_line = ft_strdup(env[i] + 5);
	i = 0;
	path = ft_split(path_line, ':');
	while (path[i] && found == 0)
	{
		free(path_line);
		path_line = ft_strjoin2(path[i], "/");
		path_line = ft_strjoin2(path_line, command);
		if (access(path_line, F_OK | X_OK ) == 0)
			found = 1;
		i++;
	}
	// free_path(path, i);
	if (found == 0)
		ft_printf("command not found\n");
	return (path_line);
}

void execute_command(t_node *command, char **env)
{
    // Si le type d'opérateur est T_WORD, il s'agit d'une commande simple
    if (command->op_type == T_WORD)
    {
        // Exécution d'une commande simple
        command->args = ft_strsplit(command->value, ' '); 
        char *command_path = get_command_path(command->value, env);
        ft_printf("Command path: %s\n", command_path);
        if (command_path != NULL)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                // Processus fils
                execve(command_path, command->args, env);
                ft_printf("%s: Command not found\n", command->value);
                return (exit(EXIT_FAILURE));
            }
            else if (pid > 0)
            {
                // Processus parent
                waitpid(pid, NULL, 0);
            }
            else
            {
                perror("Erreur de fork");
            }
            free(command_path);
        }
        else
        {
            ft_putstr_fd("Commande introuvable", 1);
        }
    }
    else if (command->op_type == T_BAR)
    {
        // Gestion du pipe (|)
        int pipe_fd[2];
        pid_t pid1, pid2;

        // Création du pipe
        if (pipe(pipe_fd) == -1)
        {
            perror("Erreur lors de la création du pipe");
            return;
        }

        pid1 = fork();
        ft_printf("est on rentrés dans le pipe ?\n");
        if (pid1 == 0)
        {
            // Processus fils (gauche du pipe)
            close(pipe_fd[0]); // Fermer l'extrémité de lecture du pipe dans le processus fils
            dup2(pipe_fd[1], STDOUT_FILENO); // Redirection de la sortie standard vers le pipe
            close(pipe_fd[1]); // Fermer l'extrémité d'écriture du pipe dans le processus fils

            execute_command(command->left, env); // Exécution de la partie gauche du pipe
            exit(EXIT_SUCCESS);
        }
        else if (pid1 > 0)
        {
            // Processus parent
            pid2 = fork();
            if (pid2 == 0)
            {
                // Processus fils (droite du pipe)
                close(pipe_fd[1]); // Fermer l'extrémité d'écriture du pipe dans le processus fils
                dup2(pipe_fd[0], STDIN_FILENO); // Redirection de l'entrée standard depuis le pipe
                close(pipe_fd[0]); // Fermer l'extrémité de lecture du pipe dans le processus fils

                execute_command(command->right, env); // Exécution de la partie droite du pipe
                exit(EXIT_SUCCESS);
            }
            else if (pid2 > 0)
            {
                // Processus parent
                close(pipe_fd[0]); // Fermer l'extrémité de lecture du pipe dans le processus parent
                close(pipe_fd[1]); // Fermer l'extrémité d'écriture du pipe dans le processus parent

                // Attente de la fin des deux processus fils
                waitpid(pid1, NULL, 0);
                waitpid(pid2, NULL, 0);
            }
            else
            {
                perror("Erreur de fork");
            }
        }
        else
        {
            perror("Erreur de fork");
        }
    }
    else if (command->op_type == T_GT)
    {
        // Gestion de la redirection (>)
        int fd = open(command->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("Erreur lors de l'ouverture du fichier pour la redirection");
            return;
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            // Processus fils
            dup2(fd, STDOUT_FILENO); // Redirection de la sortie standard vers le fichier
            close(fd); // Fermer le descripteur de fichier après la redirection

            execute_command(command->left, env); // Exécution de la partie gauche de la redirection
            exit(EXIT_SUCCESS);
        }
        else if (pid > 0)
        {
            // Processus parent
            close(fd); // Fermer le descripteur de fichier dans le processus parent
            waitpid(pid, NULL, 0); // Attente de la fin du processus fils
        }
        else
        {
            perror("Erreur de fork");
        }
    }
    else if (command->op_type == T_GTGT)
    {
        // Gestion de la redirection (> >)
        int fd = open(command->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            perror("Erreur lors de l'ouverture du fichier pour la redirection");
            return;
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            // Processus fils
            dup2(fd, STDOUT_FILENO); // Redirection de la sortie standard vers le fichier en mode append
            close(fd); // Fermer le descripteur de fichier après la redirection

            execute_command(command->left, env); // Exécution de la partie gauche de la redirection
            exit(EXIT_SUCCESS);
        }
        else if (pid > 0)
        {
            // Processus parent
            close(fd); // Fermer le descripteur de fichier dans le processus parent
            waitpid(pid, NULL, 0); // Attente de la fin du processus fils
        }
        else
        {
            perror("Erreur de fork");
        }
    }
    else if (command->op_type == T_LT)
    {
        // Gestion de la lecture depuis un fichier (<)
        int fd = open(command->right->value, O_RDONLY);
        if (fd == -1)
        {
            perror("Erreur lors de l'ouverture du fichier pour la lecture");
            return;
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            // Processus fils
            dup2(fd, STDIN_FILENO); // Redirection de l'entrée standard depuis le fichier
            close(fd); // Fermer le descripteur de fichier après la redirection

            execute_command(command->left, env); // Exécution de la partie gauche de la lecture depuis un fichier
            exit(EXIT_SUCCESS);
        }
        else if (pid > 0)
        {
            // Processus parent
            close(fd); // Fermer le descripteur de fichier dans le processus parent
            waitpid(pid, NULL, 0); // Attente de la fin du processus fils
        }
        else
        {
            perror("Erreur de fork");
        }
    }
}
