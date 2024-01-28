#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_PASSWORD_LENGTH 100
#define MAX_REFERENCE_LENGTH 100
#define ANSI_COLOR_WHITE "\x1b[37;1m" 
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_WHITE_BLUE  "\x1b[37;44;1m"
#define ANSI_COLOR_BLACK_WHITE  "\x1b[30;47m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_ERROR "\x1b[41m"   
#define ANSI_COLOR_RESET   "\x1b[0m"

void key_generator(char *key, int n);
void cipher(const char *input, char *output, const char *key);
void save_password();
void open_password();
void display_references();
void erase_vault();
void generate_random_string(char *str, int n);
