#include "shell.h"

void free_command_arguments(char **args, char **front);
char *get_current_pid(void);
char *get_environment_variable_value(char *variable, int length);
void replace_variables(char **line, int *execution_status);

/**
 * free_command_arguments - Frees up memory taken by command arguments.
 * @args: A null-terminated double pointer containing command and arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_command_arguments(char **args, char **front)
{
    size_t i;

    for (i = 0; args[i] || args[i + 1]; i++)
        free(args[i]);

    free(front);
}

/**
 * get_current_pid - Gets the current process ID.
 *
 * Return: The current process ID as a string or NULL on failure.
 *
 * Description: Reads the process ID from the /proc/self/stat file and
 * returns it as a string.
 */
char *get_current_pid(void)
{
    size_t i = 0;
    char *buffer;
    ssize_t file;

    file = open("/proc/self/stat", O_RDONLY);
    if (file == -1)
    {
        perror("Cannot read file");
        return NULL;
    }

    buffer = malloc(120);
    if (!buffer)
    {
        close(file);
        return NULL;
    }

    read(file, buffer, 120);

    while (buffer[i] != ' ')
        i++;

    buffer[i] = '\0';

    close(file);
    return buffer;
}

/**
 * get_environment_variable_value - Gets the value of an environmental variable.
 * @variable: The environmental variable to search for.
 * @length: The length of the environmental variable.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Environmental variables are stored in the format "VARIABLE=VALUE".
 */
char *get_environment_variable_value(char *variable, int length)
{
    char **var_address;
    char *replacement = NULL, *temp, *var;

    var = malloc(length + 1);
    if (!var)
        return NULL;
    var[0] = '\0';
    _strncat(var, variable, length);

    var_address = _getenv(var);
    free(var);

    if (var_address)
    {
        temp = *var_address;
        while (*temp != '=')
            temp++;

        temp++;

        replacement = malloc(_strlen(temp) + 1);
        if (replacement)
            _strcpy(replacement, temp);
    }

    return replacement;
}

/**
 * replace_variables - Handles variable replacement in the command line.
 * @line: A double pointer containing the command and arguments.
 * @execution_status: A pointer to the return value of the last executed command.
 *
 * Description: Replaces "$$" with the current PID, "$?" with the return value
 * of the last executed program, and environmental variables preceded by "$"
 * with their corresponding values.
 */
void replace_variables(char **line, int *execution_status)
{
    int j, k = 0, length;
    char *replacement = NULL, *old_line = NULL, *new_line;

    old_line = *line;

    for (j = 0; old_line[j]; j++)
    {
        if (old_line[j] == '$' && old_line[j + 1] && old_line[j + 1] != ' ')
        {
            if (old_line[j + 1] == '$')
            {
                replacement = get_current_pid();
                k = j + 2;
            }
            else if (old_line[j + 1] == '?')
            {
                replacement = _itoa(*execution_status);
                k = j + 2;
            }
            else if (old_line[j + 1])
            {
                for (k = j + 1; old_line[k] && old_line[k] != '$' && old_line[k] != ' '; k++)
                    ;

                length = k - (j + 1);
                replacement = get_environment_variable_value(&old_line[j + 1], length);
            }

            new_line = malloc(j + _strlen(replacement) + _strlen(&old_line[k]) + 1);

            if (!new_line)
                return;

            new_line[0] = '\0';
            _strncat(new_line, old_line, j);

            if (replacement)
            {
                _strcat(new_line, replacement);
                free(replacement);
                replacement = NULL;
            }

            _strcat(new_line, &old_line[k]);
            free(old_line);
            *line = new_line;
            old_line = new_line;
            j = -1;
        }
    }
}
