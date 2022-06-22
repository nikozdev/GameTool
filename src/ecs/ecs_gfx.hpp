#ifndef ECS_GFX_HPP

#	define ECS_GFX_HPP

#	include "../cfg.hpp"
#	include "../gfx.hpp"

#	include "ecs_lib.hpp"
#	include "ecs_fsx.hpp"

namespace gt {

	/* alias */
	namespace ecs {

		ECS_TYPEDEF(texid_t, v1s_t);
		ECS_TYPEDEF(texuv_t, v4f_t);

		ECS_TYPEDEF(color_t, v4f_t);
		
		typedef std::vector<gfx::tile_t> tiles_t;

	}
	/* components */
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

			pivot_t pivot = v2f_t{ 0.0f, 0.0f };
			scale_t scale = v2f_t{ 1.0f, 1.0f };
			coord_t coord = v2f_t{ 0.0f, 0.0f };

		} drawrect_t;

		typedef struct drawgrid_t {
			
			visio_t visio = {
				.texid = { 0 },
				.texuv = v4f_t{ 0.0f, 0.0f, 0.125f, 0.125f },
				.color = v4f_t{ 1.0f, 1.0f, 1.0f, 1.0f },
			};

			scale_t scale = v2f_t{ 1.0f, 1.0f };
			
			tiles_t tiles = {};

		} drawgrid_t;

	}
	/* functions */
	namespace ecs {

		template<> inline void
			ecproc(entity_t& entity, drawrect_t& drawrect)
		{
			gfx::engine_t::get()->add_for_draw(
				drawrect.pivot,
				drawrect.scale,
				drawrect.coord,
				drawrect.visio.texid,
				drawrect.visio.texuv,
				drawrect.visio.color
			);
		}
		template<> inline void
			ecproc(entity_t& entity, drawgrid_t& drawgrid)
		{
			gfx::engine_t::get()->add_for_draw(
				drawgrid.scale,
				drawgrid.visio.texid, static_cast<v4f_t>(drawgrid.visio.texuv), drawgrid.visio.color,
				drawgrid.tiles
			);
		}

		template<> inline void
			ecproc(entity_t& entity, pivot_t& pivot, scale_t& scale, coord_t& coord, texid_t& texid, texuv_t& texuv, color_t& color)
		{
			gfx::engine_t::get()->add_for_draw(
				pivot, scale, coord,
				texid, texuv, color
			);
		}

		template<> inline void
			ecproc(entity_t& entity, drawrect_t& drawrect, mover_t& mover)
		{
			static_cast<v2f_t>(drawrect.coord) += mover.veloc;
		}

	}

}

#endif /* ECS_GFX_HPP */