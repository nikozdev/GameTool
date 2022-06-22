#ifndef ECS_ENGINE_HPP

#	define ECS_ENGINE_HPP

#	include "../cfg.hpp"

#	include "ecs_lib.hpp"

#	include "../lib/lib_engine.hpp"

#	include "../../lib/entt/src/entt.hpp"

class b2World;

namespace gt {

	namespace gui { class tool_ecs_t; }

	namespace ecs {
		
		class engine_t : public lib::engine_t_t<engine_t> {
			
		public:

			using this_t = engine_t;
			
			friend class gui::tool_ecs_t;

		public:

			entity_t
				ecreate();
			bool
				eremove(entity_t entity);

			template<typename compon_t, typename ... args_t> compon_t&
				ccreate(entity_t entity, args_t&& ... args)
			{
				return this->reg.emplace_or_replace<compon_t>(entity, std::forward<args_t>(args)...);
			}
			template<typename compon_t> bool
				cremove(entity_t entity)
			{
				if (this->reg.any_of<compon_t>(entity) == false) { return false; }
				this->reg.remove<compon_t>(entity);

				return true;
			}

		public:

			bool
				fsx_play();
			bool
				fsx_stop();

			virtual bool
				init() override;
			virtual bool
				work() override;
			virtual bool
				quit() override;

			virtual bool
				proc(lib::event_a_t* event) override;

		private:

			entt::registry	reg;
			b2World*		fsx;

		};

	}

}

#endif /* ECS_ENGINE_HPP */