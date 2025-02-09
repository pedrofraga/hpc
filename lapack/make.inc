####################################################################
#  LAPACK make include file.                                       #
#  LAPACK, Version 3.8.0                                           #
#  November 2017                                                   #
####################################################################

SHELL = /bin/sh

#  CC is the C compiler, normally invoked with options CFLAGS.
#
CC     = gcc
CFLAGS = -O3

#  Modify the FORTRAN and OPTS definitions to refer to the compiler
#  and desired compiler options for your machine.  NOOPT refers to
#  the compiler options desired when NO OPTIMIZATION is selected.
#
#  Note: During a regular execution, LAPACK might create NaN and Inf
#  and handle these quantities appropriately. As a consequence, one
#  should not compile LAPACK with flags such as -ffpe-trap=overflow.
#
FORTRAN = gfortran
OPTS    = -O2 -frecursive
DRVOPTS = $(OPTS)
NOOPT   = -O0 -frecursive

#  Define LOADER and LOADOPTS to refer to the loader and desired
#  load options for your machine.
#
LOADER   = gfortran
LOADOPTS =

#  The archiver and the flag(s) to use when building an archive
#  (library).  If your system has no ranlib, set RANLIB = echo.
#
ARCH      = ar
ARCHFLAGS = cr
RANLIB    = ranlib

#  Timer for the SECOND and DSECND routines
#
#  Default:  SECOND and DSECND will use a call to the
#  EXTERNAL FUNCTION ETIME
#TIMER = EXT_ETIME
#  For RS6K:  SECOND and DSECND will use a call to the
#  EXTERNAL FUNCTION ETIME_
#TIMER = EXT_ETIME_
#  For gfortran compiler:  SECOND and DSECND will use a call to the
#  INTERNAL FUNCTION ETIME
TIMER = INT_ETIME
#  If your Fortran compiler does not provide etime (like Nag Fortran
#  Compiler, etc...) SECOND and DSECND will use a call to the
#  INTERNAL FUNCTION CPU_TIME
#TIMER = INT_CPU_TIME
#  If none of these work, you can use the NONE value.
#  In that case, SECOND and DSECND will always return 0.
#TIMER = NONE

#  Uncomment the following line to include deprecated routines in
#  the LAPACK library.
#
#BUILD_DEPRECATED = Yes

#  LAPACKE has the interface to some routines from tmglib.
#  If LAPACKE_WITH_TMG is defined, add those routines to LAPACKE.
#
#LAPACKE_WITH_TMG = Yes

#  Location of the extended-precision BLAS (XBLAS) Fortran library
#  used for building and testing extended-precision routines.  The
#  relevant routines will be compiled and XBLAS will be linked only
#  if USEXBLAS is defined.
#
#USEXBLAS = Yes
#XBLASLIB = -lxblas

#  The location of the libraries to which you will link.  (The
#  machine-specific, optimized BLAS library should be used whenever
#  possible.)
#
#BLASLIB = ../../blas$(PLAT).a
BLASLIB = /usr/local/atlas/lib/libf77blas.a /usr/local/atlas/lib/libatlas.a
CBLASLIB     = ../../libcblas.a
LAPACKLIB    = liblapack.a
TMGLIB       = libtmglib.a
LAPACKELIB   = liblapacke.a
