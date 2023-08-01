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
 * Return: The number of digits printed.
 */
int _print_number(int n)
{
    int count = 0;

    if (n < 0)
    {
        count += _putchar('-');
        n = -n;
    }

    if (n / 10)
        count += _print_number(n / 10);

    count += _putchar((n % 10) + '0');

    return count;
}

/**
 * _print_unsigned_number - Prints an unsigned integer using _putchar.
 * @n: The unsigned integer to print.
 * Return: The number of digits printed.
 */
int _print_unsigned_number(unsigned int n)
{
    int count = 0;

    if (n / 10)
        count += _print_unsigned_number(n / 10);

    count += _putchar((n % 10) + '0');

    return count;
}

/**
 * _print_hex - Prints an unsigned integer in hexadecimal format.
 * @n: The unsigned integer to print in hexadecimal.
 * @uppercase: A flag to print uppercase hexadecimal letters (X).
 * Return: The number of characters printed.
 */
int _print_hex(unsigned int n, int uppercase)
{
    int count = 0;
    char hex_digits[] = "0123456789abcdef";
    if (uppercase)
        hex_digits = "0123456789ABCDEF";

    if (n / 16)
        count += _print_hex(n / 16, uppercase);

    count += _putchar(hex_digits[n % 16]);

    return count;
}

/**
 * _printf - Custom printf function that handles %c, %s, %d, %i, %u, %o, %x, and %X specifiers.
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
                case 'u':
                    count += _print_unsigned_number(va_arg(args, unsigned int));
                    break;
                case 'o':
                    count += _print_number_base(va_arg(args, unsigned int), 8);
                    break;
                case 'x':
                    count += _print_hex(va_arg(args, unsigned int), 0);
                    break;
                case 'X':
                    count += _print_hex(va_arg(args, unsigned int), 1);
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
