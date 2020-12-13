//  Copyright (C) 2020-? T. Mitchell Kelleher
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef BST__CONFIG_H
#define BST__CONFIG_H


#include <bst/config/version.h>


/* Default is to provide BST with no namespaces and namespaced */
/// \{
#if !defined(BST_NAMESPACE_ONLY) && !defined(BST_NO_NAMESPACE)
#define BST_NO_NAMESPACE
#endif
/// \}


#include <bst/config/macros.h>


/* Configure the compiler */
/// \{
#if !defined(BST_COMPILER_CONFIG) && !defined(BST_NO_COMPILER_CONFIG) && !defined(BST_NO_CONFIG)
# include <bst/config/select_compiler.h>
#endif
#ifdef BST_COMPILER_CONFIG
# include BST_COMPILER_CONFIG
#endif
/// \}


/* Configure the platform */
/// \{
#if !defined(BST_PLATFORM_CONFIG) && !defined(BST_NO_PLATFORM_CONFIG) && !defined(BST_NO_CONFIG)
# include <bst/config/select_platform.h>
#endif
#ifdef BST_PLATFORM_CONFIG
# include BST_PLATFORM_CONFIG
#endif
/// \}


/* Ensure macros are defined */
/// \{
// Note that the processors typically handle branch prediction better for the likely case.
// Therein, the best time to use these is when you are dealing with the unlikely case.
// https://medium.com/software-design/likely-unlikely-directives-802c09bd5232
// Note that it is faster to merely write the code such that the most common case is always first.
// It is only better in the case where the most common case is not first.
// https://stackoverflow.com/questions/35938249/optimizing-a-branch-for-a-known-more-common-path/35940041#35940041
#ifndef BST_LIKELY
# define BST_LIKELY(x) x
#endif
#ifndef BST_UNLIKELY
# define BST_UNLIKELY(x) x
#endif


#if !(defined(BST_NO_STDATOMICS) || defined(BST_HAS_STDATOMICS))
# if (defined(__STDC_NO_ATOMICS__) && (__STDC_NO_ATOMICS__ == 1)) || !defined(BST_LEAST_C11)
#  define BST_NO_STDATOMICS
# else
#  define BST_HAS_STDATOMICS
# endif
#endif


#if !defined(BST_INTPTR_NBITS)
# if defined(__alpha__) || defined(__ia64__) || defined(__x86_64__) || defined(_WIN64) || defined(__ppc64__)
#  define BST_INTPTR_NBITS 64
# elif defined(__WATCOMC__) || defined(__TURBOC__)
#  if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#    define BST_INTPTR_NBITS 16
#  else
#    define BST_INTPTR_NBITS 32
#  endif
# elif defined(__i386__) || defined(_WIN32) || defined(WIN32) || defined(__ppc64__)
#  define BST_INTPTR_NBITS 32
# elif defined(BST_COMPILER_INTEL)
// If made it this far, it typically is a 32 bit system.
#  define BST_INTPTR_NBITS 32
# else
#  error "Could not determine BST_INTPTR_NBITS."
# endif
#endif


#if !defined(BST_HAS_LONG_LONG) && !defined(BST_NO_LONG_LONG) && !defined(BST_MSVC) && !defined(__BORLANDC__)
# ifdef __cplusplus
#  include <climits>
# else
#  include <limits.h>
# endif
# if (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
#   define BST_HAS_LONG_LONG
# else
#   define BST_NO_LONG_LONG
# endif
#endif


#if !defined(BST_HAS_VA_ARGS_PASTE) && !defined(BST_NO_VA_ARGS_PASTE)
# define BST_NO_VA_ARGS_PASTE
#endif
/// \}


/* Provide a null type */
/// \{
#ifndef bst_null
# ifdef BST_LEAST_CPP11
#  define bst_null nullptr
# else
#  define bst_null 0
# endif
#endif
/// \}


/* Provide a way to unpack tuples */
/// \{
#ifndef BST_UNPACK
# define BST_UNPACK(...) __VA_ARGS__
#endif
/// \}


/* Provide a way to detect if a tuple */
/// \{
#ifndef BST_ISA_TUPLE
# define BST_ISA_TUPLE(tpl, _t, _f) BST_DTL_ISA_TUPLE_CALL(BST_DTL_ISA_TUPLE_SELECT(tpl,unused), _t, _f)
# define BST_DTL_ISA_TUPLE_CALL(F, _t, _f) F(_t, _f)
# define BST_DTL_ISA_TUPLE_SELECT(tpl,U) BST_JOIN2(BST_DTL_ISA_TUPLE, BST_DTL_ISA_TUPLE_SELECT_(tpl, unused))
# define BST_DTL_ISA_TUPLE_SELECT_(tpl,U) BST_ARGCNT(0, BST_DTL_ISA_TUPLE_EXPAND tpl)
# define BST_DTL_ISA_TUPLE2(_t, _f) _f
# define BST_DTL_ISA_TUPLE3(_t, _f) _t
# define BST_DTL_ISA_TUPLE_EXPAND(...) 0, 0
#endif
/// \}


/* Provide a way to detect if-empty character is first */
/// \{
#ifndef BST_IF_ARG0_EMPTY
# ifdef BST_HAS_VA_ARGS_PASTE
#  define BST_IF_ARG0_EMPTY(tpl, _t, _f) BST_EXPAND(BST_IFEQ(BST_DTL_IF_ARG0_EMPTY1(tpl), BST_DTL_IF_ARG0_EMPTY2(tpl), _f, _t))
#  define BST_DTL_IF_ARG0_EMPTY1(tpl) BST_EXPAND(BST_DTL_IF_ARG0_EMPTY1_ tpl)
#  define BST_DTL_IF_ARG0_EMPTY1_(...) BST_DTL_IF_ARG0_EMPTY1__(__VA_ARGS__)
#  define BST_DTL_IF_ARG0_EMPTY1__(A, ...) BST_DTL_IF_ARG0_EMPTY1___(A)
#  define BST_DTL_IF_ARG0_EMPTY1___(...) BST_ARGCNT(0, __VA_ARGS__)
#  define BST_DTL_IF_ARG0_EMPTY2(tpl) BST_EXPAND(BST_DTL_IF_ARG0_EMPTY2_ tpl)
#  define BST_DTL_IF_ARG0_EMPTY2_(...) BST_DTL_IF_ARG0_EMPTY2__(__VA_ARGS__)
#  define BST_DTL_IF_ARG0_EMPTY2__(A, ...) BST_DTL_IF_ARG0_EMPTY2___(A)
#  define BST_DTL_IF_ARG0_EMPTY2___(...) BST_ARGCNT(0, ##__VA_ARGS__)
# else
#  define BST_IF_ARG0_EMPTY(tpl, _t, _f) BST_EXPAND(BST_DTL_IF_ARG0_EMPTY(_t, _f, BST_DTL_IF_ARG0_EMPTY_DETECT(tpl)))
// Need to add detection for () being the first element.
// #  define BST_DTL_IF_ARG0_EMPTY(_t, _f, ...) BST_ARGCNT(__VA_ARGS__)
#  define BST_DTL_IF_ARG0_EMPTY(_t, _f, tpl) BST_EXPAND(BST_IFEQ(BST_ARGCNT tpl, 2, _t, _f))
#  define L 0, 0
#  define BST_DTL_IF_ARG0_EMPTY_DETECT(tpl) BST_EXPAND(BST_DTL_IF_ARG0_EMPTY_DETECT1(unused, BST_UNPACK tpl, unused))
#  define BST_DTL_IF_ARG0_EMPTY_DETECT1(U,...) BST_EXPAND(BST_DTL_IF_ARG0_EMPTY_DETECT2(__VA_ARGS__))
// #  define BST_DTL_IF_ARG0_EMPTY_DETECT2(A,...) L ## A
#  define BST_DTL_IF_ARG0_EMPTY_DETECT2(A,...) (BST_CALL(BST_DTL_IF_ARG0_EMPTY_DETECT3(A, unused), A, unused))
#  define BST_DTL_IF_ARG0_EMPTY_DETECT3(A, U) BST_ISA_TUPLE(A, BST_EXPAND, BST_DTL_IF_ARG0_EMPTY_DETECT4)
#  define BST_DTL_IF_ARG0_EMPTY_DETECT4(A, U) L ## A
# endif
#endif
/// \}


#endif // BST__CONFIG_H
