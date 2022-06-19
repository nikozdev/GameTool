#ifndef CFG_GFX_HPP

#	define CFG_GFX_HPP

#   include "cfg_debug.hpp"

#   include "cfg_number.hpp"

#   ifndef GT_GFX_TEXTURE_COUNT_USE
#       define GT_GFX_TEXTURE_COUNT_MIN 0x01
#       define GT_GFX_TEXTURE_COUNT_MED 0x10
#       define GT_GFX_TEXTURE_COUNT_MAX 0x20
#       define GT_GFX_TEXTURE_COUNT_USE GT_GFX_TEXTURE_COUNT_MED
#   endif /* GT_GFX_TEXTURE_COUNT_USE */
#   ifndef GT_GFX_TEXTURE_SIZES_USE
#       define GT_GFX_TEXTURE_SIZES_MIN 0x10
#       define GT_GFX_TEXTURE_SIZES_MED 0x20
#       define GT_GFX_TEXTURE_SIZES_MAX 0x40
#       define GT_GFX_TEXTURE_SIZES_USE GT_GFX_TEXTURE_SIZES_MED
#   endif /* GT_GFX_TEXTURE_COUNT_USE */

/* vertex pointers for input-layouts|vertex-arrays */
#   ifndef GT_GFX_VPOINTER_COUNT_USE
#       define GT_GFX_VPOINTER_COUNT_MIN 0x01
#       define GT_GFX_VPOINTER_COUNT_MED 0x10
#       define GT_GFX_VPOINTER_COUNT_MAX 0x20
#       define GT_GFX_VPOINTER_COUNT_USE GT_GFX_VPOINTER_COUNT_MED
#   endif /* GT_GFX_VPOINTER_COUNT_USE */
/* shader pointers for uniforms|constants inside of a shader */
#   ifndef GT_GFX_SPOINTER_COUNT_USE
#       define GT_GFX_SPOINTER_COUNT_MIN 0x01
#       define GT_GFX_SPOINTER_COUNT_MED 0x10
#       define GT_GFX_SPOINTER_COUNT_MAX 0x20
#       define GT_GFX_SPOINTER_COUNT_USE GT_GFX_SPOINTER_COUNT_MED
#   endif /* GT_GFX_SPOINTER_COUNT_USE */

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