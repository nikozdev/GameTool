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
				
				"../rsc/imag/bit1nc16.bmp",
				"../rsc/imag/bit1nikochir32.png",
				"../rsc/imag/bit1font8.png",
				"../rsc/imag/bit1tile8.png",

				"../rsc/imag/bit1ring16.png",
				"../rsc/imag/bit1bone16.png",
				"../rsc/imag/bit1necro16.png",
				"../rsc/imag/bit2tile16.png",
			};

			for (index_t index = 0; index < binding->count; index++) {
				gfx->load_texture(files[index % files_count], index);
			}

			int index = 0;
			for (float iterx = -1.0f; iterx <= +1.0f; iterx += 0.5f) {

				for (float itery = -1.0f; itery <= +1.0f; itery += 0.5f, index++) {

					ecs::sprite_t sprite;

					sprite.vtx_coord = { iterx, itery };
					sprite.vtx_pivot = { 0.0f, 0.0f };
					sprite.vtx_scale = { 0.25f, 0.25f };
					sprite.tex_color = { 1.0f, 1.0f, 1.0f, 1.0f };
					sprite.tex_coord = { 0.0f, 0.0f, 1.0f, 1.0f };
					sprite.tex_index = { static_cast<v1f_t>(index % GT_GFX_TEXTURE_COUNT_USE) };

					ecs::entity_t entity;
					ecs->create_entity(&entity);
					ecs->create_compon<ecs::sprite_t>(&entity, sprite);

				}
			
			}
			
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