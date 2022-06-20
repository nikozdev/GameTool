#ifndef ECS_COMPON_HPP

#	define ECS_COMPON_HPP

#	include "../cfg.hpp"

#	include "../gfx/gfx_lib.hpp"
#	include "../fsx/fsx_lib.hpp"

#	include "../../lib/entt/src/entt.hpp"

namespace gt {
	
	namespace ecs {

		using entity_t = entt::entity;

	}

	namespace ecs {
		
		typedef struct {
			std::string name;
		} ebase_t;

		typedef gfx::rect_t sprite_t;

		typedef struct {
			fsx::rect_t rect;
		} collid_t;

	}

}

#endif /* ECS_COMPON_HPP */