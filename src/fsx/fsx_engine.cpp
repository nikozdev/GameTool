#ifndef FSX_ENGINE_CPP

#   define FSX_ENGINE_CPP

#   include "fsx_engine.hpp"

#   include "../app/app_engine.hpp"
#   include "../gfx/gfx_engine.hpp"
#   include "../sys/sys_window.hpp"

#   include "../lib/lib_file.hpp"

namespace gt {

    namespace fsx {

        bool
            engine_t::init()
        {
            return this->play();;
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
            
            if (event->has_kind<sys::cursor_t::event_coord_t>()) {

                auto evt = static_cast<sys::cursor_t::event_coord_t*>(event);
                
                return true;
            }

            if (event->has_kind<sys::cursor_t::event_coord_t>()) {

                auto evt = static_cast<sys::cursor_t::event_coord_t*>(event);

                return true;
            }

            if (event->has_kind<sys::window_t::event_sized_t>()) {
                
                auto evt = static_cast<sys::window_t::event_sized_t*>(event);
                
                return true;
            }

            return true;
        }

    }

}

#endif /* FSX_ENGINE_CPP */