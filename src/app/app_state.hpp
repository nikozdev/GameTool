#ifndef APP_STATE_HPP

#	define APP_STATE_HPP

#	include "../cfg.hpp"

#	include "../lib/lib_type.hpp"
#	include "../lib/lib_event.hpp"

#	include "vector"

namespace gt {

	namespace app {

		class state_a_t {

		public:

			virtual bool
				init() = 0;
			virtual bool
				work() = 0;
			virtual bool
				quit() = 0;
			
			virtual bool
				proc(lib::event_a_t* event) = 0;

		protected:

		private:

		};
		template<typename type_t>
		class state_t_t : public state_a_t {};

	}

	namespace app {

		class state_game_t : public state_t_t<state_game_t> {
			
		public:

			virtual bool
				init() override;
			virtual bool
				work() override;
			virtual bool
				quit() override;

			virtual bool
				proc(lib::event_a_t* event) override;

		protected:

		private:

		};

	}

}

#endif /* APP_STATE_HPP */