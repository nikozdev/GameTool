#ifndef ECS_ENGINE_CPP

#	define ECS_ENGINE_CPP

#	include "ecs_engine.hpp"

#	include "ecs_lib.hpp"
#	include "ecs_fsx.hpp"
#	include "ecs_gfx.hpp"

#	include "../app/app_engine.hpp"
#	include "../gfx/gfx_engine.hpp"


namespace gt {

	namespace ecs {

		bool
			engine_t::create_entity(entity_t* entity)
		{
			*entity = this->reg.create();

			ebase_t ebase = {
				.iname = static_cast<entt::id_type>(*entity),
				.sname = "entity" + std::to_string(static_cast<entt::id_type>(*entity))
			};
			this->reg.emplace<ebase_t>(*entity, ebase);

			return true;
		}
		bool
			engine_t::remove_entity(entity_t* entity)
		{
			this->reg.destroy(*entity);

			::memset(entity, 0, sizeof(entity_t));

			return true;
		}

		bool
			engine_t::init()
		{
			this->reg.create();

			return this->play();
		}
		bool
			engine_t::work()
		{
			auto app = app::engine_t::get();
			auto gfx = gfx::engine_t::get();

			/*
			this->reg.view<gravi_t, accel_t>().each(ecproc<gravi_t, accel_t>);
			this->reg.view<veloc_t, accel_t>().each(ecproc<veloc_t, accel_t>);
			this->reg.view<coord_t, veloc_t>().each(ecproc<coord_t, veloc_t>);
			this->reg.view<torqu_t, angle_t>().each(ecproc<torqu_t, angle_t>);

			this->reg.view<drawgrid_t>().each(ecproc<drawgrid_t>);
			this->reg.view<drawrect_t>().each(ecproc<drawrect_t>);
			this->reg.view<drawrect_t, mover_t>().each(ecproc<drawrect_t, mover_t>);
			*/

			auto func = [this](auto entity)->void {

				if (reg.orphan(entity)) { reg.destroy(entity); }

				if (reg.all_of<gravi_t, accel_t>(entity)) { ecproc(entity, reg.get<gravi_t>(entity), reg.get<accel_t>(entity)); }
				if (reg.all_of<accel_t, veloc_t>(entity)) { ecproc(entity, reg.get<accel_t>(entity), reg.get<veloc_t>(entity)); }
				if (reg.all_of<veloc_t, coord_t>(entity)) { ecproc(entity, reg.get<veloc_t>(entity), reg.get<coord_t>(entity)); }
				
				if (reg.all_of<mover_t>(entity)) { ecproc(entity, reg.get<drawrect_t>(entity), reg.get<mover_t>(entity)); }
				if (reg.all_of<mover_t, drawrect_t>(entity)) { ecproc(entity, reg.get<drawrect_t>(entity), reg.get<mover_t>(entity)); }
				
				if (reg.all_of<drawgrid_t>(entity)) { ecproc(entity, reg.get<drawgrid_t>(entity)); }
				if (reg.all_of<drawrect_t>(entity)) { ecproc(entity, reg.get<drawrect_t>(entity)); }

			};
			this->reg.each(func);

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