//  Copyright (C) 2020-? T. Mitchell Kelleher
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOSTC__CONFIG__SELECT_COMPILER_H
#define BOOSTC__CONFIG__SELECT_COMPILER_H


/* Determine the compiler. */
/// \{
#ifndef BSTC_COMPILER_CONFIG
# if defined(_GCCXML)
#  define BSTC_COMPILER_GCCXML
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/gccxml.h"
#  include <boostc/config/compiler/gccxml.h>
# elif defined(__clang__)
#  define BSTC_COMPILER_CLANG
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/clang.h"
#  include <boostc/config/compiler/clang.h>
# elif defined(__WATCOMC__)
#  define BSTC_COMPILER_WATCOM
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/watcom.h"
#  include <boostc/config/compiler/watcom.h>
# elif defined(__BORLANDC__)
#  define BSTC_COMPILER_BORLAND
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/borland.h"
#  include <boostc/config/compiler/borland.h>
# elif defined(__GNUC__) && !defined(__ibmxl__)
#  define BSTC_COMPILER_GCC
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/gcc.h"
#  include <boostc/config/compiler/gcc.h>
# elif defined(__TINYC__)
#  define BSTC_COMPILER_TCC
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/tcc.h"
#  include <boostc/config/compiler/tcc.h>
# elif defined(_CRAYC)
#  define BSTC_COMPILER_CRAY
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/cray.h"
#  include <boostc/config/compiler/cray.h>
# elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
#  define BSTC_COMPILER_INTEL
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/intel.h"
#  include <boostc/config/compiler/intel.h>
# elif defined(_MSC_VER)
#  define BSTC_COMPILER_VISUALC
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/visualc.h"
#  include <boostc/config/compiler/visualc.h>
# elif defined(__EMSCRIPTEN__)
#  define BSTC_COMPILER_EMSCRIPTEN
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/emscripten.h"
#  include <boostc/config/compiler/emscripten.h>
# elif defined(__MINGW32__)
#  define BSTC_COMPILER_MINGW32
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/mingw32.h"
#  include <boostc/config/compiler/mingw32.h>
# elif defined(__MINGW64__)
#  define BSTC_COMPILER_MINGW64
#  define BSTC_COMPILER_CONFIG "boostc/config/compiler/mingw64.h"
#  include <boostc/config/compiler/mingw64.h>
# else
#  define BSTC_COMPILER_UNKNOWN
# endif
#endif
/// \}


#endif // BOOSTC__CONFIG__SELECT_COMPILER_H
