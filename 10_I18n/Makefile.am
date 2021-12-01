bin_PROGRAMS=guess_game

messages.pot:	guess_game.pot guess_game.c
	xgettext -k_ -c guess_game.c -o messages.new.pot
	cp guess_game.pot messages.pot
	msgmerge -U messages.pot messages.new.pot