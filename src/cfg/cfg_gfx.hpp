#ifndef CFG_GFX_HPP

#	define CFG_GFX_HPP

#   include "cfg_debug.hpp"

#   include "cfg_number.hpp"

namespace gt {

    namespace gfx {

        extern void
            clear_error();
        extern bool
            check_error();

        extern bool
            check_shader(index_t itype, index_t index);
    
    }

}

#   define GT_GFX_DEBUG(exec)           \
        gt::gfx::clear_error();         \
        exec;                           \
        if (gt::gfx::check_error()) {   \
            GT_ERROR(#exec, {});        \
        }                               \
/* GT_GFX_DEBUG */

#endif /* CFG_GFX_HPP */