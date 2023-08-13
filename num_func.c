#include "shell.h"

unsigned len_int(int n);
char *_itoa(int n);

/**
 * digitlen - Counts the length of a digit
 * @n: The number to count
 *
 * Return: Returns (len) ie the digit length
 */
unsigned len_int(int n)
{
	unsigned int num;
	unsigned int len = 0;

	if (n < 0)
	{
		len++;
		num = n * -1;
	}
	else
	{
		num = n;
	}
	while (num > 9)
	{
		len++;
		num /= 10;
	}
	return (len);
}

/**
 * _itoa - Converts an integer to a string
 * @n: The integer to convert
 *
 * Return: On SUCCESS, returns (str) ie the converted string
 *	   On FAILURE, returns (NULL)
 */
char *_itoa(int n)
{
	unsigned int len;
	unsigned int num;
	unsigned int buffer;
	char *str;

	len = len_int(n);
	buffer = len + 1;

	str = malloc(sizeof(*str) * (buffer + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		num = n * -1;
		str[0] = '-';
	}
	else
	{
		num = n;
	}

	while (num > 0)
	{
		str[len]= (num % 10) + '0';
		num /= 10;
		len--;
	}
	str[buffer] = '\0';

	return (str);
}
