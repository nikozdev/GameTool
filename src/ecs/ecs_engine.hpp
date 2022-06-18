#ifndef ECS_ENGINE_HPP

#	define ECS_ENGINE_HPP

#	include "../cfg.hpp"

#	include "../lib/lib_engine.hpp"

#	include "../../lib/entt/src/entt.hpp"

namespace gt {

	namespace ecs {

		class engine_t : public lib::engine_t_t<engine_t> {

		public:

			virtual bool
				init() override;
			virtual bool
				work() override;
			virtual bool
				quit() override;

			virtual bool
				proc(lib::event_a_t* event) override;

		private:

			entt::registry reg;

		};

	}

}

#endif /* ECS_ENGINE_HPP */