bin_PROGRAMS=guess_game
pkgdata_DATA=ru/LC_MESSAGES/guess_game.mo

TRASH=*.cache config.* configure depcomp *.exe missing *.o

ru/LC_MESSAGES/guess_game.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

gitclean:
	git clean -fd