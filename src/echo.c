#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void escape(char *str);

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "--help") == 0)) {
        printf("Echo\nUsage: echo [ARG] [TEXT]\n"
        "args:\n"
        " -e enable interpretation of backslash escapes\n"
        "  '\\a'  alert (bell)\n"
        "  '\\b'  backspace\n"
        "  '\\c'  produce no further output\n"
        "  '\\e'  escape\n"
        "  '\\f'  form feed\n"
        "  '\\n'  newline\n"
        "  '\\r'  carriage return\n"
        "  '\\t'  horizontal tab\n"
        "  '\\v'  vertical tab\n"
        "  '\\\\'  backslash\n"
        "  '\\0NNN'  octal number NNN (zero to three digits), ninth bit ignored\n"
        "  '\\NNN'  octal number NNN (one to three digits), ninth bit ignored\n"
        "  '\\xHH'  hexadecimal number HH (one or two digits)\n");
        return 0;
    } else {
        int shift = 0;
        if (argc > 1 && strcmp(argv[1], "-e") == 0) {
            shift++;
        }
        for (int i = shift + 1; i < argc; i++) { 
            if(shift == 0) {
                if (i == argc - 1) {
                    printf("%s\n", argv[i]);
                } else {
                    printf("%s ", argv[i]);       
                }
            } else {
                if (i == argc - 1) {
                    escape(argv[i]);
                    putchar('\n');  
                } else {
                    escape(argv[i]);
                    putchar(' ');      
                }
            }
        }
    }
    return 0;
}

void escape(char *str) {
    char *p = str;
    while (*p != '\0') {
        if (*p == '\\') {
            switch (*(++p)) {
                case 'a':
                    putchar('\a');
                    break;
                case 'b':
                    putchar('\b');
                    break;
                case 'c':
                    return;
                case 'e':
                    putchar('\x1B');
                    break;
                case 'f':
                    putchar('\f');
                    break;
                case 'n':
                    putchar('\n');
                    break;
                case 'r':
                    putchar('\r');
                    break;
                case 't':
                    putchar('\t');
                    break;
                case 'v':
                    putchar('\v');
                    break;
                case '\\':
                    putchar('\\');
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7': {
                    char *endptr;
                    int value = strtol(p, &endptr, 8);
                    putchar(value);
                    p = endptr - 1;
                    break;
                }
                case 'x': {
                    char *endptr;
                    int value = strtol(++p, &endptr, 16);
                    putchar(value);
                    p = endptr - 1;
                    break;
                }
                default:
                    putchar(*p);
            }
        } else {
            putchar(*p);
        }
        p++;
    }
}