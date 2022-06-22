#ifndef APP_ESTATE_CPP

#	define APP_ESTATE_CPP

#	include "app_estate.hpp"

#	include "../app.hpp"
#	include "../gfx.hpp"
#	include "../sys.hpp"
#	include "../ecs.hpp"

namespace gt {

	namespace app {

		bool
			estate_game_t::init()
		{
			auto app = app::engine_t::get();
			auto gfx = gfx::engine_t::get();
			auto ecs = ecs::engine_t::get();

			auto drawtool = gfx->get_drawtool();
			auto materia = &drawtool->materia;
			auto binding = &materia->binding;
			
			constexpr int files_count = 8;
			const char* files[files_count] = {
				
				"../rsc/imag/bit1tile8.png",
				"../rsc/imag/bit1nc16.bmp",
				"../rsc/imag/bit1nikochir32.png",
				"../rsc/imag/bit1font8.png",

				"../rsc/imag/bit1ring16.png",
				"../rsc/imag/bit1bone16.png",
				"../rsc/imag/bit1necro16.png",
				"../rsc/imag/bit2tile16.png",
			};
			gfx->load_texture(files[0], 1);
			gfx->load_texture(files[7], 2);

			ecs::drawgrid_t drawgrid;

			drawgrid.scale = v2f_t{ 1.0f, 1.0f };
			
			drawgrid.visio.texid = v1s_t{ 0 };
			drawgrid.visio.texuv = v4f_t{ 0.0f, 0.0f, 0.125f, 0.125f };
			drawgrid.visio.color = v4f_t{ 1.0f, 1.0f, 1.0f, 1.0f };

			gfx::tile_t tile;

			for (index_t iterx = 0; iterx < 8; iterx++) {
				for (index_t itery = 0; itery < 8; itery++) {
					
					tile.mapid = { iterx, itery };
					tile.texid = { iterx, itery };
					drawgrid.tiles.push_back(tile);

				}
			}

			ecs::entity_t entity;
			ecs->create_entity(&entity);
			ecs->create_compon<ecs::drawgrid_t>(&entity, drawgrid);

			return true;
		}
		bool
			estate_game_t::work()
		{
			auto app = app::engine_t::get();
			auto gfx = gfx::engine_t::get();

			auto timer = app->get_timer();
			auto senow = timer->get_senow();
			auto sinow = sinf(senow);
			auto conow = cosf(senow);

			return true;
		}
		bool
			estate_game_t::quit()
		{
			return true;
		}

		bool
			estate_game_t::proc(lib::event_a_t* event)
		{
			

			return true;
		}

	}

}

#endif /* APP_ESTATE_CPP */