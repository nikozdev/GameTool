#ifndef ECS_ENGINE_CPP

#	define ECS_ENGINE_CPP

#	include "ecs_engine.hpp"
#	include "ecs_lib.hpp"

#	include "../app/app_engine.hpp"
#	include "../gfx/gfx_engine.hpp"

namespace gt {

	namespace ecs {

		bool
			engine_t::create_entity(entity_t* entity)
		{
			*entity = this->reg.create();

			ebase_t ebase = {
				.name = "entity" + std::to_string(static_cast<entt::id_type>(*entity))
			};
			this->reg.emplace<ebase_t>(*entity, ebase);

			return true;
		}
		bool
			engine_t::remove_entity(entity_t* entity)
		{
			auto ebase = this->reg.get<ebase_t>(*entity);

			this->reg.destroy(*entity);

			memset(entity, 0, sizeof(entity_t));

			return true;
		}

		bool
			engine_t::init()
		{
			return this->play();
		}
		bool
			engine_t::work()
		{
			auto app = app::engine_t::get();
			auto gfx = gfx::engine_t::get();

			auto view = this->reg.view<ebase_t>();
			auto view_gfx = this->reg.view<sprite_t>();

			for (auto [entity, sprite] : view_gfx.each()) {

				gfx->add_for_draw(sprite);

			}

			return true;
		}
		bool
			engine_t::quit()
		{
			this->reg.clear();

			return true;
		}

		bool
			engine_t::proc(lib::event_a_t* event)
		{
			return true;
		}

	}

}

#endif /* ECS_ENGINE_CPP */