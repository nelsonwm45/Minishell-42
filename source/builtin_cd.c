#include "minishell.h"

static void print_error(char *arg) {
    ft_putstr_fd("cd: ", 2);
    if (!arg)
        ft_putstr_fd("HOME or OLDPWD not set", 2);
    else
        ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd(": ", 2);
    ft_putendl_fd(arg, 2);
}

// Retrieves the path for HOME or OLDPWD from the environment
static char *get_env_path(t_env *env, const char *var_name) {
    while (env) {
        if (ft_strncmp(env->value, var_name, ft_strlen(var_name)) == 0)
            return (ft_strdup(env->value + ft_strlen(var_name) + 1));
        env = env->next;
    }
    return NULL;
}

// Updates the OLD_PWD environment variable to the current working directory
static int update_oldpwd(t_env *env) {
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return ERROR;
    char *oldpwd = ft_strjoin("OLDPWD=", cwd);
    if (!oldpwd)
        return ERROR;
    env_add(oldpwd, env);
    ft_memdel(oldpwd);
    return SUCCESS;
}

// Changes directory to HOME or OLDPWD based on the option (0 = HOME, 1 = OLDPWD)
static int change_to_env_path(int option, t_env *env) {
    const char *var_name = (option == 0) ? "HOME" : "OLDPWD";
    char *path = get_env_path(env, var_name);

    if (!path) {
        print_error(NULL);
        return ERROR;
    }
    if (option == 1)
        ft_putendl_fd(path, STDOUT_FILENO); // Print the path if OLDPWD

    update_oldpwd(env);
    int result = chdir(path);
    ft_memdel(path);
    return result;
}

int ft_cd(char **args, t_env *env) {
    if (!args[1])
        return change_to_env_path(0, env);  // No argument, go to HOME
    if (ft_strcmp(args[1], "-") == 0)
        return change_to_env_path(1, env);  // Go to OLDPWD

    update_oldpwd(env);
    int result = chdir(args[1]);
    if (result < 0)
        print_error(args[1]);
    return result;
}