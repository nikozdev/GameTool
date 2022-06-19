#ifndef FSX_LIB_HPP

#	define FSX_LIB_HPP

#   include "../cfg.hpp"

#   include "../lib/lib_vector.hpp"

namespace gt {
    
    namespace fsx {
        
        typedef struct {
            v2f_t coord;
            v2f_t pivot;
            v2f_t scale;
        } rect_t;

    }

}

#endif /* FSX_LIB_HPP */