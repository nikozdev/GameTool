#ifndef SYS_KEYBOD_HPP

#   define SYS_KEYBOD_HPP

#   include "../cfg.hpp"

#   include "../lib/lib_event.hpp"

namespace gt {
    
    namespace sys {

        class keybod_t {
        
        public:
        
            using this_t    = keybod_t;
            
            enum kcode_t : int {
                /* the unknown key */
                KCODE_UNKNOWN           = -1,
                /* printable keys */
                KCODE_SPACE             = 32,
                KCODE_APOSTROPHE        = 39,  /* ' */
                KCODE_COMMA             = 44,  /* , */
                KCODE_MINUS             = 45,  /* - */
                KCODE_PERIOD            = 46,  /* . */
                KCODE_SLASH             = 47,  /* / */
                KCODE_0                 = 48,
                KCODE_1                 = 49,
                KCODE_2                 = 50,
                KCODE_3                 = 51,
                KCODE_4                 = 52,
                KCODE_5                 = 53,
                KCODE_6                 = 54,
                KCODE_7                 = 55,
                KCODE_8                 = 56,
                KCODE_9                 = 57,
                KCODE_SEMICOLON         = 59,  /* ; */
                KCODE_EQUAL             = 61,  /* = */
                KCODE_A                 = 65,
                KCODE_B                 = 66,
                KCODE_C                 = 67,
                KCODE_D                 = 68,
                KCODE_E                 = 69,
                KCODE_F                 = 70,
                KCODE_G                 = 71,
                KCODE_H                 = 72,
                KCODE_I                 = 73,
                KCODE_J                 = 74,
                KCODE_K                 = 75,
                KCODE_L                 = 76,
                KCODE_M                 = 77,
                KCODE_N                 = 78,
                KCODE_O                 = 79,
                KCODE_P                 = 80,
                KCODE_Q                 = 81,
                KCODE_R                 = 82,
                KCODE_S                 = 83,
                KCODE_T                 = 84,
                KCODE_U                 = 85,
                KCODE_V                 = 86,
                KCODE_W                 = 87,
                KCODE_X                 = 88,
                KCODE_Y                 = 89,
                KCODE_Z                 = 90,
                KCODE_LEFT_BRACKET      = 91,  /* [ */
                KCODE_BACKSLASH         = 92,  /* \ */
                KCODE_RIGHT_BRACKET     = 93,  /* ] */
                KCODE_GRAVE_ACCENT      = 96,  /* ` */
                KCODE_WORLD_1           = 161, /* non-US #1 */
                KCODE_WORLD_2           = 162, /* non-US #2 */
                /* function keys */
                KCODE_ESCAPE            = 256,
                KCODE_ENTER             = 257,
                KCODE_TAB               = 258,
                KCODE_BACKSPACE         = 259,
                KCODE_INSERT            = 260,
                KCODE_DELETE            = 261,
                KCODE_RIGHT             = 262,
                KCODE_LEFT              = 263,
                KCODE_DOWN              = 264,
                KCODE_UP                = 265,
                KCODE_PAGE_UP           = 266,
                KCODE_PAGE_DOWN         = 267,
                KCODE_HOME              = 268,
                KCODE_END               = 269,
                KCODE_CAPS_LOCK         = 280,
                KCODE_SCROLL_LOCK       = 281,
                KCODE_NUM_LOCK          = 282,
                KCODE_PRINT_SCREEN      = 283,
                KCODE_PAUSE             = 284,
                KCODE_F1                = 290,
                KCODE_F2                = 291,
                KCODE_F3                = 292,
                KCODE_F4                = 293,
                KCODE_F5                = 294,
                KCODE_F6                = 295,
                KCODE_F7                = 296,
                KCODE_F8                = 297,
                KCODE_F9                = 298,
                KCODE_F10               = 299,
                KCODE_F11               = 300,
                KCODE_F12               = 301,
                KCODE_F13               = 302,
                KCODE_F14               = 303,
                KCODE_F15               = 304,
                KCODE_F16               = 305,
                KCODE_F17               = 306,
                KCODE_F18               = 307,
                KCODE_F19               = 308,
                KCODE_F20               = 309,
                KCODE_F21               = 310,
                KCODE_F22               = 311,
                KCODE_F23               = 312,
                KCODE_F24               = 313,
                KCODE_F25               = 314,
                KCODE_KP_0              = 320,
                KCODE_KP_1              = 321,
                KCODE_KP_2              = 322,
                KCODE_KP_3              = 323,
                KCODE_KP_4              = 324,
                KCODE_KP_5              = 325,
                KCODE_KP_6              = 326,
                KCODE_KP_7              = 327,
                KCODE_KP_8              = 328,
                KCODE_KP_9              = 329,
                KCODE_KP_DECIMAL        = 330,
                KCODE_KP_DIVIDE         = 331,
                KCODE_KP_MULTIPLY       = 332,
                KCODE_KP_SUBTRACT       = 333,
                KCODE_KP_ADD            = 334,
                KCODE_KP_ENTER          = 335,
                KCODE_KP_EQUAL          = 336,
                KCODE_LEFT_SHIFT        = 340,
                KCODE_LEFT_CONTROL      = 341,
                KCODE_LEFT_ALT          = 342,
                KCODE_LEFT_SUPER        = 343,
                KCODE_RIGHT_SHIFT       = 344,
                KCODE_RIGHT_CONTROL     = 345,
                KCODE_RIGHT_ALT         = 346,
                KCODE_RIGHT_SUPER       = 347,
                KCODE_MENU              = 348,
                /* the last key == count */
                KCODE_LAST              = KCODE_MENU,
                KCODE_COUNT             = KCODE_LAST,
            };

            enum state_t : int {
                /* momental */
                STATE_RAISE = 0b00,
                STATE_PRESS = 0b01,
                /* continous */
                STATE_FREE  = 0b11,
                STATE_HELD  = 0b10,
                /* the last state == count */
                STATE_LAST  = 0b100,
                STATE_COUNT = STATE_LAST,
            };

            typedef struct button_t {

                state_t state;
                count_t times;

            } button_t;

            class event_t : public lib::event_t_t<event_t> {
            
            public:

                event_t(kcode_t kcode, state_t state) : 
                    kcode(kcode), state(state)
                {
                }

            public:
            
                const kcode_t kcode;
                const state_t state;

            };

        public:

            inline button_t
            get_button(kcode_t kcode) const
            {
                return this->button_array[kcode];
            }
            inline state_t
            get_button_state(kcode_t kcode) const
            {
                return this->button_array[kcode].state;
            }
            inline count_t
            get_button_times(kcode_t kcode) const
            {
                return this->button_array[kcode].times;
            }

            inline bool
            vet_button_raise(kcode_t kcode) const
            {
                return this->get_button_times(kcode) == 0u && this->get_button_state(kcode) == 0u;
            }
            inline bool
            vet_button_press(kcode_t kcode) const
            {
                return this->get_button_times(kcode) == 0u && this->get_button_state(kcode) == 1u;
            }

            inline bool
            vet_button_free(kcode_t kcode) const
            {
                return this->get_button_times(kcode) >= 1u && this->get_button_state(kcode) == 0u;
            }
            inline bool
            vet_button_held(kcode_t kcode) const
            {
                return this->get_button_times(kcode) >= 1u && this->get_button_state(kcode) == 1u;
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

    }

}

#endif /* SYS_KEYBOD_HPP */