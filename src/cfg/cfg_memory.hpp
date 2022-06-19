#ifndef CFG_MEMORY_HPP

#	define CFG_MEMORY_HPP

#   include "memory.h"

namespace gt {

    using mptr_t    = void*;

    using msize_t   = size_t;

    using mbyte_t   = unsigned char;
    using mdata_t   = mbyte_t*;
    
    typedef struct {
        msize_t msize;
        mdata_t mdata;
    } mbufr_t;
}

#endif /* CFG_MEMORY_HPP */