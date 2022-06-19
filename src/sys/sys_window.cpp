#ifndef SYS_WINDOW_CPP

#   define SYS_WINDOW_CPP

#   include "sys_window.hpp"
#   include "sys_engine.hpp"

#   include "../app/app_engine.hpp"

#   define GLFW_EXPOSE_NATIVE_WIN32
#   include "../../lib/glfw/src/glfw3.h"
#   include "../../lib/glfw/src/glfw3native.h"

namespace gt {

    namespace sys {

            static void
            glfw_call_window_close(GLFWwindow* glfw_window)
            {
                window_t* window = reinterpret_cast<window_t*>(glfwGetWindowUserPointer(glfw_window));
                window_t::event_close_t event(true);
                window->proc(&event);

                app::engine_t::get()->proc(&event);
            }
            static void
                glfw_call_window_moved(GLFWwindow* glfw_window, int moved_x, int moved_y)
            {
                window_t* window = reinterpret_cast<window_t*>(glfwGetWindowUserPointer(glfw_window));
                window_t::event_moved_t event(moved_x, moved_y);
                window->proc(&event);

                app::engine_t::get()->proc(&event);
            }
            static void
                glfw_call_window_sized(GLFWwindow* glfw_window, int sized_w, int sized_h)
            {
                window_t* window = reinterpret_cast<window_t*>(glfwGetWindowUserPointer(glfw_window));
                window_t::event_sized_t event(sized_w, sized_h);
                window->proc(&event);

                app::engine_t::get()->proc(&event);
            }

            static void
            glfw_call_keybod(GLFWwindow* glfw_window, int kcode, int scode, int state, int modes)
            {
                window_t* window = reinterpret_cast<window_t*>(glfwGetWindowUserPointer(glfw_window));
                keybod_t::event_t event(static_cast<keybod_t::kcode_t>(kcode), static_cast<keybod_t::state_t>(state));
                window->get_keybod()->proc(&event);
                
                app::engine_t::get()->proc(&event);
            }

            static void
            glfw_call_cursor_click(GLFWwindow* glfw_window, int kcode, int state, int modes)
            {
                window_t* window = reinterpret_cast<window_t*>(::glfwGetWindowUserPointer(glfw_window));
                cursor_t::event_click_t event(static_cast<cursor_t::kcode_t>(kcode), static_cast<cursor_t::state_t>(state));
                window->get_cursor()->proc(&event);
            
                app::engine_t::get()->proc(&event);
            }
            static void
            glfw_call_cursor_coord(GLFWwindow* glfw_window, double pos_x, double pos_y)
            {
                window_t* window = reinterpret_cast<window_t*>(::glfwGetWindowUserPointer(glfw_window));
                cursor_t::event_coord_t event(pos_x, pos_y);
                window->get_cursor()->proc(&event);

                app::engine_t::get()->proc(&event);
            }
            static void
            glfw_call_cursor_scrol(GLFWwindow* glfw_window, double scrol_x, double scrol_y)
            {
                window_t* window = reinterpret_cast<window_t*>(::glfwGetWindowUserPointer(glfw_window));
                cursor_t::event_scrol_t event(scrol_x, scrol_y);
                window->get_cursor()->proc(&event);

                app::engine_t::get()->proc(&event);
            }

    }

    namespace sys {

        bool
            window_t::set_title(cstr_t title)
        {
            strcpy_s(this->title, title);

            ::glfwSetWindowTitle(reinterpret_cast<GLFWwindow*>(this->handle), this->title);

            return true;
        }

        bool
        window_t::init()
        {
            GT_CHECK(this->handle == nullptr, "window cannot init!", return false);
            
            ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            ::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            ::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            ::GLFWwindow* glfw_window = ::glfwCreateWindow(0x400, 0x300, "gametool", nullptr, nullptr);
            GT_CHECK(glfw_window != nullptr, "failed window creation!", return false);
            
            ::glfwSetWindowUserPointer(glfw_window, this);
            
            ::glfwSetKeyCallback(glfw_window, glfw_call_keybod);

            ::glfwSetMouseButtonCallback(glfw_window, glfw_call_cursor_click);
            ::glfwSetCursorPosCallback(glfw_window, glfw_call_cursor_coord);
            ::glfwSetScrollCallback(glfw_window, glfw_call_cursor_scrol);
            
            ::glfwSetWindowCloseCallback(glfw_window, glfw_call_window_close);
            ::glfwSetWindowPosCallback(glfw_window, glfw_call_window_moved);
            ::glfwSetWindowSizeCallback(glfw_window, glfw_call_window_sized);
            ::glfwSetFramebufferSizeCallback(glfw_window, glfw_call_window_sized);

            this->handle = glfw_window;
            
            GT_CHECK(this->keybod.init(),"keybod init error!", return false);
            GT_CHECK(this->cursor.init(),"cursor init error!", return false);

            return true;
        }
        bool
        window_t::work()
        {
            GT_CHECK(this->handle != nullptr, "window cannot work!", return false);

            GT_CHECK(this->keybod.work(),"keybod work error!", return false);
            GT_CHECK(this->cursor.work(),"cursor work error!", return false);

            auto timer = app::engine_t::get()->get_timer();
            auto delta = timer->get_delta();

            char title_format[GT_NAME_SIZE_MAX];
            sprintf_s(title_format, "[%s]=([delta]=(%.3lf)[fps]=(%.3lf))", this->title, delta, 1.0 / delta);
            ::glfwSetWindowTitle(reinterpret_cast<GLFWwindow*>(this->handle), title_format);

            ::glfwPollEvents();

            return true;
        }
        bool
        window_t::quit()
        {
            GT_CHECK(this->handle != nullptr, "window cannot quit!", return false);

            GT_CHECK(this->keybod.quit(),"keybod quit error!", return false);
            GT_CHECK(this->cursor.quit(),"cursor quit error!", return false);

            GLFWwindow* glfw_window = reinterpret_cast<GLFWwindow*>(this->handle);

            ::glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
            
            ::glfwDestroyWindow(glfw_window);

            this->handle = nullptr;
            
            return true;
        }

        bool
        window_t::proc(event_close_t* event)
        {

            return true;
        }
        bool
        window_t::proc(event_moved_t* event)
        {

            return true;
        }
        bool
        window_t::proc(event_sized_t* event)
        {
            return true;
        }

    }

}

#endif /* SYS_WINDOW_CPP */