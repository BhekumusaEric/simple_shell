#include "shell.h"

void partition_line(char **line, ssize_t length);
ssize_t get_partitioned_line_length(char *line);
void handle_logical_operators(char *line, ssize_t *new_length);

/**
 * partition_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @length: The length of the line.
 *
 * Description: Inserts spaces to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void partition_line(char **line, ssize_t length)
{
    char *old_line, *new_line;
    char previous, current, next;
    size_t i, j;
    ssize_t new_length;

    new_length = get_partitioned_line_length(*line);
    if (new_length == length - 1)
        return;

    new_line = malloc(new_length + 1);
    if (!new_line)
        return;

    j = 0;
    old_line = *line;

    for (i = 0; old_line[i]; i++)
    {
        current = old_line[i];
        next = old_line[i + 1];

        if (i != 0)
        {
            previous = old_line[i - 1];

            if (current == ';')
            {
                if (next == ';' && previous != ' ' && previous != ';')
                {
                    new_line[j++] = ' ';
                    new_line[j++] = ';';
                    continue;
                }
                else if (previous == ';' && next != ' ')
                {
                    new_line[j++] = ';';
                    new_line[j++] = ' ';
                    continue;
                }

                if (previous != ' ')
                    new_line[j++] = ' ';
                new_line[j++] = ';';

                if (next != ' ')
                    new_line[j++] = ' ';
                continue;
            }
            else if (current == '&')
            {
                if (next == '&' && previous != ' ')
                    new_line[j++] = ' ';
                else if (previous == '&' && next != ' ')
                {
                    new_line[j++] = '&';
                    new_line[j++] = ' ';
                    continue;
                }
            }
            else if (current == '|')
            {
                if (next == '|' && previous != ' ')
                    new_line[j++] = ' ';
                else if (previous == '|' && next != ' ')
                {
                    new_line[j++] = '|';
                    new_line[j++] = ' ';
                    continue;
                }
            }
        }
        else if (current == ';')
        {
            if (i != 0 && old_line[i - 1] != ' ')
                new_line[j++] = ' ';
            new_line[j++] = ';';
            if (next != ' ' && next != ';')
                new_line[j++] = ' ';
            continue;
        }
        new_line[j++] = old_line[i];
    }
    new_line[j] = '\0';

    free(*line);
    *line = new_line;
}

/**
 * get_partitioned_line_length - Gets the new length of a line partitioned by ";", "||", "&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the partitioned line.
 *
 * Description: Truncates lines containing '#' comments with '\0'.
 */
ssize_t get_partitioned_line_length(char *line)
{
    size_t i;
    ssize_t new_length = 0;
    char current, next;

    for (i = 0; line[i]; i++)
    {
        current = line[i];
        next = line[i + 1];

        if (current == '#')
        {
            if (i == 0 || line[i - 1] == ' ')
            {
                line[i] = '\0';
                break;
            }
        }
        else if (i != 0)
        {
            if (current == ';')
            {
                if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
                {
                    new_length += 2;
                    continue;
                }
                else if (line[i - 1] == ';' && next != ' ')
                {
                    new_length += 2;
                    continue;
                }
                if (line[i - 1] != ' ')
                    new_length++;
                if (next != ' ')
                    new_length++;
            }
            else
                handle_logical_operators(&line[i], &new_length);
        }
        else if (current == ';')
        {
            if (i != 0 && line[i - 1] != ' ')
                new_length++;
            if (next != ' ' && next != ';')
                new_length++;
        }
        new_length++;
    }
    return new_length;
}

/**
 * handle_logical_operators - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_length: Pointer to the new_length in get_partitioned_line_length function.
 */
void handle_logical_operators(char *line, ssize_t *new_length)
{
    char previous, current, next;

    previous = *(line - 1);
    current = *line;
    next = *(line + 1);

    if (current == '&')
    {
        if (next == '&' && previous != ' ')
            (*new_length)++;
        else if (previous == '&' && next != ' ')
            (*new_length)++;
    }
    else if (current == '|')
    {
        if (next == '|' && previous != ' ')
            (*new_length)++;
        else if (previous == '|' && next != ' ')
            (*new_length)++;
    }
}
