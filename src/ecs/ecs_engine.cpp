#ifndef ECS_ENGINE_CPP

#	define ECS_ENGINE_CPP

#	include "ecs_engine.hpp"

namespace gt {

	namespace ecs {

		bool
			engine_t::init()
		{

			this->set_flag(true);

			return true;
		}
		bool
			engine_t::work()
		{
			return true;
		}
		bool
			engine_t::quit()
		{
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