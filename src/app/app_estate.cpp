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

			gfx->load_texture("../rsc/imag/bit1nc2.bmp", 0);

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

			for (float iterx = -1.0f; iterx < +1.0f; iterx += 0.01f) {

				for (float itery = -1.0f; itery < +1.0f; itery += 0.01f) {

					gfx::rect_t rect;

					rect.vtx_coord = { iterx /* sinow */, itery /* conow */ };
					rect.vtx_pivot = { 0.0f, 0.0f };
					rect.vtx_scale = { 0.0025f /* sinow */, 0.0025f /* conow */};
					rect.tex_color = { iterx * sinow, itery * conow, iterx * sinow, itery * conow };
					rect.tex_coord = { 0.0, 0.0, 1.0, 1.0 };
					rect.tex_index = { 0 };

					gfx->add_for_draw(rect);
				}

			}

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