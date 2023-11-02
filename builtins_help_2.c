#include "shell.h"

void display_help_env(void);
void display_help_setenv(void);
void display_help_unsetenv(void);
void display_help_history(void);

/**
 * display_help_env - Shows information about the shellby builtin command 'env'.
 */
void display_help_env(void)
{
    char *env_info = "env: env\n\tDisplays the current environment settings.\n";

    write(STDOUT_FILENO, env_info, _strlen(env_info));
}

/**
 * display_help_setenv - Provides information about the shellby builtin command 'setenv'.
 */
void display_help_setenv(void)
{
    char *setenv_info = "setenv: setenv [VARIABLE] [VALUE]\n\tCreates a new";
    write(STDOUT_FILENO, setenv_info, _strlen(setenv_info));
    setenv_info = "environment variable or updates an existing one.\n\n";
    write(STDOUT_FILENO, setenv_info, _strlen(setenv_info));
    setenv_info = "\tIn case of an error, a message is sent to stderr.\n";
    write(STDOUT_FILENO, setenv_info, _strlen(setenv_info));
}

/**
 * display_help_unsetenv - Provides information about the shellby builtin command 'unsetenv'.
 */
void display_help_unsetenv(void)
{
    char *unsetenv_info = "unsetenv: unsetenv [VARIABLE]\n\tDeletes an ";
    write(STDOUT_FILENO, unsetenv_info, _strlen(unsetenv_info));
    unsetenv_info = "environmental variable.\n\n\tIn case of an error, a ";
    write(STDOUT_FILENO, unsetenv_info, _strlen(unsetenv_info));
    unsetenv_info = "message is sent to stderr.\n";
    write(STDOUT_FILENO, unsetenv_info, _strlen(unsetenv_info));
}
