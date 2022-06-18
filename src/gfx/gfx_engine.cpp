#ifndef GFX_ENGINE_CPP

#   define GFX_ENGINE_CPP

#   include "gfx_engine.hpp"

#   include "../sys/sys_engine.hpp"

#   include "../../lib/glad/src/glad.h"

#   define GLFW_EXPOSE_NATIVE_WIN32
#   include "../../lib/glfw/src/glfw3.h"
#   include "../../lib/glfw/src/glfw3native.h"

namespace gt {

    namespace gfx {

        bool
            engine_t::set_viewport(int x, int y, int w, int h)
        {
            this->state.viewport = { x, y, w, h };
            
            glViewport(x, y, w, h);

            return true;
        }

        bool
            engine_t::set_clear_color(float r, float g, float b, float a)
        {
            glClearColor(r, g, b, a);

            this->state.clear_color = { r, g, b, a };

            return true;
        }

        bool
            engine_t::init()
        {
            this->window = sys::engine_t::get()->get_window()->get_handle();
            GT_CHECK(this->window != nullptr, "cannot get system window handle!", return false);

            ::GLFWwindow* glfw_window = reinterpret_cast<::GLFWwindow*>(this->window);
            ::glfwMakeContextCurrent(glfw_window);

            ::HWND hwnd = ::glfwGetWin32Window(glfw_window);
            GT_CHECK(hwnd != NULL, "failed to get the platform window!", return false);
            this->device = ::GetWindowDC(hwnd);
            GT_CHECK(this->device != nullptr, "failed to get the graphics device!", return false);

            this->contex = ::wglGetCurrentContext();
            GT_CHECK(this->contex != nullptr, "failed to get the graphics context!", return false);

            ::glfwSwapInterval(1u);
            glfwGetWindowSize(glfw_window, &this->state.viewport.w, &this->state.viewport.h);

            GT_CHECK(::gladLoadGL(), "failed gladLoadGL!", return false);

            glEnable(GL_BLEND);

            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);

            this->set_clear_color(0.125,0.250,0.500,1.000);
            this->set_viewport(this->state.viewport.x, this->state.viewport.y, this->state.viewport.w, this->state.viewport.h);

            this->set_flag(true);

            return true;
        }
        bool
            engine_t::work()
        {

            glClear(GL_COLOR_BUFFER_BIT);

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
            engine_t::proc(lib::event_a_t* event)
        {
            
            if (event->has_kind<sys::cursor_t::event_coord_t>()) {

                auto evt = static_cast<sys::cursor_t::event_coord_t*>(event);
                
                float cursor_x = static_cast<float>(evt->coord_x);
                float cursor_y = static_cast<float>(evt->coord_y);
                float window_w = static_cast<float>(this->state.viewport.w);
                float window_h = static_cast<float>(this->state.viewport.h);

                this->set_clear_color(this->state.clear_color.r,cursor_x/window_w,cursor_y/window_h,this->state.clear_color.a);

                return true;
            }

            if (event->has_kind<sys::cursor_t::event_coord_t>()) {

                auto evt = static_cast<sys::cursor_t::event_coord_t*>(event);

                return true;
            }

            if (event->has_kind<sys::window_t::event_sized_t>()) {
                
                auto evt = static_cast<sys::window_t::event_sized_t*>(event);
                
                return this->set_viewport(0, 0, evt->sized_x, evt->sized_y);
            }

            return true;
        }

    }

}

#endif /* GFX_ENGINE_CPP */