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
 * _print_binary - Prints an unsigned integer in binary format.
 * @n: The unsigned integer to print in binary.
 * Return: The number of digits printed.
 */
int _print_binary(unsigned int n)
{
    int count = 0;
    unsigned int mask = 1 << ((sizeof(unsigned int) * 8) - 1);

    while (mask > 0)
    {
        if (n & mask)
            count += _putchar('1');
        else
            count += _putchar('0');
        mask >>= 1;
    }

    return count;
}

/**
 * _printf - Custom printf function that handles %c, %s, %d, %i, and %b specifiers.
 * @format: The format string.
 *
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                case 'c':
                    count += _putchar(va_arg(args, int));
                    break;
                case 's':
                {
                    char *str = va_arg(args, char *);
                    if (!str)
                        str = "(null)";
                    while (*str)
                    {
                        count += _putchar(*str);
                        str++;
                    }
                    break;
                }
                case 'd':
                case 'i':
                    count += _print_number(va_arg(args, int));
                    break;
                case 'b':
                    count += _print_binary(va_arg(args, unsigned int));
                    break;
                case '%':
                    count += _putchar('%');
                    break;
                default:
                    count += _putchar('%');
                    count += _putchar(*format);
                    break;
            }
        }
        else
        {
            count += _putchar(*format);
        }
        format++;
    }

    va_end(args);

    return count;
}
