//  Copyright (C) 2020-? T. Mitchell Kelleher
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef BSTC__DETAIL__VECTOR_H
#define BSTC__DETAIL__VECTOR_H


/* Packs the iterator defaults */
#define bstc_dtl_vect_iter_defaults(T) bstc_ctuple(bstc_dtl_vect_iter_t(T), bstc_dtl_vect_iter_nxt, bstc_dtl_vect_iter_eq, bstc_dtl_vect_iter_val, bstc_dtl_vect_iter_set, bstc_dtl_vect_iter_swap)


#define bstc_dtl_vect_iter_t(T) T*
#define bstc_dtl_vect_iter_nxt(iter) (++iter)
#define bstc_dtl_vect_iter_eq(left, right) (left == right)
#define bstc_dtl_vect_iter_val(iter) *(iter)
#define bstc_dtl_vect_iter_set(iter, val) (*(iter) = val)
#define bstc_dtl_vect_iter_swap(left, right) \
    {\
        char __bstc_dtl_swap[sizeof(*(left))];\
        memcpy((void*)__bstc_dtl_swap, (void*)(left), sizeof(*(left)));\
        memcpy((void*)(left), (void*)(right), sizeof(*(left)));\
        memcpy((void*)(right), (void*)__bstc_dtl_swap, sizeof(*(left)));\
    }


/* Packs the iterator defaults */
#define bstc_dtl_vect_riter_defaults(T) bstc_ctuple(bstc_dtl_vect_riter_t(T), bstc_dtl_vect_riter_nxt, bstc_dtl_vect_riter_eq, bstc_dtl_vect_riter_val, bstc_dtl_vect_riter_set, bstc_dtl_vect_riter_swap)


#define bstc_dtl_vect_riter_t(T) T*
#define bstc_dtl_vect_riter_nxt(riter) (--riter)
#define bstc_dtl_vect_riter_eq(left, right) (left == right)
#define bstc_dtl_vect_riter_val(riter) *((riter)-1)
#define bstc_dtl_vect_riter_set(riter, val) (*((riter)-1) = val)
#define bstc_dtl_vect_riter_swap(left, right) \
    {\
        char __bstc_dtl_swap[sizeof(*(left))];\
        memcpy((void*)__bstc_dtl_swap, (void*)(left), sizeof(*(left)));\
        memcpy((void*)(left), (void*)(right), sizeof(*(left)));\
        memcpy((void*)(right), (void*)__bstc_dtl_swap, sizeof(*(left)));\
    }


/* Detail code */
/// \{
#define bstc_dtl_vect_tmplt_t(T, ...) \
    bstc_ctuple(\
        T*,\
        (T),\
        bstc_dtl_vect_default_fns,\
        bstc_dtl_vect_iter_defaults(T),\
        bstc_dtl_vect_riter_defaults(T),\
        bstc_ctuple_ifempty(bstc_ctuple(__VA_ARGS__),\
            bstc_alloc_stdlib,\
            bstc_alloc_isa(bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0),\
                bstc_ctuple_getI(bstc_ctuple(__VA_ARGS__), 0),\
                BSTC_VECT_BAD_ALLOC_PROVIDED\
            )\
        )\
    )

// Preparing for potential specialization concept.
#define bstc_dtl_vect_default_fns \
    bstc_ctuple(\
        bstc_dtl_vect_init,\
        bstc_dtl_vect_destroy,\
        bstc_dtl_vect_len,\
        bstc_dtl_vect_cap,\
        bstc_dtl_vect_rsz,\
        bstc_dtl_vect_rsv,\
        bstc_dtl_vect_at,\
        bstc_dtl_vect_empty,\
        bstc_dtl_vect_front,\
        bstc_dtl_vect_back,\
        bstc_dtl_vect_push,\
        bstc_dtl_vect_begin,\
        bstc_dtl_vect_end,\
        bstc_dtl_vect_rbegin,\
        bstc_dtl_vect_rend\
    )

#define bstc_dtl_vect_init(tmplt, vect) (*((void**)&(vect)) = bstc_null)
#define bstc_dtl_vect_destroy(tmplt, vect) ((vect) ? bstc_alloc_free(bstc_tmplt_alloc(tmplt))(bstc_dtl_vect_raw_(vect)),*((void**)&(vect))=bstc_null,1 : 0)
#define bstc_dtl_vect_len(tmplt, vect) ((vect) ? (int)bstc_dtl_vect_len_(vect) : 0)
#define bstc_dtl_vect_cap(tmplt, vect) ((vect) ? (int)bstc_dtl_vect_cap_(vect) : 0)
#define bstc_dtl_vect_rsz(tmplt, vect, nsz) \
/* Check to see if the vector has anything allocated yet. */\
((vect) ?\
    /* Check to see if the new size already fits. */\
    (bstc_dtl_vect_cap_(vect) < (nsz) ?\
        /* Since it does not fit, check to see if twice the current size will hold the new size. */\
        (bstc_dtl_vect_cap_(vect)*2 > (nsz) ?\
            (\
                *((void**)&(vect)) = (void*)((bstc_intptr_t*)bstc_alloc_realloc(bstc_tmplt_alloc(tmplt))(\
                    bstc_dtl_vect_raw_(vect),\
                    sizeof(*(vect))*(bstc_dtl_vect_cap_(vect)*2) + 2*sizeof(bstc_intptr_t)\
                ) + 2),\
                bstc_dtl_vect_cap_(vect) = (bstc_dtl_vect_cap_(vect)*2),\
                (bstc_dtl_vect_len_(vect) = (bstc_intptr_t)(nsz))\
            )\
        :\
            (\
                *((void**)&(vect)) = (void*)((bstc_intptr_t*)bstc_alloc_realloc(bstc_tmplt_alloc(tmplt))(\
                    bstc_dtl_vect_raw_(vect),\
                    sizeof(*(vect))*(nsz) + 2*sizeof(bstc_intptr_t)\
                ) + 2),\
                bstc_dtl_vect_cap_(vect) = (bstc_intptr_t)(nsz),\
                (bstc_dtl_vect_len_(vect) = bstc_dtl_vect_cap_(vect))\
            )\
        )\
    :\
        (bstc_dtl_vect_len_(vect) = (bstc_intptr_t)(nsz))\
    )\
:\
    (\
        *((void**)&(vect)) = (void*)((bstc_intptr_t*)bstc_alloc_malloc(bstc_tmplt_alloc(tmplt))(sizeof(*(vect))*(nsz) + 2*sizeof(bstc_intptr_t)) + 2),\
        bstc_dtl_vect_cap_(vect) = (bstc_intptr_t)(nsz),\
        (bstc_dtl_vect_len_(vect) = bstc_dtl_vect_cap_(vect))\
    )\
)
#define bstc_dtl_vect_rsv(tmplt, vect, ncap) \
/* Check to see if the vector has anything allocated yet. */\
((vect) ?\
    /* Check to see if the new capacity already fits. */\
    (bstc_dtl_vect_cap_(vect) < (ncap) ?\
        (\
            *((void**)&(vect)) = (void*)((bstc_intptr_t*)bstc_alloc_realloc(bstc_tmplt_alloc(tmplt))(\
                bstc_dtl_vect_raw_(vect),\
                sizeof(*(vect))*(ncap) + 2*sizeof(bstc_intptr_t)\
            ) + 2),\
            (bstc_dtl_vect_cap_(vect) = (bstc_intptr_t)(ncap))\
        )\
    :\
        (bstc_intptr_t)(ncap)\
    )\
:\
    (\
        *((void**)&(vect)) = (void*)((bstc_intptr_t*)bstc_alloc_malloc(bstc_tmplt_alloc(tmplt))(sizeof(*(vect))*(ncap) + 2*sizeof(bstc_intptr_t)) + 2),\
        bstc_dtl_vect_len_(vect) = 0,\
        (bstc_dtl_vect_cap_(vect) = (bstc_intptr_t)(ncap))\
    )\
)
#define bstc_dtl_vect_at(tmplt, vect, i) (bstc_assert((i) < bstc_vect_len(vect)), (vect)[(i)])
#define bstc_dtl_vect_empty(tmplt, vect) (bstc_vect_len(vect) == 0)
#define bstc_dtl_vect_front(tmplt, vect) (vect)[0]
#define bstc_dtl_vect_back(tmplt, vect) (vect)[bstc_dtl_vect_len_(vect)-1]
#define bstc_dtl_vect_push(tmplt, vect, val) \
/* Check to see if the vector has anything allocated yet. */\
((vect) ?\
    (bstc_dtl_vect_cap_(vect) < (bstc_dtl_vect_len_(vect)+1) ?\
        (\
            *((void**)&(vect)) = (void*)((bstc_intptr_t*)bstc_alloc_realloc(bstc_tmplt_alloc(tmplt))(\
                bstc_dtl_vect_raw_(vect),\
                sizeof(*(vect))*(bstc_dtl_vect_cap_(vect)*2) + 2*sizeof(bstc_intptr_t)\
            ) + 2),\
            bstc_dtl_vect_cap_(vect) *= 2,\
            (vect[bstc_dtl_vect_len_(vect)++] = val)\
        )\
    :\
        (vect[bstc_dtl_vect_len_(vect)++] = val)\
    )\
:\
    (\
        *((void**)&(vect)) = (void*)((bstc_intptr_t*)bstc_alloc_malloc(bstc_tmplt_alloc(tmplt))(sizeof(*(vect))*4 + 2*sizeof(bstc_intptr_t)) + 2),\
        bstc_dtl_vect_len_(vect) = (bstc_intptr_t)(1),\
        bstc_dtl_vect_cap_(vect) = (bstc_intptr_t)(4),\
        (vect[0] = val)\
    )\
)
#define bstc_dtl_vect_begin(tmplt, vect) (vect)
#define bstc_dtl_vect_end(tmplt, vect) ((vect)+bstc_vect_len(vect))
#define bstc_dtl_vect_rbegin(tmplt, vect) ((vect)+bstc_vect_len(vect))
#define bstc_dtl_vect_rend(tmplt, vect) ((vect)+1)

#define bstc_dtl_vect_get_init(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 0)
#define bstc_dtl_vect_get_destroy(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 1)
#define bstc_dtl_vect_get_len(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 2)
#define bstc_dtl_vect_get_cap(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 3)
#define bstc_dtl_vect_get_rsz(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 4)
#define bstc_dtl_vect_get_rsv(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 5)
#define bstc_dtl_vect_get_at(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 6)
#define bstc_dtl_vect_get_empty(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 7)
#define bstc_dtl_vect_get_front(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 8)
#define bstc_dtl_vect_get_back(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 9)
#define bstc_dtl_vect_get_push(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 10)
#define bstc_dtl_vect_get_begin(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 11)
#define bstc_dtl_vect_get_end(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 12)
#define bstc_dtl_vect_get_rbegin(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 13)
#define bstc_dtl_vect_get_rend(tmplt) bstc_ctuple_getI(bstc_tmplt_fns(tmplt), 14)


// The type bstc_intptr_t is used because the memory may need to be word aligned.
// This does assume that bstc_intptr_t causes the memory to be word aligned.
#define bstc_dtl_vect_raw_(vect) ((bstc_intptr_t*)(void*)(vect) - 2)
#define bstc_dtl_vect_cap_(vect) (bstc_dtl_vect_raw_(vect)[0])
#define bstc_dtl_vect_len_(vect) (bstc_dtl_vect_raw_(vect)[1])
/// \}


#endif // BSTC__DETAIL__VECTOR_H
