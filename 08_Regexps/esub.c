#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

const int BUF_SIZE = 200;

void help() {
    printf("Usage: ./esub regexp substitution string\n");
}

void handle_regerror(regex_t r, int regexp_code, const char* msg) {
    char msg_buff[BUF_SIZE];

    if (regexp_code) {
        int a = regerror(regexp_code, &r, msg_buff, BUF_SIZE);
        printf("%s '%s'\n", msg, msg_buff);
        exit(EXIT_FAILURE);
    };
}


typedef struct string_t {
    char* s;
    size_t size;
    size_t capacity;
} string_t;

void add_symbol(char c, string_t* s) {
    if (s->size >= s->capacity) {
        s->capacity *= 2;
        s->s = (char*)realloc(s->s, sizeof(char) * s->capacity);
    }

    s->s[s->size++] = c;
}

string_t init_string() {
    string_t s;

    s.capacity = 1;
    s.size = 0;
    s.s = (char*)malloc(sizeof(char) * s.capacity);
    return s;
}

char* get_replaced(const char* substitution, const char* source, regmatch_t groupArray[], size_t maxGroups) {
    struct string_t res = init_string();
    int i = 0;

    for (int i = 0; substitution[i] != '\0'; i++) {
        if (substitution[i] != '\\' || substitution[i + 1] == '\0') {
            add_symbol(substitution[i], &res);
            continue;
        }

        if (substitution[i + 1] == '\\') {
            add_symbol(substitution[i], &res);
            i++;
            continue;
        }

        if (substitution[i + 1] < '0' || substitution[i + 1] > '9') {
            add_symbol(substitution[i], &res);
            continue;
        }

        int group = substitution[i + 1] - '0';

        if (group >= maxGroups) {
            printf("No group '%d' in regexp", group);
            exit(EXIT_FAILURE);
        }

        for (int j = groupArray[group].rm_so; j < groupArray[group].rm_eo; j++)
            add_symbol(source[j], &res);
        
        i++;
    }

    add_symbol('\0', &res);
    return res.s;
}

int main (int argc, char const *argv[]) {
    if (argc == 2 && (!strcmp(argv[1], "--help") || !strcmp(argv[1], "h"))) {
        help();
        return 0;
    }

    if (argc != 4) {
        printf("Incorrect parameters count\n");
        help();
        return 0;
    }
    
    const char* regex_string = argv[1];
    const char* substitution = argv[2];
    const char* source = argv[3];
  
    regex_t regex_compiled;

    handle_regerror(regex_compiled, regcomp(&regex_compiled, regex_string, REG_EXTENDED), "regecomp() failed with ");

    size_t maxGroups = regex_compiled.re_nsub + 1;
    regmatch_t groupArray[maxGroups];

    handle_regerror(regex_compiled, regexec(&regex_compiled, source, maxGroups, groupArray, 0), "regexec() failed with ");

    char* replaced = get_replaced(substitution, source, groupArray, maxGroups);
    size_t capacity = strlen(source) + strlen(replaced) + 1;

    char* res = (char*)malloc(sizeof(char) * capacity);
    strncpy(res, source, groupArray[0].rm_so);
    strcat(res, replaced);
    strcat(res, source + groupArray[0].rm_eo);

    printf("%s\n", res);
    regfree(&regex_compiled);
    free(res);
    free(replaced);

    return 0;
}