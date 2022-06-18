#ifndef APP_STATE_CPP

#	define APP_STATE_CPP

#	include "app_state.hpp"

#	include "app_engine.hpp"

namespace gt {

	namespace app {

		bool
			state_game_t::init()
		{
			return true;
		}
		bool
			state_game_t::work()
		{
			return true;
		}
		bool
			state_game_t::quit()
		{
			return true;
		}

		bool
			state_game_t::proc(lib::event_a_t* event)
		{
			

			return true;
		}

	}

}

#endif /* APP_STATE_CPP */