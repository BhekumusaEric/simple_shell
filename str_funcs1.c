#include "shell.h"

/**
 * str_length - Computes the length of a string.
 * @s: A pointer to the input string.
 *
 * Return: The length of the input string.
 */
int str_length(const char *s)
{
	int length = 0;

	if (!s)
		return (length);

	for (length = 0; s[length]; length++)
		;
	return (length);
}

/**
 * str_copy - Copies the source string, including the
 *            null terminator, to the destination buffer.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination buffer.
 */
char *str_copy(char *dest, const char *src)
{
	size_t index;

	for (index = 0; src[index] != '\0'; index++)
		dest[index] = src[index];
	dest[index] = '\0';

	return (dest);
}

/**
 * str_concat - Concatenates two strings.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *str_concat(char *dest, const char *src)
{
	char *dest_temp;
	const char *src_temp;

	dest_temp = dest;
	src_temp = src;

	while (*dest_temp != '\0')
		dest_temp++;

	while (*src_temp != '\0')
		*dest_temp++ = *src_temp++;
	*dest_temp = '\0';

	return (dest);
}

/**
 * str_nconcat - Concatenates two strings with a limit on the number
 *               of bytes copied from the source string.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 * @n: Number of bytes to copy from src.
 *
 * Return: Pointer to the destination string.
 */
char *str_nconcat(char *dest, const char *src, size_t n)
{
	size_t dest_length = str_length(dest);
	size_t index;

	for (index = 0; index < n && src[index] != '\0'; index++)
		dest[dest_length + index] = src[index];
	dest[dest_length + index] = '\0';

	return (dest);
}
