#ifndef APP_ENGINE_HPP

#   define APP_ENGINE_HPP

#	include "../cfg.hpp"

#	include "../lib/lib_engine.hpp"

#	include "../lib/lib_time.hpp"

#	include "vector"

namespace gt {

	namespace gui { class tool_app_t; }
	
	namespace app {

		class engine_t : public lib::engine_t_t<engine_t> {

		public:

			using this_t = engine_t;

		public:

			inline const lib::timer_t*
				get_timer() const
			{
				return &this->timer;
			}

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

			lib::timer_t timer;

			std::vector<lib::engine_a_t*> engine_array;

		};

	}

}

#endif /* APP_ENGINE_HPP */