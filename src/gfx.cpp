#ifndef GFX_CPP

#   define GFX_CPP

#   include "gfx.hpp"
#   include "sys.hpp"

#   include "../lib/glad/src/glad.h"

#   define GLFW_EXPOSE_NATIVE_WIN32
#   include "../lib/glfw/src/glfw3.h"
#   include "../lib/glfw/src/glfw3native.h"

namespace gt {
    
    namespace gfx {
    
        bool
        engine_t::set_window(window_t& window)
        {
            GT_CHECK(this->get_flag() == false, "the engine is running, cannot set the window!", return false);

            this->window = window;

            return true;
        }

        bool
        engine_t::init()
        {
            GT_CHECK(this->window != nullptr, "graphics engine window is not set!", return false);
        
            ::GLFWwindow* glfw_window = reinterpret_cast<::GLFWwindow*>(this->window);
            ::glfwMakeContextCurrent(glfw_window);

            ::HWND hwnd = ::glfwGetWin32Window(glfw_window);
            GT_CHECK(hwnd != NULL, "failed to get the platform window!", return false);            
            this->device = ::GetWindowDC(hwnd);
            GT_CHECK(this->device != nullptr, "failed to get the graphics device!", return false);            
            
            this->contex = ::wglGetCurrentContext();
            GT_CHECK(this->contex != nullptr, "failed to get the graphics context!", return false);
            
            ::glfwSwapInterval(1u);

            GT_CHECK(::gladLoadGL(), "failed gladLoadGL!", return false);

            this->set_flag(true);

            return true;
        }
        bool
        engine_t::work()
        {
            ::glfwSwapBuffers(reinterpret_cast<::GLFWwindow*>(this->window));

            return true;
        }
        bool
        engine_t::quit()
        {
            
            this->contex = nullptr;
            
            this->device = nullptr;

            this->window = nullptr;

            return true;
        }

        bool
        engine_t::proc(lib::event_t* event)
        {
            return true;
        }

    }
}

#endif /* GFX_CPP */