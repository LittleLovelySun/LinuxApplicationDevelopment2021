#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

const char roman[101][10] = {"0", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

int main(int argc, char *argv[]) {
	const char* HELP = _("Usage ./guess_game [-r|--help]\n    -r      use roman\n    --help  show this help message and exit\n");
	
	if (argc > 1) {
		printf(_("Incorrect argument count\n"));
		printf("%s", HELP);
		return -1;
	}

	int in_roman = 0;

	if (argc == 1) {
		if (argv[0] == "--help") {
			printf("%s", HELP);
			return 0;
		}
		else if (argv[0] == "-r")
			in_roman = 1;
		else {
			printf(_("Incorrect arguments count\n"));
			printf("%s", HELP);
			return -1;
		}
	}

	int i;
	char *dir;

	dir = dirname(realpath(argv[0], NULL));
	setlocale (LC_ALL, "");
	bindtextdomain ("guess_game", LOCALE_PATH);
	textdomain ("guess_game");

	const char *yes = _("yes");
	const char *no = _("no");

	printf(_("The game has begun\n"));
	printf(_("Use only `%s` and `%s` for answer\n"), yes, no);
	int a = 0;
	int b = 100;


	while (a != b) {
		int middle = (b - a) / 2 + a;

		if (in_roman)
			printf(_("Number more than %s?\n>"), roman[middle]);
		else
			printf(_("Number more than %d?\n>"), middle);

		char answer[80];

		scanf("%s", answer);

		if (!strcmp(answer, yes)) {
			a = middle + 1;
		}
		else if (!strcmp(answer, no)) {
			b = middle;
		}
		else {
			printf(_("Incorrect input\n"));
			printf(_("Use only `%s` and `%s` for answer\n"), yes, no);
		}
	}

	if (in_roman)
		printf(_("Your number is %s\n"), roman[a]);
	else
		printf(_("Your number is %d\n"), a);

	return 0;
}