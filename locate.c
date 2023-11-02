#include "shell.h"

char *locate_command_in_path(char *command);
char *generate_full_path(char *path);
list_t *split_path_directories(char *path);

/**
 * locate_command_in_path - Locates a command in the PATH environment variable.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *locate_command_in_path(char *command)
{
    char **path_env, *temp;
    list_t *dirs, *head;
    struct stat st;

    path_env = _getenv("PATH");
    if (!path_env || !(*path_env))
        return NULL;

    dirs = split_path_directories(*path_env + 5); // Skip "PATH=" prefix
    head = dirs;

    while (dirs)
    {
        temp = generate_full_path(dirs->dir, command);
        if (!temp)
            return NULL;

        if (stat(temp, &st) == 0)
        {
            free_list(head);
            return temp;
        }

        dirs = dirs->next;
        free(temp);
    }

    free_list(head);

    return NULL;
}

/**
 * generate_full_path - Generates the full path for a command in a directory.
 * @dir: The directory containing the command.
 * @command: The command to locate.
 *
 * Return: A dynamically allocated string containing the full path.
 */
char *generate_full_path(char *dir, char *command)
{
    char *full_path;
    int dir_len = _strlen(dir);
    int command_len = _strlen(command);

    full_path = malloc(sizeof(char) * (dir_len + command_len + 2));
    if (!full_path)
        return NULL;

    _strcpy(full_path, dir);
    _strcat(full_path, "/");
    _strcat(full_path, command);

    return full_path;
}

/**
 * split_path_directories - Tokenizes a colon-separated list of directories into a linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *split_path_directories(char *path)
{
    int index;
    char **dirs, *path_copy;
    list_t *head = NULL;

    path_copy = fill_path_dir(path);
    if (!path_copy)
        return NULL;
    dirs = _strtok(path_copy, ":");
    free(path_copy);
    if (!dirs)
        return NULL;

    for (index = 0; dirs[index]; index++)
    {
        if (add_node_end(&head, dirs[index]) == NULL)
        {
            free_list(head);
            free(dirs);
            return NULL;
        }
    }

    free(dirs);

    return head;
}
