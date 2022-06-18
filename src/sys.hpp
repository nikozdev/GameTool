#ifndef SYS_HPP

#   define SYS_HPP

#   include "lib.hpp"

#   ifndef GT_KEYBOD_HPP

/* The unknown key */
#       define GT_KEYBOD_BUTTON_UNKNOWN            -1

/* Printable keys */
#       define GT_KEYBOD_BUTTON_SPACE              32
#       define GT_KEYBOD_BUTTON_APOSTROPHE         39  /* ' */
#       define GT_KEYBOD_BUTTON_COMMA              44  /* , */
#       define GT_KEYBOD_BUTTON_MINUS              45  /* - */
#       define GT_KEYBOD_BUTTON_PERIOD             46  /* . */
#       define GT_KEYBOD_BUTTON_SLASH              47  /* / */
#       define GT_KEYBOD_BUTTON_0                  48
#       define GT_KEYBOD_BUTTON_1                  49
#       define GT_KEYBOD_BUTTON_2                  50
#       define GT_KEYBOD_BUTTON_3                  51
#       define GT_KEYBOD_BUTTON_4                  52
#       define GT_KEYBOD_BUTTON_5                  53
#       define GT_KEYBOD_BUTTON_6                  54
#       define GT_KEYBOD_BUTTON_7                  55
#       define GT_KEYBOD_BUTTON_8                  56
#       define GT_KEYBOD_BUTTON_9                  57
#       define GT_KEYBOD_BUTTON_SEMICOLON          59  /* ; */
#       define GT_KEYBOD_BUTTON_EQUAL              61  /* = */
#       define GT_KEYBOD_BUTTON_A                  65
#       define GT_KEYBOD_BUTTON_B                  66
#       define GT_KEYBOD_BUTTON_C                  67
#       define GT_KEYBOD_BUTTON_D                  68
#       define GT_KEYBOD_BUTTON_E                  69
#       define GT_KEYBOD_BUTTON_F                  70
#       define GT_KEYBOD_BUTTON_G                  71
#       define GT_KEYBOD_BUTTON_H                  72
#       define GT_KEYBOD_BUTTON_I                  73
#       define GT_KEYBOD_BUTTON_J                  74
#       define GT_KEYBOD_BUTTON_K                  75
#       define GT_KEYBOD_BUTTON_L                  76
#       define GT_KEYBOD_BUTTON_M                  77
#       define GT_KEYBOD_BUTTON_N                  78
#       define GT_KEYBOD_BUTTON_O                  79
#       define GT_KEYBOD_BUTTON_P                  80
#       define GT_KEYBOD_BUTTON_Q                  81
#       define GT_KEYBOD_BUTTON_R                  82
#       define GT_KEYBOD_BUTTON_S                  83
#       define GT_KEYBOD_BUTTON_T                  84
#       define GT_KEYBOD_BUTTON_U                  85
#       define GT_KEYBOD_BUTTON_V                  86
#       define GT_KEYBOD_BUTTON_W                  87
#       define GT_KEYBOD_BUTTON_X                  88
#       define GT_KEYBOD_BUTTON_Y                  89
#       define GT_KEYBOD_BUTTON_Z                  90
#       define GT_KEYBOD_BUTTON_LEFT_BRACKET       91  /* [ */
#       define GT_KEYBOD_BUTTON_BACKSLASH          92  /* \ */
#       define GT_KEYBOD_BUTTON_RIGHT_BRACKET      93  /* ] */
#       define GT_KEYBOD_BUTTON_GRAVE_ACCENT       96  /* ` */
#       define GT_KEYBOD_BUTTON_WORLD_1            161 /* non-US #1 */
#       define GT_KEYBOD_BUTTON_WORLD_2            162 /* non-US #2 */

/* Function keys */
#       define GT_KEYBOD_BUTTON_ESCAPE             256
#       define GT_KEYBOD_BUTTON_ENTER              257
#       define GT_KEYBOD_BUTTON_TAB                258
#       define GT_KEYBOD_BUTTON_BACKSPACE          259
#       define GT_KEYBOD_BUTTON_INSERT             260
#       define GT_KEYBOD_BUTTON_DELETE             261
#       define GT_KEYBOD_BUTTON_RIGHT              262
#       define GT_KEYBOD_BUTTON_LEFT               263
#       define GT_KEYBOD_BUTTON_DOWN               264
#       define GT_KEYBOD_BUTTON_UP                 265
#       define GT_KEYBOD_BUTTON_PAGE_UP            266
#       define GT_KEYBOD_BUTTON_PAGE_DOWN          267
#       define GT_KEYBOD_BUTTON_HOME               268
#       define GT_KEYBOD_BUTTON_END                269
#       define GT_KEYBOD_BUTTON_CAPS_LOCK          280
#       define GT_KEYBOD_BUTTON_SCROLL_LOCK        281
#       define GT_KEYBOD_BUTTON_NUM_LOCK           282
#       define GT_KEYBOD_BUTTON_PRINT_SCREEN       283
#       define GT_KEYBOD_BUTTON_PAUSE              284
#       define GT_KEYBOD_BUTTON_F1                 290
#       define GT_KEYBOD_BUTTON_F2                 291
#       define GT_KEYBOD_BUTTON_F3                 292
#       define GT_KEYBOD_BUTTON_F4                 293
#       define GT_KEYBOD_BUTTON_F5                 294
#       define GT_KEYBOD_BUTTON_F6                 295
#       define GT_KEYBOD_BUTTON_F7                 296
#       define GT_KEYBOD_BUTTON_F8                 297
#       define GT_KEYBOD_BUTTON_F9                 298
#       define GT_KEYBOD_BUTTON_F10                299
#       define GT_KEYBOD_BUTTON_F11                300
#       define GT_KEYBOD_BUTTON_F12                301
#       define GT_KEYBOD_BUTTON_F13                302
#       define GT_KEYBOD_BUTTON_F14                303
#       define GT_KEYBOD_BUTTON_F15                304
#       define GT_KEYBOD_BUTTON_F16                305
#       define GT_KEYBOD_BUTTON_F17                306
#       define GT_KEYBOD_BUTTON_F18                307
#       define GT_KEYBOD_BUTTON_F19                308
#       define GT_KEYBOD_BUTTON_F20                309
#       define GT_KEYBOD_BUTTON_F21                310
#       define GT_KEYBOD_BUTTON_F22                311
#       define GT_KEYBOD_BUTTON_F23                312
#       define GT_KEYBOD_BUTTON_F24                313
#       define GT_KEYBOD_BUTTON_F25                314
#       define GT_KEYBOD_BUTTON_KP_0               320
#       define GT_KEYBOD_BUTTON_KP_1               321
#       define GT_KEYBOD_BUTTON_KP_2               322
#       define GT_KEYBOD_BUTTON_KP_3               323
#       define GT_KEYBOD_BUTTON_KP_4               324
#       define GT_KEYBOD_BUTTON_KP_5               325
#       define GT_KEYBOD_BUTTON_KP_6               326
#       define GT_KEYBOD_BUTTON_KP_7               327
#       define GT_KEYBOD_BUTTON_KP_8               328
#       define GT_KEYBOD_BUTTON_KP_9               329
#       define GT_KEYBOD_BUTTON_KP_DECIMAL         330
#       define GT_KEYBOD_BUTTON_KP_DIVIDE          331
#       define GT_KEYBOD_BUTTON_KP_MULTIPLY        332
#       define GT_KEYBOD_BUTTON_KP_SUBTRACT        333
#       define GT_KEYBOD_BUTTON_KP_ADD             334
#       define GT_KEYBOD_BUTTON_KP_ENTER           335
#       define GT_KEYBOD_BUTTON_KP_EQUAL           336
#       define GT_KEYBOD_BUTTON_LEFT_SHIFT         340
#       define GT_KEYBOD_BUTTON_LEFT_CONTROL       341
#       define GT_KEYBOD_BUTTON_LEFT_ALT           342
#       define GT_KEYBOD_BUTTON_LEFT_SUPER         343
#       define GT_KEYBOD_BUTTON_RIGHT_SHIFT        344
#       define GT_KEYBOD_BUTTON_RIGHT_CONTROL      345
#       define GT_KEYBOD_BUTTON_RIGHT_ALT          346
#       define GT_KEYBOD_BUTTON_RIGHT_SUPER        347
#       define GT_KEYBOD_BUTTON_MENU               348

#       define GT_KEYBOD_BUTTON_LAST               GT_KEYBOD_BUTTON_MENU

#   endif /* GT_KEYBOD_HPP */

#   ifndef GT_CURSOR_HPP

#       define GLFW_CURSOR_BUTTON_1         0
#       define GLFW_CURSOR_BUTTON_2         1
#       define GLFW_CURSOR_BUTTON_3         2
#       define GLFW_CURSOR_BUTTON_4         3
#       define GLFW_CURSOR_BUTTON_5         4
#       define GLFW_CURSOR_BUTTON_6         5
#       define GLFW_CURSOR_BUTTON_7         6
#       define GLFW_CURSOR_BUTTON_8         7
#       define GLFW_CURSOR_BUTTON_LAST      GLFW_CURSOR_BUTTON_8
#       define GLFW_CURSOR_BUTTON_LEFT      GLFW_CURSOR_BUTTON_1
#       define GLFW_CURSOR_BUTTON_RIGHT     GLFW_CURSOR_BUTTON_2
#       define GLFW_CURSOR_BUTTON_MIDDLE    GLFW_CURSOR_BUTTON_3

#   endif /* GT_CURSOR_HPP */

namespace gt {

    namespace sys {

        class keybod_t {
        
        public:
        
            using this_t    = keybod_t;
            
            typedef struct button_t {

                int kcode;
                int state;
                int times;

            } button_t;

            class event_t : public lib::event_t {
            
            public:

                event_t(int kcode, int state) : 
                    lib::event_t(get_kind<event_t>()),
                    kcode(kcode), state(state)
                {
                }

            public:
            
                int kcode;
                int state;

            };

        public:

            inline button_t
            get_button(int index) const
            {
                return this->button_array[index];
            }
            inline int
            get_button_state(int index) const
            {
                return this->button_array[index].state;
            }
            inline int
            get_button_times(int index) const
            {
                return this->button_array[index].times;
            }

            inline bool
            vet_button_raise(int index) const
            {
                return this->get_button_times(index) == 0u && this->get_button_state(index) == 0u;
            }
            inline bool
            vet_button_press(int index) const
            {
                return this->get_button_times(index) == 0u && this->get_button_state(index) == 1u;
            }

            inline bool
            vet_button_free(int index) const
            {
                return this->get_button_times(index) >= 1u && this->get_button_state(index) == 0u;
            }
            inline bool
            vet_button_held(int index) const
            {
                return this->get_button_times(index) >= 1u && this->get_button_state(index) == 1u;
            }
        
        public:

            bool
            init();
            bool
            work();
            bool
            quit();

            bool
            proc(event_t* event);

        private:

            button_t* button_array;

        };

        class cursor_t {
        
        public:

            using this_t    = cursor_t;
            
            typedef struct button_t {
                
                double  coord_held_x;
                double  coord_held_y;
                
                double  coord_free_x;
                double  coord_free_y;

                int     kcode;
                int     state;

            };
            
            class event_click_t : public lib::event_t {
                
            public:

                event_click_t(int kcode, int state) :
                    lib::event_t(get_kind<event_click_t>()),
                    kcode(kcode), state(state)
                {
                }

            public:

                const int       kcode;
                const int       state;

            };
            class event_coord_t : public lib::event_t {
                
            public:

                event_coord_t(double coord_x, double coord_y) :
                    lib::event_t(get_kind<event_coord_t>()),
                    coord_x(coord_x), coord_y(coord_y)
                {
                }
            
            public:

                const double coord_x;
                const double coord_y;

            };
            class event_scrol_t : public lib::event_t {
                
            public:

                event_scrol_t(double scrol_x, double scrol_y) :
                    lib::event_t(get_kind<event_scrol_t>()),
                    scrol_x(scrol_x), scrol_y(scrol_y)
                {
                }
            
            public:

                const double scrol_x;
                const double scrol_y;

            };

        public:

            inline button_t
            get_button(int index) const
            {
                return this->button_array[index];
            }
            inline int
            get_button_state(int index) const
            {
                return this->button_array[index].state;
            }
        
        public:

            bool
            init();
            bool
            work();
            bool
            quit();

            bool
            proc(event_click_t* event);
            bool
            proc(event_coord_t* event);
            bool
            proc(event_scrol_t* event);

        private:

            button_t*   button_array;
            
            double      coord_x;
            double      coord_y;

            double      scrol_x;
            double      scrol_y;

        };

    }

    namespace sys {
        
        class window_t {
        
        public:

            using this_t    = window_t;
            
            using handle_t  = void*;
            
            class event_close_t : public lib::event_t {
                
            public:

                event_close_t() :
                    lib::event_t(get_kind<event_close_t>())
                {
                }
            
            public:

            };
            class event_moved_t : public lib::event_t {
                
            public:

                event_moved_t(double coord_x, double coord_y) :
                    lib::event_t(get_kind<event_moved_t>()),
                    coord_x(coord_x), coord_y(coord_y)
                {
                }

            public:

                const int   coord_x;
                const int   coord_y;

            };
            class event_sized_t : public lib::event_t {
                
            public:

                event_sized_t(int sized_x, int sized_y) :
                    lib::event_t(get_kind<event_sized_t>()),
                    sized_x(sized_x), sized_y(sized_y)
                {
                }

            public:

                const int   sized_x;
                const int   sized_y;

            };

        public:

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

            handle_t handle;

            keybod_t keybod;
            cursor_t cursor;

        };
            
    }

    namespace sys {

        class engine_t : public lib::engine_t<engine_t> {

        public:

            inline window_t*
            get_window()
            {
                return &this->window;
            }
            inline cursor_t*
            get_cursor()
            {
                return this->get_window()->get_cursor();
            }
            inline keybod_t*
            get_keybod()
            {
                return this->get_window()->get_keybod();
            }

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

            window_t window;

        };

    }

}

#endif /* SYS_HPP */