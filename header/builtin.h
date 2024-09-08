/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:22:18 by hheng             #+#    #+#             */
/*   Updated: 2024/09/08 19:22:48 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_FUNCS_H
#define BUILTIN_FUNCS_H

// Function prototypes
int execute_command(char **args);
int cmd_echo(char **args);
int cmd_cd(char **args);
int cmd_pwd(char **args);
int cmd_export(char **args);
int cmd_unset(char **args);
int cmd_env(char **args);
int cmd_exit(char **args);

#endif // BUILTIN_FUNCS_H