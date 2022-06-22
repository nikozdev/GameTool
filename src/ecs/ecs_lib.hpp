#ifndef ECS_LIB_HPP

#	define ECS_LIB_HPP

#	include "../cfg.hpp"

#	include "../gfx/gfx_lib.hpp"

#   include "../lib/lib_vector.hpp"

#	include "../../lib/entt/src/entt.hpp"

namespace gt {
	/* alias */
	namespace ecs {

		using entity_t = entt::entity;
		using holder_t = entt::registry;

		using tiles_t = std::vector<gfx::tile_t>;

	}
	/* general */
	namespace ecs {

		typedef struct ebase_t {

			iname_t	iname;
			sname_t	sname;

			entity_t owner;
			entity_t child;

			entity_t next;
			entity_t prev;

		} ebase_t;
		/* the origin for sprites and collision boxes */
		typedef v2f_t pivot_t;

		typedef struct player_t {
			
			bool	controlled;
			bool	camera_target;
			bool	grounded;

			v1f_t	speed;

		};

	}
	/* physics */
	namespace ecs {
		/* collection of position, rotation and scale */
		typedef struct tform_t {
			
			coord_t coord = { 0.0f, 0.0f };
			scale_t	scale = { 1.0f, 1.0f };

		} tform_t;
		/**/
		typedef struct mover_t {
			
			veloc_t veloc;

		} mover_t;
		/* box2d body */
		typedef struct b2body_t {
			
			bool	isdynamic;
			mptr_t	rigidbody;
			mptr_t	collision;
			
		} b2body_t;

	}
	/* graphics */
	namespace ecs {

		typedef struct visio_t {

			texid_t texid = v1s_t{ 0 };
			texuv_t texuv = v4f_t{ 0.0f, 0.0f, 1.0f, 1.0f };
			color_t color = v4f_t{ 1.0f, 1.0f, 1.0f, 1.0f };

		} visual_t;

		typedef struct drawrect_t {

			visio_t visio = {
				.texid = { 0 },
				.texuv = v4f_t{ 0.0f, 0.0f, 1.0f, 1.0f },
				.color = v4f_t{ 1.0f, 1.0f, 1.0f, 1.0f },
			};

		} drawrect_t;

		typedef struct drawgrid_t {

			visio_t visio = {
				.texid = { 0 },
				.texuv = v4f_t{ 0.0f, 0.0f, 0.125f, 0.125f },
				.color = v4f_t{ 1.0f, 1.0f, 1.0f, 1.0f },
			};

			tiles_t tiles = {};

		} drawgrid_t;

	}

}

#endif /* ECS_LIB_HPP */