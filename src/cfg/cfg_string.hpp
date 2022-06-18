#ifndef CFG_STRING_HPP

#	define CFG_STRING_HPP

#   include "string.h"

#   ifndef GT_NAME_SIZE_USE
#       define GT_NAME_SIZE_MIN 0x10
#       define GT_NAME_SIZE_MED 0x40
#       define GT_NAME_SIZE_MAX 0x80
#       define GT_NAME_SIZE_USE GT_NAME_SIZE_MED
#   endif /* GT_NAME_SIZE_USE */

namespace gt {

    using cstr_t    = const char*;
}

#endif /* CFG_STRING_HPP */