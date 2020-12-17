//  Copyright (C) 2020-? T. Mitchell Kelleher
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef BSTC__VECTOR_H
#define BSTC__VECTOR_H


#include <bstc/config.h>
#include <bstc/assert.h>
#include <bstc/ctuple.h>
#include <bstc/stdint.h>
#include <bstc/string.h>
#include <bstc/template.h>
#include <bstc/detail/vector.h>


/* Provide interface without namespace */
/// \{
#ifdef BSTC_NO_NAMESPACE
#define vect_tmplt_t bstc_vect_tmplt_t
#define vect_t bstc_vect_t
#define vect_init bstc_vect_init
#define vect_destroy bstc_vect_destroy
#define vect_len bstc_vect_len
#define vect_cap bstc_vect_cap
#define vect_rsz bstc_vect_rsz
#define vect_rsv bstc_vect_rsv
#define vect_empty bstc_vect_empty
#define vect_front bstc_vect_front
#define vect_back bstc_vect_back
#define vect_push bstc_vect_push
#define vect_begin bstc_vect_begin
#define vect_end bstc_vect_end
#define vect_rbegin bstc_vect_rbegin
#define vect_rend bstc_vect_rend


#define vect_iter_t bstc_vect_iter_t
#define vect_iter_nxt bstc_vect_iter_nxt
#define vect_iter_eq bstc_vect_iter_eq
#define vect_iter_val bstc_vect_iter_val
#define vect_iter_set bstc_vect_iter_set


#define vect_riter_t bstc_vect_riter_t
#define vect_riter_nxt bstc_vect_riter_nxt
#define vect_riter_eq bstc_vect_riter_eq
#define vect_riter_val bstc_vect_riter_val
#define vect_riter_set bstc_vect_riter_set
#endif
/// \}


/** Declares the vector template type.
 * \param T The type of the data in the vector.
 * \param alloc An optional argument which is the allocator for the template type.
 */
/// \{
#ifdef BSTC_NO_NAMESPACE
# define bstc_vect_tmplt_t(T, ...) \
    bstc_tmplt_isa(bstc_vect_tmplt_ ## T,\
        bstc_vect_tmplt_ ## T,\
        bstc_tmplt_isa(vect_tmplt_ ## T,\
            vect_tmplt_ ## T,\
            bstc_dtl_vect_tmplt_t(T, __VA_ARGS__)\
        )\
    )
#else
# define bstc_vect_tmplt_t(T, ...)  \
    bstc_tmplt_isa(bstc_vect_tmplt_ ## T,\
        bstc_vect_tmplt_ ## T,\
        bstc_dtl_vect_tmplt_t(T, __VA_ARGS__)\
    )
#endif
/// \}


/** Declares the vector type.
 * \param T The template type of the vector or the type of the vector.
 */
#define bstc_vect_t(T) bstc_tmplt_isa(T, bstc_tmplt_type(T), T*)


/** Initializes the vector structure.
 * \param vect Reference to the vector.
 */
#define bstc_vect_init(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_init(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_init(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )


/** Destroys and frees any memory allocated for the vector.
 * \param vect Reference to the vector.
 * \return Returns one when successful and zero otherwise.
 */
#define bstc_vect_destroy(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_destroy(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_destroy(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )


/** Gets the number of items that have been added or resized to.
 * \param vect Reference to the vector.
 * \return Returns the number of items.
 */
#define bstc_vect_len(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_len(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_len(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )


/** Gets the capacity that the vector has been allocated for.
 * \param vect Reference to the vector.
 * \return Returns the capacity for the vector.
 */
#define bstc_vect_cap(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_cap(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_cap(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )


/** Resizes the vector to be able to hold the new size.
 * \param vect Reference to the vector.
 * \param nsz The new size for the vector.
 * \return Returns the new size.
 */
#define bstc_vect_rsz(vect, nsz, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_rsz(vect)(vect, nsz, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_rsz(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect, nsz)\
    )


/** Reserves the requested capacity for the vector by only reserving more.
 * \param vect Reference to the vector.
 * \param ncap The new capacity for the vector.
 * \return Returns the new capacity.
 */
#define bstc_vect_rsv(vect, ncap, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_rsv(vect)(vect, ncap, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_rsv(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect, ncap)\
    )


/** Assert at the index provided then read the value in the array.
 * \param vect Reference to the vector.
 * \param i The index to access.
 * \return Returns the value at the index.
 */
#define bstc_vect_at(vect, i, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_at(vect)(vect, i, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_at(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect, i)\
    )


/** Checks to see if the vector is empty.
 * \param vect Reference to the vector.
 * \return Returns one if empty and zero otherwise.
 */
#define bstc_vect_empty(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_empty(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_empty(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )


/** Get the front value of the vector.
 * \param vect Reference to the vector.
 * \return Returns the value at the first index.
 */
#define bstc_vect_front(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_front(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_front(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )


/** Get the back value of the vector.
 * \param vect Reference to the vector.
 * \return Returns the value at the last index.
 */
#define bstc_vect_back(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_back(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_back(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )


/** Pushes a single value onto the back of the vector and resizes if needed.
 * \param vect Reference to the vector.
 * \param val The value to push on.
 * \return Returns the new value pushed on.
 */
#define bstc_vect_push(vect, val, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_push(vect)(vect, val, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_push(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect, val)\
    )


#define bstc_vect_begin(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_begin(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_begin(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )
#define bstc_vect_end(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_end(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_end(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )


#define bstc_vect_rbegin(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_rbegin(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_rbegin(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )
#define bstc_vect_rend(vect, ...) \
    bstc_tmplt_isa(vect,\
        bstc_dtl_vect_get_rend(vect)(vect, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_rend(bstc_tmplt_ctuple_alloc(bstc_alloc_stdlib), vect)\
    )


#define bstc_vect_iter_t(tmplt) bstc_iter_t(bstc_tmplt_iter(tmplt))
#define bstc_vect_iter_nxt(iter, ...) \
    bstc_tmplt_isa(iter,\
        bstc_iter_nxt(bstc_tmplt_iter(iter))(bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_iter_nxt(iter)\
    )
#define bstc_vect_iter_eq(left, right, ...) \
    bstc_tmplt_isa(left,\
        bstc_iter_eq(bstc_tmplt_iter(left))(right, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_iter_eq(left, right)\
    )
#define bstc_vect_iter_val(iter, ...) \
    bstc_tmplt_isa(iter,\
        bstc_iter_val(bstc_tmplt_iter(iter))(bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_iter_val(iter)\
    )
#define bstc_vect_iter_set(iter, val, ...) \
    bstc_tmplt_isa(iter,\
        bstc_iter_set(bstc_tmplt_iter(iter))(val, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_iter_set(iter, val)\
    )
#define bstc_vect_iter_swap(left, right, ...) \
    bstc_tmplt_isa(left,\
        bstc_iter_swap(bstc_tmplt_iter(left))(right, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_iter_swap(left, right)\
    )


#define bstc_vect_riter_t(tmplt) bstc_iter_t(bstc_tmplt_riter(tmplt))
#define bstc_vect_riter_nxt(iter, ...) \
    bstc_tmplt_isa(iter,\
        bstc_iter_nxt(bstc_tmplt_riter(iter))(bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_riter_nxt(iter)\
    )
#define bstc_vect_riter_eq(left, right, ...) \
    bstc_tmplt_isa(left,\
        bstc_iter_eq(bstc_tmplt_riter(left))(right, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_riter_eq(left, right)\
    )
#define bstc_vect_riter_val(iter, ...) \
    bstc_tmplt_isa(iter,\
        bstc_iter_val(bstc_tmplt_riter(iter))(bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_riter_val(iter)\
    )
#define bstc_vect_riter_set(iter, val, ...) \
    bstc_tmplt_isa(iter,\
        bstc_iter_set(bstc_tmplt_riter(iter))(val, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_riter_set(iter, val)\
    )
#define bstc_vect_riter_swap(left, right, ...) \
    bstc_tmplt_isa(left,\
        bstc_iter_swap(bstc_tmplt_riter(left))(right, bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0)),\
        bstc_dtl_vect_riter_swap(left, right)\
    )


#endif // BSTC__VECTOR_H