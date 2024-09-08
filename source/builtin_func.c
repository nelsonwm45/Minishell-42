/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:32:38 by hheng             #+#    #+#             */
/*   Updated: 2024/09/08 17:29:41 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// Execute the command
int execute_command(char **args) {
    if (ft_strcmp(args[0], "echo") == 0) {
        return cmd_echo(args);
    } else if (ft_strcmp(args[0], "cd") == 0) {
        return cmd_cd(args);
    } else if (ft_strcmp(args[0], "pwd") == 0) {
        return cmd_pwd(args);
    } else if (ft_strcmp(args[0], "export") == 0) {
        return cmd_export(args);
    } else if (strcmp(args[0], "unset") == 0) {
        return cmd_unset(args);
    } else if (strcmp(args[0], "env") == 0) {
        return cmd_env(args);
    } else if (strcmp(args[0], "exit") == 0) {
        return cmd_exit(args);
    } else {
        write(STDOUT_FILENO, "Command not found: ", 19);
        write(STDOUT_FILENO, args[0], ft_strlen(args[0]));
        write(STDOUT_FILENO, "\n", 1);
    }
    return 1;
}

// Implement echo with -n option using only allowed functions
int cmd_echo(char **args) {
    int n_flag = 0;
    int i = 1;

    if (args[1] != NULL && ft_strcmp(args[1], "-n") == 0) {
        n_flag = 1;
        i++;
    }

    while (args[i] != NULL) {
        write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
        if (args[i + 1] != NULL) {
            write(STDOUT_FILENO, " ", 1);
        }
        i++;
    }

    if (!n_flag) {
        write(STDOUT_FILENO, "\n", 1);
    }
    return 1;
}

// // Implement cd using only allowed functions
// int cmd_cd(char **args) {
//     if (args[1] == NULL) {
//         write(STDERR_FILENO, "cd: expected argument\n", 23);
//     } else {
//         if (chdir(args[1]) != 0) {
//             write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
//             write(STDERR_FILENO, "\n", 1);
//         }
//     }
//     return 1;
// }

// // Implement pwd using only allowed functions
// int cmd_pwd(char **args) {
//     char cwd[1024];
//     if (getcwd(cwd, sizeof(cwd)) != NULL) {
//         write(STDOUT_FILENO, cwd, ft_strlen(cwd));
//         write(STDOUT_FILENO, "\n", 1);
//     } else {
//         write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
//         write(STDERR_FILENO, "\n", 1);
//     }
//     return 1;
// }

// // Implement export using allowed functions
// int cmd_export(char **args) {
//     if (args[1] == NULL) {
//         write(STDERR_FILENO, "export: expected argument\n", 27);
//         return 1;
//     }

//     char *var = strtok(args[1], "=");
//     char *value = strtok(NULL, "=");

//     if (value != NULL) {
//         if (setenv(var, value, 1) != 0) {
//             write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
//             write(STDERR_FILENO, "\n", 1);
//         }
//     } else {
//         write(STDERR_FILENO, "export: invalid format, use VAR=value\n", 38);
//     }

//     return 1;
// }

// // Implement unset using allowed functions
// int cmd_unset(char **args) {
//     if (args[1] == NULL) {
//         write(STDERR_FILENO, "unset: expected argument\n", 26);
//     } else {
//         if (unsetenv(args[1]) != 0) {
//             write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
//             write(STDERR_FILENO, "\n", 1);
//         }
//     }
//     return 1;
// }

// // Implement env using allowed functions
// int cmd_env(char **args) {
//     extern char **environ;
//     char **env = environ;

//     while (*env) {
//         write(STDOUT_FILENO, *env, strlen(*env));
//         write(STDOUT_FILENO, "\n", 1);
//         env++;
//     }
//     return 1;
// }

// Implement exit
int cmd_exit(char **args) {
    exit(0);
}