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
    int count = 0;
    int padding = 0;

    if (n < 0 || plus_flag || space_flag)
        width--;

    if (precision >= 0 && precision > _num_digits(n))
        padding = precision - _num_digits(n);

    if (zero_flag && padding == 0 && !minus_flag)
        padding = width;

    if (width > 0)
    {
        padding = width - (_num_digits(n) + padding);

        while (padding > 0)
        {
            buffer[(*index)++] = minus_flag ? ' ' : (zero_flag ? '0' : ' ');
            padding--;
            count++;
        }
    }

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

    while (precision > 0)
    {
        buffer[(*index)++] = '0';
        precision--;
        count++;
    }

    if (n / 10)
        count += _print_number(n / 10, buffer, index, 0, 0, 0, 0, 0, 0);

    buffer[(*index)++] = (n % 10) + '0';
    count++;

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
 * _print_unsigned_number - Prints an unsigned integer using _putchar.
 * @n: The unsigned integer to print.
 * @buffer: The local buffer to store characters.
 * @index: The index to insert the character in the buffer.
 * @width: The field width for padding.
 * @precision: The precision for numeric conversions.
 * @zero_flag: A flag indicating whether the 0 flag is set.
 * @minus_flag: A flag indicating whether the - flag is set.
 * Return: The number of digits printed.
 */
int _print_unsigned_number(unsigned long int n, char *buffer, int *index, int width, int precision, int zero_flag, int minus_flag)
{
    int count = 0;
    int padding = 0;

    if (precision >= 0 && precision > _num_digits(n))
        padding = precision - _num_digits(n);

    if (zero_flag && padding == 0 && !minus_flag)
        padding = width;

    if (width > 0)
    {
        padding = width - (_num_digits(n) + padding);

        while (padding > 0)
        {
            buffer[(*index)++] = minus_flag ? ' ' : (zero_flag ? '0' : ' ');
            padding--;
            count++;
        }
    }

    while (precision > 0)
    {
        buffer[(*index)++] = '0';
        precision--;
        count++;
    }

    if (n / 10)
        count += _print_unsigned_number(n / 10, buffer, index, 0, 0, 0, 0);

    buffer[(*index)++] = (n % 10) + '0';
    count++;

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
 * _print_hex - Prints an unsigned integer in hexadecimal format.
 * @n: The unsigned integer to print in hexadecimal.
 * @uppercase: A flag to print uppercase hexadecimal letters (X).
 * @buffer: The local buffer to store characters.
 * @index: The index to insert the character in the buffer.
 * @width: The field width for padding.
 * @precision: The precision for numeric conversions.
 * @zero_flag: A flag indicating whether the 0 flag is set.
 * @minus_flag: A flag indicating whether the - flag is set.
 * Return: The number of characters printed.
 */
int _print_hex(unsigned long int n, int uppercase, char *buffer, int *index, int width, int precision, int zero_flag, int minus_flag)
{
    int count = 0;
    int padding = 0;
    char hex_digits[] = "0123456789abcdef";
    if (uppercase)
        hex_digits = "0123456789ABCDEF";

    if (precision >= 0 && precision > _num_hex_digits(n))
        padding = precision - _num_hex_digits(n);

    if (zero_flag && padding == 0 && !minus_flag)
        padding = width;

    if (width > 0)
    {
        padding = width - (_num_hex_digits(n) + padding);

        while (padding > 0)
        {
            buffer[(*index)++] = minus_flag ? ' ' : (zero_flag ? '0' : ' ');
            padding--;
            count++;
        }
    }

    while (precision > 0)
    {
        buffer[(*index)++] = '0';
        precision--;
        count++;
    }

    if (n / 16)
        count += _print_hex(n / 16, uppercase, buffer, index, 0, 0, 0, 0);

    buffer[(*index)++] = hex_digits[n % 16];
    count++;

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
