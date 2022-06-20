#ifndef GUI_ENGINE_HPP

#	define GUI_ENGINE_HPP

#	include "../cfg.hpp"

#	include "gui_tool.hpp"

#	include "../lib/lib_engine.hpp"

#	include "vector"

namespace gt {

	namespace gui {

		class engine_t : public lib::engine_t_t<engine_t> {

		public:

			using this_t = engine_t;
			using base_t = lib::engine_t_t<this_t>;

			using window_t = void*;
			using device_t = void*;
			using contex_t = void*;

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

			bool open_frame();
			bool shut_frame();

		private:

			bool frame_flag;

			window_t window;
			contex_t contex;
			device_t device;

			std::vector<tool_a_t*> tool_array;

		};

	}

}

#endif /* ECS_ENGINE_HPP */