#ifndef CFG_TOOLS_HPP

#	define CFG_TOOLS_HPP

#   ifndef GT_TOOL

#       define GT_TOOL

#       if (defined(__GNUC__) || defined(__GNUG__)) && !defined(__clang__)

#           define GT_TOOL_GNU

#       endif /* (__GNUC__ || __GNUG__) && !(__clang__) */

#       if defined(__clang__)

#          define GT_TOOL_CLG

#       endif /* __clang__ */

#       if defined(_MSC_VER)

#          define GT_TOOL_MVS

#       endif /* _MSC_VER */

#   endif   /* GT_TOOL */

#endif /* CFG_TOOLS_HPP */