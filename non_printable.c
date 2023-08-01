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
 * _print_non_printable - Prints non-printable characters in hexadecimal format.
 * @c: The character to print.
 * Return: The number of characters printed.
 */
int _print_non_printable(char c)
{
    int count = 0;
    char hex_digits[] = "0123456789ABCDEF";

    count += _putchar('\\');
    count += _putchar('x');
    count += _putchar(hex_digits[(c >> 4) & 0xF]);
    count += _putchar(hex_digits[c & 0xF]);

    return count;
}

/**
 * _printf - Custom printf function that handles %c, %s, %d, %i, %u, %o, %x, %X, and %S specifiers.
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
                // ...

                case 'S':
                {
                    char *str = va_arg(args, char *);
                    if (!str)
                        str = "(null)";
                    while (*str)
                    {
                        if (*str >= 32 && *str < 127)
                        {
                            count += _putchar(*str);
                        }
                        else
                        {
                            count += _print_non_printable(*str);
                        }
                        str++;
                    }
                    break;
                }
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
