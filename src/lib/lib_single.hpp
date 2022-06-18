#ifndef LIB_SINGLE_HPP

#	define LIB_SINGLE_HPP

#   include "../cfg.hpp"

namespace gt {

    namespace lib {

        template<typename type_t>
        class single_t_t {

        public:

            using this_t = single_t_t<type_t>;

        public:

            inline static type_t*
                get()
            {
                static type_t single;
                return &single;
            }

        };

    }

}

#endif /* LIB_SINGLE_HPP */