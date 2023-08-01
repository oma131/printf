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
 * @plus_flag: A flag indicating whether the + flag is set.
 * @space_flag: A flag indicating whether the space flag is set.
 * Return: The number of digits printed.
 */
int _print_number(long int n, char *buffer, int *index, int plus_flag, int space_flag)
{
    int count = 0;

    if (n < 0)
    {
        buffer[(*index)++] = '-';
        n = -n;
    }
    else if (plus_flag)
    {
        buffer[(*index)++] = '+';
    }
    else if (space_flag)
    {
        buffer[(*index)++] = ' ';
    }

    if (n / 10)
        count += _print_number(n / 10, buffer, index, 0, 0);

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
int _print_unsigned_number(unsigned long int n, char *buffer, int *index)
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
int _print_hex(unsigned long int n, int uppercase, char *buffer, int *index)
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
    int plus_flag = 0;
    int space_flag = 0;

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            // Check for flags
            plus_flag = 0;
            space_flag = 0;
            while (*format == '+' || *format == ' ')
            {
                if (*format == '+')
                    plus_flag = 1;
                else if (*format == ' ')
                    space_flag = 1;
                format++;
            }

            // Check for length modifiers
            int long_flag = 0;
            int long_long_flag = 0;
            int short_flag = 0;
            while (*format == 'l' || *format == 'h')
            {
                if (*format == 'l')
                {
                    long_flag++;
                    if (long_flag > 2)
                        long_flag = 2;
                }
                else if (*format == 'h')
                {
                    short_flag++;
                    if (short_flag > 2)
                        short_flag = 2;
                }
                format++;
            }

            switch (*format)
            {
                // ...

                case 'd':
                case 'i':
                    if (long_flag == 2)
                        count += _print_number(va_arg(args, long long), buffer, &index, plus_flag, space_flag);
                    else if (long_flag == 1)
                        count += _print_number(va_arg(args, long), buffer, &index, plus_flag, space_flag);
                    else if (short_flag == 2)
                        count += _print_number((short)va_arg(args, int), buffer, &index, plus_flag, space_flag);
                    else if (short_flag == 1)
                        count += _print_number((signed char)va_arg(args, int), buffer, &index, plus_flag, space_flag);
                    else
                        count += _print_number(va_arg(args, int), buffer, &index, plus_flag, space_flag);
                    break;
                case 'u':
                    if (long_flag == 2)
                        count += _print_unsigned_number(va_arg(args, unsigned long long), buffer, &index);
                    else if (long_flag == 1)
                        count += _print_unsigned_number(va_arg(args, unsigned long), buffer, &index);
                    else if (short_flag == 2)
                        count += _print_unsigned_number((unsigned short)va_arg(args, unsigned int), buffer, &index);
                    else if (short_flag == 1)
                        count += _print_unsigned_number((unsigned char)va_arg(args, unsigned int), buffer, &index);
                    else
                        count += _print_unsigned_number(va_arg(args, unsigned int), buffer, &index);
                    break;
                case 'o':
                    if (long_flag == 2)
                        count += _print_number_base(va_arg(args, unsigned long long), 8, buffer, &index, 0, space_flag);
                    else if (long_flag == 1)
                        count += _print_number_base(va_arg(args, unsigned long), 8, buffer, &index, 0, space_flag);
                    else if (short_flag == 2)
                        count += _print_number_base((unsigned short)va_arg(args, unsigned int), 8, buffer, &index, 0, space_flag);
                    else if (short_flag == 1)
                        count += _print_number_base((unsigned char)va_arg(args, unsigned int), 8, buffer, &index, 0, space_flag);
                    else
                        count += _print_number_base(va_arg(args, unsigned int), 8, buffer, &index, 0, space_flag);
                    break;
                case 'x':
                    if (long_flag == 2)
                        count += _print_hex(va_arg(args, unsigned long long), 0, buffer, &index);
                    else if (long_flag == 1)
                        count += _print_hex(va_arg(args, unsigned long), 0, buffer, &index);
                    else if (short_flag == 2)
                        count += _print_hex((unsigned short)va_arg(args, unsigned int), 0, buffer, &index);
                    else if (short_flag == 1)
                        count += _print_hex((unsigned char)va_arg(args, unsigned int), 0, buffer, &index);
                    else
                        count += _print_hex(va_arg(args, unsigned int), 0, buffer, &index);
                    break;
                case 'X':
                    if (long_flag == 2)
                        count += _print_hex(va_arg(args, unsigned long long), 1, buffer, &index);
                    else if (long_flag == 1)
                        count += _print_hex(va_arg(args, unsigned long), 1, buffer, &index);
                    else if (short_flag == 2)
                        count += _print_hex((unsigned short)va_arg(args, unsigned int), 1, buffer, &index);
                    else if (short_flag == 1)
                        count += _print_hex((unsigned char)va_arg(args, unsigned int), 1, buffer, &index);
                    else
                        count += _print_hex(va_arg(args, unsigned int), 1, buffer, &index);
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
