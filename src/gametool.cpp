#ifndef GAMETOOL_CPP

#   define GAMETOOL_CPP

#   include "gametool.hpp"

#ifdef GT_BUILD_EXE

int
main(int argc, const char** argv)
{
    printf("hello world!\n");

    return GT_ERROR_NONE;
}

#endif /* GT_BUILD_EXE */

#endif /* GAMETOOL_CPP */