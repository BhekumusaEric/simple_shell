#include "shell.h"

char *create_env_error_message(char **args);
char *create_alias_error_message(char **args);
char *create_exit_error_message(char **args);
char *create_cd_error_message(char **args);
char *create_syntax_error_message(char **args);

/**
 * create_env_error_message - Generates an error message for shell environment errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error message string.
 */
char *create_env_error_message(char **args)
{
    char *error, *hist_str;
    int len;

    hist_str = _itoa(hist);
    if (!hist_str)
        return (NULL);

    args--; // Decrementing args to access the command name.
    len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
    error = malloc(sizeof(char) * (len + 1));
    if (!error)
    {
        free(hist_str);
        return (NULL);
    }

    _strcpy(error, name);
    _strcat(error, ": ");
    _strcat(error, hist_str);
    _strcat(error, ": ");
    _strcat(error, args[0]);
    _strcat(error, ": Unable to add/remove from environment\n");

    free(hist_str);
    return (error);
}

/**
 * create_alias_error_message - Generates an error message for shell alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error message string.
 */
char *create_alias_error_message(char **args)
{
    char *error;
    int len;

    len = _strlen(name) + _strlen(args[0]) + 13;
    error = malloc(sizeof(char) * (len + 1));
    if (!error)
        return (NULL);

    _strcpy(error, "alias: ");
    _strcat(error, args[0]);
    _strcat(error, " not found\n");

    return (error);
}

/**
 * create_exit_error_message - Generates an error message for shell exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error message string.
 */
char *create_exit_error_message(char **args)
{
    char *error, *hist_str;
    int len;

    hist_str = _itoa(hist);
    if (!hist_str)
        return (NULL);

    len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 27;
    error = malloc(sizeof(char) * (len + 1));
    if (!error)
    {
        free(hist_str);
        return (NULL);
    }

    _strcpy(error, name);
    _strcat(error, ": ");
    _strcat(error, hist_str);
    _strcat(error, ": exit: Illegal number: ");
    _strcat(error, args[0]);
    _strcat(error, "\n");

    free(hist_str);
    return (error);
}

/**
 * create_cd_error_message - Generates an error message for shell cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error message string.
 */
char *create_cd_error_message(char **args)
{
    char *error, *hist_str;
    int len;

    hist_str = _itoa(hist);
    if (!hist_str)
        return (NULL);

    if (args[0][0] == '-')
        args[0][2] = '\0';
    len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
    error = malloc(sizeof(char) * (len + 1));
    if (!error)
    {
        free(hist_str);
        return (NULL);
    }

    _strcpy(error, name);
    _strcat(error, ": ");
    _strcat(error, hist_str);
    if (args[0][0] == '-')
        _strcat(error, ": cd: Illegal option ");
    else
        _strcat(error, ": cd: can't cd to ");
    _strcat(error, args[0]);
    _strcat(error, "\n");

    free(hist_str);
    return (error);
}

/**
 * create_syntax_error_message - Generates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error message string.
 */
char *create_syntax_error_message(char **args)
{
    char *error, *hist_str;
    int len;

    hist_str = _itoa(hist);
    if (!hist_str)
        return (NULL);

    len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
    error = malloc(sizeof(char) * (len + 1));
    if (!error)
    {
        free(hist_str);
        return (NULL);
    }

    _strcpy(error, name);
    _strcat(error, ": ");
    _strcat(error, hist_str);
    _strcat(error, ": Syntax error: \"");
    _strcat(error, args[0]);
    _strcat(error, "\" unexpected\n");

    free(hist_str);
    return (error);
}
