dnl@synposis BB_CHECK_PTHREADS.m4
dnl
AC_DEFUN([BB_CHECK_PTHREADS],[
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_CXX])dnl
AC_REQUIRE([AC_PROG_CPP])dnl
AC_REQUIRE([AC_PROG_CXXCPP])dnl


AC_ARG_WITH(pthreads, [  --with-pthreads         include pthreads support])

if test "x$with_pthreads" != "xno"; then
    CPPFLAGS="$CPPFLAGS -D_PTHREADS -D_REENTRANT -D_THREAD_SAFE"

    AC_LANG_PUSH(C++)

    LIBS="$LIBS -lpthread"
    AC_CACHE_CHECK([for pthreads library],
    bb_cv_check_pthreads,
    AC_TRY_LINK(
        #include <pthread.h>
        ,pthread_self(),
        bb_cv_check_pthreads=yes,bb_cv_check_pthreads=no)
    )
    if test "x$bb_cv_check_pthreads" = "xno"; then
        AC_MSG_ERROR([pthreads not found])
    fi

    AC_DEFINE(HAVE_THREADING,,[define if threading is enabled])
    AC_DEFINE(USE_PTHREADS,,[define if pthread library is available])

    AC_LANG_POP(C++)
fi
])
