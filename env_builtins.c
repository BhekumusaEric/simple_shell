#include "shell.h"

int print_environment(char **arguments, char __attribute__((__unused__)) **front);
int set_environment(char **arguments, char __attribute__((__unused__)) **front);
int unset_environment(char **arguments, char __attribute__((__unused__)) **front);

/**
 * print_environment - Prints the current environment.
 * @arguments: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of arguments.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int print_environment(char **arguments, char __attribute__((__unused__)) **front)
{
    int index;
    char new_line = '\n';

    if (!environ)
        return (-1);

    for (index = 0; environ[index]; index++)
    {
        write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
        write(STDOUT_FILENO, &new_line, 1);
    }

    (void)arguments;
    return (0);
}

/**
 * set_environment - Changes or adds an environmental variable to the PATH.
 * @arguments: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of arguments.
 * Description: arguments[1] is the name of the new or existing PATH variable.
 *              arguments[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int set_environment(char **arguments, char __attribute__((__unused__)) **front)
{
    char **env_variable = NULL, **new_environ, *new_value;
    size_t size;
    int index;

    if (!arguments[0] || !arguments[1])
        return (create_error(arguments, -1));

    new_value = malloc(_strlen(arguments[0]) + 1 + _strlen(arguments[1]) + 1);
    if (!new_value)
        return (create_error(arguments, -1));
    _strcpy(new_value, arguments[0]);
    _strcat(new_value, "=");
    _strcat(new_value, arguments[1]);

    env_variable = _getenv(arguments[0]);
    if (env_variable)
    {
        free(*env_variable);
        *env_variable = new_value;
        return (0);
    }
    for (size = 0; environ[size]; size++)
        ;

    new_environ = malloc(sizeof(char *) * (size + 2));
    if (!new_environ)
    {
        free(new_value);
        return (create_error(arguments, -1));
    }

    for (index = 0; environ[index]; index++)
        new_environ[index] = environ[index];

    free(environ);
    environ = new_environ;
    environ[index] = new_value;
    environ[index + 1] = NULL;

    return (0);
}

/**
 * unset_environment - Deletes an environmental variable from the PATH.
 * @arguments: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of arguments.
 * Description: arguments[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int unset_environment(char **arguments, char __attribute__((__unused__)) **front)
{
    char **env_variable, **new_environ;
    size_t size;
    int index, index2;

    if (!arguments[0])
        return (create_error(arguments, -1));
    env_variable = _getenv(arguments[0]);
    if (!env_variable)
        return (0);

    for (size = 0; environ[size]; size++)
        ;

    new_environ = malloc(sizeof(char *) * size);
    if (!new_environ)
        return (create_error(arguments, -1));

    for (index = 0, index2 = 0; environ[index]; index++)
    {
        if (*env_variable == environ[index])
        {
            free(*env_variable);
            continue;
        }
        new_environ[index2] = environ[index];
        index2++;
    }
    free(environ);
    environ = new_environ;
    environ[size - 1] = NULL;

    return (0);
}
