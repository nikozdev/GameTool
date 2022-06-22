#ifndef ECS_COMPON_HPP

#	define ECS_COMPON_HPP

#	include "../cfg.hpp"

#	include "../gfx/gfx_lib.hpp"

#   include "../lib/lib_vector.hpp"

#	include "../../lib/entt/src/entt.hpp"

#	define ECS_TYPEDEF(type_t, base_t)	\
	struct type_t {						\
		type_t() :						\
			base()						\
		{								\
		}								\
		type_t(const base_t& base) :	\
			base(base)					\
		{								\
		}								\
		base_t base;					\
		inline operator					\
			base_t&()					\
		{								\
			return this->base;			\
		}								\
		inline operator const			\
			base_t&() const				\
		{								\
			return this->base;			\
		}								\
		template<						\
			typename r_t, typename i_t	\
		> r_t&							\
			operator[](i_t i)			\
		{								\
			return this->base[i];		\
		}								\
		template<						\
			typename r_t, typename i_t	\
		> const r_t&					\
			operator[](i_t i) const		\
		{								\
			return this->base[i];		\
		}								\
	};									\
/* ECS_TYPEDEF */

namespace gt {
	/* alias */
	namespace ecs {

		using entity_t = entt::entity;
		using holder_t = entt::registry;

	}
	/* components */
	namespace ecs {

		typedef struct ebase_t {

			iname_t	iname;
			sname_t	sname;

			entity_t owner;
			entity_t child;

			entity_t next;
			entity_t prev;

			bool need_draw;
			bool need_work;

		} ebase_t;
		/* the origin for sprites and collision boxes */
		typedef v2f_t pivot_t;

	}
	/* functions */
	namespace ecs {
		/* entity component processing */
		template<typename ... args_t> inline void
			ecproc(entity_t& entity, args_t&& ... args);

	}

}

#endif /* ECS_COMPON_HPP */