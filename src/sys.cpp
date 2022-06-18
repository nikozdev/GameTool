#ifndef SYS_CPP

#   define SYS_CPP

#   include "sys.hpp"
#   include "gfx.hpp"

#   include "windows.h"

#   include "../lib/glfw/src/glfw3.h"

namespace gt {

    namespace sys {

            static void
            glfw_call_elog(int errnum, const char* errstr)
            {
                GT_ELOG("[glfw]={errnum=(%d)errstr=(%s)}", errnum, errstr);
            }

            static void
            glfw_call_window_close(GLFWwindow* glfw_window)
            {
                window_t* window = reinterpret_cast<window_t*>(glfwGetWindowUserPointer(glfw_window));
                window_t::event_close_t event;
                window->proc(&event);
            }

            static void
            glfw_call_keybod(GLFWwindow* glfw_window, int kcode, int scode, int state, int modes)
            {
                window_t* window = reinterpret_cast<window_t*>(glfwGetWindowUserPointer(glfw_window));
                keybod_t::event_t event(kcode, state);
                window->get_keybod()->proc(&event);
            }

            static void
            glfw_call_cursor_click(GLFWwindow* glfw_window, int kcode, int state, int modes)
            {
                window_t* window = reinterpret_cast<window_t*>(::glfwGetWindowUserPointer(glfw_window));
                cursor_t::event_click_t event(kcode, state);
                window->get_cursor()->proc(&event);
            }
            static void
            glfw_call_cursor_coord(GLFWwindow* glfw_window, double pos_x, double pos_y)
            {
                window_t* window = reinterpret_cast<window_t*>(::glfwGetWindowUserPointer(glfw_window));
                cursor_t::event_coord_t event(pos_x, pos_y);
                window->get_cursor()->proc(&event);
            }
            static void
            glfw_call_cursor_scrol(GLFWwindow* glfw_window, double scrol_x, double scrol_y)
            {
                window_t* window = reinterpret_cast<window_t*>(::glfwGetWindowUserPointer(glfw_window));
                cursor_t::event_scrol_t event(scrol_x, scrol_y);
                window->get_cursor()->proc(&event);
            }

    }

    namespace sys {

        bool
        keybod_t::init()
        {
            this->button_array = new button_t[GLFW_KEY_LAST];
            ::memset(button_array, 0, sizeof(button_t)*GLFW_KEY_LAST);

            return true;
        }
        bool
        keybod_t::work()
        {
            
            int index = 0;
            do {
                
                button_t* button = &this->button_array[index];
                button->times++;

            } while(++index < GLFW_KEY_LAST);

            return true;
        }
        bool
        keybod_t::quit()
        {
            delete this->button_array;

            return true;
        }
        
        bool
        keybod_t::proc(event_t* event)
        {
            
            button_t* button = &button_array[event->kcode];
            if (button->state != event->state) {
                
                button->times = 0;
                button->state = event->state;
            
            }
            
            return true;
        }

    }

    namespace sys {
        
        bool
        cursor_t::init()
        {
            this->button_array = new button_t[GLFW_MOUSE_BUTTON_LAST];
            ::memset(button_array, 0, sizeof(button_t)*GLFW_MOUSE_BUTTON_LAST);

            return true;
        }
        bool
        cursor_t::work()
        {
            
            int index = 0;
            do {
                
            } while(++index < GLFW_MOUSE_BUTTON_LAST);

            return true;
        }
        bool
        cursor_t::quit()
        {
            delete this->button_array;
            
            return true;
        }

        bool
        cursor_t::proc(event_coord_t* event)
        {
            return true;
        }
        bool
        cursor_t::proc(event_click_t* event)
        {
            return true;
        }
        bool
        cursor_t::proc(event_scrol_t* event)
        {
            return true;
        }

    }

    namespace sys {

        bool
        window_t::init()
        {
            GT_CHECK(this->handle == nullptr, "window cannot init!", return false);
            
            ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            ::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            ::GLFWwindow* glfw_window = ::glfwCreateWindow(800, 600, "gametool", nullptr, nullptr);
            GT_CHECK(glfw_window != nullptr, "failed window creation!", return false);
            
            ::glfwSetWindowUserPointer(glfw_window, this);
            
            ::glfwSetKeyCallback(glfw_window, glfw_call_keybod);

            ::glfwSetMouseButtonCallback(glfw_window, glfw_call_cursor_click);
            ::glfwSetCursorPosCallback(glfw_window, glfw_call_cursor_coord);
            ::glfwSetScrollCallback(glfw_window, glfw_call_cursor_scrol);
            
            ::glfwSetWindowCloseCallback(glfw_window, glfw_call_window_close);

            this->handle = glfw_window;
            
            gfx::engine_t::get()->set_window(this->handle);
            
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

            glfwPollEvents();

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
            GT_CHECK(engine_t::get()->stop(), "failed engine stop attempt!", return false);

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
        engine_t::proc(lib::event_t* event)
        {
            if (event->get_kind() == event->get_kind<keybod_t::event_t>()) {

            }

            if (event->get_kind() == event->get_kind<cursor_t::event_coord_t>()) {
                
                return this->get_cursor()->proc(static_cast<cursor_t::event_coord_t*>(event));
            }

            return false;
        }

    }

}

#endif /* SYS_CPP */