#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE(-Wall -Werror foreign)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_LIBTOOL

PLATFORM_INIT

#AM_CONDITIONAL([XO_PROTECTOR], [test "x$MACHINE" = "xprotector"] || test "x$MACHINE" = "xvolans" || test "x$MACHINE" = "xvolans_omap"])
#AM_CONDITIONAL([XO_PROTECTOR], [test "x$MACHINE" = "xprotector"])

# Checks for libraries.
PKG_CHECK_MODULES(SSL, openssl)
AC_SUBST(SSL_CFLAGS)
AC_SUBST(SSL_LIBS)

PKG_CHECK_MODULES(DLOG, dlog)
AC_SUBST(DLOG_CFLAGS)
AC_SUBST(DLOG_LIBS)


# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h fcntl.h limits.h memory.h netdb.h netinet/in.h shadow.h stddef.h stdlib.h string.h strings.h sys/file.h sys/param.h sys/socket.h sys/statvfs.h sys/time.h sys/timeb.h sys/vfs.h syslog.h unistd.h utime.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_STRUCT_TIMEZONE
AC_TYPE_UID_T

# Checks for library functions.
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_FORK
AC_PROG_GCC_TRADITIONAL
AC_FUNC_LSTAT
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_FUNC_SETPGRP
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_FUNC_STRFTIME
AC_FUNC_UTIME_NULL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([alarm bzero dup2 endpwent ftruncate gethostbyaddr gethostbyname gethostname getpass getspnam gettimeofday inet_ntoa memmove memset mkdir rmdir select socket strcasecmp strchr strdup strerror strncasecmp strpbrk strrchr strstr strtol strtoul tzset uname utime])

AC_CONFIG_FILES([Makefile
				 uw-imap-toolkit.pc
				 ])

AC_OUTPUT

