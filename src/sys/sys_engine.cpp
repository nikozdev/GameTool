#ifndef SYS_ENGINE_CPP

#   define SYS_ENGINE_CPP

#   include "sys_engine.hpp"

#   define GLFW_EXPOSE_NATIVE_WIN32
#   include "../../lib/glfw/src/glfw3.h"
#   include "../../lib/glfw/src/glfw3native.h"

namespace gt {

    namespace sys {
        
        static void
        glfw_call_elog(int errnum, const char* errstr)
        {
            GT_ELOG("[glfw]={errnum=(%d)errstr=(%s)}", errnum, errstr);
        }

    }

    namespace sys {

        bool
            engine_t::init()
        {
            ::glfwSetErrorCallback(glfw_call_elog);
            
            ::glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WIN32);
            GT_CHECK(::glfwInit(), "failed glfw init!", return false);

            GT_CHECK(this->window.init(), "window init error!", return false);
            
            this->set_flag(true);

            return true;
        }
        bool
            engine_t::work()
        {
            GT_CHECK(this->window.work(), "window work error!", return false);
            
            return true;
        }
        bool
            engine_t::quit()
        {
            GT_CHECK(this->window.quit(), "window quit error!", return false);

            ::glfwTerminate();

            return true;
        }

        bool
            engine_t::proc(lib::event_a_t* event)
        {
            if (event->get_kind() == event->get_kind<keybod_t::event_t>()) {

            }

            if (event->get_kind() == event->get_kind<cursor_t::event_coord_t>()) {
                
                return this->get_cursor()->proc(static_cast<cursor_t::event_coord_t*>(event));
            }

            return true;
        }

    }

}

#endif /* GFX_ENGINE_CPP */