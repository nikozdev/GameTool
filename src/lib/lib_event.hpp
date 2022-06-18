#ifndef LIB_EVENT_HPP

#	define LIB_EVENT_HPP

#   include "../cfg.hpp"

#   include "lib_type.hpp"

namespace gt {
    
    namespace lib {

        class event_a_t {

        public:

            using this_t = event_a_t;

            using kind_t = index_t;

        public:

            event_a_t(kind_t kind) : kind(kind) {}

        public:

            template<typename type_t> static inline
                kind_t get_kind()
            {
                static_assert(
                    std::is_base_of<this_t, type_t>::value,
                    "the template type has to be an inherit of event!"
                );
                return rtti_t::get_iname<type_t>();
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
            template<typename type_t> inline bool
                has_kind() const
            {
                return this->kind == this_t::get_kind<type_t>();
            }

        private:

            const kind_t kind;

        };

        template<typename type_t>
        class event_t_t : public event_a_t {
            
        public:

            using this_t    = event_t_t<type_t>;
            using base_t    = event_a_t;
        
        public:

            event_t_t() : base_t(this_t::get_kind()) {}

            static inline
                kind_t get_kind()
            {
                return base_t::get_kind<type_t>();
            }

        };

    }

}

#endif /* LIB_EVENT_HPP */