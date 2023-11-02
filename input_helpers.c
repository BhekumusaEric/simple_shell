#include "shell.h"

char *read_command(int *exit_status);
int execute_command(char **command, char **command_start, int *exit_status);
int handle_sequential_commands(char **commands, char **command_start, int *exit_status);
int check_leading_operators(char **commands);

/**
 * read_command - Reads a command from standard input.
 * @exit_status: A pointer to the exit status of the previous command.
 *
 * Return: If an error occurs or end-of-file is reached - NULL.
 *         Otherwise - a pointer to the command read from standard input.
 */
char *read_command(int *exit_status)
{
    size_t n = 0;
    ssize_t read;
    char *prompt = "$ ";
    char *command = NULL;

    if (command)
        free(command);

    read = _getline(&command, &n, STDIN_FILENO);
    if (read == -1)
        return (NULL);

    if (read == 1)
    {
        hist++;
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, prompt, 2);
        return read_command(exit_status);
    }

    command[read - 1] = '\0';
    variable_replacement(&command, exit_status);
    handle_line(&command, read);

    return command;
}

/**
 * execute_command - Executes a single command.
 * @command: An array of arguments for the command.
 * @command_start: A pointer to the beginning of the command array.
 * @exit_status: A pointer to the exit status of the previous command.
 *
 * Return: The exit status of the executed command.
 */
int execute_command(char **command, char **command_start, int *exit_status)
{
    int ret;
    int (*builtin)(char **command, char **command_start);

    builtin = get_builtin(command[0]);

    if (builtin)
    {
        ret = builtin(command + 1, command_start);
        if (ret != EXIT)
            *exit_status = ret;
    }
    else
    {
        *exit_status = execute(command, command_start);
        ret = *exit_status;
    }

    hist++;

    for (size_t i = 0; command[i]; i++)
        free(command[i]);

    return ret;
}

/**
 * handle_sequential_commands - Handles sequential command execution.
 * @commands: An array of commands to execute.
 * @command_start: A pointer to the beginning of the commands array.
 * @exit_status: A pointer to the exit status of the previous command.
 *
 * Return: The exit status of the last executed command.
 */
int handle_sequential_commands(char **commands, char **command_start, int *exit_status)
{
    int ret = 0;
    size_t index;

    if (!commands[0])
        return *exit_status;

    for (index = 0; commands[index]; index++)
    {
        if (_strncmp(commands[index], "||", 2) == 0)
        {
            free(commands[index]);
            commands[index] = NULL;
            commands = replace_aliases(commands);
            ret = execute_command(commands, command_start, exit_status);

            if (*exit_status != 0)
            {
                commands = &commands[++index];
                index = 0;
            }
            else
            {
                for (index++; commands[index]; index++)
                    free(commands[index]);

                return ret;
            }
        }
        else if (_strncmp(commands[index], "&&", 2) == 0)
        {
            free(commands[index]);
            commands[index] = NULL;
            commands = replace_aliases(commands);
            ret = execute_command(commands, command_start, exit_status);

            if (*exit_status == 0)
            {
                commands = &commands[++index];
                index = 0;
            }
            else
            {
                for (index++; commands[index]; index++)
                    free(commands[index]);

                return ret;
            }
        }
    }

    commands = replace_aliases(commands);
    ret = execute_command(commands, command_start, exit_status);

    return ret;
}

/**
 * check_leading_operators - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @commands: An array of commands.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 * Otherwise - 0.
 */
int check_leading_operators(char **commands)
{
    size_t i;
    char *cur, *next;

    for (i = 0; commands[i]; i++)
    {
        cur = commands[i];

        if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
        {
            if (i == 0 || cur[1] == ';')
                return create_error(&commands[i], 2);

            next = commands[i + 1];
            if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
                return create_error(&commands[i + 1], 2);
        }
    }

    return 0;
}
