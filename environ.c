#include "shell.h"

char **duplicate_environment(void);
void release_environment(void);
char **find_environment_variable(const char *variable_name);

/**
 * duplicate_environment - Creates a duplicate of the environment.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a double pointer to the duplicated environment.
 */
char **duplicate_environment(void)
{
    char **new_environment;
    size_t size;
    int index;

    for (size = 0; environ[size]; size++)
        ;

    new_environment = malloc(sizeof(char *) * (size + 1));
    if (!new_environment)
        return (NULL);

    for (index = 0; environ[index]; index++)
    {
        new_environment[index] = malloc(_strlen(environ[index]) + 1);

        if (!new_environment[index])
        {
            for (index--; index >= 0; index--)
                free(new_environment[index]);
            free(new_environment);
            return (NULL);
        }
        _strcpy(new_environment[index], environ[index]);
    }
    new_environment[index] = NULL;

    return new_environment;
}

/**
 * release_environment - Frees the duplicated environment.
 */
void release_environment(void)
{
    int index;

    for (index = 0; environ[index]; index++)
        free(environ[index]);
    free(environ);
}

/**
 * find_environment_variable - Retrieves an environmental variable from the environment.
 * @variable_name: The name of the environmental variable to retrieve.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **find_environment_variable(const char *variable_name)
{
    int index, length;

    length = _strlen(variable_name);
    for (index = 0; environ[index]; index++)
    {
        if (_strncmp(variable_name, environ[index], length) == 0)
            return (&environ[index]);
    }

    return NULL;
}
