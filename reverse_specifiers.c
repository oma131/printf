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
 * _print_string - Prints a string with handling the width and precision.
 * @str: The string to print.
 * @buffer: The local buffer to store characters.
 * @index: The index to insert the character in the buffer.
 * @width: The field width for padding.
 * @precision: The precision for string conversions.
 * @minus_flag: A flag indicating whether the - flag is set.
 * Return: The number of characters printed.
 */
int _print_string(char *str, char *buffer, int *index, int width, int precision, int minus_flag)
{
    int count = 0;
    int len = _strlen(str);
    int padding = 0;

    if (precision >= 0 && precision < len)
        len = precision;

    if (width > 0)
    {
        padding = width - len;

        while (padding > 0)
        {
            buffer[(*index)++] = minus_flag ? ' ' : '0';
            padding--;
            count++;
        }
    }

    for (int i = 0; i < len; i++)
    {
        buffer[(*index)++] = str[i];
        count++;
    }

    if (width > 0 && minus_flag)
    {
        while (padding > 0)
        {
            buffer[(*index)++] = ' ';
            padding--;
            count++;
        }
    }

    return count;
}

/**
 * _print_number - Prints an integer using _putchar.
 * @n: The integer to print.
 * @buffer: The local buffer to store characters.
 * @index: The index to insert the character in the buffer.
 * @width: The field width for padding.
 * @precision: The precision for numeric conversions.
 * @plus_flag: A flag indicating whether the + flag is set.
 * @space_flag: A flag indicating whether the space flag is set.
 * @zero_flag: A flag indicating whether the 0 flag is set.
 * @minus_flag: A flag indicating whether the - flag is set.
 * Return: The number of digits printed.
 */
int _print_number(long int n, char *buffer, int *index, int width, int precision, int plus_flag, int space_flag, int zero_flag, int minus_flag)
{
    // Implementation of _print_number remains the same as before...
}

// Other conversion functions (e.g., _print_unsigned_number, _print_hex, _print_pointer) remain the same as before...

/**
 * _print_reversed_string - Prints a reversed string.
 * @str: The string to reverse and print.
 * @buffer: The local buffer to store characters.
 * @index: The index to insert the character in the buffer.
 * Return: The number of characters printed.
 */
int _print_reversed_string(char *str, char *buffer, int *index)
{
    int count = 0;
    int len = _strlen(str);

    for (int i = len - 1; i >= 0; i--)
    {
        buffer[(*index)++] = str[i];
        count++;
    }

    return count;
}

/**
 * _printf - Custom printf function that handles %c, %s, %d, %i, %u, %o, %x, %X, %S, %p, and %r specifiers.
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
    int zero_flag = 0;
    int minus_flag = 0;
    int width = 0;
    int precision = -1; // -1 indicates no precision specified

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            // Check for flags, width, and precision
            plus_flag = 0;
            space_flag = 0;
            zero_flag = 0;
            minus_flag = 0;
            width = 0;
            precision = -1;
            while (*format == '+' || *format == ' ' || *format == '0' || *format == '-' || (*format >= '0' && *format <= '9') || *format == '.')
            {
                if (*format == '+')
                    plus_flag = 1;
                else if (*format == ' ')
                    space_flag = 1;
                else if (*format == '0')
                    zero_flag = 1;
                else if (*format == '-')
                    minus_flag = 1;
                else if (*format >= '0' && *format <= '9')
                {
                    if (precision == -1)
                        width = width * 10 + (*format - '0');
                    else
                        precision = precision * 10 + (*format - '0');
                }
                else if (*format == '.')
                    precision = 0;
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
                        count += _print_number(va_arg(args, long long), buffer, &index, width, precision, plus_flag, space_flag, zero_flag, minus_flag);
                    else if (long_flag == 1)
                        count += _print_number(va_arg(args, long), buffer, &index, width, precision, plus_flag, space_flag, zero_flag, minus_flag);
                    else if (short_flag == 2)
                        count += _print_number((short)va_arg(args, int), buffer, &index, width, precision, plus_flag, space_flag, zero_flag, minus_flag);
                    else if (short_flag == 1)
                        count += _print_number((signed char)va_arg(args, int), buffer, &index, width, precision, plus_flag, space_flag, zero_flag, minus_flag);
                    else
                        count += _print_number(va_arg(args, int), buffer, &index, width, precision, plus_flag, space_flag, zero_flag, minus_flag);
                    break;
                case 'u':
                    if (long_flag == 2)
                        count += _print_unsigned_number(va_arg(args, unsigned long long), buffer, &index, width, precision, zero_flag, minus_flag);
                    else if (long_flag == 1)
                        count += _print_unsigned_number(va_arg(args, unsigned long), buffer, &index, width, precision, zero_flag, minus_flag);
                    else if (short_flag == 2)
                        count += _print_unsigned_number((unsigned short)va_arg(args, unsigned int), buffer, &index, width, precision, zero_flag, minus_flag);
                    else if (short_flag == 1)
                        count += _print_unsigned_number((unsigned char)va_arg(args, unsigned int), buffer, &index, width, precision, zero_flag, minus_flag);
                    else
                        count += _print_unsigned_number(va_arg(args, unsigned int), buffer, &index, width, precision, zero_flag, minus_flag);
                    break;
                case 'o':
                    if (long_flag == 2)
                        count += _print_number_base(va_arg(args, unsigned long long), 8, buffer, &index, width, space_flag, zero_flag, minus_flag);
                    else if (long_flag == 1)
                        count += _print_number_base(va_arg(args, unsigned long), 8, buffer, &index, width, space_flag, zero_flag, minus_flag);
                    else if (short_flag == 2)
                        count += _print_number_base((unsigned short)va_arg(args, unsigned int), 8, buffer, &index, width, space_flag, zero_flag, minus_flag);
                    else if (short_flag == 1)
                        count += _print_number_base((unsigned char)va_arg(args, unsigned int), 8, buffer, &index, width, space_flag, zero_flag, minus_flag);
                    else
                        count += _print_number_base(va_arg(args, unsigned int), 8, buffer, &index, width, space_flag, zero_flag, minus_flag);
                    break;
                case 'x':
                    if (long_flag == 2)
                        count += _print_hex(va_arg(args, unsigned long long), 0, buffer, &index, width, precision, zero_flag, minus_flag);
                    else if (long_flag == 1)
                        count += _print_hex(va_arg(args, unsigned long), 0, buffer, &index, width, precision, zero_flag, minus_flag);
                    else if (short_flag == 2)
                        count += _print_hex((unsigned short)va_arg(args, unsigned int), 0, buffer, &index, width, precision, zero_flag, minus_flag);
                    else if (short_flag == 1)
                        count += _print_hex((unsigned char)va_arg(args, unsigned int), 0, buffer, &index, width, precision, zero_flag, minus_flag);
                    else
                        count += _print_hex(va_arg(args, unsigned int), 0, buffer, &index, width, precision, zero_flag, minus_flag);
                    break;
                case 'X':
                    if (long_flag == 2)
                        count += _print_hex(va_arg(args, unsigned long long), 1, buffer, &index, width, precision, zero_flag, minus_flag);
                    else if (long_flag == 1)
                        count += _print_hex(va_arg(args, unsigned long), 1, buffer, &index, width, precision, zero_flag, minus_flag);
                    else if (short_flag == 2)
                        count += _print_hex((unsigned short)va_arg(args, unsigned int), 1, buffer, &index, width, precision, zero_flag, minus_flag);
                    else if (short_flag == 1)
                        count += _print_hex((unsigned char)va_arg(args, unsigned int), 1, buffer, &index, width, precision, zero_flag, minus_flag);
                    else
                        count += _print_hex(va_arg(args, unsigned int), 1, buffer, &index, width, precision, zero_flag, minus_flag);
                    break;
                case 'S':
                    count += _print_string(va_arg(args, char *), buffer, &index, width, precision, minus_flag);
                    break;
                case 'p':
                    count += _print_pointer(va_arg(args, void *), buffer, &index, width, zero_flag, minus_flag);
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

