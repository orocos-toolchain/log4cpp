dnl AC_AS_MKDIR_P(PATH)
dnl this is the macro AS_MKDIR_P from autoconf 2.4x
dnl defined here for use in autoconf 2.1x, remove the AC_ when you use 2.4x 
dnl
dnl @version $Id$
dnl @author complain to <guidod@gmx.de>

AC_DEFUN([AC_AS_MKDIR_P],[dnl
case $1 in
  \\*)   ac_incr_dir=\\;;
  ?:\\*) ac_incr_dir=\\;; # ouch
  /*)    ac_incr_dir=/;;
  ?:/*)  ac_incr_dir=/;; # ouch
  *)     ac_incr_dir=.;;
esac
as_dummy=$1
for as_mkdir_dir in `echo $ac_dummy | sed -e 'y:\\/:  :'`; do
  case $as_mkdir_dir in
    # Skip DOS drivespec
    ?:) as_incr_dir=$as_mkdir_dir ;;
    *)
      as_incr_dir=$as_incr_dir/$as_mkdir_dir
      test -d "$as_incr_dir" || mkdir "$as_incr_dir"
    ;;
  esac
done
])
