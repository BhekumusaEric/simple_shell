#include "shell.h"

/**
 * _str_char - Finds the first occurrence of a character in a string.
 * @s: The string to search.
 * @c: The character to locate.
 *
 * Return: A pointer to the first occurrence of 'c' in 's', or NULL if not found.
 */
char *_str_char(char *s, char c)
{
	int index;

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

	return (NULL);
}

/**
 * _str_span - Computes the length of a prefix substring consisting of accepted characters.
 * @s: The string to search.
 * @accept: The characters to count in the prefix.
 *
 * Return: The number of characters at the beginning of 's' that belong to 'accept'.
 */
int _str_span(char *s, char *accept)
{
	int count = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				count++;
				break;
			}
		}
		s++;
	}
	return (count);
}

/**
 * _str_compare - Compares two strings.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: A positive byte difference if s1 > s2, 0 if s1 = s2, or a negative byte difference if s1 < s2.
 */
int _str_compare(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _str_ncompare - Compare two strings up to a specified number of bytes.
 * @s1: Pointer to the first string.
 * @s2: Pointer to the second string.
 * @n: The number of bytes to compare.
 *
 * Return: A value less than 0 if s1 is shorter than s2, 0 if s1 and s2 match, or greater than 0 if s1 is longer than s2.
 */
int _str_ncompare(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
