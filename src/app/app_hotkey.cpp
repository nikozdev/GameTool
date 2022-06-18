#ifndef APP_HOTKEY_CPP

#	define APP_HOTKEY_CPP

#   include "../cfg.hpp"
#   include "../lib.hpp"
#   include "../gfx.hpp"
#   include "../sys.hpp"
#   include "../gui.hpp"
#   include "../ecs.hpp"
#   include "../app.hpp"

#   include "app_hotkey.hpp"

namespace gt {

    namespace app {
        
        bool
            stop_work(hotkey_t::args_t args)
        {
            return app::engine_t::get()->stop();
        }

    }

}

#endif /* APP_HOTKEY_CPP */