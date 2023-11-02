#include "shell.h"

int file_open_error(char *file_path);
int process_file_commands(char *file_path, int *execution_return);

/**
 * file_open_error - Prints an error message when a file cannot be opened.
 * @file_path: Path to the file that couldn't be opened.
 *
 * Return: 127.
 */
int file_open_error(char *file_path)
{
	char *error_message, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error_message = malloc(sizeof(char) * (len + 1));
	if (!error_message)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error_message, name);
	_strcat(error_message, ": ");
	_strcat(error_message, hist_str);
	_strcat(error_message, ": Can't open ");
	_strcat(error_message, file_path);
	_strcat(error_message, "\n");

	free(hist_str);
	write(STDERR_FILENO, error_message, len);
	free(error_message);
	return (127);
}

/**
 * process_file_commands - Reads and processes commands from a file.
 * @file_path: Path to the file containing commands.
 * @execution_return: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise, the return value of the last executed command.
 */
int process_file_commands(char *file_path, int *execution_return)
{
	ssize_t file_descriptor, bytes_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file_descriptor = open(file_path, O_RDONLY);
	if (file_descriptor == -1)
	{
		*execution_return = file_open_error(file_path);
		return (*execution_return);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		bytes_read = read(file_descriptor, buffer, 119);
		if (bytes_read == 0 && line_size == 0)
			return (*execution_return);
		buffer[bytes_read] = '\0';
		line_size += bytes_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (bytes_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, execution_return);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*execution_return = 2;
		free_args(args, args);
		return (*execution_return);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, front, execution_return);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_args(args, front, execution_return);

	free(front);
	return (ret);
}
