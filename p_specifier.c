#include <unistd.h>
#include <stdarg.h>
#include "main.h"

/**
 * _putchar - Writes a character to stdout.
 * @c: The character to print.
 * Return: 1 on success, -1 on error.
 */
int _putchar(char c)
{
    return write(1, &c, 1);
}

/**
 * _print_number - Prints an integer using _putchar.
 * @n: The integer to print.
 * @buffer: The local buffer to store characters.
 * @index: The index to insert the character in the buffer.
 * Return: The number of digits printed.
 */
int _print_number(int n, char *buffer, int *index)
{
    int count = 0;

    if (n < 0)
    {
        buffer[(*index)++] = '-';
        n = -n;
    }

    if (n / 10)
        count += _print_number(n / 10, buffer, index);

    buffer[(*index)++] = (n % 10) + '0';
    count++;

    return count;
}

/**
 * _print_unsigned_number - Prints an unsigned integer using _putchar.
 * @n: The unsigned integer to print.
 * @buffer: The local buffer to store characters.
 * @index: The index to insert the character in the buffer.
 * Return: The number of digits printed.
 */
int _print_unsigned_number(unsigned int n, char *buffer, int *index)
{
    int count = 0;

    if (n / 10)
        count += _print_unsigned_number(n / 10, buffer, index);

    buffer[(*index)++] = (n % 10) + '0';
    count++;

    return count;
}

/**
 * _print_hex - Prints an unsigned integer in hexadecimal format.
 * @n: The unsigned integer to print in hexadecimal.
 * @uppercase: A flag to print uppercase hexadecimal letters (X).
 * @buffer: The local buffer to store characters.
 * @index: The index to insert the character in the buffer.
 * Return: The number of characters printed.
 */
int _print_hex(unsigned int n, int uppercase, char *buffer, int *index)
{
    int count = 0;
    char hex_digits[] = "0123456789abcdef";
    if (uppercase)
        hex_digits = "0123456789ABCDEF";

    if (n / 16)
        count += _print_hex(n / 16, uppercase, buffer, index);

    buffer[(*index)++] = hex_digits[n % 16];
    count++;

    return count;
}

/**
 * _print_address - Prints a pointer address in hexadecimal format.
 * @ptr: The pointer to print.
 * @buffer: The local buffer to store characters.
 * @index: The index to insert the character in the buffer.
 * Return: The number of characters printed.
 */
int _print_address(void *ptr, char *buffer, int *index)
{
    int count = 0;
    unsigned long int address = (unsigned long int)ptr;
    buffer[(*index)++] = '0';
    buffer[(*index)++] = 'x';
    count += 2;
    count += _print_hex(address, 1, buffer, index);
    return count;
}

/**
 * _printf - Custom printf function that handles %c, %s, %d, %i, %u, %o, %x, %X, %S, and %p specifiers.
 * @format: The format string.
 *
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char buffer[1024];
    int index = 0;

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                // ...

                case 'p':
                    count += _print_address(va_arg(args, void *), buffer, &index);
                    break;
                case '%':
                    buffer[index++] = '%';
                    count++;
                    break;
                default:
                    buffer[index++] = '%';
                    buffer[index++] = *format;
                    count += 2;
                    break;
            }
        }
        else
        {
            buffer[index++] = *format;
            count++;
        }

        // Flush buffer to stdout if it's full or at the end of the format string
        if (index >= 1023 || *(format + 1) == '\0')
        {
            buffer[index] = '\0';
            count -= write(1, buffer, index);
            index = 0;
        }

        format++;
    }

    va_end(args);

    return count;
}
