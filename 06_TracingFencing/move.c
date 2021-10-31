#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

void help() {
    printf("Usage <./move [infile] [outfile]\n");
    printf("    [infile] - path to input file");
    printf("    [outfile] - path to moving file");
    printf("    --help   print this message\n");
}

int move(const char* input_name, const char* output_name) {
	FILE* in = fopen(input_name, "rb");

	if (in == NULL) {
		perror("The input file could not be opened\n");
		return 2;
	}

    FILE* out = fopen(output_name, "wb");

    if (out == NULL) {
		perror("The output file could not be opened\n");

        if (fclose(in) == EOF)
            perror("The input file could not be closed\n");

		return 3;
    }

    char c;
    while((c = fgetc(in)) != EOF) {
        if (fprintf(out, "%c", c) < 0) {
            perror("Error while writing to output file\n");

            if (fclose(in) == EOF)
                perror("Error while closing input file\n");

            if (fclose(out) == EOF)
                perror("Error while closing output file\n");

            if (remove(output_name))
                perror("Error while removing output file\n");

            return 5;
        }
    }
    if (!feof(in)) {
        perror("Error while reading from input file\n");

        if (fclose(in) == EOF)
            perror("Error while closing input file\n");

        if (fclose(out) == EOF)
            perror("Error while closing output file\n");

        if (remove(output_name))
            perror("Error while removing output file\n");

        return 4;
    }

    if (fclose(in) == EOF) {
        if (fclose(out) == EOF)
            perror("Error while closing output file\n");

        if (remove(output_name))
            perror("Error while removing output file\n");

        return 6;
    }

    if (fclose(out) == EOF) {
        if (remove(output_name))
            perror("Error while removing output file\n");

        return 7;
    }

    if (unlink(input_name)) {
        perror("Error while removing input file\n");

        return 8;
    }
    return 0;
}


int main(int argc, char *argv[]) {
    float a = rand();
	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        help();
        return 0;
    }

    if (argc != 3) {
        printf("Incorrent parameters count. Use [--help] flag to see correct usage\n");
        return 1;
    }

    return move(argv[1], argv[2]);
}