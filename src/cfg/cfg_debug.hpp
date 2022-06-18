#ifndef CFG_DEBUG_HPP

#	define CFG_DEBUG_HPP

#   include "stdio.h"

#   include "cfg_tools.hpp"

#   define GT_ERROR_NONE false
#   define GT_ERROR_DONE true

#   ifdef GT_TOOL_MVS

#       define GT_OPUT(...) fprintf(stdout,__VA_ARGS__);
#       define GT_OLOG(mesg)            \
            GT_OPUT(                    \
                "file: " __FILE__ " | " \
                "line: " "%d" " | "     \
                "mesg: " "\n" mesg "\n" \
                ,__LINE__               \
            )                           \
/* GT_OLOG */
#       define GT_OLOGF(mesg, ...)      \
            GT_OPUT(                    \
                "file: " __FILE__ " | " \
                "line: " "%d" " | "     \
                "mesg: " "\n" mesg "\n" \
                ,__LINE__,##__VA_ARGS__ \
            )                           \
/* GT_OLOGF */
#       define GT_EPUT(...) fprintf(stderr,__VA_ARGS__);
#       define GT_ELOG(mesg, ...)       \
            GT_EPUT(                    \
                "file: " __FILE__ " | " \
                "line: " "%d" " | "     \
	        	"mesg: " "\n" mesg "\n" \
                ,__LINE__               \
            )                           \
/* GT_ELOG */
#       define GT_ELOGF(mesg, ...)      \
            GT_EPUT(                    \
                "file: " __FILE__ " | " \
                "line: " "%d" " | "     \
	        	"mesg: " "\n" mesg "\n" \
                ,__LINE__,##__VA_ARGS__ \
            )                           \
/* GT_ELOGF */

#       define GT_BREAK()   __debugbreak();
#       define GT_ERROR(mesg, actn)         \
            GT_ELOG(mesg)                   \
            GT_BREAK()                      \
            actn;                           \
/* GT_ERROR */
#       define GT_CHECK(expr, mesg, actn)       \
            if ((expr) == false) {              \
                GT_ERROR(mesg, actn)            \
            }                                   \
/* GT_CHECK */

#   else

#       define GT_OPUT(...)         ({  \
            fprintf(stdout,__VA_ARGS__);\
        })                              \
/* GT_OPUT */
#       define GT_OLOG(mesg, ...)   ({  \
            GT_OPUT(                    \
                "file: " __FILE__ " | " \
                "line: " "%d" " | "     \
                "mesg: " "\n" mesg "\n" \
                ,__LINE__,##__VA_ARGS__ \
            );                          \
        })                              \
/* GT_OLOG */
#       define GT_EPUT(...)         ({  \
            fprintf(stderr,__VA_ARGS__);\
        })                              \
/* GT_EPUT */
#       define GT_ELOG(mesg, ...)   ({  \
            GT_EPUT(                    \
                "file: " __FILE__ " | " \
                "line: " "%d" " | "     \
	        	"mesg: " "\n" mesg "\n" \
                ,__LINE__,##__VA_ARGS__ \
            );                          \
        })                              \
/* GT_ELOG */

#       define GT_BREAK()           ({      \
            __debugbreak();                 \
        })                                  \
/* GT_BREAK */
#       define GT_ERROR(mesg, actn) ({      \
            GT_ELOG(mesg);                  \
            GT_BREAK();                     \
            actn;                           \
        })                                  \
/* GT_ERROR */
#       define GT_CHECK(expr, mesg, actn) ({    \
            if ((expr) == false) {              \
                GT_ERROR(mesg, actn);           \
            }                                   \
        })                                      \
/* GT_CHECK */

#   endif /* !GT_TOOL_MVS */

#endif /* CFG_DEBUG_HPP */