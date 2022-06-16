#ifndef GAMETOOL_HPP

#   define GAMETOOL_HPP

#   define GT_ERROR_NONE 0

#   include "stdio.h"

#   define GT_BUILD_EXE
#   ifdef GT_BUILD_EXE


extern int
main(int argc, const char** argv);

#   endif /* GT_BUILD_EXE */

#endif /* GAMETOOL_HPP */