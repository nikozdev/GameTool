#ifndef ECS_ENGINE_CPP

#	define ECS_ENGINE_CPP

#	include "ecs_engine.hpp"
#	include "ecs_compon.hpp"

#	include "../app/app_engine.hpp"
#	include "../gfx/gfx_engine.hpp"

namespace gt {

	namespace ecs {

		bool
			engine_t::create_entity(entity_t* entity)
		{
			*entity = this->reg.create();

			auto ebase = this->reg.emplace<ebase_t>(*entity);
			ebase.name = "entity" + std::to_string(static_cast<entt::id_type>(*entity));

			auto sprite = this->reg.emplace<ecs::sprite_t>(*entity);

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