AC_PREREQ([2.69])
AC_INIT([rhasher.c], [1.00], [sd_kudinova@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_PROG_CC

AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([Missed rhash library!])])
AC_CHECK_LIB([readline],[readline],[],[])

AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

AC_ARG_ENABLE([readline],
	AS_HELP_STRING([--enable-readline], [Enable readline mode]),
	AC_DEFINE(CONF_READLINE,[1],[Readline mode]),
	[readline_mode="no"]
	)
AS_IF([test "x$readline_mode" = "xno"], [
	AC_SUBST(LIBS, ["-lrhash"])
])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT