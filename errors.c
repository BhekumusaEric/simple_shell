#include "shell.h"

int get_number_length(int num);
char *convert_integer_to_string(int num);
int handle_error(char **args, int err);

/**
 * get_number_length - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int get_number_length(int num)
{
	unsigned int num1;
	int length = 1;

	if (num < 0)
	{
		length++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		length++;
		num1 /= 10;
	}

	return length;
}

/**
 * convert_integer_to_string - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *convert_integer_to_string(int num)
{
	char *buffer;
	int length = get_number_length(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return NULL;

	buffer[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length--;
	do {
		buffer[length] = (num1 % 10) + '0';
		num1 /= 10;
		length--;
	} while (num1 > 0);

	return buffer;
}

/**
 * handle_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int handle_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = create_env_error_message(args);
		break;
	case 1:
		error = create_alias_error_message(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = create_exit_error_message(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = create_syntax_error_message(args);
		else
			error = create_cd_error_message(args);
		break;
	case 126:
		error = create_permission_denied_error_message(args);
		break;
	case 127:
		error = create_command_not_found_error_message(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return err;
}
