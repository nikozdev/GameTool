#ifndef APP_ESTATE_HPP

#	define APP_ESTATE_HPP

#	include "../cfg.hpp"

#	include "../lib/lib_type.hpp"
#	include "../lib/lib_event.hpp"

#	include "vector"

namespace gt {

	namespace app {

		class estate_a_t {

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
		class estate_t_t : public estate_a_t {};

	}

	namespace app {

		class estate_game_t : public estate_t_t<estate_game_t> {
			
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

#endif /* APP_ESTATE_HPP */