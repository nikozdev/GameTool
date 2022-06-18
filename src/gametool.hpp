#ifndef GAMETOOL_HPP

#   define GAMETOOL_HPP

#	include "lib.hpp"
#	include "sys.hpp"
#	include "gfx.hpp"

#   ifdef GT_BUILD_EXE

extern int
main(int argc, const char** argv);

#   endif /* GT_BUILD_EXE */

namespace gt {

	class engine_t : public lib::engine_t<engine_t> {

	public:

		using this_t 	= engine_t;

	public:

		virtual bool
		init() override;
		virtual bool
		work() override;
		virtual bool
		quit() override;

		virtual bool
		proc(lib::event_t* event) override;

		private:

	};

}

#endif /* GAMETOOL_HPP */