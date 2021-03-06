//  Copyright (C) 2020-? T. Mitchell Kelleher
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#include <boostc/errno.h>
#include <boostc/stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    bstc_unused(argc);
    bstc_unused(argv);
    int num_pass = 0;
    int num_fail = 0;

    // int error;

    // //--------------------------------------------------------------------------------------------------------
    // error = EDOM;
    // printf("bstc_set_errno & bstc_get_errno\n");
    // bstc_set_errno(error);
    // if(bstc_get_errno() == error)
    // {
    //     ++num_pass;
    //     printf("    passed\n");
    // }
    // else
    // {
    //     ++num_fail;
    //     printf("    failed\n");
    // }

    // //--------------------------------------------------------------------------------------------------------
    // error = ERANGE;
    // printf("errno\n");
    // bstc_errno = error;
    // if((int)bstc_errno == error)
    // {
    //     ++num_pass;
    //     printf("    passed\n");
    // }
    // else
    // {
    //     ++num_fail;
    //     printf("    failed\n");
    // }

    //--------------------------------------------------------------------------------------------------------
    printf("-----------------------------\n");
    printf("     pass     |     fail     \n");
    printf("     %04i     |     %04i     \n", num_pass, num_fail);
    printf("-----------------------------\n");
    
    return num_fail ? bstc_exit_failure : bstc_exit_success;
}
