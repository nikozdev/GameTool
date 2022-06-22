#ifndef CFG_NUMBER_HPP

#	define CFG_NUMBER_HPP

#   include "stdint.h"

#   define GT_MIN(val0, val1)       (val0) < (val1) ? (val0) : (val1)
#   define GT_MAX(val0, val1)       (val0) > (val1) ? (val0) : (val1)
#   define GT_CLAMP(val, min, max)  (GT_MAX(GT_MIN(val, max), min))

namespace gt {

    using index_t   = unsigned int;
    using count_t   = unsigned int;
    using flags_t   = unsigned long long;

    using enum_t    = index_t;

    using iname_t   = index_t;

}

#endif /* CFG_NUMBER_HPP */