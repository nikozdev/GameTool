#ifndef CFG_STRING_HPP

#	define CFG_STRING_HPP

#   include "cfg_memory.hpp"

#   include "string.h"

#   include "string"

#   ifndef GT_NAME_SIZE_USE
#       define GT_NAME_SIZE_MIN 0x10
#       define GT_NAME_SIZE_MED 0x40
#       define GT_NAME_SIZE_MAX 0x80
#       define GT_NAME_SIZE_USE GT_NAME_SIZE_MED
#   endif /* GT_NAME_SIZE_USE */

#   define GT_STRING(text) #text

namespace gt {

    using cstr_t    = const char*;
    
    using sdata_t   = char*;

    typedef struct {
        msize_t msize;
        sdata_t sdata;
    } sbufr_t;

    using sname_t   = std::string;

}

#endif /* CFG_STRING_HPP */