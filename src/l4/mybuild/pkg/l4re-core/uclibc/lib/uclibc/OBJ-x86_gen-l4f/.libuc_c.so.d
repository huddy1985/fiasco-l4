libuc_c.so : \
	/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/crtn.s.o \
	/usr/lib/gcc/x86_64-linux-gnu/5/32/crtendS.o \
	/usr/lib/gcc/x86_64-linux-gnu/5/32/libgcc_eh.a \
	/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/l4f/libgcc.so \
	_exit.s.o libc/misc/pthread/tsd.s.o \
	libpthread/src/libc_pthread_init.s.o libpthread/src/forward.s.o \
	ssp-l4.s.o libm/significandl.s.o libm/truncl.s.o libm/tgammal.s.o \
	libm/tanl.s.o libm/tanhl.s.o libm/sqrtl.s.o libm/sinl.s.o \
	libm/sinhl.s.o libm/scalbnl.s.o libm/scalblnl.s.o libm/roundl.s.o \
	libm/rintl.s.o libm/remquol.s.o libm/remainderl.s.o libm/powl.s.o \
	libm/nextafterl.s.o libm/nearbyintl.s.o libm/modfl.s.o \
	libm/lroundl.s.o libm/lrintl.s.o libm/logl.s.o libm/logbl.s.o \
	libm/log2l.s.o libm/log1pl.s.o libm/log10l.s.o libm/llroundl.s.o \
	libm/llrintl.s.o libm/lgammal.s.o libm/ldexpl.s.o libm/ilogbl.s.o \
	libm/hypotl.s.o libm/gammal.s.o libm/frexpl.s.o libm/fmodl.s.o \
	libm/fminl.s.o libm/fmaxl.s.o libm/fmal.s.o libm/floorl.s.o \
	libm/fdiml.s.o libm/fabsl.s.o libm/expm1l.s.o libm/expl.s.o \
	libm/erfl.s.o libm/erfcl.s.o libm/cosl.s.o libm/coshl.s.o \
	libm/copysignl.s.o libm/ceill.s.o libm/cbrtl.s.o libm/cargl.s.o \
	libm/atanl.s.o libm/atanhl.s.o libm/atan2l.s.o libm/asinl.s.o \
	libm/asinhl.s.o libm/acosl.s.o libm/acoshl.s.o libm/truncf.s.o \
	libm/tgammaf.s.o libm/tanhf.s.o libm/tanf.s.o libm/sqrtf.s.o \
	libm/sinhf.s.o libm/sinf.s.o libm/scalbnf.s.o libm/scalblnf.s.o \
	libm/roundf.s.o libm/rintf.s.o libm/remquof.s.o libm/remainderf.s.o \
	libm/powf.s.o libm/nextafterf.s.o libm/nearbyintf.s.o libm/modff.s.o \
	libm/lroundf.s.o libm/lrintf.s.o libm/logf.s.o libm/logbf.s.o \
	libm/log2f.s.o libm/log1pf.s.o libm/log10f.s.o libm/llrintf.s.o \
	libm/lgammaf.s.o libm/ldexpf.s.o libm/ilogbf.s.o libm/hypotf.s.o \
	libm/frexpf.s.o libm/fmodf.s.o libm/fminf.s.o libm/fmaxf.s.o \
	libm/fmaf.s.o libm/floorf.s.o libm/fdimf.s.o libm/fabsf.s.o \
	libm/expm1f.s.o libm/expf.s.o libm/exp2f.s.o libm/erff.s.o \
	libm/erfcf.s.o libm/coshf.s.o libm/cosf.s.o libm/copysignf.s.o \
	libm/ceilf.s.o libm/cbrtf.s.o libm/atanhf.s.o libm/atanf.s.o \
	libm/atan2f.s.o libm/asinhf.s.o libm/asinf.s.o libm/acoshf.s.o \
	libm/acosf.s.o libm/acos.s.o libc/misc/time/difftime.s.o \
	libc/stdlib/strtold.s.o libc/stdlib/strtof.s.o libc/stdlib/strtod.s.o \
	libc/stdlib/erand48_r.s.o libc/stdlib/erand48.s.o \
	libc/stdlib/drand48_r.s.o libc/stdlib/drand48.s.o \
	libc/stdlib/drand48-iter.s.o libc/stdlib/atof.s.o \
	libc/stdlib/_strtod.s.o libc/stdlib/__fp_range_check.s.o \
	libc/sysdeps/linux/common/creat64.s.o libc/misc/glob/glob64.s.o \
	libc/misc/dirent/scandir64.s.o libc/misc/dirent/readdir64_r.s.o \
	libc/misc/dirent/readdir64.s.o libc/misc/dirent/alphasort64.s.o \
	libc/stdio/ftello64.s.o libc/stdio/fsetpos64.s.o \
	libc/stdio/fseeko64.s.o libc/stdio/freopen64.s.o \
	libc/stdio/fopen64.s.o libc/stdio/fgetpos64.s.o \
	libc/stdlib/mkostemp64.s.o libc/misc/wctype/iswalnum.s.o \
	libc/misc/wctype/iswalpha.s.o libc/misc/wctype/iswblank.s.o \
	libc/misc/wctype/iswcntrl.s.o libc/misc/wctype/iswdigit.s.o \
	libc/misc/wctype/iswgraph.s.o libc/misc/wctype/iswprint.s.o \
	libc/misc/wctype/iswpunct.s.o libc/misc/wctype/iswspace.s.o \
	libc/misc/wctype/iswlower.s.o libc/misc/wctype/iswupper.s.o \
	libc/misc/wctype/iswxdigit.s.o libc/misc/wctype/wctrans.s.o \
	libc/misc/wctype/towctrans.s.o libc/misc/wctype/towupper.s.o \
	libc/misc/wctype/towlower.s.o libc/misc/wctype/_wctype.s.o \
	libc/misc/wctype/wctype.s.o libc/misc/wctype/iswctype.s.o \
	libc/misc/wchar/wcsrtombs.s.o libc/misc/wchar/wcsnrtombs.s.o \
	libc/misc/wchar/wcrtomb.s.o libc/misc/wchar/wctob.s.o \
	libc/misc/wchar/wchar.s.o libc/misc/wchar/mbsrtowcs.s.o \
	libc/misc/wchar/mbsnrtowcs.s.o libc/misc/wchar/mbrtowc.s.o \
	libc/misc/wchar/mbrlen.s.o libc/misc/wchar/btowc.s.o \
	libc/misc/time/wcsftime.s.o libc/stdio/wprintf.s.o \
	libc/stdio/vwprintf.s.o libc/stdio/vswprintf.s.o \
	libc/stdio/vfwprintf.s.o libc/stdio/_vfwprintf_internal.s.o \
	libc/stdio/swprintf.s.o libc/stdio/ungetwc.s.o \
	libc/stdio/fwprintf.s.o libc/stdio/fputws.__DO_UNLOCKED.s.o \
	libc/stdio/fputws.s.o libc/stdio/fgetwc.__DO_UNLOCKED.s.o \
	libc/stdio/fgetwc.s.o libc/stdio/fputwc.__DO_UNLOCKED.s.o \
	libc/stdio/fputwc.s.o libc/stdio/_wfwrite.s.o \
	libc/stdlib/mbstowcs.s.o libc/stdlib/mblen.s.o \
	libc/stdlib/wcstombs.s.o libc/stdlib/_stdlib_mb_cur_max.s.o \
	libc/string/wmemset.s.o libc/string/wmemmove.s.o \
	libc/string/wmemcmp.s.o libc/string/wmemchr.s.o \
	libc/string/wcsspn.s.o libc/string/wcsncmp.s.o \
	libc/string/wcslcpy.s.o libc/string/wcschrnul.s.o \
	libc/string/wcsxfrm.s.o libc/string/wcsrchr.s.o \
	libc/string/wcsncat.s.o libc/string/wcsdup.s.o libc/string/wcschr.s.o \
	libc/string/wcspbrk.s.o libc/string/wcscspn.s.o \
	libc/string/wcscat.s.o libc/string/wcstok.s.o \
	libc/string/wcsncasecmp.s.o libc/string/wcscpy.s.o \
	libc/string/wcscasecmp.s.o libc/string/wcsstr.s.o \
	libc/string/wmemcpy.s.o libc/string/wcsncpy.s.o \
	libc/string/wcslen.s.o libc/string/wcsnlen.s.o libc/string/wcscmp.s.o \
	libcrypt/md5.s.o libcrypt/des.s.o libcrypt/crypt.s.o libm/nan.s.o \
	libm/w_exp2.s.o libm/w_cabs.s.o libm/s_trunc.s.o libm/s_tanh.s.o \
	libm/s_tan.s.o libm/s_sin.s.o libm/s_significand.s.o \
	libm/s_signgam.s.o libm/s_signbitf.s.o libm/s_signbit.s.o \
	libm/s_scalbn.s.o libm/s_round.s.o libm/s_rint.s.o libm/s_remquo.s.o \
	libm/s_nextafterf.s.o libm/s_nextafter.s.o libm/s_modf.s.o \
	libm/s_matherr.s.o libm/s_lround.s.o libm/s_lrint.s.o libm/s_logb.s.o \
	libm/s_log1p.s.o libm/s_llround.s.o libm/s_llrint.s.o \
	libm/s_lib_version.s.o libm/s_ldexp.s.o libm/s_isinff.s.o \
	libm/s_isinf.s.o libm/s_isnanf.s.o libm/s_isnan.s.o libm/s_ilogb.s.o \
	libm/s_frexp.s.o libm/s_fmin.s.o libm/s_fmax.s.o libm/s_fma.s.o \
	libm/s_floor.s.o libm/s_finitef.s.o libm/s_finite.s.o libm/s_fdim.s.o \
	libm/s_fpclassify.s.o libm/s_fabs.s.o libm/s_expm1.s.o libm/s_erf.s.o \
	libm/s_cos.s.o libm/s_copysign.s.o libm/s_ceil.s.o libm/s_cbrt.s.o \
	libm/s_atan.s.o libm/s_asinh.s.o libm/k_tan.s.o libm/k_standard.s.o \
	libm/k_sin.s.o libm/k_rem_pio2.s.o libm/k_cos.s.o libm/e_sqrt.s.o \
	libm/e_sinh.s.o libm/e_scalb.s.o libm/e_rem_pio2.s.o \
	libm/e_remainder.s.o libm/e_pow.s.o libm/e_log2.s.o libm/e_log10.s.o \
	libm/e_log.s.o libm/e_lgamma_r.s.o libm/e_jn.s.o libm/e_j1.s.o \
	libm/e_j0.s.o libm/e_hypot.s.o libm/e_fmod.s.o libm/e_exp.s.o \
	libm/e_cosh.s.o libm/e_atanh.s.o libm/e_atan2.s.o libm/e_asin.s.o \
	libm/e_acosh.s.o libm/e_acos.s.o libm/cexp.s.o libm/carg.s.o \
	libc/termios/ttyname.s.o libc/termios/tcsetpgrp.s.o \
	libc/termios/tcsetattr.s.o libc/termios/tcgetsid.s.o \
	libc/termios/tcgetpgrp.s.o libc/termios/tcgetattr.s.o \
	libc/termios/tcflush.s.o libc/termios/speed.s.o \
	libc/termios/isatty.s.o libc/sysdeps/linux/common/getpagesize.s.o \
	libc/sysdeps/linux/common/getdirname.s.o \
	libc/sysdeps/linux/common/gethostname.s.o \
	libc/sysdeps/linux/common/getsid.s.o \
	libc/sysdeps/linux/common/getdents.s.o \
	libc/sysdeps/linux/common/longjmp.s.o \
	libc/sysdeps/linux/common/creat.s.o \
	libc/misc/elf/dl-iterate-phdr.s.o libc/misc/wordexp/wordexp.s.o \
	libc/misc/time/_time_localtime_tzi.s.o \
	libc/misc/time/_time_mktime_tzi.s.o libc/misc/time/timegm.s.o \
	libc/misc/time/dysize.s.o libc/misc/time/_time_mktime.s.o \
	libc/misc/time/__time_tm.s.o libc/misc/time/_time_t2tm.s.o \
	libc/misc/time/tzset.s.o libc/misc/time/strptime.s.o \
	libc/misc/time/strftime.s.o libc/misc/time/mktime.s.o \
	libc/misc/time/localtime_r.s.o libc/misc/time/localtime.s.o \
	libc/misc/time/gmtime_r.s.o libc/misc/time/gmtime.s.o \
	libc/misc/time/ftime.s.o libc/misc/time/ctime_r.s.o \
	libc/misc/time/ctime.s.o libc/misc/time/asctime_r.s.o \
	libc/misc/time/asctime.s.o libc/misc/time/time.s.o \
	libc/misc/search/twalk.s.o libc/misc/search/tsearch.s.o \
	libc/misc/search/tfind.s.o libc/misc/search/tdestroy.s.o \
	libc/misc/search/tdelete.s.o libc/misc/search/remque.s.o \
	libc/misc/search/lsearch.s.o libc/misc/search/lfind.s.o \
	libc/misc/search/insremque.s.o libc/misc/search/insque.s.o \
	libc/misc/search/hsearch_r.s.o libc/misc/search/hsearch.s.o \
	libc/misc/search/hdestroy_r.s.o libc/misc/search/hcreate_r.s.o \
	libc/misc/regex/regex_old.s.o libc/misc/locale/setlocale.s.o \
	libc/misc/locale/nl_langinfo.s.o libc/misc/locale/localeconv.s.o \
	libc/misc/locale/locale.s.o libc/misc/internals/tempname.s.o \
	libc/misc/internals/parse_config.s.o \
	libc/misc/internals/__uClibc_main.s.o \
	libc/misc/internals/__h_errno_location.s.o \
	libc/misc/internals/__errno_location.s.o \
	libc/misc/internals/h_errno.s.o libc/misc/internals/errno.s.o \
	libc/misc/glob/glob.s.o libc/misc/fnmatch/fnmatch.s.o \
	libc/misc/error/err.s.o libc/misc/dirent/telldir.s.o \
	libc/misc/dirent/seekdir.s.o libc/misc/dirent/scandir.s.o \
	libc/misc/dirent/rewinddir.s.o libc/misc/dirent/readdir_r.s.o \
	libc/misc/dirent/readdir.s.o libc/misc/dirent/opendir.s.o \
	libc/misc/dirent/dirfd.s.o libc/misc/dirent/closedir.s.o \
	libc/misc/dirent/alphasort.s.o libc/misc/ctype/isctype.s.o \
	libc/misc/ctype/__ctype_assert.s.o \
	libc/misc/ctype/__ctype_toupper_loc.s.o \
	libc/misc/ctype/__ctype_tolower_loc.s.o \
	libc/misc/ctype/__ctype_b_loc.s.o \
	libc/misc/ctype/__C_ctype_toupper.s.o \
	libc/misc/ctype/__C_ctype_tolower.s.o \
	libc/misc/ctype/__C_ctype_b.s.o libc/misc/ctype/toupper.s.o \
	libc/misc/ctype/tolower.s.o libc/misc/ctype/isxdigit.s.o \
	libc/misc/ctype/isupper.s.o libc/misc/ctype/isspace.s.o \
	libc/misc/ctype/ispunct.s.o libc/misc/ctype/isprint.s.o \
	libc/misc/ctype/islower.s.o libc/misc/ctype/isgraph.s.o \
	libc/misc/ctype/isdigit.s.o libc/misc/ctype/iscntrl.s.o \
	libc/misc/ctype/isblank.s.o libc/misc/ctype/isascii.s.o \
	libc/misc/ctype/isalpha.s.o libc/misc/ctype/isalnum.s.o \
	libc/misc/ctype/ctype.s.o libc/misc/assert/__assert.s.o \
	libc/stdio/vprintf.s.o libc/stdio/vsprintf.s.o \
	libc/stdio/vsnprintf.s.o libc/stdio/_ppfs_parsespec.s.o \
	libc/stdio/_ppfs_setargs.s.o libc/stdio/_ppfs_prepargs.s.o \
	libc/stdio/_ppfs_init.s.o libc/stdio/vfprintf.s.o \
	libc/stdio/_vfprintf_internal.s.o libc/stdio/_vfprintf.s.o \
	libc/stdio/vdprintf.s.o libc/stdio/vasprintf.s.o \
	libc/stdio/ungetc.s.o libc/stdio/tmpfile.s.o libc/stdio/sprintf.s.o \
	libc/stdio/snprintf.s.o libc/stdio/setlinebuf.s.o \
	libc/stdio/setbuffer.s.o libc/stdio/setbuf.s.o libc/stdio/setvbuf.s.o \
	libc/stdio/vsscanf.s.o libc/stdio/vscanf.s.o libc/stdio/fscanf.s.o \
	libc/stdio/sscanf.s.o libc/stdio/scanf.s.o \
	libc/stdio/__psfs_do_numeric.s.o libc/stdio/__psfs_parse_spec.s.o \
	libc/stdio/__scan_cookie.s.o libc/stdio/vfscanf.s.o \
	libc/stdio/_scanf.s.o libc/stdio/rewind.s.o libc/stdio/remove.s.o \
	libc/stdio/puts.s.o libc/stdio/putchar.__DO_UNLOCKED.s.o \
	libc/stdio/putchar.s.o libc/stdio/printf.s.o libc/stdio/perror.s.o \
	libc/stdio/getline.s.o libc/stdio/getdelim.s.o libc/stdio/getchar.s.o \
	libc/stdio/fwrite.__DO_UNLOCKED.s.o libc/stdio/fwrite.s.o \
	libc/stdio/funlockfile.s.o libc/stdio/ftello.s.o \
	libc/stdio/fsetpos.s.o libc/stdio/fseeko.s.o \
	libc/stdio/fread.__DO_UNLOCKED.s.o libc/stdio/fread.s.o \
	libc/stdio/fprintf.s.o libc/stdio/fputc.__DO_UNLOCKED.s.o \
	libc/stdio/fputc.s.o libc/stdio/fputs.__DO_UNLOCKED.s.o \
	libc/stdio/fputs.s.o libc/stdio/freopen.s.o libc/stdio/fopen.s.o \
	libc/stdio/flockfile.s.o libc/stdio/fileno.__DO_UNLOCKED.s.o \
	libc/stdio/fileno.s.o libc/stdio/fgets.__DO_UNLOCKED.s.o \
	libc/stdio/fgets.s.o libc/stdio/fgetpos.s.o \
	libc/stdio/fgetc.__DO_UNLOCKED.s.o libc/stdio/fgetc.s.o \
	libc/stdio/fflush.__DO_UNLOCKED.s.o libc/stdio/fflush.s.o \
	libc/stdio/ferror.__DO_UNLOCKED.s.o libc/stdio/ferror.s.o \
	libc/stdio/feof.__DO_UNLOCKED.s.o libc/stdio/feof.s.o \
	libc/stdio/fdopen.s.o libc/stdio/fcloseall.s.o libc/stdio/fclose.s.o \
	libc/stdio/dprintf.s.o libc/stdio/clearerr.__DO_UNLOCKED.s.o \
	libc/stdio/clearerr.s.o libc/stdio/asprintf.s.o \
	libc/stdio/_wcommit.s.o libc/stdio/_uintmaxtostr.s.o \
	libc/stdio/_trans2w.s.o libc/stdio/_trans2r.s.o \
	libc/stdio/_store_inttype.s.o libc/stdio/_stdio.s.o \
	libc/stdio/_rfill.s.o libc/stdio/_load_inttype.s.o \
	libc/stdio/_WRITE.s.o libc/stdio/_READ.s.o libc/stdio/_fwrite.s.o \
	libc/stdio/_fpmaxtostr.s.o libc/stdio/_fopen.s.o \
	libc/stdio/_cs_funcs.s.o libc/stdio/_adjust_pos.s.o \
	libc/stdio/__fsetlocking.s.o libc/stdlib/malloc-standard/realloc.s.o \
	libc/stdlib/malloc-standard/memalign.s.o \
	libc/stdlib/malloc-standard/mallopt.s.o \
	libc/stdlib/malloc-standard/malloc.s.o \
	libc/stdlib/malloc-standard/mallinfo.s.o \
	libc/stdlib/malloc-standard/free.s.o \
	libc/stdlib/malloc-standard/calloc.s.o libc/stdlib/strtoull.s.o \
	libc/stdlib/strtoul.s.o libc/stdlib/strtoll.s.o \
	libc/stdlib/strtol.s.o libc/stdlib/stdlib.s.o \
	libc/stdlib/srand48_r.s.o libc/stdlib/srand48.s.o \
	libc/stdlib/setenv.s.o libc/stdlib/realpath.s.o \
	libc/stdlib/random_r.s.o libc/stdlib/random.s.o \
	libc/stdlib/rand_r.s.o libc/stdlib/rand.s.o libc/stdlib/qsort_r.s.o \
	libc/stdlib/qsort.s.o libc/stdlib/posix_memalign.s.o \
	libc/stdlib/on_exit.s.o libc/stdlib/nrand48_r.s.o \
	libc/stdlib/nrand48.s.o libc/stdlib/mkstemp64.s.o \
	libc/stdlib/mkstemp.s.o libc/stdlib/mkostemp.s.o \
	libc/stdlib/lrand48_r.s.o libc/stdlib/lrand48.s.o \
	libc/stdlib/lldiv.s.o libc/stdlib/llabs.s.o libc/stdlib/ldiv.s.o \
	libc/stdlib/labs.s.o libc/stdlib/jrand48_r.s.o \
	libc/stdlib/jrand48.s.o libc/stdlib/getenv.s.o libc/stdlib/gcvt.s.o \
	libc/stdlib/exit.s.o libc/stdlib/div.s.o libc/stdlib/bsearch.s.o \
	libc/stdlib/atoll.s.o libc/stdlib/atol.s.o libc/stdlib/atoi.s.o \
	libc/stdlib/abs.s.o libc/stdlib/abort.s.o \
	libc/stdlib/_stdlib_strto_ll.s.o libc/stdlib/_stdlib_strto_l.s.o \
	libc/stdlib/__uc_malloc.s.o libc/stdlib/__strtofpmax.s.o \
	libc/stdlib/__exit_handler.s.o libc/stdlib/__cxa_atexit.s.o \
	libc/signal/sigjmp.s.o libc/signal/sigsetops.s.o \
	libc/signal/sigismem.s.o libc/signal/sigfillset.s.o \
	libc/signal/sigempty.s.o libc/signal/sigdelset.s.o \
	libc/signal/sigandset.s.o libc/signal/sigaddset.s.o \
	libc/signal/raise.s.o libc/signal/allocrtsig.s.o \
	libc/unistd/sleep.s.o libc/unistd/getopt.s.o libc/unistd/getlogin.s.o \
	libc/pwd_grp/__pgsreader.s.o libc/pwd_grp/__parsegrent.s.o \
	libc/pwd_grp/__parsepwent.s.o libc/pwd_grp/getpwent_r.s.o \
	libc/pwd_grp/getpwent.s.o libc/pwd_grp/getpwnam_r.s.o \
	libc/pwd_grp/getpwnam.s.o libc/pwd_grp/getpwuid_r.s.o \
	libc/pwd_grp/getpwuid.s.o libc/pwd_grp/getgrnam_r.s.o \
	libc/pwd_grp/getgrnam.s.o libc/pwd_grp/getgrgid_r.s.o \
	libc/pwd_grp/getgrgid.s.o libc/pwd_grp/pwd_grp.s.o \
	libc/inet/resolv.s.o libc/inet/res_query.s.o libc/inet/res_init.s.o \
	libc/inet/res_comp.s.o libc/inet/read_etc_hosts_r.s.o \
	libc/inet/opensock.s.o libc/inet/opennameservers.s.o \
	libc/inet/ntop.s.o libc/inet/ntohl.s.o libc/inet/ns_name.s.o \
	libc/inet/lengthq.s.o libc/inet/lengthd.s.o libc/inet/in6_addr.s.o \
	libc/inet/inet_ntoa.s.o libc/inet/inet_netof.s.o \
	libc/inet/inet_net.s.o libc/inet/inet_makeaddr.s.o \
	libc/inet/inet_lnaof.s.o libc/inet/inet_aton.s.o \
	libc/inet/inet_addr.s.o libc/inet/if_index.s.o libc/inet/herror.s.o \
	libc/inet/getservice.s.o libc/inet/getproto.s.o libc/inet/getnet.s.o \
	libc/inet/gethostent_r.s.o libc/inet/gethostent.s.o \
	libc/inet/gethostbyname_r.s.o libc/inet/gethostbyname2_r.s.o \
	libc/inet/gethostbyname2.s.o libc/inet/gethostbyname.s.o \
	libc/inet/gethostbyaddr_r.s.o libc/inet/gethostbyaddr.s.o \
	libc/inet/getaddrinfo.s.o libc/inet/get_hosts_byname_r.s.o \
	libc/inet/get_hosts_byaddr_r.s.o libc/inet/gai_strerror.s.o \
	libc/inet/formquery.s.o libc/inet/ether_addr.s.o \
	libc/inet/encodeq.s.o libc/inet/encodep.s.o libc/inet/encodeh.s.o \
	libc/inet/encoded.s.o libc/inet/encodea.s.o libc/inet/dnslookup.s.o \
	libc/inet/decodeq.s.o libc/inet/decodep.s.o libc/inet/decodeh.s.o \
	libc/inet/decoded.s.o libc/inet/decodea.s.o \
	libc/inet/closenameservers.s.o libc/inet/addr.s.o \
	libc/inet/_res_state.s.o libc/string/strpbrk.s.o \
	libc/string/generic/strtok_r.s.o libc/string/generic/strstr.s.o \
	libc/string/generic/strspn.s.o libc/string/generic/strsep.s.o \
	libc/string/generic/strcspn.s.o libc/string/i386/strchrnul.s.o \
	libc/string/i386/rawmemchr.s.o libc/string/generic/memrchr.s.o \
	libc/string/generic/mempcpy.s.o libc/string/generic/memmem.s.o \
	libc/string/generic/memcmp.s.o libc/string/i386/strrchr.s.o \
	libc/string/i386/strnlen.s.o libc/string/i386/strncpy.s.o \
	libc/string/i386/strncmp.s.o libc/string/i386/strncat.s.o \
	libc/string/i386/strlen.s.o libc/string/i386/strcpy.s.o \
	libc/string/i386/strcmp.s.o libc/string/i386/strchr.s.o \
	libc/string/i386/strcat.s.o libc/string/i386/memset.s.o \
	libc/string/i386/memmove.s.o libc/string/i386/memcpy.s.o \
	libc/string/i386/memchr.s.o libc/string/bzero.s.o \
	libc/string/bcopy.s.o libc/string/strtok.s.o \
	libc/string/strncasecmp.s.o libc/string/strndup.s.o \
	libc/string/sys_errlist.s.o libc/string/strlcpy.s.o \
	libc/string/strlcat.s.o libc/string/__xpg_basename.s.o \
	libc/string/psignal.s.o libc/string/strsignal.s.o \
	libc/string/sys_siglist.s.o libc/string/_string_syssigmsgs.s.o \
	libc/string/__glibc_strerror_r.s.o \
	libc/string/_string_syserrmsgs.s.o libc/string/__xpg_strerror_r.s.o \
	libc/string/strerror.s.o libc/string/strdup.s.o \
	libc/string/strcasestr.s.o libc/string/strcasecmp.s.o \
	libc/string/stpncpy.s.o libc/string/stpcpy.s.o \
	libc/string/memccpy.s.o libc/string/ffs.s.o libc/string/dirname.s.o \
	libc/string/basename.s.o libc/sysdeps/linux/i386/__longjmp.s.o \
	libc/sysdeps/linux/i386/bsd-_setjmp.s.o \
	libc/sysdeps/linux/i386/bsd-setjmp.s.o \
	libc/sysdeps/linux/i386/setjmp.s.o \
	/usr/lib/gcc/x86_64-linux-gnu/5/32/crtbeginS.o \
	/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/crti.s.o \
	/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/main_rel.ld 
/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/crtn.s.o:
/usr/lib/gcc/x86_64-linux-gnu/5/32/crtendS.o:
/usr/lib/gcc/x86_64-linux-gnu/5/32/libgcc_eh.a:
/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/l4f/libgcc.so:
_exit.s.o:
libc/misc/pthread/tsd.s.o:
libpthread/src/libc_pthread_init.s.o:
libpthread/src/forward.s.o:
ssp-l4.s.o:
libm/significandl.s.o:
libm/truncl.s.o:
libm/tgammal.s.o:
libm/tanl.s.o:
libm/tanhl.s.o:
libm/sqrtl.s.o:
libm/sinl.s.o:
libm/sinhl.s.o:
libm/scalbnl.s.o:
libm/scalblnl.s.o:
libm/roundl.s.o:
libm/rintl.s.o:
libm/remquol.s.o:
libm/remainderl.s.o:
libm/powl.s.o:
libm/nextafterl.s.o:
libm/nearbyintl.s.o:
libm/modfl.s.o:
libm/lroundl.s.o:
libm/lrintl.s.o:
libm/logl.s.o:
libm/logbl.s.o:
libm/log2l.s.o:
libm/log1pl.s.o:
libm/log10l.s.o:
libm/llroundl.s.o:
libm/llrintl.s.o:
libm/lgammal.s.o:
libm/ldexpl.s.o:
libm/ilogbl.s.o:
libm/hypotl.s.o:
libm/gammal.s.o:
libm/frexpl.s.o:
libm/fmodl.s.o:
libm/fminl.s.o:
libm/fmaxl.s.o:
libm/fmal.s.o:
libm/floorl.s.o:
libm/fdiml.s.o:
libm/fabsl.s.o:
libm/expm1l.s.o:
libm/expl.s.o:
libm/erfl.s.o:
libm/erfcl.s.o:
libm/cosl.s.o:
libm/coshl.s.o:
libm/copysignl.s.o:
libm/ceill.s.o:
libm/cbrtl.s.o:
libm/cargl.s.o:
libm/atanl.s.o:
libm/atanhl.s.o:
libm/atan2l.s.o:
libm/asinl.s.o:
libm/asinhl.s.o:
libm/acosl.s.o:
libm/acoshl.s.o:
libm/truncf.s.o:
libm/tgammaf.s.o:
libm/tanhf.s.o:
libm/tanf.s.o:
libm/sqrtf.s.o:
libm/sinhf.s.o:
libm/sinf.s.o:
libm/scalbnf.s.o:
libm/scalblnf.s.o:
libm/roundf.s.o:
libm/rintf.s.o:
libm/remquof.s.o:
libm/remainderf.s.o:
libm/powf.s.o:
libm/nextafterf.s.o:
libm/nearbyintf.s.o:
libm/modff.s.o:
libm/lroundf.s.o:
libm/lrintf.s.o:
libm/logf.s.o:
libm/logbf.s.o:
libm/log2f.s.o:
libm/log1pf.s.o:
libm/log10f.s.o:
libm/llrintf.s.o:
libm/lgammaf.s.o:
libm/ldexpf.s.o:
libm/ilogbf.s.o:
libm/hypotf.s.o:
libm/frexpf.s.o:
libm/fmodf.s.o:
libm/fminf.s.o:
libm/fmaxf.s.o:
libm/fmaf.s.o:
libm/floorf.s.o:
libm/fdimf.s.o:
libm/fabsf.s.o:
libm/expm1f.s.o:
libm/expf.s.o:
libm/exp2f.s.o:
libm/erff.s.o:
libm/erfcf.s.o:
libm/coshf.s.o:
libm/cosf.s.o:
libm/copysignf.s.o:
libm/ceilf.s.o:
libm/cbrtf.s.o:
libm/atanhf.s.o:
libm/atanf.s.o:
libm/atan2f.s.o:
libm/asinhf.s.o:
libm/asinf.s.o:
libm/acoshf.s.o:
libm/acosf.s.o:
libm/acos.s.o:
libc/misc/time/difftime.s.o:
libc/stdlib/strtold.s.o:
libc/stdlib/strtof.s.o:
libc/stdlib/strtod.s.o:
libc/stdlib/erand48_r.s.o:
libc/stdlib/erand48.s.o:
libc/stdlib/drand48_r.s.o:
libc/stdlib/drand48.s.o:
libc/stdlib/drand48-iter.s.o:
libc/stdlib/atof.s.o:
libc/stdlib/_strtod.s.o:
libc/stdlib/__fp_range_check.s.o:
libc/sysdeps/linux/common/creat64.s.o:
libc/misc/glob/glob64.s.o:
libc/misc/dirent/scandir64.s.o:
libc/misc/dirent/readdir64_r.s.o:
libc/misc/dirent/readdir64.s.o:
libc/misc/dirent/alphasort64.s.o:
libc/stdio/ftello64.s.o:
libc/stdio/fsetpos64.s.o:
libc/stdio/fseeko64.s.o:
libc/stdio/freopen64.s.o:
libc/stdio/fopen64.s.o:
libc/stdio/fgetpos64.s.o:
libc/stdlib/mkostemp64.s.o:
libc/misc/wctype/iswalnum.s.o:
libc/misc/wctype/iswalpha.s.o:
libc/misc/wctype/iswblank.s.o:
libc/misc/wctype/iswcntrl.s.o:
libc/misc/wctype/iswdigit.s.o:
libc/misc/wctype/iswgraph.s.o:
libc/misc/wctype/iswprint.s.o:
libc/misc/wctype/iswpunct.s.o:
libc/misc/wctype/iswspace.s.o:
libc/misc/wctype/iswlower.s.o:
libc/misc/wctype/iswupper.s.o:
libc/misc/wctype/iswxdigit.s.o:
libc/misc/wctype/wctrans.s.o:
libc/misc/wctype/towctrans.s.o:
libc/misc/wctype/towupper.s.o:
libc/misc/wctype/towlower.s.o:
libc/misc/wctype/_wctype.s.o:
libc/misc/wctype/wctype.s.o:
libc/misc/wctype/iswctype.s.o:
libc/misc/wchar/wcsrtombs.s.o:
libc/misc/wchar/wcsnrtombs.s.o:
libc/misc/wchar/wcrtomb.s.o:
libc/misc/wchar/wctob.s.o:
libc/misc/wchar/wchar.s.o:
libc/misc/wchar/mbsrtowcs.s.o:
libc/misc/wchar/mbsnrtowcs.s.o:
libc/misc/wchar/mbrtowc.s.o:
libc/misc/wchar/mbrlen.s.o:
libc/misc/wchar/btowc.s.o:
libc/misc/time/wcsftime.s.o:
libc/stdio/wprintf.s.o:
libc/stdio/vwprintf.s.o:
libc/stdio/vswprintf.s.o:
libc/stdio/vfwprintf.s.o:
libc/stdio/_vfwprintf_internal.s.o:
libc/stdio/swprintf.s.o:
libc/stdio/ungetwc.s.o:
libc/stdio/fwprintf.s.o:
libc/stdio/fputws.__DO_UNLOCKED.s.o:
libc/stdio/fputws.s.o:
libc/stdio/fgetwc.__DO_UNLOCKED.s.o:
libc/stdio/fgetwc.s.o:
libc/stdio/fputwc.__DO_UNLOCKED.s.o:
libc/stdio/fputwc.s.o:
libc/stdio/_wfwrite.s.o:
libc/stdlib/mbstowcs.s.o:
libc/stdlib/mblen.s.o:
libc/stdlib/wcstombs.s.o:
libc/stdlib/_stdlib_mb_cur_max.s.o:
libc/string/wmemset.s.o:
libc/string/wmemmove.s.o:
libc/string/wmemcmp.s.o:
libc/string/wmemchr.s.o:
libc/string/wcsspn.s.o:
libc/string/wcsncmp.s.o:
libc/string/wcslcpy.s.o:
libc/string/wcschrnul.s.o:
libc/string/wcsxfrm.s.o:
libc/string/wcsrchr.s.o:
libc/string/wcsncat.s.o:
libc/string/wcsdup.s.o:
libc/string/wcschr.s.o:
libc/string/wcspbrk.s.o:
libc/string/wcscspn.s.o:
libc/string/wcscat.s.o:
libc/string/wcstok.s.o:
libc/string/wcsncasecmp.s.o:
libc/string/wcscpy.s.o:
libc/string/wcscasecmp.s.o:
libc/string/wcsstr.s.o:
libc/string/wmemcpy.s.o:
libc/string/wcsncpy.s.o:
libc/string/wcslen.s.o:
libc/string/wcsnlen.s.o:
libc/string/wcscmp.s.o:
libcrypt/md5.s.o:
libcrypt/des.s.o:
libcrypt/crypt.s.o:
libm/nan.s.o:
libm/w_exp2.s.o:
libm/w_cabs.s.o:
libm/s_trunc.s.o:
libm/s_tanh.s.o:
libm/s_tan.s.o:
libm/s_sin.s.o:
libm/s_significand.s.o:
libm/s_signgam.s.o:
libm/s_signbitf.s.o:
libm/s_signbit.s.o:
libm/s_scalbn.s.o:
libm/s_round.s.o:
libm/s_rint.s.o:
libm/s_remquo.s.o:
libm/s_nextafterf.s.o:
libm/s_nextafter.s.o:
libm/s_modf.s.o:
libm/s_matherr.s.o:
libm/s_lround.s.o:
libm/s_lrint.s.o:
libm/s_logb.s.o:
libm/s_log1p.s.o:
libm/s_llround.s.o:
libm/s_llrint.s.o:
libm/s_lib_version.s.o:
libm/s_ldexp.s.o:
libm/s_isinff.s.o:
libm/s_isinf.s.o:
libm/s_isnanf.s.o:
libm/s_isnan.s.o:
libm/s_ilogb.s.o:
libm/s_frexp.s.o:
libm/s_fmin.s.o:
libm/s_fmax.s.o:
libm/s_fma.s.o:
libm/s_floor.s.o:
libm/s_finitef.s.o:
libm/s_finite.s.o:
libm/s_fdim.s.o:
libm/s_fpclassify.s.o:
libm/s_fabs.s.o:
libm/s_expm1.s.o:
libm/s_erf.s.o:
libm/s_cos.s.o:
libm/s_copysign.s.o:
libm/s_ceil.s.o:
libm/s_cbrt.s.o:
libm/s_atan.s.o:
libm/s_asinh.s.o:
libm/k_tan.s.o:
libm/k_standard.s.o:
libm/k_sin.s.o:
libm/k_rem_pio2.s.o:
libm/k_cos.s.o:
libm/e_sqrt.s.o:
libm/e_sinh.s.o:
libm/e_scalb.s.o:
libm/e_rem_pio2.s.o:
libm/e_remainder.s.o:
libm/e_pow.s.o:
libm/e_log2.s.o:
libm/e_log10.s.o:
libm/e_log.s.o:
libm/e_lgamma_r.s.o:
libm/e_jn.s.o:
libm/e_j1.s.o:
libm/e_j0.s.o:
libm/e_hypot.s.o:
libm/e_fmod.s.o:
libm/e_exp.s.o:
libm/e_cosh.s.o:
libm/e_atanh.s.o:
libm/e_atan2.s.o:
libm/e_asin.s.o:
libm/e_acosh.s.o:
libm/e_acos.s.o:
libm/cexp.s.o:
libm/carg.s.o:
libc/termios/ttyname.s.o:
libc/termios/tcsetpgrp.s.o:
libc/termios/tcsetattr.s.o:
libc/termios/tcgetsid.s.o:
libc/termios/tcgetpgrp.s.o:
libc/termios/tcgetattr.s.o:
libc/termios/tcflush.s.o:
libc/termios/speed.s.o:
libc/termios/isatty.s.o:
libc/sysdeps/linux/common/getpagesize.s.o:
libc/sysdeps/linux/common/getdirname.s.o:
libc/sysdeps/linux/common/gethostname.s.o:
libc/sysdeps/linux/common/getsid.s.o:
libc/sysdeps/linux/common/getdents.s.o:
libc/sysdeps/linux/common/longjmp.s.o:
libc/sysdeps/linux/common/creat.s.o:
libc/misc/elf/dl-iterate-phdr.s.o:
libc/misc/wordexp/wordexp.s.o:
libc/misc/time/_time_localtime_tzi.s.o:
libc/misc/time/_time_mktime_tzi.s.o:
libc/misc/time/timegm.s.o:
libc/misc/time/dysize.s.o:
libc/misc/time/_time_mktime.s.o:
libc/misc/time/__time_tm.s.o:
libc/misc/time/_time_t2tm.s.o:
libc/misc/time/tzset.s.o:
libc/misc/time/strptime.s.o:
libc/misc/time/strftime.s.o:
libc/misc/time/mktime.s.o:
libc/misc/time/localtime_r.s.o:
libc/misc/time/localtime.s.o:
libc/misc/time/gmtime_r.s.o:
libc/misc/time/gmtime.s.o:
libc/misc/time/ftime.s.o:
libc/misc/time/ctime_r.s.o:
libc/misc/time/ctime.s.o:
libc/misc/time/asctime_r.s.o:
libc/misc/time/asctime.s.o:
libc/misc/time/time.s.o:
libc/misc/search/twalk.s.o:
libc/misc/search/tsearch.s.o:
libc/misc/search/tfind.s.o:
libc/misc/search/tdestroy.s.o:
libc/misc/search/tdelete.s.o:
libc/misc/search/remque.s.o:
libc/misc/search/lsearch.s.o:
libc/misc/search/lfind.s.o:
libc/misc/search/insremque.s.o:
libc/misc/search/insque.s.o:
libc/misc/search/hsearch_r.s.o:
libc/misc/search/hsearch.s.o:
libc/misc/search/hdestroy_r.s.o:
libc/misc/search/hcreate_r.s.o:
libc/misc/regex/regex_old.s.o:
libc/misc/locale/setlocale.s.o:
libc/misc/locale/nl_langinfo.s.o:
libc/misc/locale/localeconv.s.o:
libc/misc/locale/locale.s.o:
libc/misc/internals/tempname.s.o:
libc/misc/internals/parse_config.s.o:
libc/misc/internals/__uClibc_main.s.o:
libc/misc/internals/__h_errno_location.s.o:
libc/misc/internals/__errno_location.s.o:
libc/misc/internals/h_errno.s.o:
libc/misc/internals/errno.s.o:
libc/misc/glob/glob.s.o:
libc/misc/fnmatch/fnmatch.s.o:
libc/misc/error/err.s.o:
libc/misc/dirent/telldir.s.o:
libc/misc/dirent/seekdir.s.o:
libc/misc/dirent/scandir.s.o:
libc/misc/dirent/rewinddir.s.o:
libc/misc/dirent/readdir_r.s.o:
libc/misc/dirent/readdir.s.o:
libc/misc/dirent/opendir.s.o:
libc/misc/dirent/dirfd.s.o:
libc/misc/dirent/closedir.s.o:
libc/misc/dirent/alphasort.s.o:
libc/misc/ctype/isctype.s.o:
libc/misc/ctype/__ctype_assert.s.o:
libc/misc/ctype/__ctype_toupper_loc.s.o:
libc/misc/ctype/__ctype_tolower_loc.s.o:
libc/misc/ctype/__ctype_b_loc.s.o:
libc/misc/ctype/__C_ctype_toupper.s.o:
libc/misc/ctype/__C_ctype_tolower.s.o:
libc/misc/ctype/__C_ctype_b.s.o:
libc/misc/ctype/toupper.s.o:
libc/misc/ctype/tolower.s.o:
libc/misc/ctype/isxdigit.s.o:
libc/misc/ctype/isupper.s.o:
libc/misc/ctype/isspace.s.o:
libc/misc/ctype/ispunct.s.o:
libc/misc/ctype/isprint.s.o:
libc/misc/ctype/islower.s.o:
libc/misc/ctype/isgraph.s.o:
libc/misc/ctype/isdigit.s.o:
libc/misc/ctype/iscntrl.s.o:
libc/misc/ctype/isblank.s.o:
libc/misc/ctype/isascii.s.o:
libc/misc/ctype/isalpha.s.o:
libc/misc/ctype/isalnum.s.o:
libc/misc/ctype/ctype.s.o:
libc/misc/assert/__assert.s.o:
libc/stdio/vprintf.s.o:
libc/stdio/vsprintf.s.o:
libc/stdio/vsnprintf.s.o:
libc/stdio/_ppfs_parsespec.s.o:
libc/stdio/_ppfs_setargs.s.o:
libc/stdio/_ppfs_prepargs.s.o:
libc/stdio/_ppfs_init.s.o:
libc/stdio/vfprintf.s.o:
libc/stdio/_vfprintf_internal.s.o:
libc/stdio/_vfprintf.s.o:
libc/stdio/vdprintf.s.o:
libc/stdio/vasprintf.s.o:
libc/stdio/ungetc.s.o:
libc/stdio/tmpfile.s.o:
libc/stdio/sprintf.s.o:
libc/stdio/snprintf.s.o:
libc/stdio/setlinebuf.s.o:
libc/stdio/setbuffer.s.o:
libc/stdio/setbuf.s.o:
libc/stdio/setvbuf.s.o:
libc/stdio/vsscanf.s.o:
libc/stdio/vscanf.s.o:
libc/stdio/fscanf.s.o:
libc/stdio/sscanf.s.o:
libc/stdio/scanf.s.o:
libc/stdio/__psfs_do_numeric.s.o:
libc/stdio/__psfs_parse_spec.s.o:
libc/stdio/__scan_cookie.s.o:
libc/stdio/vfscanf.s.o:
libc/stdio/_scanf.s.o:
libc/stdio/rewind.s.o:
libc/stdio/remove.s.o:
libc/stdio/puts.s.o:
libc/stdio/putchar.__DO_UNLOCKED.s.o:
libc/stdio/putchar.s.o:
libc/stdio/printf.s.o:
libc/stdio/perror.s.o:
libc/stdio/getline.s.o:
libc/stdio/getdelim.s.o:
libc/stdio/getchar.s.o:
libc/stdio/fwrite.__DO_UNLOCKED.s.o:
libc/stdio/fwrite.s.o:
libc/stdio/funlockfile.s.o:
libc/stdio/ftello.s.o:
libc/stdio/fsetpos.s.o:
libc/stdio/fseeko.s.o:
libc/stdio/fread.__DO_UNLOCKED.s.o:
libc/stdio/fread.s.o:
libc/stdio/fprintf.s.o:
libc/stdio/fputc.__DO_UNLOCKED.s.o:
libc/stdio/fputc.s.o:
libc/stdio/fputs.__DO_UNLOCKED.s.o:
libc/stdio/fputs.s.o:
libc/stdio/freopen.s.o:
libc/stdio/fopen.s.o:
libc/stdio/flockfile.s.o:
libc/stdio/fileno.__DO_UNLOCKED.s.o:
libc/stdio/fileno.s.o:
libc/stdio/fgets.__DO_UNLOCKED.s.o:
libc/stdio/fgets.s.o:
libc/stdio/fgetpos.s.o:
libc/stdio/fgetc.__DO_UNLOCKED.s.o:
libc/stdio/fgetc.s.o:
libc/stdio/fflush.__DO_UNLOCKED.s.o:
libc/stdio/fflush.s.o:
libc/stdio/ferror.__DO_UNLOCKED.s.o:
libc/stdio/ferror.s.o:
libc/stdio/feof.__DO_UNLOCKED.s.o:
libc/stdio/feof.s.o:
libc/stdio/fdopen.s.o:
libc/stdio/fcloseall.s.o:
libc/stdio/fclose.s.o:
libc/stdio/dprintf.s.o:
libc/stdio/clearerr.__DO_UNLOCKED.s.o:
libc/stdio/clearerr.s.o:
libc/stdio/asprintf.s.o:
libc/stdio/_wcommit.s.o:
libc/stdio/_uintmaxtostr.s.o:
libc/stdio/_trans2w.s.o:
libc/stdio/_trans2r.s.o:
libc/stdio/_store_inttype.s.o:
libc/stdio/_stdio.s.o:
libc/stdio/_rfill.s.o:
libc/stdio/_load_inttype.s.o:
libc/stdio/_WRITE.s.o:
libc/stdio/_READ.s.o:
libc/stdio/_fwrite.s.o:
libc/stdio/_fpmaxtostr.s.o:
libc/stdio/_fopen.s.o:
libc/stdio/_cs_funcs.s.o:
libc/stdio/_adjust_pos.s.o:
libc/stdio/__fsetlocking.s.o:
libc/stdlib/malloc-standard/realloc.s.o:
libc/stdlib/malloc-standard/memalign.s.o:
libc/stdlib/malloc-standard/mallopt.s.o:
libc/stdlib/malloc-standard/malloc.s.o:
libc/stdlib/malloc-standard/mallinfo.s.o:
libc/stdlib/malloc-standard/free.s.o:
libc/stdlib/malloc-standard/calloc.s.o:
libc/stdlib/strtoull.s.o:
libc/stdlib/strtoul.s.o:
libc/stdlib/strtoll.s.o:
libc/stdlib/strtol.s.o:
libc/stdlib/stdlib.s.o:
libc/stdlib/srand48_r.s.o:
libc/stdlib/srand48.s.o:
libc/stdlib/setenv.s.o:
libc/stdlib/realpath.s.o:
libc/stdlib/random_r.s.o:
libc/stdlib/random.s.o:
libc/stdlib/rand_r.s.o:
libc/stdlib/rand.s.o:
libc/stdlib/qsort_r.s.o:
libc/stdlib/qsort.s.o:
libc/stdlib/posix_memalign.s.o:
libc/stdlib/on_exit.s.o:
libc/stdlib/nrand48_r.s.o:
libc/stdlib/nrand48.s.o:
libc/stdlib/mkstemp64.s.o:
libc/stdlib/mkstemp.s.o:
libc/stdlib/mkostemp.s.o:
libc/stdlib/lrand48_r.s.o:
libc/stdlib/lrand48.s.o:
libc/stdlib/lldiv.s.o:
libc/stdlib/llabs.s.o:
libc/stdlib/ldiv.s.o:
libc/stdlib/labs.s.o:
libc/stdlib/jrand48_r.s.o:
libc/stdlib/jrand48.s.o:
libc/stdlib/getenv.s.o:
libc/stdlib/gcvt.s.o:
libc/stdlib/exit.s.o:
libc/stdlib/div.s.o:
libc/stdlib/bsearch.s.o:
libc/stdlib/atoll.s.o:
libc/stdlib/atol.s.o:
libc/stdlib/atoi.s.o:
libc/stdlib/abs.s.o:
libc/stdlib/abort.s.o:
libc/stdlib/_stdlib_strto_ll.s.o:
libc/stdlib/_stdlib_strto_l.s.o:
libc/stdlib/__uc_malloc.s.o:
libc/stdlib/__strtofpmax.s.o:
libc/stdlib/__exit_handler.s.o:
libc/stdlib/__cxa_atexit.s.o:
libc/signal/sigjmp.s.o:
libc/signal/sigsetops.s.o:
libc/signal/sigismem.s.o:
libc/signal/sigfillset.s.o:
libc/signal/sigempty.s.o:
libc/signal/sigdelset.s.o:
libc/signal/sigandset.s.o:
libc/signal/sigaddset.s.o:
libc/signal/raise.s.o:
libc/signal/allocrtsig.s.o:
libc/unistd/sleep.s.o:
libc/unistd/getopt.s.o:
libc/unistd/getlogin.s.o:
libc/pwd_grp/__pgsreader.s.o:
libc/pwd_grp/__parsegrent.s.o:
libc/pwd_grp/__parsepwent.s.o:
libc/pwd_grp/getpwent_r.s.o:
libc/pwd_grp/getpwent.s.o:
libc/pwd_grp/getpwnam_r.s.o:
libc/pwd_grp/getpwnam.s.o:
libc/pwd_grp/getpwuid_r.s.o:
libc/pwd_grp/getpwuid.s.o:
libc/pwd_grp/getgrnam_r.s.o:
libc/pwd_grp/getgrnam.s.o:
libc/pwd_grp/getgrgid_r.s.o:
libc/pwd_grp/getgrgid.s.o:
libc/pwd_grp/pwd_grp.s.o:
libc/inet/resolv.s.o:
libc/inet/res_query.s.o:
libc/inet/res_init.s.o:
libc/inet/res_comp.s.o:
libc/inet/read_etc_hosts_r.s.o:
libc/inet/opensock.s.o:
libc/inet/opennameservers.s.o:
libc/inet/ntop.s.o:
libc/inet/ntohl.s.o:
libc/inet/ns_name.s.o:
libc/inet/lengthq.s.o:
libc/inet/lengthd.s.o:
libc/inet/in6_addr.s.o:
libc/inet/inet_ntoa.s.o:
libc/inet/inet_netof.s.o:
libc/inet/inet_net.s.o:
libc/inet/inet_makeaddr.s.o:
libc/inet/inet_lnaof.s.o:
libc/inet/inet_aton.s.o:
libc/inet/inet_addr.s.o:
libc/inet/if_index.s.o:
libc/inet/herror.s.o:
libc/inet/getservice.s.o:
libc/inet/getproto.s.o:
libc/inet/getnet.s.o:
libc/inet/gethostent_r.s.o:
libc/inet/gethostent.s.o:
libc/inet/gethostbyname_r.s.o:
libc/inet/gethostbyname2_r.s.o:
libc/inet/gethostbyname2.s.o:
libc/inet/gethostbyname.s.o:
libc/inet/gethostbyaddr_r.s.o:
libc/inet/gethostbyaddr.s.o:
libc/inet/getaddrinfo.s.o:
libc/inet/get_hosts_byname_r.s.o:
libc/inet/get_hosts_byaddr_r.s.o:
libc/inet/gai_strerror.s.o:
libc/inet/formquery.s.o:
libc/inet/ether_addr.s.o:
libc/inet/encodeq.s.o:
libc/inet/encodep.s.o:
libc/inet/encodeh.s.o:
libc/inet/encoded.s.o:
libc/inet/encodea.s.o:
libc/inet/dnslookup.s.o:
libc/inet/decodeq.s.o:
libc/inet/decodep.s.o:
libc/inet/decodeh.s.o:
libc/inet/decoded.s.o:
libc/inet/decodea.s.o:
libc/inet/closenameservers.s.o:
libc/inet/addr.s.o:
libc/inet/_res_state.s.o:
libc/string/strpbrk.s.o:
libc/string/generic/strtok_r.s.o:
libc/string/generic/strstr.s.o:
libc/string/generic/strspn.s.o:
libc/string/generic/strsep.s.o:
libc/string/generic/strcspn.s.o:
libc/string/i386/strchrnul.s.o:
libc/string/i386/rawmemchr.s.o:
libc/string/generic/memrchr.s.o:
libc/string/generic/mempcpy.s.o:
libc/string/generic/memmem.s.o:
libc/string/generic/memcmp.s.o:
libc/string/i386/strrchr.s.o:
libc/string/i386/strnlen.s.o:
libc/string/i386/strncpy.s.o:
libc/string/i386/strncmp.s.o:
libc/string/i386/strncat.s.o:
libc/string/i386/strlen.s.o:
libc/string/i386/strcpy.s.o:
libc/string/i386/strcmp.s.o:
libc/string/i386/strchr.s.o:
libc/string/i386/strcat.s.o:
libc/string/i386/memset.s.o:
libc/string/i386/memmove.s.o:
libc/string/i386/memcpy.s.o:
libc/string/i386/memchr.s.o:
libc/string/bzero.s.o:
libc/string/bcopy.s.o:
libc/string/strtok.s.o:
libc/string/strncasecmp.s.o:
libc/string/strndup.s.o:
libc/string/sys_errlist.s.o:
libc/string/strlcpy.s.o:
libc/string/strlcat.s.o:
libc/string/__xpg_basename.s.o:
libc/string/psignal.s.o:
libc/string/strsignal.s.o:
libc/string/sys_siglist.s.o:
libc/string/_string_syssigmsgs.s.o:
libc/string/__glibc_strerror_r.s.o:
libc/string/_string_syserrmsgs.s.o:
libc/string/__xpg_strerror_r.s.o:
libc/string/strerror.s.o:
libc/string/strdup.s.o:
libc/string/strcasestr.s.o:
libc/string/strcasecmp.s.o:
libc/string/stpncpy.s.o:
libc/string/stpcpy.s.o:
libc/string/memccpy.s.o:
libc/string/ffs.s.o:
libc/string/dirname.s.o:
libc/string/basename.s.o:
libc/sysdeps/linux/i386/__longjmp.s.o:
libc/sysdeps/linux/i386/bsd-_setjmp.s.o:
libc/sysdeps/linux/i386/bsd-setjmp.s.o:
libc/sysdeps/linux/i386/setjmp.s.o:
/usr/lib/gcc/x86_64-linux-gnu/5/32/crtbeginS.o:
/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/crti.s.o:
/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/main_rel.ld:
