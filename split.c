#include "shell.h"

/**
 * token_length - Finds the length of the token delimited by a character.
 * @str: The string to search.
 * @delim: The delimiter character.
 *
 * Return: The length of the initial token up to the delimiter in the string.
 */
int token_length(char *str, char *delim)
{
	int idx = 0, length = 0;

	while (*(str + idx) && *(str + idx) != *delim)
	{
		length++;
		idx++;
	}

	return (length);
}

/**
 * count_tokens - Counts the number of words delimited by a character in a string.
 * @str: The string to examine.
 * @delim: The delimiter character.
 *
 * Return: The count of words within the string.
 */
int count_tokens(char *str, char *delim)
{
	int idx, token_count = 0, str_length = 0;

	for (idx = 0; *(str + idx); idx++)
		str_length++;

	for (idx = 0; idx < str_length; idx++)
	{
		if (*(str + idx) != *delim)
		{
			token_count++;
			idx += token_length(str + idx, delim);
		}
	}

	return (token_count);
}

/**
 * _str_tokenize - Tokenizes a string into words.
 * @line: The string to tokenize.
 * @delim: The delimiter character for tokenization.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_str_tokenize(char *line, char *delim)
{
	char **tokens;
	int idx = 0, token_count, t, letters, l;

	token_count = count_tokens(line, delim);
	if (token_count == 0)
		return (NULL);

	tokens = malloc(sizeof(char *) * (token_count + 2));
	if (!tokens)
		return (NULL);

	for (t = 0; t < token_count; t++)
	{
		while (line[idx] == *delim)
			idx++;

		letters = token_length(line + idx, delim);

		tokens[t] = malloc(sizeof(char) * (letters + 1));
		if (!tokens[t])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(tokens[idx]);
			free(tokens);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			tokens[t][l] = line[idx];
			idx++;
		}

		tokens[t][l] = '\0';
	}
	tokens[t] = NULL;
	tokens[t + 1] = NULL;

	return (tokens);
}
