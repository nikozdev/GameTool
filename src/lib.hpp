#ifndef LIB_HPP

#   define LIB_HPP

#   include "stdio.h"
#	include "stdlib.h"
#   include "stdint.h"
#	include "memory.h"

#   include "list"
#   include "vector"
#   include "stack"
#   include "queue"
#   include "unordered_map"
#   include "thread"
#   include "atomic"

#   include "../lib/glm/src/vec2.hpp"
#   include "../lib/glm/src/vec3.hpp"
#   include "../lib/glm/src/vec4.hpp"

#   include "../lib/glm/src/matrix.hpp"

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
            gt_dbg_code = GT_ERROR_DONE;    \
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
            ({                              \
                gt_dbg_code = GT_ERROR_DONE;\
                actn;                       \
            });                             \
        })                                  \
/* GT_ERROR */
#       define GT_CHECK(expr, mesg, actn) ({    \
            if ((expr) == false) {              \
                GT_ERROR(mesg, actn);           \
            }                                   \
        })                                      \
/* GT_CHECK */
#       define GT_PCALL(code, mesg, actn) ({    \
            code;                               \
            GT_CHECK(                           \
                gt_dbg_code == GT_ERROR_NONE,   \
                mesg,                           \
                ({                              \
                    actn;                       \
                    gt_dbg_code = GT_ERROR_NONE;\
                })                              \
            );                                  \
        })                                      \
/* GT_PCALL */
#   endif /* !GT_TOOL_MVS */

extern int gt_dbg_code;

namespace gt {
    
    namespace lib {

        template<typename value_t>
        using array_t = std::vector<value_t>;
        template<typename value_t>
        using queue_t = std::queue<value_t>;
        template<typename value_t>
        using stack_t = std::stack<value_t>;
        template<typename index_t, typename value_t>
        using table_t = std::unordered_map<index_t, value_t>;
        
    }

    namespace lib {

        class event_t {

        public:
            
            using this_t    = event_t;

            using kind_t    = int;

        public:

            event_t(kind_t kind) : kind(kind) {}    

        private:
            
            static inline
            kind_t& get_kind_counter()
            {
                static kind_t counter = 0;
                return counter;
            }

        public:

            template<typename type_t>
            static inline
            kind_t get_kind()
            {
                static_assert(
                    std::is_base_of<this_t, type_t>::value,
                    "the template type has to be an inherit of event!"
                );
                static kind_t kind = ++get_kind_counter();
                return kind;
            }

            inline kind_t
            get_kind() const
            {
                return this->kind;
            }

            inline bool
            has_kind(kind_t kind) const
            {
                return this->kind & kind;
            }
            template<typename type_t>
            inline bool
            has_kind() const
            {
                return this->kind == this_t::get_kind<type_t>();
            }

        private:

            const kind_t kind;
            
        };

    }

    namespace lib {
        
        template<typename type_t>
        class single_t {
            
        public:

            using this_t    = single_t<type_t>;

        public:

            inline static type_t*
            get()
            {
                static type_t single;
                return &single;
            }

        };

    }

    namespace lib {

        template<typename type_t>
        class engine_t : public single_t<type_t> {
            
        public:

            using this_t    = engine_t<type_t>;
            using base_t    = single_t<type_t>;
            
        public:

            engine_t() : flag(false) {}

            inline bool
            get_flag() const
            {
                return this->flag;
            }

            inline bool
            exec()
            {
                this->flag = true;

                GT_CHECK(this->init(), "engine init error!", return false);
                while (this->flag) { GT_CHECK(this->work(), "engine work error!", break); }
                GT_CHECK(this->quit(), "engine quit error!", return false);
                
                return true;
            }
            inline bool
            stop()
            {
                GT_CHECK(this->flag == true, "engine cannot stop!", return false);
                
                this->flag = false;
                
                return true;
            }

        public:

            virtual bool
            init() = 0;
            virtual bool
            work() = 0;
            virtual bool
            quit() = 0;
            
            virtual bool
            proc(event_t* event) = 0;
        
        protected:

        inline bool
        set_flag(bool flag)
        {
            this->flag = flag;
            return this->flag;
        }

        private:

            bool flag;

        };

    }

}

#endif /* LIB_HPP */