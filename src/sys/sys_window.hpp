#ifndef SYS_WINDOW_HPP

#   define SYS_WINDOW_HPP

#   include "sys_cursor.hpp"
#   include "sys_keybod.hpp"

#   include "../lib/lib_event.hpp"
#   include "../lib/lib_vector.hpp"

namespace gt {

    namespace sys {

        class window_t {

        public:

            using this_t = window_t;

            using handle_t = void*;

            class event_close_t : public lib::event_t_t<event_close_t> {

            public:

                event_close_t(bool close) :
                    close(close)
                {
                }

            public:

                const bool close;

            };
            class event_moved_t : public lib::event_t_t<event_moved_t> {

            public:

                event_moved_t(double coord_x, double coord_y) :
                    coord_x(coord_x), coord_y(coord_y)
                {
                }

            public:

                const int   coord_x;
                const int   coord_y;

            };
            class event_sized_t : public lib::event_t_t<event_sized_t> {

            public:

                event_sized_t(int sized_x, int sized_y) :
                    sized_x(sized_x), sized_y(sized_y)
                {
                }

            public:

                const int   sized_x;
                const int   sized_y;

            };

        public:

            inline v2u_t
                get_sizes() const
            {
                return { this->viewp[0], this->viewp[1] };
            }
            inline v2u_t
                get_coord() const
            {
                return { this->viewp[2], this->viewp[3] };
            }
            inline v4u_t
                get_viewp() const
            {
                return this->viewp;
            }

            inline cstr_t
                get_title() const
            {
                return this->title;
            }

            inline handle_t
                get_handle()
            {
                return this->handle;
            }

            inline cursor_t*
                get_cursor()
            {
                return &this->cursor;
            }
            inline const cursor_t*
                get_cursor() const
            {
                return &this->cursor;
            }

            inline keybod_t*
                get_keybod()
            {
                return &this->keybod;
            }
            inline const keybod_t*
                get_keybod() const
            {
                return &this->keybod;
            }

            bool
                set_title(cstr_t title);

        public:

            bool
                init();
            bool
                work();
            bool
                quit();

            bool
                proc(event_close_t* event);
            bool
                proc(event_moved_t* event);
            bool
                proc(event_sized_t* event);

        private:

            v4u_t viewp;

            char title[GT_NAME_SIZE_USE];

            handle_t handle;

            keybod_t keybod;
            cursor_t cursor;

        };

    }

}

#endif /* SYS_WINDOW_HPP */