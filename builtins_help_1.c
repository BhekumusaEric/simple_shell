#include "shell.h"

void display_available_commands(void);
void display_alias_command_info(void);
void display_cd_command_info(void);
void display_exit_command_info(void);
void display_help_command_info(void);

/**
 * display_available_commands - Lists all available shellby commands.
 */
void display_available_commands(void)
{
    char *message = "Shellby\nThese are the built-in shell commands:\n";

    write(STDOUT_FILENO, message, _strlen(message));
    message = "Type 'help' to see this list.\nType 'help <command>' to learn ";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "more about a specific command.\n\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  alias    \tManage command aliases\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  cd       \tChange the current directory\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  exit     \tExit the shell\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  help     \tDisplay help information\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  env      \tDisplay environment variables\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  setenv   \tSet environment variables\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  unsetenv \tUnset environment variables\n";
    write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * display_alias_command_info - Display information about the 'alias' command.
 */
void display_alias_command_info(void)
{
    char *message = "alias: alias [NAME[='VALUE'] ...]\n\tManage command aliases.\n";

    write(STDOUT_FILENO, message, _strlen(message));
    message = "  - alias: Prints a list of all aliases in the format NAME='VALUE'.\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  - alias <name1> <name2> ...: Print aliases for specified names.\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  - alias NAME='VALUE' [...]: Define or update aliases.\n";
    write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * display_cd_command_info - Display information about the 'cd' command.
 */
void display_cd_command_info(void)
{
    char *message = "cd: cd [DIRECTORY]\n\tChange the current directory.\n";

    write(STDOUT_FILENO, message, _strlen(message));
    message = "  - If no argument is given, it goes to $HOME.\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  - If the argument is '-', it goes to $OLDPWD.\n";
    write(STDOUT_FILENO, message, _strlen(message));
    message = "  - The environment variables PWD and OLDPWD are updated.\n";
    write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * display_exit_command_info - Display information about the 'exit' command.
 */
void display_exit_command_info(void)
{
    char *message = "exit: exit [STATUS]\n\tExit the shell with an optional status.\n";

    write(STDOUT_FILENO, message, _strlen(message));
    message = "  - If no status is given, it exits with status 0.\n";
    write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * display_help_command_info - Display information about the 'help' command.
 */
void display_help_command_info(void)
{
    char *message = "help: help\n\tShow available Shellby commands.\n";

    write(STDOUT_FILENO, message, _strlen(message));
    message = "  - 'help <command>' for detailed information on a command.\n";
    write(STDOUT_FILENO, message, _strlen(message));
}
