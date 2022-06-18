#ifndef LIB_TYPE_HPP

#	define LIB_TYPE_HPP

#	include "../cfg.hpp"

#   include "type_traits"

namespace gt {

	namespace lib {

		class rtti_t {

		public:

			using iname_t = index_t;

		private:

            static inline
                iname_t& get_iname_ref()
            {
                static iname_t iname = 0;
                return iname;
            }

		public:

			template<typename type_t> static inline iname_t
				get_iname()
			{
				static iname_t iname = ++get_iname_ref();
				return iname;
			}

		};

	}

}

#endif /* LIB_TYPE_HPP */